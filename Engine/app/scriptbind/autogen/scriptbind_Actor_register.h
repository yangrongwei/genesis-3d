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
    static void ICall_Actor_Bind(MonoObject* self);

    static void ICall_Actor_Release(MonoObject* self);

    static void ICall_Actor_SetName(MonoObject* self, MonoString* sName);

    static MonoString* ICall_Actor_GetName(MonoObject* self);

    static MonoString* ICall_Actor_GetTemplateName(MonoObject* self);

    static void ICall_Actor_SetLayerID(MonoObject* self, uint32 layerID);

    static uint32 ICall_Actor_GetLayerID(MonoObject* self);

    static mono_bool ICall_Actor_IsLinkTemplate(MonoObject* self);

    static void ICall_Actor_SetLinkTemplate(MonoObject* self, mono_bool bLink);

    static void ICall_Actor_SetTagID(MonoObject* self, uint32 tagID);

    static uint32 ICall_Actor_GetTagID(MonoObject* self);

    static MonoArray* ICall_Actor_GetGuid(MonoObject* self);

    static uint32 ICall_Actor_GetFastId(MonoObject* self);

    static mono_bool ICall_Actor_IsActive(MonoObject* self);

	static mono_bool ICall_Actor_GetActiveControl( MonoObject* pMonoObj );

    static void ICall_Actor_Active(MonoObject* self, mono_bool bIncludeChild);

    static void ICall_Actor_Deactive(MonoObject* self, mono_bool bActive);

    static MonoObject* ICall_Actor_GetParent(MonoObject* self);

    static void ICall_Actor_SetParent(MonoObject* self, MonoObject* parent);

    static SizeT ICall_Actor_GetChildCount(MonoObject* self);

    static MonoObject* ICall_Actor_GetChild(MonoObject* self, IndexT index);

    static MonoObject* ICall_Actor_FindChild(MonoObject* self, uint32 fastId);

    static IndexT ICall_Actor_FindChildIndex(MonoObject* self, uint32 fastId);

    static void ICall_Actor_AddChild(MonoObject* self, MonoObject* child);

    static void ICall_Actor_RemoveChild(MonoObject* self, IndexT index);

    static void ICall_Actor_SetLocalPos(MonoObject* self, Math::float3& pos);

    static void ICall_Actor_SetLocalRotation(MonoObject* self, Math::quaternion& rot);

    static void ICall_Actor_SetLocalScale(MonoObject* self, Math::float3& scale);

    static void ICall_Actor_GetLocalPos(MonoObject* self, Math::float3& outPos);

    static void ICall_Actor_GetLocalRotation(MonoObject* self, Math::quaternion& outRot);

    static void ICall_Actor_GetLocalScale(MonoObject* self, Math::float3& outScale);

    static void ICall_Actor_Roll(MonoObject* self, float angle);

    static void ICall_Actor_Pitch(MonoObject* self, float angle);

    static void ICall_Actor_Yaw(MonoObject* self, float angle);

    static void ICall_Actor_Rotate(MonoObject* self, float roll, float picth, float yaw);

    static void ICall_Actor_SetTransform(MonoObject* self, Math::matrix44& matrix);

    static void ICall_Actor_GetTransform(MonoObject* self, Math::matrix44& matrix);

    static void ICall_Actor_SetWorldTransform(MonoObject* self, Math::matrix44& matrix);

    static void ICall_Actor_GetWorldTransform(MonoObject* self, Math::matrix44& matrix);

    static void ICall_Actor_GetWorldRotation(MonoObject* self, Math::quaternion& rot);

    static void ICall_Actor_SetWorldRotation(MonoObject* self, Math::quaternion& rot);

    static void ICall_Actor_GetWorldPos(MonoObject* self, Math::float3& rot);

    static void ICall_Actor_SetWorldPos(MonoObject* self, Math::float3& rot);

    static void ICall_Actor_GetWorldScale(MonoObject* self, Math::float3& rot);

    static void ICall_Actor_SetWorldScale(MonoObject* self, Math::float3& rot);

    static void ICall_Actor_GetWorldBoundingBox(MonoObject* self, bbox_script& bb);

    static void ICall_Actor_GetWorldBoundingBoxWithChild(MonoObject* self, bbox_script& bb);

    static void ICall_Actor_GetLocalBoundingBox(MonoObject* self, bbox_script& bb);

    static void ICall_Actor_SetLocalBoundingBox(MonoObject* self, bbox_script& bb);

	static void ICall_Actor_RemoveComponent(MonoObject* pMonoObj, MonoObject* pPEC);

    static  MonoObject* ICall_Actor_AddComponentByName(MonoObject* self, MonoString* sName);

    static  MonoObject* ICall_Actor_GetComponentByName(MonoObject* self, MonoString* sName);

    static mono_bool ICall_Actor_IsAllResourcePrepared(MonoObject* self);

	static void ICall_Actor_SetPriority( MonoObject* pMonoObj ,int priority);

	static int ICall_Actor_GetPriority( MonoObject* pMonoObj );

	static int ICall_Actor_GetRefCount( MonoObject* pMonoObj );
