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
        /// 注册界面(Layout)函数
        /// </summary>
        /// <param name="layout_name">你为这个界面起的名字(会作为后面界面操作的索引关键字)</param>
        /// <param name="file_name">这个界面的.layout文件名</param>
        /// <param name="delay_load">是否延时加载</param>
        /// <param name="visible">是否默认可见</param>
        public static ExecuteResult RegisterLayout(FString layout_name, String file_name, bool delay_load, bool visible)
        {
            if (sRegWinTable.ContainKey(layout_name))
            {
                return setResult(ExecuteResult.ReregError);
            }
            Layout layout = new Layout(layout_name, file_name, visible);
            sRegWinTable.Add(layout);
            if (!delay_load)
            {
                layout.Load();
            }
            return setResult(ExecuteResult.Success);
        }
        /// <summary>
        /// 注册界面(Layout)函数
        /// </summary>
        /// <param name="parent_layout_name">父界面名称</param>
        /// <param name="parent_widget_name">挂载在父界面的具体哪一个UI控件之下</param>
        /// <param name="layout_name">你为这个界面起的名字(会作为后面界面操作的索引关键字)</param>
        /// <param name="file_name">这个界面的.layout文件名</param>
        /// <param name="delay_load">是否延时加载</param>
        /// <param name="visible">是否默认可见</param>
        public static ExecuteResult RegisterLayout(FString parent_layout_name, FString parent_widget_name, FString layout_name, String file_name, bool delay_load, bool visible)
        {
            if (sRegWinTable.ContainKey(layout_name))
            {
                return setResult(ExecuteResult.ReregError);
            }
            Layout parent_layout = null;
            Widget parent_widget = null;
            if (sRegWinTable.GetLayout(parent_layout_name, out parent_layout))
            {
                if (!parent_layout.IsLoaded)
                {
                    parent_layout.Load();
                }
                if (null == parent_widget_name)
                {
                    parent_widget = parent_layout.Root;
                }
                else
                {
                    parent_layout.FindWidget(parent_widget_name, out parent_widget);
                }
                Layout layout = new Layout(parent_widget, layout_name, file_name, visible);
                sRegWinTable.Add(layout);
                if (!delay_load)
                {
                    layout.Load();
                }
            }
            return setResult(ExecuteResult.Success);
        }
        /// <summary>
        /// 未注册界面
        /// </summary>
        /// <param name="layout_name">界面名称</param>
        public static void UnregisterLayout(FString layout_name)
        {
            Layout layout;
            if (sRegWinTable.GetLayout(layout_name, out layout))
            {
                sRegWinTable.Remove(layout_name);
                layout.Unload();
            }
        }
        /// <summary>
        /// 加载界面资源
        /// </summary>
        /// <param name="layout_name">界面名称</param>
        /// <returns>结果</returns>
        public static ExecuteResult LoadLayoutResource(FString layout_name)
        {
            Layout layout;
            if (sRegWinTable.GetLayout(layout_name, out layout))
            {
                if (!layout.IsLoaded)
                {
                    layout.Load();
                }
                return setResult(ExecuteResult.Success);
            }
            return setResult(ExecuteResult.LayoutNotExist);
        }
        /// <summary>
        /// 卸载界面资源
        /// </summary>
        /// <param name="layout_name">界面名称</param>
        /// <returns>结果</returns>
        public static ExecuteResult UnloadLayoutResource(FString layout_name)
        {
            Layout layout;
            if (sRegWinTable.GetLayout(layout_name, out layout))
            {
                layout.Unload();
                return setResult(ExecuteResult.Success);
            }
            return setResult(ExecuteResult.LayoutNotExist);
        }
        /// <summary>
        /// 重载界面资源
        /// </summary>
        /// <param name="layout_name">界面名称</param>
        /// <returns>结果</returns>
        public static ExecuteResult ReloadLayoutResource(FString layout_name)
        {
            Layout layout;
            if (sRegWinTable.GetLayout(layout_name, out layout))
            {
                layout.Reload();
                return setResult(ExecuteResult.Success);
            }
            return setResult(ExecuteResult.LayoutNotExist);
        }
        /// <summary>
        /// 设置界面是否可见
        /// </summary>
        /// <param name="layout_name">界面名称</param>
        /// <param name="visible">是否可见</param>
        /// <returns>结果</returns>
        public static ExecuteResult SetLayoutVisible(FString layout_name, bool visible)
        {
            Layout layout;
            if (sRegWinTable.GetLayout(layout_name, out layout))
            {
                if (!layout.IsLoaded)
                {
                    layout.Load();
                }
                layout.Visible = visible;
                return setResult(ExecuteResult.Success);
            }
            return setResult(ExecuteResult.LayoutNotExist);
        }

    }
}
