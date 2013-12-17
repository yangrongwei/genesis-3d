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
#ifndef __PHYSICSROLE_H__
#define __PHYSICSROLE_H__

#include "math/float3.h"
#include "math/matrix44.h"
#include "PhysicsEntity.h"
#include "PhysicsDeclaration.h"

namespace App
{
	class ControllerHitReport;
	class ControllerBehaviorReport;
	class PhysicsRole : public PhysicsEntity
	{
		__DeclareSubClass(PhysicsRole, PhysicsEntity);

	public:
		PhysicsRole();
		virtual ~PhysicsRole();

		bool OnCreate(GPtr<PhysicsBodyComponent> body);
		bool OnDestory();
		void OnShapeReBuild(PhysicsShape* shape){}
		void OnScaleWithActor();

		void	Save(AppWriter* pSerialize);
		void	Load(Version ver, AppReader* pReader);

	public:
		bool	IsValid() { return m_pController != NULL; }

		void	Move(const Math::float3& dir);
		void	MoveToPostion(const Math::float3& pos);
		void	Rotate(const Math::quaternion& quat);
		void	RotateToRotation(const Math::quaternion& quat);

		bool	CopyFrom(GPtr<PhysicsEntity> src);

		void	Tick(float time);

		PxRigidActor* GetRigidActor();

		GPtr<PhysicsShape> InsertShape(PhyXShapeType type, int index);
		GPtr<PhysicsShape> ReplaceShape(PhyXShapeType type, int index) { return NULL; }
		GPtr<PhysicsShape> RemoveShape(int index) { return NULL; }
		bool			   InsertShape(GPtr<PhysicsShape> pShape, int index) { return false; }
		bool			   ReplaceShape(GPtr<PhysicsShape> pShape, int index) { return false; }
		bool			   RemoveShape(GPtr<PhysicsShape> pShape) { return false; }
	public:
		void SetHeight( Math::scalar height );
		Math::scalar GetHeight() { return m_fHeight; }

		void SetRadius(Math::scalar radius);
		Math::scalar GetRadius() { return m_fRadius; }

		void  SetMinMoveDis(Math::scalar value);
		Math::scalar GetMinMoveDis();

		void SetSlopeLimit(Math::scalar slope);
		Math::scalar GetSlopeLimit();
		Math::scalar GetSlopeLimitDegree();

		void SetStepOffset(Math::scalar offSet);
		Math::scalar GetStepOffset();

		void  SetLocalCenter(Math::float3 center);
		const Math::float3& GetLocalCenter() { return m_vLocalCenter; }

		bool IsOnGround();

		bool IsFreeFloat();

		bool IsTouchCeil();

		bool IsTouchSides();

		PhysicsRoleHitReport* GetHitCallBack() { return m_pCallBack; }
	protected:
		Math::bbox _GetLocalBB();
		Math::scalar _GetRealHeight();
		Math::scalar _GetRealRadius();
	private:
		Math::scalar m_fHeight;
		Math::scalar m_fRadius;
		Math::scalar m_fSlopeLimit;
		Math::scalar m_fStepOffset;
		Math::vector m_vScaleFactor;
		Math::float3 m_vLocalCenter;
		Math::scalar m_fMinMoveDistance;

		int		     m_LastCollisionFlags;

		bool		 m_bInheritActor;

		PxCapsuleController* m_pController;
		ControllerHitReport* m_pHitReport;
		ControllerBehaviorReport* m_pBehaviorReport;
	};

	inline Math::scalar PhysicsRole::GetSlopeLimit()
	{
		return m_fSlopeLimit;
	}

	inline Math::scalar PhysicsRole::GetStepOffset()
	{
		return m_fStepOffset;
	}

	inline void PhysicsRole::SetMinMoveDis(Math::scalar value)
	{
		m_fMinMoveDistance = value;
	}
	inline Math::scalar PhysicsRole::GetMinMoveDis()
	{
		return m_fMinMoveDistance;
	}
}
#endif
