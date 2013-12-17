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
#ifndef RENDERSYSTEM_H_
#define RENDERSYSTEM_H_
#include "core/debug.h"
#include "core/refcounted.h"
#include "base/RenderDeviceTypes.h"
#include "base/PrimitiveGroup.h"
#include "base/RenderTarget.h"
#include "base/MultipleRenderTarget.h"
#include "base/RenderDevice.h"
#include "base/Texture.h"
#include "core/singleton.h"
#include "interface/interfacebase.h"
#include "util/guid.h"
#include "util/queue.h"
#include "util/stl.h"
#include "RenderSystemThreadHandler.h"
#include "base/GraphicCardCapability.h"
#include "base/RenderWindow.h"

namespace RenderBase
{
	class RenderSystem : public Core::RefCounted
	{
		__DeclareSubClass(RenderSystem,Core::RefCounted);
		__DeclareThreadSingleton(RenderSystem);
	public:
		/// constructor
		RenderSystem();
		/// destructor
		virtual ~RenderSystem();

		void ChangeSize(int width, int height);

		/// open the interface object
		virtual void Open(int width, int height);
		/// close the interface object
		virtual void Close();

		void SetDeviceLostCallBack(deviceLostCallBackFunc func);

		float GetHorizontalTexelOffset();
		float GetVerticalTexelOffset();
		float GetMinimumDepthInputValue();
		float GetMaximumDepthInputValue();

		void SetBlendState(const DeviceBlendState* state, float alphaRef);
		void SetRasterState(const DeviceRasterizerState* state);
		void SetDepthState(const DeviceDepthAndStencilState* state);
		void SetSamplerState(const DeviceSamplerState* state, int stencilRef);

		void SetVertexShaderConstantVectorF(const int& reg, float* val, const int& vec4count);
		void SetPixelShaderConstantVectorF(const int& reg, float* val, const int& vec4count);

		void SetVertexShaderConstantFloat(const int& reg, float* val);
		void SetPixelShaderConstantFloat(const int& reg, float* val);

