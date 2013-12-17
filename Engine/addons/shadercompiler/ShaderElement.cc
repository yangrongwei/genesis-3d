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
#include "ShaderElement.h"
#include "Utility/ShaderCompilerUtil.h"
#include "ShaderCompiler.h"
#include "ShaderTemplate/ShaderJoint.h"

namespace ShaderProgramCompiler
{
	__ImplementClass(ShaderBasis,'SHBS',Core::RefCounted);

ShaderBasis::ShaderBasis()
{

}

ShaderBasis::~ShaderBasis()
{

}


	__ImplementClass(ShaderPass,'SHPA', ShaderBasis);

ShaderPass::ShaderPass()
	: m_bNeedCompileVertex(false),
	  m_bNeedCompilePixel(false),
	  m_bNeedCompileCompositive(false)
{
	m_CompilerKeyWords.Append("VertexShader");
	m_CompilerKeyWords.Append("PixelShader");
	m_CompilerKeyWords.Append("Template");
}

ShaderPass::~ShaderPass()
{

}

bool ShaderPass::Parse()
{
	bool res = _ParseCompilerStage();
		
	if (m_CommonShaderSetting.HasEntry(CommonShaderSetting::Template))
	{
		res &= _ParseParameterStage();
	}

	_AnalyzeShaderType();

	return res;
}

bool ShaderPass::_ParseCompilerStage()
{

	for (IndexT i = 0; i < m_CompilerKeyWords.Size(); ++i)
	{
		const Util::String& entryName = m_CompilerKeyWords[i];

		IndexT pos = m_sCompiler.FindStringIndex(entryName);

		if (pos != InvalidIndex)
		{
			IndexT nCR = m_sCompiler.FindCharIndex('\n', pos);
			Util::String sEntry; 
			if (nCR != InvalidIndex)
			{
				sEntry = m_sCompiler.ExtractRange(pos, nCR - pos + 1); 
			}

			IndexT bEqual = sEntry.FindStringIndex("=");

			if (bEqual != InvalidIndex)
			{
				Util::String shaderEntry = sEntry.ExtractToEnd(bEqual+1);
				Util::Array< Util::String > shaderEntries;
				Util::String entryValue;

				SizeT nCount = ShaderUtil::TokenizeWithoutCRLF(shaderEntry, entryValue);

				if (!nCount)
				{
					SYS_EXCEPT(Exceptions::ShaderException, 
						STRING_FORMAT("Shader Entry Name is Empty!\n", ""),
						GET_FUNCTION_NAME()
						);
				}
				else if (nCount > 1)
				{
					SYS_EXCEPT(Exceptions::ShaderException, 
						STRING_FORMAT("%s support only one name!\n", entryName.AsCharPtr()),
						GET_FUNCTION_NAME()
						);
				}

				if (entryName == "VertexShader")
				{
					m_CommonShaderSetting.AddEntry(CommonShaderSetting::Vertex, entryValue);
				}
				else if (entryName == "PixelShader")
				{
					m_CommonShaderSetting.AddEntry(CommonShaderSetting::Pixel, entryValue);
				}
				else if (entryName == "Template")
				{
					m_CommonShaderSetting.AddEntry(CommonShaderSetting::Template, entryValue);
				}
				else
				{
					SYS_EXCEPT(Exceptions::ShaderException, 
						STRING_FORMAT("Invalid Entry, shader only supports VertexShader, PixelShader or Template\n", ""),
						GET_FUNCTION_NAME()
						);


					return false;
				}
			}
			else
			{
				SYS_EXCEPT(Exceptions::ShaderException, 
					STRING_FORMAT(" there must be a '=' after VertexShader, PixelShader or Template! \n", ""),
					GET_FUNCTION_NAME()
					);
			}
			
		}
		
	}

	return true;

}

bool ShaderPass::_ParseParameterStage()
{
	static const Util::String paramKeyWord( "#PARAMETER " );

	IndexT pos = m_sCompiler.FindStringIndex(paramKeyWord);
	
	if (pos != InvalidIndex)
	{
		pos += paramKeyWord.Length();

		IndexT nCR          = m_sCompiler.FindCharIndex('\n', pos);
		Util::String sParam = m_sCompiler.ExtractRange(pos, nCR - pos + 1);

		Util::Array< Util::String > params;
		
		ShaderUtil::TokenizeWithoutCRLF(sParam, params);

		if (params.IsEmpty())
		{
			SYS_EXCEPT(Exceptions::ShaderException, 
				STRING_FORMAT("at least, you must supply lighting model parameter! \n", ""),
				GET_FUNCTION_NAME()
				);
		}

		m_ShadingSetting.SetLightingType(params[0]);

		Util::Dictionary<Util::String, Util::String> paramValuePairs;

		for (IndexT i = 1; i < params.Size(); ++i)
		{
			const Util::String& param = params[i];
			IndexT pos = param.FindCharIndex(':');

			if (pos != InvalidIndex)
			{
				Util::Array<Util::String> pair;
				param.Tokenize(":", pair);

				if (pair.Size() < 2)
				{
					SYS_EXCEPT(Exceptions::ShaderException, 
						STRING_FORMAT("The value of %s is empty! \n", pair[0].AsCharPtr()),
						GET_FUNCTION_NAME()
						);
				}


				paramValuePairs.Add(pair[0], pair[1]);
			}
			else
			{
				paramValuePairs.Add(param, "None");
			}

			
		}

		for (IndexT i = 0; i < paramValuePairs.Size(); ++i)
		{
			const Util::String& key   = paramValuePairs.KeyAtIndex(i);
			const Util::String& value = paramValuePairs.ValueAtIndex(i);
		
			if (key == "disable")
			{
				if (value == "castshadow")
				{
					m_ShadingSetting.SetCastShadow(false);
				}
				else if (value == "genshadow")
				{
					m_ShadingSetting.SetGenShadow(false);
				}
				else if (value == "fog")
				{
					m_ShadingSetting.SetEnableFog(false);
				}
			}
			else if (key == "lightmap")  // lightmap support
			{
				if ( value == "on" )
				{
					m_ShadingSetting.SetEnableLightMap(true);
				}
			}
			else if (key == "lightmapuv")
			{
				if (value == "firstuv")
				{
					m_ShadingSetting.SetLightMapUsetFirstUV(true);
				}
			}
			else if (key == "vertexlight")
			{
				if (value == "on")
				{
					m_ShadingSetting.SetEnableVertexLight(true);
				}
			}
			else if (key == "light")
			{
				if (value == "off")
				{
					m_ShadingSetting.SetEnableLighting(false);
				}
			}
			else if (key == "alphablend")
			{
				m_ShadingSetting.SetAlphaBlend(true);
			}
			else if (key == "alphatest")
			{
				m_ShadingSetting.SetAlphaTest(true);
				m_ShadingSetting.SetAlphaTestValue(value);
			}			
			else
			{
				SYS_EXCEPT(Exceptions::ShaderException, 
					STRING_FORMAT("Invalid #PARAMETER value : %s! \n", key.AsCharPtr()),
					GET_FUNCTION_NAME()
					);
			}
		}
	}
	else
	{
		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Can not find #PARAMETER, maybe there is not a space between #PARAMETER and value \n", ""),
			GET_FUNCTION_NAME()
			);
	}

