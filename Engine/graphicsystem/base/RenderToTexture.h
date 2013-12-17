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
#ifndef RENDERTOTEXTURE_H_
#define RENDERTOTEXTURE_H_

#include "rendersystem/base/RenderTarget.h"
#include "foundation/util/scriptbind.h"

#if __WIN32__
#include "rendersystem/d3d9/TextureD3D9.h"
#endif

#include "util/array.h"
#include "core/singleton.h"

namespace Graphic
{
	class QuadRenderable;
	static const RenderBase::RenderResourceHandle dummyhandle = NULL;
	class RenderToTexture : public Core::RefCounted
	{
		__DeclareSubClass(RenderToTexture,Core::RefCounted)
			__ScriptBind
	public:
		RenderToTexture();
		virtual ~RenderToTexture();

		virtual void Discard();

		virtual void Setup(const int& width, const int& height,
			const RenderBase::PixelFormat::Code& colorFormat = RenderBase::PixelFormat::A32B32G32R32F,
			const uint& flag = RenderBase::RenderTarget::ClearColor, const Math::float4& color = Math::float4(0.f,0.f,1.f,1.f), 
			const bool& useDepth = false, const float& screenRatio = 0.f,
			RenderBase::AntiAliasQuality::Code quality = RenderBase::AntiAliasQuality::None,
			const Math::rectangle<int>& resolveRect = Math::rectangle<int>(0,0,0,0),
			const bool& isBackBuffer = false);

		void SetShareDepthStencilRT(const GPtr<RenderBase::RenderTarget>& rt);
		const RenderBase::RenderTargetHandle& GetTargetHandle() const;
		const GPtr<RenderBase::RenderTarget>& GetRenderTarget() const;
		const GPtr<RenderBase::RenderTarget>& GetShareDepthRenderTarget() const;
		const RenderBase::TextureHandle& GetTextureHandle() const;
		bool SaveTexture(const Util::String& path);

#if __WIN32__
		const D3D9::TextureD3D9& GetD3DTexture9();
#endif

		void ResetQuad();

		void ChangeSize(int width,int height);
		const GPtr<QuadRenderable>& GetRenderable() const;
	private:

		GPtr<RenderBase::RenderTarget> m_RT;
		RenderBase::RenderTargetHandle m_rtHandle;
		RenderBase::TextureHandle m_texHandle;
		GPtr<RenderBase::RenderTarget> m_shareDepthStencilRT;
		GPtr<QuadRenderable> m_quadRenderable;
		int                 m_width;
		int                 m_height;
	};

	class RenderToTextureManager : public Core::RefCounted
	{
		__DeclareSubClass(RenderToTextureManager, Core::RefCounted)
			__DeclareImageSingleton(RenderToTextureManager)

	public:
		RenderToTextureManager();

		virtual ~RenderToTextureManager();


	private:
		Util::Array< RenderToTexture* > m_RenderToTextures;

	};

	inline const RenderBase::RenderTargetHandle&
		RenderToTexture::GetTargetHandle() const
	{
		return m_rtHandle;
	}

	inline const RenderBase::TextureHandle&
		RenderToTexture::GetTextureHandle() const
	{
		return m_texHandle;
	}

	inline const GPtr<RenderBase::RenderTarget>& 
		RenderToTexture::GetRenderTarget() const
	{
		return m_RT;
	}

	inline const GPtr<RenderBase::RenderTarget>&
		RenderToTexture::GetShareDepthRenderTarget() const
	{
		return m_shareDepthStencilRT;
	}

	inline void 
		RenderToTexture::SetShareDepthStencilRT(const GPtr<RenderBase::RenderTarget>& rt)
	{
		m_shareDepthStencilRT = rt;
	}

	inline const GPtr<QuadRenderable>& 
		RenderToTexture::GetRenderable() const
	{
		return m_quadRenderable;
	}
}
#endif