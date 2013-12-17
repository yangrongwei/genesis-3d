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
#include "PhysicsBodyComponent.h"
#include "appframework/actor.h"
#include "resource/resourceserver.h"
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "terrainfeature/components/TerrainRenderComponent.h"
#include "basegamefeature/managers/timesource.h"
#include "physicsCore/PhysicsServer.h"
#include "physicsCore/PhysicsUtil.h"
#include "physicsCore/PhysicsMaterial.h"
#include "physicsCore/PhysicsEntity.h"
#include "physicsCore/PhysicsUtil.h"
#include "physicsCore/PhysicsShape.h"
#include "physicsCore/PhysicsMeshShape.h"
#include "physicsCore/PhysicsConvexShape.h"
#include "PxRigidBodyExt.h"
#include "PxShape.h"
#include "PxForceMode.h"
#include "PxScene.h"

namespace App
{
	__ImplementClass(App::PhysicsBodyComponent, 'PXBC', App::Component);

	using namespace Resources;

	PhysicsBodyComponent::PhysicsBodyComponent()
		:m_pPhysXActor(NULL)
	{
	}

	PhysicsBodyComponent::~PhysicsBodyComponent()
	{
	}


	void PhysicsBodyComponent::OnActivate()
	{
		if(this->IsActive())
			return;
		Super::OnActivate();
		if ( !m_pPhysXActor.isvalid() )
		{
			CreateEntity(PHYSICSDYNAMIC);
		}
		m_pPhysXActor->OnActivate();
	}

	void PhysicsBodyComponent::OnDeactivate()
	{
		if(!this->IsActive())
			return;
		Super::OnDeactivate();
		if ( m_pPhysXActor.isvalid() )
		{
			m_pPhysXActor->OnDeactivate();
		}
	}

	void PhysicsBodyComponent::SetupCallbacks()
	{
		Super::SetupCallbacks();
		mActor->RegisterComponentCallback(this, BeginFrame);
		mActor->RegisterComponentCallback(this, OnFrame);
		mActor->RegisterComponentCallback(this, MoveAfter );
	}

	void PhysicsBodyComponent::SetupAcceptedMessages()
	{
		Super::SetupAcceptedMessages();
	}

	void PhysicsBodyComponent::HandleMessage(const GPtr<Messaging::Message>& msg)
	{

	}

	void PhysicsBodyComponent::_OnBeginFrame()
	{
// 		if (m_pPhysXActor.isvalid())
// 		{
// 			m_pPhysXActor->Tick((float)GameTime::Instance()->GetFrameTime());
// 		}
	}

	void PhysicsBodyComponent::_OnFrame()
	{

	}

	void PhysicsBodyComponent::_OnMoveAfter()
	{
		if(!PhysicsServer::Instance()->IsMoveAfterEnabled() || !m_pPhysXActor.isvalid())
		{
			return;
		}
		Math::float3 worldPos;
		worldPos.x()=mActor->GetWorldPosition().x();
		worldPos.y()=mActor->GetWorldPosition().y();
		worldPos.z()=mActor->GetWorldPosition().z();
		if(IsActive())
		{
			m_pPhysXActor->MoveToPostion(worldPos);
			m_pPhysXActor->RotateToRotation(mActor->GetWorldRotation());
		}

		for ( int i=0; i<m_pPhysXActor->GetShapeCount(); ++i )
		{
			m_pPhysXActor->GetShape(i)->ScaleWithActor(mActor->GetWorldScale());
		}
	}

	void PhysicsBodyComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;

		GPtr<PhysicsEntity> _srcEntity = pComponent.downcast<PhysicsBodyComponent>()->GetEntity();
		if ( _srcEntity.isvalid() )
		{
			if ( !m_pPhysXActor.isvalid() )
			{
				CreateEntity((PhysicsType)_srcEntity->GetType());
			}
			m_pPhysXActor->CopyFrom(_srcEntity);
		}
	}

	void PhysicsBodyComponent::SetupAllResource()
	{
		//TODO:
		return;
	}

	bool PhysicsBodyComponent::IsAllResourceLoaded()
	{
		//TODO:
		return true;
	}

	GPtr<PhysicsEntity> PhysicsBodyComponent::CreateEntity( PhysicsType type /*= PHYSICSDYNAMIC*/ )
	{
		if ( m_pPhysXActor.isvalid() )
		{
			m_pPhysXActor->OnDeactivate();
			m_pPhysXActor->OnDestory();
		}

		m_pPhysXActor = PhysicsEntity::Create(this,type);

		if ( IsActive() && m_pPhysXActor.isvalid() )
		{
			m_pPhysXActor->OnActivate();
		}

		return m_pPhysXActor;
	}

	void PhysicsBodyComponent::GetReferenceResourceId( Util::Array<Resources::ReferenceResource>& list ) const
	{
		for(int i = 0;i<m_pPhysXActor->GetShapeCount();i++)
		{
			GPtr<PhysicsShape>& pShape = m_pPhysXActor->GetShapes()[i];
			const Util::String& pMaterial = pShape->GetMaterialID();
			list.Append(Resources::ReferenceResource(pMaterial, Resources::RR_Unknown));
			if(pShape->IsA(PhysicsMeshShape::RTTI))
			{
				GPtr<PhysicsMeshShape> pMeshShape = pShape.downcast<PhysicsMeshShape>();
				const Util::String& pMeshFile = pMeshShape->GetMeshFileName();
				list.Append(Resources::ReferenceResource(pMeshFile, Resources::RR_Unknown));
			}
			else if(pShape->IsA(PhysicsConvexShape::RTTI))
			{
				GPtr<PhysicsConvexShape> pMeshShape = pShape.downcast<PhysicsConvexShape>();
				const Util::String& pMeshFile = pMeshShape->GetMeshFileName();
				list.Append(Resources::ReferenceResource(pMeshFile, Resources::RR_Unknown));
			}
		}
		Super::GetReferenceResourceId(list);
	}

	void PhysicsBodyComponent::SetEntity( GPtr<PhysicsEntity>& enty )
	{
		if ( m_pPhysXActor.isvalid() )
		{
			m_pPhysXActor->OnDeactivate();
			m_pPhysXActor->OnDestory();
		}
		m_pPhysXActor = enty;
		if ( IsActive() && m_pPhysXActor.isvalid() )
		{
			m_pPhysXActor->OnActivate();
		}
	}
}

#endif
