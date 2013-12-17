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

#ifndef __TerrainRenderComponentSerialization_H__
#define __TerrainRenderComponentSerialization_H__


#include "stdneb.h"
#include "TerrainRenderComponent.h"
#include "serialization/serializeserver.h"


namespace App
{

	using namespace Math;
	using namespace Terrain;

	class TerrainRenderComponentSerialization
	{
	public:
		TerrainRenderComponentSerialization(TerrainRenderComponent* pComponent)
			: mObject(pComponent),terrainVersion(0)
		{}

		~TerrainRenderComponentSerialization()
		{}

		inline void Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args)
		{
			terrainVersion = ver;

			switch (ver)
			{
			case 1:
				{
					Load_1(pReader, args);
					break;
				}
			case 2:
				{
					Load_2(pReader, args);
					break;
				}
			case 3:
				{
					Load_3(pReader, args);
					break;

				}
			case 4:
				{
					Load_4(pReader, args);
					break;

				}
			case 5:
				{
					Load_5(pReader, args);
					break;
					break;
				}
			case 6:
				{
					Load_6(pReader,args);
					break;
				}
			case 7:
				{
					Load_7(pReader,args);
					break;
				}
			default:
				{
					n_error(" TerrainComponentSerialization::Load unknonw version " );
					break;
				}
			}

			return;
		}

