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

#ifdef WIN32

#include "stdneb.h"
#include "debug/win32/win32minidump.h"

namespace Win32
{
using namespace Util;

//------------------------------------------------------------------------------
/**
    This static method registers our own exception handler with Windows.
*/
void
Win32MiniDump::Setup()
{
    SetUnhandledExceptionFilter(Win32MiniDump::ExceptionCallback);
}

//------------------------------------------------------------------------------
/**
    This method is called by n_assert() and n_error() to write out
    a minidump file.
*/
bool
Win32MiniDump::WriteMiniDump()
{
    return Win32MiniDump::WriteMiniDumpInternal(0);
}

//------------------------------------------------------------------------------
/**
    Private method to write a mini-dump with extra exception info. This 
    method is either called from the public WriteMiniDump() method or
    from the ExceptionCallback() function.
*/
bool
Win32MiniDump::WriteMiniDumpInternal(EXCEPTION_POINTERS* exceptionInfo)
{
#if (NEBULA3_ENABLE_MINIDUMPS)
    String dumpFilename = BuildMiniDumpFilename();
    if (dumpFilename.IsValid())
    {
        HANDLE hFile = CreateFile(dumpFilename.AsCharPtr(), // lpFileName
                                  GENERIC_WRITE,            // dwDesiredAccess
                                  FILE_SHARE_READ,          // dwShareMode
                                  0,                        // lpSecurityAttributes
                                  CREATE_ALWAYS,            // dwCreationDisposition,
                                  FILE_ATTRIBUTE_NORMAL,    // dwFlagsAndAttributes
                                  NULL);                    // hTemplateFile
        if (NULL != hFile)
        {
            HANDLE hProc = GetCurrentProcess();
            DWORD procId = GetCurrentProcessId();
            BOOL res = FALSE;
            if (NULL != exceptionInfo)
            {
                // extended exception info is available
                MINIDUMP_EXCEPTION_INFORMATION extInfo = { 0 };
                extInfo.ThreadId = GetCurrentThreadId();
                extInfo.ExceptionPointers = exceptionInfo;
                extInfo.ClientPointers = TRUE;
                res = MiniDumpWriteDump(hProc, procId, hFile, MiniDumpNormal, &extInfo, NULL, NULL);
            }
            else
            {
                // extended exception info is not available
                res = MiniDumpWriteDump(hProc, procId, hFile, MiniDumpNormal, NULL, NULL, NULL);
            }
            CloseHandle(hFile);
            return true;
        }
    }
#endif
    return false;
}

//------------------------------------------------------------------------------
/**
*/
String
Win32MiniDump::BuildMiniDumpFilename()
{
    String dumpFilename;

    // get our module filename directly from windows
    TCHAR buf[512];
    Memory::Clear(buf, sizeof(buf));
    DWORD numBytes = GetModuleFileName(NULL, buf, sizeof(buf) - 1);
    if (numBytes > 0)
    {
        String modulePath(buf);
        String moduleName = modulePath.ExtractFileName();
        moduleName.StripFileExtension();
        modulePath = modulePath.ExtractToLastSlash();

        // get the current calender time
        SYSTEMTIME t;
        ::GetLocalTime(&t);
        String timeStr;
        timeStr.Format("%04d-%02d-%02d_%02d-%02d-%02d", t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond);
        
        // build the dump filename
        dumpFilename.Format("%s%s_%s.dmp", modulePath.AsCharPtr(), moduleName.AsCharPtr(), timeStr.AsCharPtr());
    }
    return dumpFilename;
}

//------------------------------------------------------------------------------
/**
    Exception handler function called back by Windows when something
    unexpected happens.
*/
LONG WINAPI
Win32MiniDump::ExceptionCallback(EXCEPTION_POINTERS* exceptionInfo)
{
    Win32MiniDump::WriteMiniDumpInternal(exceptionInfo);
    return EXCEPTION_CONTINUE_SEARCH;
}

} // namespace Debug

#endif