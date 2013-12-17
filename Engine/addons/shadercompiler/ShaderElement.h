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
#ifndef _SHADERELEMENT_H_
#define _SHADERELEMENT_H_

#include "core/refcounted.h"
#include "core/ptr.h"

#include "ShaderCompilerSetting.h"

namespace ShaderProgramCompiler
{

	class GpuProgramCompiler;

class ShaderBasis : public Core::RefCounted
{
	__DeclareClass(ShaderBasis);


public:

	ShaderBasis();

	~ShaderBasis();

public:

	void SetName(const Util::String& name);

	const Util::String& GetName() const;

private:

	Util::String      m_Name;
};

inline void ShaderBasis::SetName(const Util::String& name)
{
	m_Name = name;
}

inline const Util::String& ShaderBasis::GetName() const
{
	return m_Name;
}

class ShaderPass : public ShaderBasis
{
	__DeclareSubClass(ShaderPass, ShaderBasis);

public:

	ShaderPass();

	virtual ~ShaderPass();

public:

	void SetRenderState(const Util::String& state);

	const Util::String& GetRenderState() const;

	void SetCompiler(const Util::String& compiler);

	bool Parse();

	void Compile(GpuProgramCompiler* pCompiler);

	const CommonShaderSetting& GetCommonSetting() const;

	const ShadingTemplateSetting& GetShadingSetting() const ;

	void SetCode(const Util::String& code);

	const Util::String& GetCode() const;

	void SetCompiledCode(const Util::String& code);

	Util::String GetCompiledCode() const;

	void SetBingdings(const Util::String& bindings);

	Util::String GetBingdings() const;

	Util::String GetResult() const;

protected:

	bool _ParseCompilerStage();

	bool _ParseParameterStage();
	
	void _AnalyzeShaderType();

private:

	CommonShaderSetting   m_CommonShaderSetting;
	ShadingTemplateSetting m_ShadingSetting;

	Util::String         m_sRenderState;
	Util::String         m_sCompiler;
	
	Util::String         m_sSourceCode;
	Util::String         m_sCompiledCode;
	Util::String         m_sRegisterBingdings;
	Util::String         m_sResult;

	Util::Array<Util::String>  m_CompilerKeyWords;

	bool                 m_bNeedCompileVertex;
	bool                 m_bNeedCompilePixel;
	bool                 m_bNeedCompileCompositive;
};

inline Util::String ShaderPass::GetResult() const
{
	return m_sResult;
}

inline void ShaderPass::SetCode(const Util::String& code)
{
	m_sSourceCode = code;
}

inline const Util::String& ShaderPass::GetCode() const
{
	return m_sSourceCode;
}

inline void ShaderPass::SetCompiledCode(const Util::String& code)
{
	m_sCompiledCode = code;
}

inline Util::String ShaderPass::GetCompiledCode() const
{
	return m_sCompiledCode;
}

inline void ShaderPass::SetBingdings(const Util::String& bindings)
{
	m_sRegisterBingdings = bindings;
}

inline Util::String ShaderPass::GetBingdings() const
{
	return m_sRegisterBingdings;
}

inline void ShaderPass::SetRenderState(const Util::String& state)
{
	m_sRenderState = state;
}

inline const Util::String& ShaderPass::GetRenderState() const
{
	return m_sRenderState;
}

inline void ShaderPass::SetCompiler(const Util::String& compiler)
{
	m_sCompiler = compiler;
}

inline const CommonShaderSetting& ShaderPass::GetCommonSetting() const 
{
	return m_CommonShaderSetting;
}

inline const ShadingTemplateSetting& ShaderPass::GetShadingSetting() const
{
	return m_ShadingSetting;
}

class ShaderTechnique : public ShaderBasis
{
	__DeclareSubClass(ShaderTechnique, ShaderBasis);

public:

	ShaderTechnique();

	virtual ~ShaderTechnique();

public:

	void AddShaderPass(const GPtr<ShaderPass>& pPass );

	const Util::Array< GPtr<ShaderPass> >& GetAllShaderPass() const;

	void SetRawTechSegment(const Util::String& code);

	Util::String GetProcessedTechSegment() const;

	void Finish();

private:

	Util::Array< GPtr<ShaderPass> >  m_AllShaderPass;

	Util::String                     m_sRawSegment;
	Util::String                     m_sProcessed;
};

inline void ShaderTechnique::AddShaderPass(const GPtr<ShaderPass>& pPass)
{
	IndexT res = m_AllShaderPass.FindIndex(pPass);

	if (res == InvalidIndex)
	{
		m_AllShaderPass.Append(pPass);
	}
}

inline const Util::Array< GPtr<ShaderPass> >& ShaderTechnique::GetAllShaderPass() const
{
	return m_AllShaderPass;
}

inline void ShaderTechnique::SetRawTechSegment(const Util::String& code)
{
	m_sRawSegment = code;
}

inline Util::String ShaderTechnique::GetProcessedTechSegment() const
{
	return m_sProcessed;
}

class ShaderElement : Core::RefCounted
{
	__DeclareClass(ShaderElement)

public:

	ShaderElement();

	~ShaderElement();

public:

	void AddShaderTechnique(const GPtr<ShaderTechnique>& pTech);

	void Parse();

	void Compile(GpuProgramCompiler* pCompiler);

	void Finish();

	Util::String GetResult() const;

private:

	Util::Array< GPtr<ShaderTechnique> > m_AllTechs;

	Util::String                         m_sOutput;
};

inline void ShaderElement::AddShaderTechnique(const GPtr<ShaderTechnique>& pTech)
{
	IndexT res = m_AllTechs.FindIndex(pTech);

	if (res == InvalidIndex)
	{
		m_AllTechs.Append(pTech);
	}
}

}

#endif