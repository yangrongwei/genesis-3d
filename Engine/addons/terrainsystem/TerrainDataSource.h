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

#ifndef __TerrainDataSource_H__
#define __TerrainDataSource_H__

#include "core/refcounted.h"
#include "util/fixedarray2d.h"
#include "util/array.h"
#include "util/mipmaparray.h"

#include "math/color.h"
#include "resource/resourcemanager.h"
#include "resource/resourceserver.h"

namespace Resources
{
	class TextureResInfo;
}

namespace Terrain
{
	typedef Util::FixedArray2D<uint16> LocalYArray;
	typedef Util::FixedArray2D<float> WorldYArray;
	typedef Util::FixedArray2D<float> NormalizeLocalYArray;
	typedef Util::FixedArray2D<uchar> HoleDataArray;
	
	//------------------------------------------------------------------------------
	//heightMap type
	//------------------------------------------------------------------------------

	#define  SectorSize		17
	#define  UnitsInSector	16
	#define  InverseUnitsInSector 0.0625
    #define  UnitToSector    4
	#define  MaxHeightmapSize  2049
	#define  MaxLocalY  32766
	
	//
	enum HoleType
	{
		eNotHole = 0,				// no hole
		ePartHole = 1,				// a part of grid is hole
		eWholeHole =2				// complete hole
	};

	struct SSectorData
	{
		SSectorData()
		{
			mMinLocalY = 0;
			mMaxLocalY = 0;
			mGeoError = 0.0f;
			mHoleType = eNotHole;
		}
		int mMinLocalY;
		int mMaxLocalY;
		float  mGeoError;			// geometry error
		HoleType mHoleType;
	};

	struct DataSourceMapSetting
	{
		uint16 controlmapSize;
		uint16 colormapSize;
		uint16 basemapSize;
	};

	typedef Util::MipmapArray<SSectorData> SectorDataArray;

	struct LayermapInfo
	{
		GPtr<Resources::TextureResInfo> resourceInfo;
		Math::float2 layermapTileSize;
		Math::float2 layermapOffset;
		Resources::ResourceId materialName;

		LayermapInfo()
			:layermapTileSize(15.0f, 15.0f)
			,layermapOffset(0.0f,0.0f)
		{
			
		}
	};

	typedef Util::Array<LayermapInfo> Layermaps;
	typedef Util::Array< GPtr<Resources::TextureResInfo> > Controlmaps;

	enum DataType
	{
		COLORF,
		COLOR32
	};

	class TerrainDataSource : public Core::RefCounted
	{
		__DeclareClass(TerrainDataSource);
	public:
		TerrainDataSource();
		virtual ~TerrainDataSource();

		void SetDataSourceSetting(const DataSourceMapSetting& setting);
		const DataSourceMapSetting& GetDataSourceSetting() const;
//------------------------------------------------------------------------------
//heightMap methods
//------------------------------------------------------------------------------
		int					GetHeightMapSize() const;

		/// note ratio.y is maxWorldY / MaxLocalY
		void				SetTerrainRatio(const Math::float3& ratio);
		const Math::float3	GetTerrainRatio() const;

		int					GetLevelCount() const;
		int					GetXUnitCount(int level) const;
		int					GetZUnitCount(int level) const;
		
		float				GetGeometryError (int xSector, int zSector, int level) const;

		void				SetWorldYByUnit(int xUnit,int zUnit,float y,int level = 0);
		float				GetWorldYByUnit(int xUnit,int zUnit,int level = 0) const;

		void				SetWorldYArrayByUnit(int xUnit,int zUnit,int xSize,int zSize, WorldYArray& yArray, int level = 0);
		void				GetWorldYArrayByUnit(int xUnit,int zUnit,int xSize,int zSize, WorldYArray& yArray, int level = 0) const;

		void				SetLocalYByUnit(int xUnit,int zUnit,uint16 y, int level = 0);
		uint16				GetLocalYByUnit(int xUnit,int zUnit,int level = 0) const;

