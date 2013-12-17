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

#if WIN32

#include "stdneb.h"
#include "system/win32/win32systeminfo.h"

namespace Win32
{

//------------------------------------------------------------------------------
/**
*/
Win32SystemInfo::Win32SystemInfo()
{
    this->platform = Win32;

    // get runtime-info from Windows
    SYSTEM_INFO sysInfo;
    ::GetSystemInfo(&sysInfo);    
    switch (sysInfo.wProcessorArchitecture)
    {
        case PROCESSOR_ARCHITECTURE_AMD64:  this->cpuType = X86_64; break;
        case PROCESSOR_ARCHITECTURE_INTEL:  this->cpuType = X86_32; break;
        default:                            this->cpuType = UnknownCpuType; break;
    }
    this->numCpuCores = sysInfo.dwNumberOfProcessors;
    this->pageSize = sysInfo.dwPageSize;
}

} // namespace Win32

#endif