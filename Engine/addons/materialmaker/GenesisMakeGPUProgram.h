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
#pragma once
#ifndef GENESISMAKEGPUPROGRAM_H_
#define GENESISMAKEGPUPROGRAM_H_
#include "util/string.h"
#include "graphicsystem/Material/ShaderParam.h"
namespace GenesisMaterialMaker
{

class GenesisMakeGPUProgram
{
public:
	GenesisMakeGPUProgram();

	virtual ~GenesisMakeGPUProgram();

	void SetShaderCode(const Util::String& codeStr);
	Util::String GetShaderCode() const;
	void SetShaderType(const Util::String& type);
	const Util::String& GetShaderType() const;
	void SetDeviceType(const Util::String& api);
	const Util::String& GetDeviceType() const;
	void AddParam(const Graphic::ShaderParam& param);
	const Graphic::ShaderParamList& GetParamList() const;
	
private:
	Util::String m_codeStr;
	Util::String m_shaderType;
	Util::String m_renderAPI;
	Graphic::ShaderParamList m_paramList; 
};

typedef Util::Array<GenesisMakeGPUProgram> GenesisGPUProgramList;

inline void GenesisMakeGPUProgram::SetShaderCode(const Util::String& codeStr)
{
	m_codeStr += codeStr;
}

inline Util::String GenesisMakeGPUProgram::GetShaderCode() const
{
	return m_codeStr;
}

inline void GenesisMakeGPUProgram::SetShaderType(const Util::String& type)
{
	m_shaderType = type;
}

inline const Util::String& GenesisMakeGPUProgram::GetShaderType() const
{
	return m_shaderType;
}

inline void GenesisMakeGPUProgram::SetDeviceType(const Util::String& api)
{
	m_renderAPI = api;
}

inline const Util::String& GenesisMakeGPUProgram::GetDeviceType() const
{
	return m_renderAPI;
}

inline void GenesisMakeGPUProgram::AddParam(const Graphic::ShaderParam& param)
{
	m_paramList.Append(param);
}

inline const Graphic::ShaderParamList& GenesisMakeGPUProgram::GetParamList() const
{
	return m_paramList;
}

}

#endif//GENESISMAKEGPUPROGRAM_H_