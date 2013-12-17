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
#include "scriptfeature/inc/script_instance.h"
#include "scriptfeature/mono_script.h"
#include "scriptfeature/inc/script_utility.h"
#include "app/basegamefeature/managers/timesource.h"
#include "basegamefeature/managers/sceneschedulemanager.h"
#include "scriptfeature/script_root_instance.h"


namespace App
{
	void ICallReg_ScriptRuntime_Util( void );

	static float ICall_Util_GetDeltaTime( void )
	{
		return static_cast<float>(App::GameTime::Instance()->GetFrameTime());
	}

	static mono_bool ICall_Util_SaveScene( MonoString* pMonoString )
	{
		Util::String sceneFile = Utility_MonoStringToCppString( pMonoString );
		App::SceneScheduleManager* pSceneSchedule = App::SceneScheduleManager::Instance();
		bool b = pSceneSchedule->SaveScene(sceneFile);
		if ( b )
		{
			return c_iMonoBool_True;
		}
		else
		{
			return c_iMonoBool_False;
		}
	}

	static MonoObject* ICall_Util_GetRootScript( void )
	{	
		if (ScriptRootInstance::HasInstance())
		{
			MonoObject* ret = ScriptRootInstance::Instance()->GetMonoObj();
			return ret;
		}
		return NULL;
	}

	void ICallReg_ScriptRuntime_Util( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.Util::ICall_Util_GetDeltaTime"			 , (void*)&ICall_Util_GetDeltaTime },
			{ "ScriptRuntime.Util::ICall_Util_SaveScene"			 , (void*)&ICall_Util_SaveScene },
			{ "ScriptRuntime.Util::ICall_Util_GetRootScript"		 , (void*)&ICall_Util_GetRootScript },
		};


		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}
}