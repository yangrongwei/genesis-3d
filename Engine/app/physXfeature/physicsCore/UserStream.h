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
#ifndef _STREAM_H_
#define _STREAM_H_

#include "PxSimpleTypes.h"
#include "PxIO.h"
namespace App
{
	using namespace physx;

	class MemoryOutputStream: public PxOutputStream
	{
	public:
		MemoryOutputStream();
		virtual				~MemoryOutputStream();

		PxU32		write(const void* src, PxU32 count);

		PxU32		getSize()	const	{	return mSize; }
		PxU8*		getData()	const	{	return mData; }
	private:
		PxU8*		mData;
		PxU32		mSize;
		PxU32		mCapacity;
	};

	class MemoryInputData: public PxInputData
	{
	public:
		MemoryInputData(PxU8* data, PxU32 length);

		PxU32		read(void* dest, PxU32 count);
		PxU32		getLength() const;
		void		seek(PxU32 pos);
		PxU32		tell() const;

	private:
		PxU32		mSize;
		const PxU8*	mData;
		PxU32		mPos;
	};
}




#endif
