/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU
 
http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "stdneb.h"
#include "GLESCompiler.h"
#include "shadercompiler/ShaderElement.h"
#include "shadercompiler/ShaderCompilerSetting.h"
#include "MojoShaderTool.h"

#include "hlsl2glslfork/hlsl2glsl.h"
#include "GlslOptimizer/glsl_optimizer.h"
#include "Utility/ShaderCompilerUtil.h"
#include "rendersystem/RenderSystem.h"


namespace ShaderProgramCompiler
{

static void Destroy(const ShHandle& handleVs, const ShHandle& handlePs)
{
	Hlsl2Glsl_DestructCompiler( handleVs );
	Hlsl2Glsl_DestructCompiler( handlePs );
}

static char g_sHighPrecision[] = "#ifdef GL_FRAGMENT_PRECISION_HIGH \n" 
	"precision highp float; \n" 
	"#else \n"
	"precision mediump float; \n"
	"#endif \n";

static char g_sColorConvert[] = "(gles_Color / 255.0)";


	__ImplementClass(GLESCompiler,'GLCP', GpuProgramCompiler);

GLESCompiler::GLESCompiler()
: m_pOptCtx(NULL)
{

}

GLESCompiler::~GLESCompiler()
{

}

void GLESCompiler::InitCompiler()
{
#if RENDERDEVICE_OPENGLES
	Super::InitCompiler();
	
	for (IndexT i = 0; i < 8; ++i)
	{
		Util::String glCoord;
		Util::String glesCoord;
		glCoord.Format("gl_MultiTexCoord%d", i);
		glesCoord.Format("gles_MultiTexCoord%d", i);
		m_GLKeyWords2GLESKeyWords.Add(glCoord, glesCoord);
	}

	m_GLKeyWords2GLESKeyWords.Add("gl_Vertex", "gles_Vertex");
	m_GLKeyWords2GLESKeyWords.Add("gl_Color", "gles_Color");
	m_GLKeyWords2GLESKeyWords.Add("gl_Normal", "gles_Normal");

	Hlsl2Glsl_Initialize();

	m_pOptCtx = glslopt_initialize(true);

	ShaderUtil::ReadText("sys:common.wjh", m_sIncludeContent);

	const RenderBase::GraphicCardCapability& caps = RenderBase::RenderSystem::Instance()->GetGraphicCardCapability();
	SizeT nMaxBoneBySubmesh = (caps.mMaxUniformVectors-16)/4;

	Util::String strArraySize;
	strArraySize.Format(" float4x4 gFinalXForms[%d]; \n",nMaxBoneBySubmesh);
	m_sIncludeContent += strArraySize;
#endif

}

void GLESCompiler::Close()
{
	Hlsl2Glsl_Finalize();

	glslopt_cleanup(m_pOptCtx);
}

void GLESCompiler::Compile(ShaderPass* pPass)
{
	_Compile(pPass);

	_AfterCompile();
}

bool GLESCompiler::_Compile(const ShaderPass* pPass)
{
	const CommonShaderSetting& cs = pPass->GetCommonSetting();
	const CommonShaderSetting::ShaderType& st = cs.GetShaderType();

	if (st == CommonShaderSetting::Pixel)
	{
		m_sCompiledCode = ""; 
		return false;
	}

	_BeforeCompile(pPass);

	ShaderMarcro sdkInfo;
	sdkInfo.name  = "GLES";
	sdkInfo.value = "1";

	m_Macros.Append(sdkInfo);

	if (!cs.HasEntry(CommonShaderSetting::Vertex) || !cs.HasEntry(CommonShaderSetting::Pixel))
	{
		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("GLES Shader needs Vertex And Pixel Shader!!!\n", ""),
			GET_FUNCTION_NAME()
			);
		return false;
	}

	const Util::String& source = pPass->GetCode();

	Util::String code =  m_sIncludeContent + source;

	Util::String macros;

	SizeT nMacros = m_Macros.Size();
	for (IndexT i = 0; i < nMacros; ++i)
	{
		macros += "#define " + m_Macros[i].name + " " + m_Macros[i].value+"\n";
	}

