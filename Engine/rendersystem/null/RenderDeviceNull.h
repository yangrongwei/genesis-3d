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
#ifndef __RenderDeviceNull_H__
#define __RenderDeviceNull_H__

#include "../config/RenderDeviceConfig.h"
#include "../base/RenderDisplay.h"
#include "../base/RenderDeviceTypes.h"
#include "../base/RenderDevice.h"
#include "core/types.h"
#include "core/refcounted.h"
#include "core/singleton.h"
#include "../base/RenderWindow.h"

namespace NullDevice
{
	using namespace RenderBase;

	class RenderDeviceNull : public RenderDevice
	{
		__DeclareSubClass(RenderDeviceNull,RenderDevice);
		__DeclareThreadSingleton(RenderDeviceNull);
	public:

		RenderDeviceNull();
		virtual ~RenderDeviceNull();

		virtual bool InitDevice() ;

		virtual float GetHorizontalTexelOffset() ;
	
		virtual float GetVerticalTexelOffset() ;

		virtual float GetMinimumDepthInputValue() ;

		virtual float GetMaximumDepthInputValue() ;

		virtual void DetectGraphicCardCaps() ;

		virtual const GraphicCardCapability& GetGraphicCardCapability() ;

		virtual GPtr<PrimitiveGroup> CreatePrimitiveGroup(const VertexBufferData* vbd, const IndexBufferData* ibd)
		{
			return PrimitiveGroup::Create();
		}

		virtual void ChangePrimitiveGroup(PrimitiveGroup* group, const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd = NULL)
		{

		}
		virtual void UpdateVertexBuffer(VertexBuffer* vb, const DataStream& data)
		{

		}
		virtual void UpdateIndexBuffer(IndexBuffer* ib, const DataStream& data)
		{

		}
		virtual void ChangeTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex)
		{

		}
		virtual void UpdateTexture(RenderBase::Texture::UpdateFunction texUpdateFunc,GPtr<Texture> destTex, void* tag);

		virtual void UpdateTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex) ;

		virtual const GPtr<GPUProgram> CreateRenderGPUProgram(const GPtr<GPUProgram>& srcGPUProgram) ;

		virtual const GPtr<RenderStateDesc> CreateRenderState(const GPtr<RenderStateDesc>& state) ;

		virtual const GPtr<Texture> CreateRenderSideTexture( GPtr<Texture> tex) ;

		virtual const GPtr<RenderTarget> CreateRenderTarget(const GPtr<RenderTarget>& rt) ;

		virtual const GPtr<MultipleRenderTarget> CreateMultipleRenderTarget(const GPtr<MultipleRenderTarget>& mrt) ;

		virtual void SetBlendState(const DeviceBlendState& state) ;

		virtual void SetRasterState(const DeviceRasterizerState& state) ;

		virtual void SetDepthAndStencilState(const DeviceDepthAndStencilState& state) ;

		virtual void SetTextureSamplerState(const DeviceSamplerState& state) ;

		virtual void SetTexture(const Texture* tex) ;

		virtual void SetRenderTarget(RenderTarget* rt) ;

		virtual void SetMultipleRenderTarget(const MultipleRenderTarget* mrt, bool resume = false) ;

		virtual void DisableRenderTarget(int index) ;


		virtual void SetVertexShaderConstantVectorF(const int& reg, float* val, const int& vec4count) ;

		virtual void SetPixelShaderConstantVectorF(const int& reg, float* val, const int& vec4count) ;

		virtual void SetVertexShaderConstantFloat(const int& reg, float* val) ;

		virtual void SetPixelShaderConstantFloat(const int& reg, float* val) ;

		virtual void SetVertexShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount) ;

		virtual void SetPixelShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount) ;

		virtual bool BeginFrame() ;

		/// set the current vertex stream source
		virtual void SetStreamSource(IndexT streamIndex, const VertexBuffer* vb, IndexT offsetVertexIndex);

		virtual void SetVertexLayout(const VertexLayout* vl);

		/// set current index buffer
		virtual void SetIndexBuffer(const IndexBuffer* ib) ;

		/// set current primitive group
		virtual void SetPrimitiveGroup(const PrimitiveGroup* pg);

		/// set current GPU program
		virtual void SetGPUProgram(const GPUProgram* program) ;

		/// draw current primitives
		virtual void Draw(SizeT startVertice,SizeT endVertice,SizeT startIndice,SizeT endIndice);

		/// draw indexed, instanced primitives
		virtual void DrawIndexedInstanced(SizeT numInstances);

		/// end current frame
		virtual void EndFrame();

		/// present the rendered scene
		virtual void Present(WindHandle hwnd = 0) ;

		/// set viewport
		virtual void SetViewPort(const int& x,const int& y,const int& width,const int& height,const float& minZ,const float& maxZ);

		virtual void FXSetClipPlane(const int& index,const Math::float4& plane);

		virtual bool OnDeviceLost();
		virtual bool CheckReset()
		{
			return true;
		}
		virtual bool OnDeviceReset()
		{
			return true;
		}
		///
		bool CreateD3DObjectAndHiddenWindow();
		///
		void SetupDisplayParams();

		void SetMainWindowHandle(WindHandle hwnd);

		RenderWindow* CreateViewPortWnd( WindHandle hWnd );

	protected:
		GraphicCardCapability m_graphicCardCaps;

		IDirect3D9*				m_iD3D9;
		IDirect3DDevice9*		m_iDevice9;
		IDirect3DSurface9*		m_iBackBufferSurface9;
		IDirect3DSwapChain9*    m_iCurrentSwapChain;
		WindHandle				m_hMainWindow;
		HWND					m_hHiddenWindow;
		HINSTANCE				m_instD3D9Dll;
		D3DPRESENT_PARAMETERS	m_defaultDisplayPresentParams;
		D3DFORMAT				m_displayFormat;
		D3DDEVTYPE				m_deviceType;
		DWORD					m_deviceBehaviourFlags;
		bool					m_bWindowed;
		bool					m_bDeviceLost;
		bool					m_bNeedReset;
		D3DDISPLAYMODE 			m_lastWindowedMode;

		DWORD					m_adapterCount;
	};

	inline void RenderDeviceNull::SetMainWindowHandle(WindHandle hwnd)
	{
		m_hMainWindow = hwnd;
	}

	class RenderTargetNull: public RenderBase::RenderTarget
	{
		__DeclareSubClass(RenderTargetNull, RenderBase::RenderTarget);
	public:
		RenderTargetNull(){

		}
		virtual ~RenderTargetNull()
		{

		}

		void AssignResolveTextures();
	};

	class NullWindow : public RenderWindow
	{
	public:
		NullWindow( RenderDeviceNull* device, HWND winHandle);
		virtual ~NullWindow();
		virtual void		BeginRender();
		virtual void		EndRender();

	};
}







#endif // __RenderDeviceNull_H__
