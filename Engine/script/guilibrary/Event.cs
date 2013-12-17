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
using System.Runtime.InteropServices;

namespace ScriptGUI
{
    /// <summary>
    /// 事件类
    /// </summary>
    public class Event
    {
        /// <summary>
        /// 处理void事件
        /// </summary>
        /// <param name="sender">发送者</param>
        public delegate void SenderVoid(FString sender);
        /// <summary>
        /// 处理FString类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="value">FString类型发送参数</param>
        public delegate void SenderFString(FString sender, FString value);
        /// <summary>
        /// 处理String类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="value">String类型发送参数</param>
        public delegate void SenderString(FString sender, String value);
        /// <summary>
        /// 处理FString FString类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="value1">FString类型发送参数</</param>
        /// <param name="value2">FString类型发送参数</</param>
        public delegate void SenderFStringFString(FString sender, FString value1, FString value2);
        /// <summary>
        /// 处理bool类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="value">bool类型发送参数</param>
        public delegate void SenderBool(FString sender, bool value);
        /// <summary>
        /// 处理int类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="value">int类型发送参数</param>
        public delegate void SenderInt(FString sender, int value);
        /// <summary>
        /// 处理int int类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="value1">int类型发送参数</param>
        /// <param name="value2">int类型发送参数</param>
        public delegate void SenderIntInt(FString sender, int value1, int value2);
        /// <summary>
        /// 处理int int MouseButton类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="value1">int类型发送参数</param>
        /// <param name="value2">int类型发送参数</param>
        /// <param name="button">MouseButton类型发送参数</param>
        public delegate void SenderIntIntMouseButton(FString sender, int value1, int value2, MouseButton button);
        /// <summary>
        /// 处理KeyCode类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="code">KeyCode类型参数</param>
        public delegate void SenderKeyCode(FString sender, KeyCode code);
        /// <summary>
        /// 处理KeyCode Uint类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="code">KeyCode类型参数</param>
        /// <param name="ch">Uint类型参数</param>
        public delegate void SenderKeyCodeChar(FString sender, KeyCode code, uint ch);
        /// <summary>
        /// 处理ToolipInfo类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="info">ToolipInfo参数</param>
        public delegate void SenderToolTipInfo(FString sender, ToolTipInfo info);
        /// <summary>
        /// 处理refIntCoord Bool类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="coord">IntCoord类型参数</param>
        /// <param name="value1">bool类型参数</param>
        public delegate void SenderRefIntCoordBool(FString sender, ref IntCoord coord, bool value1);
        /// <summary>
        /// 处理ItemInfo类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="info">ItemInfo类型参数</param>
        public delegate void SenderItemInfo(FString sender, ItemInfo info);
        /// <summary>
        /// 处理ItemInfo IBDrawItemInfo类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="info">ItemInfo类型参数</param>
        /// <param name="itemInfo">IBDrawItemInfo类型参数</param>
        public delegate void SenderItemInfoIBDrawInfo(FString sender, ItemInfo info, IBDrawItemInfo itemInfo);
        /// <summary>
        /// 处理DDItemInfo ref bool类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="info">DDItemInfo类型参数</param>
        /// <param name="result">ref bool类型参数</param>
        public delegate void SenderDDItemInfoRefBool(FString sender, DDItemInfo info, ref bool result);
        /// <summary>
        /// 处理DDItemState类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="state">DDItemState类型参数</param>
        public delegate void SenderDDItemState(FString sender, DDItemState state);
        /// <summary>
        /// 处理out FString out FString IntCoord类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="layout">out FString类型参数</param>
        /// <param name="item">out FString类型参数</param>
        /// <param name="coord">IntCoord类型参数</param>
        public delegate void SenderOutFStringOutFStringIntCoord(FString sender, out FString layout, out FString item, IntCoord coord);
        /// <summary>
        /// 处理ref IBNotifyItemData类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="info">IBNotifyItemData类型参数</param>
        public delegate void SenderRefIBNotifyItemData(FString sender, ref IBNotifyItemData info);
        /// <summary>
        /// 处理Canvas_Event类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="canvasEvent">Canvas_Event类型参数</param>
        public delegate void SenderCanvas_Event(FString sender, Canvas_Event canvasEvent);
        /// <summary>
        /// 处理float float类型事件
        /// </summary>
        /// <param name="sender">发送者</param>
        /// <param name="game_time">float类型参数</param>
        /// <param name="frame_time">float类型参数</param>
        public delegate void SenderTick(FString sender, float game_time, float frame_time);




        // ----------------------- 模板，勿删 -----------------------------------------
        //internal static void On(Widget widget, EventArg arg)
        //{
        //    widget.mHandle(widget.Name);
        //}
        //internal event Event. Event
        //{
        //    add
        //    {
        //        if (null == )
        //        {
        //            if (ICall_appendEvent(this, mInstance.Ptr, EventType.))
        //            {
        //                += value;
        //            }
        //        }
        //    }
        //    remove
        //    {
        //        -= value;
        //        if (null == )
        //        {
        //            ICall_removeEvent(this, mInstance.Ptr, EventType.);
        //        }
        //    }
        //}
        //protected Event. mHandle;




