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
#include "input/inputserver.h"

namespace Input
{
#if __WIN32__
__ImplementClass(Input::InputServer, 'INPS', Win32Input::Win32InputServer);
__ImplementImageSingleton(Input::InputServer);
#elif __XBOX360__
// FIXME!
__ImplementClass(Input::InputServer, 'INPS', Xbox360::Xbox360InputServer);
__ImplementImageSingleton(Input::InputServer);
#elif __WII__
__ImplementClass(Input::InputServer, 'INPS', Wii::WiiInputServer);
__ImplementImageSingleton(Input::InputServer);
#elif __PS3__
__ImplementClass(Input::InputServer, 'INPS', PS3::PS3InputServer);
__ImplementImageSingleton(Input::InputServer);
#elif __ANDROID__
__ImplementClass(Input::InputServer, 'INPS', AndroidInput::AndroidInputServer);
__ImplementImageSingleton(Input::InputServer);
#elif __OSX__
__ImplementClass(Input::InputServer, 'INPS', OSXInput::OSXInputServer);
__ImplementImageSingleton(Input::InputServer);
#else
#error "InputServer class not implemented on this platform!"
#endif

//------------------------------------------------------------------------------
/**
*/
InputServer::InputServer()
{
	__ConstructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
InputServer::~InputServer()
{
	__DestructImageSingleton;
}



} // namespace Input
