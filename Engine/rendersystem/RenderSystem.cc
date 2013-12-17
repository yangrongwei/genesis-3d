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

#include "stdneb.h"
#include "RenderSystem.h"
#include "config/RenderDeviceConfig.h"

#if RENDERDEVICE_D3D9
#include "d3d9/RenderDeviceD3D9.h"
#include "d3d9/PrimitiveGroupD3D9.h"
#endif
#if RENDERDEVICE_OPENGLES
#include "gles/RenderDeviceGLES.h"
#endif
#if RENDERDEVICE_NULL
#include "null/RenderDeviceNull.h"
#endif

#include "base/PrimitiveGroup.h"
#include "RenderMessageProtocol.h"

namespace RenderBase
{
	__ImplementClass(RenderSystem, 'REND', Core::RefCounted);
	__ImplementThreadSingleton(RenderSystem);

#if RENDERDEVICE_D3D9
	using namespace D3D9;
#endif

#if RENDERDEVICE_OPENGLES
	using namespace GLES;
#endif

#if RENDERDEVICE_NULL
	using namespace NullDevice;
#endif

 	void RenderSystem::Open(int width, int height)
 	{
		
#if RENDERDEVICE_D3D9
		m_renderDevice = RenderDeviceD3D9::Create();
		m_renderDevice.cast<RenderDeviceD3D9>()->SetMainWindowHandle(m_mainHWND);
#endif

#if RENDERDEVICE_NULL
		m_renderDevice = RenderDeviceNull::Create();
		m_renderDevice.cast<RenderDeviceNull>()->SetMainWindowHandle(m_mainHWND);
#endif

#if RENDERDEVICE_OPENGLES
		m_renderDevice = RenderDeviceGLES::Create();
		m_renderDevice.cast<RenderDeviceGLES>()->SetMainWindowHandle(m_mainHWND);
#endif
		m_renderDevice->SetSize(width, height);
		m_renderDevice->InitDevice();

		m_renderDevice->DetectGraphicCardCaps();

		if (!m_dummyRenderTargetHandle.IsValid())
		{
			GPtr<RenderBase::RenderTarget> renderTarget = RenderBase::RenderTarget::Create();
			renderTarget->SetDefaultRenderTarget(true);
			renderTarget->SetClearColor(Math::float4(0.f,0.f,1.f,1.f));
			renderTarget->SetClearFlags(RenderBase::RenderTarget::ClearAll);
			renderTarget->SetWidth(1);
			renderTarget->SetHeight(1);
			renderTarget->SetDummy(true);
			RenderBase::TextureHandle dummytexhandle;
			m_dummyRenderTargetHandle = CreateRenderTarget(renderTarget,dummytexhandle);
		}
 	}


	void RenderSystem::Close()
	{

		for ( RenderResourceHandleSet::type::iterator itor = m_renderHandles.begin();
			itor != m_renderHandles.end(); ++itor )
		{

			itor->mRO->Release();
		}

		m_renderHandles.clear();
	}

	RenderSystem::RenderSystem()
	{
		__ConstructThreadSingleton;
		m_renderDisplay = RenderDisplay::Create();
		
	}

	RenderSystem::~RenderSystem()
	{
		m_renderDisplay = 0;
		m_renderDevice = 0;
		__DestructThreadSingleton;
	}

	void RenderSystem::BeginFrame()
	{
		m_renderDevice->BeginFrame();
	}

	void RenderSystem::EndFrame()
	{
		m_renderDevice->EndFrame();
	}

	void RenderSystem::Clear()
	{
		
	}

	PrimitiveGroup* RenderSystem::GetPrimitiveGroup(const PrimitiveHandle& handle) const
	{
		if (RenderBase::RenderCommandType::DrawPrimGroup == handle.GetType())
		{
			return static_cast<PrimitiveGroup*>(handle.mRO);
		}
		return NULL;
	}

	Texture* RenderSystem::GetTexture(const TextureHandle& handle) const
	{
		if (RenderBase::RenderCommandType::SetTexture == handle.GetType())
		{
			return static_cast<Texture*>(handle.mRO);
		}
		return NULL;
	}

