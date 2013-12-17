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
#include "TerrainDataSource.h"
#include "resource/resource.h"
#include "resource/imageoperations.h"
#include "resource/resourcemanager.h"
#include "resource/imageresloader.h"

namespace Terrain
{
	__ImplementClass(TerrainDataSource, 'TTDS', Core::RefCounted)
	TerrainDataSource::TerrainDataSource()
	:mWorldSize(0.0f, 0.0f, 0.0f),
	mHeightmapSize(-1),
	mBaseMap(NULL),
	mColorMap(NULL)
	{
		
	}

	TerrainDataSource::~TerrainDataSource()
	{

	}

	void TerrainDataSource::SetWorldYArrayByUnit(int xUnit,int zUnit,int xSize,int zSize, WorldYArray& yArray, int level)
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize > 0 && xUnit + xSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( zSize > 0 && zUnit + zSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize == yArray.RowSize() && zSize == yArray.ColSize() );

		int endXUnit = xUnit + xSize;
		int endZUnit = zUnit + zSize;

		for (int x = xUnit; x < endXUnit; x++)
		{
			for (int z = zUnit; z < endZUnit; z++)
			{
				SetWorldYByUnit(x, z, yArray.At(x - xUnit, z - zUnit), level);
			}
		}
	}

	void TerrainDataSource::GetWorldYArrayByUnit(int xUnit,int zUnit,int xSize,int zSize, WorldYArray& yArray, int level) const
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize > 0 && xUnit + xSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( zSize > 0 && zUnit + zSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize == yArray.RowSize() && zSize == yArray.ColSize() );

		int endXUnit = xUnit + xSize;
		int endZUnit = zUnit + zSize;

		for (int x = xUnit; x < endXUnit; x++)
		{
			for (int z = zUnit; z < endZUnit; z++)
			{
				yArray.At(x - xUnit, z - zUnit) = GetWorldYByUnit(x, z, level);
			}
		}
	}

	void TerrainDataSource::SetLocalYArrayByUnit(int xUnit,int zUnit,int xSize,int zSize, LocalYArray& yArray, int level)
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize > 0 && xUnit + xSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( zSize > 0 && zUnit + zSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize == yArray.RowSize() && zSize == yArray.ColSize() );

		int endXUnit = xUnit + xSize;
		int endZUnit = zUnit + zSize;

		for (int x = xUnit; x < endXUnit; x++)
		{
			for (int z = zUnit; z < endZUnit; z++)
			{
				SetLocalYByUnit(x, z, yArray.At(x - xUnit, z - zUnit), level);
			}
		}
	}

	void TerrainDataSource::GetLocalYArrayByUnit(int xUnit,int zUnit,int xSize,int zSize, LocalYArray& yArray, int level) const
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize > 0 && xUnit + xSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( zSize > 0 && zUnit + zSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize == yArray.RowSize() && zSize == yArray.ColSize() );

		int endXUnit = xUnit + xSize;
		int endZUnit = zUnit + zSize;

		for (int x = xUnit; x < endXUnit; x++)
		{
			for (int z = zUnit; z < endZUnit; z++)
			{
				yArray.At(x - xUnit, z - zUnit) = GetLocalYByUnit(x, z, level);
			}
		}
	}
	
	void TerrainDataSource::SetNormalizeLocalYArrayByUnit(int xUnit, int zUnit, int xSize, int zSize, const NormalizeLocalYArray& yArray, int level)
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize > 0 && xUnit + xSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( zSize > 0 && zUnit + zSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize == yArray.RowSize() && zSize == yArray.ColSize() );

		int endXUnit = xUnit + xSize;
		int endZUnit = zUnit + zSize;

		for (int x = xUnit; x < endXUnit; x++)
		{
			for (int z = zUnit; z < endZUnit; z++)
			{
				SetNormalizeLocalYByUnit(x, z, yArray.At(x - xUnit, z - zUnit), level);
			}
		}
	}

	void TerrainDataSource::GetNormalizeLocalYArrayByUnit(int xUnit, int zUnit, int xSize, int zSize, NormalizeLocalYArray& yArray, int level) const
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(level) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize > 0 && xUnit + xSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( zSize > 0 && zUnit + zSize - 1 <= (mSectorData.ColSize(level) << UnitToSector) );
		n_assert( xSize == yArray.RowSize() && zSize == yArray.ColSize() );

		int endXUnit = xUnit + xSize;
		int endZUnit = zUnit + zSize;

		for (int x = xUnit; x < endXUnit; x++)
		{
			for (int z = zUnit; z < endZUnit; z++)
			{
				yArray.At(x - xUnit, z - zUnit) = GetNormalizeLocalYByUnit(x, z, level);
			}
		}
	}

	void TerrainDataSource::GetSectorLocalData(int xSector, int zSector, LocalYArray& yArray,int level) const
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xSector >= 0 && xSector < mSectorData.RowSize(level) );
		n_assert( zSector >= 0 && zSector < mSectorData.ColSize(level) );
		n_assert( SectorSize == yArray.RowSize() && SectorSize == yArray.ColSize() );

		int startXUnit = xSector << UnitToSector;
		int startZUnit = zSector << UnitToSector;
		int endXUnit = startXUnit + SectorSize;
		int endZUnit = startZUnit + SectorSize;

		for (int x = startXUnit; x < endXUnit; x++)
		{
			for (int z = startZUnit; z < endZUnit; z++)
			{
				yArray.At( x - startXUnit, z - startZUnit ) = GetLocalYByUnit(x, z, level);
			}
		}
	}

	void TerrainDataSource::GetSectorWorldData( int xSector, int zSector, WorldYArray& yArray,int level /*= 0*/ ) const
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xSector >= 0 && xSector < mSectorData.RowSize(level) );
		n_assert( zSector >= 0 && zSector < mSectorData.ColSize(level) );
		n_assert( SectorSize == yArray.RowSize() && SectorSize == yArray.ColSize() );

		int startXUnit = xSector << UnitToSector;
		int startZUnit = zSector << UnitToSector;
		int endXUnit = startXUnit + SectorSize;
		int endZUnit = startZUnit + SectorSize;

		for (int x = startXUnit; x < endXUnit; x++)
		{
			for (int z = startZUnit; z < endZUnit; z++)
			{
				yArray.At( x - startXUnit, z - startZUnit ) = GetWorldYByUnit(x, z, level);
			}
		}
	}

	Math::bbox TerrainDataSource::GetSectorWorldBBox(int xSector,int zSector,int level) const
	{
		Math::bbox localBox = GetSectorLocalBBox(xSector, zSector, level);

		return localBox;
	}

	Math::bbox TerrainDataSource::GetSectorLocalBBox(int xSector,int zSector,int level) const
	{
		n_assert( level >= 0 && level < mSectorData.GetMipCount() );
		n_assert( xSector >= 0 && xSector < mSectorData.RowSize(level) );
		n_assert( zSector >= 0 && zSector < mSectorData.ColSize(level) );

		uint16 minY = mSectorData.At(xSector, zSector, level).mMinLocalY;
		uint16 maxY = mSectorData.At(xSector, zSector, level).mMaxLocalY;

		int minXUnit = xSector << (UnitToSector + level);
		int minZUnit = zSector << (UnitToSector + level);
		int maxXUnit = minXUnit + (UnitsInSector << level);
		int maxZUnit = minZUnit + (UnitsInSector << level);

		Math::bbox box;

		box.pmin.set( (Math::scalar)minXUnit, (Math::scalar)minY, (Math::scalar)minZUnit);
		box.pmax.set( (Math::scalar)maxXUnit, (Math::scalar)maxY, (Math::scalar)maxZUnit);

		Math::point xyzRatio(mXZRatio.x(), mYRatio, mXZRatio.y());

		box.pmin *= xyzRatio;
		box.pmax *= xyzRatio;

		return box;
	}

	void TerrainDataSource::CopySectorDatatFrom(const GPtr<TerrainDataSource>& obj)
	{
		// to do
	}

	void TerrainDataSource::CalculateSectorInfoDataByUnit(int xUnit, int zUnit, int xSize, int zSize)
	{
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize( 0 ) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize( 0 ) << UnitToSector) );
		n_assert( xSize > 0 && xUnit + xSize - 1 <= (mSectorData.RowSize( 0 ) << UnitToSector) );
		n_assert( zSize > 0 && zUnit + zSize - 1 <= (mSectorData.ColSize( 0 ) << UnitToSector) );

		int levelCount = mSectorData.GetMipCount();
		int xStartSector = xUnit >> UnitToSector;
		int zStartSector = zUnit >> UnitToSector;
		int xEndSector = (xUnit + xSize) >> UnitToSector;
		int zEndSector = (zUnit + zSize) >> UnitToSector;

		int maxXSectorIndex = mSectorData.RowSize( 0 ) - 1;
		int maxZSectorIndex = mSectorData.ColSize( 0 ) - 1;

		xEndSector = xEndSector > maxXSectorIndex ? maxXSectorIndex : xEndSector;
		zEndSector = zEndSector > maxZSectorIndex ? maxZSectorIndex : zEndSector;

		for (int x = xStartSector; x <= xEndSector; x++)
		{
			for (int z = zStartSector; z <= zEndSector; z++)
			{
				mSectorData.At(x, z, 0).mGeoError = 0.0f;
				// calculate the minmax localY int the level zero
				CalculateASectorMinMaxYDataBySector(x, z);
			}
		}

		for (int level = 1; level < levelCount; level++)
		{
			
			xStartSector = xStartSector >> 1;
			xEndSector = xEndSector >> 1;
			zStartSector = zStartSector >> 1;
			zEndSector = zEndSector >> 1;

			for (int x = xStartSector; x <= xEndSector; x++)
			{
				for (int z = zStartSector; z <= zEndSector; z++)
				{
					int minLocalY = +MaxLocalY;
					int maxLocalY = -MaxLocalY;

					CalculateASectorGeoErrorDataBySector(x, z, level);
					CalculateASectorMinMaxLocalYDataBySector(x, z, level, maxLocalY, minLocalY);

					mSectorData.At(x, z, level).mMaxLocalY = maxLocalY;
					mSectorData.At(x, z, level).mMinLocalY = minLocalY;
				}
			}

		}
	}

	void TerrainDataSource::ResetSectorInfo(int xUnit, int zUnit, int xSize, int zSize)
	{
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize( 0 ) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize( 0 ) << UnitToSector) );
		n_assert( xSize > 0 && xUnit + xSize - 1 <= (mSectorData.RowSize( 0 ) << UnitToSector) );
		n_assert( zSize > 0 && zUnit + zSize - 1 <= (mSectorData.ColSize( 0 ) << UnitToSector) );

		int levelCount = mSectorData.GetMipCount();
		int xStartSector = xUnit >> UnitToSector;
		int zStartSector = zUnit >> UnitToSector;
		int xEndSector = (xUnit + xSize) >> UnitToSector;
		int zEndSector = (zUnit + zSize) >> UnitToSector;

		int maxXSectorIndex = mSectorData.RowSize( 0 ) - 1;
		int maxZSectorIndex = mSectorData.ColSize( 0 ) - 1;

		xEndSector = xEndSector > maxXSectorIndex ? maxXSectorIndex : xEndSector;
		zEndSector = zEndSector > maxZSectorIndex ? maxZSectorIndex : zEndSector;

		for (int level = 0; level < levelCount; level++)
		{
			for (int x = xStartSector; x <= xEndSector; x++)
			{
				for (int z = zStartSector; z <= zEndSector; z++)
				{
					mSectorData.At(x, z, level).mGeoError = N_FLOAT32_MAX;
					mSectorData.At(x, z, level).mMinLocalY = 0;
					mSectorData.At(x, z, level).mMaxLocalY = MaxLocalY;
				}
			}

			xStartSector = xStartSector >> 1;
			xEndSector = xEndSector >> 1;
			zStartSector = zStartSector >> 1;
			zEndSector = zEndSector >> 1;
		}
	}

	Math::float3 TerrainDataSource::CalculateWorldNormalByUnit(int xUnit, int zUnit, int level) const
	{
		float sx = 0.f;
		float sy = 0.f;

		if ( (xUnit + 1) < GetXUnitCount( level ) && xUnit >= 1)
		{
			float rightWorldY = GetWorldYByUnit( xUnit + 1, zUnit, level);
			float leftWorldY = GetWorldYByUnit( xUnit - 1, zUnit, level);
			sx = rightWorldY - leftWorldY;
		}
		if ( (zUnit + 1) < GetZUnitCount( level ) && zUnit >= 1 )
		{
			float topWorldY = GetWorldYByUnit( xUnit, zUnit - 1, level );
			float bottomWorldY = GetWorldYByUnit( xUnit, zUnit + 1, level );
			sy = bottomWorldY - topWorldY;
		}

		Math::float2 xzScale = mXZRatio * (float)(1 << level);
		Math::float3 normal(-sx / xzScale.x(), 2.0f, -sy / xzScale.y() );

		normal.normalise();
		return normal;
	}

	bool TerrainDataSource::ResetHeightmpData(int heightmapSize,bool isUsePreData)
	{
		int correctSize = Math::n_clamp(heightmapSize, SectorSize, MaxHeightmapSize);
		int levelCount = 1;

		correctSize = Math::n_nexPowerOfTwo(correctSize - 1);
		levelCount = Math::n_logTwoInt( correctSize >> UnitToSector );
		levelCount++;
		correctSize++;
		mHeightmapSize = correctSize;

		mLocalYArray.Resize(mHeightmapSize, mHeightmapSize, 0);
		mSectorData.Resize(levelCount, SSectorData());
		// holedata consistency with heightmap
		mHoleDataArray.Resize(mHeightmapSize-1, mHeightmapSize-1,0);

		return true;
	}

	bool TerrainDataSource::BuildHeightmpData(int heightmapSize, LocalYArray& yArray)
	{
		int correctSize = Math::n_clamp(heightmapSize, SectorSize, MaxHeightmapSize);
		int levelCount = 1;

		correctSize = Math::n_nexPowerOfTwo(correctSize - 1);
		levelCount = Math::n_logTwoInt( correctSize >> UnitToSector );
		levelCount++;
		correctSize++;

		if (mHeightmapSize !=  correctSize || mHeightmapSize == -1)
		{
			mHeightmapSize = correctSize;
			// clean the heightmap data
			/*mLocalYArray.Clear();
			mSectorData.Clear();*/

			mLocalYArray.Resize(mHeightmapSize, mHeightmapSize);
			mSectorData.Resize(levelCount, SSectorData());
			// holedata consistency with heightmap
			mHoleDataArray.Resize(mHeightmapSize-1, mHeightmapSize-1,0);
		}

		//fill loclaY data
		if (mHeightmapSize != yArray.ColSize())
		{
			int colSize = yArray.ColSize();
			float inverseSize = 1.0f / mHeightmapSize;
			float scale = inverseSize * colSize;

			for (int x = 0; x < mHeightmapSize; x++)
			{
				for (int z = 0; z < mHeightmapSize; z++)
				{
					float X0 = x * scale;
					float Z0 = (int)z * scale;
					int intX0 = (int)X0;
					int intZ0 = (int)Z0;
					float fX = X0 - intX0;
					float fZ = Z0 - intZ0;

					mLocalYArray.At(x, z) = (uint16)(yArray.At(intX0, intZ0) * (1.f - fX) * (1.f - fZ)
						+ yArray.At(intX0 + 1, intZ0) * fX * (1.f - fZ)
						+ yArray.At(intX0, intZ0 + 1) * (1.f - fX) * fZ
						+ yArray.At(intX0 + 1, intZ0 + 1) * fX * fZ);
				}
			}
		}
		else
		{
			SetLocalYArrayByUnit(0, 0, mHeightmapSize, mHeightmapSize, yArray, 0);
		}
		//build sector data
		CalculateSectorInfoDataByUnit(0, 0, mHeightmapSize, mHeightmapSize);
		return true;
	}


