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
#include "stdneb.h"
#include "scriptfeature/inc/script_utility.h"

#if __ANDROID__
#include <jni.h>
#include "players/GenesisA/simplegameapplication.h"

namespace App
{
	void ICallReg_ScriptRuntime_AndroidJNI( void );
	using namespace Genesis;
	static gconstpointer ICall_AndroidJNI_AllocObject(gconstpointer cls)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobject jobj = jevn->AllocObject(static_cast<jclass>(cls));
		return static_cast<gconstpointer>(jobj);
	}

	static gconstpointer ICall_AndroidJNI_NewObject(gconstpointer cls,gconstpointer mtd,MonoArray* args)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jclass jcls = static_cast<jclass>(cls);
		jmethodID jmtd = static_cast<jmethodID>(mtd);
		jvalue* jargs = Utility_CreateCppArrFromMonoArr<jvalue>(args); 
		
		jobject jobj = jevn->NewObjectA(jcls,jmtd,jargs);
		Utility_FreeCppArr(jargs);

		return static_cast<gconstpointer>(jobj);
	}

	static gconstpointer ICall_AndroidJNI_GetObjectClass(gconstpointer obj)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobject jobj = static_cast<jobject>(obj);
		jclass jcls = jevn->GetObjectClass(jobj);
		return static_cast<gconstpointer>(jcls);
	}


	static gconstpointer ICall_AndroidJNI_ToBooleanArray(MonoArray* monoboolarr)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jboolean* jarr = Utility_CreateCppArrFromMonoArr<jboolean>(monoboolarr);

		size_t size			= mono_array_length( monoboolarr );
		jbooleanArray jboolarr = jevn->functions->NewBooleanArray(jevn,size);

		jevn->functions->SetBooleanArrayRegion(jevn,jboolarr,0,size,jarr);
		Utility_FreeCppArr(jarr);
		return static_cast<gconstpointer>(jboolarr);
	}

	static gconstpointer ICall_AndroidJNI_ToByteArray(MonoArray* monoarr)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jbyte* jarr = Utility_CreateCppArrFromMonoArr<jbyte>(monoarr);

		size_t size			= mono_array_length( monoarr );
		jbyteArray jboolarr = jevn->functions->NewByteArray(jevn,size);
	
		jevn->functions->SetByteArrayRegion(jevn,jboolarr,0,size,jarr);
		Utility_FreeCppArr(jarr);
		return static_cast<gconstpointer>(jboolarr);
	}

	static gconstpointer ICall_AndroidJNI_ToCharArray(MonoArray* monoarr)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jchar* jarr = Utility_CreateCppArrFromMonoArr<jchar>(monoarr);

		size_t size			= mono_array_length( monoarr );
		jcharArray jboolarr = jevn->functions->NewCharArray(jevn,size);

		jevn->functions->SetCharArrayRegion(jevn,jboolarr,0,size,jarr);
		Utility_FreeCppArr(jarr);
		return static_cast<gconstpointer>(jboolarr);
	}

	static gconstpointer ICall_AndroidJNI_ToShortArray(MonoArray* monoarr)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jshort* jarr = Utility_CreateCppArrFromMonoArr<jshort>(monoarr);

		size_t size			= mono_array_length( monoarr );
		jshortArray jboolarr = jevn->functions->NewShortArray(jevn,size);

		jevn->functions->SetShortArrayRegion(jevn,jboolarr,0,size,jarr);
		Utility_FreeCppArr(jarr);
		return static_cast<gconstpointer>(jboolarr);
	}

	static gconstpointer ICall_AndroidJNI_ToIntArray(MonoArray* monoarr)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jint* jarr = Utility_CreateCppArrFromMonoArr<jint>(monoarr);

		size_t size			= mono_array_length( monoarr );
		jintArray jboolarr = jevn->functions->NewIntArray(jevn,size);

		jevn->functions->SetIntArrayRegion(jevn,jboolarr,0,size,jarr);
		Utility_FreeCppArr(jarr);
		return static_cast<gconstpointer>(jboolarr);
	}

	static gconstpointer ICall_AndroidJNI_ToLongArray(MonoArray* monoarr)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jlong* jarr = Utility_CreateCppArrFromMonoArr<jlong>(monoarr);

		size_t size			= mono_array_length( monoarr );
		jlongArray jboolarr = jevn->functions->NewLongArray(jevn,size);

		jevn->functions->SetLongArrayRegion(jevn,jboolarr,0,size,jarr);
		Utility_FreeCppArr(jarr);
		return static_cast<gconstpointer>(jboolarr);
	}

	static gconstpointer ICall_AndroidJNI_ToFloatArray(MonoArray* monoarr)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jfloat* jarr = Utility_CreateCppArrFromMonoArr<jfloat>(monoarr);

		size_t size			= mono_array_length( monoarr );
		jfloatArray jboolarr = jevn->functions->NewFloatArray(jevn,size);

		jevn->functions->SetFloatArrayRegion(jevn,jboolarr,0,size,jarr);
		Utility_FreeCppArr(jarr);
		return static_cast<gconstpointer>(jboolarr);
	}

	static gconstpointer ICall_AndroidJNI_ToDoubleArray(MonoArray* monoarr)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jdouble* jarr = Utility_CreateCppArrFromMonoArr<jdouble>(monoarr);

		size_t size			= mono_array_length( monoarr );
		jdoubleArray jboolarr = jevn->functions->NewDoubleArray(jevn,size);

		jevn->functions->SetDoubleArrayRegion(jevn,jboolarr,0,size,jarr);
		Utility_FreeCppArr(jarr);
		return static_cast<gconstpointer>(jboolarr);
	}

	static gconstpointer ICall_AndroidJNI_ToObjectArray(MonoArray* monoarr)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobject* jarr = Utility_CreateCppArrFromMonoArr<jobject>(monoarr);
		jclass jcls=  jevn->functions->GetObjectClass(jevn,jarr[0]);
		size_t size			= mono_array_length( monoarr );
		jobjectArray jboolarr = jevn->functions->NewObjectArray(jevn,size,jcls,jarr[0]);
		for(int i = 0;i<size;i++)
		{
			jevn->functions->SetObjectArrayElement(jevn,jboolarr,i,jarr[i]);
		}
		Utility_FreeCppArr(jarr);
		return static_cast<gconstpointer>(jboolarr);
	}




	static gconstpointer ICall_AndroidJNI_NewBooleanArray(int size)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jbooleanArray jboolarr = jevn->functions->NewBooleanArray(jevn,size);
		return static_cast<gconstpointer>(jboolarr);
	}
	
	static gconstpointer ICall_AndroidJNI_NewByteArray(int size)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jbyteArray jbytearr = jevn->functions->NewByteArray(jevn,size);
		return static_cast<gconstpointer>(jbytearr);
	}

	static gconstpointer ICall_AndroidJNI_NewCharArray(int size)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jcharArray jarr = jevn->functions->NewCharArray(jevn,size);
		return static_cast<gconstpointer>(jarr);
	}
	
	static gconstpointer ICall_AndroidJNI_NewShortArray(int size)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jshortArray jarr = jevn->functions->NewShortArray(jevn,size);
		return static_cast<gconstpointer>(jarr);
	}

	static gconstpointer ICall_AndroidJNI_NewIntArray(int size)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jintArray jarr = jevn->functions->NewIntArray(jevn,size);
		return static_cast<gconstpointer>(jarr);
	}

	static gconstpointer ICall_AndroidJNI_NewLongArray(int size)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jlongArray jarr =jevn->functions->NewLongArray(jevn,size);
		return static_cast<gconstpointer>(jarr);
	}

	static gconstpointer ICall_AndroidJNI_NewFloatArray(int size)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jfloatArray jarr =jevn->functions->NewFloatArray(jevn,size);
		return static_cast<gconstpointer>(jarr);
	}

	static gconstpointer ICall_AndroidJNI_NewDoubleArray(int size)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jdoubleArray jarr = jevn->functions->NewDoubleArray(jevn,size);
		return static_cast<gconstpointer>(jarr);
	}

	static gconstpointer ICall_AndroidJNI_NewObjectArray(int size,gconstpointer clazz, gconstpointer obj)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobjectArray jarr = jevn->functions->NewObjectArray(jevn,size,(jclass)clazz,(jobject)obj);
		return static_cast<gconstpointer>(jarr);
	}

	static mono_bool ICall_AndroidJNI_GetBooleanArrayElement(gconstpointer arr,int index)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jbooleanArray jarr = static_cast<jbooleanArray>(arr);
		jboolean isCopy = true;
		jboolean* jarrele = jevn->functions->GetBooleanArrayElements(jevn,jarr,&isCopy);
		jboolean ret = jarrele[index];
		jevn->functions->ReleaseBooleanArrayElements(jevn,jarr,jarrele,0);
		return ret;
	}

	static ubyte ICall_AndroidJNI_GetByteArrayElement(gconstpointer arr,int index)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jbyteArray jarr = static_cast<jbyteArray>(arr);
		jboolean isCopy = true;
		jbyte* jarrele = jevn->functions->GetByteArrayElements(jevn,jarr,&isCopy);
		jbyte ret = jarrele[index];
		jevn->functions->ReleaseByteArrayElements(jevn,jarr,jarrele,0);
		return ret;
	}

	static char ICall_AndroidJNI_GetCharArrayElement(gconstpointer arr,int index)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jcharArray jarr = static_cast<jcharArray>(arr);
		jboolean isCopy = true;
		jchar* jarrele = jevn->functions->GetCharArrayElements(jevn,jarr,&isCopy);
		jchar ret = jarrele[index];
		jevn->functions->ReleaseCharArrayElements(jevn,jarr,jarrele,0);
		return ret;
	}

	static short ICall_AndroidJNI_GetShortArrayElement(gconstpointer arr,int index)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jshortArray jarr = static_cast<jshortArray>(arr);
		jboolean isCopy = true;
		jshort* jarrele = jevn->functions->GetShortArrayElements(jevn,jarr,&isCopy);
		jshort ret = jarrele[index];
		jevn->functions->ReleaseShortArrayElements(jevn,jarr,jarrele,0);
		return ret;
	}

	static int ICall_AndroidJNI_GetIntArrayElement(gconstpointer arr,int index)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jintArray jarr = static_cast<jintArray>(arr);
		jboolean isCopy = true;
		jint* jarrele = jevn->functions->GetIntArrayElements(jevn,jarr,&isCopy);
		jint ret = jarrele[index];
		jevn->functions->ReleaseIntArrayElements(jevn,jarr,jarrele,0);
		return ret;
	}

	static long ICall_AndroidJNI_GetLongArrayElement(gconstpointer arr,int index)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jlongArray jarr = static_cast<jlongArray>(arr);
		jboolean isCopy = true;
		jlong* jarrele = jevn->functions->GetLongArrayElements(jevn,jarr,&isCopy);
		jlong ret = jarrele[index];
		jevn->functions->ReleaseLongArrayElements(jevn,jarr,jarrele,0);
		return ret;
	}

	static float ICall_AndroidJNI_GetFloatArrayElement(gconstpointer arr,int index)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jfloatArray jarr = static_cast<jfloatArray>(arr);
		jboolean isCopy = true;
		jfloat* jarrele = jevn->functions->GetFloatArrayElements(jevn,jarr,&isCopy);
		jfloat ret = jarrele[index];
		jevn->functions->ReleaseFloatArrayElements(jevn,jarr,jarrele,0);
		return ret;
	}

	static double ICall_AndroidJNI_GetDoubleArrayElement(gconstpointer arr,int index)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jdoubleArray jarr = static_cast<jdoubleArray>(arr);
		jboolean isCopy = true;
		jdouble* jarrele = jevn->functions->GetDoubleArrayElements(jevn,jarr,&isCopy);
		jdouble ret = jarrele[index];
		jevn->functions->ReleaseDoubleArrayElements(jevn,jarr,jarrele,0);
		return ret;
	}

	static gconstpointer ICall_AndroidJNI_GetObjectArrayElement(gconstpointer arr,int index)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobjectArray jarr = static_cast<jobjectArray>(arr);
		jobject jarrele = jevn->functions->GetObjectArrayElement(jevn,jarr,index);
		return static_cast<gconstpointer>(jarrele);
	}

	static gconstpointer ICall_AndroidJNI_NewStringUTF(MonoString* bytes)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		Util::String strBytes = Utility_MonoStringToCppString(bytes);
		jstring jstr = jevn->functions->NewStringUTF(jevn,strBytes.AsCharPtr());
		return static_cast<gconstpointer>(jstr);
	}

	static int ICall_AndroidJNI_PushLocalFrame(int capacity)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		int ret = jevn->functions->PushLocalFrame(jevn,capacity);
		return ret;
	}

	static gconstpointer ICall_AndroidJNI_PopLocalFrame(gconstpointer returna)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobject ret = jevn->functions->PopLocalFrame(jevn,(jobject)returna);
		return static_cast<gconstpointer>(ret);
	}

	static gconstpointer ICall_AndroidJNI_NewLocalRef(gconstpointer obj)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobject jobj =	static_cast<jobject>(obj);

		jobject ret = jevn->functions->NewLocalRef(jevn,jobj);
		return ret;
	}

	static void ICall_AndroidJNI_DeleteLocalRef(gconstpointer obj)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobject jobj =	static_cast<jobject>(obj);

		jevn->functions->DeleteLocalRef(jevn,jobj);
	}
	
	static gconstpointer ICall_AndroidJNI_NewGlobalRef(gconstpointer obj)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobject jobj =	static_cast<jobject>(obj);

		jobject ret = jevn->functions->NewGlobalRef(jevn,jobj);
		return ret;
	}

	static void ICall_AndroidJNI_DeleteGlobalRef(gconstpointer obj)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobject jobj =	static_cast<jobject>(obj);

		jevn->functions->DeleteGlobalRef(jevn,jobj);
	}

	static gconstpointer ICall_AndroidJNI_GetStaticMethodID(gconstpointer cls,MonoString*  monoName,MonoString*  monoSig)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		Util::String name = Utility_MonoStringToCppString(monoName);
		Util::String sig = Utility_MonoStringToCppString(monoSig);
		jclass jcls =	static_cast<jclass>(cls);

		jmethodID mth = jevn->functions->GetStaticMethodID(jevn,jcls,name.AsCharPtr(),sig.AsCharPtr());
		return mth;
	}

	static gconstpointer ICall_AndroidJNI_FindClass(MonoString* monoStr)
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		Util::String str = Utility_MonoStringToCppString(monoStr);
		jclass cls =	jevn->functions->FindClass(jevn,str.AsCharPtr());

		return cls;
	}

	static MonoString* ICall_AndroidJNI_CallStringMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		
		Utility_FreeCppArr(jargs);
		return NULL;
	}

	static gconstpointer ICall_AndroidJNI_CallObjectMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		jobject ret =  jevn->functions->CallObjectMethodA(jevn,jobj,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static int ICall_AndroidJNI_CallIntMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		int ret = jevn->functions->CallIntMethodA(jevn,jobj,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static mono_bool ICall_AndroidJNI_CallBooleanMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		bool ret = jevn->functions->CallBooleanMethodA(jevn,jobj,jmth,jargs);
		Utility_FreeCppArr(jargs);

		return Utility_MonoBool(ret) ;
	}

	static short ICall_AndroidJNI_CallShortMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		short ret =	jevn->functions->CallShortMethodA(jevn,jobj,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static ubyte ICall_AndroidJNI_CallByteMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		ubyte ret = jevn->functions->CallByteMethodA(jevn,jobj,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static char ICall_AndroidJNI_CallCharMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		char ret = jevn->functions->CallCharMethodA(jevn,jobj,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static float ICall_AndroidJNI_CallFloatMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		float ret = jevn->functions->CallFloatMethodA(jevn,jobj,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}	
	
	static double ICall_AndroidJNI_CallDoubleMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		double ret = jevn->functions->CallDoubleMethodA(jevn,jobj,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}	
	
	static long ICall_AndroidJNI_CallLongMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		long ret = jevn->functions->CallLongMethodA(jevn,jobj,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static void ICall_AndroidJNI_CallVoidMethod(gconstpointer obj,gconstpointer methodID,MonoArray*  args)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		jevn->functions->CallVoidMethodA(jevn,jobj,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return;
	}

	static MonoString* ICall_AndroidJNI_CallStaticStringMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();


		Utility_FreeCppArr(jargs);
		return NULL;
	}

	static gconstpointer ICall_AndroidJNI_CallStaticObjectMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		jobject ret =  jevn->functions->CallStaticObjectMethodA(jevn,jcls,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static int ICall_AndroidJNI_CallStaticIntMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		int ret = jevn->functions->CallStaticIntMethodA(jevn,jcls,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static mono_bool ICall_AndroidJNI_CallStaticBooleanMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		bool ret = jevn->functions->CallStaticBooleanMethodA(jevn,jcls,jmth,jargs);
		Utility_FreeCppArr(jargs);

		return Utility_MonoBool(ret) ;
	}

	static short ICall_AndroidJNI_CallStaticShortMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		short ret =	jevn->functions->CallStaticShortMethodA(jevn,jcls,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static ubyte ICall_AndroidJNI_CallStaticByteMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		ubyte ret = jevn->functions->CallStaticByteMethodA(jevn,jcls,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static char ICall_AndroidJNI_CallStaticCharMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		char ret = jevn->functions->CallStaticCharMethodA(jevn,jcls,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static float ICall_AndroidJNI_CallStaticFloatMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		float ret = jevn->functions->CallStaticFloatMethodA(jevn,jcls,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}	

	static double ICall_AndroidJNI_CallStaticDoubleMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		double ret = jevn->functions->CallStaticDoubleMethodA(jevn,jcls,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}	

	static long ICall_AndroidJNI_CallStaticLongMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		long ret = jevn->functions->CallStaticLongMethodA(jevn,jcls,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return ret;
	}

	static void ICall_AndroidJNI_CallStaticVoidMethod(gconstpointer cls,gconstpointer methodID,MonoArray*  args)
	{
		jclass		jcls = static_cast<jclass>(cls);
		jmethodID   jmth = static_cast<jmethodID>(methodID);
		jvalue* jargs    =  Utility_CreateCppArrFromMonoArr<jvalue>(args);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();

		jevn->functions->CallStaticVoidMethodA(jevn,jcls,jmth,jargs);
		Utility_FreeCppArr(jargs);
		return;
	}

	static gconstpointer ICall_AndroidJNI_GetFieldID(gconstpointer cls,MonoString* name ,MonoString* sig)
	{
		jclass		jcls = static_cast<jclass>(cls);
		Util::String cppName = Utility_MonoStringToCppString(name);
		Util::String cppSig  = Utility_MonoStringToCppString(sig);

		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jfieldID fieldID =jevn->functions->GetFieldID(jevn,jcls,cppName.AsCharPtr(),cppSig.AsCharPtr());
		return static_cast<gconstpointer>(fieldID);
	}

	static gconstpointer ICall_AndroidJNI_GetObjectFeild(gconstpointer obj,gconstpointer fieldID)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jobject ret =jevn->functions->GetObjectField(jevn,jobj,jfID);
		return static_cast<jobject>(ret);
	}

	static bool ICall_AndroidJNI_GetBooleanFeild(gconstpointer obj,gconstpointer fieldID)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		return jevn->functions->GetBooleanField(jevn,jobj,jfID);
	}

	static ubyte ICall_AndroidJNI_GetByteFeild(gconstpointer obj,gconstpointer fieldID)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		return jevn->functions->GetByteField(jevn,jobj,jfID);
	}

	static char ICall_AndroidJNI_GetCharFeild(gconstpointer obj,gconstpointer fieldID)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		return jevn->functions->GetCharField(jevn,jobj,jfID);
	}

	static short ICall_AndroidJNI_GetShortFeild(gconstpointer obj,gconstpointer fieldID)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		return jevn->functions->GetShortField(jevn,jobj,jfID);
	}

	static int ICall_AndroidJNI_GetIntFeild(gconstpointer obj,gconstpointer fieldID)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		return jevn->functions->GetIntField(jevn,jobj,jfID);
	}

	static long ICall_AndroidJNI_GetLongFeild(gconstpointer obj,gconstpointer fieldID)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		return jevn->functions->GetLongField(jevn,jobj,jfID);
	}

	static float ICall_AndroidJNI_GetFloatFeild(gconstpointer obj,gconstpointer fieldID)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		return jevn->functions->GetFloatField(jevn,jobj,jfID);
	}

	static double ICall_AndroidJNI_GetDoubleFeild(gconstpointer obj,gconstpointer fieldID)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		return jevn->functions->GetDoubleField(jevn,jobj,jfID);
	}

	static void ICall_AndroidJNI_SetObjectFeild(gconstpointer obj,gconstpointer fieldID,gconstpointer objv)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jobject     jobjv = static_cast<jobject>(objv); 
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jevn->functions->SetObjectField(jevn,jobj,jfID,jobjv);
	}

	static void ICall_AndroidJNI_SetBooleanFeild(gconstpointer obj,gconstpointer fieldID,mono_bool v)
	{
		jobject		jobj = static_cast<jobject>(obj);
		bool         jv = Utility_MonoBool(v);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jevn->functions->SetBooleanField(jevn,jobj,jfID,jv);
	}

	static void ICall_AndroidJNI_SetByteFeild(gconstpointer obj,gconstpointer fieldID,ubyte v)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jevn->functions->SetByteField(jevn,jobj,jfID,v);
	}


	static void ICall_AndroidJNI_SetCharFeild(gconstpointer obj,gconstpointer fieldID,char v)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jevn->functions->SetCharField(jevn,jobj,jfID,v);
	}

	static void ICall_AndroidJNI_SetShortFeild(gconstpointer obj,gconstpointer fieldID,short v)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jevn->functions->SetShortField(jevn,jobj,jfID,v);
	}

	static void ICall_AndroidJNI_SetIntFeild(gconstpointer obj,gconstpointer fieldID,int v)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jevn->functions->SetIntField(jevn,jobj,jfID,v);
	}

	static void ICall_AndroidJNI_SetLongFeild(gconstpointer obj,gconstpointer fieldID,long v)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jevn->functions->SetLongField(jevn,jobj,jfID,v);
	}

	static void ICall_AndroidJNI_SetFloatFeild(gconstpointer obj,gconstpointer fieldID,float v)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jevn->functions->SetFloatField(jevn,jobj,jfID,v);
	}

	static void ICall_AndroidJNI_SetDoubleFeild(gconstpointer obj,gconstpointer fieldID,double v)
	{
		jobject		jobj = static_cast<jobject>(obj);
		jfieldID	jfID = static_cast<jfieldID>(fieldID);
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jevn->functions->SetDoubleField(jevn,jobj,jfID,v);
	}


	void ICallReg_ScriptRuntime_AndroidJNI( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.AndroidJNI::AllocObject"			 , (void*)&ICall_AndroidJNI_AllocObject },
			{ "ScriptRuntime.AndroidJNI::NewObject"			 , (void*)&ICall_AndroidJNI_NewObject },
			{ "ScriptRuntime.AndroidJNI::GetObjectClass"			 , (void*)&ICall_AndroidJNI_GetObjectClass },

			{ "ScriptRuntime.AndroidJNI::ToBooleanArray"		 , (void*)&ICall_AndroidJNI_ToBooleanArray },
			{ "ScriptRuntime.AndroidJNI::ToByteArray"			 , (void*)&ICall_AndroidJNI_ToByteArray },
			{ "ScriptRuntime.AndroidJNI::ToCharArray"			 , (void*)&ICall_AndroidJNI_ToCharArray },
			{ "ScriptRuntime.AndroidJNI::ToShortArray"			 , (void*)&ICall_AndroidJNI_ToShortArray },
			{ "ScriptRuntime.AndroidJNI::ToIntArray"			 , (void*)&ICall_AndroidJNI_ToIntArray },
			{ "ScriptRuntime.AndroidJNI::ToLongArray"			 , (void*)&ICall_AndroidJNI_ToLongArray },
			{ "ScriptRuntime.AndroidJNI::ToFloatArray"			 , (void*)&ICall_AndroidJNI_ToFloatArray },
			{ "ScriptRuntime.AndroidJNI::ToDoubleArray"	     , (void*)&ICall_AndroidJNI_ToDoubleArray },
			{ "ScriptRuntime.AndroidJNI::ToObjectArray"	     , (void*)&ICall_AndroidJNI_ToObjectArray },

			{ "ScriptRuntime.AndroidJNI::NewBooleanArray"		 , (void*)&ICall_AndroidJNI_NewBooleanArray },
			{ "ScriptRuntime.AndroidJNI::NewByteArray"			 , (void*)&ICall_AndroidJNI_NewByteArray },
			{ "ScriptRuntime.AndroidJNI::NewCharArray"			 , (void*)&ICall_AndroidJNI_NewCharArray },
			{ "ScriptRuntime.AndroidJNI::NewShortArray"	     , (void*)&ICall_AndroidJNI_NewShortArray },
			{ "ScriptRuntime.AndroidJNI::NewIntArray"			 , (void*)&ICall_AndroidJNI_NewIntArray },
			{ "ScriptRuntime.AndroidJNI::NewLongArray"			 , (void*)&ICall_AndroidJNI_NewLongArray },
			{ "ScriptRuntime.AndroidJNI::NewFloatArray"		 , (void*)&ICall_AndroidJNI_NewFloatArray },
			{ "ScriptRuntime.AndroidJNI::NewDoubleArray"	     , (void*)&ICall_AndroidJNI_NewDoubleArray },
			{ "ScriptRuntime.AndroidJNI::NewObjectArray"	     , (void*)&ICall_AndroidJNI_NewObjectArray },

			{ "ScriptRuntime.AndroidJNI::GetBooleanArrayElement"		 , (void*)&ICall_AndroidJNI_GetBooleanArrayElement },
			{ "ScriptRuntime.AndroidJNI::GetByteArrayElement"			 , (void*)&ICall_AndroidJNI_GetByteArrayElement },
			{ "ScriptRuntime.AndroidJNI::GetCharArrayElement"			 , (void*)&ICall_AndroidJNI_GetCharArrayElement },
			{ "ScriptRuntime.AndroidJNI::GetShortArrayElement"			 , (void*)&ICall_AndroidJNI_GetShortArrayElement },
			{ "ScriptRuntime.AndroidJNI::GetIntArrayElement"			 , (void*)&ICall_AndroidJNI_GetIntArrayElement },
			{ "ScriptRuntime.AndroidJNI::GetLongArrayElement"			 , (void*)&ICall_AndroidJNI_GetLongArrayElement },
			{ "ScriptRuntime.AndroidJNI::GetFloatArrayElement"			 , (void*)&ICall_AndroidJNI_GetFloatArrayElement },
			{ "ScriptRuntime.AndroidJNI::GetDoubleArrayElement"	     , (void*)&ICall_AndroidJNI_GetDoubleArrayElement },
			{ "ScriptRuntime.AndroidJNI::GetObjectArrayElement"		 , (void*)&ICall_AndroidJNI_GetObjectArrayElement },

			{ "ScriptRuntime.AndroidJNI::NewStringUTF"			 , (void*)&ICall_AndroidJNI_NewStringUTF },
			{ "ScriptRuntime.AndroidJNI::PushLocalFrame"			 , (void*)&ICall_AndroidJNI_PushLocalFrame },
			{ "ScriptRuntime.AndroidJNI::PopLocalFrame"			 , (void*)&ICall_AndroidJNI_PopLocalFrame },
			{ "ScriptRuntime.AndroidJNI::NewLocalRef"			 , (void*)&ICall_AndroidJNI_NewLocalRef },
			{ "ScriptRuntime.AndroidJNI::DeleteLocalRef"			 , (void*)&ICall_AndroidJNI_DeleteLocalRef },
			{ "ScriptRuntime.AndroidJNI::NewGlobalRef"			 , (void*)&ICall_AndroidJNI_NewGlobalRef },
			{ "ScriptRuntime.AndroidJNI::DeleteGlobalRef"		 , (void*)&ICall_AndroidJNI_DeleteGlobalRef },
			{ "ScriptRuntime.AndroidJNI::GetStaticMethodID"			 , (void*)&ICall_AndroidJNI_GetStaticMethodID },
			{ "ScriptRuntime.AndroidJNI::FindClass"			 , (void*)&ICall_AndroidJNI_FindClass },


			{ "ScriptRuntime.AndroidJNI::CallStringMethod"			 , (void*)&ICall_AndroidJNI_CallStringMethod },
			{ "ScriptRuntime.AndroidJNI::CallObjectMethod"			 , (void*)&ICall_AndroidJNI_CallObjectMethod },
			{ "ScriptRuntime.AndroidJNI::CallIntMethod"			 , (void*)&ICall_AndroidJNI_CallIntMethod },

			{ "ScriptRuntime.AndroidJNI::CallBooleanMethod"		, (void*)&ICall_AndroidJNI_CallBooleanMethod },
			{ "ScriptRuntime.AndroidJNI::CallShortMethod"			 , (void*)&ICall_AndroidJNI_CallShortMethod },
			{ "ScriptRuntime.AndroidJNI::CallByteMethod"			 , (void*)&ICall_AndroidJNI_CallByteMethod },

			{ "ScriptRuntime.AndroidJNI::CallCharMethod"		, (void*)&ICall_AndroidJNI_CallCharMethod },
			{ "ScriptRuntime.AndroidJNI::CallFloatMethod"			 , (void*)&ICall_AndroidJNI_CallFloatMethod },
			{ "ScriptRuntime.AndroidJNI::CallDoubleMethod"			 , (void*)&ICall_AndroidJNI_CallDoubleMethod },
			{ "ScriptRuntime.AndroidJNI::CallLongMethod"		, (void*)&ICall_AndroidJNI_CallLongMethod },
			{ "ScriptRuntime.AndroidJNI::CallVoidMethod"			 , (void*)&ICall_AndroidJNI_CallVoidMethod },

			{ "ScriptRuntime.AndroidJNI::CallStaticStringMethod"			 , (void*)&ICall_AndroidJNI_CallStaticStringMethod },
			{ "ScriptRuntime.AndroidJNI::CallStaticObjectMethod"			 , (void*)&ICall_AndroidJNI_CallStaticObjectMethod },
			{ "ScriptRuntime.AndroidJNI::CallStaticIntMethod"			 , (void*)&ICall_AndroidJNI_CallStaticIntMethod },

			{ "ScriptRuntime.AndroidJNI::CallStaticBooleanMethod"		, (void*)&ICall_AndroidJNI_CallStaticBooleanMethod },
			{ "ScriptRuntime.AndroidJNI::CallStaticShortMethod"			 , (void*)&ICall_AndroidJNI_CallStaticShortMethod },
			{ "ScriptRuntime.AndroidJNI::CallStaticByteMethod"			 , (void*)&ICall_AndroidJNI_CallStaticByteMethod },

			{ "ScriptRuntime.AndroidJNI::CallStaticCharMethod"		, (void*)&ICall_AndroidJNI_CallStaticCharMethod },
			{ "ScriptRuntime.AndroidJNI::CallStaticFloatMethod"			 , (void*)&ICall_AndroidJNI_CallStaticFloatMethod },
			{ "ScriptRuntime.AndroidJNI::CallStaticDoubleMethod"			 , (void*)&ICall_AndroidJNI_CallStaticDoubleMethod },
			{ "ScriptRuntime.AndroidJNI::CallStaticLongMethod"		, (void*)&ICall_AndroidJNI_CallStaticLongMethod },
			{ "ScriptRuntime.AndroidJNI::CallStaticVoidMethod"			 , (void*)&ICall_AndroidJNI_CallStaticVoidMethod },

			{ "ScriptRuntime.AndroidJNI::GetFieldID"			 , (void*)&ICall_AndroidJNI_GetFieldID },


			{ "ScriptRuntime.AndroidJNI::GetObjectFeild"			 , (void*)&ICall_AndroidJNI_GetObjectFeild },
			{ "ScriptRuntime.AndroidJNI::GetBooleanFeild"			 , (void*)&ICall_AndroidJNI_GetBooleanFeild },
			{ "ScriptRuntime.AndroidJNI::GetByteFeild"				 , (void*)&ICall_AndroidJNI_GetByteFeild },
			{ "ScriptRuntime.AndroidJNI::GetCharFeild"			     , (void*)&ICall_AndroidJNI_GetCharFeild },
			{ "ScriptRuntime.AndroidJNI::GetShortFeild"			     , (void*)&ICall_AndroidJNI_GetShortFeild },
			{ "ScriptRuntime.AndroidJNI::GetIntFeild"				 , (void*)&ICall_AndroidJNI_GetIntFeild },
			{ "ScriptRuntime.AndroidJNI::GetLongFeild"			     , (void*)&ICall_AndroidJNI_GetLongFeild },
			{ "ScriptRuntime.AndroidJNI::GetFloatFeild"			     , (void*)&ICall_AndroidJNI_GetFloatFeild },
			{ "ScriptRuntime.AndroidJNI::GetDoubleFeild"			 , (void*)&ICall_AndroidJNI_GetDoubleFeild },

			{ "ScriptRuntime.AndroidJNI::SetObjectFeild"			 , (void*)&ICall_AndroidJNI_SetObjectFeild },
			{ "ScriptRuntime.AndroidJNI::SetBooleanFeild"			 , (void*)&ICall_AndroidJNI_SetBooleanFeild },
			{ "ScriptRuntime.AndroidJNI::SetByteFeild"				 , (void*)&ICall_AndroidJNI_SetByteFeild },
			{ "ScriptRuntime.AndroidJNI::SetCharFeild"			     , (void*)&ICall_AndroidJNI_SetCharFeild },
			{ "ScriptRuntime.AndroidJNI::SetShortFeild"			     , (void*)&ICall_AndroidJNI_SetShortFeild },
			{ "ScriptRuntime.AndroidJNI::SetIntFeild"				 , (void*)&ICall_AndroidJNI_SetIntFeild },
			{ "ScriptRuntime.AndroidJNI::SetLongFeild"			     , (void*)&ICall_AndroidJNI_SetLongFeild },
			{ "ScriptRuntime.AndroidJNI::SetFloatFeild"			     , (void*)&ICall_AndroidJNI_SetFloatFeild },
			{ "ScriptRuntime.AndroidJNI::SetDoubleFeild"			 , (void*)&ICall_AndroidJNI_SetDoubleFeild },
		};


		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}
#endif