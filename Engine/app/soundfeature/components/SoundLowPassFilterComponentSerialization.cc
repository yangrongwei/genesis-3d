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
#ifndef __SoundLowPassFilterComponentSerialization_H__
#define __SoundLowPassFilterComponentSerialization_H__

#include "stdneb.h"
#include "SoundLowPassFilterComponent.h"

namespace App
{

	class SoundLowPassFilterComponentSerialization
	{
	public:
		SoundLowPassFilterComponentSerialization(const SoundLowPassFilterComponent* pComponent)
			: mObject(pComponent)
		{}

		~SoundLowPassFilterComponentSerialization()
		{}

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
					n_error(" SoundLowPassFilterComponentSerialization::Load unknonw version " );
					break;
				}
			}

			return;
		}

		void Load_1(AppReader* pReader);
		void Save(AppWriter* pWriter);

	protected:
		const SoundLowPassFilterComponent* mObject;
	}; //class SoundLowPassFilterComponentSerialization


	const char* s_LowPassGain = "Gain";
	const char* s_LowPassGainHF = "GainHF";

	//------------------------------------------------------------------------------
	void SoundLowPassFilterComponentSerialization::Load_1(AppReader* pReader)
	{
		n_assert(mObject);

		SoundLowPassFilterComponent* pLowPassFilter = const_cast<SoundLowPassFilterComponent*>(mObject);
		n_assert(pLowPassFilter);

		// Gain
		float Gain;
		pReader->SerializeFloat(s_LowPassGain, Gain);
		pLowPassFilter->SetLowPassParam(SoundLowPassFilterComponent::Gain,Gain);
		// GainHF
		float GainHF;
		pReader->SerializeFloat(s_LowPassGainHF, GainHF);
		pLowPassFilter->SetLowPassParam(SoundLowPassFilterComponent::GainHF,GainHF);

		return;
	}

	//------------------------------------------------------------------------------
	void SoundLowPassFilterComponentSerialization::Save(AppWriter* pWriter)
	{
		n_assert(mObject);
		n_assert(pWriter);

		SoundLowPassFilterComponent* pLowPassFilter = const_cast<SoundLowPassFilterComponent*>(mObject);
		n_assert(pLowPassFilter);

		// Gain
		float Gain = pLowPassFilter->GetLowPassParam(SoundLowPassFilterComponent::Gain);
		pWriter->SerializeFloat(s_LowPassGain, Gain);
		// GainHF
		float GainHF = pLowPassFilter->GetLowPassParam(SoundLowPassFilterComponent::GainHF);
		pWriter->SerializeFloat(s_LowPassGainHF, GainHF);
		return;
	}

	///
	//------------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version SoundLowPassFilterComponent::GetVersion() const
	{
		return 1;	//	Current version number is 1.
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Load 
	void SoundLowPassFilterComponent::Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		SoundLowPassFilterComponentSerialization serialize(this);
		serialize.Load(ver, pReader);
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Save
	void SoundLowPassFilterComponent::Save(AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		SoundLowPassFilterComponentSerialization serialize(this);
		serialize.Save(pWriter);
	}

}


#endif //__SoundLowPassFilterComponentSerialization_H__ 
#endif //__SOUND_COMMIT__
