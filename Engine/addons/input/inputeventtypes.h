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
#ifndef __inputeventtypes_H__
#define __inputeventtypes_H__
#include "input/inputevent.h"
#include "input/inputkey.h"
#include "input/inputmousebutton.h"
namespace Input
{

	struct EventBase
	{
		InputEvent::Type event;
		inline EventBase()
			:event(InputEvent::InvalidType)
		{

		}
		inline EventBase(InputEvent::Type event)
		{
			this->event = event;
		}
	};

	struct KeyEvent : public EventBase
	{
		InputKey::Code key;
		inline KeyEvent()
			:key(InputKey::InvalidKey)
		{

		}

		inline KeyEvent(InputKey::Code key, InputEvent::Type event)
			:EventBase(event)
		{
			this->key = key;
		}
	};

	struct TouchEvent : public EventBase
	{
		int id;
		inline TouchEvent()
			:id(-1)
		{

		}
		inline TouchEvent(int id, InputEvent::Type event)
			:EventBase(event)
		{
			this->id = id;
		}
	};

	struct MouseButtonEvent : public EventBase
	{
		InputMouseButton::Code button;
		inline MouseButtonEvent()
			:button(InputMouseButton::InvalidMouseButton)
		{
		}
		inline MouseButtonEvent(InputMouseButton::Code button, InputEvent::Type event)
			:EventBase(event)
		{
			this->button = button;
		}
	};

}
#endif //__inputeventtypes_H__