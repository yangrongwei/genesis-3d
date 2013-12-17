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
#ifndef __SoundSourceComponent_H__
#define __SoundSourceComponent_H__
#ifndef __SOUND_COMMIT__

#include "appframework/component.h"
#include "soundfeature/SoundFeature.h"
#include "addons/resource/audiores.h"

namespace App
{

	class SoundRes;

	struct SoundScheduledSource;

	class SoundSource : public Component
	{
		__DeclareSubClass(SoundSource, Component);
	public:
		SoundSource();
		virtual ~SoundSource();

		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		///// @Component::_OnBeginFrame called after movement has happened. 
		virtual void _OnBeginFrame();

		/// called from Actor::ActivateComponents()
		virtual void OnActivate();
		/// called from Actor::DeactivateComponents()
		virtual void OnDeactivate();
		/// resource needed
		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		void SetupAcceptedMessages();
		void HandleMessage(const GPtr<Messaging::Message>& msg);
		/// for script
	public:
		void Play(void);
		void Stop(void);
		void Pause(void);

		bool IsPlaying(void) const;
		bool IsPaused(void) const;

		bool GetLoop (void) const;
		void SetLoop (const bool loop);

		float GetVolume(void) const;
		void  SetVolume(const float volume);

		bool GetMute(void) const;
		void SetMute(const bool mute);

		// set sound res
		bool Init(const Util::String &name, const bool &is3D = false);
		bool Is3D(void) const;
		bool Set3D(const bool &is3D);

		const Util::String& GetName(void) const;
		bool SetName(const Util::String &name, Resources::Priority priority = Resources::ResourcePriority::SoundDefault);

		uint GetLength(void) const;

		float GetPitch(void) const;
		void  SetPitch(const float pitch);

		float GetSpread(void) const;
		void SetSpread(float spread);

		float GetPan() const;
		void SetPan(float pan);

		float GetMinDistance() const;
		void SetMinDistance(float minDistance);

		float GetMaxDistance() const;
		void SetMaxDistance(float maxDistance);

		RolloffMode GetRolloffMode() const;
		void SetRolloffMode(RolloffMode mode);

		int GetDecompressFlag(void) const;
		void SetDecompressFlag(const int flag);

		uint GetPosition (void)const;
		void SetPosition(uint position);

		float GetDopplerLevel(void) const;
		void SetDopplerLevel (float level);

		int GetPriority() const;
		void SetPriority(int priority);

		bool IsSteamed() const;
		void SetSteamed(bool b);

		bool IsDecompress() const;
		void SetDecompress(bool b);

		bool IsCompressed() const;
		void SetCompressed(bool b);

		bool IsStatistics() const;
		void SetStatistics(bool b);

		void SetSoundDirty(bool bDirty);
	public:

		void AssignInfo(void);

		void UpdateSoundInfo ();

		//void SetSoundRes(const GPtr<SoundRes> &res);
		SoundRes* GetSoundRes() const {return mSoundRes; }

		Sound::SoundSystemSource* GetSoundSystemSource() const {return mSoundSystemSource; }

		GPtr<Resources::AudioRes> GetAudioRes()const {return mAudioRes;}


		// to control function
		void SetDirty(void);
		void ClearDirty(void);
		void SetDirtyIndex(const int dirtyValue);
		bool IsDirty() const { return mDirtyIndex != 0; }	
		int GetDirtyIndex() { return mDirtyIndex; }

		bool GetPlayOnActive() const { return mPlayOnActive; }
		void SetPlayOnActive(const bool playOnActive);

		void AttachFilters();


		//	Serialization
	public:	
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );
	protected:
		virtual void OnDestroy();

	private:

		Sound::SoundSystemSource*		mSoundSystemSource;

		GPtr<SoundRes>					mSoundRes;
		GPtr<Resources::AudioRes>		mAudioRes;

		bool							mPlayOnActive;
		int								mDirtyIndex;

		bool							mIsSoundDirty;
		bool							mStreamed;
		bool							mCompressed;
		bool							mDecompress;
		bool							mStatistics;

		SoundSouceInfo					mSoundInfo;
		Math::vector					mLatestPos;

		/** 
		* backward compatibility props
		**/
		bool							mIsSetPlay;

	};

}

#endif // __SOUND_COMMIT__



#endif //__SoundSourceComponent_H__

