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

#ifndef __opengles_H__
#define __opengles_H__

#include "stdneb.h"
#include "core/refcounted.h"
#include "core/singleton.h"

#include "util/array.h"
#include "util/string.h"

#ifdef __OSX__
#include "ES2/gl.h"
#include "ES2/glext.h"

#include "base/RenderDeviceTypes.h"
#else
#include "GLES2/gl2.h"
#include "GLES2/gl2ext.h"
#include "EGL/egl.h"

#include "base/RenderDeviceTypes.h"
#endif


#ifdef __OSX__

#else

#endif//__OSX__

namespace GLES
{
	const int MaxTextureUnits = 8;	//	最大的纹理单元数量

	class GLESImpl : public Core::RefCounted
{
	__DeclareClass(GLESImpl);
	__DeclareImageSingleton(GLESImpl);

public:

	GLESImpl();

	virtual ~GLESImpl();

	/**
	* vertex && index buffer object                                                                    
	*/
	void ActiveIndexBufferObject(GLuint id);
	void ActiveVertexBufferObject(GLuint id);

	/**
	* shader program                                                                    
	*/
	void ActiveShaderProgram(GLuint id);

	/**
	* texture                                                                    
	*/
	void ActiveTextureUnit(GLenum texUnit);
	void ActiveTextureObject(GLenum target, GLuint id);
	void SetTextureFilter(GLenum target, RenderBase::TextureFilter filter, bool hasMipMap);
	void SetTextureWrapMode(GLenum target, GLenum address, RenderBase::TextureAddressMode addressMode);

	/**
	*  alpha blend                                                                    
	*/
	void ActiveAlphaBlend(bool bEnable);
	void SetBlendFunc( GLenum srcBlend, GLenum destBlend);
	void SetBlendFuncSeparate(GLenum srcBlend, GLenum destBlend, GLenum srcAlpha, GLenum destAlpha);
	void SetBlendEquation(GLenum e);
	void SetBlendEquationSeparate(GLenum eRGB, GLenum eAlpha);

	/**
	* cull mode                                                                    
	*/
	void SetCullMode(RenderBase::CullMode mode);

	/**
	* stencil test
	*/
	void ActiveStencilTest(bool bEnable);
	void SetStencilMask(GLuint mask);
	void SetStencilMaskSeparate(GLuint bFrontmask, GLuint bBackmask);
	void SetStencilFunc(GLenum func, GLint refV, GLuint mask);
	void SetStencilFuncSeparate(GLenum frontfunc, GLint frontrefV, GLuint frontmask,
		GLenum backfunc, GLint backrefV, GLuint backmask);
	void SetStencilOp(GLenum fail, GLenum zfail, GLenum zpass);
	void SetStencilOpSeparate(GLenum frontfail, GLenum frontzfail, GLenum frontzpass,
		GLenum backfail, GLenum backzfail, GLenum backzpass);

	/**
	* depth test                                                                    
	*/
	void ActiveDepthTest(bool bEnable);
	void SetDepthWrite(bool bEnable);
	void SetDepthFunc(GLenum func);

	/**
	* color mask                                                                    
	*/
	void SetColorMask(unsigned short int mask);

	/**
	* scissor test
	*/
	void ActiveScissorTest(bool bEnable);

	/**
	* Polygon mode                                                                    
	*/
	void SetPolyOffset(GLfloat factor, GLfloat units);

	/**
	* fbo                                                                   
	*/
	void ActiveFrameBuffer(GLuint frameBuf);
	void CheckFrameBuffer(GLuint frameBuf);


	void Init();

	bool CheckExtension(const Util::String& ext) const;

	void CheckError();

	void ResetGLState();

	const Util::String& GetVendor() const;

protected:

	void _initOpenGLESStateCache();

	void _initExtension();

protected:

	bool     m_bInit;

	/// vertex and index buffer
	GLuint m_curIndexBufferObject;
	GLuint m_curVertexBufferObject;

	//shader program
	GLuint m_ShaderProgram;
	
	/// texture
	GLenum m_curTexUnit;
	GLuint m_curTextureObjects[MaxTextureUnits];

