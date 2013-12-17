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


#ifndef SHADERCOMPILER_H_
#define SHADERCOMPILER_H_

#include "util/array.h"
#include "util/keyvaluepair.h"
#include "util/string.h"
#include "util/dictionary.h"
#include "core/refcounted.h"


namespace ShaderProgramCompiler
{
	class ShaderPass;

	class GpuProgramCompiler : public Core::RefCounted
{
	__DeclareAbstractClass(GpuProgramCompiler);

public:

	GpuProgramCompiler();

	virtual ~GpuProgramCompiler();

public:

	virtual void InitCompiler();

	virtual void Close() = 0;

	virtual void Compile(ShaderPass* pPass) = 0;

public:

	struct ShaderMarcro
	{
		ShaderMarcro ()
		{

		}
		ShaderMarcro (const Util::String& n, const Util::String& v) 
			: name(n), value(v) 
		{

		}

		Util::String name;
		Util::String value;
	};


	const Util::Array< ShaderMarcro >& GetMacros() const;

	Util::String GetResult() const;

protected:

	void _BeforeCompile(const ShaderPass* pPass);

	void _AfterCompile();

protected:

	Util::Array<ShaderMarcro>                    m_Macros;

	Util::String                                 m_sProgramStartString;

	Util::String                                 m_sResultCode;
	Util::String                                 m_sCompiledCode;
	Util::String                                 m_sRegisterBinds;

};

inline const Util::Array< GpuProgramCompiler::ShaderMarcro >& GpuProgramCompiler::GetMacros() const
{
	return m_Macros;
}

inline Util::String GpuProgramCompiler::GetResult() const
{
	return m_sResultCode;
}

};
#endif//SHADERCOMPILER_H_