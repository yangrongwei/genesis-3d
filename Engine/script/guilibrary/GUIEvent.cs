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

namespace ScriptGUI
{
    /// <summary>
    /// 用户界面接口类
    /// </summary>
    public partial class GUI
    {
        /// <summary>
        /// 用户界面控件类
        /// </summary>
        public static partial class UIWidget
        {

            /// <summary>
            /// 设置鼠标单击按钮事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制方式</param>
            /// <returns></returns>
            public static ExecuteResult SetEventMouseButtonClick(FString layout_name, FString widget_name, Event.SenderVoid func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventMouseButtonClick += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventMouseButtonClick -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置鼠标按下按钮事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制方式</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventMouseButtonPressed(FString layout_name, FString widget_name, Event.SenderIntIntMouseButton func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventMouseButtonPressed += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventMouseButtonPressed -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置鼠标释放按钮事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制方式</param>
            /// <returns></returns>
            public static ExecuteResult SetEventMouseButtonReleased(FString layout_name, FString widget_name, Event.SenderIntIntMouseButton func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventMouseButtonReleased += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventMouseButtonReleased -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置鼠标双击按钮事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制方式</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventMouseButtonDoubleClick(FString layout_name, FString widget_name, Event.SenderVoid func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventMouseButtonDoubleClick += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventMouseButtonDoubleClick -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置鼠标失去焦点事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制方式</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventMouseLostFocus(FString layout_name, FString widget_name, Event.SenderFStringFString func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventMouseLostFocus += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventMouseLostFocus -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置鼠标焦点事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制方式</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventMouseSetFocus(FString layout_name, FString widget_name, Event.SenderFStringFString func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventMouseSetFocus += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventMouseSetFocus -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设施鼠标拖拽事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventMouseDrag(FString layout_name, FString widget_name, Event.SenderIntIntMouseButton func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventMouseDrag += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventMouseDrag -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置鼠标移动事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventMouseMove(FString layout_name, FString widget_name, Event.SenderIntInt func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventMouseMove += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventMouseMove -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置鼠标滚轮事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventMouseWheel(FString layout_name, FString widget_name, Event.SenderInt func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventMouseWheel += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventMouseWheel -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置键盘丢失焦点事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventKeyLostFocus(FString layout_name, FString widget_name, Event.SenderFStringFString func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventKeyLostFocus += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventKeyLostFocus -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置键盘焦点事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventKeySetFocus(FString layout_name, FString widget_name, Event.SenderFStringFString func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventKeySetFocus += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventKeySetFocus -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置按压键盘按钮事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventKeyButtonPressed(FString layout_name, FString widget_name, Event.SenderKeyCodeChar func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventKeyButtonPressed += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventKeyButtonPressed -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置释放键盘按钮事件
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventKeyButtonReleased(FString layout_name, FString widget_name, Event.SenderKeyCode func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventKeyButtonReleased += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventKeyButtonReleased -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置root鼠标改变焦点事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventRootMouseChangeFocus(FString layout_name, FString widget_name, Event.SenderBool func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventRootMouseChangeFocus += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventRootMouseChangeFocus -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置root键盘改变焦点事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventRootKeyChangeFocus(FString layout_name, FString widget_name, Event.SenderBool func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventRootKeyChangeFocus += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventRootKeyChangeFocus -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置工具提示框事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventToolTip(FString layout_name, FString widget_name, Event.SenderToolTipInfo func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventToolTip += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventToolTip -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置记录事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventTick(FString layout_name, FString widget_name, Event.SenderTick func, EventControl control)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                widget.EventTick += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                widget.EventTick -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
        }
        /// <summary>
        /// 用户界面滚动条类
        /// </summary>
        public static partial class UIScrollBar
        {

            /// <summary>
            /// 设置指定面板控件的滚动事件操作
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">滚动事件操作代理</param>
            /// <param name="control">控制事件控制方式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetEventScrollChangePosition(FString layout_name, FString widget_name, Event.SenderInt func, EventControl control)
            {
                ScrollBar sb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out sb);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                sb.EventScrollChangePosition += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                sb.EventScrollChangePosition -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
        }

        public static partial class UIItemBox
        {
            /// <summary>
            /// 设置请求对象坐标事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventRequestCoordItem(FString layout_name, FString widget_name, Event.SenderRefIntCoordBool func, EventControl control)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                ib.RequestCoordItem = func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                ib.RequestCoordItem = null;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 请求创建控件对象事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventRequestCreateWidgetItem(FString layout_name, FString widget_name, Event.SenderItemInfo func, EventControl control)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                ib.RequestCreateWidgetItem = func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                ib.RequestCreateWidgetItem = null;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置请求绘制对象事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetEventRequestDrawItem(FString layout_name, FString widget_name, Event.SenderItemInfoIBDrawInfo func, EventControl control)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                ib.RequestDrawItem = func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                ib.RequestDrawItem = null;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置选定接受对象事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetSelectItemAccept(FString layout_name, FString widget_name, Event.SenderInt func, EventControl control)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                ib.EventSelectItemAccept += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                ib.EventSelectItemAccept -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置改变对象坐标事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetChangeItemPosition(FString layout_name, FString widget_name, Event.SenderInt func, EventControl control)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                ib.EventChangeItemPosition += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                ib.EventChangeItemPosition -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置鼠标活动事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetMouseItemActivate(FString layout_name, FString widget_name, Event.SenderInt func, EventControl control)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                ib.EventMouseItemActivate += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                ib.EventMouseItemActivate -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置通知事件
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件委托</param>
            /// <param name="control">控制属性</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetNotifyItem(FString layout_name, FString widget_name, Event.SenderRefIBNotifyItemData func, EventControl control)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                ib.EventNotifyItem += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                ib.EventNotifyItem -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
        }
        /// <summary>
        /// 用户界面窗口类
        /// </summary>
        public static partial class UIWindow
        {
            /// <summary>
            /// 设置窗口按钮按下事件操作
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">按钮按下事件操作代理</param>
            /// <param name="control">按钮按下事件控制方式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetWindowButtonPressed(FString layout_name, FString widget_name, Event.SenderString func, EventControl control)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                window.EventWindowButtonPressed += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                window.EventWindowButtonPressed -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置窗口位置大小改变事件操作
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">窗口位置大小改变代理</param>
            /// <param name="control">窗口位置大小改变事件控制方式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
             public static ExecuteResult SetWindowChangeCoord(FString layout_name, FString widget_name, Event.SenderVoid func, EventControl control)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                window.EventWindowChangeCoord += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                window.EventWindowChangeCoord -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
        }

        /// <summary>
        /// 用户界面控件列表类
        /// </summary>
        public static partial class UIListBox
        {
            /// <summary>
            /// 设置鼠标双击或接收回车键的事件操作
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件操作代理</param>
            /// <param name="control">事件控制方式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetListSelectAccept(FString layout_name, FString widget_name, Event.SenderInt func, EventControl control)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                lb.EventListSelectAccept += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                lb.EventListSelectAccept -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置列表控件位置改变事件操作
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件操作代理</param>
            /// <param name="control">事件控制方式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetListChangePosition(FString layout_name, FString widget_name, Event.SenderInt func, EventControl control)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                lb.EventListChangePosition += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                lb.EventListChangePosition -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置子控件被选择事件操作
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件操作代理</param>
            /// <param name="control">事件控制方式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetListMouseItemActivate(FString layout_name, FString widget_name, Event.SenderInt func, EventControl control)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                lb.EventListMouseItemActivate += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                lb.EventListMouseItemActivate -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置鼠标滑过子控件的事件操作
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件操作代理</param>
            /// <param name="control">事件控制方式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetListMouseItemFocus(FString layout_name, FString widget_name, Event.SenderInt func, EventControl control)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                lb.EventListMouseItemFocus += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                lb.EventListMouseItemFocus -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
            /// <summary>
            /// 设置列表控件滚动事件操作
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="func">事件操作代理</param>
            /// <param name="control">事件控制方式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetListChangeScroll(FString layout_name, FString widget_name, Event.SenderInt func, EventControl control)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {

                    switch (control)
                    {
                        case EventControl.Add:
                            {
                                lb.EventListChangeScroll += func;
                            }
                            break;
                        case EventControl.Remove:
                            {
                                lb.EventListChangeScroll -= func;
                            }
                            break;
                    }
                }
                return ret;
            }
        }
    }
}
