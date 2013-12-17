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
#ifndef __PHYSICSSHAPE_H__
#define __PHYSICSSHAPE_H__

#include "PhysicsDeclaration.h"
#include "PhysicsMaterial.h"
#include "math/float3.h"
#include "math/matrix44.h"
#include "foundation/util/scriptbind.h"
#include "appframework/actor.h"
#include "physXfeature/PhysicsBodyComponent.h"

using namespace physx;
namespace App
{
	class PhysicsMaterial;

	class PhysicsShape : public Core::RefCounted
	{
		__DeclareSubClass( PhysicsShape, Core::RefCounted );
		__ScriptBind

	public://nested type
#define MinPrecision 0.001f

		struct FilterData
		{
			int word0;
			int word1;
			int word2;
			int word3;
			FilterData(){}
			FilterData(int w0,int w1,int w2,int w3)
			{
				word0 = w0;
				word1 = w1;
				word2 = w2;
				word3 = w3;
			}
		};
	public://create and destory
		PhysicsShape();
		virtual ~PhysicsShape();

		static GPtr<PhysicsShape> Create(PhyXShapeType type);

		virtual	bool OnCreate(GPtr<PhysicsBodyComponent> component) { return false; }
		virtual void OnDestory();
		virtual void OnRecreate(GPtr<PhysicsBodyComponent> component);
		virtual void OnResize(const Math::bbox& bb){}

		virtual void	Save(AppWriter* pSerialize);
		virtual void	Load(Version ver, AppReader* pReader);
	public://update logical
		//update physic param when the r.s.t of model  changed
		virtual void UpdateTranslate(){}

		virtual void ScaleWithActor(const Math::vector& scale) {}

		virtual Math::scalar CaculateVolume() { return 1.0f;}

	public://physX 3.2 new feature:Simulation shapes and scene Query shapes

		void SetSimulationFilterData(const FilterData& data);

		PhysicsShape::FilterData GetSimulationFilterData() const;

		void SetQueryFilterData(const FilterData& data);

		PhysicsShape::FilterData GetQueryFilterData() const;

		void SetContactOffset(float contactOffset);

		void SetRestOffset(float restOffset);

		void DisableInShapePairIntersectTests();

		void EnableInShapePairIntersectTests();

		void DisableInSceneQueryTests();

		void EnableInSceneQueryTests();

		void SetCCDActive(bool isActive);

		bool GetCCDActive();

	public://getter and setter

		void SetName(const Util::String& name){ m_Name = name; }

		const Util::String& GetName() const { return m_Name; }

		const Util::String& GetMaterialID() { return m_MatID; }

		void SetMaterialID(const Util::String& materialID);

		const GPtr<PhysicsMaterial> GetMaterial() const { return m_pMaterial; }

		void SetCenter(const Math::float3& center);

		const Math::float3& GetLocalCenter() const { return m_Center; }

		void SetErular(const Math::float3& erular);

		const Math::float3& GetErular() const { return m_Euler; }

		void SetRotation(const Math::quaternion& rotation);

		const Math::quaternion& GetLocalRotation() const { return m_Rotation; }

		void SetTrigger(bool flag);

		void SetDensity(Math::scalar den);

		Math::scalar GetDensity() const { return m_fDensity; }

		PhyXShapeType GetType() { return m_ShapeType; }

		void SetGroup(App::LayerID layerID);

		App::LayerID GetGroup();

		void SetUserData(void* data);

		void* GetUserData();

		bool IsTrigger() const { return m_bTrigger; }
	public://base inherit
		/// @Component::SetupAcceptedMessages override to register accepted messages
		virtual void	SetupAcceptedMessages(){}

		virtual bool	CopyFrom( const GPtr<PhysicsShape>& pShape );

		virtual void	GetGlobalTransform(Math::matrix44& tran);

	public:
		virtual bool	IsValid() { return m_pGeometry != NULL; }
		virtual bool	IsGeometryValid() { return false; }
		bool			IsMassUpdate() { return m_bMassUpdate; }
		bool			UpdateMass() { m_bMassUpdate = false; return true; }
		bool			CreatePxShape(PxRigidActor* actor, uint layer);
		void			ReleasePxShape();
		void			SetPhysicsEntity(PhysicsEntity* ety) { m_pEntity = ety; }
		PhysicsEntity*  GetPhysicsEntity() const { return m_pEntity; }

		friend class PhysicsEntity;
		friend class PhysicsStatic;
		friend class PhysicsRole;
	public:
		virtual void	UpdateShapePosition();
		void			SetPxShape(PxShape* pShape) { m_pShape = pShape; }
	protected:
		Util::String		m_Name;
		Util::String		m_MatID;
		Math::float3		m_Center;
		Math::quaternion	m_Rotation;
		Math::float3		m_Euler;
		PxGeometry*			m_pGeometry;
		PxShape*			m_pShape;
		PhysicsEntity*		m_pEntity;

		bool				m_bInheritActor;
		bool				m_bTrigger;
		bool				m_bMassUpdate;
		float				m_fDensity;

		PhyXShapeType		m_ShapeType;

		GPtr<PhysicsMaterial> m_pMaterial;
	};
}
#endif
