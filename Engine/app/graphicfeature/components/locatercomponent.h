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
#include "resource/animationres.h"
#include "foundation/math/float3.h"
#include "foundation/math/quaternion.h"
#include "foundation/math/matrix44.h"
#include "foundation/math/float2.h"
#include "foundation/math/float4.h"
#include "animation/Animation.h"
#include "resource/skeletonres.h"

namespace App
{
	class LocaterComponent : public App::Component
	{
		__DeclareSubClass(LocaterComponent, App::Component);
	public:
		LocaterComponent(void);
		
		virtual ~LocaterComponent(void);

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

		/// called on begin of frame
		virtual void _OnBeginFrame();

		/// called before rendering happens
		virtual void _OnFrame();

		/// called before rendering happens
		virtual void _OnEndFrame();

	public:	//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

	private:
		Math::vector mDefaultPos;

		bool isAnimPlay;
		bool isLastFramePlay;
		bool firstLoaded;

		Math::matrix44 mLastAnimTrans;
		Math::matrix44 mRelativeTrans;

		Util::String mAttachedSkelName;

		bool m_bNeedSetup;

		bool m_bAttedToAttachedList;

	public:
		void SetAttachedSkelName(const Util::String& skelName);
		const Util::String& GetAttachedSkelName();

		void SetRelativeTrans(const Math::matrix44& relativeTrans);
		const Math::matrix44& GetRelativeTrans();

		void SetLastFrameTrans(const Math::matrix44& relativeTrans);
		const Math::matrix44& GetLastFrameTrans();

		void SetupLocater();
	};

	inline void LocaterComponent::SetAttachedSkelName( const Util::String& skelName )
	{
		mAttachedSkelName = skelName;
	}

	inline const Util::String& LocaterComponent::GetAttachedSkelName()
	{
		return mAttachedSkelName;
	}

	inline void LocaterComponent::SetRelativeTrans( const Math::matrix44& relativeTrans )
	{
		mRelativeTrans = relativeTrans;
		firstLoaded = true;
	}

	inline const Math::matrix44& LocaterComponent::GetRelativeTrans()
	{
		return mRelativeTrans;
	}

	inline void LocaterComponent::SetLastFrameTrans( const Math::matrix44& lastAnimTrans )
	{
		mLastAnimTrans = lastAnimTrans;
	}

	inline const Math::matrix44& LocaterComponent::GetLastFrameTrans()
	{
		return mLastAnimTrans;
	}

}

