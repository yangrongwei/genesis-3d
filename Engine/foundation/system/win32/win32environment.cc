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
#include "system/win32/win32environment.h"

namespace System
{
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
bool
Win32Environment::Exists(const String& envVarName)
{
    char buf[256];
    DWORD result = ::GetEnvironmentVariable(envVarName.AsCharPtr(), buf, sizeof(buf));
    if (0 == result)
    {
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
/**
*/
String
Win32Environment::Read(const String& envVarName)
{
    String retval;
    char buf[256];
    DWORD result = ::GetEnvironmentVariable(envVarName.AsCharPtr(), buf, sizeof(buf));
    
    // error?
    if (0 == result)
    {
        n_error("Win32Environment::Read: failed to read env variable '%s'!", envVarName.AsCharPtr());
    }
    else if (result >= sizeof(buf))
    {
        // buffer overflow?
        char* dynBuf = (char*) Memory::Alloc(Memory::ScratchHeap, result);
        DWORD dynResult = ::GetEnvironmentVariable(envVarName.AsCharPtr(), buf, sizeof(buf));
        n_assert(0 != dynResult);
        retval = dynBuf;
        Memory::Free(Memory::ScratchHeap, dynBuf);
        dynBuf = 0;
    }
    else
    {
        // all ok
        retval = buf;
    }
    return retval;
}

} // namespace System

#endif