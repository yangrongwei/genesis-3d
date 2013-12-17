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
#ifndef __SoundReverbFilterComponentSerialization_H__
#define __SoundReverbFilterComponentSerialization_H__

#include "stdneb.h"
#include "SoundReverbFilterComponent.h"

namespace App
{

	class SoundReverbFilterComponentSerialization
	{
	public:
		SoundReverbFilterComponentSerialization(const SoundReverbFilterComponent* pComponent)
			: mObject(pComponent)
		{}

		~SoundReverbFilterComponentSerialization() {}

		inline void Load(Version ver, AppReader* pReader)
		{
			switch (ver)
			{
			case 1:
				{
					Load_1(pReader);
					break;
				}
			default:
				{
					n_error(" SoundReverbFilterComponentSerialization::Load unknonw version " );
					break;
				}
			}

			return;
		}

		void Load_1(AppReader* pReader);
		void Save(AppWriter* pWriter);

	protected:
		const SoundReverbFilterComponent* mObject;
	}; //class SoundReverbFilterComponentSerialization


	const char* s_ReverbDensity = "Density";
	const char* s_ReverbDiffusion = "Diffusion";
	const char* s_ReverbGain = "Gain";
	const char* s_ReverbGainHF = "GainHF";
	const char* s_ReverbGainLF = "GainLF";
	const char* s_ReverbDecayTime = "DecayTime";
	const char* s_ReverbDecayHFRatio = "DecayHFRatio";
	const char* s_ReverbDecayLFRatio = "DecayLFRatio";
	const char* s_ReverbReflectionsGain = "ReflectionsGain";
	const char* s_ReverbReflectionsDelay = "ReflectionsDelay"; 
	const char* s_ReverbReverbGain = "ReverbGain";
	const char* s_ReverbReverbDelay = "ReverbDelay";
	const char* s_ReverbEchoTime = "EchoTime";
	const char* s_ReverbEchoDepth = "EchoDepth";
	const char* s_ReverbModulationTime = "ModulationTime";
	const char* s_ReverbModulationDepth = "ModulationDepth";
	const char* s_ReverbAirGainHF = "AirGainHF";
	const char* s_ReverbHFReference = "HFReference";
	const char* s_ReverbLFReference = "LFReference";
	const char* s_ReverbRoomRolloff = "RoomRolloff";
	const char* s_ReverbDecayHFLimit = "DecayHFLimit";
	const char* s_ReverbReverbPreset = "ReverbPreset"; 

