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
#include "PhysicsStatic.h"
#include "PhysicsServer.h"
#include "PhysicsUtil.h"
#include "PxScene.h"
#include "PxRigidStatic.h"
#include "PhysicsShape.h"
#include "physXfeature/PhysicsBodyComponent.h"

namespace App
{
	__ImplementClass(PhysicsStatic, 'PYST', PhysicsEntity);

	PhysicsStatic::PhysicsStatic()
		: m_pPxActor(NULL)
	{
		m_eType = PHYSICSSTATIC;
	}

	PhysicsStatic::~PhysicsStatic()
	{
		OnDestory();
	}

	bool PhysicsStatic::OnCreate(GPtr<PhysicsBodyComponent> body)
	{
		if (body.isvalid() && body->GetActor())
		{
			OnDestory();
			PxPhysics* pSDK = PhysicsServer::Instance()->GetPhysics();
			n_assert(pSDK);
			Math::vector pos = body->GetActor()->GetWorldPosition();
			Math::quaternion rot = body->GetActor()->GetWorldRotation();
			{
				PxTransform _ActorPose(PxVec3(pos.x(), pos.y(), pos.z()), PxQuat(rot.x(), rot.y(), rot.z(), rot.w()));
				m_pPxActor = pSDK->createRigidStatic(_ActorPose);
				m_pPxActor->userData = body.get();
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
			return true;
		}

		return false;
	}

	bool PhysicsStatic::OnDestory()
	{
		if ( IsValid() )
		{
			for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
			{
				m_arrPhysicsShapePtr[i]->SetPxShape(NULL);
				m_arrPhysicsShapePtr[i]->OnDestory();
			}
			m_pPxActor->release();
			m_pPxActor = NULL;
		}
		return true;
	}

	void PhysicsStatic::OnShapeReBuild(PhysicsShape* shape)
	{
		if(shape != NULL)
			shape->CreatePxShape(m_pPxActor, GetGroupID());
	}

	void PhysicsStatic::Move( const Math::float3& dir )
	{
		if ( m_pPxActor )
		{
			PxTransform _pos = m_pPxActor->getGlobalPose();
			_pos.p.x += dir.x();
			_pos.p.y += dir.y();
			_pos.p.z += dir.z();
			m_pPxActor->setGlobalPose(_pos);
		}
	}

	void PhysicsStatic::MoveToPostion( const Math::float3& pos )
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

	void PhysicsStatic::Rotate( const Math::quaternion& quat )
	{
		if ( m_pPxActor )
		{
			PxTransform _pos = m_pPxActor->getGlobalPose();
			Math::quaternion _quat = Math::quaternion::multiply(PxQuatToQuat(_pos.q), quat);
			_pos.q.x = _quat.x();
			_pos.q.y = _quat.y();
			_pos.q.z = _quat.z();
			_pos.q.w = _quat.w();
			m_pPxActor->setGlobalPose(_pos);
		}
	}

	void PhysicsStatic::RotateToRotation( const Math::quaternion& quat )
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

	bool PhysicsStatic::CopyFrom( GPtr<PhysicsEntity> src )
	{
		if ( !src.isvalid() || src->GetType() != m_eType )
		{
			return false;
		}
		Super::CopyFrom(src);

		return true;
	}

	GPtr<PhysicsShape> PhysicsStatic::RemoveShape( int index )
	{
		if ( m_arrPhysicsShapePtr.Size() == 1 && index == 0 )
		{
			return NULL;
		}
		else
		{
			return Super::RemoveShape(index);
		}
	}

	GPtr<PhysicsShape> PhysicsStatic::ReplaceShape( PhyXShapeType type, int index )
	{
		if ( m_arrPhysicsShapePtr.Size() == 1 && index == 0 )
		{
			if (InsertShape(type, 1).isvalid())
			{
				m_arrPhysicsShapePtr[0]->ReleasePxShape();
				m_arrPhysicsShapePtr.EraseIndex(0);
				return m_arrPhysicsShapePtr[0];
			}
			return NULL;
		}
		return Super::ReplaceShape(type,index);
	}

	bool PhysicsStatic::ReplaceShape( GPtr<PhysicsShape> pShape, int index )
	{
		if ( m_arrPhysicsShapePtr.Size() == 1 && index == 0 )
		{
			bool _ret = InsertShape(pShape, 1);
			if (_ret)
			{
				m_arrPhysicsShapePtr[0]->ReleasePxShape();
				m_arrPhysicsShapePtr.EraseIndex(0);
			}
			return _ret;
		}
		return Super::ReplaceShape(pShape,index);
	}

	void PhysicsStatic::Tick(float time)
	{
		if ( m_pPxActor )
		{
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
}
#endif