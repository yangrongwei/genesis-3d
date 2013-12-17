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
#ifndef __SOUNDSYSTEMSOURCE_H__
#define __SOUNDSYSTEMSOURCE_H__

#ifndef __SOUND_COMMIT__

#include "core/refcounted.h"
#include <OpenAL/al.h>
#include "GenesisSound.h"
#include "SoundBufferOpenAL.h"
#include "SoundSystemDSP.h"

namespace Sound
{
	class SoundSystemDSP;

	class SoundSystemSource :  public Core::RefCounted
	{
		__DeclareSubClass( SoundSystemSource, Core::RefCounted);
	public:
		SoundSystemSource();
		virtual ~SoundSystemSource();

		virtual void SetSource(void *source) = 0;
		virtual ALuint GetSource();

		virtual void SetSoundBuffer(SoundBuffer* soundBuffer) = 0;
		virtual SoundBuffer* GetSoundBuffer() = 0;

		virtual void addDSP(GPtr<SoundSystemDSP> dsp) = 0;

		virtual bool InternalReleaseSource() = 0;

		virtual bool SetPaused(bool paused) = 0;
		virtual bool GetPaused(bool *paused) = 0;

		virtual bool IsPlaying(bool *isPlaying) = 0;

		virtual bool SetVolume(float volume) = 0;

		virtual bool Stop() = 0;

		// - property pitch
		virtual float GetPitch(void) const = 0;
		virtual void  SetPitch(float pitch) = 0;

		// - property loop
		virtual bool GetLoop (void) const = 0;
		virtual void SetLoop (bool loop) = 0;

		virtual bool SetMode (GENESISOUND_MODE mode) = 0;
		
		virtual void SetSoundInfo (Math::vector pos, Math::vector vel, Math::vector forward, Math::vector up) = 0;
		virtual bool SetModeAtts(Math::vector &position, Math::vector &velocity,
									 Math::vector &orientation) = 0;
		virtual void SetMaxDistance (float maxdis) = 0;
		virtual void SetMinDistance (float mindis) = 0 ;
		virtual bool Set3DMinMaxDistance(float  mindistance, float  maxdistance) = 0 ;
		
		virtual void SetDistanceMode (DistanMode mode) = 0;

		virtual void Decode(GENESISOUND_MODE mode) = 0;

		virtual unsigned long DecodeOggVorbis(OggVorbis_File *psOggVorbisFile, char *pDecodeBuffer, unsigned long ulBufferSize, unsigned long ulChannels) = 0;

	protected:
		Util::Array< Sound::SoundSystemDSP* > m_SoundDSPContainer;
	};
}
#endif // __SOUND_COMMIT__

#endif//__SOUNDSYSTEMSOURCE_H__