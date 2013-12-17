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
#include "graphicfeature/components/spriterendercomponent.h"
#include "addons/resource/meshres.h"

namespace App
{
	void ICallReg_ScriptRuntime_SpriteRenderComponent( void );

	static void ICall_SpriteRenderComponent_Bind( MonoObject* pMonoObj )
	{
		SpriteRenderComponent* preverb = SpriteRenderComponent::Create();
		n_assert( NULL!=preverb );
		BindCppObjWithMonoObj<SpriteRenderComponent>( preverb, pMonoObj );
	}

	static void ICall_SpriteRenderComponent_Setup( MonoObject* pMonoObj, MonoString* pMonoStr )
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		Util::String packId = Utility_MonoStringToCppString( pMonoStr );
		self->Setup( packId );
	}

	static MonoString* ICall_SpriteRenderComponent_GetPackageID( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		return Utility_CppStringToMonoStringSafe(self->GetPackageID().Value());
	}

	static void ICall_SpriteRenderComponent_SetBlock( MonoObject* pMonoObj, MonoString* pMonoStr )
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		Util::String packId = Utility_MonoStringToCppString( pMonoStr );
		self->SetBlock( packId );
	}

	static void ICall_SpriteRenderComponent_SetAnimation( MonoObject* pMonoObj, MonoString* pMonoStr, int loops, mono_bool play, float speed)
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		Util::String packId = Utility_MonoStringToCppString( pMonoStr );
		self->SetAnimation(packId, loops, c_iMonoBool_True == play, speed);
	}
	static void ICall_SpriteRenderComponent_RemoveBlock( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		self->RemoveBlock();
	}

	static void ICall_SpriteRenderComponent_RemoveAnimation( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		self->RemoveAnimation();
	}

	static void ICall_SpriteRenderComponent_SetAnimationSpeed( MonoObject* pMonoObj, float speed)
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		self->SetAnimationSpeed( speed );
	}

	static void ICall_SpriteRenderComponent_Play( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		self->Play();
	}

	static void ICall_SpriteRenderComponent_Replay( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		self->Replay();
	}

	static void ICall_SpriteRenderComponent_Pause( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		self->Pause();
	}

	static void ICall_SpriteRenderComponent_Stop( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		self->Stop();
	}

	static void ICall_SpriteRenderComponent_SetPlayOnWake( MonoObject* pMonoObj, mono_bool value)
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		self->SetPlayOnWake( c_iMonoBool_True == value );
	}

	static MonoString* ICall_SpriteRenderComponent_GetBlockName( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		return Utility_CppStringToMonoStringSafe(self->GetBlockName().AsCharPtr());
	}

	static MonoString* ICall_SpriteRenderComponent_GetAnimationName( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		return Utility_CppStringToMonoStringSafe(self->GetAnimationName().AsCharPtr());
	}

	static int ICall_SpriteRenderComponent_GetAnimationLoops( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		return self->GetAnimationLoops();
	}

	static float ICall_SpriteRenderComponent_GetAnimationSpeed( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		return self->GetAnimationSpeed();
	}

	static mono_bool ICall_SpriteRenderComponent_IsAnimationPlaying( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		return Utility_MonoBool(self->IsAnimationPlaying());
	}

	static mono_bool ICall_SpriteRenderComponent_GetPlayOnWake( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<SpriteRenderComponent> self( pMonoObj );
		return Utility_MonoBool(self->GetPlayOnWake());
	}

	void ICallReg_ScriptRuntime_SpriteRenderComponent( void )
	{
 		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_Bind",				(void*)&ICall_SpriteRenderComponent_Bind},
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_Setup",				(void*)&ICall_SpriteRenderComponent_Setup},
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_GetPackageID",		(void*)&ICall_SpriteRenderComponent_GetPackageID },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_GetPackageID",		(void*)&ICall_SpriteRenderComponent_GetPackageID },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_SetBlock",			(void*)&ICall_SpriteRenderComponent_SetBlock },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_SetAnimation",		(void*)&ICall_SpriteRenderComponent_SetAnimation },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_RemoveBlock",		(void*)&ICall_SpriteRenderComponent_RemoveBlock },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_RemoveAnimation",	(void*)&ICall_SpriteRenderComponent_RemoveAnimation },

			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_SetAnimationSpeed", (void*)&ICall_SpriteRenderComponent_SetAnimationSpeed },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_Play",				(void*)&ICall_SpriteRenderComponent_Play },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_Pause",				(void*)&ICall_SpriteRenderComponent_Pause },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_Stop",				(void*)&ICall_SpriteRenderComponent_Stop },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_Replay",			(void*)&ICall_SpriteRenderComponent_Replay },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_SetPlayOnWake",		(void*)&ICall_SpriteRenderComponent_SetPlayOnWake },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_GetBlockName",		(void*)&ICall_SpriteRenderComponent_GetBlockName },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_GetAnimationName",	(void*)&ICall_SpriteRenderComponent_GetAnimationName },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_GetAnimationLoops", (void*)&ICall_SpriteRenderComponent_GetAnimationLoops },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_GetAnimationSpeed", (void*)&ICall_SpriteRenderComponent_GetAnimationSpeed },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_IsAnimationPlaying",(void*)&ICall_SpriteRenderComponent_IsAnimationPlaying },
			{ "ScriptRuntime.SpriteRenderComponent::ICall_SpriteRenderComponent_GetPlayOnWake",		(void*)&ICall_SpriteRenderComponent_GetPlayOnWake },

 		};
 
 		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
 		for( int ii=0; ii<size; ii++ )
 		{
 			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
									s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
 		}
	}

}