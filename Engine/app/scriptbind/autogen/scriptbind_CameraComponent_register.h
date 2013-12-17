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

namespace App
{ 
    static void ICall_CameraComponent_Bind( MonoObject* self);

    static float ICall_CameraComponent_GetFov( MonoObject* self);

    static float ICall_CameraComponent_GetAspect( MonoObject* self);

    static float ICall_CameraComponent_GetZNear( MonoObject* self);

    static float ICall_CameraComponent_GetZFar( MonoObject* self);

	static float ICall_CameraComponent_GetShadowDistance(MonoObject* pMonoObj);

    static int ICall_CameraComponent_GetViewType( MonoObject* self);

    static mono_bool ICall_CameraComponent_SetProj( MonoObject* self, float fovOrHeight, float zNear, float zFar, int viewType);

    static void ICall_CameraComponent_SetZNear( MonoObject* self, float zNear);

    static void ICall_CameraComponent_SetZFar( MonoObject* self, float zFar);

	static float ICall_CameraComponent_GetNearWidth( MonoObject* pMonoObj );

	static float ICall_CameraComponent_GetNearHeight( MonoObject* pMonoObj );

	static float ICall_CameraComponent_GetFarWidth( MonoObject* pMonoObj );

	static float ICall_CameraComponent_GetFarHeight( MonoObject* pMonoObj );


	static void ICall_CameraComponent_SetShadowDistance(MonoObject* pMonoObj, float shadowDistance);

    static void ICall_CameraComponent_GetView( MonoObject* self, Math::matrix44& view);

    static void ICall_CameraComponent_GetProj( MonoObject* self, Math::matrix44& proj);

    static void ICall_CameraComponent_GetViewProj( MonoObject* self, Math::matrix44& viewProj);

	static void ICall_CameraComponent_SetupPerspectiveFovRH( MonoObject* pMonoObj ,float fov, float aspect, float zNear, float zFar);

	static void ICall_CameraComponent_SetupPerspectiveFovRHEx( MonoObject* pMonoObj ,float fov, float aspect, float zNear, float zFar,const Math::float4& clipPlane_, mono_bool reflection);

	static void ICall_CameraComponent_SetRenderToTexture(MonoObject* pMonoObj ,MonoObject* pRenderToTexture);

	static void ICall_CameraComponent_SetRenderDepth( MonoObject* pMonoObj,mono_bool bRenderDepth);

	static mono_bool ICall_CameraComponent_GetRenderDepth( MonoObject* pMonoObj );

	static void ICall_CameraComponent_SetRenderNormal( MonoObject* pMonoObj,mono_bool bRenderNormal);

	static mono_bool ICall_CameraComponent_GetRenderNormal( MonoObject* pMonoObj );

	static void ICall_CameraComponent_GetViewTransForm( MonoObject* pMonoObj,Math::matrix44& out );

	static void ICall_CameraComponent_SetCustomise( MonoObject* pMonoObj ,mono_bool customise );

	static mono_bool ICall_CameraComponent_IsCustomise( MonoObject* pMonoObj );

	static void ICall_CameraComponent_SetCullMask(MonoObject* pMonoObj ,uint32 mask);

	static uint32 ICall_CameraComponent_GetCullMask( MonoObject* pMonoObj );

	static void ICall_CameraComponent_SetUseBeforeDrawEvent(MonoObject* pMonoObj, bool enable);

	static bool ICall_CameraComponent_GetUseBeforeDrawEvent(MonoObject* pMonoObj);

	static void ICall_CameraComponent_SetRenderShadowMap(MonoObject* pMonoObj, bool enable);

	static bool ICall_CameraComponent_GetRenderShadowMap(MonoObject* pMonoObj);
//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_CameraComponent( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_Bind",                         (void*)&ICall_CameraComponent_Bind},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetFov",                       (void*)&ICall_CameraComponent_GetFov},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetAspect",                    (void*)&ICall_CameraComponent_GetAspect},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetZNear",                     (void*)&ICall_CameraComponent_GetZNear},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetZFar",                      (void*)&ICall_CameraComponent_GetZFar},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetShadowDistance",            (void*)&ICall_CameraComponent_GetShadowDistance},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetViewType",                  (void*)&ICall_CameraComponent_GetViewType},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetProj",                      (void*)&ICall_CameraComponent_SetProj},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetZNear",                     (void*)&ICall_CameraComponent_SetZNear},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetZFar",                      (void*)&ICall_CameraComponent_SetZFar},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetNearWidth",					(void*)&ICall_CameraComponent_GetNearWidth},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetNearHeight",				(void*)&ICall_CameraComponent_GetNearHeight},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetFarWidth",					(void*)&ICall_CameraComponent_GetFarWidth},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetFarHeight",					(void*)&ICall_CameraComponent_GetFarHeight},

			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetShadowDistance",			(void*)&ICall_CameraComponent_SetShadowDistance},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetView",                      (void*)&ICall_CameraComponent_GetView},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetProj",                      (void*)&ICall_CameraComponent_GetProj},
             { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetViewProj",                  (void*)&ICall_CameraComponent_GetViewProj},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetupPerspectiveFovRH",        (void*)&ICall_CameraComponent_SetupPerspectiveFovRH},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetupPerspectiveFovRHEx",		(void*)&ICall_CameraComponent_SetupPerspectiveFovRHEx},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetRenderToTexture",           (void*)&ICall_CameraComponent_SetRenderToTexture},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetRenderDepth",               (void*)&ICall_CameraComponent_SetRenderDepth},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetRenderDepth",               (void*)&ICall_CameraComponent_GetRenderDepth},
		     { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetRenderNormal",				(void*)&ICall_CameraComponent_SetRenderNormal},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetRenderNormal",				(void*)&ICall_CameraComponent_GetRenderNormal},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetViewTransForm",             (void*)&ICall_CameraComponent_GetViewTransForm},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetCustomise",					(void*)&ICall_CameraComponent_SetCustomise},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_IsCustomise",					(void*)&ICall_CameraComponent_IsCustomise},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetCullMask",					(void*)&ICall_CameraComponent_SetCullMask},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetCullMask",					(void*)&ICall_CameraComponent_GetCullMask},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetUseBeforeDrawEvent",        (void*)&ICall_CameraComponent_SetUseBeforeDrawEvent},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetUseBeforeDrawEvent",		(void*)&ICall_CameraComponent_GetUseBeforeDrawEvent},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetRenderShadowMap",			(void*)&ICall_CameraComponent_SetRenderShadowMap},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_GetRenderShadowMap",			(void*)&ICall_CameraComponent_GetRenderShadowMap},
			 { "ScriptRuntime.CameraComponent::ICall_CameraComponent_SetLightLitTexture",			(void*)&ICall_CameraComponent_SetLightLitTexture},
        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
