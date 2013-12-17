/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/
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
#include <cstring>
#include "MyGUI_GenesisRTTexture.h"
#include "MyGUI_GenesisRenderManager.h"

namespace MyGUI
{

	GenesisRTTexture::GenesisRTTexture(GPtr<Graphic::RenderToTexture>& rtt)
	{
		m_rtt = rtt;
		const GPtr<RenderBase::RenderTarget>& renderTarget = rtt->GetRenderTarget();

		size_t width = renderTarget->GetWidth();
		size_t height = renderTarget->GetHeight();

		Graphic::GraphicSystem* gs = Graphic::GraphicSystem::Instance();

		mRenderTargetInfo.maximumDepth = gs->GetMaximumDepthInputValue();
		mRenderTargetInfo.hOffset = gs->GetHorizontalTexelOffset() / float(width);
		mRenderTargetInfo.vOffset = gs->GetVerticalTexelOffset() / float(height);
		mRenderTargetInfo.aspectCoef = float(height) / float(width);
		mRenderTargetInfo.pixScaleX = 1.0f / float(width);
		mRenderTargetInfo.pixScaleY = 1.0f / float(height);
	}

	GenesisRTTexture::~GenesisRTTexture()
	{
		m_rtt = NULL;
	}

	void GenesisRTTexture::begin()
	{
		GenesisRenderManager::getInstance()._beforeDraw();
		Graphic::GraphicSystem::Instance()->SetRenderTarget(m_rtt->GetTargetHandle(), 0);	
	}

	void GenesisRTTexture::end()
	{
		Graphic::GraphicSystem::Instance()->SetRenderTarget(RenderBase::TextureHandle(NULL), 0);	
	}

	void GenesisRTTexture::doRender(IVertexBuffer* _buffer, ITexture* _texture, size_t _count)
	{
		GenesisRenderManager::getInstance().doRender(_buffer, _texture, _count);
	}

} // namespace MyGUI
