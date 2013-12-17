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
    @class Core::SysFunc
    
    Wrap some platform specific low-level functions.
*/
#include "core/config.h"
#if __WIN32__
#include "core/win32/win32sysfunc.h"
namespace Core
{
class SysFunc : public Win32::SysFunc
{
    // empty
};
} // namespace Core
#elif __XBOX360__
#include "core/xbox360/xbox360sysfunc.h"
namespace Core
{
class SysFunc : public Xbox360::SysFunc
{
    // empty
};
}
#elif __WII__
#include "core/wii/wiisysfunc.h"
namespace Core
{
class SysFunc : public Wii::SysFunc
{
    // empty
};
} // namespace Core
#elif __PS3__
#include "core/ps3/ps3sysfunc.h"
namespace Core
{
class SysFunc : public PS3::SysFunc
{
    // empty
};
} // namespace Core;
#elif __OSX__
#include "core/osx/osxsysfunc.h"
namespace Core
{
class SysFunc : public OSX::SysFunc
{
    // empty
};
} // namespace Core
#elif __ANDROID__
#include "core/android/androidsysfunc.h"
namespace Core
{
class SysFunc : public Android::SysFunc
{

};
}
#else
#error "Core::SysFunc not implemented on this platform!"
#endif
//------------------------------------------------------------------------------
