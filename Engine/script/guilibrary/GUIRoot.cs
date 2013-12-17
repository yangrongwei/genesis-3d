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
using System.Runtime.CompilerServices;
using ScriptRuntime;

namespace ScriptGUI
{
    /// <summary>
    /// 用户界面控件实现基类
    /// </summary>
    public class GUIRoot
    {
        /// <summary>
        /// 基类构造函数
        /// </summary>
        public GUIRoot()
        {

        }
        /// <summary>
        /// 初始化操作，由子类实现
        /// </summary>
        public virtual void Init()
        {
            //empty
        }
        /// <summary>
        /// 窗口管理操作，由子类实现
        /// </summary>
        public virtual void WinSizeChange()
        {
            //empty
        }

        internal delegate void DelegateTick(Vector2 frame_time);

        internal static event DelegateTick EventTick
        {
            add
            {
                if (null == mHandleTick)
                {
                    if (!ICall_tickEvent(true))
                    {
                        return;
                    }
                }                       
                mHandleTick += value;
            }
            remove
            {
                mHandleTick -= value;
                if (null == mHandleTick)
                {
                    ICall_tickEvent(false);
                }
            }
        }
        internal static DelegateTick mHandleTick;


        private void onInit()
        {
            Init();
        }
        
        
        private void onWinSizeChange()
        {
            WinSizeChange();
        }

        private static void onTick(ref Vector2 frame_time)
        {
            mHandleTick(frame_time);
        }

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_tickEvent(bool start);
    }
}
