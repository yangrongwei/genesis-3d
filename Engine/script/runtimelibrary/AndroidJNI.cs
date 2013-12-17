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

    internal class WrapperlessIcall : Attribute
    {
    }

    public class AndroidJNI
    {
        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr AllocObject(IntPtr clazz);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewObject(IntPtr clazz, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr GetObjectClass(IntPtr obj);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr ToBooleanArray(bool[] array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr ToByteArray(byte[] array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr ToCharArray(char[] array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr ToShortArray(short[] array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr ToIntArray(int[] array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr ToLongArray(long[] array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr ToFloatArray(float[] array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr ToDoubleArray(double[] array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr ToObjectArray(IntPtr[] array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern bool[] FromBooleanArray(IntPtr array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern byte[] FromByteArray(IntPtr array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern char[] FromCharArray(IntPtr array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern short[] FromShortArray(IntPtr array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern int[] FromIntArray(IntPtr array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern long[] FromLongArray(IntPtr array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern float[] FromFloatArray(IntPtr array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern double[] FromDoubleArray(IntPtr array);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr[] FromObjectArray(IntPtr array);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewBooleanArray(int size);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewByteArray(int size);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewCharArray(int size);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewShortArray(int size);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewIntArray(int size);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewLongArray(int size);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewFloatArray(int size);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewDoubleArray(int size);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewObjectArray(int size, IntPtr clazz, IntPtr obj);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool GetBooleanArrayElement(IntPtr array, int index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte GetByteArrayElement(IntPtr array, int index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern char GetCharArrayElement(IntPtr array, int index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short GetShortArrayElement(IntPtr array, int index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int GetIntArrayElement(IntPtr array, int index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long GetLongArrayElement(IntPtr array, int index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float GetFloatArrayElement(IntPtr array, int index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double GetDoubleArrayElement(IntPtr array, int index);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern IntPtr GetObjectArrayElement(IntPtr array, int index);



        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewStringUTF(string bytes);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern int PushLocalFrame(int capacity);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr PopLocalFrame(IntPtr result);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewGlobalRef(IntPtr obj);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void DeleteGlobalRef(IntPtr obj);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr NewLocalRef(IntPtr obj);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void DeleteLocalRef(IntPtr obj);


        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr GetStaticMethodID(IntPtr clazz, string name, string sig);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr FindClass(string name);



        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern string CallStringMethod(IntPtr obj, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr CallObjectMethod(IntPtr obj, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern int CallIntMethod(IntPtr obj, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern bool CallBooleanMethod(IntPtr obj, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern short CallShortMethod(IntPtr obj, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern byte CallByteMethod(IntPtr obj, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern char CallCharMethod(IntPtr obj, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern float CallFloatMethod(IntPtr obj, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern double CallDoubleMethod(IntPtr obj, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern long CallLongMethod(IntPtr obj, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void CallVoidMethod(IntPtr obj, IntPtr methodID, jvalue[] args);




        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern string CallStaticStringMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr CallStaticObjectMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern int CallStaticIntMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern bool CallStaticBooleanMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern short CallStaticShortMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern byte CallStaticByteMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern char CallStaticCharMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern float CallStaticFloatMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern double CallStaticDoubleMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern long CallStaticLongMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void CallStaticVoidMethod(IntPtr cls, IntPtr methodID, jvalue[] args);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr GetFieldID(IntPtr clazz, string name, string sig);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern IntPtr GetObjectField(IntPtr obj, IntPtr fieldID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern bool GetBooleanField(IntPtr obj, IntPtr fieldID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern byte GetByteField(IntPtr obj, IntPtr fieldID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern char GetCharField(IntPtr obj, IntPtr fieldID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern short GetShortField(IntPtr obj, IntPtr fieldID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern int GetIntField(IntPtr obj, IntPtr fieldID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern long GetLongField(IntPtr obj, IntPtr fieldID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern float GetFloatField(IntPtr obj, IntPtr fieldID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern double GetDoubleField(IntPtr obj, IntPtr fieldID);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void SetStringField(IntPtr obj, IntPtr fieldID, string val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void SetObjectField(IntPtr obj, IntPtr fieldID, IntPtr val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void SetBooleanField(IntPtr obj, IntPtr fieldID, bool val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void SetByteField(IntPtr obj, IntPtr fieldID, byte val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void SetCharField(IntPtr obj, IntPtr fieldID, char val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void SetShortField(IntPtr obj, IntPtr fieldID, short val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void SetIntField(IntPtr obj, IntPtr fieldID, int val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void SetLongField(IntPtr obj, IntPtr fieldID, long val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void SetFloatField(IntPtr obj, IntPtr fieldID, float val);

        [MethodImplAttribute(MethodImplOptions.InternalCall)]
        public static extern void SetDoubleField(IntPtr obj, IntPtr fieldID, double val);

    }
}
