/****************************************************************************
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
#ifndef __inputgamepad_H__
#define __inputgamepad_H__


#if (__WIN32__ || __XBOX360__)
#include "input/xinput/xinputgamepad.h"
namespace Input
{
class InputGamePad : public XInput::XInputGamePad
{
    __DeclareClass(InputGamePad);
};
}
#elif (__WII__)
#include "input/wii/wiimote.h"
namespace Input
{
class InputGamePad : public Wii::Wiimote
{
    __DeclareClass(InputGamePad);
};
}
#elif __PS3__
#include "input/ps3/ps3gamepad.h"
namespace Input
{
class InputGamePad : public PS3::PS3GamePad
{
    __DeclareClass(InputGamePad);
public:
	virtual ~InputGamePad() {}
};
}
#elif __ANDROID__
#include "input/android/androidinputgamepad.h"
namespace Input
{
	class InputGamePad : public AndroidInput::AndoidInputGamePad
	{
		__DeclareClass(InputGamePad);
	public:
		virtual ~InputGamePad() {}
	};
}
#elif __OSX__
#include "input/osx/osxinputgamepad.h"
namespace Input
{
	class InputGamePad : public OSXInput::OSXInputGamePad
	{
		__DeclareClass(InputGamePad);
	public:
		virtual ~InputGamePad() {}
	};
}
#else
#error "GamePad class not implemented on this platform!"
#endif
//------------------------------------------------------------------------------





#endif // __inputgamepad_H__




