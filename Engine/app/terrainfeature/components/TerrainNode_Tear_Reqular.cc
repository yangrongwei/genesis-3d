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
#include "rendersystem/base/VertexBuffer.h"
#include "rendersystem/base/IndexBuffer.h"
#include "rendersystem/base/PrimitiveGroup.h"
#include "graphicsystem/GraphicSystem.h"
#include "terrainfeature/components/TerrainNode.h"
#include "terrainfeature/components/TerrainNodeTraverser.h"

namespace App
{
	using namespace Terrain;
	const int cVertexCount = SectorSize * SectorSize;

	//------------------------------------------------------------------------
	inline int INDEX_FVF_TERRAIN(IndexT x, IndexT y)
	{
		return y + x * SectorSize;
	}
	//------------------------------------------------------------------------
	/**
	* 
	Standard Grid algorithm:
	1, for some render object, if adjoining node has lower precision, interpolate this object's edge vertex and normal. Make sure edge can be sutured
	2, if a render object has hole, if it's lod level can show the hole, render the hole; otherwise, upper the level to make node has higher precision, until can currect show hole 
	Use Bundle's heightError to choose level(See HeightMap).  @ToDo  performance is not good
	*/
	//------------------------------------------------------------------------
	void TerrainNode::_BuildPrimitiveHandle_Reqular(const GPtr<Terrain::TerrainDataSource>& terrainDataSource)
	{
		n_assert(terrainDataSource.isvalid());

		// Build vertex pos,index, uv coordinate

		Graphic::VertexBufferData2 vbd2;
		Graphic::IndexBufferData2 ibd2;

		vbd2.Setup(SectorSize * SectorSize, sizeof(FVF_TERRAIN), 
			RenderBase::BufferData::Static, GetPrimitiveTopology(), true);
		FVF_TERRAIN* verticeData = vbd2.GetBufferPtr<FVF_TERRAIN>();

		m_PositionData.Resize(SectorSize * SectorSize, Resources::Vec3fArray::value_type() );


		const Math::float3 terrainRatio = terrainDataSource->GetTerrainRatio();
		const int xSector = this->x;
		const int zSector = this->y;
		int   curLevelUnitCount = (terrainDataSource->GetHeightMapSize() - 1) >> level;

		int xUnitStart = xSector * UnitsInSector;
		int zUnitStart = zSector * UnitsInSector;
		int xUnitEnd = xUnitStart + SectorSize;
		int zUnitEnd = zUnitStart + SectorSize;

		// Get height data
		Terrain::WorldYArray sectorHeights;
		sectorHeights.Resize( SectorSize, SectorSize, 0.0f );
		terrainDataSource->GetSectorWorldData(xSector, zSector,sectorHeights,level);

		for (int x = xUnitStart; x < xUnitEnd; x++)
		{
			for (int z = zUnitStart; z < zUnitEnd; z++)
			{
				int index = (z - zUnitStart) + (x - xUnitStart) * SectorSize;
				float worldY = sectorHeights.At( x - xUnitStart, z - zUnitStart);
				
				verticeData[index].x = (x << level) * terrainRatio.x();
				verticeData[index].y = worldY;
				verticeData[index].z = (z << level) * terrainRatio.z();
				
				verticeData[index].u = (float)(x * 1.0f / curLevelUnitCount);
				verticeData[index].v = (float)(z * 1.0f / curLevelUnitCount);
				
				Math::float3 normal = terrainDataSource->CalculateWorldNormalByUnit(x, z, level);
				verticeData[index].nx = normal.x();
				verticeData[index].ny = normal.y();
				verticeData[index].nz = normal.z();

				m_PositionData[index].set(verticeData[index].x, verticeData[index].y, verticeData[index].z );
			}
		}

		const int MaxIndexCount =  UnitsInSector * UnitsInSector * 6 ;

		/// index for collision 
		m_IndexData.Clear();
		m_IndexData.Reserve(MaxIndexCount);
		for( uint xx=0; xx < UnitsInSector; ++xx )
		{
			for( uint yy=0; yy < UnitsInSector; ++yy )
			{
				_BuildOneGridIdxData(m_IndexData,xx,yy);
			}
		}

		// all hole, don't need update or render
		HoleType hole_type = terrainDataSource->GetSectorHoleType(this->x, this->y, this->level);
		if ( hole_type == eWholeHole )
		{
			SetRenderEnable(false);
			m_IndexData.Fill(0,m_IndexData.Size(),0);
			return;
		}

		SetRenderEnable( true );

		_FixHeightAndNormal(verticeData,m_PositionData);

#ifdef __GENESIS_EDITOR__
		//beast use
		_SaveUVAndNormal(verticeData);			
#endif

		Util::Array<RenderBase::VertexComponent>& vertexComponents = vbd2.GetVertexComponents();
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Position, 0, RenderBase::VertexComponent::Float3));
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::TexCoord, 0, RenderBase::VertexComponent::Float2));
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Normal, 0, RenderBase::VertexComponent::Float3));

		/// index for render
		Resources::Index16Container indexForRender;
		indexForRender.Reserve(MaxIndexCount);

		if( hole_type == eNotHole )
		{
			for( uint xx=0; xx < UnitsInSector; ++xx )
			{
				for( uint yy=0; yy < UnitsInSector; ++yy )
				{
					_BuildOneGridIdxData(indexForRender,xx,yy);
				}
			}
		}
		else
		{
			//part hole

			const uint AllHoleCountInGrid = (1<<level)*(1<<level);
			IndexT xBase = this->x * UnitsInSector;
			IndexT yBase = this->y * UnitsInSector;

			// part hole
			for( uint xx=0; xx < UnitsInSector; ++xx )
			{
				for( uint yy=0; yy < UnitsInSector; ++yy )
				{
					uint holeInGrid = terrainDataSource->CalcualteMipGridHoleCount(xBase + xx, yBase + yy, this->level );

					if ( holeInGrid ==  AllHoleCountInGrid )	//	all hole
					{
						continue;
					}
					else
					{
						_BuildOneGridIdxData(indexForRender,xx,yy);
					}
				}
			}
		}

		n_assert( !indexForRender.IsEmpty() );

		ibd2.Setup(indexForRender.Size(), RenderBase::BufferData::Static, RenderBase::IndexBufferData::Int16, true);
		ibd2.SetIndices(&indexForRender[0], indexForRender.Size());
		m_IndexData = indexForRender;

		if (m_PrimitiveHandle.IsValid())
		{
			Graphic::GraphicSystem::Instance()->RemovePrimitive(m_PrimitiveHandle);
		}
		m_PrimitiveHandle = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
	}
	//------------------------------------------------------------------------
