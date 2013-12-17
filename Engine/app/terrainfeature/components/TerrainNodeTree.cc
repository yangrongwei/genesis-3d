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
#include "terrainfeature/components/TerrainNodeTree.h"

namespace App
{
	__ImplementClass(TerrainNodeTree, 'TNTR', Core::RefCounted);
	//------------------------------------------------------------------------
	TerrainNodeTree::TerrainNodeTree()
	{

	}
	//------------------------------------------------------------------------
	TerrainNodeTree::~TerrainNodeTree()
	{
		Reset();
	}
	//------------------------------------------------------------------------
	void TerrainNodeTree::Reset()
	{
		SizeT mipCount = m_TerrainTree.GetMipCount();

		for ( IndexT mip = 0; mip < mipCount; ++ mip )
		{
			SizeT rowSize = m_TerrainTree.RowSize(mip);
			SizeT colSize = m_TerrainTree.ColSize(mip);
			for ( IndexT col = 0; col < colSize; ++col )
			{
				for ( IndexT row = 0; row < rowSize;++row )
				{
					TerrainNode* node = m_TerrainTree.At(row,col,mip);
					n_delete(node);
					m_TerrainTree.At(row,col,mip) = NULL;
				}
			}
		}

		m_TerrainTree.Clear();
	}
	//------------------------------------------------------------------------
	void TerrainNodeTree::RebuildAllNodes(const GPtr<Terrain::TerrainDataSource>& terrainDataSource)
	{
		Reset();

		SizeT lodCount = terrainDataSource->GetLevelCount();// + 1;
		m_TerrainTree.Resize(lodCount,NULL);

		for (int level=0; level < lodCount; ++level)
		{
			SizeT rowSize = m_TerrainTree.RowSize(level);
			SizeT colSize = m_TerrainTree.ColSize(level);

			for ( IndexT y = 0; y < colSize; ++y )
			{
				for ( IndexT x = 0; x < rowSize;++x )
				{
					TerrainNode* node = n_new(TerrainNode);

					node->x = x;
					node->y = y;
					node->level = level;
					node->SetGeometryError( terrainDataSource->GetGeometryError(x, y, level) );
					bool bHole = terrainDataSource->GetSectorHoleType(x, y, level) == Terrain::eNotHole ? false: true;
					node->SetHole(bHole);
					Math::bbox bb = terrainDataSource->GetSectorWorldBBox(x, y, level);
					node->SetLocalBoundingBox(bb);

					m_TerrainTree.At(x,y,level) = node;
				}
			}
		}

		// Build node's neighbor and parent-child relationship
		for (int level=0; level < lodCount; ++level)
		{
			SizeT rowSize = m_TerrainTree.RowSize(level);
			SizeT colSize = m_TerrainTree.ColSize(level);

			for ( IndexT y = 0; y < colSize; ++y )
			{
				for ( IndexT x = 0; x < rowSize;++x )
				{
					TerrainNode* node = m_TerrainTree.At(x,y,level);
					n_assert(node);

					// parent
					TerrainNode* parent = GetNode(node->x / 2, node->y / 2, node->level + 1);
					node->SetParentNode(parent);

					// child
					TerrainNode* child_LeftUp = GetNode(node->x * 2, node->y * 2, node->level - 1);
					TerrainNode* child_RightUp = GetNode(node->x * 2 + 1, node->y * 2, node->level - 1);
					TerrainNode* child_LeftDown = GetNode(node->x * 2, node->y * 2 + 1, node->level - 1);
					TerrainNode* child_RightDown = GetNode(node->x * 2 + 1, node->y * 2 + 1, node->level - 1);
					node->SetChildNode(child_LeftUp, eLeftUpChild);
					node->SetChildNode(child_RightUp, eRightUpChild);
					node->SetChildNode(child_LeftDown, eLeftDownChild);
					node->SetChildNode(child_RightDown, eRightDownChild);

					// Neighbor
					TerrainNode* neighbor_Up = GetNode(node->x, node->y + 1, node->level);
					TerrainNode* neighbor_Down = GetNode(node->x, node->y - 1, node->level);
					TerrainNode* neighbor_Left =  GetNode(node->x - 1, node->y, node->level);
					TerrainNode* neighbor_Right = GetNode(node->x + 1, node->y, node->level);
					node->SetNeighborNode(neighbor_Up, eUpNeighbor );
					node->SetNeighborNode(neighbor_Down, eDownNeighbor );
					node->SetNeighborNode(neighbor_Left, eLeftNeighbor );
					node->SetNeighborNode(neighbor_Right, eRightNeighbor );
				}
			}
		}

	}
	//------------------------------------------------------------------------
	TerrainNode* TerrainNodeTree::GetRootNode()
	{
		if ( m_TerrainTree.GetMipCount() > 0 )
		{
			// miparray's highest order save 1*1 root
			return m_TerrainTree.At(0, 0,  m_TerrainTree.GetMipCount() - 1 );
		}
		else
		{
			return NULL;
		}
	}
	//------------------------------------------------------------------------
	TerrainNode* 
		TerrainNodeTree::GetNode(IndexT row, IndexT col, IndexT level)
	{
		if ( level >= 0 && level < m_TerrainTree.GetMipCount() )
		{
			SizeT rowSize = m_TerrainTree.RowSize(level);
			SizeT colSize = m_TerrainTree.ColSize(level);
			if ( row >= 0 && row < rowSize 
				&& col >= 0 && col < colSize )
			{
				return m_TerrainTree.At(row,col,level); 
			}
		}
		return NULL;
	}
}
