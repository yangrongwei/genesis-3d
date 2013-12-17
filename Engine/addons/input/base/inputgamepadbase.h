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
#ifndef __inputgamepadbase_H__
#define __inputgamepadbase_H__

#include "input/inputhandler.h"
#include "threading/criticalsection.h"
#include "threading/thread.h"

//------------------------------------------------------------------------------
namespace Input
{
	class InputGamePadBase : public Input::InputHandler
	{
		__DeclareClass(InputGamePadBase);
	public:
		/// gamepad buttons
		enum Button
		{
			DPadUpButton = 0,           // all platforms
			DPadDownButton,             // all platforms        
			DPadLeftButton,             // all platforms
			DPadRightButton,            // all platforms
			StartButton,                // all platforms
			BackButton,                 // Xbox360
			LeftThumbButton,            // Xbox360, PS3: L3
			RightThumbButton,           // Xbox360, PS3: R3
			LeftShoulderButton,         // Xbox360, PS3: L1, Wii: ClassicController ZL
			RightShoulderButton,        // Xbox360, PS3: R1, Wii: ClassicController ZR

			AButton,                    // Xbox360: A, Wii: A/a, PS3: Cross
			BButton,                    // Xbox360: B, Wii: b(pad), PS3: Circle
			XButton,                    // Xbox360: X, Wii: x(pad), PS3: Square
			YButton,                    // Xbox360: Y, Wii: y(pad), PS3: Triangle

			// Wii specific buttons
			HomeButton,                 // Xbox360: /, Wii: Home, PS3: /
			PlusButton,                 // Xbox360: /, Wii: +, PS3: /
			MinusButton,                // Xbox360: /, Wii: -, PS3: /
			OneButton,                  // Xbox360: /, Wii: 1, PS3: /
			TwoButton,                  // Xbox360: /, Wii: 2, PS3: /
			ZButton,                    // Xbox360: /, Wii: Z(Nunchuk), PS3: /
			CButton,                    // Xbox360: /, Wii: C(Nunchuk), PS3: /

			// PS3 specific buttons
			SelectButton,				// Xbox360: /, Wii: /, PS3: Select

			NumButtons,
			InvalidButton,


			// PS3 aliases !!! MUST BE after NumButtons & InvalidButton !!!
			CrossButton = AButton,
			CircleButton = BButton,
			SquareButton = XButton,
			TriangleButton = YButton,
			L1Button = LeftShoulderButton,
			R1Button = RightShoulderButton,
			L3Button = LeftThumbButton,
			R3Button = RightThumbButton,
		};

		/// gamepad axis
		enum Axis
		{
			// general axi
			LeftTriggerAxis = 0,    // 0.0f .. 1.0f
			RightTriggerAxis,       // 0.0f .. 1.0f
			LeftThumbXAxis,         // -1.0f .. 1.0f
			LeftThumbYAxis,         // -1.0f .. 1.0f
			RightThumbXAxis,        // -1.0f .. 1.0f
			RightThumbYAxis,        // -1.0f .. 1.0f

			NumAxes,
			InvalidAxis,
		};

		/// constructor
		InputGamePadBase();
		/// destructor
		virtual ~InputGamePadBase();

		/// convert button code to string
		static Util::String ButtonAsString(Button btn);
		/// convert axis to string
		static Util::String AxisAsString(Axis a);

		/// return true if this game pad is currently connected
		bool IsConnected() const;
		/// set player index -> TODO make threadsafe
		void SetPlayerIndex(IndexT i);
		/// get the player index of this game pad
		IndexT GetPlayerIndex() const;
		/// get maximum number of players
		static SizeT GetMaxNumPlayers();

		/// return true if a button is currently pressed
		bool ButtonPressed(Button btn) const;
		/// return true if button was down at least once in current frame
		bool ButtonDown(Button btn) const;
		/// return true if button was up at least once in current frame
		bool ButtonUp(Button btn) const;
		/// get current axis value
		float GetAxisValue(Axis axis) const;

