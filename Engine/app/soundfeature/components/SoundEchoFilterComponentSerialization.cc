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
#ifndef __SoundEchoFilterComponentSerialization_H__
#define __SoundEchoFilterComponentSerialization_H__

#include "stdneb.h"
#include "SoundEchoFilterComponent.h"

namespace App
{

	class SoundEchoFilterComponentSerialization
	{
	public:
		SoundEchoFilterComponentSerialization(const SoundEchoFilterComponent* pComponent)
			: mObject(pComponent)
		{}

		~SoundEchoFilterComponentSerialization() {}

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
					n_error(" SoundEchoFilterComponentSerialization::Load unknonw version " );
					break;
				}
			}

			return;
		}

		void Load_1(AppReader* pReader);
		void Save(AppWriter* pWriter);

	protected:
		const SoundEchoFilterComponent* mObject;
	}; //class SoundEchoFilterComponentSerialization


	const char* s_EchoDelay = "Delay";
	const char* s_EchoLRDelay = "LRDelay";
	const char* s_EchoDamping = "Damping";
	const char* s_EchoFeedBack = "FeedBack";
	const char* s_EchoSpread = "Spread";


	//------------------------------------------------------------------------------
	void SoundEchoFilterComponentSerialization::Load_1(AppReader* pReader)
	{
		n_assert(mObject);

		SoundEchoFilterComponent* pEchoFilter = const_cast<SoundEchoFilterComponent*>(mObject);
		n_assert(pEchoFilter);

		// Delay
		float Delay;
		pReader->SerializeFloat(s_EchoDelay, Delay);
		pEchoFilter->SetEchoParam(SoundEchoFilterComponent::Delay,Delay);
		// LRDelay
		float LRDelay;
		pReader->SerializeFloat(s_EchoLRDelay, LRDelay);
		pEchoFilter->SetEchoParam(SoundEchoFilterComponent::LRDelay,LRDelay);
		// Damping
		float Damping;
		pReader->SerializeFloat(s_EchoDamping, Damping);
		pEchoFilter->SetEchoParam(SoundEchoFilterComponent::Damping,Damping);
		// FeedBack
		float FeedBack;
		pReader->SerializeFloat(s_EchoFeedBack, FeedBack);
		pEchoFilter->SetEchoParam(SoundEchoFilterComponent::FeedBack,FeedBack);
		// Spread
		float Spread;
		pReader->SerializeFloat(s_EchoSpread, Spread);
		pEchoFilter->SetEchoParam(SoundEchoFilterComponent::Spread,Spread);

		return;
	}

	//------------------------------------------------------------------------------
	void SoundEchoFilterComponentSerialization::Save(AppWriter* pWriter)
	{
		n_assert(mObject);
		n_assert(pWriter);

		SoundEchoFilterComponent* pEchoFilter = const_cast<SoundEchoFilterComponent*>(mObject);
		n_assert(pEchoFilter);
		// Delay
		float Delay = pEchoFilter->GetEchoParam(SoundEchoFilterComponent::Delay);
		pWriter->SerializeFloat(s_EchoDelay, Delay);
		// LRDelay
		float LRDelay = pEchoFilter->GetEchoParam(SoundEchoFilterComponent::LRDelay);
		pWriter->SerializeFloat(s_EchoLRDelay, LRDelay);
		// Damping
		float Damping = pEchoFilter->GetEchoParam(SoundEchoFilterComponent::Damping);
		pWriter->SerializeFloat(s_EchoDamping, Damping);
		// FeedBack
		float FeedBack = pEchoFilter->GetEchoParam(SoundEchoFilterComponent::FeedBack);
		pWriter->SerializeFloat(s_EchoFeedBack, FeedBack);
		// Spread
		float Spread = pEchoFilter->GetEchoParam(SoundEchoFilterComponent::Spread);
		pWriter->SerializeFloat(s_EchoSpread, Spread);
		return;
	}

	///
	//------------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version SoundEchoFilterComponent::GetVersion() const
	{
		return 1;	//	Current version number is 1.
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Load 
	void SoundEchoFilterComponent::Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		SoundEchoFilterComponentSerialization serialize(this);
		serialize.Load(ver, pReader);
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Save
	void SoundEchoFilterComponent::Save(AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		SoundEchoFilterComponentSerialization serialize(this);
		serialize.Save(pWriter);
	}

}


#endif //__SoundEchoFilterComponentSerialization_H__
#endif //__SOUND_COMMIT__