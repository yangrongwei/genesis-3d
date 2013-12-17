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
#include "foundation/math/float3.h"
#include "foundation/math/ray.h"
#include "soundfeature/components/SoundSourceComponent.h"


namespace App
{
	void ICallReg_ScriptRuntime_SoundSource( void );

	//------------------------------------------------------------------------
	static void ICall_SoundSource_Play(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->Play();
	}

    //------------------------------------------------------------------------
	static void ICall_SoundSource_Stop(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->Stop();
	}

    //------------------------------------------------------------------------
	static void ICall_SoundSource_Pause(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->Pause();
	}

    //------------------------------------------------------------------------
	static mono_bool ICall_SoundSource_IsPlaying(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		bool blink =  self->IsPlaying();
		if ( blink )
		{
			return c_iMonoBool_True;
		}
		else
		{
			return c_iMonoBool_False;
		}
	}

    //------------------------------------------------------------------------
	static mono_bool ICall_SoundSource_IsPaused(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		bool blink =  self->IsPaused();
		if ( blink )
		{
			return c_iMonoBool_True;
		}
		else
		{
			return c_iMonoBool_False;
		}
	}

    //------------------------------------------------------------------------
	static mono_bool ICall_SoundSource_GetLoop(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		bool blink =  self->GetLoop();
		if ( blink )
		{
			return c_iMonoBool_True;
		}
		else
		{
			return c_iMonoBool_False;
		}
	}

    //------------------------------------------------------------------------
	static void ICall_SoundSource_SetLoop(MonoObject* pMonoObj, mono_bool bLoop)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		bool b = false;
		if ( c_iMonoBool_True==bLoop )
		{
			b = true;
		}

