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
    internal class ScrollBar : Widget
    {
        internal ScrollBar(Instance inst, FString name, Layout parent)
            : base(inst, name, parent, WidgetType.ScrollBar)
        {

        }
        ~ScrollBar()
        {
            clearEventsWidthOutParent();
        }
        private void clearEventsWidthOutParent()
        {
            clearEvent(ref mHandleScrollChangePosition, EventType.ScrollChangePosition);
        }
        internal override void Dispose()
        {
            clearEventsWidthOutParent();
            base.Dispose();
        }

        internal int ScrollPosition
        {
            get
            {
                return ICall_getScrollPosition(mInstance.Ptr);
            }
            
        }
        internal int ScrollRange
        {
            get
            {
                return ICall_getScrollRange(mInstance.Ptr);
            }
        }


        internal static void OnScrollChangePosition(ScrollBar scroll_bar, ScrollChangePositionEventArg sc_arg)
        {
            //ScrollChangePositionEventArg sc_arg = arg as ScrollChangePositionEventArg;
            int position = sc_arg.Position;
            scroll_bar.mHandleScrollChangePosition(scroll_bar.mName, position);

        }
        internal event Event.SenderInt EventScrollChangePosition
        {

            add
            {
                if (null == mHandleScrollChangePosition)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.ScrollChangePosition))
                    {
                        return;
                    }
                }
                mHandleScrollChangePosition += value;
            }
            remove
            {
                mHandleScrollChangePosition -= value;
                if (null == mHandleMouseButtonClick)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.ScrollChangePosition);
                }
            }
        }

        protected Event.SenderInt mHandleScrollChangePosition;



        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_getScrollPosition(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_getScrollRange(IntPtr widget_ptr);

    }
}
