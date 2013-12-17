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
#include "graphicsystem/Vision/RenderScene.h"
#include "Camera.h"
#include "GraphicSystem.h"
#include "materialmaker/parser/GenesisShaderParser.h"
#include "RenderPipeline/RenderPipelineManager.h"
#include "foundation/util/stl.h"
#include "graphicsystem/Renderable/RenderObject.h"

namespace Graphic
{

	_simple_scene::_simple_scene()
	{

	}

	_simple_scene::~_simple_scene()
	{

	}

	void _simple_scene::_UpdateVisEntity(const GPtr<Vis::VisEntity>& visEnt )
	{

	}
	void _simple_scene::_AddRenderObject(RenderObject* obj)
	{

	}
	void _simple_scene::_RemoveRenderObject(RenderObject* obj)
	{

	}

	// internal call
	//[zhongdaohuan]
	//这个队列里的的东西将不会产生裁剪而直接进入渲染队列。
	void _simple_scene::_AddRenderObjectNotCull(RenderObject* obj)
	{
		n_assert(obj);
		n_assert(!obj->_GetVisEnt().isvalid());
		m_notCullRenderObjects.Append(obj);	
	}
	void _simple_scene::_RemoveRenderObjectNotCull(RenderObject* obj)
	{
		n_assert(obj);
		n_assert(!obj->_GetVisEnt().isvalid());
		IndexT i = m_notCullRenderObjects.FindIndex(obj); 
		if( InvalidIndex != i )
		{
			m_notCullRenderObjects.EraseIndex(i);
		}
	}


	__ImplementClass(Camera,'CAGS',GraphicObject)
		/**
		*/
		const float Camera::PerspNormalFov = n_deg2rad(45.0f);
	float Camera::S_Camera_Far = 1000;	//	hack code for demo shadow map 
	Camera::Camera()
		:m_owner(NULL)
		,m_listener(NULL)
		,m_renderScene(NULL)
		,m_targetWindow(NULL)
		,m_bUseWindowSize(false)
		,m_bRenderDepthMap(false)
		,m_bRenderLightLitMap(false)
		,m_bRenderCustom(false)
		,m_bRenderNormal(false)
		,m_bUseViewPort(false)
		,m_bRenderSurface(false)
		,m_viewType(VT_persp)
		,m_renderOrder(eCO_InvalidCamera)
		,m_drawMode(DrawTextured)
		,m_renderMode(ForwardMode)
		,m_cullMask(eRLCameraRenderAll)
		,m_bUseBeforeDrawEvent(true)
		,m_quadRenderable(NULL)
		,m_antiAliasQuality(RenderBase::AntiAliasQuality::None)
		,m_bUseCallBack(true)
	{
		const RenderBase::DisplayMode& dm = GraphicSystem::Instance()->GetMainViewPortWindow()->GetDisplayMode();
		m_setting.SetupPerspectiveFovRH(Graphic::Camera::PerspNormalFov, float(dm.GetWidth())/float(dm.GetHeight()), 1.0f, S_Camera_Far);// 0.1f
		m_viewPort.width = dm.GetWidth();
		m_viewPort.height = dm.GetHeight();
		m_viewPort.x = dm.GetXPos();
		m_viewPort.y = dm.GetYPos();
		m_viewPort.minZ = 0.f;
		m_viewPort.maxZ = 1.f;
		m_renderPipelineManager = RenderPipelineManager::Create();
		m_renderPipelineManager->m_pipelineContext.m_camera = this;
		m_renderPipelineManager->m_pipelineContext.m_renderDatas.SetUseFor(RenderDataCollection::Normal);

		m_transform = matrix44::lookatrh(float4(1.27f, 1.2f, -800.4f, 1.f),float4(0.f, 0.f, 0.f, 1.f),float4(0.f,1.f,0.f,0.f));
		m_transform = matrix44::inverse(m_transform);
		OnTransformChanged();

		m_quadRenderable = QuadRenderable::Create();
		m_quadRenderable->Setup(dm.GetWidth(),dm.GetWidth());
	}

	//------------------------------------------------------------------------------
	/**
	*/
	Camera::~Camera()
	{
		Discard();
		m_quadRenderable->Discard();
		m_quadRenderable = NULL;
	}

