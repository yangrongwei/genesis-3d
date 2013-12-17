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
using System;
using System.Runtime.CompilerServices;
using ScriptRuntime;

namespace ScriptRuntime
{ 
    public partial class CameraComponent : Component
    {
        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_Bind(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_CameraComponent_GetFov(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_CameraComponent_GetAspect(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_CameraComponent_GetZNear(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_CameraComponent_GetZFar(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_CameraComponent_GetNearWidth(CameraComponent self);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_CameraComponent_GetNearHeight(CameraComponent self);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_CameraComponent_GetFarWidth(CameraComponent self);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_CameraComponent_GetFarHeight(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_CameraComponent_GetShadowDistance(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_CameraComponent_GetViewType(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_CameraComponent_SetProj(CameraComponent self, float fovOrHeight, float zNear, float zFar, int viewType);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetZNear(CameraComponent self, float zNear);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetZFar(CameraComponent self, float zFar);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetShadowDistance(CameraComponent self, float shadowDistance);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_GetView(CameraComponent self, out Matrix44 view);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_GetProj(CameraComponent self, out Matrix44 proj);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_GetViewProj(CameraComponent self, out Matrix44 viewProj);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetupPerspectiveFovRH(CameraComponent self, float fov, float aspect, float zNear, float zFar);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetupPerspectiveFovRHEx(CameraComponent self, float fov, float aspect, float zNear, float zFar, ref Vector4 clipPlane_, bool reflection);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetRenderToTexture(CameraComponent self, RenderToTexture renderToTexture);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetRenderDepth(CameraComponent self, bool bRenderDepth);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_CameraComponent_GetRenderDepth(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetRenderNormal(CameraComponent pMonoObj, bool bRenderNormal);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_CameraComponent_GetRenderNormal(CameraComponent self);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_GetViewTransForm(CameraComponent self, out Matrix44 view);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetCustomise(CameraComponent self, bool customise);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_CameraComponent_IsCustomise(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetCullMask(CameraComponent self,UInt32 mask);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static UInt32 ICall_CameraComponent_GetCullMask(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetUseBeforeDrawEvent(CameraComponent self, bool enable);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_CameraComponent_GetUseBeforeDrawEvent(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetRenderShadowMap(CameraComponent self, bool enable);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_CameraComponent_GetRenderShadowMap(CameraComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_CameraComponent_SetLightLitTexture(CameraComponent self, RenderToTexture renderToTexture);
    }
} 