	//alpha blend
	bool m_alphablend;
	GLenum m_srcBlend, m_destBlend, m_srcAlphaBlend, m_destAlphaBlend;
	GLenum m_blendEquation, m_blendAlphaEquation;

	// cull mode
	RenderBase::CullMode m_cullMode;
	bool m_cullEnable;
	GLenum m_cullFaceMode;

	// stencil test
	bool m_stencilTest;
	GLuint m_stencilBackWriteMask, m_stencilFrontWriteMask;
	GLenum m_stencilBackFunc, m_stencilFrontFunc;
	GLint m_stencilBackRef, m_stencilFrontRef;
	GLuint m_stencilBackMask, m_stencilFrontMask;
	GLenum m_stencilBackFail, m_stencilFrontFail;
	GLenum m_stencilBackZfail,  m_stencilFrontZfail;
	GLenum m_stencilBackZpass, m_stencilFrontZpass;

	//depth test
	bool m_depthTest;
	bool m_depthWrite;
	GLenum m_depthFunc;

	//scissor test
	bool m_scissorTest;


	// Polygon mode
	GLfloat m_PolyOffFactor;
	GLfloat m_PolyOffUnits;

	// color mask
	unsigned short int m_colorMask;

	//fbo
	GLuint              m_curFrameBuffer;

	Util::Array<Util::String> m_ExtensionList;

	Util::String        m_VendorName;
};

inline void GLESImpl::ActiveVertexBufferObject(GLuint id)
{
	if (m_curVertexBufferObject != id)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
		m_curVertexBufferObject = id;

		CheckError();
	}
}

inline void GLESImpl::ActiveIndexBufferObject(GLuint id)
{
	if ( m_curIndexBufferObject != id)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		m_curIndexBufferObject = id;

		CheckError();
	}
}

inline void GLESImpl::ActiveShaderProgram(GLuint id)
{
	if ( m_ShaderProgram != id )
	{
		glUseProgram(id);
		m_ShaderProgram = id;

		GLESImpl::Instance()->CheckError();
	}
}

inline void GLESImpl::ActiveTextureObject(GLenum target, GLuint id)
{
	if ( m_curTextureObjects[m_curTexUnit] != id )
	{
		glBindTexture(target, id);
		m_curTextureObjects[m_curTexUnit] = id;

		CheckError();
	}
	
}

inline void GLESImpl::ActiveTextureUnit(GLenum texUnit)
{
	if (m_curTexUnit != texUnit)
	{
		n_assert( texUnit >= 0 && texUnit < MaxTextureUnits);
		glActiveTexture(GL_TEXTURE0 + texUnit);
		m_curTexUnit = texUnit;

		CheckError();
	}
	
}

inline void GLESImpl::ActiveAlphaBlend(bool bEnable)
{
	if ( m_alphablend != bEnable )
	{
		if ( bEnable )
		{
			glEnable(GL_BLEND);
		}
		else
		{
			glDisable(GL_BLEND);
		}
		m_alphablend = bEnable;

		CheckError();
	}

	
}

inline void GLESImpl::SetBlendFunc(GLenum srcBlend, GLenum destBlend)
{
	if ( m_srcBlend != srcBlend || m_destBlend != destBlend)
	{
		glBlendFunc(srcBlend,destBlend);
		m_srcBlend = srcBlend;
		m_destBlend = destBlend;

		CheckError();
	}

}

inline void GLESImpl::SetBlendFuncSeparate(GLenum srcBlend, GLenum destBlend, GLenum srcAlpha, GLenum destAlpha)
{
	if ( m_srcBlend != srcBlend || m_destBlend != destBlend 
		|| m_srcAlphaBlend != srcAlpha || m_destAlphaBlend != destAlpha)
	{
		glBlendFuncSeparate(srcBlend, destBlend, srcAlpha, destAlpha);
		m_srcBlend = srcBlend;
		m_destBlend = destBlend;
		m_srcAlphaBlend = srcAlpha;
		m_destAlphaBlend = destAlpha;

		CheckError();
	}

}

