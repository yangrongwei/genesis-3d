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
using System.Collections.Generic;
namespace ScriptRuntime
{

    /// <summary>
    /// 输入类,包括键盘,鼠标,触控的输入
    /// </summary>
    public class Input:Base
    {
        /// <summary>
        /// 按键是否被按下
        /// </summary>
        /// <param name="_keyCode">键的枚举值</param>
        /// <returns>true：按键被按下； false：按键没有被按下</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        if (ScriptRuntime.Input.KeyDown(Code.Space))
        {
            ScriptRuntime.Debug.Printf("Code.Space is Down");
        }
        @endcode
        */
        static public bool KeyDown(Code _keyCode)
        {
            return ICall_Input_KeyDown((int)_keyCode);  
          //  return true;
        }

        /// <summary>
        /// 按键是否弹起
        /// </summary>
        /// <param name="_keyCode">键的枚举值</param>
        /// <returns>true：按键弹起； false：按键没有弹起</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        if (ScriptRuntime.Input.KeyUp(Code.Space))
        {
            ScriptRuntime.Debug.Printf("Code.Space is Up");
        }
        @endcode
        */
        static public bool KeyUp(Code _keyCode)
        {
            return ICall_Input_KeyUp((int)_keyCode);
            //  return true;
        }
        
        /// <summary>
        /// 按键是否是持续按下状态
        /// </summary>
        /// <param name="_keyCode">键的枚举值</param>
        /// <returns>true：按键是持续按下状态； false：按键不是持续按下状态</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        if (ScriptRuntime.Input.KeyPressed(Code.Space))
        {
            ScriptRuntime.Debug.Printf("Code.Space is Pressed");
        }
        @endcode
        */
        static public bool KeyPressed(Code _keyCode)
        {
            return ICall_Input_KeyPressed((int)_keyCode);
            //  return true;
        }

        /// <summary>
        /// 鼠标按钮是否被按下
        /// </summary>
        /// <param name="_mouseCode">鼠标按钮枚举值</param>
        /// <returns>true：鼠标按钮被按下；false：鼠标按钮没有被按下</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        if (ScriptRuntime.Input.MouseButtonDown(MouseCode.LeftButton))
        {
            ScriptRuntime.Debug.Printf("MouseCode.LeftButton is Down");
        }
        @endcode
        */
        static public bool MouseButtonDown(MouseCode _mouseCode)
        {
            return ICall_Input_MouseButtonDown((int)_mouseCode);
        }
        
        /// <summary>
        /// 鼠标滚轮是否向前滚动
        /// </summary>
        /// <returns>true：鼠标滚轮向前滚动；false：鼠标滚轮没有向前滚动</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        if (ScriptRuntime.Input.MouseWheelForward())
        {
            ScriptRuntime.Debug.Printf("Mouse Wheel Forward");
        }
        @endcode
        */
        static public bool MouseWheelForward()
        {
            return ICall_Input_MouseWheelForward();
        }
        
        /// <summary>
        /// 鼠标滚轮是否向后滚动
        /// </summary>
        /// <returns>true：鼠标滚轮向后滚动；false：鼠标滚轮没有向后滚动</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        if (ScriptRuntime.Input.MouseWheelBack())
        {
            ScriptRuntime.Debug.Printf("Mouse Wheel Back");
        }
        @endcode
        */
        static public bool MouseWheelBack()
        {
            return ICall_Input_MouseWheelBack();
        }
        
        /// <summary>
        /// 鼠标按钮是否是被按下状态
        /// </summary>
        /// <param name="_mouseCode">鼠标按钮枚举值</param>
        /// <returns>true：鼠标按钮是持续按下状态；false：鼠标按钮不是持续按下状态</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        if (ScriptRuntime.Input.MouseButtonPressed(MouseCode.LeftButton))
        {
            ScriptRuntime.Debug.Printf("MouseCode.LeftButton is Pressed");
        }
        @endcode
        */
        static public bool MouseButtonPressed(MouseCode _mouseCode)
        {
            return ICall_Input_MouseButtonPressed((int)_mouseCode);
        }
        
        /// <summary>
        /// 鼠标按钮是否弹起
        /// </summary>
        /// <param name="_mouseCode">鼠标按钮枚举值</param>
        /// <returns>true：鼠标按钮弹起；false：鼠标按钮没有弹起</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        if (ScriptRuntime.Input.MouseButtonUp(MouseCode.LeftButton))
        {
            ScriptRuntime.Debug.Printf("MouseCode.LeftButton is Up");
        }
        @endcode
        */
        static public bool MouseButtonUp(MouseCode _mouseCode)
        {
            return ICall_Input_MouseButtonUp((int)_mouseCode);
        }
        
        /// <summary>
        /// 得到鼠标光标在屏幕上的位置
        /// </summary>
        /// <param name="outFloat2">鼠标光标在屏幕上的位置</param>
        static public void GetScreenPosition(out Vector2 outFloat2)
        {
            ICall_Input_GetScreenPosition(out outFloat2);
        }
        
        /// <summary>
        /// 得到鼠标光标在屏幕上的移动距离
        /// </summary>
        /// <param name="outFloat2">鼠标光标在屏幕上的移动距离</param>
        static public void MouseGetMovement( out Vector2 outFloat2 )
        {
            ICall_Input_MouseGetMovement(out outFloat2);
        }
        
        /// <summary>
        /// 得到屏幕上的触点个数，windows平台没实现
        /// </summary>
        /// <returns>触点个数</returns>
        static public int GetScreenTouchCount()
        { 
            return ICall_Input_GetScreenTouchCount();
        }
        
