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
#ifndef _GLESCOMPILER_H_
#define _GLESCOMPILER_H_

#include "shadercompiler/ShaderCompiler.h"

struct glslopt_ctx;

namespace ShaderProgramCompiler
{

	class GLESCompiler : public GpuProgramCompiler
{
	__DeclareSubClass(GLESCompiler, GpuProgramCompiler)

public:

	GLESCompiler();

	virtual ~GLESCompiler();

public:

	virtual void InitCompiler();

	virtual void Close();

	virtual void Compile(ShaderPass* pPass);

protected:

	bool _Compile(const ShaderPass* pPass);

	void _HLSL2GLSL(const ShaderPass* pPass, const char* pSource);

	Util::String _SubsitituteGLKeyWords(const Util::String& source) const;

	void _OptimizeGLES(Util::String& vertSource, Util::String& pixelSource);
	
private:

	glslopt_ctx*   m_pOptCtx;

	Util::String   m_sIncludeContent;

	Util::Dictionary<Util::String, Util::String>  m_GLKeyWords2GLESKeyWords;
};


}




#endif