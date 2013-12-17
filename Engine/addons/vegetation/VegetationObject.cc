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
#include "vegetation/VegetationObejct.h"
#include "vegetation/InstanceMap.h"
#include "vegetation/GrassInstanceMap.h"
#include "vegetation/MeshInstanceMap.h"
#include "vegetation/TreeInstanceMap.h"

#include "resource/resourceserver.h"

namespace Vegetation
{	

	using namespace Resources;
	using namespace Graphic;

	__ImplementClass( Vegetation::VegetationObject, 'VEOJ', Core::RefCounted);

	const Resources::ResourceId NullShaderParam("");
	const Util::String NullShaderConstantParamValue("");
	const Resources::ResourceId DefaultTextureID("sys:white.dds");	
	const GPtr<VegetationObject> VegetationObject::NullVegeObj(NULL);

	VegetationObject::VegetationObject()
		: mName("VegetationObject")
		, mInstanceFilePath("")
		, mIsActive(false)
		, mIsBuildMaterials(false)
		, mIsBuildRenderable(false)
		, mIsAttached(false)
		, mIsTrans(false)
		, mCullDistance(1000.0f)
		, mLocalScale(1.f,1.f,1.f)
		, mLocalRotation(0.f,0.f,0.f,1.f)
	{

	}

	//------------------------------------------------------------------------
	VegetationObject::~VegetationObject()
	{
		if ( m_primHandle.IsValid() )
		{
			App::GraphicObjectManager::Instance()->DiscardPrimitiveHandle(m_primHandle);
		}		

	}
	//------------------------------------------------------------------------
	void VegetationObject::SetWorldMatrix( const Math::matrix44& m  )
	{
		if (mInstMap.isvalid())
		{
			mInstMap->SetParentMatrix(m);	
			mWorldMatrix = m;
		}
	}
	//------------------------------------------------------------------------	
	void VegetationObject::ClearRenderables(void)
	{
		//mVegeRenderables.Clear();
		mRenderableResUnitList.Clear();
	}
	//------------------------------------------------------------------------
	Graphic::RenderableResUnitArray& VegetationObject::GetResUnits()
	{
		return mRenderableResUnitList;
	}

	//--------------------------------------------------------------------------------
	VegeInstanceMapPtr& VegetationObject::CreateInstanceMap()
	{
		RenderType type = GetRenderType();
		if ( !mInstMap.isvalid())
		{
			switch ( type )
			{
			case eRT_Grass:
				mInstMap = GrassInstanceMap::Create();	
				break;
			case eRT_DetailMesh:
				mInstMap = MeshInstanceMap::Create();	
				break;
			case eRT_Tree:
				mInstMap = TreeInstanceMap::Create();	
				break;
			default:
				break;
			}

			mInstMap->SetParentVegeObject(this);
			//mInstMap->SetName( GetName() );

		}
		return mInstMap;
	}