	PrimitiveHandle RenderSystem::CreatePrimitiveHandle(const VertexBufferData* vbd, const IndexBufferData* ibd /* = NULL */)
	{
		GPtr<PrimitiveGroup> pg = m_renderDevice->CreatePrimitiveGroup(vbd, ibd);
		pg->SetRenderCommandType(RenderCommandType::DrawPrimGroup);
		PrimitiveHandle handle;
		handle.mRO = pg.get();

		bool bOK = _AddRenderHandle(handle);
		n_assert(bOK);

		return handle;
	}

	void RenderSystem::ChangePrimitiveHandle(RenderBase::PrimitiveHandle& handle, const RenderBase::VertexBufferData* vbd, const RenderBase::IndexBufferData* ibd /* = NULL */)
	{
		n_assert (RenderBase::RenderCommandType::DrawPrimGroup == handle.GetType())
		
		m_renderDevice->ChangePrimitiveGroup(static_cast<PrimitiveGroup*>(handle.mRO), vbd, ibd);
		
	}

	void RenderSystem::UpdateVertexBuffer(PrimitiveHandle& handle, const DataStream& data)
	{
		PrimitiveGroup* pg = GetPrimitiveGroup(handle);
		m_renderDevice->UpdateVertexBuffer(pg->GetVertexBuffer().get(), data);
	}

	void RenderSystem::UpdateIndexBuffer(PrimitiveHandle& handle, const DataStream& data)
	{
		PrimitiveGroup* pg = GetPrimitiveGroup(handle);
		m_renderDevice->UpdateIndexBuffer(pg->GetIndexBuffer().get(), data);
	}

	GPUProgramHandle RenderSystem::CreateShaderProgram( const GPtr<GPUProgram>& program )
	{
		const GPtr<RenderCommandType> rcType = m_renderDevice->CreateRenderGPUProgram(program).upcast<RenderCommandType>();
		rcType->SetRenderCommandType(RenderCommandType::SetGPUProgram);

		GPUProgramHandle handle;
		handle.mRO = rcType.get();
		
		bool bOK = _AddRenderHandle(handle);
		n_assert(bOK);

		return handle;
	}

	RenderStateDescHandle RenderSystem::CreateRenderStateObject( const GPtr<RenderStateDesc>& rsObject)
	{
		n_assert(rsObject.isvalid())
		const GPtr<RenderCommandType> rcType = m_renderDevice->CreateRenderState(rsObject).upcast<RenderCommandType>();
		rcType->SetRenderCommandType(RenderCommandType::SetRenderState);
		
		RenderStateDescHandle handle;
		handle.mRO = rcType.get();
		
		bool bOK = _AddRenderHandle(handle);
		n_assert(bOK);

		return handle;
	}

	RenderTargetHandle RenderSystem::CreateRenderTarget( const GPtr<RenderTarget>& rt, TextureHandle& texhandle)
	{
		n_assert(rt.isvalid())
		
		//generate render target guid
		GPtr<RenderTarget> deviceRT = m_renderDevice->CreateRenderTarget(rt);
		GPtr<RenderCommandType> rcType = deviceRT.upcast<RenderCommandType>();
		rcType->SetRenderCommandType(RenderCommandType::SetRenderTarget);

		RenderTargetHandle handle;
		handle.mRO = rcType.get();
		
		bool bOK = _AddRenderHandle(handle);
		n_assert(bOK);

		if (!rt->IsDefaultRenderTarget())
		{
			//generate render texture guid
			GPtr<RenderCommandType> rcType = deviceRT->GetResolveTexture().upcast<RenderCommandType>();
			texhandle.mRO = rcType.get();
			
			bool bOK = _AddRenderHandle(texhandle);
			n_assert(bOK);
		}
		return handle;
	}