	//------------------------------------------------------------------------------
	void SoundReverbFilterComponentSerialization::Load_1(AppReader* pReader)
	{
		n_assert(mObject);

		SoundReverbFilterComponent* pReverbFilter = const_cast<SoundReverbFilterComponent*>(mObject);
		n_assert(pReverbFilter);

		//ReverbPresent
		int ReverbPreset;
		pReader->SerializeInt(s_ReverbReverbPreset, ReverbPreset);
		pReverbFilter->SetReverbPreset(ReverbPreset);
		// Density
		float Density;
		pReader->SerializeFloat(s_ReverbDensity, Density);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::Density,Density);
		// Diffusion
		float Diffusion;
		pReader->SerializeFloat(s_ReverbDiffusion, Diffusion);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::Diffusion,Diffusion);
		// Gain
		float Gain;
		pReader->SerializeFloat(s_ReverbGain, Gain);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::Gain,Gain);
		// GainHF
		float GainHF;
		pReader->SerializeFloat(s_ReverbGainHF, GainHF);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::GainHF,GainHF);
		// GainLF
		float GainLF;
		pReader->SerializeFloat(s_ReverbGainLF, GainLF);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::GainLF,GainLF);
		// DecayTime
		float DecayTime;
		pReader->SerializeFloat(s_ReverbDecayTime, DecayTime);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::DecayTime,DecayTime);
		// DecayHFRatio
		float DecayHFRatio;
		pReader->SerializeFloat(s_ReverbDecayHFRatio, DecayHFRatio);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::DecayHFRatio,DecayHFRatio);
		// DecayLFRatio
		float DecayLFRatio;
		pReader->SerializeFloat(s_ReverbDecayLFRatio, DecayLFRatio);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::DecayLFRatio,DecayLFRatio);
		// ReflectionsGain
		float ReflectionsGain;
		pReader->SerializeFloat(s_ReverbReflectionsGain, ReflectionsGain);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::ReflectionsGain,ReflectionsGain);
		// ReflectionsDelay
		float ReflectionsDelay;
		pReader->SerializeFloat(s_ReverbReflectionsDelay, ReflectionsDelay);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::ReflectionsDelay,ReflectionsDelay);
		// ReverbGain
		float ReverbGain;
		pReader->SerializeFloat(s_ReverbReverbGain, ReverbGain);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::ReverbGain,ReverbGain);
		// ReverbDelay
		float ReverbDelay;
		pReader->SerializeFloat(s_ReverbReverbDelay, ReverbDelay);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::ReverbDelay,ReverbDelay);
		// EchoTime
		float EchoTime;
		pReader->SerializeFloat(s_ReverbEchoTime, EchoTime);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::EchoTime,EchoTime);
		// EchoDepth
		float EchoDepth;
		pReader->SerializeFloat(s_ReverbEchoDepth, EchoDepth);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::EchoDepth,EchoDepth);
		// ModulationTime
		float ModulationTime;
		pReader->SerializeFloat(s_ReverbModulationTime, ModulationTime);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::ModulationTime,ModulationTime);
		// ModulationDepth
		float ModulationDepth;
		pReader->SerializeFloat(s_ReverbModulationDepth, ModulationDepth);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::ModulationDepth,ModulationDepth);
		// AirGainHF
		float AirGainHF;
		pReader->SerializeFloat(s_ReverbAirGainHF, AirGainHF);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::AirGainHF,AirGainHF);
		// HFReference
		float HFReference;
		pReader->SerializeFloat(s_ReverbHFReference, HFReference);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::HFReference,HFReference);
		// LFReference
		float LFReference;
		pReader->SerializeFloat(s_ReverbLFReference, LFReference);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::LFReference,LFReference);
		// RoomRolloff
		float RoomRolloff;
		pReader->SerializeFloat(s_ReverbRoomRolloff, RoomRolloff);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::RoomRolloff,RoomRolloff);
		// DecayHFLimit
		float DecayHFLimit;
		pReader->SerializeFloat(s_ReverbDecayHFLimit, DecayHFLimit);
		pReverbFilter->SetReverbParam(SoundReverbFilterComponent::DecayHFLimit,DecayHFLimit);

		return;
	}

	//------------------------------------------------------------------------------
	void SoundReverbFilterComponentSerialization::Save(AppWriter* pWriter)
	{
		n_assert(mObject);
		n_assert(pWriter);

		SoundReverbFilterComponent* pReverbFilter = const_cast<SoundReverbFilterComponent*>(mObject);
		n_assert(pReverbFilter);

		//ReverbPresent
		int ReverbPreset = pReverbFilter->GetReverbPreset();
		pWriter->SerializeInt(s_ReverbReverbPreset, ReverbPreset);		
		// Density
		float Density = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::Density);
		pWriter->SerializeFloat(s_ReverbDensity, Density);
		// Diffusion
		float Diffusion = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::Diffusion);
		pWriter->SerializeFloat(s_ReverbDiffusion, Diffusion);
		// Gain
		float Gain = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::Gain);
		pWriter->SerializeFloat(s_ReverbGain, Gain);
		// GainHF
		float GainHF = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::GainHF);
		pWriter->SerializeFloat(s_ReverbGainHF, GainHF);
		// GainLF
		float GainLF = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::GainLF);
		pWriter->SerializeFloat(s_ReverbGainLF, GainLF);
		// DecayTime
		float DecayTime = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::DecayTime);
		pWriter->SerializeFloat(s_ReverbDecayTime, DecayTime);
		// DecayHFRatio
		float DecayHFRatio = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::DecayHFRatio);
		pWriter->SerializeFloat(s_ReverbDecayHFRatio, DecayHFRatio);
		// DecayLFRatio
		float DecayLFRatio = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::DecayLFRatio);
		pWriter->SerializeFloat(s_ReverbDecayLFRatio, DecayLFRatio);
		// ReflectionsGain
		float ReflectionsGain = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::ReflectionsGain);
		pWriter->SerializeFloat(s_ReverbReflectionsGain, ReflectionsGain);
		// ReflectionsDelay
		float ReflectionsDelay = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::ReflectionsDelay);
		pWriter->SerializeFloat(s_ReverbReflectionsDelay, ReflectionsDelay);
		// ReverbGain
		float ReverbGain = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::ReverbGain);
		pWriter->SerializeFloat(s_ReverbReverbGain, ReverbGain);
		// ReverbDelay
		float ReverbDelay = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::ReverbDelay);
		pWriter->SerializeFloat(s_ReverbReverbDelay, ReverbDelay);
		// EchoTime
		float EchoTime = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::EchoTime);
		pWriter->SerializeFloat(s_ReverbEchoTime, EchoTime);
		// EchoDepth
		float EchoDepth = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::EchoDepth);
		pWriter->SerializeFloat(s_ReverbEchoDepth, EchoDepth);
		// ModulationTime
		float ModulationTime = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::ModulationTime);
		pWriter->SerializeFloat(s_ReverbModulationTime, ModulationTime);
		// ModulationDepth
		float ModulationDepth = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::ModulationDepth);
		pWriter->SerializeFloat(s_ReverbModulationDepth, ModulationDepth);
		// AirGainHF
		float AirGainHF = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::AirGainHF);
		pWriter->SerializeFloat(s_ReverbAirGainHF, AirGainHF);
		// HFReference
		float HFReference = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::HFReference);
		pWriter->SerializeFloat(s_ReverbHFReference, HFReference);
		// LFReference
		float LFReference = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::LFReference);
		pWriter->SerializeFloat(s_ReverbLFReference, LFReference);
		// RoomRolloff
		float RoomRolloff = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::RoomRolloff);
		pWriter->SerializeFloat(s_ReverbRoomRolloff, RoomRolloff);
		// DecayHFLimit
		float DecayHFLimit = pReverbFilter->GetReverbParam(SoundReverbFilterComponent::DecayHFLimit);
		pWriter->SerializeFloat(s_ReverbDecayHFLimit, DecayHFLimit);
		return;

	}

	///
	//------------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version SoundReverbFilterComponent::GetVersion() const
	{
		return 1;	//	Current version number is 1.
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Load 
	void SoundReverbFilterComponent::Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		SoundReverbFilterComponentSerialization serialize(this);
		serialize.Load(ver, pReader);
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Save
	void SoundReverbFilterComponent::Save(AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		SoundReverbFilterComponentSerialization serialize(this);
		serialize.Save(pWriter);
	}

}

#endif //__SoundReverbFilterComponentSerialization_H__


#endif //__SOUND_COMMIT__
