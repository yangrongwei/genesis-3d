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
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "resource/resourceserver.h"
#include "graphicfeature/components/rendercomponent.h"
#include "graphicsystem/GraphicObjectManager.h"
#include "resource/resourcemanager.h"
#include "app/appframework/actor.h"

namespace App
{
	using namespace Resources;
	using namespace Graphic;
	using namespace RenderBase;

	__ImplementClass(App::RenderComponent, 'RCAP', App::Component );

	const Resources::ResourceId NullShaderParam;
	const Util::String NullShaderConstantParamValue;
	//const Resources::ResourceId DefalutShaderID("asset:Shader/Common_Diffuse.shader");
	//const Resources::ResourceId DefaultTextureID("sys:white.dds");

	//------------------------------------------------------------------------
	RenderComponent::RenderComponent()
		:mMatDirty(false)
		,mCanCreateMaterial(false)
		,m_bAllTexLoaded(true)
		,mVisible(true)
		,mbCastShadow(true)
		,mbReceiveShadow(true)
	{
		//empty
	}
	//------------------------------------------------------------------------
	RenderComponent::~RenderComponent()
	{
		//n_assert( mMaterials.IsEmpty() );
	}
	//------------------------------------------------------------------------
	void RenderComponent::OnActivate()
	{
		Super::OnActivate();
		UpdateRenderLayer();
		n_assert( mActor );
	}
	//------------------------------------------------------------------------
	void RenderComponent::OnDeactivate()
	{
		Super::OnDeactivate();
	}
	//------------------------------------------------------------------------
	// @Component::_OnDestroy called only form Actor::Destroy
	void RenderComponent::OnDestroy()
	{
		// deActive material
		_ClearRenderResUnits();
		mMatDirty = false;
	}
	//------------------------------------------------------------------------
	void RenderComponent::SetupCallbacks()
	{
		//empty
	}

	void RenderComponent::StandaloneRender(const GPtr<Graphic::Material>& customMat)
	{
		//empty
	}

	void RenderComponent::OnWillRenderObject(Graphic::Camera* sender)
	{
		eventWillRenderObject(this);
	}

