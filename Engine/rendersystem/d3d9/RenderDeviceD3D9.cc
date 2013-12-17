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

#if WIN32

#include "stdneb.h"
#ifdef __OSX__
#include "../../profilesystem/ProfileSystem.h"
#else
#include "profilesystem/ProfileSystem.h"
#endif
#include "RenderDeviceD3D9.h"
#include "PrimitiveGroupD3D9.h"
#include "D3D9Types.h"
#include "../foundation/util/stl.h"
#include "../foundation/memory/memory.h"

namespace D3D9
{

	static const int MRT_COUNT = 8;

	using namespace RenderBase;


	RenderDeviceD3D9::D3D9RenderStateCache::D3D9RenderStateCache()
	{
		ClearCache();
	}


	void RenderDeviceD3D9::D3D9RenderStateCache::ClearCache()
	{
		programCache = NULL;
		primitiveCache = NULL;
		for ( IndexT i = 0; i < MAX_TEXTURE_COUNT; ++i)
		{
			textureCache[i] = NULL;
		}
		Memory::Fill(deviceStates, MAX_DEVICE_STATE_COUNT * sizeof(DWORD), 0xff);
	}

	__ImplementClass(RenderDeviceD3D9, 'RDVC', RenderDevice);
	__ImplementThreadSingleton(RenderDeviceD3D9);
	//------------------------------------------------------------------------------
	/**
	*/
	RenderDeviceD3D9::RenderDeviceD3D9():
	m_iD3D9( NULL ),
		m_iDevice9( NULL ),
		m_iBackBufferSurface9( NULL ),
		m_iCurrentSwapChain( NULL ),
		m_hMainWindow( NULL ),
		m_hHiddenWindow( NULL ),
		m_instD3D9Dll( NULL ),
		m_bWindowed( true ),
		m_bNeedReset( false ),
		m_bGPUDebugging( false ),
		m_adapterD3D9(D3DADAPTER_DEFAULT),
		m_adapterCount( D3DADAPTER_DEFAULT ),
		m_displayFormat( D3DFMT_X8R8G8B8 ),
		m_deviceType(D3DDEVTYPE_HAL)
	{
		__ConstructThreadSingleton;

		m_pRenderTargets.Fill(0,MRT_COUNT,0);

		m_defaultDisplayPresentParams.BackBufferCount = 1;
		m_defaultDisplayPresentParams.Windowed = m_bWindowed;
		m_defaultDisplayPresentParams.BackBufferFormat = m_displayFormat;
		m_defaultDisplayPresentParams.BackBufferWidth = 1;
		m_defaultDisplayPresentParams.BackBufferHeight = 1;
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

	//------------------------------------------------------------------------------
	/**
	*/
	RenderDeviceD3D9::~RenderDeviceD3D9()
	{
		__DestructThreadSingleton;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool RenderDeviceD3D9::InitDevice()
	{
		if(!CreateD3DObjectAndHiddenWindow())
			return false;

		UINT adapterIndex = D3DADAPTER_DEFAULT;
		D3DDEVTYPE devType = D3DDEVTYPE_HAL;
		m_adapterCount = m_iD3D9->GetAdapterCount();


#ifdef __D3D_DEBUG_TOOL__

		D3DADAPTER_IDENTIFIER9 perfHudID;
		memset( &perfHudID, 0, sizeof(perfHudID) );
		m_iD3D9->GetAdapterIdentifier( m_adapterCount-1, 0, &perfHudID );
		perfHudID.Description[MAX_DEVICE_IDENTIFIER_STRING-1] = 0;
		if( strstr( perfHudID.Description, "PerfHUD" ) != NULL )
		{
			adapterIndex = m_adapterCount-1;
			devType = D3DDEVTYPE_REF;
			//m_bGPUDebugging = true;
		}
		m_bGPUDebugging = true;
#endif

		SetupDefaultDisplayParams();
		
		HRESULT hr = m_iD3D9->CreateDevice(adapterIndex,
			devType,
			m_bGPUDebugging ? (HWND)m_hMainWindow : (HWND)m_hHiddenWindow,
			m_deviceBehaviourFlags,
			&m_defaultDisplayPresentParams,
			&m_iDevice9
			);

		if (FAILED(hr))
		{
			n_error("CreateDevice Failed : %s!\n", DXGetErrorString9(hr));
			return false;
		}
		return true;
	}

	//------------------------------------------------------------------------
	void RenderDeviceD3D9::DetectGraphicCardCaps()
	{
#if RENDERDEVICE_D3D9 
		m_graphicCardCaps.DetectGraphicCardCapsD3D9();
#endif
	}
	//------------------------------------------------------------------------
	const GraphicCardCapability& 
	RenderDeviceD3D9::GetGraphicCardCapability()
	{
		return m_graphicCardCaps;
	}
	//------------------------------------------------------------------------

	float RenderDeviceD3D9::GetHorizontalTexelOffset()
	{
		// D3D considers the origin to be in the center of a pixel
		return -0.5f;
	}

	float RenderDeviceD3D9::GetVerticalTexelOffset()
	{
		// D3D considers the origin to be in the center of a pixel
		return -0.5f;
	}

	float RenderDeviceD3D9::GetMinimumDepthInputValue()
	{
		// Range [0.0f, 1.0f]
		return 0.0f;
	}

	float RenderDeviceD3D9::GetMaximumDepthInputValue()
	{
		// Range [0.0f, 1.0f]
		// D3D inverts even identity view matrices, so maximum INPUT is -1.0
		return -1.0f;
	}

	void RenderDeviceD3D9::SetupDefaultDisplayParams()
	{

		// backbuffer 的格式和大小由上层控制
		m_defaultDisplayPresentParams.hDeviceWindow = (HWND)m_hHiddenWindow;
		m_defaultDisplayPresentParams.BackBufferFormat = D3D9Types::AsD3D9PixelFormat(RenderBase::PixelFormat::X8R8G8B8);
		if (m_bGPUDebugging)
		{
			m_defaultDisplayPresentParams.BackBufferWidth = m_width;
			m_defaultDisplayPresentParams.BackBufferHeight = m_height;
		}
		

	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool RenderDeviceD3D9::CreateD3DObjectAndHiddenWindow()
	{
		m_instD3D9Dll = LoadLibrary( "d3d9.dll" );

		if (!m_instD3D9Dll)
		{
			n_error("RenderDeviceD3D9::CreateD3DObjectAndHiddenWindow Error: can't find d3d9.dll,please make sure DX9 installed.\n");
			m_instD3D9Dll = NULL;
			return false;
		}

		Direct3DCreate9Func d3dcreateFunc = (Direct3DCreate9Func)GetProcAddress( m_instD3D9Dll, "Direct3DCreate9");

		if( !d3dcreateFunc )
		{
			n_error( "RenderDeviceD3D9::CreateD3DObjectAndHiddenWindow Error: Can't find D3D9 function : Direct3DCreate9.\n" );
			FreeLibrary( m_instD3D9Dll );
			m_instD3D9Dll = NULL;
			return false;
		}

		m_iD3D9 = d3dcreateFunc( D3D_SDK_VERSION );
		if ( !m_iD3D9 )
		{
			n_error("RenderDeviceD3D9::CreateD3DObjectAndHiddenWindow Error: D3D_SDK_VERSION is not correct!");
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
			n_error("RenderDeviceD3D9::CreateD3DObjectAndHiddenWindow Error: Can't Create Hidden Window!");
			return false;
		}

		return true;
	}

	void RenderDeviceD3D9::SetBlendState(const DeviceBlendState& state)
	{
		int i = 0;

		if(state.m_alphaBlendEnable[i])
		{
			SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
			
			SetRenderState(D3DRS_BLENDOP,D3D9Types::AsD3D9BlendOperation(state.m_blendOP[i]));
			SetRenderState(D3DRS_SRCBLEND,D3D9Types::AsD3D9BlendFactor(state.m_srcBlend[i]));
			SetRenderState(D3DRS_DESTBLEND,D3D9Types::AsD3D9BlendFactor(state.m_destBlend[i]));
			
			SetRenderState(D3DRS_BLENDOPALPHA,D3D9Types::AsD3D9BlendOperation(state.m_blendOPAlpha[i]));
			SetRenderState(D3DRS_SRCBLENDALPHA,D3D9Types::AsD3D9BlendFactor(state.m_srcBlendAlpha[i]));
			SetRenderState(D3DRS_DESTBLENDALPHA,D3D9Types::AsD3D9BlendFactor(state.m_destBlendAlpha[i]));
			
			SetRenderState(D3DRS_COLORWRITEENABLE,D3D9Types::AsD3D9ColorMask(state.m_colorWriteMask[i]));
		}
		else
		{
			SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
		}

		if (state.m_separateAlphaBlendEnable)
		{
			SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE,TRUE);
		}
		else
		{
			SetRenderState( D3DRS_SEPARATEALPHABLENDENABLE,FALSE);
		}

		if (state.m_alphaTestEnable)
		{
			SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);
			SetRenderState(D3DRS_ALPHAFUNC,D3D9Types::AsD3D9CompareFunction(state.m_alphaFunc));
			SetRenderState(D3DRS_ALPHAREF,DWORD(state.m_alphaRef));
		}
		else
		{
			SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
		}


	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetRasterState(const DeviceRasterizerState& state)
	{
		if(m_bDrawWireFrame)
			SetRenderState( D3DRS_FILLMODE, D3D9Types::AsD3D9FillMode(eFMWIREFRAME));
		else
			SetRenderState( D3DRS_FILLMODE, D3D9Types::AsD3D9FillMode(state.m_fillMode));
		SetRenderState( D3DRS_CULLMODE, D3D9Types::AsD3D9CullMode(state.m_cullMode));
		SetRenderState( D3DRS_DEPTHBIAS, (DWORD)state.m_depthBias);
		SetRenderState( D3DRS_SLOPESCALEDEPTHBIAS,(DWORD)state.m_slopScaleDepthBias);
		SetRenderState( D3DRS_SCISSORTESTENABLE, state.m_scissorTestEnable ? TRUE : FALSE );
		SetRenderState( D3DRS_MULTISAMPLEANTIALIAS,state.m_multisampleEnable ? TRUE : FALSE);
		SetRenderState(	D3DRS_ANTIALIASEDLINEENABLE,state.m_multisampleEnable ? TRUE : FALSE);


	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetTextureSamplerState(const DeviceSamplerState& state)
	{
		for (SizeT i = 0; i < 8; ++i)
		{
			if (state.m_textureIndexEnable[i])
			{
				m_iDevice9->SetSamplerState(i,D3DSAMP_ADDRESSU,D3D9Types::AsD3D9TextureAddress(state.m_addressU[i]));
				m_iDevice9->SetSamplerState(i,D3DSAMP_ADDRESSV,D3D9Types::AsD3D9TextureAddress(state.m_addressV[i]));
				m_iDevice9->SetSamplerState(i,D3DSAMP_ADDRESSW,D3D9Types::AsD3D9TextureAddress(state.m_addressW[i]));
				HRESULT hr = D3D9Types::AsD3D9TextureFilter(i,state.m_Filter[i]);
				n_assert(SUCCEEDED(hr))
				m_iDevice9->SetSamplerState(i,D3DSAMP_MAXANISOTROPY,state.m_maxAnisotropy[i]);
			}

		}

		for (SizeT i = 8; i < 12; ++i)
		{
			if (state.m_textureIndexEnable[i])
			{
				DWORD vtIndex = D3DVERTEXTEXTURESAMPLER0 + i - 8;
				m_iDevice9->SetSamplerState(vtIndex,D3DSAMP_ADDRESSU,D3D9Types::AsD3D9TextureAddress(state.m_addressU[i]));
				m_iDevice9->SetSamplerState(vtIndex,D3DSAMP_ADDRESSV,D3D9Types::AsD3D9TextureAddress(state.m_addressV[i]));
				m_iDevice9->SetSamplerState(vtIndex,D3DSAMP_ADDRESSW,D3D9Types::AsD3D9TextureAddress(state.m_addressW[i]));
				HRESULT hr = D3D9Types::AsD3D9TextureFilter(vtIndex,state.m_Filter[i]);
				n_assert(SUCCEEDED(hr))
				m_iDevice9->SetSamplerState(vtIndex,D3DSAMP_MAXANISOTROPY,state.m_maxAnisotropy[i]);
			}

		}

	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetDepthAndStencilState(const DeviceDepthAndStencilState& state)
	{

		//depth
		if (state.m_depthEnable)
		{
			SetRenderState(D3DRS_ZENABLE,D3DZB_TRUE);
			SetRenderState(D3DRS_ZFUNC,D3D9Types::AsD3D9CompareFunction(state.m_zFunc));
		}
		else
		{
			SetRenderState(D3DRS_ZENABLE,D3DZB_FALSE);
		}

		if (state.m_depthWriteMask)
		{
			SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
		}
		else
		{
			SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
		}

		//stencil
		SetRenderState (D3DRS_STENCILENABLE, state.m_stencilEnable ? TRUE : FALSE );

		if (!state.m_stencilEnable)
		{
			SetRenderState (D3DRS_TWOSIDEDSTENCILMODE, FALSE);
			return;
		}

		if (state.m_stencilTwoEnable)
		{
			SetRenderState (D3DRS_TWOSIDEDSTENCILMODE, TRUE);
		}
		else
		{
			SetRenderState (D3DRS_TWOSIDEDSTENCILMODE, FALSE);
		}

		SetRenderState (D3DRS_STENCILMASK,state.m_stencilReadMask);
		SetRenderState (D3DRS_STENCILWRITEMASK, state.m_stencilWriteMask);
		SetRenderState (D3DRS_STENCILFUNC, D3D9Types::AsD3D9CompareFunction(state.m_stencilFunc));
		SetRenderState (D3DRS_STENCILFAIL, D3D9Types::AsD3D9StencilOperation(state.m_stencilFail));
		SetRenderState (D3DRS_STENCILZFAIL, D3D9Types::AsD3D9StencilOperation(state.m_stencilZFail));
		SetRenderState (D3DRS_STENCILPASS, D3D9Types::AsD3D9StencilOperation(state.m_stencilPass));
		SetRenderState (D3DRS_CCW_STENCILFUNC, D3D9Types::AsD3D9CompareFunction(state.m_StencilTwoFunc));
		SetRenderState (D3DRS_CCW_STENCILFAIL, D3D9Types::AsD3D9StencilOperation(state.m_stencilTwoFail));
		SetRenderState (D3DRS_CCW_STENCILZFAIL, D3D9Types::AsD3D9StencilOperation(state.m_stencilTwoZFail));
		SetRenderState (D3DRS_CCW_STENCILPASS, D3D9Types::AsD3D9StencilOperation(state.m_stencilTwoPass));
		SetRenderState (D3DRS_STENCILREF, state.m_stencilRef);

	}
	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetStreamSource(IndexT streamIndex, const VertexBuffer* vb, IndexT offsetVertexIndex)
	{
		n_assert((streamIndex >= 0) && (streamIndex < MaxNumVertexStreams));
		n_assert(0 != this->m_iDevice9);
		{
			const VertexBufferD3D9* pVB = _Convert<VertexBuffer, VertexBufferD3D9>(vb);
			HRESULT hr;
			IDirect3DVertexBuffer9* d3d9VertexBuffer = pVB->GetD3D9VertexBuffer();
			DWORD vertexByteSize = pVB->GetVertexLayout()->GetVertexByteSize();
			DWORD vertexByteOffset = offsetVertexIndex * vertexByteSize;
			hr = m_iDevice9->SetStreamSource(streamIndex, d3d9VertexBuffer, vertexByteOffset, vertexByteSize);
			n_assert(SUCCEEDED(hr));
		}
		Super::SetStreamSource(streamIndex, vb, offsetVertexIndex);
	}

	//--------------------------------------------------------------------------------
	void RenderDeviceD3D9::SetStreamSourceFreq(IndexT streamIndex, unsigned long setting)
	{
		n_assert((streamIndex >= 0) && (streamIndex < MaxNumVertexStreams));
		n_assert(0 != this->m_iDevice9);

		HRESULT hr = m_iDevice9->SetStreamSourceFreq(streamIndex, setting);
		n_assert(SUCCEEDED(hr));
	}
	//--------------------------------------------------------------------------------
	HRESULT RenderDeviceD3D9::Clear( DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color,float Z, DWORD Stencil )
	{
		n_assert(m_iDevice9)
		return m_iDevice9->Clear(Count,pRects,Flags,Color,Z,Stencil);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	HRESULT RenderDeviceD3D9::CreateVertexBuffer(UINT Length,DWORD Usage,DWORD FVF,D3DPOOL Pool,IDirect3DVertexBuffer9** ppVertexBuffer,HANDLE* pSharedHandle)
	{
		n_assert(m_iDevice9)

			HRESULT ret = m_iDevice9->CreateVertexBuffer(Length,
			Usage,
			FVF,
			Pool,
			ppVertexBuffer,
			pSharedHandle);
		return ret;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	HRESULT RenderDeviceD3D9::CreateIndexBuffer(UINT Length,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DIndexBuffer9** ppIndexBuffer,HANDLE* pSharedHandle)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->CreateIndexBuffer(Length,
			Usage,
			Format,
			Pool,
			ppIndexBuffer,
			pSharedHandle);
	}

	HRESULT RenderDeviceD3D9::CreateVertexDeclaration(D3DVERTEXELEMENT9* pVertexElements,IDirect3DVertexDeclaration9** ppDecl)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->CreateVertexDeclaration(pVertexElements,ppDecl);
	}

	HRESULT RenderDeviceD3D9::CreateRenderTarget(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Lockable,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->CreateRenderTarget(Width,Height,Format,MultiSample,MultisampleQuality,Lockable,ppSurface,pSharedHandle);
	}

	HRESULT RenderDeviceD3D9::CreateDepthStencilSurface(UINT Width,UINT Height,D3DFORMAT Format,D3DMULTISAMPLE_TYPE MultiSample,DWORD MultisampleQuality,BOOL Discard,IDirect3DSurface9** ppSurface,HANDLE* pSharedHandle)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->CreateDepthStencilSurface(Width,Height,Format,MultiSample,MultisampleQuality,Discard,ppSurface,pSharedHandle);
	}

	HRESULT RenderDeviceD3D9::CreateTexture(UINT Width,UINT Height,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DTexture9** ppTexture,HANDLE* pSharedHandle)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->CreateTexture(Width,Height,Levels,Usage,Format,Pool,ppTexture,pSharedHandle);

	}

	HRESULT RenderDeviceD3D9::CreateCubeTexture(UINT EdgeLength,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DCubeTexture9** ppTexture,HANDLE* pSharedHandle)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
	}



	HRESULT RenderDeviceD3D9::CreateVolumeTexture( UINT Width,UINT Height,UINT Depth,UINT Levels,DWORD Usage,D3DFORMAT Format,D3DPOOL Pool,IDirect3DVolumeTexture9** ppVolumeTexture,HANDLE* pSharedHandle)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
	}


