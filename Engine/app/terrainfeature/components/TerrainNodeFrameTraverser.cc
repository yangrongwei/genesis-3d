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
#include "TerrainNodeFrameTraverser.h"
#include "terrainfeature/components/TerrainRenderComponent.h"

namespace App
{
	//------------------------------------------------------------------------
	MarkNodeDrawModeTraverser::MarkNodeDrawModeTraverser(NodeDrawMode drawMode, TerrainNodeTraverser::TraversalMode m )
		: TerrainNodeTraverser(m)
		, m_drawMode(drawMode)
	{
	}
	//------------------------------------------------------------------------
	void MarkNodeDrawModeTraverser::Apply(TerrainNode& node)
	{
		node.SetNodeDrawMode(m_drawMode);
		Traverse(node);
	}
	//------------------------------------------------------------------------
	UpdateTerrainLodLevelTraverser::UpdateTerrainLodLevelTraverser(float cameraFactor,
		const Math::vector& cameraLocalPos, float squareNodeDistance)
		: TerrainNodeTraverser(TRAVERSE_CHILDREN)
		, m_MarkLodParentDrawedTraverser(eNodeDrawParent)
	{
		m_CameraFactor =  cameraFactor;
		m_CameraLocalPos = cameraLocalPos;
		m_LodMaxLevel = 0;
		m_SquareNodeDistance = squareNodeDistance;
	}
	//------------------------------------------------------------------------
	void UpdateTerrainLodLevelTraverser::Apply(TerrainNode& node)
	{
	/*algorithm: see W. de Boer 2000 calculation
	    don't need to subdivision condition: D >= K*¦Ä/¦Ñ
										     because: CF = K/maxPixError											 
											=> D >= CF*¦Ä
	    
	 */
		float distanceSquared = node.GetLocalBoundingBox().distancesq( m_CameraLocalPos );

		float nodeGeoError = node.GetGeometryError();
		if ( node.level > 0 && node.HaveHole() )
		{// fore split for see hole
			nodeGeoError = N_FLOAT32_MAX;
		}
		float distSquaredTransition = m_CameraFactor * nodeGeoError;

		distSquaredTransition *= distSquaredTransition;

		bool bNeedSubdivision = ( node.level > m_LodMaxLevel )
			&& ( distanceSquared < distSquaredTransition  );

		if(!bNeedSubdivision)
		{// don't need to split,then render

			node.SetNodeDrawMode(  eNodeDrawSelf );
			node.SetUseBaseMap( distanceSquared > m_SquareNodeDistance );
			m_MarkLodParentDrawedTraverser.Traverse(node);
		}
		else
		{	// needs split
			node.SetNodeDrawMode( eNodeDrawChild );
			Traverse(node);
		}
	}
	//------------------------------------------------------------------------
	LevelupNeighborLODTraverser::LevelupNeighborLODTraverser(const Math::vector& cameraLocalPos,	float squareNodeDistance)	
		: TerrainNodeTraverser(TRAVERSE_CHILDREN) 
		, m_MarkLodParentDrawedTraverser(eNodeDrawParent)
	{
		m_CameraLocalPos = cameraLocalPos;
		m_SquareNodeDistance = squareNodeDistance;
	}
	//------------------------------------------------------------------------
	void LevelupNeighborLODTraverser::Apply(TerrainNode& node)
	{
		if (node.GetNodeDrawMode() == eNodeDrawParent )
		{
			return;
		}
		else if ( node.GetNodeDrawMode()  == eNodeDrawSelf )
		{
			for (int i=eLeftNeighbor;i<=eDownNeighbor;i++)
			{
				TerrainNode* neighbor = node.GetNeighborNode(i);

				if(!neighbor)
				{
					continue;;
				}

				TerrainNode* neighborParent;

				int dLevel = 0;
				for(dLevel=0; dLevel < 4; ++dLevel)
				{
					neighborParent = neighbor->GetParentNode();
					if (neighborParent && neighborParent->GetNodeDrawMode() == eNodeDrawParent)
						neighbor = neighborParent;
					else
						break;
				}

				if(dLevel = 4 && neighborParent && neighborParent->GetNodeDrawMode() == eNodeDrawParent)
				{
					// Neighbor node's parent node is eNodeDrawParent, means adjoining render object's Lod level is higher than current node
					//and difference is bigger than 4, levelIp neighbor
					LevelUpNode(*neighborParent);
				}
			}
		}
		else // if (node.m_drawMode == eNodeDrawChild)
		{
			Traverse(node);
		}
	}
	//------------------------------------------------------------------------
	void LevelupNeighborLODTraverser::LevelUpNode(TerrainNode& node)
	{
		TerrainNode* parent = node.GetParentNode();
		if ( parent == NULL )
		{
			return;
		}

		if (parent->GetNodeDrawMode() == eNodeDrawParent)
		{
			// keep find parent
			LevelUpNode(*parent);
		}
		else if ( parent->GetNodeDrawMode() == eNodeDrawSelf )
		{
			for (int i=eLeftUpChild;i<=eRightDownChild;i++)
			{
				TerrainNode* childNode = parent->GetChildNode(i);
				n_assert(childNode);	//	parent nod must has 4 children

				childNode->SetNodeDrawMode( eNodeDrawSelf );

				Math::scalar dis_sq = node.GetLocalBoundingBox().distancesq( m_CameraLocalPos );
				bool useBaseMap =  ( dis_sq > m_SquareNodeDistance );
				childNode->SetUseBaseMap( useBaseMap );

				// set child eNodeDrawParent
				m_MarkLodParentDrawedTraverser.Traverse(node);
			}

			parent->SetNodeDrawMode( eNodeDrawChild );

			// parent and child node's status changed, parent must be checked.
			Traverse(*parent);

		}
		/** else if eNodeDrawChild, impossible 
		ensure node pyramid from top to bottom, in eNodeDrawChild -> eNodeDrawSelf -> eNodeDrawParent order¡£
		_ForceSplit is from eNodeDrawParent search back.
		**/
		return;
	}
	//------------------------------------------------------------------------
	BuildEdgeMaskTraverser::BuildEdgeMaskTraverser()
		: TerrainNodeTraverser(TRAVERSE_CHILDREN)  
	{

	}
	//------------------------------------------------------------------------
	void BuildEdgeMaskTraverser::Apply(TerrainNode& node)
	{
		if ( node.GetNodeDrawMode() == eNodeDrawSelf )
		{
			/// compute and check edge mask
			int edgeMask = node.ComputeNodeEdgeMask();
			if ( edgeMask != node.GetEdgeMask() || node.m_NeedRebuild)
			{
				node.SetEdgeMask(edgeMask);
				node.RequestBuildPritiveHandle();
			}
		}
		else
		{
			Traverse(node);
		}
	}
	//------------------------------------------------------------------------
	BuildPrimitiveTraverser::BuildPrimitiveTraverser(const GPtr<Terrain::TerrainDataSource> &terrainDataSource)
		: TerrainNodeTraverser(TRAVERSE_CHILDREN) 
		, m_TerrainDataSource(terrainDataSource)
	{
		n_assert(m_TerrainDataSource);
	}
	//------------------------------------------------------------------------
	void BuildPrimitiveTraverser::Apply(TerrainNode& node)
	{
		if ( node.GetNodeDrawMode() == eNodeDrawSelf )
		{
			/// Rebuild if need
			if ( node.IsNeedBulidPritiveHandle() )
			{
				node.BuildPrimitiveHandleIfNeed(m_TerrainDataSource);
			}
		}
		else
		{
			Traverse(node);
		}
	}
	//------------------------------------------------------------------------
	BuildGraphicObjectTraverser::BuildGraphicObjectTraverser(TerrainRenderComponent* comObj)
		: TerrainNodeTraverser(TRAVERSE_CHILDREN) 
		, m_TerrainComponent(comObj)
	{
		n_assert(m_TerrainComponent);
	}
	//------------------------------------------------------------------------
	void BuildGraphicObjectTraverser::Apply(TerrainNode& node)
	{
		if ( node.GetNodeDrawMode() == eNodeDrawSelf )
		{
			if ( !node.GetRenderObject() )
			{
				m_TerrainComponent->AttachNodeToRender(node);
			}
		}
		else
		{
			// if has renderNode
			if ( node.GetRenderObject() )
			{
				m_TerrainComponent->DeattachNodeFromRender(node);
			}
		}

		Traverse(node);
	}

	//------------------------------------------------------------------------
	RequestBuildNodeAndParentTraverser::RequestBuildNodeAndParentTraverser(const GPtr<Terrain::TerrainDataSource>& terrainDataSource)
		: TerrainNodeTraverser(TRAVERSE_PARENTS)  
	{
		m_TerrainDataSource = terrainDataSource;
		n_assert(m_TerrainDataSource.isvalid());
	}
	//------------------------------------------------------------------------
	void RequestBuildNodeAndParentTraverser::Apply(TerrainNode& node)
	{
		node.SetGeometryError( m_TerrainDataSource->GetGeometryError(node.x, node.y, node.level) );
		bool bHole = m_TerrainDataSource->GetSectorHoleType(node.x, node.y, node.level) == Terrain::eNotHole ? false: true;
		node.SetHole(bHole);
		Math::bbox bb = m_TerrainDataSource->GetSectorWorldBBox(node.x, node.y, node.level);
		node.SetLocalBoundingBox(bb);

		node.RequestBuildPritiveHandle();
		Traverse(node);
	}
}