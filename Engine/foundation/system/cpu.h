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
//------------------------------------------------------------------------------
/**
    @class System::Cpu
    
    Provides information about the system's CPU(s).
*/
#if __WIN32__
#include "system/win32/win32cpu.h"
namespace System
{
typedef Win32::Win32Cpu Cpu;
}
#elif __XBOX360__
#include "system/xbox360/xbox360cpu.h"
namespace System
{
typedef Xbox360::Xbox360Cpu Cpu;
}
#elif __WII__
#include "system/wii/wiicpu.h"
namespace System
{
typedef Wii::WiiCpu Cpu;
}
#elif __PS3__
#include "system/ps3/ps3cpu.h"
namespace System
{
typedef PS3::PS3Cpu Cpu;
}
#elif __OSX__
#include "system/osx/osxcpu.h"
namespace System
{
typedef OSX::OSXCpu Cpu;
}
#elif __ANDROID__
#include "system/android/androidcpu.h"
namespace System
{
typedef Android::AndroidCpu Cpu;
}
#else
#error "System::Cpu not implemented on this platform!"
#endif
//------------------------------------------------------------------------------
    