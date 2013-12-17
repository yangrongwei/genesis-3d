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
    static void ICall_SoundEchoFilterComponent_Bind( MonoObject* self);


	static float ICall_SoundEchoFilterComponent_GetDelay(MonoObject* pMonoObj);

	static void ICall_SoundEchoFilterComponent_SetDelay(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundEchoFilterComponent_GetLRDelay(MonoObject* pMonoObj);

	static void ICall_SoundEchoFilterComponent_SetLRDelay(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundEchoFilterComponent_GetDamping(MonoObject* pMonoObj);

	static void ICall_SoundEchoFilterComponent_SetDamping(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundEchoFilterComponent_GetFeedBack(MonoObject* pMonoObj);

	static void ICall_SoundEchoFilterComponent_SetFeedBack(MonoObject* pMonoObj, float pvalue);

	static float ICall_SoundEchoFilterComponent_GetSpread(MonoObject* pMonoObj);

	static void ICall_SoundEchoFilterComponent_SetSpread(MonoObject* pMonoObj, float pvalue);

	//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_SoundEchoFilterComponent( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_Bind",       (void*)&ICall_SoundEchoFilterComponent_Bind},
			 { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_GetDelay",(void*)&ICall_SoundEchoFilterComponent_GetDelay},
			 { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_SetDelay",(void*)&ICall_SoundEchoFilterComponent_SetDelay},
			 { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_GetLRDelay",(void*)&ICall_SoundEchoFilterComponent_GetLRDelay},
			 { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_SetLRDelay",(void*)&ICall_SoundEchoFilterComponent_SetLRDelay},
			 { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_GetDamping",(void*)&ICall_SoundEchoFilterComponent_GetDamping},
			 { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_SetDamping",(void*)&ICall_SoundEchoFilterComponent_SetDamping},
			 { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_GetFeedBack",(void*)&ICall_SoundEchoFilterComponent_GetFeedBack},
			 { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_SetFeedBack",(void*)&ICall_SoundEchoFilterComponent_SetFeedBack},
			 { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_GetSpread",(void*)&ICall_SoundEchoFilterComponent_GetSpread},
			 { "ScriptRuntime.SoundEchoFilterComponent::ICall_SoundEchoFilterComponent_SetSpread",(void*)&ICall_SoundEchoFilterComponent_SetSpread},
        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
