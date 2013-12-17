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

	//------------------------------------------------------------------------
	TerrainNode::TerrainNode()
	{
		Reset();
	}
	//------------------------------------------------------------------------
	TerrainNode::~TerrainNode()
	{
		Reset();
	}
	//------------------------------------------------------------------------
	void TerrainNode::Reset()
	{
		m_RenderEnable = true;
		m_EdgeMask = -1; 
		m_GeometryError = 0; 
		m_bHaveHole = false;
		m_DrawMode = eNodeDrawParent; 
		m_UseBaseMap = false;

		m_Parent = NULL;
		for ( int i = eLeftNeighbor; i< eNeighborCount; ++i)
		{
			m_Neighbors[i] = NULL;
		}

		for ( int i = eLeftUpChild; i < eChildCount; ++i)
		{
			m_Childs[i] = NULL;
		}

		m_PositionData.Clear();
		m_IndexData.Clear();

		if ( m_PrimitiveHandle )
		{
			Graphic::GraphicSystem::Instance()->RemovePrimitive(m_PrimitiveHandle);
			m_PrimitiveHandle  = RenderBase::PrimitiveHandle();
		}
		m_NeedBuildHandle = true;
	}
	//------------------------------------------------------------------------
	void TerrainNode::ChangeRenderScene(Graphic::RenderScene* rnsc)
	{
		if (m_RenderObject && m_RenderObject->Attached())
		{
			m_RenderObject->Attach(rnsc);
		}

		for ( int i = eLeftUpChild; i < eChildCount; ++i)
		{
			if( m_Childs[i] )
			{
				m_Childs[i]->ChangeRenderScene(rnsc);
			}
		}
	}
	//------------------------------------------------------------------------
	void TerrainNode::Accept(TerrainNodeTraverser& nt)
	{
		nt.Apply(*this);
	}
	//------------------------------------------------------------------------
	void TerrainNode::TraverseParent(TerrainNodeTraverser& nt)
	{
		if ( m_Parent )
		{
			m_Parent->Accept(nt);
		}

	}
	//------------------------------------------------------------------------
	void TerrainNode::TraverseChilds(TerrainNodeTraverser& nt)
	{
		for ( int i = eLeftUpChild; i < eChildCount; ++i)
		{
			if( m_Childs[i] )
			{
				m_Childs[i]->Accept(nt);
			}
		}
	}
	//------------------------------------------------------------------------
	void TerrainNode::TraverseNeighbor(TerrainNodeTraverser& nt)
	{
		for ( int i = eLeftNeighbor; i< eNeighborCount; ++i)
		{
			if ( m_Neighbors[i] )
			{
				m_Neighbors[i]->Accept(nt);
			}
		}
	}
	//------------------------------------------------------------------------
	void TerrainNode::SetLocalBoundingBox(const Math::bbox& bb)
	{
		///avoid frequently change
		if ( bb != m_LocalBoundingBox )
		{
			m_LocalBoundingBox = bb;
			if ( m_RenderObject )
			{
				m_RenderObject->SetBoundingBox(m_LocalBoundingBox);
			}
		}
	}
	//------------------------------------------------------------------------
	void TerrainNode::BuildPrimitiveHandleIfNeed(const GPtr<Terrain::TerrainDataSource>& terrainDataSource)
	{
		if ( !m_NeedBuildHandle )
		{
			return;
		}

		ForceBuildPrimitiveHandle(terrainDataSource);
	}

	//------------------------------------------------------------------------
	void TerrainNode::ForceBuildPrimitiveHandle(const GPtr<Terrain::TerrainDataSource>& terrainDataSource)
	{
		n_assert(terrainDataSource.isvalid());
		_BuildPrimitiveHandle_Reqular(terrainDataSource);

		// Update RenderObject's bounding box
		m_LocalBoundingBox = terrainDataSource->GetSectorLocalBBox(this->x, this->y, this->level);

		m_NeedBuildHandle = false;
	}

	//------------------------------------------------------------------------
	int TerrainNode::ComputeNodeEdgeMask()
	{
		TerrainNode* parentNode = GetParentNode();
		if ( parentNode )
		{
			return _ComputeNeedSutureEdgeMask(*parentNode,*this);
		}
		else
		{
			return 0;
		}
	}
	//------------------------------------------------------------------------
	int TerrainNode::_ComputeNeedSutureEdgeMask(const TerrainNode &node, TerrainNode &nodeAnalysis)
	{
		int mask = 0;
		bool needRebuild = false;
		TerrainNode* pNeighbor(NULL);
		for(int i = eLeftNeighbor; i <= eDownNeighbor; i++)
		{
			TerrainNode* pNeighbor(NULL);
			pNeighbor = nodeAnalysis.GetNeighborNode(i);
			if(pNeighbor == NULL)
				continue;

			while(pNeighbor->GetNodeDrawMode() != eNodeDrawSelf)
			{
				pNeighbor = pNeighbor->GetParentNode();
				if(pNeighbor == NULL)
					break;
			}

			if(pNeighbor == NULL)
				continue;


			int diffLevel = pNeighbor->level - nodeAnalysis.level;
			needRebuild |= (nodeAnalysis.m_levelDif[i] != diffLevel);

			nodeAnalysis.m_levelDif[i] = diffLevel;

			if(diffLevel >= 1)
				mask |= 1 << i;
		}	
		nodeAnalysis.m_NeedRebuild = needRebuild;

		return mask;
	}

}