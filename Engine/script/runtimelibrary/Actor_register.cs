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
    public partial class Actor : Base
    {
        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_Bind(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_Release(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetName(Actor self, String sName);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_Actor_GetName(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_Actor_GetTemplateName(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetLayerID(Actor self, UInt32 layerID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static UInt32 ICall_Actor_GetLayerID(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Actor_IsLinkTemplate(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetLinkTemplate(Actor self, bool bLink);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetTagID(Actor self, UInt32 tagID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static UInt32 ICall_Actor_GetTagID(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static byte[] ICall_Actor_GetGuid(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static UInt32 ICall_Actor_GetFastId(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Actor_IsActive(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Actor_GetActiveControl(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_Active(Actor self, bool forceActiveControlofChild);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_Deactive(Actor self, bool forceActiveControlofChild);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_Actor_GetParent(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetParent(Actor self, Actor parent);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_Actor_GetChildCount(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_Actor_GetChild(Actor self, int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Actor ICall_Actor_FindChild(Actor self, UInt32 fastId);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_Actor_FindChildIndex(Actor self, UInt32 fastId);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_AddChild(Actor self, Actor child);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_RemoveChild(Actor self, int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetLocalPos(Actor self, ref Vector3 pos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetLocalRotation(Actor self, ref Quaternion rot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetLocalScale(Actor self, ref Vector3 scale);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetLocalPos(Actor self, out Vector3 outPos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetLocalRotation(Actor self, out Quaternion outRot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetLocalScale(Actor self, out Vector3 outScale);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_Roll(Actor self, float angle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_Pitch(Actor self, float angle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_Yaw(Actor self, float angle);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_Rotate(Actor self, float roll, float picth, float yaw);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetTransform(Actor self, ref Matrix44 matrix);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetTransform(Actor self, out Matrix44 matrix);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetWorldTransform(Actor self, ref Matrix44 matrix);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetWorldTransform(Actor self, out Matrix44 matrix);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetInheritRotation(Actor self, bool bInherit);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Actor_GetInheritRotation(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetInheritScale(Actor self, bool bInherit);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Actor_GetInheritScale(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetWorldRotation(Actor self, out Quaternion rot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetWorldRotation(Actor self, ref Quaternion rot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetWorldPos(Actor self, out Vector3 rot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetWorldPos(Actor self, ref Vector3 rot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetWorldScale(Actor self, out Vector3 rot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetWorldScale(Actor self, ref Vector3 rot);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetWorldBoundingBox(Actor self, out BoundingBox bb);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetWorldBoundingBoxWithChild(Actor self, out BoundingBox bb);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_GetLocalBoundingBox(Actor self, out BoundingBox bb);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetLocalBoundingBox(Actor self, ref BoundingBox bb);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Component ICall_Actor_RemoveComponent(Actor self, Component comp);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Component ICall_Actor_AddComponentByName(Actor self, String sName);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Component ICall_Actor_GetComponentByName(Actor self, String sName);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Actor_IsAllResourcePrepared(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Actor_SetPriority(Actor self, int priority);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_Actor_GetPriority(Actor self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_Actor_GetRefCount(Actor self);
    }
} 
