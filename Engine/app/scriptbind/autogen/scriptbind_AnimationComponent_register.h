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
    static void ICall_AnimationComponent_SetAnimationID( MonoObject* self, MonoString* id);

    static void ICall_AnimationComponent_CrossFading( MonoObject* self, MonoString* name, int type, float time);

    static void ICall_AnimationComponent_PlayAnimation( MonoObject* self, MonoString* name);

	static void ICall_AnimationComponent_StopAnimation( MonoObject* self, MonoString* name);

	static void ICall_AnimationComponent_BlendingAnimation( MonoObject* self, MonoString* name, float weight, float time);

    static void ICall_AnimationComponent_SetAnimationSpeed( MonoObject* self, MonoString* name, float speed);

    static void ICall_AnimationComponent_SetAnimationWrapMode( MonoObject* self, MonoString* name, int wrapMode);

	static void ICall_AnimationComponent_SetAnimationLayer( MonoObject* self, MonoString* name, int layer);

	static void ICall_AnimationComponent_AddAffectedNodes( MonoObject* self, MonoString* animName, MonoString* nodeName, mono_bool recursive);

	static void ICall_AnimationComponent_RemoveAffectedNodes( MonoObject* self, MonoString* animName, MonoString* nodeName);

	static void ICall_AnimationComponent_RemoveAffectedNodes_2( MonoObject* self, MonoString* animName, MonoString* nodeName, mono_bool recursive);

	static void ICall_AnimationComponent_AddAttachedActor( MonoObject* pMonoObj, MonoObject* pActor, MonoString* pMonoString);

	static void ICall_AnimationComponent_RemoveAttachedActor( MonoObject* pMonoObj, MonoObject* pActor);

    static mono_bool ICall_AnimationComponent_IsAnimationPlaying( MonoObject* self, MonoString* name);

	static float ICall_AnimationComponent_GetCurAnimCurrentFrame(MonoObject* self);

	static float ICall_AnimationComponent_GetCurrentFrame(MonoObject* self, MonoString* name);

	static int ICall_AnimationComponent_GetAnimFrameCount(MonoObject* self, MonoString* name);

	static int ICall_AnimationComponent_GetCurrentAnimFrameCount(MonoObject* self);

	static MonoString* ICall_AnimationComponent_GetCurrentAnimation(MonoObject* self);

	static mono_bool ICall_AnimationComponent_GetNodeTransform(MonoObject* self, MonoString* name, Math::matrix44& matrix);

	static int ICall_AnimationComponent_GetWrapMode(MonoObject* self, MonoString* name);

//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_AnimationComponent( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_SetAnimationID",         (void*)&ICall_AnimationComponent_SetAnimationID},
             { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_CrossFading",            (void*)&ICall_AnimationComponent_CrossFading},
             { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_PlayAnimation",          (void*)&ICall_AnimationComponent_PlayAnimation},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_StopAnimation",          (void*)&ICall_AnimationComponent_StopAnimation},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_BlendingAnimation",		(void*)&ICall_AnimationComponent_BlendingAnimation},
             { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_SetAnimationSpeed",      (void*)&ICall_AnimationComponent_SetAnimationSpeed},
             { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_SetAnimationWrapMode",   (void*)&ICall_AnimationComponent_SetAnimationWrapMode},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_SetAnimationLayer",		(void*)&ICall_AnimationComponent_SetAnimationLayer},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_AddAffectedNodes",		(void*)&ICall_AnimationComponent_AddAffectedNodes},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_RemoveAffectedNodes",	(void*)&ICall_AnimationComponent_RemoveAffectedNodes},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_RemoveAffectedNodes_2",	(void*)&ICall_AnimationComponent_RemoveAffectedNodes_2},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_AddAttachedActor",		(void*)&ICall_AnimationComponent_AddAttachedActor},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_RemoveAttachedActor",	(void*)&ICall_AnimationComponent_RemoveAttachedActor},
             { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_IsAnimationPlaying",     (void*)&ICall_AnimationComponent_IsAnimationPlaying},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_GetCurAnimCurrentFrame",	(void*)&ICall_AnimationComponent_GetCurAnimCurrentFrame},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_GetCurrentFrame",		(void*)&ICall_AnimationComponent_GetCurrentFrame},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_GetAnimFrameCount",		(void*)&ICall_AnimationComponent_GetAnimFrameCount},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_GetCurrentAnimFrameCount",(void*)&ICall_AnimationComponent_GetCurrentAnimFrameCount},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_GetCurrentAnimation",	(void*)&ICall_AnimationComponent_GetCurrentAnimation},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_GetNodeTransform",		(void*)&ICall_AnimationComponent_GetNodeTransform},
			 { "ScriptRuntime.AnimationComponent::ICall_AnimationComponent_GetWrapMode",			(void*)&ICall_AnimationComponent_GetWrapMode},

        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
