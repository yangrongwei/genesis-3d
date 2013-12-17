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
#if __WIN32__

#include "CGTool.h"

#include "shadercompiler/ShaderElement.h"
#include "shadercompiler/ShaderCompiler.h"
#include "shadercompiler/Utility/ShaderCompilerUtil.h"

#include "exception/exceptions.h"

namespace ShaderProgramCompiler
{
	__ImplementClass(CGTool,'CGTL',Core::RefCounted);
	__ImplementImageSingleton(CGTool);


static void ErrorHandler(CGcontext context, CGerror error, void *data)
{
	n_warning("Cg Error: %s \n", cgGetErrorString(error));
}


CGTool::CGTool()
{
	__ConstructImageSingleton;
}

CGTool::~CGTool()
{
	__DestructImageSingleton;
}

void CGTool::InitCG()
{
	cgSetErrorHandler( ErrorHandler, NULL );

	m_Context = cgCreateContext();
	m_Error   = CG_NO_ERROR;

	ShaderUtil::ReadText("sys:common.wjh", m_sIncludeContent);

	SizeT nMaxBoneBySubmesh = 60;
	Util::String strArraySize;
	strArraySize.Format(" float4x4 gFinalXForms[%d]; \n",nMaxBoneBySubmesh);	
	m_sIncludeContent += strArraySize;
}

void CGTool::CloseCG()
{
	cgDestroyContext(m_Context);
}

void CGTool::Prepare(const ShaderPass* pPass, const GpuProgramCompiler* pCompiler)
{
	const CommonShaderSetting& cs = pPass->GetCommonSetting();

	const Util::Array<GpuProgramCompiler::ShaderMarcro>& macros = pCompiler->GetMacros();

	for (IndexT i = 0; i < macros.Size(); ++i)
	{
		m_Parameters.Append("-D" + macros[i].name + "=" + macros[i].value);
	}



	const CommonShaderSetting::ShaderType  type  = cs.GetShaderType();
	const CommonShaderSetting::ShaderModel model = cs.GetShaderModel();
	const CommonShaderSetting::GPUSDK      sdk   = cs.GetGpuSDK();

	if (type == CommonShaderSetting::Vertex)
	{
		if (model == CommonShaderSetting::ShaderModel11)
		{
			if (sdk == CommonShaderSetting::GPUSDKD3D9)
			{
				m_Profile = CG_PROFILE_VS_1_1;
			}

		}
		else if (model == CommonShaderSetting::ShaderModel20)
		{
			if (sdk == CommonShaderSetting::GPUSDKD3D9)
			{
				m_Profile = CG_PROFILE_VS_2_0;
			}
		}
		else if (model == CommonShaderSetting::ShaderModel30)
		{
			if (sdk == CommonShaderSetting::GPUSDKD3D9)
			{
				m_Profile = CG_PROFILE_VS_3_0;
			}
		}
	}
	else if (type == CommonShaderSetting::Pixel)
	{
		if (model == CommonShaderSetting::ShaderModel11)
		{
			if (sdk == CommonShaderSetting::GPUSDKD3D9)
			{
				m_Profile = CG_PROFILE_PS_1_1;
			}

		}
		else if (model == CommonShaderSetting::ShaderModel20)
		{
			if (sdk == CommonShaderSetting::GPUSDKD3D9)
			{
				m_Profile = CG_PROFILE_PS_2_0;
			}
		}
		else if (model == CommonShaderSetting::ShaderModel30)
		{
			if (sdk == CommonShaderSetting::GPUSDKD3D9)
			{
				m_Profile = CG_PROFILE_PS_3_0;
			}
		}
	}
}

bool CGTool::Compile(const Util::String& sourceCode, const Util::String& entryName)
{
	SizeT nParams = m_Parameters.Size();

	const char** args = n_new_array(const char*, nParams + 1);

	for ( IndexT i = 0; i < nParams; ++i )
	{
		args[i] = m_Parameters[i].AsCharPtr();
		
	}

	args[nParams] = NULL;

	Util::String shaderStr = m_sIncludeContent + sourceCode;

	m_CGProgram = cgCreateProgram( m_Context, CG_SOURCE, shaderStr.AsCharPtr(), m_Profile, entryName.AsCharPtr(), args );

	n_delete_array(args);

	const char* pLastList = cgGetLastListing(m_Context);

	if (pLastList != NULL)
	{
		n_warning("Compile Shader Warning : %s \n", pLastList);
	}

	m_Error = cgGetError();

	if (m_Error != CG_NO_ERROR)
	{

		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Compile Shader Error : %s \n.", pLastList),
			GET_FUNCTION_NAME()
			);

		return false;
	}