//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_Actor( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.Actor::ICall_Actor_Bind",                                             (void*)&ICall_Actor_Bind},
             { "ScriptRuntime.Actor::ICall_Actor_Release",                                          (void*)&ICall_Actor_Release},
             { "ScriptRuntime.Actor::ICall_Actor_SetName",                                          (void*)&ICall_Actor_SetName},
             { "ScriptRuntime.Actor::ICall_Actor_GetName",                                          (void*)&ICall_Actor_GetName},
             { "ScriptRuntime.Actor::ICall_Actor_GetTemplateName",                                  (void*)&ICall_Actor_GetTemplateName},
             { "ScriptRuntime.Actor::ICall_Actor_SetLayerID",                                       (void*)&ICall_Actor_SetLayerID},
             { "ScriptRuntime.Actor::ICall_Actor_GetLayerID",                                       (void*)&ICall_Actor_GetLayerID},
             { "ScriptRuntime.Actor::ICall_Actor_IsLinkTemplate",                                   (void*)&ICall_Actor_IsLinkTemplate},
             { "ScriptRuntime.Actor::ICall_Actor_SetLinkTemplate",                                  (void*)&ICall_Actor_SetLinkTemplate},
             { "ScriptRuntime.Actor::ICall_Actor_SetTagID",                                         (void*)&ICall_Actor_SetTagID},
             { "ScriptRuntime.Actor::ICall_Actor_GetTagID",                                         (void*)&ICall_Actor_GetTagID},
             { "ScriptRuntime.Actor::ICall_Actor_GetGuid",                                          (void*)&ICall_Actor_GetGuid},
             { "ScriptRuntime.Actor::ICall_Actor_GetFastId",                                        (void*)&ICall_Actor_GetFastId},
             { "ScriptRuntime.Actor::ICall_Actor_IsActive",                                         (void*)&ICall_Actor_IsActive},
			 { "ScriptRuntime.Actor::ICall_Actor_GetActiveControl",									(void*)&ICall_Actor_GetActiveControl},
             { "ScriptRuntime.Actor::ICall_Actor_Active",                                           (void*)&ICall_Actor_Active},
             { "ScriptRuntime.Actor::ICall_Actor_Deactive",                                         (void*)&ICall_Actor_Deactive},
             { "ScriptRuntime.Actor::ICall_Actor_GetParent",                                        (void*)&ICall_Actor_GetParent},
             { "ScriptRuntime.Actor::ICall_Actor_SetParent",                                        (void*)&ICall_Actor_SetParent},
             { "ScriptRuntime.Actor::ICall_Actor_GetChildCount",                                    (void*)&ICall_Actor_GetChildCount},
             { "ScriptRuntime.Actor::ICall_Actor_GetChild",                                         (void*)&ICall_Actor_GetChild},
             { "ScriptRuntime.Actor::ICall_Actor_FindChild",                                        (void*)&ICall_Actor_FindChild},
             { "ScriptRuntime.Actor::ICall_Actor_FindChildIndex",                                   (void*)&ICall_Actor_FindChildIndex},
             { "ScriptRuntime.Actor::ICall_Actor_AddChild",                                         (void*)&ICall_Actor_AddChild},
             { "ScriptRuntime.Actor::ICall_Actor_RemoveChild",                                      (void*)&ICall_Actor_RemoveChild},
             { "ScriptRuntime.Actor::ICall_Actor_SetLocalPos",                                      (void*)&ICall_Actor_SetLocalPos},
             { "ScriptRuntime.Actor::ICall_Actor_SetLocalRotation",                                 (void*)&ICall_Actor_SetLocalRotation},
             { "ScriptRuntime.Actor::ICall_Actor_SetLocalScale",                                    (void*)&ICall_Actor_SetLocalScale},
             { "ScriptRuntime.Actor::ICall_Actor_GetLocalPos",                                      (void*)&ICall_Actor_GetLocalPos},
             { "ScriptRuntime.Actor::ICall_Actor_GetLocalRotation",                                 (void*)&ICall_Actor_GetLocalRotation},
             { "ScriptRuntime.Actor::ICall_Actor_GetLocalScale",                                    (void*)&ICall_Actor_GetLocalScale},
             { "ScriptRuntime.Actor::ICall_Actor_Roll",                                             (void*)&ICall_Actor_Roll},
             { "ScriptRuntime.Actor::ICall_Actor_Pitch",                                            (void*)&ICall_Actor_Pitch},
             { "ScriptRuntime.Actor::ICall_Actor_Yaw",                                              (void*)&ICall_Actor_Yaw},
             { "ScriptRuntime.Actor::ICall_Actor_Rotate",                                           (void*)&ICall_Actor_Rotate},
             { "ScriptRuntime.Actor::ICall_Actor_SetTransform",                                     (void*)&ICall_Actor_SetTransform},
             { "ScriptRuntime.Actor::ICall_Actor_GetTransform",                                     (void*)&ICall_Actor_GetTransform},
             { "ScriptRuntime.Actor::ICall_Actor_SetWorldTransform",                                (void*)&ICall_Actor_SetWorldTransform},
             { "ScriptRuntime.Actor::ICall_Actor_GetWorldTransform",                                (void*)&ICall_Actor_GetWorldTransform},
             { "ScriptRuntime.Actor::ICall_Actor_GetWorldRotation",                                 (void*)&ICall_Actor_GetWorldRotation},
             { "ScriptRuntime.Actor::ICall_Actor_SetWorldRotation",                                 (void*)&ICall_Actor_SetWorldRotation},
             { "ScriptRuntime.Actor::ICall_Actor_GetWorldPos",                                      (void*)&ICall_Actor_GetWorldPos},
             { "ScriptRuntime.Actor::ICall_Actor_SetWorldPos",                                      (void*)&ICall_Actor_SetWorldPos},
             { "ScriptRuntime.Actor::ICall_Actor_GetWorldScale",                                    (void*)&ICall_Actor_GetWorldScale},
             { "ScriptRuntime.Actor::ICall_Actor_SetWorldScale",                                    (void*)&ICall_Actor_SetWorldScale},
             { "ScriptRuntime.Actor::ICall_Actor_GetWorldBoundingBox",                              (void*)&ICall_Actor_GetWorldBoundingBox},
             { "ScriptRuntime.Actor::ICall_Actor_GetWorldBoundingBoxWithChild",                     (void*)&ICall_Actor_GetWorldBoundingBoxWithChild},
             { "ScriptRuntime.Actor::ICall_Actor_GetLocalBoundingBox",                              (void*)&ICall_Actor_GetLocalBoundingBox},
             { "ScriptRuntime.Actor::ICall_Actor_SetLocalBoundingBox",                              (void*)&ICall_Actor_SetLocalBoundingBox},
			 { "ScriptRuntime.Actor::ICall_Actor_RemoveComponent",									(void*)&ICall_Actor_RemoveComponent},
             { "ScriptRuntime.Actor::ICall_Actor_AddComponentByName",                               (void*)&ICall_Actor_AddComponentByName},
             { "ScriptRuntime.Actor::ICall_Actor_GetComponentByName",                               (void*)&ICall_Actor_GetComponentByName},
             { "ScriptRuntime.Actor::ICall_Actor_IsAllResourcePrepared",                            (void*)&ICall_Actor_IsAllResourcePrepared},
			 { "ScriptRuntime.Actor::ICall_Actor_SetPriority",										(void*)&ICall_Actor_SetPriority},
			 { "ScriptRuntime.Actor::ICall_Actor_GetPriority",										(void*)&ICall_Actor_GetPriority}, 
			 { "ScriptRuntime.Actor::ICall_Actor_GetRefCount",										(void*)&ICall_Actor_GetRefCount},  
        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
