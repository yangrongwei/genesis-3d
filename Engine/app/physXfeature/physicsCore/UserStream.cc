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
#ifndef __PHYSX_COMMIT__
#include "stdneb.h"
#include "UserStream.h"
#include "PxAssert.h"
#include "PxMath.h"
#include "PxPhysics.h"

#if __WIN32__
#include "foundation/memory/win360/win360memory.h"
#endif

namespace App
{
	MemoryOutputStream::MemoryOutputStream()
		:mData		(NULL),
		mSize		(0),
		mCapacity	(0)
	{
	}

	MemoryOutputStream::~MemoryOutputStream()
	{
		if(mData)
			delete[] mData;
	}

	PxU32 MemoryOutputStream::write(const void* src, PxU32 size)
	{
		PxU32 expectedSize = mSize + size;
		if(expectedSize > mCapacity)
		{
			mCapacity = expectedSize + 4096;

			PxU8* newData = new PxU8[mCapacity];
			PX_ASSERT(newData!=NULL);

			if(newData)
			{
				memcpy(newData, mData, mSize);
				delete[] mData;
			}
			mData = newData;
		}
		memcpy(mData+mSize, src, size);
		mSize += size;
		return size;
	}

	///////////////////////////////////////////////////////////////////////////////

	MemoryInputData::MemoryInputData(PxU8* data, PxU32 length) :
	mSize	(length),
		mData	(data),
		mPos	(0)
	{
	}

	PxU32 MemoryInputData::read(void* dest, PxU32 count)
	{
		PxU32 length = PxMin<PxU32>(count, mSize-mPos);
		memcpy(dest, mData+mPos, length);
		mPos += length;
		return length;
	}

	PxU32 MemoryInputData::getLength() const
	{
		return mSize;
	}

	void MemoryInputData::seek(PxU32 offset)
	{
		mPos = PxMin<PxU32>(mSize, offset);
	}

	PxU32 MemoryInputData::tell() const
	{
		return mPos;
	}
} 
#endif //__PHYSX_COMMIT__
