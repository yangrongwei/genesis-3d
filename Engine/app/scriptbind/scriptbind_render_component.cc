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
#include "graphicfeature/components/meshrendercomponent.h"
#include "graphicsystem/base/RenderToTexture.h"

namespace App
{
	void ICallReg_ScriptRuntime_RenderComponent( void );
	//--------------------------------------------------------------------------------------------------
	static MonoString* ICall_RenderComponent_GetMaterialID( MonoObject* pMonoObj, int iSubMesh)
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );
		Util::StringAtom matId= self->GetMaterialID( iSubMesh);

		const char* name = matId.Value();
		MonoString* mono= Utility_CppStringToMonoString( name );
		if (mono != NULL)
		{
			return mono;
		}
		else
		{
			mono = Utility_CppStringToMonoString("");
			return mono;
		}
	}
	//--------------------------------------------------------------------------------------------------
	static MonoObject* ICall_RenderComponent_GetMaterialInstance( MonoObject* pMonoObj, int iSubMesh)
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );
		GPtr<Graphic::MaterialInstance>& instance = self->GetMaterial( iSubMesh);

		return CppPointerToScriptObj( instance.get_unsafe() );
	}
	//--------------------------------------------------------------------------------------------------
	static void ICall_RenderComponent_SetMaterialID( MonoObject* pMonoObj, int iSubMesh, MonoString* pMonoStr, mono_bool bCopy)
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );
		Util::String sShaderID = Utility_MonoStringToCppString( pMonoStr );

		bool b = Utility_MonoBool(bCopy);
		self->SetMaterialID( iSubMesh, sShaderID, b);
	}
	//--------------------------------------------------------------------------------------------------
	static void ICall_RenderComponent_SetMaterialInstance( MonoObject* pMonoObj, int iSubMesh, MonoObject* pMonoInstance, mono_bool bCopy)
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );

		ScriptObjWrapper<Graphic::MaterialInstance> instance( pMonoInstance);
		Graphic::MaterialInstance* materialInstance = instance.GetCppObjPtr();
		bool b = Utility_MonoBool(bCopy);

		self->SetMaterialID( iSubMesh, materialInstance->GetMaterialID(), b);
	}
	//--------------------------------------------------------------------------------------------------
	static MonoString* ICall_RenderComponent_GetShaderID(MonoObject* pMonoObj,int index)
	{		
		ScriptObjWrapper<RenderComponent> self( pMonoObj );

		Util::StringAtom shaderID= self->GetShaderID(index);

		const char* name = shaderID.Value();

		MonoString* mono= Utility_CppStringToMonoString( name );

		if (mono != NULL)
		{
			return mono;
		}
		else
		{
			mono = Utility_CppStringToMonoString("");
			return mono;
		}
	}
	//--------------------------------------------------------------------------------------------------
	static void ICall_RenderComponent_SetShaderID( MonoObject* pMonoObj, int iSubMesh, MonoString* pMonoStr )
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );
		Util::String sShaderID = Utility_MonoStringToCppString( pMonoStr );

		self->SetMaterialByShaderID( iSubMesh, sShaderID );
	}
	//--------------------------------------------------------------------------------------------------
	static void ICall_RenderComponent_SetTexture( MonoObject*pMonoObj, 
		int iSubMesh, 
		MonoString* pMonoStrParamName, 
		MonoString* pMonoStrTexId,
		int iPriority)
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );
		Util::String sParamName = Utility_MonoStringToCppString( pMonoStrParamName );
		Util::String sTexId     = Utility_MonoStringToCppString( pMonoStrTexId );

		self->SetTexture( iSubMesh, sParamName, sTexId, iPriority );
	}
	//--------------------------------------------------------------------------------------------------
	static void ICall_RenderComponent_SetTextureRTT( MonoObject*pMonoObj, 
		int iSubMesh, 
		MonoString* pMonoStrParamName, 
		MonoObject* pMonoRTT)
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );
		Util::String sParamName;
		Utility_MonoStringToCppString( pMonoStrParamName, sParamName );
		ScriptObjWrapper<Graphic::RenderToTexture> rtt( pMonoRTT );

		self->SetTexture( iSubMesh, sParamName, rtt->GetTextureHandle());
	}
	//--------------------------------------------------------------------------------------------------
	static void ICall_RenderComponent_SetShaderConstantParam( MonoObject*pMonoObj, 
		int iSubMesh, 
		MonoString* paramName, 
		float val)
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );

		char* pStr = mono_string_to_utf8( paramName );
		Util::StringAtom cppString( pStr );
		mono_free( pStr );
		self->SetShaderConstantParam(iSubMesh,cppString,val);
	}
	//--------------------------------------------------------------------------------------------------
	static void ICall_RenderComponent_SetShaderConstantParamF4( MonoObject*pMonoObj, 
		int iSubMesh, 
		MonoString* paramName, 
		Math::float4& val)
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );

		char* pStr = mono_string_to_utf8( paramName );
		Util::StringAtom cppString( pStr );
		mono_free( pStr );
		self->SetShaderConstantParam(iSubMesh,cppString,val);
	}
	//--------------------------------------------------------------------------------------------------
	static int ICall_RenderComponent_GetShaderCount( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );
		return self->GetShaderCount();
	}
	//--------------------------------------------------------------------------------------------------
	static void  ICall_RenderComponent_StandaloneRender( MonoObject* pMonoObj, MonoObject* material )
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );
		ScriptObjWrapper<Graphic::Material> mat( material );
		GPtr<Graphic::Material> pMat = mat.GetCppObjPtr();
		self->StandaloneRender(pMat);
	}
	//--------------------------------------------------------------------------------------------------
	static void ICall_RenderComponent_SetVisible( MonoObject* pMonoObj, bool visible )
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );
		self->SetVisible( visible );
	}
	//--------------------------------------------------------------------------------------------------
	static bool ICall_RenderComponent_IsVisible( MonoObject* pMonoObj, bool visible )
	{
		ScriptObjWrapper<RenderComponent> self( pMonoObj );
		return self->GetVisible();
	}

	void ICallReg_ScriptRuntime_RenderComponent( void )
	{
		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_GetMaterialID",				(void*)&ICall_RenderComponent_GetMaterialID},
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_GetMaterialInstance",		(void*)&ICall_RenderComponent_GetMaterialInstance},
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_SetMaterialID",				(void*)&ICall_RenderComponent_SetMaterialID},
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_SetMaterialInstance",		(void*)&ICall_RenderComponent_SetMaterialInstance},
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_GetShaderID",				(void*)&ICall_RenderComponent_GetShaderID },
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_SetShaderID",				(void*)&ICall_RenderComponent_SetShaderID },
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_SetTexture",				(void*)&ICall_RenderComponent_SetTexture },
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_SetTextureRTT",				(void*)&ICall_RenderComponent_SetTextureRTT },
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_SetShaderConstantParam",	(void*)&ICall_RenderComponent_SetShaderConstantParam },		
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_SetShaderConstantParamF4",	(void*)&ICall_RenderComponent_SetShaderConstantParamF4 },
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_GetShaderCount",			(void*)&ICall_RenderComponent_GetShaderCount },
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_StandaloneRender",			(void*)&ICall_RenderComponent_StandaloneRender },
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_SetVisible",				(void*)&ICall_RenderComponent_SetVisible },
			{ "ScriptRuntime.RenderComponent::ICall_RenderComponent_IsVisible",					(void*)&ICall_RenderComponent_IsVisible },
		};

		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
		for( int ii=0; ii<size; ii++ )
		{
			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
				s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
		}
	}

}