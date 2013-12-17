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
#include "PhysicsSphereShape.h"
#include "PhysicsMaterial.h"
#include "PhysicsServer.h"
#include "PhysicsUtil.h"
#include "PxShape.h"
#include "PxPhysics.h"
#include "PxRigidActor.h"
#include "PxSphereGeometry.h"
#include "physXfeature/PhysicsBodyComponent.h"

namespace App
{
	__ImplementClass(App::PhysicsSphere, 'PHSS', App::PhysicsShape);


	PhysicsSphere::PhysicsSphere()
		: m_Radius(0.5f)
		, m_ActorScale(1.f,1.f,1.f)
	{
		m_ShapeType = SPHERESHAPE;
	}

	PhysicsSphere::~PhysicsSphere()
	{
		OnDestory();
	}

	bool PhysicsSphere::OnCreate(GPtr<PhysicsBodyComponent> component)
	{
		m_ActorScale = component->GetActor()->GetWorldScale();
		if (m_bInheritActor)
		{
			OnResize(component->GetActor()->GetLocalBoundingBox());
			m_bInheritActor = false;
		}
		m_pGeometry = new PxSphereGeometry(_GetRealRadius());
		n_assert(m_pGeometry);
		return true;
	}

	void PhysicsSphere::OnResize(const Math::bbox& bb)
	{
		const Math::bbox& _box = bb;
		Math::vector _center(_box.center().x(), _box.center().y(), _box.center().z());
		Math::vector _value = _center*m_ActorScale;
		m_Center.set(_value.x(), _value.y(), _value.z());
		_value = _box.size();
		if (!Math::n_nearequal(_value.length(),0.0f,0.001f))
		{
			m_Radius = Math::n_max(_value.x(), Math::n_max(_value.y(), _value.z())) * 0.5f;
		}
	}

	void PhysicsSphere::SetRadius(Math::scalar radius)
	{
		if ( m_Radius == radius )
		{
			return;
		}
		m_Radius = radius;
		SetRadiusDo(_GetRealRadius());
	}
	//------------------------------------------------------------------------
	void PhysicsSphere::SetRadiusDo(Math::scalar radius)
	{
		radius = Math::n_abs(radius);
		if (m_pGeometry)
		{
			PxSphereGeometry* pShpere = static_cast<PxSphereGeometry*>(m_pGeometry);
			n_assert(pShpere);
			pShpere->radius = radius;
			if (m_pShape && m_pShape->getGeometryType() == m_pGeometry->getType())
			{
				m_pShape->setGeometry(*pShpere);
				m_bMassUpdate = true;
			}
		}
	}

	Math::scalar PhysicsSphere::CaculateVolume()
	{
		Math::scalar r = _GetRealRadius();
		return r*r*r*(Math::scalar)PI*4.0f/3.0f;
	}

	bool PhysicsSphere::CopyFrom( const GPtr<PhysicsShape>& pShape )
	{
		if ( !pShape.isvalid() || pShape->GetType() != m_ShapeType )
		{
			return false;
		}
		Super::CopyFrom(pShape);
		SetRadius(pShape.downcast<PhysicsSphere>()->GetRadius());
		return true;
	}

	void PhysicsSphere::ScaleWithActor(const Math::vector& scale)
	{
		m_ActorScale = scale;
		SetRadiusDo(_GetRealRadius());
	}

	void PhysicsSphere::Save( AppWriter* pSerialize )
	{
		Super::Save(pSerialize);
		pSerialize->SerializeFloat("Radius", m_Radius);
	}

	void PhysicsSphere::Load( Version ver, AppReader* pReader )
	{
		Super::Load(ver,pReader);
		pReader->SerializeFloat("Radius", m_Radius);
	}

	bool PhysicsSphere::IsGeometryValid()
	{
		return IsValid() && ((PxSphereGeometry*)m_pGeometry)->isValid();
	}

}//end namespace app

#endif

