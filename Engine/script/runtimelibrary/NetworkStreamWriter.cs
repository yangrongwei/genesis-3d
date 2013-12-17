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

using System.Globalization;
using System.Runtime.InteropServices;

namespace ScriptRuntime
{
    /// <summary>
    /// 网络流写入类
    /// </summary>
    public class NetworkStreamWriter : Base
    {
        // - private data

        private NetworkStreamWriter(DummyClass__ dummyObj)
        {
            //empty
        }
        /// <summary>
        /// 网络流写入构造函数
        /// </summary>
        public NetworkStreamWriter()
        {
            ICall_NetworkStreamWriter_Bind(this);
        }
        ~NetworkStreamWriter()
        {
            ICall_NetworkStreamWriter_Release(this);
        }
        /// <summary>
        /// 重置偏移量
        /// </summary>
        public void Reset()
        {
            ICall_NetworkStreamWriter_Reset(this);
        }
        /// <summary>
        /// 获取网络流长度
        /// </summary>
        /// <returns>长度信息</returns>
        public UInt32 Length()
        {
            UInt32 len = 0;
            ICall_NetworkStreamWriter_Length(this, out len);
            return len;
        }
        /// <summary>
        /// 获取网络流实际长度
        /// </summary>
        /// <returns>实际长度</returns>
        public UInt32 RealLength()
        {
            UInt32 len = 0;
            ICall_NetworkStreamWriter_RealLength(this, out len);
            return len;
        }
        /// <summary>
        /// 获取偏移量
        /// </summary>
        /// <returns>偏移量</returns>
        public UInt32 Offset()
        {
            UInt32 len = 0;
            ICall_NetworkStreamWriter_Offset(this, out len);
            return len;
        }
        /// <summary>
        /// 设置偏移量
        /// </summary>
        /// <param name="dwOffset">偏移量</param>
        public void Seek(UInt32 dwOffset)
        {
            ICall_NetworkStreamWriter_Seek(this, ref dwOffset);
        }
        /// <summary>
        /// 向网络流中写入带符号的8位数据
        /// </summary>
        /// <param name="val">带符号的8位数据</param>
        /// <returns>是否写入成功</returns>
        public bool WriteInt8(sbyte val)
        {
            Int32 temp = Convert.ToInt32(val);
            return ICall_NetworkStreamWriter_WriteInt8(this, ref temp);
        }
        /// <summary>
        /// 向网络流中写入无符号的8位数据
        /// </summary>
        /// <param name="val">无符号的8位数据</param>
        /// <returns>是否写入成功</returns>
        public bool WriteUint8(byte val)
        {
            UInt32 temp = Convert.ToUInt32(val);
            return ICall_NetworkStreamWriter_WriteUint8(this, ref temp);
        }
        /// <summary>
        /// 向网络流中写入带符号的16位数据
        /// </summary>
        /// <param name="val">带符号的16位数据</param>
        /// <returns>是否写入成功</returns>
        public bool WriteInt16(Int16 val)
        {
            Int32 temp = Convert.ToInt32(val);
            return ICall_NetworkStreamWriter_WriteInt16(this, ref temp);
        }
        /// <summary>
        /// 向网络流中写入无符号的16位数据
        /// </summary>
        /// <param name="val">无符号的16位数据</param>
        /// <returns>是否写入成功</returns>
        public bool WriteUint16(UInt16 val)
        {
            UInt32 temp = Convert.ToUInt32(val);
            return ICall_NetworkStreamWriter_WriteUint16(this, ref temp);
        }
        /// <summary>
        /// 向网络流中写入带符号的32位数据
        /// </summary>
        /// <param name="val">向网络流中写入带符号的32位数据</param>
        /// <returns>是否写入成功</returns>
        public bool WriteInt32(Int32 val)
        {
            return ICall_NetworkStreamWriter_WriteInt32(this, ref val);
        }
        /// <summary>
        /// 向网络流中写入无符号的32位数据
        /// </summary>
        /// <param name="val">无符号的32位数据</param>
        /// <returns>是否写入成功</returns>
        public bool WriteUint32(UInt32 val)
        {
            return ICall_NetworkStreamWriter_WriteUint32(this, ref val);
        }
        /// <summary>
        /// 向网络流中写入带符号的64位数据
        /// </summary>
        /// <param name="val">带符号的64位数据</param>
        /// <returns>是否写入成功</returns>
        public bool WriteInt64(Int64 val)
        {
            return ICall_NetworkStreamWriter_WriteInt64(this, ref val);
        }
        /// <summary>
        /// 向网络流中写入无符号的64位数据
        /// </summary>
        /// <param name="val">无符号的64位数据</param>
        /// <returns>是否写入成功</returns>
        public bool WriteUint64(UInt64 val)
        {
            return ICall_NetworkStreamWriter_WriteUint64(this, ref val);
        }
        /// <summary>
        /// 向网络流中写入32位浮点数数据
        /// </summary>
        /// <param name="val">32位浮点数数据</param>
        /// <returns>是否写入成功</returns>
        public bool WriteReal32(float val)
        {
            return ICall_NetworkStreamWriter_WriteReal32(this, ref val);
        }
        /// <summary>
        /// 向网络流中写入64位浮点数数据
        /// </summary>
        /// <param name="val">64位浮点数数据</param>
        /// <returns>是否写入成功</returns>
        public bool WriteReal64(double val)
        {
            return ICall_NetworkStreamWriter_WriteReal64(this, ref val);
        }
        /// <summary>
        /// 向网络流中写入字符串
        /// </summary>
        /// <param name="val">字符串</param>
        /// <returns>是否写入成功</returns>
        public bool WriteString(String val)
        {
            return ICall_NetworkStreamWriter_WriteString(this, val);
        }

        // - internal call declare, follow the turn which function appears
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamWriter_Bind(NetworkStreamWriter self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamWriter_Release(NetworkStreamWriter self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamWriter_Reset(NetworkStreamWriter self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamWriter_Length(NetworkStreamWriter self, out UInt32 len);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamWriter_RealLength(NetworkStreamWriter self,out UInt32 len);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamWriter_Offset(NetworkStreamWriter self, out UInt32 offset);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamWriter_Seek(NetworkStreamWriter self, ref UInt32 dwOffset);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteInt8(NetworkStreamWriter self, ref Int32 val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteUint8(NetworkStreamWriter self, ref UInt32 val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteInt16(NetworkStreamWriter self, ref Int32 val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteUint16(NetworkStreamWriter self, ref UInt32 val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteInt32(NetworkStreamWriter self, ref Int32 val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteUint32(NetworkStreamWriter self, ref UInt32 val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteInt64(NetworkStreamWriter self, ref Int64 val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteUint64(NetworkStreamWriter self, ref UInt64 val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteReal32(NetworkStreamWriter self, ref float val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteReal64(NetworkStreamWriter self, ref double val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_NetworkStreamWriter_WriteString(NetworkStreamWriter self, String val);
    }
}
