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
#ifndef __SOUND_COMMIT__
#include "stdneb.h"
#include "SoundEchoFilterComponent.h"
#include "math/scalar.h"

namespace App
{
	__ImplementClass(SoundEchoFilterComponent, 'SEFC' , SoundFilterComponent);

	SoundEchoFilterComponent::SoundEchoFilterComponent () 
		: Super()
		, mDelay(AL_ECHO_DEFAULT_DELAY)
		, mLRDelay(AL_ECHO_DEFAULT_LRDELAY)
		, mDamping(AL_ECHO_DEFAULT_DAMPING)
		, mFeedBack(AL_ECHO_DEFAULT_FEEDBACK)
		, mSpread(AL_ECHO_DEFAULT_SPREAD)
	{
		mDspType = AL_EFFECT_ECHO;
		Setup();
	}

	SoundEchoFilterComponent::~SoundEchoFilterComponent()
	{}

	void SoundEchoFilterComponent::ParamsValidCheck()
	{
		mDelay		= Math::n_clamp(mDelay,AL_ECHO_MIN_DELAY,AL_ECHO_MAX_DELAY);
		mLRDelay	= Math::n_clamp(mLRDelay,AL_ECHO_MIN_LRDELAY,AL_ECHO_MAX_LRDELAY);
		mDamping	= Math::n_clamp(mDamping,AL_ECHO_MIN_DAMPING,AL_ECHO_MAX_DAMPING);
		mFeedBack	= Math::n_clamp(mFeedBack,AL_ECHO_MIN_FEEDBACK,AL_ECHO_MAX_FEEDBACK);
		mSpread	= Math::n_clamp(mSpread, AL_ECHO_MIN_SPREAD, AL_ECHO_MAX_SPREAD);
	}

	void SoundEchoFilterComponent::SetDspParamter()
	{
		if ( !mDSP.isvalid() )
		{
			return;
		}

		mDSP->setParameter( AL_ECHO_DELAY, mDelay);
		mDSP->setParameter( AL_ECHO_LRDELAY, mLRDelay);
		mDSP->setParameter( AL_ECHO_DAMPING, mDamping);
		mDSP->setParameter( AL_ECHO_FEEDBACK, mFeedBack);
		mDSP->setParameter( AL_ECHO_SPREAD, mSpread);
		int iSendIndex = mDSP->GetSendIndex();
		AttachFilter(__Active, iSendIndex);

	}

	void SoundEchoFilterComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;

		GPtr<SoundEchoFilterComponent> pSource = pComponent.downcast<SoundEchoFilterComponent>();

		mDelay = pSource->GetEchoParam(Delay);
		mLRDelay = pSource->GetEchoParam(LRDelay);
		mDamping = pSource->GetEchoParam(Damping);
		mFeedBack = pSource->GetEchoParam(FeedBack);
		mSpread = pSource->GetEchoParam(Spread);

	}

	float SoundEchoFilterComponent::GetEchoParam( EchoParam param ) const
	{
		switch (param)
		{
		case Delay:
			return mDelay;
		case LRDelay:
			return mLRDelay;
		case Damping:
			return mDamping;
		case FeedBack:
			return mFeedBack;
		case Spread:
			return mSpread;
		default :
			return -1.0f;
		}
	}

	void SoundEchoFilterComponent::SetEchoParam( EchoParam param, float value )
	{
		switch (param)
		{
		case Delay:
			mDelay= value; break;
		case LRDelay:
			mLRDelay= value; break;
		case Damping:
			mDamping= value; break;
		case FeedBack:
			mFeedBack= value; break;
		case Spread:
			mSpread= value; break;
		}

		ParamsValidCheck();
		SetDspParamter();
	}

}

#endif