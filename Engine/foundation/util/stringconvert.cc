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
#include "stringconvert.h"
#ifdef __WIN32__
#include "util/win32/win32stringconverter.h"
#define utf8_to_wide Win32::Win32StringConverter::UTF8ToWide

#elif __ANDROID__	
#include "util/android/androidstringconverter.h"
#define utf8_to_wide Android::AndroidStringConverter::UTF8ToWide

#elif __OSX__
#include "string.h"
//#define utf8_to_wide OSX::OSXStringConverter::UTF8ToWide
namespace OSX {

static SizeT UTF8ToWideIOS(const Util::String& src, ushort* dst, SizeT dstMaxBytes)
{
    return UTF8ToWideIOS(src.AsCharPtr(), dst, NULL);
}

static SizeT UTF8ToWideIOS(const char* src, ushort* dst, SizeT dstMaxBytes)
{
    n_assert((0 != src) && (0 != dst) && (dstMaxBytes > 2) && ((dstMaxBytes & 1) == 0));
    SizeT numConv = mbstowcs( (wchar_t*)dst, src,  strlen(src) * 2);
    if (numConv > 0)
    {
        dst[numConv] = 0;
        return numConv;
    }
    else
    {
        n_error("-----------------------failed to convert string to wide char!-----------------------");
        return -1;
    }
}

static Util::String WideToUTF8IOS(ushort* src)
{
    n_assert(0 != src);
    Util::String returnString;
    char dstBuf[1024];
    SizeT numBytesWritten = wcstombs(dstBuf, (wchar_t*)src, strlen(dstBuf));
    if (numBytesWritten > 0)
    {
        n_assert(numBytesWritten < sizeof(dstBuf));
        returnString.Set(dstBuf, numBytesWritten);
        return returnString;
    }
    else
    {
        n_error("-----------------------failed to convert string!-----------------------");
        return 0;
    }
}

static void WideToUTF8IOS(ushort* src, Util::String& out)
{
    out = WideToUTF8IOS(src);
}
}
#else
#error "unknown platform"

#endif // WIN32

namespace Util
{
	void StringConvert::UTF8ToWide(const char* src, char16_t* dst, SizeT dstMaxBytes)
	{
#if __OSX__
        OSX::UTF8ToWideIOS(src, (ushort*)dst, dstMaxBytes);
#else
		utf8_to_wide(src, dst, dstMaxBytes);
#endif
	}

	void StringConvert::UTF8ToWide(const Util::String& src, char16_t* dst, SizeT dstMaxBytes)
	{
#if __OSX__
        OSX::UTF8ToWideIOS(src, (ushort*)dst, dstMaxBytes);
#else
		utf8_to_wide(src, dst, dstMaxBytes);
#endif
	}
#ifdef WIN32
	void StringConvert::WideToUTF8(char16_t* src, Util::String& out)
	{
		n_assert(0 != src);
		char dstBuf[1024];
		int numBytesWritten = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR) src, -1, dstBuf, sizeof(dstBuf), 0, 0);
		if (numBytesWritten > 0)
		{
			n_assert(numBytesWritten < sizeof(dstBuf));
			out.Set(dstBuf, numBytesWritten);
		}
		else
		{
			n_error("Win32StringConverter::WideToUTF8(): failed to convert string!");
		}
	}
#endif
}


