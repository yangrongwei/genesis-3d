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
#ifndef __inputwindowsource_H__
#define __inputwindowsource_H__

#include "core/config.h"

#if __WIN32__

#include "input/win32/win32inputwindowsource.h"
namespace Input
{
	class InputWindowSource : public Win32Input::Win32InputWindowSource
	{
		__DeclareClass(InputWindowSource);
	};
}
#elif __ANDROID__
#include "input/android/androidinputsource.h"
namespace Input
{
	class InputWindowSource : public AndroidInput::AndroidInputSource
	{
		__DeclareClass(InputWindowSource);
	};
}
#elif __OSX__
#include "input/osx/osxinputsource.h"
namespace Input
{
	class InputWindowSource : public OSXInput::OSXInputSource
	{
		__DeclareClass(InputWindowSource);
	};
}
#endif




#endif // __inputwindowsource_H__













