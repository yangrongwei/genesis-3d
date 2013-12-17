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
#ifndef __inputserverbase_H__
#define __inputserverbase_H__

#include "core/refcounted.h"
#include "input/inputsource.h"
#include "input/inputpriority.h"
#include "input/inputevent.h"
#include "threading/criticalsection.h"   
#include "threading/thread.h"

namespace Input
{
	class InputMouse;
	class InputKeyboard;
	class InputTouchScreen;
	class InputGamePad;
	class InputHandler;
}    

//------------------------------------------------------------------------------
namespace Input
{
	class InputServerBase : public Core::RefCounted
	{
		__DeclareClass(InputServerBase);
	public:
		/// constructor
		InputServerBase();
		/// destructor
		virtual ~InputServerBase();

		/// set the max number of local players for this application (default is 4)
		void SetMaxNumLocalPlayers(SizeT maxNumLocalPlayers);
		/// get the max number of local players
		SizeT GetMaxNumLocalPlayers() const;
		/// open the input server
		virtual void Open();
		/// close the input server
		virtual void Close();
		/// return true if open
		bool IsOpen() const;
		/// set the quit requested flag
		void SetQuitRequested(bool b);
		/// return true if some subsystem has requested to quit the app (e.g. Alt-F4)
		bool IsQuitRequested() const;
		/// reset input state
		void Reset();
		/// get the default keyboard input handler
		const GPtr<Input::InputKeyboard>& GetDefaultKeyboard() const;
		/// get the default mouse input handler
		const GPtr<Input::InputMouse>& GetDefaultMouse() const;
		/// get default gamepad handler (playerIndex is valid up to MaxNumLocalPlayers)
		GPtr<Input::InputGamePad> GetDefaultGamePad(IndexT playerIndex) const;

		/// attach an input handler
		void AttachInputHandler(Input::InputPriority::Code pri, const GPtr<Input::InputHandler>& inputHandler);
		/// remove an input handler
		void RemoveInputHandler(const GPtr<Input::InputHandler>& inputHandler);

		/// attach a input source 
		void AttachInputSource( const GPtr<Input::InputSource>& inputSource);
		/// remove a input source
		void RemoveInputSource( const GPtr<Input::InputSource>& inputSource);

		/// call before processing window events
		virtual void BeginFrame();
		/// call after processing window events
		virtual void OnFrame();
		/// call at end of frame
		void EndFrame();
		/// put an input event into the handler chain
		void PutEvent(const Input::InputEvent& ie);

		/// clear the current mouse capture (if exists)
		void ClearMouseCapture();
		/// clear the current keyboard capture (if exists)
		void ClearKeyboardCapture();
		/// clear both mouse and keyboard captures
		void ClearCapture();
		/// return the current mouse capture input handler (return invalid ptr if no capture set)
		const GPtr<Input::InputHandler>& GetMouseCaptureHandler() const;
		/// return the current keyboard capture input handler (return invalid ptr if no capture set)
		const GPtr<Input::InputHandler>& GetKeyboardCaptureHandler() const;

		/// only call from InputHandler: capture mouse input to the given input handler
		void ObtainMouseCapture(const GPtr<Input::InputHandler>& inputHandler);
		/// only call from InputHandler: release mouse capture
		void ReleaseMouseCapture(const GPtr<Input::InputHandler>& inputHandler);
		/// only call from InputHandler: capture keyboard input to the given input handler
		void ObtainKeyboardCapture(const GPtr<Input::InputHandler>& inputHandler);
		/// only call from InputHandler: release keyboard capture
		void ReleaseKeyboardCapture(const GPtr<Input::InputHandler>& inputHandler);

	protected:
		bool isOpen;
		bool inBeginFrame;
		bool isQuitRequested;
		int inputHandlersLockCount;
		SizeT maxNumLocalPlayers;
		Util::Array<Util::KeyValuePair<Input::InputPriority::Code,GPtr<Input::InputHandler> > > inputHandlers;
		Util::Array< GPtr<Input::InputSource> > mInputSourceList;
		GPtr<Input::InputHandler> mouseCaptureHandler;
		GPtr<Input::InputHandler> keyboardCaptureHandler;
		GPtr<Input::InputKeyboard> defaultKeyboard;
		GPtr<Input::InputMouse> defaultMouse;
		
		Util::FixedArray<GPtr<Input::InputGamePad> > defaultGamePad; 
		Threading::CriticalSection critSect;    
		Threading::ThreadId creatorThreadId;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputServerBase::IsOpen() const
	{
		return this->isOpen;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	SizeT
	InputServerBase::GetMaxNumLocalPlayers() const
	{
		return this->maxNumLocalPlayers;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	void
	InputServerBase::SetQuitRequested(bool b)
	{
		this->isQuitRequested = b;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputServerBase::IsQuitRequested() const
	{
		return this->isQuitRequested;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	const GPtr<Input::InputKeyboard>&
	InputServerBase::GetDefaultKeyboard() const
	{    
		n_assert2(creatorThreadId == Threading::Thread::GetMyThreadId(), "GetDefaultKeyboard can't be called from any thread but the creator thread!");
		return this->defaultKeyboard;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	const GPtr<Input::InputMouse>&
	InputServerBase::GetDefaultMouse() const
	{
		n_assert2(creatorThreadId == Threading::Thread::GetMyThreadId(), "GetDefaultMouse can't be called from any thread but the creator thread!");
		return this->defaultMouse;
	}

} // namespace Input
//------------------------------------------------------------------------------









#endif // __inputserverbase_H__