		void Load_1(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_2(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_3(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_4(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_5(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_6(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Load_7(AppReader* pReader, const Serialization::SerializationArgs* args);
		void Save(AppWriter* pWriter);

	protected:
		TerrainRenderComponent* mObject;
		Version terrainVersion;
	}; //class TerrainComponentSerialization

	///
	const char* s_TerrainName = "TerrainName";
	const char* s_NameDummy = "EmptyNull";
	const char* s_HeightMapWidth = "HeightMapWidth";
	const char* s_HeightMapScale = "HeightMapScale";
	const char* s_HeightMapHights = "HeightMapHights";
	const char* s_BasemapResolution = "BasemapResolution";
	const char* s_ControlmapResolution = "AlphamapResolution";
	const char* s_HeightmapID = "HeightmapID";
	const char* s_HeightmapPriority = "HeightmapPriority";
	const char* s_HeightmapBaseHeight = "HeightmapBaseHeight";

	const char* s_Hole_Num = "Hole_Num";
	const char* s_Hole_PosX = "Hole_PosX";
	const char* s_Hole_PosY = "Hole_PosY";
	const char* s_Hole_Val = "Hole_Val";
	const char* s_PixelError = "PixelError";
	const char* s_BaseMapDis = "BaseMapDis";
	const char* s_ColorMapRes = "ColorMapRes";

	const char* s_TerrainLMIndex = "terrainLightmapIndex";
	const char* s_TerrainLMSize = "terrainLightmapSize";

	const int saveGrids = 32;

	struct SHoleInfo
	{
		uint val;
		int  posX;
		int  posY;
	};

	//------------------------------------------------------------------------------
	void TerrainRenderComponentSerialization::Load_1(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		n_assert(mObject);

		TerrainRenderComponent* pTRenderCom = const_cast<TerrainRenderComponent*>( mObject );

		// name
		Util::String name;
		pReader->SerializeString(s_TerrainName, name);
		pTRenderCom->SetTerrainName(name);

		//------------------------------------------------------------------------------
		// heightmap data
		// height width
		const GPtr<Terrain::TerrainDataSource>& terrainDatasource = pTRenderCom->GetTerrainDataSource();
		int width = 0;
		pReader->SerializeInt(s_HeightMapWidth, width);
		terrainDatasource->ResetHeightmpData(width);

		// scale
		float3 sacle(0.0f, 0.0f, 0.0f);
		pReader->SerializeFloat3(s_HeightMapScale, sacle);
		if ( terrainVersion < 7 )
		{
			sacle.y() /= MaxLocalY;
		} 		

		terrainDatasource->SetTerrainRatio(sacle);

		// height map
		Util::String heightmapID;
		pReader->SerializeString(s_HeightmapID, heightmapID);
		int heightPriority;
		pReader->SerializeInt(s_HeightmapPriority, heightPriority);//discard parameter
		const ComponentSerializationArgs* cargs = args->cast_fast<ComponentSerializationArgs>();
		Resources::Priority priority = (Resources::ResourcePriority::Undefinition == cargs->getPriority()) ? Resources::ResourcePriority::SkeletonDefault : cargs->getPriority();
		pTRenderCom->SetRawResID(heightmapID, heightPriority);

		//------------------------------------------------------------------------------
		// LayerBlendMap data
		int basemapSize = 0;
		pReader->SerializeInt(s_BasemapResolution, basemapSize);

		int controlmapSize = 0;
		pReader->SerializeInt(s_ControlmapResolution, controlmapSize);

		DataSourceMapSetting dataSetting;
		dataSetting.basemapSize = basemapSize;
		dataSetting.controlmapSize = controlmapSize;

		pTRenderCom->GetTerrainDataSource()->SetDataSourceSetting(dataSetting);

		pTRenderCom->CheckRenderables();
		// render data
		const SizeT count = pTRenderCom->GetShaderCount();

		for ( IndexT iMat = 0; iMat < count; ++iMat )
		{
			// shader id
			const Resources::ResourceId& materialID = pTRenderCom->GetMaterialID(iMat);
			n_assert( materialID.IsValid() );

			// texture param
			int skipNum = 0;
			const SizeT texParamCount = pTRenderCom->GetTextureParamCount(iMat);
			for ( IndexT iTex = 0; iTex < texParamCount; ++iTex )
			{
				const ShaderParamString& texParamName =  pTRenderCom->EnumTextureParam( iMat, iTex );
				n_assert( texParamName.IsValid() );

				const Resources::ResourceId& texID = pTRenderCom->GetTexture(iMat,texParamName);
				n_assert( texID.IsValid() );

				const char* kBaseTexParamName = "_mainTex";
				const char* kControlParamName = "_controlMap";
				const char* kBlendParamName = "_blendMap";
				const char* kColorTexParamName = "_colorMap";
				const IndexT kBrushMaterialIdx		= 2;
				float4 val(0.0f, 0.0f, 0.0f, 0.0f);

				if (texParamName == kBaseTexParamName)
				{
					GPtr<Resources::TextureResInfo> texInfo = pTRenderCom->_GetTextureParam(iMat,texParamName);
					pTRenderCom->GetTerrainDataSource()->SetBaseMap(texInfo);
					continue;
				}
				else if ( texParamName == kColorTexParamName )
				{
					GPtr<Resources::TextureResInfo> texInfo = pTRenderCom->_GetTextureParam(iMat,texParamName);
					pTRenderCom->GetTerrainDataSource()->SetColorMap(texInfo);
					continue;
				}
				else if (texParamName == kControlParamName)
				{
					const Util::String controlMap = texID.AsString();
					if (controlMap.FindStringIndex("AlphaMap_") != InvalidIndex)
					{
						n_assert(iMat >= kBrushMaterialIdx);
						GPtr<Resources::TextureResInfo> texInfo = pTRenderCom->_GetTextureParam(iMat,texParamName);

						int controlMapIndex = (iMat-kBrushMaterialIdx)/4;
						if(controlMapIndex == pTRenderCom->GetTerrainDataSource()->GetControlMapSize())
							pTRenderCom->GetTerrainDataSource()->AddControlMap( texInfo );
					}
					skipNum++;
				}
				else if(texParamName == kBlendParamName) //brush texture
				{
					n_assert(iMat >= kBrushMaterialIdx);

					const Util::String& paramValue = pTRenderCom->_GetShaderConstantParamValue(iMat, "_uvMap");
					if(!paramValue.IsEmpty())
					{
						val = paramValue.AsFloat4();
						val.set_x( pTRenderCom->GetTerrainSize().x()/val.x() );
						val.set_y( pTRenderCom->GetTerrainSize().z()/val.y() );
						val.set_z( val.z() * val.x() ); 
						val.set_w( val.w() * val.y() );

						GPtr<Resources::TextureResInfo> texInfo = pTRenderCom->_GetTextureParam(iMat,texParamName);
						Terrain::LayermapInfo layerInfo;
						layerInfo.resourceInfo = texInfo;
						layerInfo.materialName = materialID;
						layerInfo.layermapTileSize = float2(val.x(),val.y());
						layerInfo.layermapOffset = float2(val.z(),val.w());
						pTRenderCom->GetTerrainDataSource()->AddLayermap(iMat-kBrushMaterialIdx, layerInfo);
					}			
				}
			} 
		}

		return;
	}

	//------------------------------------------------------------------------
	void TerrainRenderComponentSerialization::Load_2(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		Load_1(pReader, args);

		// get hole data
		n_assert(mObject);

		TerrainRenderComponent* pTRenderCom = const_cast<TerrainRenderComponent*>( mObject );

		const GPtr<Terrain::TerrainDataSource>& terrainDatasource = pTRenderCom->GetTerrainDataSource();
		int nNum = 0;
		pReader->SerializeInt(s_Hole_Num,nNum);

		if ( nNum != 0 )
		{
			
			// name
			Util::String strName;
			for ( int i = 0; i < nNum; i++ )
			{
			 	SHoleInfo holes;
			 	strName.Format("%s_%d",s_Hole_PosX,i);
			 	pReader->SerializeInt( strName.Get(), holes.posX);
			 
			 	strName.Format("%s_%d",s_Hole_PosY,i);
			 	pReader->SerializeInt( strName.Get(), holes.posY);
			 
			 	strName.Format("%s",s_Hole_Val);
			 	pReader->SerializeUInt( strName.Get(), holes.val);
			 
			 
			 
			 	for ( int k = 0; k < saveGrids; k++ )
			 	{
					uchar val = ( holes.val & (1<<k) ) >> k;
					terrainDatasource->SetHoleDataByUnit(holes.posX+k,holes.posY,val);
			 	}
			}
			 
			
		}


	}
	//------------------------------------------------------------------------
	void TerrainRenderComponentSerialization::Load_3(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		Load_2(pReader, args);

		// 
		n_assert(mObject);

		TerrainRenderComponent* pTRenderCom = const_cast<TerrainRenderComponent*>( mObject );	
		int nNum = 0;
		pReader->SerializeInt(s_HeightmapBaseHeight,nNum);

		pTRenderCom->SetBaseHeight(nNum);
	}
	//------------------------------------------------------------------------
	void TerrainRenderComponentSerialization::Load_4(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		Load_3(pReader, args);

		// 
		n_assert(mObject);

		TerrainRenderComponent* pTRenderCom = const_cast<TerrainRenderComponent*>( mObject );	
		Math::scalar fVal = 0.f;
		pReader->SerializeFloat(s_PixelError,fVal);
		pTRenderCom->SetPixError(fVal);

		pReader->SerializeFloat(s_BaseMapDis,fVal);
		pTRenderCom->SetBaseMapDis(fVal);

	}
	//------------------------------------------------------------------------
	void TerrainRenderComponentSerialization::Load_5(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		Load_4(pReader, args);
		//
		n_assert(mObject);

		TerrainRenderComponent* pTRenderCom = const_cast<TerrainRenderComponent*>( mObject );
		int nVal = 0;
		pReader->SerializeInt(s_ColorMapRes, nVal);
		DataSourceMapSetting dataSetting = pTRenderCom->GetTerrainDataSource()->GetDataSourceSetting();
		dataSetting.colormapSize = nVal;
		pTRenderCom->GetTerrainDataSource()->SetDataSourceSetting(dataSetting);
	}
	//------------------------------------------------------------------------------
	void TerrainRenderComponentSerialization::Load_6(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		Load_5(pReader, args);

		n_assert(mObject);
		TerrainRenderComponent* pTRenderCom = const_cast<TerrainRenderComponent*>( mObject );
		unsigned int uIvalue;

		pReader->SerializeUInt(s_TerrainLMIndex, uIvalue);
		pTRenderCom->SetLMIndex( uIvalue );

		pReader->SerializeUInt(s_TerrainLMSize, uIvalue);
		pTRenderCom->SetLMSize( uIvalue );
	}

	//------------------------------------------------------------------------
	void TerrainRenderComponentSerialization::Load_7(AppReader* pReader, const Serialization::SerializationArgs* args)
	{
		Load_6(pReader, args);
	}




	void TerrainRenderComponentSerialization::Save(AppWriter* pWriter)
	{
		n_assert(mObject);
		Util::String name = mObject->GetTerrainName();
		if (!name.IsValid())
		{
			name = s_NameDummy;
		}
		pWriter->SerializeString(s_TerrainName, name);

		// save height map data
		const GPtr<Terrain::TerrainDataSource>& terrainDatasource = mObject->GetTerrainDataSource();
		const DataSourceMapSetting dataSetting = terrainDatasource->GetDataSourceSetting();
		pWriter->SerializeInt(s_HeightMapWidth, terrainDatasource->GetHeightMapSize());
		pWriter->SerializeFloat3(s_HeightMapScale, terrainDatasource->GetTerrainRatio());

		const GPtr<Resources::RawResInfo> &pInfo = mObject->GetRawResInfo();
		if (pInfo.isvalid())
		{
			const Util::String heightmapID = pInfo->GetResID().AsString();
			pWriter->SerializeString(s_HeightmapID, heightmapID);
			int heightPriority = mObject->m_RawResInfo->GetPriority();
			pWriter->SerializeInt(s_HeightmapPriority, heightPriority);
		}
		else
		{
			pWriter->SerializeString(s_HeightmapID, "asset:Terrain/" + mObject->GetTerrainName() +".xraw");
			pWriter->SerializeInt(s_HeightmapPriority, 0);
		}


		// save blend map data
		pWriter->SerializeInt(s_BasemapResolution, dataSetting.basemapSize);
		pWriter->SerializeInt(s_ControlmapResolution, dataSetting.controlmapSize);



		// save hole data
		Util::Array<SHoleInfo> holes;

		for ( int y = 0; y < terrainDatasource->GetHeightMapSize()-1; y++)
		{
			for ( int x = 0; x < terrainDatasource->GetHeightMapSize()-1; x+= saveGrids)
			{
				uint saveVal = 0;
				for ( int i = 0; i < saveGrids; i++ )
				{
					uint val = terrainDatasource->GetHoleDataByUnit(x+i,y);
					saveVal |= val << i;
				}

				if ( saveVal != 0 )
				{
					SHoleInfo info;
					info.val = saveVal;
					info.posX = x;
					info.posY = y;
					holes.Append(info);
				}

			}
		}

		// hole num
		pWriter->SerializeInt( s_Hole_Num, holes.Size());

		Util::String strName;		
		for ( IndexT i = 0; i < holes.Size(); i++ )
		{
			strName.Format("%s_%d",s_Hole_PosX,i);
			pWriter->SerializeInt( strName.Get(), holes[i].posX);

			strName.Format("%s_%d",s_Hole_PosY,i);
			pWriter->SerializeInt( strName.Get(), holes[i].posY);

			strName.Format("%s",s_Hole_Val);
			pWriter->SerializeUInt( strName.Get(), holes[i].val);
		}

		pWriter->SerializeInt(s_HeightmapBaseHeight,mObject->GetBaseHeight());

		// pixerror and basemap
		pWriter->SerializeFloat(s_PixelError,mObject->GetPixError());
		pWriter->SerializeFloat(s_BaseMapDis,mObject->GetBaseMapDis());

		//
		pWriter->SerializeInt(s_ColorMapRes,dataSetting.colormapSize);

		// support lightmap
		pWriter->SerializeUInt(s_TerrainLMIndex, mObject->GetLMIndex() );
		pWriter->SerializeUInt(s_TerrainLMSize, mObject->GetLMSize() );

		return;
	}

	///
	//------------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version TerrainRenderComponent::GetVersion() const
	{
		//return 1;	//	current version is 1
		//return 2;	//  add hole
		//return 3;	//	add height baseHeight
		//return 4; // baseMapDis and pixelerror
		//return 5;   // colormap res
		//return 6; // current version is 6; support lightmap
		return 7; // terrain refactor,change scaleY semantic
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Load 
	void TerrainRenderComponent::Load(Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		TerrainRenderComponentSerialization serialize(this);
		serialize.Load(ver, pReader, args);
	}

	//------------------------------------------------------------------------------
	// @ISerialization::Save
	void TerrainRenderComponent::Save(AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		TerrainRenderComponentSerialization serialize(const_cast<TerrainRenderComponent*>(this));
		serialize.Save(pWriter);
	}

}

#endif //__TerrainRenderComponentSerialization_H__
