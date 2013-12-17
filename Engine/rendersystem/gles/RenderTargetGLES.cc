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
#ifdef __OSX__
#include "../../profilesystem/ProfileSystem.h"
#else
#include "profilesystem/ProfileSystem.h"
#endif
#include "RenderTargetGLES.h"
#include "OpenGLES.h"
#include "GLESTypes.h"
#include "base/RenderDisplay.h"
#include "RenderSystem.h"

namespace GLES
{
	__ImplementClass(RenderTargetGLES, 'GERT', RenderBase::RenderTarget);

RenderTargetGLES::RenderTargetGLES()
{

}

RenderTargetGLES::~RenderTargetGLES()
{
	if ( !this->isDefaultRenderTarget )
	{
		Discard();
	}
	
}

void RenderTargetGLES::LoadBuffers(SizeT _width, SizeT _height)
{	
	memorySize = 0;
	if (this->isDefaultRenderTarget)
	{
		this->SetWidth(_width);
		this->SetHeight(_height);
		this->SetAntiAliasQuality(AntiAliasQuality::None);
		this->SetColorBufferFormat(PixelFormat::X8R8G8B8);
	}

	if (!this->isDefaultRenderTarget && GetScreenSizeRatio() > 0.f)
	{
		this->SetWidth(int(_width * GetScreenSizeRatio()));
		this->SetHeight(int(_height * GetScreenSizeRatio()));
	}

	if ( this->isDefaultRenderTarget )
	{
		return;
	}

	const RenderBase::GraphicCardCapability& caps = RenderBase::RenderSystem::Instance()->GetGraphicCardCapability();

	glGenFramebuffers(1, &m_GLESRenderTarget.FrameBuf);

	GLESImpl::Instance()->CheckError();

	GLESImpl::Instance()->ActiveFrameBuffer(m_GLESRenderTarget.FrameBuf);

	SizeT renderTexWidth  = width;
	SizeT renderTexHeight = height;
	if (renderTexWidth > caps.mMaxTextureWidth)
	{
		renderTexWidth = width;
	}

	if (renderTexHeight > caps.mMaxTextureHeight)
	{
		renderTexHeight = height;
	}

	SizeT renderBufferWidth  = width;
	SizeT renderBufferHeight = height;

	if (renderBufferWidth > caps.mMaxTextureWidth)
	{
		renderBufferWidth = caps.mMaxTextureWidth;
	}

	if (renderBufferHeight > caps.mMaxTextureHeight)
	{
		renderBufferHeight = caps.mMaxTextureHeight;
	}


	//创建颜色缓冲纹理
	{
		glGenTextures(1, &m_GLESRenderTarget.FrameTexAttached);
		GLESImpl::Instance()->CheckError();

		glBindTexture(GL_TEXTURE_2D, m_GLESRenderTarget.FrameTexAttached);

		GLenum deviceInternalFormat = GLESTypes::AsGLESInternalPixelFormat( colorBufferFormat );
		GLenum deviceOriginFormat   = GLESTypes::AsGLESOriginPixelFormat( colorBufferFormat );
		GLenum deviceTypeFormat     = GLESTypes::AsGLESPixelDataType( colorBufferFormat );

		glTexImage2D(GL_TEXTURE_2D, 0, deviceInternalFormat, renderTexWidth, renderTexHeight, 0, deviceOriginFormat, deviceTypeFormat, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		GLESImpl::Instance()->CheckError();

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_GLESRenderTarget.FrameTexAttached, NULL);
		memorySize += PixelFormat::GetMemorySize( renderTexWidth, renderTexHeight, 1, this->GetColorBufferFormat() );

		GLESImpl::Instance()->CheckError();

	}

	//创建深度纹理或Renderbuffer
#if RENDERDEVICE_OPENGLES
	{
		if (caps.mDepthFormat)
		{
			glGenTextures(1, &m_GLESRenderTarget.FrameDepthTexAttached);
			GLESImpl::Instance()->CheckError();

			glBindTexture(GL_TEXTURE_2D, m_GLESRenderTarget.FrameDepthTexAttached);

			GLESImpl::Instance()->CheckError();

			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, renderTexWidth, renderTexHeight, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_GLESRenderTarget.FrameDepthTexAttached, NULL);

			memorySize += (renderTexWidth * renderTexHeight * 2);
			GLESImpl::Instance()->CheckError();
		}
		else
		{
			glGenRenderbuffers(1, &m_GLESRenderTarget.FrameDepthRBAttached);
			GLESImpl::Instance()->CheckError();

			glBindRenderbuffer(GL_RENDERBUFFER, m_GLESRenderTarget.FrameDepthRBAttached);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, renderBufferWidth, renderBufferHeight);

			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_GLESRenderTarget.FrameDepthRBAttached);
			GLESImpl::Instance()->CheckError();

			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}
		
	}
