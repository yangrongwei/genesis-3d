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
    static void ICall_LightComponent_Bind( MonoObject* self);

    static int ICall_LightComponent_GetLightType( MonoObject* self);

    static void ICall_LightComponent_SetLightType( MonoObject* self, int lightType);

    static void ICall_LightComponent_GetPosition( MonoObject* self, Math::float3& outPos);

    static void ICall_LightComponent_SetPosition( MonoObject* self, const Math::float3& pos);

    static void ICall_LightComponent_GetDirection( MonoObject* self, Math::float3& dir);

    static void ICall_LightComponent_SetDirection( MonoObject* self, const Math::float3& dir);

    static void ICall_LightComponent_GetColorF( MonoObject* self, Math::float4& color);

    static void ICall_LightComponent_SetColorF( MonoObject* self, const Math::float4& color);

    static float ICall_LightComponent_GetIntensity( MonoObject* self);

    static void ICall_LightComponent_SetIntensity( MonoObject* self, float intensity);

    static float ICall_LightComponent_GetRange( MonoObject* pMonoObj);

	static void ICall_LightComponent_SetRange( MonoObject* pMonoObj, float range);

	static void ICall_LightComponent_SetDistanceFallOff( MonoObject* pMonoObj, float falloff);

	static float ICall_LightComponent_GetDistanceFallOff( MonoObject* pMonoObj);

	static void ICall_LightComponent_SetSpotInnerAngle( MonoObject* pMonoObj, float innerAngle);

	static float ICall_LightComponent_GetSpotInnerAngle( MonoObject* pMonoObj);

	static void ICall_LightComponent_SetSpotOuterAngle( MonoObject* pMonoObj, float outerAngle);

	static float ICall_LightComponent_GetSpotOuterAngle( MonoObject* pMonoObj);

	static void ICall_LightComponent_SetSpotExponent( MonoObject* pMonoObj, float exponent);

	static float ICall_LightComponent_GetSpotExponent( MonoObject* pMonoObj);

//********************************* Register func to mono ********************************************
	void ICallReg_ScriptRuntime_LightComponent( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
             { "ScriptRuntime.LightComponent::ICall_LightComponent_Bind",                           (void*)&ICall_LightComponent_Bind},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_GetLightType",                   (void*)&ICall_LightComponent_GetLightType},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_SetLightType",                   (void*)&ICall_LightComponent_SetLightType},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_GetPosition",                    (void*)&ICall_LightComponent_GetPosition},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_SetPosition",                    (void*)&ICall_LightComponent_SetPosition},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_GetDirection",                   (void*)&ICall_LightComponent_GetDirection},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_SetDirection",                   (void*)&ICall_LightComponent_SetDirection},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_GetColorF",                      (void*)&ICall_LightComponent_GetColorF},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_SetColorF",                      (void*)&ICall_LightComponent_SetColorF},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_GetIntensity",                   (void*)&ICall_LightComponent_GetIntensity},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_SetIntensity",                   (void*)&ICall_LightComponent_SetIntensity},
             { "ScriptRuntime.LightComponent::ICall_LightComponent_GetRange",						(void*)&ICall_LightComponent_GetRange},
			 { "ScriptRuntime.LightComponent::ICall_LightComponent_SetRange",						(void*)&ICall_LightComponent_SetRange},
			 { "ScriptRuntime.LightComponent::ICall_LightComponent_SetDistanceFallOff",             (void*)&ICall_LightComponent_SetDistanceFallOff},
			 { "ScriptRuntime.LightComponent::ICall_LightComponent_GetDistanceFallOff",             (void*)&ICall_LightComponent_GetDistanceFallOff},
			 { "ScriptRuntime.LightComponent::ICall_LightComponent_SetSpotInnerAngle",              (void*)&ICall_LightComponent_SetSpotInnerAngle},
			 { "ScriptRuntime.LightComponent::ICall_LightComponent_GetSpotInnerAngle",              (void*)&ICall_LightComponent_GetSpotInnerAngle},
			 { "ScriptRuntime.LightComponent::ICall_LightComponent_SetSpotOuterAngle",              (void*)&ICall_LightComponent_SetSpotOuterAngle},
			 { "ScriptRuntime.LightComponent::ICall_LightComponent_GetSpotOuterAngle",              (void*)&ICall_LightComponent_GetSpotOuterAngle},
			 { "ScriptRuntime.LightComponent::ICall_LightComponent_SetSpotExponent",                (void*)&ICall_LightComponent_SetSpotExponent},
			 { "ScriptRuntime.LightComponent::ICall_LightComponent_GetSpotExponent",                (void*)&ICall_LightComponent_GetSpotExponent}

        };
        int size = sizeof(s_cScriptBindInternalCallDetail) / sizeof(InternalCallDetail);
        for (int ii = 0; ii < size; ++ii)
        {
                mono_add_internal_call(s_cScriptBindInternalCallDetail[ii].__pScriptFunName,
                        s_cScriptBindInternalCallDetail[ii].__pCppFunPtr);
        }
    }
} 
