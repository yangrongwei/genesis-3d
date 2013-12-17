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
    static void ICall_SoundReverbFilterComponent_Bind( MonoObject* self);

	static void ICall_SoundReverbFilterComponent_CopyValueFromPreset( MonoObject* self, int preset);

	static int ICall_SoundReverbFilterComponent_GetReverbPreset( MonoObject* self);

	static void ICall_SoundReverbFilterComponent_SetReverbPreset( MonoObject* self, int preset);

	static void ICall_SoundReverbFilterComponent_Attach( MonoObject* self);
	
	static void ICall_SoundReverbFilterComponent_Detach( MonoObject* self);

	static float ICall_SoundReverbFilterComponent_GetDensity(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetDensity(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetDiffusion(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetDiffusion(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetGain(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetGain(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetGainHF(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetGainHF(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetDecayTime(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetDecayTime(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetDecayHFRatio(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetDecayHFRatio(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetDecayLFRatio(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetDecayLFRatio(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetReflectionsGain(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetReflectionsGain(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetReverbGain(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetReverbGain(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetReverbDelay(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetReverbDelay(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetEchoTime(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetEchoTime(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetEchoDepth(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetEchoDepth(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetModulationTime(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetModulationTime(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetModulationDepth(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetModulationDepth(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetAirGainHF(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetAirGainHF(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetHFReference(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetHFReference(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetLFReference(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetLFReference(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundReverbFilterComponent_GetRoomRolloff(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetRoomRolloff(MonoObject* pMonoObj, float pvalue);

	static mono_bool ICall_SoundReverbFilterComponent_GetDecayHFLimit(MonoObject* pMonoObj);

	static void ICall_SoundReverbFilterComponent_SetDecayHFLimit(MonoObject* pMonoObj, mono_bool isDecayHFLimit);
//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_SoundReverbFilterComponent( void )
    {
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_Bind", (void*)&ICall_SoundReverbFilterComponent_Bind },
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetReverbPreset", (void*)&ICall_SoundReverbFilterComponent_GetReverbPreset },
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetReverbPreset",(void*) &ICall_SoundReverbFilterComponent_SetReverbPreset },
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_CopyValueFromPreset", (void*)&ICall_SoundReverbFilterComponent_CopyValueFromPreset },
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_Attach", (void*)&ICall_SoundReverbFilterComponent_Attach },
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_Detach", (void*)&ICall_SoundReverbFilterComponent_Detach },
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetDensity",(void*)&ICall_SoundReverbFilterComponent_GetDensity},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetDensity",(void*)&ICall_SoundReverbFilterComponent_SetDensity},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetDiffusion",(void*)&ICall_SoundReverbFilterComponent_GetDiffusion},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetDiffusion",(void*)&ICall_SoundReverbFilterComponent_SetDiffusion},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetGain",(void*)&ICall_SoundReverbFilterComponent_GetGain},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetGain",(void*)&ICall_SoundReverbFilterComponent_SetGain},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetGainHF",(void*)&ICall_SoundReverbFilterComponent_GetGainHF},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetGainHF",(void*)&ICall_SoundReverbFilterComponent_SetGainHF},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetDecayTime",(void*)&ICall_SoundReverbFilterComponent_GetDecayTime},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetDecayTime",(void*)&ICall_SoundReverbFilterComponent_SetDecayTime},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetDecayHFRatio",(void*)&ICall_SoundReverbFilterComponent_GetDecayHFRatio},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetDecayHFRatio",(void*)&ICall_SoundReverbFilterComponent_SetDecayHFRatio},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetDecayLFRatio",(void*)&ICall_SoundReverbFilterComponent_GetDecayLFRatio},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetDecayLFRatio",(void*)&ICall_SoundReverbFilterComponent_SetDecayLFRatio},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetReflectionsGain",(void*)&ICall_SoundReverbFilterComponent_GetReflectionsGain},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetReflectionsGain",(void*)&ICall_SoundReverbFilterComponent_SetReflectionsGain},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetReflectionsDelay",(void*)&ICall_SoundReverbFilterComponent_GetReflectionsDelay},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetReflectionsDelay",(void*)&ICall_SoundReverbFilterComponent_SetReflectionsDelay},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetReverbGain",(void*)&ICall_SoundReverbFilterComponent_GetReverbGain},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetReverbGain",(void*)&ICall_SoundReverbFilterComponent_SetReverbGain},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetReverbDelay",(void*)&ICall_SoundReverbFilterComponent_GetReverbDelay},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetReverbDelay",(void*)&ICall_SoundReverbFilterComponent_SetReverbDelay},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetEchoTime",(void*)&ICall_SoundReverbFilterComponent_GetEchoTime},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetEchoTime",(void*)&ICall_SoundReverbFilterComponent_SetEchoTime},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetEchoDepth",(void*)&ICall_SoundReverbFilterComponent_GetEchoDepth},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetEchoDepth",(void*)&ICall_SoundReverbFilterComponent_SetEchoDepth},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetModulationTime",(void*)&ICall_SoundReverbFilterComponent_GetModulationTime},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetModulationTime",(void*)&ICall_SoundReverbFilterComponent_SetModulationTime},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetModulationDepth",(void*)&ICall_SoundReverbFilterComponent_GetModulationDepth},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetModulationDepth",(void*)&ICall_SoundReverbFilterComponent_SetModulationDepth},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetAirGainHF",(void*)&ICall_SoundReverbFilterComponent_GetAirGainHF},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetAirGainHF",(void*)&ICall_SoundReverbFilterComponent_SetAirGainHF},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetHFReference",(void*)&ICall_SoundReverbFilterComponent_GetHFReference},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetHFReference",(void*)&ICall_SoundReverbFilterComponent_SetHFReference},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetLFReference",(void*)&ICall_SoundReverbFilterComponent_GetLFReference},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetLFReference",(void*)&ICall_SoundReverbFilterComponent_SetLFReference},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetRoomRolloff",(void*)&ICall_SoundReverbFilterComponent_GetRoomRolloff},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetRoomRolloff",(void*)&ICall_SoundReverbFilterComponent_SetRoomRolloff},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_GetDecayHFLimit",(void*)&ICall_SoundReverbFilterComponent_GetDecayHFLimit},
			{ "ScriptRuntime.SoundReverbFilterComponent::ICall_SoundReverbFilterComponent_SetDecayHFLimit",(void*)&ICall_SoundReverbFilterComponent_SetDecayHFLimit},
		};

        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
