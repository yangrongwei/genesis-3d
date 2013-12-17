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
#include "UnsignedIntPacking.h"

namespace Resources
{
	//------------------------------------------------------------------------------
	UnsignedIntPacking::UnsignedIntPacking(unsigned int valueCount, 
										   unsigned int packingBitsCount)
		: mValueCount(valueCount)
		, mPackingBitsCount(packingBitsCount)
		, mByteCount(0)
		, mNextBitToWrite(0)
	{
		if ( (mValueCount != 0) && (mPackingBitsCount != 0) )
		{
			mByteCount = (mValueCount * mPackingBitsCount + 7)/8;
			mBuffer.Resize(mByteCount, 0);
		}
	}
	//------------------------------------------------------------------------------
	unsigned int UnsignedIntPacking::GetValueCount()
	{
		return mValueCount;
	}
	bool UnsignedIntPacking::SetValueCount(unsigned int valueCount, bool resizeBuffer)
	{
		if (0 == valueCount)
		{
			return false;
		}

		mValueCount = valueCount;
		if (resizeBuffer && (mPackingBitsCount != 0) )
		{
			mByteCount = (mValueCount * mPackingBitsCount + 7)/8;
			mBuffer.Clear();
			mBuffer.Resize(mByteCount, 0);
			mNextBitToWrite = 0;
		}

		return true;
	}
	//------------------------------------------------------------------------------
	unsigned int UnsignedIntPacking::GetPackingBitsCount()
	{
		return mPackingBitsCount;
	}
	bool UnsignedIntPacking::SetPackingBitsCount(unsigned int packingBitsCount, bool resizeBuffer)
	{
		if (0 == packingBitsCount)
		{
			return false;
		}

		mPackingBitsCount = packingBitsCount;
		if (resizeBuffer && (mValueCount != 0) )
		{
			mByteCount = (mValueCount * mPackingBitsCount + 7)/8;
			mBuffer.Clear();
			mBuffer.Resize(mByteCount, 0);
			mNextBitToWrite = 0;
		}

		return true;
	}
	//------------------------------------------------------------------------------
	bool UnsignedIntPacking::Pack(unsigned int inputUnsignedInt)
	{
		//The code in this function is modified base on  Jonathan Blow's sample code.

		n_assert( (inputUnsignedInt & ((1 << mPackingBitsCount) - 1)) == inputUnsignedInt);
		if ( (0 == mValueCount) || (0 == mPackingBitsCount) )
		{
			return false;
		}

		// Scoot the value bits up to the top of the word; this makes
		// them easier to work with.
		inputUnsignedInt <<= (32 - mPackingBitsCount);

		// First we do the hard part: pack bits into the first byte,
		// which may already have bits in it.
		unsigned int byteIndex = (mNextBitToWrite / 8);
		if (byteIndex >= mByteCount)
		{
			return false;
		}

		unsigned int bitIndex = (mNextBitToWrite % 8);
		unsigned int emptySpaceThisTyte = (8 - bitIndex) & 0x7;

		// Update mNextBitToWrite for the next call; we don't need 
		// the old value any more.
		mNextBitToWrite += mPackingBitsCount;

		if (emptySpaceThisTyte)
		{
			unsigned int toCopy = emptySpaceThisTyte;

			if (toCopy > mPackingBitsCount)
			{
				// We don't have enough bits to fill up this byte.
				toCopy = mPackingBitsCount;
			}

			unsigned int fillBits = inputUnsignedInt >> (32 - emptySpaceThisTyte);
			mBuffer[byteIndex] |= fillBits;

			byteIndex++;
			inputUnsignedInt <<= toCopy;
		}

		// Now we do the fast and easy part for what is hopefully
		// the bulk of the data.
		while (inputUnsignedInt)
		{
			mBuffer[byteIndex] = inputUnsignedInt >> 24;
			byteIndex++;
			inputUnsignedInt <<= 8;
		}

		return true;
	}
	//------------------------------------------------------------------------------
	Util::Array<unsigned char>& UnsignedIntPacking::GetBuffer()
	{
		return mBuffer;
	}
}//namespace Resources