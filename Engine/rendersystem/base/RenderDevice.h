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
#ifndef RENDERDEVICE_H_
#define RENDERDEVICE_H_
#include "../config/RenderDeviceConfig.h"
#include "foundation/delegates/delegatetype.h"
#include "../base/RenderDisplay.h"
#include "../base/BufferData.h"
#include "../base/RenderDeviceTypes.h"
#include "../base/GraphicCardCapability.h"
#include "core/types.h"
#include "VertexBuffer.h"
#include "VertexLayout.h"
#include "IndexBuffer.h"
#include "PrimitiveGroup.h"
#include "RenderTarget.h"
#include "MultipleRenderTarget.h"
#include "GPUProgram.h"
#include "Texture.h"
#include "core/refcounted.h"
#include "RenderStateDesc.h"

#ifdef __ANDROID__

#ifdef _DEBUG

#include <typeinfo>

#endif 

#endif 

namespace RenderBase
{
typedef void (*deviceLostCallBackFunc)();

class RenderDevice : public Core::RefCounted
{
	__DeclareAbstractClass(RenderDevice)
public:
	
	RenderDevice();
	virtual ~RenderDevice();

	virtual bool InitDevice() = 0;

	/** From Ogre: Returns the horizontal texel offset value required for mapping 
	texel origins to pixel origins in this rendersystem.
	@remarks
	Since rendersystems sometimes disagree on the origin of a texel, 
	mapping from texels to pixels can sometimes be problematic to 
	implement generically. This method allows you to retrieve the offset
	required to map the origin of a texel to the origin of a pixel in
	the horizontal direction.
	*/
	virtual float GetHorizontalTexelOffset() = 0;
	/** From Ogre: Returns the vertical texel offset value required for mapping 
	texel origins to pixel origins in this rendersystem.
	@remarks
	Since rendersystems sometimes disagree on the origin of a texel, 
	mapping from texels to pixels can sometimes be problematic to 
	implement generically. This method allows you to retrieve the offset
	required to map the origin of a texel to the origin of a pixel in
	the vertical direction.
	*/
	virtual float GetVerticalTexelOffset() = 0;

	/** From Ogre: Gets the minimum (closest) depth value to be used when rendering
	using identity transforms.
	@remarks
	When using identity transforms you can manually set the depth
	of a vertex; however the input values required differ per
	rendersystem. This method lets you retrieve the correct value.
	@see Renderable::getUseIdentityView, Renderable::getUseIdentityProjection
	*/
	virtual float GetMinimumDepthInputValue() = 0;
	/** From Ogre:  Gets the maximum (farthest) depth value to be used when rendering
	using identity transforms.
	@remarks
	When using identity transforms you can manually set the depth
	of a vertex; however the input values required differ per
	rendersystem. This method lets you retrieve the correct value.
	@see Renderable::getUseIdentityView, Renderable::getUseIdentityProjection
	*/
	virtual float GetMaximumDepthInputValue() = 0;

	SizeT GetNumTriangles();

	SizeT GetNumVertexs();

	SizeT GetNumDrawCalls();

	SizeT GetNumRenderTargets();

	// 测试当前硬件的性能，需要在设备初始化之后立刻调用
	virtual void DetectGraphicCardCaps() = 0;

	// 获取当前硬件的性能参数
	virtual const GraphicCardCapability& GetGraphicCardCapability() = 0;


	/// Create true primitive group
	virtual GPtr<PrimitiveGroup> CreatePrimitiveGroup(const VertexBufferData* vbd, const IndexBufferData* ibd) = 0;
	virtual void ChangePrimitiveGroup(PrimitiveGroup* group, const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd = NULL) = 0;
	virtual void UpdateVertexBuffer(VertexBuffer* vb, const DataStream& data) = 0;
	virtual void UpdateIndexBuffer(IndexBuffer* ib, const DataStream& data) = 0;

