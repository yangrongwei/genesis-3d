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
#include "PhysicsPlaneShape.h"
#include "PhysicsMaterial.h"
#include "PhysicsServer.h"
#include "PhysicsUtil.h"
#include "PxShape.h"
#include "PxPhysics.h"
#include "PxPlaneGeometry.h"
#include "PxRigidActor.h"
#include "physXfeature/PhysicsBodyComponent.h"

namespace App
{
	__ImplementClass(App::PhysicsPlaneShape, 'PHPS', App::PhysicsShape);


	PhysicsPlaneShape::PhysicsPlaneShape()
		: m_Normal(Math::float3(0.0f, 1.0f, 0.0f)),
		m_Distance(0.0f)
	{
		m_ShapeType = PLANESHAPE;
	}

	PhysicsPlaneShape::~PhysicsPlaneShape()
	{
		OnDestory();
	}

	bool PhysicsPlaneShape::OnCreate(GPtr<PhysicsBodyComponent> component)
	{
		m_pGeometry = new PxPlaneGeometry();
		return true;
	}

	bool PhysicsPlaneShape::CopyFrom( const GPtr<PhysicsShape>& pShape )
	{
		if ( !pShape.isvalid() || pShape->GetType() != m_ShapeType )
		{
			return false;
		}
		return Super::CopyFrom(pShape);
	}

	bool PhysicsPlaneShape::IsGeometryValid()
	{
		return IsValid() && ((PxPlaneGeometry*)m_pGeometry)->isValid();
	}

}
#endif

