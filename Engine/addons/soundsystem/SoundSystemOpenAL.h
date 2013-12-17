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
#ifndef __SOUNDSYSTEMOPENAL_H__
#define __SOUNDSYSTEMOPENAL_H__

#ifndef __SOUND_COMMIT__

#define NUM_BUFFERS 4

#include "SoundSystem.h"
#include "SoundBuffer.h"
#include "CWaves.h"
#include "mpg123/mpg123.h"
#include "Vorbisfile/vorbisfile.h"

namespace Sound
{
	class SoundSystemOpenAL :  public SoundSystem
	{
		__DeclareSubClass(SoundSystemOpenAL, Sound::SoundSystem);
	private:
		void CleanupMpg123(mpg123_handle *mh);
	public:
		SoundSystemOpenAL();
		virtual ~SoundSystemOpenAL();

		bool InitSoundSystem();
		void ReleaseSoundSystem();

		bool CreateSoundBuffer(const char* nameOrData, SizeT dataSize, 
							   SoundBuffer **soundBuffer, 
							   GENESISOUND_MODE mode,
							   GENESIS_FILE_FORMAT fileFormat);
		bool createDSPByType(ALuint type, GPtr<SoundSystemDSP>& dsp);	// create a filter


		bool PlaySound(SoundBuffer* soundBuffer, SoundSystemSource **ssSource, bool paused);

		bool ReleaseSingleSource(SoundSystemSource *source);
		bool ReleaseSingleBuffer(SoundBuffer *buffer);

		bool SetListenerAttrs(int listener, const Math::vector& pos, 
									const Math::vector& v, 
									const Math::vector& forward,
									const Math::vector& up);

		void SetBufferInfo(SoundBuffer::BufferInfo &bf);
	};
}

// For Mp3
ssize_t ReadMP3MemoryStream(void *handle, void *buf, size_t sz);
off_t LseekMP3MemoryStream(void *handle, off_t offset, int whence);
void CleanupMP3MemoryStream(void *handle);

// For Ogg
size_t ReadOggMemoryStream(void *ptr, size_t size, size_t nmemb, void *datasource);
int SeekOggMemoryStream(void *datasource, ogg_int64_t offset, int whence);
int CloseOggMemoryStream(void *datasource);
long TellOggMemoryStream(void *datasource);

#endif // __SOUND_COMMIT__
#endif//__SOUNDSYSTEMOPENAL_H__