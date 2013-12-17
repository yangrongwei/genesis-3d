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

#include "stdneb.h"
#include "graphicfeature/components/skeletoncomponent.h"
#include "graphicfeature/components/animationcomponent.h"
#include "graphicfeature/graphicsfeature.h"
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "resource/resourceserver.h"

namespace App
{
	using namespace Graphic;
	using namespace Resources;

	__ImplementClass(SkeletonComponent, 'SKCM', App::Component);

	SkeletonComponent::SkeletonComponent()
		:  m_pSkelResInfo(NULL),
		m_pEmptyRes(NULL),
		m_bSkeletonDirty(false),
		m_nPriority(Resources::ResourcePriority::SkeletonDefault)
	{

	}

	SkeletonComponent::~SkeletonComponent()
	{
		if (m_pSkelResInfo.isvalid())
		{
			m_pSkelResInfo = NULL;
		}
	}

	void SkeletonComponent::OnActivate()
	{
		Actor::Check_Skeleton(this);
		Super::OnActivate();
	}

	void SkeletonComponent::OnDeactivate()
	{
		Super::OnDeactivate();
	}

	void SkeletonComponent::SetupCallbacks()
	{
		mActor->RegisterComponentCallback(this, BeginFrame);
	}

	void SkeletonComponent::SetupAcceptedMessages()
	{
		Super::SetupAcceptedMessages();
	}

	void SkeletonComponent::HandleMessage(const GPtr<Messaging::Message>& msg)
	{
		Super::HandleMessage(msg);
	}

	void SkeletonComponent::SetSkeletonID(const Resources::ResourceId &skeletonID, IndexT priority)
	{
		if (m_SkelID != skeletonID)
		{
			m_SkelID = skeletonID;

			if (m_pSkelResInfo.isvalid())
			{
				m_pSkelResInfo   = NULL;
			}
			if (mActor && mActor->PriorityDefinition())
			{
				priority = mActor->GetPriority();
			}
			m_nPriority      = priority;

		}
		m_bSkeletonDirty = true;
	}

	void SkeletonComponent::_OnBeginFrame()
	{
		if (m_bSkeletonDirty)
		{
			if ( m_pSkelResInfo.isvalid() )
			{
				if (m_pSkelResInfo->GetRes().isvalid())
				{
					SetAnimSkelTree();
				}
			}
			else
			{
				m_pSkelResInfo = Resources::ResourceManager::Instance()->CreateSkeletonResInfo(m_SkelID, m_nPriority);
			}
		}


	}

	void SkeletonComponent::SetAnimSkelTree()
	{
		//Find animation data
		Actor* actorParent = mActor->GetParent();
		if (!actorParent)
		{
			return;
		}

		GPtr<Component> animation = actorParent->FindComponent(AnimationComponent::RTTI);
		if(animation.isvalid())
		{
			GPtr<AnimationComponent> pAnimationCom = animation.downcast<AnimationComponent>();

			const GPtr<SkeletonRes>& skeletonRes = GetSkeleton();
			if (skeletonRes.isvalid() && !skeletonRes->IsSkelTreeEmpty())
			{
				pAnimationCom->SetSkelTree(skeletonRes->GetSkelTree());
				pAnimationCom->SetSkelTree(skeletonRes->GetSkelTreeArray());

				pAnimationCom->SetGetSkelTree(true);

				m_bSkeletonDirty = false;
			}
		}

	}

	//------------------------------------------------------------------------
	void SkeletonComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;
		// TODO:

		GPtr<SkeletonComponent> pSource = pComponent.downcast<SkeletonComponent>();
		n_assert(pSource.isvalid());

		SetSkeletonID(pSource->GetSkeletonID());
	}

	void SkeletonComponent::SetupAllResource()
	{
		if (mActor->PriorityUndefinition())
			return;

		SetSkeletonID(m_SkelID,mActor->GetPriority());
	}

	bool SkeletonComponent::IsAllResourceLoaded()
	{
		return IsAllLoaded();
	}

	void SkeletonComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		list.Append(Resources::ReferenceResource(m_SkelID, Resources::RR_Unknown));
		Super::GetReferenceResourceId(list);
	}

}