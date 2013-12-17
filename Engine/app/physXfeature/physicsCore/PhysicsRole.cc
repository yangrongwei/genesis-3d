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
#include "PhysicsRole.h"
#include "PhysicsUtil.h"
#include "appframework/actor.h"
#include "PxShape.h"
#include "PxRigidDynamic.h"
#include "PxCapsuleController.h"
#include "PxControllerManager.h"
#include "PxControllerBehavior.h"
#include "PhysicsServer.h"
#include "PhysicsShape.h"
#include "PhysicsCapsuleShape.h"
#include "basegamefeature/managers/timesource.h"
#include "physXfeature/PhysicsBodyComponent.h"

namespace App
{
	__ImplementClass(PhysicsRole, 'PYRL', PhysicsEntity);

	class ControllerHitReport : public PxUserControllerHitReport
	{
	public:
		ControllerHitReport(PhysicsRole* target): m_pTarget(target) {}
		~ControllerHitReport() { m_pTarget = NULL; }

		void onShapeHit(const PxControllerShapeHit& hit);
		void onControllerHit(const PxControllersHit& hit);
		void onObstacleHit(const PxControllerObstacleHit& hit) {}
	private:
		PhysicsRole* m_pTarget;
	};

	class ControllerBehaviorReport : public PxControllerBehaviorCallback
	{
	public:
		ControllerBehaviorReport(PhysicsRole* target): m_pTarget(target) {}
		~ControllerBehaviorReport() { m_pTarget = NULL; }

		PxU32 getBehaviorFlags(const PxShape&){ return 0; }
		PxU32 getBehaviorFlags(const PxController&){ return 0; }
		PxU32 getBehaviorFlags(const PxObstacle&){ return 0; }
	private:
		PhysicsRole* m_pTarget;
	};

	void ControllerHitReport::onShapeHit( const PxControllerShapeHit& hit )
	{
		if ( m_pTarget )
		{
			PhysicsBodyComponent* _pMyBody = (PhysicsBodyComponent*)(m_pTarget->GetRigidActor()->userData);
			PhysicsBodyComponent* _pBody = (PhysicsBodyComponent*)(hit.shape->getActor().userData);

			if ( _pBody && _pMyBody )
			{
				GPtr<UserReportPair> _pairs = UserReportPair::Create(_pMyBody, _pBody);
				_pMyBody->SendMessageToScript<UserReportPair>("OnControllerShapeCollision", *_pairs.get_unsafe());
				_pBody->SendMessageToScript<UserReportPair>("OnControllerShapeCollision", *_pairs.get_unsafe());
			}

			if ( m_pTarget->GetHitCallBack() && _pBody )
			{
				if (_pBody->GetEntityType() == PHYSICSDYNAMIC)
				{
					m_pTarget->GetHitCallBack()->onHitWithDynamic(_pBody->GetEntity());
				}
				else
				{
					m_pTarget->GetHitCallBack()->onHitWithStatic(_pBody->GetEntity());
				}
			}
		}
	}

	void ControllerHitReport::onControllerHit( const PxControllersHit& hit )
	{
		if ( m_pTarget )
		{
			PhysicsBodyComponent* _pMyBody = (PhysicsBodyComponent*)(m_pTarget->GetRigidActor()->userData);
			PhysicsBodyComponent* _pBody = (PhysicsBodyComponent*)(hit.other->getUserData());

			if ( _pBody && _pMyBody )
			{
				GPtr<UserReportPair> _pairs = UserReportPair::Create(_pMyBody, _pBody);
				_pMyBody->SendMessageToScript<UserReportPair>("OnControllerShapeCollision", *_pairs.get_unsafe());
				_pBody->SendMessageToScript<UserReportPair>("OnControllerShapeCollision", *_pairs.get_unsafe());
			}

			if (m_pTarget->GetHitCallBack() && _pBody && _pBody->GetEntityType() == PHYSICSCONTROLLER)
			{
				m_pTarget->GetHitCallBack()->onHitWithRole(_pBody->GetEntity());
			}
		}
	}

