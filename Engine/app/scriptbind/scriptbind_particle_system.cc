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
#include "addons/particles/particleserver.h"
#include "addons/particles/particlesystem.h"
#include "foundation/math/float3.h"

namespace App
{

	void ICallReg_ScriptRuntime_ParticleSystem( void );

	static void ICall_ParticleSystem_Bind( MonoObject* pMonoObj )
	{
		Particles::ParticleSystem* pPs =  Particles::ParticleSystem::Create();
		n_assert( NULL!=pPs );
		BindCppObjWithMonoObj<Particles::ParticleSystem>( pPs, pMonoObj );
	}
	
	static void ICall_ParticleSystem_Release( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Particles::ParticleSystem> self( pMonoObj );
		Particles::ParticleSystem* ptr = self.GetCppObjPtr();

		ReleaseCppObjWithMonoObj<Particles::ParticleSystem>( ptr, pMonoObj );
	}

	static void ICall_ParticleSystem_SetName( MonoObject* pMonoObj, MonoString* pMonoString )
	{
		ScriptObjWrapper<Particles::ParticleSystem> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );

		self->SetName(name);
	}
	static MonoString* ICall_ParticleSystem_GetName( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<Particles::ParticleSystem> self( pMonoObj );
		Util::String sName = self->GetName();
		return Utility_NewMonoString( sName );
	}

	//临时hack，设置粒子发射最大值现在在Tech层，以后考虑干掉Tech。
	static void ICall_ParticleSystem_SetQuato( MonoObject* pMonoObj,int quato )
	{
		ScriptObjWrapper<Particles::ParticleSystem> self( pMonoObj );

		self->SetParticleQuota(quato);
	}
	static int ICall_ParticleSystem_GetQuato( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<Particles::ParticleSystem> self( pMonoObj );
		return self->GetParticleQuota();
	}

	static void ICall_ParticleSystem_SetPlayRateScale( MonoObject* pMonoObj, float rateScale )
	{
		ScriptObjWrapper<Particles::ParticleSystem> self( pMonoObj );

		self->SetPlayRateScale(rateScale);
	}

	static float ICall_ParticleSystem_GetPlayRateScale( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<Particles::ParticleSystem> self( pMonoObj );
		
		return self->GetPlayRateScale();
	}

	static void ICall_ParticleSystem_Play( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Particles::ParticleSystem> self( pMonoObj );
		self->Play();
	}

	static void ICall_ParticleSystem_Pause( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Particles::ParticleSystem> self( pMonoObj );
		self->Pause();
	}

	static void ICall_ParticleSystem_Stop( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Particles::ParticleSystem> self( pMonoObj );
		self->Stop();
	}

	static mono_bool ICall_ParticleSystem_IsPlaying( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Particles::ParticleSystem> self(pMonoObj);
		return Utility_MonoBool(self->IsPlaying());
	}

	static mono_bool ICall_ParticleSystem_IsPaused( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Particles::ParticleSystem> self(pMonoObj);
		return Utility_MonoBool(self->IsPaused());
	}

	static mono_bool ICall_ParticleSystem_IsStop( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Particles::ParticleSystem> self(pMonoObj);
		return Utility_MonoBool(self->IsStop());
	}

	void ICallReg_ScriptRuntime_ParticleSystem( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_Bind",						 (void*)&ICall_ParticleSystem_Bind },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_Release",						 (void*)&ICall_ParticleSystem_Release },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_SetName",						 (void*)&ICall_ParticleSystem_SetName },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_GetName",						 (void*)&ICall_ParticleSystem_GetName },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_Play",                         (void*)&ICall_ParticleSystem_Play },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_Pause",                        (void*)&ICall_ParticleSystem_Pause },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_Stop",                         (void*)&ICall_ParticleSystem_Stop },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_IsPlaying",                    (void*)&ICall_ParticleSystem_IsPlaying },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_IsPaused",                     (void*)&ICall_ParticleSystem_IsPaused },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_IsStop",                       (void*)&ICall_ParticleSystem_IsStop },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_SetPlayRateScale",			 (void*)&ICall_ParticleSystem_SetPlayRateScale },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_GetPlayRateScale",			 (void*)&ICall_ParticleSystem_GetPlayRateScale },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_SetQuato",					 (void*)&ICall_ParticleSystem_SetQuato },
			{ "ScriptRuntime.ParticleSystem::ICall_ParticleSystem_GetQuato",					 (void*)&ICall_ParticleSystem_GetQuato },
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}

}