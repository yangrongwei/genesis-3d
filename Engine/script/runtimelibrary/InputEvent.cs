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
namespace ScriptRuntime
{
    public enum Code : int
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
        NumKeyCodes,
        InvalidKey
    }

    public enum MouseCode : int
    {
        LeftButton,
        RightButton,
        MiddleButton,
        NumMouseButtons,
        InvalidMouseButton
    }


    public enum InputEventType : int
    {
        InvalidType,
        AppObtainFocus,
        AppLoseFocus,
        AppDisplayMini,
        AppDisplayRestore,
        Reset,
        KeyDown,
        KeyUp,
        Character,
        MouseMove,
        RawMouseMove,
        MouseButtonDown,
        MouseButtonUp,
        MouseButtonDoubleClick,
        MouseWheelForward,
        MouseWheelBackward,
        BeginMouseCapture,
        EndMouseCapture,
        BeginKeyboardCapture,
        EndKeyboardCapture,
        GamePadButtonDown,
        GamePadButtonUp,
        TouchMotionMove,
        TouchMotionDown,
        TouchMotionUp,
        TouchMotionCancel
    }

    /// <summary>
    /// 按键事件
    /// </summary>
    public struct KeyEvent
    {
        public Code key;
        public InputEventType eventType;
    }

    /// <summary>
    /// 鼠标事件
    /// </summary>
    public struct MouseEvent
    {
        public MouseCode button;
        public InputEventType eventType;
    }

    /// <summary>
    /// 触控事件
    /// </summary>
    public struct TouchEvent
    {
        public int id;
        public InputEventType eventType;
    }

}