inline void GLESImpl::SetBlendEquation(GLenum e)
{
	if ( m_blendEquation != e )
	{
		glBlendEquation(e);
		m_blendEquation = e;

		CheckError();
	}

}

inline void GLESImpl::SetBlendEquationSeparate(GLenum eRGB, GLenum eAlpha)
{
	if ( m_blendEquation != eRGB || m_blendAlphaEquation != eAlpha )
	{
		glBlendEquationSeparate(eRGB,eAlpha);
		m_blendEquation = eRGB;
		m_blendAlphaEquation = eAlpha;

		CheckError();
	}

}

inline void GLESImpl::SetCullMode(RenderBase::CullMode mode)
{
	if ( m_cullMode != mode )
	{
		if ( mode == RenderBase::eCMNONE )
		{
			if ( m_cullEnable )
			{
				glDisable(GL_CULL_FACE);
				m_cullEnable = false;
			}
		}
		else
		{
			if ( !m_cullEnable )
			{
				glEnable(GL_CULL_FACE);
				m_cullEnable = true;
			}

			if ( mode == RenderBase::eCMFRONT )
			{
				if ( m_cullFaceMode != GL_FRONT )
				{
					glCullFace(GL_FRONT);
					m_cullFaceMode = GL_FRONT;
				}
			}
			else // mode ==  RenderBase::CM_Back
			{
				if ( m_cullFaceMode != GL_BACK )
				{
					glCullFace(GL_BACK);
					m_cullFaceMode = GL_BACK;
				}
			}
		}

		m_cullMode = mode;

		CheckError();
	}

}

inline void GLESImpl::ActiveDepthTest(bool bEnable)
{
	if ( m_depthTest != bEnable )
	{
		if ( bEnable )
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
		m_depthTest = bEnable;

		CheckError();
	}
}

inline void GLESImpl::SetDepthWrite(bool bEnable)
{
	if ( m_depthWrite != bEnable )
	{
		glDepthMask(bEnable?GL_TRUE:GL_FALSE);
		m_depthWrite = bEnable;

		CheckError();
	}
}

inline void GLESImpl::SetDepthFunc(GLenum func)
{	
	if ( m_depthFunc != func )
	{
		glDepthFunc(func);
		m_depthFunc = func;

		CheckError();
	}
}

inline void GLESImpl::ActiveStencilTest(bool bEnable)
{
	if ( m_stencilTest != bEnable )
	{
		if ( bEnable )
		{
			glEnable(GL_STENCIL_TEST);
		}
		else
		{	
			glDisable(GL_STENCIL_TEST);
		}
		m_stencilTest = bEnable;

		CheckError();
	}
	
}

inline void GLESImpl::SetStencilMask(GLuint mask)
{
	if ( m_stencilFrontWriteMask != mask )
	{
		glStencilMask(mask);
		m_stencilFrontWriteMask = mask;

		CheckError();
	}
}

inline void GLESImpl::SetStencilMaskSeparate(GLuint bFrontmask, GLuint bBackmask)
{
	if ( m_stencilFrontWriteMask != bFrontmask )
	{
		glStencilMaskSeparate(GL_FRONT,bFrontmask);
		m_stencilFrontWriteMask = bFrontmask;

		CheckError();
	}

	if ( m_stencilBackWriteMask != bBackmask )
	{
		glStencilMaskSeparate(GL_BACK,bBackmask);
		m_stencilBackWriteMask = bBackmask;

		CheckError();
	}
	
}

inline void GLESImpl::SetStencilFunc(GLenum func, GLint refV, GLuint mask)
{
	if ( m_stencilFrontFunc != func || m_stencilFrontRef != refV || m_stencilFrontMask != mask )
	{
		glStencilFunc(func,refV,mask);
		m_stencilFrontFunc = func;
		m_stencilFrontRef = refV;
		m_stencilFrontMask = mask;

		CheckError();
	}
}

