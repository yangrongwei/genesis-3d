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
#include "appframework/component.h"
#include "soundfeature/SoundFeature.h"
#include "SoundFilterComponent.h"
#include "app/soundfeature/SoundTypes.h"
#include "math/scalar.h"
#include "SoundReverbFilterComponent.h"

#include "OpenAL/EFX-Util.h"
#include "soundsystem/Framework.h"


#include "SoundSourceComponent.h"
#include "appframework/actor.h"

namespace App
{
	__ImplementClass(SoundReverbFilterComponent, 'SRFC' , SoundFilterComponent);

	SoundReverbFilterComponent::SoundReverbFilterComponent()
		: Super()
		, mReflectionsDelay(AL_EAXREVERB_DEFAULT_REFLECTIONS_DELAY)
		, mAirGainHF(AL_EAXREVERB_DEFAULT_AIR_ABSORPTION_GAINHF)
		, mHFReference(AL_EAXREVERB_DEFAULT_HFREFERENCE)
		, mGain(AL_EAXREVERB_DEFAULT_GAIN)
		, mGainHF(AL_EAXREVERB_DEFAULT_GAINHF)
		, mGainLF(AL_EAXREVERB_DEFAULT_GAINLF)
		, mDensity(AL_EAXREVERB_DEFAULT_DENSITY)
		, mDiffusion(AL_EAXREVERB_DEFAULT_DIFFUSION)
		, mReflectionsGain(AL_EAXREVERB_DEFAULT_REFLECTIONS_GAIN)
		, mDecayTime(AL_EAXREVERB_DEFAULT_DECAY_TIME)
		, mRoomRolloff(AL_EAXREVERB_DEFAULT_ROOM_ROLLOFF_FACTOR)
		, mDecayHFLimit(AL_EAXREVERB_DEFAULT_DECAY_HFLIMIT)
		, mReverbGain(AL_EAXREVERB_DEFAULT_LATE_REVERB_GAIN)
		, mReverbDelay(AL_EAXREVERB_DEFAULT_LATE_REVERB_DELAY)
		, mDecayHFRatio(AL_EAXREVERB_DEFAULT_DECAY_HFRATIO)
		, mDecayLFRatio(AL_EAXREVERB_DEFAULT_DECAY_LFRATIO)
		, mLFReference(AL_EAXREVERB_DEFAULT_LFREFERENCE)
		, mEchoTime(AL_EAXREVERB_DEFAULT_ECHO_TIME)
		, mEchoDepth(AL_EAXREVERB_DEFAULT_ECHO_DEPTH)
		, mModulationTime(AL_EAXREVERB_DEFAULT_MODULATION_TIME)
		, mModulationDepth(AL_EAXREVERB_DEFAULT_MODULATION_DEPTH)
		, mReverbPreset(1)
	{
		mDspType = AL_EFFECT_EAXREVERB;
		Setup();
		// Update();
	}

	SoundReverbFilterComponent::~SoundReverbFilterComponent() {}

