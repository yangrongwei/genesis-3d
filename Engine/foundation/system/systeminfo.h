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
#pragma once
//------------------------------------------------------------------------------
/**
    @class System::SystemInfo
    
    Provides information about the host system.
*/
#if __WIN32__
#include "system/win32/win32systeminfo.h"
namespace System
{
class SystemInfo : public Win32::Win32SystemInfo {};
}
#elif __XBOX360__
#include "system/xbox360/xbox360systeminfo.h"
namespace System
{
class SystemInfo : public Xbox360::Xbox360SystemInfo {};
}
#elif __WII__
#include "system/wii/wiisysteminfo.h"
namespace System
{
class SystemInfo : public Wii::WiiSystemInfo {};
}
#elif __PS3__
#include "system/ps3/ps3systeminfo.h"
namespace System
{
class SystemInfo : public PS3::PS3SystemInfo {};
}
#elif __ANDROID__
#include "system/android/androidsysteminfo.h"
namespace System
{
	class SystemInfo : public Android::AndroidSystemInfo {};
}
#elif __OSX__
#include "system/osx/osxsysteminfo.h"
namespace System
{
	class SystemInfo : public OSX::OSXSystemInfo {};
}
#else
#error "System::SystemInfo not implemented on this platform!"
#endif
//------------------------------------------------------------------------------
