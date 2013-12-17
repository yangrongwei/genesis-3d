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
#ifndef __PHYSICSCAPSULESHAPE_H__
#define __PHYSICSCAPSULESHAPE_H__

#include "PhysicsShape.h"
#include "physXfeature/PhysicsBodyComponent.h"

namespace App
{
	class PhysicsCapsuleShape : public App::PhysicsShape
	{
		__DeclareSubClass(PhysicsCapsuleShape, App::PhysicsShape);

	public:
		PhysicsCapsuleShape();
		virtual ~PhysicsCapsuleShape();
		bool OnCreate(GPtr<PhysicsBodyComponent> component);
		void OnResize(const Math::bbox& bb);

		bool CopyFrom(const GPtr<PhysicsShape>& pComponent);

		void	Save(AppWriter* pSerialize);
		void	Load(Version ver, AppReader* pReader);

		bool	IsGeometryValid();
	public:
		void CreateRenderShape();
		void ScaleWithActor(const Math::vector& scale);

		Math::scalar GetHeight() { return m_Height; }
		void  SetHeight(Math::scalar height);

		Math::scalar GetRadius() { return m_Radius; }
		void  SetRadius(Math::scalar radius);

		int GetDirection() { return m_Direct; }
		void SetDirection(int dir);
		Math::scalar CaculateVolume();

		void GetGlobalTransform(Math::matrix44& tran);

		__forceinline Math::scalar getRealHeight() { return _GetRealHeight(); }
		__forceinline Math::scalar getRealRadius() { return _GetRealRadius(); }
	protected:
		Math::float2 _GetScaledLocalExtent(const Math::vector dimension, Math::scalar dir);
		Math::quaternion _GetQuatByDirection(Math::scalar dir);

		Math::scalar _GetRealHeight();
		Math::scalar _GetRealRadius();

		void  SetHeightDo(Math::scalar height);
		void  SetRadiusDo(Math::scalar radius);

		void  UpdateShapePosition();
		friend class PhysicsRole;
	protected:
		int				m_Direct;
		Math::scalar	m_Radius;
		Math::scalar	m_Height;
		Math::vector	m_ActorScale;
	};
	inline void PhysicsCapsuleShape::GetGlobalTransform(Math::matrix44& tran)
	{
		Super::GetGlobalTransform(tran);
		tran.scale(Math::float4(_GetRealHeight(),_GetRealRadius()*2,_GetRealHeight(),1.f));
	}
}





#endif