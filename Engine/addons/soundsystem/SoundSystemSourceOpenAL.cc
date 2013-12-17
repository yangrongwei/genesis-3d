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
#include "stdneb.h"
#include "SoundSystemSourceOpenAL.h"
#include "OpenAL/al.h"
#include "SoundSystem.h"
#include "SoundSystemOpenAL.h"
#include "soundsystem/Framework.h"

namespace Sound
{
	__ImplementClass(Sound::SoundSystemSourceOpenAL, 'SSOA', Sound::SoundSystemSource);

	SoundSystemSourceOpenAL::SoundSystemSourceOpenAL()
		: mSource(NULL)
		, mIs3D(true)
		, mSoundBuffer(NULL)
		, mStopByPlayOver(false)
		, mIsLoop(false)
		, m_bDecode(true)
	{}
	//------------------------------------------------------------------------
	SoundSystemSourceOpenAL::~SoundSystemSourceOpenAL() {}
	//------------------------------------------------------------------------------
	void SoundSystemSourceOpenAL::SetSource(void *source)
	{
		ALuint *alsource = static_cast< ALuint* >(source);
		mSource = *alsource; 
		return; 
	}
	//------------------------------------------------------------------------------
	bool SoundSystemSourceOpenAL::InternalReleaseSource()
	{
		alSource3i(mSource, AL_AUXILIARY_SEND_FILTER, AL_EFFECTSLOT_NULL, 0, AL_FILTER_NULL);
		alSourceStop(mSource);
		alSourcei(mSource, AL_BUFFER, 0);
		alDeleteSources(1, &mSource);
		mSource = NULL;

		if (alGetError() == AL_NO_ERROR)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//------------------------------------------------------------------------------
	bool SoundSystemSourceOpenAL::SetPaused(bool paused)
	{
		if (paused)
		{
			alSourcePause(mSource);
		} 
		else
		{
			alSourcePlay(mSource);

			GENESISOUND_MODE mode = mSoundBuffer->GetBufferMode();
			if (mode & GENESISSOUND_CREATESTREAM)
			{
				mStopByPlayOver = false;
			}
		}

		return true;
	}
	//------------------------------------------------------------------------------
	bool SoundSystemSourceOpenAL::GetPaused(bool *paused)
	{
		ALint iState;

		alGetSourcei( mSource, AL_SOURCE_STATE, &iState);

		if ( iState == AL_PAUSED )
		{
			*paused = true;
		} 
		else
		{
			*paused = false;
		}

		return true;
	}
	//------------------------------------------------------------------------------
	bool SoundSystemSourceOpenAL::IsPlaying(bool *isPlaying)
	{
		ALint iState;

		alGetSourcei( mSource, AL_SOURCE_STATE, &iState);

		if ( iState == AL_PLAYING )
		{
			*isPlaying = true;
		} 
		else
		{
			*isPlaying = false;
		}

		return true;
	}
	//------------------------------------------------------------------------------
	bool SoundSystemSourceOpenAL::SetVolume(float volume)
	{
		alSourcef(mSource, AL_GAIN, volume);

		return true;
	}
	//------------------------------------------------------------------------------
	bool SoundSystemSourceOpenAL::Stop()
	{
		alSourceStop(mSource);

		GENESIS_FILE_FORMAT fileFormat = mSoundBuffer->GetFileFormat();
		if ( fileFormat & GENESIS_FILE_FORMAT_MP3 )
		{
			//Set decoder pointer to file head for next playing.
			mpg123_handle *mpg123 = mSoundBuffer->GetMpg123Handle();
			mpg123_seek(mpg123, 0, 0);
		}
		else if( fileFormat & GENESIS_FILE_FORMAT_OGG )
		{
			//Set decoder pointer to file head for next playing.
			OggVorbis_File* oggHandle = mSoundBuffer->GetOggHandle();
			ov_raw_seek(oggHandle,0);
		}
		
		SoundSystem::Instance()->ReleaseSingleSource(this);

		return true;
	}
	//------------------------------------------------------------------------------
	float SoundSystemSourceOpenAL::GetPitch(void) const
	{
		float pitch = -1.f;
		alGetSourcef(mSource, AL_PITCH, &pitch);
		return pitch;
	}
	//------------------------------------------------------------------------------
	void SoundSystemSourceOpenAL::SetPitch(float pitch)
	{
		alSourcef(mSource, AL_PITCH, pitch);
	}
	//------------------------------------------------------------------------
	bool SoundSystemSourceOpenAL::GetLoop (void) const
	{
		return mIsLoop;
	}
	//------------------------------------------------------------------------
	void SoundSystemSourceOpenAL::SetLoop (bool loop)
	{
		mIsLoop = loop;

		GENESISOUND_MODE mode = mSoundBuffer->GetBufferMode();
		if ( (mode & GENESISSOUND_CREATESTREAM) == false )
			alSourcei(mSource, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	}
	//------------------------------------------------------------------------
	bool SoundSystemSourceOpenAL::SetMode (GENESISOUND_MODE mode)
	{
		if ( mode & GENESISSOUND_3D_WORLDRELATIVE )
		{
			mIs3D = true;
			alSourcei(mSource,AL_SOURCE_RELATIVE,AL_FALSE);    
			if (alGetError() != AL_NO_ERROR)
			{
				return false;
			}
		}
		else if (mode & GENESISSOUND_3D_HEADRELATIVE)
		{
			mIs3D = false;
			alSourcei(mSource,AL_SOURCE_RELATIVE,AL_TRUE);
			if (alGetError() != AL_NO_ERROR)
			{
				return false;
			}
		}

		if (mode & GENESISSOUND_3D_INVERSEROLLOFF)
		{
			alSourcef(mSource, AL_ROLLOFF_FACTOR, 1.0);
			if (alGetError() != AL_NO_ERROR)
			{
				return false;
			}
			alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
			if (alGetError() != AL_NO_ERROR)
			{
				return false;
			}
		}
		else if (mode & GENESISSOUND_3D_LINEARROLLOFF)
		{
			alSourcef(mSource, AL_ROLLOFF_FACTOR, 1.0);
			if (alGetError() != AL_NO_ERROR)
			{
				return false;
			}
			alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
			if (alGetError() != AL_NO_ERROR)
			{
				return false;
			}
		}
		else if (mode & GENESISSOUND_3D_LINEARSQUAREROLLOFF)
		{
			alSourcef(mSource, AL_ROLLOFF_FACTOR, 2.0);
			if (alGetError() != AL_NO_ERROR)
			{
				return false;
			}
			alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
			if (alGetError() != AL_NO_ERROR)
			{
				return false;
			}
		}

		return true;
	}
	//------------------------------------------------------------------------
	void SoundSystemSourceOpenAL::SetMaxDistance(float maxdis)
	{
		alSourcef(mSource,AL_MAX_DISTANCE,maxdis);
	}
	//------------------------------------------------------------------------
	void SoundSystemSourceOpenAL::SetMinDistance(float mindis)
	{
		alSourcef(mSource,AL_REFERENCE_DISTANCE,mindis);
	}
	//------------------------------------------------------------------------------
	bool SoundSystemSourceOpenAL::Set3DMinMaxDistance(float  mindistance, 
													  float  maxdistance)
	{
		alSourcef(mSource,AL_REFERENCE_DISTANCE, mindistance);
		if (alGetError() != AL_NO_ERROR)
		{
			return false;
		}

		alSourcef(mSource,AL_MAX_DISTANCE, maxdistance);
		if (alGetError() != AL_NO_ERROR)
		{
			return false;
		}

		return true;
	}
	//------------------------------------------------------------------------
	void SoundSystemSourceOpenAL::SetDistanceMode(DistanMode mode)
	{
		switch(mode)
		{
		case EXPONENT_DISTANCE :
			{
				alDistanceModel(AL_EXPONENT_DISTANCE_CLAMPED);
				break;
			}
		case LINEAR_MODE :
			{
				alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
				break;
			}
		}
	}
	//------------------------------------------------------------------------
	void SoundSystemSourceOpenAL::SetSoundInfo(Math::vector p, Math::vector v, Math::vector sourceForward, Math::vector sourceUp)
	{
		ALfloat pos[] = {p.x(), p.y(), p.z()};
		ALfloat vel[] = {v.x(), v.y(), v.z()};
		ALfloat dir[] = {sourceForward.x(), sourceForward.y(), sourceForward.z(), sourceUp.x(), sourceUp.y(), sourceUp.z()};
		if (!mIs3D)
		{
			pos[0] = 0.f;
			pos[1] = 0.f;
			pos[2] = 0.f;
			vel[0] = 0.f;
			vel[1] = 0.f;
			vel[2] = 0.f;
		}
		alSourcefv(mSource, AL_POSITION, pos);
		alSourcefv(mSource, AL_VELOCITY, vel);
		alSourcefv(mSource, AL_DIRECTION, dir);
	}
	//------------------------------------------------------------------------------
	bool SoundSystemSourceOpenAL::SetModeAtts(Math::vector &position, 
		Math::vector &velocity,
		Math::vector &orientation)
	{
		ALfloat pos[] = {position.x(), position.y(), position.z() };
		ALfloat vel[] = {velocity.x(), velocity.y(), velocity.z() };
		Math::matrix44 rotation = Math::matrix44::rotationyawpitchroll(
															orientation.x(),
															orientation.y(),
															orientation.z());
		Math::float3 forward = Math::float3::normalize(Math::float3(
													rotation.get_zaxis().x(), 
													rotation.get_zaxis().y(), 
													rotation.get_zaxis().z() ) );
		Math::float3 up = Math::float3::normalize(Math::float3(
													rotation.get_yaxis().x(), 
													rotation.get_yaxis().y(), 
													rotation.get_yaxis().z() ) );
		ALfloat dir[] = {forward.x(), forward.y(), forward.z(), up.x(), up.y(), up.z() };

		if (!mIs3D)
		{
			pos[0] = 0.f;
			pos[1] = 0.f;
			pos[2] = 0.f;
			vel[0] = 0.f;
			vel[1] = 0.f;
			vel[2] = 0.f;
		}

		alSourcefv(mSource, AL_POSITION, pos);
		if (alGetError() != AL_NO_ERROR)
		{
			return false;
		}

		alSourcefv(mSource, AL_VELOCITY, vel);
		if (alGetError() != AL_NO_ERROR)
		{
			return false;
		}

		alSourcefv(mSource, AL_DIRECTION, dir);

		return true;
	}
	//------------------------------------------------------------------------------
	void SoundSystemSourceOpenAL::Decode(GENESIS_FILE_FORMAT fileFormat)
	{
		if (mStopByPlayOver || !m_bDecode)
		{
			return;
		}

		bool bPaused = false;
		GetPaused(&bPaused);
		if ( bPaused)
		{
			return;
		}

		int iBuffersProcessed = NULL;
		ALuint uiBuffer = NULL;
		int iState = NULL;
		int iQueuedBuffers = NULL;

		alGetSourcei(mSource, AL_BUFFERS_PROCESSED, &iBuffersProcessed);

		size_t ulBytesWritten = NULL;
		mpg123_handle *mpg123 = mSoundBuffer->GetMpg123Handle();
		OggVorbis_File* oggHandle = mSoundBuffer->GetOggHandle();
		unsigned char *pDecodeBuffer = mSoundBuffer->GetDecodeBuffer();
		unsigned long ulBufferSize = mSoundBuffer->GetDecodeBufferSize();
		ALuint ulFormat = mSoundBuffer->GetBufferFormat();
		unsigned long ulFrequency = mSoundBuffer->GetBufferFrequency();
		unsigned long ulChannels = mSoundBuffer->GetBufferChannelCount();
		
		while(iBuffersProcessed)
		{
			uiBuffer = 0;
			// Remove the Buffer from the Queue.  (uiBuffer contains the Buffer ID for the unqueued Buffer)
			alSourceUnqueueBuffers(mSource, 1, &uiBuffer);
			
			if ( fileFormat & GENESIS_FILE_FORMAT_MP3 )
			{
				// mp3 Read more audio data (if there is any)
				mpg123_read(mpg123, pDecodeBuffer, ulBufferSize, &ulBytesWritten);
			}
			else if( fileFormat & GENESIS_FILE_FORMAT_OGG )
			{
				// ogg Read more audio data (if there is any)
				ulBytesWritten = DecodeOggVorbis(oggHandle, (char*)pDecodeBuffer, ulBufferSize, ulChannels);
			}

			if(ulBytesWritten)
			{
				alBufferData(uiBuffer, ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
				alSourceQueueBuffers(mSource, 1, &uiBuffer);
			}
			else if( GetLoop() )
			{
				if ( fileFormat & GENESIS_FILE_FORMAT_MP3 )
				{
					// for mp3
					mpg123_seek(mpg123, 0, 0);
					mpg123_read(mpg123, pDecodeBuffer, ulBufferSize, &ulBytesWritten);
					if(ulBytesWritten)
					{
						alBufferData(uiBuffer, ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
						alSourceQueueBuffers(mSource, 1, &uiBuffer);
					}
				}
				else if(fileFormat & GENESIS_FILE_FORMAT_OGG )
				{
					// for ogg
					ov_raw_seek(oggHandle, 0);
					ulBytesWritten = DecodeOggVorbis( oggHandle, (char*)pDecodeBuffer, ulBufferSize, ulChannels);
					if(ulBytesWritten)
					{
						alBufferData(uiBuffer, ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
						alSourceQueueBuffers(mSource, 1, &uiBuffer);
					}
				}
			}
			iBuffersProcessed--;

		}
		alGetSourcei(mSource, AL_SOURCE_STATE, &iState);
		if(iState != AL_PLAYING)
		{
			alGetSourcei(mSource, AL_BUFFERS_QUEUED, &iQueuedBuffers);

			if(iQueuedBuffers)
			{
				alSourcePlay(mSource);//buffers have data, play it
			}
			else
			{
				if ( fileFormat & GENESIS_FILE_FORMAT_MP3 )
				{
					// mp3
					mpg123_seek(mpg123, 0, 0);
					ALuint * queueBuffers = mSoundBuffer->GetQueueBuffers();
					for(int iLoop = 0; iLoop < NUM_BUFFERS; iLoop++)
					{
						mpg123_read(mpg123, pDecodeBuffer, ulBufferSize,&ulBytesWritten);
						alBufferData(queueBuffers[iLoop], ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
						alSourceQueueBuffers(mSource, 1, &queueBuffers[iLoop]);
					}
				}
				else if( fileFormat & GENESIS_FILE_FORMAT_OGG )
				{
					// ogg
					ov_raw_seek(oggHandle, 0);
					ALuint * queueBuffers = mSoundBuffer->GetQueueBuffers();
					// Fill all the Buffers with decoded audio data from the OggVorbis file
					for (int iLoop = 0; iLoop < NUM_BUFFERS; iLoop++)
					{
						ulBytesWritten = DecodeOggVorbis(oggHandle, (char*)pDecodeBuffer, ulBufferSize, ulChannels);
						if (ulBytesWritten)
						{
							alBufferData(queueBuffers[iLoop], ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
							alSourceQueueBuffers(mSource, 1, &queueBuffers[iLoop]);
						}
					}
				}

				mStopByPlayOver = true;
			}
		}
	}
	//------------------------------------------------------------------------------
	void SoundSystemSourceOpenAL::addDSP( GPtr<SoundSystemDSP> dsp )
	{
		m_SoundDSPContainer.Append(dsp);
	}
	//------------------------------------------------------------------------------
	unsigned long SoundSystemSourceOpenAL::DecodeOggVorbis( OggVorbis_File *psOggVorbisFile, char *pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels )
	{
		int current_section;
		long lDecodeSize;
		unsigned long ulSamples;
		short *pSamples;

		unsigned long ulBytesDone = 0;
		while (1)
		{
			lDecodeSize = ov_read(psOggVorbisFile, pDecodeBuffer + ulBytesDone, ulBufferSize - ulBytesDone, 0, 2, 1, &current_section);
			if (lDecodeSize > 0)
			{
				ulBytesDone += lDecodeSize;

				if (ulBytesDone >= ulBufferSize)
					break;
			}
			else
			{
				break;
			}
		}

		// Mono, Stereo and 4-Channel files decode into the same channel order as WAVEFORMATEXTENSIBLE,
		// however 6-Channels files need to be re-ordered
		if (ulChannels == 6)
		{		
			pSamples = (short*)pDecodeBuffer;
			for (ulSamples = 0; ulSamples < (ulBufferSize>>1); ulSamples+=6)
			{
				// WAVEFORMATEXTENSIBLE Order : FL, FR, FC, LFE, RL, RR
				// OggVorbis Order            : FL, FC, FR,  RL, RR, LFE
				Swap(pSamples[ulSamples+1], pSamples[ulSamples+2]);
				Swap(pSamples[ulSamples+3], pSamples[ulSamples+5]);
				Swap(pSamples[ulSamples+4], pSamples[ulSamples+5]);
			}
		}

		return ulBytesDone;
	}
	//------------------------------------------------------------------------------
	void SoundSystemSourceOpenAL::Swap( short &s1, short &s2 )
	{
		short sTemp = s1;
		s1 = s2;
		s2 = sTemp;
	}

}