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
    /// 磁盘文件读写操作类
    /// </summary>
    public class IO: Base
    {
        /// <summary>
        /// 生成Xml格式文件读取器
        /// </summary>
        /// <param name="filePath">xml文件ID(如asset:test.xml)</param>
        /// <returns></returns>
        public static XmlReader GetXmlReader(String filePath)
        {
            return ICall_IO_GetXmlReader(filePath);
        }

        /// <summary>
        /// 生成Xml格式文件写入器
        /// </summary>
        /// <param name="filePath">xml文件ID(如asset:test.xml)</param>
        /// <returns></returns>
        public static XmlWriter GetXmlWriter(String filePath)
        {
            return ICall_IO_GetXmlWriter(filePath);
        }

        /// <summary>
        /// 结束写入文件
        /// </summary>
        /// <param name="writer">与文件关联的写入器</param>
        public static void CloseWriteFile(XmlWriter writer)
        {
            ICall_IO_CloseWriteFile(writer);
        }

        /// <summary>
        /// 保存场景
        /// </summary>
        /// <param name="filePath">场景文件ID(如asset:test.scene)</param>
        public static void SaveScene(String filePath)
        {
            ICall_IO_SaveScene(filePath);
        }

        /// <summary>
        /// 以文本形式读取文件所有行
        /// </summary>
        /// <param name="filePath">要读取的文件ID(如asset:test.txt)</param>
        /// <returns>读取的字符串数组</returns>
        public static String[] ReadAllLines( String filePath )
        {
            return ICall_IO_ReadAllLines(filePath);
        }

        // - internal call declare
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static XmlReader ICall_IO_GetXmlReader(String filePath);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static XmlWriter ICall_IO_GetXmlWriter(String filePath);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_IO_CloseWriteFile(XmlWriter writer);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_IO_SaveScene(String filePath);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String[] ICall_IO_ReadAllLines(String filePath);
    }
}
