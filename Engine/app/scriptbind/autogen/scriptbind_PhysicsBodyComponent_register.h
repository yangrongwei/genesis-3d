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

namespace App
{ 
    static void ICall_PhysicsBodyComponent_SetLinearVelocity(MonoObject* self, Math::float3& velocity );

    static void ICall_PhysicsBodyComponent_GetLinearVelocity(MonoObject* self, Math::float3& velocity);

    static void ICall_PhysicsBodyComponent_SetAngularVelocity(MonoObject* self, Math::float3& velocity);

    static void ICall_PhysicsBodyComponent_GetAngularVelocity(MonoObject* self, Math::float3& velocity);

    static void ICall_PhysicsBodyComponent_SetLinearDamping(MonoObject* self, float scalar);

    static float ICall_PhysicsBodyComponent_GetLinearDamping(MonoObject* pMonoObj);

    static void ICall_PhysicsBodyComponent_SetAngularDamping(MonoObject* self, float damping);

    static float ICall_PhysicsBodyComponent_GetAngularDamping(MonoObject* pMonoObj);

    static float ICall_PhysicsBodyComponent_GetMass(MonoObject* self);

    static void ICall_PhysicsBodyComponent_SetDynamic(MonoObject* self, mono_bool dynamic);

    static mono_bool ICall_PhysicsBodyComponent_GetDynamic(MonoObject* self);

    static void ICall_PhysicsBodyComponent_SetKinematic(MonoObject* self, mono_bool Kinematic);

    static mono_bool ICall_PhysicsBodyComponent_GetKinematic(MonoObject* self);

    static void ICall_PhysicsBodyComponent_SetUseGravity(MonoObject* self, mono_bool UseGravity);

    static mono_bool ICall_PhysicsBodyComponent_GetUseGravity(MonoObject* self);

	static void ICall_PhysicsBodyComponent_SetCollision(MonoObject* self, mono_bool conllision);

	static mono_bool ICall_PhysicsBodyComponent_GetCollision(MonoObject* self);

    static void ICall_PhysicsBodyComponent_SetConstForce(MonoObject* self, Math::float3& force);

	static void ICall_PhysicsBodyComponent_GetConstForce(MonoObject* self, Math::float3& force);

	static void ICall_PhysicsBodyComponent_GetConstLineVelocity(MonoObject* self, Math::float3& force);

	static void ICall_PhysicsBodyComponent_SetConstLineVelocity(MonoObject* self, Math::float3& force);

    static void ICall_PhysicsBodyComponent_SetConstTorque(MonoObject* self, Math::float3& torque);

    static void ICall_PhysicsBodyComponent_GetConstTorque(MonoObject* self, Math::float3& torque);

	static void ICall_PhysicsBodyComponent_SetConstAngularVelocity(MonoObject* self, Math::float3& torque);

	static void ICall_PhysicsBodyComponent_GetConstAngularVelocity(MonoObject* self, Math::float3& torque);

    static void ICall_PhysicsBodyComponent_MovePostion(MonoObject* self, Math::float3& pos);

    static void ICall_PhysicsBodyComponent_RotateRotation(MonoObject* self, Math::quaternion& qua);

    static void ICall_PhysicsBodyComponent_MoveToPostion(MonoObject* self, Math::float3& pos);

    static void ICall_PhysicsBodyComponent_RotateToRotation(MonoObject* self, Math::quaternion& qua);

	static void ICall_PhysicsBodyComponent_AddForce(MonoObject* self, Math::float3& force, PhysicsDynamic::ForceType forcetype, mono_bool bWakeUp);

	static void ICall_PhysicsBodyComponent_AddForceAtPos(MonoObject* self, Math::float3& force, Math::float3& pos,PhysicsDynamic::ForceType forcetype, mono_bool bWakeUp);

