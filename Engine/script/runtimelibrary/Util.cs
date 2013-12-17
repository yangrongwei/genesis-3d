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
using System.Runtime.InteropServices;
using ScriptRuntime;
namespace ScriptRuntime
{

    public static class FlagUtil
    {
        public const uint BIT_FLAG_NONE = 0;
        public const uint BIT_FLAG_0 = (uint)1;
        public const uint BIT_FLAG_1 = (uint)1 << 1;
        public const uint BIT_FLAG_2 = (uint)1 << 2;
        public const uint BIT_FLAG_3 = (uint)1 << 3;
        public const uint BIT_FLAG_4 = (uint)1 << 4;
        public const uint BIT_FLAG_5 = (uint)1 << 5;
        public const uint BIT_FLAG_6 = (uint)1 << 6;
        public const uint BIT_FLAG_7 = (uint)1 << 7;

        public const uint BIT_FLAG_8 = (uint)1 << 8;
        public const uint BIT_FLAG_9 = (uint)1 << 9;
        public const uint BIT_FLAG_10 = (uint)1 << 10;
        public const uint BIT_FLAG_11 = (uint)1 << 11;
        public const uint BIT_FLAG_12 = (uint)1 << 12;
        public const uint BIT_FLAG_13 = (uint)1 << 13;
        public const uint BIT_FLAG_14 = (uint)1 << 14;
        public const uint BIT_FLAG_15 = (uint)1 << 15;

        public const uint BIT_FLAG_16 = (uint)1 << 16;
        public const uint BIT_FLAG_17 = (uint)1 << 17;
        public const uint BIT_FLAG_18 = (uint)1 << 18;
        public const uint BIT_FLAG_19 = (uint)1 << 19;
        public const uint BIT_FLAG_20 = (uint)1 << 20;
        public const uint BIT_FLAG_21 = (uint)1 << 21;
        public const uint BIT_FLAG_22 = (uint)1 << 22;
        public const uint BIT_FLAG_23 = (uint)1 << 23;

        public const uint BIT_FLAG_24 = (uint)1 << 24;
        public const uint BIT_FLAG_25 = (uint)1 << 25;
        public const uint BIT_FLAG_26 = (uint)1 << 26;
        public const uint BIT_FLAG_27 = (uint)1 << 27;
        public const uint BIT_FLAG_28 = (uint)1 << 28;
        public const uint BIT_FLAG_29 = (uint)1 << 29;
        public const uint BIT_FLAG_30 = (uint)1 << 30;
        public const uint BIT_FLAG_31 = (uint)1 << 31;


        public const byte BIT_FLAG_8BIT_MAX = 0xff;
        public const ushort BIT_FLAG_16BIT_MAX = 0xffff;
        public const uint BIT_FLAG_32BIT_MAX = 0xffffffff;
        public const int UNVALID_COUNT = -1;

        public static uint BIT_FLAG(int num)
        {
            return ((uint)1 << (num));
        }
    }


    /// <summary>
    /// 场景中的基本方法，此类的方法都为静态方法。
    /// </summary>
    public class Util : Base
    {

        static internal Guid CreateFromCPPByteArray(IntPtr arrayBegin)
        {
            Byte[] array = new Byte[16];
            Marshal.Copy(arrayBegin, array, 0, 16);
            return new Guid(array);
        }
        /// <summary>
        /// 获取当前帧的时间.
        /// </summary>
        /// <returns>当前帧的时间.</returns>
        /**@brief<b>示例</b>
        *@code{.cpp}
        float fDeltaTime = Util.GetDeltaTime();
        @endcode
        */
        static public float GetDeltaTime()
        {
            return ICall_Util_GetDeltaTime();

        }

        /// <summary>
        /// 保存场景
        /// </summary>
        /// <param name="sceneName">要保存的场景的名字</param>
        /// <returns>是否保存成功</returns>
        static public bool SaveScene(String sceneName)
        {
            return ICall_Util_SaveScene(sceneName);
        }
        /// <summary>
        /// 获取脚本根节点.
        /// </summary>
        /// <returns>脚本根节点.</returns>
        static public RuntimeScriptRoot GetRootScript()
        {
            return ICall_Util_GetRootScript();
        }


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static float ICall_Util_GetDeltaTime();

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static bool ICall_Util_SaveScene(String sceneName);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        extern private static RuntimeScriptRoot ICall_Util_GetRootScript();
    }
}