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
#ifndef __SOUNDBUFFER_H__
#define __SOUNDBUFFER_H__

#ifndef __SOUND_COMMIT__
#include "core/refcounted.h"
#include <OpenAL/al.h>
#include "mpg123/mpg123.h"
#include "Vorbisfile/vorbisfile.h"
#include "io/memoryreader.h"
#include "GenesisSound.h"

namespace Sound
{
	class SoundBuffer :  public Core::RefCounted
	{
		__DeclareSubClass(SoundBuffer, Core::RefCounted);
	public:
		struct BufferInfo
		{
			unsigned long		frequency;
			unsigned long		format;
			unsigned long		channels;
			unsigned long		bufferSize;

			BufferInfo() : frequency(0),
				format(0),channels(0),bufferSize(0)
			{

			}
		};
	public:
		SoundBuffer();
		virtual ~SoundBuffer();

		/*virtual void SetBuffer(ALuint buffer) = 0;
		virtual ALuint GetBuffer() = 0;*/

		virtual void SetBuffer(void *buffer);
		virtual void* GetBuffer();

		virtual void SetQueueBuffers(ALuint *queueBuffers) = 0;
		virtual ALuint* GetQueueBuffers() = 0;

		virtual void SetMpg123Handle(mpg123_handle *mpg123) = 0;
		virtual mpg123_handle* GetMpg123Handle() = 0;

		virtual void SetOggHandle(OggVorbis_File *oggHandle) = 0;
		virtual OggVorbis_File* GetOggHandle() = 0;

		virtual void SetMemoryStream( GPtr<IO::MemoryReader> &memoryStream) = 0;
		virtual GPtr<IO::MemoryReader> GetMemoryStream() = 0;

		virtual void SetDecodeBuffer( unsigned char* pDecodeBuffer) = 0;
		virtual unsigned char* GetDecodeBuffer() = 0;
		virtual void SetDecodeBufferSize( unsigned long ulDecodeBufferSize) = 0;
		virtual unsigned long GetDecodeBufferSize() = 0;

		virtual void SetBufferFormat(ALuint ulFormat) = 0;
		virtual ALuint GetBufferFormat() = 0;

		virtual void SetBufferFrequency(unsigned long ulFrequency) = 0;
		virtual unsigned long GetBufferFrequency() = 0;

		virtual void SetBufferChannelCount(unsigned long ulFrequency) = 0;
		virtual unsigned long GetBufferChannelCount() = 0;


		virtual void SetBufferMode(GENESISOUND_MODE mode) = 0;
		virtual GENESISOUND_MODE GetBufferMode() = 0;

		virtual void SetFileFormat(GENESIS_FILE_FORMAT fileFormat);
		virtual GENESIS_FILE_FORMAT GetFileFormat();

		virtual bool ReleaseBuffer() = 0;
		virtual bool InternalReleaseBuffer() = 0;
	};
}

#endif

#endif//__SOUNDBUFFER_H__