	static void ICall_PhysicsBodyComponent_AddForceAtLocalPos(MonoObject* self, Math::float3& force, Math::float3& pos, PhysicsDynamic::ForceType forcetype, mono_bool bWakeUp);

	static void ICall_PhysicsBodyComponent_AddLocalForceAtPos(MonoObject* self, Math::float3& force, Math::float3& pos,PhysicsDynamic::ForceType forcetype, mono_bool bWakeUp);

	static void ICall_PhysicsBodyComponent_AddLocalForceAtLocalPos(MonoObject* self, Math::float3& force, Math::float3& pos,PhysicsDynamic::ForceType forcetype, mono_bool bWakeUp);

	static void ICall_PhysicsEntity_CreateShape(MonoObject* self, int shapeType);

	static void ICall_PhysicsEntity_RemoveShapeAt(MonoObject* self, int index);

	static void ICall_PhysicsEntity_ReplaceShape(MonoObject* self, int index, int shapeType);

	static MonoObject* ICall_PhysicsEntity_GetShapeAt(MonoObject* self, int index);

	static int ICall_PhysicsEntity_GetShapeCount(MonoObject* self);

	static mono_bool ICall_PhysicsRole_IsOnGround(MonoObject* pMonoObj);

	static mono_bool ICall_PhysicsRole_IsFreeFloat(MonoObject* pMonoObj);

	static mono_bool ICall_PhysicsRole_IsTouchCeil(MonoObject* pMonoObj);

	static mono_bool ICall_PhysicsRole_IsTouchSides(MonoObject* pMonoObj);

	static void ICall_PhysicsRole_SetRadius(MonoObject* pMonoObj, float radius);

	static float ICall_PhysicsRole_GetRadius(MonoObject* pMonoObj);

	static void ICall_PhysicsRole_SetHeight(MonoObject* pMonoObj, float height);

	static float ICall_PhysicsRole_GetHeight(MonoObject* pMonoObj);

	static void ICall_PhysicsRole_SetCenter(MonoObject* pMonoObj, Math::float3& center);

	static Math::float3 ICall_PhysicsRole_GetCenter(MonoObject* pMonoObj);

	static void ICall_PhysicsRole_SetSlopeLimit(MonoObject* pMonoObj, float slope);

	static float ICall_PhysicsRole_GetSlopeLimit(MonoObject* pMonoObj);

	static void ICall_PhysicsRole_SetStepOffset(MonoObject* pMonoObj, float offSet);

