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

#ifndef __GPUProgramGLES_H__
#define __GPUProgramGLES_H__

#include "base/GPUProgram.h"
#include "OpenGLES.h"
#include "util/dictionary.h"

namespace GLES
{
	using namespace RenderBase;

	struct Attribute 
	{
		IndexT       location;
		GLenum       type;
		SizeT        size;
	};

	struct Uniform 
	{
		Util::String name;
		IndexT       location;
		GLenum       type;
		SizeT        size;
	};

	class GPUProgramGLES : public GPUProgram
{
	__DeclareSubClass(GPUProgramGLES, GPUProgram)

public:

	/// constructor
	GPUProgramGLES();
	/// destructor
	virtual ~GPUProgramGLES();
	/// get gles vs buffer
	GLuint GetVertexShaderGLES() const;
	/// get gles ps buffer
	GLuint GetPixelShaderGLES() const;

	void LoadBuffers();

	void BindProgram() const;

	void UnbindProgram() const;

	GLuint GetShaderProgram() const;

	const Util::Dictionary<Util::String, Attribute>& GetActiveAttributes() const;

	const Util::Array<Uniform>& GetActiveUniforms() const;

	const IndexT GetTextureUniformLocation(const IndexT& texUnit) const;

	virtual void OnDeviceLost();

	virtual void OnDeviceReset();

protected:

	void _DeleteShaderObject();

	void _ProcessShader(GLuint& shader, const char** pFile, GLint iShaderType);

	void _InitActiveAttribute();

	void _InitActiveUniform();

private:

	GLuint  m_VertexShaderGLSL;
	GLuint  m_PixelShaderGLSL;
	GLuint  m_ShaderProgram;	

	Util::Dictionary<Util::String, Attribute>  m_ActiveAttributes;
	Util::Array<Uniform>                       m_ActiveUniforms;

	//ÎÆÀíµ¥Ôª, ¼Ä´æÆ÷ºÅ
	Util::Dictionary<IndexT, IndexT>           m_TexUnitsMap;
};

inline GLuint GPUProgramGLES::GetVertexShaderGLES() const
{
	return m_VertexShaderGLSL;
}

inline GLuint GPUProgramGLES::GetPixelShaderGLES() const
{
	return m_PixelShaderGLSL;
}

inline void GPUProgramGLES::BindProgram() const
{
	GLESImpl::Instance()->ActiveShaderProgram(m_ShaderProgram);
}

inline void GPUProgramGLES::UnbindProgram() const
{
	GLESImpl::Instance()->ActiveShaderProgram(0);
}

inline GLuint GPUProgramGLES::GetShaderProgram() const
{
	return m_ShaderProgram;
}

inline const Util::Dictionary<Util::String, Attribute>& GPUProgramGLES::GetActiveAttributes() const
{
	return m_ActiveAttributes;
}

inline const Util::Array<Uniform>& GPUProgramGLES::GetActiveUniforms() const
{
	return m_ActiveUniforms;
}

inline const IndexT GPUProgramGLES::GetTextureUniformLocation(const IndexT& texUnit) const
{
	return m_TexUnitsMap[texUnit];
}

}

#endif