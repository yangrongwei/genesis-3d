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
using System.Runtime.InteropServices;

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
            /// 设置颜色
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="colour">颜色</param>
            /// <returns></returns>
            public static ExecuteResult SetColour(FString layout_name, FString widget_name, Colour colour)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.Colour = colour;
                }
                return ret;
            }
            /// <summary>
            /// 获取客户坐标
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns></returns>
            public static IntCoord GetClientCoord(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.ClientCoord;
                }
                return new IntCoord();
            }
            /// <summary>
            /// 获取坐标
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns></returns>
            public static IntCoord GetCoord(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.Coord;
                }
                return new IntCoord();
            }
            /// <summary>
            /// 设置坐标
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="coord">坐标</param>
            public static void SetCoord(FString layout_name, FString widget_name, IntCoord coord)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.Coord = coord;
                }

            }
            /// <summary>
            /// 设置用户数据
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="data">数据</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetUserData(FString layout_name, FString widget_name, object data)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.UserData = data;
                }
                return ret;
            }
            /// <summary>
            /// 获取用户数据
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>用户数据</returns>
            public static object GetUserData(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.UserData;
                }
                return null;
            }
            /// <summary>
            /// 设置是否可见
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="visible">是否可见</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetVisible(FString layout_name, FString widget_name, bool visible)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.Visible = visible;
                }
                return ret;
            }
            /// <summary>
            /// 获取是否可见
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>是否可见</returns>
            public static bool GetVisible(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.Visible;
                }
                return false;
            }
            /// <summary>
            /// 获取可见继承
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>是否可见继承</returns>
            public static bool GetInheritedVisible(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.InheritedVisible;
                }
                return false;
            }
            /// <summary>
            /// 设置位置
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">坐标值</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetPosition(FString layout_name, FString widget_name, IntPoint value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.Position = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取位置
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>坐标</returns>
            public static IntPoint GetPosition(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.Position;
                }
                return new IntPoint();
            }
            /// <summary>
            /// 设置尺寸
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">尺寸大小</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetSize(FString layout_name, FString widget_name, IntSize value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.Size = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取尺寸
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>结果</returns>
            public static IntSize GetSize(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.Size;
                }
                return new IntSize();
            }
            /// <summary>
            /// 设置真实位置
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">坐标</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetRealPosition(FString layout_name, FString widget_name, FloatPoint value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.SetRealPosition(value);
                }
                return ret;
            }
            /// <summary>
            /// 设置真实尺寸
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">尺寸大小</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetRealSize(FString layout_name, FString widget_name, FloatSize value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.SetRealSize(value);
                }
                return ret;
            }
            /// <summary>
            /// 设置真实坐标
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">坐标值</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetRealCoord(FString layout_name, FString widget_name, FloatCoord value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.SetRealCoord(value);
                }
                return ret;
            }
            /// <summary>
            /// 获取绝对位置
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>位置</returns>
            public static IntPoint GetAbsolutePosition(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.AbsolutePosition;
                }
                return new IntPoint();
            }
            /// <summary>
            /// 获取绝对矩形区
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>矩形区域</returns>
            public static IntRect GetAbsoluteRect(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.AbsoluteRect;
                }
                return new IntRect();
            }
            /// <summary>
            /// 获取绝对坐标
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>坐标值</returns>
            public static IntCoord GetAbsoluteCoord(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.AbsoluteCoord;
                }
                return new IntCoord();
            }
            /// <summary>
            /// 设置对齐方式
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name"><控件名称/param>
            /// <param name="value">对其方式</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetAlign(FString layout_name, FString widget_name, Align value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.Align = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取对齐方式
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>对齐方式</returns>
            public static Align GetAlign(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.Align;
                }
                return Align.Default;
            }
            /// <summary>
            /// 设置需要提示框
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">是否需要</param>
            /// <returns>结果</returns>
            public static float GetAlpha(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.Alpha;
                }
                return 0.0f;
            }

            public static ExecuteResult SetAlpha(FString layout_name, FString widget_name,float alp)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.Alpha = alp;
                }
                return ret;
            }
            
            public static ExecuteResult SetNeedToolTip(FString layout_name, FString widget_name, bool value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.NeedToolTip = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取是否需要提示框
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>是否需要</returns>
            public static bool GetNeedToolTip(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.NeedToolTip;
                }
                return false;
            }
            /// <summary>
            /// 设置是否有指针
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">是否有指针</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetPointer(FString layout_name, FString widget_name, string value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.Pointer = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取是否有指针
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>是否有指针</returns>
            public static string GetPointer(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.Pointer;
                }
                return null;
            }

            /// <summary>
            /// 设置是否需要键盘焦点
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">是否需要</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetNeedKeyFocus(FString layout_name, FString widget_name, bool value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.NeedKeyFocus = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取是否需要键盘焦点
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>是否需要</returns>
            public static bool GetNeedKeyFocus(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.NeedKeyFocus;
                }
                return false;
            }
            /// <summary>
            /// 设置是否需要鼠标焦点
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">是否需要</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetNeedMouseFocus(FString layout_name, FString widget_name, bool value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.NeedMouseFocus = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取是否需要鼠标焦点
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>是否需要</returns>
            public static bool GetNeedMouseFocus(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.NeedMouseFocus;
                }
                return false;
            }
            /// <summary>
            /// 设置继承选择
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">是否继承选择</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetInheritsPick(FString layout_name, FString widget_name, bool value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.InheritsPick = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取是否继承选择
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>是否继承选择</returns>
            public static bool GetInheritsPick(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.InheritsPick;
                }
                return false;
            }
            /// <summary>
            /// 设置遮罩选择
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">是否选择</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetMaskPick(FString layout_name, FString widget_name, string value)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    widget.SetMaskPick(value);
                }
                return ret;
            }
            /// <summary>
            /// 
            /// </summary>
            /// <param name="layout_name"></param>
            /// <param name="widget_name"></param>
            /// <param name="point"></param>
            /// <param name="coord"></param>
            /// <returns></returns>
            public static bool IsMaskPickInside(FString layout_name, FString widget_name, IntPoint point, IntCoord coord)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.IsMaskPickInside(point, coord);
                }
                return false;
            }
            /// <summary>
            /// 获取root鼠标焦点
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>结果</returns>
            public static bool GetRootMouseFocus(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.RootMouseFocus;
                }
                return false;
            }
            /// <summary>
            /// 获取root键盘焦点
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>结果</returns>
            public static bool GetRootKeyFocus(FString layout_name, FString widget_name)
            {
                Widget widget = null;
                ExecuteResult ret = FindWidget(layout_name, widget_name, out widget);
                if (ExecuteResult.Success == ret)
                {
                    return widget.RootKeyFocus;
                }
                return false;
            }

        }
        /// <summary>
        /// 用户界面文字处理类
        /// </summary>
        public static class UITextBox
        {
            /// <summary>
            /// 设置文字内容
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="caption">文字内容</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetCaption(FString layout_name, FString widget_name, string caption)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    tb.Caption = caption;
                }
                return ret;
            }
            /// <summary>
            /// 获取文字内容
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>文字内容，若获取失败，则返回默认值</returns>
            public static string GetCaption(FString layout_name, FString widget_name)
            {

                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    return tb.Caption;
                }
                return null;
            }
            /// <summary>
            /// 设置文字颜色
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="colour">文字颜色值</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetTextColour(FString layout_name, FString widget_name, Colour colour)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    tb.TextColour = colour;
                }
                return ret;
            }
            /// <summary>
            /// 获取文字颜色
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>文字颜色，若获取失败，则返回默认值</returns>
            public static Colour GetTextColour(FString layout_name, FString widget_name)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    return tb.TextColour;
                }
                return default(Colour);
            }
            /// <summary>
            /// 获取文字区域
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>文字区域，若获取失败，则返回默认值</returns>
            public static IntCoord GetTextRegion(FString layout_name, FString widget_name)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    return tb.TextRegion;
                }
                return default(IntCoord);
            }
            /// <summary>
            /// 获取文字大小
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>文字大小，若获取失败，则返回默认值</returns>
            public static IntSize GetTextSize(FString layout_name, FString widget_name)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    return tb.TextSize;
                }
                return default(IntSize);
            }
            /// <summary>
            /// 设置文字名称
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">文字名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetFontName(FString layout_name, FString widget_name, string value)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    tb.FontName = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取文字名称
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>文字名称，若获取失败，则返回默认值</returns>
            public static string GetFontName(FString layout_name, FString widget_name)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    return tb.FontName;
                }
                return default(string);
            }
            /// <summary>
            /// 设置文字高度
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">文字高度值</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetFontHeight(FString layout_name, FString widget_name, int value)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    tb.FontHeight = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取文字高度
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>文字高度，若获取失败，则返回默认值</returns>
            public static int GetFontHeight(FString layout_name, FString widget_name)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    return tb.FontHeight;
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 设置文字对齐方式
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">文字对齐方式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetTextAlign(FString layout_name, FString widget_name, Align value)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    tb.TextAlign = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取文字对齐方式
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>文字对齐方式，若获取失败，则返回默认值</returns>
            public static Align GetTextAlign(FString layout_name, FString widget_name)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    return tb.TextAlign;
                }
                return Align.Default;
            }
            /// <summary>
            /// 用替换的方式设置文字控件描述
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">文字控件描述</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetCaptionWithReplacing(FString layout_name, FString widget_name, string value)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    tb.SetCaptionWithReplacing(value);
                }
                return ret;
            }
            /// <summary>
            /// 设置文字阴影颜色
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">文字阴影颜色</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetTextShadowColour(FString layout_name, FString widget_name, Colour value)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    tb.TextShadowColour = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取文字阴影颜色
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>文字阴影颜色，若获取失败，则返回默认值</returns>
            public static Colour GetTextShadowColour(FString layout_name, FString widget_name)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    return tb.TextShadowColour;
                }
                return default(Colour);
            }
            /// <summary>
            /// 设置文字阴影标志
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">文字阴影标志</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetTextShadow(FString layout_name, FString widget_name, bool value)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    tb.TextShadow = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取文字阴影标志
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>文字阴影标志，若获取失败，则返回默认值</returns>
            public static bool GetTextShadow(FString layout_name, FString widget_name)
            {
                TextBox tb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out tb);
                if (ExecuteResult.Success == ret)
                {
                    return tb.TextShadow;
                }
                return default(bool);
            }

        }
        /// <summary>
        /// 用户界面按钮类
        /// </summary>
        public static class UIButton
        {
            /// <summary>
            /// 设置面板控件是否选中的状态
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">状态表示值</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetStateSelected(FString layout_name, FString widget_name, bool value)
            {
                Button btn = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out btn);
                if (ExecuteResult.Success == ret)
                {
                    btn.StateSelected = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取面板控件是否选中的状态
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static bool GetStateSelected(FString layout_name, FString widget_name)
            {
                Button btn = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out btn);
                if (ExecuteResult.Success == ret)
                {
                    return btn.StateSelected;
                }
                return false;
            }
            /// <summary>
            /// 设置是否支持图片模式
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">图片模式是否允许</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetModeImage(FString layout_name, FString widget_name, bool value)
            {
                Button btn = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out btn);
                if (ExecuteResult.Success == ret)
                {
                    btn.ModeImage = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取是否支持图片模式的状态
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>若获取到指定的控件，则返回控件的设置状态；否则，返回false</returns>
            public static bool GetModeImage(FString layout_name, FString widget_name)
            {
                Button btn = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out btn);
                if (ExecuteResult.Success == ret)
                {
                    return btn.ModeImage;
                }
                return false;
            }
            /// <summary>
            /// 设置图片资源
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件面板</param>
            /// <param name="value">图片资源</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetImageResource(FString layout_name, FString widget_name, string value)
            {
                Button btn = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out btn);
                if (ExecuteResult.Success == ret)
                {
                    btn.SetImageResource(value);
                }
                return ret;
            }
            /// <summary>
            /// 设置图片所属分组
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">图片分组名</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetImageGroup(FString layout_name, FString widget_name, string value)
            {
                Button btn = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out btn);
                if (ExecuteResult.Success == ret)
                {
                    btn.SetImageGroup(value);
                }
                return ret;
            }
            /// <summary>
            /// 设置图片名称
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">图片名</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetImageName(FString layout_name, FString widget_name, string value)
            {
                Button btn = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out btn);
                if (ExecuteResult.Success == ret)
                {
                    btn.SetImageName(value);
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
            /// 设置窗口平滑是否可见
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="_value">窗口平滑可见标志</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetVisibleSmooth(FString layout_name, FString widget_name, bool _value)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    window.SetVisibleSmooth(_value);
                }
                return ret;
            }
            /// <summary>
            /// 消除窗口平滑
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult DestroySmooth(FString layout_name, FString widget_name)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    window.DestroySmooth();
                }
                return ret;
            }
            /// <summary>
            /// 设置窗口自动透明模式标志
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">窗口自动透明模式标志</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetAutoAlpha(FString layout_name, FString widget_name, bool value)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    window.AutoAlpha = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取窗口自动透明模式标志
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>窗口自动透明模式标志，若获取失败，则返回默认值</returns>
            public static bool GetAutoAlpha(FString layout_name, FString widget_name)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    return window.AutoAlpha;
                }
                return default(bool);
            }
            /// <summary>
            /// 设置窗口描述
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">窗口描述</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetCaption(FString layout_name, FString widget_name, string value)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    window.Caption = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取窗口描述
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>窗口描述，若获取失败，则返回默认值</returns>
            public static string GetCaption(FString layout_name, FString widget_name)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    return window.Caption;
                }
                return default(string);
            }
            /// <summary>
            /// 获取窗口描述控件
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>窗口描述控件，若获取失败，则返回默认值</returns>
            public static FString GetCaptionWidget(FString layout_name, FString widget_name)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    TextBox text_box = window.GetCaptionWidget();
                    if (null != text_box)
                    {
                        return text_box.Name;
                    }
                }
                return default(FString);
            }
            /// <summary>
            /// 设置窗口的最小尺寸
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">窗口尺寸值</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetMinSize(FString layout_name, FString widget_name, IntSize value)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    window.MinSize = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取窗口的最小尺寸
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>窗口的最小尺寸，若获取失败，则返回默认值</returns>
            public static IntSize GetMinSize(FString layout_name, FString widget_name)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    return window.MinSize;
                }
                return default(IntSize);
            }
            /// <summary>
            /// 设置窗口的最大尺寸
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">窗口尺寸值</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetMaxSize(FString layout_name, FString widget_name, IntSize value)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    window.MaxSize = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取窗口的最大尺寸
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>窗口的最大尺寸，若获取失败，则返回默认值</returns>
            public static IntSize GetMaxSize(FString layout_name, FString widget_name)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    return window.MaxSize;
                }
                return default(IntSize);
            }
            /// <summary>
            /// 设置边框模式
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">边框模式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetSnap(FString layout_name, FString widget_name, bool value)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    window.Snap = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取边框模式
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>边框模式，若获取失败，则返回默认值</returns>
            public static bool GetSnap(FString layout_name, FString widget_name)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    return window.Snap;
                }
                return default(bool);
            }
            /// <summary>
            /// 获取窗口的可移动区域
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>窗口的可移动区域，若获取失败，则返回默认值</returns>
            public static IntCoord GetActionScale(FString layout_name, FString widget_name)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    return window.ActionScale;
                }
                return default(IntCoord);
            }
            /// <summary>
            /// 设置窗口可移动的状态
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">状态值参数</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetMovable(FString layout_name, FString widget_name, bool value)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    window.Movable = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取窗口是否可移动状态
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>窗口是否可移动状态，若获取失败，则返回默认值</returns>
            public static bool GetMovable(FString layout_name, FString widget_name)
            {
                Window window = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out window);
                if (ExecuteResult.Success == ret)
                {
                    return window.Movable;
                }
                return default(bool);
            }

            //public static ExecuteResult (FString layout_name, FString widget_name)
            //{
            //    Window window = null;
            //    ExecuteResult ret = FindUI(layout_name, widget_name, out window);
            //    if (ExecuteResult.Success == ret)
            //    {
            //        window.;
            //    }
            //    return ret;
            //}
        }

        public static class UIEditBox
        {
        }
        /// <summary>
        /// 用户界面容器类
        /// </summary>
        public static class UIDDContainer
        {
            /// <summary>
            /// 获取指定面板控件的拖拽模式标志
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>若获取成功，返回该拖拽标志；否则，返回false</returns>
            public static bool GetNeedDragDrop(FString layout_name, FString widget_name)
            {
                DDContainer dd = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out dd);
                if (ExecuteResult.Success == ret)
                {
                    return dd.NeedDragDrop;
                }
                return false;
            }
            /// <summary>
            /// 设置指定面板的拖拽标志。若找到指定面板控件，则设置拖拽标志。最后返回执行结果
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">需要设置的拖拽标志</param>
            /// <returns>执行结果，若结果为Success，则表示设置面板控件的拖拽标志成功；否则，表示设置失败</returns>
            public static ExecuteResult GetNeedDragDrop(FString layout_name, FString widget_name, bool value)
            {
                DDContainer dd = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out dd);
                if (ExecuteResult.Success == ret)
                {
                    dd.NeedDragDrop = value;
                }
                return ret;
            }
            /// <summary>
            /// 释放指定面板控件的拖拽操作
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示释放成功；否则，表示释放失败</returns>
            public static ExecuteResult RestDrop(FString layout_name, FString widget_name)
            {
                DDContainer dd = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out dd);
                if (ExecuteResult.Success == ret)
                {
                    dd.RestDrop();
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
            /// 获取滚动条的位置
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>滚动条的位置</returns>
            public static int GetScrollPosition(FString layout_name, FString widget_name)
            {
                ScrollBar sb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out sb);
                if (ExecuteResult.Success == ret)
                {
                    return sb.ScrollPosition;
                }
                return 0;
            }
            /// <summary>
            /// 获取滚动条的滚动范围
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>滚动条的滚动范围</returns>
            public static int GetScrollRange(FString layout_name, FString widget_name)
            {
                ScrollBar sb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out sb);
                if (ExecuteResult.Success == ret)
                {
                    return sb.ScrollRange;
                }
                return 0;
            }
        }
        /// <summary>
        /// 用户界面图像处理控件类
        /// </summary>
        public static partial class UIImageBox
        {
            /// <summary>
            /// 设置子控件资源
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="name">控件使用到的资源</param>
            /// <returns>若资源设置成功，则返回true；否则，返回false</returns>
            public static bool SetItemResource(FString layout_name, FString widget_name, string name)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    return ib.SetItemResource(name);
                }
                return false;
            }
            /// <summary>
            /// 设置子控件组名称
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="name">组名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetItemGroup(FString layout_name, FString widget_name, string name)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetItemGroup(name);
                }
                return ret;
            }
            /// <summary>
            /// 设置图片名称
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="name">图片名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetItemName(FString layout_name, FString widget_name, string name)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetItemName(name);
                }
                return ret;
            }
            /// <summary>
            /// 设置图片
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="texture">纹理信息</param>
            /// <param name="coord">区域信息</param>
            /// <param name="tile">分片信息</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetImageInfo(FString layout_name, FString widget_name, String texture, IntCoord coord, IntSize tile)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetImageInfo(texture, coord, tile);
                }
                return ret;
            }
            /// <summary>
            /// 设置图片纹理
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="texture">图片纹理</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetImageTexture(FString layout_name, FString widget_name, String texture)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetImageTexture(texture);
                }
                return ret;
            }
            /// <summary>
            /// 设置图片纹理尺寸
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value"></param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetImageRect(FString layout_name, FString widget_name, IntRect value)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetImageRect(value);
                }
                return ret;
            }
            /// <summary>
            /// 设置图片区域
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="coord">图片区域</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetImageCoord(FString layout_name, FString widget_name, IntCoord coord)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetImageCoord(coord);
                }
                return ret;
            }
            /// <summary>
            /// 设置图片分片尺寸
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="tile">图片分片尺寸</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetImageTile(FString layout_name, FString widget_name, IntSize tile)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetImageTile(tile);
                }
                return ret;
            }
            /// <summary>
            /// 设置图片索引
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">图片索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetImageIndex(FString layout_name, FString widget_name, int index)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetImageIndex(index);
                }
                return ret;
            }
            /// <summary>
            /// 获取图片索引
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>图片索引</returns>
            public static int GetImageIndex(FString layout_name, FString widget_name)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    return ib.GetImageIndex();
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 获取子控件的数量
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>子控件的数量</returns>
            public static int GetItemCount(FString layout_name, FString widget_name)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    return ib.GetItemCount();
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 选择指定的子控件索引
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetItemSelect(FString layout_name, FString widget_name, int index)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetItemSelect(index);
                }
                return ret;
            }
            /// <summary>
            /// 获取被选择的子控件索引
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>被选择的子控件索引</returns>
            public static int GetItemSelect(FString layout_name, FString widget_name)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    return ib.GetItemSelect();
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 重置选择的子控件
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult ResetItemSelect(FString layout_name, FString widget_name)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.ResetItemSelect();
                }
                return ret;
            }
            /// <summary>
            /// 插入子控件
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="item">图片纹理映射坐标</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult InsertItem(FString layout_name, FString widget_name, int index, IntCoord item)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.InsertItem(index, item);
                }
                return ret;
            }
            /// <summary>
            /// 添加子控件
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="item">图片纹理映射坐标</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult AddItem(FString layout_name, FString widget_name, IntCoord item)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.AddItem(item);
                }
                return ret;
            }
            /// <summary>
            /// 修改子控件
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="item">图片纹理映射坐标</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetItem(FString layout_name, FString widget_name, int index, IntCoord item)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetItem(index, item);
                }
                return ret;
            }
            /// <summary>
            /// 删除指定的子控件
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult DeleteItem(FString layout_name, FString widget_name, int index)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.DeleteItem(index);
                }
                return ret;
            }
            /// <summary>
            /// 删除所有的子控件
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult DeleteAllItems(FString layout_name, FString widget_name)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.DeleteAllItems();
                }
                return ret;
            }
            /// <summary>
            /// 添加子控件帧
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="item">图片纹理映射坐标</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult AddItemFrame(FString layout_name, FString widget_name, int index, IntCoord item)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.AddItemFrame(index, item);
                }
                return ret;
            }
            /// <summary>
            /// 插入子控件帧
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="indexFrame">帧索引</param>
            /// <param name="item">图片纹理映射坐标</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult InsertItemFrame(FString layout_name, FString widget_name, int index, int indexFrame, IntCoord item)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.InsertItemFrame(index, indexFrame, item);
                }
                return ret;
            }
            /// <summary>
            /// 添加子控件帧的一个拷贝
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="indexSourceFrame">源帧索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult AddItemFrameDublicate(FString layout_name, FString widget_name, int index, int indexSourceFrame)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.AddItemFrameDublicate(index, indexSourceFrame);
                }
                return ret;
            }
            /// <summary>
            /// 插入子控件帧的一个拷贝
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="indexFrame">帧索引</param>
            /// <param name="indexSourceFrame">源帧索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult InsertItemFrameDublicate(FString layout_name, FString widget_name, int index, int indexFrame, int indexSourceFrame)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.InsertItemFrameDublicate(index, indexFrame, indexSourceFrame);
                }
                return ret;
            }
            /// <summary>
            /// 修改子控件对应的帧
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="indexFrame">帧索引</param>
            /// <param name="item">图片纹理映射坐标</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetItemFrame(FString layout_name, FString widget_name, int index, int indexFrame, IntCoord item)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetItemFrame(index, indexFrame, item);
                }
                return ret;
            }
            /// <summary>
            /// 删除子控件对应的帧
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="indexFrame">帧索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult DeleteItemFrame(FString layout_name, FString widget_name, int index, int indexFrame)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.DeleteItemFrame(index, indexFrame);
                }
                return ret;
            }
            /// <summary>
            /// 删除子控件所有的帧
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult DeleteAllItemFrames(FString layout_name, FString widget_name, int index)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.DeleteAllItemFrames(index);
                }
                return ret;
            }
            /// <summary>
            /// 设置图片子控件帧速率
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="rate">帧速率</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetItemFrameRate(FString layout_name, FString widget_name, int index, float rate)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetItemFrameRate(index, rate);
                }
                return ret;
            }
            /// <summary>
            /// 获取图片子控件帧速率
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>图片子控件帧速率</returns>
            public static float GetItemFrameRate(FString layout_name, FString widget_name, int index)
            {
                ImageBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    return ib.GetItemFrameRate(index);
                }
                return 0;
            }


        }

        public static partial class UIItemBox
        {
            /// <summary>
            /// 添加项目
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="obj">添加项</param>
            /// <returns>结果</returns>
            public static ExecuteResult AddItem(FString layout_name, FString widget_name, object obj)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.AddItem(obj);
                }
                return ret;
            }
            /// <summary>
            /// 获取项目数据
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">索引</param>
            /// <returns>项目数据</returns>
            public static object GetItemData(FString layout_name, FString widget_name, int index)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    return ib.GetItemDataAt(index);
                }
                return null;
            }
            /// <summary>
            /// 删除所有项目
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>结果</returns>
            public static ExecuteResult RemoveAllItems(FString layout_name, FString widget_name)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.RemoveAllItems();
                }
                return ret;
            }
            /// <summary>
            /// 获取项目数量
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>项目数量</returns>
            public static int GetItemCount(FString layout_name, FString widget_name)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    return ib.ItemCount;
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 在指定位置插入项目
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">指定位置</param>
            /// <param name="data">项目数据</param>
            /// <returns>结果</returns>
            public static ExecuteResult InsetItemAt(FString layout_name, FString widget_name, int index, object data)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.InsetItemAt(index, data);
                }
                return ret;
            }
            /// <summary>
            /// 删除指定位置的项目
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">指定位置</param>
            /// <returns>结果</returns>
            public static ExecuteResult RemoveItemAt(FString layout_name, FString widget_name, int index)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.RemoveItemAt(index);
                }
                return ret;
            }
            /// <summary>
            /// 重绘指定位置的项目
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">指定位置</param>
            /// <returns>结果</returns>
            public static ExecuteResult RedrawItemAt(FString layout_name, FString widget_name, int index)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.RedrawItemAt(index);
                }
                return ret;
            }
            /// <summary>
            /// 重绘所有项
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>结果</returns>
            public static ExecuteResult RedrawAllItems(FString layout_name, FString widget_name)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.RedrawAllItems();
                }
                return ret;
            }
            /// <summary>
            /// 返回选中项目的索引
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>位置索引</returns>
            public static int GetIndexSelect(FString layout_name, FString widget_name)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    return ib.IndexSelect;
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 设置选中项目的索引
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">索引</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetIndexSelect(FString layout_name, FString widget_name, int index)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.IndexSelect = index;
                }
                return ret;
            }
            /// <summary>
            /// 清除选中项索引
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>结果</returns>
            public static ExecuteResult ClearIndexSelect(FString layout_name, FString widget_name)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.ClearIndexSelect();
                }
                return ret;
            }
            /// <summary>
            /// 设置索引所对应项的数据
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">索引</param>
            /// <param name="data">数据</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetItemDataAt(FString layout_name, FString widget_name, int index, object data)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.SetItemDataAt(index, data);
                }
                return ret;
            }
            /// <summary>
            /// 清除索引所对应项的数据
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">索引</param>
            /// <returns>结果</returns>
            public static ExecuteResult ClearItemDataAt(FString layout_name, FString widget_name, int index)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.CleartemDataAt(index);
                }
                return ret;
            }
            /// <summary>
            /// 设置垂直对齐
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="value">是否对齐</param>
            /// <returns>结果</returns>
            public static ExecuteResult SetVerticalAlignment(FString layout_name, FString widget_name, bool value)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.VerticalAlignment = value;
                }
                return ret;
            }
            /// <summary>
            /// 获取是否垂直对齐
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>是否对齐</returns>
            public static bool GetVerticalAlignment(FString layout_name, FString widget_name)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    return ib.VerticalAlignment;
                }
                return false;
            }
            /// <summary>
            /// 获取控件中的索引
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="widget_find">要找的项目</param>
            /// <returns>索引</returns>
            public static int GetIndexByWidget(FString layout_name, FString widget_name, FString widget_find)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    Widget widget = null;
                    if (ExecuteResult.Success == FindWidget(layout_name, widget_find, out widget))
                    {
                        return ib.GetIndexByWidget(widget);
                    }
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 获取控件拖拽操作
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>拖拽的控件名称</returns>
            public static FString GetWidgetDrag(FString layout_name, FString widget_name)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    Widget widget = ib.GetWidgetDrag();
                    if (null != widget)
                    {
                        return widget.Name;
                    }

                }
                return null;
            }
            /// <summary>
            /// 获取控件拖拽操作
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">索引</param>
            /// <returns>拖拽的控件名称</returns>
            public static FString GetWidgetDrag(FString layout_name, FString widget_name, int index)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    Widget widget = ib.GetWidgetByIndex(index);
                    if (null != widget)
                    {
                        return widget.Name;
                    }
                }
                return null;
            }
            /// <summary>
            /// 重置拖拽
            /// </summary>
            /// <param name="layout_name">界面名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>结果</returns>
            public static ExecuteResult ResetDrag(FString layout_name, FString widget_name)
            {
                ItemBox ib = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out ib);
                if (ExecuteResult.Success == ret)
                {
                    ib.ResetDrag();
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
            /// 获取子控件数量
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>子控件数量，若指定的面板控件未找到，则返回一个非法值</returns>
            public static int GetItemCount(FString layout_name, FString widget_name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.ItemCount;
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 插入子控件到控件列表中
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">列表索引</param>
            /// <param name="name">子控件名称</param>
            /// <param name="data">对象数据</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult InsertItemAt(FString layout_name, FString widget_name, int index, string name, object data)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.InsertItemAt(index, name, data);
                }
                return ret;
            }
            /// <summary>
            /// 添加一个控件到控件列表中
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="name">子控件名称</param>
            /// <param name="data">对象数据</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult AddItem(FString layout_name, FString widget_name, string name, object data)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.AddItem(name, data);
                }
                return ret;
            }
            /// <summary>
            /// 删除指定索引的子控件
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult RemoveItemAt(FString layout_name, FString widget_name, int index)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.RemoveItemAt(index);
                }
                return ret;
            }
            /// <summary>
            /// 移除所有子控件
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult RemoveAllItems(FString layout_name, FString widget_name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.RemoveAllItems();
                }
                return ret;
            }
            /// <summary>
            /// 交换子控件
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index1">子控件索引</param>
            /// <param name="index2">子控件索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SwapItemsAt(FString layout_name, FString widget_name, int index1, int index2)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.SwapItemsAt(index1, index2);
                }
                return ret;
            }
            /// <summary>
            /// 通过名称查询子控件的索引
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="name">需要查询子控件的名称</param>
            /// <returns>被查询的子控件索引</returns>
            public static int FindItemIndexWith(FString layout_name, FString widget_name, string name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.FindItemIndexWith(name);
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 获取选中的子控件索引
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>选中的子控件索引，若未发现该控件，则返回一个非法的值</returns>
            public static int GetIndexSelected(FString layout_name, FString widget_name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.IndexSelected;
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 设置选中的索引
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">选中的子控件索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetIndexSelected(FString layout_name, FString widget_name, int index)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.IndexSelected = index;
                }
                return ret;
            }
            /// <summary>
            /// 清除选中的索引
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult ClearIndexSelected(FString layout_name, FString widget_name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.ClearIndexSelected();
                }
                return ret;
            }
            /// <summary>
            /// 设置子控件数据
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="data">子控件数据</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetItemDataAt(FString layout_name, FString widget_name, int index, object data)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.SetItemDataAt(index, data);
                }
                return ret;
            }
            /// <summary>
            /// 清除子控件数据
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult ClearItemDataAt(FString layout_name, FString widget_name, int index)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.ClearItemDataAt(index);
                }
                return ret;
            }
            /// <summary>
            /// 获取子控件数据
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>子控件数据</returns>
            public static object GetItemDataAt(FString layout_name, FString widget_name, int index)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.GetItemDataAt(index);
                }
                return default(object);
            }
            /// <summary>
            /// 获取子控件数据
            /// </summary>
            /// <typeparam name="T">类模版参数</typeparam>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>子控件数据</returns>
            public static T GetItemDataAt<T>(FString layout_name, FString widget_name, int index)
                where T : class
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.GetItemDataAt<T>(index);
                }
                return default(T);
            }
            /// <summary>
            /// 设置子控件名称
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="name">子控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetItemNameAt(FString layout_name, FString widget_name, int index, string name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.SetItemNameAt(index, name);
                }
                return ret;
            }
            /// <summary>
            /// 获取子控件的名称
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>子控件的名称，若未找到该控件，则返回一个默认的名称</returns>
            public static string GetItemNameAt(FString layout_name, FString widget_name, int index)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.GetItemNameAt(index);
                }
                return default(string);
            }
            /// <summary>
            /// 设置到指定的子控件上
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult BeginToItemAt(FString layout_name, FString widget_name, int index)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.BeginToItemAt(index);
                }
                return ret;
            }
            /// <summary>
            /// 设置到第一个子控件上
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult BeginToItemFirst(FString layout_name, FString widget_name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.BeginToItemFirst();
                }
                return ret;
            }
            /// <summary>
            /// 设置到最后一个子控件上
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult BeginToItemLast(FString layout_name, FString widget_name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.BeginToItemLast();
                }
                return ret;
            }
            /// <summary>
            /// 设置到被选中的子控件上
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult BeginToItemSelected(FString layout_name, FString widget_name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.BeginToItemSelected();
                }
                return ret;
            }
            /// <summary>
            /// 设置子控件是否可见
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <param name="fill">状态填充参数</param>
            /// <returns>可见状态，若未找到该控件，则返回一个默认的可见状态</returns>
            public static bool IsItemVisibleAt(FString layout_name, FString widget_name, int index, bool fill)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.IsItemVisibleAt(index, fill);
                }
                return default(bool);
            }
            /// <summary>
            /// 返回子控件是否可见
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="index">子控件索引</param>
            /// <returns>可见状态，若未找到该控件，则返回一个默认的可见状态</returns>
            public static bool IsItemVisibleAt(FString layout_name, FString widget_name, int index)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.IsItemVisibleAt(index);
                }
                return default(bool);
            }
            /// <summary>
            /// 设置控件是否可见
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="fill">状态填充参数</param>
            /// <returns>可见状态，若未找到该控件，则返回一个默认的可见状态</returns>
            public static bool IsItemSelectedVisible(FString layout_name, FString widget_name, bool fill)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.IsItemSelectedVisible(fill);
                }
                return default(bool);
            }
            /// <summary>
            /// 返回控件是否可见
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>可见状态，若未找到该控件，则返回一个默认的可见状态</returns>
            public static bool IsItemSelectedVisible(FString layout_name, FString widget_name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.IsItemSelectedVisible();
                }
                return default(bool);
            }
            /// <summary>
            /// 设置控件是否可见
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="visible">是否可见参数</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetScrollVisible(FString layout_name, FString widget_name, bool visible)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.SetScrollVisible(visible);
                }
                return ret;
            }
            /// <summary>
            /// 设置列表控件的位置
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="position">位置参数</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult SetScrollPosition(FString layout_name, FString widget_name, int position)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    lb.SetScrollPosition(position);
                }
                return ret;
            }
            /// <summary>
            /// 获取列表控件的最佳高度
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>列表控件的最佳高度，若未找到该控件，则返回一个非法值</returns>
            public static int GetOptimalHeight(FString layout_name, FString widget_name)
            {
                ListBox lb = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out lb);
                if (ExecuteResult.Success == ret)
                {
                    return lb.OptimalHeight;
                }
                return Util.UNVALID_COUNT;
            }
        }
        /// <summary>
        /// 用户界面布局控件类
        /// </summary>
        public static class UICanvas
        {
            /// <summary>
            /// 获取指定纹理的实际宽度
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>若找到指定的控件，则返回该纹理实际宽度；否则，返回一个非法值</returns>
            public static int GetTextureRealWidth(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    return c.TextureRealWidth;
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 获取指定纹理的实际高度
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>若找到指定的控件，则返回该纹理实际高度；否则，返回一个非法值</returns>
            public static int GetTextureRealHeight(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    return c.TextureRealHeight;
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 获取指定纹理的资源宽度
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>若找到指定的控件，则返回该纹理资源宽度；否则，返回一个非法值</returns>
            public static int GetTextureSrcWidth(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    return c.TextureSrcWidth;
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 获取指定纹理的资源高度
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>若找到指定的控件，则返回该纹理资源高度；否则，返回一个非法值</returns>
            public static int GetTextureSrcHeight(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    return c.TextureSrcHeight;
                }
                return Util.UNVALID_COUNT;
            }
            /// <summary>
            /// 获取指定面板控件的纹理格式
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>若找到指定的控件，则返回该纹理格式；否则，返回一个未知的纹理格式值</returns>
            public static PixelFormat GetTextureFormat(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    return c.TextureFormat;
                }
                return PixelFormat.Unknow;
            }
            /// <summary>
            /// 返回缩放模式
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>返回指定控件的缩放模式，若控件未找到，则返回默认的缩放模式</returns>
            public static TextureResizeMode GetResizeMode(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    return c.ResizeMode;
                }
                return default(TextureResizeMode);
            }
            /// <summary>
            /// 返回纹理是否存在资源尺寸的状态
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>若面板控件有资源尺寸，则返回true；否则，返回false</returns>
            public static bool IsTextureSrcSize(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    return c.IsTextureSrcSize;
                }
                return false;
            }
            /// <summary>
            /// 返回纹理是否本创建的状态
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>若面板控件已经创建纹理，则返回true；否则，返回false</returns>
            public static bool IsTextureCreated(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    return c.IsTextureCreated;
                }
                return false;
            }
            /// <summary>
            /// 返回是否具有纹理的状态
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>若面板控件具有纹理，则返回true；否则，返回false</returns>
            public static bool IsTextureManaged(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    return c.IsTextureManaged;
                }
                return false;
            }
            /// <summary>
            /// 创建指定控件的纹理
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="_resizeMode">缩放模式</param>
            /// <param name="_usage">使用标志</param>
            /// <param name="_format">像素格式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult CreateTexture(FString layout_name, FString widget_name, TextureResizeMode _resizeMode, TextureUsage _usage, PixelFormat _format)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    c.CreateTexture(_resizeMode, _usage, _format);
                }
                return ret;
            }
            /// <summary>
            /// 创建指定控件的纹理
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="_width">设置的宽度</param>
            /// <param name="_height">设置的高度</param>
            /// <param name="_resizeMode">缩放模式</param>
            /// <param name="_usage">使用标志</param>
            /// <param name="_format">像素格式</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult CreateTexture(FString layout_name, FString widget_name, int _width, int _height, TextureResizeMode _resizeMode, TextureUsage _usage, PixelFormat _format)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    c.CreateTexture(_width, _height, _resizeMode, _usage, _format);
                }
                return ret;
            }
            /// <summary>
            /// 创建指定控件的纹理
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <param name="rtt">需要设置的纹理对象</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult CreateTexture(FString layout_name, FString widget_name, ScriptRuntime.RenderToTexture rtt)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    c.CreateTexture(rtt);
                }
                return ret;
            }
            /// <summary>
            /// 销毁指定控件的纹理
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult DestroyTexture(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    c.DestroyTexture();
                }
                return ret;
            }
            /// <summary>
            /// 更新指定控件的纹理
            /// </summary>
            /// <param name="layout_name">面板名称</param>
            /// <param name="widget_name">控件名称</param>
            /// <returns>执行结果，若结果为Success，则表示操作成功；否则，表示操作失败</returns>
            public static ExecuteResult UpdateTexture(FString layout_name, FString widget_name)
            {
                Canvas c = null;
                ExecuteResult ret = FindUI(layout_name, widget_name, out c);
                if (ExecuteResult.Success == ret)
                {
                    c.UpdateTexture();
                }
                return ret;
            }
            public const TextureUsage DefaultTextureUsage = Canvas.DefaultTextureUsage;
            public const PixelFormat DefaultTextureFormat = Canvas.DefaultTextureFormat;
        }
    }
}