	void RenderComponent::HandleMessage(const GPtr<Messaging::Message>& msg)
	{
		Super::HandleMessage(msg);
	}
	//------------------------------------------------------------------------
	void RenderComponent::SetupAcceptedMessages()
	{
		Super::SetupAcceptedMessages();
	}
	//------------------------------------------------------------------------
	const Resources::ResourceId& 
		RenderComponent::GetShaderID(IndexT iSubMesh )
	{
		if ( iSubMesh < 0 || iSubMesh >= mRenderableResUnitList.Size() ||  !mRenderableResUnitList[iSubMesh].GetResInfo().isvalid())
		{
			return NullShaderParam;
		}

		GPtr<MaterialInstance> matIns = mRenderableResUnitList[iSubMesh].GetResInfo()->GetHandle();
		n_assert(matIns);
		return matIns->GetShaderID();		
	}
	//------------------------------------------------------------------------
	const Resources::ResourceId& 
		RenderComponent::GetMaterialID(IndexT iSubMesh )
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
		RenderComponent::SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy/* = false*/  )
	{
		if ( iSubMesh < 0 || !matID.IsValid() )
		{
			return;
		}
		if ( iSubMesh >= mRenderableResUnitList.Size() )
		{
			// 填充到iSubMesh的数量
			while( iSubMesh >= mRenderableResUnitList.Size() )
			{
				GPtr<MaterialResInfo> sri = ResourceManager::Instance()->CreateMaterialInfoByMatID(matID,bCopy);

				mRenderableResUnitList.Append(RenderbleResUnit());
				RenderbleResUnit& renderableUnit = mRenderableResUnitList.Back();
				renderableUnit.SetResInfo(sri);	
				_DirtyMaterial(iSubMesh);

			}
		}
		else
		{
			if ( mRenderableResUnitList[iSubMesh].GetResInfo().isvalid() ) //资源热加载有可能有同名的ID
			{// 切换材质
				Resources::MaterialResInfo* sri = ResourceManager::Instance()->CreateMaterialInfoByMatID(matID,bCopy);

				GPtr<MaterialInstance> pMatIns = sri->GetHandle();
				//sri->SetMatID(pMatIns->GetMaterialID());		//YY:有可能sri用的是默认资源，所以ID号还应该是以前的;
				//sri->SetResID(pMatIns->GetShaderID());

				RenderbleResUnit& renderableUnit = mRenderableResUnitList[iSubMesh];
				renderableUnit.SetResInfo(sri);
				_DirtyMaterial(iSubMesh);
			} 
		}

	}

	//------------------------------------------------------------------------
	void 
		RenderComponent::SetMaterialByShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID,const bool bSave /*= true*/ )
	{
		if ( iSubMesh < 0 || !shaderID.IsValid() )
		{
			return;
		}

		if ( iSubMesh >= mRenderableResUnitList.Size() )
		{
			// 填充到iSubMesh的数量
			while( iSubMesh >= mRenderableResUnitList.Size() )
			{
				GPtr<Resources::MaterialResInfo> sri = ResourceManager::Instance()->CreateMaterialInfo(shaderID,bSave);
				mRenderableResUnitList.Append(RenderbleResUnit());
				RenderbleResUnit& renderableUnit = mRenderableResUnitList.Back();
				
				GPtr<MaterialInstance> pMatIns = sri->GetHandle();
				//sri->SetMatID(pMatIns->GetMaterialID());
				if ( !bSave )
				{
					sri->SetSave(false);
				}
				renderableUnit.SetResInfo(sri);	

			}

		}
		else
		{
			if ( mRenderableResUnitList[iSubMesh].GetResInfo().isvalid())
			{
				ModifyMaterialShaderID(iSubMesh,shaderID);		
			} 
		}
	}
	//------------------------------------------------------------------------
	void
		RenderComponent::ModifyMaterialShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID)
	{
		if ( iSubMesh < 0 || !shaderID.IsValid() )
		{
			return;
		}

		if ( iSubMesh >= mRenderableResUnitList.Size() )
		{
			// 填充到iSubMesh的数量
			while( iSubMesh >= mRenderableResUnitList.Size() )
			{
				GPtr<Resources::MaterialResInfo> sri = ResourceManager::Instance()->CreateMaterialInfo(shaderID);

				mRenderableResUnitList.Append(RenderbleResUnit());
				RenderbleResUnit& renderableUnit = mRenderableResUnitList.Back();
				renderableUnit.SetResInfo(sri);	
				_DirtyMaterial(iSubMesh);
			}
		}
		else
		{
			if ( !mRenderableResUnitList[iSubMesh].GetResInfo().isvalid())
			{
				return;
			}
			GPtr<Resources::MaterialResInfo> oldMatResInfo = mRenderableResUnitList[iSubMesh].GetResInfo().downcast<Resources::MaterialResInfo>();
			if ( !oldMatResInfo->GetHandle().isvalid() )
			{
				return;
			}
			if ( GetShaderID(iSubMesh) != shaderID )
			{
				Resources::ResourceId matID = mRenderableResUnitList[iSubMesh].GetResInfo()->GetMatID();

				// modify
				GPtr<Resources::MaterialResInfo> sri  = ResourceManager::Instance()->ModifyMaterialInfo(matID,shaderID);

				RenderbleResUnit& renderableUnit = mRenderableResUnitList[iSubMesh];
				renderableUnit.SetResInfo(sri);	

				_DirtyMaterial(iSubMesh);
			} 
		}

	}
	//------------------------------------------------------------------------
	void RenderComponent::DelMaterial(IndexT iSubMesh)
	{
		if ( iSubMesh >= mRenderableResUnitList.Size() )
		{
			n_assert(0);
			return;
		}
		// erase material,not del from material manager,because it may be referenced at other
		mRenderableResUnitList.EraseIndex(iSubMesh);
	}

	//------------------------------------------------------------------------
	void 
		RenderComponent::_AddTextureParam( IndexT iSubMesh, const ShaderParamString& paramName, const Resources::ResourceId& _texID, Resources::Priority priority/* = 1*/)
	{
		n_assert( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() );

		if ( !paramName.IsValid() )
		{
			return;
		}
		const GPtr<MaterialInstance>& mat = GetMaterial(iSubMesh);
		if (mat.isvalid())
		{
			if (mActor && mActor->PriorityDefinition())
			{
				priority = mActor->GetPriority();
			}
			
			mat->SetTexture(paramName, _texID, priority);

 			if ( priority <= Resources::ResourcePriority::Synchronization )
 			{
				mat->AssignTexture(_texID);
			}
			
			mMatDirty = true;
		}
	}
	//------------------------------------------------------------------------
	void 
		RenderComponent::_ClearTextureParam( IndexT iSubMesh )
	{
		n_assert( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() );
		
		if ( GetMaterial(iSubMesh).isvalid() )
		{
			GetMaterial(iSubMesh)->ClearTextureCache();
		}

	}
	//------------------------------------------------------------------------
	SizeT 
		RenderComponent::GetTextureParamCount(IndexT iSubMesh) const
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() && GetMaterial(iSubMesh).isvalid() )
		{

			return GetMaterial(iSubMesh)->GetTextureParamCount();
		}		

		return 0;		
	}
	//------------------------------------------------------------------------
	const ShaderParamString& 
		RenderComponent::EnumTextureParam(IndexT iSubMesh, IndexT iParam) const
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() )
		{
			const GPtr<MaterialInstance>& material = GetMaterial(iSubMesh);
			if ( material.isvalid() )
			{
				if ( iParam >=0 && iParam < material->GetTextureParamCount() )
				{
					return material->GetTextureParamName( iParam );
				}
			}
		}

		return NullShaderParam;
	}
	//------------------------------------------------------------------------
	bool 
		RenderComponent::HasTextureParam(IndexT iSubMesh, const ShaderParamString& shaderparam ) const
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() )
		{
			if ( GetMaterial(iSubMesh).isvalid() )
			{
				return  GetMaterial(iSubMesh)->ContainsTextureParam(shaderparam);
			}
		}

		return false;
	}
	//------------------------------------------------------------------------
	void 
		RenderComponent::SetTexture( IndexT iSubMesh, const ShaderParamString& paramName, const Resources::ResourceId& texID, const Resources::Priority priority /* = 1*/)
	{
		if ( !texID.IsValid() )
		{
			return;
		}
		m_bAllTexLoaded = false;

		_AddTextureParam(iSubMesh, paramName, texID, priority);
	}
	//------------------------------------------------------------------------
	void RenderComponent::SetTexture(IndexT iSubMesh, const ShaderParamString& paramName, const RenderBase::TextureHandle& handle)
	{
		if (!handle.IsValid())
		{
			return;
		}
		GPtr<MaterialInstance>& mat = GetMaterial(iSubMesh);
		mat->SetTexture(paramName, handle);
	}
	//------------------------------------------------------------------------
	const Resources::ResourceId& 
		RenderComponent::GetTexture(IndexT iSubMesh, const ShaderParamString& paramName ) const
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() )
		{
			const GPtr<MaterialInstance>& material = GetMaterial(iSubMesh);
			if ( material.isvalid() )
			{
				IndexT findtex = material->GetTextureParamIndex( paramName );
				if ( findtex != InvalidIndex )
				{
					TextureResInfo* tri = material->GetTextureResInfo( findtex );
					return tri->GetResID();
				}
			}
		}
		return Resources::Resource::EmptyResID;
	}
	//------------------------------------------------------------------------
	void 
		RenderComponent::_SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Util::String& val)
	{
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

	//------------------------------------------------------------------------
	void 
		RenderComponent::SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Math::float4& val)
	{
		if (iSubMesh < 0 || iSubMesh >= mRenderableResUnitList.Size())
		{
			return;
		}
		const GPtr<MaterialInstance>& mat = GetMaterial(iSubMesh);
		mat->SetConstantParam(paramName, val);
	}

	//------------------------------------------------------------------------
	void 
		RenderComponent::SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Math::matrix44& val)
	{
		if (iSubMesh < 0 || iSubMesh >= mRenderableResUnitList.Size())
		{
			return;
		}
		const GPtr<MaterialInstance>& mat = GetMaterial(iSubMesh);
		mat->SetConstantParam(paramName, val);
	}

	void 
		RenderComponent::SetShaderConstantParam( IndexT iSubMesh, const ShaderParamString& paramName, const Math::scalar& val )
	{
		if (iSubMesh < 0 || iSubMesh >= mRenderableResUnitList.Size())
		{
			return;
		}
		const GPtr<MaterialInstance>& mat = GetMaterial(iSubMesh);
		mat->SetConstantParam(paramName, val);
	}

	void RenderComponent::ClearShaderConstantParams( IndexT iSubMesh )
	{
		n_assert ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() );
		GetMaterial(iSubMesh)->ClearConstantParamCache();
	}

	//------------------------------------------------------------------------
	SizeT 
		RenderComponent::GetShaderConstantParamCount(IndexT iSubMesh) const
	{
		if ( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() &&  GetMaterial(iSubMesh).isvalid())
		{
			return GetMaterial(iSubMesh)->GetConstantParamCount();
		}
		else
		{
			return 0;
		}
	}

	//------------------------------------------------------------------------
	const ShaderParamString& RenderComponent::EnumShaderConstantParam(IndexT iSubMesh, IndexT iParam) const
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

	const Util::String& RenderComponent::_GetShaderConstantParamValue(IndexT iSubMesh, const ShaderParamString& paramName ) const
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

	//------------------------------------------------------------------------
	Graphic::MaterialParameterType RenderComponent::GetShaderConstantParamValue(ShaderParamString& paramValue,const IndexT& iSubMesh, const ShaderParamString& paramName)
	{
			paramValue = _GetShaderConstantParamValue(iSubMesh,paramName);


			const MaterialParamList& mpl = GetMaterial(iSubMesh)->GetParamList();
			for (IndexT i = 0; i < mpl.Size(); ++i)
			{
				const MaterialParam& mp = *mpl[i];
				if (mp.GetName() == paramName.AsString())
				{
					return mp.GetType();
				}
			}
			return eMaterialParamInvailid;
		
	}
	//------------------------------------------------------------------------
	void RenderComponent::_SetActor(Actor* v)
	{
		Super::_SetActor(v);
		UpdateRenderLayer();
	}
	//------------------------------------------------------------------------
	void RenderComponent::_OnMoveAfter()
	{
		//empty
	}
	//------------------------------------------------------------------------
	void RenderComponent::_OnBeginFrame()
	{
		
		if ( mMatDirty )
		{
			bool hasMatDirty = false;
			
			for ( IndexT iMat = 0; iMat < mRenderableResUnitList.Size(); ++iMat )
			{
				GPtr<Graphic::MaterialInstance>& mat = GetMaterial(iMat);
				if (!mCanCreateMaterial)
				{
					mCanCreateMaterial = true;
					if (iMat < mRenderableResUnitList.Size() -1)
					{
						mCanCreateMaterial = false;
					}
					
				}
				if (!mat->IsAllLoaded())
				{
					m_bAllTexLoaded = false;
				}

				hasMatDirty |= mat->IsDirty();
			}

			mMatDirty = hasMatDirty;

			if (!mMatDirty)
			{
				m_bAllTexLoaded = true;
#ifndef __SCRIPT_COMMIT__
				mActor->Check_OnWillRenderObject_Bind();
#endif
			}
		}
		//_SetVisible(mbVisible);
		//_UpdateRenderQueue();
	}
	
	//------------------------------------------------------------------------
	void RenderComponent::_DirtyMaterial(IndexT iSubMesh )
	{
		n_assert( iSubMesh >= 0 && iSubMesh < mRenderableResUnitList.Size() );

		mMatDirty = true;

		//m_bAllTexLoaded = false;
	}
	//------------------------------------------------------------------------
	void RenderComponent::_ClearRenderResUnits()
	{
		mRenderableResUnitList.Clear();
	}
	//--------------------------------------------------------------------------------
	void RenderComponent::SetVisible( bool bVisible)
	{
		mVisible = bVisible;
	}
	//------------------------------------------------------------------------------
	bool RenderComponent::GetVisible()
	{
		return mVisible;
	}
	//------------------------------------------------------------------------
	void RenderComponent::SetCastShadow( bool bCastShadow )
	{
		mbCastShadow = bCastShadow;
	}
	//------------------------------------------------------------------------
	bool RenderComponent::GetCastShadow()
	{
		return mbCastShadow;
	}
	//------------------------------------------------------------------------
	void RenderComponent::SetReceiveShadow( bool bReceiveShadow )
	{
		mbReceiveShadow = bReceiveShadow;
	}
	//------------------------------------------------------------------------
	bool RenderComponent::GetReceiveShadow()
	{
		return mbReceiveShadow;
	}
	//------------------------------------------------------------------------
	void RenderComponent::_UpdateShadow()
	{
		
	}
	// copy from other component
	void RenderComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		CopyFrom_2(pComponent);

	}
	//------------------------------------------------------------------------
	void RenderComponent::CopyFrom_1( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;

		// 清除原有的数据
		{
			mRenderableResUnitList.Clear();
		}

		GPtr<RenderComponent> pSource = pComponent.downcast<RenderComponent>();

		SizeT matCount = pSource->GetShaderCount();
		for ( IndexT iShader = 0 ; iShader < matCount; ++iShader )
		{
			SetMaterialByShaderID( iShader, pSource->GetShaderID(iShader),true );

			SizeT texCount = pSource->GetTextureParamCount(iShader);
			for ( IndexT iTex = 0; iTex < texCount; ++iTex )
			{
				const ShaderParamString& paramName = pSource->EnumTextureParam(iShader, iTex);
				const Resources::ResourceId& resID = pSource->GetTexture(iShader, paramName);

				_AddTextureParam(iShader, paramName, resID );
			}

			SizeT constantCount = pSource->GetShaderConstantParamCount(iShader);
			for ( IndexT iParam = 0; iParam < constantCount; ++iParam )
			{
				const ShaderParamString& paramName = pSource->EnumShaderConstantParam(iShader, iParam);
				const Util::String& paramValue = pSource->_GetShaderConstantParamValue(iShader, paramName);

				_SetShaderConstantParam(iShader,  paramName, paramValue);
			}
		}

	}
	//------------------------------------------------------------------------
	void RenderComponent::CopyFrom_2( const GPtr<Component>& pComponent )
	{// 
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;

		// 清除原有的数据
		{
			mRenderableResUnitList.Clear();
		}

		GPtr<RenderComponent> pSource = pComponent.downcast<RenderComponent>();

		SizeT matCount = pSource->GetMaterialCount();
		for ( IndexT iMat = 0 ; iMat < matCount; ++iMat )
		{
			SetMaterialID( iMat, pSource->GetMaterialID(iMat),false );

			SizeT texCount = pSource->GetTextureParamCount(iMat);
			for ( IndexT iTex = 0; iTex < texCount; ++iTex )
			{
				const ShaderParamString& paramName = pSource->EnumTextureParam(iMat, iTex);
				const Resources::ResourceId& resID = pSource->GetTexture(iMat, paramName);

				_AddTextureParam(iMat, paramName, resID );
			}

			SizeT constantCount = pSource->GetShaderConstantParamCount(iMat);
			for ( IndexT iParam = 0; iParam < constantCount; ++iParam )
			{
				const ShaderParamString& paramName = pSource->EnumShaderConstantParam(iMat, iParam);
				const Util::String& paramValue = pSource->_GetShaderConstantParamValue(iMat, paramName);

				_SetShaderConstantParam(iMat,  paramName, paramValue);
			}
		}

		bool isReceiveShadow = pSource->GetReceiveShadow();
		bool isCastShadow = pSource->GetCastShadow();

		SetReceiveShadow( isReceiveShadow );
		SetCastShadow( isCastShadow );

	}

	//------------------------------------------------------------------------
	SizeT RenderComponent::GetShaderCount(void) const
	{
		return mRenderableResUnitList.Size();
	}
	//------------------------------------------------------------------------
	GPtr<Graphic::MaterialInstance>& RenderComponent::GetMaterial(IndexT index )
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
	const GPtr<Graphic::MaterialInstance>& RenderComponent::GetMaterial( IndexT index ) const
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
	bool RenderComponent::HaveMaterial(Resources::ResourceId& matID ) const
	{
		for ( IndexT i = 0; i < mRenderableResUnitList.Size(); i++ )
		{
			if ( mRenderableResUnitList[i].GetResInfo().isvalid() && mRenderableResUnitList[i].GetResInfo()->GetMatID() == matID)
			{
				return true;
			}

		}
		return false;
	}
	//--------------------------------------------------------------------------------
	void RenderComponent::SetupAllResource()
	{
		if (mActor->PriorityUndefinition())
			return;
		SizeT matCount = GetMaterialCount();
		for ( IndexT iMat = 0 ; iMat < matCount; ++iMat )
		{
			SetMaterialID( iMat, GetMaterialID(iMat),false );

			SizeT texCount = GetTextureParamCount(iMat);

			for ( IndexT iTex = 0; iTex < texCount; ++iTex )
			{
				const ShaderParamString& paramName = EnumTextureParam(iMat, iTex);
				const Resources::ResourceId& resID = GetTexture(iMat, paramName);

				_AddTextureParam(iMat, paramName, resID, mActor->GetPriority() );
			}

			SizeT constantCount = GetShaderConstantParamCount(iMat);
			for ( IndexT iParam = 0; iParam < constantCount; ++iParam )
			{
				const ShaderParamString& paramName = EnumShaderConstantParam(iMat, iParam);
				const Util::String& paramValue = _GetShaderConstantParamValue(iMat, paramName);

				_SetShaderConstantParam(iMat,  paramName, paramValue);
			}
		}
	}

	//--------------------------------------------------------------------------------
	bool RenderComponent::IsAllResourceLoaded()
	{
		//TODO
		return m_bAllTexLoaded;
	}

	//------------------------------------------------------------------------
	void RenderComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		for (int i = 0; i < mRenderableResUnitList.Size(); ++i)
		{
			const GPtr<Resources::MaterialResInfo>& matInfo = mRenderableResUnitList[i].GetResInfo();
			list.Append(ReferenceResource(matInfo->GetMatID(), Resources::RR_Material));
		}
		Super::GetReferenceResourceId(list);
	}

}