	return true;
}

void ShaderPass::_AnalyzeShaderType()
{
	bool bRes = true;

	if (!m_CommonShaderSetting.HasEntry())
	{

		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("No VetexShader , PixelShader or Template! \n", ""),
			GET_FUNCTION_NAME()
			);

		bRes = false;
	}

	if (!m_CommonShaderSetting.HasEntry(CommonShaderSetting::Template))
	{
		if (!m_CommonShaderSetting.HasEntry(CommonShaderSetting::Pixel) && !m_CommonShaderSetting.HasEntry(CommonShaderSetting::Vertex))
		{

			SYS_EXCEPT(Exceptions::ShaderException, 
				STRING_FORMAT("if there is no Template, shader must define a VertexShader and a PixelShader!\n", ""),
				GET_FUNCTION_NAME()
				);

			bRes = false;
		}
	}

	if (!m_CommonShaderSetting.HasEntry(CommonShaderSetting::Pixel) && !m_CommonShaderSetting.HasEntry(CommonShaderSetting::Template))
	{

		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Shader must define a PixelShader or Template!\n", ""),
			GET_FUNCTION_NAME()
			);

		bRes = false;
	}

	if (bRes)
	{
		if (m_CommonShaderSetting.HasEntry(CommonShaderSetting::Vertex) && !m_CommonShaderSetting.HasEntry(CommonShaderSetting::Template))
		{
			m_bNeedCompileVertex = true;
		}

		if (m_CommonShaderSetting.HasEntry(CommonShaderSetting::Pixel))
		{
			m_bNeedCompilePixel = true;
		}

		if (m_CommonShaderSetting.HasEntry(CommonShaderSetting::Template))
		{
			m_bNeedCompileCompositive = true;
		}
	}
}

