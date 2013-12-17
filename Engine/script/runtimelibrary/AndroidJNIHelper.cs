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


namespace ScriptRuntime
{
    public class AndroidJNIHelper
    {
        public static jvalue[] CreateJNIArgArray(object[] args)
        {
            return _AndroidJNIHelper.CreateJNIArgArray(args);
        }
        public static IntPtr ConvertToJNIArray(Array array)
        {
            return _AndroidJNIHelper.ConvertToJNIArray(array);
        }

        public static IntPtr GetConstructorID(IntPtr jclass, object[] args)
        {
            return _AndroidJNIHelper.GetConstructorID(jclass, args);
        }

        public static string GetSignature(object obj)
        {
            return _AndroidJNIHelper.GetSignature(obj);
        }
        public static string GetSignature(object[] args)
        {
            return _AndroidJNIHelper.GetSignature(args);
        }

        public static string GetSignature<ReturnType>(object[] args)
        {
            return _AndroidJNIHelper.GetSignature<ReturnType>(args);
        }

 
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr GetConstructorID(IntPtr javaClass, string signature);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr GetMethodID(IntPtr javaClass, string methodName, string signature, bool isStatic);

        public static IntPtr GetMethodID(IntPtr javaClass, string methodName, string signature)
        {
            bool isStatic = false;
            return AndroidJNIHelper.GetMethodID(javaClass, methodName, signature, isStatic);
        }
        public static IntPtr GetMethodID(IntPtr javaClass, string methodName)
        {
            bool isStatic = false;
            string empty = string.Empty;
            return AndroidJNIHelper.GetMethodID(javaClass, methodName, empty, isStatic);
        }

        public static IntPtr GetMethodID(IntPtr jclass, string methodName, object[] args, bool isStatic)
        {
            return _AndroidJNIHelper.GetMethodID(jclass, methodName, args, isStatic);
        }


        public static IntPtr GetMethodID<ReturnType>(IntPtr jclass, string methodName, object[] args, bool isStatic)
        {
            return _AndroidJNIHelper.GetMethodID<ReturnType>(jclass, methodName, args, isStatic);
        }

    }
}
