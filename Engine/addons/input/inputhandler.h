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
#ifndef __inputhandler_H__
#define __inputhandler_H__


#include "core/refcounted.h"
#include "input/inputevent.h"

namespace Input
{
	class InputServerBase;
}

//------------------------------------------------------------------------------
namespace Input
{
	class InputHandler : public Core::RefCounted
	{
		__DeclareClass(InputHandler);
	public:
		/// constructor
		InputHandler();
		/// destructor
		virtual ~InputHandler();

		/// return true if the input handler is currently attached
		bool IsAttached() const;
		/// capture input to this event handler
		virtual void BeginCapture();
		/// end input capturing to this event handler
		virtual void EndCapture();
		/// return true if this input handler captures input
		bool IsCapturing() const;

	protected:
		friend class Input::InputServerBase;

		/// called when the handler is attached to the input server
		virtual void OnAttach(const GPtr<InputServerBase>& inputServer );
		/// called when the handler is removed from the input server
		virtual void OnRemove();
		/// called on InputServer::BeginFrame()
		virtual void OnBeginFrame();
		/// called on InputServer::EndFrame();
		virtual void OnEndFrame();
		/// called when input handler obtains capture
		virtual void OnObtainCapture();
		/// called when input handler looses capture
		virtual void OnReleaseCapture();
		/// called when an input event should be processed
		virtual bool OnEvent(const InputEvent& inputEvent);
		/// called when the handler should reset itself
		virtual void OnReset();

		bool isAttached;
		bool isCapturing;
		GPtr<InputServerBase> mInputServer;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputHandler::IsAttached() const
	{
		return this->isAttached;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	inline 
	bool
	InputHandler::IsCapturing() const
	{
		return this->isCapturing;
	}

} // namespace Input
//------------------------------------------------------------------------------





#endif // __inputhandler_H__




