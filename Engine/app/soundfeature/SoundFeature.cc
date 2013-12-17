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
#include "foundation/io/assignregistry.h"
#include "profilesystem/ProfileSystem.h"
#include "soundfeature/components/SoundSourceComponent.h"
#include "soundfeature/SoundFeature.h"

#include "soundsystem/SoundSystemOpenAL.h"
#include "soundsystem/SoundBufferOpenAL.h"

namespace App
{

	__ImplementClass(App::SoundFeature, 'SDFT' , App::Feature);
	__ImplementImageSingleton(App::SoundFeature);

	//------------------------------------------------------------------------------
	SoundFeature::SoundFeature()
		: mVolume(1.0f)
		, mEnableAutoPlay(true)
		, mSoundSystem(NULL)
	{
		__ConstructImageSingleton;

		mFeatureName = "Sound";
	}

	//------------------------------------------------------------------------------
	SoundFeature::~SoundFeature()
	{
		mSources.Clear();
		mListeners.Clear();
		mSoundSystem->ReleaseSoundSystem();
		__DestructImageSingleton;
	}
	//------------------------------------------------------------------------------
	void SoundFeature::OnActivate()
	{
		Feature::OnActivate();
		bool ret = InitSoundSystem();
		if (!ret)
		{
			return;
		}
		return;
	}
	//------------------------------------------------------------------------------
	bool SoundFeature::InitSoundSystem()
	{
		mSoundSystem = Sound::SoundSystemOpenAL::Create();

		if (NULL != mSoundSystem)
		{
			bool ret = mSoundSystem->InitSoundSystem();
			return ret;
		}

		return false;
	}
	//------------------------------------------------------------------------------
	void SoundFeature::AttachSoundSource(SoundSource* source)
	{
		n_assert(source);
		mSources.AddBack(source);
	}

	//------------------------------------------------------------------------------
	void SoundFeature::DetachSoundSource(SoundSource* source)
	{
		n_assert(source);
		Util::List< GPtr<SoundSource> >::Iterator itor = mSources.Begin();
		itor = mSources.Find(source, itor);
		if (itor != mSources.End())
		{
			mSources.Remove(itor);
		}

		return;
	}
	//------------------------------------------------------------------------------
	Sound::SoundSystemSource* SoundFeature::GetFreeSoundSystemSource(Sound::SoundBuffer* soungBuffer, bool paused)
	{
		if (!mSoundSystem)
		{
			return NULL;
		}

		Sound::SoundSystemSource* source = NULL;

		bool ret = mSoundSystem->PlaySound(soungBuffer, &source, paused);

		if (!ret)
		{
			return NULL;
		}

		return source;
	}

	//------------------------------------------------------------------------------
	void SoundFeature::OnFrame()
	{	
		PROFILER_ADDDTICKBEGIN(soundsTime);

		Util::List< GPtr<SoundListener> >::Iterator itorL;
		for (itorL = mListeners.Begin(); itorL != mListeners.End(); itorL++)
		{
			SoundListener& curListener = **itorL;
			curListener.UpdateListenerInfo();
		}

		Util::List< GPtr<SoundSource> >::Iterator itorS;
		for (itorS = mSources.Begin(); itorS != mSources.End(); itorS++)
		{
			SoundSource& curSource = **itorS;
			curSource.UpdateSoundInfo();
		}

		Super::OnFrame();
		PROFILER_ADDDTICKEND(soundsTime);
	}
	//------------------------------------------------------------------------------
	Sound::SoundBuffer* SoundFeature::CreateSoundBuffer(const char* nameOrData, 
		SizeT dataSize, 
		GENESISOUND_MODE mode,
		GENESIS_FILE_FORMAT fileFormat)
	{
		Sound::SoundBuffer* soundBuf = NULL;

		if (!mSoundSystem.isvalid())
		{
			return NULL;
		}

		bool ret = false;
		if (mode & GENESISSOUND_OPENMEMORY)
		{
			ret = mSoundSystem->CreateSoundBuffer(nameOrData, dataSize, &soundBuf,
				mode, fileFormat);
		} 
		else
		{
			IO::URI inputFile = IO::AssignRegistry::Instance()->ResolveAssigns(nameOrData);
			Util::String inputPath = inputFile.LocalPath();
			ret = mSoundSystem->CreateSoundBuffer(inputPath.AsCharPtr(), 0, &soundBuf, 
				mode, fileFormat);
		}

		if (!ret)
		{
			return NULL;
		}

		return soundBuf;
	}
	//------------------------------------------------------------------------------
	void SoundFeature::AttachSoundListener(SoundListener* listener)
	{
		n_assert(listener);

		mListeners.AddBack(listener);
		return;
	}

	//------------------------------------------------------------------------------
	void SoundFeature::DetachSoundListener(SoundListener* listener)
	{
		n_assert(listener);

		Util::List< GPtr<SoundListener> >::Iterator itor = mListeners.Begin();
		itor = mListeners.Find(listener, itor);
		if (itor != mListeners.End())
		{
			mListeners.Remove(itor);
		}

		return;
	}

	//------------------------------------------------------------------------------
	SoundListener* SoundFeature::GetSoundListener()
	{
		if (!mListeners.IsEmpty())
		{
			return mListeners.Back();
		}

		return NULL;
	}
	//------------------------------------------------------------------------------
	float SoundFeature::CalcInvFrameTime(const float dt)
	{
		if (dt > TINY)
		{
			return 1.0F / dt;
		}
		else
		{
			return 1.0F;
		}
	}

	//------------------------------------------------------------------------------
	void SoundFeature::UpdateListenerAttrs(const Math::vector& pos, 
		const Math::vector& v, 
		const Math::vector& forward,
		const Math::vector& up)
	{
		if (!mSoundSystem)
		{
			return;
		}

		mSoundSystem->SetListenerAttrs(0, pos, v, forward, up);
	}

	//------------------------------------------------------------------------------
	float SoundFeature::GetVolume(void) const
	{
		return mVolume;
	}

	//------------------------------------------------------------------------------
	void SoundFeature::SetVolume(const float volume)
	{
		mVolume = volume;
	}

} // namespace App
#endif //__SOUND_COMMIT__

