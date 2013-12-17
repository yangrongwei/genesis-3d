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
#include "ShaderAnalyzer.h"
#include "ShaderElement.h"
#include "shadercompiler/Utility/ShaderCompilerUtil.h"
#include "exception/exceptions.h"

namespace ShaderProgramCompiler
{
ShaderAnalyzer::ShaderAnalyzer()
: m_pShaderElement(NULL)
{

}

ShaderAnalyzer::~ShaderAnalyzer()
{
	if (m_pShaderElement != NULL)
	{
		n_delete(m_pShaderElement);
	}
}

void ShaderAnalyzer::_Prepare(const Util::String& content)
{
	m_OriginalContent = content;

	Util::String sourceCode = content;

	//抽出代码段S
	static Util::String sBegin = "CODEBEGIN";
	static Util::String sEnd   = "CODEEND";

	IndexT begin = sourceCode.FindStringIndex(sBegin, 0);
	IndexT end   = sourceCode.FindStringIndex(sEnd, begin);

	if (begin != InvalidIndex && end != InvalidIndex)
	{
		m_CodeSegment = sourceCode.ExtractRange(begin + sBegin.Length(), end - (begin + sBegin.Length()) );
	} 
	else
	{

		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Can not find CODEBEGIN or CODEEND! \n.", ""),
			GET_FUNCTION_NAME()
			);

	}
	
	sourceCode = sourceCode.EraseRange(begin, (end + sEnd.Length()) - begin);
	
	//抽出Compiler
	Util::String compiler;
	IndexT compilerBegin, compilerEnd;
	compilerBegin = sourceCode.FindStringIndex("Compiler");
	compilerEnd   = sourceCode.FindCharIndex('}', compilerBegin);

	if (compilerBegin == InvalidIndex || compilerEnd == InvalidIndex)
	{
		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Can not find Compiler when parse shader! \n.", ""),
			GET_FUNCTION_NAME()
			);
	
	} 

	compiler      = sourceCode.ExtractRange(compilerBegin, compilerEnd - compilerBegin + 1);

	sourceCode = sourceCode.EraseRange(compilerBegin,  (compilerEnd+1) - compilerBegin );
	Util::String sWithoutCodeAndCompiler = sourceCode;

	//抽出RenderState
	Util::String renderState;
	IndexT renderStateBegin, renderStateEnd;
	renderStateBegin = sourceCode.FindStringIndex("RenderSTATE");
	renderStateEnd   = sourceCode.FindCharIndex('}', renderStateBegin);

	if (renderStateBegin == InvalidIndex || renderStateEnd == InvalidIndex)
	{

		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Can not find RenderState when parse shader! \n.", ""),
			GET_FUNCTION_NAME()
			);

	}

	renderState = sourceCode.ExtractRange(renderStateBegin, renderStateEnd - renderStateBegin + 1);

	sWithoutCodeAndCompiler = sWithoutCodeAndCompiler.InsertRange(renderStateEnd+1, "\n \n \n \n #CODE \n");

	sourceCode = sourceCode.EraseRange(renderStateBegin,  (renderStateEnd+1) - renderStateBegin );

	//抽出Pass
	Util::String sPass;
	IndexT passBegin, passEnd;
	passBegin = sourceCode.FindStringIndex("Pass");
	passEnd   = sourceCode.FindCharIndex('}', passBegin);

	if (passBegin == InvalidIndex || passEnd == InvalidIndex)
	{
		
		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Can not find Pass in shader! \n.", ""),
			GET_FUNCTION_NAME()
			);

	} 

	sPass     = sourceCode.ExtractRange(passBegin, passEnd - passBegin + 1);

	sourceCode = sourceCode.EraseRange(passBegin,  (passEnd+1) - passBegin );

	//抽出Technique
	Util::String sTech;
	IndexT techBegin, techEnd;
	techBegin = sourceCode.FindStringIndex("Technique");
	techEnd   = sourceCode.FindCharIndex('}', techBegin);

	if (techBegin == InvalidIndex || techEnd == InvalidIndex)
	{
		SYS_EXCEPT(Exceptions::ShaderException, 
			STRING_FORMAT("Can not find Pass in shader! \n.", ""),
			GET_FUNCTION_NAME()
			);
	}

	sTech     = sourceCode.ExtractRange(techBegin, techEnd - techBegin + 1);

	m_pShaderElement = ShaderElement::Create();
	GPtr<ShaderTechnique> pTech = ShaderTechnique::Create();
	GPtr<ShaderPass>      pPass = ShaderPass::Create();


	pPass->SetRenderState(renderState);
	pPass->SetCompiler(compiler);
	pPass->SetCode(m_CodeSegment);


	pTech->AddShaderPass(pPass);
	pTech->SetRawTechSegment(sWithoutCodeAndCompiler);

	m_pShaderElement->AddShaderTechnique(pTech);

}

bool ShaderAnalyzer::Parse(const Util::String& content)
{
	_Prepare(content);

	m_pShaderElement->Parse();

	return true;
}

void ShaderAnalyzer::Compile(GpuProgramCompiler* pCompiler)
{
	m_pShaderElement->Compile(pCompiler);
}

void ShaderAnalyzer::Finish()
{
	m_pShaderElement->Finish();
}

Util::String ShaderAnalyzer::GetResult() const
{
	return m_pShaderElement->GetResult();
}

}