	PhysicsRole::PhysicsRole()
		:m_pController(NULL),
		m_pHitReport(NULL),
		m_fRadius(0.5f),
		m_fHeight(1.0f),
		m_fStepOffset(0.5f),
		m_pBehaviorReport(NULL),
		m_fMinMoveDistance(0.01f),
		m_fSlopeLimit(0.707f),
		m_LastCollisionFlags(0),
		m_vScaleFactor(1.0f,1.0f,1.0f),
		m_vLocalCenter(0.f,0.f,0.f),
		m_bInheritActor(true)
	{
		m_eType = PHYSICSCONTROLLER;
		m_pHitReport = new ControllerHitReport(this);
		m_pBehaviorReport = new ControllerBehaviorReport(this);
	}

	PhysicsRole::~PhysicsRole()
	{
		OnDestory();
		if ( m_pHitReport )
		{
			delete m_pHitReport;
		}
		if( m_pBehaviorReport )
		{
			delete m_pBehaviorReport;
		}
	}

	bool PhysicsRole::OnCreate(GPtr<PhysicsBodyComponent> body)
	{
		if (body.isvalid() && body->GetActor())
		{
			OnDestory();
			PxCapsuleControllerDesc desc;
			const float minSize = 0.01f;
			if ( m_bInheritActor )
			{
				Math::bbox box = _GetLocalBB();
				Math::vector extents = box.extents(); 
				m_fRadius = Math::n_max (extents.x(), extents.z());
				m_fHeight = extents.y() * 2.0f;
				m_bInheritActor = false;
			}
			Math::scalar height = _GetRealHeight();
			Math::scalar radius = _GetRealRadius();
			if(height < minSize)
			{
				desc.height     = minSize;
			}
			else
			{
				desc.height     = height;
			}

			if(radius < minSize)
			{
				desc.radius     = minSize;
			}
			else
			{
				desc.radius     = radius;
			}

			if(m_IsCopyed)
			{
				desc.height = Math::n_max(Math::n_abs(m_fHeight*m_vScaleFactor.y()), 0.01f);
				desc.radius = Math::n_max(Math::n_abs(m_fRadius*Math::n_max(m_vScaleFactor.x(),m_vScaleFactor.z())), 0.01f);
			}
			
			if(m_fStepOffset > 2*desc.radius + desc.height - 0.0001f)
			{
				m_fStepOffset = 2*desc.radius + desc.height - 0.0001f;//必须要减个很小的数，否则会有问题。
			}

			desc.material	= PhysicsServer::Instance()->GetDefaultPxMaterial();
			Math::vector worldPos =body->GetActor()->GetWorldPosition();

			Math::float4 cPos(worldPos.x(), worldPos.y(), worldPos.z(), 1.0f);
			PxExtendedVec3 NxEV3 = PxExtendedVec3(cPos.x()+m_vLocalCenter.x(), cPos.y()+m_vLocalCenter.y()
				, cPos.z()+m_vLocalCenter.z());
			desc.position        = NxEV3;
			desc.stepOffset		 = m_fStepOffset;
			desc.slopeLimit			= m_fSlopeLimit;
			desc.contactOffset			= 0.01f;
			desc.invisibleWallHeight	= 0.0f;
			desc.maxJumpHeight			= 2.0f;
			desc.scaleCoeff            = 0.9f;
			desc.climbingMode          = PxCapsuleClimbingMode::eEASY;
			desc.userData        = this;
			desc.callback        = m_pHitReport;
			desc.behaviorCallback= m_pBehaviorReport;

			PxControllerManager* pManager= PhysicsServer::Instance()->GetControllerManager();
			PxCapsuleController* pController = (PxCapsuleController*)pManager->createController(*PhysicsServer::Instance()->GetPhysics(), PhysicsServer::Instance()->GetPhysXScene(), desc);
			if(!pController)
				return false;
			m_pController = pController;
			PxRigidDynamic* pActor = m_pController->getActor();
			pActor->userData = body.get();
			n_assert(pActor->getNbShapes() != 0);
			m_pController->setClimbingMode(PxCapsuleClimbingMode::eCONSTRAINED);

			// Make sure that the PhysicsShape can get the right information when it be created; 
			{
				Math::float3 worldPos;
				worldPos.x()=body->GetActor()->GetWorldPosition().x();
				worldPos.y()=body->GetActor()->GetWorldPosition().y();
				worldPos.z()=body->GetActor()->GetWorldPosition().z();
				this->RotateToRotation(body->GetActor()->GetWorldRotation());
				this->MoveToPostion(worldPos);
			}
			for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
			{
				PxShape* _pPxShape = NULL;
				pActor->getShapes(&_pPxShape, 1, 0);
				m_arrPhysicsShapePtr[i]->SetPxShape(_pPxShape);
				m_arrPhysicsShapePtr[i]->SetPhysicsEntity(this);
				m_arrPhysicsShapePtr[i]->m_pGeometry = &_pPxShape->getGeometry().any();
				m_arrPhysicsShapePtr[i]->ScaleWithActor(body->GetActor()->GetWorldScale());
			}

			m_pComponent = body.get();
			m_IsCopyed = false;
			return true;
		}
		return false;
	}

