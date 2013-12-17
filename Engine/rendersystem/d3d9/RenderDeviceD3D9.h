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
#ifndef RENDERDEVICED3D9_H_
#define RENDERDEVICED3D9_H_
#include "../config/RenderDeviceConfig.h"
#include "../base/RenderDisplay.h"
#include "../base/RenderDeviceTypes.h"
#include "../base/RenderDevice.h"
#include "core/types.h"
#include "RenderTargetD3D9.h"
#include "MRTD3D9.h"
#include "GPUProgramD3D9.h"
#include "TextureD3D9.h"
#include "core/refcounted.h"
#include "core/singleton.h"
#include "D3D9Window.h"
typedef IDirect3D9* (WINAPI* Direct3DCreate9Func)(UINT);

namespace D3D9
{
	using namespace RenderBase;
	class PrimitiveGroupD3D9;

#define MAX_TEXTURE_COUNT 8
#define MAX_DEVICE_STATE_COUNT 300//在d3d9中 D3DRENDERSTATETYPE 的最大有效值为D3DRS_BLENDOPALPHA                 = 209,


	class RenderDeviceD3D9 : public RenderDevice
	{
		__DeclareSubClass(RenderDeviceD3D9,RenderDevice);
		__DeclareThreadSingleton(RenderDeviceD3D9);
	public:

		RenderDeviceD3D9();
		virtual ~RenderDeviceD3D9();

		virtual bool InitDevice();

		virtual void DetectGraphicCardCaps();
		virtual const GraphicCardCapability& GetGraphicCardCapability();

		virtual float GetHorizontalTexelOffset();
		virtual float GetVerticalTexelOffset();
		virtual float GetMinimumDepthInputValue();
		virtual float GetMaximumDepthInputValue();

		virtual void SetBlendState(const DeviceBlendState& state);
		virtual void SetRasterState(const DeviceRasterizerState& state);
		virtual void SetDepthAndStencilState(const DeviceDepthAndStencilState& state);
		virtual void SetTextureSamplerState(const DeviceSamplerState& state);

		// encrypt d3d9 APIs
		HRESULT Clear( DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color,float Z, DWORD Stencil );

