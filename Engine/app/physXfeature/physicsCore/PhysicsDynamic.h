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
#ifndef __PHYSICSDYNAMIC_H__
#define __PHYSICSDYNAMIC_H__

#include "stdneb.h"
#include "PhysicsEntity.h"
#include "PhysicsDeclaration.h"

namespace App
{
	class PhysicsBodyComponent;
	using namespace physx;

	class PhysicsDynamic : public PhysicsEntity
	{
		__DeclareSubClass(PhysicsDynamic, PhysicsEntity)
	public:
		enum ForceType
		{
			FORCE_NORMAL,
			FORCE_IMPULSE,
			FORCE_VELOCITY_CHANGE,
			FORCE_ACCELERATION
		};

		PhysicsDynamic();
		virtual ~PhysicsDynamic();

	public:
		bool	OnCreate(GPtr<PhysicsBodyComponent> body);
		bool	OnDestory();
		void	OnShapeReBuild(PhysicsShape* shape);

		void	Save(AppWriter* pSerialize);
		void	Load(Version ver, AppReader* pReader);

	public:
		bool	IsValid() { return m_pPxActor != NULL; }
		bool	IsJointFather() { return m_bJointFather; }
		bool	IsUseGravity() { return m_bUseGravity; }
		bool	IsKinematic() { return m_bKinematic; }
		void	SetJointFather(bool joint);
		void	SetUseGravity(bool usege);
		void	SetKinematic(bool kinematic);

		float	GetMass();

		void	SetLinearDamping(float damping);
		float	GetLinearDamping() { return m_fLinearDamping; }
		void	SetAngularDamping(float damping);
		float	GetAngularDamping() { return m_fAngularDamping; }
		void	SetMaxAngularVel(float vel);
		float	GetMaxAngularVel() { return m_fMaxAngularVel; }
		void	SetSleepThreshold(float threshold);
		float	GetSleepThreshold() { return m_fSleepThreshold; }

		void SetConstantForce(const Math::float3& force) { m_vContantForce = force; }
		const Math::float3& GetConstantForce() { return m_vContantForce; }
		void SetConstantVelocity(const Math::float3& velocity) { m_vContantVelocity = velocity; }
		const Math::float3& GetConstantVelocity() { return m_vContantVelocity; }
		void SetConstantTorques(const Math::float3& torques) { m_vContantTorques = torques; }
		const Math::float3& GetConstantTorques() { return m_vContantTorques; }
		void SetConstantAngularVel(const Math::float3& velocity) { m_vContantAngularVel = velocity; }
		const Math::float3& GetConstantAngularVel() { return m_vContantAngularVel; }
		void SetLinearVelocity(Math::float3& vel);
		void SetAngularVelocity(Math::float3& vel);
		Math::float3 GetLinearVelocity() const;
		Math::float3 GetAngularVelocity() const;

		void AddForce(const Math::float3& force,ForceType forcetype = FORCE_NORMAL,bool bWakeUp = true);
		void AddForceAtPos(const Math::float3& force,const Math::float3& pos,ForceType forcetype = FORCE_NORMAL,bool bWakeUp = true);
		void AddForceAtLocalPos(const Math::float3& force,const Math::float3& pos,ForceType forcetype = FORCE_NORMAL,bool bWakeUp = true);
		void AddLocalForceAtPos(const Math::float3& force,const Math::float3& pos,ForceType forcetype = FORCE_NORMAL,bool bWakeUp = true);
		void AddLocalForceAtLocalPos(const Math::float3& force,const Math::float3& pos,ForceType forcetype = FORCE_NORMAL,bool bWakeUp = true);
		void AddTorque(const Math::float3& torque,ForceType forcetype = FORCE_NORMAL,bool bWakeUp = true);

		void	Move(const Math::float3& dir);
		void	MoveToPostion(const Math::float3& pos);
		void	Rotate(const Math::quaternion& quat);
		void	RotateToRotation(const Math::quaternion& quat);

		void	Tick(float time);

		bool	CopyFrom(GPtr<PhysicsEntity> src);
	protected:
		void	UpdateEntityMass();
		PxRigidActor* GetRigidActor();
		void	CaptureShapeFromChildren();
		void	ReleaseChildShape();

	private:
		PxRigidDynamic* m_pPxActor;

		bool		m_bJointFather;
		bool		m_bUseGravity;
		bool		m_bKinematic;
		float		m_fLinearDamping;
		float		m_fAngularDamping;
		float		m_fMaxAngularVel;
		float		m_fSleepThreshold;
		Math::float3 m_vContantForce;
		Math::float3 m_vContantVelocity;
		Math::float3 m_vContantTorques;
		Math::float3 m_vContantAngularVel;
	};
}
#endif