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
#ifndef RENDERTARGET_H_
#define RENDERTARGET_H_

#include "RenderCommandType.h"
#include "RenderDeviceTypes.h"
#include "Texture.h"
#include "math/rectangle.h"

namespace RenderBase
{
class RenderTarget;
}

//------------------------------------------------------------------------------
namespace RenderBase
{
class RenderTarget : public RenderCommandType
{
    __DeclareClass(RenderTarget);
public:
    /// clear flags
    enum ClearFlag
    {
		ClearNone = 0,
        ClearColor = (1<<0),
        ClearDepth = (1<<1),
        ClearStencil = (1<<2),
		ClearAll = ClearColor | ClearDepth | ClearStencil,
    };

    /// constructor
    RenderTarget();
    /// destructor
    virtual ~RenderTarget();
  	/// discard the render target object
	virtual void Discard();

    /// return true if valid (has been setup)
    bool IsValid() const;



    /// set to true if default render target (only called by RenderDevice)
    void SetDefaultRenderTarget(bool b);
    /// get default render target flag
    bool IsDefaultRenderTarget() const;
    /// set render target width
    void SetWidth(SizeT w);
    /// get width of render target in pixels
    SizeT GetWidth() const;
    /// set render target height
    void SetHeight(SizeT h);
    /// get height of render target in pixels
    SizeT GetHeight() const;
    /// set antialias quality
    void SetAntiAliasQuality(AntiAliasQuality::Code c);
    /// get anti-alias-quality
    AntiAliasQuality::Code GetAntiAliasQuality() const;
    /// add a color buffer
    void SetColorBufferFormat(PixelFormat::Code colorFormat);
    /// get color buffer format at index
    PixelFormat::Code GetColorBufferFormat() const;
    /// internally create a depth/stencil buffer
    void AddDepthStencilBuffer();
    /// use external depth-stencil buffer
    void AddSharedDepthStencilBuffer(const GPtr<RenderTarget>& rt);
    /// return true if the render target has a depth/stencil buffer
    bool HasDepthStencilBuffer() const;
    /// enable mipmap generation for this render target
    void SetMipMapsEnabled(bool b);
    /// get mipmap generation flag
    bool AreMipMapsEnabled() const;
    /// set resolve texture width
    void SetResolveTextureWidth(SizeT w);
    /// get resolve texture width
    SizeT GetResolveTextureWidth() const;
    /// set resolve texture height
    void SetResolveTextureHeight(SizeT h);
    /// get resolve texture height
    SizeT GetResolveTextureHeight() const;    
    /// set cpu access flag
    void SetResolveTargetCpuAccess(bool b);
    /// get cpu access flag
    bool GetResolveTargetCpuAccess() const;
    /// set optional MRT (Multiple Render Target) index, default is 0
    void SetMRTIndex(IndexT i);
    /// get multiple-render-target index
    IndexT GetMRTIndex() const;

    /// set clear flags
    void SetClearFlags(uint clearFlags);
    /// get clear flags
    uint GetClearFlags() const;
    /// set clear color 
    void SetClearColor(const Math::float4& c);
    /// get clear color
    const Math::float4& GetClearColor() const;
    /// set clear depth
    void SetClearDepth(float d);
    /// get clear depth
    float GetClearDepth() const;
    /// set clear stencil value
    void SetClearStencil(uchar s);
    /// get clear stencil value
    uchar GetClearStencil() const;
    /// set the current resolve rectangle (in pixels)
    void SetResolveRect(const Math::rectangle<int>& r);
    /// get resolve rectangle
    const Math::rectangle<int>& GetResolveRect() const;

