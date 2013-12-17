#pragma once
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

#include "core/config.h"
#if (__WIN32__ || __XBOX360__)
#include "threading/win360/win360interlocked.h"
namespace Threading
{
class Interlocked : public Win360::Win360Interlocked
{ };
}
#elif __WII__
#include "threading/wii/wiiinterlocked.h"
namespace Threading
{
class Interlocked : public Wii::WiiInterlocked
{ };
}
#elif __PS3__
#include "threading/ps3/ps3interlocked.h"
namespace Threading
{
class Interlocked : public PS3::PS3Interlocked
{ };
}
#elif __OSX__
#include "threading/osx/osxinterlocked.h"
namespace Threading
{
class Interlocked : public OSX::OSXInterlocked
{ };
}
#elif __ANDROID__
#include "threading/android/androidInterlocked.h"
namespace Threading
{
	class Interlocked : public Android::AndroidInterlocked
	{ };
}
#else
#error "Threading::Interlocked not implemented on this platform!"
#endif
//------------------------------------------------------------------------------
