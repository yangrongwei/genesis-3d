/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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

//------------------------------------------------------------------------------
//  rendertargetbase.cc
//  (C) 2007 Radon Labs GmbH
//------------------------------------------------------------------------------
#include "stdneb.h"
#include "profilesystem/ProfileSystem.h"
#include "RenderTarget.h"

namespace RenderBase
{
	__ImplementClass(RenderBase::RenderTarget, 'RTRS', RenderCommandType);


	//------------------------------------------------------------------------------
	/**
	*/
	RenderTarget::RenderTarget() :
		width(0),
		height(0),
		resolveTextureDimensionsValid(false),
		resolveRectValid(false),
		resolveTextureWidth(0),
		resolveTextureHeight(0),
		resolveRect(0, 0, 0, 0),
		mrtIndex(0),
		clearFlags(0),
		memorySize(0),
		clearColor(0.0f, 0.0f, 1.0f, 0.0f),
		clearDepth(1.0f),
		clearStencil(0),
		antiAliasQuality(AntiAliasQuality::None),
		colorBufferFormat(PixelFormat::X8R8G8B8),
		mipMapsEnabled(false),
		isValid(false),    
		inBeginPass(false),
		inBeginBatch(false),
		hasDepthStencilBuffer(false),
		isDefaultRenderTarget(false),
		resolveCpuAccess(false),
		screenSizeRatio(0.0),
		attahcedToMRT(false),
		dummyRT(false)
	{
		SetRenderCommandType(RenderCommandType::SetRenderTarget);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	RenderTarget::~RenderTarget()
	{
		n_assert(!this->isValid);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::setup()
	{
		n_assert(!this->isValid);
		this->isValid = true;
		SetRenderCommandType(RenderCommandType::SetRenderTarget);
		PROFILER_ADDDEVICESTATEVAL(videoRam, memorySize);
		PROFILER_ADDDEVICESTATEVAL(fboRam, memorySize);
		PROFILER_ADDDEVICESTATEVAL(renderTargetNum, 1);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::Discard()
	{
		PROFILER_ADDDEVICESTATEVAL(videoRam, -memorySize);
		PROFILER_ADDDEVICESTATEVAL(fboRam, -memorySize);
		PROFILER_ADDDEVICESTATEVAL(renderTargetNum, -1);
		memorySize = 0;

		n_assert(this->isValid);
		n_assert(!this->inBeginPass);
		n_assert(!this->inBeginBatch);
		this->sharedDepthStencilBufferTarget = 0;
		if (this->resolveTexture.isvalid())
		{
			this->resolveTexture = 0;
		}
		if (this->resolveCPUTexture.isvalid())
		{
			resolveCPUTexture = 0;
		}
		if (this->resolveDepthTexture.isvalid())
		{
			resolveDepthTexture = 0;
		}
		this->isValid = false;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::AddDepthStencilBuffer()
	{
		n_assert(!this->hasDepthStencilBuffer);
		this->hasDepthStencilBuffer = true;
		this->sharedDepthStencilBufferTarget = 0;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::AddSharedDepthStencilBuffer(const GPtr<RenderTarget>& rt)
	{
		n_assert(!this->hasDepthStencilBuffer);
		this->hasDepthStencilBuffer = true;
		this->sharedDepthStencilBufferTarget = rt;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::BeginPass()
	{
		n_assert(this->isValid);
		n_assert(!this->inBeginPass);
		n_assert(!this->inBeginBatch);
		this->inBeginPass = true;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::BeginBatch()
	{
		n_assert(this->inBeginPass);
		n_assert(!this->inBeginBatch);
		this->inBeginBatch = true;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::EndBatch()
	{
		n_assert(this->inBeginBatch);
		this->inBeginBatch = false; 
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::EndPass()
	{
		n_assert(this->isValid);
		n_assert(this->inBeginPass);
		n_assert(!this->inBeginBatch);
		this->inBeginPass = false;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::GenerateMipLevels()
	{
		n_assert(this->mipMapsEnabled);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::ResolveDepthBuffer()
	{
		n_error("RenderTargetBase::ResolveDepthBuffer not implemented!");
	}

	//------------------------------------------------------------------------------
	/**
	*/
	int 
		RenderTarget::GetMemorySize()
	{
		return memorySize;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void 
		RenderTarget::CopyFrom(const Math::float4& srcRect, const GPtr<RenderTarget>srcRT, const Math::float4& desRect)
	{
		n_error("this function need to be implemented in child class!");
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderTarget::OnDeviceLost()
	{

	}

	//------------------------------------------------------------------------------
	/**
	*/
	void 
		RenderTarget::OnDeviceReset()
	{

	}

} // namespace Base