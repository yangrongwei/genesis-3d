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
#include "input/base/inputmousebase.h"
#include "input/inputserver.h"

namespace Input
{
__ImplementClass(Input::InputMouseBase, 'MSBS', Input::InputHandler);

using namespace Input;

//------------------------------------------------------------------------------
/**
*/
InputMouseBase::InputMouseBase() :
    buttonStates(InputMouseButton::NumMouseButtons),
    wheelForward(false),
    wheelBackward(false),
    initialMouseMovement(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
InputMouseBase::~InputMouseBase()
{
    n_assert(!this->IsAttached());
}

//------------------------------------------------------------------------------
/**
*/
void
InputMouseBase::BeginCapture()
{
    InputHandler::BeginCapture();
	n_assert(mInputServer.isvalid());
    mInputServer->ObtainMouseCapture(this);
}

//------------------------------------------------------------------------------
/**
*/
void
InputMouseBase::EndCapture()
{
    InputHandler::EndCapture();
	n_assert(mInputServer.isvalid());
    mInputServer->ReleaseMouseCapture(this);
}

//------------------------------------------------------------------------------
/**
*/
void
InputMouseBase::OnAttach(const GPtr<InputServerBase>& inputServer)
{
    InputHandler::OnAttach(inputServer);

    ButtonState initialButtonState;
    this->buttonStates.Fill(initialButtonState);
    this->beginFramePixelPosition.set(0.0f, 0.0f);
    this->beginFrameScreenPosition.set(0.0f, 0.0f);
    this->pixelPosition.set(0.0f, 0.0f);
    this->screenPosition.set(0.0f, 0.0f);
    this->movement.set(0.0f, 0.0f);
    this->wheelForward = false;
    this->wheelBackward = false;
    this->initialMouseMovement = true;
}

//------------------------------------------------------------------------------
/**
*/
void
InputMouseBase::OnBeginFrame()
{
    InputHandler::OnBeginFrame();

    // reset button up/down/doubleclick flags, but retain the pressed state
    IndexT i;
    for (i = 0; i < this->buttonStates.Size(); i++)
    {
        ButtonState& state = this->buttonStates[i];

        // NOTE: if the button was released in the previous frame,
        // clear the pressed state (see the ButtonUp-handling
        // code in OnEvent for details why this is a good thing)
        if (state.up)
        {
            state.pressed = false;
        }
        state.down = false;
        state.up = false;
        state.doubleClicked = false;
    }
    this->beginFramePixelPosition = this->pixelPosition;
    this->beginFrameScreenPosition = this->screenPosition;
    this->movement.set(0.0f, 0.0f);
    this->wheelForward = false;
    this->wheelBackward = false;
	currentEvents.Clear();
}

//------------------------------------------------------------------------------
/**
*/
bool
InputMouseBase::OnEvent(const InputEvent& inputEvent)
{
    switch (inputEvent.GetType())
    {
        // reset input handler if another one begins to capture
        case InputEvent::BeginMouseCapture:
            if (!this->IsCapturing())
            {
                this->OnReset();
            }
            break;

        case InputEvent::MouseMove:
            this->UpdateMousePositions(inputEvent.GetAbsMousePos(), inputEvent.GetNormMousePos());
			this->currentEvents.Append(MouseButtonEvent(InputMouseButton::InvalidMouseButton, inputEvent.GetType()));
            break;

        case InputEvent::RawMouseMove:
            this->movement = inputEvent.GetAbsMousePos();
            break;

        case InputEvent::MouseButtonDown:
            {
                InputMouseButton::Code btn = inputEvent.GetMouseButton();
                if (InputMouseButton::InvalidMouseButton != btn)
                {
                    this->buttonStates[btn].down = true;
                    this->buttonStates[btn].pressed = true;
                    this->UpdateMousePositions(inputEvent.GetAbsMousePos(), inputEvent.GetNormMousePos());
					this->currentEvents.Append(MouseButtonEvent(btn, inputEvent.GetType()));
                }
            }
            break;

        case InputEvent::MouseButtonUp:
            {
                InputMouseButton::Code btn = inputEvent.GetMouseButton();
                if (InputMouseButton::InvalidMouseButton != btn)
                {
                    this->buttonStates[btn].up = true;
                    // NOTE: we don't clear the pressed flag here because
                    // it may happen that a button was only tapped shortly
                    // within a frame, and in this case we still want the
                    // pressed flag to be set for the current frame (otherwise an application
                    // may miss the pressed state) instead, the pressed state will
                    // be cleared at the beginning of the next frame
                    // when the button up flag was set
                    this->UpdateMousePositions(inputEvent.GetAbsMousePos(), inputEvent.GetNormMousePos());
					this->currentEvents.Append(MouseButtonEvent(btn, inputEvent.GetType()));
                }
            }
            break;
       
        case InputEvent::MouseButtonDoubleClick:
            {
                InputMouseButton::Code btn = inputEvent.GetMouseButton();
                if (InputMouseButton::InvalidMouseButton != btn)
                {
                    this->buttonStates[btn].doubleClicked = true;
                    this->UpdateMousePositions(inputEvent.GetAbsMousePos(), inputEvent.GetNormMousePos());
					this->currentEvents.Append(MouseButtonEvent(btn, inputEvent.GetType()));
                }
            }
            break;

        case InputEvent::MouseWheelForward:
            this->wheelForward = true;
			this->currentEvents.Append(MouseButtonEvent(InputMouseButton::MiddleButton, inputEvent.GetType()));
            break;

        case InputEvent::MouseWheelBackward:
            this->wheelBackward = true;
			this->currentEvents.Append(MouseButtonEvent(InputMouseButton::MiddleButton, inputEvent.GetType()));
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
InputMouseBase::OnObtainCapture()
{
    InputHandler::OnObtainCapture();
    
    // put begin mouse capture event
    InputEvent beginCaptureEvent;
    beginCaptureEvent.SetType(InputEvent::BeginMouseCapture);
	n_assert(mInputServer.isvalid());
    mInputServer->PutEvent(beginCaptureEvent);
}

//------------------------------------------------------------------------------
/**
*/
void
InputMouseBase::OnReleaseCapture()
{
    // put end mouse capture event
    InputEvent endCaptureEvent;
    endCaptureEvent.SetType(InputEvent::EndMouseCapture);
	n_assert(mInputServer.isvalid());
    mInputServer->PutEvent(endCaptureEvent);

    InputHandler::OnReleaseCapture();
}

//------------------------------------------------------------------------------
/**
*/
void
InputMouseBase::UpdateMousePositions(const Math::float2& pixelPos, const Math::float2& screenPos)
{    
    // prevent a mouse-jump at the beginning
    if (this->initialMouseMovement)
    {
        this->beginFramePixelPosition = pixelPos;
        this->beginFrameScreenPosition = screenPos;
        this->initialMouseMovement = false;
    }
    this->pixelPosition = pixelPos;
    this->screenPosition = screenPos;
}

//------------------------------------------------------------------------------
/**
*/
void
InputMouseBase::OnReset()
{
    // reset buttons
    IndexT i;
    for (i = 0; i < InputMouseButton::NumMouseButtons; i++)
    {
        ButtonState& state = this->buttonStates[i];
        if (state.pressed)
        {
            state.up = true;
        }
        else
        {
            state.up = false;
        }
        state.down = false;
        state.pressed = false;
    }
    //this->pixelPosition.set(0.0f, 0.0f);
    //this->screenPosition.set(0.0f, 0.0f);
    this->movement.set(0.0f, 0.0f);
    this->wheelForward = false;
    this->wheelBackward = false;
    this->initialMouseMovement = true;
}

} // namespace Input