	const char* pResult = cgGetProgramString( m_CGProgram, CG_COMPILED_PROGRAM );

	if (pResult == NULL)
	{
		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Can not Get Compiled Code\n."),
			GET_FUNCTION_NAME()
			);

		return false;
	}

	m_sAssembly = pResult;

	_TrimCode();

	return true;
}

void CGTool::_TrimCode()
{
	IndexT pos = m_sAssembly.FindStringIndex("//");
	IndexT firstSlash = pos;
	IndexT lastSlash = 0;

	while (pos != InvalidIndex)
	{
		lastSlash = pos;
		pos = m_sAssembly.FindStringIndex("//", pos+1);
	}

	IndexT codePos = m_sAssembly.FindCharIndex('\n', lastSlash);
	m_sAssembly = m_sAssembly.EraseRange(firstSlash, codePos - firstSlash);

	
}

void CGTool::GetRegisterIndex()
{

	CGparameter cgParam = NULL;

	bool bProgram = _HasProgramParameter(cgParam);

	if (bProgram)
	{
		while(cgParam != NULL)
		{
			_IterateParamter(cgParam, m_sBindings);
			cgParam = _ResurseParameter(cgParam);
		}
	}

	cgParam = NULL;

	bool bGlobal = _HasGlobalParameter(cgParam);

	if (bGlobal)
	{
		while(cgParam != NULL)
		{
			_IterateParamter(cgParam, m_sBindings);
			cgParam = _ResurseParameter(cgParam);
		}
	}


}

void CGTool::_IterateParamter(const CGparameter cgParam, Util::String& bindings)
{

	CGenum paramDirection = cgGetParameterDirection(cgParam);

	if (paramDirection != CG_IN && paramDirection != CG_INOUT || !cgIsParameterReferenced(cgParam))
	{
		return;
	}


	Util::String paramName = cgGetParameterName(cgParam);

	IndexT leftBracket = paramName.FindCharIndex('[', 0);
	
	if (leftBracket	!= InvalidIndex)
	{
		paramName = paramName.EraseRange(leftBracket, 1);
	}

	IndexT rightBracket = paramName.FindCharIndex(']', 0);
	if (rightBracket != InvalidIndex)
	{
		paramName = paramName.EraseRange(rightBracket, 1);
	}
	
	CGresource cgResource     = cgGetParameterResource(cgParam);
	CGresource cgBaseResource = cgGetParameterBaseResource(cgParam);
	CGparameterclass cgClass  = cgGetParameterClass(cgParam);

	uint nRegister            = cgGetParameterResourceIndex(cgParam);


	if ( cgClass == CG_PARAMETERCLASS_SAMPLER && cgBaseResource == CG_TEXUNIT0 )
	{
		CGtype type = cgGetParameterBaseType( cgParam );
		bindings   += "BindTexture " + Util::String::FromInt(nRegister) + " [" + paramName + "] ";

		if (type == CG_SAMPLER1D)
		{
			bindings += "1D\n";
		}
		else if (type == CG_SAMPLER2D)
		{
			 bindings += "2D\n";
		}
		else if (type == CG_SAMPLER3D)
		{
			bindings += "3D\n";
		}
		else if (type == CG_SAMPLERCUBE)
		{
			bindings += "CUBE\n";
		}

	}

	if (cgResource == CG_C)
	{
		if (cgClass == CG_PARAMETERCLASS_SCALAR)
		{
			bindings += "SetParam " + Util::String::FromInt(nRegister) + " [" + paramName + "]" + " Float\n";
		}
		else if (cgClass == CG_PARAMETERCLASS_VECTOR)
		{
			bindings += "SetParam " + Util::String::FromInt(nRegister) + " [" + paramName + "]" + " Vector\n";
		}
		else if (cgClass == CG_PARAMETERCLASS_MATRIX)
		{
			bindings += "SetParam " + Util::String::FromInt(nRegister) + " [" + paramName + "]" + " Matrix\n";
		}
	}

}

}

#endif