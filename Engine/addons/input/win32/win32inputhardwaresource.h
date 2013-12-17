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
#ifndef __win32inputhardwaresource_H__
#define __win32inputhardwaresource_H__

#include "input/inputsource.h"



namespace Win32Input
{
	class Win32InputHardwareSource: public Input::InputSource
	{
		__DeclareSubClass(Win32InputHardwareSource, Input::InputSource);
	public:
		Win32InputHardwareSource();
		virtual ~Win32InputHardwareSource();

		// @ InputSource::Open()
		virtual void Open(const GPtr<Input::InputServerBase>& inputServer);

		// @ InputSource::Close()
		virtual void Close();

		// @ InputSource::BeginFrame()
		virtual void BeginFrame();

	protected:
		/// setup the DirectInput mouse device for tracking mouse movement 
		bool _OpenDInputMouse();
		/// shutdown the DirectInput mouse device
		void _CloseDInputMouse();
		/// get mouse readings
		void _ReadDInputMouse();

	protected:
		IDirectInput8* mDi8;
		IDirectInputDevice8* mDi8Mouse;
		static const int DInputMouseBufferSize = 16;
	};
}









#endif // __win32inputhardwaresource_H__
