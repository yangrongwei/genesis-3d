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
#include "math/intersection.h"
#include "apputil/intersectutil.h"
#include "graphicfeature/components/cameracomponent.h"
#include "graphicfeature/graphicsfeature.h"
#include "graphicfeature/components/meshrendercomponent.h"
#include "appframework/actormanager.h"
#include "vegetation/VegetationObejct.h"
#include "vegetation/InstanceMap.h"
#include "graphicfeature/components/lightcomponent.h"
namespace AppUtil
{
	using namespace App;
	using namespace Math;
	using namespace Resources;
	using namespace RenderBase;

	//------------------------------------------------------------------------
	bool 
	IntersectUtil::ComputeDefaultWorldMouseRay( const App::Actor* cameraActor, const Math::float2& mouseScreenPos , Math::Ray& rayout )
	{
		if ( !GraphicsFeature::HasInstance() )
		{
			return false;
		}
		if (NULL == cameraActor)
		{
			if ( GraphicsFeature::HasInstance() )
			{
				cameraActor = GraphicsFeature::Instance()->GetDefaultCameraActor().get_unsafe();
			}
			else
			{
				return false;
			}

		}
		// get the attribute of camera
		if ( !cameraActor)
		{
			return false;
		}

		GPtr<CameraComponent> pCamera = cameraActor->FindComponent<CameraComponent>();
		n_assert(pCamera.isvalid());

		Math::matrix44 invViewM = pCamera->GetActorTransform();

		float nearWidth, nearHeight, nearPlaneDis, farPlaneDis;
		pCamera->GetProjParam( &nearWidth , &nearHeight , &nearPlaneDis , &farPlaneDis );

		rayout = AppUtil::MouseRayUtil::ComputeWorldMouseRay(mouseScreenPos, invViewM, nearWidth, nearHeight, nearPlaneDis, pCamera->GetViewType());
		return true;
	}
	//------------------------------------------------------------------------
	bool 
	IntersectUtil::ComputeDefaultWorldMouseLine(const Math::float2& mouseScreenPos , Math::line& lineout, float length)
	{
		if ( !GraphicsFeature::HasInstance() )
		{
			return false;
		}

		// get the attribute of camera
		const GPtr<Actor>& pActor = GraphicsFeature::Instance()->GetDefaultCameraActor();
		if ( !pActor.isvalid() )
		{
			return false;
		}

		const GPtr<Component> obj = pActor->FindComponent( CameraComponent::RTTI );
		if( !obj.isvalid() )
			return false;
		GPtr<CameraComponent> pCamera = obj.downcast<CameraComponent>();

		const Math::matrix44& viewM = pCamera->GetViewMat();
		Math::matrix44 invViewM = Math::matrix44::inverse(viewM);

		const Math::matrix44& projM = pCamera->GetProjMat();
		Math::matrix44 invProjM = Math::matrix44::inverse(projM);

		float nearWidth, nearHeight, nearPlaneDis, farPlaneDis;
		pCamera->GetProjParam( &nearWidth , &nearHeight , &nearPlaneDis , &farPlaneDis );
		lineout = AppUtil::MouseRayUtil::ComputeWorldMouseRay(mouseScreenPos, length, invViewM, invProjM, nearPlaneDis);
		return true;
	}
	//------------------------------------------------------------------------
	// @Todo: use spatial tree to manage actor 
	bool 
	IntersectUtil::IntersectWorld( const Math::Ray& worldRay, SelectMark selectMask, bool onlyUseBBox, IntersectResultList& result , Math::scalar fTolerance /* = N_TINY */,IntersectTriangle *triAngle /* = NULL */)
	{
		if ( !ActorManager::HasInstance() )
		{
			return false;
		}

		ActorManager* pActorMgr = ActorManager::Instance();
		
		IndexT intersectCount = 0;

		SizeT actorSize = pActorMgr->GetActiveActorCount();
		for ( IndexT i = 0; i < actorSize; ++i )
		{
			const GPtr<Actor>& pActor = pActorMgr->GetActiveActor(i);
			n_assert( pActor.isvalid() );
			scalar fout;

			if( IntersectActor(worldRay,  pActor, selectMask, onlyUseBBox, fout, fTolerance, triAngle ) )
			{
				++intersectCount;
				result.Append( IntersectResult(pActor, fout ) );
			}
		}

		return intersectCount != 0 ;
	}

