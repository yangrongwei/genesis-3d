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
#ifndef __PHYSICSBOXSHAPE_H__
#define __PHYSICSBOXSHAPE_H__

#include "PhysicsShape.h"

namespace App
{
	class PhysicsBoxShape : public App::PhysicsShape
	{
		__DeclareSubClass(PhysicsBoxShape, App::PhysicsShape)

	public:
		PhysicsBoxShape();
		virtual ~PhysicsBoxShape();

		bool OnCreate(GPtr<PhysicsBodyComponent> component);
		void OnResize(const Math::bbox& bb);

		bool CopyFrom( const GPtr<PhysicsShape>& pShape );

		void	Save(AppWriter* pSerialize);
		void	Load(Version ver, AppReader* pReader);

		bool	IsGeometryValid();
	public:
		void	CreateRenderShape();
		void	ScaleWithActor(const Math::vector& scale);
		void	SetDimension(const Math::float3& dimension);
		Math::float3& GetDimension() { return m_Dimension; }

		void	GetGlobalTransform(Math::matrix44& tran);

	protected:
		void		 SetDimensionDo(const Math::float3& dimension);
		Math::scalar CaculateVolume();

		Math::float3 _GetRealDemension();

	private:
		Math::float3 m_Dimension;
		Math::vector m_ActorScale;
	};
	inline void PhysicsBoxShape::GetGlobalTransform(Math::matrix44& tran)
	{
		Super::GetGlobalTransform(tran);
		Math::float3 _scale = _GetRealDemension();
		tran.scale(Math::float4(_scale.x(),_scale.y(),_scale.z(),1.f));
	}
}








#endif
