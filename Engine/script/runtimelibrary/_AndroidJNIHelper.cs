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
using System.Text;

namespace ScriptRuntime
{
    public class _AndroidJNIHelper
    {
        public static jvalue[] CreateJNIArgArray(object[] args)
        {
            jvalue[] array = new jvalue[args.GetLength(0)];
            int num = 0;
            for (int i = 0; i < args.Length; i++)
            {
                object obj = args[i];
                if (obj == null)
                {
                    array[num].l = IntPtr.Zero;
                }
                else
                {
                    if (obj.GetType().IsPrimitive)
                    {
                        if (obj is int)
                        {
                            array[num].i = (int)obj;
                        }
                        else
                        {
                            if (obj is bool)
                            {
                                array[num].z = (bool)obj;
                            }
                            else
                            {
                                if (obj is byte)
                                {
                                    array[num].b = (byte)obj;
                                }
                                else
                                {
                                    if (obj is short)
                                    {
                                        array[num].s = (short)obj;
                                    }
                                    else
                                    {
                                        if (obj is long)
                                        {
                                            array[num].j = (long)obj;
                                        }
                                        else
                                        {
                                            if (obj is float)
                                            {
                                                array[num].f = (float)obj;
                                            }
                                            else
                                            {
                                                if (obj is double)
                                                {
                                                    array[num].d = (double)obj;
                                                }
                                                else
                                                {
                                                    if (obj is char)
                                                    {
                                                        array[num].c = (char)obj;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        if (obj is string)
                        {
                            array[num].l = AndroidJNI.NewStringUTF((string)obj);
                        }
                        else
                        {
                            if (obj is AndroidJavaObject)
                            {
                                array[num].l = ((AndroidJavaObject)obj).GetRawObject();
                            }
                            else
                            {
                                if (obj is Array)
                                {
                                    array[num].l = _AndroidJNIHelper.ConvertToJNIArray((Array)obj);
                                }
                                else
                                {
//                                     if (obj is AndroidJavaRunnable)
//                                     {
//                                         array[num].l = AndroidJNIHelper.CreateJavaRunnable((AndroidJavaRunnable)obj);
//                                     }
//                                     else
                                    {
                                        Debug.Warning("JNI: Unknown argument type '" + obj.GetType() + "'");
                                    }
                                }
                            }
                        }
                    }
                }
                num++;
            }
            return array;
        }


        public static IntPtr ConvertToJNIArray(Array array)
        {
            Type elementType = array.GetType().GetElementType();
            if (elementType.IsPrimitive)
            {
                if (elementType == typeof(int))
                {
                    return AndroidJNI.ToIntArray((int[])array);
                }
                if (elementType == typeof(bool))
                {
                    return AndroidJNI.ToBooleanArray((bool[])array);
                }
                if (elementType == typeof(byte))
                {
                    return AndroidJNI.ToByteArray((byte[])array);
                }
                if (elementType == typeof(short))
                {
                    return AndroidJNI.ToShortArray((short[])array);
                }
                if (elementType == typeof(long))
                {
                    return AndroidJNI.ToLongArray((long[])array);
                }
                if (elementType == typeof(float))
                {
                    return AndroidJNI.ToFloatArray((float[])array);
                }
                if (elementType == typeof(double))
                {
                    return AndroidJNI.ToDoubleArray((double[])array);
                }
                if (elementType == typeof(char))
                {
                    return AndroidJNI.ToCharArray((char[])array);
                }
            }
            else
            {
                if (elementType == typeof(string))
                {
                    string[] array2 = (string[])array;
                    int length = array.GetLength(0);
                    IntPtr[] array3 = new IntPtr[length];
                    for (int i = 0; i < length; i++)
                    {
                        array3[i] = AndroidJNI.NewStringUTF(array2[i]);
                    }
                    return AndroidJNI.ToObjectArray(array3);
                }
                if (elementType == typeof(AndroidJavaObject))
                {
                    AndroidJavaObject[] array4 = (AndroidJavaObject[])array;
                    int length2 = array.GetLength(0);
                    IntPtr[] array5 = new IntPtr[length2];
                    for (int j = 0; j < length2; j++)
                    {
                        array5[j] = ((array4[j] != null) ? array4[j].GetRawObject() : IntPtr.Zero);
                    }
                    return AndroidJNI.ToObjectArray(array5);
                }
                Debug.Warning("JNI: Unknown array type '" + elementType + "'");
            }
            return IntPtr.Zero;
        }

        public static IntPtr GetConstructorID(IntPtr jclass, object[] args)
        {
            string signature = _AndroidJNIHelper.GetSignature(args);
            IntPtr constructorID = AndroidJNIHelper.GetConstructorID(jclass, signature);
            if (constructorID == IntPtr.Zero)
            {
                Debug.Warning("JNI: Unable to find constructor method id with signature '" + signature + "'");
            }
            return constructorID;
        }

        public static string GetSignature(object[] args)
        {
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.Append('(');
            for (int i = 0; i < args.Length; i++)
            {
                object obj = args[i];
                stringBuilder.Append(_AndroidJNIHelper.GetSignature(obj));
            }
            stringBuilder.Append(")V");
            return stringBuilder.ToString();
        }

        public static string GetSignature(object obj)
        {
            if (obj == null)
            {
                return "Ljava/lang/Object;";
            }
            Type type = (!(obj is Type)) ? obj.GetType() : ((Type)obj);
            if (type.IsPrimitive)
            {
                if (type.Equals(typeof(int)))
                {
                    return "I";
                }
                if (type.Equals(typeof(bool)))
                {
                    return "Z";
                }
                if (type.Equals(typeof(byte)))
                {
                    return "B";
                }
                if (type.Equals(typeof(short)))
                {
                    return "S";
                }
                if (type.Equals(typeof(long)))
                {
                    return "J";
                }
                if (type.Equals(typeof(float)))
                {
                    return "F";
                }
                if (type.Equals(typeof(double)))
                {
                    return "D";
                }
                if (type.Equals(typeof(char)))
                {
                    return "C";
                }
            }
            else
            {
                if (type.Equals(typeof(string)))
                {
                    return "Ljava/lang/String;";
                }
//                 if (type.Equals(typeof(AndroidJavaRunnable)))
//                 {
//                     return "Ljava/lang/Runnable;";
//                 }
                if (type.Equals(typeof(AndroidJavaObject)))
                {
                    if (obj == type)
                    {
                        return "Ljava/lang/Object;";
                    }
                    AndroidJavaObject androidJavaObject = (AndroidJavaObject)obj;
                    AndroidJavaObject androidJavaObject2 ;

                    object[] args = new object[0];
                    IntPtr cachedMethodID = AndroidJNIHelper.GetMethodID<AndroidJavaObject>(androidJavaObject.GetRawClass(), "getClass", args, false);
                    jvalue[] args2 = AndroidJNIHelper.CreateJNIArgArray(args);
                    IntPtr pobj = AndroidJNI.CallObjectMethod(androidJavaObject.GetRawObject(), cachedMethodID, args2);
                    androidJavaObject2 = new AndroidJavaObject(pobj);


                    string retStr ;
                    IntPtr cachedMethodID2 = AndroidJNIHelper.GetMethodID<AndroidJavaObject>(androidJavaObject.GetRawClass(), "getName", args, false);

                    retStr = AndroidJNI.CallStringMethod(androidJavaObject2.GetRawObject(), cachedMethodID2, args2);
                    return "L" + retStr + ";";
                }
                else
                {
                    if (typeof(Array).IsAssignableFrom(type))
                    {
                        if (type.GetArrayRank() != 1)
                        {
                            Debug.Warning("JNI: System.Array in n dimensions is not allowed");
                            return string.Empty;
                        }
                        StringBuilder stringBuilder = new StringBuilder();
                        stringBuilder.Append('[');
                        stringBuilder.Append(_AndroidJNIHelper.GetSignature(type.GetElementType()));
                        return stringBuilder.ToString();
                    }
                    else
                    {
                        Debug.Warning(string.Concat(new object[]
						{
							"JNI: Unknown signature for type '",
							type,
							"' (obj = ",
							obj,
							") ",
							(type != obj) ? "instance" : "equal"
						}));
                    }
                }
            }
            return string.Empty;
        }

        public static string GetSignature<ReturnType>(object[] args)
        {
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.Append('(');
            for (int i = 0; i < args.Length; i++)
            {
                object obj = args[i];
                stringBuilder.Append(_AndroidJNIHelper.GetSignature(obj));
            }
            stringBuilder.Append(')');
            stringBuilder.Append(_AndroidJNIHelper.GetSignature(typeof(ReturnType)));
            return stringBuilder.ToString();
        }
        public static IntPtr GetMethodID(IntPtr jclass, string methodName, object[] args, bool isStatic)
        {
            string signature = _AndroidJNIHelper.GetSignature(args);
            IntPtr methodID = AndroidJNIHelper.GetMethodID(jclass, methodName, signature, isStatic);
            if (methodID == IntPtr.Zero)
            {
                Debug.Warning("JNI: Unable to find method id for '" + methodName + "'" + ((!isStatic) ? string.Empty : " (static)"));
               // AndroidJNI.ExceptionClear();
            }
            return methodID;
        }

        public static IntPtr GetMethodID<ReturnType>(IntPtr jclass, string methodName, object[] args, bool isStatic)
        {
            string signature = _AndroidJNIHelper.GetSignature<ReturnType>(args);
            IntPtr methodID = AndroidJNIHelper.GetMethodID(jclass, methodName, signature, isStatic);
            if (methodID == IntPtr.Zero)
            {
                Debug.Warning("JNI: Unable to find method id for '" + methodName + "'" + ((!isStatic) ? string.Empty : " (static)"));
                //AndroidJNI.ExceptionClear();
            }
            return methodID;
        }


//         public static ArrayType ConvertFromJNIArray<ArrayType>(IntPtr array)
//         {
//             Type elementType = typeof(ArrayType).GetElementType();
//             if (elementType.IsPrimitive)
//             {
//                 if (elementType == typeof(int))
//                 {
//                     return (ArrayType)AndroidJNI.FromIntArray(array);
//                 }
//                 if (elementType == typeof(bool))
//                 {
//                     return (ArrayType)AndroidJNI.FromBooleanArray(array);
//                 }
//                 if (elementType == typeof(byte))
//                 {
//                     return (ArrayType)AndroidJNI.FromByteArray(array);
//                 }
//                 if (elementType == typeof(short))
//                 {
//                     return (ArrayType)AndroidJNI.FromShortArray(array);
//                 }
//                 if (elementType == typeof(long))
//                 {
//                     return (ArrayType)AndroidJNI.FromLongArray(array);
//                 }
//                 if (elementType == typeof(float))
//                 {
//                     return (ArrayType)AndroidJNI.FromFloatArray(array);
//                 }
//                 if (elementType == typeof(double))
//                 {
//                     return (ArrayType)AndroidJNI.FromDoubleArray(array);
//                 }
//                 if (elementType == typeof(char))
//                 {
//                     return (ArrayType)AndroidJNI.FromCharArray(array);
//                 }
//             }
//             else
//             {
//                 if (elementType == typeof(string))
//                 {
//                     IntPtr[] array2 = AndroidJNI.FromObjectArray(array);
//                     int length = array2.GetLength(0);
//                     string[] array3 = new string[length];
//                     for (int i = 0; i < length; i++)
//                     {
//                         array3[i] = AndroidJNI.GetStringUTFChars(array2[i]);
//                     }
//                     return (ArrayType)array3;
//                 }
//                 if (elementType == typeof(AndroidJavaObject))
//                 {
//                     IntPtr[] array4 = AndroidJNI.FromObjectArray(array);
//                     int length2 = array4.GetLength(0);
//                     AndroidJavaObject[] array5 = new AndroidJavaObject[length2];
//                     for (int j = 0; j < length2; j++)
//                     {
//                         array5[j] = new AndroidJavaObject(array4[j]);
//                     }
//                     return (ArrayType)array5;
//                 }
//                 Debug.Log("JNI: Unknown generic array type '" + elementType + "'");
//             }
//             return default(ArrayType);
//         }
    }
}
