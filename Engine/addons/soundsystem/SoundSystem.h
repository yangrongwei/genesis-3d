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
#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__
#ifndef __SOUND_COMMIT__

#include "core/refcounted.h"
#include "SoundBuffer.h"
#include "util/array.h"
#include "SoundSystemSource.h"
#include "core/singleton.h"
#include "GenesisSound.h"
#include "SoundSystemDSP.h"

namespace Sound
{
	class SoundSystem :  public Core::RefCounted
	{
		__DeclareSubClass(SoundSystem, Core::RefCounted);
		__DeclareImageSingleton(SoundSystem);
	protected:
		Util::Array< GPtr< Sound::SoundBuffer > > mSoundBufferContainer;
		Util::Array< GPtr< Sound::SoundSystemSource > > mSoundSourceContainer;

	public:
		SoundSystem();
		virtual ~SoundSystem();

		virtual bool InitSoundSystem() = 0;
		virtual void ReleaseSoundSystem() = 0;
		
		virtual bool CreateSoundBuffer(const char* nameOrData, SizeT dataSize, 
									   SoundBuffer **soundBuffer, 
									   GENESISOUND_MODE mode,
									   GENESIS_FILE_FORMAT fileFormat) = 0;
		virtual bool createDSPByType(ALuint type, GPtr<SoundSystemDSP>& dsp) = 0;	// create a filter

		virtual bool PlaySound(SoundBuffer* soundBuffer, SoundSystemSource **ssSource, bool paused) = 0;

		virtual bool ReleaseSingleSource(SoundSystemSource *source) = 0;
		virtual bool ReleaseSingleBuffer(SoundBuffer *buffer) = 0;

		virtual bool SetListenerAttrs(int listener, const Math::vector& pos, const Math::vector& v, const Math::vector& forward, const Math::vector& up) = 0;

		virtual void SetBufferInfo(SoundBuffer::BufferInfo &bf) = 0;
	};
}

#endif // __SOUND_COMMIT__
#endif//__SOUNDSYSTEM_H__