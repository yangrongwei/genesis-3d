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
#include "SoundBuffer.h"

#ifndef __SOUND_COMMIT__
namespace Sound
{
	__ImplementAbstractClass(Sound::SoundBuffer, 'SDBF', Core::RefCounted);

	//------------------------------------------------------------------------------
	SoundBuffer::SoundBuffer() {}
	//------------------------------------------------------------------------------
	SoundBuffer::~SoundBuffer() {}
	//------------------------------------------------------------------------------
	void SoundBuffer::SetBuffer(void *buffer) 
	{ 
		//need override in derived class
		n_assert(false);
	}
	//------------------------------------------------------------------------------
	void* SoundBuffer::GetBuffer() 
	{ 
		//need override in derived class
		n_assert(false);
		void* buffer = 0;
		return buffer; 
	}
	//------------------------------------------------------------------------------
	void SoundBuffer::SetFileFormat(GENESIS_FILE_FORMAT fileFormat)
	{
		//need override in SoundBufferOpenAL class
		n_assert(false);
	}
	//------------------------------------------------------------------------------
	GENESIS_FILE_FORMAT SoundBuffer::GetFileFormat()
	{
		//need override in SoundBufferOpenAL class
		n_assert(false);
		GENESIS_FILE_FORMAT fileFormat = 0;
		return fileFormat;
	}
}
#endif // __SOUND_COMMIT__

