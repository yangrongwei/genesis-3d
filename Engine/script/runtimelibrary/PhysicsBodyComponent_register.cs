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
    public partial class PhysicsBodyComponent : Component
    {
        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetLinearVelocity(PhysicsBodyComponent self, ref Vector3 velocity );

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_GetLinearVelocity(PhysicsBodyComponent self, out Vector3 velocity);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetAngularVelocity(PhysicsBodyComponent self, ref Vector3 velocity);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_GetAngularVelocity(PhysicsBodyComponent self, out Vector3 velocity);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetLinearDamping(PhysicsBodyComponent self, float scalar);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_PhysicsBodyComponent_GetLinearDamping(PhysicsBodyComponent self );

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetAngularDamping(PhysicsBodyComponent self, float damping);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_PhysicsBodyComponent_GetAngularDamping(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_PhysicsBodyComponent_GetMass(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetDynamic(PhysicsBodyComponent self, bool dynamic);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_PhysicsBodyComponent_GetDynamic(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetKinematic(PhysicsBodyComponent self, bool Kinematic);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_PhysicsBodyComponent_GetKinematic(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetUseGravity(PhysicsBodyComponent self, bool UseGravity);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_PhysicsBodyComponent_GetUseGravity(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetCollision(PhysicsBodyComponent self, bool IsCollision);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_PhysicsBodyComponent_GetCollision(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetConstForce(PhysicsBodyComponent self, ref Vector4 force);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_GetConstForce(PhysicsBodyComponent self, out Vector4 force);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetConstTorque(PhysicsBodyComponent self, ref Vector4 torque);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_GetConstTorque(PhysicsBodyComponent self, out Vector4 torque);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_SetGravityCenter(PhysicsBodyComponent self, ref Vector4 pos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_GetGravityCenter(PhysicsBodyComponent self, out Vector4 pos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_MovePostion(PhysicsBodyComponent self, ref Vector3 pos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_RotateRotation(PhysicsBodyComponent self, ref Quaternion qua);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_MoveToPostion(PhysicsBodyComponent self, ref Vector3 pos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_RotateToRotation(PhysicsBodyComponent self, ref Quaternion qua);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_AddForce(PhysicsBodyComponent self,ref Vector3 force, ForceType forcetype, bool bWakeUp);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_AddForceAtPos(PhysicsBodyComponent self, ref Vector3 force, ref Vector3 pos, ForceType forcetype, bool bWakeUp);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_AddLocalForceAtPos(PhysicsBodyComponent self, ref Vector3 force, ref Vector3 pos, ForceType forcetype, bool bWakeUp);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_AddForceAtLocalPos(PhysicsBodyComponent self, ref Vector3 force, ref Vector3 pos, ForceType forcetype, bool bWakeUp);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsBodyComponent_AddLocalForceAtLocalPos(PhysicsBodyComponent self, ref Vector3 force, ref Vector3 pos, ForceType forcetype, bool bWakeUp);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsEntity_CreateShape(PhysicsBodyComponent self, int shapeType);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsEntity_RemoveShapeAt(PhysicsBodyComponent self, int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsEntity_ReplaceShape(PhysicsBodyComponent self, int index, int shapeType);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static PhysicsShape ICall_PhysicsEntity_GetShapeAt(PhysicsBodyComponent self, int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_PhysicsEntity_GetShapeCount(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_PhysicsRole_IsOnGround(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_PhysicsRole_IsFreeFloat(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_PhysicsRole_IsTouchCeil(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_PhysicsRole_IsTouchSides(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsRole_SetRadius(PhysicsBodyComponent self, float radius);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_PhysicsRole_GetRadius(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsRole_SetCenter(PhysicsBodyComponent self, ref Vector3 center);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static Vector3 ICall_PhysicsRole_GetCenter(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsRole_SetHeight(PhysicsBodyComponent self, float height);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_PhysicsRole_GetHeight(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsRole_SetSlopeLimit(PhysicsBodyComponent self, float slope);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_PhysicsRole_GetSlopeLimit(PhysicsBodyComponent self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_PhysicsRole_SetStepOffset(PhysicsBodyComponent self, float offset);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_PhysicsRole_GetStepOffset(PhysicsBodyComponent self);
    }
} 