	//------------------------------------------------------------------------
	bool 
	IntersectUtil::IntersectActor(const Math::Ray& worldRay, const GPtr<App::Actor>& actor, SelectMark selectMask, bool onlyUseBBox, Math::scalar& fout, Math::scalar fTolerance /* = N_TINY */,IntersectTriangle *triAngle /* = NULL */)
	{
		if ( !actor.isvalid() )
		{
			return false;
		}
		else if (0 == (actor->GetCullMark() & selectMask))
		{
			return false;
		}

		const Math::bbox& worldBB = actor->GetWorldBoundingBox();

		scalar fOut1, fOut2;
		if ( Math::Intersection::Intersect(worldRay, worldBB, fOut1, fOut2 ) )
		{
			if ( fOut1 < 0.0f && fOut2 < 0.0f )
			{
				return false;	//	all behind the ray
			}

			fout = N_INFINITY;
			if ( fOut1 >= 0.0f )
			{
				fout = n_min( fOut1, fout );
			}
			if ( fOut2 >= 0.0f )
			{
				fout = n_min( fOut2, fout );
			}

			if ( onlyUseBBox )
			{
				return true;
			}
			else
			{
				const GPtr<Component> obj = actor->FindComponent( MeshRenderComponent::RTTI );
				const GPtr<Component> terrainObj = actor->FindComponent( TerrainRenderComponent::RTTI );
				const GPtr<Component> lightObj = actor->FindComponent( LightComponent::RTTI );
				const GPtr<Component> cameraObj = actor->FindComponent( CameraComponent::RTTI );

				// some code add meshrendercomponent to terrain. Ignore this , only picked it up by terrain
				if ( obj.isvalid() && !terrainObj )
				{
					GPtr<MeshRenderComponent> pMeshComponent = obj.downcast<MeshRenderComponent>();
					const GPtr<PrimitiveResInfo>& pri = pMeshComponent->GetPrimtiveResInfo();
					if (!pri||!pri->GetRes())
					{
						return false;
					}
					const GPtr<Resources::MeshRes>& mesh = pri->GetRes().downcast<Resources::MeshRes>();
						

					const matrix44& worldM = actor->GetWorldTransform();
					matrix44 invWorldM = Math::matrix44::inverse( worldM );

					Ray localRay = worldRay.Tramsform( invWorldM );
					
					scalar meshOut = 0;
					if ( IntersectMesh(localRay, mesh, meshOut, fTolerance, triAngle ) )
					{
						// transform meshOut to world space
						if ( n_fequal(meshOut, 0.0, N_TINY  ) )
						{
							fout = n_max(meshOut,0.0f);
						}
						else if( meshOut > 0.0f )
						{
							// meshOut
							float3 localInterPoint = localRay.PointAt( meshOut );
							float3 worldInterPoint = localInterPoint.transformPoint( worldM );

							float3 pdiff = worldInterPoint - worldRay.Start();
							scalar l = pdiff.length();
							fout = l ;
						}
						else
						{
							return false;	//	must not be impl
						}

						return true;
					}
					else
					{
						return false;
					}
				}
				//else if		like terrain component
				else if (terrainObj.isvalid())
				{
					GPtr<TerrainRenderComponent> pTRComponent = terrainObj.downcast<TerrainRenderComponent>();
					const matrix44& worldM = actor->GetWorldTransform();
					matrix44 invWorldM = Math::matrix44::inverse( worldM );
					Ray localRay = worldRay.Tramsform( invWorldM );

					scalar meshOut = 0;
					if ( IntersectTerrain(localRay, pTRComponent, meshOut, fTolerance, triAngle ) )
					{
						// transform meshOut to world space
						if ( n_fequal(meshOut, 0.0, N_TINY  ) )
						{
							fout = n_max(meshOut,0.0f);
						}
						else if( meshOut > 0.0f )
						{
							// meshOut
							float3 localInterPoint = localRay.PointAt( meshOut );
							float3 worldInterPoint = localInterPoint.transformPoint( worldM );

							float3 pdiff = worldInterPoint - worldRay.Start();
							scalar l = pdiff.length();
							fout = l ;
						}
						else
						{
							return false;	//	must not be impl
						}

						return true;
					}
					else
					{
						return false;
					}
				}
				// for the actor with indicator(like light and camera), when it don't add rendercomponent, 
				// for the purpose of picking indicator precisely, recalculate the picking bounding box.
				else if( (cameraObj.isvalid()||lightObj.isvalid())  && !obj && !terrainObj )
				{
					Math::bbox worldBB = actor->GetLocalBoundingBox();
					Math::quaternion rotQuat = actor->GetWorldRotation();
					Math::vector vScale(1.f,1.f,1.f);
					Math::vector vPos = actor->GetWorldPosition();

					const Math::matrix44 mat44 = Math::matrix44::transformation(vScale,rotQuat,vPos);
					worldBB.transform(mat44);

					scalar fOut1, fOut2;
					if ( Math::Intersection::Intersect(worldRay, worldBB, fOut1, fOut2 ) )
					{
						if ( fOut1 < 0.0f && fOut2 < 0.0f )
						{
							return false;	//	all behind the ray
						}

						fout = N_INFINITY;
						if ( fOut1 >= 0.0f )
						{
							fout = n_min( fOut1, fout );
						}
						if ( fOut2 >= 0.0f )
						{
							fout = n_min( fOut2, fout );
						}

						return true;
					}else
					{
						return false;
					}
				}
				else
				{
					return true;
				}
			}
		}
		return false;
	}

