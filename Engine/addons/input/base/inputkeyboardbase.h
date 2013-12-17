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
#ifndef __inputkeyboardbase_H__
#define __inputkeyboardbase_H__

#include "input/inputhandler.h"
#include "input/inputeventtypes.h"

//------------------------------------------------------------------------------
namespace Input
{


	class InputKeyboardBase : public Input::InputHandler
	{
		__DeclareClass(InputKeyboardBase);
	public:

		/// constructor
		InputKeyboardBase();
		/// destructor
		virtual ~InputKeyboardBase();

		/// capture input to this event handler
		virtual void BeginCapture();
		/// end input capturing to this event handler
		virtual void EndCapture();

		/// return true if a key is currently pressed
		bool KeyPressed(Input::InputKey::Code keyCode) const;
		/// return true if key was down at least once in current frame
		bool KeyDown(Input::InputKey::Code keyCode) const;
		/// return true if key was up at least once in current frame
		bool KeyUp(Input::InputKey::Code keyCode) const;
		/// get character input in current frame
		const Util::String& GetCharInput() const;

		int GetCurrentEventCount() const;

		KeyEvent GetCurrentEvent(int index) const;

	protected:
		/// called when the handler is attached to the input server
		virtual void OnAttach(const GPtr<InputServerBase>& inputServer);
		/// called on InputServer::BeginFrame()
		virtual void OnBeginFrame();
		/// called when an input event should be processed
		virtual bool OnEvent(const Input::InputEvent& inputEvent);
		/// called when input handler obtains capture
		virtual void OnObtainCapture();
		/// called when input handler looses capture
		virtual void OnReleaseCapture();
		/// reset the input handler
		virtual void OnReset(); 


	private:
		class KeyState
		{
		public:
			/// constructor
			KeyState() : pressed(false), down(false), up(false) {};

			bool pressed;       // currently pressed
			bool down;          // was down this frame
			bool up;            // was up this frame
		};
		Util::FixedArray<KeyState> keyStates;
		Util::Array<KeyEvent> keyEventCache;
		Util::String charInput;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputKeyboardBase::KeyPressed(Input::InputKey::Code keyCode) const
	{
		return this->keyStates[keyCode].pressed;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputKeyboardBase::KeyDown(Input::InputKey::Code keyCode) const
	{
		return this->keyStates[keyCode].down;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputKeyboardBase::KeyUp(Input::InputKey::Code keyCode) const
	{
		return this->keyStates[keyCode].up;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	const Util::String&
	InputKeyboardBase::GetCharInput() const
	{
		return this->charInput;
	}

	inline
	int
	InputKeyboardBase::GetCurrentEventCount() const
	{
		return keyEventCache.Size();
	}

	inline
	KeyEvent
	InputKeyboardBase::GetCurrentEvent(int index) const
	{
		return keyEventCache[index];
	}

} // namespace Input
//------------------------------------------------------------------------------



#endif // __inputkeyboardbase_H__