void ShaderPass::Compile(GpuProgramCompiler* pCompiler)
{
	if (m_bNeedCompileVertex)
	{
		m_CommonShaderSetting.SetShaderType(CommonShaderSetting::Vertex);
		pCompiler->Compile(this);

		Util::String result = pCompiler->GetResult();

		m_sResult += "ShaderType \"vs\" {\n" + result + "}\n";
	}

	if (m_bNeedCompilePixel)
	{
		m_CommonShaderSetting.SetShaderType(CommonShaderSetting::Pixel);
		pCompiler->Compile(this);

		Util::String result = pCompiler->GetResult();

		m_sResult += "ShaderType \"ps\" {\n" + result + "}\n";
	}

	if (m_bNeedCompileCompositive)
	{
		ShaderJoint* pJonit = n_new(ShaderJoint);
		pJonit->Generate(&m_CommonShaderSetting, &m_ShadingSetting, m_sRenderState, m_sSourceCode);

		const Util::Dictionary< ShaderJoint::PassType, ShaderJoint::PassInfo >& passInfos = pJonit->GetPassInfo();
		const Util::Dictionary< ShaderJoint::PassType, Util::String>&     passRenderState = pJonit->GetPassRenderState();

		m_sResult += "\t\n";

		SizeT nCount = passInfos.Size();
		for (IndexT i = 0; i < nCount; ++i)
		{
			const ShaderJoint::PassInfo& info     = passInfos.ValueAtIndex(i);
			const ShaderJoint::PassType& passType = passInfos.KeyAtIndex(i);

			SetCode(info.source);
			
			//Set Entry name of Shader
			if (!m_CommonShaderSetting.HasEntry(CommonShaderSetting::Vertex))
			{
				m_CommonShaderSetting.AddEntry(CommonShaderSetting::Vertex, info.vertEntry);
			}

			if (!m_CommonShaderSetting.HasEntry(CommonShaderSetting::Pixel))
			{
				m_CommonShaderSetting.AddEntry(CommonShaderSetting::Pixel, info.pixelEntry);
			} 
			else
			{
				m_CommonShaderSetting.SetEntryName(CommonShaderSetting::Pixel, info.pixelEntry);
			}

			//Compile Vertex Shader
			m_CommonShaderSetting.SetShaderType(CommonShaderSetting::Vertex);
			pCompiler->Compile(this);

			if (passType != ShaderJoint::Forward)
			{
				m_sResult += passRenderState[passType];
			}

			Util::String vsResult = pCompiler->GetResult();
			
			m_sResult += "ShaderType \"vs\" {\n" + vsResult + "}\n";

			//Compile Pixel Shader

			m_CommonShaderSetting.SetShaderType(CommonShaderSetting::Pixel);
			pCompiler->Compile(this);

			Util::String psResult = pCompiler->GetResult();

			m_sResult += "ShaderType \"ps\" {\n" + psResult + "}\n";

			
		}
	}
}

	__ImplementClass(ShaderTechnique,'SHTQ', ShaderBasis);

ShaderTechnique::ShaderTechnique()
{

}

ShaderTechnique::~ShaderTechnique()
{
	m_AllShaderPass.Clear();
}

void ShaderTechnique::Finish()
{
	IndexT res = m_sRawSegment.FindStringIndex("#CODE");

	if (res != InvalidIndex)
	{
		m_sProcessed = m_sRawSegment.InsertRange(res, m_AllShaderPass[0]->GetResult());
		m_sProcessed.SubstituteString("#CODE", "");
	}
}

	__ImplementClass(ShaderElement,'SHET',Core::RefCounted);

ShaderElement::ShaderElement()
{

}

ShaderElement::~ShaderElement()
{
	m_AllTechs.Clear();
}

void ShaderElement::Compile(GpuProgramCompiler* pCompiler)
{
	IndexT nTech = m_AllTechs.Size();

	for (IndexT i = 0; i < nTech; ++i)
	{
		const Util::Array< GPtr<ShaderPass> >& allPass = m_AllTechs[i]->GetAllShaderPass();

		SizeT nPass = allPass.Size();

		for (IndexT j = 0; j < nPass; ++j)
		{
			allPass[j]->Compile(pCompiler);
		}
	}
}

void ShaderElement::Parse()
{
	SizeT nTech = m_AllTechs.Size();

	for (IndexT i = 0; i < nTech; ++i)
	{
		const Util::Array< GPtr<ShaderPass> >& allPass = m_AllTechs[i]->GetAllShaderPass();

		IndexT nPass = allPass.Size();

		for (IndexT j = 0; j < nPass; ++j)
		{
			allPass[j]->Parse();
		}
	}
}

void ShaderElement::Finish()
{
	SizeT nTech = m_AllTechs.Size();

	for (IndexT i = 0; i < nTech; ++i)
	{
		m_AllTechs[i]->Finish();

		m_sOutput += m_AllTechs[i]->GetProcessedTechSegment();
	}
}

Util::String ShaderElement::GetResult() const
{
	return m_sOutput;
}

}