        /// <summary>
        /// 得到屏幕上触点ID
        /// </summary>
        /// <param name="index">触点索引</param>
        /// <returns>屏幕上触点ID</returns>
        static public int GetScreenTouchID(int index)
        {
            return ICall_Input_GetScreenTouchID(index);
        }

        /// <summary>
        /// 手指是否按下
        /// </summary>
        /// <param name="id">触点索引</param>
        /// <returns>true：手指按下；false：手指没有按下</returns>
        static public bool IsFingerDown(int id)
        {
            return ICall_Input_IsFingerDown(id);
        }
        
        /// <summary>
        /// 手指是否是按下状态
        /// </summary>
        /// <param name="id">触点索引</param>
        /// <returns>true：手指是按下状态；false：手指不是按下状态</returns>
        static public bool IsFingerPressing(int id)
        {
            return ICall_Input_IsFingerPressing(id);
        }
        
        /// <summary>
        /// 手指是否弹起
        /// </summary>
        /// <param name="id">触点索引</param>
        /// <returns>true：手指是弹起；false：手指不是弹起</returns>
        static public bool IsFingerUp(int id)
        {
            return ICall_Input_IsFingerUp(id);
        }
        
        /// <summary>
        /// 得到手指在屏幕上的移动距离
        /// </summary>
        /// <param name="id">触点索引</param>
        /// <returns>手指在屏幕上的移动距离</returns>
        static public Vector2 GetScreenTouchMovement(int id)
        {
            Vector2 v2 = new Vector2();
            ICall_Input_GetScreenTouchMovement(id, out v2);
            return v2;
        }
        
        /// <summary>
        /// 得到触点在屏幕的位置，为相对位置，范围：0-1
        /// </summary>
        /// <param name="id">触点索引</param>
        /// <returns>屏幕的位置</returns>
        static public Vector2 GetScreenTouchScreenPosition(int id)
        {
            Vector2 v2 = new Vector2();
            ICall_Input_GetScreenTouchScreenPos(id, out v2);
            return v2;
        }
        
        /// <summary>
        /// 得到在触点在屏幕上的像素位置
        /// </summary>
        /// <param name="id">触点索引</param>
        /// <returns>屏幕上的像素位置</returns>
        static public Vector2 GetScreenTouchPixelPosition(int id)
        {
            Vector2 v2 = new Vector2();
            ICall_Input_GetScreenTouchPixelPos(id, out v2);
            return v2;
        }
        
        /// <summary>
        /// 得到当前按键的事件
        /// </summary>
        /// <returns>按键事件数组</returns>
        static public KeyEvent[] GetCurrentKeyEvents()
        {
            List<KeyEvent> events = new List<KeyEvent>();
            int count = ICall_Input_GetCurrentKeyEventCount();
            for (int i = 0; i < count; ++i)
            {
                KeyEvent key_event = new KeyEvent();
                ICall_Input_GetCurrentKeyEvent(i, out key_event.key, out key_event.eventType);
                events.Add(key_event);
            }
            return events.ToArray();
        }
        
        /// <summary>
        /// 得到当前鼠标事件
        /// </summary>
        /// <returns>当前鼠标事件数组</returns>
        static public MouseEvent[] GetCurrentMouseEvents()
        {
            List<MouseEvent> events = new List<MouseEvent>();
            int count = ICall_Input_GetCurrentMouseButtonEventCount();
            for (int i = 0; i < count; ++i)
            {
                MouseEvent _event = new MouseEvent();
                ICall_Input_GetCurrentMouseButtonEvent(i, out _event.button, out _event.eventType);
                events.Add(_event);
            }
            return events.ToArray();
        }
        
        /// <summary>
        /// 得到当前触点事件
        /// </summary>
        /// <returns>当前触点数组</returns>
        static public TouchEvent[] GetCurrentTouchEvents()
        {
            List<TouchEvent> events = new List<TouchEvent>();
            int count = ICall_Input_GetCurrentTouchEventCount();
            for (int i = 0; i < count; ++i)
            {
                TouchEvent _event = new TouchEvent();
                ICall_Input_GetCurrentTouchEvent(i, out _event.id, out _event.eventType);
                events.Add(_event);
            }
            return events.ToArray();
        }

        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_KeyDown(int _keyCode);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_KeyUp(int _keyCode);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_KeyPressed(int _keyCode);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_MouseButtonDown(int _mouseCode);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_MouseButtonPressed(int _mouseCode);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_MouseButtonUp(int _mouseCode);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Input_GetScreenPosition(out Vector2 outFloat2);
       
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_MouseWheelForward();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_MouseWheelBack();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Input_MouseGetMovement( out Vector2 outFloat2 );

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_Input_GetScreenTouchCount();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_Input_GetScreenTouchID(int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_IsFingerDown(int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_IsFingerPressing(int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Input_IsFingerUp(int index);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Input_GetScreenTouchMovement(int index,out Vector2 moveMent);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Input_GetScreenTouchScreenPos(int index, out Vector2 screenPos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Input_GetScreenTouchPixelPos(int index, out Vector2 pixelPos);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_Input_GetCurrentKeyEventCount();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Input_GetCurrentKeyEvent(int index, out Code code, out InputEventType _event);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_Input_GetCurrentMouseButtonEventCount();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Input_GetCurrentMouseButtonEvent(int index, out MouseCode code, out InputEventType _event);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static int ICall_Input_GetCurrentTouchEventCount();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Input_GetCurrentTouchEvent(int index, out int id, out InputEventType _event);
    }
}