#pragma once
/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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

#include "core/config.h"
#if __WIN32__
#include "util/win32/win32guid.h"
namespace Util
{
typedef Win32::Win32Guid Guid;
}
#elif __XBOX360__
#include "util/xbox360/xbox360guid.h"
namespace Util
{
typedef Xbox360::Xbox360Guid Guid;
}
#elif __WII__
#include "util/wii/wiiguid.h"
namespace Util
{
typedef Wii::WiiGuid Guid;
}
#elif __PS3__
#include "util/ps3/ps3guid.h"
namespace Util
{
typedef PS3::PS3Guid Guid;
}
#elif __OSX__
#include "util/osx/osxguid.h"
namespace Util
{
typedef OSX::OSXGuid Guid;
}
#elif __ANDROID__
#include "util/android/androidguid.h"
namespace Util
{
typedef Android::AndroidGuid Guid;
}
#else
#error "Util::Guid not implemented on this platform!"
#endif
//------------------------------------------------------------------------------
    