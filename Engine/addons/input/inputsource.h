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
#ifndef __InputSource_H__
#define __InputSource_H__
#include "core/refcounted.h"
#include "input/inputevent.h"
namespace Input
{
	class InputServerBase;
}

namespace Input
{
	class InputSource: public Core::RefCounted
	{
		__DeclareClass(InputSource);
	public:
		/// constructor
		InputSource();
		
		/// destructor
		virtual ~InputSource();

		/// return true if open
		bool IsOpen(void) const;

		/// called when the input server Open
		virtual void Open(const GPtr<InputServerBase>& inputServer );

		/// called whem the input server Close
		virtual void Close(void);

		/// called when the input server BeginFrame. Maybe Create InputEvent there
		virtual void BeginFrame(void);
		
		void SetKeyDown(Util::Array< Input::InputEvent >& inputEventList,
			Input::InputEvent& inputEvent, 
			Input::InputKey::Code keyCode,
			void* wParam);

		void SetKeyUp(Util::Array< Input::InputEvent >& inputEventList,
			Input::InputEvent& inputEvent, 
			Input::InputKey::Code keyCode);

		void SetChar(Util::Array< Input::InputEvent >& inputEventList,
			Input::InputEvent& inputEvent, 
			Input::Char ch);


		int VirtualKeyToText(void* _virtualKey);
	protected:
		friend class Input::InputServerBase;

		bool mIsOpen;
		GPtr<InputServerBase> mInputServer;

	};
//------------------------------------------------------------------------
	inline 
	bool 
	InputSource::IsOpen() const
	{
		return mIsOpen;
	}
	inline void InputSource::SetKeyDown(Util::Array< Input::InputEvent >& inputEventList,
		Input::InputEvent& inputEvent, 
		Input::InputKey::Code keyCode,
		void* wParam)
	{
		
		inputEvent.SetType(InputEvent::KeyDown);
		inputEvent.SetKey(keyCode);
		inputEvent.SetChar(VirtualKeyToText(wParam));
		inputEventList.Append(inputEvent);

	}

	inline void InputSource::SetKeyUp(Util::Array< Input::InputEvent >& inputEventList,
		Input::InputEvent& inputEvent, 
		Input::InputKey::Code keyCode)
	{
		inputEvent.SetType(InputEvent::KeyUp);
		inputEvent.SetKey(keyCode);
		inputEventList.Append(inputEvent);
	}

	inline void InputSource::SetChar(Util::Array< Input::InputEvent >& inputEventList,
		Input::InputEvent& inputEvent, 
		Input::Char ch)
	{
		inputEvent.SetType(InputEvent::Character);
		inputEvent.SetChar(ch);
		inputEventList.Append(inputEvent);
	}
}












#endif // __InputSource_H__
