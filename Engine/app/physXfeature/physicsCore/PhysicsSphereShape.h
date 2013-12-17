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
#ifndef __PHYSICSSHPERESHAPE_H__
#define __PHYSICSSHPERESHAPE_H__

#include "PhysicsShape.h"

namespace App
{
	class PhysicsBodyComponent;
	class PhysicsSphere : public PhysicsShape
	{
		__DeclareSubClass(PhysicsSphere, App::PhysicsShape);

	public:
		PhysicsSphere();
		virtual ~PhysicsSphere();
		bool	OnCreate(GPtr<PhysicsBodyComponent> component);
		void	OnResize(const Math::bbox& bb);
		void	ScaleWithActor(const Math::vector& scale);

		bool	CopyFrom( const GPtr<PhysicsShape>& pComponent );

		void	Save(AppWriter* pSerialize);
		void	Load(Version ver, AppReader* pReader);

		bool	IsGeometryValid();
	public:

		Math::scalar GetRadius() { return m_Radius; }
		void SetRadius(Math::scalar radius);
		Math::scalar CaculateVolume();

		void	GetGlobalTransform(Math::matrix44& tran);
		__forceinline Math::scalar getRealRadius() { return _GetRealRadius(); }
	protected:
		void SetRadiusDo(Math::scalar radius);
		Math::scalar _GetRealRadius();
	private:
		Math::scalar m_Radius;
		Math::vector m_ActorScale;
	};

	inline Math::scalar PhysicsSphere::_GetRealRadius()
	{
		m_ActorScale.set(Math::n_abs(m_ActorScale.x()), Math::n_abs(m_ActorScale.y()), Math::n_abs(m_ActorScale.z()));
		return m_Radius * Math::n_max(m_ActorScale.x(), Math::n_max(m_ActorScale.y(), m_ActorScale.z()));
	}
	inline void PhysicsSphere::GetGlobalTransform(Math::matrix44& tran)
	{
		Super::GetGlobalTransform(tran);
		tran.scale(Math::float4(_GetRealRadius(),_GetRealRadius(),_GetRealRadius(),1.f));
	}
}

#endif 