	static float ICall_PhysicsRole_GetStepOffset(MonoObject* pMonoObj);
//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_PhysicsBodyComponent( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetLinearVelocity",  (void*)&ICall_PhysicsBodyComponent_SetLinearVelocity},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetLinearVelocity",  (void*)&ICall_PhysicsBodyComponent_GetLinearVelocity},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetAngularVelocity", (void*)&ICall_PhysicsBodyComponent_SetAngularVelocity},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetAngularVelocity", (void*)&ICall_PhysicsBodyComponent_GetAngularVelocity},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetLinearDamping",   (void*)&ICall_PhysicsBodyComponent_SetLinearDamping},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetLinearDamping",   (void*)&ICall_PhysicsBodyComponent_GetLinearDamping},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetAngularDamping",  (void*)&ICall_PhysicsBodyComponent_SetAngularDamping},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetAngularDamping",  (void*)&ICall_PhysicsBodyComponent_GetAngularDamping},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetMass",            (void*)&ICall_PhysicsBodyComponent_GetMass},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetDynamic",         (void*)&ICall_PhysicsBodyComponent_SetDynamic},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetDynamic",         (void*)&ICall_PhysicsBodyComponent_GetDynamic},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetKinematic",       (void*)&ICall_PhysicsBodyComponent_SetKinematic},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetKinematic",       (void*)&ICall_PhysicsBodyComponent_GetKinematic},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetUseGravity",      (void*)&ICall_PhysicsBodyComponent_SetUseGravity},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetUseGravity",      (void*)&ICall_PhysicsBodyComponent_GetUseGravity},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetCollision",      (void*)&ICall_PhysicsBodyComponent_SetCollision},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetCollision",      (void*)&ICall_PhysicsBodyComponent_GetCollision},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetConstForce",      (void*)&ICall_PhysicsBodyComponent_SetConstForce},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetConstForce",      (void*)&ICall_PhysicsBodyComponent_GetConstForce},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetConstLineVelocity",(void*)&ICall_PhysicsBodyComponent_SetConstLineVelocity},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetConstLineVelocity",(void*)&ICall_PhysicsBodyComponent_GetConstLineVelocity},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetConstTorque",     (void*)&ICall_PhysicsBodyComponent_SetConstTorque},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetConstTorque",     (void*)&ICall_PhysicsBodyComponent_GetConstTorque},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_SetAngularVelocity", (void*)&ICall_PhysicsBodyComponent_SetConstAngularVelocity},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_GetAngularVelocity", (void*)&ICall_PhysicsBodyComponent_GetConstAngularVelocity},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_MovePostion",        (void*)&ICall_PhysicsBodyComponent_MovePostion},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_RotateRotation",     (void*)&ICall_PhysicsBodyComponent_RotateRotation},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_MoveToPostion",      (void*)&ICall_PhysicsBodyComponent_MoveToPostion},
             { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_RotateToRotation",   (void*)&ICall_PhysicsBodyComponent_RotateToRotation},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_AddForce",			(void*)&ICall_PhysicsBodyComponent_AddForce},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_AddForceAtPos",		(void*)&ICall_PhysicsBodyComponent_AddForceAtPos},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_AddForceAtLocalPos",	(void*)&ICall_PhysicsBodyComponent_AddForceAtLocalPos},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_AddLocalForceAtPos",	(void*)&ICall_PhysicsBodyComponent_AddLocalForceAtPos},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsBodyComponent_AddLocalForceAtLocalPos",(void*)&ICall_PhysicsBodyComponent_AddLocalForceAtLocalPos},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsEntity_CreateShape",          (void*)&ICall_PhysicsEntity_CreateShape},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsEntity_RemoveShapeAt",        (void*)&ICall_PhysicsEntity_RemoveShapeAt},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsEntity_ReplaceShape",         (void*)&ICall_PhysicsEntity_ReplaceShape},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsEntity_GetShapeAt",           (void*)&ICall_PhysicsEntity_GetShapeAt},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsEntity_GetShapeCount",        (void*)&ICall_PhysicsEntity_GetShapeCount},
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_IsOnGround", (void*)&ICall_PhysicsRole_IsOnGround },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_IsFreeFloat", (void*)&ICall_PhysicsRole_IsFreeFloat },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_IsTouchCeil", (void*)&ICall_PhysicsRole_IsTouchCeil },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_IsTouchSides", (void*)&ICall_PhysicsRole_IsTouchSides },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_SetRadius", (void*)&ICall_PhysicsRole_SetRadius },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_GetRadius", (void*)&ICall_PhysicsRole_GetRadius },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_SetHeight", (void*)&ICall_PhysicsRole_SetHeight },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_GetHeight", (void*)&ICall_PhysicsRole_GetHeight },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_SetCenter", (void*)&ICall_PhysicsRole_SetCenter },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_GetCenter", (void*)&ICall_PhysicsRole_GetCenter },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_SetSlopeLimit", (void*)&ICall_PhysicsRole_SetSlopeLimit },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_GetSlopeLimit", (void*)&ICall_PhysicsRole_GetSlopeLimit },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_SetStepOffset", (void*)&ICall_PhysicsRole_SetStepOffset },
			 { "ScriptRuntime.PhysicsBodyComponent::ICall_PhysicsRole_GetStepOffset", (void*)&ICall_PhysicsRole_GetStepOffset },
        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
