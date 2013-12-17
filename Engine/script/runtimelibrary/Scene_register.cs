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
    public partial class Scene : Base
    {
        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Scene_Release(Scene self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_Scene_GetActorCount(Scene self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_Scene_GetActor(Scene self, int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_Scene_FindActorByFastID(Scene self, UInt32 fastID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_Scene_FindActorByTag(Scene self, UInt32 tagID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor[] ICall_Scene_FindActorsByTag(Scene self, UInt32 tagID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Scene_AddActor(Scene self, Actor pActor);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Scene_RemoveActor(Scene self, Actor pActor);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_Scene_FindActorByGuid(Scene self, byte[] guid);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_Scene_FindActorByName(Scene self, String name);

    }
} 
