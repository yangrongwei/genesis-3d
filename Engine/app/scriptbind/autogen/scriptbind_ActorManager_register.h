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

namespace App
{ 
    static MonoObject* ICall_ActorManager_CreateFromTemplate(MonoString* name, mono_bool bCopy);

    static MonoObject* ICall_ActorManager_GetActiveActor(IndexT index);

    static SizeT ICall_ActorManager_GetActiveActorCount( void );

    static MonoObject* ICall_ActorManager_FindActiveActorByFastID(App::Actor::FastId fastID);

	static MonoArray* ICall_ActorManager_FindActiveActorsInGroup(App::TagID tagID);

	static MonoObject* ICall_ActorManager_FindActiveActorInGroup(App::TagID tagID);

    static MonoObject* ICall_ActorManager_FindActiveActorByGuid( MonoArray* guid);

    static MonoObject* ICall_ActorManager_FindActiveActorByName(MonoString* name);

    static MonoObject* ICall_ActorManager_GetMainCameraActor( void );

//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_ActorManager( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.ActorManager::ICall_ActorManager_CreateFromTemplate",                 (void*)&ICall_ActorManager_CreateFromTemplate},
             { "ScriptRuntime.ActorManager::ICall_ActorManager_GetActiveActor",                     (void*)&ICall_ActorManager_GetActiveActor},
             { "ScriptRuntime.ActorManager::ICall_ActorManager_GetActiveActorCount",                (void*)&ICall_ActorManager_GetActiveActorCount},
             { "ScriptRuntime.ActorManager::ICall_ActorManager_FindActiveActorByFastID",            (void*)&ICall_ActorManager_FindActiveActorByFastID},
			 { "ScriptRuntime.ActorManager::ICall_ActorManager_FindActiveActorsInGroup",             (void*)&ICall_ActorManager_FindActiveActorsInGroup},
			 { "ScriptRuntime.ActorManager::ICall_ActorManager_FindActiveActorInGroup",             (void*)&ICall_ActorManager_FindActiveActorInGroup},
             { "ScriptRuntime.ActorManager::ICall_ActorManager_FindActiveActorByGuid",              (void*)&ICall_ActorManager_FindActiveActorByGuid},
             { "ScriptRuntime.ActorManager::ICall_ActorManager_FindActiveActorByName",              (void*)&ICall_ActorManager_FindActiveActorByName},
             { "ScriptRuntime.ActorManager::ICall_ActorManager_GetMainCameraActor",                 (void*)&ICall_ActorManager_GetMainCameraActor},
        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
