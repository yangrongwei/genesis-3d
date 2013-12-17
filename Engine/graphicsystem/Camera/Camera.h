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
#ifndef CAMERA_H_
#define CAMERA_H_

#include "RenderSystem/RenderSystem.h"
#include "Camera/CameraSetting.h"
#include "base/GraphicObject.h"
#include "Light/Light.h"
#include "base/RenderToTexture.h"
#include "util/stl.h"
#include "base/ImageFilters.h"
#include "graphicsystem/Material/Material.h"
#include "graphicsystem/Vision/RenderScene.h"
#include "Camera/RenderPipeline/RenderPipeline.h"
#include "foundation/util/scriptbind.h"

namespace Vis
{
	class VisQuery;
}

namespace Graphic
{
	class RenderPipelineManager;
	class Light;
	class RenderObject;
	class ViewPortWindow;
	class RenderScene;

	class Camera;
	class CameraListener
	{
	public:
		virtual ~CameraListener(){};
		virtual void RenderBegin(Camera* sender) = 0;
		virtual void RenderEnd(Camera* sender) = 0;
		virtual void CopyParam(Camera* sender,Camera* source) = 0;
		virtual void Discard(Camera* sender) = 0;
	};

	class _simple_scene : public IRenderScene
	{
	public:
		_simple_scene();
		virtual ~_simple_scene();
		// internal call
		virtual void _UpdateVisEntity(const GPtr<Vis::VisEntity>& visEnt );
		virtual void _AddRenderObject(RenderObject* obj);
		virtual void _RemoveRenderObject(RenderObject* obj);

		// internal call
		virtual void _AddRenderObjectNotCull(RenderObject* obj);
		virtual void _RemoveRenderObjectNotCull(RenderObject* obj);

		const Util::Array<RenderObject*>& _GetNotCullRenderObjects() const;
	private:
		Util::Array<RenderObject*>	m_notCullRenderObjects;
	};

	inline const Util::Array<RenderObject*>& _simple_scene::_GetNotCullRenderObjects() const
	{
		return m_notCullRenderObjects;
	}

	class Camera : public GraphicObject
	{
		__DeclareSubClass(Camera,GraphicObject)
			__ScriptBind
	public:

		static float S_Camera_Far;	//	hack code for demo shadow map 
		enum RenderMode
		{
			ForwardMode,
			DeferredMode,
			CustomedMode
		};

		struct ViewPort
		{
			SizeT x;
			SizeT y;
			SizeT width;
			SizeT height;
			float minZ;
			float maxZ;
		};

		enum DrawType
		{
			DrawTextured				= 0,
			DrawWire					= 1,
			DrawTexturedWire			= 2,
			DrawRenderPaths				= 3,
		};

		enum ViewType
		{
			VT_ortho,//正交投影
			VT_persp//透视投影
		};
		static const float PerspNormalFov;
		Camera();
		virtual ~Camera();

		virtual void Setup();

		virtual void Discard();

		void RenderBegin();

		void RenderEnd();

		GPtr<Vis::VisQuery> Cull() const;
		RenderScene* GetRenderScene() const;

		/// set render order
		void SetCameraOrder(CameraOrder order);
		/// get render order
		const CameraOrder& GetCameraOrder() const;		

		/// set draw mode
		void SetDrawType(DrawType mode);
		/// get drawmode
		const DrawType& GetDrawType() const;

		ViewType GetViewType() const;

		void SetViewType(ViewType type, float fovOrHeight);
		/// set
		void SetRenderMode(RenderMode mode);
		/// get
		RenderMode GetRenderMode() const;

		/// set new camera settings
		void SetCameraSetting(const CameraSetting& camSetting);
		/// get camera settings
		const CameraSetting& GetCameraSetting() const;

		/// get projection matrix
		const Math::matrix44& GetProjTransform() const;
		/// get view transform (inverse transform)
		const Math::matrix44& GetViewTransform() const;
		/// get view projection matrix 
		const Math::matrix44& GetViewProjTransform() const;
		/// get view frustum
		const Math::frustum& GetViewFrustum() const;

		void SetProj(ViewType vt, float fovOrHeight, float zNear, float zFar);

		/// setup a perspective view volume
		void SetPerspectiveFovRH(float fov, float aspect, float zNear, float zFar);
		/// setup a perspective oblique view volume with a clipplane
		void SetPerspectiveFovRH(float fov, float aspect, float zNear, float zFar, Math::float4 clipPlane, bool reflection = false);
		/// setup an orthogonal projection transform
		void SetOrthogonal(float w, float h, float zNear, float zFar);

		/// set shadow distence
		void SetShadowDistence(float shadowDis);
		/// get shadow distence
		const float GetShadowDistence() const;

