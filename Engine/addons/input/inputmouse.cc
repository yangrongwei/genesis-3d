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
#include "input/input_stdneb.h"
#include "input/inputmouse.h"
#if __WIN32__
namespace Input
{
__ImplementClass(Input::InputMouse, 'MOUS', Win32Input::Win32InputMouse);
}
#elif __XBOX360__
namespace Input
{
__ImplementClass(Input::InputMouse, 'MOUS', Xbox360::Xbox360Mouse);
}
#elif __WII__
namespace Input
{
__ImplementClass(Input::InputMouse, 'MOUS', Wii::WiiMouse);
}
#elif __PS3__
namespace Input
{
__ImplementClass(Input::InputMouse, 'MOUS', Base::MouseBase);
}
#elif __ANDROID__
namespace Input
{
	__ImplementClass(Input::InputMouse, 'MOUS', Input::InputMouseBase);
}
#elif __OSX__
namespace Input
{
	__ImplementClass(Input::InputMouse, 'MOUS', Input::InputMouseBase);
}
#else
#error "Mouse class not implemented on this platform!"
#endif
