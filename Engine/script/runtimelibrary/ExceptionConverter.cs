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
    /// 异常转换类，主要是负责将
    /// 异常信息输出至字符串中
    /// </summary>
    public class ExceptionConverter : Base
    {
        /// <summary>
        /// 类ExceptionConverter的无参数构造函数
        /// </summary>
        /// <return>无返回值</return>
        public ExceptionConverter()
        {

        }
        /// <summary>
        /// 将异常信息输出至字符串中
        /// </summary>
        /// <param name="exception">类Exception的实例，包含具体的异常信息</param>
        /// <param name="exc">out类型，存储转换后的字符串</param>
        /// <return>返回值为空类型</return>
        public static void ExceptionToString(Exception exception,out string exc)
        {
            exc = "";
           
            String traceString = "";
            String message = "";
            while (exception != null)
            {
                traceString += exception.StackTrace + "\n"; //get stack information

                string thisMessage = exception.GetType().Name; //get exception type
                string exceptionMessage = "";

                if (exception.Message != null)
                {
                    exceptionMessage = exception.Message; //get exception message
                }
                if (exceptionMessage.Trim().Length != 0)
                {
                    thisMessage += ": " + exceptionMessage;  //append exceptionMessage to thisMessage
                }
                message = thisMessage; // get exception message
                if (exception.InnerException != null) // if there's an inner exception,we'll get it's content
                {
                    traceString = "Rethrow as " + thisMessage + "\n" + traceString;
                }
                exception = exception.InnerException;
            }
            exc += message;
            exc += "\n";
            exc += traceString;
        }
    }
}