		///
		GPtr<RenderPipelineManager>& GetRenderPipelineManager();

		ImageFilterManager& GetPostEffectFilters();
		///
		void OnTransformChanged();

		const RenderBase::RenderResourceHandle& GetBackBuffer() const;

		/// set rendertotexture
		void SetRenderToTexture(const GPtr<RenderToTexture>& rtt);
		/// get rendertotexture
		const GPtr<RenderToTexture>& GetRenderToTexture() const;	
		/// set swap texture
		void SetSwapTexture(const GPtr<RenderToTexture>& rtt);
		/// get swap texture
		const GPtr<RenderToTexture>& GetSwapTexture() const;
		///set lightlit map
		void SetLightLitMap(const GPtr<RenderToTexture>& rtt);
		/// render depth map
		bool HasDepthMap() const;
		/// get depth map
		const GPtr<RenderToTexture>& GetDepthMap() const;

		const GPtr<RenderToTexture>& GetDeferredNormalMap() const;

		const GPtr<RenderToTexture>& GetDeferredParamMap() const;

		const GPtr<RenderToTexture>& GetDeferredLightMap() const;

		/// render light lit map
		bool HasLightLitMap() const;
		/// get light lit map
		const GPtr<RenderToTexture>& GetLightLitTexture() const;
		/// get light lit material
		const GPtr<Material>& GetLightLitMaterial() const;
		/// get shadow blur material
		const GPtr<Material>& GetShadowBlurMaterial() const;

		/// rendered with custom material
		const bool IsRenderCustom() const;

		/// need set view port
		const bool UseViewport() const;

		/// set viewport
		void SetViewport(const ViewPort& vp);
		/// get viewport
		const ViewPort& GetViewport() const;

		void SetTargetWindow(ViewPortWindow* target);

		ViewPortWindow* GetTargetWindow() const;
		/// get custom material
		const GPtr<Material>& GetCustomMaterial() const;
		/// get wire material
		//const GPtr<Material>& GetWireMaterial() const;
		/// set wire color
		//void SetWireColor(const float4& color) const;

		const bool IsRenderNormal() const;

		void SetDebugFrustum(bool enable, const Math::float4& color);

		/// get debug color
		const Math::float4& GetDebugColor() const;
		/// set debug color
		void SetDebugColor(const Math::float4& color);

		/// get cull mask
		const RenderLayer& GetCullMask() const;
		/// set cull mask
		void SetCullMask(const RenderLayer& rl);

		void SetRenderSurface(bool bRenderSurface);

		const bool IsRenderSurface() const;

		void SetRenderNormal(bool bNormal);

		void SetRenderDepth(bool bDepth);

		void SetUseCustomMaterial(bool bUse);

		void SetCustomMaterial(const GPtr<Material>& pMat);

		void SetClipPlane(const Math::float4& plane);

		void SetUseWindowSize(bool bWinSize);

		const bool IsUsingWindowSize() const;

		void OnResizeWindow(const RenderBase::DisplayMode& dm);

		void OnDeviceReset(const RenderBase::DisplayMode& dm);

		const Math::float4& GetClipPlane() const;

		// set custom pipeline
		bool SetCustomPipeline(const GPtr<RenderPipeline>& customPipeline);

		void CopyParam(const GPtr<Camera>& source);//不包括rendertarget
		void SetListener(CameraListener* listener);

		void SetRenderScene(RenderScene* scene);

		//[zhongdaohuan]
		//这个队列里的的东西将不会产生裁剪而直接进入渲染队列。
		IRenderScene* GetCameraScene();
		const Util::Array<RenderObject*>& GetNotCullRenderObjects() const;

		void SetOwner(void* owner);

		void* GetOwner() const;

		void SetBeforeDrawEvent(bool enable);

		bool IsUseBeforeDrawEvent() const;

		const GPtr<QuadRenderable>&  GetQuadRenderable() const;

		//临时处理让摄影机不参与shadow map的渲染
		void SetRenderLightLitMap(bool enable);

		void SetAntiAliasQuality(RenderBase::AntiAliasQuality::Code qua);

		RenderBase::AntiAliasQuality::Code GetAntiAliasQuality();

		void SetUseCallBack(bool bUse);

		bool GetUseCallBack();
	private: 

		void registWindowEvent();

		void unregistWindowEvent();

		void setupDeferred();
		void onTargetSizeChange(ViewPortWindow* sender);
		void setupDepthMap();

		void* m_owner;

		GPtr<QuadRenderable>  m_quadRenderable;				//use for blit image,if we use same quad,dx has a 0.5 

		GPtr<RenderPipelineManager> m_renderPipelineManager;