		HRESULT CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle);
		HRESULT CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle);
		HRESULT CreateVertexDeclaration(D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl);
		HRESULT CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle);
		HRESULT CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppTexture,HANDLE* pSharedHandle);
		//--tex3d
		HRESULT CreateVolumeTexture(UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle);

		HRESULT CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
		HRESULT CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle);
		HRESULT CreateVertexShader(CONST DWORD * pFunction,IDirect3DVertexShader9** ppShader);
		HRESULT CreatePixelShader(CONST DWORD * pFunction,IDirect3DPixelShader9** ppShader);
		
		HRESULT SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value);
		HRESULT SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9 *pRenderTarget);
		HRESULT SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil);
		HRESULT StretchRect( IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter);

		HMONITOR GetAdapterMonitor( UINT Adapter );
		HRESULT CheckDeviceFormat( UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat );
		HRESULT GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9 * pCaps);
		HRESULT GetAdapterIdentifier( UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 * pIdentifier );

		HRESULT CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels);
		HRESULT GetBackBuffer( UINT iSwapChain, UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer);
		HRESULT GetRenderTargetData( IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface);
		HRESULT CreateAdditionalSwapChain( D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain9 **ppSwapChain );


		HRESULT D3DXCreateTextureFromFileInMemory( LPCVOID pSrcData, UINT SrcDataSize, LPDIRECT3DTEXTURE9* ppTexture);
		HRESULT D3DXCreateVolumeTextureFromFileInMemory( LPCVOID pSrcData, UINT SrcDataSize, LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture);
		HRESULT D3DXCreateCubeTextureFromFileInMemory( LPCVOID pSrcData, UINT SrcDataSize, LPDIRECT3DCUBETEXTURE9* ppCubeTexture);
		

		
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
		/// draw current primitive
		virtual void Draw(SizeT startVertice,SizeT numVertice,SizeT startIndice,SizeT numIndice);
		/// draw indexed, instanced primitives
		virtual void DrawIndexedInstanced(SizeT numInstances);
		/// end current frame
		virtual void EndFrame();
		/// check if inside BeginFrame
		virtual void Present(WindHandle hwnd );



		// Fixed Pipeline Functions
		void FXSetClipPlane(const int& index,const Math::float4& plane);
		/// set current render target
		void SetRenderTarget(RenderTarget* rt);
		///
		void SetMultipleRenderTarget(const MultipleRenderTarget*  mrt, bool resume = false);

		void DisableRenderTarget(int index);
		/// set texture
		void SetTexture(const Texture* tex);

		/// set the current vertex stream source frequency 
		void SetStreamSourceFreq(IndexT streamIndex, unsigned long setting);

		virtual void SetVertexShaderConstantVectorF(const int& reg, float* val, const int& vec4count);
		virtual void SetPixelShaderConstantVectorF(const int& reg, float* val, const int& vec4count);

		virtual void SetVertexShaderConstantFloat(const int& reg, float* val);
		virtual void SetPixelShaderConstantFloat(const int& reg, float* val);

		virtual void SetVertexShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount);
		virtual void SetPixelShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount);

		/// create Render side Primitive Group
		virtual GPtr<PrimitiveGroup> CreatePrimitiveGroup(const VertexBufferData* vbd, const IndexBufferData* ibd);
		virtual void ChangePrimitiveGroup(PrimitiveGroup* group, const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd = NULL);
		virtual void UpdateVertexBuffer(VertexBuffer* vb, const DataStream& data);
		virtual void UpdateIndexBuffer(IndexBuffer* ib, const DataStream& data);

		virtual void ChangeTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex);
		/// update render side Texture
		virtual void UpdateTexture(RenderBase::Texture::UpdateFunction texUpdateFunc,GPtr<Texture> destTex, void* tag);
		/// update render side Texutre by texture data
		virtual void UpdateTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex);

		/// create render side GPU program
		const GPtr<GPUProgram> CreateRenderGPUProgram(const GPtr<GPUProgram>& srcGPUProgram);
		/// create render side RenderState
		const GPtr<RenderStateDesc> CreateRenderState(const GPtr<RenderStateDesc>& state);
		/// create render side Texture
		const GPtr<Texture> CreateRenderSideTexture(GPtr<Texture> tex);

		/// create render side RenderTarget
		const GPtr<RenderTarget> CreateRenderTarget(const GPtr<RenderTarget>& tex);
		/// create render side MultipleRenderTarget
		const GPtr<MultipleRenderTarget> CreateMultipleRenderTarget(const GPtr<MultipleRenderTarget>& mrt);

		virtual bool OnDeviceLost();

		virtual bool CheckReset();

		virtual bool OnDeviceReset();

		/// set viewport
		void SetViewPort(const int& x,const int& y,const int& width,const int& height,const float& minZ,const float& maxZ);


		///
		bool CreateD3DObjectAndHiddenWindow();
		///
		void SetupDefaultDisplayParams();

		void SetMainWindowHandle(WindHandle hwnd);

		IDirect3DDevice9* GetD3D9Device();

		DWORD GetAdapter();

		D3DDEVTYPE GetDeviceType();

		
		
		D3D9Window* CreateViewPortWnd( WindHandle hWnd );

		void DestroyViewPortWnd( D3D9Window* view );

		D3DPRESENT_PARAMETERS GetDefaultPresentParamters(); 

	private:
		IDirect3D9*				m_iD3D9;
		IDirect3DDevice9*		m_iDevice9;
		IDirect3DSurface9*		m_iBackBufferSurface9;
		IDirect3DSwapChain9*    m_iCurrentSwapChain;
		WindHandle				m_hMainWindow;
		WindHandle				m_hHiddenWindow;
		HINSTANCE				m_instD3D9Dll;
		D3DPRESENT_PARAMETERS	m_defaultDisplayPresentParams;
		D3DFORMAT				m_displayFormat;
		D3DDEVTYPE				m_deviceType;
		DWORD					m_deviceBehaviourFlags;
		bool					m_bWindowed;
		bool					m_bNeedReset;
		bool					m_bGPUDebugging;
		D3DDISPLAYMODE 			m_lastWindowedMode;

		DWORD					m_adapterCount;
		DWORD					m_adapterD3D9;

		const PrimitiveGroupD3D9*		m_primitiveGroupD9;
		const GPUProgramD3D9*			m_pGPUProgramD9;
		Util::Array<RenderTargetD3D9*> m_pRenderTargets;

		
		//GPUInfo::GraphicCardInfo mGraphicCardObj;
		//GpuInfo	mGpuInfo;

		GraphicCardCapability m_graphicCardCaps;

		/// 在CPU端cache一些D3D的状态设置，减少状态切换
	protected:
		struct D3D9RenderStateCache
		{
			const GPUProgramD3D9* programCache;
			const PrimitiveGroupD3D9* primitiveCache;
			const TextureD3D9*  textureCache[MAX_TEXTURE_COUNT];
			DWORD deviceStates[MAX_DEVICE_STATE_COUNT];
			D3D9RenderStateCache();
			void ClearCache();
		};

		void SetRenderState( D3DRENDERSTATETYPE State, DWORD Value);
		void ClearCache();
		D3D9RenderStateCache m_stateCache;
	};

	inline void RenderDeviceD3D9::SetMainWindowHandle(WindHandle hwnd)
	{
		m_hMainWindow = (HWND)hwnd;
	}

	inline DWORD RenderDeviceD3D9::GetAdapter()
	{
		return m_adapterD3D9;
	}

	inline D3DDEVTYPE RenderDeviceD3D9::GetDeviceType()
	{
		return m_deviceType;
	}

	inline IDirect3DDevice9* RenderDeviceD3D9::GetD3D9Device()
	{
		return m_iDevice9;
	}

	inline void RenderDeviceD3D9::SetRenderState(D3DRENDERSTATETYPE state, DWORD value)
	{
		if (m_stateCache.deviceStates[state] != value)
		{
			m_stateCache.deviceStates[state] = value;
			m_iDevice9->SetRenderState( state, value );
		}

	}

	inline D3DPRESENT_PARAMETERS RenderDeviceD3D9::GetDefaultPresentParamters()
	{
		return m_defaultDisplayPresentParams;
	}
}
#endif //RENDERDEVICED3D9_H_