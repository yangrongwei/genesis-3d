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
#include "scriptfeature/inc/script_utility.h"
#include "appframework/actormanager.h"
#include "appframework/app_fwd_decl.h"
#include "graphicfeature/graphicsfeature.h"

namespace App
{
	void ICallReg_ScriptRuntime_ActorManager( void );

	static MonoObject* ICall_ActorManager_CreateFromTemplate(MonoString* pMonoString, mono_bool bCopy)
	{	
		Util::String name = Utility_MonoStringToCppString( pMonoString );
		TActorPtr pActor =ActorManager::Instance()->CreateFromTemplate( name );
		return CppPointerToScriptObj( pActor.get_unsafe() );//empty pointer is allowed here.
	}

	static MonoObject* ICall_ActorManager_GetActiveActor(int i)
	{
		TActorPtr pActor = ActorManager::Instance()->GetActiveActor(i);

		return CppPointerToScriptObj( pActor.get_unsafe() );
	}

	static int ICall_ActorManager_GetActiveActorCount()
	{
		return ActorManager::Instance()->GetActiveActorCount();
	}

	static MonoObject* ICall_ActorManager_FindActiveActorByFastID(App::Actor::FastId fastID)
	{
		Actor* actor = ActorManager::Instance()->FindActiveActor(fastID);
		if (actor)
		{
			return CppObjectToScriptObj( *actor );
		}
		return NULL;
	}

	static MonoArray* ICall_ActorManager_FindActiveActorsInGroup(App::TagID tagID)
	{
		Util::Array< GPtr<Actor> > actors;
		ActorManager::Instance()->FindActiveActorsInGroup(tagID,actors);
		
	
		return Utility_CppArrToMonoArr(actors);
	}

	static MonoObject* ICall_ActorManager_FindActiveActorInGroup(App::TagID tagID)
	{
		Actor* actor = ActorManager::Instance()->FindActiveActorInGroup(tagID);
		if(actor)
		{
			return CppObjectToScriptObj( *actor );
		}
		return NULL;
	}
	static MonoObject* ICall_ActorManager_FindActiveActorByGuid(MonoArray* guid)
	{
		Util::Guid uGuid = Utility_MonoGuidToUtilGuid(guid);
		Actor* actor = ActorManager::Instance()->FindActiveActorByGUID(uGuid);
		if (actor)
		{
			return CppObjectToScriptObj( *actor );
		}
		return NULL;
	}

	static MonoObject* ICall_ActorManager_FindActiveActorByName(MonoString* name)
	{
		Util::String uName;
		Utility_MonoStringToCppString(name, uName);
		Actor* actor = ActorManager::Instance()->FindActiveActorByName(uName);
		if (actor)
		{
			return CppObjectToScriptObj( *actor );
		}
		return NULL;
	}

	static MonoObject* ICall_ActorManager_GetMainCameraActor()
	{
		Actor* actor = GraphicsFeature::Instance()->GetDefaultCameraActor();
		if (actor)
		{
			return CppObjectToScriptObj( *actor );
		}
		return NULL;
	}

}

#include "autogen/scriptbind_ActorManager_register.h"
