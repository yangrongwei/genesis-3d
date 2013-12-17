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
#include "input/base/inputgamepadbase.h"

namespace Input
{
__ImplementClass(Input::InputGamePadBase, 'IGPB', Input::InputHandler);

using namespace Input;
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
InputGamePadBase::InputGamePadBase() :
    playerIndex(0),
    isConnected(false),
    buttonStates(NumButtons),
    axisValues(NumAxes, 0.0f),
    vibratorsDirty(false),
    lowFreqVibrator(0.0f),
    highFreqVibrator(0.0f),
    creatorThreadId(Threading::Thread::GetMyThreadId())
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
InputGamePadBase::~InputGamePadBase()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
InputGamePadBase::OnAttach(const GPtr<InputServerBase>& inputServer )
{
    InputHandler::OnAttach(inputServer);

    // need to reset our state
    ButtonState initialButtonState;
    this->buttonStates.Fill(initialButtonState);
    this->axisValues.Fill(0.0f);
}

//------------------------------------------------------------------------------
/**
*/
void
InputGamePadBase::OnReset()
{
    InputHandler::OnReset();

    // reset button states (should behave as if the player
    // suddenly released all buttons and triggers)
    IndexT i;
    for (i = 0; i < this->buttonStates.Size(); i++)
    {
        ButtonState& btnState = this->buttonStates[i];
        if (btnState.pressed)
        {
            btnState.up = true;
        }
        else
        {
            btnState.up = false;
        }
        btnState.down = false;
        btnState.pressed = false;
    }
    this->axisValues.Fill(0.0f);
}

//------------------------------------------------------------------------------
/**
*/
String
InputGamePadBase::ButtonAsString(Button btn)
{
    switch (btn)
    {
        case DPadUpButton:          return "DPadUpButton";
        case DPadDownButton:        return "DPadDownButton";
        case DPadLeftButton:        return "DPadLeftButton";
        case DPadRightButton:       return "DPadRightButton";
        case StartButton:           return "StartButton";
        case BackButton:            return "BackButton";
        case LeftThumbButton:       return "LeftThumbButton";
        case RightThumbButton:      return "RightThumbButton";
        case LeftShoulderButton:    return "LeftShoulderButton";        
        case RightShoulderButton:   return "RightShoulderButton";        
        case AButton:               return "AButton";
        case BButton:               return "BButton";
        case XButton:               return "XButton";
        case YButton:               return "YButton";
        case HomeButton:            return "HomeButton";
        case PlusButton:            return "PlusButton";
        case MinusButton:           return "MinusButton";
        case OneButton:             return "OneButton";
        case TwoButton:             return "TwoButton";
        case ZButton:               return "ZButton";
        case CButton:               return "CButton";
		case SelectButton:			return "SelectButton";
        default:
            n_error("GamePadBase::ButtonAsString(): invalid button code!\n");
            return "";
    }
}

//------------------------------------------------------------------------------
/**
*/
String
InputGamePadBase::AxisAsString(Axis axis)
{
    switch (axis)
    {
        case LeftTriggerAxis:   return "LeftTriggerAxis";
        case RightTriggerAxis:  return "RightTriggerAxis";
        case LeftThumbXAxis:    return "LeftThumbXAxis";
        case LeftThumbYAxis:    return "LeftThumbYAxis";
        case RightThumbXAxis:   return "RightThumbXAxis";
        case RightThumbYAxis:   return "RightThumbYAxis";
        default:
            n_error("GamePadBase::AxisAsString(): invalid axis code!\n");
            return "";
    }
}

//------------------------------------------------------------------------------
/**
    This method should return the current state of the game pad
    as input events. It is up to a specific subclass to implement
    this method.
*/
Array<InputEvent>
InputGamePadBase::GetStateAsInputEvents() const
{
    Array<InputEvent> emptyArray;
    return emptyArray;
}

} // namespace Input
