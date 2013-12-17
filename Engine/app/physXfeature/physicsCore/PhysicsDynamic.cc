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
#include "PxRigidDynamic.h"
#include "PhysicsDynamic.h"
#include "PhysicsServer.h"
#include "PhysicsShape.h"
#include "PxScene.h"
#include "PxShape.h"
#include "PxFlags.h"
#include "PxRigidBodyExt.h"
#include "PxRigidDynamic.h"
#include "PhysicsUtil.h"
#include "physXfeature/PhysicsBodyComponent.h"

namespace App
{
	__ImplementClass(PhysicsDynamic, 'PYDY', PhysicsEntity);

	PhysicsDynamic::PhysicsDynamic()
		: m_pPxActor(NULL)
		, m_bJointFather(false)
		, m_bUseGravity(true)
		, m_bKinematic(false)
		, m_fLinearDamping(0.0f)
		, m_fAngularDamping(0.05f)
		, m_vContantForce(0.f)
		, m_vContantVelocity(0.f)
		, m_vContantTorques(0.f)
		, m_vContantAngularVel(0.f)
	{
		m_eType = PHYSICSDYNAMIC;
		m_fMaxAngularVel = PhysicsServer::Instance()->GetMaxAngularVelocity();
		m_fSleepThreshold = PhysicsServer::Instance()->GetSleepThreshold();
	}

	PhysicsDynamic::~PhysicsDynamic()
	{
		OnDestory();
	}

	PxRigidActor* PhysicsDynamic::GetRigidActor()
	{
		return m_pPxActor;
	}