		self->SetLoop( b );
	}

    //------------------------------------------------------------------------
	static float ICall_SoundSource_GetVolume(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetVolume();
	}

    //------------------------------------------------------------------------
	static void ICall_SoundSource_SetVolume(MonoObject* pMonoObj, float volume)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->SetVolume(volume);
	}

    //------------------------------------------------------------------------
	static mono_bool ICall_SoundSource_GetMute(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		bool blink =  self->GetMute();
		if ( blink )
		{
			return c_iMonoBool_True;
		}
		else
		{
			return c_iMonoBool_False;
		}
	}

    //------------------------------------------------------------------------
	static void ICall_SoundSource_SetMute(MonoObject* pMonoObj, mono_bool bMute)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		bool b = false;
		if ( c_iMonoBool_True == bMute )
		{
			b = true;
		}

		self->SetMute(b);
	}

    //------------------------------------------------------------------------
	static void ICall_SoundSource_Init(MonoObject* pMonoObj, MonoString* pMonoString, mono_bool is3D)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
        Util::String name = Utility_MonoStringToCppString( pMonoString );

        bool b = false;
		if ( c_iMonoBool_True == is3D )
		{
			b = true;
		}

		self->Init(name, b);
	}

    //------------------------------------------------------------------------
	static mono_bool ICall_SoundSource_Is3D(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		bool blink =  self->Is3D();
		if ( blink )
		{
			return c_iMonoBool_True;
		}
		else
		{
			return c_iMonoBool_False;
		}
	}

    //------------------------------------------------------------------------
	static void ICall_SoundSource_Set3D(MonoObject* pMonoObj, mono_bool is3D)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		bool b = false;
		if ( c_iMonoBool_True == is3D )
		{
			b = true;
		}
        self->Set3D(b);
	}

    //------------------------------------------------------------------------
	static MonoString* ICall_SoundSource_GetName(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		Util::String sName = self->GetName();
		return Utility_NewMonoString( sName );
	}

    //------------------------------------------------------------------------
	static void ICall_SoundSource_SetName(MonoObject* pMonoObj, MonoString* pMonoString, int loadpriority )
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		Util::String name = Utility_MonoStringToCppString( pMonoString );
        self->SetName(name, loadpriority);
	}

    //------------------------------------------------------------------------
	static uint ICall_SoundSource_GetLength(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetLength();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundSource_SetPitch(MonoObject* pMonoObj, float pitch)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->SetPitch(pitch);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundSource_GetPitch(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetPitch();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundSource_SetDopplerLevel(MonoObject* pMonoObj, float level)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->SetDopplerLevel(level);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundSource_GetDopplerLevel(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetDopplerLevel();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundSource_SetSpread(MonoObject* pMonoObj, float spread)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->SetSpread(spread);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundSource_GetSpread(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetSpread();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundSource_SetPriority(MonoObject* pMonoObj, int priority)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->SetPriority(priority);
	}
	//------------------------------------------------------------------------
	static int ICall_SoundSource_GetPriority(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetPriority();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundSource_SetMinDistance(MonoObject* pMonoObj, float minDistance)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->SetMinDistance(minDistance);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundSource_GetMinDistance(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetMinDistance();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundSource_SetMaxDistance(MonoObject* pMonoObj, float maxDistance)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->SetMaxDistance(maxDistance);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundSource_GetMaxDistance(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetMaxDistance();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundSource_SetPan(MonoObject* pMonoObj, float pan)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->SetPan(pan);
	}
	//------------------------------------------------------------------------
	static float ICall_SoundSource_GetPan(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetPan();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundSource_SetPosition(MonoObject* pMonoObj, uint position)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->SetPosition(position);
	}
	//------------------------------------------------------------------------
	static uint ICall_SoundSource_GetPosition(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetPosition();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundSource_SetAutoPlay(MonoObject* pMonoObj, mono_bool setPlay)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		bool b = false;
		if ( c_iMonoBool_True == setPlay )
		{
			b = true;
		}
		self->SetPlayOnActive(b);
	}
	//------------------------------------------------------------------------
	static mono_bool ICall_SoundSource_GetAutoPlay(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		bool blink =  self->GetPlayOnActive();

		if ( blink )
		{
			return c_iMonoBool_True;
		}
		else
		{
			return c_iMonoBool_False;
		}
	}
	//------------------------------------------------------------------------
	static int ICall_SoundSource_GetLoadPriority(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return self->GetSoundRes()->GetPriority();
	}
	//------------------------------------------------------------------------
	static int ICall_SoundSource_GetRolloffMode(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		return (int)self->GetRolloffMode();
	}
	//------------------------------------------------------------------------
	static void ICall_SoundSource_SetRolloffMode(MonoObject* pMonoObj, int rolloffMode)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		self->SetRolloffMode((RolloffMode)rolloffMode);
	}
	//------------------------------------------------------------------------
	static mono_bool ICall_SoundSource_IsAllLoaded(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<SoundSource> self( pMonoObj );
		GPtr<Resources::AudioRes> mAudioRes  = self->GetAudioRes();
		bool blink = mAudioRes.isvalid();
		if ( blink )
		{
      if (mAudioRes->GetState() == Resources::Resource::Loaded)
      {
			   return c_iMonoBool_True;
      }
      else 
      {
         return c_iMonoBool_False;
      }
		}
		else
		{
			return c_iMonoBool_False;
		}
	}
	//------------------------------------------------------------------------

	void ICallReg_ScriptRuntime_SoundSource( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
            { "ScriptRuntime.SoundSource::ICall_SoundSource_Play", (void*)&ICall_SoundSource_Play },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_Stop", (void*)&ICall_SoundSource_Stop },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_Pause", (void*)&ICall_SoundSource_Pause },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_IsPlaying", (void*)&ICall_SoundSource_IsPlaying },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_IsPaused", (void*)&ICall_SoundSource_IsPaused },	
            { "ScriptRuntime.SoundSource::ICall_SoundSource_GetLoop", (void*)&ICall_SoundSource_GetLoop },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_SetLoop", (void*)&ICall_SoundSource_SetLoop },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_GetVolume", (void*)&ICall_SoundSource_GetVolume },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_SetVolume", (void*)&ICall_SoundSource_SetVolume },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_GetMute", (void*)&ICall_SoundSource_GetMute },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_SetMute", (void*)&ICall_SoundSource_SetMute },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_Init", (void*)&ICall_SoundSource_Init },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_Is3D", (void*)&ICall_SoundSource_Is3D },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_Set3D", (void*)&ICall_SoundSource_Set3D },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_GetName", (void*)&ICall_SoundSource_GetName },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_SetName", (void*)&ICall_SoundSource_SetName },
            { "ScriptRuntime.SoundSource::ICall_SoundSource_GetLength", (void*)&ICall_SoundSource_GetLength },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetPitch", (void*)&ICall_SoundSource_GetPitch },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_SetPitch", (void*)&ICall_SoundSource_SetPitch },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_SetDopplerLevel", (void*)&ICall_SoundSource_SetDopplerLevel },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetDopplerLevel", (void*)&ICall_SoundSource_GetDopplerLevel },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_SetSpread", (void*)&ICall_SoundSource_SetSpread },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetSpread", (void*)&ICall_SoundSource_GetSpread },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_SetPriority", (void*)&ICall_SoundSource_SetPriority },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetPriority", (void*)&ICall_SoundSource_GetPriority },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_SetMinDistance", (void*)&ICall_SoundSource_SetMinDistance },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetMinDistance", (void*)&ICall_SoundSource_GetMinDistance },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetMaxDistance", (void*)&ICall_SoundSource_GetMaxDistance },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_SetMaxDistance", (void*)&ICall_SoundSource_SetMaxDistance },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetPan", (void*)&ICall_SoundSource_GetPan },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_SetPan", (void*)&ICall_SoundSource_SetPan },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_SetPosition", (void*)&ICall_SoundSource_SetPosition },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetPosition", (void*)&ICall_SoundSource_GetPosition },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetLoadPriority", (void*)&ICall_SoundSource_GetLoadPriority },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_SetRolloffMode", (void*)&ICall_SoundSource_SetRolloffMode },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetRolloffMode", (void*)&ICall_SoundSource_GetRolloffMode },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_SetAutoPlay", (void*)&ICall_SoundSource_SetAutoPlay },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_GetAutoPlay", (void*)&ICall_SoundSource_GetAutoPlay },
			{ "ScriptRuntime.SoundSource::ICall_SoundSource_IsAllLoaded", (void*)&ICall_SoundSource_IsAllLoaded }
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
									s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}

}

#endif
