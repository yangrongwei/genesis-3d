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
#include "input/base/inputserverbase.h"
#include "input/inputhandler.h"
#include "input/inputkeyboard.h"
#include "input/inputmouse.h"
#include "input/inputtouchscreen.h"
#include "input/inputgamepad.h"

namespace Input
{
__ImplementClass(Input::InputServerBase, 'IPSB', Core::RefCounted);

using namespace Input;
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
InputServerBase::InputServerBase() :
    isOpen(false),
    inBeginFrame(false),
    isQuitRequested(false),
    inputHandlersLockCount(0),
    maxNumLocalPlayers(4),
    defaultGamePad(InputGamePad::GetMaxNumPlayers()),
    creatorThreadId(Threading::Thread::GetMyThreadId())
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
InputServerBase::~InputServerBase()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**
    Setup the maximum number of local players for this application. The
    default number is 1. This defines the number of game pad objects
    created and queried.
*/
void
InputServerBase::SetMaxNumLocalPlayers(SizeT num)
{
    n_assert(!this->isOpen);
    n_assert(num <= InputGamePad::GetMaxNumPlayers());
    this->maxNumLocalPlayers = num;
}

//------------------------------------------------------------------------------
/**
*/
void
InputServerBase::Open()
{
    n_assert(!this->isOpen);
    n_assert(!this->inBeginFrame);
    this->isOpen = true;
	
	SizeT count = mInputSourceList.Size();
	for ( IndexT index = 0; index < count; ++index )
	{
		mInputSourceList[index]->Open(this);
	}
}

//------------------------------------------------------------------------------
/**
*/
void
InputServerBase::Close()
{
    n_assert(this->IsOpen());

    // remove all input handlers
    IndexT i;
    for (i = 0; i < this->inputHandlers.Size(); i++)
    {
        this->inputHandlers[i].Value()->OnRemove();
    }
    this->inputHandlers.Clear();
    this->keyboardCaptureHandler = 0;
    this->mouseCaptureHandler = 0;

    // release default input handlers
    this->defaultKeyboard = 0;
    this->defaultMouse = 0;
    this->defaultGamePad.Fill(0);

	SizeT count = mInputSourceList.Size();
	for ( IndexT index = 0; index < count; ++index )
	{
		mInputSourceList[index]->Close();
	}

    this->isOpen = false;

}

//------------------------------------------------------------------------------
/**
*/
void
InputServerBase::Reset()
{
    InputEvent resetEvent;
    resetEvent.SetType(InputEvent::Reset);
    this->PutEvent(resetEvent);
    if (this->mouseCaptureHandler.isvalid())
    {
        this->ReleaseMouseCapture(this->mouseCaptureHandler);
    }
    if (this->keyboardCaptureHandler.isvalid())
    {
        this->ReleaseKeyboardCapture(this->keyboardCaptureHandler);
    }
}

//------------------------------------------------------------------------------
/**
*/
void
InputServerBase::AttachInputHandler(InputPriority::Code pri, const GPtr<InputHandler>& inputHandler)
{
    n_assert(0 == this->inputHandlersLockCount);

    // make sure the input handler isn't attached yet
    IndexT i;
    for (i = 0; i < this->inputHandlers.Size(); i++)
    {
        n_assert(inputHandler != this->inputHandlers[i].Value());
    }    

    // add a new entry to the sorted input handler array
    KeyValuePair<InputPriority::Code,GPtr<InputHandler> > kvp(pri, inputHandler);
    this->inputHandlers.InsertSorted(kvp);
    inputHandler->OnAttach(this);
}

//------------------------------------------------------------------------------
/**
*/
void
InputServerBase::RemoveInputHandler(const GPtr<InputHandler>& inputHandler)
{
    n_assert(0 == this->inputHandlersLockCount);

    // check if the input handler currently captures input
    if (this->mouseCaptureHandler.isvalid() && (this->mouseCaptureHandler == inputHandler))
    {
        this->ReleaseMouseCapture(inputHandler);
    }
    if (this->keyboardCaptureHandler.isvalid() && (this->keyboardCaptureHandler == inputHandler))
    {
        this->ReleaseKeyboardCapture(inputHandler);
    }

    // remove input handler
    IndexT i;
    for (i = 0; i < this->inputHandlers.Size(); i++)
    {
        if (inputHandler == this->inputHandlers[i].Value())
        {
            this->inputHandlers[i].Value()->OnRemove();
            this->inputHandlers.EraseIndex(i);
            return;
        }
    }
}

void InputServerBase::AttachInputSource( const GPtr<Input::InputSource>& inputSource)
{
	n_assert( !inputSource->IsOpen() );

	// make sure the input handler isn't attached yet
	SizeT count = mInputSourceList.Size();
	for (IndexT i = 0; i < count; i++)
	{
		n_assert(inputSource != this->mInputSourceList[i] );
	}
	mInputSourceList.Append( inputSource );

	if ( this->IsOpen() )
	{
		inputSource->Open(this);
	}
}

void InputServerBase::RemoveInputSource( const GPtr<Input::InputSource>& inputSource)
{
	IndexT findIndex = InvalidIndex;

	SizeT count = mInputSourceList.Size();
	for (IndexT i = 0; i < count; i++)
	{
		if( inputSource == this->mInputSourceList[i] ) 
		{
			findIndex = i;
			break;
		}
	}

	if ( findIndex != InvalidIndex )
	{
		mInputSourceList.EraseIndex(findIndex);
		if ( inputSource->IsOpen() )
		{
			inputSource->Close();
		}
	}
}

//------------------------------------------------------------------------------
/**
*/
void
InputServerBase::BeginFrame()
{
    n_assert(!this->inBeginFrame);
    this->inBeginFrame = true;


	// first handler, then source. because hander maybe clear all input status

    // notify input handlers
    this->inputHandlersLockCount++;
    IndexT i;
    for (i = 0; i < this->inputHandlers.Size(); i++)
    {
        this->inputHandlers[i].Value()->OnBeginFrame();
    }
    this->inputHandlersLockCount--;

	// notify input source
	{
		SizeT count = mInputSourceList.Size();
		for ( IndexT index = 0; index < count; ++index )
		{
			mInputSourceList[index]->BeginFrame();
		}
	}
}

//------------------------------------------------------------------------------
/**
*/
void
InputServerBase::OnFrame()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Call this somewhere towards the end of frame, when it is guaraneteed
    that noone needs input anymore.
*/
void
InputServerBase::EndFrame()
{
    n_assert(this->inBeginFrame);

    // notify input handlers
    this->inputHandlersLockCount++;
    IndexT i;
    for (i = 0; i < this->inputHandlers.Size(); i++)
    {
        this->inputHandlers[i].Value()->OnEndFrame();
    }
    this->inputHandlersLockCount--;
    this->inBeginFrame = false;
}

//------------------------------------------------------------------------------
/**
    NOTE: MouseMove and RawMouseMove events will be distributed to all
    input handlers regardless of mouse capture state!
*/
void
InputServerBase::PutEvent(const InputEvent& inputEvent)
{
    n_assert2(creatorThreadId == Threading::Thread::GetMyThreadId(), "PutEvent can't be called from any thread but the creator thread!");
    // check for mouse capture
    if (this->mouseCaptureHandler.isvalid())
    {
        // route mouse events exclusively to mouse capture handler
        switch (inputEvent.GetType())
        {
            // do not route this events exclusively
            case InputEvent::BeginMouseCapture:
            case InputEvent::EndMouseCapture:
                break;

			case InputEvent::AppDisplayMini:
            case InputEvent::AppLoseFocus:
            case InputEvent::Reset:
                this->ReleaseMouseCapture(this->mouseCaptureHandler);
                break;

            case InputEvent::MouseButtonDown:
            case InputEvent::MouseButtonUp:
            case InputEvent::MouseButtonDoubleClick:
            case InputEvent::MouseWheelForward:
            case InputEvent::MouseWheelBackward:
                this->mouseCaptureHandler->OnEvent(inputEvent);
                return;
			default:
				break;
        }
    }

    // check for keyboard capture
    if (this->keyboardCaptureHandler.isvalid())
    {
        // route keyboard events exclusively to keyboard capture handler
        switch (inputEvent.GetType())
        {
            // do not route this events exclusively
            case InputEvent::BeginKeyboardCapture:
            case InputEvent::EndKeyboardCapture:
                break;

			case InputEvent::AppDisplayMini:
            case InputEvent::AppLoseFocus:
            case InputEvent::Reset:
                this->ReleaseKeyboardCapture(this->keyboardCaptureHandler);
                break;

            case InputEvent::KeyDown:
            case InputEvent::KeyUp:
            case InputEvent::Character:
                this->keyboardCaptureHandler->OnEvent(inputEvent);
                return;

			default:
				break;
        }
    }

    // normal input event handling
    this->inputHandlersLockCount++;
    IndexT i;
    for (i = 0; i < this->inputHandlers.Size(); i++)
    {
        if (!this->inputHandlers[i].Value()->OnEvent(inputEvent))
        {
            break;
        }   
    }
    this->inputHandlersLockCount--;
}

//------------------------------------------------------------------------------
/**
    Obtain the mouse capture. All mouse input will go exclusively to the
    capture input handler until ReleaseMouseCapture() is called.
*/
void
InputServerBase::ObtainMouseCapture(const GPtr<InputHandler>& inputHandler)
{
    if (this->mouseCaptureHandler.isvalid())
    {
        this->mouseCaptureHandler->OnReleaseCapture();
        this->mouseCaptureHandler = 0;
    }
    this->mouseCaptureHandler = inputHandler;
    this->mouseCaptureHandler->OnObtainCapture();
}

//------------------------------------------------------------------------------
/**
    Release the mouse capture. The provided pointer must match the current
    capture input handler.
*/
void
InputServerBase::ReleaseMouseCapture(const GPtr<InputHandler>& inputHandler)
{
    if (this->mouseCaptureHandler.isvalid() && (this->mouseCaptureHandler == inputHandler))
    {
        this->mouseCaptureHandler->OnReleaseCapture();
        this->mouseCaptureHandler = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
const GPtr<InputHandler>&
InputServerBase::GetMouseCaptureHandler() const
{
    return this->mouseCaptureHandler;
}

//------------------------------------------------------------------------------
/**
    This clears the currently set mouse capture (if exists).
*/
void
InputServerBase::ClearMouseCapture()
{
    if (this->mouseCaptureHandler.isvalid())
    {
        this->mouseCaptureHandler->OnReleaseCapture();
        this->mouseCaptureHandler = 0;
    }
}

//------------------------------------------------------------------------------
/**
    This clears the currently set keyboard capture (if exists).
*/
void
InputServerBase::ClearKeyboardCapture()
{
    if (this->keyboardCaptureHandler.isvalid())
    {
        this->keyboardCaptureHandler->OnReleaseCapture();
        this->keyboardCaptureHandler = 0;
    }
}

//------------------------------------------------------------------------------
/**
    This clears the mouse and keyboards captures, if set.
*/
void
InputServerBase::ClearCapture()
{
    this->ClearMouseCapture();
    this->ClearKeyboardCapture();
}

//------------------------------------------------------------------------------
/**
    Obtain the keyboard capture. All keyboard input will go exclusively to the
    capture input handler until ReleaseKeyboardCapture() is called.
*/
void
InputServerBase::ObtainKeyboardCapture(const GPtr<InputHandler>& inputHandler)
{
    if (this->keyboardCaptureHandler.isvalid())
    {
        this->keyboardCaptureHandler->OnReleaseCapture();
        this->keyboardCaptureHandler = 0;
    }
    this->keyboardCaptureHandler = inputHandler;
    this->keyboardCaptureHandler->OnObtainCapture();
}

//------------------------------------------------------------------------------
/**
    Release the mouse capture. The provided pointer must match the current
    capture input handler.
*/
void
InputServerBase::ReleaseKeyboardCapture(const GPtr<InputHandler>& inputHandler)
{
    if (this->keyboardCaptureHandler.isvalid() && (this->keyboardCaptureHandler == inputHandler))
    {
        this->keyboardCaptureHandler->OnReleaseCapture();
        this->keyboardCaptureHandler = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
const GPtr<InputHandler>&
InputServerBase::GetKeyboardCaptureHandler() const
{
    return this->keyboardCaptureHandler;
}
    
//------------------------------------------------------------------------------
/**
*/
GPtr<Input::InputGamePad>
InputServerBase::GetDefaultGamePad(IndexT playerIndex) const
{
    this->critSect.Enter();
    n_assert(playerIndex < this->maxNumLocalPlayers);
    GPtr<Input::InputGamePad> result = this->defaultGamePad[playerIndex];
    this->critSect.Leave();
    return result;
}

} // namespace Input
