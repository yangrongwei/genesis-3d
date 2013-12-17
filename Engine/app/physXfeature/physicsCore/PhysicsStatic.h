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
#ifndef __PHYSICSSTATIC_H__
#define __PHYSICSSTATIC_H__

#include "stdneb.h"
#include "PhysicsEntity.h"
#include "PhysicsDeclaration.h"

namespace App
{
	class PhysicsBodyComponent;
	using namespace physx;

	class PhysicsStatic : public PhysicsEntity
	{
		__DeclareSubClass(PhysicsStatic, PhysicsEntity)
	public:
		PhysicsStatic();
		virtual ~PhysicsStatic();

	public:
		bool	OnCreate(GPtr<PhysicsBodyComponent> body);
		bool	OnDestory();
		void	OnShapeReBuild(PhysicsShape* shape);

		bool	IsValid() { return m_pPxActor != NULL; }
		void	Move(const Math::float3& dir);
		void	MoveToPostion(const Math::float3& pos);
		void	Rotate(const Math::quaternion& quat);
		void	RotateToRotation(const Math::quaternion& quat);

		void	Tick(float time);

		bool	CopyFrom(GPtr<PhysicsEntity> src);

		PxRigidActor* GetRigidActor() { return (PxRigidActor*)m_pPxActor; }

		GPtr<PhysicsShape> ReplaceShape(PhyXShapeType type, int index);
		GPtr<PhysicsShape> RemoveShape(int index);
		bool			   ReplaceShape(GPtr<PhysicsShape> pShape, int index);

	private:
		PxRigidStatic* m_pPxActor;
	};
}
#endif