        unsafe private static void onEvent(Widget widget, IntPtr int_ptr)
        {

            EventArg arg = Util.PtrToStruct<EventArg>(int_ptr);
            switch (arg.EventType)
            {
                case EventType.MouseButtonClick:
                    {
                        Widget.OnMouseButtonClick(widget, Util.PtrToStruct<EventArg>(int_ptr));//
                    }
                    break;
                case EventType.MouseButtonPressed:
                    {
                        Widget.OnMouseButtonPressed(widget, Util.PtrToStruct<MouseButtonEventArg>(int_ptr));
                    }
                    break;
                case EventType.MouseButtonReleased:
                    {
                        Widget.OnMouseButtonReleased(widget, Util.PtrToStruct<MouseButtonEventArg>(int_ptr));
                    }
                    break;
                case EventType.MouseButtonDoubleClick:
                    {
                        Widget.OnMouseButtonDoubleClick(widget, Util.PtrToStruct<EventArg>(int_ptr));
                    }
                    break;
                case EventType.MouseLostFocus:
                    {
                        Widget.OnMouseLostFocus(widget, Util.PtrToStruct<FocusEventArg>(int_ptr));
                    }
                    break;
                case EventType.MouseSetFocus:
                    {
                        Widget.OnMouseSetFocus(widget, Util.PtrToStruct<FocusEventArg>(int_ptr));
                    }
                    break;
                case EventType.MouseDrag:
                    {
                        Widget.OnMouseDrag(widget, Util.PtrToStruct<MouseDragEventArg>(int_ptr));
                    }
                    break;
                case EventType.MouseMove:
                    {
                        Widget.OnMouseMove(widget, Util.PtrToStruct<MouseMoveEventArg>(int_ptr));
                    }
                    break;
                case EventType.MouseWheel:
                    {
                        Widget.OnMouseWheel(widget, Util.PtrToStruct<MouseWheelEventArg>(int_ptr));
                    }
                    break;
                case EventType.KeyLostFocus:
                    {
                        Widget.OnKeyLostFocus(widget, Util.PtrToStruct<FocusEventArg>(int_ptr));
                    }
                    break;
                case EventType.KeySetFocus:
                    {
                        Widget.OnKeySetFocus(widget, Util.PtrToStruct<FocusEventArg>(int_ptr));
                    }
                    break;
                case EventType.KeyButtonPressed:
                    {
                        Widget.OnKeyButtonPressed(widget, Util.PtrToStruct<KeyButtonPressedEventArg>(int_ptr));
                    }
                    break;
                case EventType.KeyButtonReleased:
                    {
                        Widget.OnKeyButtonReleased(widget, Util.PtrToStruct<KeyButtonReleasedEventArg>(int_ptr));
                    }
                    break;
                case EventType.RootMouseChangeFocus:
                    {
                        Widget.OnRootMouseChangeFocus(widget, Util.PtrToStruct<RootChangeFocusEventArg>(int_ptr));
                    }
                    break;
                case EventType.RootKeyChangeFocus:
                    {
                        Widget.OnRootKeyChangeFocus(widget, Util.PtrToStruct<RootChangeFocusEventArg>(int_ptr));
                    }
                    break;
                case EventType.ToolTip:
                    {
                        Widget.OnToolTip(widget, Util.PtrToStruct<ToolTipEventArg>(int_ptr));
                    }
                    break;


                case EventType.ScrollChangePosition:
                    {
                        ScrollBar sb = widget as ScrollBar;
                        if (null != sb)
                        {
                            ScrollBar.OnScrollChangePosition(sb, Util.PtrToStruct<ScrollChangePositionEventArg>(int_ptr));
                        }
                    }
                    break;
                // --------------------------------------- DDContainer event ------------------------------------------------
                case EventType.StartDrag:
                    {
                        DDContainer ct = widget as DDContainer;
                        if (null != ct)
                        {
                            DDContainer.OnStartDrag(ct, Util.PtrToStruct<DragEventArg>(int_ptr));
                        }
                    }
                    break;

                case EventType.RequestDrop:
                    {
                        DDContainer ct = widget as DDContainer;
                        if (null != ct)
                        {
                            DDContainer.OnRequestDrop(ct, Util.PtrToStruct<DragEventArg>(int_ptr));
                        }
                    }
                    break;
                case EventType.DropResult:
                    {
                        DDContainer ct = widget as DDContainer;
                        if (null != ct)
                        {
                            DDContainer.OnDropResult(ct, Util.PtrToStruct<DragEventArg>(int_ptr));
                        }
                    }
                    break;
                case EventType.ChangeDDState:
                    {
                        DDContainer ct = widget as DDContainer;
                        if (null != ct)
                        {
                            DDContainer.OnChangeDDState(ct, Util.PtrToStruct<ChangeDDStateEventArg>(int_ptr));
                        }
                    }
                    break;
                case EventType.RequestDragWidgetInfo:
                    {
                        DDContainer ct = widget as DDContainer;
                        if (null != ct)
                        {
                            DDContainer.OnDragWidgetInfo(ct, Util.PtrToStruct<RequestDragWidgetInfoEventArg>(int_ptr));
                        }
                    }
                    break;
                // --------------------------------------- item box event ------------------------------------------------
                case EventType.RequestCoordItem:
                    {
                        ItemBox ib = widget as ItemBox;
                        if (null != ib)
                        {
                            ItemBox.OnRequestCoordItem(ib, Util.PtrToStruct<RequestCoordWidgetItemEventArg>(int_ptr));
                        }
                    }
                    break;
                case EventType.RequestCreateWidgetItem:
                    {
                        ItemBox ib = widget as ItemBox;
                        if (null != ib)
                        {
                            ItemBox.OnRequestCreateWidgetItem(ib, Util.PtrToStruct<RequestCreateWidgetItemEventArg>(int_ptr));
                        }
                    }
                    break;
                case EventType.RequestDrawItem:
                    {
                        ItemBox ib = widget as ItemBox;
                        if (null != ib)
                        {
                            ItemBox.OnRequestDrawItem(ib, Util.PtrToStruct<RequestDrawItemEventArg>(int_ptr));
                        }
                    }
                    break;

                case EventType.SelectItemAccept:
                    {
                        ItemBox ib = widget as ItemBox;
                        if (null != ib)
                        {
                            ItemBox.OnSelectItemAccept(ib, Util.PtrToStruct<ItemEventArg>(int_ptr));
                        }
                    }
                    break;

                case EventType.ChangeItemPosition:
                    {
                        ItemBox ib = widget as ItemBox;
                        if (null != ib)
                        {
                            ItemBox.OnChangeItemPosition(ib, Util.PtrToStruct<ItemEventArg>(int_ptr));
                        }
                    }
                    break;

                case EventType.MouseItemActivate:
                    {
                        ItemBox ib = widget as ItemBox;
                        if (null != ib)
                        {
                            ItemBox.OnMouseItemActivate(ib, Util.PtrToStruct<ItemEventArg>(int_ptr));
                        }
                    }
                    break;

                case EventType.NotifyItem:
                    {
                        ItemBox ib = widget as ItemBox;
                        if (null != ib)
                        {
                            ItemBox.OnNotifyItem(ib, Util.PtrToStruct<NotifyItemEventArg>(int_ptr));
                        }
                    }
                    break;

                // -------------------------------- List Box event ----------------------------------
                case EventType.ListSelectAccept:
                    {
                        ListBox ib = widget as ListBox;
                        if (null != ib)
                        {
                            ListBox.OnListSelectAccept(ib, Util.PtrToStruct<ListBoxEventArg>(int_ptr));
                        }
                    }
                    break;

                case EventType.ListChangePosition:
                    {
                        ListBox ib = widget as ListBox;
                        if (null != ib)
                        {
                            ListBox.OnListChangePosition(ib, Util.PtrToStruct<ListBoxEventArg>(int_ptr));
                        }
                    }
                    break;

                case EventType.ListMouseItemActivate:
                    {
                        ListBox ib = widget as ListBox;
                        if (null != ib)
                        {
                            ListBox.OnListMouseItemActivate(ib, Util.PtrToStruct<ListBoxEventArg>(int_ptr));
                        }
                    }
                    break;

                case EventType.ListMouseItemFocus:
                    {
                        ListBox ib = widget as ListBox;
                        if (null != ib)
                        {
                            ListBox.OnListMouseItemFocus(ib, Util.PtrToStruct<ListBoxEventArg>(int_ptr));
                        }
                    }
                    break;

                case EventType.ListChangeScroll:
                    {
                        ListBox ib = widget as ListBox;
                        if (null != ib)
                        {
                            ListBox.OnListChangeScroll(ib, Util.PtrToStruct<ListBoxEventArg>(int_ptr));
                        }
                    }
                    break;

                // -------------------------------- Window event ----------------------------------
                case EventType.WindowButtonPressed:
                    {
                        Window window = widget as Window;
                        if (null != window)
                        {
                            Window.OnWindowButtonPressed(window, Util.PtrToStruct<WindowButtonPressedEventArg>(int_ptr));
                        }
                    }
                    break;
                case EventType.WindowChangeCoord:
                    {
                        Window window = widget as Window;
                        if (null != window)
                        {
                            Window.OnWindowChangeCoord(window, arg);
                        }
                    }
                    break;
                // -------------------------------- Canvas event ----------------------------------
                case EventType.PreTextureChanges:
                    {
                        Canvas canvas = widget as Canvas;
                        if (null != canvas)
                        {
                            Canvas.OnPreTextureChanges(canvas, Util.PtrToStruct<EventArg>(int_ptr));
                        }
                    }
                    break;
                case EventType.RequestUpdateCanvas:
                    {
                        Canvas canvas = widget as Canvas;
                        if (null != canvas)
                        {
                            Canvas.OnRequestUpdateCanvas(canvas, Util.PtrToStruct<RequestUpdateCanvasEventArg>(int_ptr));
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
