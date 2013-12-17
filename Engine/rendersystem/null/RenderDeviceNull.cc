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
#if __WIN32__
#include "stdneb.h"
#include "d3d9/D3D9Types.h"
#include "d3d9/RenderTargetD3D9.h"
#include "null/RenderDeviceNull.h"

namespace NullDevice
{
	using namespace RenderBase;

	using namespace D3D9;

	typedef IDirect3D9* (WINAPI* Direct3DCreate9Func)(UINT);

	__ImplementClass(RenderTargetNull, 'RDTN', RenderTarget);

	__ImplementClass(RenderDeviceNull, 'RDVN', RenderDevice);
	__ImplementThreadSingleton(RenderDeviceNull);

	NullWindow::NullWindow( RenderDeviceNull*  device, HWND winHandle)
		: RenderWindow( winHandle )
	{
	}


	NullWindow::~NullWindow()
	{	
	}

	void NullWindow::BeginRender()
	{
	}

	void NullWindow::EndRender()
	{
	}

	//------------------------------------------------------------------------------
	void RenderTargetNull::AssignResolveTextures()
	{
		if (this->isDefaultRenderTarget)
		{
			return;
		}

		this->resolveTexture = Texture::Create();
		n_assert(this->resolveTexture.isvalid());
		this->resolveTexture->Setup();
	}
	//------------------------------------------------------------------------
	RenderDeviceNull::RenderDeviceNull():
	m_iD3D9( NULL ),
		m_iDevice9( NULL ),
		m_iBackBufferSurface9( NULL ),
		m_iCurrentSwapChain( NULL ),
		m_hMainWindow( NULL ),
		m_hHiddenWindow( NULL ),
		m_instD3D9Dll( NULL ),
		m_bWindowed( true ),
		m_bDeviceLost( false ),
		m_bNeedReset( false ),
		m_adapterCount( D3DADAPTER_DEFAULT ),
		m_displayFormat( D3DFMT_X8R8G8B8 ),
		m_deviceType(D3DDEVTYPE_HAL)
	{
		__ConstructThreadSingleton;

		m_defaultDisplayPresentParams.BackBufferCount = 1;
		m_defaultDisplayPresentParams.Windowed = m_bWindowed;
		m_defaultDisplayPresentParams.BackBufferFormat = m_displayFormat;
		m_defaultDisplayPresentParams.BackBufferWidth = 1024;
		m_defaultDisplayPresentParams.BackBufferHeight = 768;
		m_defaultDisplayPresentParams.EnableAutoDepthStencil = FALSE;
		m_defaultDisplayPresentParams.AutoDepthStencilFormat = D3DFMT_D24S8;
		m_defaultDisplayPresentParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		m_defaultDisplayPresentParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
		m_defaultDisplayPresentParams.hDeviceWindow = (HWND)m_hMainWindow;
		m_defaultDisplayPresentParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
		m_defaultDisplayPresentParams.MultiSampleType = D3DMULTISAMPLE_NONE;
		m_defaultDisplayPresentParams.MultiSampleQuality = 0;
		m_defaultDisplayPresentParams.Flags = 0;

		m_deviceBehaviourFlags = D3DCREATE_FPU_PRESERVE | D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	//------------------------------------------------------------------------
	RenderDeviceNull::~RenderDeviceNull()
	{
		__DestructThreadSingleton;
	}
	//------------------------------------------------------------------------
	bool RenderDeviceNull::CreateD3DObjectAndHiddenWindow()
	{

		m_instD3D9Dll = LoadLibrary( "d3d9.dll" );

		if (!m_instD3D9Dll)
		{
			n_error("RenderDeviceD3D9::CreateD3DObjectAndHiddenWindow: No D3D9Runtime Installed\n");
			m_instD3D9Dll = NULL;
			return false;
		}

		Direct3DCreate9Func d3dcreateFunc = (Direct3DCreate9Func)GetProcAddress( m_instD3D9Dll, "Direct3DCreate9");

		if( !d3dcreateFunc )
		{
			n_error( "RenderDeviceD3D9::CreateD3DObjectAndHiddenWindow: Direct3DCreate9 Not Found\n" );
			FreeLibrary( m_instD3D9Dll );
			m_instD3D9Dll = NULL;
			return false;
		}

		m_iD3D9 = d3dcreateFunc( D3D_SDK_VERSION );
		if ( !m_iD3D9 )
		{
			n_error("RenderDeviceD3D9::CreateD3DObjectAndHiddenWindow: D3D9 Version Is Not Correct");
			m_iD3D9 = NULL;
			return false;
		}

		//Create Hidden Window
		m_hHiddenWindow = CreateWindowW(
			L"STATIC",
			L"GenesisHiddenWindow",
			WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS |	WS_CLIPCHILDREN,
			0, 0, 1, 1,
			NULL, NULL,
			GetModuleHandle(0), NULL );
		if( !m_hHiddenWindow )
		{
			n_error("RenderDeviceD3D9::CreateD3DObjectAndHiddenWindow: Create Hidden Window Failed!");
			return false;
		}

		return true;

	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetupDisplayParams()
	{
		// backbuffer 的格式和大小由上层控制
		m_defaultDisplayPresentParams.hDeviceWindow = m_hHiddenWindow;
		m_defaultDisplayPresentParams.BackBufferFormat = D3D9::D3D9Types::AsD3D9PixelFormat(RenderBase::PixelFormat::X8R8G8B8);
		m_defaultDisplayPresentParams.BackBufferHeight = 800;
		m_defaultDisplayPresentParams.BackBufferWidth = 600;
	}
	//----------------------------------------------------------------------
	bool RenderDeviceNull::InitDevice()
	{
		if(!CreateD3DObjectAndHiddenWindow())
			return false;

		SetupDisplayParams();

		HRESULT hr = m_iD3D9->CreateDevice(m_adapterCount,
			D3DDEVTYPE_HAL,
			m_hHiddenWindow,
			m_deviceBehaviourFlags,
			&m_defaultDisplayPresentParams,
			&m_iDevice9
			);

		if (FAILED(hr))
		{
			n_error("Failed to create Direct3D device object: %s!\n", DXGetErrorString9(hr));
			return false;
		}
		return true;
	}
	//------------------------------------------------------------------------
	float RenderDeviceNull::GetHorizontalTexelOffset()
	{
		return -0.5f;
	}
	//------------------------------------------------------------------------
	float RenderDeviceNull::GetVerticalTexelOffset()
	{
		return -0.5f;
	}
	//------------------------------------------------------------------------
	float RenderDeviceNull::GetMinimumDepthInputValue()
	{
		return 0.0f;
	}
	//------------------------------------------------------------------------
	float RenderDeviceNull::GetMaximumDepthInputValue()
	{
		return -1.0f;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::DetectGraphicCardCaps()
	{
		//m_graphicCardCaps.DetectGraphicCardCapsD3D9();
	}
	//------------------------------------------------------------------------
	const GraphicCardCapability& RenderDeviceNull::GetGraphicCardCapability()
	{
		return m_graphicCardCaps;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::UpdateTexture(RenderBase::Texture::UpdateFunction texUpdateFunc,GPtr<Texture> destTex, void* tag)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::UpdateTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex)
	{
		return;
	}
	//------------------------------------------------------------------------
	const GPtr<GPUProgram> RenderDeviceNull::CreateRenderGPUProgram(const GPtr<GPUProgram>& srcGPUProgram)
	{
		return GPUProgram::Create();
	}
	//------------------------------------------------------------------------
	const GPtr<RenderStateDesc> RenderDeviceNull::CreateRenderState(const GPtr<RenderStateDesc>& state)
	{
		return RenderStateDesc::Create();
	}
	//------------------------------------------------------------------------
	const GPtr<Texture> RenderDeviceNull::CreateRenderSideTexture( GPtr<Texture> tex)
	{
		return Texture::Create();
	}
	//------------------------------------------------------------------------
	const GPtr<RenderTarget> RenderDeviceNull::CreateRenderTarget(const GPtr<RenderTarget>& rt)
	{
		GPtr<RenderTargetNull> rtD9 = RenderTargetNull::Create();
		rtD9->AssignResolveTextures();
		return rtD9.upcast<RenderTarget>();
	}
	//------------------------------------------------------------------------
	const GPtr<MultipleRenderTarget> RenderDeviceNull::CreateMultipleRenderTarget(const GPtr<MultipleRenderTarget>& mrt)
	{
		return MultipleRenderTarget::Create();
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetBlendState(const DeviceBlendState& state)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetRasterState(const DeviceRasterizerState& state)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetDepthAndStencilState(const DeviceDepthAndStencilState& state)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetTextureSamplerState(const DeviceSamplerState& state)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetTexture(const Texture* tex)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetRenderTarget(RenderTarget* rt)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetMultipleRenderTarget(const MultipleRenderTarget* mrt, bool resume )
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::DisableRenderTarget(int index)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetVertexShaderConstantVectorF(const int& reg, float* val, const int& vec4count)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetPixelShaderConstantVectorF(const int& reg, float* val, const int& vec4count)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetVertexShaderConstantFloat(const int& reg, float* val)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetPixelShaderConstantFloat(const int& reg, float* val)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetVertexShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetPixelShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount)
	{
		return;
	}
	//------------------------------------------------------------------------
	bool RenderDeviceNull::BeginFrame()
	{
		HRESULT hr;
		if (m_bDeviceLost)
		{
			SetupDisplayParams();
			Sleep(100);
			bool bRealDeviceLost = false;
			while ( FAILED(hr = m_iDevice9->TestCooperativeLevel()))
			{
				if (hr == D3DERR_DEVICELOST)
				{
					bRealDeviceLost = true;
					Sleep(100);
					continue;
				}

				if (hr == D3DERR_DEVICENOTRESET)
				{
					bRealDeviceLost = true;
					//if(!_OnDeviceLost())
					{
						continue;
					}
				}

			}
			if (false == bRealDeviceLost)
			{
				//_OnDeviceLost();
			}
			m_bDeviceLost = false;
		}
		this->m_iDevice9->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0f, 0 );
		hr = this->m_iDevice9->BeginScene();
		n_assert(SUCCEEDED(hr));
		return true;
	}
	//------------------------------------------------------------------------
	/// set the current vertex stream source
	void RenderDeviceNull::SetStreamSource(IndexT streamIndex, const VertexBuffer* vb, IndexT offsetVertexIndex)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetVertexLayout(const VertexLayout* vl)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetIndexBuffer(const IndexBuffer* ib)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetPrimitiveGroup(const PrimitiveGroup* pg)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::SetGPUProgram(const GPUProgram* program)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::Draw(SizeT startVertice,SizeT endVertice,SizeT startIndice,SizeT endIndice)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::DrawIndexedInstanced(SizeT numInstances)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::EndFrame()
	{
		HRESULT hr = this->m_iDevice9->EndScene();
		n_assert(SUCCEEDED(hr));

		for (SizeT i = 0; i < 8; ++i)
		{
			hr = m_iDevice9->SetTexture(i,NULL);
			n_assert(SUCCEEDED(hr))
		}

		for (DWORD i = D3DVERTEXTEXTURESAMPLER0; i <= D3DVERTEXTEXTURESAMPLER3; ++i)
		{
			hr = m_iDevice9->SetTexture(i,NULL);
			n_assert(SUCCEEDED(hr))
		}

	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::Present(WindHandle hwnd ) 
	{
		if (!hwnd)		
			hwnd = m_hMainWindow;

		m_iDevice9->Present(NULL,NULL,(HWND)hwnd,NULL);
	}
	//------------------------------------------------------------------------
	/// set viewport
	void RenderDeviceNull::SetViewPort(const int& x,const int& y,const int& width,const int& height,const float& minZ,const float& maxZ)
	{
		return;
	}
	//------------------------------------------------------------------------
	void RenderDeviceNull::FXSetClipPlane(const int& index,const Math::float4& plane)
	{
		return;
	}

	RenderWindow* RenderDeviceNull::CreateViewPortWnd( WindHandle hWnd )
	{
		return new NullWindow( this, (HWND)hWnd );
	}

	bool RenderDeviceNull::OnDeviceLost()
	{
		return true;
	}
}

#endif