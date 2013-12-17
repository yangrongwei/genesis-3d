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

#ifndef __TerrainNodeTraverser_H__
#define __TerrainNodeTraverser_H__

#include "terrainfeature/components/TerrainNode.h"

namespace App
{
	class TerrainNodeTraverser
	{
	public:
		enum TraversalMode
		{
			TRAVERSE_PARENTS,	//	Traversal parent
			TRAVERSE_CHILDREN,	//	Traversal children
			TRAVERSE_NEIGHBOR,	//	Traversal neighbor
			TRAVERSE_USER,		//	User traversal
		};

		TerrainNodeTraverser();
		TerrainNodeTraverser(TraversalMode mode);
		virtual ~TerrainNodeTraverser();

		inline void Traverse(TerrainNode& node);

		virtual void Apply(TerrainNode& node);
	protected:
		TraversalMode m_TraversalMode;
	};
	//------------------------------------------------------------------------
	inline 
		void TerrainNodeTraverser::Traverse(TerrainNode& node)
	{
		if ( m_TraversalMode==TRAVERSE_CHILDREN ) 
		{
			node.TraverseChilds(*this);
		}
		else if ( m_TraversalMode==TRAVERSE_PARENTS )
		{
			node.TraverseParent(*this);
		}
		else if ( m_TraversalMode==TRAVERSE_NEIGHBOR )
		{
			node.TraverseNeighbor(*this);
		}
	}
}

#endif // __TerrainNodeTraverser_H__
