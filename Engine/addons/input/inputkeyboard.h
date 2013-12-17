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
#ifndef __inputkeyboard_H__
#define __inputkeyboard_H__

#if __WIN32__
#include "input/base/inputkeyboardbase.h"
namespace Input
{
class InputKeyboard : public Input::InputKeyboardBase
{
    __DeclareClass(InputKeyboard);
};
}
#elif __XBOX360__
#include "input/xbox360/xbox360keyboard.h"
namespace Input
{
class InputKeyboard : public Xbox360::Xbox360Keyboard
{
    __DeclareClass(InputKeyboard);
};
}
#elif __WII__
#include "input/wii/wiikeyboard.h"
namespace Input
{
class InputKeyboard : public Wii::WiiKeyboard
{
    __DeclareClass(InputKeyboard);
};
}
#elif __PS3__
#include "input/base/keyboardbase.h"
namespace Input
{
class InputKeyboard : public Base::KeyboardBase
{
    __DeclareClass(InputKeyboard);
};
}
#elif __ANDROID__
#include "input/base/inputkeyboardbase.h"
namespace Input
{
	class InputKeyboard : public Input::InputKeyboardBase
	{
		__DeclareClass(InputKeyboard);
	};
}
#elif __OSX__
#include "input/base/inputkeyboardbase.h"
namespace Input
{
	class InputKeyboard : public Input::InputKeyboardBase
	{
		__DeclareClass(InputKeyboard);
	};
}
#else
#error "Keyboard class not implemented on this platform!"
#endif
//------------------------------------------------------------------------------







#endif // __inputkeyboard_H__



