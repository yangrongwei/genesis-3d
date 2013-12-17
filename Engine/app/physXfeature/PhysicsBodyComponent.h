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
#ifndef __PHYSICSBODY_COMPONENT_H__
#define __PHYSICSBODY_COMPONENT_H__

#include "appframework/component.h"
#include "resource/physxmaterialres.h"
#include "physicsCore/PhysicsEntity.h"
#include "physicsCore/PhysicsDeclaration.h"
#include "core/ptr.h"
#include "util/array.h"

using namespace physx;

namespace App
{
	class PhysicsShape;
	class PhysicsBodyComponent : public App::Component
	{
		__DeclareSubClass( PhysicsBodyComponent , App::Component );

	public:

		PhysicsBodyComponent();

		virtual ~PhysicsBodyComponent();

		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();
	public:

		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		virtual void OnDeactivate();

		/// @Component::SetupAcceptedMessages override to register accepted messages
		virtual void SetupAcceptedMessages();

		/// @Component::SetupAcceptedMessages handle a single message
		virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

		virtual void _OnBeginFrame();

		virtual void _OnFrame();

		virtual void _OnMoveAfter();
	public:

		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

		virtual void SetupAllResource();
		virtual bool IsAllResourceLoaded();
		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		void EnablePhysicsSimulate(bool enable);

		GPtr<PhysicsEntity> CreateEntity(PhysicsType type = PHYSICSDYNAMIC);
		GPtr<PhysicsEntity> GetEntity() { return m_pPhysXActor; }
		void SetEntity(GPtr<PhysicsEntity>& enty);
		inline uint GetEntityType();

	private:
		GPtr<PhysicsEntity> m_pPhysXActor;
	};

	inline uint PhysicsBodyComponent::GetEntityType()
	{
		if ( m_pPhysXActor.isvalid() )
		{
			return m_pPhysXActor->GetType();
		}
		return (uint)PHYSICSNONE;
	}

	inline void PhysicsBodyComponent::EnablePhysicsSimulate(bool enable) 
	{ 
		if (enable)
		{
			OnActivate();
		} 
		else
		{
			OnDeactivate();
		}
	}
}

#endif
