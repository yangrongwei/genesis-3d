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
#include "input/inputhandler.h"
#include "input/base/inputserverbase.h"

namespace Input
{
__ImplementClass(Input::InputHandler, 'INPH', Core::RefCounted);

//------------------------------------------------------------------------------
/**
*/
InputHandler::InputHandler() :
    isAttached(false),
    isCapturing(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
InputHandler::~InputHandler()
{
    n_assert(!this->IsAttached());
}

//------------------------------------------------------------------------------
/**
    Begin capturing input to this input handler. This method must be
    overriden in a subclass, the derived method must call 
    ObtainMouseCapture(), ObtainKeyboardCapture(), or both, depending
    on what type input events you want to capture. An input handler
    which captures input gets all input events of the given type exclusively.
*/
void
InputHandler::BeginCapture()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    End capturing input to this input handler. Override this method
    in a subclass and release the captures obtained in BeginCapture().
*/
void
InputHandler::EndCapture()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
InputHandler::OnAttach(const GPtr<InputServerBase>& inputServer)
{
    n_assert(!this->IsAttached());
    this->isAttached = true;
	mInputServer = inputServer;
	n_assert( mInputServer.isvalid() );
}

//------------------------------------------------------------------------------
/**
*/
void
InputHandler::OnRemove()
{
    n_assert(this->IsAttached());
    this->isAttached = false;
	mInputServer = NULL;
}

//------------------------------------------------------------------------------
/**
*/
void
InputHandler::OnBeginFrame()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
InputHandler::OnEndFrame()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
InputHandler::OnObtainCapture()
{
    this->isCapturing = true;
}

//------------------------------------------------------------------------------
/**
*/
void
InputHandler::OnReleaseCapture()
{
    this->isCapturing = false;
}

//------------------------------------------------------------------------------
/**
*/
bool
InputHandler::OnEvent(const InputEvent& inputEvent)
{
    switch (inputEvent.GetType())
    {

        case InputEvent::AppObtainFocus:
        case InputEvent::AppLoseFocus:
		case InputEvent::AppDisplayMini:
		case InputEvent::AppDisplayRestore:
        case InputEvent::Reset:
            this->OnReset();
            break;

		default:
			break;
    }        
    return true;
}

//------------------------------------------------------------------------------
/**
    OnReset is called when the app loses or gains focus (amongst other
    occasions). The input handler should reset its internal state
    to prevent keys from sticking down, etc...
*/
void
InputHandler::OnReset()
{
    // empty
}

} // namespace Input


