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

#pragma once

#ifndef __TERRAINRENDERCOMPONENT_H__
#define __TERRAINRENDERCOMPONENT_H__

#include "graphicfeature/components/rendercomponent.h"
#include "graphicsystem/Material/materialinstance.h"
#include "appframework/actor.h"
#include "graphicsystem/Camera/Camera.h"
#include "resource/rawres.h"
#include "terrainfeature/components/TerrainNodeTree.h"
#include "terrainsystem/TerrainDataSource.h"

#include "Lightmap/lightmapSetting.h"

namespace App
{
	const int sMaxControlMapSizeSize = 32;

	struct TerrainSettings
	{
	public:
		TerrainSettings():width(0.0f),length(0.0f),topheight(0.0f),baseheight(0.0f),heightmapRes(0.0f)
		{}

		float width;
		float length;
		float topheight;
		float baseheight;
		float heightmapRes;//heightMap resolution

	};

	class TerrainRenderObject;
	class TerrainRenderComponent: public RenderComponent
	{
		__DeclareSubClass(TerrainRenderComponent, RenderComponent);

	public:
		typedef TerrainRenderObject RenderObjectType;
		typedef GPtr<RenderObjectType> TerrainRenderObjectPtr;
		typedef Util::Dictionary<IndexT, TerrainRenderObjectPtr> TerrainRenderObjects;

	public:
		TerrainRenderComponent();
		virtual ~TerrainRenderComponent();

	protected:
		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		virtual void OnRenderSceneChanged();

		/// @Component::_OnBeginFrame called after movement has happened. 
		virtual void _OnBeginFrame();

		/// called before rendering happens
		virtual void _OnFrame();

		/// @Component::Component called after movement has happened. 
		virtual void _OnMoveAfter();

	public:
		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		virtual void UpdateRenderLayer();

		virtual void StandaloneRender(const GPtr<Graphic::Material>& customMat);

		virtual void SetMaterialID( IndexT iSubMesh, const Resources::ResourceId& matID,const bool bCopy = false );

		virtual void SetMaterialByShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID,const bool bSave = true );

		virtual void ModifyMaterialShaderID( IndexT iSubMesh, const Resources::ResourceId& shaderID);

		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		virtual void SetVisible(bool bVisible);

	protected:
		Resources::TextureResInfo* _GetTextureParam(IndexT index,const Graphic::ShaderParamString& shdTexKey);
		void _SetMaterialTextureParam(IndexT matIndex, const ShaderParamString& paramName, const Resources::ResourceId& texID, Resources::Priority priority = Resources::ResourcePriority::TextureDefault);
		/// Set texture's tileSize and tileOffset
		void _SetMaterialTileOffsetParam(IndexT index, const ShaderParamString& paramName, const Math::float4& value);
		void _ModifyTerrainMaterialDir(const Resources::ResourceId& oldMatID,Resources::ResourceId& outMatID);


		//===============================================================================================================
		//TerrainData
	public:
		GPtr<Terrain::TerrainDataSource>& GetTerrainDataSource(void) { return m_TerrainDataSource; }
		const GPtr<Terrain::TerrainDataSource>& GetTerrainDataSource(void) const { return m_TerrainDataSource; }

		//Get for intersect
		TerrainNode* GetRootNode(){return m_TerrainTree->GetRootNode();}
		RenderBase::PrimitiveTopology::Code GetPrimitiveTopology(void) const;
	
	protected:
		GPtr<Terrain::TerrainDataSource> 	m_TerrainDataSource;  // Terrain's data
		GPtr<TerrainNodeTree>       m_TerrainTree;	//	manage terrain's LOD Node and render data
		Math::matrix44				m_TerrainWordTransform;	//	terrain's world transform, can only translate, can not scale or rotate


		//===============================================================================================================
		//TerrainRender
	public:
		void AttachNodeToRender(TerrainNode& node);

		void DeattachNodeFromRender(TerrainNode& node);

		void RebuildAllNodes();

		void CheckRenderables();//called after material being setted

		// Get all terrain renderobject
		TerrainRenderComponent::TerrainRenderObjects GetAllRenderObjects();

	protected:
		void _ResetRenderableMark(int index);

		void _ClearRenderObjects();	

		virtual void _UpdateShadow();

		/// check need or not update heightmap
		void _RebuildTerrainRenderData();

