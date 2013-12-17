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

#ifndef __TerrainNode_H__
#define __TerrainNode_H__ 

#include "core/refcounted.h"
#include "math/bbox.h"
#include "resource/meshres.h"
#include "terrainsystem/TerrainDataSource.h"
#include "terrainfeature/components/TerrainRenderObject.h"

namespace Graphic
{
	class RenderScene;
}

namespace App
{
	//base enum and struct=============================================================================
	enum NodeNeighborDir
	{
		eLeftNeighbor	= 0,
		eRightNeighbor	= 1, 
		eUpNeighbor		= 2, 
		eDownNeighbor	= 3, 
		eNeighborCount	= 4,
	};

	enum NodeChildDir
	{
		eLeftUpChild	= 0,
		eRightUpChild	= 1,
		eLeftDownChild	= 2, 
		eRightDownChild = 3,
		eChildCount		= 4,
	};

	enum NodeDrawMode
	{
		eNodeDrawParent	= 0,
		eNodeDrawChild	= 1,
		eNodeDrawSelf	= 2
	};

	// veritce buffer
	struct FVF_TERRAIN
	{
		float x, y, z; //position
		float u, v; //texcoord
		float nx, ny, nz;	//normal
	};

	// a unit grid
	struct SRenderNormal
	{
		int haveTriangleIdx[2];		// one unit grid contains 2 triangle
	};
	typedef SRenderNormal* TSRenderNormal;


	//=============================================================================
	class TerrainNodeTraverser;
	class TerrainRenderObject;
	class TerrainNode
	{
	public:
		TerrainNode();
		~TerrainNode();
		void Reset();

		void ChangeRenderScene(Graphic::RenderScene* rnsc);

		//-------------------For Traverser Pattern-----------------------------------------------------
		/// accept NV's Apply function
		void Accept(TerrainNodeTraverser& nv);

		/** Traverse upwards : calls parents' accept method with NodeTraverser.*/
		void TraverseParent(TerrainNodeTraverser& nv);

		/** Traverse downwards : calls children's accept method with NodeTraverser.*/
		void TraverseChilds(TerrainNodeTraverser& nv);  

		/** Traverse Neighbor : calls Neighbor's accept method with NodeTraverser.*/
		void TraverseNeighbor(TerrainNodeTraverser& nv);

		//----------------------basic property--------------------------------------------------

		const Math::bbox&	GetLocalBoundingBox() const;
		void				SetLocalBoundingBox(const Math::bbox& bb);
		RenderBase::PrimitiveTopology::Code GetPrimitiveTopology(void)const ;
		bool				IsUseBaseMap(void) const ;
		void				SetUseBaseMap(bool b);
		void				SetNodeDrawMode( NodeDrawMode v);
		NodeDrawMode		GetNodeDrawMode(void) const;
		float				GetGeometryError(void) const;
		void				SetGeometryError(float h);
		bool				HaveHole();
		void				SetHole(bool b);

		//------------------neighbor and parent-child relationship------------------------------------------------------
		TerrainNode*		GetParentNode()const  ;
		void				SetParentNode(TerrainNode* p);
		TerrainNode*		GetChildNode(int dir) const;
		void				SetChildNode(TerrainNode* child, int dir);
		TerrainNode*		GetNeighborNode(int dir) const;
		void				SetNeighborNode(TerrainNode* neighbor, int dir);

		//---------------------------Render---------------------------------------------
		/// Set need render
		void				SetRenderEnable(bool b) ;
		bool 				GetRenderEnable(void);
		const GPtr<TerrainRenderObject>& GetRenderObject() const;
		void 				SetRenderObject(const GPtr<TerrainRenderObject>& renderObj);
		void 				SetEdgeMask( int mask );
		int 				GetEdgeMask(void) const;
		int 				ComputeNodeEdgeMask() ;
		const RenderBase::PrimitiveHandle& GetPrimitiveHandle() const ;
		void 				RequestBuildPritiveHandle();
		bool 				IsNeedBulidPritiveHandle() const ;

