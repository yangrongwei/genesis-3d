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
#ifndef _CGTOOL_H_
#define _CGTOOL_H_

#include "Cg/cg.h"
#include "util/string.h"
#include "util/array.h"
#include "core/refcounted.h"
#include "core/singleton.h"

namespace ShaderProgramCompiler
{
	class ShaderPass;
	class GpuProgramCompiler;

	class CGTool : public Core::RefCounted
{
	__DeclareClass(CGTool);
	__DeclareImageSingleton(CGTool);

public:

	CGTool();

	~CGTool();

public:

	void InitCG();

	void CloseCG();

	void Prepare(const ShaderPass* pPass, const GpuProgramCompiler* pCompiler);

	bool Compile(const Util::String& sourceCode, const Util::String& entryName);

	void GetRegisterIndex();

	void SetProfile(const CGprofile& profile);

	void Clean();

	const Util::String& GetCompiled() const;

	const Util::String& GetBindings() const;

protected:

	void _TrimCode();

	void _IterateParamter(const CGparameter cgParam, Util::String& bindings);

	bool _HasProgramParameter(CGparameter& cgParam);

	bool _HasGlobalParameter(CGparameter& cgParam);

	CGparameter _ResurseParameter(const CGparameter cgParam);

private:

	CGcontext	   m_Context;
	CGerror		   m_Error;
	CGprofile      m_Profile;
	CGprogram      m_CGProgram;

	Util::Array< Util::String > m_Parameters;

	Util::String   m_sIncludeContent;

	Util::String   m_sAssembly;

	Util::String   m_sBindings;

};

inline void CGTool::SetProfile(const CGprofile& profile)
{
	m_Profile = profile; 
}

inline bool CGTool::_HasProgramParameter(CGparameter& cgParam)
{
	cgParam = cgGetFirstLeafParameter(m_CGProgram, CG_PROGRAM);
	
	return cgParam != NULL;
}

inline bool CGTool::_HasGlobalParameter(CGparameter& cgParam)
{
	cgParam = cgGetFirstLeafParameter(m_CGProgram, CG_GLOBAL);

	return cgParam != NULL;
}

inline CGparameter CGTool::_ResurseParameter(const CGparameter cgParam)
{
	return cgGetNextLeafParameter(cgParam);
}

inline void CGTool::Clean()
{
	cgDestroyProgram(m_CGProgram);
	m_CGProgram = NULL;
	
	m_sAssembly.Clear();
	m_sBindings.Clear();
}

inline const Util::String& CGTool::GetCompiled() const
{
	return m_sAssembly;
}

inline const Util::String& CGTool::GetBindings() const
{
	return m_sBindings;
}

}






#endif