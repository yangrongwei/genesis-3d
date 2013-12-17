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
#ifndef __SoundFeature_H__
#define __SoundFeature_H__
#ifndef __SOUND_COMMIT__

#include "soundsystem/SoundSystem.h"


#include "foundation/core/types.h"
#include "appframework/feature.h"
#include "soundfeature/SoundRes.h"
#include "soundfeature/SoundTypes.h"
#include "soundfeature/SoundSouceInfo.h"
#include "soundfeature/components/SoundListenerComponent.h"

namespace App
{

	class SoundSource;
	class SoundListener;


	class SoundFeature : public App::Feature    
	{
		__DeclareSubClass(SoundFeature, Feature);
		__DeclareImageSingleton(SoundFeature);   
	public:

		/// constructor
		SoundFeature();
		/// destructor
		virtual ~SoundFeature();

		/// called from GameServer::AttachGameFeature()
		virtual void OnActivate();

		/// called in the middle of the feature trigger cycle
		virtual void OnFrame();

	public:

		bool InitSoundSystem();

		void AttachSoundListener(SoundListener* listener);
		void DetachSoundListener(SoundListener* listener);

		void AttachSoundSource(SoundSource* source);
		void DetachSoundSource(SoundSource* source);

		SoundListener* GetSoundListener();

		Sound::SoundBuffer* CreateSoundBuffer(const char* nameOrData, SizeT dataSize,
			GENESISOUND_MODE mode,
			GENESIS_FILE_FORMAT fileFormat);
		Sound::SoundSystemSource* GetFreeSoundSystemSource(Sound::SoundBuffer* soungBuffer, bool paused = true);
		Sound::SoundSystem*	GetSoundSystem() const { return mSoundSystem; }


		float CalcInvFrameTime (const float dt);


		void UpdateListenerAttrs(const Math::vector& pos, 
			const Math::vector& v, 
			const Math::vector& up,
			const Math::vector& forward);

		float GetVolume(void) const;
		void SetVolume(const float volume);

		bool GetEnableAutoPlay() const { return mEnableAutoPlay; }
		void SetEnableAutoPlay(const bool b) { mEnableAutoPlay = b; }

	private:
		float								mVolume;
		bool								mEnableAutoPlay;

		Util::List< GPtr<SoundSource> >		mSources;
		Util::List< GPtr<SoundListener> >	mListeners;

		GPtr<Sound::SoundSystem>			mSoundSystem;
	};
}
#endif // __SOUND_COMMIT__



#endif //__SoundFeature_H__