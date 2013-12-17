/****************************************************************************
Copyright (C) 2007 Radon Labs GmbH
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
//  d3d9rendertarget.cc
//  (C) 2007 Radon Labs GmbH
//------------------------------------------------------------------------------
#if WIN32



#include "stdneb.h"
#include "profilesystem/ProfileSystem.h"
#include "RenderTargetD3D9.h"
#include "RenderDeviceD3D9.h"
#include "D3D9Types.h"

namespace D3D9
{
__ImplementClass(D3D9::RenderTargetD3D9, 'D9RT', RenderBase::RenderTarget);

//------------------------------------------------------------------------------
/**
*/
RenderTargetD3D9::RenderTargetD3D9() :
    d3d9RenderTarget(0),
    d3d9DepthStencil(0),
    d3d9ResolveTexture(0),
    d3d9CPUResolveTexture(0),
	d3d9swapChain(0),
    d3d9MultiSampleType(D3DMULTISAMPLE_NONE),
    d3d9MultiSampleQuality(0),
    d3d9ColorBufferFormat(D3DFMT_UNKNOWN),
    needsResolve(false),
	d3dpoolType(D3DPOOL_MANAGED)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
RenderTargetD3D9::~RenderTargetD3D9()
{
	Discard();
    n_assert(!this->isValid);
    n_assert(0 == this->d3d9RenderTarget);
    n_assert(0 == this->d3d9DepthStencil);
    n_assert(0 == this->d3d9ResolveTexture);
}
//------------------------------------------------------------------------------
/**
*/
void
RenderTargetD3D9::LoadBuffers(SizeT _width, SizeT _height)
{
	//todo : need not to set width && height .must be set before here
    n_assert(0 == this->d3d9RenderTarget);
    n_assert(0 == this->d3d9DepthStencil);
    n_assert(0 == this->d3d9ResolveTexture);
    HRESULT hr;
    RenderDeviceD3D9* device = RenderDeviceD3D9::Instance();
	memorySize = 0;

    // if we're the default render target, query display device
    // for setup parameters
    if (this->isDefaultRenderTarget)
    {
        // NOTE: the default render target will never be anti-aliased!
        // this assumes a render pipeline where the actual rendering goes
        // into an offscreen render target and is then resolved to the back buffer
		this->SetWidth(_width);
        this->SetHeight(_height);
        this->SetAntiAliasQuality(AntiAliasQuality::None);
		this->SetColorBufferFormat(PixelFormat::X8R8G8B8);
    }

	if (!this->isDefaultRenderTarget && screenSizeRatio > 0.f)
	{
		if (this->resolveTextureDimensionsValid)
		{
			if ((this->resolveTextureWidth != this->width) || (this->resolveTextureHeight != this->height))
			{
				//do nothing
			}
			else
			{
				this->SetResolveTextureWidth(SizeT(_width*screenSizeRatio));
				this->SetResolveTextureHeight(SizeT(_height*screenSizeRatio));
				this->resolveRect.right = int(_width*screenSizeRatio);
				this->resolveRect.bottom = int(_height*screenSizeRatio);
			}
		}

 		this->SetWidth(int(_width*screenSizeRatio));
 		this->SetHeight(int(_height*screenSizeRatio));
	}

    // setup our pixel format and multisample parameters (order important!)
    this->d3d9ColorBufferFormat = D3D9Types::AsD3D9PixelFormat(this->colorBufferFormat);
    this->SetupMultiSampleType();

    // check if a resolve texture must be allocated
    if (this->mipMapsEnabled ||
        (D3DMULTISAMPLE_NONE != this->d3d9MultiSampleType) ||
        (this->resolveTextureDimensionsValid &&
         ((this->resolveTextureWidth != this->width) ||
          (this->resolveTextureHeight != this->height))))
    {
        this->needsResolve = true;
    }
    else
    {
        this->needsResolve = false;
    }

    // create the render target either as a texture, or as
    // a surface, or don't create it if rendering goes
    // into backbuffer
    if (!this->needsResolve)
    {
        if (!this->isDefaultRenderTarget)
        {
            DWORD usage = D3DUSAGE_RENDERTARGET;
            D3DPOOL d3dpoolType = D3DPOOL_DEFAULT;

            // inplace resolve texture can be used (render target == resolve texture)
            hr = device->CreateTexture(this->width,                    // Width
                                        this->height,                   // Height
                                        1,                              // Levels
                                        usage,                          // Usage
                                        this->d3d9ColorBufferFormat,    // Format
                                        d3dpoolType,                           // Pool
                                        &(this->d3d9ResolveTexture),    // ppTexture
                                        NULL);                          // pSharedHandle
            n_assert(SUCCEEDED(hr));
            n_assert(0 != this->d3d9ResolveTexture);
            
            // get the actual render target surface of the texture
            hr = this->d3d9ResolveTexture->GetSurfaceLevel(0, &(this->d3d9RenderTarget));
            n_assert(SUCCEEDED(hr));
			memorySize += PixelFormat::GetMemorySize( width, height, 1, GetColorBufferFormat() );

            // create extra cpu texture for cpu look up (read-only)
            if (this->resolveCpuAccess)
            {
                usage = D3DUSAGE_DYNAMIC;        
                d3dpoolType = D3DPOOL_SYSTEMMEM;
                hr = device->CreateTexture(this->width,    // Width
                    this->height,                           // Height
                    1,                                      // Levels
                    usage,                                  // Usage
                    this->d3d9ColorBufferFormat,            // Format
                    d3dpoolType,                                   // Pool
                    &(this->d3d9CPUResolveTexture),         // ppTexture
                    NULL);                                  // pSharedHandle

                n_assert(SUCCEEDED(hr));
                n_assert(0 != this->d3d9CPUResolveTexture);
				memorySize += PixelFormat::GetMemorySize( width, height, 1, GetColorBufferFormat() );
            }
        }
        else
        {
            // NOTE: if we are the default render target and not antialiased, 
            // rendering will go directly to the backbuffer, so there's no
            // need to allocate a render target
            D3DPRESENT_PARAMETERS displayPresentParams = device->GetDefaultPresentParamters();
			displayPresentParams.BackBufferWidth = _width;
			displayPresentParams.BackBufferHeight = _height;
			displayPresentParams.BackBufferFormat = D3D9Types::AsD3D9PixelFormat(GetColorBufferFormat());
            device->CreateAdditionalSwapChain(&displayPresentParams,&d3d9swapChain);
        }
    }
    else
    {
        // need to create an extra resolve texture, create the
        // actual render target directly as surface
        hr = device->CreateRenderTarget(this->width,                   // Width
                                         this->height,                  // Height
                                         this->d3d9ColorBufferFormat,   // Format
                                         this->d3d9MultiSampleType,     // MultiSample
                                         this->d3d9MultiSampleQuality,  // MultisampleQuality
                                         FALSE,                         // Lockable
                                         &(this->d3d9RenderTarget),     // ppSurface
                                         NULL);                         // pSharedHandle
        n_assert(SUCCEEDED(hr));
        n_assert(0 != this->d3d9RenderTarget);

        // create the resolve texture
        SizeT resolveWidth = this->resolveTextureDimensionsValid ? this->resolveTextureWidth : this->width;
        SizeT resolveHeight = this->resolveTextureDimensionsValid ? this->resolveTextureHeight : this->height;

		memorySize += PixelFormat::GetMemorySize( width, height, 1, GetColorBufferFormat() );

        DWORD usage = D3DUSAGE_RENDERTARGET;
        d3dpoolType = D3DPOOL_DEFAULT;
        if (this->mipMapsEnabled)
        {
            usage |= D3DUSAGE_AUTOGENMIPMAP;
        }
        hr = device->CreateTexture(resolveWidth,                   // Width
                                    resolveHeight,                  // Height
                                    1,                              // Levels
                                    usage,                          // Usage
                                    this->d3d9ColorBufferFormat,    // Format
                                    d3dpoolType,                    // Pool
                                    &(this->d3d9ResolveTexture),    // ppTexture
                                    NULL);                          // pSharedHandle
        
        n_assert(SUCCEEDED(hr));
        n_assert(0 != this->d3d9ResolveTexture);
		memorySize += PixelFormat::GetMemorySize( resolveWidth, resolveHeight, 1, GetColorBufferFormat() );
        // create extra cpu texture for cpu look up (read-only)
        if (this->resolveCpuAccess)
        {
            usage = D3DUSAGE_DYNAMIC;        
            d3dpoolType = D3DPOOL_SYSTEMMEM;
            hr = device->CreateTexture(resolveWidth,                   // Width
                resolveHeight,                  // Height
                1,                              // Levels
                usage,                          // Usage
                this->d3d9ColorBufferFormat,    // Format
                d3dpoolType,                    // Pool
                &(this->d3d9CPUResolveTexture), // ppTexture
                NULL);                          // pSharedHandle

            n_assert(SUCCEEDED(hr));
            n_assert(0 != this->d3d9CPUResolveTexture);
			memorySize += PixelFormat::GetMemorySize( resolveWidth, resolveHeight, 1, GetColorBufferFormat() );
        }
    }

    // create the depth/stencil buffer if needed
    if (this->HasDepthStencilBuffer())
    {
        if (sharedDepthStencilBufferTarget.isvalid())
        {
			GPtr<RenderTargetD3D9> pSharedDepthStencilBufferTarget = this->sharedDepthStencilBufferTarget.downcast<RenderTargetD3D9>();
            n_assert(0 != pSharedDepthStencilBufferTarget->d3d9DepthStencil);
            n_assert(this->width == pSharedDepthStencilBufferTarget->width);
            n_assert(this->height == pSharedDepthStencilBufferTarget->height);
            n_assert(this->antiAliasQuality == pSharedDepthStencilBufferTarget->antiAliasQuality);
            this->d3d9DepthStencil = pSharedDepthStencilBufferTarget->d3d9DepthStencil;
            this->d3d9DepthStencil->AddRef();
        }
        else
        {
			D3DFORMAT dephFormat = D3DFMT_D24S8;
            hr = device->CreateDepthStencilSurface(this->width,                   // Width
                                                    this->height,                  // Height
                                                    dephFormat,                  // Format
                                                    this->d3d9MultiSampleType,     // MultiSample
                                                    this->d3d9MultiSampleQuality,  // MultisampleQuality
                                                    TRUE,                          // Discard
                                                    &(this->d3d9DepthStencil),     // ppSurface
                                                    NULL);                         // pSharedHandle
            n_assert(SUCCEEDED(hr));
            n_assert(0 != this->d3d9DepthStencil);
			memorySize += PixelFormat::GetMemorySize( width, height, 1, D3D9Types::AsGenesisPixelFormat(dephFormat));
        }
    }

	Super::setup();
}

