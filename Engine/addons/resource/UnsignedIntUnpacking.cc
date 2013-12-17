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

The method in this file is written according to Jonathan Blow's article in the 
Inner Product column of Game Developer Magazine. The article is available at
http://number-none.com/product/Packing%20Integers/index.html. The sample code 
is available at http://www.gdcvault.com/gdmag.
****************************************************************************/
#include "resource/resource_stdneb.h"
#include "UnsignedIntUnpacking.h"

namespace Resources
{
	//------------------------------------------------------------------------------
	UnsignedIntUnpacking::UnsignedIntUnpacking(unsigned int valueCount, 
		unsigned int unpackingBitsCount)
		: mValueCount(valueCount)
		, mUnpackingBitsCount(unpackingBitsCount)
		, mByteCount(0)
		, mNextBitToRead(0)
	{
		if ( (mValueCount != 0) && (mUnpackingBitsCount != 0) )
		{
			mByteCount = (mValueCount * mUnpackingBitsCount + 7)/8;
			mBuffer.Resize(mByteCount, 0);
		}
	}
	//------------------------------------------------------------------------------
	unsigned int UnsignedIntUnpacking::GetValueCount()
	{
		return mValueCount;
	}
	bool UnsignedIntUnpacking::SetValueCount(unsigned int valueCount, bool resizeBuffer)
	{
		if (0 == valueCount)
		{
			return false;
		}

		mValueCount = valueCount;
		if (resizeBuffer && (mUnpackingBitsCount != 0) )
		{
			mByteCount = (mValueCount * mUnpackingBitsCount + 7)/8;
			mBuffer.Clear();
			mBuffer.Resize(mByteCount, 0);
			mNextBitToRead = 0;
		}

		return true;
	}
	//------------------------------------------------------------------------------
	unsigned int UnsignedIntUnpacking::GetUnpackingBitsCount()
	{
		return mUnpackingBitsCount;
	}
	bool UnsignedIntUnpacking::SetUnpackingBitsCount(unsigned int packingBitsCount, bool resizeBuffer)
	{
		if (0 == packingBitsCount)
		{
			return false;
		}

		mUnpackingBitsCount = packingBitsCount;
		if (resizeBuffer && (mValueCount != 0) )
		{
			mByteCount = (mValueCount * mUnpackingBitsCount + 7)/8;
			mBuffer.Clear();
			mBuffer.Resize(mByteCount, 0);
			mNextBitToRead = 0;
		}

		return true;
	}
	//------------------------------------------------------------------------------
	bool UnsignedIntUnpacking::Unpack(unsigned int *pOutputUnsignedInt)
	{
		if ( (0 == mValueCount) || (0 == mUnpackingBitsCount) )
		{
			return false;
		}

		unsigned int byteIndex = (mNextBitToRead / 8);
		if (byteIndex >= mByteCount)
		{
			return false;
		}

		unsigned int bitIndex = (mNextBitToRead % 8);
		unsigned int remainingSpaceThisByte = (8 - bitIndex) & 0x7;

		unsigned int unpackingBitsCount = mUnpackingBitsCount;
		// Make 'mNextBitToRead' to the new position for the next call.
		mNextBitToRead += unpackingBitsCount;

		unsigned int output = 0;
		if (remainingSpaceThisByte)
		{
			unsigned int toCopy = remainingSpaceThisByte;

			if (toCopy > unpackingBitsCount)
			{
				// Remaining space in current byte is big enough for copy
				toCopy = unpackingBitsCount;
			}

			// Shift the bits to the leftest end of the unsigned int. This remove
			//the bits are already copied.
			output = (unsigned int)mBuffer[byteIndex] << (32 - remainingSpaceThisByte);
			output >>= (32 - unpackingBitsCount);
			byteIndex++;

			unpackingBitsCount -= toCopy;
		}

		unsigned int tempReadedNumber = 0;
		while (unpackingBitsCount)
		{
			tempReadedNumber = (unsigned int)mBuffer[byteIndex] << 24;
			tempReadedNumber >>= (32 - unpackingBitsCount);
			output |= tempReadedNumber;
			byteIndex++;
			if (unpackingBitsCount < 8)
			{
				unpackingBitsCount = 0;
			}
			else
			{
				unpackingBitsCount -= 8;
			}
		}

		*pOutputUnsignedInt = output;

		return true;
	}
	//------------------------------------------------------------------------------
	Util::Array<unsigned char>& UnsignedIntUnpacking::GetBuffer()
	{
		return mBuffer;
	}
}//namespace Resources