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
#include "appframework/actor.h"
#include "io/assignregistry.h"
#include "math/scalar.h"
#include "basegamefeature/managers/timesource.h"
#include "addons/resource/resourcemanager.h"

#include "SoundSourceComponent.h"
#include "soundfeature/components/SoundFilterComponent.h"
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "addons/soundsystem/SoundBufferOpenAL.h"

namespace App
{

	__ImplementClass(SoundSource, 'SSCP', Component);

	using namespace Math;
	using namespace Graphic;
	//------------------------------------------------------------------------------
	SoundSource::SoundSource()
		: mStreamed(false)
		, mCompressed(true)
		, mSoundSystemSource(NULL)
		, mSoundRes(NULL)
		, mDecompress(false)
		, mStatistics(false)
		, mIsSetPlay(false)
		, mDirtyIndex(0)
		, mPlayOnActive(false)
		, mIsSoundDirty(false)
	{
		mSoundInfo.DopplerLevel = 1.0f;
		mSoundInfo.rolloffMode = ROLLOFF_INVERSE;
		mSoundInfo.priority = 128;
		mSoundInfo.position = 0;
		mSoundInfo.pan = 0.0f;
		mSoundInfo.pitch = 1.0f;
		mSoundInfo.spread = 0.0f;
		mSoundInfo.minDistance = 1.0f;
		mSoundInfo.maxDistance = 5.0f;
		mSoundInfo.loop = false;
		mSoundInfo.mute = false;
		mSoundInfo.volume = 1.0f;


		mSoundRes = SoundRes::Create();
		n_assert(mSoundRes);

	}

	//------------------------------------------------------------------------------
	SoundSource::~SoundSource()
	{
	}
	//------------------------------------------------------------------------------
	void SoundSource::SetupCallbacks()
	{
		mActor->RegisterComponentCallback(this, BeginFrame);
		return;
	}

