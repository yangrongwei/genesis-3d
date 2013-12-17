/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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
#ifndef WIN32_WIN32MINIDUMP_H
#define WIN32_WIN32MINIDUMP_H

#include "core/types.h"
#include "util/string.h"

//------------------------------------------------------------------------------
namespace Win32
{
class Win32MiniDump
{
public:
    /// setup the the Win32 exception callback hook
    static void Setup();
    /// write a mini dump
    static bool WriteMiniDump();
	/// internal mini-dump-writer method with extra exception info
	static bool WriteMiniDumpInternal(EXCEPTION_POINTERS* exceptionInfo);
private:
    /// build a filename for the dump file
    static Util::String BuildMiniDumpFilename();
    /// the actual exception handler function called back by Windows
    static LONG WINAPI ExceptionCallback(EXCEPTION_POINTERS* exceptionInfo);
};
 
} // namespace Win32
//------------------------------------------------------------------------------
#endif
