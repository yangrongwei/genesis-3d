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
using System.Collections.Generic;
using System.Text;
using System.Runtime.CompilerServices;

namespace ScriptGUI
{
    internal partial class Widget
    {
        protected void clearEvent<T>(ref T handle, EventType event_type)
            where T : class
        {
            if (null != handle)
            {
                handle = null;
                ICall_removeEvent(this, mInstance.Ptr, event_type);
            }

        }

        private void clearEventsWidthOutParent()
        {
            clearEvent(ref mHandleMouseButtonReleased, EventType.MouseButtonReleased);
            clearEvent(ref mHandleMouseButtonClick, EventType.MouseButtonClick);
            clearEvent(ref mHandleMouseButtonDoubleClick, EventType.MouseButtonDoubleClick);
            clearEvent(ref mHandleMouseLostFocus, EventType.MouseLostFocus);
            clearEvent(ref mHandleMouseSetFocus, EventType.MouseSetFocus);
            clearEvent(ref mHandleMouseDrag, EventType.MouseDrag);
            clearEvent(ref mHandleMouseMove, EventType.MouseMove);
            clearEvent(ref mHandleMouseWheel, EventType.MouseWheel);
            clearEvent(ref mHandleKeyLostFocus, EventType.KeyLostFocus);
            clearEvent(ref mHandleKeySetFocus, EventType.KeySetFocus);
            clearEvent(ref mHandleKeyButtonPressed, EventType.KeyButtonPressed);
            clearEvent(ref mHandleKeyButtonReleased, EventType.KeyButtonReleased);
            clearEvent(ref mHandleRootMouseChangeFocus, EventType.RootMouseChangeFocus);
            clearEvent(ref mHandleRootKeyChangeFocus, EventType.RootKeyChangeFocus);
            clearEvent(ref mHandleToolTip, EventType.ToolTip);

            if (null != mHandleTick)
            {
                GUIRoot.EventTick -= OnTick;
                mHandleTick = null;
            }
        }


