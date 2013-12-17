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
#ifndef RENDERTARGETD3D9_H_
#define RENDERTARGETD3D9_H_

#include "base/RenderTarget.h"
#include "d3d9/TextureD3D9.h"

//------------------------------------------------------------------------------
namespace D3D9
{
	using namespace RenderBase;
class RenderTargetD3D9 : public RenderTarget
{
	__DeclareSubClass(RenderTargetD3D9,RenderTarget);
public:
    /// constructor
    RenderTargetD3D9();
    /// destructor
    virtual ~RenderTargetD3D9();
    /// discard the render target object
    virtual void Discard();  
    /// setup the render target object
    //void LoadBuffers();
	void LoadBuffers(SizeT _width, SizeT _height);

	/// binding textures;
	void AssignD3D9Textures(bool bIsLostDevice = false);

    /// begin a render pass
    void BeginPass();
    /// end current render pass
    void EndPass();
    /// generate mipmap levels
    void GenerateMipLevels();

	/// on device lost
	virtual void OnDeviceLost();
	/// on device reset
	virtual void OnDeviceReset();

	D3DPOOL GetD3D9PoolType();

	IDirect3DSurface9* GetD3DRT()	{ return d3d9RenderTarget ; }

	IDirect3DSwapChain9* GetD3D9SwapChain() { return d3d9swapChain ; }

	void CopyFrom(const Math::float4& srcRect, const GPtr<RenderTarget>srcRT, const Math::float4& desRect);

protected:
    friend class RenderDeviceD3D9;

    /// setup compatible multisample type
    void SetupMultiSampleType();
                                                      
    IDirect3DSurface9* d3d9RenderTarget;
    IDirect3DSurface9* d3d9DepthStencil;
    IDirect3DTexture9* d3d9ResolveTexture;
    IDirect3DTexture9* d3d9CPUResolveTexture;
	IDirect3DSwapChain9* d3d9swapChain;
    D3DMULTISAMPLE_TYPE d3d9MultiSampleType;
    DWORD d3d9MultiSampleQuality;
    D3DFORMAT d3d9ColorBufferFormat;
    bool needsResolve;
	D3DPOOL	d3dpoolType;
};

inline D3DPOOL RenderTargetD3D9::GetD3D9PoolType()
{
	return d3dpoolType;
}

} // namespace D3D9
//------------------------------------------------------------------------------
#endif