		GPtr<RenderToTexture> m_renderToTexture;
		GPtr<RenderToTexture> m_lightLitTexture;
		GPtr<RenderToTexture> m_swapTexture;
		GPtr<RenderToTexture> m_depthMap;
		GPtr<RenderToTexture> m_backBuffer;
		GPtr<Material>        m_lightLitMaterial;
		GPtr<Material>		 m_customMaterial;
		// deferred lighting 
		GPtr<RenderToTexture> m_deferredNormalMap;
		GPtr<RenderToTexture> m_deferredParamMap;
		GPtr<RenderToTexture> m_deferredLightMap;

		RenderScene*				m_renderScene;
		ViewPortWindow*		m_targetWindow;
		CameraListener*		m_listener;

		_simple_scene		m_cameraScene;
		CameraSetting				m_setting;
		ImageFilterManager				m_postEffects;

		Math::float4				m_debugColor;
		Math::float4				m_ClipPlane;

		CameraOrder		m_renderOrder;
		RenderLayer		m_cullMask;
		DrawType		m_drawMode;
		ViewType		m_viewType;
		ViewPort		m_viewPort;
		RenderMode		m_renderMode;
		RenderBase::AntiAliasQuality::Code m_antiAliasQuality;

		bool m_bUseViewPort;
		bool m_bRenderDepthMap;
		bool m_bRenderLightLitMap;
		bool m_bRenderCustom;
		bool m_bRenderNormal;
		bool m_bRenderSurface;
		bool m_bUseWindowSize;
		bool m_bUseBeforeDrawEvent;
		bool m_bUseCallBack;

	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::matrix44&
		Camera::GetProjTransform() const
	{
		return m_setting.GetProjTransform();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::matrix44&
		Camera::GetViewTransform() const
	{
		return m_setting.GetViewTransform();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::matrix44&
		Camera::GetViewProjTransform() const
	{
		return m_setting.GetViewProjTransform();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const Math::frustum&
		Camera::GetViewFrustum() const
	{
		n_error("Frustum's compution is not right");
		return m_setting.GetViewFrustum();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline const CameraSetting&
		Camera::GetCameraSetting() const
	{
		return m_setting;
	}

	inline GPtr<RenderPipelineManager>& Camera::GetRenderPipelineManager()
	{
		return m_renderPipelineManager;
	}


	inline void Camera::SetCameraOrder(CameraOrder order)
	{
		m_renderOrder = order;
	}

	inline const CameraOrder& Camera::GetCameraOrder() const
	{
		return m_renderOrder;
	}

	inline void Camera::SetRenderMode(RenderMode mode)
	{
		m_renderMode = mode;
	}

	inline Camera::RenderMode Camera::GetRenderMode() const
	{
		return m_renderMode;
	}

	inline void Camera::SetRenderToTexture(const GPtr<RenderToTexture>& rtt)
	{
		m_renderToTexture = rtt;
	}

	inline const GPtr<RenderToTexture>& Camera::GetRenderToTexture() const
	{
		return m_renderToTexture;
	}

	inline const RenderBase::RenderResourceHandle& Camera::GetBackBuffer() const
	{
		return m_backBuffer ? m_backBuffer->GetTargetHandle() : dummyhandle;
	}

	inline void Camera::SetSwapTexture(const GPtr<RenderToTexture>& rtt)
	{
		m_swapTexture = rtt;
	}

	inline const GPtr<RenderToTexture>& Camera::GetSwapTexture() const
	{
		return m_swapTexture;
	}

	inline bool Camera::HasDepthMap() const
	{
		return m_bRenderDepthMap;
	}

	inline const GPtr<RenderToTexture>& Camera::GetDepthMap() const
	{
		return m_depthMap;
	}

	inline const GPtr<RenderToTexture>& Camera::GetDeferredNormalMap() const
	{
		return m_deferredNormalMap;
	}

	inline const GPtr<RenderToTexture>& Camera::GetDeferredParamMap() const
	{
		return m_deferredParamMap;
	}

	inline const GPtr<RenderToTexture>& Camera::GetDeferredLightMap() const
	{
		return m_deferredLightMap;
	}

	inline bool Camera::HasLightLitMap() const
	{
		return m_bRenderLightLitMap;
	}

	inline const GPtr<RenderToTexture>& Camera::GetLightLitTexture() const
	{
		return m_lightLitTexture;
	}

	inline const GPtr<Material>& Camera::GetLightLitMaterial() const
	{
		return m_lightLitMaterial;
	}

	inline const bool Camera::IsRenderCustom() const
	{
		return m_bRenderCustom;
	}

	inline const GPtr<Material>& Camera::GetCustomMaterial() const
	{
		return m_customMaterial;
	}

	inline const bool Camera::IsRenderNormal() const
	{
		return m_bRenderNormal;
	}

	inline void Camera::SetDebugColor(const Math::float4& color)
	{
		m_debugColor = color;
	}

	inline const Math::float4& Camera::GetDebugColor() const
	{
		return m_debugColor;
	}

	inline void Camera::SetCullMask(const RenderLayer& rl)
	{
		m_cullMask = rl;
	}

	inline const RenderLayer& Camera::GetCullMask() const
	{
		return m_cullMask;
	}

	inline const bool Camera::IsRenderSurface() const
	{
		return m_bRenderSurface;
	}

	inline void Camera::SetRenderSurface(bool bRenderSurface)
	{
		m_bRenderSurface = bRenderSurface;
	}

	inline const bool Camera::UseViewport() const
	{
		return m_bUseViewPort;
	}

	inline void Camera::SetViewport(const ViewPort& vp)
	{
		m_viewPort     = vp;
		m_bUseViewPort = true;
	}

	inline const Camera::ViewPort& Camera::GetViewport() const
	{
		return m_viewPort;
	}

	inline ViewPortWindow* Camera::GetTargetWindow() const
	{
		return m_targetWindow;
	}

	inline void Camera::SetRenderNormal(bool bNormal)
	{
		m_bRenderNormal = bNormal;
	}

	inline void Camera::SetUseCustomMaterial(bool bUse)
	{
		m_bRenderCustom = bUse;
	}

	inline void Camera::SetRenderDepth(bool bDepth)
	{
		m_bRenderDepthMap = bDepth;
	}

	inline void Camera::SetCustomMaterial(const GPtr<Material>& pMat)
	{
		m_customMaterial = pMat;
	}

	inline void Camera::SetClipPlane(const Math::float4& plane)
	{
		m_ClipPlane = plane;
	}

	inline const Math::float4& Camera::GetClipPlane() const
	{
		return m_ClipPlane;
	}

	inline void Camera::SetUseWindowSize(bool bWinSize)
	{
		m_bUseWindowSize = bWinSize;
	}

	inline const bool Camera::IsUsingWindowSize() const
	{
		return m_bUseWindowSize;
	}
	//--------------------------------------------------------------------------------
	inline  void  Camera::SetDrawType(Camera::DrawType mode)
	{
		m_drawMode = mode;
	}
	//--------------------------------------------------------------------------------
	inline const Camera::DrawType&  Camera::GetDrawType() const
	{
		return m_drawMode;
	}
	//--------------------------------------------------------------------------------
	inline Camera::ViewType Camera::GetViewType() const
	{
		return m_viewType;
	}
	//---------------------------------------------------------------------------------
	inline ImageFilterManager& Camera::GetPostEffectFilters()
	{
		return m_postEffects;
	}
	inline const Util::Array<RenderObject*>& Camera::GetNotCullRenderObjects() const
	{
		return m_cameraScene._GetNotCullRenderObjects();
	}

	inline void Camera::SetListener(CameraListener* listener)
	{
		m_listener = listener;
	}

	inline void Camera::SetRenderScene(RenderScene* scene)
	{
		m_renderScene = scene;
	}
	//---------------------------------------------------------------------------------
	inline void Camera::SetShadowDistence(float shadowDis)
	{
		m_setting.SetShadowDistance(shadowDis);
	}

	inline const float Camera::GetShadowDistence() const
	{
		return m_setting.GetShadowDistance();
	}

	inline void Camera::SetOwner(void* owner)
	{
		m_owner = owner;
	}

	inline void* Camera::GetOwner() const
	{
		return m_owner;
	}

	inline void Camera::SetBeforeDrawEvent(bool enable)
	{
		m_bUseBeforeDrawEvent = enable;
	}

	inline bool Camera::IsUseBeforeDrawEvent() const
	{
		return m_bUseBeforeDrawEvent;
	}

	inline const GPtr<QuadRenderable>&  Camera::GetQuadRenderable() const
	{
		return m_quadRenderable;
	}

	inline void Camera::SetRenderLightLitMap(bool enable)
	{
		m_bRenderLightLitMap = enable;
	}


	inline RenderBase::AntiAliasQuality::Code Camera::GetAntiAliasQuality()
	{
		return m_antiAliasQuality;
	}

	inline RenderScene* Camera::GetRenderScene() const
	{
		return m_renderScene;
	}

	inline void Camera::SetUseCallBack( bool bUse )
	{
		m_bUseCallBack = bUse;
	}

	inline bool Camera::GetUseCallBack()
	{
		return m_bUseCallBack;
	}
	//---------------------------------------------------------------------------------
}


#endif //CAMERA_H_
