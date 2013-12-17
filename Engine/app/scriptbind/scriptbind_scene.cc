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
#include "scriptfeature/inc/script_component.h"
#include "scriptfeature/inc/script_utility.h"
#include "foundation/core/rtti.h"
#include "appframework/scene.h"


using namespace Util;

namespace App
{
	void ICallReg_ScriptRuntime_Scene( void );

	static void ICall_Scene_Release( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Scene> self( pMonoObj );
		Scene* pInst = self.GetCppObjPtr();
		n_assert( NULL!=pInst );
		ReleaseCppObjWithMonoObj<Scene>( pInst, pMonoObj );
	}

	static int ICall_Scene_GetActorCount( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Scene> self( pMonoObj );

		return (int)self->GetActorCount();
	}

	static MonoObject* ICall_Scene_GetActor( MonoObject* pMonoObj, int index )
	{
		ScriptObjWrapper<Scene> self( pMonoObj );
		const GPtr<Actor>& pActor =  self->GetActor(index);
		if ( pActor.isvalid() )
		{
			return CppObjectToScriptObj( *pActor );
		}
		return NULL;
	}

	static MonoObject* ICall_Scene_FindActorByFastID( MonoObject* pMonoObj, uint index )
	{
		ScriptObjWrapper<Scene> self( pMonoObj );
		const GPtr<Actor>& pActor =  self->FindActor(index);
		if ( pActor.isvalid() )
		{
			return CppObjectToScriptObj( *pActor );
		}
		return NULL;
	}

	static MonoObject* ICall_Scene_FindActorByTag( MonoObject* pMonoObj, uint index )
	{
		ScriptObjWrapper<Scene> self( pMonoObj );
		const GPtr<Actor>& pActor =  self->FindActorByTag(index);
		if ( pActor.isvalid() )
		{
			return CppObjectToScriptObj( *pActor );
		}
		return NULL;
	}

	static MonoArray* ICall_Scene_FindActorsByTag( MonoObject* pMonoObj, uint index )
	{
		Util::Array< GPtr<Actor> > actors;
		ScriptObjWrapper<Scene> self( pMonoObj );
		self->FindActorsByTag(index,actors);
		return Utility_CppArrToMonoArr(actors);
	}

	static mono_bool ICall_Scene_AddActor( MonoObject* pMonoObj, MonoObject* pActor )
	{
		ScriptObjWrapper<Scene> self( pMonoObj );
		ScriptObjWrapper<Actor> add( pActor );
		GPtr<Actor> actorPtr(add.GetCppObjPtr());
		self->AddActor( actorPtr );
		return c_iMonoBool_True;
	}

	static mono_bool ICall_Scene_RemoveActor( MonoObject* pMonoObj, MonoObject* pActor )
	{
		ScriptObjWrapper<Scene> self( pMonoObj );
		ScriptObjWrapper<Actor> sub( pActor );
		GPtr<Actor> actorPtr(sub.GetCppObjPtr());
		self->RemoveActor( actorPtr );
		return c_iMonoBool_True;
	}

	static MonoObject* ICall_Scene_FindActorByGuid( MonoObject* pMonoObj, MonoArray* guid)
	{
		ScriptObjWrapper<Scene> self( pMonoObj );

		Util::Guid uGuid = Utility_MonoGuidToUtilGuid(guid);

		const GPtr<Actor>& pActor = self->FindActor(uGuid);
		if ( pActor.isvalid() )
		{
			return CppObjectToScriptObj( *pActor );
		}
		return NULL;
	}

	static MonoObject* ICall_Scene_FindActorByName( MonoObject* pMonoObj, MonoString* name)
	{
		ScriptObjWrapper<Scene> self( pMonoObj );

		Util::String uString;
		Utility_MonoStringToCppString(name, uString);

		const GPtr<Actor>& pActor = self->FindActor(uString);
		if ( pActor.isvalid() )
		{
			return CppObjectToScriptObj( *pActor );
		}
		return NULL;
	}

}

#include "autogen/scriptbind_Scene_register.h"