	virtual void ChangeTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex) = 0;
	virtual void UpdateTexture(RenderBase::Texture::UpdateFunction texUpdateFunc,GPtr<Texture> destTex, void* tag) = 0;
	virtual void UpdateTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex) = 0;
	virtual const GPtr<GPUProgram> CreateRenderGPUProgram(const GPtr<GPUProgram>& srcGPUProgram) = 0;
	virtual const GPtr<RenderStateDesc> CreateRenderState(const GPtr<RenderStateDesc>& state) = 0;
	virtual const GPtr<Texture> CreateRenderSideTexture( GPtr<Texture> tex) = 0;
	virtual const GPtr<RenderTarget> CreateRenderTarget(const GPtr<RenderTarget>& rt) = 0;
	virtual const GPtr<MultipleRenderTarget> CreateMultipleRenderTarget(const GPtr<MultipleRenderTarget>& mrt) = 0;

	virtual void SetBlendState(const DeviceBlendState& state) = 0;
	virtual void SetRasterState(const DeviceRasterizerState& state) = 0;
	virtual void SetDepthAndStencilState(const DeviceDepthAndStencilState& state) = 0;
	virtual void SetTextureSamplerState(const DeviceSamplerState& state) = 0;
	virtual void SetTexture(const Texture* tex) = 0;
	virtual void SetRenderTarget(RenderTarget* rt) = 0;
	virtual void SetMultipleRenderTarget(const MultipleRenderTarget* mrt, bool resume = false) = 0;
	virtual void DisableRenderTarget(int index) = 0;


	virtual void SetVertexShaderConstantVectorF(const int& reg, float* val, const int& vec4count) = 0;
	virtual void SetPixelShaderConstantVectorF(const int& reg, float* val, const int& vec4count) = 0;

	virtual void SetVertexShaderConstantFloat(const int& reg, float* val) = 0;
	virtual void SetPixelShaderConstantFloat(const int& reg, float* val) = 0;

	virtual void SetVertexShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount) = 0;
	virtual void SetPixelShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount) = 0;

	/// begin complete frame
	virtual bool BeginFrame() = 0;
	/// set the current vertex stream source
	virtual void SetStreamSource(IndexT streamIndex, const VertexBuffer* vb, IndexT offsetVertexIndex);
	/// set the current vertex stream source Frequency 
	//virtual void SetStreamSourceFreq(IndexT streamIndex, IndexT setting);
	/// set current vertex layout
	virtual void SetVertexLayout(const VertexLayout* vl) = 0;
	/// set current index buffer
	virtual void SetIndexBuffer(const IndexBuffer* ib) = 0;
	/// set current primitive group
	virtual void SetPrimitiveGroup(const PrimitiveGroup* pg) = 0;
	/// set current GPU program
	virtual void SetGPUProgram(const GPUProgram* program) = 0;
	/// draw current primitives
	virtual void Draw(SizeT startVertice,SizeT endVertice,SizeT startIndice,SizeT endIndice) = 0;
	/// draw indexed, instanced primitives
	virtual void DrawIndexedInstanced(SizeT numInstances);
	/// end current frame
	virtual void EndFrame() = 0;
	/// present the rendered scene
	virtual void Present(WindHandle hwnd ) = 0;
	/// set viewport
	virtual void SetViewPort(const int& x,const int& y,const int& width,const int& height,const float& minZ,const float& maxZ) = 0;
	
	//////////////////////////////////////////////////////////////////////////
	//Fixed Pipeline Functions
	virtual void FXSetClipPlane(const int& index,const Math::float4& plane) = 0;

	virtual bool OnDeviceLost() = 0;

	virtual bool CheckReset() = 0;

	virtual bool OnDeviceReset() = 0;

	//////////////////////////////////////////////////////////////////////////
	//Set DrawWireFrame
	void SetDrawWireFrame(bool wireFrame = false);

	void SetSize(int width, int height);

	int GetWidth() const;
	int GetHeight() const;

	bool IsDeviceLost();
	void SetDeviceLost();

	void SetDeviceLostCallBack(deviceLostCallBackFunc func);

	template<typename From, typename To>
	static To* _Convert(From* value);

	template<typename From, typename To>
	static const To* _Convert(const From* value);
	protected:

	const VertexBuffer* streamVertexBuffers[MaxNumVertexStreams];
	IndexT streamVertexOffsets[MaxNumVertexStreams];
	bool m_bDrawWireFrame;
	int m_width;
	int m_height;
	bool m_bDeviceLost;
	deviceLostCallBackFunc m_deviceCallBack;
};

	inline void RenderDevice::SetSize(int width, int height)
	{
		this->m_width = width;
		this->m_height = height;
	}

	inline int RenderDevice::GetWidth() const
	{
		return m_width;
	}

	inline int RenderDevice::GetHeight() const
	{
		return m_height;
	}

	inline
		void RenderDevice::SetDrawWireFrame(bool wireFrame)
	{
		m_bDrawWireFrame = wireFrame;
	}

	inline bool RenderDevice::IsDeviceLost()
	{
		return m_bDeviceLost;
	}

	inline void RenderDevice::SetDeviceLost()
	{
		m_bDeviceLost = true;
	}

	inline void RenderDevice::SetDeviceLostCallBack(deviceLostCallBackFunc func)
	{
		m_deviceCallBack = func;
	}

	template<typename From, typename To>
	inline 
		To* RenderDevice::_Convert(From* value)
	{
#ifdef _DEBUG
			To* temp = dynamic_cast<To*>(value);
			if (NULL == temp)
			{
				n_error("Type Error: the value is not %s", typeid(To).name());
			}
			return temp;
#else
			return static_cast<To*>(value);
#endif // _DEBUG
	}

	template<typename From, typename To>
	inline 
		const To* RenderDevice::_Convert(const From* value)
	{
#ifdef _DEBUG
		const To* temp = dynamic_cast<const To*>(value);
		if (NULL == temp)
		{
			n_error("Type Error: the value is not %s", typeid(To).name());
		}
		return temp;
#else
		return static_cast<const To*>(value);
#endif // _DEBUG
	}
}
#endif