	////------------------------------------------------------------------------------
	void SoundSource::_OnBeginFrame()
	{
		if (mIsSoundDirty)
		{
			n_assert(mSoundRes);

			if (mSoundRes->GetName() == "")
			{
				mIsSoundDirty = false;
				return;
			}

			if ( !mAudioRes.isvalid() )
			{	
				const Util::String resID = mSoundRes->GetName();
				GPtr<Resources::AudioResInfo> pAudioInfo = Resources::ResourceManager::Instance()->CreateAudioResInfo(resID, mSoundRes->GetPriority());
				if (pAudioInfo.isvalid() && pAudioInfo->GetRes().isvalid())
				{
					mAudioRes = pAudioInfo->GetRes().downcast<Resources::AudioRes>();
				}
				else
				{
					mAudioRes = NULL;
				}
			}
			else
			{
				/*The state of the resource is 'Failed' only if the user delete 
				the default audio resource.But this behavior is rare.So the 
				resource can only have two states('UnLoaded' and 'Loaded') when 
				the code is executed here.If the state of the resource is 'UnLoaded'
				,it means that the resource is loaded asynchronously and the loading
				request haven't been processed*/
				const Util::String resID = mSoundRes->GetName();
				GPtr<Resources::AudioResInfo> pAudioInfo = Resources::ResourceManager::Instance()->CreateAudioResInfo(resID, mSoundRes->GetPriority());
				if (pAudioInfo.isvalid() && pAudioInfo->GetRes().isvalid())
				{
					mAudioRes = pAudioInfo->GetRes().downcast<Resources::AudioRes>();
				}
				else
				{
					mAudioRes = NULL;
				}

				if (mAudioRes->GetState() == Resources::Resource::Loaded)
				{
					mIsSoundDirty = false;

					if( !mSoundRes->IsSoundValiad())
					{
						GENESISOUND_MODE mode = NULL;
						GENESIS_FILE_FORMAT fileFormat = NULL;
						/*If the audio file doesn't find in target path, the resource manager
						will use the default audio file(a empty wave file).In this case the 
						file name in the 'mAudioRes' is different from the file name in the
						'm_SoundRes'.But the address of the memory transmit to low level 
						sound system is the address of the default audio file.So we should
						use the file name in the 'mAudioRes' for file format determination.*/ 
						Util::String fileExtension =  mAudioRes->GetResourceId().AsString().GetFileExtension();
						fileExtension.ToLower();
						if ( "mp3" == fileExtension  )
						{
							fileFormat = fileFormat | GENESIS_FILE_FORMAT_MP3;
							mode = mode | GENESISSOUND_CREATESTREAM;
						}
						else if( "ogg" == fileExtension )
						{
							fileFormat = fileFormat | GENESIS_FILE_FORMAT_OGG;
							mode = mode | GENESISSOUND_CREATESTREAM;
						}
						else if ( "wav" == fileExtension)
						{
							fileFormat = fileFormat | GENESIS_FILE_FORMAT_WAV;
							mode = mode | GENESISSOUND_CREATESAMPLE;
						}

						mode = mode | GENESISSOUND_OPENMEMORY;

						/*Because switching the mode between 2D and 3D isn't supported
						when use hardware mix on win32 platform,so all the sound is
						created as 3D mode and simulate the switch between 2D and 3D
						by set the mode to GENESISSOUND_3D_HEADRELATIVE or 
						GENESISSOUND_3D_WORLDRELATIVE.*/
						mode = mode | GENESISSOUND_3D;

						if ( mode & GENESISSOUND_OPENMEMORY )
						{
							mSoundRes->CreateSoundBuffer(mAudioRes->GetPtr(), 
								mAudioRes->Size(), mode, fileFormat);
						}
						else
						{
							mSoundRes->CreateSoundBuffer(GetName().AsCharPtr(), 
								mAudioRes->Size(), mode,fileFormat);
						}
						if ( mIsSetPlay )
						{
							Play();
							mIsSetPlay = false;
						}
					}
				}
			}
		}
		else
		{
			if (mSoundSystemSource == NULL)
			{
				return;
			}

			Sound::SoundBuffer* soundBuffer = mSoundSystemSource->GetSoundBuffer();
			GENESISOUND_MODE mode = soundBuffer->GetBufferMode();
			if( mode & GENESISSOUND_CREATESTREAM)
			{
				GENESIS_FILE_FORMAT fileFormat = soundBuffer->GetFileFormat();
				mSoundSystemSource->Decode(fileFormat);
			}
		}
	}
	//------------------------------------------------------------------------------
	void SoundSource::OnActivate()
	{
		Super::OnActivate();

		bool b = SoundFeature::Instance()->GetEnableAutoPlay();
		if ( GetPlayOnActive() && b == true )
		{
			Play();
		}

		return;
	}

	//------------------------------------------------------------------------------
	void SoundSource::OnDeactivate()
	{
		Super::OnDeactivate();

		Stop();

		return;
	}
	//------------------------------------------------------------------------------
	void SoundSource::SetupAcceptedMessages()
	{
		Super::SetupAcceptedMessages();
	}
	//------------------------------------------------------------------------------
	void SoundSource::HandleMessage(const GPtr<Messaging::Message>& msg)
	{

	}
	//------------------------------------------------------------------------------
	void SoundSource::AssignInfo(void)
	{
		SetPriority(mSoundInfo.priority);
		SetRolloffMode(mSoundInfo.rolloffMode);
		Set3D(Is3D());
		SetVolume(mSoundInfo.volume);
		SetLoop(mSoundInfo.loop);
		SetDopplerLevel(mSoundInfo.DopplerLevel);
		SetMute(mSoundInfo.mute);
		SetPitch(mSoundInfo.pitch);
		SetPan(mSoundInfo.pan);
		SetMaxDistance(mSoundInfo.maxDistance);
		SetMinDistance(mSoundInfo.minDistance);
		SetSpread(mSoundInfo.spread);
		return;
	}