	void Camera::Discard()
	{
		if(m_listener)
		{
			m_listener->Discard(this);
		}

		if (m_renderPipelineManager.isvalid())
		{
			m_renderPipelineManager->Close();
			m_renderPipelineManager = 0;
			SetRenderMode(ForwardMode);
			SetDrawType(DrawTextured);
		}

		if (m_depthMap.isvalid())
		{
			m_depthMap = 0;
		}

		if (m_backBuffer.isvalid())
		{
			m_backBuffer = 0;
		}

		if (m_renderToTexture.isvalid())
		{
			m_renderToTexture = 0;
		}
		if (m_swapTexture.isvalid())
		{
			m_swapTexture = 0;
		}
		if (m_lightLitTexture.isvalid())
		{
			m_lightLitTexture = 0;
		}
		if (m_lightLitMaterial.isvalid())
		{
			m_lightLitMaterial = 0;
		}

		if (m_deferredNormalMap.isvalid())
		{
			m_deferredNormalMap = 0;
		}

		if (m_deferredLightMap)
		{
			m_deferredLightMap = 0;
		}
		if (m_renderOrder == eCO_Main || m_renderOrder == eCO_PuppetMain)
		{
			unregistWindowEvent();
		}
	}

	void Camera::Setup()
	{
		if ( !m_renderPipelineManager )
		{
			m_renderPipelineManager = RenderPipelineManager::Create();
		}

		if (m_renderOrder == eCO_Main)
		{
			//			SetRenderMode(DeferredMode);
			unregistWindowEvent();
			ViewPortWindow* targetWindow = (NULL == m_targetWindow) ? GraphicSystem::Instance()->GetMainViewPortWindow().get() : m_targetWindow;
			m_bUseWindowSize = true;
			m_backBuffer = RenderToTexture::Create();
			const RenderBase::DisplayMode& dm = targetWindow->GetDisplayMode();
			m_backBuffer->Setup(dm.GetWidth(),dm.GetHeight(),
				RenderBase::PixelFormat::X8R8G8B8,
				RenderBase::RenderTarget::ClearAll, Math::float4(0.0f,0.0f,1.0f,1.f), 
				true,1.f, RenderBase::AntiAliasQuality::None,Math::rectangle<int>(0,0,0,0),true);

			m_renderToTexture = RenderToTexture::Create();
			if (DeferredMode == m_renderMode)
			{
				m_renderToTexture->Setup(dm.GetWidth(),dm.GetHeight(),
					RenderBase::PixelFormat::A8R8G8B8, 
					RenderBase::RenderTarget::ClearAll, Math::float4(0.2f,0.2f,0.2f,1.f), 
					true,1.f, RenderBase::AntiAliasQuality::None);//RenderBase::AntiAliasQuality::High
			}
			else
			{
				m_renderToTexture->Setup(dm.GetWidth(),dm.GetHeight(),
					RenderBase::PixelFormat::A8R8G8B8, 
					RenderBase::RenderTarget::ClearAll, Math::float4(0.2f,0.2f,0.2f,1.f), 
					true, 1.f, m_antiAliasQuality);
			}


			Material::GetGlobalMaterialParams()->SetVectorParam(eGShaderVecScreenSize,float4(float(dm.GetWidth()),float(dm.GetHeight()),float(0.5/dm.GetWidth()),float(0.5/dm.GetHeight())));

			m_swapTexture = RenderToTexture::Create();
			m_swapTexture->Setup(dm.GetWidth(),dm.GetHeight(),RenderBase::PixelFormat::A8R8G8B8, RenderBase::RenderTarget::ClearAll, Math::float4(0.f,0.f,0.f,1.f),  false,1.f,RenderBase::AntiAliasQuality::None);


			m_viewPort.width = dm.GetWidth();
			m_viewPort.height = dm.GetHeight();
			m_viewPort.x = dm.GetXPos();
			m_viewPort.y = dm.GetYPos();
			m_viewPort.minZ = 0.f;
			m_viewPort.maxZ = 1.f;
			m_bUseViewPort = true;

			m_bRenderNormal = true;

			setupDepthMap();

#if __WIN32__ && RENDERDEVICE_D3D9
			m_lightLitTexture = RenderToTexture::Create();

			m_lightLitTexture->Setup(dm.GetWidth(),dm.GetHeight(),RenderBase::PixelFormat::R16F,//A8R8G8B8/*R16F*/, 
				RenderBase::RenderTarget::ClearAll, Math::float4(1.f,1.f,1.f,1.f), 
				true,1.f);

			Util::StringAtom fileName("sys:Forward_lightLitMap.shader");
			m_lightLitMaterial = GenesisMaterialMaker::MakeFromShader( fileName );

			m_bRenderLightLitMap = true;
#endif			
			registWindowEvent();

		}
		else if (m_renderOrder == eCO_Shadow)
		{
			m_bRenderCustom = true;
			m_bRenderNormal = false;
		}
		else
		{
			n_error("Custom RenderMode is not implemented right now!");
		}
		//else if (m_renderOrder == eCO_Reflection)
		//{
		//	n_error("Reflection Camera is not implemented right now!");
		//}
		//else if ( m_renderOrder > eCO_CustomBeforeMain && m_renderOrder < eCO_Main)
		//{
		//	n_error("customized Cameras,not implemented at this moment!");
		//}


		if (DeferredMode == m_renderMode)
		{
			SetRenderDepth(true);
			setupDeferred();
			m_renderPipelineManager->SetupDeferred();
		}


	}

