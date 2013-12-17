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
#pragma once

#include "util/array.h"
#include "foundation/core/ptr.h"
#include "io/binaryreader.h"
#include "floatsCompression.h"
#include "UnsignedIntUnpacking.h"

namespace Resources
{
	//------------------------------------------------------------------------
	template<typename T, typename ElemT>
	bool ReadPackedFloat(GPtr<IO::BinaryReader>& pReader, T& outData)
	{
		float minNumber = pReader->ReadFloat();
		float maxNumber = pReader->ReadFloat();
		unsigned int quantizationBitsCount = pReader->ReadUInt();
		Resources::FloatsCompression fc(minNumber, maxNumber, quantizationBitsCount);
		unsigned int valueCount = pReader->ReadUInt();
		unsigned int unpackingBitsCount = pReader->ReadUInt();
		Resources::UnsignedIntUnpacking uiu(valueCount, unpackingBitsCount);
		Util::Array<unsigned char>& dataBuffer = uiu.GetBuffer();
		pReader->ReadRawData( &(dataBuffer[0]), dataBuffer.Size() );

		int elemSize = sizeof(ElemT) / (sizeof(float));
		int elemCount = valueCount / elemSize;
		outData.Resize(elemCount, ElemT());

		float *pIterator = (float*)( &(outData[0]) );
		unsigned int tempValue = 0;
		bool result = true;
		for (unsigned int i = 0; i < valueCount; i++)
		{
			result = uiu.Unpack(&tempValue);
			result = fc.DecodeRL(tempValue, pIterator);
			if (!result)
			{
				return false;
			}

			pIterator++;
		}

		return true;
	}
	//------------------------------------------------------------------------------
	template<typename T, typename ElemT, typename IntType>
	bool ReadPackedInt(GPtr<IO::BinaryReader>& pReader, T& outData)
	{
		unsigned int valueCount = pReader->ReadUInt();
		unsigned int unpackingBitsCount = pReader->ReadUInt();
		Resources::UnsignedIntUnpacking uiu(valueCount, unpackingBitsCount);
		Util::Array<unsigned char>& dataBuffer = uiu.GetBuffer();
		pReader->ReadRawData( &(dataBuffer[0]), dataBuffer.Size() );

		int elemSize = sizeof(ElemT) / (sizeof(IntType));
		int elemCount = valueCount / elemSize;
		outData.Resize(elemCount, ElemT());

		ElemT *pIterator = (ElemT*)( &(outData[0]) );
		unsigned int tempValue = 0;
		bool result = true;
		for (unsigned int i = 0; i < valueCount; i++)
		{
			result = uiu.Unpack(&tempValue);
			if (!result)
			{
				return false;
			}

			*pIterator = (ElemT)tempValue;
			pIterator++;
		}

		return true;
	}
}
