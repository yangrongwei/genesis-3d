/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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

#if WIN32



#include "stdneb.h"
#include "win32stringconverter.h"

namespace Win32
{
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
SizeT
Win32StringConverter::UTF8ToWide(const String& src, ushort* dst, SizeT dstMaxBytes)
{
    return UTF8ToWide(src.AsCharPtr(), dst, dstMaxBytes);
}

//------------------------------------------------------------------------------
/**
*/
SizeT
Win32StringConverter::UTF8ToWide(const char* src, ushort* dst, SizeT dstMaxBytes)
{
    n_assert((0 != src) && (0 != dst) && (dstMaxBytes > 2) && ((dstMaxBytes & 1) == 0));
    SizeT numConv = MultiByteToWideChar(CP_UTF8, 0, src, -1, (LPWSTR) dst, (dstMaxBytes / 2) - 1);
    if (numConv > 0)
    {
        dst[numConv] = 0;
        return numConv;
    }
    else
    {
        DWORD errCode = GetLastError();
        String errMessage;
        switch (errCode)
        {
            case ERROR_INSUFFICIENT_BUFFER: errMessage.Format("ERROR_INSUFFICIENT_BUFFER dstMaxBytes: %d", dstMaxBytes); break;
            case ERROR_INVALID_FLAGS: errMessage.Format("ERROR_INVALID_FLAGS"); break;
            case ERROR_INVALID_PARAMETER: errMessage.Format("ERROR_INVALID_PARAMETER: May occur if src and dst are the same pointer."); break;
            case ERROR_NO_UNICODE_TRANSLATION: errMessage.Format("ERROR_NO_UNICODE_TRANSLATION... should never happen."); break;
            default: errMessage = "Unknown Error";
        }
        n_error("Win32StringConverter::UTF8ToWide() failed to convert string '%s' to wide char! Error '%s'", src, errMessage.AsCharPtr());
        return 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
String
Win32StringConverter::WideToUTF8(ushort* src)
{
    n_assert(0 != src);
    String returnString;
    char dstBuf[1024];
    int numBytesWritten = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR) src, -1, dstBuf, sizeof(dstBuf), 0, 0);
    if (numBytesWritten > 0)
    {
        n_assert(numBytesWritten < sizeof(dstBuf));
        returnString.Set(dstBuf, numBytesWritten);
        return returnString;
    }
    else
    {
        n_error("Win32StringConverter::WideToUTF8(): failed to convert string!");
        return 0;
    }
}

} // namespace Win32

#endif