	void Camera::RenderBegin()
	{
		if (m_listener)
		{
			m_listener->RenderBegin(this);
		}
	}

	void Camera::RenderEnd()
	{
		if (m_listener)
		{
			m_listener->RenderEnd(this);
		}
	}

	GPtr<Vis::VisQuery> Camera::Cull() const
	{
		n_assert(m_renderScene);
		return m_renderScene->Cull(*this);
	}

	void Camera::SetTargetWindow(ViewPortWindow* target)
	{
		if (m_targetWindow != target)
		{
			unregistWindowEvent();
			m_targetWindow = target;
			registWindowEvent();
		}
	}

	// set custom pipeline
	bool Camera::SetCustomPipeline(const GPtr<RenderPipeline>& customPipeline)
	{
		bool isSucceed = false;

		if ( customPipeline.isvalid() )
		{
			m_renderPipelineManager->SetCustomPipeline(customPipeline);
			m_renderMode = CustomedMode;
			isSucceed = true;
		}
		return isSucceed;
	}

	IRenderScene* Camera::GetCameraScene()
	{
		return &m_cameraScene;
	}

	void Camera::registWindowEvent()
	{
		if (m_renderOrder == eCO_Main)
		{
			ViewPortWindow* targetWindow = (NULL == m_targetWindow) ? GraphicSystem::Instance()->GetMainViewPortWindow().get() : m_targetWindow;
			targetWindow->eventViewportChange += Delegates::newDelegate(this, &Camera::onTargetSizeChange); 
		}
	}

	void Camera::unregistWindowEvent()
	{
		if (m_renderOrder == eCO_Main || m_renderOrder == eCO_PuppetMain)
		{
			ViewPortWindow* targetWindow = (NULL == m_targetWindow) ? GraphicSystem::Instance()->GetMainViewPortWindow().get() : m_targetWindow;
			targetWindow->eventViewportChange -= Delegates::newDelegate(this, &Camera::onTargetSizeChange); 
		}
	}


	void Camera::setupDepthMap()
	{
		if (m_renderOrder == eCO_Main)
		{
			if (m_depthMap)
			{
				return;
			}
			m_depthMap = RenderToTexture::Create();
			m_depthMap->SetShareDepthStencilRT(m_renderToTexture->GetRenderTarget());
#if __WIN32__ && RENDERDEVICE_D3D9
			m_depthMap->Setup(m_viewPort.width,m_viewPort.height,RenderBase::PixelFormat::R32F, 
				RenderBase::RenderTarget::ClearAll, Math::float4(1.f,1.f,1.f,1.f), 
				true,1.0f, RenderBase::AntiAliasQuality::None);
#elif __ANDROID__	|| RENDERDEVICE_OPENGLES
			m_depthMap->Setup(m_viewPort.width,m_viewPort.height,RenderBase::PixelFormat::A8R8G8B8, 
				RenderBase::RenderTarget::ClearAll, Math::float4(1.f,1.f,1.f,1.f), 
				true,1.0f, RenderBase::AntiAliasQuality::None);
#endif
			
		}
	}

