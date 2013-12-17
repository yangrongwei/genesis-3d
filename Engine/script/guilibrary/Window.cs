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
    internal class Window : TextBox
    {
        internal Window(Instance inst, FString name, Layout parent)
            :base(inst, name, parent, WidgetType.Window)
        {

        }


		/** Hide or Show window Smooth */
		internal void SetVisibleSmooth(bool _value)
        {
            ICall_setVisibleSmooth(mInstance.Ptr, _value);
        }
		/** Hide window Smooth and then destroy it */
		internal void DestroySmooth()
        {
            ICall_destroySmooth(mInstance.Ptr);
        }

		/** Enable or disable auto alpha mode */
		internal bool AutoAlpha
        {
            get
            {
                return ICall_getAutoAlpha(mInstance.Ptr);
            }
            set
            {
                ICall_setAutoAlpha(mInstance.Ptr, value);
            }
        }

		internal override string Caption
        {
            set
            {
                base.Caption = value;
            }
            get
            {
                return base.Caption;
            }

        }

        ///** Get window caption widget */
        internal TextBox GetCaptionWidget()
        {
            if (null == mCaption)
            {
                Instance inst = ICall_getCaptionWidget(mInstance.Ptr);
                if (inst.IsValid)
                {
                    int temp = mInstance.Ptr.ToInt32() + inst.Ptr.ToInt32();

                    string name = mName + "_" + Widget.GetName(inst.Ptr) + "_" + temp.ToString();
                    mCaption = new TextBox(inst, name, mParentLayout);
                    mParentLayout.AddWidget(mCaption);
                }
            }
            return mCaption;
        }

		/** Set minimal possible window Size */
        /** Get minimal possible window Size */
		internal IntSize MinSize
        {
            set
            {
                ICall_setMinSize(mInstance.Ptr, ref value);
            }
            get
            {

                IntSize value;
                ICall_getMinSize(mInstance.Ptr, out value);
                return value;
                //IntPtr ptr = ICall_getMinSize(mInstance.Ptr);
                //return Util.PtrToStruct<IntSize>(ptr);
            }
        }

		/** Set maximal possible window Size */
		/** Get maximal possible window Size */
		internal IntSize MaxSize
        {
            set
            {
                ICall_setMaxSize(mInstance.Ptr, ref value);
            }
            get
            {

                IntSize value;
                ICall_getMaxSize(mInstance.Ptr, out value);
                return value;
                //IntPtr ptr = ICall_getMaxSize(mInstance.Ptr);
                //return Util.PtrToStruct<IntSize>(ptr);
            }
        }


		/** Enable or disable Snap to borders mode */
		internal bool Snap
        {
            set
            {
                ICall_setSnap(mInstance.Ptr, value);
            }
            get
            {
                return ICall_getSnap(mInstance.Ptr);
            }

        }

		/** Get current action applied to move/resize window. */
        internal IntCoord ActionScale
        {
            get
            {
                IntPtr ptr = ICall_getActionScale(mInstance.Ptr);
                return Util.PtrToStruct<IntCoord>(ptr);
            }
         }

		/** Enable or disable possibility to move window. */
        internal bool Movable
        {
            get
            {
                return ICall_getMovable(mInstance.Ptr);
            }
            set
            {
                ICall_setMovable(mInstance.Ptr, value);
            }
        }



        internal static void OnWindowButtonPressed(Window widget, WindowButtonPressedEventArg arg)
        {
            widget.mHandleWindowButtonPressed(widget.Name, arg.Name);
        }
        internal event Event.SenderString EventWindowButtonPressed
        {
            add
            {
                if (null == mHandleWindowButtonPressed)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.WindowButtonPressed))
                    {
                        return;
                    }
                }
                mHandleWindowButtonPressed += value;
            }
            remove
            {
                mHandleWindowButtonPressed -= value;
                if (null == mHandleWindowButtonPressed)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.WindowButtonPressed);
                }
            }
        }
        protected Event.SenderString mHandleWindowButtonPressed;

        internal static void OnWindowChangeCoord(Window widget, EventArg arg)
        {
            widget.mHandleWindowChangeCoord(widget.Name);
        }
        internal event Event.SenderVoid EventWindowChangeCoord
        {
            add
            {
                if (null == mHandleWindowChangeCoord)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.WindowChangeCoord))
                    {
                        return;
                    }
                } 
                mHandleWindowChangeCoord += value;
            }
            remove
            {
                mHandleWindowChangeCoord -= value;
                if (null == mHandleWindowChangeCoord)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.WindowChangeCoord);
                }
            }
        }
        protected Event.SenderVoid mHandleWindowChangeCoord;




        protected TextBox mCaption;



        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static IntPtr ICall_getCaptionWidget(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static void ICall_setVisibleSmooth(IntPtr widget_ptr, bool _value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static void ICall_destroySmooth(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static void ICall_setAutoAlpha(IntPtr widget_ptr, bool _value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static bool ICall_getAutoAlpha(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static void ICall_setMinSize(IntPtr widget_ptr, ref IntSize _value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static IntPtr ICall_getMinSize(IntPtr widget_ptr, out IntSize _value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setMaxSize(IntPtr widget_ptr, ref IntSize _value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static IntPtr ICall_getMaxSize(IntPtr widget_ptr, out IntSize _value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static void ICall_setSnap(IntPtr widget_ptr, bool _value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static bool ICall_getSnap(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static IntPtr ICall_getActionScale(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static void ICall_setMovable(IntPtr widget_ptr, bool _value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
		extern private static bool ICall_getMovable(IntPtr widget_ptr);
    }
}