	//------------------------------------------------------------------------------
	void SoundSource::Play(void)
	{
		if (!mActive)
		{
			return;
		}

		if (mIsSoundDirty)
		{
			mIsSetPlay = true;
			return;
		}

		// there are two conditions mIsSoundDirty can be false
		// 1.audio res file has been loaded
		// 2.audio res file name is ""
		// so we need to judge is the second condition or not before playing
		n_assert(mSoundRes);
		if (mSoundRes->GetName() == "")
		{
			return;
		}

		// when the sound res is loadded, sound Res may change, so we should judge the fmod sound
		// before playing
		if ( !mSoundRes->IsSoundValiad() )
		{
			return;
		}

		if ( !mSoundSystemSource )
		{
			mSoundSystemSource = mSoundRes->CreateSoundSystemSource();
			if (mSoundSystemSource)
			{
				AttachFilters();
				AssignInfo();
				mSoundSystemSource->SetPaused(false);
				n_assert( SoundFeature::Instance() );
				SoundFeature::Instance()->AttachSoundSource(this);
			}
		}
		else
		{
			// when the mSoundSystemSource is not null, it means that we have execute playSound func
			// so the sound component can only be two state, one is playing , the other is pause
			if ( IsPlaying() )
			{
				return;
			}
			else
			{
				mSoundSystemSource->SetPaused(false);
			}
		}

		return;
	}

	//------------------------------------------------------------------------------
	void SoundSource::Stop(void)
	{
		n_assert(SoundFeature::HasInstance());

		if (mSoundSystemSource)
		{
			mSoundSystemSource->Stop();
		}

		mSoundSystemSource = NULL;
		mSoundRes->SetSoundSystemSource(NULL);

		SoundFeature::Instance()->DetachSoundSource(this);

		mIsSetPlay = false;

		return;
	}

	//------------------------------------------------------------------------------
	void SoundSource::Pause(void)
	{
		if (mSoundSystemSource)
		{
			mSoundSystemSource->SetPaused(true);
		}
	}

	//------------------------------------------------------------------------------
	void SoundSource::SetDirty()
	{
		mDirtyIndex++;
		if (mDirtyIndex == 0)
		{
			mDirtyIndex = 1;
		}

		return;
	}

	//------------------------------------------------------------------------------
	void SoundSource::ClearDirty()
	{
		mDirtyIndex = 0;
		return;
	}

	//------------------------------------------------------------------------------
	void SoundSource::SetDirtyIndex(const int dirtyValue)
	{
		mDirtyIndex = dirtyValue;
		return;
	}

	//------------------------------------------------------------------------------
	float SoundSource::GetVolume() const
	{
		return mSoundInfo.volume;
	}

	//------------------------------------------------------------------------------
	void SoundSource::SetVolume(const float volume)
	{
		mSoundInfo.volume = Math::n_clamp(volume, 0.0f, 1.0f);
		if (mSoundSystemSource)
		{
			mSoundSystemSource->SetVolume(mSoundInfo.volume);
		}
	}

	//------------------------------------------------------------------------------
	void SoundSource::SetPlayOnActive(const bool playOnActive)
	{
		mPlayOnActive = playOnActive;
		return;
	}

	//------------------------------------------------------------------------------
	bool SoundSource::GetMute() const
	{
		return mSoundInfo.mute;
	}

	//------------------------------------------------------------------------------
	void SoundSource::SetMute(const bool mute)
	{
		mSoundInfo.mute = mute;
		return;
	}

	//------------------------------------------------------------------------------
	bool SoundSource::GetLoop(void) const
	{
		return mSoundInfo.loop;
	}

	//------------------------------------------------------------------------------
	void SoundSource::SetLoop(const bool loop)
	{
		mSoundInfo.loop = loop;
		if (mSoundSystemSource)
		{
			mSoundSystemSource->SetLoop( loop );
		}
		return;
	}

