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
    public partial class LightComponent : Component
    {
        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_Bind(LightComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_LightComponent_GetLightType(LightComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_SetLightType(LightComponent self, int lightType);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_GetPosition(LightComponent self, out Vector3 outPos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_SetPosition(LightComponent self, ref Vector3 pos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_GetDirection(LightComponent self, out Vector3 dir);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_SetDirection(LightComponent self, ref Vector3 dir);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_GetColorF(LightComponent self, out ColorF color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_SetColorF(LightComponent self, ref ColorF color);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_LightComponent_GetIntensity(LightComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_SetIntensity(LightComponent self, float intensity);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_LightComponent_GetRange(LightComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_SetRange(LightComponent self, float range);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_LightComponent_GetDistanceFallOff(LightComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_SetDistanceFallOff(LightComponent self, float falloff);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_LightComponent_GetSpotInnerAngle(LightComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_SetSpotInnerAngle(LightComponent self, float innerAngle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_LightComponent_GetSpotOuterAngle(LightComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_SetSpotOuterAngle(LightComponent self, float outerAngle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_LightComponent_GetSpotExponent(LightComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_LightComponent_SetSpotExponent(LightComponent self, float exponent);
    }
} 