		void				SetNormalizeLocalYByUnit(int xUnit, int zUnit, float y, int level = 0);
		float				GetNormalizeLocalYByUnit(int xUnit, int zUnit, int level = 0) const;
		
		void				SetLocalYArrayByUnit(int xUnit,int zUnit,int xSize,int zSize, LocalYArray& yArray, int level = 0);
		void				GetLocalYArrayByUnit(int xUnit,int zUnit,int xSize,int zSize, LocalYArray& yArray, int level = 0) const;

		void                SetNormalizeLocalYArrayByUnit(int xUnit, int zUnit, int xSize, int zSize, const NormalizeLocalYArray& heights, int level = 0 );
		void                GetNormalizeLocalYArrayByUnit(int xUnit, int zUnit, int xSize, int zSize, NormalizeLocalYArray& heights, int level = 0) const;
		// Get Interpolation worldY by xUnit,zUnit,and fX that is offset in the x direction
		// and fZ that is offset in the z direction
		float				GetWorldYByUnit(int xUnit, int zUnit, float fX, float fZ, int level = 0) const;

		IndexT				GetSectorIndex(int xSector,int zSector,int level = 0) const;
		void				GetSectorLocalData(int xSector, int zSector, LocalYArray& aArray,int level = 0) const;
		void				GetSectorWorldData(int xSector, int zSector, WorldYArray& aArray,int level = 0) const;

		Math::bbox			GetSectorWorldBBox(int xSector,int zSector,int level = 0) const;
		Math::bbox			GetSectorLocalBBox(int xSector,int zSector,int level = 0) const;
		/// [terrain:to be continue]
		void				CopySectorDatatFrom(const GPtr<TerrainDataSource>& obj);
		void				CalculateSectorInfoDataByUnit(int xUnit, int zUnit, int xSize, int zSize);
		///LOD
		void				ResetSectorInfo(int xUnit, int zUnit, int xSize, int zSize);

		Math::float3        CalculateWorldNormalByUnit(int xUnit, int zUnit, int level) const;

		bool				BuildHeightmpData(int heightmapSize, LocalYArray& yArray);
		bool				ResetHeightmpData(int heightmapSize, bool isUsePreData = false);
//------------------------------------------------------------------------------
//hole methods
//------------------------------------------------------------------------------
		void				SetHoleDataByUnit(int xUnit,int zUnit,uchar val);
		uchar				GetHoleDataByUnit(int xUnit,int zUnit) const;
		HoleType			GetSectorHoleType(int xSector, int zSector, int level) const;
		HoleType			CalculateMaxDetailedSectorHoleType(int xSector, int zSector) const;
		uint				CalcualteMipGridHoleCount(int xUnit, int zUnit, int mipLevel) const;
//------------------------------------------------------------------------------
//LayerMap methods
//------------------------------------------------------------------------------
		void                SetLayermaps(const Layermaps & layermaps);
		const Layermaps&    GetLayermpas() const;

		void				AddLayermap(int layerIndex, LayermapInfo layermapInfo);
		void				DelLayermap(int layerIndex);
		void				SetLayermap(int layerIndex, LayermapInfo layermapInfo);
		LayermapInfo		GetLayermap(int layerIndex);