	//------------------------------------------------------------------------
	// get the point in the world space that ray intersects with terrain.
	bool 
	IntersectUtil::IntersectTerrainPos( const Math::Ray& worldRay,  const GPtr<App::Actor>& actor,
		App::LayerID selectLayers, App::TagID selectTags , bool onlyUseBBox, Math::scalar& fout,
		Math::float3& pos, Math::scalar fTolerance, IntersectTriangle*triAngle /*= NULL*/ )
	{
		if ( !actor.isvalid() )
		{
			return false;
		}

		if (actor->GetLayerID() == 0)
		{
		}
		else
		{
			if ( (actor->GetLayerID() & selectLayers) == 0 )
			{
				return false;
			}
		}
		

		if ( onlyUseBBox )
		{
			return true;
		}
		else
		{
			const GPtr<Component> terrainObj = actor->FindComponent( TerrainRenderComponent::RTTI );
			
			if (terrainObj.isvalid())
			{
				GPtr<TerrainRenderComponent> pTRComponent = terrainObj.downcast<TerrainRenderComponent>();
				const matrix44& worldM = actor->GetWorldTransform();
				matrix44 invWorldM = Math::matrix44::inverse( worldM );
				Ray localRay = worldRay.Tramsform( invWorldM );

				scalar meshOut = 0;
				if ( IntersectTerrain(localRay, pTRComponent, meshOut, fTolerance, triAngle ) )
				{
					if ( n_fequal(meshOut, 0.0, N_TINY  ) )
					{
						fout = n_max(meshOut,0.0f);
					}
					else if( meshOut > 0.0f )
					{
						// meshOut
						float3 localInterPoint = localRay.PointAt( meshOut );
						float3 worldInterPoint = localInterPoint.transformPoint( worldM );
						pos = worldInterPoint;
					}
					else
					{
						return false;	//	must not be impl
					}

					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return true;
			}
			
		}
		
		return false;
	}
	//------------------------------------------------------------------------
	bool IntersectUtil::IntersectTerrainNode_Visbile(const Math::Ray& localRay, RenderBase::PrimitiveTopology::Code type, App::TerrainNode* node, Math::scalar& fout, Math::scalar fTolerance, IntersectTriangle*triAngle /*= NULL*/ )
	{
		if ( !node || node->GetNodeDrawMode() != eNodeDrawSelf ) 
		{
			return  false;
		}

		// pick itself 
		scalar interPoint = N_INFINITY;
		const Resources::PositionData::value_type* verteies = node->GetPositionData();
		const Resources::Index16Container::value_type* indicies16 = node->GetIndexData();
		SizeT indexCount = node->GetIndexDataCount();
		if (verteies && indicies16)
		{
			scalar f = 0.0f;
			if( IntersectPrimitive(localRay, type, verteies, indicies16, indexCount, f,  fTolerance, triAngle ) )
			{
				interPoint = n_min( interPoint, f );
			}
		}

		if ( interPoint != N_INFINITY )
		{
			fout = interPoint;
			return true;
		}
		else
		{
			return false;
		}
	}
	//------------------------------------------------------------------------
	bool IntersectUtil::IntersectTerrainNode(const Math::Ray& localRay, RenderBase::PrimitiveTopology::Code type, App::TerrainNode* node, Math::scalar& fout, Math::scalar fTolerance,IntersectTriangle*triAngle /*= NULL*/ )
	{
		if ( node == NULL )
		{
			return false;
		}

		// pick the bounding box
		const Math::bbox& bb = node->GetLocalBoundingBox();
		Math::scalar fOut1, fOut2;
		if ( !Math::Intersection::Intersect(localRay, bb, fOut1, fOut2 ) )
		{
			return false;
		}

		scalar interPoint = N_INFINITY;

		// recursivly pick the children node, find the nearest point
		for ( IndexT i = eLeftUpChild; i < eChildCount; ++i)
		{
			TerrainNode* child = node->GetChildNode(i);
			if ( !child )
			{		
				continue;					
			}
			scalar f = 0.0f;
			bool bSucc = IntersectTerrainNode(localRay, type, child, f, fTolerance,triAngle);
			if(bSucc)
			{
				interPoint = n_min( interPoint, f );
			}
			
		}

		if ( node->GetNodeDrawMode() == eNodeDrawSelf )
		{
			scalar f = 0.0f;
			bool bSucc = IntersectTerrainNode_Visbile(localRay, type, node, f, fTolerance,triAngle) ;
			if ( bSucc )
			{
				interPoint = n_min( interPoint, f );
			}
		}

		if ( interPoint != N_INFINITY )
		{
			fout = interPoint;
			return true;
		}
		else
		{
			return false;
		}
	
	}
	//------------------------------------------------------------------------------
	bool 
	IntersectUtil::IntersectTerrain(const Math::Ray& localRay, const GPtr<TerrainRenderComponent>& TRComponent,Math::scalar& fout, Math::scalar fTolerance, IntersectTriangle* triAngle /* = NULL*/)
	{
		if (!TRComponent.isvalid())
		{
			return false;
		}

		const PrimitiveTopology::Code type = TRComponent->GetPrimitiveTopology();
		
		TerrainNode* root = TRComponent->GetRootNode();
		if ( !root )
		{
			return false;
		}

		return IntersectTerrainNode(localRay,type,root,fout,fTolerance,triAngle);
	}

	//------------------------------------------------------------------------
	bool 
	IntersectUtil::IntersectMesh(const Math::Ray& localRay, const GPtr<Resources::MeshRes>& mesh,Math::scalar& fout, Math::scalar fTolerance, IntersectTriangle* triAngle )
	{
		if ( !mesh.isvalid() )
		{
			return false;
		}

		PrimitiveTopology::Code type = mesh->GetTopologyType();

		SizeT vertexCount = mesh->GetVertexCount();
		const Resources::PositionData::value_type* verteies = mesh->GetVertexData<Resources::PositionData>(0);

		SizeT subMeshCount = mesh->GetSubMeshCount();

		SizeT indexCount = mesh->GetIndexCount();
		bool useIndex16 = mesh->IsUseIndex16();
		const Resources::Index16Container::value_type* indicies16 = mesh->GetIndex16();
		const Resources::Index32Container::value_type* indicies32 = mesh->GetIndex32();

		if ( vertexCount == 0 )
		{
			return false;
		}

		if ( indicies16 == NULL && indicies32 == NULL )
		{
			return false;
		}


		scalar interPoint = N_INFINITY;
		if ( subMeshCount > 0 )
		{
			for ( IndexT index = 0; index < subMeshCount; ++index )
			{
				const SubMesh* subMesh = mesh->GetSubMesh(index);
				if( !subMesh )
					continue;

				if ( useIndex16 )
				{
					// use 16 bits index
					n_assert( indicies16 );
					scalar f;
					const Index16Container::value_type* beginIndex = indicies16 + subMesh->FirstIndex;
					if ( IntersectPrimitive(localRay, type, verteies, beginIndex, subMesh->numIndex, f,  fTolerance, triAngle))
					{
						interPoint = n_min( interPoint, f );
					}
				}
				else
				{
					// use 32 bits index
					n_assert( indicies32 );
					scalar f;
					const Index32Container::value_type* beginIndex = indicies32 + subMesh->FirstIndex;
					if ( IntersectPrimitive(localRay, type, verteies, beginIndex, subMesh->numIndex, f, fTolerance, triAngle ))
					{
						interPoint = n_min( interPoint, f );
					}
				}
			}

		}
		else
		{
			if ( indexCount > 0 )
			{
				if ( useIndex16 )
				{
					// use 16 bits index
					n_assert( indicies16 );
					scalar f;
					if ( IntersectPrimitive(localRay, type, verteies, indicies16, indexCount, f,  fTolerance, triAngle ))
					{
						interPoint = n_min( interPoint, f );
					}
				}
				else
				{
					// use 32 bits index
					n_assert( indicies32 );
					scalar f;
					if ( IntersectPrimitive(localRay, type, verteies, indicies32, indexCount, f, fTolerance, triAngle ))
					{
						interPoint = n_min( interPoint, f );
					}
				}
			}
			else if( indexCount == 0 ) 
			{
				scalar f;
				if ( IntersectPrimitive( localRay, type,verteies, vertexCount, f, fTolerance, triAngle ))
				{
					interPoint = n_min( interPoint, f );
				}				
			}
		}


		if ( interPoint != N_INFINITY )
		{
			fout = interPoint;
			return true;
		}
		else
		{
			return false;
		}

	}
	//------------------------------------------------------------------------
	bool 
	IntersectUtil::IntersectPrimitive(const Math::Ray& localRay,
		RenderBase::PrimitiveTopology::Code type, 
		const Resources::PositionData::value_type* verticies,
		SizeT numVertex, 
		Math::scalar& fout, 
		Math::scalar fTolerance,
		IntersectTriangle* triAngle /* = NULL */)
	{
		if ( verticies == NULL )
		{
			return false;
		}

		scalar interPoint = N_INFINITY;

		switch (type)
		{
		case PrimitiveTopology::PointList:
			{
				for ( IndexT i = 0; i < numVertex; ++i)
				{
					if ( Intersection::Intersect(localRay, verticies[i], fTolerance )  )
					{
						float3 diff = verticies[i] - localRay.Start();
						if(triAngle != NULL && diff.length() < interPoint)
						{
							triAngle->point0 = verticies[i];
							triAngle->point1 = verticies[i];
							triAngle->point2 = verticies[i];
						}
						interPoint = n_min( interPoint, diff.length() );
					}
				}
			}
			break;
		case PrimitiveTopology::LineList:
			{
				for ( IndexT i = 0; i < numVertex ; )
				{
					scalar f;
					if ( Intersection::Intersect(localRay, verticies[i], verticies[i+1], f, fTolerance ) )
					{
						if(triAngle != NULL && f < interPoint)
						{
							triAngle->point0 = verticies[i];
							triAngle->point1 = verticies[i+1];
							triAngle->point2 = verticies[i];
						}
						interPoint = n_min( interPoint, f );
					}

					i += 2;
				}
			}
			break;
		case PrimitiveTopology::LineStrip:
			{
				SizeT size = numVertex - 1;
				for ( IndexT i = 0; i < size ; ++i)
				{
					scalar f;
					if ( Intersection::Intersect(localRay, verticies[i], verticies[i+1], f, fTolerance ) )
					{
						if(triAngle != NULL && f < interPoint)
						{
							triAngle->point0 = verticies[i];
							triAngle->point1 = verticies[i+1];
							triAngle->point2 = verticies[i];
						}
						interPoint = n_min( interPoint, f );
					}
				}
			}
			break;
		case PrimitiveTopology::TriangleList:
			{
				for ( IndexT i = 0; i < numVertex ; )
				{
					scalar f;
					if ( Intersection::Intersect(localRay, verticies[i], verticies[i+1], verticies[i+2], f, fTolerance ) )
					{
						if(triAngle != NULL && f < interPoint)
						{
							triAngle->point0 = verticies[i];
							triAngle->point1 = verticies[i+1];
							triAngle->point2 = verticies[i+2];
						}
						interPoint = n_min( interPoint, f );
					}

					i += 3;
				}
			}
			break;
		case PrimitiveTopology::TriangleStrip:
			{
				SizeT size = numVertex - 1;
				for ( IndexT i = 0; i < size ; ++i)
				{
					scalar f;
					if ( Intersection::Intersect(localRay, verticies[i], verticies[i+1],verticies[i+2],  f, fTolerance ) )
					{
						if(triAngle != NULL && f < interPoint)
						{
							triAngle->point0 = verticies[i];
							triAngle->point1 = verticies[i+1];
							triAngle->point2 = verticies[i+2];
						}
						interPoint = n_min( interPoint, f );
					}
				}
			}
			break;
		default:
			break;
		}

		if ( interPoint != N_INFINITY )
		{
			fout = interPoint;
			return true;
		}
		else
		{
			return false;
		}
	}
	//------------------------------------------------------------------------
	template<typename Index_type>
	bool 
	IntersectPrimitiveImpl(const Math::Ray& localRay,  
		RenderBase::PrimitiveTopology::Code type,
		const Resources::PositionData::value_type* verticies,
		const Index_type* indicies,
		SizeT indexCount, 
		Math::scalar& fout, 
		Math::scalar fTolerance,
		IntersectTriangle* triAngle = NULL)
	{
		if ( verticies == NULL || indicies == NULL )
		{
			return false;
		}

		scalar interPoint = N_INFINITY;

		// hack : for the point and line, tolerance is bigger. More reasonable algorithm is letting the line
		// and point project on the screen to judge. Because at present only editor's indicators need this, we
		// think that there are a bigger tolerance is going to be
		const Math::scalar ToleranceForLine = Math::scalar(0.01);

		switch (type)
		{
		case PrimitiveTopology::PointList:
			{
				for ( IndexT i = 0; i < indexCount; ++i)
				{
					Index_type index = indicies[i];
					if ( Intersection::Intersect(localRay, verticies[index], ToleranceForLine )  )
					{
						float3 diff = verticies[index] - localRay.Start();
						if(triAngle != NULL && diff.length() < interPoint)
						{
							triAngle->point0 = verticies[index];
							triAngle->point1 = verticies[index];
							triAngle->point2 = verticies[index];
						}
						interPoint = n_min( interPoint, diff.length() );
					}
				}
			}
			break;
		case PrimitiveTopology::LineList:
			{
				for ( IndexT i = 0; i < indexCount ; )
				{
					scalar f;
					Index_type index0 = indicies[i];
					Index_type index1 = indicies[i+1];
					if ( Intersection::Intersect(localRay, verticies[index0], verticies[index1], f, ToleranceForLine ) )
					{
						if(triAngle != NULL && f < interPoint)
						{
							triAngle->point0 = verticies[index0];
							triAngle->point1 = verticies[index1];
							triAngle->point2 = verticies[index0];
						}
						interPoint = n_min( interPoint, f );
					}

					i += 2;
				}
			}
			break;
		case PrimitiveTopology::LineStrip:
			{
				SizeT size = indexCount - 1;
				for ( IndexT i = 0; i < size ; ++i)
				{
					scalar f;
					Index_type index0 = indicies[i];
					Index_type index1 = indicies[i+1];
					if ( Intersection::Intersect(localRay, verticies[index0], verticies[index1], f, ToleranceForLine ) )
					{
						if(triAngle != NULL && f < interPoint)
						{
							triAngle->point0 = verticies[index0];
							triAngle->point1 = verticies[index1];
							triAngle->point2 = verticies[index0];
						}
						interPoint = n_min( interPoint, f );
					}
				}
			}
			break;
		case PrimitiveTopology::TriangleList:
			{
				for ( IndexT i = 0; i < indexCount ; )
				{
					scalar f;
					Index_type index0 = indicies[i];
					Index_type index1 = indicies[i+1];
					Index_type index2 = indicies[i+2];
					if ( Intersection::Intersect(localRay, verticies[index0], verticies[index1], verticies[index2], f, fTolerance ) )
					{
						if(triAngle != NULL && f < interPoint)
						{
							triAngle->point0 = verticies[index0];
							triAngle->point1 = verticies[index1];
							triAngle->point2 = verticies[index2];
						}
						interPoint = n_min( interPoint, f );
					}

					i += 3;
				}
			}
			break;
		case PrimitiveTopology::TriangleStrip:
			{
				SizeT size = indexCount - 1;
				for ( IndexT i = 0; i < size ; ++i)
				{
					scalar f;
					Index_type index0 = indicies[i];
					Index_type index1 = indicies[i+1];
					Index_type index2 = indicies[i+2];

					if ( Intersection::Intersect(localRay, verticies[index0], verticies[index1],verticies[index2],  f, fTolerance ) )
					{
						if(triAngle != NULL && f < interPoint)
						{
							triAngle->point0 = verticies[index0];
							triAngle->point1 = verticies[index1];
							triAngle->point2 = verticies[index2];
						}
						interPoint = n_min( interPoint, f );
					}
				}
			}
			break;
		default:
			break;
		}

		if ( interPoint != N_INFINITY )
		{
			fout = interPoint;
			return true;
		}
		else
		{
			return false;
		}
	}
	//------------------------------------------------------------------------
	// intersect primitive index by 16 bit
	bool 
	IntersectUtil::IntersectPrimitive(const Math::Ray& localRay,  
		RenderBase::PrimitiveTopology::Code type,
		const Resources::PositionData::value_type* verticies,
		const Resources::Index16Container::value_type* indicies,
		SizeT indexCount, 
		Math::scalar& fout, 
		Math::scalar fTolerance,
		IntersectTriangle* triAngle /* = NULL */)
	{
		return IntersectPrimitiveImpl(localRay, type, verticies, indicies, indexCount, fout, fTolerance, triAngle );
	}

	// intersect primitive index by 32 bit 
	bool 
	IntersectUtil::IntersectPrimitive(const Math::Ray& localRay,  
		RenderBase::PrimitiveTopology::Code type,
		const Resources::PositionData::value_type* verticies,
		const Resources::Index32Container::value_type* indicies,
		SizeT indexCount, 
		Math::scalar& fout, 
		Math::scalar fTolerance,
		IntersectTriangle* triAngle /* = NULL */)
	{
		return IntersectPrimitiveImpl(localRay, type, verticies, indicies, indexCount, fout, fTolerance, triAngle );
	}
}