	MultipleRenderTargetHandle RenderSystem::CreateMultipleRenderTarget(const GPtr<MultipleRenderTarget>& mrt, Util::Array< RenderBase::RenderTargetHandle >& handles)
	{
		n_assert(mrt.isvalid())

			for (IndexT i = 0; i < handles.Size(); ++i)
			{
				GPtr<RenderCommandType> rcType( (RenderCommandType*)handles[i].mRO );
				GPtr<RenderTarget> rt = rcType.downcast<RenderTarget>();
				n_assert(rt);

				mrt->AddRenderTarget(rt);
			}

			GPtr<MultipleRenderTarget> deviceMRT = m_renderDevice->CreateMultipleRenderTarget(mrt);
			GPtr<RenderCommandType> rcType = deviceMRT.upcast<RenderCommandType>();
			rcType->SetRenderCommandType(RenderCommandType::SetMultiRenderTarget);

			MultipleRenderTargetHandle handle;
			handle.mRO = rcType.get();

			bool bOK = _AddRenderHandle(handle);
			n_assert(bOK);

			return handle;
	}

	TextureHandle RenderSystem::CreateTexture( const GPtr<Texture>& tex)
	{
		n_assert(tex.isvalid())
		GPtr<RenderCommandType> rcType = m_renderDevice->CreateRenderSideTexture(tex).upcast<RenderCommandType>();
		rcType->SetRenderCommandType(RenderCommandType::SetTexture);
		
		TextureHandle handle;
		handle.mRO = rcType.get();
		
		bool bOK = _AddRenderHandle(handle);
		n_assert(bOK);

		return handle;
	}

	void RenderSystem::UpdateTexture(TextureHandle texHandle, RenderBase::Texture::UpdateFunction texUpdateFunc, void* tag)
	{
		if (!texHandle.IsValid())
		{
			n_warning("RenderSystem::UpdateTexture():texHandle is invalid!\n");
			return;
		}

		GPtr<RenderCommandType> rcType( (RenderCommandType*)texHandle.mRO );
		GPtr<Texture> destTex = rcType.downcast<Texture>();
		n_assert(destTex.isvalid())
		m_renderDevice->UpdateTexture(texUpdateFunc,destTex, tag);

	}

	void RenderSystem::UpdateTexture(TextureHandle texHandle, GPtr<RenderBase::Texture> texture)
	{
		if (!texHandle.IsValid())
		{
			n_warning("RenderSystem::UpdateTexture():texHandle is invalid!\n");
			return;
		}

		GPtr<RenderCommandType> rcType( (RenderCommandType*)texHandle.mRO );
		GPtr<Texture> destTex = rcType.downcast<Texture>();
		n_assert(destTex.isvalid())
		m_renderDevice->UpdateTexture( texture, destTex );

	}

	void RenderSystem::ChangeTexture(RenderBase::TextureHandle texHandle, GPtr<Texture> texture)
	{
		if (!texHandle.IsValid())
		{
			n_warning("RenderSystem::UpdateTexture():texHandle is invalid!\n");
			return;
		}

		GPtr<RenderCommandType> rcType( (RenderCommandType*)texHandle.mRO );
		GPtr<Texture> destTex = rcType.downcast<Texture>();
		n_assert(destTex.isvalid())
		m_renderDevice->ChangeTexture( texture, destTex );
	}

	void RenderSystem::_DrawPrimitive(PrimitiveHandle handle,SizeT startVertice,SizeT endVertice,SizeT startIndice,SizeT endIndice)
	{

		n_assert( handle.IsValid() );
		n_assert(startVertice >= 0);
		n_assert(endVertice >= 0);
		n_assert(startIndice >= 0);
		n_assert(endIndice >= 0);

		const PrimitiveGroup* primGroup = static_cast<const PrimitiveGroup*>(handle.mRO);
		n_assert(primGroup);

		m_renderDevice->SetPrimitiveGroup(primGroup);

		m_renderDevice->Draw(startVertice, endVertice, startIndice, endIndice);
	}
	//--------------------------------------------------------------------------------
	void RenderSystem::_DrawPrimitive(PrimitiveHandle handle)
	{
		const PrimitiveGroup* primGroup = RenderDevice::_Convert<Core::RefCounted, PrimitiveGroup>(handle.mRO);
		m_renderDevice->SetPrimitiveGroup(primGroup);
		m_renderDevice->Draw(primGroup->GetBaseVertex(), primGroup->GetNumVertices(), primGroup->GetBaseIndex(), primGroup->GetNumIndices());
	}
	//--------------------------------------------------------------------------------
	void RenderSystem::_DrawPrimitiveHWInstance(PrimitiveHandle handle)
	{	

		
	}
	//--------------------------------------------------------------------------------

