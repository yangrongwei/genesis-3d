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
#ifndef _MOJOSHADERTOOL_H_
#define _MOJOSHADERTOOL_H_

#include "core/singleton.h"

#include "core/refcounted.h"
#include "core/singleton.h"

struct MOJOSHADER_astData;

namespace ShaderProgramCompiler
{
	class ShaderJoint;

	class MojoShaderTool : public Core::RefCounted
{
	__DeclareClass(MojoShaderTool);
	__DeclareImageSingleton(MojoShaderTool);

public:

	MojoShaderTool();
	
	~MojoShaderTool();

public:

	enum InputModifier
	{
		INPUTMOD_NONE = 0,
		INPUTMOD_IN,
		INPUTMOD_OUT,
		INPUTMOD_INOUT,
		INPUTMOD_UNIFORM
	};

	struct MojoFuncInfo
	{
		Util::String   type;
		Util::String   name;
		Util::String   semantic;
		InputModifier  modifier;
	};


	void    MojoJointParse(ShaderJoint* pJoint, const Util::String& source, const Util::String& customEntry);

	bool    MojoPreprocess(Util::String& source);

protected:

	bool    _MojoParseFunctionParam(const MOJOSHADER_astData* pMojoData, const Util::String& customEntry, Util::Array<MojoFuncInfo>& funcInfos);

	void    _MojoParseParamType(const MOJOSHADER_astData* pMojoData, const Util::String& typeName, Util::Array<MojoFuncInfo>& funcInfos);


};

}



#endif