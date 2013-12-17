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
#ifndef __inputkey_H__
#define __inputkey_H__


#include "core/types.h"
#include "util/string.h"
#include "util/dictionary.h"

//------------------------------------------------------------------------------
namespace Input
{
class InputKey
{
public:
    /// key codes
    enum Code
    {
        Back,
        Tab,
        Clear,
        Return,
        Shift,
        Control,
        Menu,
        Pause,
        Capital,
        Escape,
        Convert,
        NonConvert,
        Accept,
        ModeChange,
        Space,
        Prior,
        Next,
        End,
        Home,
        Left,
        Right,
        Up,
        Down,
        Select,
        Print,
        Execute,
        Snapshot,
        Insert,
        Delete,
        Help,
        LeftWindows,
        RightWindows,
        Apps,
        Sleep,
        NumPad0,
        NumPad1,
        NumPad2,
        NumPad3,
        NumPad4,
        NumPad5,
        NumPad6,
        NumPad7,
        NumPad8,
        NumPad9,
        Multiply,
        Add,
        Subtract,
        Separator,
        Decimal,
        Divide,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        NumLock,
        Scroll,
        Semicolon,
        Slash,
        Tilde,
        LeftBracket,
        RightBracket,
        BackSlash,
        Quote,
        Comma,
        Underbar,
        Period,
        Equality,
        LeftShift,
        RightShift,
        LeftControl,
        RightControl,
        LeftMenu,
        RightMenu,
        BrowserBack,
        BrowserForward,
        BrowserRefresh,
        BrowserStop,
        BrowserSearch,
        BrowserFavorites,
        BrowserHome,
        VolumeMute,
        VolumeDown,
        VolumeUp,
        MediaNextTrack,
        MediaPrevTrack,
        MediaStop,
        MediaPlayPause,
        LaunchMail,
        LaunchMediaSelect,
        LaunchApp1,
        LaunchApp2,
        Key0,
        Key1,
        Key2,
        Key3,
        Key4,
        Key5,
        Key6,
        Key7,
        Key8,
        Key9,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
		
		System, // Alt Key

        NumKeyCodes,
        InvalidKey,
    }; 

    /// key group
    enum Group
    {
        Letters, // (A, B, ..., Z)
        Numbers, // (Key_0, ..., Key_9)
        NumPad, // (NumPad_0, ... NumPad9...+-*/)
        FunctionKeys, // (F1, ... , F24)
        CursorKeys,  // (->,... ,<-)
        HomeBlock // (Home, End, Prior, Next, Insert, Delete)
    };
    
    /// convert to string
    static Util::String ToString(Code code);
    /// convert from string
    static Code FromString(const Util::String& str);
    /// get key codes by group
    static Util::Array<InputKey::Code> KeyCodesByGroup(InputKey::Group group);
private:
    static Util::Dictionary<Util::String,Code> dict;
};

};
//------------------------------------------------------------------------------





#endif // __inputkey_H__



