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
#ifndef __SOUND_COMMIT__
#include "stdneb.h"
#include "scriptfeature/inc/script_utility.h"
#include "soundfeature/components/SoundReverbFilterComponent.h"

namespace App
{
	void ICallReg_ScriptRuntime_SoundReverbFilterComponent(void);

	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_Bind( MonoObject* pMonoObj )
	{
		SoundReverbFilterComponent* preverb = SoundReverbFilterComponent::Create();
		n_assert( NULL!=preverb );
		
		BindCppObjWithMonoObj<SoundReverbFilterComponent>( preverb, pMonoObj );
	}

	//------------------------------------------------------------------------
	static int ICall_SoundReverbFilterComponent_GetReverbPreset(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbPreset();
	}

	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetReverbPreset(MonoObject* pMonoObj, int preset)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		self->SetReverbPreset(preset);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_CopyValueFromPreset(MonoObject* pMonoObj, int preset)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		self->CopyValueFromPreset(preset);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_Attach(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		self->Attach();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_Detach(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		self->Detach();
	}

	static float ICall_SoundReverbFilterComponent_GetDensity(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::Density);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetDensity(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::Density, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetDiffusion(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::Diffusion);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetDiffusion(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::Diffusion, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetGain(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::Gain);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetGain(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::Gain, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetGainHF(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::GainHF);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetGainHF(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::GainHF, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetDecayTime(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::DecayTime);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetDecayTime(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::DecayTime, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetDecayHFRatio(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::DecayHFRatio);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetDecayHFRatio(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::DecayHFRatio, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetDecayLFRatio(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::DecayLFRatio);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetDecayLFRatio(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::DecayLFRatio, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetReflectionsGain(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::ReflectionsGain);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetReflectionsGain(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::ReflectionsGain, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetReflectionsDelay(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::ReflectionsDelay);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetReflectionsDelay(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::ReflectionsDelay, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetReverbGain(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::ReverbGain);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetReverbGain(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::ReverbGain, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetReverbDelay(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::ReverbDelay);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetReverbDelay(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::ReverbDelay, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetEchoTime(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::EchoTime);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetEchoTime(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::EchoTime, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetEchoDepth(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::EchoDepth);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetEchoDepth(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::EchoDepth, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetModulationTime(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::ModulationTime);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetModulationTime(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::ModulationTime, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetModulationDepth(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::ModulationDepth);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetModulationDepth(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::ModulationDepth, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetAirGainHF(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::AirGainHF);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetAirGainHF(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::AirGainHF, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetHFReference(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::HFReference);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetHFReference(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::HFReference, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetLFReference(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::LFReference);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetLFReference(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::LFReference, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundReverbFilterComponent_GetRoomRolloff(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->GetReverbParam(SoundReverbFilterComponent::RoomRolloff);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetRoomRolloff(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		return self->SetReverbParam(SoundReverbFilterComponent::RoomRolloff, pvalue);
	}
	//------------------------------------------------------------------------
	static mono_bool ICall_SoundReverbFilterComponent_GetDecayHFLimit(
														MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		float isDecayHFLimit = self->GetReverbParam(
									SoundReverbFilterComponent::DecayHFLimit);
		if ( 1 == isDecayHFLimit )
		{
			return c_iMonoBool_True;
		}
		else
		{
			return c_iMonoBool_False;
		}
	}
	//------------------------------------------------------------------------
	static void ICall_SoundReverbFilterComponent_SetDecayHFLimit(
								MonoObject* pMonoObj, mono_bool isDecayHFLimit)
	{
		ScriptObjWrapper<SoundReverbFilterComponent> self( pMonoObj );
		if ( c_iMonoBool_True == isDecayHFLimit )
		{
			self->SetReverbParam(SoundReverbFilterComponent::DecayHFLimit, 1);
		}
		else
		{
			self->SetReverbParam(SoundReverbFilterComponent::DecayHFLimit, 0);
		}
		
	}
	//------------------------------------------------------------------------
}


#include "autogen/scriptbind_SoundReverbFilterComponent_register.h"
#endif