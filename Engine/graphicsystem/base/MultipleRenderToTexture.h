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
#ifndef MULTIPLERENDERTOTEXTURE_H_
#define MULTIPLERENDERTOTEXTURE_H_


#include "rendersystem/base/RenderTarget.h"
#include "rendersystem/base/MultipleRenderTarget.h"
#include "RenderToTexture.h"
#include "util/array.h"

namespace Graphic
{

	class MultipleRenderToTexture : public Core::RefCounted
	{
		__DeclareSubClass(MultipleRenderToTexture,Core::RefCounted)

	public:

		MultipleRenderToTexture();

		virtual ~MultipleRenderToTexture();

		void Discard();

		const RenderBase::MultipleRenderTargetHandle& GetMultipleTargetHandle() const;

		void Setup();

		void AttachRenderTexture(const GPtr<RenderToTexture>& rt);

		void DettachRenderTextures();

	private:

		GPtr<RenderBase::MultipleRenderTarget> m_pMRT;
		RenderBase::MultipleRenderTargetHandle m_mrtHandle;

		Util::Array< RenderBase::RenderTargetHandle >    m_RenderTextures;
	};

	inline const RenderBase::MultipleRenderTargetHandle& MultipleRenderToTexture::GetMultipleTargetHandle() const
	{
		return m_mrtHandle;
	}

	inline void MultipleRenderToTexture::AttachRenderTexture(const GPtr<RenderToTexture> &rt)
	{
		m_RenderTextures.Append(rt->GetTargetHandle());
	}

	inline void MultipleRenderToTexture::DettachRenderTextures()
	{
		m_RenderTextures.Clear();
	}

}

#endif