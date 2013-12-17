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
#include "soundfeature/components/SoundEchoFilterComponent.h"

namespace App
{
	void ICallReg_ScriptRuntime_SoundEchoFilterComponent( void );

	//------------------------------------------------------------------------
	static void ICall_SoundEchoFilterComponent_Bind( MonoObject* pMonoObj )
	{
		SoundEchoFilterComponent* pEcho = SoundEchoFilterComponent::Create();
		n_assert( NULL!=pEcho );
		
		BindCppObjWithMonoObj<SoundEchoFilterComponent>( pEcho, pMonoObj );
	}

	static float ICall_SoundEchoFilterComponent_GetDelay(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundEchoFilterComponent> self( pMonoObj );
		return self->GetEchoParam(SoundEchoFilterComponent::Delay);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundEchoFilterComponent_SetDelay(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundEchoFilterComponent> self( pMonoObj );
		return self->SetEchoParam(SoundEchoFilterComponent::Delay, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundEchoFilterComponent_GetLRDelay(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundEchoFilterComponent> self( pMonoObj );
		return self->GetEchoParam(SoundEchoFilterComponent::LRDelay);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundEchoFilterComponent_SetLRDelay(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundEchoFilterComponent> self( pMonoObj );
		return self->SetEchoParam(SoundEchoFilterComponent::LRDelay, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundEchoFilterComponent_GetDamping(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundEchoFilterComponent> self( pMonoObj );
		return self->GetEchoParam(SoundEchoFilterComponent::Damping);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundEchoFilterComponent_SetDamping(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundEchoFilterComponent> self( pMonoObj );
		return self->SetEchoParam(SoundEchoFilterComponent::Damping, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundEchoFilterComponent_GetFeedBack(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundEchoFilterComponent> self( pMonoObj );
		return self->GetEchoParam(SoundEchoFilterComponent::FeedBack);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundEchoFilterComponent_SetFeedBack(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundEchoFilterComponent> self( pMonoObj );
		return self->SetEchoParam(SoundEchoFilterComponent::FeedBack, pvalue);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundEchoFilterComponent_GetSpread(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundEchoFilterComponent> self( pMonoObj );
		return self->GetEchoParam(SoundEchoFilterComponent::Spread);
	}
	//------------------------------------------------------------------------
	static void ICall_SoundEchoFilterComponent_SetSpread(MonoObject* pMonoObj, float pvalue)
	{
		ScriptObjWrapper<SoundEchoFilterComponent> self( pMonoObj );
		return self->SetEchoParam(SoundEchoFilterComponent::Spread, pvalue);
	}
	//------------------------------------------------------------------------
}

#include "autogen/scriptbind_SoundEchoFilterComponent_register.h"
#endif