	//------------------------------------------------------------------------------
	void SoundSource::UpdateSoundInfo()
	{
		if (!mSoundSystemSource)
		{
			return;
		}

		bool isPaused = false;
		mSoundSystemSource->GetPaused(&isPaused);
		if (isPaused)
		{
			return;
		}

		Math::vector pos(0, 0, 0);
		Math::vector vel(0, 0, 0);
		Math::vector ori(0, 0, 0);

		n_assert(mSoundRes);
		if (mSoundRes->Is3D())
		{
			pos = mActor->GetWorldPosition();

			double dFrameTime = GameTime::Instance()->GetFrameTime();
			float frameTime = static_cast<float>(dFrameTime);
			float inverseFrameTime = SoundFeature::Instance()->
				CalcInvFrameTime(frameTime);
			vel = (pos - mLatestPos) * inverseFrameTime;

			Math::scalar yaw, pitch, roll;
			const Math::quaternion &rot = mActor->GetWorldRotation();
			Math::quaternion::getyawpitchroll(rot, yaw, pitch, roll);
			Math::float3 orient(yaw, pitch, roll);
			orient = Math::float3::normalize(orient);
			ori.x() = orient.x();
			ori.y() = orient.x();
			ori.z() = orient.x();

			mLatestPos = pos;
		}

		mSoundSystemSource->SetModeAtts(pos, vel, ori);
	}
	//------------------------------------------------------------------------------
	bool SoundSource::IsPlaying(void) const
	{
		if (mSoundSystemSource)
		{
			bool result;
			bool isPlaying = false;
			bool isPaused = false;

			result = mSoundSystemSource->IsPlaying(&isPlaying);
			result = mSoundSystemSource->GetPaused(&isPaused);

			return result && ((isPlaying) && (!isPaused));
		}
		return false;
	}

	//------------------------------------------------------------------------------
	bool SoundSource::IsPaused(void) const
	{
		if (mSoundSystemSource)
		{
			bool result;
			bool isPaused = false;

			result = mSoundSystemSource->GetPaused(&isPaused);
			return ( result == true ) && isPaused;
		}
		return false;
	}

	//------------------------------------------------------------------------------
	bool SoundSource::Init(const Util::String &name, const bool &is3D)
	{
		bool bIsSetName = SetName(name);
		bool bIsSet3D = Set3D(is3D);
		return (bIsSetName && bIsSet3D);
	}

	//------------------------------------------------------------------------------
	bool SoundSource::Is3D(void) const
	{
		n_assert(mSoundRes);
		return mSoundRes->Is3D();
	}

	//------------------------------------------------------------------------------
	bool SoundSource::Set3D(const bool &is3D)
	{
		n_assert(mSoundRes);

		return mSoundRes->Set3D(is3D);
	}

	//------------------------------------------------------------------------------
	const Util::String& SoundSource::GetName(void) const
	{
		n_assert(mSoundRes);
		return mSoundRes->GetName();
	}

	//------------------------------------------------------------------------------
	/**
	set the sound name, discard origin sound and set the sound to be dirty
	at next frame in the soundsource's _OnBeginFrame function create new sound
	*/
	bool SoundSource::SetName(const Util::String &name, Resources::Priority priority )
	{
		n_assert(mSoundRes);

		Util::String previousName = GetName();
		if (  previousName == name )
			return true;

		if ( name.IsEmpty())
			SetSoundDirty(false);	// when editor or script delete or stop sound , the name would be empty,mIsSoundDirty state should be false
		else
			SetSoundDirty(true);	// when chanding the sound name , the name is not empty , mIsSoundDirty state should be true

		if (mActor && mActor->PriorityDefinition())
			priority = mActor->GetPriority();

		mSoundRes->SetName(name, priority);	

		return true;
	}

	//------------------------------------------------------------------------------
	uint SoundSource::GetLength(void) const
	{
		if (mSoundRes)
		{
			return mSoundRes->GetLength();
		}

		return 0;
	}

	//------------------------------------------------------------------------------
	float SoundSource::GetPitch(void) const
	{
		return mSoundInfo.pitch;
	}

	//------------------------------------------------------------------------------
	void  SoundSource::SetPitch(const float pitch)
	{
		mSoundInfo.pitch = pitch;
		if (mSoundSystemSource && mSoundRes.isvalid())
		{
			mSoundSystemSource->SetPitch(pitch);
		}
	}
	//------------------------------------------------------------------------------
	int SoundSource::GetPriority() const
	{
		return mSoundInfo.priority;
	}
	//------------------------------------------------------------------------------
	void SoundSource::SetPriority(int priority)
	{
		priority = Math::n_clamp(priority, 0, 256);
		mSoundInfo.priority = priority;

		return;
	}
	//------------------------------------------------------------------------------
	bool SoundSource::IsSteamed() const
	{
		// TODO
		return mStreamed;
	}