	void SoundReverbFilterComponent::ParamsValidCheck()
	{
		mDensity	= Math::n_clamp(mDensity,AL_EAXREVERB_MIN_DENSITY,AL_EAXREVERB_MAX_DENSITY);
		mDiffusion = Math::n_clamp(mDiffusion,AL_EAXREVERB_MIN_DIFFUSION, AL_EAXREVERB_MAX_DIFFUSION);
		mGain		= Math::n_clamp(mGain, AL_EAXREVERB_MIN_GAIN, AL_EAXREVERB_MAX_GAIN);
		mDecayTime = Math::n_clamp(mDecayTime, AL_EAXREVERB_MIN_DECAY_TIME, AL_EAXREVERB_MAX_DECAY_TIME);
		mDecayHFRatio = Math::n_clamp(mDecayHFRatio,AL_EAXREVERB_MIN_DECAY_HFRATIO, AL_EAXREVERB_MAX_DECAY_HFRATIO);
		mGainHF	= Math::n_clamp(mGainHF, AL_EAXREVERB_MIN_GAINHF, AL_EAXREVERB_MAX_GAINHF);
		mGainLF	= Math::n_clamp(mGainLF, AL_EAXREVERB_MIN_GAINLF, AL_EAXREVERB_MAX_GAINLF);
		mReflectionsDelay = Math::n_clamp( mReflectionsDelay, AL_EAXREVERB_MIN_REFLECTIONS_DELAY, AL_EAXREVERB_MAX_REFLECTIONS_DELAY);
		mReverbGain	= Math::n_clamp(mReverbGain, AL_EAXREVERB_MIN_REFLECTIONS_GAIN,AL_EAXREVERB_MAX_LATE_REVERB_GAIN);
		mReverbDelay	= Math::n_clamp(mReverbDelay,AL_EAXREVERB_MIN_LATE_REVERB_DELAY,AL_EAXREVERB_MAX_LATE_REVERB_DELAY);
		mModulationDepth	= Math::n_clamp(mModulationDepth,AL_EAXREVERB_MIN_MODULATION_DEPTH,AL_EAXREVERB_MAX_MODULATION_DEPTH);
		mAirGainHF		= Math::n_clamp(mAirGainHF,AL_EAXREVERB_MIN_AIR_ABSORPTION_GAINHF,AL_EAXREVERB_MAX_AIR_ABSORPTION_GAINHF);
		mHFReference	= Math::n_clamp(mHFReference,AL_EAXREVERB_MIN_HFREFERENCE,AL_EAXREVERB_MAX_HFREFERENCE);
		mLFReference	= Math::n_clamp(mLFReference,AL_EAXREVERB_MIN_LFREFERENCE,AL_EAXREVERB_MAX_LFREFERENCE);
		mDecayLFRatio = Math::n_clamp(mDecayLFRatio, AL_EAXREVERB_MIN_DECAY_LFRATIO, AL_EAXREVERB_MAX_DECAY_LFRATIO);
		mReflectionsGain = Math::n_clamp(mReflectionsGain, AL_EAXREVERB_MIN_REFLECTIONS_GAIN, AL_EAXREVERB_MAX_REFLECTIONS_GAIN);
		mEchoTime		= Math::n_clamp(mEchoTime,AL_EAXREVERB_MIN_ECHO_TIME,AL_EAXREVERB_MAX_ECHO_TIME);
		mEchoDepth		= Math::n_clamp(mEchoDepth,AL_EAXREVERB_MIN_ECHO_DEPTH,AL_EAXREVERB_MAX_ECHO_DEPTH);
		mModulationTime	= Math::n_clamp(mModulationTime,AL_EAXREVERB_MIN_MODULATION_TIME,AL_EAXREVERB_MAX_MODULATION_TIME);
		mRoomRolloff	= Math::n_clamp(mRoomRolloff,AL_EAXREVERB_MIN_ROOM_ROLLOFF_FACTOR,AL_EAXREVERB_MAX_ROOM_ROLLOFF_FACTOR);
		mDecayHFLimit	= Math::n_clamp(mDecayHFLimit,AL_EAXREVERB_MIN_DECAY_HFLIMIT,AL_EAXREVERB_MAX_DECAY_HFLIMIT);
	}

