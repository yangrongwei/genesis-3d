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
#include "scriptfeature/inc/script_utility.h"
#include "graphicfeature/components/cameracomponent.h"
#include "foundation/math/newMath/new_matrix44.h"
#include "basegamefeature/managers/sceneschedulemanager.h"

namespace App
{
	void ICallReg_ScriptRuntime_CameraComponent();

	//------------------------------------------------------------------------
	static void ICall_CameraComponent_Bind( MonoObject* pMonoObj )
	{
		CameraComponent* pCamera = CameraComponent::Create();
		pCamera->GetCameraObject()->SetRenderScene(SceneScheduleManager::Instance()->_GetMainRenderScene());
		n_assert( NULL!=pCamera );
		pCamera->SetUseBeforeDrawEvent(false);
		BindCppObjWithMonoObj<CameraComponent>( pCamera, pMonoObj );
	}

	static float ICall_CameraComponent_GetFov(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return self->GetFov();
	}

	
	static float ICall_CameraComponent_GetAspect(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return self->GetAspect();
	}

	
	static float ICall_CameraComponent_GetZNear(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return self->GetZNear();
	}

	
	static float ICall_CameraComponent_GetZFar(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return self->GetZFar();
	}

	static float ICall_CameraComponent_GetNearWidth( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return self->GetNearWidth();
	}
	static float ICall_CameraComponent_GetNearHeight( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return self->GetNearHeight();
	}
	static float ICall_CameraComponent_GetFarWidth( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return self->GetFarWidth();
	}
	static float ICall_CameraComponent_GetFarHeight( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return self->GetFarHeight();
	}

	static float ICall_CameraComponent_GetShadowDistance(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return self->GetShadowDistence();
	}

	static int ICall_CameraComponent_GetViewType(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return ViewTypeConvert::Conver(self->GetViewType());
	}
	
	static mono_bool ICall_CameraComponent_SetProj(MonoObject* pMonoObj, float fovOrHeight, float zNear, float zFar, int viewType)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		return Utility_MonoBool( self->SetProj(fovOrHeight, zNear, zFar, ViewTypeConvert::Conver(viewType)) );
	}

	static void ICall_CameraComponent_SetZNear(MonoObject* pMonoObj, float zNear)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		self->SetZNear(zNear);
	}

	static void ICall_CameraComponent_SetZFar(MonoObject* pMonoObj, float zFar)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		self->SetZFar(zFar);
	}


	static void ICall_CameraComponent_SetShadowDistance(MonoObject* pMonoObj, float shadowDistance)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		self->SetShadowDistence(shadowDistance);
	}

	static void ICall_CameraComponent_GetView(MonoObject* pMonoObj, Math::matrix44& view)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		view = self->GetViewMat();
	}

	static void ICall_CameraComponent_GetProj(MonoObject* pMonoObj, Math::matrix44& proj)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		proj = self->GetProjMat();
	}

	static void ICall_CameraComponent_GetViewProj(MonoObject* pMonoObj, Math::matrix44& viewProj)
	{
		ScriptObjWrapper<CameraComponent> self(pMonoObj);
		viewProj = self->GetViewProjMat();
	}

	static void ICall_CameraComponent_SetupPerspectiveFovRH( MonoObject* pMonoObj ,float fov, float aspect, float zNear, float zFar)
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		self->SetPerspectiveFovRH(fov, aspect, zNear, zFar);
	}

	static void ICall_CameraComponent_SetupPerspectiveFovRHEx( MonoObject* pMonoObj ,float fov, float aspect, float zNear, float zFar,const Math::float4& clipPlane_, mono_bool reflection)
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		self->SetPerspectiveFovRHEx(fov, aspect, zNear, zFar,clipPlane_,Utility_MonoBool(reflection));
	}

	static void ICall_CameraComponent_SetRenderToTexture(MonoObject* pMonoObj ,MonoObject* pRenderToTexture)
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		ScriptObjWrapper<Graphic::RenderToTexture> renderToTexture( pRenderToTexture );

		self->SetRenderToTexture( renderToTexture.GetCppObjPtr() );
	}

	static void ICall_CameraComponent_SetRenderDepth( MonoObject* pMonoObj,mono_bool bRenderDepth)
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		self->SetRenderDepth(Utility_MonoBool(bRenderDepth));
	}

	static mono_bool ICall_CameraComponent_GetRenderDepth( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		return Utility_MonoBool( self->IsRenderDepth() );
	}

	static void ICall_CameraComponent_SetRenderNormal( MonoObject* pMonoObj,mono_bool bRenderNormal)
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		self->SetRenderNormal(Utility_MonoBool(bRenderNormal));
	}

	static mono_bool ICall_CameraComponent_GetRenderNormal( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		return Utility_MonoBool( self->IsRenderNormal() );
	}

	static void ICall_CameraComponent_GetViewTransForm( MonoObject* pMonoObj,Math::matrix44& out )
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		out = self->GetViewMat();
	}

	static void ICall_CameraComponent_SetCustomise( MonoObject* pMonoObj ,mono_bool customise )
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		self->SetRenderCustom(Utility_MonoBool(customise));
	}

	static mono_bool ICall_CameraComponent_IsCustomise( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		return  Utility_MonoBool( self->IsRenderCustom());
	}

	static void ICall_CameraComponent_SetCullMask(MonoObject* pMonoObj ,uint32 mask)
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		self->SetCullMarkID((CameraComponent::CullMarkID)mask);
	}

	static uint32 ICall_CameraComponent_GetCullMask( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		return self->GetCullMarkID();
	}

	static void ICall_CameraComponent_SetUseBeforeDrawEvent(MonoObject* pMonoObj, bool enable)
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		self->SetUseBeforeDrawEvent(enable);
	}

	static bool ICall_CameraComponent_GetUseBeforeDrawEvent(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		return self->GetUseBeforeDrawEvent();
	}

	static void ICall_CameraComponent_SetRenderShadowMap(MonoObject* pMonoObj, bool enable)
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		self->SetRenderShadowMap(enable);
	}

	static bool ICall_CameraComponent_GetRenderShadowMap(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<CameraComponent> self( pMonoObj );
		return self->GetRenderShadowMap();
	}

	static void ICall_CameraComponent_SetLightLitTexture(MonoObject* pMonoObj ,MonoObject* pRenderToTexture)
	{
			ScriptObjWrapper<CameraComponent> self( pMonoObj );
			ScriptObjWrapper<Graphic::RenderToTexture> renderToTexture( pRenderToTexture );

			self->SetLightLitTexture( renderToTexture.GetCppObjPtr() );
	}

}

#include "autogen/scriptbind_CameraComponent_register.h"