	void Camera::setupDeferred()
	{
		const RenderBase::DisplayMode& dm = GraphicSystem::Instance()->GetMainViewPortWindow()->GetDisplayMode();

		m_deferredNormalMap = RenderToTexture::Create();
		m_deferredNormalMap->SetShareDepthStencilRT(m_renderToTexture->GetRenderTarget());
		m_deferredNormalMap->Setup(dm.GetWidth(),dm.GetHeight(),RenderBase::PixelFormat::G16R16F, 
			RenderBase::RenderTarget::ClearAll, Math::float4(0.0f,0.0f,0.0f,0.0f), 
			true,1.f);
		m_deferredParamMap = RenderToTexture::Create();//临时
		m_deferredParamMap->SetShareDepthStencilRT(m_renderToTexture->GetRenderTarget());
		m_deferredParamMap->Setup(dm.GetWidth(),dm.GetHeight(),RenderBase::PixelFormat::G16R16F,
			RenderBase::RenderTarget::ClearAll, Math::float4(0.f,0.f,0.f,0.f), 
			true,1.f);

		Material::GetGlobalMaterialParams()->SetTextureParam(eGShaderTexDfNormalMap, "g_DfNormalMap", m_deferredNormalMap->GetTextureHandle());
		Material::GetGlobalMaterialParams()->SetTextureParam(eGShaderTexDfDepthMap, "g_DfDepthMap", m_depthMap->GetTextureHandle());//m_deferredDepthMap
		Material::GetGlobalMaterialParams()->SetTextureParam(eGShaderTexDfParamMap, "g_DfParamMap", m_deferredParamMap->GetTextureHandle());

		m_deferredLightMap = RenderToTexture::Create();
		m_deferredLightMap->Setup(dm.GetWidth(),dm.GetHeight(),RenderBase::PixelFormat::A16B16G16R16F, 
			RenderBase::RenderTarget::ClearAll, Math::float4(0.0f,0.0f,0.0f,0.0f), 
			false, 1.f);
		Material::GetGlobalMaterialParams()->SetTextureParam(eGShaderTexDfLightMap0, "g_DfAndSpecMap0",m_deferredLightMap->GetTextureHandle());
	}
	void Camera::onTargetSizeChange(ViewPortWindow* sender)
	{
		n_assert( (NULL == m_targetWindow && GraphicSystem::Instance()->GetMainViewPortWindow().get()) || ( m_targetWindow == sender) );
		OnResizeWindow(sender->GetDisplayMode());
	}

	//------------------------------------------------------------------------------
	/**
	Set new the camera settings. This updates the internal matrices.
	*/
	void Camera::SetCameraSetting(const CameraSetting& camSetting)
	{
		m_setting = camSetting;
		m_setting.UpdateViewMatrix(matrix44::inverse(m_transform));

	}

	//------------------------------------------------------------------------------
	/**
	We need to keep track of modifications of the transformation matrix.
	*/
	void Camera::OnTransformChanged()
	{
		// keep track of view matrix
		m_setting.UpdateViewMatrix(matrix44::inverse(m_transform));
	}

	void Camera::SetDebugFrustum(bool enable, const float4& color)
	{

	}
	/// setup a perspective view volume
	void Camera::SetPerspectiveFovRH(float fov, float aspect, float zNear, float zFar)
	{

		m_viewType = VT_persp;
		m_setting.SetupPerspectiveFovRH(fov, aspect, zNear, zFar);
	}
	/// setup a perspective oblique view volume with a clipplane
	void Camera::SetPerspectiveFovRH(float fov, float aspect, float zNear, float zFar, Math::float4 clipPlane, bool reflection)
	{
		m_viewType = VT_persp;
		m_setting.SetupPerspectiveFovRH(fov, aspect, zNear, zFar, clipPlane, reflection);
	}
	/// setup an orthogonal projection transform
	void Camera::SetOrthogonal(float w, float h, float zNear, float zFar)
	{
		m_viewType = VT_ortho;
		m_setting.SetupOrthogonal((float)w, (float)h, zNear, zFar);
	}