	code = macros + code;

	bool bRes = MojoShaderTool::Instance()->MojoPreprocess(code);

	if (!bRes)
	{
		return false;
	}

	_HLSL2GLSL(pPass, code.AsCharPtr());

	return true;
}

void GLESCompiler::_HLSL2GLSL(const ShaderPass* pPass, const char* pSource)
{
#if RENDERDEVICE_OPENGLES
	ShHandle vertexParser = Hlsl2Glsl_ConstructCompiler( EShLangVertex );
	ShHandle pixelParser  = Hlsl2Glsl_ConstructCompiler( EShLangFragment );

	IndexT parseVsOk = Hlsl2Glsl_Parse (vertexParser, pSource, ETranslateOpUsePrecision);
	IndexT parsePsOk = Hlsl2Glsl_Parse (pixelParser, pSource, ETranslateOpUsePrecision);

	if (parseVsOk && parsePsOk)
	{
		static EAttribSemantic kAttribSemantic[] = {
			EAttrSemTangent,
		};
		static const char* kAttribString[] = {
			"TANGENT",
		};

		Hlsl2Glsl_SetUserAttributeNames (vertexParser, kAttribSemantic, kAttribString, 1);
		Hlsl2Glsl_SetUserAttributeNames (pixelParser, kAttribSemantic, kAttribString, 1);
		Hlsl2Glsl_UseUserVaryings (vertexParser, true);
		Hlsl2Glsl_UseUserVaryings (pixelParser, true);

		const CommonShaderSetting& cs = pPass->GetCommonSetting();

		const Util::String& vertexEntry = cs.GetEntryName(CommonShaderSetting::Vertex);
		const Util::String& pixelEntry  = cs.GetEntryName(CommonShaderSetting::Pixel);

		IndexT translateVsOk = Hlsl2Glsl_Translate (vertexParser, vertexEntry.AsCharPtr(), ETranslateOpUsePrecision);
		IndexT translatePsOk = Hlsl2Glsl_Translate( pixelParser, pixelEntry.AsCharPtr(), ETranslateOpUsePrecision );

		if (translateVsOk && translatePsOk)
		{
			Util::String vertexCode = Hlsl2Glsl_GetShader( vertexParser );
			Util::String pixelCode  = Hlsl2Glsl_GetShader( pixelParser );


			vertexCode = _SubsitituteGLKeyWords(vertexCode);

			_OptimizeGLES(vertexCode, pixelCode);

			const RenderBase::GraphicCardCapability& caps = RenderBase::RenderSystem::Instance()->GetGraphicCardCapability();

			if ( (caps.mHighFloatRange[0] == 0 &&
				caps.mHighFloatRange[1] == 0) ||
				caps.mHighFloatPrecision == 0 || !caps.mFragmentHightPrecision)
			{
				pixelCode = g_sHighPrecision + pixelCode;
			}

			IndexT colorIndex = vertexCode.FindStringIndex("gles_Color");
			if (colorIndex != InvalidIndex)
			{
				IndexT ret = vertexCode.FindStringIndex("{", colorIndex);

				if (ret != InvalidIndex)
				{
					colorIndex = vertexCode.FindStringIndex("gles_Color", ret);

					if (colorIndex != InvalidIndex)
					{
						vertexCode = vertexCode.EraseRange(colorIndex, strlen("gles_Color"));
						vertexCode = vertexCode.InsertRange(colorIndex, g_sColorConvert);
					}
				}
			}


			m_sCompiledCode += "VertexBegin\n"   + vertexCode + "\nVertexEnd\n";
			m_sCompiledCode += "PixelBegin\n" + pixelCode  + "\nPixelEnd\n";

			Destroy(vertexParser, pixelParser);
		} 
		else
		{
			if (!translateVsOk)
			{
				const char* infoLog = Hlsl2Glsl_GetInfoLog( vertexParser );

				Destroy(vertexParser, pixelParser);

				SYS_EXCEPT(Exceptions::ShaderException, 
					STRING_FORMAT("Translate Vertex Shader Error: %s \n", infoLog),
					GET_FUNCTION_NAME()
					);
			}
			
			if (!translatePsOk)
			{
				const char* infoLog = Hlsl2Glsl_GetInfoLog( pixelParser );

				Destroy(vertexParser, pixelParser);

				SYS_EXCEPT(Exceptions::ShaderException, 
					STRING_FORMAT("Translate Pixel Shader Error: %s \n", infoLog),
					GET_FUNCTION_NAME()
					);
			}
			
			
		}


	}
	else
	{
		if (!vertexParser)
		{
			const char* infoLog = Hlsl2Glsl_GetInfoLog( vertexParser );

			Destroy(vertexParser, pixelParser);

			SYS_EXCEPT(Exceptions::ShaderException, 
				STRING_FORMAT("Parsing Vertex Error When Convert HLSL to GLSL: %s \n", infoLog),
				GET_FUNCTION_NAME()
				);
		}

		if (!pixelParser)
		{
			const char* infoLog = Hlsl2Glsl_GetInfoLog( pixelParser );

			Destroy(vertexParser, pixelParser);

			SYS_EXCEPT(Exceptions::ShaderException, 
				STRING_FORMAT("Parsing Pixel Error When Convert HLSL to GLSL: %s \n", infoLog),
				GET_FUNCTION_NAME()
				);
		}		

	}

	
#endif
}

