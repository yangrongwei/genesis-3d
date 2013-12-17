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
#include "ShaderFactory.h"
#include "ShaderCompiler.h"



#include "ShaderData.h"
#include "Compilers/MojoShaderTool.h"
#include "Compilers/CGTool.h"


namespace ShaderProgramCompiler
{
	__ImplementClass(ShaderFactory,'SHFA',Core::RefCounted);
	__ImplementImageSingleton(ShaderFactory);

ShaderFactory::ShaderFactory()
	: m_pCGTool(NULL),
	  m_pMojoTool(NULL)
{
	__ConstructImageSingleton;

	m_pMojoTool = MojoShaderTool::Create();

#if __WIN32__
	m_pCGTool = CGTool::Create();
#endif
	
}

ShaderFactory::~ShaderFactory()
{
	__DestructImageSingleton;

#if __WIN32__
	if (m_pCGTool !=NULL)
	{
		n_delete(m_pCGTool);
	}
#endif

	if (m_pMojoTool != NULL)
	{
		n_delete(m_pMojoTool);
	}
}

void ShaderFactory::Add(const Util::String& name)
{
	m_ShaderData = ShaderData::Create();
	m_ShaderData->SetName(name);
}

void ShaderFactory::Process()
{
	m_ShaderData->Init();
	m_ShaderData->Compile();

	m_Output = m_ShaderData->Output();
}

void ShaderFactory::Finish()
{
	m_ShaderData = NULL;
}

}

