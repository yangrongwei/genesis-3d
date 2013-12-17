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
#ifndef __SOUNDREVERB_FILTER_H__ 
#define __SOUNDREVERB_FILTER_H__ 

#include "appframework/component.h"
#include "soundfeature/SoundFeature.h"
#include "SoundFilterComponent.h"
#include "app/soundfeature/SoundTypes.h"


namespace App
{
	class SoundReverbFilterComponent : public SoundFilterComponent
	{
		__DeclareSubClass(SoundReverbFilterComponent, SoundFilterComponent);

	public:
		enum ReverbParam
		{
			Density = 0,
			Diffusion,
			Gain,
			GainHF,
			GainLF,
			DecayTime,
			DecayHFRatio,
			DecayLFRatio,
			ReflectionsGain,
			ReflectionsDelay,
			ReverbGain,
			ReverbDelay,
			EchoTime,
			EchoDepth,
			ModulationTime,
			ModulationDepth,
			AirGainHF,
			HFReference,
			LFReference,
			RoomRolloff,
			DecayHFLimit,
			Present,
			None
		};

		SoundReverbFilterComponent();
		virtual ~SoundReverbFilterComponent();

		virtual void ParamsValidCheck ();
		virtual void SetDspParamter();
		virtual void OnActivate();
		virtual void OnDeactivate();

		int GetReverbPreset() const { return mReverbPreset; }
		void SetReverbPreset(const int reverbPreset);

		float GetReverbParam(ReverbParam param) const;
		void  SetReverbParam(ReverbParam param, float value);

		void CopyValueFromPreset(int preset);

		//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

		bool SetEFXEAXReverbProperties(EFXEAXREVERBPROPERTIES *pEFXEAXReverb);


	private:
		float mDensity;
		float mDiffusion;
		float mGain;
		float mGainHF;
		float mReverbGain;
		float mHFReference;
		float mDecayTime;
		float mGainLF;
		float mDecayHFRatio;
		float mDecayLFRatio;
		float mReflectionsGain;
		float mReflectionsDelay;
		float mLFReference;
		float mRoomRolloff;
		int	  mDecayHFLimit;
		int	  mReverbPreset;
		float mEchoDepth;
		float mReverbDelay;
		float mEchoTime;
		float mAirGainHF;
		float mModulationTime;
		float mModulationDepth;
	};

}
#endif //__SOUNDREVERB_FILTER_H__


