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

namespace ScriptRuntime
{
    public class AndroidJavaObject : AndroidJNIHelper
    {
        protected IntPtr m_jobject;
        protected IntPtr m_jclass;
        protected Dictionary<int, IntPtr> m_methodIDs;
        protected Dictionary<int, IntPtr> m_fieldIDs;

        public AndroidJavaObject(IntPtr jobject)
            : this()
        {
            if (jobject == IntPtr.Zero)
            {
                Debug.Warning("JNI: Init'd AndroidJavaObject with null ptr!");
                return;
            }
            this.m_jobject = AndroidJNI.NewGlobalRef(jobject);
            this.m_jclass = AndroidJNI.NewGlobalRef(AndroidJNI.GetObjectClass(this.m_jobject));
        }
        protected AndroidJavaObject()
        {
            this.m_methodIDs = new Dictionary<int, IntPtr>();
            this.m_fieldIDs = new Dictionary<int, IntPtr>();
        }
        public AndroidJavaObject(string className, params object[] args)
            : this()
        {
            this._AndroidJavaObject(className, args);
        }
        private void _AndroidJavaObject(string className, params object[] args)
        {
            if (args == null)
            {
                args = new object[1];
            }
            className = className.Replace('.', '/');
            IntPtr intPtr = AndroidJNI.FindClass(className);
            this.m_jclass = AndroidJNI.NewGlobalRef(intPtr);
            IntPtr constructorID = AndroidJNIHelper.GetConstructorID(intPtr, args);
            jvalue[] args2 = AndroidJNIHelper.CreateJNIArgArray(args);
            IntPtr obj = AndroidJNI.NewObject(intPtr, constructorID, args2);
            this.m_jobject = AndroidJNI.NewGlobalRef(obj);
        }

        public IntPtr GetRawObject()
        {
            return this.m_jobject;
        }

        public IntPtr GetRawClass()
        {
            return this.m_jclass;
        }
        public void Call(string methodName, params object[] args)
        {
            this._Call(methodName, args);
        }

        public ReturnType Call<ReturnType>(string methodName, params object[] args)
        {
            return this._Call<ReturnType>(methodName, args);
        }

        protected void _Call(string methodName, params object[] args)
        {
            if (args == null)
            {
                args = new object[1];
            }
            string signature = AndroidJNIHelper.GetSignature(args);
            Debug.Warning("Call<void>"+ methodName+ signature+ args);
            IntPtr cachedMethodID = AndroidJNIHelper.GetMethodID(this.m_jclass, methodName, args, false);
            jvalue[] args2 = AndroidJNIHelper.CreateJNIArgArray(args);
            AndroidJNI.CallVoidMethod(this.m_jobject, cachedMethodID, args2);
        }

        protected ReturnType _Call<ReturnType>(string methodName, params object[] args) 
        {
            if (args == null)
            {
                args = new object[1];
            }
            string signature = AndroidJNIHelper.GetSignature<ReturnType>(args);
            Debug.Warning("Call<" + typeof(ReturnType).ToString() + ">"+methodName+signature+args);
            IntPtr cachedMethodID = AndroidJNIHelper.GetMethodID<ReturnType> (this.m_jclass, methodName, args, false);
            jvalue[] args2 = AndroidJNIHelper.CreateJNIArgArray(args);
            if (typeof(ReturnType).IsPrimitive)
            {
                if (typeof(ReturnType) == typeof(int))
                {
                    object rt = AndroidJNI.CallIntMethod(this.m_jobject, cachedMethodID, args2) ;
                    return (ReturnType)rt;
                }
                if (typeof(ReturnType) == typeof(bool))
                {
                    object rt = AndroidJNI.CallBooleanMethod(this.m_jobject, cachedMethodID, args2);
                    return (ReturnType)rt;
                }
                if (typeof(ReturnType) == typeof(byte))
                {
                    object rt = AndroidJNI.CallByteMethod(this.m_jobject, cachedMethodID, args2);
                    return (ReturnType)rt;
                }
                if (typeof(ReturnType) == typeof(short))
                {
                    object rt = AndroidJNI.CallShortMethod(this.m_jobject, cachedMethodID, args2);
                    return (ReturnType)rt;
                }
                if (typeof(ReturnType) == typeof(long))
                {
                    object rt = AndroidJNI.CallLongMethod(this.m_jobject, cachedMethodID, args2);
                    return (ReturnType)rt;
                }
                if (typeof(ReturnType) == typeof(float))
                {
                    object rt = AndroidJNI.CallFloatMethod(this.m_jobject, cachedMethodID, args2);
                    return (ReturnType)rt;
                }
                if (typeof(ReturnType) == typeof(double))
                {
                    object rt = AndroidJNI.CallDoubleMethod(this.m_jobject, cachedMethodID, args2);
                    return (ReturnType)rt;
                }
                if (typeof(ReturnType) == typeof(char))
                {
                    object rt = AndroidJNI.CallCharMethod(this.m_jobject, cachedMethodID, args2);
                    return (ReturnType)rt;
                }
            }
            else
            {
                if (typeof(ReturnType) == typeof(string))
                {
                    object rt = AndroidJNI.CallStringMethod(this.m_jobject, cachedMethodID, args2);
                    return (ReturnType)rt;
                }
                if (typeof(ReturnType) == typeof(AndroidJavaObject))
                {
                    IntPtr jobject = AndroidJNI.CallObjectMethod(this.m_jobject, cachedMethodID, args2);
                    object rt = new AndroidJavaObject(jobject);
                    return (ReturnType)rt;
                }
//                 if (typeof(Array).IsAssignableFrom(typeof(ReturnType)))
//                 {
//                     IntPtr array = AndroidJNI.CallObjectMethod(this.m_jobject, cachedMethodID, args2);
//                     return (ReturnType)AndroidJNIHelper.ConvertFromJNIArray<ReturnType>(array);
//                 }
                Debug.Warning("JNI: Unknown return type '" + typeof(ReturnType) + "'");
            }
            return default(ReturnType);
        }

    }
}
