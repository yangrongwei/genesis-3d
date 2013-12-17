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
#include "PxMaterial.h"
#include "PxRigidActor.h"
#include "PxRigidBody.h"
#include "PxPhysics.h"
#include "PxShape.h"
#include "PxMat44.h"
#include "PxGeometry.h"
#include "PxFiltering.h"
#include "PhysicsShape.h"
#include "PhysicsBoxShape.h"
#include "PhysicsCapsuleShape.h"
#include "PhysicsSphereShape.h"
#include "PhysicsMeshShape.h"
#include "PhysicsConvexShape.h"
#include "PhysicsTerrian.h"
#include "PhysicsPlaneShape.h"
#include "PhysicsServer.h"
#include "PhysicsMaterial.h"
#include "graphicfeature/graphicsfeature.h"
#include "appframework/actor.h"
#include "resource/resource.h"
#include "resource/resourcemanager.h"
#include "physXfeature/PhysicsBodyComponent.h"
#include "PhysicsUtil.h"

#define MaxLayers 32

namespace App
{
	__ImplementClass(App::PhysicsShape, 'PPSB', Core::RefCounted);

	using namespace Graphic;

	PhysicsShape::PhysicsShape()
		: m_pShape(NULL), 
		m_MatID(""),
		m_Name(""),
		m_pMaterial(NULL),
		m_pGeometry(NULL),
		m_pEntity(NULL),
		m_Center(0.f),
		m_Rotation(),
		m_Euler(0.0f,0.0f,0.0f),
		m_fDensity(1.0f),
		m_bTrigger(false),
		m_bMassUpdate(false),
		m_bInheritActor(true),
		m_ShapeType(PRIMITIVE)
	{
		m_MatID = PhysicsServer::Instance()->GetDefaultMaterial();
	}

	PhysicsShape::~PhysicsShape()
	{

	}

	void PhysicsShape::OnDestory()
	{
		if ( m_pGeometry )
		{
			delete m_pGeometry;
			m_pGeometry = NULL;
		}
		ReleasePxShape();
		m_pMaterial = NULL;
	}

	void PhysicsShape::OnRecreate(GPtr<PhysicsBodyComponent> component)
	{
		if(m_pEntity != NULL && m_pEntity->GetType() == PHYSICSDYNAMIC)
			OnDestory();
		OnCreate(component);
		if (m_pShape)
		{
			if (m_pGeometry && m_pShape->getGeometryType() == m_pGeometry->getType())
			{
				m_pShape->setGeometry(*m_pGeometry);
			}
			else
			{
				ReleasePxShape();
			}
		}
		else
		{
			if(m_pEntity != NULL)
				m_pEntity->OnShapeReBuild(this);
		}
	}

	GPtr<PhysicsShape> PhysicsShape::Create(PhyXShapeType type)
	{
		GPtr<PhysicsShape> _shape(NULL);

		switch (type)
		{
		case BOXSHAPE:
			_shape = PhysicsBoxShape::Create();
			break;
		case CAPSULESHAPE:
			_shape = PhysicsCapsuleShape::Create();
			break;
		case SPHERESHAPE:
			_shape = PhysicsSphere::Create();
			break;
		case PLANESHAPE:
			_shape = PhysicsPlaneShape::Create();
			break;
		case MESHSHAPE:
			_shape = PhysicsMeshShape::Create();
			break;
		case TERRAINSHAPE:
			_shape = PhysicsTerrain::Create();
			break;
		case CONVEXSHAPE:
			_shape = PhysicsConvexShape::Create();
			break;
		default:
			break;
		}
		return _shape;
	}
	//------------------------------------------------------------------------
	void PhysicsShape::SetGroup(App::LayerID unGroup)
	{
		if ( m_pShape )
		{
			if ( unGroup >= MaxLayers )
			{
				n_assert(0);
				return;
			}
			PxFilterData fd = m_pShape->getSimulationFilterData();
			fd.word0 = unGroup;
			m_pShape->setSimulationFilterData(fd);
		}
	}

	App::LayerID PhysicsShape::GetGroup()
	{
		if ( m_pShape )
		{
			PxFilterData fd = m_pShape->getSimulationFilterData();
			return fd.word0;
		}
		return 0;
	}

	void PhysicsShape::SetUserData(void* data)
	{
		if( m_pShape )
		{
			m_pShape->userData = data;
		}
	}

	void* PhysicsShape::GetUserData()
	{
		if( m_pShape )
		{
			if(!m_pShape->userData)
				return new Util::String;
			return m_pShape->userData;
		}
		return new Util::String;
	}