#ifdef __GENESIS_EDITOR__
	void TerrainNode::_SaveUVAndNormal(const FVF_TERRAIN* verticeData)
	{
		m_texUV.Resize(cVertexCount, Resources::Vec2fArray::value_type());
		m_normalData.Resize(cVertexCount, Resources::Vec3fArray::value_type());
		for (uint xx=0; xx<SectorSize; ++xx)
		{
			for (uint yy=0; yy<SectorSize; ++yy)
			{
				int index = INDEX_FVF_TERRAIN(xx,yy);
				// UV
				m_texUV[index].x() = verticeData[index].u;
				m_texUV[index].y() = verticeData[index].v ;				

				//// Normal
				m_normalData[index].x() = verticeData[index].nx;
				m_normalData[index].y() = verticeData[index].ny;
				m_normalData[index].z() = verticeData[index].nz;				
			}
		}
	}
#endif
	//------------------------------------------------------------------------
	void TerrainNode::_BuildOneGridIdxData(Util::Array<uint16>& indexData, int xx,int yy)
	{
		//lef bottom |_
		indexData.Append( static_cast<ushort>( INDEX_FVF_TERRAIN(xx,yy)     ) );
		indexData.Append( static_cast<ushort>( INDEX_FVF_TERRAIN(xx,yy+1)   ) );
		indexData.Append( static_cast<ushort>( INDEX_FVF_TERRAIN(xx+1,yy+1) ) );


		//right top -|
		indexData.Append( static_cast<ushort>( INDEX_FVF_TERRAIN(xx,yy)     ) );
		indexData.Append( static_cast<ushort>( INDEX_FVF_TERRAIN(xx+1,yy+1) ) );
		indexData.Append( static_cast<ushort>( INDEX_FVF_TERRAIN(xx+1,yy)   ) );
	}
	//------------------------------------------------------------------------
	void TerrainNode::_FixHeightAndNormal(FVF_TERRAIN* heightArray,Resources::PositionData& posData)
	{
		// fix tear. algorithm: according EdgeMask, choose using original height or interpolated height, to make sure has same height with adjoining low precision node
		if ( m_EdgeMask == 0 )
			return;

		/// left node's precision is lower, lower left edge's precision to suture
		if ( m_EdgeMask & (1<<eLeftNeighbor))
		{  
			TerrainNode* pNeighborParent(NULL);
			pNeighborParent = GetNeighborNode(eLeftNeighbor)->GetParentNode();
			while(pNeighborParent->GetNodeDrawMode() != eNodeDrawSelf)
			{
				pNeighborParent = pNeighborParent->GetParentNode();
				if(pNeighborParent == NULL)
					break;
			}

			if(pNeighborParent != NULL)
			{
				int neighborLevel = pNeighborParent->level;
				int step = (int)Math::n_pow((float)2, (float)(neighborLevel -level));
				IndexT xStart = 0;
				for( IndexT y = 0; y < SectorSize - 1; ++y )
				{
					int last = y - y%step;
					int next = y + (step - y%step);
					IndexT iMin = INDEX_FVF_TERRAIN(xStart,last);
					IndexT iMax = INDEX_FVF_TERRAIN(xStart,next);
					float hMin = heightArray[ iMin ].y;
					float hMax = heightArray[ iMax ].y;

					IndexT iY = INDEX_FVF_TERRAIN(xStart, y);
					heightArray[ iY ].y = hMin + (hMax - hMin) * 1.0f/ step * (y%step);

					posData[iY].y() = heightArray[ iY ].y;

					Math::float3 nMin(heightArray[ iMin ].nx, heightArray[ iMin ].ny, heightArray[ iMin ].nz );
					Math::float3 nMax(heightArray[ iMax ].nx, heightArray[ iMax ].ny, heightArray[ iMax ].nz );

					Math::float3 nY = nMin + (nMax - nMin) / (float)step * (float)(y%step);
					nY.normalise();
					heightArray[iY].nx = nY.x();
					heightArray[iY].ny = nY.y();
					heightArray[iY].nz = nY.z();
				}
			}

			
		}

		/// right
		if ( m_EdgeMask & (1<<eRightNeighbor))
		{
			TerrainNode* pNeighborParent(NULL);
			pNeighborParent = GetNeighborNode(eRightNeighbor)->GetParentNode();
			while(pNeighborParent->GetNodeDrawMode() != eNodeDrawSelf)
			{
				pNeighborParent = pNeighborParent->GetParentNode();
				if(pNeighborParent == NULL)
					break;
			}

			if(pNeighborParent != NULL)
			{
				int neighborLevel = pNeighborParent->level;
				int step = (int)Math::n_pow((float)2, (float)(neighborLevel - level));

				IndexT xStart = SectorSize - 1 ;
				for( IndexT y = 0; y < SectorSize - 1; ++y )
				{

					int last = y - y%step;
					int next = y + (step - y%step);
					IndexT iMin = INDEX_FVF_TERRAIN(xStart,last);
					IndexT iMax = INDEX_FVF_TERRAIN(xStart,next);
					float hMin = heightArray[ iMin ].y;
					float hMax = heightArray[ iMax ].y;

					IndexT iY = INDEX_FVF_TERRAIN(xStart, y);
					heightArray[ iY ].y = hMin + (hMax - hMin) * 1.0f/ step * (y%step);

					posData[iY].y() = heightArray[ iY ].y;

					Math::float3 nMin(heightArray[ iMin ].nx, heightArray[ iMin ].ny, heightArray[ iMin ].nz );
					Math::float3 nMax(heightArray[ iMax ].nx, heightArray[ iMax ].ny, heightArray[ iMax ].nz );

					Math::float3 nY = nMin + (nMax - nMin) / (float)step * (float)(y%step);
					nY.normalise();
					heightArray[iY].nx = nY.x();
					heightArray[iY].ny = nY.y();
					heightArray[iY].nz = nY.z();
				}
			}
			
		}

		/// top
		if ( m_EdgeMask & (1<<eUpNeighbor))
		{
			TerrainNode* pNeighborParent(NULL);
			pNeighborParent = GetNeighborNode(eUpNeighbor)->GetParentNode();
			while(pNeighborParent->GetNodeDrawMode() != eNodeDrawSelf)
			{
				pNeighborParent = pNeighborParent->GetParentNode();
				if(pNeighborParent == NULL)
					break;
			}

			if(pNeighborParent != NULL)
			{
				int neighborLevel = pNeighborParent->level;
				int step = (int)Math::n_pow((float)2, (float)(neighborLevel - level));

				IndexT yStart = SectorSize - 1 ;
				for ( IndexT x = 0; x < SectorSize - 1; ++x)
				{
					int last = x - x%step;
					int next = x + (step - x%step);
					IndexT iMin = INDEX_FVF_TERRAIN(last,yStart);
					IndexT iMax = INDEX_FVF_TERRAIN(next,yStart);
					float hMin = heightArray[ iMin ].y;
					float hMax = heightArray[ iMax ].y;

					IndexT iX = INDEX_FVF_TERRAIN(x, yStart);
					heightArray[ iX ].y = hMin + (hMax - hMin) / step * (x%step);

					posData[iX].y() = heightArray[ iX ].y;

					Math::float3 nMin(heightArray[ iMin ].nx, heightArray[ iMin ].ny, heightArray[ iMin ].nz );
					Math::float3 nMax(heightArray[ iMax ].nx, heightArray[ iMax ].ny, heightArray[ iMax ].nz );

					Math::float3 nX = nMin + (nMax - nMin) / (float)step * (float)(x%step);
					nX.normalise();
					heightArray[iX].nx = nX.x();
					heightArray[iX].ny = nX.y();
					heightArray[iX].nz = nX.z();
				}
			}
			
		}

		/// bottom
		if ( m_EdgeMask & (1<<eDownNeighbor))
		{
			TerrainNode* pNeighborParent(NULL);
			pNeighborParent = GetNeighborNode(eDownNeighbor)->GetParentNode();
			while(pNeighborParent->GetNodeDrawMode() != eNodeDrawSelf)
			{
				pNeighborParent = pNeighborParent->GetParentNode();
				if(pNeighborParent == NULL)
					break;
			}

			if(pNeighborParent != NULL)
			{
				int neighborLevel = pNeighborParent->level;
				int step = (int)Math::n_pow((float)2, (float)(neighborLevel - level));

				IndexT yStart = 0;
				for ( IndexT x = 0; x < SectorSize - 1; ++x)
				{
					int last = x - x%step;
					int next = x + (step - x%step);
					IndexT iMin = INDEX_FVF_TERRAIN(last,yStart);
					IndexT iMax = INDEX_FVF_TERRAIN(next,yStart);
					float hMin = heightArray[ iMin ].y;
					float hMax = heightArray[ iMax ].y;

					IndexT iX = INDEX_FVF_TERRAIN(x, yStart);
					heightArray[ iX ].y = hMin + (hMax - hMin) * 1.0f/ step * (x%step);

					posData[iX].y() = heightArray[ iX ].y;

					Math::float3 nMin(heightArray[ iMin ].nx, heightArray[ iMin ].ny, heightArray[ iMin ].nz );
					Math::float3 nMax(heightArray[ iMax ].nx, heightArray[ iMax ].ny, heightArray[ iMax ].nz );

					Math::float3 nX = nMin + (nMax - nMin) / (float)step * (float)(x%step);
					nX.normalise();
					heightArray[iX].nx = nX.x();
					heightArray[iX].ny = nX.y();
					heightArray[iX].nz = nX.z();
				}
			}
		}
	}
}
