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
    public partial class RenderComponent : Component
    {
        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static string ICall_RenderComponent_GetMaterialID(RenderComponent self, int iSubMesh);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static MaterialInstance ICall_RenderComponent_GetMaterialInstance(RenderComponent self, int iSubMesh);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderComponent_SetMaterialID(RenderComponent self, int iSubMesh, String pMonoStr, bool bCopy = false);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderComponent_SetMaterialInstance(RenderComponent self, int iSubMesh, MaterialInstance pMonoStr, bool bCopy = false);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_RenderComponent_GetShaderID(RenderComponent self, int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderComponent_SetShaderID(RenderComponent self, int iSubMesh, String sSharderId);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderComponent_SetTexture(RenderComponent self, int iSubMesh, String sParamName, String sTexId, int iPriority);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderComponent_SetTextureRTT(RenderComponent self, int iSubMesh, String sParamName, RenderToTexture rtt);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderComponent_SetShaderConstantParam(RenderComponent self, int iSubMesh, String sParamName, float val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderComponent_SetShaderConstantParamF4(RenderComponent self, int iSubMesh, String sParamName, ref Vector4 val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static uint ICall_RenderComponent_GetShaderCount(RenderComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderComponent_StandaloneRender(RenderComponent self, MaterialInstance customMat);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_RenderComponent_SetVisible(RenderComponent self, bool bVis);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_RenderComponent_IsVisible(RenderComponent self);
    }
}
