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
    public partial class AnimationComponent : Component
    {
        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_SetAnimationID(AnimationComponent self, String id);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_CrossFading(AnimationComponent self, String name, int type, float time);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_PlayAnimation(AnimationComponent self, String name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_StopAnimation(AnimationComponent self, String name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_BlendingAnimation(AnimationComponent self, String name, float weight, float time);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_SetAnimationSpeed(AnimationComponent self, String name, float speed);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_SetAnimationWrapMode(AnimationComponent self, String name, int wrapMode);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_SetAnimationLayer(AnimationComponent self, String name, int layer);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_AddAffectedNodes(AnimationComponent self, String animName, String nodeName, bool recursive);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_RemoveAffectedNodes_2(AnimationComponent self, String animName, String nodeName, bool recursive);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_AddAttachedActor(AnimationComponent self, Actor actor, String skelName);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_AnimationComponent_RemoveAttachedActor(AnimationComponent self, Actor actor);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_AnimationComponent_IsAnimationPlaying(AnimationComponent self, String name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_AnimationComponent_GetCurrentFrame(AnimationComponent self, String name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_AnimationComponent_GetCurAnimCurrentFrame(AnimationComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_AnimationComponent_GetAnimFrameCount(AnimationComponent self, String name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_AnimationComponent_GetCurrentAnimFrameCount(AnimationComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_AnimationComponent_GetCurrentAnimation(AnimationComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_AnimationComponent_GetNodeTransform(AnimationComponent self, String name, out Matrix44 matrix);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_AnimationComponent_GetWrapMode(AnimationComponent self, String name);
    }
} 
