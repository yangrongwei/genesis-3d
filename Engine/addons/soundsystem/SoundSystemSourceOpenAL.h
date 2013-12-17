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
#ifndef __SOUNDSYSTEMSOURCEOPENAL_H__
#define __SOUNDSYSTEMSOURCEOPENAL_H__

#include "SoundSystemSource.h"
#include "SoundSystemDSPOpenAL.h"
#include <OpenAL/al.h>

namespace Sound
{
	class SoundSystemSourceOpenAL :  public Sound::SoundSystemSource
	{
		__DeclareSubClass(SoundSystemSourceOpenAL, Sound::SoundSystemSource);
	public:
		SoundSystemSourceOpenAL();
		virtual ~SoundSystemSourceOpenAL();

		void SetSource(void *source);
		ALuint GetSource() { return mSource; }

		void SetSoundBuffer(SoundBuffer* soundBuffer) { mSoundBuffer = soundBuffer; return; }
		SoundBuffer* GetSoundBuffer() { return mSoundBuffer; }

		bool InternalReleaseSource();

		virtual bool SetPaused(bool paused);
		virtual bool GetPaused(bool *paused);

		virtual bool IsPlaying(bool *isPlaying);

		virtual bool SetVolume(float volume);

		virtual bool Stop();

		virtual float GetPitch(void) const;
		virtual void SetPitch(float pitch);

		virtual bool GetLoop (void) const;
		virtual void SetLoop (bool loop);

		virtual bool SetMode(GENESISOUND_MODE mode);

		virtual void SetMaxDistance(float maxdis);
		virtual void SetMinDistance(float mindis);
		
		virtual void SetSoundInfo (Math::vector pos,
									 Math::vector vel,
									 Math::vector forward,
									 Math::vector up);

		bool Set3DMinMaxDistance(float  mindistance, float  maxdistance);

		bool SetModeAtts(Math::vector &position, Math::vector &velocity,
							 Math::vector &orientation);
		
		virtual void SetDistanceMode(DistanMode mode);

		virtual void addDSP(GPtr<SoundSystemDSP> dsp);

		void Decode(GENESIS_FILE_FORMAT fileFormat);

		unsigned long DecodeOggVorbis(OggVorbis_File *psOggVorbisFile, char *pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels);
		void Swap(short &s1, short &s2);

		void SetDecode(bool bDecode);

	private:
		SoundBuffer*  mSoundBuffer;
		bool		  mIs3D;
		bool          mStopByPlayOver;
		bool		  mIsLoop;
		ALuint        mSource;
		bool          m_bDecode;

	};

	inline void SoundSystemSourceOpenAL::SetDecode(bool bDecode)
	{
		m_bDecode = bDecode;
	}
}

#endif//__SOUNDSYSTEMSOURCEOPENAL_H__