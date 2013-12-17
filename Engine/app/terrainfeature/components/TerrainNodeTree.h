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

#ifndef __TerrainNodeTree_H__
#define __TerrainNodeTree_H__

#include "terrainfeature/components/TerrainNode.h"
#include "util/mipmaparray.h"
#include "terrainsystem/TerrainDataSource.h"


namespace App
{
	struct NodePos
	{
		int x;
		int y;
	};


	class TerrainNodeTree: public Core::RefCounted
	{
		__DeclareSubClass(TerrainNodeTree, Core::RefCounted);
	public:
		TerrainNodeTree();
		virtual ~TerrainNodeTree();

		/// Reset terrain node tree to default, 0 node
		void Reset();

		/// Get tree's depth. [ 0,GetDepth() )
		SizeT GetDepth() const;

		/// get some level node count in X dir
		SizeT GetRowSize(int depth) const;

		/// get some level node count in Y dir
		SizeT GetColSize(int depth) const;

		/// Using heightMap to rebuild all terrain node. Offset is all node's offset
		void RebuildAllNodes(const GPtr<Terrain::TerrainDataSource>& terrainDataSource);

		/// Get root node, return NULL if invalid
		TerrainNode* GetRootNode();

		/// Get node in pos(row,col) in level, return NULL if invalid
		TerrainNode* GetNode(IndexT row, IndexT col, IndexT level);

	protected:
		typedef Util::MipmapArray<TerrainNode*> TerrainTree;

		TerrainTree m_TerrainTree;
	};

	//------------------------------------------------------------------------
	inline
		SizeT
		TerrainNodeTree::GetDepth() const
	{
		return m_TerrainTree.GetMipCount();
	}
	//------------------------------------------------------------------------
	inline 
		SizeT
		TerrainNodeTree::GetRowSize(int depth) const
	{
		if ( depth < m_TerrainTree.GetMipCount() )
		{
			return m_TerrainTree.RowSize(depth);
		}
		return 0;
	}
	//------------------------------------------------------------------------
	inline
		SizeT
		TerrainNodeTree::GetColSize(int depth) const
	{
		if ( depth < m_TerrainTree.GetMipCount() )
		{
			return m_TerrainTree.ColSize(depth);
		}
		return 0;
	}

}

#endif // __TerrainNodeTree_H__
