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
#include "input/input_stdneb.h"
#include "input/base/inputkeyboardbase.h"
#include "input/inputserver.h"

namespace Input
{
__ImplementClass(Input::InputKeyboardBase, 'KBBS', Input::InputHandler);

using namespace Input;
 
//------------------------------------------------------------------------------
/**
*/
InputKeyboardBase::InputKeyboardBase() :
    keyStates(InputKey::NumKeyCodes)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
InputKeyboardBase::~InputKeyboardBase()
{
    n_assert(!this->IsAttached());
}

//------------------------------------------------------------------------------
/**
*/
void
InputKeyboardBase::BeginCapture()
{
    InputHandler::BeginCapture();
	n_assert(mInputServer.isvalid());
    mInputServer->ObtainKeyboardCapture(this);
}

//------------------------------------------------------------------------------
/**
*/
void
InputKeyboardBase::EndCapture()
{
    InputHandler::EndCapture();
	n_assert(mInputServer.isvalid());
    mInputServer->ReleaseKeyboardCapture(this);
}

//------------------------------------------------------------------------------
/**
*/
void
InputKeyboardBase::OnAttach(const GPtr<InputServerBase>& inputServer)
{
    InputHandler::OnAttach(inputServer);
    KeyState initialKeyState;
    this->keyStates.Fill(initialKeyState);
    this->charInput.Clear();
}

//------------------------------------------------------------------------------
/**
*/
void
InputKeyboardBase::OnBeginFrame()
{
    InputHandler::OnBeginFrame();

    // reset the up and down state of all keys
    IndexT i;
    for (i = 0; i < this->keyStates.Size(); i++)
    {
        KeyState& keyState = this->keyStates[i];
        
        // NOTE: if the key was released in the previous frame,
        // clear the pressed state (see the KeyUp-handling
        // code in OnEvent for details why this is a good thing)
        if (keyState.up)
        {
            keyState.pressed = false;
        }
        keyState.down = false;
        keyState.up = false;
    }

    // clear character input
    this->charInput.Clear();

	this->keyEventCache.Clear();
}

//------------------------------------------------------------------------------
/**
*/
bool
InputKeyboardBase::OnEvent(const InputEvent& inputEvent)
{
    switch (inputEvent.GetType())
    {
        // reset input handler if another one begins to capture
        case InputEvent::BeginKeyboardCapture:
            if (!this->IsCapturing())
            {
                this->OnReset();
            }
            break;

        case InputEvent::KeyDown:
            // note: if we're already pressed we don't record
            // a key down, this happens when the key repeat kicks in
            {
                KeyState& keyState = this->keyStates[inputEvent.GetKey()];
                if (!keyState.pressed)
                {
                    keyState.down = true;
                    keyState.pressed = true;
                }
				this->keyEventCache.Append(KeyEvent(inputEvent.GetKey(), inputEvent.GetType()));
            }
            break;

        case InputEvent::KeyUp:
            {
                KeyState& keyState = this->keyStates[inputEvent.GetKey()];
                keyState.up = true;
				this->keyEventCache.Append(KeyEvent(inputEvent.GetKey(), inputEvent.GetType()));
                // NOTE: we don't clear the pressed flag here because
                // it may happen that a key was only tapped shortly
                // within a frame, and in this case we still want the
                // pressed flag to be set for the current frame (otherwise an application
                // may miss the pressed state) instead, the pressed state will
                // be cleared at the beginning of the next frame
                // when the key up flag was set
            }
            break;

        case InputEvent::Character:
            {
                uchar chr = inputEvent.GetChar();
                this->charInput.AppendRange((const char*)&chr, 1);
            }
            break;

		default:
			break;
    }
    return InputHandler::OnEvent(inputEvent);
}

//------------------------------------------------------------------------------
/**
*/
void
InputKeyboardBase::OnObtainCapture()
{
    InputHandler::OnObtainCapture();

    // put begin keyboard capture event
    InputEvent beginCaptureEvent;
    beginCaptureEvent.SetType(InputEvent::BeginKeyboardCapture);
	n_assert(mInputServer.isvalid());
    mInputServer->PutEvent(beginCaptureEvent);
}

//------------------------------------------------------------------------------
/**
*/
void
InputKeyboardBase::OnReleaseCapture()
{
    // put end keyboard capture event
    InputEvent endCaptureEvent;
    endCaptureEvent.SetType(InputEvent::EndKeyboardCapture);
	n_assert(mInputServer.isvalid());
    mInputServer->PutEvent(endCaptureEvent);

    InputHandler::OnReleaseCapture();
}

//------------------------------------------------------------------------------
/**
*/
void
InputKeyboardBase::OnReset()
{
    IndexT i;
    for (i = 0; i < this->keyStates.Size(); i++)
    {
        KeyState& keyState = this->keyStates[i];
        if (keyState.pressed)
        {
            keyState.up = true;
        }
        else
        {
            keyState.up = false;
        }
        keyState.down = false;
        keyState.pressed = false;
    }
    this->charInput.Clear();
}

} // namespace Input
