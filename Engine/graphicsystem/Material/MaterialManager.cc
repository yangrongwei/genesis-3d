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
#include "materialinstance.h"
#include "addons/resource/resourcemanager.h"
#include "serialization/serializeserver.h"
#include "materialmaker/GenesisMaterial.h"
#include "materialmaker/parser/GenesisShaderParser.h"
#include "io/memorystream.h"
#include "io/iointerfaceprotocol.h"
#include "io/iointerface.h"

#include "MaterialManager.h"


namespace Graphic
{
	const  Resources::ResourceId s_strMatMngFile ("asset:AllMaterialInfo.mng");
	const  Resources::ResourceId s_strMatInstancePath("asset:");
	const  Resources::ResourceId s_strMatInstanceFile ("NewMaterial");
	const  Resources::ResourceId s_strMatInstanceFileExt (".material");
	const Resources::ResourceId DefalutShaderID("shd:Common_Diffuse.shader");


	__ImplementClass( MaterialInstanceManager, 'MIMA', Core::RefCounted);

	MaterialInstanceManager::MaterialInstanceManager():m_usedMaterialNameIdx(0)
	{
		//empty
	}

	//------------------------------------------------------------------------
	MaterialInstanceManager::~MaterialInstanceManager()
	{

	}
	//------------------------------------------------------------------------
	GPtr<Graphic::MaterialInstance> 
		MaterialInstanceManager::CreateMaterialInstance( const Resources::ResourceId& shaderID )
	{
		if ( !shaderID.IsValid() )
		{
			n_error("invalid shaderID!");
		}

		GPtr<MaterialInstance> pAppMaterial = _CreateMaterialInstance( shaderID );
		if ( !pAppMaterial.isvalid() )
		{
			n_error("can't create AppMaterial!");
			//return MaterialInstance::Create();
		}
		return pAppMaterial;
	}	
	//------------------------------------------------------------------------
	GPtr<Graphic::MaterialInstance>						
		MaterialInstanceManager::UpdateShader(const Resources::ResourceId& shaderID)
	{
		IndexT index = m_graphicMaterialMap.FindIndex(shaderID);
		GPtr<Graphic::Material> mat = GenesisMaterialMaker::MakeFromShader(shaderID);		

		if (InvalidIndex != index)
			m_graphicMaterialMap.Erase(shaderID);

		m_graphicMaterialMap.Add(shaderID,mat);


		GPtr<MaterialInstance> aMat = MaterialInstance::Create();	
		_InitMaterialInstance(aMat,shaderID,mat);	
		return aMat;
	}
	//------------------------------------------------------------------------
	void 
		MaterialInstanceManager::_SetMaterialID(GPtr<Graphic::MaterialInstance>& matIns)
	{
		if ( !matIns )
		{
			n_assert(0);
			return;
		}

		Util::Guid guid;
		guid.Generate();
		Util::String strMatID = s_strMatInstancePath.Value();
		strMatID = strMatID + guid.AsString() + s_strMatInstanceFileExt.Value();
		//strMatID.Format("%s%s%d%s",s_strMatInstancePath.Value(),s_strMatInstanceFile.Value(),GetMaterialNameIdx(),s_strMatInstanceFileExt.Value());
		Resources::ResourceId matID(strMatID.Get());

		matIns->SetMaterialID(matID);

		m_graphicMaterialInstanceMap.Add(matIns->GetMaterialID(),matIns);	
	}
	//------------------------------------------------------------------------
	GPtr<MaterialInstance>
		MaterialInstanceManager::_CreateMaterialInstance( const Resources::ResourceId& shaderID )
	{
		// 创建某个材质的副本
		GPtr<MaterialInstance> aMat = 0;		
		aMat = _CreateNewMaterialInstance(shaderID);
		_SetMaterialID(aMat);	

		return aMat;
	}


	//------------------------------------------------------------------------
	GPtr<Graphic::MaterialInstance>
		MaterialInstanceManager::_CreateNewMaterialInstance( const Resources::ResourceId& shaderID )
	{// 注意此函数创建出来的材质不会放入材质管理器，不受材质管理器的管理
		GPtr<MaterialInstance> aMat = 0;
		IndexT index = m_graphicMaterialMap.FindIndex(shaderID);
		if (InvalidIndex != index)
		{
			GPtr<Graphic::Material>& mat = m_graphicMaterialMap.ValueAtIndex(index);
			// add ref cnt
			//mat->SetHaveMaterialInstanceCnt(mat->GetHaveMaterialInstanceCnt() + 1);

			aMat = MaterialInstance::Create();	
			_InitMaterialInstance(aMat,shaderID,mat);			
		}
		else
		{
			GPtr<Graphic::Material> mat = GenesisMaterialMaker::MakeFromShader(shaderID);
			m_graphicMaterialMap.Add(shaderID,mat);	

			aMat = MaterialInstance::Create();	
			_InitMaterialInstance(aMat,shaderID,mat);

		}	


		return aMat;
	}
	//------------------------------------------------------------------------
	void MaterialInstanceManager::_InitMaterialInstance(GPtr<Graphic::MaterialInstance>& matIns, const Resources::ResourceId& shaderID,const GPtr<Graphic::Material>& mat)
	{
		matIns->Clone(mat);
		matIns->_SetShaderID(shaderID);
		matIns->_AssignDefaultToInstance();
	}
	//------------------------------------------------------------------------
	bool			
		MaterialInstanceManager::HaveMaterialInstance(const MaterialId& matID)
	{
		IndexT index = m_graphicMaterialInstanceMap.FindIndex(matID);
		return (InvalidIndex != index );

	}
	//------------------------------------------------------------------------
	const GPtr<Graphic::MaterialInstance>&
		MaterialInstanceManager::GetMaterialInstance(const MaterialId& matID)
	{
		IndexT index = m_graphicMaterialInstanceMap.FindIndex(matID);
		if(InvalidIndex != index )
		{
			return m_graphicMaterialInstanceMap.ValueAtIndex(index);
		}
		return MaterialInstance::NullMaterial;
	}