		/// if need, build PrimitiveHandle
		void 				BuildPrimitiveHandleIfNeed(const GPtr<Terrain::TerrainDataSource>& terrainDataSource);

		/// Force build PrimitiveHandle, slow! use it carefully!
		void 				ForceBuildPrimitiveHandle(const GPtr<Terrain::TerrainDataSource>& terrainDataSource);


		//--------------------------Ray Intersect----------------------------------------------
		const Resources::PositionData::Elem* GetPositionData() const;

		Resources::Index16Container::value_type* GetIndexData() const;

		SizeT 				GetIndexDataCount() const;

		SizeT 				GetPostionDataCount() const;
#ifdef __GENESIS_EDITOR__
		const Resources::TexCoordData::Elem* GetTexCoorData() const;
		const Resources::NormalData::Elem* GetNormalData() const;

#endif

	protected:
		int  _ComputeNeedSutureEdgeMask(const TerrainNode &node, TerrainNode &nodeAnalysis);

		// Use standard grid to build edge
		void 				_BuildPrimitiveHandle_Reqular(const GPtr<Terrain::TerrainDataSource>& terrainDataSource);
		void 				_BuildOneGridIdxData(Util::Array<uint16>& indexData, int xx,int yy);
		void 				_BuildOneGridIdxDataWithHole(Util::Array<uint16>& indexData, int xx,int yy);
		void 				_FixHeightAndNormal(FVF_TERRAIN* heightArray,Resources::PositionData& posData);
#ifdef __GENESIS_EDITOR__
		void 				_SaveUVAndNormal(const FVF_TERRAIN* verticeData);
#endif

	public:
		int			x;
		int			y;
		int			level;
		int         bundleIndex;
		int			m_levelDif[eNeighborCount];
		bool		m_NeedRebuild;

	protected:
		bool				m_RenderEnable;		//	enable render
		NodeDrawMode		m_DrawMode;			//	node's LOD draw mode
		float				m_GeometryError;	//	node's bundle geometry error
		Math::bbox			m_LocalBoundingBox;	//	local Bound
		bool				m_UseBaseMap;		//	whether or not use base map		
		int					m_EdgeMask;			//  show the edge suture status. 0: sutured. 1: need suture.
		bool				m_bHaveHole;

		RenderBase::PrimitiveHandle		m_PrimitiveHandle;	//	render handle
		bool							m_NeedBuildHandle;	//	whether or not need build PrimitiveHandle
		GPtr<TerrainRenderObject>		m_RenderObject;		//	Node's renderObject
		TerrainNode*					m_Neighbors[eNeighborCount];
		TerrainNode*					m_Childs[eChildCount];
		TerrainNode*					m_Parent;

		/// Use for ray intersect
		Resources::PositionData			m_PositionData;
		Resources::Index16Container		m_IndexData;
#ifdef __GENESIS_EDITOR__
		Resources::TexCoordData			m_texUV;	
		Resources::NormalData			m_normalData;
#endif

	};

	//inline method implement=====================================================
	inline const Math::bbox& TerrainNode::GetLocalBoundingBox() const{
		return m_LocalBoundingBox;
	}

	inline RenderBase::PrimitiveTopology::Code TerrainNode::GetPrimitiveTopology(void) const{
		return RenderBase::PrimitiveTopology::TriangleList;
	}

	inline bool TerrainNode::IsUseBaseMap(void) const{
		return m_UseBaseMap;
	}

	inline void TerrainNode::SetUseBaseMap(bool b){
		m_UseBaseMap = b;
	}

	inline void TerrainNode::SetNodeDrawMode( NodeDrawMode v){
		m_DrawMode = v;
	}

	inline NodeDrawMode TerrainNode::GetNodeDrawMode(void) const{
		return m_DrawMode;
	}

