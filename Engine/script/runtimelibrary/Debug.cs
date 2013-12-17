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

namespace ScriptRuntime
{
    /// <summary>
    /// 调试类，处理调试信息的输出
    /// </summary>
    public class Debug : Base
    {
        /// <summary>
        /// 输出参数内容至控制台窗口或日志文件
        /// </summary>
        /// <param name="str">待输出的字符串</param>
        /// <return>返回值为空类型</return>
        /**@brief<b>示例</b>
        *@code{.cpp}
        ScriptRuntime.Debug.Printf("ScriptRuntime.Debug.Printf");
        @endcode
        */
        public static void Printf(String str)
        {
            ICall_Debug_Printf(str);
        }

       /// <summary>
       /// 输出参数内容至调试（debug）窗口
       /// </summary>
        /// <param name="str">待输出的字符串</param>
        /// <return>返回值为空类型</return>
        /**@brief<b>示例</b>
        *@code{.cpp}
        ScriptRuntime.Debug.Dbgout("ScriptRuntime.Debug.Dbgout");
        @endcode
        */
        public static void Dbgout(String str)
        {
            ICall_Debug_Dbgout(str);
        }
        /// <summary>
        /// 输出警告（warning）信息至控制台窗口
        /// </summary>
        /// <param name="str">存储警告信息的字符串</param>
        /// <return>返回值为空类型</return>
        /**@brief<b>示例</b>
        *@code{.cpp}
        ScriptRuntime.Debug.Warning("ScriptRuntime.Debug.Warning");
        @endcode
        */
        public static void Warning(String str)
        {
            ICall_Debug_Warning(str);
        }

        
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Debug_Printf(String str);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Debug_Dbgout(String str);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_Debug_Warning(String str);
 
    }
}