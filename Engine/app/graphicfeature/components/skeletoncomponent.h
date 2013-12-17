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

#pragma once

#include "appframework/component.h"
#include "appframework/actor.h"
#include "graphicfeature/components/rendercomponent.h"

namespace App
{
	class SkeletonComponent : public App::Component
	{
		__DeclareSubClass(SkeletonComponent, App::Component)

	public:
		SkeletonComponent();
		virtual ~SkeletonComponent();

		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		/// @Component::SetupAcceptedMessages override to register accepted messages
		virtual void SetupAcceptedMessages();

		/// @Component::SetupAcceptedMessages handle a single message
		virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

		void SetSkeletonID(const Resources::ResourceId& skeletonID, IndexT priority = Resources::ResourcePriority::SkeletonDefault);

		const Resources::ResourceId& GetSkeletonID() const;

		const GPtr<Resources::SkeletonRes>& GetSkeleton() const;

		const Resources::Priority GetLoadPriority() const;

		bool  IsAllLoaded() const;

		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

	private:
		void SetAnimSkelTree();

	public:	//	Serialization
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

		bool IsSkelDirty();

	protected:
		/// @component::_OnBeginFrame called on begin of frame
		virtual void _OnBeginFrame();

	protected:

		GPtr<Resources::SkeletonResInfo> m_pSkelResInfo;
		Resources::ResourceId           m_SkelID;
		bool                            m_bSkeletonDirty;
		Resources::Priority				m_nPriority;

		GPtr<Resources::SkeletonRes>     m_pEmptyRes;
	};

	inline const Resources::ResourceId& SkeletonComponent::GetSkeletonID() const
	{
		return m_SkelID;

	}

	inline const GPtr<Resources::SkeletonRes>& SkeletonComponent::GetSkeleton() const
	{
		bool bValid = m_pSkelResInfo.isvalid();
		if ( !bValid )
		{
			return m_pEmptyRes;	
		}

		const GPtr<Resources::Resource>& resPtr = m_pSkelResInfo->GetRes();
		bValid = resPtr.isvalid();
		if ( !bValid )
		{
			return m_pEmptyRes;
		}

		return resPtr.downcast<Resources::SkeletonRes>();
	}

	inline const Resources::Priority SkeletonComponent::GetLoadPriority() const
	{
		return m_nPriority;
	}

	inline bool SkeletonComponent::IsAllLoaded() const
	{
		if (m_bSkeletonDirty)
		{
			return false;
		} 
		else
		{
			return true;
		}
	}

	inline bool SkeletonComponent::IsSkelDirty()
	{
		return m_bSkeletonDirty;
	}
}