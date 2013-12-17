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
    internal class DDContainer : Widget
    {

        internal DDContainer(Instance inst, FString name, Layout parent)
            : base(inst, name, parent, WidgetType.DDContainer)
        {

        }
        internal DDContainer(Instance inst, FString name, Layout parent, WidgetType type)
            : base(inst, name, parent, type)
        {

        }

        ~DDContainer()
        {
            clearEventsWidthOutParent();
        }
        private void clearEventsWidthOutParent()
        {
            clearEvent(ref mHandleStartDrag, EventType.StartDrag);
            clearEvent(ref mHandleRequestDrop, EventType.RequestDrop);
            clearEvent(ref mHandleDropResult, EventType.DropResult);
            clearEvent(ref mHandleChangeDDState, EventType.ChangeDDState);
            clearEvent(ref mHandleDragWidgetInfo, EventType.RequestDragWidgetInfo);
        }
        internal override void Dispose()
        {
            clearEventsWidthOutParent();
            base.Dispose();
        }
        internal static void SetItemInfo(DDContainer sender, ref DragEventArg arg, ref DDItemInfo item_info)
        {

            _DDItemInfo _info = (_DDItemInfo)Util.PtrToStruct<_DDItemInfo>(arg.DDItemInfo);

            item_info.receiver_index = _info.receiver_index;
            item_info.sender_index = _info.sender_index;

            item_info.sender = sender.Name;

            if (_info.receiver == IntPtr.Zero)
            {
                item_info.receiver = null;
            }
            item_info.receiver = Widget.GetName(_info.receiver);
        }

        unsafe internal static void OnStartDrag(DDContainer widget, DragEventArg arg)
        {
            DDItemInfo item_info = new DDItemInfo();
            SetItemInfo(widget, ref arg, ref item_info);
            widget.mHandleStartDrag(widget.Name, item_info, ref *((bool*)arg.result.ToPointer()));
        }
        internal event Event.SenderDDItemInfoRefBool EventStartDrag
        {
            add
            {
                if (null == mHandleStartDrag)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.StartDrag))
                    {
                        return;
                    }
                }
                mHandleStartDrag += value;
            }
            remove
            {
                mHandleStartDrag -= value;
                if (null == mHandleStartDrag)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.StartDrag);
                }
            }
        }
        protected Event.SenderDDItemInfoRefBool mHandleStartDrag;

        unsafe internal static void OnRequestDrop(DDContainer widget, DragEventArg arg)
        {
            DDItemInfo item_info = new DDItemInfo();
            SetItemInfo(widget, ref arg, ref item_info);
            widget.mHandleRequestDrop(widget.Name, item_info, ref *((bool*)arg.result.ToPointer()));
        }
        internal event Event.SenderDDItemInfoRefBool EventRequestDrop
        {
            add
            {
                if (null == mHandleRequestDrop)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.RequestDrop))
                    {
                        return;
                    }
                }
                mHandleRequestDrop += value;
            }
            remove
            {
                mHandleRequestDrop -= value;
                if (null == mHandleRequestDrop)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.RequestDrop);
                }
            }
        }
        protected Event.SenderDDItemInfoRefBool mHandleRequestDrop;

        unsafe internal static void OnDropResult(DDContainer widget, DragEventArg arg)
        {
            DDItemInfo item_info = new DDItemInfo();
            SetItemInfo(widget, ref arg, ref item_info);
            widget.mHandleRequestDrop(widget.Name, item_info, ref *((bool*)arg.result.ToPointer()));
        }
        internal event Event.SenderDDItemInfoRefBool EventDropResult
        {
            add
            {
                if (null == mHandleDropResult)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.DropResult))
                    {
                        return;
                    }
                }
                mHandleDropResult += value;
            }
            remove
            {
                mHandleDropResult -= value;
                if (null == mHandleDropResult)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.DropResult);
                }
            }
        }
        protected Event.SenderDDItemInfoRefBool mHandleDropResult;

        internal static void OnChangeDDState(DDContainer widget, ChangeDDStateEventArg arg)
        {
            widget.mHandleChangeDDState(widget.Name, arg.State);
        }
        internal event Event.SenderDDItemState EventChangeDDState
        {
            add
            {
                if (null == mHandleChangeDDState)
                {
                    if (!ICall_appendEvent(this, mInstance.Ptr, EventType.ChangeDDState))
                    {
                        return;
                    }
                }
                mHandleChangeDDState += value;
            }
            remove
            {
                mHandleChangeDDState -= value;
                if (null == mHandleChangeDDState)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.ChangeDDState);
                }
            }
        }
        protected Event.SenderDDItemState mHandleChangeDDState;

        internal static void OnDragWidgetInfo(DDContainer widget, RequestDragWidgetInfoEventArg arg)
        {
            FString layout;
            FString item;
            widget.mHandleDragWidgetInfo(widget.Name, out layout, out item, arg.Dimension);
            Widget wd = null;
            
            if (null != layout && null !=item)
            {
                ExecuteResult ret = GUI.FindWidget(layout, item, out wd);
                if (ExecuteResult.Success == ret)
                {
                    arg.Item = wd.Instance.Ptr;
                }
            }
        }
        internal Event.SenderOutFStringOutFStringIntCoord EventDragWidgetInfo
        {
            set
            {
                mHandleDragWidgetInfo = value;
                if (null == mHandleDragWidgetInfo)
                {
                    ICall_removeEvent(this, mInstance.Ptr, EventType.RequestDragWidgetInfo);
                }
                else
                {
                    ICall_appendEvent(this, mInstance.Ptr, EventType.RequestDragWidgetInfo);
                }
            }
        }
        protected Event.SenderOutFStringOutFStringIntCoord mHandleDragWidgetInfo;




        internal bool NeedDragDrop
        {
            get
            {
                return ICall_getNeedDragDrop(mInstance.Ptr);
            }
            set
            {
                ICall_setNeedDragDrop(mInstance.Ptr, value);
            }
        }

        internal void RestDrop()
        {
            ICall_resetDrag(mInstance.Ptr);
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static void ICall_setNeedDragDrop(IntPtr widget_ptr, bool value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static bool ICall_getNeedDragDrop(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern protected static void ICall_resetDrag(IntPtr widget_ptr);

    }
}
