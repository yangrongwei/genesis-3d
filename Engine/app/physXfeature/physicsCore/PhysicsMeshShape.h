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
#ifndef __PHYSICSMESHSHAPE_H__
#define __PHYSICSMESHSHAPE_H__

#include "PhysicsShape.h"
#include "resource/meshres.h"
#include "physXfeature/PhysicsBodyComponent.h"

namespace Resources
{
	class PrimitiveResInfo;
}

using namespace physx;
namespace App
{
	class PhysicsMeshShape : public App::PhysicsShape
	{
		__DeclareSubClass(PhysicsMeshShape, App::PhysicsShape);

	public:
		PhysicsMeshShape();
		virtual ~PhysicsMeshShape();

		bool					OnCreate(GPtr<PhysicsBodyComponent> component);

		void					Save(AppWriter* pSerialize);
		void					Load(Version ver, AppReader* pReader);


		bool					IsGeometryValid();
	public:		
		const Math::float3&		GetScale() { return m_Scale; }
		void					SetScale(const Math::float3& scale);

		void					SetMeshFileName(const Util::String& strName);
		const Util::String&		GetMeshFileName() { return m_MeshFileName; }

		bool					CopyFrom(const GPtr<PhysicsShape>& pShape);
		void					ScaleWithActor(const Math::vector& scale);

		void					GetGlobalTransform(Math::matrix44& tran);

	protected:
		bool					CreateShape(GPtr<PhysicsBodyComponent> component);
		PxTriangleMesh*			CreatePxMesh(Math::float3* pData, SizeT nVertexCount, SizeT nIndexCount, 
			uint* pIndex32, ushort* pIndex16);

		GPtr<Resources::PrimitiveResInfo>   CreatePhysicsMeshFromFile(const Util::String& fileName);

		void					SetScaleDo(Math::float3 scale);
		Math::float3			_GetRealScale();
	private:
		bool					m_UseActorMesh;

		Math::float3			m_Scale;
		Math::float3            m_RightScale;
		Util::String            m_MeshFileName;	
		Math::float3			m_ActorScale;
	};

	inline void PhysicsMeshShape::ScaleWithActor(const Math::vector& scale)
	{
		m_ActorScale = Math::float3(scale.x(),scale.y(),scale.z());
		SetScaleDo(_GetRealScale());
	}

	inline void PhysicsMeshShape::SetScale( const Math::float3& scale )
	{
		if(m_Scale == scale)
			return;

		m_Scale = scale;
		SetScaleDo(_GetRealScale());
	}

	inline void PhysicsMeshShape::GetGlobalTransform(Math::matrix44& tran)
	{
		Super::GetGlobalTransform(tran);
		Math::float3 _realScale = _GetRealScale();
		tran.scale(Math::float4(_realScale.x(),_realScale.y(),_realScale.z(),1.f));
	}
}


#endif