		int					GetLayerMapCount() const;

//------------------------------------------------------------------------------
//ControlMap methods
// Set/Get Control/Color/Base MapData methods should use template function! /// [terrain:to be continue]
//------------------------------------------------------------------------------
		bool				IsValidControlMap() const;
		bool				CreateControlMap(const Resources::ResourceId& resID);
		GPtr<Resources::TextureResInfo>& GetControlMap(const int idx);
		void				AddControlMap(GPtr<Resources::TextureResInfo>& texInfo);
		void				DelControlMap(const int idx);
		int					GetControlMapSize() const;
		void				GetControlMapData(Math::Color32* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		void				GetControlMapData(Math::ColorF* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		void				SetControlMapData(Math::Color32* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		void				SetControlMapData(Math::ColorF* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		void				RefreshControlMap(const int index,int texNumBeforeDel);
//------------------------------------------------------------------------------
//ColorMap methods
//------------------------------------------------------------------------------
		bool                IsValidColormap() const;
		bool				CreateColorMap(const Resources::ResourceId& resID);
		void				SetColorMap(GPtr<Resources::TextureResInfo>& texInfo);
		void				GetColorMapData(Math::Color32* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		void				GetColorMapData(Math::ColorF* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		void				SetColorMapData(Math::Color32* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		void				SetColorMapData(Math::ColorF* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
//------------------------------------------------------------------------------
//BaseMap methods
//------------------------------------------------------------------------------
		bool				IsValidBasemap() const;
		bool				CreateBaseMap(const Resources::ResourceId& resID);
		void				SetBaseMap(GPtr<Resources::TextureResInfo>& texInfo);
		void				GetBaseMapData(Math::Color32* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		void				GetBaseMapData(Math::ColorF* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		void				SetBaseMapData(Math::Color32* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		void				SetBaseMapData(Math::ColorF* buffer,const int xStart = 0,const int yStart = 0,const int width = -1,const int height = -1);
		//void	            RefreshBasemap(const int xStart = 0,const int yStart = 0, const int width = -1, const int height = -1 );

		void	            RefreshBasemap(float xStart = 0.0f, float yStart = 0.0f, float relativeWidth = 1.0f, float relativeHeight = 1.0f);
//------------------------------------------------------------------------------
//other unclassify methods
//------------------------------------------------------------------------------
		void				SaveAllMaps();
		void				SaveControlMap();
		void				SaveColorMap();
		void				SaveBaseMap();
	protected:
		void				_GetBlendWeights(int xStart, int yStart, int width, int height, float* buffer);		
		bool                GetImagesData(GPtr<Resources::TextureResInfo> & texResInfo, int xStart, int yStart, int width, int height, void* buffer, DataType datatype);
		bool                SetImagesData(GPtr<Resources::TextureResInfo> & texResInfo, int xStart, int yStart, int width, int height, void* buffer, DataType datatype);
		void				_saveImage(GPtr<Resources::TextureResInfo> & texResInfo);

		void				CalculateASectorGeoErrorDataBySector(int xSector, int zSector, int level);
		void				CalculateASectorMinMaxLocalYDataBySector(int xSector, int zSector, int level, int& maxLocalY,int& minLocalY );
		void				CalculateASectorMinMaxYDataBySector(int xSector, int zSector);
private:
		static void _UpdateTextureFunction(RenderBase::Texture::MapInfo& texMap,int width,int height, int depth, RenderBase::PixelFormat::Code format, int mipLevel, void* tag);

private:
		DataSourceMapSetting					mapSetting;

		LocalYArray								mLocalYArray;
		HoleDataArray							mHoleDataArray;  // we can't use std::bitset,because holedata' size will changing wtih height map size

		SectorDataArray		mSectorData;
		float               mYRatio;
		Math::float2        mXZRatio;
		Math::float3        mWorldSize;
		int                 mHeightmapSize;

		Layermaps								mLayermaps; 
		Controlmaps								mControlmaps;
		GPtr<Resources::TextureResInfo>			mBaseMap;
		GPtr<Resources::TextureResInfo>			mColorMap;
	};
//==============================================================================================================
	inline void TerrainDataSource::SetDataSourceSetting(const DataSourceMapSetting& setting)
	{
		mapSetting = setting;
	}

	inline const DataSourceMapSetting& TerrainDataSource::GetDataSourceSetting() const
	{
		return mapSetting;
	}

	inline int TerrainDataSource::GetHeightMapSize() const
	{
		return mHeightmapSize;
	}

	inline void TerrainDataSource::SetTerrainRatio(const Math::float3& ratio)
	{
		mXZRatio.x() = ratio.x();
		mYRatio = ratio.y();
		mXZRatio.y() = ratio.z();
	}

	inline const Math::float3 TerrainDataSource::GetTerrainRatio() const
	{
		return Math::float3(mXZRatio.x(),mYRatio,mXZRatio.y());
	}

	inline int TerrainDataSource::GetLevelCount() const
	{
		return mSectorData.GetMipCount();
	}

	inline int TerrainDataSource::GetXUnitCount(int level) const
	{
		n_assert( level < mSectorData.GetMipCount() );
		return (mSectorData.RowSize(level) << UnitToSector) + 1;
	}

	inline int TerrainDataSource::GetZUnitCount(int level) const
	{
		n_assert( level < mSectorData.GetMipCount() );
		return (mSectorData.ColSize(level) << UnitToSector) + 1;
	}

	inline float TerrainDataSource::GetGeometryError (int xSector, int zSector, int level) const
	{
		n_assert( level < mSectorData.GetMipCount() );
		n_assert( xSector >= 0 && xSector < mSectorData.RowSize( level ) );
		n_assert( zSector >= 0 && zSector < mSectorData.ColSize( level ) );
		return mSectorData.At( xSector, zSector, level ).mGeoError;
	}

	inline void TerrainDataSource::SetLayermaps(const Layermaps & layermaps)
	{
		mLayermaps = layermaps;
	}

	inline const Layermaps& TerrainDataSource::GetLayermpas() const
	{
		return mLayermaps;
	}

	inline int TerrainDataSource::GetLayerMapCount() const
	{
		return mLayermaps.Size();
	}

	inline void TerrainDataSource::SetWorldYByUnit(int xUnit, int zUnit, float y, int level)
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );

		uint16 localY = (uint16)(y / mYRatio);
		mLocalYArray.At(xUnit << level, zUnit << level) = localY;
	}

	inline float TerrainDataSource::GetWorldYByUnit(int xUnit, int zUnit, int level) const
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );

		float worldY = mLocalYArray.At(xUnit << level, zUnit << level) * mYRatio;
		return worldY;
	}

	inline void TerrainDataSource::SetLocalYByUnit(int xUnit,int zUnit,uint16 y, int level)
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );

		mLocalYArray.At(xUnit << level, zUnit << level) = y;
	}

	inline uint16 TerrainDataSource::GetLocalYByUnit(int xUnit,int zUnit,int level) const
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );

		return mLocalYArray.At(xUnit << level, zUnit << level);
	}

	inline void TerrainDataSource::SetNormalizeLocalYByUnit(int xUnit, int zUnit, float y, int level)
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );

		int localY = (int)(y * MaxLocalY + 0.5f);
		mLocalYArray.At(xUnit << level, zUnit << level) = Math::n_clamp(localY, 0, MaxLocalY);
	}

