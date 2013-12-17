/****************************************************************************
Copyright (c) 2007,Radon Labs GmbH
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
#ifndef __inputserver_H__
#define __inputserver_H__

#include "core/singleton.h"
#if __WIN32__
#include "input/win32/win32inputserver.h"
namespace Input
{
class InputServer : public Win32Input::Win32InputServer
{
    __DeclareClass(InputServer);
	__DeclareImageSingleton(InputServer);
public:
    /// constructor
    InputServer();
    /// destructor
    virtual ~InputServer();

	

private:
	
};
}
#elif __XBOX360__
#include "input/xbox360/xbox360inputserver.h"
namespace Input
{
class InputServer : public Xbox360::Xbox360InputServer
{
    __DeclareClass(InputServer);
public:
    /// constructor
    InputServer();
    /// destructor
    virtual ~InputServer();
};
}
#elif __WII__
#include "input/wii/wiiinputserver.h"
namespace Input
{
class InputServer : public Wii::WiiInputServer
{
    __DeclareClass(InputServer);
public:
    /// constructor
    InputServer();
    /// destructor
    virtual ~InputServer();
};
}
#elif __PS3__
#include "input/ps3/ps3inputserver.h"
namespace Input
{
class InputServer : public PS3::PS3InputServer
{
    __DeclareClass(InputServer);
public:
    /// constructor
	InputServer();
    /// destructor
	virtual ~InputServer();
};
}

#elif	 __ANDROID__
#include "input/android/androidinputserver.h"
namespace Input
{
	class InputServer : public AndroidInput::AndroidInputServer
	{
		__DeclareClass(InputServer);
		__DeclareImageSingleton(InputServer);
	public:
		/// constructor
		InputServer();
		/// destructor
		virtual ~InputServer();
	};
}

#elif	 __OSX__
#include "input/osx/osxinputserver.h"
namespace Input
{
	class InputServer : public OSXInput::OSXInputServer
	{
		__DeclareClass(InputServer);
		__DeclareImageSingleton(InputServer);
	public:
		/// constructor
		InputServer();
		/// destructor
		virtual ~InputServer();
	};
}

#else
#error "InputServer class not implemented on this platform!"
#endif
//------------------------------------------------------------------------------






#endif // __inputserver_H__




   