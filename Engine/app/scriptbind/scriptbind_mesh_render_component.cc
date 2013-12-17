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
#include "addons/resource/meshres.h"


namespace App
{
	void ICallReg_ScriptRuntime_MeshRenderComponent( void );
	static void ICall_MeshRenderComponent_SetMeshID( MonoObject* pMonoObj, MonoString* pMonoStr )
	{
		ScriptObjWrapper<MeshRenderComponent> self( pMonoObj );
		Util::String sMeshId = Utility_MonoStringToCppString( pMonoStr );

		self->SetMeshID( sMeshId );
	}

	static MonoString* ICall_MeshRenderComponent_GetMeshID( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<MeshRenderComponent> self( pMonoObj );
		Resources::ResourceId resId =  self->GetMeshID();
		Util::String str = resId.AsString();
		MonoString* monoStr = Utility_CppStringToMonoString(str.AsCharPtr());
		return monoStr;
	}

	static void ICall_MeshRenderComponent_SetDrawDepth(MonoObject* pMonoObj, bool bDraw)
	{
		ScriptObjWrapper<MeshRenderComponent> self( pMonoObj );
		self->SetDrawDepth(bDraw);
	}

	static int ICall_MeshRenderComponent_GetTriangleCount( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<MeshRenderComponent> self( pMonoObj );

		const  GPtr<Resources::PrimitiveResInfo>& resInfo =  self->GetPrimtiveResInfo();
		if(!resInfo.isvalid())
		{
			return 0;
		}
		const GPtr<Resources::MeshRes>& meshRes = resInfo->GetRes().downcast<Resources::MeshRes>();
		return meshRes->GetIndexCount()/3;
	}

	static int ICall_MeshRenderComponent_GetVertexCount( MonoObject* pMonoObj )
	{
		ScriptObjWrapper<MeshRenderComponent> self( pMonoObj );

		const  GPtr<Resources::PrimitiveResInfo>& resInfo =  self->GetPrimtiveResInfo();
		if(!resInfo.isvalid())
		{
			return 0;
		}
		const GPtr<Resources::MeshRes>& meshRes = resInfo->GetRes().downcast<Resources::MeshRes>();
		return meshRes->GetVertexCount();
	}


	void ICallReg_ScriptRuntime_MeshRenderComponent( void )
	{
 		static const InternalCallDetail s_cScriptBindInternalCallDetail[] = {
			{ "ScriptRuntime.MeshRenderComponent::ICall_MeshRenderComponent_SetMeshID", (void*)&ICall_MeshRenderComponent_SetMeshID },
			{ "ScriptRuntime.MeshRenderComponent::ICall_MeshRenderComponent_GetMeshID", (void*)&ICall_MeshRenderComponent_GetMeshID },
			{ "ScriptRuntime.MeshRenderComponent::ICall_MeshRenderComponent_SetDrawDepth", (void*)&ICall_MeshRenderComponent_SetDrawDepth },
			{ "ScriptRuntime.MeshRenderComponent::ICall_MeshRenderComponent_GetTriangleCount", (void*)&ICall_MeshRenderComponent_GetTriangleCount },
			{ "ScriptRuntime.MeshRenderComponent::ICall_MeshRenderComponent_GetVertexCount", (void*)&ICall_MeshRenderComponent_GetVertexCount },
 		};
 
 		int size = sizeof(s_cScriptBindInternalCallDetail)/sizeof(InternalCallDetail);
 		for( int ii=0; ii<size; ii++ )
 		{
 			mono_add_internal_call( s_cScriptBindInternalCallDetail[ii].__pScriptFunName, 
									s_cScriptBindInternalCallDetail[ii].__pCppFunPtr );
 		}
	}

}