Util::String GLESCompiler::_SubsitituteGLKeyWords(const Util::String& source) const
{

	Util::String reDefine;
	IndexT nCount = m_GLKeyWords2GLESKeyWords.Size();
	for (IndexT i = 0; i < nCount; ++i)
	{
		const Util::String& glKeyWord   = m_GLKeyWords2GLESKeyWords.KeyAtIndex(i);
		const Util::String& glesKeyWord = m_GLKeyWords2GLESKeyWords.ValueAtIndex(i);

		IndexT res = source.FindStringIndex(glKeyWord);

		if (res != InvalidIndex)
		{
			if (glKeyWord == "gl_Normal")
			{
				Util::String str;
				str.Format("#define %s %s\n", glKeyWord.AsCharPtr(), glesKeyWord.AsCharPtr());
				reDefine += str;

				str.Format("attribute vec3 %s;\n", glesKeyWord.AsCharPtr());
				reDefine += str;
			} 
			else
			{
				Util::String str;

				str.Format("#define %s %s\n", glKeyWord.AsCharPtr(), glesKeyWord.AsCharPtr() );
				reDefine += str;
				str.Format("attribute vec4 %s;\n", glesKeyWord.AsCharPtr());
				reDefine += str;
			}
		}
	}

	reDefine += source;

	reDefine.SubstituteString("\t", " ");

	return reDefine;
}

void GLESCompiler::_OptimizeGLES(Util::String& vertSource, Util::String& pixelSource)
{
	glslopt_shader* pVertShader = glslopt_optimize(m_pOptCtx, kGlslOptShaderVertex, vertSource.AsCharPtr(), 0);

	if (glslopt_get_status (pVertShader))
	{
		vertSource = glslopt_get_output (pVertShader);
	}
	else
	{		
		n_warning("Vertex Shader optimization failed\n");

		const char* log = glslopt_get_log (pVertShader);

		n_warning(log);

		vertSource.SubstituteString("#line", "//#line");
	}

	glslopt_shader_delete (pVertShader);

	glslopt_shader* pPixelShader = glslopt_optimize(m_pOptCtx, kGlslOptShaderFragment, pixelSource.AsCharPtr(), 0);

	if (glslopt_get_status (pPixelShader))
	{
		pixelSource = glslopt_get_output (pPixelShader);
	}
	else
	{		
		n_warning("Pixel Shader optimization failed\n");

		const char* log = glslopt_get_log (pPixelShader);

		n_warning(log);

		pixelSource.SubstituteString("#line", "//#line");
	}

	glslopt_shader_delete (pPixelShader);

}

}
