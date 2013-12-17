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
#ifndef __inputevent_H__
#define __inputevent_H__

#include "core/types.h"
#include "input/inputkey.h"
#include "input/inputchar.h"
#include "input/inputmousebutton.h"
#include "math/float2.h"
#include "util/array.h"

//------------------------------------------------------------------------------
namespace Input
{
class InputEvent
{
public:
    /// input event types
    enum Type
    {
        InvalidType = 0,

        AppObtainFocus,         // application window obtained focus (or minimized, etc)
        AppLoseFocus,           // application window lost focus
		AppDisplayMini,			// application window mini
		AppDisplayRestore,	    // application window Restore
        Reset,                  // InputServer::Reset() has been called
        KeyDown,                // a key has been pressed
        KeyUp,                  // a key has been released
        Character,              // a translated character has been input

        MouseMove,              // mouse has been moved (limited by screen borders)
        RawMouseMove,           // raw mouse movement (not limited by screen borders)
        MouseButtonDown,        // a mouse button has been pressed
        MouseButtonUp,          // a mouse button has been released
        MouseButtonDoubleClick, // a mouse button has been double-clicked
        MouseWheelForward,      // mouse wheel moved forward
        MouseWheelBackward,     // mouse wheel moved backward
        BeginMouseCapture,      // a mouse input handler begin to capture
        EndMouseCapture,        // a mouse input handler end his capture
        BeginKeyboardCapture,   // a keyboard input handler begin to capture
        EndKeyboardCapture,     // a keyboard input handler end his capture

        GamePadButtonDown,      // a game pad button has been pressed
        GamePadButtonUp,        // a game pad button has been released

		TouchMotionMove,
		TouchMotionDown,
		TouchMotionUp,
		TouchMotionCancel,
    };

    /// default constructor
    InputEvent();

    /// set event type
    void SetType(Type t);
    /// get event type
    Type GetType() const;
    /// set key code
    void SetKey(InputKey::Code key);
    /// get key code
    InputKey::Code GetKey() const;
    /// set character code
    void SetChar(Char chr);
    /// get character code
    Char GetChar() const;
    /// set button code
    void SetMouseButton(InputMouseButton::Code button);
    /// get button code
    InputMouseButton::Code GetMouseButton() const;
    /// set optional device index (e.g. player index for game pads)
    void SetDeviceIndex(IndexT i);
    /// get device index
    IndexT GetDeviceIndex() const;
    /// set absolute pixel mouse position
    void SetAbsMousePos(const Math::float2& p);
    /// get absolute pixel mouse position
    const Math::float2& GetAbsMousePos() const;
    /// set normalized mouse position
    void SetNormMousePos(const Math::float2& p);
    /// get normalized mouse position
    const Math::float2& GetNormMousePos() const;
    /// convert type to string
    static const char* TypeToString(Type t);

#if __ANDROID__ || __OSX__

	const SizeT GetPointersCount() const;

	void SetPointerId(const IndexT id);

	const IndexT GetPointerId(const IndexT id) const;

	void SetAbsTouchPos(const Math::float2& absPos, const IndexT id);

	const Math::float2& GetAbsTouchPos(const IndexT id) const;

	void SetNormTouchPos(const Math::float2& normPos, const IndexT id);

