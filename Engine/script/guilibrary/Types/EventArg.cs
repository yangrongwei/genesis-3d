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
using System;
using System.Runtime.InteropServices;

namespace ScriptGUI
{
    // 继承于EventArg的Event Arg模板
    //[StructLayout(LayoutKind.Sequential)]
    //struct EventArg
    //{
    //    [MarshalAs(UnmanagedType.Struct)]
    //    EventArg BaseArg;
    //}

    [StructLayout(LayoutKind.Sequential)]
    struct EventArg
    {
        [MarshalAs(UnmanagedType.I4)]
        public EventType EventType;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct ScrollChangePositionEventArg 
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public int Position;
    }


    // -------------------------------- widget event ----------------------------------
    [StructLayout(LayoutKind.Sequential)]
    struct FocusEventArg //Mouse Lost Focus, Mouse Set Focus, Key Lost Focus, Key Set Focus
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr focus_widget; //MyGUI::Widget*  
      
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr focus_widget_root; //MyGUI::Widget*
    }

    [StructLayout(LayoutKind.Sequential)]
    struct MouseDragEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public int Left;
        [MarshalAs(UnmanagedType.I4)]
        public int Top;
        [MarshalAs(UnmanagedType.I4)]
        public MouseButton ButtonID;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct MouseMoveEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public int Left;
        [MarshalAs(UnmanagedType.I4)]
        public int Top;
    }


    [StructLayout(LayoutKind.Sequential)]
    struct MouseWheelEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public int Rel;
    }



    [StructLayout(LayoutKind.Sequential)]
    struct MouseButtonEventArg //Mouse Button Pressed, Mouse Button Released
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;

        [MarshalAs(UnmanagedType.I4)]
        public int Left;
        [MarshalAs(UnmanagedType.I4)]
        public int Top;
        [MarshalAs(UnmanagedType.I4)]
        public MouseButton ButtonID;

    }

    [StructLayout(LayoutKind.Sequential)]
    struct KeyButtonPressedEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public KeyCode Key;
        [MarshalAs(UnmanagedType.U4)]
        public UInt32 Char;
    }


    [StructLayout(LayoutKind.Sequential)]
    struct KeyButtonReleasedEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public KeyCode Key;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct RootChangeFocusEventArg      //Root Mouse Change Focus, Root Key Change Focus
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.Bool)]
        public bool Focus;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct ToolTipEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr ToolTip; //const MyGUI::ToolTipInfo& _info
    }


    // -------------------------------- DDContainer event ----------------------------------
    [StructLayout(LayoutKind.Sequential)]
    struct DragEventArg     //StartDrag, RequestDrop, DropResult
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr DDItemInfo;  //const MyGUI::DDItemInfo&
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr result;  //bool*
    }

    [StructLayout(LayoutKind.Sequential)]
    struct ChangeDDStateEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public DDItemState State;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct RequestDragWidgetInfoEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;

        [MarshalAs(UnmanagedType.Struct)]
        public IntPtr Item;//MyGUI::Widget*&

        [MarshalAs(UnmanagedType.Struct)]
        public IntCoord Dimension;
    }

    // -------------------------------- Item Box event ----------------------------------
    [StructLayout(LayoutKind.Sequential)]
    struct RequestCoordWidgetItemEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr Coord;
        [MarshalAs(UnmanagedType.Bool)]
        public bool drop;
    }

    [StructLayout(LayoutKind.Sequential)]
    struct RequestCreateWidgetItemEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr Item; //MyGUI::Widget*
    }

    [StructLayout(LayoutKind.Sequential)]
    struct RequestDrawItemEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr Item; //MyGUI::Widget*
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr DrawItemInfo; //const MyGUI::IBDrawItemInfo& _data
    }


    [StructLayout(LayoutKind.Sequential)]
    struct ItemEventArg //SelectItemAccept, ChangeItemPosition
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;

        [MarshalAs(UnmanagedType.I4)]
        public uint index; //

    }

    [StructLayout(LayoutKind.Sequential)]
    struct NotifyItemEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr IBNotifyItemData;//const MyGUI::IBNotifyItemData&

    }

    // -------------------------------- List Box event ----------------------------------
    [StructLayout(LayoutKind.Sequential)]
    struct ListBoxEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;

        [MarshalAs(UnmanagedType.U4)]
        public uint index;
    }


    // -------------------------------- Window event ----------------------------------

    [StructLayout(LayoutKind.Sequential)]
    struct WindowButtonPressedEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;

        [MarshalAs(UnmanagedType.LPStr)]
        public String Name;
    }
    // -------------------------------- Canvas event ----------------------------------
    [StructLayout(LayoutKind.Sequential)]
    struct RequestUpdateCanvasEventArg
    {
        [MarshalAs(UnmanagedType.Struct)]
        EventArg BaseArg;
        [MarshalAs(UnmanagedType.I4)]
        public IntPtr CanvesEvent;//const MyGUI::Canvas::Event&
    }

    //[StructLayout(LayoutKind.Sequential)]
    //struct EventArg
    //{
    //    [MarshalAs(UnmanagedType.Struct)]
    //    EventArg BaseArg;
    //}
}
