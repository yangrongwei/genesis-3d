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
#include "ShaderData.h"
#include "io/uri.h"
#include "Compilers/D3DCompiler.h"
#include "Compilers/GLESCompiler.h"
#include "ShaderAnalyzer.h"
#include "Utility/ShaderCompilerUtil.h"

namespace ShaderProgramCompiler
{
	__ImplementClass(ShaderData,'SHDA',Core::RefCounted);

ShaderData::ShaderData()
: m_pCompiler(NULL),
  m_pAnalyzer(NULL)
{

}

ShaderData::~ShaderData()
{
	if (m_pCompiler != NULL)
	{
		n_delete(m_pCompiler);
	}

	if (m_pAnalyzer != NULL)
	{
		n_delete(m_pAnalyzer);
	}
}

void ShaderData::Init()
{

	if ( !ShaderUtil::ReadText(m_Name, m_OriginalContent) )
	{
		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("ProcessGenesisShader:read input error!File: %s", m_Name.AsCharPtr()),
			GET_FUNCTION_NAME()
			);
	}


#if RENDERDEVICE_D3D9
	m_pCompiler = D3DCompiler::Create();
#elif RENDERDEVICE_OPENGLES
	m_pCompiler = GLESCompiler::Create();
#endif

	m_pCompiler->InitCompiler();

	m_pAnalyzer = n_new(ShaderAnalyzer);

	
}

void ShaderData::Compile()
{
	m_pAnalyzer->Parse(m_OriginalContent);
	m_pAnalyzer->Compile(m_pCompiler);
	m_pAnalyzer->Finish();
}

Util::String ShaderData::Output() const
{
	return m_pAnalyzer->GetResult();
}

}