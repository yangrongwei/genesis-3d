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

#ifndef __RenderDeviceGLES_H__
#define __RenderDeviceGLES_H__

#include "../config/RenderDeviceConfig.h"
#include "../base/RenderDisplay.h"
#include "../base/RenderDeviceTypes.h"
#include "../base/RenderDevice.h"
#include "core/refcounted.h"
#include "core/singleton.h"

#include "EGLContext.h"
#include "OpenGLES.h"
#include "PrimitiveGroupObjectGLES.h"
#include "MRTGLES.h"
#include "GPUProgramGLES.h"
#include "GlesWindow.h"

namespace GLES
{
class TextureGLES;

using namespace RenderBase;

class RenderDeviceGLES : public  RenderBase::RenderDevice
{
	__DeclareSubClass(RenderDeviceGLES,RenderDevice);
	__DeclareThreadSingleton(RenderDeviceGLES);

public:

	RenderDeviceGLES();
	virtual ~RenderDeviceGLES();

public:
	virtual bool InitDevice();

	virtual void DetectGraphicCardCaps();
	virtual const GraphicCardCapability& GetGraphicCardCapability();

	virtual float GetHorizontalTexelOffset();
	virtual float GetVerticalTexelOffset();
	virtual float GetMinimumDepthInputValue();
	virtual float GetMaximumDepthInputValue();

	virtual GPtr<PrimitiveGroup> CreatePrimitiveGroup(const VertexBufferData* vbd, const IndexBufferData* ibd);

	virtual void ChangePrimitiveGroup(PrimitiveGroup* group, const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd = NULL);
	virtual void UpdateVertexBuffer(VertexBuffer* vb, const DataStream& data);
	virtual void UpdateIndexBuffer(IndexBuffer* ib, const DataStream& data);

	virtual const GPtr<GPUProgram> CreateRenderGPUProgram(const GPtr<GPUProgram>& srcGPUProgram);
	virtual const GPtr<RenderStateDesc> CreateRenderState(const GPtr<RenderStateDesc>& state);
	virtual const GPtr<Texture> CreateRenderSideTexture( GPtr<Texture> tex);
	virtual void ChangeTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex);
	virtual void UpdateTexture(RenderBase::Texture::UpdateFunction texUpdateFunc,GPtr<Texture> destTex, void* tag);
	virtual void UpdateTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex);

	virtual const GPtr<RenderTarget> CreateRenderTarget(const GPtr<RenderTarget>& rt);
	virtual const GPtr<MultipleRenderTarget> CreateMultipleRenderTarget(const GPtr<MultipleRenderTarget>& mrt);

	virtual void SetBlendState(const DeviceBlendState& state);
	virtual void SetRasterState(const DeviceRasterizerState& state);
	virtual void SetDepthAndStencilState(const DeviceDepthAndStencilState& state);
	virtual void SetTextureSamplerState(const DeviceSamplerState& state);
	virtual void SetTexture(const Texture* tex);
	virtual void SetRenderTarget(RenderTarget* rt);
	virtual void SetMultipleRenderTarget(const MultipleRenderTarget* mrt, bool resume = false);
	virtual void DisableRenderTarget(int index);

	virtual void SetVertexShaderConstantVectorF(const int& reg, float* val, const int& vec4count);
	virtual void SetPixelShaderConstantVectorF(const int& reg, float* val, const int& vec4count);

	virtual void SetVertexShaderConstantFloat(const int& reg, float* val);
	virtual void SetPixelShaderConstantFloat(const int& reg, float* val);

	virtual void SetVertexShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount);
	virtual void SetPixelShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount);

	/// begin complete frame
	virtual bool BeginFrame();
	/// set the current vertex stream source
	virtual void SetStreamSource(IndexT streamIndex, const VertexBuffer* vb, IndexT offsetVertexIndex);
	/// set current vertex layout
	virtual void SetVertexLayout(const VertexLayout* vl);
	/// set current index buffer
	virtual void SetIndexBuffer(const IndexBuffer* ib);
	/// set current primitive group
	virtual void SetPrimitiveGroup(const PrimitiveGroup* pg);
	/// set current GPU program
	virtual void SetGPUProgram(const GPUProgram* program);
	/// draw current primitives
	virtual void Draw(SizeT startVertice,SizeT numVertice,SizeT startIndice,SizeT numIndice);
	/// draw indexed, instanced primitives
	virtual void DrawIndexedInstanced(SizeT numInstances);
	/// end current frame
	virtual void EndFrame();
	/// present the rendered scene
	virtual void Present(WindHandle hwnd = 0);
	/// set viewport
	virtual void SetViewPort(const int& x,const int& y,const int& width,const int& height,const float& minZ,const float& maxZ);

	//////////////////////////////////////////////////////////////////////////
	//Fixed Pipeline Functions
	virtual void FXSetClipPlane(const int& index,const Math::float4& plane);

	virtual bool OnDeviceLost();

	virtual bool CheckReset();

	virtual bool OnDeviceReset();

	GLESWindow* CreateViewPortWnd( void* hWnd );

	void DestroyViewPortWnd( GLESWindow* view );

public:
	void SetMainWindowHandle(void* hWnd);


protected:

	void _UnbindBuffer();

protected:

	GPtr<GLESContext>                    m_activeContext;
	const PrimitiveGroupObjectGLES*     m_primitiveGroupGLES;
	const GPUProgramGLES*				m_pGPUProgramGLES;
	GLESImpl*			                m_glesImpl;

	GLenum                              m_texturesTypes[GLES::MaxTextureUnits];

	Util::Dictionary<IndexT,  TextureGLES* >  m_Textures;

	GraphicCardCapability m_graphicCardCaps;
    int                                 m_mainFBOnum;
};


inline void RenderDeviceGLES::SetMainWindowHandle(void* hWnd)
{
	if (m_activeContext.isvalid())
	{
		m_activeContext->SetWindow(hWnd);
	}
}

}

#endif