	void SoundSource::SetSteamed(bool b)
	{
		mStreamed = b;
	}
	//------------------------------------------------------------------------------
	bool SoundSource::IsDecompress() const
	{
		// TODO
		return mDecompress;
	}

	void SoundSource::SetDecompress(bool b)
	{
		mDecompress = b;
	}
	//------------------------------------------------------------------------------
	bool SoundSource::IsCompressed() const
	{
		// TODO
		return mCompressed;
	}

	void SoundSource::SetCompressed(bool b)
	{
		mCompressed = b;
	}
	//------------------------------------------------------------------------------
	bool SoundSource::IsStatistics() const
	{
		return mStatistics;
	}

	void SoundSource::SetStatistics(bool b)
	{
		mStatistics = b;
	}
	//------------------------------------------------------------------------------
	float SoundSource::GetSpread(void) const
	{
		return mSoundInfo.spread;
	}
	//------------------------------------------------------------------------------
	void SoundSource::SetSpread(float spread)
	{
		spread = Math::n_clamp(spread, 0.0f, 360.0f);
		mSoundInfo.spread = spread;
		return;
	}
	//------------------------------------------------------------------------------
	void SoundSource::SetDopplerLevel(float level)
	{
		level = Math::n_clamp(level, 0.0f, 5.0f);
		mSoundInfo.DopplerLevel = level;
		return;
	}
	//------------------------------------------------------------------------------
	float SoundSource::GetDopplerLevel() const
	{
		return mSoundInfo.DopplerLevel;
	}
	//------------------------------------------------------------------------------
	float SoundSource::GetPan() const
	{
		return mSoundInfo.pan;
	}
	//------------------------------------------------------------------------------
	void SoundSource::SetPan(float pan)
	{
		pan = Math::n_clamp(pan, -1.0f, 1.0f);
		mSoundInfo.pan = pan;

		return;
	}
	//------------------------------------------------------------------------------
	float SoundSource::GetMinDistance() const
	{
		return mSoundInfo.minDistance;
	}
	//------------------------------------------------------------------------------
	void SoundSource::SetMinDistance(float minDistance)
	{
		mSoundInfo.minDistance = minDistance;
		if (mSoundInfo.minDistance < 0.3)
		{
			mSoundInfo.minDistance = 0.3f;
		}
		if (mSoundInfo.maxDistance < (mSoundInfo.minDistance + 0.1f))
		{
			mSoundInfo.maxDistance = mSoundInfo.minDistance + 0.1f;
		}
		if (mSoundSystemSource)
		{
			mSoundSystemSource->Set3DMinMaxDistance(mSoundInfo.minDistance,
				mSoundInfo.maxDistance);
		}

		return;
	}
	//------------------------------------------------------------------------------
	float SoundSource::GetMaxDistance() const
	{
		return mSoundInfo.maxDistance;
	}
	//------------------------------------------------------------------------------
	void SoundSource::SetMaxDistance(float maxDistance)
	{
		mSoundInfo.maxDistance = maxDistance;
		if (mSoundInfo.maxDistance < 0.4)
		{
			mSoundInfo.maxDistance = 0.4f;
		}
		if (mSoundInfo.minDistance > (mSoundInfo.maxDistance - 0.1f))
		{
			mSoundInfo.minDistance = mSoundInfo.maxDistance - 0.1f;
		}

		if (mSoundSystemSource)
		{
			mSoundSystemSource->Set3DMinMaxDistance(mSoundInfo.minDistance,
				mSoundInfo.maxDistance);
		}

		return;
	}
	//------------------------------------------------------------------------------
	RolloffMode SoundSource::GetRolloffMode() const
	{
		return mSoundInfo.rolloffMode;
	}
	//------------------------------------------------------------------------------
	void SoundSource::SetRolloffMode(RolloffMode mode)
	{
		mSoundInfo.rolloffMode = mode;

		if(mSoundSystemSource == NULL)
			return;

		switch (mode)
		{
		case ROLLOFF_INVERSE :
			mSoundSystemSource->SetMode(GENESISSOUND_3D_INVERSEROLLOFF);
			break;
		case ROLLOFF_LINEAR :
			mSoundSystemSource->SetMode(GENESISSOUND_3D_LINEARROLLOFF);
			break;
		case ROLLOFF_LINEARSQUARE :
			mSoundSystemSource->SetMode(GENESISSOUND_3D_LINEARSQUAREROLLOFF);
			break;
		}

	}
	//------------------------------------------------------------------------------
	void SoundSource::SetPosition(uint position)
	{
		mSoundInfo.position = position;
		return;
	}
	//------------------------------------------------------------------------------
	uint SoundSource::GetPosition(void) const
	{
		return mSoundInfo.position;
	}
	//------------------------------------------------------------------------------
	int SoundSource::GetDecompressFlag(void) const
	{
		n_assert(mSoundRes.isvalid());
		return mSoundRes->GetDecompressFlag();
	}
	//------------------------------------------------------------------------------
	void SoundSource::SetDecompressFlag(const int flag)
	{
		n_assert(mSoundRes.isvalid());
		mSoundRes->SetDecompressFlag(flag);
		return;
	}
	//------------------------------------------------------------------------
	void SoundSource::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;
		// TODO:
		GPtr<SoundSource> pSource = pComponent.downcast<SoundSource>();