	bool PhysicsDynamic::OnCreate(GPtr<PhysicsBodyComponent> body)
	{
		if ( !m_bJointFather && body.isvalid() && body->GetActor() )
		{
			OnDestory();
			PxPhysics* pSDK = PhysicsServer::Instance()->GetPhysics();
			n_assert(pSDK);
			Math::vector pos = body->GetActor()->GetWorldPosition();
			Math::quaternion rot = body->GetActor()->GetWorldRotation();
			PxTransform _ActorPose(PxVec3(pos.x(), pos.y(), pos.z()), PxQuat(rot.x(), rot.y(), rot.z(), rot.w()));

			m_pPxActor = pSDK->createRigidDynamic(_ActorPose);
			n_assert(m_pPxActor)
				m_pPxActor->userData = body.get();
			m_pPxActor->setActorFlag(PxActorFlag::eVISUALIZATION, true);
			if ( m_bKinematic )
			{
				m_pPxActor->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, m_bKinematic);
			} 
			else
			{
				m_pPxActor->setAngularDamping (m_fAngularDamping);
				m_pPxActor->setLinearDamping(m_fLinearDamping );
				m_pPxActor->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, false);
				m_pPxActor->setMaxAngularVelocity(PhysicsServer::Instance()->GetMaxAngularVelocity());
				m_pPxActor->setSleepThreshold(PhysicsServer::Instance()->GetSleepThreshold());
				m_pPxActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !m_bUseGravity);
			}
			for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
			{
				if (!m_arrPhysicsShapePtr[i]->IsValid())
				{
					m_arrPhysicsShapePtr[i]->OnCreate(body);
				}
				m_arrPhysicsShapePtr[i]->SetPhysicsEntity(this);
				m_arrPhysicsShapePtr[i]->CreatePxShape(m_pPxActor, GetGroupID());
			}
			UpdateEntityMass();

			// Not using
			// CaptureShapeFromChildren();
			return true;
		}
		return m_bJointFather;
	}

	void PhysicsDynamic::CaptureShapeFromChildren()
	{
		if ( m_pPxActor == NULL )
		{
			return;
		}
		for ( int i=0; i<m_pComponent->GetActor()->GetChildCount(); ++i )
		{
			GPtr<PhysicsEntity> _pChildEntity = GetEntityInActor(m_pComponent->GetActor()->GetChild(i));
			if ( _pChildEntity.isvalid() && _pChildEntity->GetType()&m_eType )
			{
				GPtr<PhysicsDynamic> _pDynamic = _pChildEntity.downcast<PhysicsDynamic>();
				if ( !_pDynamic->IsJointFather() )
				{
					continue;
				}
				for ( int i=0; i<_pChildEntity->GetShapeCount(); ++i )
				{
					_pChildEntity->GetShape(i)->CreatePxShape(m_pPxActor, GetGroupID());
				}
			}
		}
	}


	bool PhysicsDynamic::OnDestory()
	{
		if ( IsValid() )
		{
			Super::OnDestory();
			//ReleaseChildShape();
			m_pPxActor->release();
			m_pPxActor = NULL;
		}
		return true;
	}

	void PhysicsDynamic::OnShapeReBuild(PhysicsShape* shape)
	{
		if ( GetRigidActor() && shape != NULL)
		{
			shape->CreatePxShape(GetRigidActor(),m_eGroup);
			UpdateEntityMass();
		}
	}

	void PhysicsDynamic::ReleaseChildShape()
	{
		if ( m_pPxActor == NULL || m_pComponent == NULL || !m_pComponent->GetActor() )
		{
			return;
		}
		for ( int i=0; i<m_pComponent->GetActor()->GetChildCount(); ++i )
		{
			GPtr<PhysicsEntity> _pChildEntity = GetEntityInActor(m_pComponent->GetActor()->GetChild(i));
			if ( _pChildEntity.isvalid() && _pChildEntity->GetType()&m_eType )
			{
				GPtr<PhysicsDynamic> _pDynamic = _pChildEntity.downcast<PhysicsDynamic>();
				if ( !_pDynamic->IsJointFather() )
				{
					continue;
				}
				for ( int i=0; i<_pChildEntity->GetShapeCount(); ++i )
				{
					_pChildEntity->GetShape(i)->ReleasePxShape();
				}
			}
		}
	}


	void PhysicsDynamic::SetKinematic( bool kinematic )
	{
		m_bKinematic = kinematic;
		if ( m_pPxActor )
		{
			m_pPxActor->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, m_bKinematic);
		} 
	}

	void PhysicsDynamic::SetJointFather( bool joint )
	{
		if ( m_bJointFather == joint )
		{
			return;
		}
		m_bJointFather = joint;
		OnCreate(m_pComponent);
	}

	void PhysicsDynamic::SetUseGravity( bool usege )
	{
		m_bUseGravity = usege;
		if ( m_pPxActor && !m_bKinematic )
		{
			m_pPxActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !m_bUseGravity);
			m_pPxActor->wakeUp();
		}
	}

	void PhysicsDynamic::SetLinearVelocity( Math::float3& vel )
	{
		if ( m_pPxActor && !m_bKinematic )
		{
			m_pPxActor->setLinearVelocity(PxVec3(vel.x(),vel.y(),vel.z()));
		}
	}

	void PhysicsDynamic::SetAngularVelocity( Math::float3& vel )
	{
		if ( m_pPxActor && !m_bKinematic )
		{
			m_pPxActor->setAngularVelocity(PxVec3(vel.x(),vel.y(),vel.z()));
		}
	}

	Math::float3 PhysicsDynamic::GetLinearVelocity() const
	{
		Math::float3 vel(0.0f,0.0f,0.0f);
		if ( m_pPxActor && !m_bKinematic )
		{
			PxVec3 v = m_pPxActor->getLinearVelocity();
			vel.x() = v.x;
			vel.y() = v.y;
			vel.z() = v.z;
		}
		return vel;
	}

	Math::float3 PhysicsDynamic::GetAngularVelocity() const
	{
		Math::float3 vel(0.0f,0.0f,0.0f);
		if ( m_pPxActor && !m_bKinematic )
		{
			PxVec3 v = m_pPxActor->getAngularVelocity();
			vel.x() = v.x;
			vel.y() = v.y;
			vel.z() = v.z;
		}
		return vel;
	}

	void PhysicsDynamic::SetLinearDamping( float damping )
	{
		if ( damping < 0.f )
		{
			damping = 0.f;
		}
		m_fLinearDamping = damping;
		if ( m_pPxActor )
		{
			m_pPxActor->setLinearDamping(m_fLinearDamping);
		}
	}

	void PhysicsDynamic::SetAngularDamping( float damping )
	{
		if ( damping < 0.f )
		{
			damping = 0.f;
		}
		m_fAngularDamping = damping;
		if ( m_pPxActor )
		{
			m_pPxActor->setAngularDamping(m_fAngularDamping);
		}
	}

	void PhysicsDynamic::SetMaxAngularVel( float vel )
	{
		if ( vel < 0.f )
		{
			vel = 0.f;
		}
		m_fMaxAngularVel = vel;
		if ( m_pPxActor )
		{
			m_pPxActor->setMaxAngularVelocity(m_fMaxAngularVel);
		}
	}

	void PhysicsDynamic::SetSleepThreshold( float threshold )
	{
		if (threshold < 0.f)
		{
			threshold = 0.f;
		}
		m_fSleepThreshold = threshold;
		if ( m_pPxActor )
		{
			m_pPxActor->setSleepThreshold(m_fSleepThreshold);
		}
	}

	//------------------------------------------------------------------------
	void PhysicsDynamic::AddForce( const Math::float3& force,ForceType forcetype /*= FORCE_NORMAL*/,bool bWakeUp /*= true*/ )
	{
		if (NULL != m_pPxActor && !m_bKinematic)
		{
			m_pPxActor->addForce(PxVec3(force.x(),force.y(),force.z()),(PxForceMode::Enum)forcetype,bWakeUp);
		}
	}
	//------------------------------------------------------------------------
	void PhysicsDynamic::AddForceAtPos(const Math::float3& force,const Math::float3& pos,ForceType forcetype /*= FORCE_NORMAL*/,bool bWakeUp /*= true*/)
	{
		if (NULL != m_pPxActor && !m_bKinematic)
		{
			PxRigidBodyExt::addForceAtPos(*(PxRigidBody*)m_pPxActor, PxVec3(force.x(),force.y(),force.z()), 
				PxVec3(pos.x(),pos.y(),pos.z()), (PxForceMode::Enum)forcetype, bWakeUp);
		}
	}
	//------------------------------------------------------------------------
	void PhysicsDynamic::AddForceAtLocalPos(const Math::float3& force,const Math::float3& pos,ForceType forcetype /*= FORCE_NORMAL*/,bool bWakeUp /*= true*/)
	{
		if (NULL != m_pPxActor && !m_bKinematic)
		{
			PxRigidBodyExt::addForceAtLocalPos(*(PxRigidBody*)m_pPxActor, PxVec3(force.x(),force.y(),force.z()), 
				PxVec3(pos.x(),pos.y(),pos.z()), (PxForceMode::Enum)forcetype, bWakeUp);
		}
	}
	//------------------------------------------------------------------------
	void PhysicsDynamic::AddLocalForceAtPos(const Math::float3& force,const Math::float3& pos,ForceType forcetype /*= FORCE_NORMAL*/,bool bWakeUp /*= true*/)
	{
		if (NULL != m_pPxActor && !m_bKinematic)
		{
			PxRigidBodyExt::addLocalForceAtPos(*(PxRigidBody*)m_pPxActor, PxVec3(force.x(),force.y(),force.z()), 
				PxVec3(pos.x(),pos.y(),pos.z()), (PxForceMode::Enum)forcetype, bWakeUp);
		}
	}
	//------------------------------------------------------------------------
	void PhysicsDynamic::AddLocalForceAtLocalPos(const Math::float3& force,const Math::float3& pos,ForceType forcetype /*= FORCE_NORMAL*/,bool bWakeUp /*= true*/)
	{
		if (NULL != m_pPxActor && !m_bKinematic)
		{
			PxRigidBodyExt::addLocalForceAtLocalPos(*(PxRigidBody*)m_pPxActor, PxVec3(force.x(),force.y(),force.z()), 
				PxVec3(pos.x(),pos.y(),pos.z()), (PxForceMode::Enum)forcetype, bWakeUp);
		}
	}

	void PhysicsDynamic::AddTorque( const Math::float3& torque,ForceType forcetype /*= FORCE_NORMAL*/,bool bWakeUp /*= true*/ )
	{
		if ( NULL != m_pPxActor && !m_bKinematic)
		{
			m_pPxActor->addTorque(PxVec3(torque.x(),torque.y(),torque.z()),(PxForceMode::Enum)forcetype,bWakeUp);
		}
	}

	void PhysicsDynamic::Move( const Math::float3& dir )
	{
		if ( m_pPxActor )
		{
			PxTransform _pos = m_pPxActor->getGlobalPose();
			_pos.p.x += dir.x();
			_pos.p.y += dir.y();
			_pos.p.z += dir.z();
			if ( !m_bKinematic )
			{
				m_pPxActor->setGlobalPose(_pos);
			} 
			else
			{
				m_pPxActor->setKinematicTarget(_pos);
			}
		}
	}

	void PhysicsDynamic::MoveToPostion( const Math::float3& pos )
	{
		if ( m_pPxActor )
		{
			PxTransform _pos = m_pPxActor->getGlobalPose();
			_pos.p.x = pos.x();
			_pos.p.y = pos.y();
			_pos.p.z = pos.z();
			m_pPxActor->setGlobalPose(_pos);
		}
	}

	void PhysicsDynamic::Rotate( const Math::quaternion& quat )
	{
		if ( m_pPxActor )
		{
			PxTransform _pos = m_pPxActor->getGlobalPose();
			Math::quaternion _quat = Math::quaternion::multiply(PxQuatToQuat(_pos.q), quat);
			_pos.q.x = _quat.x();
			_pos.q.y = _quat.y();
			_pos.q.z = _quat.z();
			_pos.q.w = _quat.w();
			if ( !m_bKinematic )
			{
				m_pPxActor->setGlobalPose(_pos);
			} 
			else
			{
				m_pPxActor->setKinematicTarget(_pos);
			}
		}
	}

	void PhysicsDynamic::RotateToRotation( const Math::quaternion& quat )
	{
		if ( m_pPxActor )
		{
			PxTransform _pos = m_pPxActor->getGlobalPose();
			_pos.q.x = quat.x();
			_pos.q.y = quat.y();
			_pos.q.z = quat.z();
			_pos.q.w = quat.w();
			m_pPxActor->setGlobalPose(_pos);
		}
	}

	void PhysicsDynamic::Tick( float time )
	{
		if ( m_pPxActor )
		{
			if ( !m_bKinematic )
			{
				if ( m_vContantForce.length() > 0.01f )
				{
					m_pPxActor->addForce((PxVec3&)m_vContantForce);
				}
				else if ( m_vContantVelocity.length() > 0.01f )
				{
					m_pPxActor->setLinearVelocity((PxVec3&)m_vContantVelocity);
				}
				if ( m_vContantTorques.length() > 0.01f )
				{
					m_pPxActor->addTorque((PxVec3&)m_vContantTorques);
				}
				else if ( m_vContantAngularVel.length() > 0.01f )
				{
					m_pPxActor->setAngularVelocity((PxVec3&)m_vContantAngularVel);
				}
			}
			if ( m_pComponent && m_pComponent->GetActor() )
			{
				PxTransform _GlobalPos = m_pPxActor->getGlobalPose();

				Math::float4     pos(_GlobalPos.p.x, _GlobalPos.p.y, _GlobalPos.p.z, 1.0f);
				Math::quaternion rot(_GlobalPos.q.x, _GlobalPos.q.y, _GlobalPos.q.z, _GlobalPos.q.w);

				m_pComponent->GetActor()->SetWorldPosition(pos);
				m_pComponent->GetActor()->SetWorldRotation(rot);
			}
		}
	}

	bool PhysicsDynamic::CopyFrom( GPtr<PhysicsEntity> src )
	{
		if ( !src.isvalid() || src->GetType() != m_eType )
		{
			return false;
		}
		Super::CopyFrom(src);
		GPtr<PhysicsDynamic> _pSrc = src.downcast<PhysicsDynamic>();
		this->m_bJointFather		= _pSrc->IsJointFather();
		this->m_bUseGravity			= _pSrc->IsUseGravity();
		this->m_bKinematic			= _pSrc->IsKinematic();
		this->m_fLinearDamping		= _pSrc->GetLinearDamping();
		this->m_fAngularDamping		= _pSrc->GetAngularDamping();
		this->m_fMaxAngularVel		= _pSrc->GetMaxAngularVel();
		this->m_fSleepThreshold		= _pSrc->GetSleepThreshold();
		this->m_vContantForce		= _pSrc->GetConstantForce();
		this->m_vContantVelocity	= _pSrc->GetConstantVelocity();
		this->m_vContantTorques		= _pSrc->GetConstantTorques();
		this->m_vContantAngularVel	= _pSrc->GetConstantAngularVel();

		return true;
	}

	void PhysicsDynamic::UpdateEntityMass()
	{
		if (m_pPxActor != NULL)
		{
			int cnt = m_arrPhysicsShapePtr.Size();
			int nb = m_pPxActor->getNbShapes();
			PxReal* fDensities = new PxReal[nb];
			PxShape** mShapes = new PxShape*[nb];
			m_pPxActor->getShapes(mShapes,nb*sizeof(PxShape*));
			int k=0;
			for(int i=0;i<nb;i++)
			{
				int j=0;
				for(j=0;j<cnt;j++)
				{
					if ( !m_arrPhysicsShapePtr[j]->IsValid() )
					{
						continue;
					}
					if(m_arrPhysicsShapePtr[j]->GetName() == mShapes[i]->getName())
						break;
				}
				if(j>=cnt)
				{
					delete []fDensities;
					delete []mShapes;
					m_pPxActor->setMass(0.01f);
					return;
				}
				if((PxU8)(mShapes[i]->getFlags() & PxShapeFlag::eSIMULATION_SHAPE) == 0)
				{
					continue;
				}
				fDensities[k++] = m_arrPhysicsShapePtr[j]->GetDensity();
			}
			if(k<=0)
			{
				delete []fDensities;
				delete []mShapes;
				m_pPxActor->setMass(0.01f);
				return;
			}
			PxRigidBodyExt::updateMassAndInertia(*m_pPxActor, fDensities,k);
			delete []fDensities;
			delete []mShapes;
		} 
	}

	float PhysicsDynamic::GetMass()
	{
		if ( m_pPxActor == NULL )
		{
			return 0.01f;
		}
		bool _needUpdate = false;
		for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
		{
			if ( !m_arrPhysicsShapePtr[i]->IsValid() )
			{
				//m_pPxActor->setMass(0.01f);
				//return 0.01f;
				continue;
			}
			if ( m_arrPhysicsShapePtr[i]->IsMassUpdate() )
			{
				_needUpdate = true;
				m_arrPhysicsShapePtr[i]->UpdateMass();
			}
		}
		if ( _needUpdate )
		{
			UpdateEntityMass();
		}
		return m_pPxActor->getMass();
	}

	void PhysicsDynamic::Save( AppWriter* pSerialize )
	{
		Super::Save(pSerialize);
		pSerialize->SerializeBool("JointFather", m_bJointFather);
		pSerialize->SerializeBool("UseGravity", m_bUseGravity);
		pSerialize->SerializeBool("Kinematic", m_bKinematic);
		pSerialize->SerializeFloat("LinearDamp", m_fLinearDamping);
		pSerialize->SerializeFloat("AngularDamp", m_fAngularDamping);
		pSerialize->SerializeFloat("MaxAngularVel", m_fMaxAngularVel);
		pSerialize->SerializeFloat("SleepThrehold", m_fSleepThreshold);
		pSerialize->SerializeFloat3("ContantForce", m_vContantForce);
		pSerialize->SerializeFloat3("ContantVelocity", m_vContantVelocity);
		pSerialize->SerializeFloat3("ContantTorques", m_vContantTorques);
		pSerialize->SerializeFloat3("ContantAngularVel", m_vContantAngularVel);
	}

	void PhysicsDynamic::Load( Version ver, AppReader* pReader )
	{
		Super::Load(ver,pReader);
		pReader->SerializeBool("JointFather", m_bJointFather);
		pReader->SerializeBool("UseGravity", m_bUseGravity);
		pReader->SerializeBool("Kinematic", m_bKinematic);
		pReader->SerializeFloat("LinearDamp", m_fLinearDamping);
		pReader->SerializeFloat("AngularDamp", m_fAngularDamping);
		pReader->SerializeFloat("MaxAngularVel", m_fMaxAngularVel);
		pReader->SerializeFloat("SleepThrehold", m_fSleepThreshold);
		pReader->SerializeFloat3("ContantForce", m_vContantForce);
		pReader->SerializeFloat3("ContantVelocity", m_vContantVelocity);
		pReader->SerializeFloat3("ContantTorques", m_vContantTorques);
		pReader->SerializeFloat3("ContantAngularVel", m_vContantAngularVel);
	}

}

#endif