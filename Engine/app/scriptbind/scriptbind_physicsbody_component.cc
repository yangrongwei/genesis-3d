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
#ifndef __PHYSX_COMMIT__

#include "stdneb.h"
#include "scriptfeature/inc/script_utility.h"
#include "physXfeature/PhysicsBodyComponent.h"
#include "physXfeature/physicsCore/PhysicsEntity.h"
#include "physXfeature/physicsCore/PhysicsDynamic.h"
#include "physXfeature/physicsCore/PhysicsStatic.h"
#include "physXfeature/physicsCore/PhysicsShape.h"
#include "physXfeature/physicsCore/PhysicsRole.h"

namespace App
{
	static void ICall_PhysicsBodyComponent_SetLinearVelocity(MonoObject* pMonoObj,Math::float3& velocity )
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
 			pEntity.downcast<PhysicsDynamic>()->SetLinearVelocity(velocity);
	}

	static void ICall_PhysicsBodyComponent_GetLinearVelocity(MonoObject* pMonoObj,Math::float3& velocity)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			velocity = pEntity.downcast<PhysicsDynamic>()->GetLinearVelocity();
	}

	static void ICall_PhysicsBodyComponent_SetAngularVelocity(MonoObject* pMonoObj,Math::float3& velocity)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->SetAngularVelocity(velocity);
	}

	static void ICall_PhysicsBodyComponent_GetAngularVelocity(MonoObject* pMonoObj,Math::float3& velocity)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			velocity = pEntity.downcast<PhysicsDynamic>()->GetAngularVelocity();
	}

	static void ICall_PhysicsBodyComponent_SetLinearDamping(MonoObject* pMonoObj,Math::scalar scalar)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->SetLinearDamping(scalar);
	}

	static float ICall_PhysicsBodyComponent_GetLinearDamping(MonoObject* pMonoObj)
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			return pEntity.downcast<PhysicsDynamic>()->GetLinearDamping();
		return 0.f;
	}

	static void ICall_PhysicsBodyComponent_SetAngularDamping(MonoObject* pMonoObj,Math::scalar damping)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->SetAngularDamping(damping);
	}

	static float ICall_PhysicsBodyComponent_GetAngularDamping(MonoObject* pMonoObj)
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			return pEntity.downcast<PhysicsDynamic>()->GetAngularDamping();
		return 0.f;
	}

	static float ICall_PhysicsBodyComponent_GetMass(MonoObject* pMonoObj)
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			return pEntity.downcast<PhysicsDynamic>()->GetMass();
		return 0.f;
	}

	static void ICall_PhysicsBodyComponent_SetDynamic(MonoObject* pMonoObj,mono_bool dynamic)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		if (Utility_MonoBool(dynamic))
		{
			if(self->GetEntityType() != PHYSICSDYNAMIC)
				self->CreateEntity(PHYSICSDYNAMIC);
		}
		else
		{
			if(self->GetEntityType() != PHYSICSSTATIC)
				self->CreateEntity(PHYSICSSTATIC);
		}
	}

	static mono_bool ICall_PhysicsBodyComponent_GetDynamic(MonoObject* pMonoObj)
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			return true;
		return false;
	}

	static void ICall_PhysicsBodyComponent_SetKinematic(MonoObject* pMonoObj,mono_bool Kinematic)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->SetKinematic(Utility_MonoBool(Kinematic));
	}

	static mono_bool ICall_PhysicsBodyComponent_GetKinematic(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			return pEntity.downcast<PhysicsDynamic>()->IsKinematic();
		return false;
	}

	static void ICall_PhysicsBodyComponent_SetUseGravity(MonoObject* pMonoObj,mono_bool UseGravity)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->SetUseGravity(Utility_MonoBool(UseGravity));
	}

	static mono_bool ICall_PhysicsBodyComponent_GetUseGravity(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			return pEntity.downcast<PhysicsDynamic>()->IsUseGravity();
		return true;
	}

	static void ICall_PhysicsBodyComponent_SetCollision(MonoObject* pMonoObj,mono_bool bConllision)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		self->EnablePhysicsSimulate(bConllision>0);
	}

	static mono_bool ICall_PhysicsBodyComponent_GetCollision(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		return self->IsActive();
	}

	static void ICall_PhysicsBodyComponent_SetConstForce(MonoObject* pMonoObj,Math::float3& force)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->SetConstantForce(force);
	}

	static void ICall_PhysicsBodyComponent_GetConstForce(MonoObject* pMonoObj,Math::float3& force)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			force = pEntity.downcast<PhysicsDynamic>()->GetConstantForce();
	}

	static void ICall_PhysicsBodyComponent_SetConstLineVelocity(MonoObject* pMonoObj,Math::float3& force)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->SetConstantVelocity(force);
	}

	static void ICall_PhysicsBodyComponent_GetConstLineVelocity(MonoObject* pMonoObj,Math::float3& force)
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			force = pEntity.downcast<PhysicsDynamic>()->GetConstantVelocity();
	}

	static void ICall_PhysicsBodyComponent_SetConstTorque(MonoObject* pMonoObj,Math::float3& torque)
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->SetConstantTorques(torque);
	}

	static void ICall_PhysicsBodyComponent_GetConstTorque(MonoObject* pMonoObj,Math::float3& torque)
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			torque = pEntity.downcast<PhysicsDynamic>()->GetConstantTorques();
	}

	static void ICall_PhysicsBodyComponent_SetConstAngularVelocity(MonoObject* pMonoObj,Math::float3& torque)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->SetConstantAngularVel(torque);
	}

	static void ICall_PhysicsBodyComponent_GetConstAngularVelocity(MonoObject* pMonoObj,Math::float3& torque)
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			torque = pEntity.downcast<PhysicsDynamic>()->GetConstantAngularVel();
	}

	static void ICall_PhysicsBodyComponent_MovePostion( MonoObject* pMonoObj, Math::float3& pos)
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if (pEntity.isvalid())
		{
			pEntity->Move(pos);
		}
	}

	static void ICall_PhysicsBodyComponent_RotateRotation( MonoObject* pMonoObj, Math::quaternion& qua)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity.isvalid())
			pEntity->Rotate(qua);
	}

	static void ICall_PhysicsBodyComponent_MoveToPostion( MonoObject* pMonoObj, Math::float3& pos)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity.isvalid())
			pEntity->MoveToPostion(pos);
	}

	static void ICall_PhysicsBodyComponent_RotateToRotation( MonoObject* pMonoObj, Math::quaternion& qua)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity.isvalid())
			pEntity->RotateToRotation(qua);
	}

	static void ICall_PhysicsBodyComponent_AddForce(MonoObject* pMonoObj, Math::float3& force, PhysicsDynamic::ForceType forcetype, mono_bool bWakeUp)
	{
 		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->AddForce(force,forcetype,Utility_MonoBool(bWakeUp));
	}

	static void ICall_PhysicsBodyComponent_AddForceAtPos(MonoObject* pMonoObj, Math::float3& force, Math::float3& pos,PhysicsDynamic::ForceType forcetype, mono_bool bWakeUp)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->AddForceAtPos(force,pos,forcetype,Utility_MonoBool(bWakeUp));
	}

	static void ICall_PhysicsBodyComponent_AddForceAtLocalPos(MonoObject* pMonoObj, Math::float3& force, Math::float3& pos, PhysicsDynamic::ForceType forcetype, mono_bool bWakeUp)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->AddForceAtLocalPos(force,pos,forcetype,Utility_MonoBool(bWakeUp));
	}

	static void ICall_PhysicsBodyComponent_AddLocalForceAtPos(MonoObject* pMonoObj, Math::float3& force, Math::float3& pos,PhysicsDynamic::ForceType forcetype, mono_bool bWakeUp)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->AddLocalForceAtPos(force,pos,forcetype,Utility_MonoBool(bWakeUp));
	}

	static void ICall_PhysicsBodyComponent_AddLocalForceAtLocalPos(MonoObject* pMonoObj, Math::float3& force, Math::float3& pos,PhysicsDynamic::ForceType forcetype, mono_bool bWakeUp)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsDynamic::RTTI))
			pEntity.downcast<PhysicsDynamic>()->AddLocalForceAtLocalPos(force,pos,forcetype,Utility_MonoBool(bWakeUp));
	}

	static void ICall_PhysicsEntity_CreateShape( MonoObject* pMonoObj,int shapeType)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity.isvalid())
		{
			if((PhyXShapeType)shapeType == MESHSHAPE && pEntity->IsA(PhysicsDynamic::RTTI))
				pEntity->InsertShape(CONVEXSHAPE,pEntity->GetShapeCount());
			else
				pEntity->InsertShape((PhyXShapeType)shapeType,pEntity->GetShapeCount());
		}
	}

	static void ICall_PhysicsEntity_RemoveShapeAt( MonoObject* pMonoObj,int index)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity.isvalid())
			pEntity->RemoveShape(index);
	}

	static void ICall_PhysicsEntity_ReplaceShape( MonoObject* pMonoObj,int index,int shapeType)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity.isvalid())
			pEntity->ReplaceShape((PhyXShapeType)shapeType,index);
	}

	static MonoObject* ICall_PhysicsEntity_GetShapeAt( MonoObject* pMonoObj,int index)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(!pEntity.isvalid())
			return NULL;
		GPtr<PhysicsShape> shape = pEntity->GetShape(index);
		return CppPointerToScriptObj(shape.get_unsafe());
	}

	static int ICall_PhysicsEntity_GetShapeCount( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity.isvalid())
			return pEntity->GetShapeCount();
		return 0;
	}

	static mono_bool ICall_PhysicsRole_IsOnGround(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			return pEntity.downcast<PhysicsRole>()->IsOnGround();
		return false;
	}

	static mono_bool ICall_PhysicsRole_IsFreeFloat(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			return pEntity.downcast<PhysicsRole>()->IsFreeFloat();
		return false;
	}

	static mono_bool ICall_PhysicsRole_IsTouchCeil(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			return pEntity.downcast<PhysicsRole>()->IsTouchCeil();
		return false;
	}

	static mono_bool ICall_PhysicsRole_IsTouchSides(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			return pEntity.downcast<PhysicsRole>()->IsTouchSides();
		return false;
	}

	static void ICall_PhysicsRole_SetCenter(MonoObject* pMonoObj, Math::float3& center)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			pEntity.downcast<PhysicsRole>()->SetLocalCenter(center);
	}

	static Math::float3 ICall_PhysicsRole_GetCenter(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			return pEntity.downcast<PhysicsRole>()->GetLocalCenter();
		return Math::float3();
	}

	static void ICall_PhysicsRole_SetRadius(MonoObject* pMonoObj, float radius)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			pEntity.downcast<PhysicsRole>()->SetRadius(radius);
	}

	static float ICall_PhysicsRole_GetRadius(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			return pEntity.downcast<PhysicsRole>()->GetRadius();
		return 0.0f;
	}

	static void ICall_PhysicsRole_SetHeight(MonoObject* pMonoObj, float height)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			pEntity.downcast<PhysicsRole>()->SetHeight(height);
	}

	static float ICall_PhysicsRole_GetHeight(MonoObject* pMonoObj) 
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			return pEntity.downcast<PhysicsRole>()->GetHeight();
		return 0.0f;
	}

	static void ICall_PhysicsRole_SetSlopeLimit(MonoObject* pMonoObj, float slope)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			pEntity.downcast<PhysicsRole>()->SetSlopeLimit(slope);
	}

	static float ICall_PhysicsRole_GetSlopeLimit(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			return pEntity.downcast<PhysicsRole>()->GetSlopeLimitDegree();
		return 0.0f;
	}

	static void ICall_PhysicsRole_SetStepOffset(MonoObject* pMonoObj, float offSet)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			pEntity.downcast<PhysicsRole>()->SetStepOffset(offSet);
	}

	static float ICall_PhysicsRole_GetStepOffset(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<PhysicsBodyComponent> self( pMonoObj );
		GPtr<PhysicsEntity> pEntity = self->GetEntity();
		if(pEntity->IsA(PhysicsRole::RTTI))
			return pEntity.downcast<PhysicsRole>()->GetStepOffset();
		return 0.0f;
	}
}
#include "autogen\scriptbind_PhysicsBodyComponent_register.h"
#endif