void RenderTargetD3D9::AssignD3D9Textures(bool bIsLostDevice)
{
	// if a resolve texture exists, create a shared texture resource, so that
	// the texture is publicly visible
	if ((0 != this->d3d9ResolveTexture))
	{
		if (!bIsLostDevice)
		{
			this->resolveTexture = TextureD3D9::Create();
		}
		n_assert(this->resolveTexture.isvalid())
		this->resolveTexture->Setup();
		this->resolveTexture.downcast<TextureD3D9>()->SetupFromD3D9Texture(this->d3d9ResolveTexture);
		this->d3d9ResolveTexture->AddRef();
	}
	// if a cpu resolve texture exists, create a shared texture resource, so that
	// the texture is usable for a cpu lockup
	if ((0 != this->d3d9CPUResolveTexture)/* && this->resolveTextureResId.IsValid()*/)
	{
		if (!bIsLostDevice)
		{
			this->resolveCPUTexture = TextureD3D9::Create(); 
		}
		n_assert(this->resolveCPUTexture.isvalid())
		this->resolveCPUTexture->SetUsage(Texture::UsageDynamic);
		this->resolveCPUTexture->SetAccess(Texture::AccessRead);               
		this->resolveCPUTexture.downcast<TextureD3D9>()->SetupFromD3D9Texture(this->d3d9CPUResolveTexture);
		this->d3d9CPUResolveTexture->AddRef();
	}
}

