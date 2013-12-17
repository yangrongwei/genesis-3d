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
#include "graphicfeature/components/locatercomponent.h"
#include "graphicfeature/components/animationcomponent.h"


namespace App
{
	__ImplementClass(LocaterComponent, 'LCTC', App::Component);
	LocaterComponent::LocaterComponent(void)
		: firstLoaded(false),
		isAnimPlay(false),
		isLastFramePlay(false),
		m_bAttedToAttachedList(false)
	{

		mDefaultPos = Math::vector::nullvec();

		mLastAnimTrans = Math::matrix44::identity();
		mRelativeTrans = Math::matrix44::identity(); 
	}


	LocaterComponent::~LocaterComponent(void)
	{
	}
	
	void LocaterComponent::OnActivate()
	{
		Super::OnActivate();
	}

	void LocaterComponent::OnDeactivate()
	{
		Super::OnDeactivate();
	}

	void LocaterComponent::SetupAcceptedMessages()
	{
		Super::SetupAcceptedMessages();
	}

	void LocaterComponent::HandleMessage( const GPtr<Messaging::Message>& msg )
	{
		Super::HandleMessage(msg);
	}

	void LocaterComponent::SetupCallbacks()
	{
		mActor->RegisterComponentCallback(this, EndFrame);
		mActor->RegisterComponentCallback(this, BeginFrame);
		mActor->RegisterComponentCallback(this, OnFrame);
	}

	void LocaterComponent::_OnBeginFrame()
	{
		Super::_OnBeginFrame();

		GPtr<App::Actor> parentActor = mActor->GetParent();

		if(!parentActor.isvalid())
		{
			return;
		}

		GPtr<Component> com;
		com = parentActor->FindComponent( AnimationComponent::RTTI );

		if(com.isvalid())
		{
			GPtr<AnimationComponent> animationComponent = com.downcast<AnimationComponent>();
			if(!m_bAttedToAttachedList)
			{
				animationComponent->AddToAttachedActorList(mActor, mAttachedSkelName);
				m_bAttedToAttachedList = true;
			}

			//when animation is playing, the locater maybe updated before skinnedMesh 
			//so the animation data must be updated, if not, just return
			if(animationComponent->IsAnyAnimationPlaying() && animationComponent->IsToParentXEmpty())
				return;

			if(m_bNeedSetup)
			{
				mLastAnimTrans = Math::matrix44::identity();
				if(mActor)
				{
					mActor->SetPosition(Math::vector(0.0f,0.0f,0.0f));
					mActor->SetRotation(Math::quaternion(0.0f,0.0f,0.0f,1.0f));
				}
				m_bNeedSetup = false;
			}

			Math::matrix44 NodeTrans = Math::matrix44::identity();
			bool ret = animationComponent->GetNodeTransform(mAttachedSkelName, NodeTrans);

			Math::matrix44 finalTrans;

			Math::matrix44 actorTrans = mActor->GetTransform();


			if(!firstLoaded)
			{
				Math::matrix44 NodeTransInv = Math::matrix44::inverse(mLastAnimTrans);
				mRelativeTrans = Math::matrix44::multiply(NodeTransInv,actorTrans);	
			}
			firstLoaded = false;

			finalTrans = Math::matrix44::multiply(NodeTrans,mRelativeTrans);
			finalTrans.setrow3( Math::float4(0.0f,0.0f,0.0f,1.0f));
			mActor->SetTransform(finalTrans);

			mLastAnimTrans = NodeTrans;
		}
	}


	void LocaterComponent::_OnFrame()
	{
		Super::_OnFrame();	
	}

	void LocaterComponent::_OnEndFrame()
	{
		Super::_OnEndFrame();
	}

	void LocaterComponent::SetupLocater()
	{
		m_bNeedSetup = true;
	}

	void LocaterComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;
		// TODO:

		GPtr<LocaterComponent> pSource = pComponent.downcast<LocaterComponent>();
		n_assert(pSource.isvalid());

		const Util::String attachedSkelName = pSource->GetAttachedSkelName();
		this->SetAttachedSkelName(attachedSkelName);
		const Math::matrix44 relativeTrans = pSource->GetRelativeTrans();
		this->SetRelativeTrans(relativeTrans);
	}

}