    /// begin rendering to the render target
    void BeginPass();
    /// begin a batch
    void BeginBatch();
    /// end current batch
    void EndBatch();
    /// end current render pass
    void EndPass();
    /// generate mipmap levels
    void GenerateMipLevels();
    /// return true if resolve texture is valid
    bool HasResolveTexture() const;
    /// get the resolve texture as Nebula texture object
    const GPtr<Texture>& GetResolveTexture() const;  
    /// return true if cpu access resolve texture is valid
    bool HasCPUResolveTexture() const;
    /// get the resolve texture as Nebula texture object
    const GPtr<Texture>& GetCPUResolveTexture() const;  
    /// return true if resolve texture is valid
    bool HasDepthResolveTexture() const;
    /// get the resolve texture as Nebula texture object
    const GPtr<Texture>& GetDepthResolveTexture() const;
    /// resolve depth buffer
    virtual void ResolveDepthBuffer();

	/// on device lost
	virtual void OnDeviceLost();
	/// on device reset
	virtual void OnDeviceReset();

	/// set use screen size
	void SetScreenSizeRatio(float ratio = 0.f);
	/// get screen size ratio
	const float GetScreenSizeRatio() const;

    /// get byte size in memory, implemented in platform specific classes
    int GetMemorySize();		
	/// 
	bool IsResolveTextureDimensionsValid() const;

	///
	virtual void CopyFrom(const Math::float4& srcRect, const GPtr<RenderTarget>srcRT, const Math::float4& desRect);

	///
	void SetDummy(bool b);

	///
	bool IsDummy() const;


	/// 
	void AttachToMRT();
	///
	bool IsAttachedToMRT() const;

protected:
	/// setup the render target object
	void setup();

