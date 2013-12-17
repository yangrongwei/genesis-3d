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
#ifndef __intersectutil_H__
#define __intersectutil_H__
#include "apputil/mouserayutil.h"
#include "appframework/actor.h"
#include "resource/meshres.h"
#include "terrainfeature/components/TerrainRenderComponent.h"
#include "vegetationfeature/components/vegetationrendercomponent.h"

namespace AppUtil
{
typedef uint SelectMark;
struct IntersectResult
{
	IntersectResult() :intersectPoint(0.0f) { } 

	IntersectResult( const GPtr<App::Actor> _actor, Math::scalar _f )
		: actor(_actor)
		, intersectPoint(_f)
	{  }

	GPtr<App::Actor> actor;
	Math::scalar intersectPoint;

	inline bool operator < ( const IntersectResult& rhs ) const
	{
		return this->intersectPoint < rhs.intersectPoint;
	}
};
struct IntersectTriangle
{
	IntersectTriangle() :point0(0.0f),point1(0.0f),point2(0.0f){}

	IntersectTriangle(Math::float3& p1,Math::float3& p2,Math::float3& p3)
	{
		point0 = p1;
		point1 = p2;
		point2 = p3;
	}
	Math::float3 point0;
	Math::float3 point1;
	Math::float3 point2;
};
typedef Util::Array<IntersectResult> IntersectResultList;

class IntersectUtil
{
public:

	/// compute world-space ray from mouse position use main camera in game world. (mouse screen position is expected in the range 0..1)
	static bool ComputeDefaultWorldMouseRay( const App::Actor* cameraActor, const Math::float2& mouseScreenPos , Math::Ray& rayout );
	//  compute world-space line from mouse position use main camera in game world. (mouse screen position is expected in the range 0..1)
	static bool ComputeDefaultWorldMouseLine(const Math::float2& mouseScreenPos , Math::line& lineout, float length);
	/**
	* IntersectWorld   use ray to intersect world. 
	* @param: const Math::Ray & worldRay    ray in world space
	* @param: SelectMark selectMask			only (the actor's layerID & selectMask) != 0 , the actor will be intersecting. use 0xFFFFFFFF for all Layer
	* @param: bool onlyUseBBox              if true, we only intersect actor's boundingbox; if false, we will use exact intersect(eg. triangle intersect), slow!!!!
	* @param: IntersectResultList & result  return the actors and nearest intersect points in worldRay. this list not sort, you can manu sort use IntersectResultList::sort
	* @param: Math::scalar fTolerance       tolerance, default is N_TINY
	* @return: bool                         return true, if has some actor intersected.  
	* @see: 
	* @remark:  
	*/
	static bool IntersectWorld( const Math::Ray& worldRay, 
							SelectMark selectMask, 
							bool onlyUseBBox, 
							IntersectResultList& result , 
							Math::scalar fTolerance = N_TINY,
							IntersectTriangle *triAngle = NULL);

	/**
	* IntersectActor  use ray to intersect actor
	* @param: const Math::Ray & worldRay    ray in world space
	* @param: const GPtr<App::Actor>& actor	the actor will intersect with worldRay
	* @param: SelectMark selectMask			only (the actor's layerID & selectMask) != 0 , the actor will be intersecting. use 0xFFFFFFFF for all Layer
	* @param: bool onlyUseBBox              if true, we only intersect actor's boundingbox; if false, we will use exact intersect(eg. triangle intersect), slow!!!!
	* @param: Math::scalar & fout           if intersected, is the nearest in worldRay
	* @param: Math::scalar fTolerance       tolerance, default is N_TINY
	* @return: bool                         return true, if has the actor intersected with worldRay.  
	* @see: 
	* @remark:  
	*/
	static bool IntersectActor( const Math::Ray& worldRay,  const GPtr<App::Actor>& actor,
						SelectMark selectMask,
						bool onlyUseBBox, 
						Math::scalar& fout, 
						Math::scalar fTolerance = N_TINY,
						IntersectTriangle* triAngle = NULL);


	/**
	* IntersectMesh   use ray to intersect actor
	* @param: const Math::Ray & localRay             ray is mesh's space
	* @param: const GPtr<Resources::MeshRes> & mesh   the mesh will intersect with localRay 
	* @param: Math::scalar & fout                    if intersected, is the nearest in localRay    
	* @param: Math::scalar fTolerance                tolerance, default is N_TINY
	* @return: bool     return true, if has the MeshRes intersected with localRay.                              
	* @see: 
	* @remark:  
	*/
	static bool IntersectMesh(const Math::Ray& localRay, const GPtr<Resources::MeshRes>& mesh,Math::scalar& fout, Math::scalar fTolerance = N_TINY, IntersectTriangle*triAngle = NULL);
	
	static bool IntersectTerrainNode(const Math::Ray& localRay, RenderBase::PrimitiveTopology::Code type, App::TerrainNode* node, Math::scalar& fout, Math::scalar fTolerance, IntersectTriangle*triAngle = NULL );
	static bool IntersectTerrainNode_Visbile(const Math::Ray& localRay, RenderBase::PrimitiveTopology::Code type, App::TerrainNode* node, Math::scalar& fout, Math::scalar fTolerance, IntersectTriangle*triAngle = NULL );
	static bool IntersectTerrain(const Math::Ray& localRay, const GPtr<App::TerrainRenderComponent>& TRComponent,Math::scalar& fout, Math::scalar fTolerance, IntersectTriangle*triAngle = NULL );
	static bool IntersectTerrainPos(const Math::Ray& worldRay,  const GPtr<App::Actor>& actor, App::LayerID selectLayers, App::TagID selectTags , 
		bool onlyUseBBox, Math::scalar& fout, Math::float3& pos, Math::scalar fTolerance = N_TINY, IntersectTriangle*triAngle = NULL );


	// intersect primitive
	static bool IntersectPrimitive(const Math::Ray& localRay, 
							RenderBase::PrimitiveTopology::Code type, 
							const Resources::PositionData::value_type* verticies,
							SizeT numVertex,
							Math::scalar& fout, 
							Math::scalar fTolerance = N_TINY,
							IntersectTriangle* triAngle = NULL);

	// intersect primitive index by 16 bit
	static bool IntersectPrimitive(const Math::Ray& localRay,  
						RenderBase::PrimitiveTopology::Code type,
						const Resources::PositionData::value_type* verticies,
						const Resources::Index16Container::value_type* indicies,
						SizeT indexCount, 
						Math::scalar& fout, 
						Math::scalar fTolerance = N_TINY,
						IntersectTriangle* triAngle = NULL);

	// intersect primitive index by 32 bit 
	static bool IntersectPrimitive(const Math::Ray& localRay,  
						RenderBase::PrimitiveTopology::Code type,
						const Resources::PositionData::value_type* verticies,
						const Resources::Index32Container::value_type* indicies,
						SizeT indexCount, 
						Math::scalar& fout, 
						Math::scalar fTolerance = N_TINY,
						IntersectTriangle* triAngle = NULL);
};


}








#endif // __intersectutil_H__
