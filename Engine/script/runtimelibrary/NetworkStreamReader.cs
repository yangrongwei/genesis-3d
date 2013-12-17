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
    /// 网络流读取类
    /// </summary>
    public class NetworkStreamReader : Base
    {
        // - private data

        private NetworkStreamReader(DummyClass__ dummyObj)
        {
            //empty
        }
        /// <summary>
        /// 网络流读取构造函数
        /// </summary>
        public NetworkStreamReader()
        {
            ICall_NetworkStreamReader_Bind(this);
        }
        ~NetworkStreamReader()
        {
            ICall_NetworkStreamReader_Release(this);
        }
        /// <summary>
        /// 获取网络流长度
        /// </summary>
        /// <returns>长度信息</returns>
        public UInt32 Length()
        {
            UInt32 len = 0;
            ICall_NetworkStreamReader_Length(this, out len);
            return len;
        }
        /// <summary>
        /// 获取偏移量
        /// </summary>
        /// <returns>偏移量</returns>
        public UInt32 Offset()
        {
            UInt32 Offset = 0;
            ICall_NetworkStreamReader_Offset(this, out Offset);
            return Offset;
        }
        /// <summary>
        /// 设置偏移量
        /// </summary>
        /// <param name="dwOffset">偏移量</param>
        public void Seek(UInt32 dwOffset)
        {
            ICall_NetworkStreamReader_Seek(this, out dwOffset);
        }
        /// <summary>
        /// 从网络流中读取带符号的8位数据
        /// </summary>
        /// <returns>带符号的8位数据</returns>
        public sbyte ReadInt8()
        {
            Int32 read = 0;
            ICall_NetworkStreamReader_ReadInt8(this, out read);
            return Convert.ToSByte( read );
        }
        /// <summary>
        /// 从网络流中读取无符号的8位数据
        /// </summary>
        /// <returns>无符号的8位数据</returns>
        public byte ReadUint8()
        {
            UInt32 read = 0;
            ICall_NetworkStreamReader_ReadUint8(this, out read);
            return Convert.ToByte(read);
        }
        /// <summary>
        /// 从网络流中读取带符号的16位数据
        /// </summary>
        /// <returns>带符号的16位数据</returns>
        public Int16 ReadInt16()
        {
            Int32 read = 0;
            ICall_NetworkStreamReader_ReadInt16(this, out read);
            return Convert.ToInt16(read);
        }
        /// <summary>
        /// 从网络流中读取无符号的16位数据
        /// </summary>
        /// <returns>无符号的16位数据</returns>
        public UInt16 ReadUint16()
        {
            UInt32 read = 0;            
            ICall_NetworkStreamReader_ReadUint16(this, out read);
            return Convert.ToUInt16(read);
        }
        /// <summary>
        /// 从网络流中读取带符号的32位数据
        /// </summary>
        /// <returns>带符号的32位数据</returns>
        public Int32 ReadInt32()
        {
            Int32 read = 0;
            ICall_NetworkStreamReader_ReadInt32(this, out read);
            return Convert.ToInt32(read);
        }
        /// <summary>
        /// 从网络流中读取无符号的32位数据
        /// </summary>
        /// <returns>无符号的32位数据</returns>
        public UInt32 ReadUint32()
        {
            UInt32 read = 0;
            ICall_NetworkStreamReader_ReadUint32(this, out read);
            return Convert.ToUInt32(read);
        }
        /// <summary>
        /// 从网络流中读取带符号的64位数据
        /// </summary>
        /// <returns>带符号的64位数据</returns>
        public Int64 ReadInt64()
        {
            Int64 read = 0;
            ICall_NetworkStreamReader_ReadInt64(this, out read);
            return read;
        }
        /// <summary>
        /// 从网络流中读取无符号的64位数据
        /// </summary>
        /// <returns>无符号的64位数据</returns>
        public UInt64 ReadUint64()
        {
            UInt64 read = 0;
            ICall_NetworkStreamReader_ReadUint64(this, out read);
            return read;
        }
        /// <summary>
        /// 从网络流中读取32位浮点数数据
        /// </summary>
        /// <returns>32位浮点数数据</returns>
        public float ReadReal32()
        {
            float f = 0f;
            ICall_NetworkStreamReader_ReadReal32(this, out f);
            return f;
        }
        /// <summary>
        /// 从网络流中读取64位浮点数数据
        /// </summary>
        /// <returns>64位浮点数数据</returns>
        public double ReadReal64()
        {
            double f = 0f;
            ICall_NetworkStreamReader_ReadReal64(this, out f);
            return f;
        }
        /// <summary>
        /// 从网络流中读取字符串
        /// </summary>
        /// <returns>字符串</returns>
        public String ReadString()
        {
            return ICall_NetworkStreamReader_ReadString(this);
        }

        // - internal call declare, follow the turn which function appears
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_Bind(NetworkStreamReader self);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_Release(NetworkStreamReader obj);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_Length(NetworkStreamReader self, out UInt32 len);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_Offset(NetworkStreamReader self, out UInt32 offset);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_Seek(NetworkStreamReader self, out UInt32 dwOffset);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_ReadInt8(NetworkStreamReader self, out Int32 read);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_ReadUint8(NetworkStreamReader self, out UInt32 read);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_ReadInt16(NetworkStreamReader self, out Int32 read);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_ReadUint16(NetworkStreamReader self, out UInt32 read);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_ReadInt32(NetworkStreamReader self, out Int32 read);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_ReadUint32(NetworkStreamReader self, out UInt32 read);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_ReadInt64(NetworkStreamReader self, out Int64 read);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void  ICall_NetworkStreamReader_ReadUint64(NetworkStreamReader self, out UInt64 read);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_ReadReal32(NetworkStreamReader self, out float read);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static void ICall_NetworkStreamReader_ReadReal64(NetworkStreamReader self, out double read);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static String ICall_NetworkStreamReader_ReadString(NetworkStreamReader self);
    }
}