		mPlayOnActive = pSource->GetPlayOnActive();
		mSoundInfo.loop = pSource->GetLoop();
		mSoundInfo.mute = pSource->GetMute();
		mSoundInfo.volume = pSource->GetVolume();
		mSoundInfo.pitch = pSource->GetPitch();
		mSoundInfo.spread = pSource->GetSpread();
		mSoundInfo.pan = pSource->GetPan();
		mSoundInfo.minDistance = pSource->GetMinDistance();
		mSoundInfo.maxDistance = pSource->GetMaxDistance();
		mSoundInfo.rolloffMode = pSource->GetRolloffMode();

		mSoundRes->CopyFrom(*(pSource->GetSoundRes()));
		// when execute m_SoundRes->CopyFrom(*(pSource->GetSoundRes())); m_Sound would set be null,
		// mSound pointer would get reset when in the _OnBeginFrame() function is called
		// so we need to set the mSoundDirty to be true. So the mSound can be revalued.
		if (mSoundRes->GetName() != "")
		{
			SetSoundDirty(true);
		}
	}
	//--------------------------------------------------------------------------------
	void SoundSource::SetSoundDirty(bool bDirty)
	{
		Stop();

		n_assert(mSoundRes);
		mSoundRes->Discard();

		if ( mAudioRes.isvalid() )
			mAudioRes = NULL;

		mIsSoundDirty = bDirty;

	}
	//------------------------------------------------------------------------------
	void SoundSource::AttachFilters()
	{
		if ( !mSoundSystemSource )
			return;

		const Actor* actor = GetActor();
		Util::Array<GPtr<Component> > FilterArray = actor->FindComponents(SoundFilterComponent::RTTI);

		for (int i=0;i<FilterArray.Size();i++)
		{
			GPtr<SoundFilterComponent> pSoundFilter = FilterArray[i].downcast<SoundFilterComponent>();

			if (pSoundFilter.isvalid())
			{
				GPtr<Sound::SoundSystemDSP> dsp = pSoundFilter->GetDSP();
				if (dsp.isvalid())
				{
					uint dspType = dsp->getType();
					if (AL_FILTER_LOWPASS == dspType)
					{
						dsp->apply(mSoundSystemSource, NULL);
					} 
					else
					{
						int iSendIndex = dsp->GetSendIndex();
						dsp->apply(mSoundSystemSource, iSendIndex);
					}
				}
			}
		}
	}

	//------------------------------------------------------------------------------
	void SoundSource::OnDestroy()
	{
		Stop();
		Super::OnDestroy();
	}
	//------------------------------------------------------------------------------
	void SoundSource::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		list.Append(Resources::ReferenceResource(GetName(), Resources::RR_Unknown));
		Super::GetReferenceResourceId(list);
	}
	//------------------------------------------------------------------------------
}
#endif
