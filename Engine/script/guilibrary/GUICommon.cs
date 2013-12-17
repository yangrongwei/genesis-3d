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
        /// 执行结果
        /// </summary>
        public static ExecuteResult ExecuteResult
        {
            get
            {
                return mExecuteResult;
            }
        }
        private static ExecuteResult mExecuteResult;
        private static ExecuteResult setResult(ExecuteResult ret)
        {
            mExecuteResult = ret;
            return ret;
        }
        // ------------------------------ public -----------------------------------------------------------------

        //public static ExecuteResult SetProperty(FString widget_name)
        //{
        //    return ExecuteResult.False;
        //}
        /// <summary>
        /// 设置界面坐标
        /// </summary>
        /// <param name="layout_name">界面名称</param>
        /// <param name="int_coord">坐标</param>
        /// <returns>结果</returns>
        public static ExecuteResult SetLayoutCoord(FString layout_name, IntCoord int_coord)
        {
            Layout layout;
            if (sRegWinTable.GetLayout(layout_name, out layout))
            {
                if (!layout.IsLoaded)
                {
                    layout.Load();
                }
                layout.Root.Coord = int_coord;
                return setResult(ExecuteResult.Success);
            }
            return setResult(ExecuteResult.LayoutNotExist);
        }
        /// <summary>
        /// 获取场景大小
        /// </summary>
        /// <returns>场景大小</returns>
        public static IntSize GetScreenSize()
        {
            IntSize size;
            ICall_getScreenSize(out size);
            return size;
        }
        /// <summary>
        /// 获取分辨率
        /// </summary>
        /// <returns>分辨率</returns>
        public static IntSize GetResolution()
        {
            IntSize size;
            ICall_getResolution(out size);
            return size;
        }
        /// <summary>
        /// 设置分辨率
        /// </summary>
        /// <param name="size">分辨率</param>
        public static void SetResolution(IntSize size)
        {
            ICall_setResolution(ref size);
        }
        /// <summary>
        /// 自动分辨率宽度
        /// </summary>
        /// <returns>分辨率宽度</returns>
        public bool AutoResolutionWidth()
        {
            return AutoResolutionWidth();
        }
        /// <summary>
        /// 自动分辨率高度
        /// </summary>
        /// <returns>分辨率高度</returns>
        public bool AutoResolutionHeight()
        {
            return AutoResolutionHeight();
        }

        // ------------------------------ internal -----------------------------------------------------------------
        #region internal
        internal static Instance LoadLayout(Widget parent, String file_name)
        {
            if (null == parent)
            {
                return ICall_loadLayout(IntPtr.Zero, file_name);
            }
            return ICall_loadLayout(parent.Instance.Ptr, file_name);

        }

        internal static ExecuteResult UnloadLayout(FString layout_name)
        {
            Layout layout;
            if (sRegWinTable.GetLayout(layout_name, out layout))
            {
                layout.Unload();
                sRegWinTable.Remove(layout_name);
                return setResult(ExecuteResult.Success);
            }
            return setResult(ExecuteResult.LayoutNotExist);
        }

        internal static void DisposeWidget(Instance widget_inst)
        {
            if (widget_inst.IsValid)
            {
                ICall_destroyWidget(widget_inst.Ptr);
            }

        }
        internal static bool SearchLayout(Instance inst, out Layout layout)
        {
            return sRegWinTable.GetLayout(inst, out layout);
        }

        internal static ExecuteResult FindWidget(FString layout_name, FString widget_name, out Widget widget)
        {
            Layout layout = null;
            widget = null;
            ExecuteResult ret = ExecuteResult.Success;

            if (sRegWinTable.GetLayout(layout_name, out layout))
            {
                if (!layout.IsLoaded)
                {
                    layout.Load();
                }
                if (!layout.FindWidget(widget_name, out widget))
                {
                    ret = ExecuteResult.WidgetNotExist;
                }
            }
            else
            {
                ret = ExecuteResult.LayoutNotExist;
            }
            return setResult(ret);
        }
        internal static ExecuteResult FindUI<T>(FString layout_name, FString widget_name, out T widget)
            where T : Widget
        {
            widget = null;
            Widget wd = null;
            ExecuteResult ret = FindWidget(layout_name, widget_name, out wd);
            if (ExecuteResult.Success == ret)
            {
                widget = wd as T;
                if (null == widget)
                {
                    ret = ExecuteResult.TypeError;
                    return setResult(ret);
                }
            }
            return ret;

        }

        internal static IntPtr FindWidget(IntPtr parent, String widget_name)
        {
            return ICall_findWidget(parent, widget_name);
        }

        private static LayoutCollection  sRegWinTable = new LayoutCollection();

        #endregion
      


#region CPP Interface

        // - internal call declare, follow the turn which function appears
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static IntPtr ICall_loadLayout(IntPtr parent, String file_name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_destroyWidget(IntPtr widget_ptr);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static IntPtr ICall_findWidget(IntPtr parent, String widget_name);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getScreenSize(out IntSize value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_getResolution(out IntSize value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_setResolution(ref IntSize value);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_autoResolutionWidth();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_autoResolutionHeight();

#endregion



    }
}
