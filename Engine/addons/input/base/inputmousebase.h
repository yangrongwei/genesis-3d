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
#ifndef __inputmousebase_H__
#define __inputmousebase_H__

#include "input/inputhandler.h"
#include "input/inputeventtypes.h"

//------------------------------------------------------------------------------
namespace Input
{
	class InputMouseBase : public Input::InputHandler
	{
		__DeclareClass(InputMouseBase);
	public:
		/// constructor
		InputMouseBase();
		/// destructor
		virtual ~InputMouseBase();

		/// capture input to this event handler
		virtual void BeginCapture();
		/// end input capturing to this event handler
		virtual void EndCapture();

		/// return true if button is currently pressed
		bool ButtonPressed(Input::InputMouseButton::Code btn) const;
		/// return true if button was down at least once in current frame
		bool ButtonDown(Input::InputMouseButton::Code btn) const;
		/// return true if button was up at least once in current frame
		bool ButtonUp(Input::InputMouseButton::Code btn) const;
		/// return true if a button has been double clicked
		bool ButtonDoubleClicked(Input::InputMouseButton::Code btn) const;
		/// return true if mouse wheel rotated forward
		bool WheelForward() const;
		/// return true if mouse wheel rotated backward
		bool WheelBackward() const;
		/// get current absolute mouse position (in pixels)
		const Math::float2& GetPixelPosition() const;
		/// get current screen space mouse position (0.0 .. 1.0)
		const Math::float2& GetScreenPosition() const;
		/// get mouse movement
		const Math::float2& GetMovement() const;

		int GetCurrentEventCount() const;

		MouseButtonEvent GetCurrentEvent(int index) const;

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
		/// update mouse position members
		void UpdateMousePositions(const Math::float2& pixelPos, const Math::float2& screenPos);

		struct ButtonState
		{
		public:
			/// constructor
			ButtonState() : pressed(false), down(false), up(false), doubleClicked(false) {};

			bool pressed;
			bool down;
			bool up;
			bool doubleClicked;
		};
		Util::Array<MouseButtonEvent> currentEvents;
		Util::FixedArray<ButtonState> buttonStates;
		Math::float2 beginFramePixelPosition;
		Math::float2 beginFrameScreenPosition;
		Math::float2 pixelPosition;
		Math::float2 screenPosition;
		Math::float2 movement;
		bool wheelForward;
		bool wheelBackward;
		bool initialMouseMovement;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool 
	InputMouseBase::ButtonPressed(Input::InputMouseButton::Code btn) const
	{
		return this->buttonStates[btn].pressed;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputMouseBase::ButtonDown(Input::InputMouseButton::Code btn) const
	{
		return this->buttonStates[btn].down;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputMouseBase::ButtonUp(Input::InputMouseButton::Code btn) const
	{
		return this->buttonStates[btn].up;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputMouseBase::ButtonDoubleClicked(Input::InputMouseButton::Code btn) const
	{
		return this->buttonStates[btn].doubleClicked;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	const Math::float2&
	InputMouseBase::GetPixelPosition() const
	{
		return this->pixelPosition;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	const Math::float2&
	InputMouseBase::GetScreenPosition() const
	{
		return this->screenPosition;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	const Math::float2&
	InputMouseBase::GetMovement() const
	{
		return this->movement;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputMouseBase::WheelForward() const
	{
		return this->wheelForward;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputMouseBase::WheelBackward() const
	{
		return this->wheelBackward;
	}

	inline
	int
	InputMouseBase::GetCurrentEventCount() const
	{
		return currentEvents.Size();
	}

	inline
	MouseButtonEvent
	InputMouseBase::GetCurrentEvent(int index) const
	{
		return currentEvents[index];
	}

} // namespace Input
//------------------------------------------------------------------------------








#endif // __inputmousebase_H__

