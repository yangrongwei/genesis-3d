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
#include "SoundBufferOpenAL.h"
#include "SoundSystemOpenAL.h"

namespace Sound
{
	__ImplementClass(Sound::SoundBufferOpenAL, 'SBOA', Sound::SoundBuffer);

	SoundBufferOpenAL::SoundBufferOpenAL()
		: mBuffer(NULL)
		, mQueueBuffers(NULL)
		, mMpg123(NULL)
		, mOggVorbisFile(NULL)
		, mMemoryStream(NULL)
		, mDecodeBuffer(NULL)
		, mDecodeBufferSize(0)
		, mBufferFormat(0)
		, mBufferFrequency(0)
	{}
	SoundBufferOpenAL::~SoundBufferOpenAL() {}
	//------------------------------------------------------------------------------
	void SoundBufferOpenAL::SetBuffer(void *buffer)
	{ 
		ALuint *alBuffer = static_cast< ALuint* >(buffer);
		mBuffer = *alBuffer; 
		return; 
	}
	//------------------------------------------------------------------------------
	bool SoundBufferOpenAL::ReleaseBuffer()
	{
		bool ret = SoundSystem::Instance()->ReleaseSingleBuffer(this);
		return ret;
	}
	//------------------------------------------------------------------------------
	bool SoundBufferOpenAL::InternalReleaseBuffer()
	{
		if (mDecodeBuffer)
		{
			free(mDecodeBuffer);
			mDecodeBuffer = NULL;
		}

		if ( mMemoryStream )
		{
			mMemoryStream->Close();
			mMemoryStream = NULL;
		}

		if (mMpg123)
		{
			mpg123_close(mMpg123);
			mMpg123 = NULL;
		}

		if (mOggVorbisFile)
		{
			ov_clear(mOggVorbisFile);
			mOggVorbisFile = NULL;
		}

		if (NULL != mBuffer)
			alDeleteBuffers(1, &mBuffer);
		else
			alDeleteBuffers( NUM_BUFFERS, mQueueBuffers );

		if (alGetError() == AL_NO_ERROR)
			return true;
		else
			return false;
	}
}

#endif // __SOUND_COMMIT__