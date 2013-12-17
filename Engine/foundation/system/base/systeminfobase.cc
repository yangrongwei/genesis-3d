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
#include "system/base/systeminfobase.h"

namespace Base
{
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
SystemInfoBase::SystemInfoBase() :
    platform(UnknownPlatform),
    cpuType(UnknownCpuType),
    numCpuCores(0),
    pageSize(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
String
SystemInfoBase::PlatformAsString(Platform p)
{
    switch (p)
    {
        case Win32:     return "win32";
        case Xbox360:   return "xbox360";
        case Wii:       return "wii";
        case PS3:       return "ps3";
		case Android:   return "android";
        default:        return "unknownplatform";
    }
}

//------------------------------------------------------------------------------
/**
*/
String
SystemInfoBase::CpuTypeAsString(CpuType c)
{
    switch (c)
    {
        case X86_32:            return "x86_32";
        case X86_64:            return "x86_64";
        case PowerPC_Xbox360:   return "powerpc_xbox360";
        case PowerPC_PS3:       return "powerpc_ps3";
        case PowerPC_Wii:       return "powerpc_wii";
		case ARM:               return "arm";
        default:                return "unknowncputype";
    }
}

} // namespace Base