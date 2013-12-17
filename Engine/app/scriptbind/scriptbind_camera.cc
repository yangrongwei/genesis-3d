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
#include "graphicsystem/Camera/Camera.h"
#include "graphicsystem/base/RenderToTexture.h"
#include "foundation/math/newMath/new_matrix44.h"
#include "basegamefeature/managers/sceneschedulemanager.h"
namespace App
{
	 void ICallReg_ScriptRuntime_Camera( void );

	 static void ICall_Camera_Bind( MonoObject* pMonoObj )
	 {
		Graphic::Camera* pCamera = Graphic::Camera::Create();
		n_assert( NULL!=pCamera );

		pCamera->SetRenderScene( SceneScheduleManager::Instance()->_GetMainRenderScene());
		pCamera->SetCameraOrder(Graphic::eCO_Main);
		pCamera->SetUseCallBack(false);
		BindCppObjWithMonoObj<Graphic::Camera>(pCamera,pMonoObj);
	 }

	 static void ICall_Camera_Release( MonoObject* pMonoObj )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );

		 ReleaseCppObjWithMonoObj<Graphic::Camera>( self.GetCppObjPtr(), pMonoObj );
	 }

	 static void ICall_Camera_SetupPerspectiveFovRH( MonoObject* pMonoObj ,float fov, float aspect, float zNear, float zFar)
	 {
		  ScriptObjWrapper<Graphic::Camera> self( pMonoObj );

		  Graphic::CameraSetting cs = self->GetCameraSetting();
		  cs.SetupPerspectiveFovRH(fov, aspect, zNear, zFar);
		  self->SetCameraSetting(cs);
	 }

	 static void ICall_Camera_SetupPerspectiveFovRHEx( MonoObject* pMonoObj ,float fov, float aspect, float zNear, float zFar,const Math::float4& clipPlane_, mono_bool reflection)
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );

		 Graphic::CameraSetting cs = self->GetCameraSetting();
		 cs.SetupPerspectiveFovRH(fov, aspect, zNear, zFar,clipPlane_,Utility_MonoBool(reflection));
		 self->SetCameraSetting(cs);
	 }

	 static void ICall_Camera_SetRenderToTexture(MonoObject* pMonoObj ,MonoObject* pRenderToTexture)
	 {
		  ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		  ScriptObjWrapper<Graphic::RenderToTexture> renderToTexture( pRenderToTexture );

		  self->SetRenderToTexture( renderToTexture.GetCppObjPtr() );
	 }

	 static void ICall_Camera_SetRenderDepth( MonoObject* pMonoObj,mono_bool bRenderDepth)
	 {
		  ScriptObjWrapper<Graphic::Camera> self( pMonoObj );

		  self->SetRenderDepth(Utility_MonoBool(bRenderDepth));
	 }

	 static mono_bool ICall_Camera_GetRenderDepth( MonoObject* pMonoObj )
	 {
		  ScriptObjWrapper<Graphic::Camera> self( pMonoObj );

		  return Utility_MonoBool( self->HasDepthMap() );
	 }

	 static void ICall_Camera_SetRenderNormal( MonoObject* pMonoObj,mono_bool bRenderNormal)
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );

		 self->SetRenderNormal(Utility_MonoBool(bRenderNormal));
	 }

	 static mono_bool ICall_Camera_GetRenderNormal( MonoObject* pMonoObj )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );

		 return Utility_MonoBool( self->IsRenderNormal() );
	 }

	 static void ICall_Camera_SetViewTransForm( MonoObject* pMonoObj,const Math::matrix44& view )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 self->SetTransform(Math::matrix44::inverse(view));
		 self->OnTransformChanged();
	 }

	 static void ICall_Camera_GetViewTransForm( MonoObject* pMonoObj,Math::matrix44& out )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 out = self->GetViewTransform();
	 }

	 static void ICall_Camera_GetProjTransForm( MonoObject* pMonoObj,Math::matrix44& out )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 out = self->GetProjTransform();
	 }

	 static float ICall_Camera_GetAspect( MonoObject* pMonoObj )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 Graphic::CameraSetting cs = self->GetCameraSetting();
		 return cs.GetAspect();
	 }

	 static float ICall_Camera_GetFov( MonoObject* pMonoObj )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 Graphic::CameraSetting cs = self->GetCameraSetting();
		 return cs.GetFov();
	 }

	 static float ICall_Camera_GetNear( MonoObject* pMonoObj )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 Graphic::CameraSetting cs = self->GetCameraSetting();
		 return cs.GetZNear();
	 }

	 static float ICall_Camera_GetFar( MonoObject* pMonoObj )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 Graphic::CameraSetting cs = self->GetCameraSetting();
		 return cs.GetZFar();
	 }

	 static void ICall_Camera_SetCullMask(MonoObject* pMonoObj ,uint32 mask)
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 self->SetCullMask( (Graphic::RenderLayer)mask );
	 }

	 static uint32 ICall_Camera_GetCullMask( MonoObject* pMonoObj )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 return self->GetCullMask();
	 }

	 static void ICall_Camera_SetCustomise( MonoObject* pMonoObj ,mono_bool customise )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 self->SetUseCustomMaterial(Utility_MonoBool(customise));
	 }

	 static mono_bool ICall_Camera_IsCustomise( MonoObject* pMonoObj )
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 return  Utility_MonoBool( self->IsRenderCustom());
	 }

	 static void ICall_Camera_SetUseBeforeDrawEvent(MonoObject* pMonoObj, bool enable)
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 self->SetBeforeDrawEvent(enable);
	 }

	 static void ICall_Camera_SetRenderShadowMap(MonoObject* pMonoObj, bool enable)
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 self->SetRenderLightLitMap(enable);
	 }

	 static void ICall_Camera_SetLightLitTexture(MonoObject* pMonoObj ,MonoObject* pRenderToTexture)
	 {
		 ScriptObjWrapper<Graphic::Camera> self( pMonoObj );
		 ScriptObjWrapper<Graphic::RenderToTexture> renderToTexture( pRenderToTexture );

		 self->SetLightLitMap( renderToTexture.GetCppObjPtr() );
	 }

	 void ICallReg_ScriptRuntime_Camera( void )
	 {
		 static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			 { "ScriptRuntime.Camera::ICall_Camera_Bind",									 (void*)&ICall_Camera_Bind },
			 { "ScriptRuntime.Camera::ICall_Camera_Release",								 (void*)&ICall_Camera_Release },
			 { "ScriptRuntime.Camera::ICall_Camera_SetupPerspectiveFovRH",					 (void*)&ICall_Camera_SetupPerspectiveFovRH },
			 { "ScriptRuntime.Camera::ICall_Camera_SetupPerspectiveFovRHEx",				 (void*)&ICall_Camera_SetupPerspectiveFovRHEx },		 
			 { "ScriptRuntime.Camera::ICall_Camera_SetRenderToTexture",						 (void*)&ICall_Camera_SetRenderToTexture },
			 { "ScriptRuntime.Camera::ICall_Camera_SetRenderDepth",							 (void*)&ICall_Camera_SetRenderDepth },
			 { "ScriptRuntime.Camera::ICall_Camera_GetRenderDepth",							 (void*)&ICall_Camera_GetRenderDepth },
			 { "ScriptRuntime.Camera::ICall_Camera_SetRenderNormal",						 (void*)&ICall_Camera_SetRenderNormal },
			 { "ScriptRuntime.Camera::ICall_Camera_GetRenderNormal",						 (void*)&ICall_Camera_GetRenderNormal },
			 { "ScriptRuntime.Camera::ICall_Camera_GetViewTransForm",						 (void*)&ICall_Camera_GetViewTransForm },
			 { "ScriptRuntime.Camera::ICall_Camera_GetProjTransForm",						 (void*)&ICall_Camera_GetProjTransForm },
			 { "ScriptRuntime.Camera::ICall_Camera_SetViewTransForm",						 (void*)&ICall_Camera_SetViewTransForm },	 
			 { "ScriptRuntime.Camera::ICall_Camera_GetAspect",								 (void*)&ICall_Camera_GetAspect },	 
			 { "ScriptRuntime.Camera::ICall_Camera_GetFov",									 (void*)&ICall_Camera_GetFov },	 
			 { "ScriptRuntime.Camera::ICall_Camera_GetNear",								 (void*)&ICall_Camera_GetNear },	 
			 { "ScriptRuntime.Camera::ICall_Camera_GetFar",									 (void*)&ICall_Camera_GetFar },	 
			 { "ScriptRuntime.Camera::ICall_Camera_SetCullMask",							 (void*)&ICall_Camera_SetCullMask },	 
			 { "ScriptRuntime.Camera::ICall_Camera_GetCullMask",							 (void*)&ICall_Camera_GetCullMask },	 
			 { "ScriptRuntime.Camera::ICall_Camera_SetCustomise",							 (void*)&ICall_Camera_SetCustomise },	 
			 { "ScriptRuntime.Camera::ICall_Camera_IsCustomise",							 (void*)&ICall_Camera_IsCustomise },	
			 { "ScriptRuntime.Camera::ICall_Camera_SetUseBeforeDrawEvent",					 (void*)&ICall_Camera_SetUseBeforeDrawEvent},
			 { "ScriptRuntime.Camera::ICall_Camera_SetRenderShadowMap",						 (void*)&ICall_Camera_SetRenderShadowMap},
			 { "ScriptRuntime.Camera::ICall_Camera_SetLightLitTexture",						 (void*)&ICall_Camera_SetLightLitTexture},
		 };

		 int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		 for( int ii=0; ii<size; ii++ )
		 {
			 mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				 s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		 }
	 }
}