//------------------------------------------------------------------------------
/**
*/
void
RenderTargetD3D9::Discard()
{
    if (0 != this->d3d9RenderTarget)
    {
        this->d3d9RenderTarget->Release();
        this->d3d9RenderTarget = 0;
    }
    if (0 != this->d3d9DepthStencil)
    {
        this->d3d9DepthStencil->Release();
        this->d3d9DepthStencil = 0;
    }
    if (0 != this->d3d9ResolveTexture)
    {
        this->d3d9ResolveTexture->Release();
        this->d3d9ResolveTexture = 0;
    }
    if (0 != this->d3d9CPUResolveTexture)
    {
        this->d3d9CPUResolveTexture->Release();
        this->d3d9CPUResolveTexture = 0;
    }
	if (0 != this->d3d9swapChain)
	{
		this->d3d9swapChain->Release();
		this->d3d9swapChain = 0;
	}
    Super::Discard();
}

//------------------------------------------------------------------------------
/**
    Select the antialias parameters that most closely resembly 
    the preferred settings in the DisplayDevice object.
*/

void
RenderTargetD3D9::SetupMultiSampleType()
{
    n_assert(D3DFMT_UNKNOWN != this->d3d9ColorBufferFormat);
    RenderDeviceD3D9* renderDevice = RenderDeviceD3D9::Instance();

    #if NEBULA3_DIRECT3D_DEBUG
        this->d3d9MultiSampleType = D3DMULTISAMPLE_NONE;
        this->d3d9MultiSampleQuality = 0;
    #else
        // convert Nebula3 antialias quality into D3D type
        this->d3d9MultiSampleType = D3D9Types::AsD3D9MultiSampleType(this->antiAliasQuality);
        
        // check if the multisample type is compatible with the selected display mode
        DWORD availableQualityLevels = 0;
        HRESULT renderTargetResult = renderDevice->CheckDeviceMultiSampleType(0, 
                                     D3DDEVTYPE_HAL,
                                     this->d3d9ColorBufferFormat,
                                     FALSE,
                                     this->d3d9MultiSampleType,
                                     &availableQualityLevels);
        HRESULT depthBufferResult = renderDevice->CheckDeviceMultiSampleType(0,
                                    D3DDEVTYPE_HAL,
                                    D3DFMT_D24S8,
                                    FALSE,
                                    this->d3d9MultiSampleType,
                                    NULL);
        if ((D3DERR_NOTAVAILABLE == renderTargetResult) || (D3DERR_NOTAVAILABLE == depthBufferResult))
        {
            // reset to no multisampling
            this->d3d9MultiSampleType = D3DMULTISAMPLE_NONE;
            this->d3d9MultiSampleQuality = 0;
        }
        else
        {
            n_assert(SUCCEEDED(renderTargetResult) && SUCCEEDED(depthBufferResult));
        }

        // clamp multisample quality to the available quality levels
        if (availableQualityLevels > 0)
        {
            this->d3d9MultiSampleQuality = availableQualityLevels - 1;
        }
        else
        {
            this->d3d9MultiSampleQuality = 0;
        }
    #endif
}  
//------------------------------------------------------------------------------
/**
*/