    friend class RenderDevice;
    GPtr<RenderTarget> sharedDepthStencilBufferTarget;   // target which provides shared depth-stencil buffer
    SizeT width;
    SizeT height;
    bool resolveTextureDimensionsValid;
    bool resolveRectValid;
    SizeT resolveTextureWidth;
    SizeT resolveTextureHeight;
    Math::rectangle<int> resolveRect;
    IndexT mrtIndex;
    uint clearFlags;
    Math::float4 clearColor;
    float clearDepth;
    uchar clearStencil;
    AntiAliasQuality::Code antiAliasQuality;
    PixelFormat::Code colorBufferFormat;
    GPtr<Texture> resolveTexture;
    GPtr<Texture> resolveCPUTexture;
    GPtr<Texture> resolveDepthTexture;
    bool mipMapsEnabled;
    bool isValid;
    bool inBeginPass;
    bool inBeginBatch;
    bool hasDepthStencilBuffer;
    bool isDefaultRenderTarget;
	float screenSizeRatio; //if not 0,use screenSize * screenSizeRatio as RT width and height
    bool resolveCpuAccess;
	int memorySize;
	bool  attahcedToMRT;
	bool  dummyRT;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderTarget::IsValid() const
{
    return this->isValid;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetDefaultRenderTarget(bool b)
{
    this->isDefaultRenderTarget = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderTarget::IsDefaultRenderTarget() const
{
    return this->isDefaultRenderTarget;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetWidth(SizeT w)
{
    this->width = w;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
RenderTarget::GetWidth() const
{
    return this->width;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetHeight(SizeT h)
{
    this->height = h;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
RenderTarget::GetHeight() const
{
    return this->height;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetAntiAliasQuality(AntiAliasQuality::Code aaq)
{
    this->antiAliasQuality = aaq;
}

//------------------------------------------------------------------------------
/**
*/
inline AntiAliasQuality::Code
RenderTarget::GetAntiAliasQuality() const
{
    return this->antiAliasQuality;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetColorBufferFormat(PixelFormat::Code colorFormat)
{
    this->colorBufferFormat = colorFormat;
}

//------------------------------------------------------------------------------
/**
*/
inline PixelFormat::Code
RenderTarget::GetColorBufferFormat() const
{
    return this->colorBufferFormat;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderTarget::HasDepthStencilBuffer() const
{
    return this->hasDepthStencilBuffer;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetClearColor(const Math::float4& c)
{
    this->clearColor = c;
}

//------------------------------------------------------------------------------
/**
*/
inline const Math::float4&
RenderTarget::GetClearColor() const
{
    return this->clearColor;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetClearDepth(float d)
{
    this->clearDepth = d;
}

//------------------------------------------------------------------------------
/**
*/
inline float
RenderTarget::GetClearDepth() const
{
    return this->clearDepth;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetClearStencil(uchar s)
{
    this->clearStencil = s;
}

//------------------------------------------------------------------------------
/**
*/
inline uchar
RenderTarget::GetClearStencil() const
{
    return this->clearStencil;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderTarget::HasResolveTexture() const
{
    return this->resolveTexture.isvalid();
}

//------------------------------------------------------------------------------
/**
*/
inline const GPtr<Texture>&
RenderTarget::GetResolveTexture() const
{
    n_assert(this->resolveTexture.isvalid());
    return this->resolveTexture;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderTarget::HasCPUResolveTexture() const
{
    return this->resolveCPUTexture.isvalid();
}

//------------------------------------------------------------------------------
/**
*/
inline const GPtr<Texture>&
RenderTarget::GetCPUResolveTexture() const
{
    n_assert(this->resolveCPUTexture.isvalid());
    return this->resolveCPUTexture;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderTarget::HasDepthResolveTexture() const
{
    return this->resolveDepthTexture.isvalid();
}

//------------------------------------------------------------------------------
/**
*/
inline const GPtr<Texture>& 
RenderTarget::GetDepthResolveTexture() const
{
    n_assert(this->resolveDepthTexture.isvalid());
    return this->resolveDepthTexture;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetMipMapsEnabled(bool b)
{
    this->mipMapsEnabled = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderTarget::AreMipMapsEnabled() const
{
    return this->mipMapsEnabled;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetResolveTextureWidth(SizeT w)
{
    this->resolveTextureWidth = w;
    this->resolveTextureDimensionsValid = true;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
RenderTarget::GetResolveTextureWidth() const
{
    return this->resolveTextureWidth;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetResolveTextureHeight(SizeT h)
{
    this->resolveTextureHeight = h;
    this->resolveTextureDimensionsValid = true;
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
RenderTarget::GetResolveTextureHeight() const
{
    return this->resolveTextureHeight;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetResolveRect(const Math::rectangle<int>& r)
{
    this->resolveRectValid = true;
    this->resolveRect = r;
}

//------------------------------------------------------------------------------
/**
*/
inline const Math::rectangle<int>&
RenderTarget::GetResolveRect() const
{
    return this->resolveRect;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetResolveTargetCpuAccess(bool b)
{
    this->resolveCpuAccess = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
RenderTarget::GetResolveTargetCpuAccess() const
{
    return this->resolveCpuAccess;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetMRTIndex(IndexT i)
{
    this->mrtIndex = i;
}

//------------------------------------------------------------------------------
/**
*/
inline IndexT
RenderTarget::GetMRTIndex() const
{
    return this->mrtIndex;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetClearFlags(uint f)
{
    this->clearFlags = f;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
RenderTarget::GetClearFlags() const
{
    return this->clearFlags;
}
//------------------------------------------------------------------------------
/**
*/
inline bool
RenderTarget::IsResolveTextureDimensionsValid() const
{
	return this->resolveTextureDimensionsValid;
}

/// set use screen size
inline void 
RenderTarget::SetScreenSizeRatio(float ratio)
{
	screenSizeRatio = ratio;
}
/// get screen size ratio
inline const float 
RenderTarget::GetScreenSizeRatio() const
{
	return screenSizeRatio;
}


inline void
	RenderTarget::AttachToMRT()
{
	this->attahcedToMRT = true;
}

inline bool
	RenderTarget::IsAttachedToMRT() const
{
	return this->attahcedToMRT;
}

//------------------------------------------------------------------------------
/**
*/
inline void
	RenderTarget::SetDummy(bool b)
{
	dummyRT = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
	RenderTarget::IsDummy() const
{
	return dummyRT;
}


} // namespace RenderBase    
//------------------------------------------------------------------------------

#endif