	void Camera::SetProj(ViewType vt, float fovOrHeight, float zNear, float zFar)
	{
		ViewPortWindow* view = NULL;
		if (NULL == m_targetWindow)
		{
			const GPtr<ViewPortWindow>& p = GraphicSystem::Instance()->GetMainViewPortWindow();
			view = p.get_unsafe();
		}
		else
		{
			view = m_targetWindow;
		}
		//ViewPortWindow* view = (NULL == m_targetWindow) ? GraphicSystem::Instance()->GetMainViewPortWindow() : m_targetWindow;

		const RenderBase::DisplayMode& mode = view->GetDisplayMode();
		m_viewType = vt;
		if (VT_persp == m_viewType)
		{
			float aspect = (float)(mode.GetWidth()) / (float)mode.GetHeight();
			m_setting.SetupPerspectiveFovRH(fovOrHeight , aspect , zNear , zFar) ;
		}
		else if (VT_ortho == m_viewType)
		{
			float width = fovOrHeight * float(mode.GetWidth()) / float(mode.GetHeight());
			m_setting.SetupOrthogonal((float)width, (float)fovOrHeight, zNear, zFar);
		}

	}

	void Camera::CopyParam(const GPtr<Camera>& source)
	{
		Graphic::CameraSetting cs = source->GetCameraSetting();

		SetCameraSetting(cs);
		m_debugColor = source->m_debugColor;

		m_renderOrder = source->m_renderOrder;
		m_cullMask = source->m_cullMask;

		m_drawMode = source->m_drawMode;

		m_viewType = source->m_viewType;
		m_viewPort = source->m_viewPort;
		m_bUseViewPort = source->m_bUseViewPort;

		m_renderMode = source->m_renderMode;

		m_bRenderDepthMap = source->m_bRenderDepthMap;

		if (source->m_listener)
		{
			source->m_listener->CopyParam(this , source.get());
		}
		if(m_listener)
		{
			m_listener->CopyParam(this , source.get());
		}
	}