	void SoundReverbFilterComponent::SetDspParamter()
	{
		if ( !mDSP.isvalid() )
		{
			return;
		}

		if (mReverbPreset < 22)
		{
			CopyValueFromPreset(mReverbPreset);

			EFXEAXREVERBPROPERTIES prop = ReverbPresets[mReverbPreset];
			SetEFXEAXReverbProperties(&prop);
		}
		else
		{
			mDSP->setParameter( AL_EAXREVERB_DENSITY,mDensity);
			mDSP->setParameter( AL_EAXREVERB_DIFFUSION,mDiffusion);
			mDSP->setParameter( AL_EAXREVERB_GAIN, mGain);
			mDSP->setParameter( AL_EAXREVERB_GAINHF, mGainHF);
			mDSP->setParameter( AL_EAXREVERB_GAINLF, mGainLF);
			mDSP->setParameter( AL_EAXREVERB_DECAY_TIME, mDecayTime);
			mDSP->setParameter( AL_EAXREVERB_DECAY_HFRATIO, mDecayHFRatio);
			mDSP->setParameter( AL_EAXREVERB_DECAY_LFRATIO, mDecayLFRatio);
			mDSP->setParameter( AL_EAXREVERB_REFLECTIONS_GAIN, mReflectionsGain);
			mDSP->setParameter( AL_EAXREVERB_REFLECTIONS_DELAY, mReflectionsDelay);
			mDSP->setParameter( AL_EAXREVERB_LATE_REVERB_GAIN, mReverbGain);
			mDSP->setParameter( AL_EAXREVERB_LATE_REVERB_DELAY, mReverbDelay);
			mDSP->setParameter( AL_EAXREVERB_ECHO_TIME, mEchoTime);
			mDSP->setParameter( AL_EAXREVERB_ECHO_DEPTH, mEchoDepth);
			mDSP->setParameter( AL_EAXREVERB_MODULATION_TIME, mModulationTime);
			mDSP->setParameter( AL_EAXREVERB_MODULATION_DEPTH, mModulationDepth);
			mDSP->setParameter( AL_EAXREVERB_AIR_ABSORPTION_GAINHF, mAirGainHF);
			mDSP->setParameter( AL_EAXREVERB_HFREFERENCE, mHFReference);
			mDSP->setParameter( AL_EAXREVERB_LFREFERENCE, mLFReference);
			mDSP->setParameter( AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, mRoomRolloff);
			mDSP->setParameter( AL_EAXREVERB_DECAY_HFLIMIT, (float)mDecayHFLimit, true);
		}

		int iSendIndex = mDSP->GetSendIndex();
		AttachFilter(__Active, iSendIndex);
	}

	void SoundReverbFilterComponent::CopyValueFromPreset(int preset)
	{
		if ( preset < 22 )
		{
			EFXEAXREVERBPROPERTIES prop = ReverbPresets[preset];
			mDensity			= prop.flDensity;
			mDiffusion			= prop.flDiffusion;
			mGain				= prop.flGain;
			mGainHF			= prop.flGainHF;
			mGainLF			= prop.flGainLF;
			mDecayTime			= prop.flDecayTime;
			mDecayHFRatio		= prop.flDecayHFRatio;
			mDecayLFRatio		= prop.flDecayLFRatio;
			mReflectionsGain	= prop.flReflectionsGain;
			mReflectionsDelay  = prop.flReflectionsDelay;
			mReverbGain		= prop.flLateReverbGain;
			mReverbDelay		= prop.flLateReverbDelay;
			mEchoTime			= prop.flEchoTime;
			mEchoDepth			= prop.flEchoDepth;
			mModulationTime	= prop.flModulationTime;
			mModulationDepth	= prop.flModulationDepth;
			mAirGainHF			= prop.flAirAbsorptionGainHF;
			mHFReference		= prop.flHFReference;
			mLFReference		= prop.flLFReference;
			mRoomRolloff		= prop.flRoomRolloffFactor;
			mDecayHFLimit		= prop.iDecayHFLimit;
		}

	}

	void SoundReverbFilterComponent::SetReverbPreset(const int reverbPreset)
	{
		if (mReverbPreset != reverbPreset)
		{
			mReverbPreset = reverbPreset;
			SetDspParamter();
		}
	}

	void SoundReverbFilterComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;

		GPtr<SoundReverbFilterComponent> pSource = pComponent.downcast<SoundReverbFilterComponent>();
		mReverbPreset		= pSource->GetReverbPreset();

