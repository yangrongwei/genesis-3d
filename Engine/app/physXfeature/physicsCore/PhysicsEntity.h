
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
#ifndef __PHYSICSENTITY_H__
#define __PHYSICSENTITY_H__

#include "core/refcounted.h"
#include "appframework/serialization.h"
#include "appframework/actor.h"
#include "PhysicsDeclaration.h"

namespace App
{
	using namespace physx;

	class PhysicsRoleHitReport
	{
	public:
		PhysicsRoleHitReport() {}
		virtual ~PhysicsRoleHitReport() {}

		virtual void onHitWithDynamic(GPtr<PhysicsEntity> other) = 0;
		virtual void onHitWithStatic(GPtr<PhysicsEntity> other) = 0;
		virtual void onHitWithRole(GPtr<PhysicsEntity> other) = 0;
	};

	class PhysicsShape;
	class PhysicsBodyComponent;
	class PhysicsEntity : public Core::RefCounted
	{
		__DeclareSubClass(PhysicsEntity, Core::RefCounted);
	public://construct
		PhysicsEntity();
		virtual ~PhysicsEntity();
		static GPtr<PhysicsEntity> Create(GPtr<PhysicsBodyComponent> body, PhysicsType type);

		virtual bool	OnActivate();
		virtual bool	OnDeactivate();
		virtual bool	OnCreate(GPtr<PhysicsBodyComponent> body) {return false;}
		virtual bool	OnDestory();
		virtual void	OnShapeReBuild(PhysicsShape* shape){}// The call back when the shape is rebuilt
		virtual void	OnScaleWithActor(){}

		virtual void	Save(AppWriter* pSerialize);
		virtual void	Load(Version ver, AppReader* pReader);


		void	RegistHitCallBack(PhysicsRoleHitReport* report) { m_pCallBack = report; }
		void	UnRegistHitCallBack() { m_pCallBack = NULL; }
	public:
		virtual GPtr<PhysicsShape> InsertShape(PhyXShapeType type, int index);
		virtual GPtr<PhysicsShape> ReplaceShape(PhyXShapeType type, int index);
		virtual GPtr<PhysicsShape> RemoveShape(int index);
		virtual GPtr<PhysicsShape> GetShape(int index);
		virtual bool			   InsertShape(GPtr<PhysicsShape> pShape, int index);
		virtual bool			   ReplaceShape(GPtr<PhysicsShape> pShape, int index);
		virtual bool			   RemoveShape(GPtr<PhysicsShape> pShape);
		int						   FindShape(GPtr<PhysicsShape> pShape);
		int						   GetShapeCount() { return m_arrPhysicsShapePtr.Size(); }
		const Util::Array< GPtr<PhysicsShape> >& GetShapes() { return m_arrPhysicsShapePtr; }

	public:
		uint			GetType() { return m_eType; }

		void			SetGroupID(uint layer);
		uint			GetGroupID() { return m_eGroup; }

		bool			IsActive() { return m_IsActive; }
		virtual bool	IsValid() { return false; }
		virtual float	GetMass() { return 0.f; }

		virtual void	Move(const Math::float3& dir) {}
		virtual void	MoveToPostion(const Math::float3& pos) {}
		virtual void	Rotate(const Math::quaternion& quat) {}
		virtual void	RotateToRotation(const Math::quaternion& quat) {}

		virtual void	Tick(float time) {}

		virtual bool	CopyFrom(GPtr<PhysicsEntity> src);
	public:		
		virtual void	UpdateEntityMass() {}
		virtual PxRigidActor* GetRigidActor() { return NULL; }
		PhysicsBodyComponent* GetBodyCom() { return m_pComponent; }

		static GPtr<PhysicsEntity> GetEntityInActor(Actor* pActor);

	protected:
		uint		m_eType;
		bool		m_IsActive;
		bool		m_IsCopyed;
		uint		m_eGroup;
		Util::Array< GPtr<PhysicsShape> > m_arrPhysicsShapePtr;
		PhysicsBodyComponent* m_pComponent;

		PhysicsRoleHitReport* m_pCallBack;
	};
}

#endif
