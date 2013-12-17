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
    public partial class SpriteRenderComponent : Component
    {

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_Bind(SpriteRenderComponent self);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_Setup(SpriteRenderComponent self, String pMonoStr);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_SpriteRenderComponent_GetPackageID(SpriteRenderComponent self, String pMonoStr );
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_SpriteRenderComponent_GetPackageID( SpriteRenderComponent self );
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_SetBlock( SpriteRenderComponent self, String pMonoStr );
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_SetAnimation(SpriteRenderComponent self, String pMonoStr, int loops, bool play, float speed);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_RemoveBlock(SpriteRenderComponent self);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_RemoveAnimation(SpriteRenderComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_SetAnimationSpeed( SpriteRenderComponent self, float speed);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_Play( SpriteRenderComponent self);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_Pause( SpriteRenderComponent self);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_Stop( SpriteRenderComponent self);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_Replay(SpriteRenderComponent self);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_SpriteRenderComponent_SetPlayOnWake( SpriteRenderComponent self, bool value);
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_SpriteRenderComponent_GetBlockName( SpriteRenderComponent self );
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_SpriteRenderComponent_GetAnimationName( SpriteRenderComponent self );        
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_SpriteRenderComponent_GetAnimationLoops( SpriteRenderComponent self );
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_SpriteRenderComponent_GetAnimationSpeed( SpriteRenderComponent self );
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SpriteRenderComponent_IsAnimationPlaying( SpriteRenderComponent self );
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_SpriteRenderComponent_GetPlayOnWake( SpriteRenderComponent self );
       
       
    }
} 