		mDensity			= pSource->GetReverbParam(Density);
		mDiffusion			= pSource->GetReverbParam(Diffusion);
		mGain				= pSource->GetReverbParam(Gain);
		mGainHF			= pSource->GetReverbParam(GainHF);
		mGainLF			= pSource->GetReverbParam(GainLF);
		mDecayTime			= pSource->GetReverbParam(DecayTime);
		mDecayHFRatio		= pSource->GetReverbParam(DecayHFRatio);
		mDecayLFRatio		= pSource->GetReverbParam(DecayLFRatio);
		mReflectionsGain	= pSource->GetReverbParam(ReflectionsGain);
		mReflectionsDelay	= pSource->GetReverbParam(ReflectionsDelay);
		mReverbGain		= pSource->GetReverbParam(ReverbGain);
		mReverbDelay		= pSource->GetReverbParam(ReverbDelay);
		mEchoTime			= pSource->GetReverbParam(EchoTime);
		mEchoDepth			= pSource->GetReverbParam(EchoDepth);
		mModulationTime	= pSource->GetReverbParam(ModulationTime);
		mModulationDepth	= pSource->GetReverbParam(ModulationDepth);
		mAirGainHF			= pSource->GetReverbParam(AirGainHF);
		mHFReference		= pSource->GetReverbParam(HFReference);
		mLFReference		= pSource->GetReverbParam(LFReference);
		mRoomRolloff		= pSource->GetReverbParam(RoomRolloff);
		mDecayHFLimit		= (int)pSource->GetReverbParam(DecayHFLimit);
	}


	bool SoundReverbFilterComponent::SetEFXEAXReverbProperties( EFXEAXREVERBPROPERTIES *pEFXEAXReverb)
	{
		bool result = false;

		if ( pEFXEAXReverb )
		{
			mDSP->setParameter(AL_EAXREVERB_DENSITY,pEFXEAXReverb->flDensity);
			mDSP->setParameter(AL_EAXREVERB_DIFFUSION,pEFXEAXReverb->flDiffusion);
			mDSP->setParameter( AL_EAXREVERB_GAIN, pEFXEAXReverb->flGain);
			mDSP->setParameter( AL_EAXREVERB_GAINHF, pEFXEAXReverb->flGainHF);
			mDSP->setParameter( AL_EAXREVERB_GAINLF, pEFXEAXReverb->flGainLF);
			mDSP->setParameter( AL_EAXREVERB_DECAY_TIME, pEFXEAXReverb->flDecayTime);
			mDSP->setParameter( AL_EAXREVERB_DECAY_HFRATIO, pEFXEAXReverb->flDecayHFRatio);
			mDSP->setParameter( AL_EAXREVERB_DECAY_LFRATIO, pEFXEAXReverb->flDecayLFRatio);
			mDSP->setParameter( AL_EAXREVERB_REFLECTIONS_GAIN, pEFXEAXReverb->flReflectionsGain);
			mDSP->setParameter( AL_EAXREVERB_REFLECTIONS_DELAY, pEFXEAXReverb->flReflectionsDelay);
			mDSP->setParameters( AL_EAXREVERB_REFLECTIONS_PAN, pEFXEAXReverb->flReflectionsPan);
			mDSP->setParameter( AL_EAXREVERB_LATE_REVERB_GAIN, pEFXEAXReverb->flLateReverbGain);
			mDSP->setParameter( AL_EAXREVERB_LATE_REVERB_DELAY, pEFXEAXReverb->flLateReverbDelay);
			mDSP->setParameters( AL_EAXREVERB_LATE_REVERB_PAN, pEFXEAXReverb->flLateReverbPan);
			mDSP->setParameter( AL_EAXREVERB_ECHO_TIME, pEFXEAXReverb->flEchoTime);
			mDSP->setParameter( AL_EAXREVERB_ECHO_DEPTH, pEFXEAXReverb->flEchoDepth);
			mDSP->setParameter( AL_EAXREVERB_MODULATION_TIME, pEFXEAXReverb->flModulationTime);
			mDSP->setParameter( AL_EAXREVERB_MODULATION_DEPTH, pEFXEAXReverb->flModulationDepth);
			mDSP->setParameter( AL_EAXREVERB_AIR_ABSORPTION_GAINHF, pEFXEAXReverb->flAirAbsorptionGainHF);
			mDSP->setParameter( AL_EAXREVERB_HFREFERENCE, pEFXEAXReverb->flHFReference);
			mDSP->setParameter( AL_EAXREVERB_LFREFERENCE, pEFXEAXReverb->flLFReference);
			mDSP->setParameter( AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, pEFXEAXReverb->flRoomRolloffFactor);
			mDSP->setParameter( AL_EAXREVERB_DECAY_HFLIMIT, (float)pEFXEAXReverb->iDecayHFLimit, true);

			if (alGetError() == AL_NO_ERROR)
				result = AL_TRUE;
		}

		return result;
	}

	float SoundReverbFilterComponent::GetReverbParam(ReverbParam param) const
	{
		switch(param)
		{
		case Density:
			return mDensity;
		case Diffusion:
			return mDiffusion;
		case Gain:
			return mGain;
		case GainHF:
			return mGainHF;
		case GainLF:
			return mGainLF;
		case DecayTime:
			return mDecayTime;
		case DecayHFRatio:
			return mDecayHFRatio;
		case DecayLFRatio:
			return mDecayLFRatio;
		case ReflectionsGain:
			return mReflectionsGain;
		case ReflectionsDelay:
			return mReflectionsDelay;
		case ReverbGain:
			return mReverbGain;
		case ReverbDelay:
			return mReverbDelay;
		case EchoTime:
			return mEchoTime;
		case EchoDepth:
			return mEchoDepth;
		case ModulationTime:
			return mModulationTime;
		case ModulationDepth:
			return mModulationDepth;
		case AirGainHF:
			return mAirGainHF;
		case HFReference:
			return mHFReference;
		case LFReference:
			return mLFReference;
		case RoomRolloff:
			return mRoomRolloff;
		case DecayHFLimit:
			return (float)mDecayHFLimit;
		default:
			return -1.0f;
		}
	}

	void SoundReverbFilterComponent::SetReverbParam(ReverbParam param, float value)
	{
		switch(param)
		{
		case Density:
			mDensity = value; break;
		case Diffusion:
			mDiffusion = value; break;
		case Gain:
			mGain = value; break;
		case GainHF:
			mGainHF = value; break;
		case GainLF:
			mGainLF = value; break;
		case DecayTime:
			mDecayTime = value; break;
		case DecayHFRatio:
			mDecayHFRatio = value; break;
		case DecayLFRatio:
			mDecayLFRatio = value; break;
		case ReflectionsGain:
			mReflectionsGain = value; break;
		case ReflectionsDelay:
			mReflectionsDelay = value; break;
		case ReverbGain:
			mReverbGain = value; break;
		case ReverbDelay:
			mReverbDelay = value; break;
		case EchoTime:
			mEchoTime = value; break;
		case EchoDepth:
			mEchoDepth = value; break;
		case ModulationTime:
			mModulationTime = value; break;
		case ModulationDepth:
			mModulationDepth = value; break;
		case AirGainHF:
			mAirGainHF = value; break;
		case HFReference:
			mHFReference = value; break;
		case LFReference:
			mLFReference = value; break;
		case RoomRolloff:
			mRoomRolloff = value; break;
		case DecayHFLimit:
			mDecayHFLimit = (int)value; break;
		}

		ParamsValidCheck();
		SetDspParamter();
	}

	void SoundReverbFilterComponent::OnActivate()
	{
		Super::OnActivate();
	}

	void SoundReverbFilterComponent::OnDeactivate()
	{
		Super::OnDeactivate();
	}


}

#endif //__SOUND_COMMIT__
