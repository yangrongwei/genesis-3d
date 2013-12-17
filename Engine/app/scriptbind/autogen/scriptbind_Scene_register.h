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
    static void ICall_Scene_Release( MonoObject* self);

    static int ICall_Scene_GetActorCount( MonoObject* self);

    static MonoObject* ICall_Scene_GetActor( MonoObject* self, int index);

    static MonoObject* ICall_Scene_FindActorByFastID( MonoObject* self, App::Actor::FastId fastID);

	static MonoObject* ICall_Scene_FindActorByTag( MonoObject* self, uint fastID);

	static MonoArray* ICall_Scene_FindActorsByTag( MonoObject* pMonoObj, uint index );

    static mono_bool ICall_Scene_AddActor( MonoObject* self, MonoObject* pActor);

    static mono_bool ICall_Scene_RemoveActor( MonoObject* self, MonoObject* pActor);

    static MonoObject* ICall_Scene_FindActorByGuid( MonoObject* self,  MonoArray* guid);

    static MonoObject* ICall_Scene_FindActorByName( MonoObject* self, MonoString* name);

//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_Scene( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.Scene::ICall_Scene_Release",                                          (void*)&ICall_Scene_Release},
             { "ScriptRuntime.Scene::ICall_Scene_GetActorCount",                                    (void*)&ICall_Scene_GetActorCount},
             { "ScriptRuntime.Scene::ICall_Scene_GetActor",                                         (void*)&ICall_Scene_GetActor},
             { "ScriptRuntime.Scene::ICall_Scene_FindActorByFastID",                                (void*)&ICall_Scene_FindActorByFastID},
             { "ScriptRuntime.Scene::ICall_Scene_AddActor",                                         (void*)&ICall_Scene_AddActor},
             { "ScriptRuntime.Scene::ICall_Scene_RemoveActor",                                      (void*)&ICall_Scene_RemoveActor},
             { "ScriptRuntime.Scene::ICall_Scene_FindActorByGuid",                                  (void*)&ICall_Scene_FindActorByGuid},
			 { "ScriptRuntime.Scene::ICall_Scene_FindActorByTag",                                  (void*)&ICall_Scene_FindActorByTag},	 
			 { "ScriptRuntime.Scene::ICall_Scene_FindActorsByTag",                                  (void*)&ICall_Scene_FindActorsByTag},	 
             { "ScriptRuntime.Scene::ICall_Scene_FindActorByName",                                 (void*) &ICall_Scene_FindActorByName},
        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
