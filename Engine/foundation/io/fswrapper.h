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
#pragma once
//------------------------------------------------------------------------------
/**
    @class IO::FSWrapper
    
    This is an internal IO class used to wrap platform specific
    filesystem access into a generic class. To port the filesystem code
    to a new platform all that has to be done is to write a new 
    FSWrapper class.
*/
#if (__WIN32__ || __XBOX360__)
#include "io/win360/win360fswrapper.h"
namespace IO
{
class FSWrapper : public Win360::Win360FSWrapper
{ };
}
#elif __WII__
#include "io/wii/wiifswrapper.h"
namespace IO
{
class FSWrapper : public Wii::WiiFSWrapper
{ };
}
#elif __PS3__
#include "io/ps3/ps3fswrapper.h"
namespace IO
{
class FSWrapper : public PS3::PS3FSWrapper
{ };
}
#elif __OSX__
#include "io/osx/osxfswrapper.h"
namespace IO
{
class FSWrapper : public OSX::OSXFSWrapper
{ };
}
#elif __ANDROID__
#include "io/android/androidfswrapper.h"
namespace IO
{
class FSWrapper : public Android::AndroidFSWrapper
{

};
}
#else
#error "FSWrapper class not implemented on this platform!"
#endif
//------------------------------------------------------------------------------


