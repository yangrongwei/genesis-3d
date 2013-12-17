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
#ifndef __PHYSICSPLANESHAPE_H__
#define __PHYSICSPLANESHAPE_H__

#include "PhysicsShape.h"

namespace App
{
	class PhysicsPlaneShape : public App::PhysicsShape
	{
		__DeclareSubClass(PhysicsPlaneShape, App::PhysicsShape);

	public:
		PhysicsPlaneShape();
		virtual ~PhysicsPlaneShape();

		virtual bool OnCreate(GPtr<PhysicsBodyComponent> component);

		virtual bool CopyFrom( const GPtr<PhysicsShape>& pShape );

		bool	IsGeometryValid();
	public:

		const Math::float3 GetNormal() const;
		const Math::scalar GetDistance() const;
		void  SetPlane(const Math::float3& normal, const Math::scalar& distance) { m_Normal = normal; m_Distance = distance;}
	private:
		Math::float3 m_Normal;
		Math::scalar m_Distance;

	};

	inline const Math::float3 PhysicsPlaneShape::GetNormal() const
	{
		return m_Normal;
	}

	inline const Math::scalar PhysicsPlaneShape::GetDistance() const
	{
		return m_Distance;
	}

}
#endif