	bool PhysicsRole::OnDestory()
	{
		if ( IsValid() )
		{
			for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
			{
				m_arrPhysicsShapePtr[i]->SetPxShape(NULL);
				m_arrPhysicsShapePtr[i]->m_pGeometry = NULL;
				m_arrPhysicsShapePtr[i]->OnDestory();
			}
			m_pController->release();
			m_pController = NULL;
		}
		return true;
	}

	void PhysicsRole::OnScaleWithActor()
	{
		Math::scalar height = _GetRealHeight();
		Math::scalar radius = _GetRealRadius();
		if(m_IsCopyed)
		{
			height = Math::n_max(Math::n_abs(m_fHeight*m_vScaleFactor.y()), 0.01f);
			radius = Math::n_max(Math::n_abs(m_fRadius*Math::n_max(m_vScaleFactor.x(),m_vScaleFactor.z())), 0.01f);
		}
		if(m_fStepOffset > 2*radius + height)
		{
			m_fStepOffset = 2*radius + height;
		}
	}

	bool PhysicsRole::IsOnGround()
	{
		if (m_LastCollisionFlags & PxControllerFlag::eCOLLISION_DOWN)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool PhysicsRole::IsFreeFloat()
	{
		if (m_LastCollisionFlags == 0)
		{
			return true;
		} 
		else
		{
			return false;
		}
	}

	bool PhysicsRole::IsTouchCeil()
	{
		if (m_LastCollisionFlags & PxControllerFlag::eCOLLISION_UP)
		{
			return true;
		} 
		else
		{
			return false;
		}
	}

	bool PhysicsRole::IsTouchSides()
	{
		if (m_LastCollisionFlags & PxControllerFlag::eCOLLISION_SIDES)
		{
			return true;
		} 
		else
		{
			return false;
		}
	}

	void PhysicsRole::SetRadius( Math::scalar radius )
	{
		if ( radius < 0.0f )
		{
			return;
		}
		m_fRadius = radius;

		for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
		{
			if ( m_arrPhysicsShapePtr[i]->IsA(PhysicsCapsuleShape::RTTI) )
			{
				GPtr<PhysicsCapsuleShape> _pCapsule = m_arrPhysicsShapePtr[i].downcast<PhysicsCapsuleShape>();
				_pCapsule->m_Radius = radius;
			}
		}

		if (m_pController)
		{
			float _realRadius = m_fRadius;
			if ( m_pComponent && m_pComponent->GetActor() )
			{
				const Math::vector& _scale = m_pComponent->GetActor()->GetWorldScale();
				_realRadius *= Math::n_max(_scale.x(), _scale.y());
			}
			m_pController->setRadius(_realRadius);
		}
	}

	void PhysicsRole::SetHeight(Math::scalar height)
	{
		if ( height < 0.0f )
		{
			return;
		}
		m_fHeight = height;

		for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
		{
			if ( m_arrPhysicsShapePtr[i]->IsA(PhysicsCapsuleShape::RTTI) )
			{
				GPtr<PhysicsCapsuleShape> _pCapsule = m_arrPhysicsShapePtr[i].downcast<PhysicsCapsuleShape>();
				_pCapsule->m_Height = height;
			}
		}

		if (m_pController)
		{
			float _realHeight = m_fHeight;
			if ( m_pComponent && m_pComponent->GetActor() )
			{
				_realHeight *= m_pComponent->GetActor()->GetWorldScale().y();
			}
			m_pController->setHeight( Math::n_max(_realHeight, 0.01f) );
		}
	}

	void PhysicsRole::SetSlopeLimit(Math::scalar slope)
	{
		Math::scalar cosSlope = Math::n_cos(Math::n_deg2rad(slope));

		m_fSlopeLimit = cosSlope;
		m_fSlopeLimit = Math::n_clamp(m_fSlopeLimit,0.f,FLT_MAX);

		if (m_pController)
		{
			m_bInheritActor = false;
			OnDestory();
			OnCreate(m_pComponent);
		}
	}
	Math::scalar PhysicsRole::GetSlopeLimitDegree()
	{
		if(Math::n_nearequal(m_fSlopeLimit,0.707f,0.001f))
			return 45.0f;
		Math::scalar value = Math::n_acos(m_fSlopeLimit);
		value              = Math::n_rad2deg(value);
		return value;
	}


	void PhysicsRole::SetStepOffset(Math::scalar offSet)
	{
		Math::scalar radius = _GetRealRadius();
		Math::scalar height = _GetRealHeight();
		if(offSet > radius*2 + height)
			offSet = radius*2 + height;

		m_fStepOffset = offSet;

		if (m_IsActive)
		{
			m_pController->setStepOffset(offSet);
		}
	}

	Math::scalar PhysicsRole::_GetRealHeight()
	{
		float _realHeight = m_fHeight;
		if ( m_pComponent && m_pComponent->GetActor() )
		{
			_realHeight *= m_pComponent->GetActor()->GetWorldScale().y();
		}
		return Math::n_max(Math::n_abs(_realHeight), 0.01f);
	}

	Math::scalar PhysicsRole::_GetRealRadius()
	{
		float _realRadius = m_fRadius;
		if ( m_pComponent && m_pComponent->GetActor() )
		{
			const Math::vector& _scale = m_pComponent->GetActor()->GetWorldScale();
			_realRadius *= Math::n_max(_scale.x(), _scale.z());
		}
		return Math::n_max(Math::n_abs(_realRadius), 0.01f);
	}


	Math::bbox PhysicsRole::_GetLocalBB()
	{
		if(!m_pComponent)
			return Math::bbox();
		Actor* mActor = m_pComponent->GetActor();
		if(!mActor)
			return Math::bbox();
		Math::bbox box = mActor->GetLocalBoundingBox();
		if (Math::n_nearequal(box.size().length(),0.0f,0.001f))
			return Math::bbox();
		return box;
	}

	void PhysicsRole::Move( const Math::float3& dir )
	{
		if ( m_pController )
		{
			m_LastCollisionFlags = m_pController->move((PxVec3&)dir, m_fMinMoveDistance, (float)GameTime::Instance()->GetFrameTime(), PxControllerFilters());
			PxExtendedVec3 _pPos = m_pController->getPosition();
			PxTransform _pActorPos = m_pController->getActor()->getGlobalPose();
			_pActorPos.p = PxVec3((PxReal)_pPos.x,(PxReal)_pPos.y,(PxReal)_pPos.z);
			m_pController->getActor()->setGlobalPose(_pActorPos);
		}
	}

	void PhysicsRole::MoveToPostion( const Math::float3& pos )
	{
		if ( m_pController )
		{
			m_pController->setPosition(Float3ToPxExtended(pos+m_vLocalCenter));
			PxExtendedVec3 _pPos = m_pController->getPosition();
			//PxExtendedVec3 _pPos = Float3ToPxExtended(pos + m_vLocalCenter);
			PxTransform _pActorPos = m_pController->getActor()->getGlobalPose();
			_pActorPos.p = PxVec3((PxReal)_pPos.x,(PxReal)_pPos.y,(PxReal)_pPos.z);
 			m_pController->getActor()->setGlobalPose(_pActorPos);
		}
	}

	void PhysicsRole::Rotate( const Math::quaternion& quat )
	{
		if ( m_pController && m_pController->getActor() )
		{
			Math::vector f4Axis(0.f,0.f,1.f);
			Math::scalar sRadian = (Math::scalar)(0.5f*PI);
			Math::quaternion _tempRot = Math::quaternion::rotationaxis(f4Axis,sRadian);
			_tempRot = Math::quaternion::multiply(quat,_tempRot);
			PxTransform _pos = m_pController->getActor()->getGlobalPose();
			_tempRot = Math::quaternion::multiply(quat,Math::quaternion(_pos.q.x,_pos.q.y,_pos.q.z,_pos.q.w));
			_pos.q.x = _tempRot.x();
			_pos.q.y = _tempRot.y();
			_pos.q.z = _tempRot.z();
			_pos.q.w = _tempRot.w();
			m_pController->getActor()->setGlobalPose(_pos);
		}
	}

	void PhysicsRole::RotateToRotation( const Math::quaternion& quat )
	{
		if ( m_pController && m_pController->getActor() )
		{
			/*Math::vector f4Axis(0.f,0.f,1.f);
			Math::scalar sRadian = (Math::scalar)(0.5f*PI);
			Math::quaternion _tempRot = Math::quaternion::rotationaxis(f4Axis,sRadian);
			_tempRot = Math::quaternion::multiply(quat,_tempRot);
			PxTransform _pos = m_pController->getActor()->getGlobalPose();
			_pos.q.x = _tempRot.x();
			_pos.q.y = _tempRot.y();
			_pos.q.z = _tempRot.z();
			_pos.q.w = _tempRot.w();*/
			Math::vector dir = quat * Math::vector(0.0f,1.0f,0.0f);
			PxVec3 pDir(dir.x(),dir.y(),dir.z());
			pDir.normalize();
			m_pController->setUpDirection(pDir);
			//m_pController->getActor()->setGlobalPose(_pos);
		}
	}

	inline PxRigidActor* PhysicsRole::GetRigidActor()
	{
		if ( m_pController )
		{
			return m_pController->getActor();
		}
		return NULL;
	}

	bool PhysicsRole::CopyFrom( GPtr<PhysicsEntity> src )
	{
		if ( !src.isvalid() || src->GetType() != m_eType )
		{
			return false;
		}
		Super::CopyFrom(src);
		GPtr<PhysicsRole> _pSrc = src.downcast<PhysicsRole>();
		this->m_fMinMoveDistance = _pSrc->GetMinMoveDis();
		this->m_fSlopeLimit		 = _pSrc->GetSlopeLimit();
		this->m_fStepOffset		 = _pSrc->GetStepOffset();
		this->m_fHeight			 = _pSrc->GetHeight();
		this->m_fRadius			 = _pSrc->GetRadius();
		this->m_vLocalCenter	 = _pSrc->m_vLocalCenter;
		if(_pSrc->GetBodyCom() && _pSrc->GetBodyCom()->GetActor())
			this->m_vScaleFactor = _pSrc->GetBodyCom()->GetActor()->GetWorldScale();
		m_bInheritActor = false;
		m_IsCopyed = true;
		return true;
	}

	void PhysicsRole::Tick( float time )
	{
		if ( m_pController && m_pComponent && m_pComponent->GetActor() )
		{
			/*PxTransform _GlobalPos = m_pController->getActor()->getGlobalPose();
			Math::vector _pos((float)_GlobalPos.p.x-m_vLocalCenter.x(), (float)_GlobalPos.p.y-m_vLocalCenter.y(),
				(float)_GlobalPos.p.z-m_vLocalCenter.z());
			Math::quaternion _rot(_GlobalPos.q.x, _GlobalPos.q.y, _GlobalPos.q.z, _GlobalPos.q.w);
			Math::vector f4Axis(0.f,0.f,1.f);
			Math::scalar sRadian = (Math::scalar)(-0.5f*PI);
			Math::quaternion _tempRot = Math::quaternion::rotationaxis(f4Axis,sRadian);
			_tempRot = Math::quaternion::multiply(_rot,_tempRot);*/
			
			PxExtendedVec3 _GlobalPos = m_pController->getPosition();
			Math::vector _pos((float)_GlobalPos.x-m_vLocalCenter.x(), (float)_GlobalPos.y-m_vLocalCenter.y(),
				(float)_GlobalPos.z-m_vLocalCenter.z());
			PxVec3 _GlobalRot = m_pController->getUpDirection();
			Math::quaternion _rot = Math::quaternion::identity();
			_rot = _rot * Math::vector(_GlobalRot.x,_GlobalRot.y,_GlobalRot.z);//(_GlobalRot.x, _GlobalRot.y, _GlobalRot.z, 1.0f);
			m_pComponent->GetActor()->SetWorldPosition(_pos);
			m_pComponent->GetActor()->SetWorldRotation(_rot);
		}
	}

	void PhysicsRole::Save( AppWriter* pSerialize )
	{
		Super::Save(pSerialize);
		pSerialize->SerializeFloat("fMinMoveDistance", m_fMinMoveDistance);
		pSerialize->SerializeFloat("fSlopeLimit", m_fSlopeLimit);
		pSerialize->SerializeFloat("fStepOffset", m_fStepOffset);
		pSerialize->SerializeFloat("fHeight", m_fHeight);
		pSerialize->SerializeFloat("fRadius", m_fRadius);
		pSerialize->SerializeFloat3("CLCentre", m_vLocalCenter);
	}

	void PhysicsRole::Load( Version ver, AppReader* pReader )
	{
		Super::Load(ver,pReader);
		pReader->SerializeFloat("fMinMoveDistance", m_fMinMoveDistance);
		pReader->SerializeFloat("fSlopeLimit", m_fSlopeLimit);
		pReader->SerializeFloat("fStepOffset", m_fStepOffset);
		pReader->SerializeFloat("fHeight", m_fHeight);
		pReader->SerializeFloat("fRadius", m_fRadius);
		if (ver <= 6)
		{
			bool _detect;
			pReader->SerializeBool("bDetectCollision", _detect);
		}
		if (ver > 5)
		{
			pReader->SerializeFloat3("CLCentre", m_vLocalCenter);
		}
		m_bInheritActor = false;
	}

	GPtr<PhysicsShape> PhysicsRole::InsertShape( PhyXShapeType type, int index )
	{
		if ( index == 0 )
		{
			GPtr<PhysicsShape> _pShape = PhysicsShape::Create(type);
			_pShape->SetPhysicsEntity(this);
			GPtr<PhysicsCapsuleShape> _pCapsule = _pShape.downcast<PhysicsCapsuleShape>();
			if ( _pCapsule.isvalid() )
			{
				_pCapsule->SetHeight(m_fHeight);
				_pCapsule->SetRadius(m_fRadius);
			}
			m_arrPhysicsShapePtr.Insert(index, _pShape);
			if ( m_pController )
			{
				PxShape* _pPxShape = NULL;
				m_pController->getActor()->getShapes(&_pPxShape, 1, 0);
				_pShape->SetPxShape(_pPxShape);
				_pShape->SetGroup(m_eGroup);
				_pShape->m_pGeometry = &_pPxShape->getGeometry().any();
			}
			if (m_pComponent)
			{
				_pShape->ScaleWithActor(m_pComponent->GetActor()->GetWorldScale());
			}
			return _pShape;
		}
		return NULL;
	}

	void PhysicsRole::SetLocalCenter( Math::float3 center )
	{
		Math::float3 oldCenter = m_vLocalCenter;
		m_vLocalCenter = center;
		if ( m_pController )
		{
			const PxExtendedVec3& position = m_pController->getPosition();
			oldCenter.x() = (Math::scalar)position.x - oldCenter.x();
			oldCenter.y() = (Math::scalar)position.y - oldCenter.y();
			oldCenter.z() = (Math::scalar)position.z - oldCenter.z();
			MoveToPostion(oldCenter);
		}
	}

}
#endif

