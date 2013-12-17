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
#include "SoundSystemOpenAL.h"
#include "Framework.h"
#include "SoundBufferOpenAL.h"
#include "SoundSystemSourceOpenAL.h"
#include "SoundSystemDSPOpenAL.h"
#include "io/memoryreader.h"
#include "io/assignregistry.h"
#include "Vorbisfile/vorbisfile.h"

namespace Sound
{
	__ImplementClass(Sound::SoundSystemOpenAL, 'SDAL', Sound::SoundSystem);
	//------------------------------------------------------------------------------
	SoundSystemOpenAL::SoundSystemOpenAL() {}
	//------------------------------------------------------------------------------
	SoundSystemOpenAL::~SoundSystemOpenAL() {}
	//------------------------------------------------------------------------------
	bool SoundSystemOpenAL::InitSoundSystem()
	{
#ifndef __OSX__
		alc_init();
#endif
		ALFWInit();

		//initialize mpg123
		int iMpg123_ret = NULL;
		iMpg123_ret = mpg123_init();
		if ( MPG123_OK != iMpg123_ret )
		{
			return false;
		}

		bool ret = ALFWInitOpenAL();
		if (!ret)
		{
			ALFWShutdown();
		}

		return ret;
	}
	//------------------------------------------------------------------------------
	void SoundSystemOpenAL::ReleaseSoundSystem()
	{
		//Must release all allocated resource before sound system shutdown.
		SizeT size = mSoundSourceContainer.Size();
		for (SizeT i = 0; i < size; i++)
		{
			mSoundSourceContainer[i]->InternalReleaseSource();
		}

		mSoundSourceContainer.Clear();

		size = mSoundBufferContainer.Size();
		for (SizeT i = 0; i < size; i++)
		{
			mSoundBufferContainer[i]->InternalReleaseBuffer();
		}

		mSoundBufferContainer.Clear();

		ALFWShutdownOpenAL();
		ALFWShutdown();
#ifndef __OSX__
		alc_deinit();
#endif
	}
	//------------------------------------------------------------------------------
	bool SoundSystemOpenAL::CreateSoundBuffer(const char* nameOrData, SizeT dataSize, 
											  SoundBuffer **soundBuffer, 
											  GENESISOUND_MODE mode,
											  GENESIS_FILE_FORMAT fileFormat)
	{
		GPtr< SoundBufferOpenAL > tempSoundBuffer = SoundBufferOpenAL::Create();
		tempSoundBuffer->SetBufferMode(mode);
		tempSoundBuffer->SetFileFormat(fileFormat);

		bool bOpenMemory = (GENESISSOUND_OPENMEMORY == (mode & GENESISSOUND_OPENMEMORY));
		bool bCreateStream = (GENESISSOUND_CREATESTREAM == (mode & GENESISSOUND_CREATESTREAM));

		SoundBuffer::BufferInfo bufferInfo;
		if (bCreateStream)
		{
			//Create file stream
			GPtr<IO::MemoryReader> pMemoryData = IO::MemoryReader::Create();
			pMemoryData->SetAccessMode( IO::Stream::ReadWriteAccess );
			pMemoryData->Open();
			pMemoryData->Write(nameOrData, dataSize);
			pMemoryData->Seek(0,IO::Stream::Begin);				

			if ( fileFormat & GENESIS_FILE_FORMAT_OGG )
			{
				// Open Ogg Stream
				ov_callbacks	sCallbacks;
				OggVorbis_File	*sOggVorbisFile = new OggVorbis_File();
				vorbis_info		*psVorbisInfo;

				sCallbacks.read_func = ReadOggMemoryStream;
				sCallbacks.seek_func = SeekOggMemoryStream;
				sCallbacks.close_func = CloseOggMemoryStream;
				sCallbacks.tell_func = TellOggMemoryStream;

				if (ov_open_callbacks(pMemoryData.get(), sOggVorbisFile, NULL, NULL, sCallbacks))
				{
					pMemoryData->Close();
					ov_clear(sOggVorbisFile);
					return false;
				}

				psVorbisInfo = ov_info(sOggVorbisFile, -1);
				if ( !psVorbisInfo )
				{
					pMemoryData->Close();
					ov_clear(sOggVorbisFile);
					return false;
				}
					
				bufferInfo.frequency = psVorbisInfo->rate;
				bufferInfo.channels  = psVorbisInfo->channels;
				SetBufferInfo(bufferInfo);

				if ( !bufferInfo.format )
				{
					pMemoryData->Close();
					ov_clear(sOggVorbisFile);
					return false;
				}

				// Allocate a buffer to be used to store decoded data for all Buffers
				unsigned char* pDecodeBuffer = (unsigned char*)malloc(bufferInfo.bufferSize);
				if (!pDecodeBuffer)
				{
					pMemoryData->Close();
					ov_clear(sOggVorbisFile);
					return false;
				}

				tempSoundBuffer->SetBufferFormat(bufferInfo.format);
				tempSoundBuffer->SetBufferFrequency(bufferInfo.frequency);
				tempSoundBuffer->SetBufferChannelCount(bufferInfo.channels);
				tempSoundBuffer->SetDecodeBufferSize(bufferInfo.bufferSize);

				tempSoundBuffer->SetDecodeBuffer(pDecodeBuffer);

				// TODO Move to the soundBuffer
				ALuint *g_Buffers = new ALuint[NUM_BUFFERS];

				// Generate some AL Buffers for streaming
				alGenBuffers(NUM_BUFFERS, g_Buffers);
				tempSoundBuffer->SetQueueBuffers(g_Buffers);

				// set vorbis
				tempSoundBuffer->SetOggHandle(sOggVorbisFile);
				tempSoundBuffer->SetMemoryStream(pMemoryData);
			}
			else if( fileFormat & GENESIS_FILE_FORMAT_MP3 )
			{
				int iMpg123_ret = NULL;
				//open a default mpg123 decoder
				mpg123_handle *mpg123 ;
				mpg123 = mpg123_new(mpg123_decoders()[0], &iMpg123_ret);
				if ( NULL == mpg123)
				{
					mpg123_exit();
					return false;
				}
				tempSoundBuffer->SetMpg123Handle(mpg123);

				int iMpg123_ret2;
				iMpg123_ret = mpg123_replace_reader_handle(mpg123, ReadMP3MemoryStream, LseekMP3MemoryStream, CleanupMP3MemoryStream);
				iMpg123_ret2 = mpg123_open_handle( mpg123, pMemoryData.get() );
				if ( MPG123_OK != iMpg123_ret || MPG123_OK != iMpg123_ret2)
				{
					pMemoryData->Close();
					CleanupMpg123(mpg123);
					return false;
				}
				tempSoundBuffer->SetMemoryStream(pMemoryData);

				//get mp3 format infomation
				long lSampleRate;
				int iEncoding, iChannels;
				iMpg123_ret = mpg123_getformat(mpg123, &lSampleRate, &iChannels,  &iEncoding);
				if ( MPG123_OK != iMpg123_ret)
				{
					pMemoryData->Close();
					CleanupMpg123(mpg123);
					return false;
				}

				bufferInfo.frequency = lSampleRate;
				bufferInfo.channels  = iChannels;
				SetBufferInfo(bufferInfo);

				if (!bufferInfo.format)
				{
					pMemoryData->Close();
					CleanupMpg123(mpg123);
					return false;
				}

				tempSoundBuffer->SetBufferChannelCount(bufferInfo.channels);
				tempSoundBuffer->SetBufferFormat(bufferInfo.format);
				tempSoundBuffer->SetBufferFrequency(bufferInfo.frequency);

				// Allocate a buffer to be used to store decoded data for all Buffers
				unsigned char *pDecodeBuffer = (unsigned char *)malloc(bufferInfo.bufferSize);

				if (!pDecodeBuffer)
				{
					pMemoryData->Close();
					CleanupMpg123(mpg123);
					return false;
				}

				tempSoundBuffer->SetDecodeBuffer(pDecodeBuffer);
				tempSoundBuffer->SetDecodeBufferSize(bufferInfo.bufferSize);

				ALuint *g_Buffers = new ALuint[NUM_BUFFERS];
				alGenBuffers(NUM_BUFFERS, g_Buffers);
				tempSoundBuffer->SetQueueBuffers(g_Buffers);
			}
		} 
		else
		{
			ALuint uiBuffer = NULL;

			// Generate an AL Buffer.
			//Buffer's release is in function'bool SoundBufferOpenAL::Release()'.
			alGenBuffers( 1, &uiBuffer );
			bool ret = ALFWLoadWaveToBuffer(nameOrData, dataSize, uiBuffer, 0, bOpenMemory);
			if ( !ret )
				return false;

			tempSoundBuffer->SetBuffer(&uiBuffer);
		}

		mSoundBufferContainer.Append( tempSoundBuffer.upcast<SoundBuffer>() );
		*soundBuffer = tempSoundBuffer.get();

		return true;
	}
	//------------------------------------------------------------------------------
	void SoundSystemOpenAL::SetBufferInfo( SoundBuffer::BufferInfo& bufferInfo )
	{
		if (bufferInfo.channels == 1)
		{
			bufferInfo.format = AL_FORMAT_MONO16;
			// Set BufferSize to 250ms (Frequency * 2 (16bit) divided by 4 (quarter of a second))
			bufferInfo.bufferSize = bufferInfo.frequency >> 1;
			// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
			bufferInfo.bufferSize -= (bufferInfo.bufferSize % 2);
		}
		else if (bufferInfo.channels == 2)
		{
			bufferInfo.format = AL_FORMAT_STEREO16;
			// Set BufferSize to 250ms (Frequency * 4 (16bit stereo) divided by 4 (quarter of a second))
			bufferInfo.bufferSize = bufferInfo.frequency;
			// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
			bufferInfo.bufferSize -= (bufferInfo.bufferSize % 4);
		}
		else if (bufferInfo.channels == 4)
		{
			bufferInfo.format = alGetEnumValue("AL_FORMAT_QUAD16");
			// Set BufferSize to 250ms (Frequency * 8 (16bit 4-channel) divided by 4 (quarter of a second))
			bufferInfo.bufferSize = bufferInfo.frequency * 2;
			// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
			bufferInfo.bufferSize -= (bufferInfo.bufferSize % 8);
		}
		else if (bufferInfo.channels == 6)
		{
			bufferInfo.format = alGetEnumValue("AL_FORMAT_51CHN16");
			// Set BufferSize to 250ms (Frequency * 12 (16bit 6-channel) divided by 4 (quarter of a second))
			bufferInfo.bufferSize = bufferInfo.frequency * 3;
			// IMPORTANT : The Buffer Size must be an exact multiple of the BlockAlignment ...
			bufferInfo.bufferSize -= (bufferInfo.bufferSize % 12);
		}
	}
	//------------------------------------------------------------------------------
	bool SoundSystemOpenAL::PlaySound(SoundBuffer* soundBuffer, SoundSystemSource **ssSource, bool paused)
	{
		ALuint uiSource = NULL;
		// Generate a Source to playback the Buffer
		alGenSources( 1, &uiSource );

		GPtr< SoundSystemSourceOpenAL > tempSoundSource = SoundSystemSourceOpenAL::Create();
		
		GENESISOUND_MODE mode = soundBuffer->GetBufferMode();
		GENESIS_FILE_FORMAT fileFormat = soundBuffer->GetFileFormat();
		if (mode & GENESISSOUND_CREATESTREAM)
		{
			if ( fileFormat & GENESIS_FILE_FORMAT_MP3 )
			{
				size_t ulBytesWritten = NULL;
				int iMpg123_ret = NULL;
				mpg123_handle *mpg123 = soundBuffer->GetMpg123Handle();
				unsigned char *pDecodeBuffer = soundBuffer->GetDecodeBuffer();
				unsigned long ulBufferSize = soundBuffer->GetDecodeBufferSize();
				ALuint * queueBuffers = soundBuffer->GetQueueBuffers();
				ALuint ulFormat = soundBuffer->GetBufferFormat();
				unsigned long ulFrequency = soundBuffer->GetBufferFrequency();
				for(int iLoop = 0; iLoop < NUM_BUFFERS; iLoop++)
				{
					iMpg123_ret = mpg123_read(mpg123, pDecodeBuffer, ulBufferSize,&ulBytesWritten);
					if (iMpg123_ret == MPG123_OK)
					{
						alBufferData(queueBuffers[iLoop], ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
						alSourceQueueBuffers(uiSource, 1, &queueBuffers[iLoop]);
					}
					else
					{
						tempSoundSource->SetDecode(false);
						break;
					}
				}
			}
			else if ( fileFormat & GENESIS_FILE_FORMAT_OGG )
			{
				size_t ulBytesWritten = NULL;
				OggVorbis_File *oggHandle = soundBuffer->GetOggHandle();
				unsigned char *pDecodeBuffer = soundBuffer->GetDecodeBuffer();
				unsigned long ulBufferSize = soundBuffer->GetDecodeBufferSize();
				ALuint * queueBuffers = soundBuffer->GetQueueBuffers();
				ALuint ulFormat = soundBuffer->GetBufferFormat();
				unsigned long ulFrequency = soundBuffer->GetBufferFrequency();
				unsigned long ulChannels = soundBuffer->GetBufferChannelCount();
				// Fill all the Buffers with decoded audio data from the OggVorbis file
				for (int iLoop = 0; iLoop < NUM_BUFFERS; iLoop++)
				{
					ulBytesWritten = tempSoundSource->DecodeOggVorbis(oggHandle, (char*)pDecodeBuffer, ulBufferSize, ulChannels);
					if (ulBytesWritten)
					{
						alBufferData(queueBuffers[iLoop], ulFormat, pDecodeBuffer, ulBytesWritten, ulFrequency);
						alSourceQueueBuffers(uiSource, 1, &queueBuffers[iLoop]);
					}
				}
			}

		}
		else
		{
			// Attach Source to Buffer
			void *vpBuffer = soundBuffer->GetBuffer();
			ALuint *pBuffer = NULL;
			pBuffer = (ALuint*)(vpBuffer);
			alSourcei( uiSource, AL_BUFFER, *pBuffer);
		}
		
		tempSoundSource->SetSource(&uiSource);
		tempSoundSource->SetSoundBuffer(soundBuffer);
		mSoundSourceContainer.Append( tempSoundSource.upcast<SoundSystemSource>() );
		*ssSource = tempSoundSource.get();

		tempSoundSource->SetPaused(paused);

		return true;
	}
	//------------------------------------------------------------------------------
	bool SoundSystemOpenAL::ReleaseSingleSource(SoundSystemSource *source)
	{
		bool ret = false;
		SizeT size = mSoundSourceContainer.Size();
		for (SizeT i = size - 1; i >= 0; --i)
		{
			if (mSoundSourceContainer[i].get() == source)
			{
				ret = mSoundSourceContainer[i]->InternalReleaseSource();
				if (!ret)
				{
					return ret;
				}

				mSoundSourceContainer.EraseIndex(i);
				break;
			}
		}

		return ret;
	}
	//------------------------------------------------------------------------------
	bool SoundSystemOpenAL::ReleaseSingleBuffer(SoundBuffer *buffer)
	{
		bool ret = false;
		SizeT size = mSoundBufferContainer.Size();
		for (SizeT i = size - 1; i >= 0; --i)
		{
			if (mSoundBufferContainer[i].get() == buffer)
			{
				ret = mSoundBufferContainer[i]->InternalReleaseBuffer();
				if (!ret)
					return ret;

				mSoundBufferContainer.EraseIndex(i);
				break;
			}
		}

		return ret;
	}
	//------------------------------------------------------------------------------
	void SoundSystemOpenAL::CleanupMpg123(mpg123_handle *mh)
	{
		mpg123_delete(mh);
		mpg123_exit();
	}
	//------------------------------------------------------------------------------
	bool SoundSystemOpenAL::SetListenerAttrs(int listener,
												const Math::vector& pos, 
												const Math::vector& v, 
												const Math::vector& forward,
												const Math::vector& up)
	{
		ALfloat listenerPos[] = {pos.x(), pos.y(), pos.z()};
		ALfloat listenerVel[] = {v.x(), v.y(), v.z()};
		ALfloat listenerOri[] = {forward.x(), forward.y(), forward.z(), up.x(), up.y(), up.z()};

		// Position
		alListenerfv(AL_POSITION,listenerPos);
		if (alGetError() != AL_NO_ERROR)
		{
			return false;
		}
		// Velocity
		alListenerfv(AL_VELOCITY,listenerVel);
		if (alGetError() != AL_NO_ERROR)
		{
			return false;
		}
		// Orientation
		alListenerfv(AL_ORIENTATION,listenerOri);
		if (alGetError() != AL_NO_ERROR)
		{
			return false;
		}

		return true;
	}
	//------------------------------------------------------------------------------
	bool SoundSystemOpenAL::createDSPByType( ALuint type, GPtr<SoundSystemDSP>& dsp )
	{
		dsp = SoundSystemDSPOpenAL::Create();
		dsp->init(type);
		return true;
	}
}

//------------------------------------------------------------------------------
ssize_t ReadMP3MemoryStream(void *handle, void *buf, size_t sz)
{
	ssize_t ret;
	IO::MemoryStream *pData = static_cast< IO::MemoryStream* >(handle);
	ret = pData->Read(buf, sz);
	return ret;
}
//------------------------------------------------------------------------------
off_t LseekMP3MemoryStream(void *handle, off_t offset, int whence)
{
	IO::MemoryStream *pData = static_cast< IO::MemoryStream* >(handle);
	switch (whence)
	{
	case 0:
		pData->Seek(offset, IO::Stream::Begin);
		break;
	case 2:
		pData->Seek(offset, IO::Stream::End);
		break;
	default:
		pData->Seek(offset, IO::Stream::Current);
	}
	off_t ret = pData->GetPosition();
	return ret;
}
//------------------------------------------------------------------------------
void CleanupMP3MemoryStream(void *handle)
{
	
}
//------------------------------------------------------------------------------
size_t ReadOggMemoryStream( void *ptr, size_t size, size_t nmemb, void *datasource )
{
	ssize_t ret;
	IO::MemoryStream* pData = static_cast< IO::MemoryStream* >(datasource);
	ret = pData->Read(ptr, nmemb);
	return ret;
}
//------------------------------------------------------------------------------
int SeekOggMemoryStream( void *datasource, ogg_int64_t offset, int whence )
{
	IO::MemoryStream *pData = static_cast< IO::MemoryStream* >(datasource);
	switch (whence)
	{
	case SEEK_SET:
		pData->Seek((int)offset, IO::Stream::Begin);
		break;
	case SEEK_CUR:
		pData->Seek((int)offset, IO::Stream::Current);
		break;
	case SEEK_END:
		pData->Seek((int)offset, IO::Stream::End);
		break;
	}

	return NULL;
}
//------------------------------------------------------------------------------
int CloseOggMemoryStream( void *datasource )
{
 	return NULL;
}
//------------------------------------------------------------------------------
long TellOggMemoryStream( void *datasource )
{
	IO::MemoryStream *pData = static_cast< IO::MemoryStream* >(datasource);
	size_t position = pData->GetPosition();
	return position;
}


#endif // __SOUND_COMMIT__
