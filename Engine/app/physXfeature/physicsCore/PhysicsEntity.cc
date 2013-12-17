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
#include "appframework/actor.h"
#include "PhysicsEntity.h"
#include "PhysicsUtil.h"
#include "PhysicsShape.h"
#include "PhysicsServer.h"
#include "PhysicsDynamic.h"
#include "PhysicsStatic.h"
#include "PhysicsRole.h"
#include "math/matrix44.h"
#include "math/vector.h"
#include "PhysicsServer.h"
#include "physXfeature/UserReport.h"
#include "physXfeature/PhysicsBodyComponent.h"
#include "PxRigidActor.h"
#include "PxScene.h"
namespace App
{
	__ImplementClass(PhysicsEntity, 'PYET', Core::RefCounted);

	PhysicsEntity::PhysicsEntity()
		: m_IsActive(false)
		, m_eType(PHYSICSNONE)
		, m_eGroup(0)
		, m_IsCopyed(false)
		, m_pComponent(NULL)
		, m_pCallBack(NULL)
	{
	}

	PhysicsEntity::~PhysicsEntity()
	{
		OnDestory();
	}

	GPtr<PhysicsEntity> PhysicsEntity::Create(GPtr<PhysicsBodyComponent> body, PhysicsType type /* = PHYSDYNAMIC */)
	{
		GPtr<PhysicsEntity> pEntity(NULL);
		switch (type)
		{
		case PHYSICSDYNAMIC:
			pEntity = PhysicsDynamic::Create();
			pEntity->m_pComponent = body.get();
			break;
		case PHYSICSSTATIC:
			pEntity = PhysicsStatic::Create();
			pEntity->m_pComponent = body.get();
			break;
		case PHYSICSCONTROLLER:
			pEntity = PhysicsRole::Create();
			pEntity->m_pComponent = body.get();
			break;
		default:
			break;
		}
		return pEntity;
	}

	bool PhysicsEntity::OnActivate()
	{
		m_IsActive = true;
		if ( !IsValid() )
		{
			OnCreate(m_pComponent);
		}
		PxRigidActor* _pPxActor = GetRigidActor();
		if ( _pPxActor && _pPxActor->getScene() == NULL )
		{
			PhysicsServer::Instance()->GetPhysXScene()->addActor(*_pPxActor);
		}
		PhysicsServer::Instance()->AttachPhysicsEntity(this);
		return true;
	}

	bool PhysicsEntity::OnDeactivate()
	{
		m_IsActive = false;

		OnDestory();
		PhysicsServer::Instance()->DettachPhysicsEntity(this);
		return true;
	}

	GPtr<PhysicsShape> PhysicsEntity::InsertShape( PhyXShapeType type, int index )
	{
		GPtr<PhysicsShape> _pShape = PhysicsShape::Create(type);
		_pShape->SetPhysicsEntity(this);
		if ( index > m_arrPhysicsShapePtr.Size() )
		{
			index = m_arrPhysicsShapePtr.Size();
		}
		if(index < 0)
		{
			index = 0;
		}
		if ( _pShape.isvalid() )
		{
			m_arrPhysicsShapePtr.Insert(index,_pShape);
			if ( IsActive() )
			{
				_pShape->OnCreate(m_pComponent);
			}
			if ( GetRigidActor() )
			{
				_pShape->CreatePxShape(GetRigidActor(),m_eGroup);
				UpdateEntityMass();
			}
		}

		return _pShape;
	}

	bool PhysicsEntity::InsertShape( GPtr<PhysicsShape> pShape, int index )
	{
		if (pShape.isvalid())
		{
			bool _ret = true;
			m_arrPhysicsShapePtr.Insert(index,pShape);// Regardless the shape can not be used, we insert it in the map
			if ( !pShape->IsValid() )
			{
				_ret = pShape->OnCreate(m_pComponent);
			}
			if ( _ret )
			{
				if (GetRigidActor())
				{
					pShape->CreatePxShape(GetRigidActor(),m_eGroup);
					UpdateEntityMass();
				}
				return true;
			}
		}
		return false;
	}

	GPtr<PhysicsShape> PhysicsEntity::ReplaceShape( PhyXShapeType type, int index )
	{
		GPtr<PhysicsShape> _pShape(NULL);
		if ( index >= 0 && index < m_arrPhysicsShapePtr.Size() )
		{
			_pShape = PhysicsShape::Create(type);
			_pShape->SetPhysicsEntity(this);
			if ( _pShape.isvalid() )
			{
				m_arrPhysicsShapePtr[index]->ReleasePxShape();
				m_arrPhysicsShapePtr[index] = _pShape;
				if ( IsActive() && m_arrPhysicsShapePtr[index]->OnCreate(m_pComponent) )
				{
					m_arrPhysicsShapePtr[index]->CreatePxShape(GetRigidActor(),m_eGroup);
					UpdateEntityMass();
				}
			}
		}
		return _pShape;
	}

