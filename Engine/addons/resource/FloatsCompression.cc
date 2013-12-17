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
http://number-none.com/product/Scalar%20Quantization/index.html. The sample
code is available at http://www.gdcvault.com/gdmag.
****************************************************************************/
#include "resource/resource_stdneb.h"
#include "floatsCompression.h"

namespace Resources
{
	//------------------------------------------------------------------------------
	FloatsCompression::FloatsCompression(float minNumber, float maxNumber, 
										unsigned int quantizationBitsCount)
		: mMinNumber(minNumber)
		, mMaxNumber(maxNumber)
		, mQuantizationBitsCount(quantizationBitsCount)
	{
		mValueRange = mMaxNumber - mMinNumber;
		unsigned int normalIntervals = (1 << mQuantizationBitsCount) - 1;
		if ( (0 == mValueRange) || (0 == normalIntervals) )
		{
			mIntervalsR = 0;
			mIntervalSizeR = 0;
		}
		else
		{
			mIntervalsR = normalIntervals - 1;
			mIntervalSizeR = mValueRange / mIntervalsR;
		}
	}
	//------------------------------------------------------------------------------
	float FloatsCompression::GetMinNumber()
	{
		return mMinNumber;
	}
	bool FloatsCompression::SetMinNumber(float minNumber)
	{
		if (minNumber > mMaxNumber)
		{
			return false;
		}

		mMinNumber  = minNumber;
		mValueRange = mMaxNumber - mMinNumber;
		mIntervalSizeR = mValueRange / mIntervalsR;

		return true;
	}
	//------------------------------------------------------------------------------
	float FloatsCompression::GetMaxNumber()
	{
		return mMaxNumber;
	}
	bool FloatsCompression::SetMaxNumber(float maxNumber)
	{
		if (maxNumber < mMinNumber)
		{
			return false;
		}

		mMaxNumber = maxNumber;
		mValueRange = mMaxNumber - mMinNumber;
		mIntervalSizeR = mValueRange / mIntervalsR;

		return true;
	}
	//------------------------------------------------------------------------------
	unsigned int FloatsCompression::GetQuantizationBitsCount()
	{
		return mQuantizationBitsCount;
	}
	bool FloatsCompression::SetQuantizationBitsCount(unsigned int quantizationBitsCount)
	{
		if (0 == quantizationBitsCount)
		{
			return false;
		}

		mQuantizationBitsCount = quantizationBitsCount;
		unsigned int normalIntervals = (1 << mQuantizationBitsCount) - 1;
		mIntervalsR = normalIntervals - 1;
		mIntervalSizeR = mValueRange / mIntervalsR;

		return true;
	}
	//------------------------------------------------------------------------------
	bool FloatsCompression::CodeRL(float inputFloat, 
									unsigned int *pOutputUnsignedInt)
	{
		if ( (0 == mValueRange) || (0 == mIntervalsR) )
		{
			return false;
		}

		float normalizedFloat = (inputFloat - mMinNumber) / mValueRange;
		unsigned int roundedResult = (unsigned int)(normalizedFloat * mIntervalsR + 0.5f);
		if (roundedResult > mIntervalsR)
		{
			roundedResult = mIntervalsR;
		}

		*pOutputUnsignedInt = roundedResult;

		return true;
	}
	//------------------------------------------------------------------------------
	bool FloatsCompression::DecodeRL(unsigned int inputUnsignedInt, 
										float *pOutputFloat)
	{
		if ( (0 == mValueRange) || (0 == mIntervalSizeR) )
		{
			return false;
		}

		*pOutputFloat = mMinNumber + inputUnsignedInt * mIntervalSizeR;

		return true;
	}
}//namespace Resources