        internal static void OnMouseButtonClick(Widget widget, EventArg arg)
        {
            widget.mHandleMouseButtonClick(widget.mName);
        }
        internal event Event.SenderVoid EventMouseButtonClick
        {
            add
            {
                if ( null == mHandleMouseButtonClick)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.MouseButtonClick))
                    {
                        return;
                    }
                } 
                mHandleMouseButtonClick += value;
            }
            remove
            {
                mHandleMouseButtonClick -= value;
                if (null == mHandleMouseButtonClick)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.MouseButtonClick);
                }
            }
        }
        protected Event.SenderVoid mHandleMouseButtonClick;

        internal static void OnMouseButtonDoubleClick(Widget widget, EventArg arg)
        {
            widget.mHandleMouseButtonDoubleClick(widget.mName);
        }
        internal event Event.SenderVoid EventMouseButtonDoubleClick
        {

            add
            {
                if (null == mHandleMouseButtonDoubleClick)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.MouseButtonDoubleClick))
                    {
                        return;
                    }
                }
                mHandleMouseButtonDoubleClick += value;
            }
            remove
            {
                mHandleMouseButtonDoubleClick -= value;
                if (null == mHandleMouseButtonClick)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.MouseButtonDoubleClick);
                }
            }
        }
        protected Event.SenderVoid mHandleMouseButtonDoubleClick;

        internal static void OnMouseLostFocus(Widget widget, FocusEventArg arg)
        {
            Instance root_inst = arg.focus_widget_root;
            Instance widget_inst = arg.focus_widget;
            Layout layout = null;
            if (GUI.SearchLayout(root_inst, out layout))
            {
                Widget widget2 = null;
                if (layout.TryGetWidget(widget_inst, out widget2))
                {
                    widget.mHandleMouseLostFocus(widget.Name, layout.Name, widget2.Name);
                    return;
                }
                else if (widget_inst.IsValid)
                {
                    String name = Widget.GetName(widget_inst.Ptr);
                    if (name.Length > 0)//[2012/6/17 zhongdaohuan]暂不支持编辑匿名的ui控件
                    {
                        widget2 = Widget.CreateWidget(widget_inst, name, layout);
                        widget.mHandleMouseLostFocus(widget.Name, layout.Name, widget2.Name);
                        return;
                    }
                }
            }
            widget.mHandleMouseLostFocus(widget.Name, null, null);
        }
        internal event Event.SenderFStringFString EventMouseLostFocus
        {
            add
            {
                if (null == mHandleMouseLostFocus)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.MouseLostFocus))
                    {
                        return;
                    }
                }  
                mHandleMouseLostFocus+= value;
            }
            remove
            {
                mHandleMouseLostFocus-= value;
                if (null == mHandleMouseLostFocus)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.MouseLostFocus);
                }
            }
        }
        protected Event.SenderFStringFString mHandleMouseLostFocus;


        internal static void OnMouseSetFocus(Widget widget, FocusEventArg arg)
        {

            Instance root_inst = arg.focus_widget_root;
            Instance widget_inst = arg.focus_widget;
            Layout layout = null;
            if (GUI.SearchLayout(root_inst, out layout))
            {
                Widget widget2 = null;
                if (layout.TryGetWidget(widget_inst, out widget2))
                {
                    widget.mHandleMouseSetFocus(widget.Name, layout.Name, widget2.Name);
                    return;
                }
                else if (widget_inst.IsValid)
                {
                    String name = Widget.GetName(widget_inst.Ptr);
                    if (name.Length > 0)//[2012/6/17 zhongdaohuan]暂不支持编辑匿名的ui控件
                    {
                        widget2 = Widget.CreateWidget(widget_inst, name, layout);
                        widget.mHandleMouseSetFocus(widget.Name, layout.Name, widget2.Name);
                        return;
                    }
                }
            }
            widget.mHandleMouseSetFocus(widget.Name, null, null);
        }
        internal event Event.SenderFStringFString EventMouseSetFocus
        {
            add
            {
                if (null == mHandleMouseSetFocus)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.MouseSetFocus))
                    {
                        return;
                    }
                } 
                mHandleMouseSetFocus += value;
            }
            remove
            {
                mHandleMouseSetFocus-= value;
                if (null == mHandleMouseSetFocus)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.MouseSetFocus);
                }
            }
        }
        protected Event.SenderFStringFString mHandleMouseSetFocus;

        internal static void OnMouseDrag(Widget widget, MouseDragEventArg arg)
        {
            widget.mHandleMouseDrag(widget.Name, arg.Left, arg.Top, arg.ButtonID);
        }
        internal event Event.SenderIntIntMouseButton EventMouseDrag
        {
            add
            {
                if (null == mHandleMouseDrag)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.MouseDrag))
                    {
                        return;
                    }
                }
                mHandleMouseDrag += value;
            }
            remove
            {
                mHandleMouseDrag-= value;
                if (null == mHandleMouseDrag)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.MouseDrag);
                }
            }
        }
        protected Event.SenderIntIntMouseButton mHandleMouseDrag;


        internal static void OnMouseMove(Widget widget, MouseMoveEventArg arg)
        {
            widget.mHandleMouseMove(widget.Name, arg.Left, arg.Top);
        }
        internal event Event.SenderIntInt EventMouseMove
        {
            add
            {
                if (null == mHandleMouseMove)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.MouseMove))
                    {
                        return;
                    }
                }
                mHandleMouseMove += value;
            }
            remove
            {
                mHandleMouseMove -= value;
                if (null == mHandleMouseMove)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.MouseMove);
                }
            }
        }
        protected Event.SenderIntInt mHandleMouseMove;


        internal static void OnMouseWheel(Widget widget, MouseWheelEventArg arg)
        {
            widget.mHandleMouseWheel(widget.Name, arg.Rel);
        }
        internal event Event.SenderInt EventMouseWheel
        {
            add
            {
                if (null == mHandleMouseWheel)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.MouseWheel))
                    {
                        return;
                    }
                }
                mHandleMouseWheel += value;
            }
            remove
            {
                mHandleMouseWheel -= value;
                if (null == mHandleMouseWheel)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.MouseWheel);
                }
            }
        }
        protected Event.SenderInt mHandleMouseWheel;

        internal static void OnMouseButtonPressed(Widget widget, MouseButtonEventArg arg)
        {
            widget.mHandleMouseButtonPressed(widget.Name, arg.Left, arg.Top, arg.ButtonID);
        }
        internal event Event.SenderIntIntMouseButton EventMouseButtonPressed
        {
            add
            {
                if (null == mHandleMouseButtonPressed)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.MouseButtonPressed))
                    {
                        return;
                    }
                }
                mHandleMouseButtonPressed += value;
            }
            remove
            {
                mHandleMouseButtonPressed -= value;
                if (null == mHandleMouseButtonPressed)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.MouseButtonPressed);
                }
            }
        }
        protected Event.SenderIntIntMouseButton mHandleMouseButtonPressed;


        internal static void OnMouseButtonReleased(Widget widget, MouseButtonEventArg arg)
        {
            widget.mHandleMouseButtonReleased(widget.Name, arg.Left, arg.Top, arg.ButtonID);
        }
        internal event Event.SenderIntIntMouseButton EventMouseButtonReleased
        {
            add
            {
                if (null == mHandleMouseButtonReleased)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.MouseButtonReleased))
                    {
                        return;
                    }
                }  
                mHandleMouseButtonReleased += value;
            }
            remove
            {
                mHandleMouseButtonReleased -= value;
                if (null == mHandleMouseButtonReleased)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.MouseButtonReleased);
                }
            }
        }

        protected Event.SenderIntIntMouseButton mHandleMouseButtonReleased;

        internal static void OnKeyLostFocus(Widget widget, FocusEventArg arg)
        {
                        Instance root_inst = arg.focus_widget_root;
            Instance widget_inst = arg.focus_widget;
            Layout layout = null;
            if (GUI.SearchLayout(root_inst, out layout))
            {
                Widget widget2 = null;
                if (layout.TryGetWidget(widget_inst, out widget2))
                {
                    widget.mHandleKeyLostFocus(widget.Name, layout.Name, widget2.Name);
                    return;
                }
                else if (widget_inst.IsValid)
                {
                    String name = Widget.GetName(widget_inst.Ptr);
                    if (name.Length > 0)//[2012/6/17 zhongdaohuan]暂不支持编辑匿名的ui控件
                    {
                        widget2 = Widget.CreateWidget(widget_inst, name, layout);
                        widget.mHandleKeyLostFocus(widget.Name, layout.Name, widget2.Name);
                        return;
                    }
                }
            }
            widget.mHandleKeyLostFocus(widget.Name, null, null);
        }
        internal event Event.SenderFStringFString EventKeyLostFocus
        {
            add
            {
                if (null == mHandleKeyLostFocus)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.KeyLostFocus))
                    {
                        return;
                    }
                } 
                mHandleKeyLostFocus += value;
            }
            remove
            {
                mHandleKeyLostFocus -= value;
                if (null == mHandleKeyLostFocus)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.KeyLostFocus);
                }
            }
        }
        protected Event.SenderFStringFString mHandleKeyLostFocus;


        internal static void OnKeySetFocus(Widget widget, FocusEventArg arg)
        {
                        Instance root_inst = arg.focus_widget_root;
            Instance widget_inst = arg.focus_widget;
            Layout layout = null;
            if (GUI.SearchLayout(root_inst, out layout))
            {
                Widget widget2 = null;
                if (layout.TryGetWidget(widget_inst, out widget2))
                {
                    widget.mHandleKeySetFocus(widget.Name, layout.Name, widget2.Name);
                    return;
                }
                else if (widget_inst.IsValid)
                {
                    String name = Widget.GetName(widget_inst.Ptr);
                    if (name.Length > 0)//[2012/6/17 zhongdaohuan]暂不支持编辑匿名的ui控件
                    {
                        widget2 = Widget.CreateWidget(widget_inst, name, layout);
                        widget.mHandleKeySetFocus(widget.Name, layout.Name, widget2.Name);
                        return;
                    }
                }
            }
            widget.mHandleKeySetFocus(widget.Name, null, null);
        }
        internal event Event.SenderFStringFString EventKeySetFocus
        {
            add
            {
                if (null == mHandleKeySetFocus)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.KeySetFocus))
                    {
                        return;
                    }
                }
                mHandleKeySetFocus += value;
            }
            remove
            {
                mHandleKeySetFocus  -= value;
                if (null == mHandleKeySetFocus)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.KeySetFocus);
                }
            }
        }
        protected Event.SenderFStringFString mHandleKeySetFocus;

        internal static void OnKeyButtonPressed(Widget widget, KeyButtonPressedEventArg arg)
        {
            widget.mHandleKeyButtonPressed(widget.Name, arg.Key, arg.Char);
        }
        internal event Event.SenderKeyCodeChar EventKeyButtonPressed
        {
            add
            {
                if (null == mHandleKeyButtonPressed)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.KeyButtonPressed))
                    {
                        return;
                    }
                }
                mHandleKeyButtonPressed += value;
            }
            remove
            {
                mHandleKeyButtonPressed -= value;
                if (null == mHandleKeyButtonPressed)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.KeyButtonPressed);
                }
            }
        }
        protected Event.SenderKeyCodeChar mHandleKeyButtonPressed;

        internal static void OnKeyButtonReleased(Widget widget, KeyButtonReleasedEventArg arg)
        {
            widget.mHandleKeyButtonReleased(widget.Name, arg.Key);
        }
        internal event Event.SenderKeyCode EventKeyButtonReleased
        {
            add
            {
                if (null == mHandleKeyButtonReleased)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.KeyButtonReleased))
                    {
                        return;
                    }
                }   
                mHandleKeyButtonReleased += value;
            }
            remove
            {
                mHandleKeyButtonReleased -= value;
                if (null == mHandleKeyButtonReleased)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.KeyButtonReleased);
                }
            }
        }
        protected Event.SenderKeyCode mHandleKeyButtonReleased;

        internal static void OnRootMouseChangeFocus(Widget widget, RootChangeFocusEventArg arg)
        {
            widget.mHandleRootMouseChangeFocus(widget.Name, arg.Focus);
        }
        internal event Event.SenderBool EventRootMouseChangeFocus
        {
            add
            {
                if (null == mHandleRootMouseChangeFocus)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.RootMouseChangeFocus))
                    {
                        return;
                    }
                }
                mHandleRootMouseChangeFocus += value;
            }
            remove
            {
                mHandleRootMouseChangeFocus -= value;
                if (null == mHandleRootMouseChangeFocus)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.RootMouseChangeFocus);
                }
            }
        }
        protected Event.SenderBool mHandleRootMouseChangeFocus;


        internal static void OnRootKeyChangeFocus(Widget widget, RootChangeFocusEventArg arg)
        {
            widget.mHandleRootKeyChangeFocus(widget.Name, arg.Focus);
        }
        internal event Event.SenderBool EventRootKeyChangeFocus
        {
            add
            {
                if (null == mHandleRootKeyChangeFocus)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.RootKeyChangeFocus))
                    {
                        return;
                    }
                } 
                mHandleRootKeyChangeFocus += value;
            }
            remove
            {
                mHandleRootKeyChangeFocus -= value;
                if (null == mHandleRootKeyChangeFocus)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.RootKeyChangeFocus);
                }
            }
        }
        protected Event.SenderBool mHandleRootKeyChangeFocus;

        internal static void OnToolTip(Widget widget, ToolTipEventArg arg)
        {
            ToolTipInfo info = (ToolTipInfo)Util.PtrToStruct<ToolTipInfo>(arg.ToolTip);
            widget.mHandleToolTip(widget.Name, info);
        }
        internal event Event.SenderToolTipInfo EventToolTip
        {
            add
            {
                if (null == mHandleToolTip)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.ToolTip))
                    {
                        return;
                    }
                } 
                mHandleToolTip += value;
            }
            remove
            {
                mHandleToolTip -= value;
                if (null == mHandleToolTip)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.ToolTip);
                }
            }
        }
        protected Event.SenderToolTipInfo mHandleToolTip;


        internal void OnTick(ScriptRuntime.Vector2 frame_time)
        {
            mHandleTick(mName, frame_time.X, frame_time.Y);
        }
        internal event Event.SenderTick EventTick
        {
            add
            {
                if (null == mHandleTick)
                {
                    GUIRoot.EventTick += OnTick;
                }
                mHandleTick += value;
            }
            remove
            {
                mHandleTick -= value;
                if (null == mHandleTick)
                {
                    GUIRoot.EventTick -= OnTick;
                }
            }
        }
        internal Event.SenderTick mHandleTick;


        internal bool NeedToolTip
        {
            get
            {
                return ICall_getNeedToolTip(mInstance.Ptr);
            }
            set
            {
                ICall_setNeedToolTip(mInstance.Ptr, value);
            }
        }

        internal String Pointer
        {
            get
            {
                return ICall_getPointer(mInstance.Ptr);
            }
            set
            {
                ICall_setPointer(mInstance.Ptr, value);
            }
        }

        internal bool NeedKeyFocus
        {
            get
            {
                return ICall_getNeedKeyFocus(mInstance.Ptr);
            }
            set
            {
                ICall_setNeedKeyFocus(mInstance.Ptr, value);
            }
        }

        internal bool NeedMouseFocus
        {
            get
            {
                return ICall_getNeedMouseFocus(mInstance.Ptr);
            }
            set
            {
                ICall_setNeedMouseFocus(mInstance.Ptr, value);
            }
        }


        internal bool InheritsPick
        {
            get
            {
                return ICall_getInheritsPick(mInstance.Ptr);
            }
            set
            {
                ICall_setInheritsPick(mInstance.Ptr, value);
            }
        }

        internal bool RootMouseFocus
        {
            get
            {
                return ICall_getRootMouseFocus(mInstance.Ptr);
            }
        }

        internal bool RootKeyFocus
        {
            get
            {
                return ICall_getRootKeyFocus(mInstance.Ptr);
            }
        }

        internal void SetMaskPick(String file_name)
        {
            ICall_setMaskPick(mInstance.Ptr, file_name);
        }

        internal bool IsMaskPickInside(IntPoint point, IntCoord coord)
        {
            return ICall_isMaskPickInside(mInstance.Ptr, ref point, ref coord);
        }



        #region Engine Interface
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static bool ICall_appendEvent(Widget widget, IntPtr widget_ptr, EventType type);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static void ICall_removeEvent(Widget widget, IntPtr widget_ptr, EventType type);





        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static void ICall_setNeedToolTip(IntPtr widget_ptr, bool value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static bool ICall_getNeedToolTip(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static void ICall_setPointer(IntPtr widget_ptr, String value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static String ICall_getPointer(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static void ICall_setNeedKeyFocus(IntPtr widget_ptr, bool value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static bool ICall_getNeedKeyFocus(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static void ICall_setNeedMouseFocus(IntPtr widget_ptr, bool value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static bool ICall_getNeedMouseFocus(IntPtr widget_ptr);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static void ICall_setInheritsPick(IntPtr widget_ptr, bool value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static bool ICall_getInheritsPick(IntPtr widget_ptr);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static void ICall_setMaskPick(IntPtr widget_ptr, String filename);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static bool ICall_isMaskPickInside(IntPtr widget_ptr, ref IntPoint point, ref IntCoord coord);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static bool ICall_getRootMouseFocus(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static bool ICall_getRootKeyFocus(IntPtr widget_ptr);




        #endregion
    }
}
