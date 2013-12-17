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
#include "OpenGLES.h"
#include "GLESTypes.h"

#include <sstream>
#include <string>

namespace GLES
{
	__ImplementClass(GLESImpl,'GEIL',Core::RefCounted);
	__ImplementImageSingleton(GLESImpl);

GLESImpl::GLESImpl()
: m_bInit(false)
{
	__ConstructImageSingleton;
}

GLESImpl::~GLESImpl()
{
	__DestructImageSingleton;
}

void GLESImpl::Init()
{
	if (!m_bInit)
	{
		_initExtension();

		_initOpenGLESStateCache();

		m_bInit = true;
	}
}

bool GLESImpl::CheckExtension(const Util::String& ext) const
{
	IndexT found = m_ExtensionList.FindIndex(ext);
	if (found != InvalidIndex)
	{
		return true;
	} 
	else
	{
		return false;
	}
	
}

void GLESImpl::_initExtension()
{

	// Set version string
	const GLubyte* pcVer = glGetString(GL_VERSION);
	n_printf("Version:  %s\n", pcVer);

	// Get vendor
	const GLubyte* pcVendor = glGetString(GL_VENDOR);
	n_printf("Vendor:  %s\n", pcVendor);

	GLubyte* pVendor = const_cast<GLubyte*>(pcVendor);

	m_VendorName.SetCharPtr((char*)pVendor);
	

	// Set extension list
	std::stringstream ext;
	std::string       str;

	const GLubyte* pcExt = glGetString(GL_EXTENSIONS);

	ext << pcExt;

	 while (ext >> str)
	 {
		 m_ExtensionList.Append( str.c_str() );
	 }
}

void GLESImpl::_initOpenGLESStateCache()
{
	m_curIndexBufferObject  = 0;
	m_curVertexBufferObject = 0;

	m_ShaderProgram         = 0;

	// texture
	m_curTexUnit = 0;
	for (int i =0; i < MaxTextureUnits;++i)
	{
		m_curTextureObjects[i] = 0;
	}

	// blend
	m_alphablend = false;
	m_srcBlend = GL_ONE;
	m_destBlend = GL_ZERO;
	m_srcAlphaBlend = GL_ONE;
	m_destAlphaBlend = GL_ZERO;
	m_blendEquation = GL_FUNC_ADD;
	m_blendAlphaEquation = GL_FUNC_ADD;

	// cull mode
	m_cullMode = RenderBase::eCMNONE;
	m_cullEnable = false;
	m_cullFaceMode = GL_BACK;

	// Polygon mode  
	m_PolyOffFactor = 0.0f;
	m_PolyOffUnits = 0.0f;

	// stencil test
	m_stencilTest = false;
	m_stencilBackWriteMask = 0xFFFFFFFF; 
	m_stencilFrontWriteMask = 0xFFFFFFFF;
	m_stencilBackFunc = GL_ALWAYS;
	m_stencilFrontFunc = GL_ALWAYS;
	m_stencilBackRef  = 0;
	m_stencilFrontRef = 0;
	m_stencilBackMask = 0xFFFFFFFF; 
	m_stencilFrontMask = 0xFFFFFFFF; 
	m_stencilBackFail = GL_KEEP; 
	m_stencilFrontFail = GL_KEEP;
	m_stencilBackZfail = GL_KEEP;
	m_stencilFrontZfail = GL_KEEP;
	m_stencilBackZpass = GL_KEEP;
	m_stencilFrontZpass = GL_KEEP;

	//scissor test
	m_scissorTest = false;

	//depth test
	m_depthTest = false;
	m_depthWrite = true;
	m_depthFunc = GL_LESS;

	//frame buffer
	m_curFrameBuffer = 0;
}

void GLESImpl::SetTextureFilter(GLenum target, RenderBase::TextureFilter filter, bool hasMipMap)
{
	using namespace RenderBase;

	if (hasMipMap)
	{
		switch (filter)
		{
			case eTFPOINT:
				glTexParameteri(target,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(target,GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				return;

			case eTFLINEAR:
				glTexParameteri(target,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(target,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				return;

			case eTFANISOTROPIC:
				glTexParameteri(target,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(target,GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				return;

			default:
				n_error("GLESImpl::etTextureFilter Error : must have a valid filter!");
				glTexParameteri(target,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(target,GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
				return;
		}	
	} 
	else
	{
		switch (filter)
		{
		case eTFPOINT:
			glTexParameteri(target,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			return;
		case eTFLINEAR:
		case eTFANISOTROPIC:
			glTexParameteri(target,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			return;
		
		default:
			n_error("GLESImpl::TextureFilter Error : must have a valid filter!");
			glTexParameteri(target,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(target,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			return;

		}
	}
}

void GLESImpl::SetTextureWrapMode(GLenum target, GLenum address, RenderBase::TextureAddressMode addressMode)
{
	GLint wrapMode = GLESTypes::AsGLESSTextureAddress(addressMode);

	glTexParameteri(target, address, wrapMode);
	
	CheckError();
}

void GLESImpl::CheckFrameBuffer(GLuint frameBuf)
{
	ActiveFrameBuffer(frameBuf);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status !=GL_FRAMEBUFFER_COMPLETE)
	{
		if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)
		{
			n_error("Frame Buffer error!");
		}

		else if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)
		{
			n_error("Frame Buffer error!");
		}

		else if (status == GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS)
		{
			n_error("Frame Buffer error!");
		}

		else if (status == GL_FRAMEBUFFER_UNSUPPORTED)
		{
			n_error("Frame Buffer error!");
		}

		n_error("Frame Buffer error!");
	}
}

void GLESImpl::CheckError()
{
#if _DEBUG || DEBUG
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		n_printf("GL ERROR ID: %d", error);
		//n_error("GL error!");
	}
#else	
	return;
#endif //_DEBUG
}

}