inline void GLESImpl::SetStencilFuncSeparate(GLenum frontfunc, GLint frontrefV, GLuint frontmask, GLenum backfunc, GLint backrefV, GLuint backmask)
{
	if ( m_stencilFrontFunc != frontfunc || m_stencilFrontRef != frontrefV || m_stencilFrontMask != frontmask )
	{
		glStencilFuncSeparate(GL_FRONT,frontfunc,frontrefV,frontmask);
		m_stencilFrontFunc = frontfunc;
		m_stencilFrontRef = frontrefV;
		m_stencilFrontMask = frontmask;

		CheckError();
	}

	if ( m_stencilBackFunc != backfunc || m_stencilBackRef != backrefV || m_stencilBackMask != backmask )
	{
		glStencilFuncSeparate(GL_BACK,backfunc,backrefV,backmask);
		m_stencilBackFunc = backfunc;
		m_stencilBackRef = backrefV;
		m_stencilBackMask = backmask;

		CheckError();
	}

}

inline void GLESImpl::SetStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
	if ( m_stencilFrontFail != fail || m_stencilFrontZfail != zfail || m_stencilFrontZpass != zpass )
	{
		glStencilOp(fail,zfail,zpass);
		m_stencilFrontFail = fail;
		m_stencilFrontZfail = zfail;
		m_stencilFrontZpass = zpass;

		CheckError();
	}
}

inline void GLESImpl::SetStencilOpSeparate(GLenum frontfail, GLenum frontzfail, GLenum frontzpass, GLenum backfail, GLenum backzfail, GLenum backzpass)
{
	if ( m_stencilFrontFail != frontfail || m_stencilFrontZfail != frontzfail || m_stencilFrontZpass != frontzpass )
	{
		glStencilOpSeparate(GL_FRONT,frontfail,frontzfail,frontzpass);
		m_stencilFrontFail = frontfail;
		m_stencilFrontZfail = frontzfail;
		m_stencilFrontZpass = frontzpass;

		CheckError();
	}

	if ( m_stencilBackFail != backfail || m_stencilBackZfail != backzfail || m_stencilBackZpass != backzpass )
	{
		glStencilOpSeparate(GL_BACK,backfail,backzfail,backzpass);
		m_stencilBackFail = backfail;
		m_stencilBackZfail = backzfail;
		m_stencilBackZpass = backzpass;

		CheckError();
	}

}

inline void GLESImpl::ActiveFrameBuffer(GLuint frameBuf)
{
	if (m_curFrameBuffer != frameBuf)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, frameBuf);
		m_curFrameBuffer = frameBuf;

		CheckError();
	}
	
}

inline void GLESImpl::SetColorMask(unsigned short int mask)
{
	if ( m_colorMask != mask )
	{
		GLboolean rMask = (mask & RenderBase::eCOLORMASKRED)   ? GL_TRUE : GL_FALSE; 
		GLboolean gMask = (mask & RenderBase::eCOLORMASKGREEN) ? GL_TRUE : GL_FALSE; 
		GLboolean bMask = (mask & RenderBase::eCOLORMASKBLUE)  ? GL_TRUE : GL_FALSE; 
		GLboolean aMask = (mask & RenderBase::eCOLORMASKALPHA) ? GL_TRUE : GL_FALSE; 
		glColorMask(rMask,gMask,bMask,aMask);
		m_colorMask = mask;

		CheckError();
	}
}

inline void GLESImpl::SetPolyOffset(GLfloat factor, GLfloat units)
{
	if ( m_PolyOffFactor != factor || m_PolyOffUnits != units )
	{
		glPolygonOffset(factor,units);
		m_PolyOffFactor = factor;
		m_PolyOffUnits = units;

		CheckError();
	}

}

inline void GLESImpl::ActiveScissorTest(bool bEnable)
{
	if ( m_scissorTest != bEnable )
	{
		if ( bEnable )
		{
			glEnable(GL_SCISSOR_TEST);
		}
		else
		{
			glDisable(GL_SCISSOR_TEST);
		}
		m_scissorTest = bEnable;

		CheckError();
	}
	
}

inline void GLESImpl::ResetGLState()
{
	_initOpenGLESStateCache();
}

inline const Util::String& GLESImpl::GetVendor() const
{
	return m_VendorName;
}

}


#endif