void
RenderTargetD3D9::EndPass()
{
    HRESULT hr;
    RenderDeviceD3D9* renderDevice = RenderDeviceD3D9::Instance();

    // if necessary need to resolve the render target, either
    // into our resolve texture, or into the back buffer
    if (this->needsResolve)
    {        
        RECT destRect;
        CONST RECT* pDestRect = NULL;
        if (this->resolveRectValid)
        {
            destRect.left   = this->resolveRect.left;
            destRect.right  = this->resolveRect.right;
            destRect.top    = this->resolveRect.top;
            destRect.bottom = this->resolveRect.bottom;
            pDestRect = &destRect;
        }
        IDirect3DSurface9* resolveSurface = 0;
        hr = this->d3d9ResolveTexture->GetSurfaceLevel(0, &resolveSurface);
        hr = renderDevice->StretchRect(this->d3d9RenderTarget, NULL, resolveSurface, pDestRect, D3DTEXF_NONE);
        n_assert(SUCCEEDED(hr));
        
        // need cpu access, copy from gpu mem to sys mem
        if (this->resolveCpuAccess)
        {
            HRESULT hr;   
            D3DLOCKED_RECT dstLockRect;
            D3DLOCKED_RECT srcLockRect;
            IDirect3DSurface9* dstSurface = 0;
            hr = this->d3d9CPUResolveTexture->GetSurfaceLevel(0, &dstSurface);
            n_assert(SUCCEEDED(hr));
            hr = dstSurface->LockRect(&dstLockRect, 0, 0);
            n_assert(SUCCEEDED(hr));
            hr = resolveSurface->LockRect(&srcLockRect, 0, D3DLOCK_READONLY);
            n_assert(SUCCEEDED(hr));
            Memory::Copy(srcLockRect.pBits, dstLockRect.pBits, dstLockRect.Pitch * this->resolveCPUTexture->GetWidth());
            dstSurface->Release();
        }
        resolveSurface->Release();
    }
    else if (this->resolveCpuAccess)
    {
        HRESULT hr;
        // copy data
        IDirect3DSurface9* resolveSurface = 0;
        hr = this->d3d9CPUResolveTexture->GetSurfaceLevel(0, &resolveSurface);
        n_assert(SUCCEEDED(hr));
        hr = renderDevice->GetRenderTargetData(this->d3d9RenderTarget, resolveSurface);
        n_assert(SUCCEEDED(hr));
        resolveSurface->Release();
    }
    // unset multiple rendertargets
    if (this->mrtIndex > 0)
    {
        renderDevice->SetRenderTarget(this->mrtIndex, 0);
    }    
}

