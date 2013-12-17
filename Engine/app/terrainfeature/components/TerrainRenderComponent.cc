/****************************************************************************
This source file is part of OGRE
Copyright (c) 2000-2009 Torus Knot Software Ltd
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
#include "TerrainRenderComponent.h"
#include "terrainfeature/components/TerrainRenderObject.h"
#include "graphicsystem/GraphicSystem.h"
#include "graphicsystem/GraphicObjectManager.h"
#include "serialization/serializeserver.h"
#include "io/memorystream.h"
#include "io/filestream.h"

#include "terrainfeature/components/TerrainNodeFrameTraverser.h"
#include "graphicfeature/graphicsfeature.h"
#include "graphicfeature/components/cameracomponent.h"
#include "graphicfeature/components/meshrendercomponent.h"
#include "graphicsystem/Renderable/GraphicRenderer.h"
#include "resource/imageresloader.h"

#include "resource/imageres.h"
#include "graphicsystem/Material/materialinstance.h"
#include "rendersystem/base/Texture.h"

namespace App
{

	using namespace Graphic;
	using namespace RenderBase;
	using namespace Terrain;

	const char* sBaseTexParamName	= "_mainTex";
	const char* sColorTexParamName	= "_colorMap";
	const char* sControlParamName	= "_controlMap";

	const char* sLayerParamName		= "_blendMap";
	const char* sBlendIdxParamName	= "_blendIdx";
	const char* sUVParamName		= "_uvMap";

	const char* sBaseMapShaderID	= "sys:TerrainDiffuse.shader";				//base map use
	const char* sColorMapShderID	= "sys:TerrainColorMap.shader";			// color map use
	const char* sDefaultShaderID	= "sys:TerrainDefault.shader";
	const char* sTerrainDefaultTex		= "sys:TerrainDefault.dds";

	const char* sColorMapPath			= "asset:Terrain/";
	const char* sBaseMapPath			= "asset:Terrain/";
	const char* sControlMapPath			= "asset:Terrain/";

	const IndexT sBaseMapMaterialIdx	= 0;
	const IndexT sColorMapMaterialIdx	= 1;
	// first brush material number
	const IndexT sBrushIdxBase			= 2;						

	const IndexT sMaterialNumMax		= 102;

	__ImplementClass(TerrainRenderComponent, 'TRCP', RenderComponent);

	//------------------------------------------------------------------------------
	TerrainRenderComponent::TerrainRenderComponent()
		: m_RawResInfo(NULL),
		m_bIsResInfoDirty(false),
		m_PixelError(4.3f),
		m_BaseMapDis(1000.f), 
		mLMIndex (0xFFFF),
		mLMSize(1024),
		m_bIsHeightMapDirty(false),
		m_bIsTextureDirty(false),
		m_BaseHeight(0)
	{
		m_TerrainDataSource = Terrain::TerrainDataSource::Create();
		m_TerrainTree = TerrainNodeTree::Create();
	}
	//------------------------------------------------------------------------------
	TerrainRenderComponent::~TerrainRenderComponent()
	{}
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::SetupCallbacks()
	{
		n_assert(mActor);
		mActor->RegisterComponentCallback(this, MoveAfter);
		mActor->RegisterComponentCallback(this, BeginFrame);
		mActor->RegisterComponentCallback(this, OnFrame);
		Super::SetupCallbacks();
	}
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::_OnBeginFrame()
	{
		Super::_OnBeginFrame();

		// Load heightMap res, using fileHandle mode
		if (m_bIsResInfoDirty && m_RawResInfo && m_RawResInfo->GetRes())
		{
			SetNormalizeHeights(m_RawResInfo);
		}

		if(m_bIsHeightMapDirty)
		{
			// If heightMap is totally updated, rebuild all data
			_RebuildTerrainRenderData();

			m_bIsHeightMapDirty = false;
		}

		// Update shadow
		_UpdateShadow();
		return;
	}

	//------------------------------------------------------------------------------
	void TerrainRenderComponent::_OnFrame()
	{
		Super::_OnFrame();

		if(m_bIsTextureDirty)
		{
			bool allLoaded = true;
			int layerCount = _GetLayerMapCount();
			for(int layerIndex = 0; layerIndex < layerCount; ++layerIndex)
			{
				int matIndex = layerIndex + sBrushIdxBase;
				//check controlMap all loaded
				GPtr<Resources::TextureResInfo> pTexParam = NULL;
				pTexParam = _GetTextureParam(matIndex, sControlParamName);

				if ( !(pTexParam && pTexParam->GetRes() && pTexParam->GetRes()->GetState() == Resources::Resource::Loaded) )
					allLoaded = false;

				//check layerMap all loaded
				pTexParam = _GetTextureParam(matIndex, sLayerParamName);

				if ( pTexParam && pTexParam->GetRes() && pTexParam->GetRes()->GetState() == Resources::Resource::Loaded )
				{
					LayermapInfo layerInfo = m_TerrainDataSource->GetLayermap(layerIndex);
					layerInfo.resourceInfo = pTexParam;
					m_TerrainDataSource->SetLayermap(layerIndex,layerInfo);
					allLoaded &= true;
				}
				else
				{
					allLoaded = false;
				}
			}

			//check baseMap and colorMap loaded
			GPtr<Resources::TextureResInfo> pTexParam = NULL;
			pTexParam = _GetTextureParam(sBaseMapMaterialIdx, sBaseTexParamName);
			if ( !(pTexParam && pTexParam->GetRes() && pTexParam->GetRes()->GetState() == Resources::Resource::Loaded) )
				allLoaded = false;

			pTexParam = _GetTextureParam(sColorMapMaterialIdx, sColorTexParamName);
			if ( !(pTexParam && pTexParam->GetRes() && pTexParam->GetRes()->GetState() == Resources::Resource::Loaded) )
				allLoaded = false;

			if(allLoaded)
			{
				_UpdateColorMap();
				_UpdateBaseMap();

				m_bIsTextureDirty = false;
			}
			
		}
		
	}
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::_OnMoveAfter()
	{
		if (mActor != NULL)
		{
			TerrainRenderObjects::Iterator begin = m_RenderObjects.Begin();
			TerrainRenderObjects::Iterator end = m_RenderObjects.End();
			const matrix44& world = mActor->GetWorldTransform();
			m_TerrainWordTransform.set_position( world.get_position() );
			while (begin != end)
			{
				TerrainRenderObjectPtr& renderable = begin->Value();
				renderable->SetTransform(m_TerrainWordTransform);
				++begin;
			}
		}
	}
	//------------------------------------------------------------------------------

	void TerrainRenderComponent::OnActivate()
	{
		n_assert( mActor );
		if (GetTerrainName() != mActor->GetGUID().AsString())
		{
			n_error("Terrain Name error. Terrain guid = %s, parent actor guid = %s", GetTerrainName().AsCharPtr(), mActor->GetGUID().AsString().AsCharPtr());
		}
		const Math::matrix44& world = mActor->GetWorldTransform();
		m_TerrainWordTransform.set_position( world.get_position() );

		if(mVisible)
		{
			//when active, need rebuild all data
			m_bIsHeightMapDirty = true;

			//void _UpdateLodAndRender( Graphic::Camera* camera );
			Graphic::GraphicSystem::Instance()->m_BeforeDrawEvent+= Delegates::newDelegate(this, &TerrainRenderComponent::_UpdateLodAndRender);
		}


		Super::OnActivate();
	}
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::OnDeactivate()
	{
		if(mVisible)
		{
			_ClearRenderObjects();
			Graphic::GraphicSystem::Instance()->m_BeforeDrawEvent -= Delegates::newDelegate(this, &TerrainRenderComponent::_UpdateLodAndRender);
		}

		// deActive material
		Super::OnDeactivate();

		return;
	}
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::SetVisible(bool bVisible)
	{
		if(bVisible == mVisible)
			return;

		mVisible = bVisible;
		if (IsActive())
		{
			if (mVisible)
			{
				m_bIsHeightMapDirty = true;
				Graphic::GraphicSystem::Instance()->m_BeforeDrawEvent+= Delegates::newDelegate(this, &TerrainRenderComponent::_UpdateLodAndRender);
			}
			else
			{
				_ClearRenderObjects();
				Graphic::GraphicSystem::Instance()->m_BeforeDrawEvent -= Delegates::newDelegate(this, &TerrainRenderComponent::_UpdateLodAndRender);
			}
		}
	}
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::UpdateRenderLayer()
	{
		TerrainRenderObjects::Iterator begin = m_RenderObjects.Begin();
		TerrainRenderObjects::Iterator end = m_RenderObjects.End();
		LayerID layer_id = mActor->GetLayerID();
		while (begin != end)
		{
			TerrainRenderObjectPtr& renderable = begin->Value();
			if (renderable.isvalid())
			{
				renderable->SetLayerID(layer_id);
			}
			++begin;
		}
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::StandaloneRender(const GPtr<Graphic::Material>& customMat)
	{
		for ( TerrainRenderObjects::Iterator it = m_RenderObjects.Begin(); it != m_RenderObjects.End(); ++it )
		{
			TerrainRenderObjectPtr& renderObj = it->Value();
			if (!renderObj.isvalid())
			{
				continue;
			}
			if ( mRenderableResUnitList.Size() < 1 )
			{
				return;
			}
			Renderable* rdbl = mRenderableResUnitList[0].GetRenderable();
			GraphicRenderer::BeforeRender(rdbl, eCustomized, customMat.get_unsafe());
			renderObj->Render(rdbl, eCustomized, customMat.get_unsafe());

		}	
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		Util::Array<Util::String> allResIds;

		if( IsLMTextureHandleValid() )
		{
			LightmapName name;
			LightmapSetting::GetInstance().GetLightmap( mLMIndex, name);

			if ( name.IsValid() )
				list.Append(Resources::ReferenceResource(name, Resources::RR_Unknown));
		}

		if(GetRawResInfo().isvalid())
		{
			const Resources::ResourceId hightMap = GetRawResInfo()->GetResID();
			if(hightMap.IsValid())
			{
				list.Append(Resources::ReferenceResource(hightMap, Resources::RR_Unknown));
			}
		}


		Super::GetReferenceResourceId(list);
	}
	//------------------------------------------------------------------------------
	
	TerrainRenderComponent::TerrainRenderObjects TerrainRenderComponent::GetAllRenderObjects()
	{
		return m_RenderObjects;
	}

	
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::_UpdateShadow()
	{
		TerrainRenderObjects::Iterator begin = m_RenderObjects.Begin();
		TerrainRenderObjects::Iterator end = m_RenderObjects.End();

		bool isReceiveShadow = this->GetReceiveShadow();

		while (begin != end)
		{
			TerrainRenderObjectPtr& renderable = begin->Value();
			if (renderable.isvalid())
			{
				renderable->SetReceiveShadow( isReceiveShadow );
				renderable->SetCastShadow( false );
			}
			++begin;
		}
	}
	
	
	
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::_RebuildTerrainRenderData()
	{
		n_assert(m_TerrainDataSource.isvalid());
		n_assert(mActor);

		/// This part compute height data change
		// Clear first then Rebuild
		_ClearRenderObjects();
		RebuildAllNodes();		

		return;
	}

	//------------------------------------------------------------------------------
	void TerrainRenderComponent::_ClearRenderObjects()
	{
		TerrainRenderObjects::Iterator begin = m_RenderObjects.Begin();
		TerrainRenderObjects::Iterator end = m_RenderObjects.End();
		while (begin != end)
		{
			TerrainRenderObjectPtr& renderable = begin->Value();
			TerrainNode* node = renderable->GetTerrainNode();
			if ( node )
			{
				node->SetRenderObject(NULL);
			}

			renderable->Detach();
			++begin;
		}

		m_RenderObjects.Clear();
	}

	//------------------------------------------------------------------------------

	void TerrainRenderComponent::RebuildAllNodes()
	{
		n_assert(m_TerrainDataSource);
		n_assert(mActor);

		m_TerrainTree->RebuildAllNodes(m_TerrainDataSource);

		mActor->_UpdateLocalBBox();
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::CheckRenderables()
	{
		for (int i = 0; i < mRenderableResUnitList.Size(); ++i)
		{
			RenderbleResUnit& unit = mRenderableResUnitList[i];
			if (NULL == unit.GetRenderable())
			{
				unit.ResetRenderable<RenderObjectType::RenderableType>();
				_ResetRenderableMark(i);
			}
		}
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::_ResetRenderableMark(int index)
	{
		//mRenderableResUnitList[index].GetResInfo()->GetHandle()->SetID((Graphic::Material::ID)(Graphic::Material::ID_TerrainBegin + index));
		if (0 != index && sBrushIdxBase != index)
		{
			if (mRenderableResUnitList[index].GetRenderable())
			{
				mRenderableResUnitList[index].GetRenderable()->SetMark(Graphic::Renderable::MarkNone);
			}

		}
	}
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::_UpdateLodAndRender( Graphic::Camera* camera )
	{/*algorithm: see W. de Boer 2000 calculation
		formula: ¦Ñ=¦Ä.K/D 
				 K = viewPortH / ( 2*tan(fovy/2) )
	           => K = A*vph/2                   
			      and T = 2*maxPixError/vph (maxPixError: user set value,
				                                          example 1: delta error pixel number is 1 in screen space )
	           => cameraFacotr = A/T = K/maxPixError
	 */
	
		if (camera==NULL)
		{
			return;
		}

		int vpH	= camera->GetViewport().height;
		float A = 0.0f;
		if (camera->GetViewType() == Graphic::Camera::VT_ortho)
		{
			A = 1.f;
		}
		else
		{
			A = 1.f/Math::n_tan( (camera->GetCameraSetting().GetFov() / 2.0F) );
		}

	
		float T				= 2 * m_PixelError / (float)vpH;
		float cameraFactor	=  A / T;

		Math::vector cameraLocalPos = camera->GetTransform().get_position() - m_TerrainWordTransform.get_position();
		float squareNodeDistance = m_BaseMapDis * m_BaseMapDis;

		TerrainNode* root = m_TerrainTree->GetRootNode();
		if ( !root )
		{
			return;
		}

		/**
		* @Todo When camera moved or data update, do calculate                                                                    
		*/

		// Step1 according camera position compute LOD weight
		UpdateTerrainLodLevelTraverser updateLodLevelTraverser(cameraFactor, cameraLocalPos,  squareNodeDistance );
		root->Accept(updateLodLevelTraverser);

		LevelupNeighborLODTraverser levelupNeighborLodTraverser(cameraLocalPos,  squareNodeDistance);
		root->Accept(levelupNeighborLodTraverser);

		// Step2 compute edge Mask
		BuildEdgeMaskTraverser edgeMaskTraverser;
		root->Accept(edgeMaskTraverser);

		// Step3 for visible render data, update if need
		if ( m_TerrainDataSource.isvalid() )
		{
			BuildPrimitiveTraverser buildPriTraverser(m_TerrainDataSource);
			root->Accept(buildPriTraverser);
		}

		// Step4 add or remove GraphicObject
		BuildGraphicObjectTraverser goVisitor(this);
		root->Accept(goVisitor);

		return;
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::AttachNodeToRender(TerrainNode& node)
	{
		if ( node.GetRenderObject() )
		{
			return;
		}

		n_assert( GraphicObjectManager::HasInstance() );
		n_assert( GraphicSystem::HasInstance() );
		n_assert( mActor );
		
		int patchIndex  = m_TerrainDataSource->GetSectorIndex(node.x, node.y, node.level);
		node.bundleIndex = patchIndex;
		GPtr<RenderObjectType> renderobject = RenderObjectType::Create();

		renderobject->Set(this, &node, m_TerrainWordTransform );
		node.SetRenderObject(renderobject);

		n_assert( m_RenderObjects.FindIndex(patchIndex) == InvalidIndex);

		m_RenderObjects.Add(patchIndex, renderobject);
		renderobject->Attach(mActor->GetRenderScene());
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::DeattachNodeFromRender(TerrainNode& node)
	{
		if ( !node.GetRenderObject() )
		{
			return;
		}

		IndexT found = m_RenderObjects.FindIndex(node.bundleIndex);

		if (found != InvalidIndex)
		{
			TerrainRenderObjectPtr& obj = m_RenderObjects.ValueAtIndex(found);
			n_assert( &node == obj->GetTerrainNode() )
				node.SetRenderObject(NULL);
			node.SetNodeDrawMode(eNodeDrawParent);

			obj->Detach();
			m_RenderObjects.EraseAtIndex(found);
		}
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::OnRenderSceneChanged()
	{
		TerrainNode* node = GetRootNode();
		if (node)
		{
			node->ChangeRenderScene(mActor->GetRenderScene());
		}
	}

	//------------------------------------------------------------------------------
	void TerrainRenderComponent::SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy)
	{
		Super::SetMaterialID(iSubMesh, matID, bCopy);
		_ResetRenderableMark(iSubMesh);
	}

	void TerrainRenderComponent::SetMaterialByShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID,const bool bSave)
	{
		Super::SetMaterialByShaderID(iSubMesh, shaderID, bSave);
		_ResetRenderableMark(iSubMesh);
	}

	void TerrainRenderComponent::ModifyMaterialShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID)
	{
		Super::ModifyMaterialShaderID(iSubMesh, shaderID);
		_ResetRenderableMark(iSubMesh);
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::_ModifyTerrainMaterialDir(const Resources::ResourceId& oldMatID, Resources::ResourceId& outMatID)
	{
		Util::String strOldMatID= oldMatID.AsString();
		Util::String matFile = strOldMatID.ExtractFileName();
		outMatID = "asset:Terrain/" + matFile;
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::_SetMaterialTextureParam(IndexT matIndex, const ShaderParamString& paramName, const Resources::ResourceId& texID, Resources::Priority priority /*= 1*/)
	{
		if ( !GetMaterial(matIndex).isvalid() )
		{
			n_assert(0);
			return;
		}

		if (!HasTextureParam(matIndex, paramName))
		{
			_AddTextureParam(matIndex, paramName, sTerrainDefaultTex, priority);
		}

		SetTexture(matIndex, paramName, texID, priority);
	}

	//------------------------------------------------------------------------------
	void TerrainRenderComponent::_SetMaterialTileOffsetParam(IndexT matIndex, const ShaderParamString& paramName, const float4& value)
	{
		n_assert(matIndex >= sBrushIdxBase);

		SetShaderConstantParam(matIndex, paramName, value);

		int layerIndex = matIndex - sBrushIdxBase;

		float4 fBlendIdxParam;
		IndexT idx = layerIndex%4;
		if ( idx == 0 )
		{
			fBlendIdxParam.set(1.0f,0.f,0.f,0.f);
		} 
		else if ( idx == 1 )
		{
			fBlendIdxParam.set(0.f,1.f,0.f,0.f);
		} 
		else if ( idx == 2 )
		{
			fBlendIdxParam.set(0.f,0.f,1.f,0.f);
		} 
		else if ( idx == 3 )
		{
			fBlendIdxParam.set(0.f,0.f,0.f,1.f);
		}
		else
		{
			n_assert(0);		
		}
		SetShaderConstantParam(matIndex, sBlendIdxParamName, fBlendIdxParam);
	}

	//------------------------------------------------------------------------
	void TerrainRenderComponent::_UpdateLayerBlendIndex()
	{
		int layerCount = _GetLayerMapCount();

		n_assert(layerCount > 0);
		for (int layerIndex=0; layerIndex<layerCount; ++layerIndex)
		{
			float4 fBlendIndexParam;
			IndexT idx = layerIndex % 4;
			if ( idx == 0 )
			{
				fBlendIndexParam.set(1.0f,0.f,0.f,0.f);
			} 
			else if ( idx == 1 )
			{
				fBlendIndexParam.set(0.f,1.f,0.f,0.f);
			} 
			else if ( idx == 2 )
			{
				fBlendIndexParam.set(0.f,0.f,1.f,0.f);
			} 
			else if ( idx == 3 )
			{
				fBlendIndexParam.set(0.f,0.f,0.f,1.f);
			}
			else
			{
				n_assert(0);		
			}

			int matIndex = layerIndex + sBrushIdxBase;
			SetShaderConstantParam(matIndex, sBlendIdxParamName, fBlendIndexParam);
		}
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::_UpdataLayerControlMapName()
	{
		int layerCount = _GetLayerMapCount();

		n_assert(layerCount > 0);
		for (int layerIndex=0; layerIndex<layerCount; ++layerIndex)
		{
			int matIndex = layerIndex + sBrushIdxBase;
			int controlMapIndex = layerIndex / 4;
			const Util::String& newControlMapName = "asset:Terrain/" + GetControlMapName(controlMapIndex);

			GPtr<Resources::TextureResInfo> controlTexInfo = _GetTextureParam(matIndex, sControlParamName);
			if(newControlMapName != controlTexInfo->GetResID().AsString())
			{
				_SetMaterialTextureParam(matIndex, sControlParamName, newControlMapName, 0);
			}
		}
	}
	//------------------------------------------------------------------------

	Resources::TextureResInfo* TerrainRenderComponent::_GetTextureParam(IndexT matIndex, const Graphic::ShaderParamString& shdTexKey)
	{
		n_assert(matIndex<sMaterialNumMax);
		const GPtr<MaterialInstance>& materail = GetMaterial(matIndex);
		if (mRenderableResUnitList.Size() >= 0 && materail.isvalid())
		{
			IndexT foundIndex = materail->GetTextureParamIndex( shdTexKey );
			if ( foundIndex != InvalidIndex )
			{
				const GPtr<Resources::TextureResInfo>& texParam = materail->GetTextureResInfo( foundIndex );

				return texParam.get();			
			}
		}
		return NULL;
	}

	//------------------------------------------------------------------------
	int TerrainRenderComponent:: _GetLayerMapCount()
	{
		int cnt = GetMaterialCount() - sBrushIdxBase;
		if ( cnt < 0 )
		{// when basemap colormap material hasn't create.
			cnt = 0;
		}
		return cnt;
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::AddMaterialBrush(const Resources::ResourceId &matID, const Math::float2 &size, const Math::float2 &offset, const Resources::ResourceId &texID)
	{
		n_assert(matID.IsValid());
		if (!m_TerrainDataSource.isvalid())
		{
			n_warning("AddMaterialBrush():terrain data is null.");
			return;
		}

		IndexT matIdx = GetMaterialCount();

		// material of brush begin idx
		n_assert(matIdx >= sBrushIdxBase);	
		SetMaterialID(matIdx,matID,true);

		// put material in System contents to hide	
		Resources::ResourceId curMatID = GetMaterialID(matIdx);
		Resources::ResourceId newMatId;
		_ModifyTerrainMaterialDir(curMatID,newMatId);
		Resources::ResourceManager::Instance()->ModifyMaterialInstanceID(curMatID,newMatId);


		// Set texture brush's uv info
		float4 uvVal = _ConvertTileSizeToTileCount(size,offset);

		_SetMaterialTileOffsetParam(matIdx, sUVParamName, uvVal);

		// update diffuse
		Resources::TextureResInfo* pLayerTex = _GetTextureParam(matIdx,sLayerParamName);
		if ( !pLayerTex )
		{
			n_error("unknown terrain material!!");
			return;
		}
		Resources::ResourceId tmpTexID = pLayerTex->GetResID();

		if ( texID.IsValid() )
		{
			tmpTexID = texID;

			_SetMaterialTextureParam(matIdx,sLayerParamName, tmpTexID, 0);
		}

		_AddControlMaps();

		int layerIndex = matIdx - sBrushIdxBase;
		Terrain::LayermapInfo layerInfo;
		layerInfo.resourceInfo = pLayerTex;
		layerInfo.materialName = newMatId;
		layerInfo.layermapTileSize = size;
		layerInfo.layermapOffset = offset;
		m_TerrainDataSource->AddLayermap(layerIndex, layerInfo);

		CheckRenderables();

		m_bIsTextureDirty = true;
	}

	//------------------------------------------------------------------------------
	void TerrainRenderComponent::RemoveMaterialBrush(const int brushIndex)
	{
		n_assert(m_TerrainDataSource);
		n_assert(brushIndex != InvalidIndex);

		if ( brushIndex == 0 )
		{
			// default layer can not be delete, otherwise terrain will not be rendered
			return;
		}

		int matIndex = brushIndex + sBrushIdxBase;
		//first delete controlMap's unused data
		_DeleteControlMap(brushIndex);	

		int controlMapCout_Before = _GetLayerMapCount() / 4 + ((_GetLayerMapCount() % 4) != 0 ? 1 : 0);  
		// then del material
		DelMaterial(matIndex);

		int controlMapCout_Affter = _GetLayerMapCount() / 4 + ((_GetLayerMapCount() % 4) != 0 ? 1 : 0); 

		if(controlMapCout_Before - controlMapCout_Affter == 1)
		{
			m_TerrainDataSource->DelControlMap(controlMapCout_Before -1);
		}

		if(mVisible)
		{
			// delete layer related info 
			//(these render data will be attached when rebuild LOD data)
			_ClearRenderObjects();	
		}

		// update layer blendIndex
		_UpdateLayerBlendIndex();

		_UpdataLayerControlMapName();

		m_TerrainDataSource->DelLayermap(brushIndex);

		m_bIsTextureDirty = true;
	}

	//------------------------------------------------------------------------------

	void TerrainRenderComponent::ChangeBrushMaterial(const Resources::ResourceId &matID, IndexT brushIndex)
	{
		n_assert(matID.IsValid());
		//n_assert(mActor);

		if (!m_TerrainDataSource.isvalid())
		{
			n_warning("AddMaterialBrush():terrain data is null.");
			return;
		}

		const int matIdx = brushIndex+sBrushIdxBase;

		// Get old tex diffuse
		Resources::TextureResInfo* pLayerTex = _GetTextureParam(matIdx,sLayerParamName);
		if ( !pLayerTex )
		{
			n_error("unknown terrain material!!");
			return;
		}
		Resources::ResourceId oldLayerTexID = pLayerTex->GetResID();

		Resources::TextureResInfo* pControlTex = _GetTextureParam(matIdx,sControlParamName);
		if ( !pControlTex )
		{
			n_error("unknown terrain material!!");
			return;
		}
		Resources::ResourceId oldControlTexID = pControlTex->GetResID();

		//Get old uv info
		const Util::String& tileOffsetValue = _GetShaderConstantParamValue(matIdx, sUVParamName);
		float4 oldTilezOffset(0.0f,0.0f,0.0f,0.0f);
		if(!tileOffsetValue.IsEmpty())
		{
			oldTilezOffset = tileOffsetValue.AsFloat4();
		}

		//Get old material sortID(or instanceID) to make new material has same draw order
		GPtr<Graphic::MaterialInstance> matInstance = GetMaterial(matIdx);
		uint sortId = n_min(matInstance->GetInstanceID(),matInstance->GetSort());

		//Delete old material
// 		GPtr<Graphic::MaterialInstanceManager>& pManager = App::GraphicObjectManager::Instance()->GetMaterialInstanceManager();
// 		pManager->RemoveMaterialInstance(matInstance->GetMaterialID());

		//Create new material 
		n_assert(matIdx >= sBrushIdxBase);	// material of brush begin idx
		SetMaterialID(matIdx,matID,true);

		
		//Modfiy materialID to "asset:Terrain/" dir
		Resources::ResourceId curMatID = GetMaterialID(matIdx);
		Resources::ResourceId newMatId;
		_ModifyTerrainMaterialDir(curMatID,newMatId);
		Resources::ResourceManager::Instance()->ModifyMaterialInstanceID(curMatID,newMatId);

		//Set sortID to new material
		GPtr<Graphic::MaterialInstance> newMatInstance = GetMaterial(matIdx);
		newMatInstance->SetSort(sortId);

		// Set texture brush's uv info
		_SetMaterialTileOffsetParam(matIdx, sUVParamName, oldTilezOffset);

		// update diffuse
		if ( oldLayerTexID.IsValid() )
		{
			_SetMaterialTextureParam(matIdx,sLayerParamName, oldLayerTexID, 0);
		}
		// update controlMap
		if ( oldControlTexID.IsValid() )
		{
			_SetMaterialTextureParam(matIdx,sControlParamName, oldControlTexID, 0);
		}

		m_bIsTextureDirty = true;

		CheckRenderables();
	}

	
	void TerrainRenderComponent::ChangeBrushTexture( IndexT brushIndex, const ShaderParamString &paramName, const Resources::ResourceId &texID )
	{
		n_assert(texID.IsValid());
		//n_assert(mActor);

		if (!m_TerrainDataSource.isvalid())
		{
			n_warning("AddMaterialBrush():terrain data is null.");
			return;
		}

		IndexT matIndex = brushIndex + sBrushIdxBase;

		// material of brush begin idx
		n_assert(matIndex >= sBrushIdxBase);	

		// Get old tex diffuse
		Resources::TextureResInfo* pLayerTex = _GetTextureParam(matIndex,paramName);
		if ( !pLayerTex )
		{
			n_warning("unknown terrain material!!");
			return;
		}

		// update diffuse
		if ( texID.IsValid() )
		{
			_SetMaterialTextureParam(matIndex, paramName, texID, 0);
		}

		Terrain::LayermapInfo layerInfo = m_TerrainDataSource->GetLayermap(brushIndex);
		layerInfo.resourceInfo = pLayerTex;
		m_TerrainDataSource->SetLayermap(brushIndex, layerInfo);

		m_bIsTextureDirty = true;

		CheckRenderables();
	}

	//------------------------------------------------------------------------------
	void TerrainRenderComponent::ChangeBrushTileOffset(IndexT brushIndex, Math::float2 tileSize, Math::float2 offset)
	{
		n_assert(m_TerrainDataSource.isvalid());

		const int matIdx = brushIndex+sBrushIdxBase;

		// Set texture brush's uv info
		float4 uvValTileCnt = _ConvertTileSizeToTileCount(tileSize, offset);
		const Util::String uvparamString = sUVParamName ;

		_SetMaterialTileOffsetParam(matIdx, uvparamString, uvValTileCnt);

		Terrain::LayermapInfo layerInfo = m_TerrainDataSource->GetLayermap(brushIndex);
		layerInfo.layermapTileSize = tileSize;
		layerInfo.layermapOffset = offset;
		m_TerrainDataSource->SetLayermap(brushIndex, layerInfo);

		return;
	}

	//------------------------------------------------------------------------------

	bool TerrainRenderComponent::CheckBrushMaterialParam( IndexT brushIndex, const ShaderParamString &paramName )
	{
		if (!m_TerrainDataSource.isvalid())
		{
			n_warning("AddMaterialBrush():terrain data is null.");
			return false;
		}

		IndexT matIndex = brushIndex + sBrushIdxBase;
		n_assert(matIndex >= sBrushIdxBase);	// material of brush begin idx

		bool hasParam = HasTextureParam(matIndex, paramName);
		return hasParam;
	}

	//------------------------------------------------------------------------------

	Util::String TerrainRenderComponent::GetBrushMaterialID( IndexT brushIndex )
	{
		if (!m_TerrainDataSource.isvalid())
		{
			n_warning("AddMaterialBrush():terrain data is null.");
			return "";
		}

		IndexT matIndex = brushIndex + sBrushIdxBase;
		n_assert(matIndex >= sBrushIdxBase);	// material of brush begin idx

		Resources::ResourceId matID = GetMaterialID(matIndex);
		return matID.AsString();
	}

	Util::String TerrainRenderComponent::GetBrushTextureName( IndexT brushIndex, const ShaderParamString &paramName )
	{
		if (!m_TerrainDataSource.isvalid())
		{
			n_warning("AddMaterialBrush():terrain data is null.");
			return "";
		}

		IndexT matIndex = brushIndex + sBrushIdxBase;
		n_assert(matIndex >= sBrushIdxBase);	// material of brush begin idx

		Resources::TextureResInfo* pLayerTex = _GetTextureParam(matIndex,paramName);
		if ( !pLayerTex )
		{
			n_error("unknown terrain material!!");
			return "";
		}
		Resources::ResourceId texID = pLayerTex->GetResID();
		return texID.AsString();
	}


	Math::float4 TerrainRenderComponent::GetBrushTileOffset( IndexT brushIndex)
	{
		if (!m_TerrainDataSource.isvalid())
		{
			n_error("AddMaterialBrush():terrain data is null.");
		}

		IndexT matIndex = brushIndex + sBrushIdxBase;
		n_assert(matIndex >= sBrushIdxBase);	// material of brush begin idx

		const Util::String& paramValue = _GetShaderConstantParamValue(matIndex,"_uvMap");
		float4 val(0.0f, 0.0f, 0.0f, 0.0f);
		if(!paramValue.IsEmpty())
		{
			val = paramValue.AsFloat4();
			val = _ConvertTileCountToTileSize(float2(val.x(),val.y()),float2(val.z(),val.w()));
		}	
		return val;
	}

	
	//------------------------------------------------------------------------
	Math::float4 TerrainRenderComponent::_ConvertTileSizeToTileCount(const Math::float2& tileSize, const Math::float2& offset)
	{
		float4 val(0.0f, 0.0f, 0.0f, 0.0f);
		val.set_z( offset.x() / tileSize.x() ); 
		val.set_w( offset.y() / tileSize.y() );
		val.set_x( GetTerrainSize().x()/tileSize.x() );
		val.set_y( GetTerrainSize().z()/tileSize.y() );
		
		return val;
	}

	Math::float4 TerrainRenderComponent::_ConvertTileCountToTileSize(const Math::float2& tileCount, const Math::float2& offset)
	{
		float4 val(0.0f, 0.0f, 0.0f, 0.0f);
		val.set_x( GetTerrainSize().x()/tileCount.x() );
		val.set_y( GetTerrainSize().z()/tileCount.y() );
		val.set_z( offset.x() * val.x() ); 
		val.set_w( offset.y() * val.y() );
		
		return val;
	}
	//------------------------------------------------------------------------
	bool TerrainRenderComponent::_CreateControlMapTexture(Util::String mapName)
	{
		const IO::URI terrainPath("asset:Terrain");
		if (!IO::IoServer::Instance()->DirectoryExists(terrainPath))
		{
			bool bRet = IO::IoServer::Instance()->CreateDirectory(terrainPath);
			if ( !bRet )
			{
				return false;
			}
		}

		bool bCreated = m_TerrainDataSource->CreateControlMap(mapName);   

		return bCreated;
	}
	//------------------------------------------------------------------------------
	const Util::String TerrainRenderComponent::GetControlMapName(IndexT controlMapIdx)
	{
		Util::String name = GetTerrainName() + "_AlphaMap_" + Util::String::FromInt(controlMapIdx) + ".tga";
		return name;
	}
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::_AddControlMaps(void)
	{
		n_assert(m_TerrainDataSource);


		int layerCount = _GetLayerMapCount();

		bool bAllLoad = true;
		n_assert(layerCount > 0);

		Util::String lastControlMapName;
		for (int layerIndex=0; layerIndex<layerCount; ++layerIndex)
		{
			int matIndex = layerIndex + sBrushIdxBase;
			int controlMapIndex = layerIndex / 4;
			int curControlMapCount = m_TerrainDataSource->GetControlMapSize();

			const Util::String& newControlMapName = "asset:Terrain/" + GetControlMapName(controlMapIndex);
			
			if(controlMapIndex == curControlMapCount)
			{
				bool bCreated = _CreateControlMapTexture(newControlMapName);

				if(!bCreated)
				{
					n_warning("ControlMap %s created failed.\n",newControlMapName.AsCharPtr());
				}

				_SetMaterialTextureParam(matIndex, sControlParamName, newControlMapName, 0);

				GPtr<Resources::TextureResInfo> controlTexInfo = _GetTextureParam(matIndex, sControlParamName);

				m_TerrainDataSource->AddControlMap(controlTexInfo);
			}	

			GPtr<Resources::TextureResInfo> controlTexInfo = _GetTextureParam(matIndex, sControlParamName);
			if(newControlMapName != controlTexInfo->GetResID().AsString())
			{
				_SetMaterialTextureParam(matIndex, sControlParamName, newControlMapName, 0);
			}

		}

	}

	//------------------------------------------------------------------------
	void TerrainRenderComponent::_DeleteControlMap(const int layerIndex)
	{
		n_assert(m_TerrainDataSource.isvalid());

		if ( layerIndex >= _GetLayerMapCount())
		{
			return;
		}

		int numBeforeDel = _GetLayerMapCount();

		//Update controlMapData (When delete: move tunnels after deleted tunnel, and clear unused tunnel)
		m_TerrainDataSource->RefreshControlMap(layerIndex,numBeforeDel);
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::_UpdateBaseMap()
	{
		if (m_TerrainDataSource->IsValidBasemap() == false)
		{
			GPtr<Resources::TextureResInfo> pTexParam = NULL;
			pTexParam = _GetTextureParam(sBaseMapMaterialIdx,sBaseTexParamName);

			//if can not read new res, read old
			if ( !pTexParam )
			{
				pTexParam = _GetTextureParam(sBaseMapMaterialIdx,sBaseTexParamName);
			}

			if (pTexParam && pTexParam->GetRes() && pTexParam->GetRes()->GetState() == Resources::Resource::Loaded)
			{
				m_TerrainDataSource->SetBaseMap(pTexParam);
				m_TerrainDataSource->RefreshBasemap();
			}
		}
		else
		{
			m_TerrainDataSource->RefreshBasemap();
		}

	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::_UpdateColorMap()
	{
		if (m_TerrainDataSource->IsValidColormap() == false)
		{
			GPtr<Resources::TextureResInfo> pTexParam = _GetTextureParam(sColorMapMaterialIdx,sColorTexParamName);

			//if can not read new res, read old
			if ( !pTexParam )
			{
				pTexParam = _GetTextureParam(sColorMapMaterialIdx,sColorTexParamName);
			}
			if (pTexParam && pTexParam->GetRes() && pTexParam->GetRes()->GetState() == Resources::Resource::Loaded)
			{
				m_TerrainDataSource->SetColorMap(pTexParam);
			}
		}

	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::CreateBaseMap()
	{/*
	 * 1.create first material(idx=0) used by basemap 
	 * 2.create basemap res(.tga file)
	 */
		const IO::URI terrainPath("asset:Terrain");
		if (!IO::IoServer::Instance()->DirectoryExists(terrainPath))
		{
			IO::IoServer::Instance()->CreateDirectory(terrainPath);
		}

		Util::String fileName = GetTerrainName() + "_BaseMap";
		fileName = sBaseMapPath + fileName;

		GPtr<Resources::TextureResInfo> pTexParam = _GetTextureParam(0,sBaseTexParamName);
		if (pTexParam && pTexParam->GetResID() == fileName)
		{
			n_error("material 0 of own this tex had be create!!");
			return;
		}

		m_TerrainDataSource->CreateBaseMap(fileName);

		// parma save = false ,avoid user modify material
		SetMaterialByShaderID(sBaseMapMaterialIdx, sBaseMapShaderID,true);		

		Resources::ResourceId curMatID = GetMaterialID(sBaseMapMaterialIdx);
		Resources::ResourceId newMatId;
		_ModifyTerrainMaterialDir(curMatID,newMatId);
		Resources::ResourceManager::Instance()->ModifyMaterialInstanceID(curMatID,newMatId);

		// first add an default tex
		if (!HasTextureParam(sBaseMapMaterialIdx, sBaseTexParamName))
		{
			_AddTextureParam(sBaseMapMaterialIdx, sBaseTexParamName, sTerrainDefaultTex);
		}

		// change tex param
		SetTexture(sBaseMapMaterialIdx, sBaseTexParamName, fileName.Get());		// asynchronous load tex


		if ( !m_TerrainDataSource.isvalid())
		{
			n_assert(0);
			return;
		}
		pTexParam = _GetTextureParam(0,sBaseTexParamName);
		m_TerrainDataSource->SetBaseMap(pTexParam);
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::CreateColorMap()
	{// create second material(idx =1) used by colormap
		const IO::URI terrainPath("asset:Terrain");
		if (!IO::IoServer::Instance()->DirectoryExists(terrainPath))
		{
			IO::IoServer::Instance()->CreateDirectory(terrainPath);
		}

		Util::String fileName = GetTerrainName() + "_ColorMap";
		Util::String resId = sColorMapPath + fileName;
		GPtr<Resources::TextureResInfo> pTexParam = _GetTextureParam(1,sColorTexParamName);
		if (pTexParam && pTexParam->GetResID() == resId)
		{
			n_error("material 1 of own this tex had be create!!");
			return;
		}

		m_TerrainDataSource->CreateColorMap(resId);	

		// parma save = false ,avoid user modify material
		SetMaterialByShaderID(sColorMapMaterialIdx, sColorMapShderID,true);		

		Resources::ResourceId curMatID = GetMaterialID(sColorMapMaterialIdx);
		Resources::ResourceId newMatId;
		_ModifyTerrainMaterialDir(curMatID,newMatId);
		Resources::ResourceManager::Instance()->ModifyMaterialInstanceID(curMatID,newMatId);

		// first add an default tex
		if (!HasTextureParam(sColorMapMaterialIdx, sColorTexParamName))
		{
			_AddTextureParam(sColorMapMaterialIdx, sColorTexParamName, sTerrainDefaultTex);
		}

		// change tex param
		SetTexture(sColorMapMaterialIdx, sColorTexParamName, resId);		// asynchronous load tex


		if ( !m_TerrainDataSource.isvalid())
		{
			n_assert(0);
			return;
		}
		pTexParam = _GetTextureParam(1,sColorTexParamName);
		m_TerrainDataSource->SetColorMap(pTexParam);
	}
	
	//------------------------------------------------------------------------------
	void TerrainRenderComponent::SaveTerrainFile(void)
	{
		n_assert(mActor);
		n_assert(m_TerrainDataSource);

		Util::String name = "asset:Terrain/" + GetTerrainName();


		// save control map
		m_TerrainDataSource->SaveControlMap();

		// save base map
		m_TerrainDataSource->SaveBaseMap();

		// save color map
		m_TerrainDataSource->SaveColorMap();


		int heightMapSize = m_TerrainDataSource->GetHeightMapSize();
		LocalYArray localHeights(heightMapSize, heightMapSize,0);
		m_TerrainDataSource->GetLocalYArrayByUnit(0,0,heightMapSize, heightMapSize,localHeights);
		void* ptrLocal = localHeights.Begin();
		SizeT sizeWrite = sizeof(uint16)*heightMapSize*heightMapSize;

		// maybe heightmap data save looks like some confused,
		// actually it solved for issue (one bug: open scene again when editor is opened)
		// 
		// 1.save data to disk; 
		// 2.sync heightdata to resinfo,make sure disk and memeory(resinfo)is the same
		// 3. because 2 only happened load one terrain,so when create one terrain,
		//    we use this method create resinfo and reload
		{// 1.save disk		

			// save terrain heightmap to a file
			GPtr<IO::BinaryWriter> pWriter = IO::BinaryWriter::Create();
			pWriter->SetStreamByteOrder(System::ByteOrder::LittleEndian);
			GPtr<IO::Stream> dstStream = IO::IoServer::Instance()->CreateFileStream(name + ".xraw");
			if (pWriter && dstStream)
			{
				dstStream->SetAccessMode(IO::Stream::WriteAccess);
				if (dstStream->Open())
				{
					pWriter->SetStream( dstStream );
					if ( !pWriter->Open() )
					{
						n_warning("SaveTerrainFile(): open height map file error!");
						return;
					}		    		

					pWriter->WriteRawData(ptrLocal,sizeWrite);
					dstStream->Close();
					pWriter->Close();
				}
			}
		}
		//2.write back to memory(resinfo)
		if (m_RawResInfo)
		{
			const GPtr<Resources::RawRes> &rawRes = m_RawResInfo->GetRes().downcast<Resources::RawRes>();
			n_assert(rawRes.isvalid());
			Memory::Copy(ptrLocal,rawRes->Ptr(),sizeWrite);
		}
		//3. make resinfo
		const Util::String hightMapRes = "asset:Terrain/" + GetTerrainName() +".xraw";
		SetRawResID(hightMapRes, 0);


		return;
	}
	//------------------------------------------------------------------------------
	float3 TerrainRenderComponent::GetTerrainSize(void)  const
	{
		Math::float3 ratio = m_TerrainDataSource->GetTerrainRatio();
		int heightMapSize = m_TerrainDataSource->GetHeightMapSize() - 1;
		Math::float3 terrainSize(ratio.x()*heightMapSize, ratio.y()*MaxLocalY, ratio.z()*heightMapSize);

		return terrainSize;
	}

	//------------------------------------------------------------------------------
	void TerrainRenderComponent::SetTerrainSize(const float3& size)
	{
		n_assert(m_TerrainDataSource.isvalid());
		Math::float2 terrainScale(0.0f,0.0f);
		terrainScale.x() = size.x() / (m_TerrainDataSource->GetHeightMapSize() - 1);
		terrainScale.y() = size.z() / (m_TerrainDataSource->GetHeightMapSize() - 1);
		float heightScale = size.y() / MaxLocalY;

		Math::float3 ratio(terrainScale.x(),heightScale,terrainScale.y());
		m_TerrainDataSource->SetTerrainRatio(ratio);
		if(mVisible)
		{
			m_bIsHeightMapDirty = true;
		}

		return;
	}

	//------------------------------------------------------------------------------
	int TerrainRenderComponent::GetResolution(void)  const
	{
		n_assert(m_TerrainDataSource.isvalid());

		return m_TerrainDataSource->GetHeightMapSize();
	}

	//------------------------------------------------------------------------------
	void TerrainRenderComponent::SetResolution(int resolution)
	{
		int nextPowerOfTwo = Math::n_nexPowerOfTwo(resolution -1);
		n_assert(m_TerrainDataSource.isvalid());

		m_TerrainDataSource->ResetHeightmpData(nextPowerOfTwo);

		if(mVisible)
		{
			//	if MipMap level changed, Node and Renderable should be destroyed
			_ClearRenderObjects();
			m_bIsHeightMapDirty = true;
		}

		m_TerrainTree->Reset();


		return;
	}
	//------------------------------------------------------------------------
	const int TerrainRenderComponent::GetBaseHeight()
	{
		return m_BaseHeight;
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::SetBaseHeight(int baseHeight)
	{
		m_BaseHeight = baseHeight;
	}

	//------------------------------------------------------------------------
	void TerrainRenderComponent::ResetTerrainSetting(const TerrainSettings& settings)
	{/*Note:
	 * any data's change in setting, will cause whole terrain's update, and this operation happened not often, so compute all
	 */
		float3 size;
		size.x() = settings.width;
		size.y() = settings.topheight;
		size.z() = settings.length;

		//Update=====================================================
		SetBaseHeight((int)settings.baseheight);

		// Clear data
		if(mVisible)
		{
			_ClearRenderObjects();
			m_bIsHeightMapDirty = true;
		}
		m_TerrainTree->Reset();	

		/*
		*  Update new data
		*/
		SetTerrainSize(size);  // size's update need HeightMap's size, should update after _ResetHeightmapAttr()
		_RebuildTerrainRenderData();	

		// Material
		SizeT layerCount = _GetLayerMapCount();	
		for ( IndexT layerIndex = 0; layerIndex < layerCount; layerIndex++ )
		{
			LayermapInfo layerInfo = m_TerrainDataSource->GetLayermap(layerIndex);
			ChangeBrushTileOffset(layerIndex,  layerInfo.layermapTileSize, layerInfo.layermapOffset);
		}

		// update baseMap
		n_assert(m_TerrainDataSource.isvalid());
		m_TerrainDataSource->RefreshBasemap();

	}
	//------------------------------------------------------------------------------
	/// Get Height
	void TerrainRenderComponent::GetNormalizeHeights(int xStart, int yStart, int width, int height, Terrain::NormalizeLocalYArray& heights) const
	{
		n_assert(m_TerrainDataSource.isvalid());

		m_TerrainDataSource->GetNormalizeLocalYArrayByUnit(xStart, yStart, width, height, heights);

		return;
	}

	/// Get Height
	void TerrainRenderComponent::GetNormalizeHeights(int xStart, int yStart, int width, int height, float* heights) const
	{
		n_assert(m_TerrainDataSource.isvalid());
		Terrain::NormalizeLocalYArray height_array;
		height_array.Resize(width, height);
		GetNormalizeHeights(xStart,yStart,width,height,height_array);

		for ( Terrain::NormalizeLocalYArray::Iterator itor = height_array.Begin();
			itor != height_array.End();
			++itor, ++heights
			)
		{
			(*heights) = (*itor);
		}

		return;
	}
	//------------------------------------------------------------------------------
	/// Set Height
	void TerrainRenderComponent::SetNormalizeHeights(int xStart, int yStart, int width, int height, const Terrain::NormalizeLocalYArray& heights, bool forceMaxError)
	{
		if ( !m_TerrainDataSource.isvalid() )
		{
			return;
		}

		int heightMapSize = m_TerrainDataSource->GetHeightMapSize();
		if ( xStart < 0 || xStart >= heightMapSize || xStart + width >  heightMapSize
			|| yStart < 0 || yStart >= heightMapSize || yStart + height > heightMapSize ) 
		{
			return;
		}

		if ( width > heights.RowSize() || height > heights.ColSize() )
		{
			return;
		}

		m_TerrainDataSource->SetNormalizeLocalYArrayByUnit(xStart, yStart, width, height, heights);	

		if(forceMaxError)
			m_TerrainDataSource->ResetSectorInfo(xStart,yStart,width,height);
		else
			m_TerrainDataSource->CalculateSectorInfoDataByUnit(xStart,yStart,width,height);

		_RequestRebuildEffecedNodePrimitive(xStart, yStart, width, height);
		return;
	}
	void TerrainRenderComponent::SetNormalizeHeights(int xStart, int yStart, int width, int height, const float* heights, bool forceMaxError)
	{
		if ( !m_TerrainDataSource.isvalid() )
		{
			return;
		}

		int heightMapSize = m_TerrainDataSource->GetHeightMapSize();
		if ( xStart < 0 || xStart >= heightMapSize || xStart + width >  heightMapSize
			|| yStart < 0 || yStart >= heightMapSize || yStart + height > heightMapSize ) 
		{
			return;
		}

		Terrain::NormalizeLocalYArray heightArray;
		heightArray.Resize(width, height);

		for ( Terrain::NormalizeLocalYArray::Iterator itor = heightArray.Begin();
			itor != heightArray.End() ;++itor, ++heights)
		{
			(*itor) = (*heights);
		}

		SetNormalizeHeights(xStart,yStart,width,height,heightArray,forceMaxError);
	}

	void TerrainRenderComponent::SetNormalizeHeights(GPtr<Resources::RawResInfo> &pInfo)
	{
		n_assert(m_TerrainDataSource);
		n_assert(pInfo);

		const GPtr<Resources::RawRes> &rawRes = pInfo->GetRes().downcast<Resources::RawRes>();
		if (rawRes->Ptr() == NULL)
		{
			return;
		}

		m_bIsResInfoDirty = false;

		const int heightMapW = m_TerrainDataSource->GetHeightMapSize();
		const int heightMapH = m_TerrainDataSource->GetHeightMapSize();

		if (rawRes->Size() != heightMapW * heightMapH)
		{
			return;
		}

		Terrain::LocalYArray heights;
		heights.Resize(heightMapH, heightMapW, 0 );

		uint16 *lvalue = rawRes->Ptr();
		Terrain::LocalYArray::Iterator itor = heights.Begin();

		for (int i=0; i<rawRes->Size(); ++i, ++lvalue,++itor)
		{
			(*itor) = *lvalue;
		}
		m_TerrainDataSource->BuildHeightmpData(heightMapH,heights);
		if(mVisible)
		{
			m_bIsHeightMapDirty = true;
		}

		return;
	}


	void TerrainRenderComponent::ResetHeightLOD( int xStart, int yStart, int width, int height, bool heightChange, bool HoleChange)
	{
		m_bIsHeightMapDirty = true;
		m_TerrainDataSource->CalculateSectorInfoDataByUnit(xStart,yStart,width,height);
	}
	//------------------------------------------------------------------------------

	float TerrainRenderComponent::GetWorldYAtActorCoord( float fX, float fZ, int level /*= 0*/ ) const
	{
		float3 terrainSize = GetTerrainSize();
		float heightMapU = fX / terrainSize.x();
		float heightMapV = fZ / terrainSize.z();
		float fHeightMapX = heightMapU * ((m_TerrainDataSource->GetHeightMapSize() >> level) - 1);
		float fHeightMapZ = heightMapV * ((m_TerrainDataSource->GetHeightMapSize() >> level) - 1);

		int heightMapX = (int)fHeightMapX;
		int heightMapZ = (int)fHeightMapZ;

		float lerpU = fHeightMapX - heightMapX;
		float lerpV = fHeightMapZ - heightMapZ;

		return m_TerrainDataSource->GetWorldYByUnit(heightMapX,heightMapZ,lerpU,lerpV,level);
	}

	//------------------------------------------------------------------------------
	const Util::String& TerrainRenderComponent::GetTerrainName(void) const
	{
		return m_TerrainName;
	}

	//------------------------------------------------------------------------------
	void TerrainRenderComponent::SetTerrainName(const Util::String &name)
	{
		m_TerrainName = name;
	}

	//------------------------------------------------------------------------------
	bool TerrainRenderComponent::SetRawResID(const Resources::ResourceId& resId, Resources::Priority priority)
	{
		n_assert(m_TerrainDataSource);
		if (mActor && mActor->PriorityDefinition())
		{
			priority = mActor->GetPriority();
		}

		m_RawResInfo = Resources::ResourceManager::Instance()->CreateRawResInfo(resId, priority);
		
		m_bIsResInfoDirty = true;

		if (priority == 0)
		{
			SetNormalizeHeights(m_RawResInfo);

			m_bIsResInfoDirty = false;
		}

		m_bIsHeightMapDirty = true;

		return true;
	}
	



	
	//------------------------------------------------------------------------
	void TerrainRenderComponent::_RequestRebuildEffecedNodePrimitive(int x,int y,int w,int h)
	{
		n_assert(m_TerrainDataSource.isvalid());

		int xBegin = x - 1;
		int yBegin = y - 1;
		int xEnd = x + w + SectorSize;
		int yEnd = y + h + SectorSize;

		xBegin = Math::n_max(0, xBegin);
		yBegin = Math::n_max(0, yBegin);

		RequestBuildNodeAndParentTraverser requestVisitor(m_TerrainDataSource);

		for ( IndexT row = xBegin; row <= xEnd; row+=UnitsInSector )
		{
			for ( IndexT col = yBegin; col <= yEnd; col+= UnitsInSector )
			{
				int xPatch = int(row / UnitsInSector);
				int yPatch = int(col / UnitsInSector);
				TerrainNode* node = m_TerrainTree->GetNode(xPatch,yPatch,0);
				if ( node )
				{
					node->Accept( requestVisitor );
				}
			}
		}

		if (mActor)
		{
			mActor->_UpdateLocalBBox();
		}
	}
	
	//------------------------------------------------------------------------
	int GetEffectedNodeNum(int x,int w)
	{	
		if ( w < 1 )
		{
			n_assert(0);
			return 0;
		}

		int first = 1;

		int mod = x%UnitsInSector ;
		int nTemp = (w - (UnitsInSector  - mod));
		int mid	  = nTemp/UnitsInSector ;
		int last  = nTemp <= 0 ? 0 : ((nTemp%UnitsInSector  != 0) ? 1: 0 );

		return first + mid + last;
	}


	//------------------------------------------------------------------------
	bool TerrainRenderComponent::MakeHole(int holeX, int holeY, int holeW, int holeH,const Terrain::HoleDataArray& dataArray)
	{
		for (int y=0;y<holeH;y++)
		{
			for (int x=0;x<holeW;x++)
			{
				IndexT xGrid = x + holeX;
				IndexT yGrid = y + holeY;
				uchar val = dataArray.At(x,y);				
				_SetBitMasks(xGrid,yGrid,1,1,val);
				
			}
		}
		// rebuild effected node
		_RequestRebuildEffecedNodePrimitive(holeX,holeY,holeW,holeH);	
		return true;
	}
	//------------------------------------------------------------------------
	bool TerrainRenderComponent::MakeHole(int holeX, int holeY, int holeW, int holeH ,uchar val)
	{
		_SetBitMasks(holeX,holeY,holeW,holeH,val);

		// rebuild effected node
		_RequestRebuildEffecedNodePrimitive(holeX,holeY,holeW,holeH);	
		return true;
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponent::_SetBitMasks(int holeX, int holeY, int holeW, int holeH,uchar val)
	{
		n_assert(m_TerrainDataSource.isvalid());

		for (int y=0;y<holeH;y++)
		{
			for (int x=0;x<holeW;x++)
			{
				IndexT xGrid = x + holeX;
				IndexT yGrid = y + holeY;
				m_TerrainDataSource->SetHoleDataByUnit(xGrid,yGrid,val);
			}
		}

	}
	//------------------------------------------------------------------------
	bool TerrainRenderComponent::IsHole(int holeX, int holeY)
	{
		return m_TerrainDataSource->GetHoleDataByUnit(holeX,holeY) == 1 ? true: false;
	}
	
	//------------------------------------------------------------------------
	void TerrainRenderComponent::SetBrushColor( IndexT brushIndex, Math::ColorF color )
	{
		if (brushIndex < 0)
		{
			return;
		}
		m_BrushColor = color;
	}
	//------------------------------------------------------------------------
	Math::ColorF TerrainRenderComponent::GetBrushColor( IndexT brushIndex )
	{
		Math::ColorF result(0,0,0,0);
		if (brushIndex < 0)
		{
			return result;
		}

		return m_BrushColor;
	}

	//------------------------------------------------------------------------
	Terrain::LayermapInfo TerrainRenderComponent::GetBrushSetting(const int brushIndex)
	{
		n_assert(brushIndex >=0);
		int matIndex = brushIndex + sBrushIdxBase;
		LayermapInfo layerInfo;
		layerInfo.materialName = GetMaterialID(matIndex);
		layerInfo.resourceInfo = _GetTextureParam(matIndex, sLayerParamName);
		const Util::String tileOffset = _GetShaderConstantParamValue(matIndex, sUVParamName);
		float4 val(0.0f, 0.0f, 0.0f, 0.0f);
		if(!tileOffset.IsEmpty())
		{
			val = tileOffset.AsFloat4();
			val = _ConvertTileCountToTileSize(float2(val.x(),val.y()),float2(val.z(),val.w()));
		}
		layerInfo.layermapOffset = Math::float2(val.x(), val.y());
		layerInfo.layermapOffset = Math::float2(val.z(), val.w());

		return layerInfo;
	}

}//namespace App
