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
#include "SoundLowPassFilterComponent.h"
#include "math/scalar.h"

namespace App
{
	__ImplementClass(SoundLowPassFilterComponent, 'SLPF' , SoundFilterComponent);

	SoundLowPassFilterComponent::SoundLowPassFilterComponent() 
		: Super()
		, mGain(LOWPASS_DEFAULT_GAIN)
		, mGainHF(LOWPASS_DEFAULT_GAINHF)
	{
		mDspType = AL_FILTER_LOWPASS;
		Setup();
	}

	SoundLowPassFilterComponent::~SoundLowPassFilterComponent()
	{}

	void SoundLowPassFilterComponent::ParamsValidCheck()
	{
		mGain	= Math::n_clamp( mGain, LOWPASS_MIN_GAIN, LOWPASS_MAX_GAIN);
		mGainHF	= Math::n_clamp( mGainHF, LOWPASS_MIN_GAINHF, LOWPASS_MAX_GAINHF); 
	}

	void SoundLowPassFilterComponent::SetDspParamter()
	{
		if ( !mDSP.isvalid() )
		{
			return;
		}

		mDSP->setParameter( AL_LOWPASS_GAIN, mGain);
		mDSP->setParameter( AL_LOWPASS_GAINHF, mGainHF);
		int iSendIndex = mDSP->GetSendIndex();
		AttachFilter(__Active, iSendIndex);
	}

	void SoundLowPassFilterComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;

		GPtr<SoundLowPassFilterComponent> pSource = pComponent.downcast<SoundLowPassFilterComponent>();
		mGain	= pSource->GetLowPassParam(Gain);
		mGainHF= pSource->GetLowPassParam(GainHF);
	}

	float SoundLowPassFilterComponent::GetLowPassParam( LowPassParam param ) const
	{	
		switch(param)
		{
		case Gain:
			return mGain;
		case GainHF:
			return mGainHF;
		default:
			return -1.0f;
		}
	}

	void SoundLowPassFilterComponent::SetLowPassParam( LowPassParam param, float value )
	{
		switch(param)
		{
		case Gain:
			mGain = value; break;
		case GainHF:
			mGainHF = value; break;
		}
		ParamsValidCheck();
		SetDspParamter();
	}

}
#endif