//------------------------------------------------------------------------------
/**
*/
void
RenderTargetD3D9::GenerateMipLevels()
{
    n_assert(0 != this->d3d9ResolveTexture);
    n_assert(this->mipMapsEnabled);
    this->d3d9ResolveTexture->GenerateMipSubLevels();
}

//------------------------------------------------------------------------------
/**
*/
void
RenderTargetD3D9::OnDeviceLost()
{
	if (this->sharedDepthStencilBufferTarget.isvalid())
	{
		this->sharedDepthStencilBufferTarget.downcast<RenderTargetD3D9>()->OnDeviceLost();
	}
	if (this->resolveTexture.isvalid())
	{
		this->resolveTexture.downcast<TextureD3D9>()->OnDeviceLost();
	}
	if (this->resolveCPUTexture.isvalid())
	{
		resolveCPUTexture.downcast<TextureD3D9>()->OnDeviceLost();
	}
	if (this->resolveDepthTexture.isvalid())
	{
		resolveDepthTexture.downcast<TextureD3D9>()->OnDeviceLost();
	}
	if (0 != this->d3d9RenderTarget)
	{
		this->d3d9RenderTarget->Release();
		this->d3d9RenderTarget = 0;
	}
	if (0 != this->d3d9DepthStencil)
	{
		this->d3d9DepthStencil->Release();
		this->d3d9DepthStencil = 0;
	}
	if (0 != this->d3d9ResolveTexture)
	{
		this->d3d9ResolveTexture->Release();
		this->d3d9ResolveTexture = 0;
	}
	if (0 != this->d3d9CPUResolveTexture)
	{
		this->d3d9CPUResolveTexture->Release();
		this->d3d9CPUResolveTexture = 0;
	}
	if (0 != this->d3d9swapChain)
	{
		this->d3d9swapChain->Release();
		this->d3d9swapChain = 0;
	}
	this->isValid = false;
}
//------------------------------------------------------------------------------
/**
*/
void
RenderTargetD3D9::OnDeviceReset()
{
	LoadBuffers(GetWidth(),GetHeight());
	AssignD3D9Textures(true);
}

//------------------------------------------------------------------------------
/**
*/
void
	RenderTargetD3D9::CopyFrom(const Math::float4& srcRect, const GPtr<RenderTarget>srcRT, const Math::float4& desRect)
{
	GPtr<RenderTargetD3D9> srt = srcRT.downcast<RenderTargetD3D9>();
	n_assert(srt);
	HRESULT hr;
	RenderDeviceD3D9* renderDevice = RenderDeviceD3D9::Instance();

	RECT srcRECT;
	srcRECT.left = LONG(srcRect.x());
	srcRECT.top = LONG(srcRect.y());
	srcRECT.right = LONG(srcRect.z());
	srcRECT.bottom = LONG(srcRect.w());

	RECT desRECT;
	desRECT.left = LONG(desRect.x());
	desRECT.top = LONG(desRect.y());
	desRECT.right = LONG(desRect.z());
	desRECT.bottom = LONG(desRect.w());
	hr = renderDevice->StretchRect(srt->GetD3DRT(),&srcRECT,d3d9RenderTarget,&desRECT,D3DTEXF_NONE);
	n_assert(SUCCEEDED(hr));
}


} // namespace D3D9

#endif
