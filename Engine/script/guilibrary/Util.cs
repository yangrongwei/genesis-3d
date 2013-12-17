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
using System.Runtime.InteropServices;

namespace ScriptGUI
{
    internal static class Util
    {
        internal static T PtrToStruct<T>(IntPtr ptr)
        {
            return (T)Marshal.PtrToStructure(ptr, typeof(T));
        }
        internal const int MYGUI_FLAG_NONE = 0;
        internal const int MYGUI_FLAG_0 = 1;
        internal const int MYGUI_FLAG_1 = 1 << 1;
        internal const int MYGUI_FLAG_2 = 1 << 2;
        internal const int MYGUI_FLAG_3 = 1 << 3;
        internal const int MYGUI_FLAG_4 = 1 << 4;
        internal const int MYGUI_FLAG_5 = 1 << 5;
        internal const int MYGUI_FLAG_6 = 1 << 6;
        internal const int MYGUI_FLAG_7 = 1 << 7;
        public const int UNVALID_COUNT = -1;
        internal static int MYGUI_FLAG(int num)
        {
            return (1 << (num));
        }
    }
}