//------------------------------------------------------------------------------
//ControlMap methods
//------------------------------------------------------------------------------
	

	bool TerrainDataSource::CreateControlMap(const Resources::ResourceId& resID)
	{
#if __OSX__
        return false;
#else
		Math::Color32 color = Math::Color32(0,0,0,0);
		if (mControlmaps.Size() == 0)
		{
			color.r = 255;
		}

		bool isSucceed = Resources::ImageOperations::CreateTGAImageResAndSave(resID.AsString(), mapSetting.colormapSize, mapSetting.colormapSize, color);
		return isSucceed;
#endif
	}

	void TerrainDataSource::GetControlMapData(Math::Color32* buffer,const int xStart, const int yStart,const int width, const int height)
	{
		const int pixelCnt = width * height;
		for (int i = 0; i < mControlmaps.Size(); i++)
		{
			if(GetImagesData(mControlmaps[i],xStart,yStart,width,height,buffer+i*pixelCnt,COLOR32))
				continue;
			Memory::Fill(buffer + i * pixelCnt, pixelCnt * sizeof(Math::Color32), 0);
		}
	}

	void TerrainDataSource::GetControlMapData(Math::ColorF* buffer,const int xStart, const int yStart, const int width, const int height)
	{
		const int pixelCnt = width * height;
		for (int i = 0; i < mControlmaps.Size(); i++)
		{
			if(GetImagesData(mControlmaps[i],xStart,yStart,width,height,buffer+i*pixelCnt,COLORF))
				continue;
			Memory::Fill(buffer + i * pixelCnt, pixelCnt * sizeof(Math::ColorF), 0);
		}
	}

	void TerrainDataSource::SetControlMapData(Math::Color32* buffer,const int xStart,const int yStart,const int width,const int height)
	{
		for (int i = 0; i < mControlmaps.Size(); i++)
		{
			SetImagesData(mControlmaps[i],xStart,yStart,width,height,buffer + i*width*height,COLOR32);
			if (mControlmaps[i])
				Graphic::GraphicSystem::Instance()->UpdateTexture(mControlmaps[i]->GetHandle(), &_UpdateTextureFunction,mControlmaps[i]);
		}
		RefreshBasemap(xStart / (float)mapSetting.colormapSize, yStart / (float)mapSetting.colormapSize, 
			width / (float)mapSetting.colormapSize, height / (float)mapSetting.colormapSize);
	}

	void TerrainDataSource::SetControlMapData(Math::ColorF* buffer,const int xStart,const int yStart,const int width, const int height)
	{
		for (int i = 0; i < mControlmaps.Size(); i++)
		{
			SetImagesData(mControlmaps[i],xStart,yStart,width,height,buffer + i*width*height,COLORF);
			if (mControlmaps[i])
				Graphic::GraphicSystem::Instance()->UpdateTexture(mControlmaps[i]->GetHandle(), &_UpdateTextureFunction, mControlmaps[i]);
		}
		RefreshBasemap(xStart / (float)mapSetting.colormapSize, yStart / (float)mapSetting.colormapSize, 
			width / (float)mapSetting.colormapSize, height / (float)mapSetting.colormapSize);
	}
	
	void TerrainDataSource::RefreshControlMap(const int index,int texNumBeforeDel)
	{
		int nChanelCount = texNumBeforeDel;
		int width       = mapSetting.controlmapSize;
		int height      = width;

		if ( index >= nChanelCount )
		{
			return;
		}

		int nMapCount    = (nChanelCount + 3) / 4 ;
		int deleteChanelIndex = index;

		ubyte** pixel = n_new_array(ubyte*, nMapCount);
		ubyte* weightData = n_new_array(ubyte, nChanelCount);

		for (int mapIndex = 0; mapIndex < nMapCount; ++mapIndex)
		{
			GPtr<Resources::ImageRes> imageRes = mControlmaps[mapIndex]->GetRes().downcast<Resources::ImageRes>();
			const GPtr<Resources::ImageData>& pImageData = imageRes->GetImageData();
			n_assert( imageRes->GetPixelFormat() == RenderBase::PixelFormat::A8R8G8B8 );
			n_assert( imageRes->GetWidth() == width );
			n_assert( imageRes->GetHeight() == width );
			
			pixel[mapIndex] = pImageData->Ptr();
		}

		int byteCount = height * width * 4;
		
		for (int i = 0; i < byteCount; i += 4)
		{
			int sum = 0;
			int index = -1;
			int mapIndex = 0;
			int subChanelIndex = 0;
			
			for (int channel = 0; channel < nChanelCount; ++channel)
			{
				mapIndex = channel / 4;
				subChanelIndex = channel % 4;
				subChanelIndex = subChanelIndex & 0x01 ? subChanelIndex : subChanelIndex ^ 0x02;
				weightData[++index] = pixel[ mapIndex ][ i +  subChanelIndex];
				sum += weightData[index];
			}

			sum -= weightData[ deleteChanelIndex ];
			
			if (sum == 0)
			{
				memset(weightData, 0, nChanelCount );
				weightData[0] = 255;
			}
			else
			{
				double multiplier = 255.f / sum ;

				for (int channel = 0; channel < deleteChanelIndex; channel++)
				{
					weightData[channel] = (ubyte)(weightData[channel] * multiplier);
				}

				for (int channel = deleteChanelIndex; channel < nChanelCount - 1; channel++)
				{
					weightData[channel] = (ubyte)(weightData[channel + 1] * multiplier);
				}

				weightData[nChanelCount - 1] = 0;
			}

			for (int channel = 0; channel < nChanelCount; ++channel)
			{
				mapIndex = channel / 4;
				subChanelIndex = channel % 4;
				subChanelIndex = subChanelIndex & 0x01 ? subChanelIndex : subChanelIndex ^ 0x02;
				pixel[ mapIndex ][ i + subChanelIndex ] = weightData[channel];
			}
		}

		n_delete_array(pixel);
		n_delete_array(weightData);

		for (int mapIndex = 0; mapIndex < nMapCount; mapIndex++)
			{
			if (mControlmaps[mapIndex])
			{
				Graphic::GraphicSystem::Instance()->UpdateTexture(mControlmaps[mapIndex]->GetHandle(), &_UpdateTextureFunction, mControlmaps[mapIndex]);
			}
		}

	}

	//------------------------------------------------------------------------------
	//BaseMap methods
	//------------------------------------------------------------------------------

	bool TerrainDataSource::IsValidBasemap() const
	{
		return mBaseMap.isvalid();
	}

	bool TerrainDataSource::CreateBaseMap(const Resources::ResourceId& resID)
	{
#if __OSX__
        return false;
#else
		if(mBaseMap)
			return false;
		Math::Color32 color = Math::Color32 (159,159,159,255);
		bool isSucceed = Resources::ImageOperations::CreateTGAImageResAndSave(resID.AsString(), mapSetting.basemapSize, mapSetting.basemapSize, color);
		return isSucceed;
#endif
	}

	void TerrainDataSource::SetBaseMap(GPtr<Resources::TextureResInfo>& texInfo)
	{
		mBaseMap = texInfo;
	}

	void TerrainDataSource::GetBaseMapData(Math::Color32* buffer,const int xStart,const int yStart,const int width,const int height)
	{
		if( GetImagesData(mBaseMap,xStart,yStart,width,height,buffer,COLOR32) )
			return;
		memset (buffer, 0, width * height * sizeof(Math::Color32));
	}

	void TerrainDataSource::GetBaseMapData(Math::ColorF* buffer,const int xStart,const int yStart,const int width,const int height)
	{
		if( GetImagesData(mBaseMap,xStart,yStart,width,height,buffer,COLORF) )
			return;
		memset (buffer, 0, width * height * sizeof(Math::ColorF));
	}

	void TerrainDataSource::SetBaseMapData(Math::Color32* buffer,const int xStart,const int yStart,const int width,const int height)
	{
		SetImagesData(mBaseMap,xStart,yStart,width,height,buffer,COLOR32);
		mBaseMap = mBaseMap;
		if (mBaseMap)
			Graphic::GraphicSystem::Instance()->UpdateTexture(mBaseMap->GetHandle(), &_UpdateTextureFunction, mBaseMap);
		//RefreshBasemap(xStart,yStart,width,height);
	}

	void TerrainDataSource::SetBaseMapData(Math::ColorF* buffer,const int xStart,const int yStart,const int width,const int height)
	{
		SetImagesData(mBaseMap,xStart,yStart,width,height,buffer,COLORF);
		mBaseMap = mBaseMap;
		if (mBaseMap)
			Graphic::GraphicSystem::Instance()->UpdateTexture(mBaseMap->GetHandle(), &_UpdateTextureFunction, mBaseMap);
		//RefreshBasemap(xStart,yStart,width,height);
	}


	struct TargetData
	{
		typedef uint ColorType;
		int width;
		int height;
		int refreshWidth;
		int refreshHeight;
		int beginX;
		int beginY;
		ColorType* data;

		TargetData()
			:refreshWidth(0)
			,refreshHeight(0)
			,width(0)
			,height(0)
			,beginX(0)
			,beginY(0)
			,data(NULL)
		{

		}
		void SetColor(int biasX, int biasY, const Math::Color32& color)
		{
			*(data + ((biasY + beginY) * width + (biasX + beginX))) = color.HexARGB();
		}
	private:
		TargetData(const TargetData&);
	};

	struct BrushData
	{
		typedef Math::Color32 ColorType;
		int absoluteWidth;
		int absoluteHeight;
		int mip;
		int channel;
		float ddX;
		float ddY;
		float ofX;
		float ofY;
		ColorType* data;

		BrushData()
			:absoluteWidth(0)
			,absoluteHeight(0)
			,ddX(0.0f)
			,ddY(0.0f)
			,ofX(0.0f)
			,ofY(0.0f)
			,channel(0)
			,mip(1)
			,data(NULL)
		{

		}
		// Sx: sample coord x, Mw: map width.
		// Bw: base map width, Tw: terrain width(in world).
		// TOw: brush map tile offset x(in world).
		// TSw: brush map tile width(in world).
		// Sx / Mw = [(x / Bw) * Tw + TOx] / Tw * (Tw / TSw)
		//	 	   = x * (Tw / Bw / TSw) + TOx / TSw
		//		   = x * ddx + ofx
		// ddx = (Tw / Bw / TSw)
		// ofx = TOx / TSw
		// ddy the sampe as ddx.
		// ofy the sampe as ofx.
		// param y the sampe as x.
		ColorType* Sample(int x, int y) const
		{
			float fx = ddX * x + ofX;
			float fy = ddY * y + ofY;

			fx -= floorf(fx);
			fy -= floorf(fy);

			int sx = (int)(fx * absoluteWidth);
			int sy = (int)(fy * absoluteHeight);

			return data + (sy * absoluteWidth + sx);
		}
	private:
		BrushData(const BrushData&);
	};

	struct BlendData
	{
		int absoluteWidth;
		int absoluteHeight;
		int floatSize;
		float ddX;
		float ddY;
		float* data;
		BlendData()
			:absoluteWidth(0)
			,absoluteHeight(0)
			,ddX(0.0f)
			,ddY(0.0f)
			,floatSize(0)
			,data(NULL)
		{

		}

		float* Sample(int biasX, int biasY) const
		{
			int sx = int(biasX * ddX);
			int sy = int(biasY * ddY);
			return data + (int)(sy * absoluteWidth * floatSize + sx * floatSize);
		}
	private:
		BlendData(const BlendData&);
	};


	void TerrainDataSource::RefreshBasemap(float xStart /* = 0.0f */, float yStart /* = 0.0f */, float relativeWidth /* = 1.0f */, float relativeHeight /* = 1.0f */)
	{
		if ( !mBaseMap )
		{
			return;
		}

		TargetData targetData;
		BlendData blendData;
		Util::Array<BrushData> brushs;
		Math::float2 terrainSize = mXZRatio * (float)(mHeightmapSize - 1);

		// target data.
		targetData.width = mapSetting.basemapSize;
		targetData.height = mapSetting.basemapSize;
		targetData.refreshWidth = (int)(relativeWidth * mapSetting.basemapSize);
		targetData.refreshHeight = (int)(relativeHeight * mapSetting.basemapSize);
		targetData.beginX = (int)(xStart * mapSetting.basemapSize);
		targetData.beginY = (int)(yStart * mapSetting.basemapSize);
		GPtr<Resources::ImageRes> imageRes = mBaseMap->GetRes().downcast<Resources::ImageRes>();
		//n_assert(imageRes->GetPixelFormat() == PixelFormat::A8R8G8B8);
		targetData.data = reinterpret_cast<TargetData::ColorType*>( imageRes->GetImageData()->Ptr());

		// blend data.
		blendData.absoluteWidth = (int)(relativeWidth * mapSetting.controlmapSize);
		blendData.absoluteHeight = (int)(relativeHeight * mapSetting.controlmapSize);
		blendData.ddX = (float)blendData.absoluteWidth / (float)targetData.refreshWidth;
		blendData.ddY = (float)blendData.absoluteHeight / (float)targetData.refreshHeight;
		blendData.floatSize = mControlmaps.Size() * (sizeof(Math::ColorF) / sizeof(float));
		blendData.data = n_new_array(float, blendData.floatSize * blendData.absoluteWidth * blendData.absoluteHeight);

		_GetBlendWeights((int)(xStart * mapSetting.colormapSize), (int)(yStart * mapSetting.colormapSize),
			blendData.absoluteWidth, blendData.absoluteHeight, blendData.data);

		// texture brush data.
		brushs.Resize(mLayermaps.Size(), BrushData());
		for (int i = 0; i < mLayermaps.Size(); ++i)
		{
			GPtr<Resources::ImageRes> texture = mLayermaps[i].resourceInfo->GetRes().downcast<Resources::ImageRes>();
			brushs[i].channel = i;

			// ddx,ddy,ofx,ofy. see BrushData::Sample()
			brushs[i].ddX = terrainSize.x() / (float)mapSetting.controlmapSize / mLayermaps[i].layermapTileSize.x();
			brushs[i].ddY = terrainSize.y() / (float)mapSetting.controlmapSize / mLayermaps[i].layermapTileSize.y();
			brushs[i].ofX = mLayermaps[i].layermapOffset.x() / mLayermaps[i].layermapTileSize.x();
			brushs[i].ofY = mLayermaps[i].layermapOffset.y() / mLayermaps[i].layermapTileSize.y();

			int mipCount = texture->GetMipMapLevel();
			if ( 2 > mipCount)
			{
				brushs[i].mip = 0;
				brushs[i].absoluteWidth = texture->GetWidth();
				brushs[i].absoluteHeight = texture->GetHeight();
			}
			else
			{
				int width = texture->GetWidth();
				int height = texture->GetHeight();

				float w = 1.0f / brushs[i].ddX;
				float h = 1.0f / brushs[i].ddY;

				float lv_w = Math::n_log2(width / w);
				float lv_h = Math::n_log2(height / h);
				int level = int((lv_h + lv_w) * 0.5f);

				level = Math::n_clamp(level, 0, mipCount - 1);

				//for decompress
				int minSize;
				RenderBase::PixelFormat::Code _pixCode = texture->GetPixelFormat();
				if ( _pixCode == RenderBase::PixelFormat::DXT1 ||
					_pixCode == RenderBase::PixelFormat::DXT2 ||
					_pixCode == RenderBase::PixelFormat::DXT3 ||
					_pixCode == RenderBase::PixelFormat::DXT4 ||
					_pixCode == RenderBase::PixelFormat::DXT5 )
				{
					minSize = 4;
				}
				else
				{
					minSize = 1;

				}
				
				int mipWidth	= Math::n_max (width >> level, minSize);                                                                                                               
				int mipHeight	= Math::n_max (height >> level, minSize);

				brushs[i].mip = level;
				brushs[i].absoluteWidth = mipWidth;
				brushs[i].absoluteHeight = mipHeight;
			}

			brushs[i].data = n_new_array(BrushData::ColorType, brushs[i].absoluteWidth * brushs[i].absoluteHeight);

			if(!texture->GetPixels(brushs[i].mip, brushs[i].data))
			{
				Memory::Clear(brushs[i].data, brushs[i].mip * brushs[i].absoluteWidth * brushs[i].absoluteHeight * sizeof(BrushData::ColorType));		
				n_warning( "Failed to get pixels from texture: %s", mLayermaps[i].resourceInfo->GetResID().Value());
			}
		}


		// blending..

		for (int pixelY = 0; pixelY < targetData.refreshHeight; ++pixelY)		
		{
			for (int pixelX = 0; pixelX < targetData.refreshWidth; ++pixelX)
			{
				const int rgb = 3;
				float blendColor[rgb] = {0.0f};
				float* blendWeights = blendData.Sample(pixelX, pixelY);  
				int x = pixelX + targetData.beginX;
				int y = pixelY + targetData.beginY;
				for (int channel = 0; channel < brushs.Size(); ++channel)
				{
					Math::Color32* color = brushs[channel].Sample(x, y);
					blendColor[0] += (color->r * blendWeights[channel]);
					blendColor[1] += (color->g * blendWeights[channel]);
					blendColor[2] += (color->b * blendWeights[channel]);
				}

				int cr = blendColor[0] < 255.0f ? (int)blendColor[0] : 255;
				int cg = blendColor[1] < 255.0f ? (int)blendColor[1] : 255;
				int cb = blendColor[2] < 255.0f ? (int)blendColor[2] : 255;
				targetData.SetColor(pixelX, pixelY, Math::Color32((ubyte)cr, (ubyte)cg, (ubyte)cb, (ubyte)255));
			}
		}

		//SetBasemapDirty(false);
		Graphic::GraphicSystem::Instance()->UpdateTexture(mBaseMap->GetHandle(), &_UpdateTextureFunction, mBaseMap);
		

		for (int i = 0; i < brushs.Size(); ++i)
		{
			n_delete_array(brushs[i].data);
		}

		if (blendData.data)
		{
			n_delete_array(blendData.data);
		}
	}
	//------------------------------------------------------------------------------
	//ColorMap methods
	//------------------------------------------------------------------------------
	bool TerrainDataSource::IsValidColormap() const
	{
		return mColorMap.isvalid();
	}
	bool TerrainDataSource::CreateColorMap(const Resources::ResourceId& resID)
	{
#if __OSX__
        return false;
#else
		if(mColorMap)
			return false;
		Math::Color32 color = Math::Color32(0,0,0,0);
		bool isSucceed = Resources::ImageOperations::CreateTGAImageResAndSave(resID.AsString(), mapSetting.colormapSize, mapSetting.colormapSize, color);
		return isSucceed;
#endif
	}
	void TerrainDataSource::SetColorMap(GPtr<Resources::TextureResInfo>& texInfo)
	{
		mColorMap = texInfo;
	}
	void TerrainDataSource::GetColorMapData(Math::Color32* buffer,const int xStart /* = 0 */,const int yStart /* = 0 */,const int width /* = -1 */,const int height /* = -1 */)
	{
		if(GetImagesData(mColorMap,xStart,yStart,width,height,buffer,COLOR32))
			return;
		memset (buffer, 0, width * height * sizeof(Math::Color32));
	}
	void TerrainDataSource::GetColorMapData(Math::ColorF* buffer,const int xStart /* = 0 */,const int yStart /* = 0 */,const int width /* = -1 */,const int height /* = -1 */)
	{
		if(GetImagesData(mColorMap,xStart,yStart,width,height,buffer,COLORF))
			return;
		memset (buffer, 0, width * height * sizeof(Math::ColorF));
	}
	void TerrainDataSource::SetColorMapData(Math::ColorF* buffer,const int xStart /* = 0 */,const int yStart /* = 0 */,const int width /* = -1 */,const int height /* = -1 */)
	{
		SetImagesData(mColorMap,xStart,yStart,width,height,buffer,COLORF);
		if (mColorMap)
			Graphic::GraphicSystem::Instance()->UpdateTexture(mColorMap->GetHandle(), &_UpdateTextureFunction, mColorMap);
		//RefreshBasemap(xStart,yStart,width,height);
	}
	void TerrainDataSource::SetColorMapData(Math::Color32* buffer,const int xStart /* = 0 */,const int yStart /* = 0 */,const int width /* = -1 */,const int height /* = -1 */)
	{
		SetImagesData(mColorMap,xStart,yStart,width,height,buffer,COLOR32);
		if (mColorMap)
			Graphic::GraphicSystem::Instance()->UpdateTexture(mColorMap->GetHandle(), &_UpdateTextureFunction, mColorMap);
		//RefreshBasemap(xStart,yStart,width,height);
	}
	//------------------------------------------------------------------------------
	//other unclassify methods
	//------------------------------------------------------------------------------
	void TerrainDataSource::SaveAllMaps()
	{
		SaveBaseMap();
		SaveColorMap();
		SaveControlMap();
	}

	void TerrainDataSource::SaveControlMap()
	{
		for (int i=0; i < mControlmaps.Size(); ++i)
		{
			_saveImage(mControlmaps[i]);
		}
	}

	void TerrainDataSource::SaveColorMap()
	{
		_saveImage(mColorMap);
	}

	void TerrainDataSource::SaveBaseMap()
	{
		_saveImage(mBaseMap);
	}

	void TerrainDataSource::_GetBlendWeights(int xStart, int yStart, int width, int height, float* weights)
	{
		int elemCount = width * height;

		Math::Color32* tmpBuf = n_new_array(Math::Color32, elemCount);
		Math::ColorF* colorDest = reinterpret_cast<Math::ColorF*>(weights);

		int colorsOnElem = mControlmaps.Size();

		for (int a = 0; a < colorsOnElem; ++a)
		{
			GPtr<Resources::ImageRes> texture = mControlmaps[a]->GetRes().downcast<Resources::ImageRes>();
			if (texture.isvalid() && texture->GetState() == Resources::Resource::Loaded) 
			{
				texture->GetPixels(xStart, yStart, width, height, 0, tmpBuf);
			}
			else
			{
				memset (tmpBuf, 0, width * height * sizeof(Math::Color32));
			}
			for (int y = 0; y < elemCount; ++y)
			{
				const Math::Color32& color = tmpBuf[y];
				colorDest[colorsOnElem * y + a] = Math::ColorF(color);
			}
		}
		n_delete_array(tmpBuf);
	}


	bool TerrainDataSource::GetImagesData(GPtr<Resources::TextureResInfo> & texResInfo, int xStart, int yStart, 
		int width, int height, void* buffer, DataType datatype)
	{
		GPtr<Resources::ImageRes> texture = texResInfo->GetRes().downcast<Resources::ImageRes>();

		if (!texture.isvalid() || texture->GetState() != Resources::Resource::Loaded)
		{
			n_warning("data is invalid");
			return false;
		}

		if ( width == -1)
		{
			width = texture->GetWidth() - xStart;
		}

		if (height == -1)
		{
			height = texture->GetHeight() - yStart;
		}

		n_assert( xStart >= 0 && xStart < texture->GetWidth() && "xStart is invalid" );
		n_assert( yStart >= 0 && yStart < texture->GetHeight() && "yStart is invalid" );
		n_assert( width >= 1 && width + xStart <=  texture->GetWidth() && "width is invalid");
		n_assert( height >= 1 && height + yStart <= texture->GetHeight() && "height is invalid");

		if (datatype == COLORF)
		{
			Math::ColorF * dataBuffer = reinterpret_cast<Math::ColorF *>(buffer);
			texture->GetPixels( xStart, yStart, width, height, 0, dataBuffer);
		}
		else if (datatype == COLOR32)
		{
			Math::Color32 * dataBuffer = reinterpret_cast<Math::Color32 *>(buffer);
			texture->GetPixels( xStart, yStart, width, height, 0, dataBuffer);
		}
		return true;
	}

	bool TerrainDataSource::SetImagesData(GPtr<Resources::TextureResInfo> & texResInfo, int xStart, int yStart, 
		int width, int height, void* buffer, DataType datatype)
	{
		GPtr<Resources::ImageRes> texture = texResInfo->GetRes().downcast<Resources::ImageRes>();

		if (!texture.isvalid() || texture->GetState() != Resources::Resource::Loaded)
		{
			n_warning("data is invalid");
			return false;
		}

		if ( width == -1)
		{
			width = texture->GetWidth() - xStart;
		}

		if (height == -1)
		{
			height = texture->GetHeight() - yStart;
		}

		n_assert( xStart >= 0 && xStart < texture->GetWidth() && "xStart is invalid" );
		n_assert( yStart >= 0 && yStart < texture->GetHeight() && "yStart is invalid" );
		n_assert( width >= 1 && width + xStart <=  texture->GetWidth() && "width is invalid");
		n_assert( height >= 1 && height + yStart <= texture->GetHeight() && "height is invalid");

		if (datatype == COLORF)
		{
			Math::ColorF * dataBuffer = reinterpret_cast<Math::ColorF *>(buffer);
			texture->SetPixels( xStart, yStart, width, height, 0, dataBuffer);
		}
		else if (datatype == COLOR32)
		{
			Math::Color32 * dataBuffer = reinterpret_cast<Math::Color32 *>(buffer);
			texture->SetPixels( xStart, yStart, width, height, 0, dataBuffer);
		}
		return true;
	}
	void TerrainDataSource::_saveImage(GPtr<Resources::TextureResInfo> & texResInfo)
	{
		n_assert(IO::AssignRegistry::HasInstance());
		n_assert(Resources::ImageResCodecReg::HasInstance());
		n_assert( texResInfo.isvalid() );

		const Resources::ResourceId &name = texResInfo->GetResID();
		Util::String texName = name.AsString();
		if (texName.FindStringIndex( "sys:TerrainDefault.dds" ) != InvalidIndex)
		{
			return;
		}

		IO::AssignRegistry* pAssignRegistry = IO::AssignRegistry::Instance();
		const Util::String imagePath = pAssignRegistry->ResolveAssigns(name.AsString()).LocalPath();

		Util::String fileExt = name.AsString().GetFileExtension();
		GPtr<Resources::ImageRes> imageRes = texResInfo->GetRes().downcast<Resources::ImageRes>();
#if  __OSX__

#else
		Resources::ImageOperations::SaveTGAImage(imagePath, imageRes);
#endif
	}
	//------------------------------------------------------------------------------
	void TerrainDataSource::_UpdateTextureFunction(RenderBase::Texture::MapInfo& texMap, int width, int height, 
		int depth, RenderBase::PixelFormat::Code format, int mipLevel, void* tag)
	{
		if (format == RenderBase::PixelFormat::A8R8G8B8)
		{
			if (mipLevel == 0)
			{
				if (tag)
				{
					Resources::TextureResInfo* texture = static_cast<Resources::TextureResInfo*>(tag);
					Memory::CopyToGraphicsMemory(texture->GetRes().downcast<Resources::ImageRes>()->GetImageData()->Ptr(), 
						texMap.data, 
						RenderBase::PixelFormat::GetMemorySize(width, height, 1, format));
				}
			}
		}
	}

	//------------------------------------------------------------------------
	void TerrainDataSource::AddLayermap( int layerIndex, LayermapInfo layermapInfo )
	{
		mLayermaps.Append(layermapInfo);
	}

	void TerrainDataSource::DelLayermap( int layerIndex )
	{
		mLayermaps.EraseIndex(layerIndex);
	}

	void TerrainDataSource::SetLayermap( int layerIndex, LayermapInfo layermapInfo )
	{
		mLayermaps[layerIndex] = layermapInfo;
	}

	LayermapInfo TerrainDataSource::GetLayermap( int layerIndex )
	{
		return mLayermaps[layerIndex];
	}

	void TerrainDataSource::SetHoleDataByUnit(int xUnit,int zUnit,uchar val)
	{
		n_assert( xUnit >= 0 && xUnit <= (mSectorData.RowSize(0) << UnitToSector) );
		n_assert( zUnit >= 0 && zUnit <= (mSectorData.ColSize(0) << UnitToSector) );

		mHoleDataArray.At(xUnit, zUnit) = val;
		// content: update sectorData hole info for lod and build primitive,
		// if sector have hole and it's level != 0 (0: detailed level),we force geoError is N_FLOAT32_MAX,
		// in order to achieve see hole
	
		// level 0's holetype
		int xTargetSector = xUnit >> UnitToSector;
		int zTargetSector = zUnit >> UnitToSector;
		HoleType holetype = CalculateMaxDetailedSectorHoleType(xTargetSector,zTargetSector);
		mSectorData.At(xTargetSector, zTargetSector, 0).mHoleType = holetype;

		// other parent's sector holetype
		int levelCount = mSectorData.GetMipCount();
		int xCurLevelSector = xTargetSector;
		int zCurLevelSector = zTargetSector;


		for (int level = 1; level < levelCount; level++)
		{

			xCurLevelSector = xCurLevelSector >> 1;
			zCurLevelSector = zCurLevelSector >> 1;
			int childLevel = level - 1;

			// current level sector's hole type depend ont four child's holetype
			int xChildSector = xCurLevelSector << 1;
			int zChildSector = zCurLevelSector << 1;
			int totalHole(0);
			totalHole += (int) (mSectorData.At(xChildSector, zChildSector, childLevel).mHoleType);
			totalHole += (int) (mSectorData.At(xChildSector+1, zChildSector, childLevel).mHoleType);
			totalHole += (int) (mSectorData.At(xChildSector, zChildSector+1, childLevel).mHoleType);
			totalHole += (int) (mSectorData.At(xChildSector+1, zChildSector+1, childLevel).mHoleType);

			HoleType parentHole(eNotHole);
			if ( totalHole == 0 )
			{
				parentHole = eNotHole; 
			}
			else if ( totalHole == eWholeHole*4 )
			{
				parentHole = eWholeHole;
			}
			else
			{
				parentHole = ePartHole;
			}
			mSectorData.At(xCurLevelSector, zCurLevelSector, level).mHoleType = parentHole;		

		}
	}




}