	inline float TerrainNode::GetGeometryError(void) const{
		return m_GeometryError;
	}

	inline void TerrainNode::SetGeometryError(float h){
		m_GeometryError = h;
	}

	inline bool	TerrainNode::HaveHole(){
		return m_bHaveHole;
	}
	inline void	TerrainNode::SetHole(bool b){
		m_bHaveHole = b;
	}

	//------------------neighbor and parent-child relationship------------------------------------------------------
	inline TerrainNode* TerrainNode::GetParentNode() const{
		return m_Parent;
	}

	inline void TerrainNode::SetParentNode(TerrainNode* p){
		m_Parent = p;
	}

	inline TerrainNode* TerrainNode::GetChildNode(int dir) const{
		n_assert(dir >=eLeftUpChild && dir < eChildCount);
		return m_Childs[dir];
	}

	inline void TerrainNode::SetChildNode(TerrainNode* child, int dir){
		n_assert(dir >=eLeftUpChild && dir < eChildCount);
		m_Childs[dir] = child;
	}

	inline TerrainNode* TerrainNode::GetNeighborNode(int dir) const{
		n_assert(dir >=eLeftNeighbor && dir < eNeighborCount);
		return m_Neighbors[dir];
	}

	inline void TerrainNode::SetNeighborNode(TerrainNode* neighbor, int dir){
		n_assert(dir >=eLeftNeighbor && dir < eNeighborCount);
		m_Neighbors[dir] = neighbor;
	}

	//---------------------------Render---------------------------------------------
	/// Set need render
	inline void TerrainNode::SetRenderEnable(bool b) {
		m_RenderEnable = b;
	}

	inline bool TerrainNode::GetRenderEnable(void){
		return m_RenderEnable;
	}

	inline const GPtr<TerrainRenderObject>& TerrainNode::GetRenderObject() const{
		return m_RenderObject;
	}

	inline void TerrainNode::SetRenderObject(const GPtr<TerrainRenderObject>& renderObj){
		m_RenderObject = renderObj;
	}

	/// Set edge's suture mask. When suture changed, call RequestBuildPritiveHandle to rebuild
	inline void TerrainNode::SetEdgeMask( int mask ){
		m_EdgeMask = mask;
	}

	inline int TerrainNode::GetEdgeMask(void) const{
		return m_EdgeMask;
	}

	inline const RenderBase::PrimitiveHandle& TerrainNode::GetPrimitiveHandle() const{
		return m_PrimitiveHandle;
	}

	inline void TerrainNode::RequestBuildPritiveHandle(){
		m_NeedBuildHandle = true;
	}

	inline bool TerrainNode::IsNeedBulidPritiveHandle() const {
		return m_NeedBuildHandle;
	}
	inline const Resources::PositionData::Elem* TerrainNode::GetPositionData() const{
		if ( m_PositionData.IsEmpty() )
		{
			return NULL;
		}
		return &m_PositionData[0];
	}

	inline Resources::Index16Container::value_type* TerrainNode::GetIndexData() const{
		if ( m_IndexData.IsEmpty() )
		{
			return NULL;
		}
		return &m_IndexData[0];
	}

	inline SizeT TerrainNode::GetIndexDataCount() const{
		return m_IndexData.Size();
	}

	inline SizeT TerrainNode::GetPostionDataCount() const{
		return m_PositionData.Size();
	}
#ifdef __GENESIS_EDITOR__
	inline const Resources::TexCoordData::Elem* 
		TerrainNode::GetTexCoorData() const{
			if ( m_texUV.IsEmpty() )
			{
				return NULL;
			}
			return &m_texUV[0];
	}

	inline const Resources::NormalData::Elem* 
		TerrainNode::GetNormalData() const{
			if ( m_normalData.IsEmpty() )
			{
				return NULL;
			}
			return &m_normalData[0];
	}

#endif

}

#endif // __TerrainNode_H__
