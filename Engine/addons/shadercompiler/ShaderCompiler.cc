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
#include "ShaderCompiler.h"
#include "util/array.h"

#include "ShaderElement.h"

namespace ShaderProgramCompiler
{
	
	__ImplementAbstractClass(GpuProgramCompiler,'GPCP',Core::RefCounted);

GpuProgramCompiler::GpuProgramCompiler()
{

}

GpuProgramCompiler::~GpuProgramCompiler()
{

}

void GpuProgramCompiler::InitCompiler()
{
	
}

void GpuProgramCompiler::_BeforeCompile(const ShaderPass* pPass)
{
	m_sRegisterBinds.Clear();
	m_sCompiledCode.Clear();
	m_Macros.Clear();

	const ShadingTemplateSetting& shadeSetting = pPass->GetShadingSetting();
	const CommonShaderSetting&   cs           = pPass->GetCommonSetting();

	if (shadeSetting.HasShadingOption(ShadingTemplateSetting::LightMap))
	{
		ShaderMarcro macro;
		macro.name = "LIGHTMAP_ON";
		m_Macros.Append(macro);
	}

	if (shadeSetting.HasShadingOption(ShadingTemplateSetting::VertexLight))
	{
		ShaderMarcro macro;
		macro.name = "VERTEXLIGHT_ON";
		m_Macros.Append(macro);
	}

	if (shadeSetting.HasShadingOption(ShadingTemplateSetting::Light))
	{
		ShaderMarcro macro;
		macro.name = "LIGHT_ON";
		m_Macros.Append(macro);
	}

	if (shadeSetting.HasShadingOption(ShadingTemplateSetting::Fog))
	{
		ShaderMarcro macro;
		macro.name = "FOG_ON";
		m_Macros.Append(macro);
	}

	m_sProgramStartString = "RenderAPI \"" + CommonShaderSetting::GpuSdkAsString(cs.GetGpuSDK()) + "\" {\n";


}

void GpuProgramCompiler::_AfterCompile()
{
	m_sResultCode.Clear();

	m_sResultCode += m_sProgramStartString;
	m_sResultCode += m_sRegisterBinds;
	
	SizeT maxLength = 5000;

	if (m_sCompiledCode.Length() > maxLength)
	{
		IndexT departs =m_sCompiledCode.Length()/ maxLength;
		Util::String tmpStr; 
		for (SizeT i = 0; i < departs; ++i)
		{
			if (i != 0)
			{
				tmpStr += "\"\nSetShaderCode \"";
			}
			tmpStr += m_sCompiledCode.ExtractRange(i * maxLength, maxLength);				
		}
		tmpStr += "\"\nSetShaderCode \"" + m_sCompiledCode.ExtractToEnd(departs * maxLength);
		m_sCompiledCode = tmpStr;

	}

	m_sResultCode += "SetShaderCode \"" + m_sCompiledCode + "\"\n}\n\n";
}

}