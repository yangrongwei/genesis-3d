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
    public partial class SoundReverbFilterComponent : Component
    {
        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_Bind(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_Attach(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_Detach(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_SoundReverbFilterComponent_GetReverbPreset(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetReverbPreset(SoundReverbFilterComponent self, int preset);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetDensity(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetDensity(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetDiffusion(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetDiffusion(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetGain(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetGain(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetGainHF(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetGainHF(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetDecayTime(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetDecayTime(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetDecayHFRatio(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetDecayHFRatio(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetDecayLFRatio(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetDecayLFRatio(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetReflectionsGain(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetReflectionsGain(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetReflectionsDelay(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetReflectionsDelay(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetReverbGain(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetReverbGain(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetReverbDelay(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetReverbDelay(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetEchoTime(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetEchoTime(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetEchoDepth(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetEchoDepth(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetModulationTime(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetModulationTime(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetModulationDepth(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetModulationDepth(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetAirGainHF(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetAirGainHF(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetHFReference(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetHFReference(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetLFReference(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetLFReference(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundReverbFilterComponent_GetRoomRolloff(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetRoomRolloff(SoundReverbFilterComponent self, float pvalue);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SoundReverbFilterComponent_GetDecayHFLimit(SoundReverbFilterComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundReverbFilterComponent_SetDecayHFLimit(SoundReverbFilterComponent self, bool isDecayHFLimit);
    }
} 