	HRESULT RenderDeviceD3D9::CreateVertexShader(CONST DWORD * pFunction,IDirect3DVertexShader9** ppShader)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->CreateVertexShader(pFunction,ppShader);
	}

	HRESULT RenderDeviceD3D9::CreatePixelShader(CONST DWORD * pFunction,IDirect3DPixelShader9** ppShader)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->CreatePixelShader(pFunction,ppShader);
	}

	HRESULT RenderDeviceD3D9::D3DXCreateTextureFromFileInMemory( LPCVOID pSrcData, UINT SrcDataSize, LPDIRECT3DTEXTURE9* ppTexture)
	{
		n_assert(m_iDevice9)
			return ::D3DXCreateTextureFromFileInMemory(m_iDevice9,pSrcData,SrcDataSize,ppTexture);
	}

	HRESULT RenderDeviceD3D9::D3DXCreateVolumeTextureFromFileInMemory( LPCVOID pSrcData, UINT SrcDataSize, LPDIRECT3DVOLUMETEXTURE9* ppVolumeTexture)
	{
		n_assert(m_iDevice9)
			return ::D3DXCreateVolumeTextureFromFileInMemory(m_iDevice9,pSrcData,SrcDataSize,ppVolumeTexture);
	}

	HRESULT RenderDeviceD3D9::D3DXCreateCubeTextureFromFileInMemory( LPCVOID pSrcData, UINT SrcDataSize, LPDIRECT3DCUBETEXTURE9* ppCubeTexture)
	{
		n_assert(m_iDevice9)
			return ::D3DXCreateCubeTextureFromFileInMemory(m_iDevice9,pSrcData,SrcDataSize,ppCubeTexture);
	}

	HRESULT RenderDeviceD3D9::CheckDeviceFormat( UINT Adapter, D3DDEVTYPE DeviceType, D3DFORMAT AdapterFormat, DWORD Usage, D3DRESOURCETYPE RType, D3DFORMAT CheckFormat )
	{
		n_assert(m_iD3D9)
			return m_iD3D9->CheckDeviceFormat(Adapter, DeviceType, AdapterFormat, Usage, RType,CheckFormat);
	}

	HMONITOR RenderDeviceD3D9::GetAdapterMonitor( UINT Adapter )
	{
		n_assert(m_iD3D9)
			return m_iD3D9->GetAdapterMonitor( Adapter );
	}

	HRESULT RenderDeviceD3D9::GetDeviceCaps(UINT Adapter,D3DDEVTYPE DeviceType,D3DCAPS9* pCaps)
	{
		n_assert(m_iD3D9)
			return m_iD3D9->GetDeviceCaps( Adapter, DeviceType, pCaps);
	}

	HRESULT RenderDeviceD3D9::GetAdapterIdentifier( UINT Adapter, DWORD Flags, D3DADAPTER_IDENTIFIER9 * pIdentifier )
	{
		n_assert(m_iD3D9)
			return m_iD3D9->GetAdapterIdentifier( Adapter, Flags, pIdentifier);
	}

	HRESULT RenderDeviceD3D9::CheckDeviceMultiSampleType(UINT Adapter,D3DDEVTYPE DeviceType,D3DFORMAT SurfaceFormat,BOOL Windowed,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD* pQualityLevels)
	{
		n_assert(m_iD3D9)
			return m_iD3D9->CheckDeviceMultiSampleType( Adapter, DeviceType,SurfaceFormat, Windowed, MultiSampleType, pQualityLevels);
	}

	HRESULT RenderDeviceD3D9::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer,D3DBACKBUFFER_TYPE Type,IDirect3DSurface9** ppBackBuffer)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->GetBackBuffer(iSwapChain,iBackBuffer,Type,ppBackBuffer);

	}

	HRESULT RenderDeviceD3D9::GetRenderTargetData( IDirect3DSurface9* pRenderTarget,IDirect3DSurface9* pDestSurface)
	{
		n_assert(m_iDevice9)
			return m_iDevice9->GetRenderTargetData(pRenderTarget,pDestSurface);
	}

	HRESULT RenderDeviceD3D9::CreateAdditionalSwapChain( D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain9 **ppSwapChain )
	{
		n_assert(m_iDevice9)
			return m_iDevice9->CreateAdditionalSwapChain(pPresentationParameters,ppSwapChain);

	}


	//------------------------------------------------------------------------------
	/**
	*/
	HRESULT RenderDeviceD3D9::SetSamplerState(DWORD Sampler,D3DSAMPLERSTATETYPE Type,DWORD Value)
	{
		n_assert(m_iDevice9)
		return m_iDevice9->SetSamplerState(Sampler,Type,Value);
	}
	//------------------------------------------------------------------------------
	/**
	*/
	HRESULT RenderDeviceD3D9::SetRenderTarget(DWORD RenderTargetIndex,IDirect3DSurface9 *pRenderTarget)
	{
		n_assert(m_iDevice9)
		return m_iDevice9->SetRenderTarget(RenderTargetIndex,pRenderTarget);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	HRESULT RenderDeviceD3D9::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
	{
		n_assert(m_iDevice9)
		return m_iDevice9->SetDepthStencilSurface(pNewZStencil);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	HRESULT RenderDeviceD3D9::StretchRect( IDirect3DSurface9* pSourceSurface,CONST RECT* pSourceRect,IDirect3DSurface9* pDestSurface,CONST RECT* pDestRect,D3DTEXTUREFILTERTYPE Filter)
	{
		n_assert(m_iDevice9)
		return m_iDevice9->StretchRect(pSourceSurface,pSourceRect,pDestSurface,pDestRect,Filter);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetVertexLayout(const VertexLayout* vl)
	{
		n_assert(vl);

		const VertexLayoutD3D9* pVL = _Convert<VertexLayout, VertexLayoutD3D9>(vl);
		HRESULT hr;
		IDirect3DVertexDeclaration9* d3d9VertexDecl = pVL->GetD3D9VertexDeclaration();
		hr = this->m_iDevice9->SetVertexDeclaration(d3d9VertexDecl);
		n_assert(SUCCEEDED(hr));
		
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetIndexBuffer(const IndexBuffer* ib)
	{
		n_assert(0 != this->m_iDevice9);
		n_assert(ib);

		//if (this->indexBuffer != ib)
		{
			HRESULT hr;

			// set the index buffer on the d3d device
			const IndexBufferD3D9* pIB = _Convert<IndexBuffer, IndexBufferD3D9>(ib);
			IDirect3DIndexBuffer9* d3d9IndexBuffer = pIB->GetD3D9IndexBuffer();
			hr = this->m_iDevice9->SetIndices(d3d9IndexBuffer);
			n_assert(SUCCEEDED(hr));
		}
		//Super::SetIndexBuffer(ib);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetPrimitiveGroup(const PrimitiveGroup* pg)
	{
		this->m_primitiveGroupD9 = _Convert<PrimitiveGroup, PrimitiveGroupD3D9>(pg);

		if ( m_stateCache.primitiveCache != m_primitiveGroupD9)
		{
			m_stateCache.primitiveCache = m_primitiveGroupD9;

			SetStreamSource(0, m_primitiveGroupD9->GetVertexBuffer(), 0);
			SetVertexLayout((m_primitiveGroupD9->GetVertexBuffer())->GetVertexLayout());
			
			if (m_primitiveGroupD9->GetIndexBuffer())
			{
				SetIndexBuffer(m_primitiveGroupD9->GetIndexBuffer());
			}	
		}
	}
	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetGPUProgram(const GPUProgram* program)
	{
		m_pGPUProgramD9 = _Convert<GPUProgram, GPUProgramD3D9>(program);

		if ( m_pGPUProgramD9 != m_stateCache.programCache )
		{
			m_stateCache.programCache = m_pGPUProgramD9;

			m_iDevice9->SetVertexShader(m_pGPUProgramD9->GetVertexShaderD3D9());
			m_iDevice9->SetPixelShader(m_pGPUProgramD9->GetPixelShaderD3D9());
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetVertexShaderConstantVectorF(const int& reg, float* val, const int& vec4count)
	{
		n_assert(m_iDevice9);
		m_iDevice9->SetVertexShaderConstantF(reg,val,vec4count);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetPixelShaderConstantVectorF(const int& reg, float* val, const int& vec4count)
	{
		n_assert(m_iDevice9);
		m_iDevice9->SetPixelShaderConstantF(reg,val,vec4count);
	}
	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetVertexShaderConstantFloat(const int& reg, float* val)
	{
		n_assert(m_iDevice9);
		m_iDevice9->SetVertexShaderConstantF(reg,val,1);
	}
	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetPixelShaderConstantFloat(const int& reg, float* val)
	{
		n_assert(m_iDevice9);
		m_iDevice9->SetPixelShaderConstantF(reg,val,1);
	}
	//------------------------------------------------------------------------------
	/**
	*/
	void 
		RenderDeviceD3D9::SetVertexShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount)
	{
		n_assert(m_iDevice9);
		m_iDevice9->SetVertexShaderConstantF(reg,val,matrixCount * 4);
	}
	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::SetPixelShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount)
	{
		n_assert(m_iDevice9)
			m_iDevice9->SetPixelShaderConstantF(reg,val,matrixCount * 4);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool
		RenderDeviceD3D9::BeginFrame()
	{
		HRESULT hr;
		hr = this->m_iDevice9->BeginScene();
		n_assert(SUCCEEDED(hr));
		ClearCache();
		return true;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	bool RenderDeviceD3D9::OnDeviceLost()
	{
		SetupDefaultDisplayParams();
		return true;
	}

	bool RenderDeviceD3D9::CheckReset()
	{
		return (D3DERR_DEVICENOTRESET == m_iDevice9->TestCooperativeLevel());
	}

	bool RenderDeviceD3D9::OnDeviceReset()
	{
		HRESULT hr;
		while ( FAILED(hr = m_iDevice9->TestCooperativeLevel()))
		{
			if (hr == D3DERR_DEVICENOTRESET)
			{
				//bRealDeviceLost = true;
				if(FAILED(m_iDevice9->Reset(&m_defaultDisplayPresentParams)))
				{
					Sleep(10);
					continue;
				}
			}
		}
		return true;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void RenderDeviceD3D9::SetRenderTarget( RenderTarget* rt)
	{
		HRESULT hr;
		 RenderTargetD3D9* rtd3d9 = _Convert<RenderTarget, RenderTargetD3D9>(rt);
		IndexT i = rt->GetMRTIndex();

		if (m_pRenderTargets[i])
		{
			m_pRenderTargets[i]->EndPass();
		}
		m_pRenderTargets[i] = rtd3d9;
		if (NULL != rtd3d9->d3d9RenderTarget)
		{
			m_iDevice9->SetRenderTarget(i, rtd3d9->d3d9RenderTarget);
		}
		else
		{	
			n_assert(rt->IsDefaultRenderTarget())
			n_assert(NULL == m_iBackBufferSurface9)
			if (rt->IsDummy() && 0 != m_iCurrentSwapChain)
			{
				//Do nothing
			}
			else
			{
				m_iCurrentSwapChain = rtd3d9->GetD3D9SwapChain();
			}
			if (m_bGPUDebugging)
			{
				hr = m_iDevice9->GetBackBuffer(0,0, D3DBACKBUFFER_TYPE_MONO, &m_iBackBufferSurface9);	
			}
			else
			{
				hr = m_iCurrentSwapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &m_iBackBufferSurface9);
			}
			n_assert(SUCCEEDED(hr));			
			hr = m_iDevice9->SetRenderTarget(0, m_iBackBufferSurface9);
			n_assert(SUCCEEDED(hr));
			m_iBackBufferSurface9->Release();
			m_iBackBufferSurface9 = 0;
		}

		// apply the depth stencil buffer
		if (NULL != rtd3d9->d3d9DepthStencil)
		{
			hr = m_iDevice9->SetDepthStencilSurface(m_pRenderTargets[i]->d3d9DepthStencil);
			n_assert(SUCCEEDED(hr));
		}
		else
		{
			m_iDevice9->SetDepthStencilSurface(NULL);     
		}

		DWORD d3d9ClearFlags = 0;
		if (0 != (rtd3d9->clearFlags & RenderTarget::ClearColor))
		{
			d3d9ClearFlags |= D3DCLEAR_TARGET;
		}
		if (0 != rtd3d9->d3d9DepthStencil)
		{
			if (0 != (rtd3d9->clearFlags & RenderTarget::ClearDepth))
			{
				d3d9ClearFlags |= D3DCLEAR_ZBUFFER;
			}
			if (0 != (rtd3d9->clearFlags & RenderTarget::ClearStencil))
			{
				d3d9ClearFlags |= D3DCLEAR_STENCIL;
			}
		}
		if (0 != d3d9ClearFlags)
		{
			hr = m_iDevice9->Clear(0,             // Count
				NULL,          // pRects
				d3d9ClearFlags,    // Flags
				D3DCOLOR_COLORVALUE(m_pRenderTargets[i]->GetClearColor().x(), 
				rtd3d9->GetClearColor().y(), 
				rtd3d9->GetClearColor().z(), 
				rtd3d9->GetClearColor().w()),  // Color
				rtd3d9->clearDepth,           // Z
				rtd3d9->clearStencil);        // Stencil
			n_assert(SUCCEEDED(hr));
		}

	}

	void RenderDeviceD3D9::SetMultipleRenderTarget(const MultipleRenderTarget* mrt, bool resume /* = false */)
	{
		n_assert(mrt);
		
		const MultipleRenderTargetD3D9* mrtD9 = _Convert<MultipleRenderTarget, MultipleRenderTargetD3D9>(mrt);

		for (IndexT i = 0; i < mrtD9->GetNumRendertargets(); ++i)
		{
			const GPtr<RenderTarget>& rt = mrtD9->GetRenderTarget(i);

			if (resume)
			{
				IndexT index = rt->GetMRTIndex();

				if (index != 0)
				{
					DisableRenderTarget(index);
				}
			}
			else
			{
				SetRenderTarget(rt);
			}

		}
			
		

	}

	void RenderDeviceD3D9::DisableRenderTarget(int index)
	{
		n_assert(0 != index);
		SetRenderTarget(index, NULL);
	}

	void RenderDeviceD3D9::SetTexture(const Texture* tex)
	{
		n_assert(m_iDevice9)
		const TextureD3D9* texture = _Convert<Texture, TextureD3D9>(tex);

		if (texture->GetUnitIndex() < 8)
		{
			if ( m_stateCache.textureCache[texture->GetUnitIndex()] != texture )
			{
				m_stateCache.textureCache[texture->GetUnitIndex()] = texture;

				HRESULT hr = m_iDevice9->SetTexture(texture->GetUnitIndex(),texture->GetD3D9BaseTexture());
				n_assert(SUCCEEDED(hr))
			}
		}
		else
		{
			SizeT index = texture->GetUnitIndex() - 8;
			DWORD vtIndex = D3DVERTEXTEXTURESAMPLER0;
			switch (index)
			{
			case 0:
				break;
			case 1:
				vtIndex = D3DVERTEXTEXTURESAMPLER1;
				break;
			case 2:
				vtIndex = D3DVERTEXTEXTURESAMPLER2;
				break;
			case 3:
				vtIndex = D3DVERTEXTEXTURESAMPLER3;
				break;
			default:
				n_error("Set VertexTexture error!");
			}
			HRESULT hr = m_iDevice9->SetTexture(vtIndex,texture->GetD3D9BaseTexture());
			n_assert(SUCCEEDED(hr))
		}
			
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::EndFrame()
	{

		for(int i = 0; i < MRT_COUNT; ++i)
		{
			if (m_pRenderTargets[i])
			{
				m_pRenderTargets[i]->EndPass();
				m_pRenderTargets[i] = NULL;
			}
		}

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

		ClearCache();
		
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::Present(WindHandle hwnd)
	{
		if (!hwnd)		
			hwnd = m_hMainWindow;
		HRESULT hr = S_OK;
		if (m_bGPUDebugging)
		{
			hr = m_iDevice9->Present(NULL,NULL,(HWND)hwnd,NULL);
		}
		else
		{
			n_assert(m_iCurrentSwapChain);
			hr = m_iCurrentSwapChain->Present(NULL,NULL, (HWND)hwnd,NULL,0);//hwnd
			m_iCurrentSwapChain = 0;
		}
		if(hr == D3DERR_DEVICELOST)
		{
			m_bDeviceLost = true;
			if (m_deviceCallBack)
			{
				m_deviceCallBack();
			}
		}
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::Draw(SizeT startVertice,SizeT numVertice,SizeT startIndice,SizeT numIndice)
	{
		D3DPRIMITIVETYPE d3dPrimType = D3D9Types::AsD3D9PrimitiveType(this->m_primitiveGroupD9->GetPrimitiveTopology());

		n_assert(m_primitiveGroupD9->GetNumVertices() >= numVertice && m_primitiveGroupD9->GetNumVertices() >= startVertice)
		n_assert(m_primitiveGroupD9->GetNumIndices() >= numIndice && m_primitiveGroupD9->GetNumIndices() >= startIndice)
		SizeT numTris = 0;
		if (this->m_primitiveGroupD9->GetNumIndices() > 0)
		{
			// use indexed rendering
			numTris = this->m_primitiveGroupD9->NumberOfPrimitives( m_primitiveGroupD9->GetPrimitiveTopology(), numIndice);
			HRESULT hr;
			hr = m_iDevice9->DrawIndexedPrimitive(
				d3dPrimType,                                        // Type
				0,                                                  // BaseVertexIndex
				startVertice,               // MinIndex
				numVertice,              // NumVertices
				startIndice,                // StartIndex
				numTris );           // PrimitiveCount
			n_assert(SUCCEEDED(hr));
			
		}
		else
		{
			numTris = this->m_primitiveGroupD9->NumberOfPrimitives( m_primitiveGroupD9->GetPrimitiveTopology(), numVertice);
			// use non-indexed rendering
			HRESULT hr;
			hr = m_iDevice9->DrawPrimitive(
				d3dPrimType,                                        // Type
				m_primitiveGroupD9->GetBaseVertex(),               // StartVertex
				numTris );           // PrimitiveCount
			n_assert(SUCCEEDED(hr));
		}
		PROFILER_ADDDEVICESTATEVAL( tris, numTris );
		PROFILER_ADDDEVICESTATEVAL( calls, 1 );
		PROFILER_ADDDEVICESTATEVAL( verts, numVertice );
	}

	//------------------------------------------------------------------------------
	/**
	*/
	void
		RenderDeviceD3D9::DrawIndexedInstanced(SizeT numInstances)
	{
		//n_assert(this->inBeginPass);
		// override in subclass!
	}

	GPtr<PrimitiveGroup> RenderDeviceD3D9::CreatePrimitiveGroup(const VertexBufferData* vbd, const IndexBufferData* ibd)
	{
		n_assert(NULL != vbd);
		GPtr<PrimitiveGroupD3D9> prim = PrimitiveGroupD3D9::Create();
		prim->LoadBuffers(vbd, ibd);
		return prim.upcast<PrimitiveGroup>();
	}
	void RenderDeviceD3D9::ChangePrimitiveGroup(PrimitiveGroup* group, const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd /* = NULL */)
	{
		PrimitiveGroupD3D9* pg9 = static_cast<PrimitiveGroupD3D9*>(group);
		if (vbd)
		{
			pg9->DiscardVertexBuffer();
		}
		if (ibd)
		{
			pg9->DiscardIndexBuffer();
		}
		pg9->LoadBuffers(vbd, ibd);
	}

	void RenderDeviceD3D9::UpdateVertexBuffer(VertexBuffer* vb, const DataStream& data)
	{
		n_assert(vb);
		VertexBufferD3D9* vb9 = _Convert<VertexBuffer, VertexBufferD3D9>(vb);
		vb9->UpdateData(data);
	}

	void RenderDeviceD3D9::UpdateIndexBuffer(IndexBuffer* ib, const DataStream& data)
	{
		n_assert(ib);
		IndexBufferD3D9* ib9 = _Convert<IndexBuffer, IndexBufferD3D9>(ib);
		ib9->UpdateData(data);
	}

	const GPtr<GPUProgram> RenderDeviceD3D9::CreateRenderGPUProgram(const GPtr<GPUProgram>& srcGPUProgram)
	{
		GPtr<GPUProgramD3D9> pGPUProgramD9 = GPUProgramD3D9::Create();
		pGPUProgramD9->SetCodePath(srcGPUProgram->GetCodePath());
		pGPUProgramD9->SetVertexCode(srcGPUProgram->GetVertexCode());
		pGPUProgramD9->SetPixelCode(srcGPUProgram->GetPixelCode());
		if (srcGPUProgram->GetCodePath().IsValid())
		{
			pGPUProgramD9->LoadBuffers();
		}
		else
		{
			pGPUProgramD9->LoadCodes();
		}
		pGPUProgramD9->SetVertexCode("");
		pGPUProgramD9->SetPixelCode("");
		
		return pGPUProgramD9.upcast<GPUProgram>();
	}

	const GPtr<RenderStateDesc> RenderDeviceD3D9::CreateRenderState(const GPtr<RenderStateDesc>& state)
	{
		GPtr<RenderStateDesc> rsDesc = RenderStateDesc::Create();
		rsDesc->Setup();
		rsDesc->SetBlendState(state->GetBlendState());
		rsDesc->SetSamplerState(state->GetSamplerState());
		rsDesc->SetDepthAndStencilState(state->GetDepthAndStencilState());
		rsDesc->SetRasterizerState(state->GetRasterizerState());
		rsDesc->SetUpdateFlag(state->GetUpdateFlag());
		return rsDesc;
	}

	const GPtr<RenderTarget> RenderDeviceD3D9::CreateRenderTarget(const GPtr<RenderTarget>& rt)
	{
		GPtr<RenderTargetD3D9> rtD9 = RenderTargetD3D9::Create();
		rtD9->SetDummy(rt->IsDummy());
		rtD9->SetWidth(rt->GetWidth());
		rtD9->SetHeight(rt->GetHeight());
		rtD9->SetAntiAliasQuality(rt->GetAntiAliasQuality());
		rtD9->SetColorBufferFormat(rt->GetColorBufferFormat());
		rtD9->SetMipMapsEnabled(rt->AreMipMapsEnabled());
		rtD9->SetClearFlags(rt->GetClearFlags());
		rtD9->SetClearColor(rt->GetClearColor());
		rtD9->SetClearStencil(rt->GetClearStencil());
		rtD9->SetClearDepth(rt->GetClearDepth());
		if (rt->HasDepthStencilBuffer())
		{
			rtD9->AddDepthStencilBuffer();
		}
		if (rt->IsResolveTextureDimensionsValid())
		{
			rtD9->SetResolveTextureWidth(rt->GetResolveTextureWidth());
			rtD9->SetResolveTextureHeight(rt->GetResolveTextureHeight());
			rtD9->SetResolveTargetCpuAccess(rt->GetResolveTargetCpuAccess());
			rtD9->SetResolveRect(rt->GetResolveRect());
		}

		rtD9->SetScreenSizeRatio(rt->GetScreenSizeRatio());
		rtD9->SetDefaultRenderTarget(rt->IsDefaultRenderTarget());
		rtD9->LoadBuffers(rt->GetWidth(), rt->GetHeight());
		rtD9->AssignD3D9Textures();
		return rtD9.upcast<RenderTarget>();
	}

	const GPtr<MultipleRenderTarget> RenderDeviceD3D9::CreateMultipleRenderTarget(const GPtr<MultipleRenderTarget>& mrt)
	{
		GPtr<MultipleRenderTargetD3D9> mrtD9 = MultipleRenderTargetD3D9::Create();

		for (IndexT i = 0; i < mrt->GetNumRendertargets(); ++i)
		{
			const GPtr<RenderTarget>& rt = mrt->GetRenderTarget(i);
			mrtD9->AddRenderTarget(rt);
		}

		return mrtD9.upcast<MultipleRenderTarget>();
	}

	const GPtr<Texture> RenderDeviceD3D9::CreateRenderSideTexture(GPtr<Texture> tex)
	{
		GPtr<TextureD3D9> texture = TextureD3D9::Create();
		texture->Setup(tex);
		if ( texture->GetPixelFormat() == PixelFormat::InvalidPixelFormat )
		{
			texture->LoadFileFromBuffers();
		}
		else
		{
			texture->LoadBuffers();
		}
		texture->SetStream(NULL);
		return texture.upcast<Texture>();
	}

	void RenderDeviceD3D9::UpdateTexture(RenderBase::Texture::UpdateFunction texUpdateFunc,GPtr<Texture> destTex, void* tag)
	{
		GPtr<TextureD3D9> destTexD9 = destTex.downcast<TextureD3D9>();
		n_assert(destTexD9.isvalid())
		//TODO
		destTexD9->UpdateTexture(texUpdateFunc, tag);
	}

	void RenderDeviceD3D9::UpdateTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex)
	{
		GPtr<TextureD3D9> destTexD9 = destTex.downcast<TextureD3D9>();
		n_assert(destTexD9.isvalid())

		destTexD9->UpdateTexture( srcTex );
	}

	void RenderDeviceD3D9::ChangeTexture(GPtr<Texture> srcTex, GPtr<Texture> destTex)
	{
		GPtr<TextureD3D9> destTexD9 = destTex.downcast<TextureD3D9>();
		n_assert(destTexD9.isvalid());
		destTexD9->Unload();

		destTexD9->Setup(srcTex);

		if ( destTexD9->GetPixelFormat() == PixelFormat::InvalidPixelFormat )
		{
			destTexD9->LoadFileFromBuffers();
		}
		else
		{
			destTexD9->LoadBuffers();
		}
		destTexD9->SetStream(NULL);
	}

	void RenderDeviceD3D9::SetViewPort(const int& x,const int& y,const int& width,const int& height,const float& minZ,const float& maxZ)
	{
		D3DVIEWPORT9 vp;
		vp.X = x;
		vp.Y = y;
		vp.Width = width;
		vp.Height = height;
		vp.MinZ = minZ;
		vp.MaxZ = maxZ;
		m_iDevice9->SetViewport(&vp);

	}

	// Fixed Pipeline Functions
	//------------------------------------------------------------------------------
	/**
	*/
	void RenderDeviceD3D9::FXSetClipPlane(const int& index,const Math::float4& plane)
	{
		m_iDevice9->SetClipPlane(index,(float*)&plane);
	}

	//------------------------------------------------------------------------
	void RenderDeviceD3D9::ClearCache()
	{
		m_stateCache.ClearCache();
	}

	D3D9Window* RenderDeviceD3D9::CreateViewPortWnd( WindHandle hWnd )
	{
		return new D3D9Window( this, hWnd );
	}

	void RenderDeviceD3D9::DestroyViewPortWnd( D3D9Window* view )
	{
		delete view;
	}
}

#endif