	void Camera::OnResizeWindow(const RenderBase::DisplayMode& dm)
	{
		m_quadRenderable->Discard();
		m_quadRenderable->Setup(dm.GetWidth(),dm.GetHeight());
		m_viewPort.width = dm.GetWidth();
		m_viewPort.height = dm.GetHeight();
		m_viewPort.x = dm.GetXPos();
		m_viewPort.y = dm.GetYPos();
		m_viewPort.minZ = 0.f;
		m_viewPort.maxZ = 1.f;
		if (VT_persp == m_viewType)
		{
			float aspect = (float)(dm.GetWidth()) / (float)dm.GetHeight();
			m_setting.SetupPerspectiveFovRH(m_setting.GetFov(), aspect, m_setting.GetZNear(), m_setting.GetZFar()) ;
		}
		else if (VT_ortho == m_viewType)
		{
			float width = m_setting.GetFarHeight() * float(dm.GetWidth()) / float(dm.GetHeight());
			m_setting.SetupOrthogonal((float)width, (float)m_setting.GetFarHeight(), m_setting.GetZNear(), m_setting.GetZFar());
		}

		//m_setting.SetupPerspectiveFovRH(m_setting.GetFov(), float(m_viewPort.width)/float(m_viewPort.height),m_setting.GetZNear(),m_setting.GetZFar());
		//todo: change RTs size
		if (m_renderOrder == eCO_Main)
		{
			m_backBuffer->Setup(dm.GetWidth(),dm.GetHeight(),
				RenderBase::PixelFormat::X8R8G8B8,
				RenderBase::RenderTarget::ClearAll, Math::float4(0.0f,0.0f,1.0f,1.f), 
				true,1.f, m_antiAliasQuality, Math::rectangle<int>(0,0,0,0), true);

			m_renderToTexture->Setup( dm.GetWidth(),dm.GetHeight(),
				RenderBase::PixelFormat::A8R8G8B8, 
				RenderBase::RenderTarget::ClearAll, Math::float4(0.2f,0.2f,0.2f,1.f), 
				true,1.f, m_antiAliasQuality );

			Material::GetGlobalMaterialParams()->SetTextureParam(eGShaderTexMainBuffer, "g_MainBuffer",m_renderToTexture->GetTextureHandle());

			m_swapTexture->Setup(dm.GetWidth(),dm.GetHeight(),RenderBase::PixelFormat::A8R8G8B8, RenderBase::RenderTarget::ClearAll, Math::float4(0.f,0.f,0.f,1.f),  false,1.f,RenderBase::AntiAliasQuality::None);
			Material::GetGlobalMaterialParams()->SetTextureParam(eGShaderTexSwapBuffer, "g_SwapBuffer",m_swapTexture->GetTextureHandle());

			m_bRenderNormal = true;
			m_bRenderLightLitMap = true;

			// 在获取新的深度缓冲区的时候，需要将旧的缓冲区先释放掉
			if (m_depthMap.isvalid())
			{
				m_depthMap = 0;
				m_depthMap = RenderToTexture::Create();
				m_depthMap->SetShareDepthStencilRT(m_renderToTexture->GetRenderTarget());
			}

			m_depthMap->Setup(dm.GetWidth(),dm.GetHeight(),RenderBase::PixelFormat::R32F, 
				RenderBase::RenderTarget::ClearAll, Math::float4(1.f,1.f,1.f,1.f), 
				true,1.0f, RenderBase::AntiAliasQuality::None, Math::rectangle<int>(0,0,0,0));

			if (m_bRenderLightLitMap)
			{
				m_lightLitTexture->Setup(dm.GetWidth(),dm.GetHeight(),RenderBase::PixelFormat::R16F, 
					RenderBase::RenderTarget::ClearAll, Math::float4(0.f,0.f,0.f,1.f), 
					true,1.f);
			}
			else
			{
				m_lightLitTexture->Setup(1,1,RenderBase::PixelFormat::X8R8G8B8, 
					RenderBase::RenderTarget::ClearAll, Math::float4(1.0f,1.0f,1.0f,1.0f), 
					true,1.f);
			}

		}
	}

	void Camera::OnDeviceReset(const RenderBase::DisplayMode& dm)
	{
		int t_width = dm.GetWidth();
		int t_height = dm.GetHeight();

		GPtr<RenderToTexture> rt = GetRenderToTexture();
		rt->ChangeSize(t_width,t_height);
		rt = GetSwapTexture();
		rt->ChangeSize(t_width,t_height);
		if (HasDepthMap())
		{
			rt = GetDepthMap();
			rt->ChangeSize(t_width,t_height);
		}
		if (HasLightLitMap())
		{
			rt = GetLightLitTexture();
			rt->ChangeSize(t_width,t_height);
		}
		m_quadRenderable->Discard();
		m_quadRenderable->Setup(dm.GetWidth(), dm.GetHeight());
	}


	void Camera::SetAntiAliasQuality( RenderBase::AntiAliasQuality::Code qua )
	{
		m_antiAliasQuality = qua;
		ViewPortWindow* targetWindow = (NULL == m_targetWindow) ? GraphicSystem::Instance()->GetMainViewPortWindow().get() : m_targetWindow;
		const RenderBase::DisplayMode& dm = targetWindow->GetDisplayMode();

		if(m_renderToTexture.isvalid())
		{
			m_renderToTexture->Setup( dm.GetWidth(),dm.GetHeight(),
				RenderBase::PixelFormat::A8R8G8B8, 
				RenderBase::RenderTarget::ClearAll, Math::float4(0.2f,0.2f,0.2f,1.f), 
				true,1.f, m_antiAliasQuality );
		}
	}

	void Camera::SetViewType(ViewType type, float fovOrHeight)
	{
		SetProj(type, fovOrHeight, m_setting.GetZNear() , m_setting.GetZFar());
	}

	void Camera::SetLightLitMap(const GPtr<RenderToTexture>& rtt)
	{
		m_lightLitTexture = rtt;
		Material::GetGlobalMaterialParams()->SetTextureParam(eGShaderTexLightLitMap, "g_LightLitMap",m_lightLitTexture->GetTextureHandle());
	}

}
