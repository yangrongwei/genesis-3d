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
#include "graphicfeature/components/lightcomponent.h"

namespace App
{
	void ICallReg_ScriptRuntime_LightComponent();

	
	static void ICall_LightComponent_Bind(MonoObject* pMonoObj)
	{
		LightComponent* pLight = LightComponent::Create();
		n_assert( NULL!=pLight );
		BindCppObjWithMonoObj<LightComponent>( pLight, pMonoObj );
	}
	static int ICall_LightComponent_GetLightType(MonoObject* pMonoObj)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return LightTypeConvert::Conver(self->GetLightType());
	}

	static void ICall_LightComponent_SetLightType(MonoObject* pMonoObj, int lightType)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return self->SetLightType(LightTypeConvert::Conver(lightType));
	}

	static void ICall_LightComponent_GetPosition( MonoObject* pMonoObj, Math::float3& outPos )
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		outPos = self->GetLightPos();
	}

	static void ICall_LightComponent_SetPosition( MonoObject* pMonoObj, const Math::float3& pos )
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		self->SetLightPos(pos);
	}

	static void ICall_LightComponent_GetDirection( MonoObject* pMonoObj, Math::float3& dir )
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		dir = self->GetLightDir();
	}

	static void ICall_LightComponent_SetDirection( MonoObject* pMonoObj, const Math::float3& dir )
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		self->SetLightDir(dir);
	}

	static void ICall_LightComponent_GetColorF( MonoObject* pMonoObj, Math::float4& color )
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		color = self->GetLightColorF();
	}

	static void ICall_LightComponent_SetColorF( MonoObject* pMonoObj, const Math::float4& color )
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		self->SetLightColorF(color);
	}

	static float ICall_LightComponent_GetIntensity( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return self->GetLightIntensity();
	}

	static void ICall_LightComponent_SetIntensity( MonoObject* pMonoObj, float inensitiy )
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		self->SetLightIntensity(inensitiy);
	}
	static float ICall_LightComponent_GetRange( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return self->GetLightRange();
	}

	static void ICall_LightComponent_SetRange( MonoObject* pMonoObj, float range)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return self->SetLightRange(range);
	}

	static void ICall_LightComponent_SetDistanceFallOff( MonoObject* pMonoObj, float falloff)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return self->SetFalloff(falloff);
	}
	static float ICall_LightComponent_GetDistanceFallOff( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return self->GetFalloff();
	}
	static void ICall_LightComponent_SetSpotInnerAngle( MonoObject* pMonoObj, float innerAngle)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return self->SetCosHalfInnerAngle(Math::n_cos(innerAngle*0.5f*N_PI/180.0f));
	}
	static float ICall_LightComponent_GetSpotInnerAngle( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return Math::n_acos(self->GetCosHalfInnerAngle())*2.0f*180.0f/N_PI;
	}
	static void ICall_LightComponent_SetSpotOuterAngle( MonoObject* pMonoObj, float outerAngle)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return self->SetCosHalfOuterAngle(Math::n_cos(outerAngle*0.5f*N_PI/180.0f));
	}
	static float ICall_LightComponent_GetSpotOuterAngle( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return Math::n_acos(self->GetCosHalfOuterAngle())*2.0f*180.0f/N_PI;
	}
	static void ICall_LightComponent_SetSpotExponent( MonoObject* pMonoObj, float exponent)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return self->SetSpotExponent(exponent);
	}
	static float ICall_LightComponent_GetSpotExponent( MonoObject* pMonoObj)
	{
		ScriptObjWrapper<LightComponent> self( pMonoObj );
		return self->GetSpotExponent();
	}
}

#include "autogen/scriptbind_LightComponent_register.h"
