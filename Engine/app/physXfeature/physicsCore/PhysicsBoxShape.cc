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
#include "PhysicsBoxShape.h"
#include "PhysicsMaterial.h"
#include "PhysicsUtil.h"
#include "PhysicsServer.h"
#include "PxShape.h"
#include "PxBoxGeometry.h"
#include "PxRigidActor.h"
#include "PxGeometry.h"
#include "PxMat44.h"
#include "PxVec3.h"
#include "physXfeature/PhysicsBodyComponent.h"
using namespace physx;
using namespace App;
namespace App
{
	__ImplementClass(App::PhysicsBoxShape, 'PYSB', App::PhysicsShape);


	PhysicsBoxShape::PhysicsBoxShape()
		:m_Dimension(1.0f,1.0f,1.0f)
		,m_ActorScale(1.0f,1.0f,1.0f)
	{
		m_ShapeType = BOXSHAPE;
	}

	PhysicsBoxShape::~PhysicsBoxShape()
	{
		OnDestory();
	}

	bool PhysicsBoxShape::OnCreate(GPtr<PhysicsBodyComponent> component)
	{
		m_ActorScale = component->GetActor()->GetWorldScale();
		if (m_bInheritActor)
		{
			OnResize(component->GetActor()->GetLocalBoundingBox());
			m_bInheritActor = false;
		}
		Math::float3 _realDimension = _GetRealDemension() / 2;
		m_pGeometry = new PxBoxGeometry(Math::n_max(_realDimension.x(), 0.1f), Math::n_max(_realDimension.y(), 0.1f), Math::n_max(_realDimension.z(), 0.1f));
		n_assert(m_pGeometry)
			return true;
	}

	void PhysicsBoxShape::OnResize(const Math::bbox& bb)
	{
		const Math::bbox& _box = bb;
		Math::vector _value = _box.size();
		if (!Math::n_nearequal(_value.length(),0.0f,0.001f))
		{
			m_Dimension.set(_value.x(), _value.y(), _value.z());
		}
		Math::vector _center(_box.center().x(), _box.center().y(), _box.center().z());
		_value = _center*m_ActorScale;
		m_Center.set(_value.x(), _value.y(), _value.z());
	}

	void PhysicsBoxShape::SetDimension( const Math::float3& dimension )
	{
		if ( m_Dimension == dimension )
		{
			return;
		}
		m_Dimension = dimension.abs();

		if (m_pGeometry)
		{
			SetDimensionDo(_GetRealDemension());
		}
	}

	//------------------------------------------------------------------------
	void PhysicsBoxShape::SetDimensionDo( const Math::float3& dimension )
	{
		PxVec3 nxV3(dimension.x(),dimension.y(),dimension.z());
		if (m_pGeometry && m_pGeometry->getType() == PxGeometryType::eBOX)
		{
			PxBoxGeometry* pBoxShape = static_cast<PxBoxGeometry*>(m_pGeometry);
			n_assert(pBoxShape);
			pBoxShape->halfExtents = nxV3 / 2;
			if ( m_pShape && m_pShape->getGeometryType() == m_pGeometry->getType() )
			{
				m_pShape->setGeometry(*m_pGeometry);
				m_bMassUpdate = true;
			}
		}
	}
	//------------------------------------------------------------------------
	void PhysicsBoxShape::CreateRenderShape()
	{
	}
	//------------------------------------------------------------------------
	bool PhysicsBoxShape::CopyFrom( const GPtr<PhysicsShape>& pShape )
	{
		if ( !pShape.isvalid() || pShape->GetType() != m_ShapeType )
		{
			return false;
		}
		Super::CopyFrom(pShape);
		SetDimension(pShape.downcast<PhysicsBoxShape>()->GetDimension());
		return true;
	}

	Math::scalar PhysicsBoxShape::CaculateVolume()
	{
		Math::float3 dim = GetDimension();
		return dim.x()*dim.y()*dim.z()*8;
	}

	void PhysicsBoxShape::ScaleWithActor(const Math::vector& scale)
	{
		m_ActorScale = scale;
		SetDimensionDo(_GetRealDemension());
	}

	Math::float3 PhysicsBoxShape::_GetRealDemension()
	{
		Math::float3 _scale;
		_scale.x() = Math::n_abs(m_ActorScale.x()* m_Dimension.x());
		_scale.y() = Math::n_abs(m_ActorScale.y()* m_Dimension.y());
		_scale.z() = Math::n_abs(m_ActorScale.z()* m_Dimension.z());
		_scale.x() = Math::n_nearequal(_scale.x(), 0.0f, MinPrecision)? MinPrecision:_scale.x();
		_scale.y() = Math::n_nearequal(_scale.y(), 0.0f, MinPrecision)? MinPrecision:_scale.y();
		_scale.z() = Math::n_nearequal(_scale.z(), 0.0f, MinPrecision)? MinPrecision:_scale.z();

		return _scale;
	}

	void PhysicsBoxShape::Save( AppWriter* pSerialize )
	{
		Super::Save(pSerialize);
		pSerialize->SerializeFloat3("Dimension", m_Dimension);
	}

	void PhysicsBoxShape::Load( Version ver, AppReader* pReader )
	{
		Super::Load(ver,pReader);
		pReader->SerializeFloat3("Dimension", m_Dimension);
	}

	bool PhysicsBoxShape::IsGeometryValid()
	{
		return IsValid() && ((PxBoxGeometry*)m_pGeometry)->isValid();
	}

}
#endif