	//------------------------------------------------------------------------
	GPtr<Graphic::MaterialInstance> 
		MaterialInstanceManager::NewMaterialInstanceCopyByMatID(const MaterialId& matID)
	{// 有该材质则创建该材质的copy，

		GPtr<MaterialInstance> aMat = 0;
		IndexT index = m_graphicMaterialInstanceMap.FindIndex(matID);
		if(InvalidIndex == index )
		{
			n_assert(0);
			return aMat;			
		}

		aMat = m_graphicMaterialInstanceMap.ValueAtIndex(index);

		// 材质id 是自动生成的
		GPtr<MaterialInstance> aMatRet = _CreateMaterialInstance(aMat->GetShaderID());
		aMatRet->CopyFrom(aMat); //copyFrom need to be continue...
		return aMatRet;
	}

	//------------------------------------------------------------------------
	void
		MaterialInstanceManager::RemoveMaterialInstance(const MaterialId& matID)
	{
		IndexT index = m_graphicMaterialInstanceMap.FindIndex(matID);
		if(InvalidIndex != index )
		{
			m_graphicMaterialInstanceMap.Erase(matID);
		}
	}
	//------------------------------------------------------------------------
	/*
	* 修改材质参数接口集
	*/
	GPtr<Graphic::MaterialInstance> 
		MaterialInstanceManager::ModifyMaterialInstance(const MaterialId& matID,const Resources::ResourceId& newShaderID)
	{
		GPtr<MaterialInstance> aMat = 0;
		IndexT index = m_graphicMaterialInstanceMap.FindIndex(matID);
		if(InvalidIndex == index )
		{
			n_assert(0);
			return aMat;			
		}
		aMat = m_graphicMaterialInstanceMap.ValueAtIndex(index);
		GPtr<MaterialInstance> newMat = _CreateNewMaterialInstance(newShaderID);
		newMat->SetMaterialID(aMat->GetMaterialID());
		aMat->CopyFrom(newMat);
		return aMat;
	}
	//------------------------------------------------------------------------
	void MaterialInstanceManager::ModifyMaterialInstanceID(const MaterialId& matID,const MaterialId& newMatID)
	{

		IndexT index = m_graphicMaterialInstanceMap.FindIndex(matID);
		if(InvalidIndex == index )
		{
			n_assert(0);
			return ;			
		}

		GPtr<MaterialInstance> aMat = 0;
		aMat = m_graphicMaterialInstanceMap.ValueAtIndex(index);
		m_graphicMaterialInstanceMap.EraseAtIndex(index);

		aMat->SetMaterialID(newMatID);
		m_graphicMaterialInstanceMap.Add(newMatID,aMat);	
	}

	//------------------------------------------------------------------------
	GPtr<Graphic::MaterialInstance> 
		MaterialInstanceManager::LoadMaterialInstance(const MaterialId& matID,const Resources::ResourceId& shaderID )
	{// 此函数的处理：如果同一个材质被第2次请求load，其流程是先删掉旧的，再从磁盘加载一遍。（材质热加载需要这样的流程）
		GPtr<MaterialInstance> aMat = 0;
		IndexT index = m_graphicMaterialInstanceMap.FindIndex(matID);
		if(InvalidIndex != index )
		{
			n_warning("LoadMaterialInstance load same material %s",matID.Value());
			m_graphicMaterialInstanceMap.EraseAtIndex(index);
		}

		//
		aMat = _CreateNewMaterialInstance(shaderID);
		aMat->SetMaterialID(matID);
		m_graphicMaterialInstanceMap.Add(aMat->GetMaterialID(),aMat);
		return aMat;
	}

	//------------------------------------------------------------------------
	void
		MaterialInstanceManager::SaveMaterial()
	{
		//_SaveMaterialMngFile();
		//_SaveAllMaterialInstance();
		Resources::ResourceManager::Instance()->SaveMaterials();

	}
	//------------------------------------------------------------------------
	void MaterialInstanceManager::SaveOneMaterialInstance(const Resources::ResourceId& matID)
	{
		Resources::ResourceManager::Instance()->SaveMaterial(matID);

	}	
	//------------------------------------------------------------------------

	Util::String MaterialInstanceManager::GetInitParamValue(const Resources::ResourceId& matID,int paramIndex)
	{
		int index = m_graphicMaterialMap.FindIndex(matID);
		if(index == -1)
			return "";
		GPtr<Graphic::Material>& mat = m_graphicMaterialMap.ValueAtIndex(index);
		const MaterialParamList& paramList = mat->GetParamList();
		if(paramIndex >= paramList.Size())
			return "";
		return paramList[paramIndex]->GetStringValue();
	}


}