		void SetVertexShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount);
		void SetPixelShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount);

		void BeginFrame();
		void EndFrame();
		
		void Clear();

		GPUProgramHandle CreateShaderProgram(const GPtr<GPUProgram>& program);
		void _SetShaderProgram(GPUProgramHandle handle);

		PrimitiveGroup* GetPrimitiveGroup(const PrimitiveHandle& handle) const;
		Texture* GetTexture(const TextureHandle& handle) const;


		PrimitiveHandle CreatePrimitiveHandle(const VertexBufferData* vbd, const IndexBufferData* ibd = NULL);
		void ChangePrimitiveHandle(RenderBase::PrimitiveHandle& handle, const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd = NULL);
		void UpdateVertexBuffer(PrimitiveHandle& handle, const DataStream& data);
		void UpdateIndexBuffer(PrimitiveHandle& handle, const DataStream& data);
		
		void _DrawPrimitive(PrimitiveHandle handle,SizeT startVertice,SizeT endVertice,SizeT startIndice,SizeT endIndice);
		void _DrawPrimitive(PrimitiveHandle handle);
		void _DrawPrimitiveHWInstance(PrimitiveHandle handle);
		

		RenderStateDescHandle CreateRenderStateObject( const GPtr<RenderStateDesc>& rsObject);
		void _SetRenderState( GPtr<RenderStateDesc> rsObject);

		RenderTargetHandle CreateRenderTarget( const GPtr<RenderTarget>& rt, TextureHandle& texhandle );
		void _SetRenderTarget(RenderTargetHandle handle,SizeT index,uint clearflag);
		void _SetRenderTargetClearColor(RenderTargetHandle handle,const Math::float4& clearColor);
		void _ReSizeRenderTarget(RenderTargetHandle handle,const int& width,const int& height);
		void CopyRenderTarget(RenderTargetHandle srcHandle, const Math::float4& srcRect, RenderTargetHandle desHandle, const Math::float4& desRect);
		
		MultipleRenderTargetHandle CreateMultipleRenderTarget(const GPtr<MultipleRenderTarget>& mrt, Util::Array< RenderBase::RenderTargetHandle >& handles);
		void _SetMultipleRenderTarget(MultipleRenderTargetHandle handle, bool resume = false);
		void _ReSizeMultipleRenderTarget(MultipleRenderTargetHandle handle,const int& width,const int& height);

		TextureHandle CreateTexture( const GPtr<Texture>& tex);
		void _SetTexture(TextureHandle handle,SizeT index);
		void UpdateTexture(TextureHandle texHandle, RenderBase::Texture::UpdateFunction texUpdateFunc, void* tag);
		void UpdateTexture(TextureHandle texHandle, GPtr<RenderBase::Texture> texture);
		void ChangeTexture(RenderBase::TextureHandle texHandle, GPtr<Texture> texture);

		void _RemoveResouce(const RenderResourceHandle& handle);

		void _SetDisplayMode(const DisplayMode& mode);
		void _SetViewPort(const int& x,const int& y,const int& width,const int& height,const float& minZ,const float& maxZ);

		//fixed pipeline functions
		void _FXSetClipPlane(const int& index,const Math::float4& plane);

		const GraphicCardCapability& GetGraphicCardCapability();

		GPtr<RenderTarget>	GetRenderTarget( RenderTargetHandle ) ;
		bool OutPutRenderTarget( RenderTargetHandle , const Util::String& path ) ;

		void _OnWindowChanged();
		
		RenderWindow* CreateViewPortWnd( WindHandle hWnd );

		void DestroyViewPortWnd( RenderWindow* view );

		void SetWireFrameMode(bool wireframe = false);

		void OnDeviceLost();

		bool CheckReset();

		void OnDeviceReset();

	protected:
		bool _AddRenderHandle( const RenderBase::RenderResourceHandle& handle);
		bool _RemoveRenderHandle( const RenderBase::RenderResourceHandle& handle);
		bool _HasRenderHandle(const RenderBase::RenderResourceHandle& handle);

	private:
		friend class RenderSystemThreadHandler;

		GPtr<RenderDevice> m_renderDevice;
		GPtr<RenderDisplay> m_renderDisplay;
		RenderBase::RenderTargetHandle m_dummyRenderTargetHandle;

		typedef Util::STL_set<RenderResourceHandle> RenderResourceHandleSet;
		RenderResourceHandleSet::type m_renderHandles;

		void _OnDeviceLost();
		void _OnDeviceReset();
	private:
		RenderResourceHandleSet::type& GetRenderResourceHandles();

		WindHandle m_mainHWND;
#ifdef __WIN32__
		
	public:
		void SetMainWindowHandle(WindHandle hwnd);
		WindHandle GetMainWindowHandle(void)const;
#endif
	};

	inline void RenderSystem::ChangeSize(int width, int height)
	{
		m_renderDevice->SetSize(width, height);
	}

	inline const GraphicCardCapability& RenderSystem::GetGraphicCardCapability()
	{
		n_assert(m_renderDevice);
		return m_renderDevice->GetGraphicCardCapability();
	}

#ifdef __WIN32__
	inline void RenderSystem::SetMainWindowHandle(WindHandle hwnd)
	{
		m_mainHWND = hwnd;
	}
	inline WindHandle RenderSystem::GetMainWindowHandle(void)const
	{
		return m_mainHWND;
	}
#endif

	extern RenderSystem* rendersystem;
	inline RenderSystem& GetRenderSystem()
	{
		n_assert( rendersystem );
		return *rendersystem;
	}

	inline RenderSystem::RenderResourceHandleSet::type& RenderSystem::GetRenderResourceHandles()
	{
		return m_renderHandles;
	}

	inline void RenderSystem::SetWireFrameMode(bool wireframe /* = false */)
	{
		m_renderDevice->SetDrawWireFrame(wireframe);
	}

	inline float RenderSystem::GetHorizontalTexelOffset()
	{
		return m_renderDevice->GetHorizontalTexelOffset();
	}
	inline float RenderSystem::GetVerticalTexelOffset()
	{
		return m_renderDevice->GetVerticalTexelOffset();
	}
	inline float RenderSystem::GetMinimumDepthInputValue()
	{
		return m_renderDevice->GetMinimumDepthInputValue();
	}
	inline float RenderSystem::GetMaximumDepthInputValue()
	{
		return m_renderDevice->GetMinimumDepthInputValue();
	}
}

#endif //RENDERSYSTEM_H_