#endif

#if __ANDROID__ //|| __OSX__
	//创建模板Render buffer
	{
		glGenRenderbuffers(1, &m_GLESRenderTarget.FrameStencilAttached);
		GLESImpl::Instance()->CheckError();

		glBindRenderbuffer(GL_RENDERBUFFER, m_GLESRenderTarget.FrameStencilAttached);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_STENCIL_INDEX8, renderBufferWidth, renderBufferHeight);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_GLESRenderTarget.FrameStencilAttached);
		GLESImpl::Instance()->CheckError();

		glBindRenderbuffer(GL_RENDERBUFFER, 0);

	}
#endif

	if (!this->resolveTexture.isvalid())
	{
		this->resolveTexture = TextureGLES::Create();
		n_assert(this->resolveTexture.isvalid());
	}

	GLESImpl::Instance()->CheckFrameBuffer(m_GLESRenderTarget.FrameBuf);
#if __OSX__
	GLESImpl::Instance()->ActiveFrameBuffer(1);
#else
    GLESImpl::Instance()->ActiveFrameBuffer(0);
#endif
	GLESImpl::Instance()->ActiveTextureObject(GL_TEXTURE_2D, 0);

	Super::setup();
}

void RenderTargetGLES::Discard()
{
	if (m_GLESRenderTarget.FrameBuf > 0)
	{
		glDeleteFramebuffers(1, &m_GLESRenderTarget.FrameBuf);
		m_GLESRenderTarget.FrameBuf = 0;
	}

	if (m_GLESRenderTarget.FrameTexAttached > 0)
	{
		glDeleteTextures(1, &m_GLESRenderTarget.FrameTexAttached);
		m_GLESRenderTarget.FrameTexAttached = 0;
	}

	if (m_GLESRenderTarget.FrameDepthTexAttached > 0)
	{
		glDeleteTextures(1, &m_GLESRenderTarget.FrameDepthTexAttached);
		m_GLESRenderTarget.FrameDepthTexAttached = 0;
	}

	if (m_GLESRenderTarget.FrameDepthRBAttached > 0)
	{
		glDeleteRenderbuffers(1, &m_GLESRenderTarget.FrameDepthRBAttached);
		m_GLESRenderTarget.FrameDepthRBAttached = 0;
	}

	if (m_GLESRenderTarget.FrameStencilAttached > 0)
	{
		glDeleteRenderbuffers(1, &m_GLESRenderTarget.FrameStencilAttached);
		m_GLESRenderTarget.FrameStencilAttached = 0;
	}

	this->resolveTexture.downcast<TextureGLES>()->ClearDummy();
#ifdef __OSX__
	GLESImpl::Instance()->ActiveFrameBuffer(1);
#else
    GLESImpl::Instance()->ActiveFrameBuffer(0);
#endif
	GLESImpl::Instance()->ActiveTextureObject(GL_TEXTURE_2D, 0);

	Super::Discard();
}

void RenderTargetGLES::AssignGLESTextures()
{
	if (this->isDefaultRenderTarget)
	{
		return;
	}

	this->resolveTexture->Setup();
	this->resolveTexture.downcast<TextureGLES>()->SetupFromGLESTexture(m_GLESRenderTarget.FrameTexAttached);
	this->resolveTexture->SetWidth(this->width);
	this->resolveTexture->SetHeight(this->height);
}

void RenderTargetGLES::OnDeviceLost()
{
	m_GLESRenderTarget.Clear();
	if (this->resolveTexture.isvalid())
	{
		this->resolveTexture.downcast<TextureGLES>()->ClearDummy();
	}
}

void RenderTargetGLES::OnDeviceReset()
{
	LoadBuffers(GetWidth(),GetHeight());
	AssignGLESTextures();
}

}