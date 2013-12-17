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
	void ICallReg_ScriptRuntime_AndroidJNIHelper( void );

	//------------------------------------------------------------------------
	using namespace Genesis;
	static gconstpointer ICall_AndroidJNIHelper_GetMethodID(gconstpointer cls,MonoString* name,MonoString* sig,mono_bool isStatic )
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jclass jcls = static_cast<jclass>(cls);
		Util::String cppName = Utility_MonoStringToCppString(name);
		Util::String cppSig = Utility_MonoStringToCppString(sig);
		bool cppStatic = Utility_MonoBool(isStatic);
		jmethodID jmtd;
		if(cppStatic)
		{
			jmtd = jevn->functions->GetStaticMethodID(jevn,jcls,cppName.AsCharPtr(),cppSig.AsCharPtr());
		} 
		else
		{
			jmtd = jevn->functions->GetMethodID(jevn,jcls,cppName.AsCharPtr(),cppSig.AsCharPtr());
		}
		
		return static_cast<gconstpointer>(jmtd);
	}


	static gconstpointer ICall_AndroidJNIHelper_GetConstructorID(gconstpointer cls,MonoString* sig )
	{
		JNIEnv* jevn = DemoPublishGameApplication::Instance()->GetJNIEvn();
		jclass jcls = static_cast<jclass>(cls);
		Util::String cppSig = Utility_MonoStringToCppString(sig);
		jmethodID jmtd = jevn->functions->GetMethodID(jevn,jcls,"<init>",cppSig.AsCharPtr());
		return static_cast<gconstpointer>(jmtd);
	}

	void ICallReg_ScriptRuntime_AndroidJNIHelper( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.AndroidJNIHelper::ICall_AndroidJNIHelper_GetMethodID",									 (void*)&ICall_AndroidJNIHelper_GetMethodID },
			{ "ScriptRuntime.AndroidJNIHelper::ICall_AndroidJNIHelper_GetConstructorID",							 (void*)&ICall_AndroidJNIHelper_GetConstructorID },
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