		//  When height,hole data changed, call this to rebuild render data
		void _RequestRebuildEffecedNodePrimitive(int x,int y,int w,int h);

	protected:
		TerrainRenderObjects		m_RenderObjects;

		bool						m_bIsHeightMapDirty;

		//===============================================================================================================
		//TerrainSetting
	public:
		void ResetTerrainSetting(const TerrainSettings& settings);

		const Util::String& GetTerrainName(void) const;
		void SetTerrainName(const Util::String &name);

		Math::float3 GetTerrainSize(void) const;
		void SetTerrainSize(const Math::float3& size);

		int GetResolution(void) const;
		void SetResolution(int resolution);

		const int  GetBaseHeight();
		void SetBaseHeight(int baseHeight);
		
	protected:
		Util::String m_TerrainName;
		int m_BaseHeight;
		//===============================================================================================================
		//HeightMap
	public:
		bool SetRawResID(const Resources::ResourceId& resId, Resources::Priority priority = Resources::ResourcePriority::Synchronization);
		const GPtr<Resources::RawResInfo> &GetRawResInfo(void) const { return m_RawResInfo; }

		/// Get normalized rawHeight
		void GetNormalizeHeights(int xStart, int yStart, int width, int height, Terrain::NormalizeLocalYArray& heights) const;
		void GetNormalizeHeights(int xStart, int yStart, int width, int height, float* heights) const;

		/// Set normalized rawHeight
		void SetNormalizeHeights(int xStart, int yStart, int width, int height, const Terrain::NormalizeLocalYArray& heights, bool forceMaxError = false);
		void SetNormalizeHeights(int xStart, int yStart, int width, int height, const float* heights, bool forceMaxError = false);
		void SetNormalizeHeights(GPtr<Resources::RawResInfo> &pInfo);

		float GetWorldYAtActorCoord(float fX, float fZ, int level = 0) const;

	protected:
		void _ResetHeightmapAttr(const float& defaultNormal, const float& fLow, const float& fHigh,const int& oldResolution, const int& newResolution);

	protected:
		GPtr<Resources::RawResInfo> m_RawResInfo;
		bool                        m_bIsResInfoDirty;


		//===============================================================================================================
		//Terrain LOD
	public:
		void ResetHeightLOD(int xStart, int yStart, int width, int height, bool heightChange, bool HoleChange);
		
		Math::scalar GetPixError() const;
		void SetPixError(const Math::scalar& val) ;

	protected:
		/// Update LOD status and render data
		void _UpdateLodAndRender( Graphic::Camera* camera );
		
	protected:
		Math::scalar m_PixelError;

		//===============================================================================================================
		//TerrainTexture
		/// add Shader ID. 
	public:
		void CreateBaseMap();
		void CreateColorMap();
		bool _CreateControlMapTexture(Util::String mapName);

		const Util::String  GetControlMapName(IndexT idx);
		
		//Base Map
		Math::scalar GetBaseMapDis() const;
		void SetBaseMapDis(const Math::scalar& val) ;
	

	protected:
		void _DeleteControlMap(const int index);
		void _UpdateBaseMap();
		void _UpdateColorMap();

		void _AddControlMaps(void);

		void _UpdateLayerBlendIndex();
		void _UpdataLayerControlMapName();

		int  _GetLayerMapCount();

		/// convert tile size to tile count
		Math::float4 _ConvertTileSizeToTileCount(const Math::float2& tileSize, const Math::float2& offset);
		Math::float4 _ConvertTileCountToTileSize(const Math::float2& tileCount, const Math::float2& offset);

	protected:
		bool										m_bIsTextureDirty;

	protected:
		Math::scalar m_BaseMapDis;
	
		//===============================================================================================================
		//Terrain Texture Brush
	public:
		const int GetBrushCount();

		Terrain::LayermapInfo GetBrushSetting(const int brushIndex);

		// brush color
		void SetBrushColor(IndexT brushIndex, Math::ColorF color);
		Math::ColorF GetBrushColor(IndexT brushIndex);

		/// change brush's data
		

		void AddMaterialBrush(const Resources::ResourceId &matID, const Math::float2 &size, const Math::float2 &offset, const Resources::ResourceId &texID);
		void RemoveMaterialBrush(const int index);