	inline float TerrainDataSource::GetNormalizeLocalYByUnit(int xUnit, int zUnit, int level) const
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );

		uint16 localY = mLocalYArray.At(xUnit << level, zUnit << level);
		return localY * 1.0f / MaxLocalY;
	}

	inline float TerrainDataSource::GetWorldYByUnit(int xUnit, int zUnit, float fX, float fZ, int level) const
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize( level ) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize( level ) << UnitToSector) );
		n_assert( fX >= 0 && fX <= 1);
		n_assert( fZ >= 0 && fZ <= 1);

		float fLocalY = GetLocalYByUnit(xUnit, zUnit, level) * (1.f - fX) * (1 - fZ)
			+ GetLocalYByUnit(xUnit + 1, zUnit, level) * fX * (1.f - fZ)
			+ GetLocalYByUnit(xUnit, zUnit + 1, level) * (1.f - fX) * fZ
			+ GetLocalYByUnit(xUnit + 1, zUnit + 1, level) * fX * fZ;
		return fLocalY * mYRatio;
	}

	inline IndexT TerrainDataSource::GetSectorIndex(int xSector,int zSector,int level) const
	{
		return mSectorData.Index(xSector, zSector, level);
	}

	inline void TerrainDataSource::CalculateASectorMinMaxYDataBySector(int xSector, int zSector)
	{
		int startXUnit = xSector << UnitToSector;
		int startZUnit = zSector << UnitToSector;
		int endXUnit = startXUnit + SectorSize;
		int endZUnit = startZUnit + SectorSize;
		int minLocalY = MaxLocalY;
		int maxLocalY = -MaxLocalY;

		for (int x = startXUnit; x < endXUnit; x++)
		{
			for (int z = startZUnit; z < endZUnit; z++)
			{
				int localY = GetLocalYByUnit(x, z, 0);
				minLocalY = localY < minLocalY ? localY : minLocalY;
				maxLocalY = localY > maxLocalY ? localY : maxLocalY;
			}
		}

		mSectorData.At(xSector, zSector, 0).mMinLocalY = minLocalY;
		mSectorData.At(xSector, zSector, 0).mMaxLocalY = maxLocalY;
	}

	inline void TerrainDataSource::CalculateASectorGeoErrorDataBySector(int xSector, int zSector, int level)
	{
		if (level == 0)
		{
			mSectorData.At(xSector, zSector, level).mGeoError = 0.0f;
			return;
		}
		
		int startXUnit = xSector << ( UnitToSector + level );
		int startZUnit = zSector << ( UnitToSector + level );
		int endXUnit = startXUnit + ( UnitsInSector << level ) + 1;
		int endZUnit = startZUnit + ( UnitsInSector << level ) + 1;
		float inverseLodSize = 1.0f / (1 << level);
		float geoError = 0.0f;

		// first xUnit and last xUnit  when geoError is 0.f
		// first zUnit and last zUnit  when geoError is 0.f
		startXUnit++;
		startZUnit++;
		endXUnit--;
		endZUnit--;

		for (int x = startXUnit; x < endXUnit; x++)
		{
			for (int z = startZUnit; z < endZUnit; z++)
			{
				float trueWorldY = GetWorldYByUnit(x, z, 0);
				int xUnit = x >> level;
				int zUnit = z >> level;
				float fx = (x - (xUnit << level) ) * inverseLodSize;
				float fz = (z - (zUnit << level) ) * inverseLodSize;
				float interpolatedWorldY = GetWorldYByUnit(xUnit, zUnit, fx, fz, level);
				float deltaY = Math::n_abs(interpolatedWorldY - trueWorldY);
				geoError = deltaY > geoError ? deltaY : geoError;
			}
		}

		mSectorData.At(xSector, zSector, level).mGeoError = geoError;
	}

	inline void TerrainDataSource::CalculateASectorMinMaxLocalYDataBySector(int xSector, int zSector, int level, int& maxLocalY,int& minLocalY )
	{
		SSectorData & sectorData1 = mSectorData.At( xSector << 1, zSector << 1, level - 1);
		SSectorData & sectorData2 = mSectorData.At( (xSector << 1) + 1, zSector << 1, level - 1);
		SSectorData & sectorData3 = mSectorData.At( (xSector << 1), (zSector << 1) + 1, level - 1);
		SSectorData & sectorData4 = mSectorData.At( (xSector << 1) + 1, (zSector << 1) + 1, level - 1);

		minLocalY = sectorData1.mMinLocalY < minLocalY  ? sectorData1.mMinLocalY : minLocalY;
		minLocalY = sectorData2.mMinLocalY < minLocalY  ? sectorData2.mMinLocalY : minLocalY;
		minLocalY = sectorData3.mMinLocalY < minLocalY  ? sectorData3.mMinLocalY : minLocalY;
		minLocalY = sectorData4.mMinLocalY < minLocalY  ? sectorData4.mMinLocalY : minLocalY;

		maxLocalY = sectorData1.mMaxLocalY > maxLocalY ? sectorData1.mMaxLocalY : maxLocalY;
		maxLocalY = sectorData2.mMaxLocalY > maxLocalY ? sectorData2.mMaxLocalY : maxLocalY;
		maxLocalY = sectorData3.mMaxLocalY > maxLocalY ? sectorData3.mMaxLocalY : maxLocalY;
		maxLocalY = sectorData4.mMaxLocalY > maxLocalY ? sectorData4.mMaxLocalY : maxLocalY;
	}

	inline bool TerrainDataSource::IsValidControlMap() const
	{
		return mControlmaps.Size() > 0;
	}

	inline GPtr<Resources::TextureResInfo>& TerrainDataSource::GetControlMap(const int idx)
	{
		n_assert( idx >= 0 && idx < mControlmaps.Size() );
		return mControlmaps[idx];
	}

	inline void TerrainDataSource::DelControlMap(const int idx)
	{
		n_assert( idx >= 0 && idx < mControlmaps.Size() );
		mControlmaps.EraseIndex(idx);
	}

	inline int TerrainDataSource::GetControlMapSize() const
	{
		return mControlmaps.Size();
	}

	inline void TerrainDataSource::AddControlMap(GPtr<Resources::TextureResInfo>& texInfo)
	{
		mControlmaps.Append( texInfo );
	}


	inline uchar TerrainDataSource::GetHoleDataByUnit(int xUnit,int zUnit) const
	{
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(0) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(0) << UnitToSector) );

		return mHoleDataArray.At(xUnit, zUnit);
	}

	inline HoleType	TerrainDataSource::GetSectorHoleType(int xSector, int zSector, int level) const
	{
		n_assert( level < mSectorData.GetMipCount() );
		n_assert( xSector >= 0 && xSector < mSectorData.RowSize( level ) );
		n_assert( zSector >= 0 && zSector < mSectorData.ColSize( level ) );
		return mSectorData.At( xSector, zSector, level ).mHoleType;
	}
	inline HoleType TerrainDataSource::CalculateMaxDetailedSectorHoleType(int xSector, int zSector) const
	{
		int startXUnit = xSector << UnitToSector;
		int startZUnit = zSector << UnitToSector;
		int endXUnit   = startXUnit + UnitsInSector;
		int endZUnit   = startZUnit + UnitsInSector;

		int total(0);
		for (int x = startXUnit; x < endXUnit; x++)
		{
			for (int z = startZUnit; z < endZUnit; z++)
			{
				if ( mHoleDataArray.At(x,z) == 1 )
				{
					total++;
				}				
			}
		}

		HoleType hole(eNotHole);
		if ( total == 0 )
		{
			hole = eNotHole;
		}
		else if ( total < UnitsInSector* UnitsInSector)
		{
			hole = ePartHole;
		} 
		else
		{
			hole = eWholeHole;			
		}	
		return hole;
	}
	inline uint	TerrainDataSource::CalcualteMipGridHoleCount(int xUnit, int zUnit, int mipLevel) const
	{
		if ( mipLevel == 0 )
		{
			return mHoleDataArray.At(xUnit,zUnit)==1? 1: 0;
		} 
		else
		{
			int startXUnit = xUnit << mipLevel;
			int startZUnit = zUnit << mipLevel;
			int endXUnit   = startXUnit + (1<<mipLevel);
			int endZUnit   = startZUnit + (1<<mipLevel);

			int total(0);
			for (int x = startXUnit; x < endXUnit; x++)
			{
				for (int z = startZUnit; z < endZUnit; z++)
				{
					if ( mHoleDataArray.At(x,z) == 1 )
					{
						total++;
					}				
				}
			}
			return total;
		}
		
	}
}



#endif // __TerrainDataSource_H__