	void RenderSystem::_SetRenderTarget(RenderTargetHandle handle,SizeT index,uint clearflag)
	{
		if (!handle.IsValid())
		{

			if (0 != index)
			{
				m_renderDevice->DisableRenderTarget(index);
				return;
			}
			handle = m_dummyRenderTargetHandle;
		}
		
		GPtr<RenderCommandType> rcType( (RenderCommandType*)handle.mRO );
		GPtr<RenderTarget> rt = rcType.downcast<RenderTarget>();
		n_assert(rt);

		if (handle != m_dummyRenderTargetHandle)
		{
			rt->SetMRTIndex(index);
			
		}
		rt->SetClearFlags(clearflag);
		m_renderDevice->SetRenderTarget(rt);
	}
	//--------------------------------------------------------------------------------
	void RenderSystem::_SetRenderTargetClearColor(RenderTargetHandle handle,const Math::float4& clearColor)
	{
		GPtr<RenderCommandType> rcType( (RenderCommandType*)handle.mRO );
		GPtr<RenderTarget> rt = rcType.downcast<RenderTarget>();
		n_assert(rt);
		
		rt->SetClearColor(clearColor);
	}

	//--------------------------------------------------------------------------------
	void RenderSystem::_ReSizeRenderTarget(RenderTargetHandle handle,const int& width,const int& height)
	{
		GPtr<RenderCommandType> rcType( (RenderCommandType*)handle.mRO );
		GPtr<RenderTarget> rt = rcType.downcast<RenderTarget>();
		n_assert(rt);
		rt->SetWidth(width);
		rt->SetHeight(height);
	}

	//--------------------------------------------------------------------------------
	void RenderSystem::CopyRenderTarget(RenderTargetHandle srcHandle, const Math::float4& srcRect, RenderTargetHandle desHandle, const Math::float4& desRect)
	{
		GPtr<RenderCommandType> srcRCType( (RenderCommandType*)srcHandle.mRO );
		GPtr<RenderTarget> srcRT = srcRCType.downcast<RenderTarget>();
		n_assert(srcRT);
		GPtr<RenderCommandType> desRCType( (RenderCommandType*)desHandle.mRO );
		GPtr<RenderTarget> desRT = desRCType.downcast<RenderTarget>();
		n_assert(desRT);
		desRT->CopyFrom(srcRect,srcRT,desRect);

	}

	void RenderSystem::_SetMultipleRenderTarget(MultipleRenderTargetHandle handle, bool resume)
	{
		GPtr<RenderCommandType> rcType( (RenderCommandType*)handle.mRO );
		GPtr<MultipleRenderTarget> mrt = rcType.downcast<MultipleRenderTarget>();

		m_renderDevice->SetMultipleRenderTarget(mrt, resume);
	}

	void RenderSystem::_ReSizeMultipleRenderTarget(MultipleRenderTargetHandle handle,const int& width,const int& height)
	{
		//TODO
		n_error("RenderSystem::_ReSizeMultipleRenderTarget() has not implemented!");
	}

	void RenderSystem::_SetTexture(TextureHandle handle,SizeT index)
	{
		n_assert(handle.IsValid());

		GPtr<RenderCommandType> rcType( (RenderCommandType*)handle.mRO );
		GPtr<Texture> tex = rcType.downcast<Texture>();
		n_assert(tex);

		n_assert( index >= 0 && index <= 12)

		tex->SetUnitIndex(index);
		m_renderDevice->SetTexture(tex);
	}

	void RenderSystem::_SetShaderProgram(GPUProgramHandle handle)
	{
		n_assert(handle.IsValid());

		GPtr<RenderCommandType> rcType( (RenderCommandType*)handle.mRO );
		GPtr<GPUProgram> program = rcType.downcast<GPUProgram>();
		n_assert(program);

		m_renderDevice->SetGPUProgram(program);
	}

