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
    public partial class SoundSource : Component
    {
        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_Play(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_Stop(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_Pause(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SoundSource_IsPlaying(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SoundSource_IsPaused(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SoundSource_GetLoop(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetLoop(SoundSource self, bool bLoop);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundSource_GetVolume(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetVolume(SoundSource self, float volume);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SoundSource_GetMute(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetMute(SoundSource self, bool mute);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SoundSource_Is3D(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_Set3D(SoundSource self, bool is3D);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static UInt32 ICall_SoundSource_GetLength(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundSource_GetPitch(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetPitch(SoundSource self, float pitch);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundSource_GetDopplerLevel(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetDopplerLevel(SoundSource self, float level);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundSource_GetSpread(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetSpread(SoundSource self, float spread);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_SoundSource_GetPriority(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetPriority(SoundSource self, int priority);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundSource_GetMinDistance(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetMinDistance(SoundSource self, float minDistance);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundSource_GetMaxDistance(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetMaxDistance(SoundSource self, float maxDistance);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SoundSource_GetPan(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetPan(SoundSource self, float pan);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static UInt32 ICall_SoundSource_GetPosition(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetPosition(SoundSource self, UInt32 position);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SoundSource_GetAutoPlay(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetAutoPlay(SoundSource self, bool setPlay);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_SoundSource_GetLoadPriority(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SoundSource_GetIgnoreEffect(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetIgnoreEffect(SoundSource self, bool IgnoreEffect);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_SoundSource_GetRolloffMode(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetRolloffMode(SoundSource self, int rolloffMode);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SoundSource_IsAllLoaded(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_SoundSource_GetName(SoundSource self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SoundSource_SetName(SoundSource self, String pMonoString, int loadpriority);

    }
} 
