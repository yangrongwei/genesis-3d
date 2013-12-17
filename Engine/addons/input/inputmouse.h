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
#ifndef __inputmouse_H__
#define __inputmouse_H__

#if __WIN32__
#include "input/win32/win32inputmouse.h"
namespace Input
{
class InputMouse : public Win32Input::Win32InputMouse
{
    __DeclareClass(InputMouse);
};
}
#elif __XBOX360__
#include "input/xbox360/xbox360mouse.h"
namespace Input
{
class InputMouse : public Xbox360::Xbox360Mouse
{
    __DeclareClass(InputMouse);
};
}
#elif __WII__
#include "input/wii/wiimouse.h"
namespace Input
{
class InputMouse : public Wii::WiiMouse
{
    __DeclareClass(InputMouse);
};
}
#elif __PS3__
#include "input/base/mousebase.h"
namespace Input
{
class InputMouse : public Base::MouseBase
{
    __DeclareClass(InputMouse);
};
}
#elif __ANDROID__
#include "input/base/inputmousebase.h"
namespace Input
{
	class InputMouse : public Input::InputMouseBase
	{
		__DeclareClass(InputMouse);
	};
}
#elif __OSX__
#include "input/base/inputmousebase.h"
namespace Input
{
	class InputMouse : public Input::InputMouseBase
	{
		__DeclareClass(InputMouse);
	};
}
#else
#error "Mouse class not implemented on this platform!"
#endif
//------------------------------------------------------------------------------





#endif // __inputmouse_H__




