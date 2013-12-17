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
    public partial class ProjectorRenderComponent : RenderComponent
    {
        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_ProjectorRenderComponent_GetFov(ProjectorRenderComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ProjectorRenderComponent_SetFov(ProjectorRenderComponent self, float fov);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_ProjectorRenderComponent_GetViewType(ProjectorRenderComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ProjectorRenderComponent_SetViewType(ProjectorRenderComponent self, int viewType);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_ProjectorRenderComponent_GetAspect(ProjectorRenderComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ProjectorRenderComponent_SetAspect(ProjectorRenderComponent self, float aspect);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_ProjectorRenderComponent_GetZNear(ProjectorRenderComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ProjectorRenderComponent_SetZNear(ProjectorRenderComponent self, float znear);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_ProjectorRenderComponent_GetZFar(ProjectorRenderComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ProjectorRenderComponent_SetZFar(ProjectorRenderComponent self, float zfar);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_ProjectorRenderComponent_GetNearHeight(ProjectorRenderComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ProjectorRenderComponent_SetNearHeight(ProjectorRenderComponent self, float nearHeight);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static UInt32 ICall_ProjectorRenderComponent_GetIgnoreLayers(ProjectorRenderComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ProjectorRenderComponent_SetIgnoreLayers(ProjectorRenderComponent self, UInt32 mask);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_ProjectorRenderComponent_EnableProjector(ProjectorRenderComponent self, bool b);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_ProjectorRenderComponent_IsEnabledProjector(ProjectorRenderComponent self);
    }
}
