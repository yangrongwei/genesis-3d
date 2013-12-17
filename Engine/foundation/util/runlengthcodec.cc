/****************************************************************************
Copyright (c) 2008, Radon Labs GmbH
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
#include "util/runlengthcodec.h"

namespace Util
{

//------------------------------------------------------------------------------
/**
    Get some safe destination buffer size for runlength-encoding.
    This actually can be up to twice as big as the source buffer for
    completely random data!
*/
SizeT
RunLengthCodec::GetSafeRLEBufferSize(SizeT srcBufferSize)
{
    return srcBufferSize * 2;
}

//------------------------------------------------------------------------------
/**
*/
SizeT
RunLengthCodec::Encode(const uchar* srcPtr, SizeT srcNumBytes, uchar* dstPtr, SizeT dstNumBytes)
{
    n_assert(srcNumBytes >= 2);
    n_assert(0 != srcPtr);
    n_assert(0 != dstPtr);
    n_assert((srcNumBytes > 0) && (dstNumBytes >= RunLengthCodec::GetSafeRLEBufferSize(srcNumBytes)));

    const uchar* dstStore = dstPtr;
    const uchar* srcEndPtr = srcPtr + srcNumBytes;

    while (srcPtr < srcEndPtr)
    {
        uchar curByte = *srcPtr++;
        SizeT numBytes = 1;
        while ((srcPtr < srcEndPtr) && (curByte == *srcPtr) && (numBytes < 255))
        {
            numBytes++;
            srcPtr++;
        }
        *dstPtr++ = (uchar) numBytes;
        *dstPtr++ = curByte;
    }
    return SizeT(dstPtr - dstStore);
}

//------------------------------------------------------------------------------
/**
*/
SizeT
RunLengthCodec::ComputeDecodedSize(const uchar* srcPtr, SizeT srcNumBytes)
{
    SizeT decodedSize = 0;
    const uchar* srcEndPtr = srcPtr + srcNumBytes;
    while (srcPtr < srcEndPtr)
    {
        uchar num = *srcPtr++;
        srcPtr++;
        decodedSize += num;
    }
    return decodedSize;
}

//------------------------------------------------------------------------------
/**
*/
SizeT
RunLengthCodec::Decode(const uchar* srcPtr, SizeT srcNumBytes, uchar* dstPtr, SizeT dstNumBytes)
{
    n_assert(srcNumBytes >= 2);
    n_assert((srcNumBytes & 1) == 0);

    const uchar* srcEndPtr = srcPtr + srcNumBytes;
    const uchar* dstEndPtr = dstPtr + dstNumBytes;
    const uchar* dstStore = dstPtr;
    
    while (srcPtr < srcEndPtr)
    {
        uchar num = *srcPtr++;
        uchar val = *srcPtr++;
        IndexT i;
        for (i = 0; i < num; i++)
        {
            n_assert(dstPtr < dstEndPtr);
            *dstPtr++ = val;
        }
    }
    return SizeT(dstPtr - dstStore);
}

} // namespace Util