	//-----------------------------------------------------------------------------
	struct INSTANCEDATA_POS* VegetationObject::CreateInstance()
	{
		if ( mIsBuildRenderable )
		{
			mIsBuildRenderable = false;
			//mVegeRenderables.Clear();			
		}
		CreateInstanceMap();		
		mInstMap->AddInstance(INSTANCEDATA_POS());
		return mInstMap->GetInstance(mInstMap->GetInstanceCount()-1);
	}
	//--------------------------------------------------------------------------------
	void VegetationObject::RemoveInstance(IndexT nInstID)
	{
		mInstMap->RemoveInstance(nInstID);
	}
	//--------------------------------------------------------------------------------
	void VegetationObject::SetInstanceMap(const VegeInstanceMapPtr& tplInstMap)
	{

		mInstMap = Clone(tplInstMap);
		mInstMap->SetParentVegeObject(this);

	}
	//--------------------------------------------------------------------------------	
	void VegetationObject::SetHWInstancing(bool bUseHWInst)
	{
		if ( mInstMap.isvalid() )
		{
			mInstMap->SetHWInstacing( bUseHWInst );
		}
	}
	//--------------------------------------------------------------------------------	
	bool VegetationObject::IsHWInstancing() const
	{
		if ( mInstMap.isvalid() )
		{
			return mInstMap->IsHWInstancing();
		}
		return false;
	}
	//-------------------------------------------------------------------------
	void VegetationObject::DirtyMaterial(IndexT iSubMesh )
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() )
		{
			const GPtr<Graphic::MaterialInstance>& pMatInst =  GetMaterial(iSubMesh);
			if (pMatInst.isvalid())
			{
				mMatDirty = true;
			}
		}
	}
	//------------------------------------------------------------------------
	void VegetationObject::SetShaderID(IndexT iSubMesh , const Resources::ResourceId& shaderID)
	{	
		//mVegeBrush->SetMaterial(iSubMesh, shaderID);
		if (iSubMesh >= mRenderableResUnitList.Size())
		{
			Resources::MaterialResInfo* sri = ResourceManager::Instance()->CreateMaterialInfo(shaderID,true);	
			mRenderableResUnitList.Append(Graphic::RenderbleResUnit());
			Graphic::RenderbleResUnit& renderableUnit = mRenderableResUnitList.Back();
			renderableUnit.SetResInfo(sri);

			Resources::ResourceId newMatId;
			_ModifyMaterialDir(sri->GetMatID(), newMatId);
			Resources::ResourceManager::Instance()->ModifyMaterialInstanceID(sri->GetMatID(),newMatId);
		}
		else
		{
			if ( mRenderableResUnitList[iSubMesh].GetResInfo()->GetResID() != shaderID)
			{
				Resources::MaterialResInfo* sri = ResourceManager::Instance()->CreateMaterialInfo(shaderID,true);
				Graphic::RenderbleResUnit& renderableUnit = mRenderableResUnitList[iSubMesh];
				renderableUnit.SetResInfo(sri);	

				Resources::ResourceId newMatId;
				_ModifyMaterialDir(sri->GetMatID(), newMatId);
				Resources::ResourceManager::Instance()->ModifyMaterialInstanceID(sri->GetMatID(),newMatId);
			} 
		}
		DirtyMaterial(iSubMesh);
	}

	void VegetationObject::_ModifyMaterialDir(const Resources::ResourceId& oldMatID, Resources::ResourceId& outMatID)
	{
		Util::String strOldMatID= oldMatID.AsString();
		Util::String matFile = strOldMatID.ExtractFileName();
		outMatID = "asset:Terrain/" + matFile;
	}
	//------------------------------------------------------------------------
	const Resources::ResourceId& VegetationObject::GetShaderID(IndexT iSubMesh )const
	{
		//return mVegeBrush->GetMaterialID(iSubMesh);	
		if ( iSubMesh < 0 || iSubMesh >= mRenderableResUnitList.Size() )
		{
			return NullShaderParam;
		}
		const GPtr<Graphic::MaterialInstance>& curMat = GetMaterial(iSubMesh);
		return curMat->GetShaderID();		
	}
	//--------------------------------------------------------------------------------
	void VegetationObject::RemoveShader(IndexT iSubMesh)
	{
		//mVegeBrush->RemoveMaterial(iSubMesh);
		mRenderableResUnitList.EraseIndex(iSubMesh);
		mMatDirty = false;
	}
	//------------------------------------------------------------------------
	void VegetationObject::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const 
	{
		//material 
		for ( IndexT i = 0; i < mRenderableResUnitList.Size(); i++ )
		{
			if ( mRenderableResUnitList[i].GetResInfo().isvalid() )
			{
				list.Append(Resources::ReferenceResource(mRenderableResUnitList[i].GetResInfo()->GetMatID(), Resources::RR_Material));
			}

		}

		//mesh
		const Resources::ResourceId& meshId = GetMeshID();
		if (meshId.IsValid())
		{
			list.Append(Resources::ReferenceResource(meshId.Value(), Resources::RR_Unknown));
		}

		//veg
		list.Append(Resources::ReferenceResource(GetInstanceFilePath(), Resources::RR_Unknown));
	}
	//--------------------------------------------------------------------------------
	SizeT VegetationObject::GetShaderCount() const
	{
		//if ( mVegeBrush.isvalid() )
		//{
		//	return mVegeBrush->GetMaterialsCount();

		//}
		//return 0;

		if (mRenderableResUnitList.IsEmpty() )
			return 0;

		return mRenderableResUnitList.Size() ; 
	}
	//------------------------------------------------------------------------
	GPtr<Graphic::MaterialInstance> VegetationObject::GetMaterial(IndexT index )
	{
		if ( index >= 0 
			&& index < mRenderableResUnitList.Size() 
			&& mRenderableResUnitList[index].GetResInfo().isvalid() )
		{
			return mRenderableResUnitList[index].GetResInfo()->GetHandle();
		}
		return Graphic::MaterialInstance::NullMaterial;
	}	
	//--------------------------------------------------------------------------------
	const GPtr<Graphic::MaterialInstance>& VegetationObject::GetMaterial( int index ) const
	{
		if ( index >= 0 
			&& index < mRenderableResUnitList.Size() 
			&& mRenderableResUnitList[index].GetResInfo().isvalid() )
		{
			return mRenderableResUnitList[index].GetResInfo()->GetHandle();
		}
		return Graphic::MaterialInstance::NullMaterial;
	}
	//------------------------------------------------------------------------
	const Resources::ResourceId& 
		VegetationObject::GetMaterialID(IndexT iSubMesh ) const
	{
		if ( iSubMesh >= 0 
			&& iSubMesh < mRenderableResUnitList.Size() 
			&& mRenderableResUnitList[iSubMesh].GetResInfo().isvalid() )
		{
			const GPtr<Resources::MaterialResInfo>& matInfo = mRenderableResUnitList[iSubMesh].GetResInfo();
			return matInfo->GetMatID();
		}
		return NullShaderParam;

	}
	//------------------------------------------------------------------------
	void 
		VegetationObject::SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy/* = false*/  )
	{
		if ( iSubMesh < 0 || !matID.IsValid() )
		{
			return;
		}
		if ( iSubMesh >= mRenderableResUnitList.Size() )
		{
			while( iSubMesh >= mRenderableResUnitList.Size() )
			{
				GPtr<MaterialResInfo> sri = ResourceManager::Instance()->CreateMaterialInfoByMatID(matID,bCopy);
				//GPtr<MaterialInstance> pMatIns = sri->GetHandle();
				//sri->SetMatID(pMatIns->GetMaterialID());
				//sri->SetResID(pMatIns->GetShaderID());

				mRenderableResUnitList.Append(RenderbleResUnit());
				RenderbleResUnit& renderableUnit = mRenderableResUnitList.Back();
				renderableUnit.SetResInfo(sri);

			}
		}
		else
		{
			if ( mRenderableResUnitList[iSubMesh].GetResInfo().isvalid() ) 
			{
				Resources::MaterialResInfo* sri = ResourceManager::Instance()->CreateMaterialInfoByMatID(matID,bCopy);

				GPtr<MaterialInstance> pMatIns = sri->GetHandle();
				//sri->SetMatID(pMatIns->GetMaterialID());
				//sri->SetResID(pMatIns->GetShaderID());

				RenderbleResUnit& renderableUnit = mRenderableResUnitList[iSubMesh];
				renderableUnit.SetResInfo(sri);
			} 
		}

	}
	//------------------------------------------------------------------------
	void VegetationObject::SetMeshID(const Resources::ResourceId& meshID, const Resources::Priority priority )
	{		
		//if( mVegeBrush->GetMeshID() != meshID )
		//	mVegeBrush->SetMeshID( meshID, priority );

		//if (!mMeshInfo || mMeshInfo->GetResID() != meshID)
		{
			mMeshInfo = Resources::ResourceManager::Instance()->CreatePrimitiveInfo(meshID, priority);
			mMeshDirty = true;
			mIsBuildRenderable = false;
		}
	}
	//--------------------------------------------------------------------------------
	const Resources::ResourceId& VegetationObject::GetMeshID() const
	{
		if ( !mMeshInfo )
		{
			return Resource::EmptyResID;
		}
		return mMeshInfo->GetResID();
	}
	//--------------------------------------------------------------------------------
	const Resources::PrimitiveResInfo* VegetationObject::GetMeshInfo(void) const
	{
		if ( mMeshInfo )
		{
			return mMeshInfo;
		}
		return NULL;
	}
	//------------------------------------------------------------------------

	void VegetationObject::RemoveTexture( IndexT iSubMesh, const ShaderParamString& paramName)
	{	

		if ( GetMaterial(iSubMesh).isvalid() )
		{
			GetMaterial(iSubMesh)->RemoveTexture(paramName);
			DirtyMaterial( iSubMesh );
		}



	}
	//------------------------------------------------------------------------

	void VegetationObject::SetTexture( IndexT iSubMesh, const ShaderParamString& paramName, const Resources::ResourceId& texID )
	{
		if ( !texID.IsValid() )
		{
			return;
		}

		if ( GetMaterial(iSubMesh).isvalid() )
		{
			GetMaterial(iSubMesh)->SetTexture(paramName, texID, 1);
			DirtyMaterial( iSubMesh );
		}

	}
	//--------------------------------------------------------------------------------
	SizeT VegetationObject::GetTextureParamCount(IndexT iSubmesh) const
	{
		//return mVegeBrush->GetTextureParamCount(iSubMesh);
		if ( iSubmesh >= 0 && iSubmesh < mRenderableResUnitList.Size() )
		{

			// if do not map to subclass, this method maybe get zero 
			if (GetMaterial(iSubmesh).isvalid() )
				return GetMaterial(iSubmesh)->GetTextureParamCount();
		}

		return 0;		
	}
	//------------------------------------------------------------------------
	const Resources::ResourceId& VegetationObject::GetTexture(IndexT iSubMesh, const ShaderParamString& paramName ) const
	{
		//return mVegeBrush->GetTexture(iSubMesh, paramName);
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() )
		{
			const GPtr<MaterialInstance>& material = GetMaterial(iSubMesh);
			if ( material.isvalid() )
			{
				IndexT findtex = material->GetTextureParamIndex( paramName );
				if ( findtex != InvalidIndex )
				{
					const GPtr<Resources::TextureResInfo>& texParam = material->GetTextureResInfo(findtex);//texMap.ValueAtIndex( findtex );
					if (texParam.isvalid())
						return texParam->GetResID();
				}
			}
		}
		return Resources::Resource::EmptyResID;
	}
	//--------------------------------------------------------------------------------
	const ShaderParamString& VegetationObject::GetTextureName(IndexT iSubMesh, IndexT  nIdx) const
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() )
		{
			const GPtr<MaterialInstance>& material = GetMaterial(iSubMesh);
			if ( material.isvalid() )
			{
				if ( nIdx >=0 && nIdx < material->GetTextureParamCount() )
				{
					return GetMaterial(iSubMesh)->GetTextureParamName(nIdx);
				}
			}
		}
		return NullShaderParam;
	}
	//------------------------------------------------------------------------
	bool VegetationObject::HasTextureParam(IndexT iSubMesh, const ShaderParamString& shaderparam ) const
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() )
		{
			if ( GetMaterial(iSubMesh).isvalid() )
			{
				return GetMaterial(iSubMesh)->ContainsTextureParam(shaderparam);
			}
		}

		return false;
	}
	//--------------------------------------------------------------------------------
	const ShaderParamString& VegetationObject::GetShaderConstantParam(IndexT iSubMesh, IndexT iParam) const
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() )
		{
			if ( GetMaterial(iSubMesh).isvalid() )
			{
				const GPtr<MaterialInstance>& mat =  GetMaterial(iSubMesh);

				if ( iParam >=0 && iParam < mat->GetConstantParamCount() )
				{
					return mat->GetConstantParamName(iParam);
				}
			}
		}

		return NullShaderParam;
	}
	//------------------------------------------------------------------------
	void VegetationObject::SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Util::String& val)
	{
		//n_assert( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() );
		if (iSubMesh < 0 || iSubMesh >= mRenderableResUnitList.Size())
		{
			return;
		}

		if ( !paramName.IsValid() )
		{
			return;
		}

		if ( !val.IsValid() )
		{
			return;
		}
		GetMaterial(iSubMesh)->_SetConstantParam(paramName, val);

	}

	//--------------------------------------------------------------------------------
	void VegetationObject::SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Math::float4& val)
	{
		//_SetShaderConstantParam(iSubMesh,paramName,Util::String::FromFloat4(val));
		if (iSubMesh < 0 || iSubMesh >= mRenderableResUnitList.Size())
		{
			return;
		}
		const GPtr<MaterialInstance>& mat = GetMaterial(iSubMesh);
		mat->SetConstantParam(paramName, val);

	}
	//------------------------------------------------------------------------
	void VegetationObject::SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Math::matrix44& val)
	{
		if (iSubMesh < 0 || iSubMesh >= mRenderableResUnitList.Size())
		{
			return;
		}
		const GPtr<MaterialInstance>& mat = GetMaterial(iSubMesh);
		mat->SetConstantParam(paramName, val);
	}
	//--------------------------------------------------------------------------------
	void VegetationObject::SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Math::scalar& val )
	{
		if (iSubMesh < 0 || iSubMesh >= mRenderableResUnitList.Size())
		{
			return;
		}
		const GPtr<MaterialInstance>& mat = GetMaterial(iSubMesh);
		mat->SetConstantParam(paramName, val);
	}
	//--------------------------------------------------------------------------------
	void VegetationObject::ClearShaderConstantParams( IndexT iSubMesh )
	{
		n_assert ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() );
		GetMaterial(iSubMesh)->ClearConstantParamCache();
	}
	//--------------------------------------------------------------------------------
	void VegetationObject::RemoveShaderConstParam( IndexT iSubMesh, const ShaderParamString& paramName)
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() )
		{
			if ( !paramName.IsValid() )
			{
				return;
			}

			if (GetMaterial(iSubMesh).isvalid())
			{
				GetMaterial(iSubMesh)->RemoveConstantParam(paramName);
			}

		}
	}
	//--------------------------------------------------------------------------------
	SizeT VegetationObject::GetShaderConstantParamCount(IndexT iSubMesh) const
	{
		//return mVegeBrush->GetShaderConstantParamCount(iSubMesh);
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() && GetMaterial(iSubMesh).isvalid() )	
			return  GetMaterial(iSubMesh)->GetConstantParamCount();	

		return 0;		
	}
	//--------------------------------------------------------------------------------
	const Util::String& VegetationObject::GetShaderConstantParamValue(IndexT iSubMesh, const ShaderParamString& paramName ) const
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() )
		{
			if ( GetMaterial(iSubMesh).isvalid() )
			{
				const GPtr<MaterialInstance>& mat =  GetMaterial(iSubMesh);

				IndexT findtex = mat->GetConstantParamIndex( paramName );
				if ( findtex != InvalidIndex )
				{
					return mat->GetConstantParamValue(findtex);
				}
			}
		}
		return NullShaderConstantParamValue;
	}

	//--------------------------------------------------------------------------------
	const Util::String& VegetationObject::GetShaderConstantParamValue(IndexT iSubMesh, IndexT idx) const
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() && GetMaterial(iSubMesh).isvalid() )
		{
			const GPtr<MaterialInstance>& mat =  GetMaterial(iSubMesh);

			if ( idx != InvalidIndex && mat->GetConstantParamCount() > idx )
			{
				return mat->GetConstantParamValue(idx);
			}
		}
		return NullShaderConstantParamValue;
	}
	//--------------------------------------------------------------------------
	void  VegetationObject::Update()
	{
		if (!mInstMap.isvalid())
			return;

		mInstMap->Update();
	}
	//------------------------------------------------------------------------
	void VegetationObject::Active(void)
	{
		//VegetationServer::Instance()->_attachVegetationInstMap( GPtr<VegeInstanceMap>(this) );
		//mIsActive = true;
		mInstMap->Active();
	}
	//------------------------------------------------------------------------
	void VegetationObject::DeActive(void)
	{
		//VegetationServer::Instance()->_deattachVegetationInstMap( GPtr<VegeInstanceMap>(this) );
		//mIsActive = false;
		mInstMap->DeActive();
	}	
	//------------------------------------------------------------------------
	void VegetationObject::_onActive()
	{
		n_assert( !mIsActive );

		//mInstMap->_onActivate();
		mIsActive = true;
	}
	//------------------------------------------------------------------------
	void VegetationObject::_onDeactive()
	{
		n_assert( mIsActive );


		//mInstMap->_onDeactivate();
		mIsActive = false;
	}
	//--------------------------------------------------------------------------------
	void VegetationObject::SetRotation(Math::quaternion rot)
	{
		this->mLocalRotation = rot;
		//mInstMap->UpdateInstData();
		//mWorldMatrix = Math::matrix44::multiply(mWorldMatrix, Math::matrix44::rotationquaternion( this->mLocalRotation ));
	}
	//--------------------------------------------------------------------------------
	void VegetationObject::SetScale(Math::vector scale)
	{
		this->mLocalScale = scale;
		//mInstMap->UpdateInstData();
		//mWorldMatrix.scale(this->mLocalScale);
	}
	//--------------------------------------------------------------------------------
	void VegetationObject::ReBuildRenderables()
	{
		mIsBuildMaterials = false;
		mIsBuildRenderable = false;
		mIsAttached = false;

		mMeshDirty = false;
		mCanCreateMaterial = false;
		mIsAllTexLoaded = false;

	}

}
