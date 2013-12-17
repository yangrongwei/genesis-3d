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
#include "RenderToTexture.h"
#include "GraphicSystem.h"
#if __WIN32__
#include "rendersystem/d3d9/RenderDeviceD3D9.h"
#include "d3d9/TextureD3D9.h"
#include "d3d9/D3D9Types.h"
#endif

#include "addons/resource/imageoperations.h"
#include "Renderable/QuadRenderable.h"

namespace Graphic
{
	__ImplementClass(RenderToTexture,'RTGS',Core::RefCounted)
		__ImplementClass(RenderToTextureManager,'RTMG',Core::RefCounted);
	__ImplementImageSingleton(RenderToTextureManager);

	RenderToTexture::RenderToTexture()
		: m_width(1),
		m_height(1)
	{

	}

	RenderToTexture::~RenderToTexture()
	{
		Discard();
	}

	void RenderToTexture::Setup(const int& width, const int& height, const RenderBase::PixelFormat::Code& colorFormat, const uint& flag, const Math::float4& color, 
		const bool& useDepth, const float& screenRatio,
		RenderBase::AntiAliasQuality::Code quality,
		const Math::rectangle<int>& resolveRect, const bool& isBackBuffer)
	{

		GPtr<RenderBase::RenderTarget> shareDepthStencilRT = m_shareDepthStencilRT;

		// 为了修复共享深度buffer的bug，创建一个m_shareDepthStencilRT的备份
		Discard();
		m_shareDepthStencilRT = shareDepthStencilRT;

		m_RT = RenderBase::RenderTarget::Create();
		m_RT->SetDefaultRenderTarget(isBackBuffer);
		m_RT->SetWidth(width);
		m_RT->SetHeight(height);

		if (resolveRect.right == 0 && resolveRect.left == 0 && resolveRect.top == 0 && resolveRect.bottom == 0)
		{
		}
		else
		{
			m_RT->SetResolveTextureWidth(resolveRect.width());
			m_RT->SetResolveTextureHeight(resolveRect.height());
			m_RT->SetResolveRect(resolveRect);
		}

		m_RT->SetScreenSizeRatio(screenRatio);
		m_RT->SetClearColor(color);
		m_RT->SetClearFlags(flag);
		m_RT->SetColorBufferFormat(colorFormat);
		m_RT->SetAntiAliasQuality(quality);
		if (useDepth)
		{
			if (m_shareDepthStencilRT.isvalid())
			{
				m_RT->AddSharedDepthStencilBuffer(m_shareDepthStencilRT);
			}
			else
			{
				m_RT->AddDepthStencilBuffer();
			}
		}
		m_rtHandle = GraphicSystem::Instance()->CreateRenderTarget(m_RT,m_texHandle);

		if (!m_quadRenderable.isvalid())
		{
			m_quadRenderable = QuadRenderable::Create();
		}
		else
		{
			m_quadRenderable->Discard();
		}

		m_quadRenderable->Setup(width, height);

		m_width  = width;
		m_height = height;
	}

	void RenderToTexture::ChangeSize(int width,int height)
	{
		m_RT->SetWidth(width);
		m_RT->SetHeight(height);
		GraphicSystem::Instance()->ReSizeRenderTarget(m_rtHandle,width,height);

		if (m_quadRenderable.isvalid())
		{
			m_quadRenderable->Discard();
		}
		else
		{
			m_quadRenderable = QuadRenderable::Create();
		}

		m_quadRenderable->Setup(width, height);
	}

	void RenderToTexture::Discard()
	{
		if (m_texHandle.IsValid())
		{
			GraphicSystem::Instance()->RemoveTexture(m_texHandle);
			m_texHandle = dummyhandle;
		}

		if (m_rtHandle.IsValid())
		{
			GraphicSystem::Instance()->RemoveRenderTarget(m_rtHandle);
			m_rtHandle = dummyhandle;
		}
		m_shareDepthStencilRT = 0;
		m_RT = 0;
	}

	bool RenderToTexture::SaveTexture( const Util::String& path )
	{
#if __WIN32__
		Core::RefCounted* Ro = this->m_texHandle.AsObject();
		n_assert(Ro!=NULL);
		D3D9::TextureD3D9 * Instance = reinterpret_cast<D3D9::TextureD3D9*>(Ro);
		n_assert(Instance!=NULL);

		SizeT levelPixelSize =Instance->GetTextureSize();

		ubyte* data = new ubyte[levelPixelSize];
		n_assert(data!=NULL);
		Instance->GetTextureData(data);

		GPtr<Resources::ImageRes> textureImageRes = Resources::ImageRes::Create();
		textureImageRes->SetHeight(Instance->GetHeight());
		textureImageRes->SetWidth(Instance->GetWidth());
		textureImageRes->SetPixelFormat(Instance->GetPixelFormat());
		textureImageRes->SetDepth(1);
		textureImageRes->SetMipMapLevel(1);
		textureImageRes->SetNumFace(1);
		textureImageRes->SetImageData(data, levelPixelSize);
		return Resources::ImageOperations::SaveTGAImage(path, textureImageRes);
#endif

		return false;
	}

#if __WIN32__
	const D3D9::TextureD3D9& RenderToTexture::GetD3DTexture9()
	{
		const RenderBase::TextureHandle handle = this->GetTextureHandle();
		const Core::RefCounted* Ro = handle.AsObject();
		const D3D9::TextureD3D9* front = reinterpret_cast<const D3D9::TextureD3D9*>(Ro);
		return *front;
	}
#endif

	void RenderToTexture::ResetQuad()
	{
		m_quadRenderable->Setup(m_width, m_height);
	}

	RenderToTextureManager::RenderToTextureManager()
	{
		__ConstructImageSingleton
	}

	RenderToTextureManager::~RenderToTextureManager()
	{
		__DestructImageSingleton
			m_RenderToTextures.Clear();
	}


}