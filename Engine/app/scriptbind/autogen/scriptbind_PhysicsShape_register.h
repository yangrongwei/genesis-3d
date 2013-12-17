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
	static void ICall_PhysicsShape_SetDensity( MonoObject* pMonoObj, Math::scalar density );

	static Math::scalar ICall_PhysicsShape_GetDensity( MonoObject* pMonoObj );

    static void ICall_PhysicsShape_SetCenterPos(MonoObject* self, Math::float3& pos );

    static void ICall_PhysicsShape_GetCenterPos(MonoObject* self, Math::float3& pos );

	static void ICall_PhysicsShape_SetRotation( MonoObject* pMonoObj, Math::quaternion& rotation );

	static void ICall_PhysicsShape_GetRotation( MonoObject* pMonoObj, Math::quaternion& rotation );

    static void ICall_PhysicsShape_SetMaterialID(MonoObject* self, MonoString* matID );

    static MonoString* ICall_PhysicsShape_GetMaterialID(MonoObject* self);

	static void ICall_PhysicsShape_SetUserData( MonoObject* pMonoObj, void* obj);

	static void* ICall_PhysicsShape_GetUserData( MonoObject* pMonoObj );

	static void ICall_PhysicsShape_SetGroup( MonoObject* pMonoObj, int group);

	static int ICall_PhysicsShape_GetGroup( MonoObject* pMonoObj );

//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_PhysicsShape( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			 { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_SetDensity",                       (void*)&ICall_PhysicsShape_SetDensity},
			 { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_GetDensity",                       (void*)&ICall_PhysicsShape_GetDensity}, 
			 { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_SetCenterPos",                       (void*)&ICall_PhysicsShape_SetCenterPos},
             { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_GetCenterPos",                       (void*)&ICall_PhysicsShape_GetCenterPos},
			 { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_SetRotation",                       (void*)&ICall_PhysicsShape_SetRotation},
             { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_GetRotation",                       (void*)&ICall_PhysicsShape_GetRotation},
             { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_SetMaterialID",                      (void*)&ICall_PhysicsShape_SetMaterialID},
             { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_GetMaterialID",                      (void*)&ICall_PhysicsShape_GetMaterialID},
			 { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_SetUserData",						(void*)&ICall_PhysicsShape_SetUserData},
			 { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_GetUserData",						(void*)&ICall_PhysicsShape_GetUserData},
			 { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_SetGroup",							(void*)&ICall_PhysicsShape_SetGroup},
			 { "ScriptRuntime.PhysicsShape::ICall_PhysicsShape_GetGroup",							(void*)&ICall_PhysicsShape_GetGroup},
        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