		void ChangeBrushMaterial(const Resources::ResourceId &matID, IndexT index);
		void ChangeBrushTexture(IndexT index, const ShaderParamString &paramName, const Resources::ResourceId &texID);
		void ChangeBrushTileOffset(IndexT index, Math::float2 tileSize, Math::float2 offset);

		bool CheckBrushMaterialParam(IndexT index, const ShaderParamString &paramName);

		Util::String GetBrushMaterialID(IndexT index);
		Util::String GetBrushTextureName(IndexT index, const ShaderParamString &paramName);
		Math::float4 GetBrushTileOffset(IndexT index);

		//BrushProjector
#ifdef __GENESIS_EDITOR__
		void SetRenderProjector(bool isRender);
		bool GetRenderProjector() const;
#endif

	protected:
		Math::ColorF m_BrushColor;
		//===============================================================================================================
		//Terrain Hole
 	public:
		bool MakeHole(int holeX, int holeY, int holeW, int holeH,const Terrain::HoleDataArray& dataArray); 
		bool MakeHole(int holeX, int holeY, int holeW, int holeH,uchar val); 
		void _SetBitMasks(int holeX, int holeY, int holeW, int holeH,uchar val);
		bool IsHole(int holeX, int holeY);

		//===============================================================================================================
		//	Serialization
	public:
		friend class TerrainRenderComponentSerialization;

		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		void SaveTerrainFile(void);

	
		//===============================================================================================================
		//LightMap
	public:
		void SetLMSize(unsigned int lmSize);
		unsigned int GetLMSize() const;
		
		void SetLMIndex(int index);
		unsigned int  GetLMIndex() const;

		void SetLMDirty();

		const RenderBase::TextureHandle& GetLMTextureHandle();
		bool IsUseLM() const;
		const bool IsLMTextureHandleValid() const;

	private:
		// used for lightmap
		unsigned int mLMSize;
		unsigned int mLMIndex;
		bool  mLMDirty;
		RenderBase::TextureHandle mLMHandle;


		friend class TerrainRenderer;
	};



	inline const int TerrainRenderComponent::GetBrushCount()
	{
		return _GetLayerMapCount();
	}



	inline RenderBase::PrimitiveTopology::Code TerrainRenderComponent::GetPrimitiveTopology(void) const
	{
		return RenderBase::PrimitiveTopology::TriangleList;
	}

	inline Math::scalar TerrainRenderComponent::GetPixError() const
	{
		return m_PixelError;
	}
	inline void TerrainRenderComponent::SetPixError(const Math::scalar& val)
	{
		m_PixelError = val;
	}

	inline Math::scalar TerrainRenderComponent::GetBaseMapDis() const
	{
		return m_BaseMapDis;
	}

	inline void TerrainRenderComponent::SetBaseMapDis(const Math::scalar& val)
	{
		m_BaseMapDis = val;
	}

	inline void TerrainRenderComponent::SetLMSize(unsigned int lmSize) 
	{
		mLMSize = lmSize;
	}

	inline unsigned int TerrainRenderComponent::GetLMSize() const 
	{ 
		return mLMSize;
	}

	inline void TerrainRenderComponent::SetLMIndex(int index)
	{
		if ( index != mLMIndex)
		{
			mLMIndex = index;
			mLMDirty = true;
		}
	}

	inline unsigned int  TerrainRenderComponent::GetLMIndex() const
	{
		return mLMIndex;
	}

	inline void TerrainRenderComponent::SetLMDirty()
	{
		mLMDirty = true;
	}

	inline const RenderBase::TextureHandle& TerrainRenderComponent::GetLMTextureHandle()
	{
		if (mLMDirty)
		{
			if ( IsUseLM() )
			{
				mLMHandle = LightmapSetting::GetInstance().GetLightmapTexHandle( mLMIndex );
			}
			else
			{
				mLMHandle = RenderBase::TextureHandle();
			}

			mLMDirty = false;
		}

		return mLMHandle;
	}

	inline bool TerrainRenderComponent::IsUseLM() const
	{
		return mLMIndex != 0xFFFF;
	}

	inline const bool TerrainRenderComponent::IsLMTextureHandleValid() const
	{
		if ( mLMDirty )
		{
			if ( IsUseLM() )
				return LightmapSetting::GetInstance().GetLightmapTexHandle( mLMIndex ).IsValid();
			else
				return false;
		}
		else
			return mLMHandle.IsValid();
	}
}

#endif//__TERRAINRENDERCOMPONENT_H__
