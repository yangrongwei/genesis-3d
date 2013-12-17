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
#include "appframework/actor.h"
#include "scriptfeature/inc/script_instance.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_utility.h"

namespace App
{
	void ICallReg_ScriptRuntime_ScriptableClass( void );
	//------------------------------------------------------------------------
	static MonoObject* ICall_ScriptableClass_GetOwner( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<ScriptInstance> self( pMonoObj );
		ScriptInstance* pInstance = self.GetCppObjPtr();
		Actor* pActor = pInstance->GetOwner();
		return CppPointerToScriptObj<Actor>( pActor );
	}
	//------------------------------------------------------------------------
	static void ICall_ScriptableClass_SetName( MonoObject* pMonoObj , MonoString* pMonoStr)
	{
		ScriptObjWrapper<ScriptInstance> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoStr );
		self->SetName(name);
	}
	//------------------------------------------------------------------------
	static MonoString* ICall_ScriptableClass_GetName( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<ScriptInstance> self( pMonoObj );
		Util::String sName = self->GetName();
		return Utility_NewMonoString( sName );
	}
    //------------------------------------------------------------------------
	static void ICall_ScriptableClass_Release( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<ScriptInstance> self( pMonoObj );
		ReleaseCppObjWithMonoObj<App::ScriptInstance>(self.GetCppObjPtr(),pMonoObj);
	}
	//------------------------------------------------------------------------
	void ICallReg_ScriptRuntime_ScriptableClass( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.ScriptableClass::ICall_ScriptableClass_GetOwner", (void*)&ICall_ScriptableClass_GetOwner },
			{ "ScriptRuntime.ScriptableClass::ICall_ScriptableClass_SetName",  (void*)&ICall_ScriptableClass_SetName },
			{ "ScriptRuntime.ScriptableClass::ICall_ScriptableClass_Release",  (void*)&ICall_ScriptableClass_Release },
			{ "ScriptRuntime.ScriptableClass::ICall_ScriptableClass_GetName",  (void*)&ICall_ScriptableClass_GetName },
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
									s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}

}