	void PhysicsShape::SetDensity(Math::scalar den)
	{
		if(den <= 0.0f)
			den = 0.01f;

		if(m_fDensity == den)
			return;
		m_fDensity = den;
		m_bMassUpdate = true;
	}
	//------------------------------------------------------------------------
	void PhysicsShape::SetTrigger( bool flag )
	{
		if ( m_bTrigger == flag )
		{
			return;
		}

		m_bTrigger = flag;
		if (m_pShape && m_pGeometry->getType() != PxGeometryType::eTRIANGLEMESH)
		{
			if(flag)
			{
				m_pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE,false);
				m_pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE,true);
			}
			else
			{
				m_pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE,false);
				m_pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE,true);
			}
			if(m_pEntity)
				m_pEntity->UpdateEntityMass();
		}
	}
	//------------------------------------------------------------------------

	bool PhysicsShape::CopyFrom(const GPtr<PhysicsShape>& pShape)
	{
		SetName(pShape->GetName());
		SetCenter(pShape->GetLocalCenter());
		SetErular(pShape->GetErular());
		SetTrigger(pShape->IsTrigger());
		SetDensity(pShape->GetDensity());
		SetMaterialID(pShape->GetMaterialID());
		m_bInheritActor = false;
		return true;
	}

	void PhysicsShape::SetCenter( const Math::float3& center )
	{
		if(center == m_Center)
			return;

		m_Center = center;

		UpdateShapePosition();
	}

	void PhysicsShape::SetErular(const Math::float3& erular)
	{
		m_Euler = erular;
		float _x = erular.x() * N_PI_DOUBLE / 360.0f;
		float _y = erular.y() * N_PI_DOUBLE / 360.0f;
		float _z = erular.z() * N_PI_DOUBLE / 360.0f;
		Math::quaternion q = Math::quaternion::rotationyawpitchroll(_y,_x,_z);
		SetRotation(q);
	}

	void PhysicsShape::SetRotation( const Math::quaternion& rotation )
	{
		if (m_Rotation == rotation)
		{
			return;
		}

		m_Rotation = rotation;

		UpdateShapePosition();
	}

	void PhysicsShape::UpdateShapePosition()
	{
		if ( m_pShape )
		{
			m_pShape->setLocalPose(PxTransform(RotPosToPxMat(m_Center,m_Rotation)));
		}
	}

	void PhysicsShape::SetSimulationFilterData(const FilterData& data) 
	{
		PxFilterData fData(data.word0,data.word1,data.word2,data.word3);
		m_pShape->setSimulationFilterData(fData);
	}

	PhysicsShape::FilterData PhysicsShape::GetSimulationFilterData() const
	{
		PxFilterData pData = m_pShape->getSimulationFilterData();
		return FilterData(pData.word0,pData.word1,pData.word2,pData.word3);
	}

	void PhysicsShape::SetQueryFilterData(const FilterData& data) 
	{
		if ( !m_pShape )
		{
			return;
		}
		PxFilterData fData(data.word0,data.word1,data.word2,data.word3);
		m_pShape->setQueryFilterData(fData); 
	}

	PhysicsShape::FilterData PhysicsShape::GetQueryFilterData() const
	{
		if ( !m_pShape )
		{
			return FilterData();
		}
		PxFilterData pData =  m_pShape->getQueryFilterData(); 
		return FilterData(pData.word0,pData.word1,pData.word2,pData.word3);
	}

	void PhysicsShape::SetContactOffset(float contactOffset) 
	{
		if(m_pShape)
			m_pShape->setContactOffset(contactOffset); 
	}

	void PhysicsShape::SetRestOffset(float restOffset) 
	{ 
		if(m_pShape)
			m_pShape->setRestOffset(restOffset); 
	}

	void PhysicsShape::DisableInShapePairIntersectTests()
	{
		if(m_pShape)
		{
			m_pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE,false);
		}
	}

	void PhysicsShape::EnableInShapePairIntersectTests()
	{
		if(m_pShape)
		{
			m_pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE,true);
		}
	}

	void PhysicsShape::DisableInSceneQueryTests()
	{
		if(m_pShape)
		{
			m_pShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE,false);
		}
	}

	void PhysicsShape::EnableInSceneQueryTests()
	{
		if(m_pShape)
		{
			m_pShape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE,true);
		}
	}

	void PhysicsShape::SetCCDActive(bool isActive)
	{
		if(m_pShape)
		{
			m_pShape->setFlag(PxShapeFlag::eUSE_SWEPT_BOUNDS,isActive);
			PxFilterData fd = m_pShape->getSimulationFilterData();
			if(isActive)
				fd.word3 |= PhysicsFlag::eSL_CCD_FLAG;
			else
				fd.word3 &= ~PhysicsFlag::eSL_CCD_FLAG;
			m_pShape->setSimulationFilterData(fd);
		}
	}

	bool PhysicsShape::GetCCDActive()
	{
		if(m_pShape)
		{
			PxFilterData fd = m_pShape->getSimulationFilterData();
			if((fd.word3 & PhysicsFlag::eSL_CCD_FLAG) != 0)
				return true;
		}
		return false;
	}

	void PhysicsShape::GetGlobalTransform( Math::matrix44& tran )
	{
		if ( m_pShape )
		{
			PxTransform _local = m_pShape->getLocalPose();
			PxTransform _global = m_pShape->getActor().getGlobalPose();
			if(!_local.isValid() || !_global.isValid())
			{//mesh shape缩放为0时会有问题。
				if(m_pEntity && m_pEntity->GetBodyCom() && m_pEntity->GetBodyCom()->GetActor())
				{
					tran = m_pEntity->GetBodyCom()->GetActor()->GetWorldTransform();
					tran = Math::matrix44::multiply(tran,Math::matrix44::rotationquaternion(m_Rotation));
					tran.set_position(tran.get_position() + Math::float4(m_Center.x(),m_Center.y(),m_Center.z(),1.0f));
				}
				return;
			}
			PxTransform _pos = _global * _local;
			tran = Math::matrix44::multiply(tran,Math::matrix44::rotationquaternion(PxQuatToQuat(_pos.q)));
			tran.set_position( Math::float4(_pos.p.x, _pos.p.y, _pos.p.z, 1.0f) );
		}
	}

	void PhysicsShape::SetMaterialID( const Util::String& materialID )
	{
		m_MatID = materialID;
		if ( m_MatID.IsValid() )
		{
			m_pMaterial = PhysicsMaterial::Create(m_MatID);
		}
		else
		{
			m_pMaterial = NULL;
		}
		if(m_pShape)
		{
			PxMaterial *tmpP = NULL;
			if(!m_pMaterial.isvalid())
			{
				tmpP = PhysicsServer::Instance()->GetDefaultPxMaterial();
			}
			else
			{
				tmpP = m_pMaterial->GetMaterial();
			}
			m_pShape->setMaterials(&tmpP,1);
		}
	}

	bool PhysicsShape::CreatePxShape( PxRigidActor* actor, uint layer )
	{
		if ( actor == NULL || !IsGeometryValid() )
		{
			return false;
		}
		PxMaterial* _pPxMaterial = NULL;
		if ( m_pMaterial.isvalid() )
		{
			_pPxMaterial = m_pMaterial->GetMaterial();
		} 
		else
		{
			_pPxMaterial = PhysicsServer::Instance()->GetDefaultPxMaterial();
		}

		m_pShape = actor->createShape(*m_pGeometry, *_pPxMaterial);
		UpdateShapePosition();

		n_assert(m_pShape)
			if ( m_pShape )
			{
				m_Name = Util::String::FromInt((int)this);
				m_pShape->userData = this;
				m_pShape->setContactOffset(0.02f);
				m_pShape->setRestOffset(-0.01f);
				m_pShape->setName(m_Name.AsCharPtr());
				m_pShape->resetFiltering();
				if(m_bTrigger && m_ShapeType != MESHSHAPE)
				{
					m_pShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE,false);
					m_pShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE,true);
				}
				PxFilterData fd = m_pShape->getSimulationFilterData();
				fd.word0 = layer;
				m_pShape->setSimulationFilterData(fd);
			}

			return true;
	}

	void PhysicsShape::ReleasePxShape()
	{
		if ( m_pShape )
		{
			m_pShape->release();
			m_pShape = NULL;
		}
	}

	void PhysicsShape::Save( AppWriter* pSerialize )
	{
		pSerialize->SerializeString("Name", m_Name);
		pSerialize->SerializeString("MaterialFile", m_MatID);
		pSerialize->SerializeFloat3("Center", m_Center);
		pSerialize->SerializeFloat3("Euler", m_Euler);
		pSerialize->SerializeQuaternion("Rotation", m_Rotation);
		pSerialize->SerializeBool("Trigger", m_bTrigger);
		pSerialize->SerializeFloat("Density", m_fDensity);
	}

	void PhysicsShape::Load( Version ver, AppReader* pReader )
	{
		pReader->SerializeString("Name", m_Name);
		pReader->SerializeString("MaterialFile", m_MatID);
		if (m_MatID.IsValid())
		{
			m_pMaterial = PhysicsMaterial::Create(m_MatID);
		}
		pReader->SerializeFloat3("Center", m_Center);
		pReader->SerializeFloat3("Euler", m_Euler);
		pReader->SerializeQuaternion("Rotation", m_Rotation);
		pReader->SerializeBool("Trigger", m_bTrigger);
		pReader->SerializeFloat("Density", m_fDensity);
		m_bInheritActor = false;
	}

}
#endif //__PHYSX_COMMIT__