	void RenderSystem::SetVertexShaderConstantVectorF(const int& reg, float* val, const int& vec4count)
	{
		m_renderDevice->SetVertexShaderConstantVectorF(reg,val,vec4count);
	}

	void RenderSystem::SetPixelShaderConstantVectorF(const int& reg, float* val, const int& vec4count)
	{
		m_renderDevice->SetPixelShaderConstantVectorF(reg,val,vec4count);
	}

	void RenderSystem::SetVertexShaderConstantFloat(const int& reg, float* val)
	{
		m_renderDevice->SetVertexShaderConstantFloat(reg, val);
	}

	void RenderSystem::SetPixelShaderConstantFloat(const int& reg, float* val)
	{
		m_renderDevice->SetPixelShaderConstantFloat(reg, val);
	}

	void RenderSystem::SetVertexShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount)
	{
		m_renderDevice->SetVertexShaderConstantMatrixF(reg, val, matrixCount);
	}

	void RenderSystem::SetPixelShaderConstantMatrixF(const int& reg, float* val, const int& matrixCount)
	{
		m_renderDevice->SetPixelShaderConstantMatrixF(reg, val, matrixCount);
	}

	void RenderSystem::_SetRenderState( GPtr<RenderStateDesc> rsObject)
	{
		n_assert(rsObject.isvalid())
			unsigned int flag = rsObject->GetUpdateFlag();
		n_assert(RenderStateDesc::eInvalidRenderState != flag)
			if (flag & RenderStateDesc::eRenderSamplerState)
			{
				m_renderDevice->SetTextureSamplerState(rsObject->GetSamplerState());
			}
			if (flag & RenderStateDesc::eRenderBlendState)
			{
				m_renderDevice->SetBlendState(rsObject->GetBlendState());
			}
			if (flag & RenderStateDesc::eRenderDepthAndStencilState)
			{
				m_renderDevice->SetDepthAndStencilState(rsObject->GetDepthAndStencilState());
			}
			if (flag & RenderStateDesc::eRenderRasterizerState)
			{
				m_renderDevice->SetRasterState(rsObject->GetRasterizerState());
			}

	}

	void RenderSystem::_RemoveResouce(const RenderResourceHandle& handle)
	{
		if ( handle.IsValid() )
		{
			bool bOK = _RemoveRenderHandle( handle );
			n_assert(bOK);
		}
	}

	void RenderSystem::_SetDisplayMode(const DisplayMode& mode)
	{

	}

	void RenderSystem::_SetViewPort(const int& x,const int& y,const int& width,const int& height,const float& minZ,const float& maxZ)
	{
		m_renderDevice->SetViewPort(x,y,width,height,minZ,maxZ);
	}
	//////////////////////////////////////////////////////////////////////////

	void RenderSystem::_FXSetClipPlane(const int& index,const Math::float4& plane)
	{
		m_renderDevice->FXSetClipPlane(index,plane);
	}

	//------------------------------------------------------------------------
	bool RenderSystem::_AddRenderHandle( const RenderBase::RenderResourceHandle& handle)
	{
		n_assert(handle);

		RenderResourceHandleSet::InsertResult res = m_renderHandles.insert(handle);

		if( res.second )
		{
			res.first->mRO->AddRef();	//	make a new insert
			return true;
		}
		else
		{
			return false;
		}
	}
	//------------------------------------------------------------------------
	bool RenderSystem::_RemoveRenderHandle( const RenderBase::RenderResourceHandle& handle)
	{
		n_assert(handle);
		RenderResourceHandleSet::type::iterator itor = m_renderHandles.find(handle);
		if ( itor != m_renderHandles.end() )
		{
			RenderResourceHandle oldHandle = *itor;
			n_assert(oldHandle);
			m_renderHandles.erase(itor);
			oldHandle.mRO->Release();
			return true;
		}
		else
		{
			return false;
		}
	}
	//------------------------------------------------------------------------
	bool RenderSystem::_HasRenderHandle(const RenderBase::RenderResourceHandle& handle)
	{
		return m_renderHandles.find( handle ) != m_renderHandles.end();
	}

	GPtr<RenderTarget>	RenderSystem::GetRenderTarget( RenderTargetHandle hdl )
	{
		if ( !hdl.IsValid() )
		{
			return NULL ; 
		}

		GPtr<RenderCommandType> rcType( (RenderCommandType*)hdl.mRO );
		GPtr<RenderTarget> rt = rcType.downcast<RenderTarget>();
		n_assert(rt);

		return rt ;
	}

	bool RenderSystem::OutPutRenderTarget( RenderTargetHandle hdl , const Util::String& path )
	{
		GPtr<RenderTarget> rt = GetRenderTarget( hdl ) ;
		if( !rt.isvalid() )
			return false ;

		return false;

#if RENDERDEVICE_D3D9
		Core::Rtti* pRtti = rt->GetRtti() ;

		if( *pRtti != RenderTargetD3D9::RTTI )
			return false ;
		GPtr<RenderTargetD3D9>	dx9rt = rt.downcast<RenderTargetD3D9>() ;

		if( !dx9rt.isvalid() )
			return false ;

		IDirect3DSurface9* sfs = dx9rt->GetD3DRT() ;

		HRESULT res = D3DXSaveSurfaceToFile( path.Get() , D3DXIFF_TGA , sfs , NULL , NULL ) ;

		return ( res == S_OK ) ;
#endif

	}

	void RenderSystem::_OnDeviceLost()
	{
		RenderBase::RenderSystem::RenderResourceHandleSet::type &handles = RenderSystem::Instance()->GetRenderResourceHandles();
		RenderBase::RenderSystem::RenderResourceHandleSet::type::iterator it = handles.begin();
		while(it != handles.end())
		{
			GPtr<RenderCommandType> rcType( (RenderCommandType*)(*it).mRO );

			rcType->OnDeviceLost();

			++it;
		}
	}

	void RenderSystem::_OnDeviceReset()
	{
		RenderBase::RenderSystem::RenderResourceHandleSet::type &handles = RenderSystem::Instance()->GetRenderResourceHandles();
		RenderBase::RenderSystem::RenderResourceHandleSet::type::iterator it = handles.begin();
		while(it != handles.end())
		{
			GPtr<RenderCommandType> rcType( (RenderCommandType*)(*it).mRO );
			rcType->OnDeviceReset();
			++it;
		}

	}

	void RenderSystem::SetDeviceLostCallBack(deviceLostCallBackFunc func)
	{
		m_renderDevice->SetDeviceLostCallBack(func);
	}


	void RenderSystem::_OnWindowChanged()
	{
#if RENDERDEVICE_D3D9
		// part this operator
		//m_renderDevice.cast<RenderDeviceD3D9>()->SetDeviceLost();
#endif		
	}

	RenderWindow* RenderSystem::CreateViewPortWnd( WindHandle hWnd )
	{
#if RENDERDEVICE_D3D9
		return m_renderDevice.cast<RenderDeviceD3D9>()->CreateViewPortWnd( hWnd );
#endif

#if RENDERDEVICE_OPENGLES

		return m_renderDevice.cast<RenderDeviceGLES>()->CreateViewPortWnd(hWnd);
#endif

#if RENDERDEVICE_NULL
		return m_renderDevice.cast<RenderDeviceNull>()->CreateViewPortWnd(hWnd);
#endif
		return NULL;
	}


	void RenderSystem::DestroyViewPortWnd(RenderWindow* view)
	{
#if RENDERDEVICE_D3D9
		m_renderDevice.cast<RenderDeviceD3D9>()->DestroyViewPortWnd( static_cast<D3D9Window*>(view) );
#endif

#if RENDERDEVICE_OPENGLES

		m_renderDevice.cast<RenderDeviceGLES>()->DestroyViewPortWnd(static_cast<GLESWindow*>(view));
#endif
	}

	void RenderSystem::OnDeviceLost()
	{
		m_renderDevice->OnDeviceLost();
		_OnDeviceLost();
	}

	bool RenderSystem::CheckReset()
	{
		return m_renderDevice->CheckReset();
	}

	void RenderSystem::OnDeviceReset()
	{
		m_renderDevice->OnDeviceReset();
		_OnDeviceReset();
	}

	
}