	bool PhysicsEntity::ReplaceShape( GPtr<PhysicsShape> pShape, int index )
	{
		if (pShape.isvalid() && index>=0 && index<m_arrPhysicsShapePtr.Size())
		{
			bool _ret = true;
			m_arrPhysicsShapePtr[index]->ReleasePxShape();
			m_arrPhysicsShapePtr[index] = pShape;// Regardless the shape can not be used, we use it instead of the original
			if ( !pShape->IsValid() )
			{
				_ret = pShape->OnCreate(m_pComponent);
			}
			if ( _ret )
			{
				pShape->CreatePxShape(GetRigidActor(),m_eGroup);
				UpdateEntityMass();
				return true;
			}
		}
		return false;
	}

	GPtr<PhysicsShape> PhysicsEntity::RemoveShape( int index )
	{
		if ( index >= 0 && index < m_arrPhysicsShapePtr.Size() )
		{
			GPtr<PhysicsShape> _pShape = m_arrPhysicsShapePtr[index];
			_pShape->ReleasePxShape();
			m_arrPhysicsShapePtr.EraseIndex(index);
			UpdateEntityMass();
			return _pShape;
		}
		return NULL;
	}

	bool PhysicsEntity::RemoveShape( GPtr<PhysicsShape> pShape )
	{
		for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
		{
			if ( pShape == m_arrPhysicsShapePtr[i] )
			{
				return RemoveShape(i).isvalid();
			}
		}
		return false;
	}

	int PhysicsEntity::FindShape( GPtr<PhysicsShape> pShape )
	{
		for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
		{
			if ( pShape == m_arrPhysicsShapePtr[i] )
			{
				return i;
			}
		}
		return -1;
	}

	void PhysicsEntity::SetGroupID( App::LayerID layer )
	{
		if ( layer == m_eGroup )
		{
			return;
		}
		m_eGroup = layer;
		for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
		{
			m_arrPhysicsShapePtr[i]->SetGroup(layer);
		}
	}

	GPtr<PhysicsEntity> PhysicsEntity::GetEntityInActor(Actor* pActor)
	{
		if ( pActor )
		{
			GPtr<Component> _pComponent = pActor->FindComponent(PhysicsBodyComponent::RTTI);
			if ( _pComponent.isvalid() )
			{
				GPtr<PhysicsBodyComponent> _pBody = _pComponent.downcast<PhysicsBodyComponent>();
				return _pBody->GetEntity();
			}
		}
		return NULL;
	}

	inline GPtr<PhysicsShape> PhysicsEntity::GetShape(int index)
	{
		if ( index >= 0 && index < m_arrPhysicsShapePtr.Size() )
		{
			return m_arrPhysicsShapePtr[index];
		}
		return NULL;
	}

	bool PhysicsEntity::CopyFrom( GPtr<PhysicsEntity> src )
	{
		m_eGroup = src->GetGroupID();
		for ( int i=0; i<src->GetShapeCount(); ++i )
		{
			GPtr<PhysicsShape> _pNewShape = PhysicsShape::Create(src->GetShape(i)->GetType());
			_pNewShape->SetPhysicsEntity(this);
			if ( _pNewShape.isvalid() )
			{
				bool _ret = true;
				_ret &= _pNewShape->CopyFrom(src->GetShape(i));
				if ( _ret )
				{
					m_arrPhysicsShapePtr.Append(_pNewShape);
				}
				else
				{
					n_warning("The Copy of PhysicsShape is failed at the index of %d\n", i);
				}
			}
		}
		return true;
	}

	bool PhysicsEntity::OnDestory()
	{
		for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
		{
			m_arrPhysicsShapePtr[i]->OnDestory();
		}
		return true;
	}

	void PhysicsEntity::Save( AppWriter* pSerialize )
	{
		pSerialize->SerializeUInt("GroupID",m_eGroup);
		pSerialize->SerializeInt("ShapeCount",m_arrPhysicsShapePtr.Size());
		for ( int i=0; i<m_arrPhysicsShapePtr.Size(); ++i )
		{
			pSerialize->SerializeUInt("ShapeType",m_arrPhysicsShapePtr[i]->GetType());
			m_arrPhysicsShapePtr[i]->Save(pSerialize);
		}
	}

	void PhysicsEntity::Load( Version ver, AppReader* pReader )
	{
		pReader->SerializeUInt("GroupID",m_eGroup);

		int _shapeCount = 0;
		pReader->SerializeInt("ShapeCount", _shapeCount);
		for ( int i=0; i<_shapeCount; ++i )
		{
			uint _shapeType = PRIMITIVE;
			pReader->SerializeUInt("ShapeType", _shapeType);
			GPtr<PhysicsShape> _pShape = PhysicsShape::Create((PhyXShapeType)_shapeType);
			n_assert(_pShape.isvalid());
			_pShape->Load(ver,pReader);
			m_arrPhysicsShapePtr.Append(_pShape);
		}
	}

}
#endif




