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

//#ifdef __ANDROID__
#include "stdneb.h"
#include "GPUProgramGLES.h"

namespace GLES
{
	__ImplementClass(GPUProgramGLES,'GPGE',RenderBase::GPUProgram)

GPUProgramGLES::GPUProgramGLES()
: m_VertexShaderGLSL(0),
  m_PixelShaderGLSL(0),
  m_ShaderProgram(0)
{

}

GPUProgramGLES::~GPUProgramGLES()
{
	_DeleteShaderObject();
}

void GPUProgramGLES::_DeleteShaderObject()
{
	UnbindProgram();

	if (m_VertexShaderGLSL)
	{
		glDeleteShader(m_VertexShaderGLSL);
		m_VertexShaderGLSL = 0;
	}

	if (m_PixelShaderGLSL)
	{
		glDeleteShader(m_PixelShaderGLSL);
	}

	if (m_ShaderProgram)
	{
		glDeleteProgram(m_ShaderProgram);
	}
	
	m_ActiveAttributes.Clear();
	m_ActiveUniforms.Clear();
}

void GPUProgramGLES::_ProcessShader(GLuint& shader, const char** pFile, GLint iShaderType)
{
	shader = glCreateShader(iShaderType);

	glShaderSource(shader, 1, pFile, NULL);

	glCompileShader(shader);

	GLint iStatus;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &iStatus);

	if (iStatus != GL_TRUE)
	{
#ifdef __ANDROID__
		LOGI("------------------Shader Compiling Error!------------------");
#endif
		GLint iLen;
		char* pErrorLog = NULL;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &iLen);

		pErrorLog = n_new_array(char, iLen);

		glGetShaderInfoLog(shader, iLen, NULL, pErrorLog);

		n_error(pErrorLog);

		n_delete_array(pErrorLog);
#ifdef __ANDROID__
		if (iShaderType == GL_VERTEX_SHADER)
		{
			LOGI("--------------------VERTEX SHADER ERROR--------------------");
		}
		else
		{
			LOGI("--------------------PIXEL SHADER ERROR--------------------");
		}

		LOGI(pErrorLog);
#endif
	}
}

void GPUProgramGLES::LoadBuffers()
{
	_DeleteShaderObject();

	if ( !m_vertexCode.IsEmpty() )
	{
		const char* pVertexCode = m_vertexCode.AsCharPtr();

		_ProcessShader(m_VertexShaderGLSL, &pVertexCode, GL_VERTEX_SHADER);
	}

	if ( !m_pixelCode.IsEmpty() )
	{
		const char* pFragmentCode = m_pixelCode.AsCharPtr();

		_ProcessShader(m_PixelShaderGLSL, &pFragmentCode, GL_FRAGMENT_SHADER);
	}

	m_ShaderProgram = glCreateProgram();

	glAttachShader(m_ShaderProgram, m_VertexShaderGLSL);
	glAttachShader(m_ShaderProgram, m_PixelShaderGLSL);
	glLinkProgram(m_ShaderProgram);

	GLint linkStatus;

	glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &linkStatus);

	if (linkStatus)
	{
		BindProgram();
	} 
	else
	{
		GLint length;
		char* pLog = NULL;
		glGetProgramiv(m_ShaderProgram, GL_INFO_LOG_LENGTH, &length);

		pLog = n_new_array(char, length);
		glGetProgramInfoLog(m_ShaderProgram, length, &length, pLog);
		n_error(pLog);

		n_delete_array(pLog);
#ifdef __ANDROID__
		LOGI("------------------Shader Linking Error!------------------");
		LOGI(pLog);
#endif

	}

	_InitActiveAttribute();
	_InitActiveUniform();

}

void GPUProgramGLES::_InitActiveAttribute()
{
	GLint maxAttributeLen;
	GLint numAttribute;
	char *pAttributeName = NULL;

	glGetProgramiv(m_ShaderProgram, GL_ACTIVE_ATTRIBUTES, &numAttribute);
	glGetProgramiv(m_ShaderProgram, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &maxAttributeLen);

	pAttributeName = n_new_array(char, maxAttributeLen);
	GLint size;
	GLenum type;
	for (IndexT index = 0; index < numAttribute; ++index)
	{
		glGetActiveAttrib(m_ShaderProgram, index, maxAttributeLen, NULL, &size, &type, pAttributeName);
		IndexT loc = glGetAttribLocation(m_ShaderProgram, pAttributeName);
		Attribute attri;
		attri.type     = type;
		attri.location = loc;
		attri.size     = size;

		m_ActiveAttributes.Add(pAttributeName, attri);
	}
	n_delete_array(pAttributeName);
}

void GPUProgramGLES::_InitActiveUniform()
{
	GLint maxUniformLen;
	GLint numUniforms;
	char *pUniformName;

	glGetProgramiv(m_ShaderProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
	glGetProgramiv(m_ShaderProgram, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLen);

	pUniformName = n_new_array(char, maxUniformLen);
	GLint  size;
	GLenum type;
	IndexT nTexUnit = 0;

	for (IndexT index = 0; index < numUniforms; ++index)
	{
		glGetActiveUniform(m_ShaderProgram, index, maxUniformLen, NULL, &size, &type, pUniformName);
		IndexT loc = glGetUniformLocation(m_ShaderProgram, pUniformName);
		Uniform uni;
		uni.type     = type;
		uni.name     = pUniformName;

		if (type == GL_SAMPLER_2D || type == GL_SAMPLER_CUBE)
		{
			uni.location = nTexUnit;
			m_TexUnitsMap.Add(nTexUnit, loc);
			nTexUnit++;
		} 
		else
		{
			uni.location = loc;
		}
		
		uni.size     = size;

		m_ActiveUniforms.Append(uni);
	}
	n_delete_array(pUniformName);
}

void GPUProgramGLES::OnDeviceLost()
{
	UnbindProgram();

	m_VertexShaderGLSL = 0;
	m_PixelShaderGLSL  = 0;
	m_ShaderProgram    = 0;


}

void GPUProgramGLES::OnDeviceReset()
{
	LoadBuffers();
}

}
//#endif