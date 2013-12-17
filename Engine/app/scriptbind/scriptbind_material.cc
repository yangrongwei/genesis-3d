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
#include "foundation/util/scriptbind.h"
#include "foundation/util/string.h"
#include "graphicsystem/Material/materialinstance.h"
#include "resource/resourcemanager.h"
namespace App 
{
  

    void ICallReg_ScriptRuntime_Material( void );

    //------------------------------------------------------------------------
  
    //------------------------------------------------------------------------
	static void ICall_Material_Bind( MonoObject* pMonoObj )
	{
		Graphic::MaterialInstance* pRTT = Graphic::MaterialInstance::Create();

		n_assert( NULL!=pRTT );
		BindCppObjWithMonoObj<Graphic::MaterialInstance>(pRTT,pMonoObj);
	}

	static void ICall_Material_Release( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<Graphic::MaterialInstance> self( pMonoObj );
		Graphic::MaterialInstance* pRT = self.GetCppObjPtr();
		n_assert( NULL!=pRT );

		ReleaseCppObjWithMonoObj<Graphic::MaterialInstance>( pRT, pMonoObj );
	}

	static void ICall_Material_SetTexture(MonoObject* pMonoObj, MonoString* paramName, gpointer textureHandlePtr)
	{
		ScriptObjWrapper<Graphic::MaterialInstance> self( pMonoObj );
		RenderBase::TextureHandle* tex = static_cast<RenderBase::TextureHandle*>(textureHandlePtr);
		Graphic::ShaderParamString name;
		Utility_MonoStringToCppString(paramName, name);
		self->SetTexture(name, *tex);
	}

	static void ICall_Material_SetTextureResource(MonoObject* pMonoObj, MonoString* paramName, MonoString* id, Resources::Priority priority)
	{
		ScriptObjWrapper<Graphic::MaterialInstance> self( pMonoObj );
		Graphic::ShaderParamString param_name;
		Resources::ResourceId source_id;
		Utility_MonoStringToCppString(paramName, param_name);
		Utility_MonoStringToCppString(id, source_id);

		self->SetTexture(param_name, source_id, priority);
	}

	static void ICall_Material_SetValueFloat(MonoObject* pMonoObj, MonoString* paramName, float value)
	{
		ScriptObjWrapper<Graphic::MaterialInstance> self( pMonoObj );
		Graphic::ShaderParamString param_name;
		Utility_MonoStringToCppString(paramName, param_name);
		self->SetConstantParam(param_name, value);
	}

	static void ICall_Material_SetValueVector4(MonoObject* pMonoObj, MonoString* paramName, const Math::float4& value)
	{
		ScriptObjWrapper<Graphic::MaterialInstance> self( pMonoObj );
		Graphic::ShaderParamString param_name;
		Utility_MonoStringToCppString(paramName, param_name);
		self->SetConstantParam(param_name, value);
	}

	static void ICall_Material_SetValueMatrix44(MonoObject* pMonoObj, MonoString* paramName, const Math::matrix44& value)
	{
		ScriptObjWrapper<Graphic::MaterialInstance> self( pMonoObj );
		Graphic::ShaderParamString param_name;
		Utility_MonoStringToCppString(paramName, param_name);
		self->SetConstantParam(param_name, value);
	}


	static void ICall_Material_SetGlobalMatrix(int index, const Math::matrix44& value)
	{
		Graphic::GlobalMaterialParam* pGMP = Graphic::Material::GetGlobalMaterialParams();
		pGMP->SetMatrixParam(TypeConvert<Graphic::GlobalMatrixParamIndex>::Conver(index), value);

	}

	static void ICall_Material_SetGlobalVector(int index, const Math::float4& value)
	{
		Graphic::GlobalMaterialParam* pGMP = Graphic::Material::GetGlobalMaterialParams();
		pGMP->SetVectorParam(TypeConvert<Graphic::GlobalVectorParamIndex>::Conver(index), value);

	}
    //------------------------------------------------------------------------
    void ICallReg_ScriptRuntime_Material( void )
    {
        static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
 			{ "ScriptRuntime.MaterialInstance::ICall_Material_Bind",							(void*)&ICall_Material_Bind },
			{ "ScriptRuntime.MaterialInstance::ICall_Material_Release",							(void*)&ICall_Material_Release },
			{ "ScriptRuntime.MaterialInstance::ICall_Material_SetTexture",						(void*)&ICall_Material_SetTexture },
			{ "ScriptRuntime.MaterialInstance::ICall_Material_SetTextureResource",				(void*)&ICall_Material_SetTextureResource },
			{ "ScriptRuntime.MaterialInstance::ICall_Material_SetValueFloat",					(void*)&ICall_Material_SetValueFloat },
			{ "ScriptRuntime.MaterialInstance::ICall_Material_SetValueVector4",					(void*)&ICall_Material_SetValueVector4 },
			{ "ScriptRuntime.MaterialInstance::ICall_Material_SetValueMatrix44",				(void*)&ICall_Material_SetValueMatrix44 },
			{ "ScriptRuntime.MaterialInstance::ICall_Material_SetGlobalMatrix",					(void*)&ICall_Material_SetGlobalMatrix },
			{ "ScriptRuntime.MaterialInstance::ICall_Material_SetGlobalVector",					(void*)&ICall_Material_SetGlobalVector },
        };

        int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
        for( int ii=0; ii<size; ii++ )
        {
            mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
                s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
        }
    }
}
