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

#ifndef __TerrainNodeFrameTraverser_H__
#define __TerrainNodeFrameTraverser_H__
#include "terrainfeature/components/TerrainNodeTraverser.h"
#include "graphicsystem/Camera/Camera.h"


namespace App
{
	class TerrainRenderComponent;

	/// Set Node's draw mode
	class MarkNodeDrawModeTraverser: public TerrainNodeTraverser
	{
	public:
		MarkNodeDrawModeTraverser(NodeDrawMode vis, TerrainNodeTraverser::TraversalMode m = TerrainNodeTraverser::TRAVERSE_CHILDREN );

		virtual ~MarkNodeDrawModeTraverser(){

		}

		virtual void Apply(TerrainNode& node);
	protected:
		NodeDrawMode m_drawMode;
	};

	/// according camera position, calculate terrain nodes LOD status(DrawMode)
	class UpdateTerrainLodLevelTraverser: public TerrainNodeTraverser
	{
	public:
		UpdateTerrainLodLevelTraverser(float cameraFactor,	//	camera
			const Math::vector& cameraLocalPos,	//	camera position in terrain coordinate
			float SquareNodeDistance);	//	distance of use or not use baseMap

		virtual ~UpdateTerrainLodLevelTraverser(){

		}

		virtual void Apply(TerrainNode& node);
	protected:
		float				m_CameraFactor;
		Math::vector		m_CameraLocalPos;
		float				m_SquareNodeDistance;
		int					m_LodMaxLevel;

		MarkNodeDrawModeTraverser m_MarkLodParentDrawedTraverser;
	};

	//ergodic tree, make sure every adjoining node's level difference not bigger than 1. for convenience suture edge
	class LevelupNeighborLODTraverser: public TerrainNodeTraverser
	{
	public:
		LevelupNeighborLODTraverser(	const Math::vector& cameraLocalPos,	//	camera position in terrain coordinate
										float squareNodeDistance);			//	distance of use or not use baseMap
		virtual ~LevelupNeighborLODTraverser(){

		}

		virtual void		Apply(TerrainNode& node);
		void				LevelUpNode(TerrainNode& node);

	protected:
		Math::vector		m_CameraLocalPos;
		float				m_SquareNodeDistance;
		MarkNodeDrawModeTraverser m_MarkLodParentDrawedTraverser;
	};

	//ergodic every visible LOD node, if edge changed, rebuild PrimitiveHandle
	class BuildEdgeMaskTraverser: public TerrainNodeTraverser
	{
	public:
		BuildEdgeMaskTraverser();
		virtual ~BuildEdgeMaskTraverser(){

		}
		virtual void Apply(TerrainNode& node);
	};

	//ergodic every visible LOD node, rebuild PrimitiveHandle
	class BuildPrimitiveTraverser: public TerrainNodeTraverser
	{
	public:
		BuildPrimitiveTraverser(const GPtr<Terrain::TerrainDataSource>& terrainDataSource);
		virtual ~BuildPrimitiveTraverser(){

		}

		virtual void Apply(TerrainNode& node);

	protected:
		GPtr<Terrain::TerrainDataSource> m_TerrainDataSource;
	};

	/** ergodic every, remove unused GraphicOject, add useful GraphicObject
	*                                                                     
	*/
	class BuildGraphicObjectTraverser: public TerrainNodeTraverser
	{
	public:
		BuildGraphicObjectTraverser(TerrainRenderComponent* comObj);
		virtual ~BuildGraphicObjectTraverser(){

		}
		virtual void Apply(TerrainNode& node);
	protected:
		TerrainRenderComponent* m_TerrainComponent;
	};

	/// set node and child node need rebuild PrimitiveHandle
	class RequestBuildNodeAndParentTraverser: public TerrainNodeTraverser
	{
	public:
		RequestBuildNodeAndParentTraverser(const GPtr<Terrain::TerrainDataSource>& terrainDataSource);
		virtual ~RequestBuildNodeAndParentTraverser(){

		}
		virtual void Apply(TerrainNode& node); 
	protected:
		GPtr<Terrain::TerrainDataSource> m_TerrainDataSource;
	};
}

#endif // __TerrainNodeFrameTraverser_H__