		/// set low-frequency vibration effect (0.0f .. 1.0f)
		void SetLowFrequencyVibrator(float f);
		/// get low-frequency vibration
		float GetLowFrequencyVibrator() const;
		/// set high-frequency vibration effect (0.0f .. 1.0f)
		void SetHighFrequencyVibrator(float f);
		/// get high-frequency vibration
		float GetHighFrequencyVibrator() const;

		/// get current state as an array of input events (override in subclass!)
		Util::Array<Input::InputEvent> GetStateAsInputEvents() const;

	protected:   
		/// called when the handler is attached to the input server
		virtual void OnAttach(const GPtr<InputServerBase>& inputServer);
		/// reset the input handler
		virtual void OnReset();

		struct ButtonState
		{
		public:
			/// constructor
			ButtonState() : pressed(false), down(false), up(false) {};

			bool pressed;
			bool down;
			bool up;
		};

		IndexT playerIndex;
		bool isConnected;
		Util::FixedArray<ButtonState> buttonStates;
		Util::FixedArray<float> axisValues;
		bool vibratorsDirty;
		float lowFreqVibrator;
		float highFreqVibrator;
		Threading::CriticalSection critSect;
		Threading::ThreadId creatorThreadId;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputGamePadBase::IsConnected() const
	{
		n_assert2(creatorThreadId == Threading::Thread::GetMyThreadId(), "IsConnected can't be called from any thread but the creator thread!");
		return this->isConnected;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	void
	InputGamePadBase::SetPlayerIndex(IndexT i)
	{
		n_assert(i < this->GetMaxNumPlayers());
		this->playerIndex = i;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	IndexT
	InputGamePadBase::GetPlayerIndex() const
	{
		return this->playerIndex;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	SizeT
	InputGamePadBase::GetMaxNumPlayers()
	{
		return 4;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputGamePadBase::ButtonPressed(Button btn) const
	{
		n_assert2(creatorThreadId == Threading::Thread::GetMyThreadId(), "ButtonPressed can't be called from any thread but the creator thread!");
		return this->buttonStates[btn].pressed;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputGamePadBase::ButtonDown(Button btn) const
	{
		n_assert2(creatorThreadId == Threading::Thread::GetMyThreadId(), "ButtonDown can't be called from any thread but the creator thread!");
		return this->buttonStates[btn].down;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputGamePadBase::ButtonUp(Button btn) const
	{
		n_assert2(creatorThreadId == Threading::Thread::GetMyThreadId(), "ButtonUp can't be called from any thread but the creator thread!");
		return this->buttonStates[btn].up;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	float
	InputGamePadBase::GetAxisValue(Axis axis) const
	{
		n_assert2(creatorThreadId == Threading::Thread::GetMyThreadId(), "GetAxisValue can't be called from any thread but the creator thread!");
		return this->axisValues[axis];
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	void
	InputGamePadBase::SetLowFrequencyVibrator(float f)
	{        
		critSect.Enter();
		this->vibratorsDirty = true;
		this->lowFreqVibrator = Math::n_clamp(f, 0.0f, 1.0f);
		critSect.Leave();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	float
	InputGamePadBase::GetLowFrequencyVibrator() const
	{                    
		critSect.Enter();
		float result = this->lowFreqVibrator;
		critSect.Leave();
		return result;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	void
	InputGamePadBase::SetHighFrequencyVibrator(float f)
	{   
		critSect.Enter();
		this->vibratorsDirty = true;
		this->highFreqVibrator = Math::n_clamp(f, 0.0f, 1.0f);;
		critSect.Leave();
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline
	float
	InputGamePadBase::GetHighFrequencyVibrator() const
	{   
		critSect.Enter();
		float result = this->highFreqVibrator;
		critSect.Leave();
		return result;
	}

} // namespace Input
//------------------------------------------------------------------------------








#endif // __inputgamepadbase_H__



