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
#ifndef __SOUNDBUFFEROPENAL_H__
#define __SOUNDBUFFEROPENAL_H__

#ifndef __SOUND_COMMIT__

#include "SoundBuffer.h"
#include <OpenAL/al.h>

namespace Sound
{
	class SoundBufferOpenAL :  public Sound::SoundBuffer
	{
		__DeclareSubClass(SoundBufferOpenAL, Sound::SoundBuffer);
	public:
		SoundBufferOpenAL();
		virtual ~SoundBufferOpenAL();

		/*void SetBuffer(ALuint buffer) { mBuffer = buffer; return; }
		ALuint GetBuffer() { return mBuffer; }*/

		void SetBuffer(void *buffer); 
		void* GetBuffer() { return &mBuffer; }

		void SetQueueBuffers(ALuint *queueBuffers) { mQueueBuffers = queueBuffers; return; }
		ALuint* GetQueueBuffers() { return mQueueBuffers; }

		void SetMpg123Handle(mpg123_handle *mpg123) { mMpg123 = mpg123; return; }
		mpg123_handle* GetMpg123Handle() { return mMpg123; }

		void SetOggHandle(OggVorbis_File *oggHandle) { mOggVorbisFile = oggHandle; return; }
		OggVorbis_File* GetOggHandle() { return mOggVorbisFile; }

		void SetMemoryStream( GPtr<IO::MemoryReader> &memoryStream) { mMemoryStream = memoryStream; return; }
		GPtr<IO::MemoryReader> GetMemoryStream() { return mMemoryStream; }

		void SetDecodeBuffer( unsigned char* pDecodeBuffer) { mDecodeBuffer = pDecodeBuffer; return; }
		unsigned char* GetDecodeBuffer() { return mDecodeBuffer; }
		void SetDecodeBufferSize( unsigned long ulDecodeBufferSize) { mDecodeBufferSize = ulDecodeBufferSize; return; }
		unsigned long GetDecodeBufferSize() { return mDecodeBufferSize; }

		void SetBufferFormat(ALuint ulFormat) { mBufferFormat = ulFormat; return; }
		ALuint GetBufferFormat() { return mBufferFormat; }

		void SetBufferFrequency(unsigned long ulFrequency) { mBufferFrequency = ulFrequency; return; }
		unsigned long GetBufferFrequency() { return mBufferFrequency; }

		void SetBufferChannelCount(unsigned long ulChannels) { mChannels = ulChannels; }
		unsigned long GetBufferChannelCount() { return mChannels; }

		void SetBufferMode(GENESISOUND_MODE mode) { mBufferMode = mode; return; }
		GENESISOUND_MODE GetBufferMode() { return mBufferMode; }

		void SetFileFormat(GENESIS_FILE_FORMAT fileFormat) { mFileFormat = fileFormat; }
		GENESIS_FILE_FORMAT GetFileFormat() { return mFileFormat; }

		bool ReleaseBuffer();
		bool InternalReleaseBuffer();
	private:
		ALuint                    mBuffer;
		ALuint*                   mQueueBuffers;
		GPtr<IO::MemoryReader>    mMemoryStream;
		unsigned char*            mDecodeBuffer;
		unsigned long             mDecodeBufferSize;
		ALuint                    mBufferFormat;
		unsigned long             mBufferFrequency;
		unsigned long			  mChannels;
		GENESISOUND_MODE          mBufferMode;
		GENESIS_FILE_FORMAT       mFileFormat;

		mpg123_handle*            mMpg123;
		OggVorbis_File*			  mOggVorbisFile;
	};
}

#endif // __SOUND_COMMIT__
#endif//__SOUNDBUFFEROPENAL_H__