	const Math::float2& GetNormTouchPos(const IndexT id) const;

#endif

private:
    Type type;
    InputKey::Code keyCode;
    Char character;
    IndexT deviceIndex;
    InputMouseButton::Code mouseButton;
    Math::float2 absMousePos;
    Math::float2 normMousePos;

#if __ANDROID__ || __OSX__
	Util::Array<IndexT>                     pointerIds;
	Util::Dictionary<IndexT, Math::float2>  absTouchPos;
	Util::Dictionary<IndexT, Math::float2>  normTouchPos;

#endif
};

//------------------------------------------------------------------------------
/**
*/
inline
InputEvent::InputEvent() :
    type(InvalidType),
    keyCode(InputKey::InvalidKey),
    character(0),
    deviceIndex(0),
    mouseButton(InputMouseButton::InvalidMouseButton)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline void
InputEvent::SetType(Type t)
{
    this->type = t;
}

//------------------------------------------------------------------------------
/**
*/
inline InputEvent::Type
InputEvent::GetType() const
{
    return this->type;
}

//------------------------------------------------------------------------------
/**
*/
inline void
InputEvent::SetKey(InputKey::Code key)
{
    this->keyCode = key;
}

//------------------------------------------------------------------------------
/**
*/
inline InputKey::Code
InputEvent::GetKey() const
{
    return this->keyCode;
}

//------------------------------------------------------------------------------
/**
*/
inline void
InputEvent::SetChar(Char chr)
{
    this->character = chr;
}

//------------------------------------------------------------------------------
/**
*/
inline Char
InputEvent::GetChar() const
{
    return this->character;
}

//------------------------------------------------------------------------------
/**
*/
inline void
InputEvent::SetMouseButton(InputMouseButton::Code btn)
{
    this->mouseButton = btn;
}

//------------------------------------------------------------------------------
/**
*/
inline InputMouseButton::Code
InputEvent::GetMouseButton() const
{
    return this->mouseButton;
}

//------------------------------------------------------------------------------
/**
*/
inline void
InputEvent::SetAbsMousePos(const Math::float2& p)
{
    this->absMousePos = p;
}

//------------------------------------------------------------------------------
/**
*/
inline const Math::float2&
InputEvent::GetAbsMousePos() const
{
    return this->absMousePos;
}

//------------------------------------------------------------------------------
/**
*/
inline void
InputEvent::SetNormMousePos(const Math::float2& p)
{
    this->normMousePos = p;
}

//------------------------------------------------------------------------------
/**
*/
inline const Math::float2&
InputEvent::GetNormMousePos() const
{
    return this->normMousePos;
}

//------------------------------------------------------------------------------
/**
*/
inline void
InputEvent::SetDeviceIndex(IndexT i)
{
    this->deviceIndex = i;
}

//------------------------------------------------------------------------------
/**
*/
inline IndexT
InputEvent::GetDeviceIndex() const
{
    return this->deviceIndex;
}

//------------------------------------------------------------------------------
/**
*/
inline const char*
InputEvent::TypeToString(Type t)
{
    switch (t)
    {
        case InvalidType:               return "InvalidTyp";
        case AppObtainFocus:            return "AppObtainFocus";
        case AppLoseFocus:              return "AppLoseFocus";
		case AppDisplayMini:            return "AppDisplayMini";
		case AppDisplayRestore:         return "AppDisplayRestore";
        case Reset:                     return "Reset";
        case KeyDown:                   return "KeyDown";
        case KeyUp:                     return "KeyUp";
        case Character:                 return "Character";
        case MouseMove:                 return "MouseMove";
        case RawMouseMove:              return "RawMouseMove";
        case MouseButtonDown:           return "MouseButtonDown";
        case MouseButtonUp:             return "MouseButtonUp";
        case MouseButtonDoubleClick:    return "MouseButtonDoubleClick";
        case MouseWheelForward:         return "MouseWheelForward";
        case MouseWheelBackward:        return "MouseWheelBackward";
        case BeginMouseCapture:         return "BeginMouseCapture";
        case EndMouseCapture:           return "EndMouseCapture";
        case BeginKeyboardCapture:      return "BeginKeyboardCapture";
        case EndKeyboardCapture:        return "EndKeyboardCapture";
        case GamePadButtonDown:         return "GamePadButtonDown";
        case GamePadButtonUp:           return "GamePadButtonUp";
        default:
            n_error("InputEvent::TypeToString(): invalid type!\n");
            return "<INVALID>";
    }
}

#if __ANDROID__ || __OSX__

inline const SizeT InputEvent::GetPointersCount() const
{
	return this->pointerIds.Size();
}

inline void InputEvent::SetPointerId(const IndexT id)
{
	this->pointerIds.Append(id);
}

inline const IndexT InputEvent::GetPointerId(const IndexT pointer) const
{
	n_assert( pointer <= this->pointerIds.Size() );

	return this->pointerIds[pointer];
}

inline void InputEvent::SetAbsTouchPos(const Math::float2& absPos, const IndexT id)
{
	IndexT ret = this->absTouchPos.FindIndex(id);

	if (ret != InvalidIndex)
	{
		this->absTouchPos[id] = absPos;
	} 
	else
	{
		this->absTouchPos.Add(id, absPos);
	}
}

inline const Math::float2& InputEvent::GetAbsTouchPos(const IndexT id) const
{
	IndexT ret = this->absTouchPos.FindIndex(id);

	if (ret != InvalidIndex)
	{
		return this->absTouchPos[id];
	} 
	else
	{
		n_error("InputEvent::GetAbsTouchPos : Invalid Pointer !!!");
	}
}

inline void InputEvent::SetNormTouchPos(const Math::float2& normPos, const IndexT id)
{
	IndexT ret = this->normTouchPos.FindIndex(id);

	if (ret != InvalidIndex)
	{
		this->normTouchPos[id] = normPos;
	} 
	else
	{
		this->normTouchPos.Add(id, normPos);
	}
}

inline const Math::float2& InputEvent::GetNormTouchPos(const IndexT id) const
{
	IndexT ret = this->normTouchPos.FindIndex(id);

	if (ret != InvalidIndex)
	{
		return this->normTouchPos[id];
	} 
	else
	{
		n_error("InputEvent::GetNormTouchPos : Invalid Pointer !!!");
	}
}

#endif


} // namespace Input
//------------------------------------------------------------------------------


#endif // __inputevent_H__



