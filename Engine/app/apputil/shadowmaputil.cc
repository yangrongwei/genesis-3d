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
#include "shadowmaputil.h"
#include "math/frustum.h"
namespace AppUtil
{
	void ShadowMapUtil::CalculateAABBPoints(Math::float4* aabbPoints, const Math::float4& sceneCenter, const Math::float4& sceneExtends)
	{
		//This map enables us to use a for loop and do vector math.
		static const Math::float4 vExtentsMap[8] = 
		{ 
			Math::float4(1.0f, 1.0f, -1.0f, 1.0f), 
			Math::float4(-1.0f, 1.0f, -1.0f, 1.0f), 
			Math::float4(1.0f, -1.0f, -1.0f, 1.0f), 
			Math::float4(-1.0f, -1.0f, -1.0f, 1.0f), 
			Math::float4(1.0f, 1.0f, 1.0f, 1.0f), 
			Math::float4(-1.0f, 1.0f, 1.0f, 1.0f), 
			Math::float4(1.0f, -1.0f, 1.0f, 1.0f), 
			Math::float4(-1.0f, -1.0f, 1.0f, 1.0f) 
		};

		for( IndexT index = 0; index < 8; ++index ) 
		{
			aabbPoints[index] = Math::float4::multiply(vExtentsMap[index], sceneExtends) + sceneCenter; 
		}
	}

	void ShadowMapUtil::CreateFrustumPointsFromCascadeInterval(float fCascadeIntervalBegin, float fCascadeIntervalEnd, const Math::matrix44 &vProjection,Math::float4* pvCornerPointsWorld)
	{
		Math::frustum::ComputeFrustumFromProjection( pvCornerPointsWorld,fCascadeIntervalBegin,fCascadeIntervalEnd, vProjection, 0.0f != vProjection.mx[3][2]);
	}
	// From DX SDK
	void ShadowMapUtil::ComputeNearAndFar( float& fNearPlane, float& fFarPlane, Math::float4 vLightCameraOrthographicMin, Math::float4 vLightCameraOrthographicMax, Math::float4* pvPointsInCameraView )
	{
		//--------------------------------------------------------------------------------------
		// Used to compute an intersection of the orthographic projection and the Scene AABB
		//--------------------------------------------------------------------------------------
		struct Triangle 
		{
			Math::float4 pt[3];
			bool culled;
		};
		// Initialize the near and far planes
		fNearPlane = S_C_FLOAT4MAX.x();
		fFarPlane = -S_C_FLOAT4MAX.x();

		Triangle triangleList[16];
		IndexT iTriangleCnt = 1;

		triangleList[0].pt[0] = pvPointsInCameraView[0];
		triangleList[0].pt[1] = pvPointsInCameraView[1];
		triangleList[0].pt[2] = pvPointsInCameraView[2];
		triangleList[0].culled = false;

		// These are the indices used to tesselate an AABB into a list of triangles.
		static const IndexT iAABBTriIndexes[] = 
		{
			0,1,2,  1,2,3,
			4,5,6,  5,6,7,
			0,2,4,  2,4,6,
			1,3,5,  3,5,7,
			0,1,4,  1,4,5,
			2,3,6,  3,6,7 
		};

		IndexT iPointPassesCollision[3];

		// At a high level: 
		// 1. Iterate over all 12 triangles of the AABB.  
		// 2. Clip the triangles against each plane. Create new triangles as needed.
		// 3. Find the min and max z values as the near and far plane.

		//This is easier because the triangles are in camera spacing making the collisions tests simple comparisions.

		float fLightCameraOrthographicMinX = vLightCameraOrthographicMin.x();
		float fLightCameraOrthographicMaxX = vLightCameraOrthographicMax.x(); 
		float fLightCameraOrthographicMinY = vLightCameraOrthographicMin.x();
		float fLightCameraOrthographicMaxY = vLightCameraOrthographicMax.x();

		for( IndexT AABBTriIter = 0; AABBTriIter < 12; ++AABBTriIter ) 
		{

			triangleList[0].pt[0] = pvPointsInCameraView[ iAABBTriIndexes[ AABBTriIter*3 + 0 ] ];
			triangleList[0].pt[1] = pvPointsInCameraView[ iAABBTriIndexes[ AABBTriIter*3 + 1 ] ];
			triangleList[0].pt[2] = pvPointsInCameraView[ iAABBTriIndexes[ AABBTriIter*3 + 2 ] ];
			iTriangleCnt = 1;
			triangleList[0].culled = false;

			// Clip each invidual triangle against the 4 frustums.  When ever a triangle is clipped into new triangles, 
			//add them to the list.
			for( IndexT frustumPlaneIter = 0; frustumPlaneIter < 4; ++frustumPlaneIter ) 
			{

				Math::scalar fEdge;
				IndexT iComponent;

				if( frustumPlaneIter == 0 ) 
				{
					fEdge = fLightCameraOrthographicMinX; // todo make float temp
					iComponent = 0;
				} 
				else if( frustumPlaneIter == 1 ) 
				{
					fEdge = fLightCameraOrthographicMaxX;
					iComponent = 0;
				} 
				else if( frustumPlaneIter == 2 ) 
				{
					fEdge = fLightCameraOrthographicMinY;
					iComponent = 1;
				} 
				else 
				{
					fEdge = fLightCameraOrthographicMaxY;
					iComponent = 1;
				}

				for( IndexT triIter=0; triIter < iTriangleCnt; ++triIter ) 
				{
					// We don't delete triangles, so we skip those that have been culled.
					if( !triangleList[triIter].culled ) 
					{
						IndexT iInsideVertCount = 0;
						Math::float4 tempOrder;
						// Test against the correct frustum plane.
						// This could be written more compactly, but it would be harder to understand.

						if( frustumPlaneIter == 0 ) 
						{
							for( IndexT triPtIter=0; triPtIter < 3; ++triPtIter ) 
							{
								if( triangleList[triIter].pt[triPtIter].x() >
									vLightCameraOrthographicMin.x() ) 
								{ 
									iPointPassesCollision[triPtIter] = 1;
								}
								else 
								{
									iPointPassesCollision[triPtIter] = 0;
								}
								iInsideVertCount += iPointPassesCollision[triPtIter];
							}
						}
						else if( frustumPlaneIter == 1 ) 
						{
							for( IndexT triPtIter=0; triPtIter < 3; ++triPtIter ) 
							{
								if( triangleList[triIter].pt[triPtIter].x() < 
									vLightCameraOrthographicMax.x() ) 
								{
									iPointPassesCollision[triPtIter] = 1;
								}
								else
								{ 
									iPointPassesCollision[triPtIter] = 0;
								}
								iInsideVertCount += iPointPassesCollision[triPtIter];
							}
						}
						else if( frustumPlaneIter == 2 ) 
						{
							for( IndexT triPtIter=0; triPtIter < 3; ++triPtIter ) 
							{
								if( triangleList[triIter].pt[triPtIter].y() > 
									vLightCameraOrthographicMin.y() ) 
								{
									iPointPassesCollision[triPtIter] = 1;
								}
								else 
								{
									iPointPassesCollision[triPtIter] = 0;
								}
								iInsideVertCount += iPointPassesCollision[triPtIter];
							}
						}
						else 
						{
							for( IndexT triPtIter=0; triPtIter < 3; ++triPtIter ) 
							{
								if( triangleList[triIter].pt[triPtIter].y() < 
									vLightCameraOrthographicMax.y() ) 
								{
									iPointPassesCollision[triPtIter] = 1;
								}
								else 
								{
									iPointPassesCollision[triPtIter] = 0;
								}
								iInsideVertCount += iPointPassesCollision[triPtIter];
							}
						}

						// Move the points that pass the frustum test to the begining of the array.
						if( iPointPassesCollision[1] && !iPointPassesCollision[0] ) 
						{
							tempOrder =  triangleList[triIter].pt[0];   
							triangleList[triIter].pt[0] = triangleList[triIter].pt[1];
							triangleList[triIter].pt[1] = tempOrder;
							iPointPassesCollision[0] = 1;            
							iPointPassesCollision[1] = 0;            
						}
						if( iPointPassesCollision[2] && !iPointPassesCollision[1] ) 
						{
							tempOrder =  triangleList[triIter].pt[1];   
							triangleList[triIter].pt[1] = triangleList[triIter].pt[2];
							triangleList[triIter].pt[2] = tempOrder;
							iPointPassesCollision[1] = 1;            
							iPointPassesCollision[2] = 0;                        
						}
						if( iPointPassesCollision[1] && !iPointPassesCollision[0] ) 
						{
							tempOrder =  triangleList[triIter].pt[0];   
							triangleList[triIter].pt[0] = triangleList[triIter].pt[1];
							triangleList[triIter].pt[1] = tempOrder;
							iPointPassesCollision[0] = 1;            
							iPointPassesCollision[1] = 0;            
						}

						if( iInsideVertCount == 0 ) 
						{ // All points failed. We're done,  
							triangleList[triIter].culled = true;
						}
						else if( iInsideVertCount == 1 ) 
						{// One point passed. Clip the triangle against the Frustum plane
							triangleList[triIter].culled = false;

							// 
							Math::float4 vVert0ToVert1 = triangleList[triIter].pt[1] - triangleList[triIter].pt[0];
							Math::float4 vVert0ToVert2 = triangleList[triIter].pt[2] - triangleList[triIter].pt[0];

							// Find the collision ratio.
							Math::scalar fHitPointTimeRatio = fEdge -  triangleList[triIter].pt[0][iComponent] ;
							// Calculate the distance along the vector as ratio of the hit ratio to the component.
							Math::scalar fDistanceAlongVector01 = fHitPointTimeRatio /  vVert0ToVert1[iComponent];
							Math::scalar fDistanceAlongVector02 = fHitPointTimeRatio / vVert0ToVert2[iComponent];
							// Add the point plus a percentage of the vector.
							vVert0ToVert1 *= fDistanceAlongVector01;
							vVert0ToVert1 += triangleList[triIter].pt[0];
							vVert0ToVert2 *= fDistanceAlongVector02;
							vVert0ToVert2 += triangleList[triIter].pt[0];

							triangleList[triIter].pt[1] = vVert0ToVert2;
							triangleList[triIter].pt[2] = vVert0ToVert1;

						}
						else if( iInsideVertCount == 2 ) 
						{ // 2 in  // tesselate into 2 triangles


							// Copy the triangle\(if it exists) after the current triangle out of
							// the way so we can override it with the new triangle we're inserting.
							triangleList[iTriangleCnt] = triangleList[triIter+1];

							triangleList[triIter].culled = false;
							triangleList[triIter+1].culled = false;

							// Get the vector from the outside point into the 2 inside points.
							Math::float4 vVert2ToVert0 = triangleList[triIter].pt[0] - triangleList[triIter].pt[2];
							Math::float4 vVert2ToVert1 = triangleList[triIter].pt[1] - triangleList[triIter].pt[2];

							// Get the hit point ratio.
							Math::scalar fHitPointTime_2_0 =  fEdge - triangleList[triIter].pt[2][iComponent];
							Math::scalar fDistanceAlongVector_2_0 = fHitPointTime_2_0 / vVert2ToVert0[iComponent];
							// Calcaulte the new vert by adding the percentage of the vector plus point 2.
							vVert2ToVert0 *= fDistanceAlongVector_2_0;
							vVert2ToVert0 += triangleList[triIter].pt[2];

							// Add a new triangle.
							triangleList[triIter+1].pt[0] = triangleList[triIter].pt[0];
							triangleList[triIter+1].pt[1] = triangleList[triIter].pt[1];
							triangleList[triIter+1].pt[2] = vVert2ToVert0;

							//Get the hit point ratio.
							Math::scalar fHitPointTime_2_1 =  fEdge - triangleList[triIter].pt[2][iComponent];
							Math::scalar fDistanceAlongVector_2_1 = fHitPointTime_2_1 / vVert2ToVert1[iComponent];
							vVert2ToVert1 *= fDistanceAlongVector_2_1;
							vVert2ToVert1 += triangleList[triIter].pt[2];
							triangleList[triIter].pt[0] = triangleList[triIter+1].pt[1];
							triangleList[triIter].pt[1] = triangleList[triIter+1].pt[2];
							triangleList[triIter].pt[2] = vVert2ToVert1;
							// Cncrement triangle count and skip the triangle we just inserted.
							++iTriangleCnt;
							++triIter;


						}
						else 
						{ // all in
							triangleList[triIter].culled = false;

						}
					}// end if !culled loop            
				}
			}
			for( IndexT index=0; index < iTriangleCnt; ++index ) 
			{
				if( !triangleList[index].culled ) 
				{
					// Set the near and far plan and the min and max z values respectivly.
					for( int vertind = 0; vertind < 3; ++ vertind ) 
					{
						float fTriangleCoordZ = triangleList[index].pt[vertind].z();
						if( fNearPlane > fTriangleCoordZ ) 
						{
							fNearPlane = fTriangleCoordZ;
						}
						if( fFarPlane  <fTriangleCoordZ ) 
						{
							fFarPlane = fTriangleCoordZ;
						}
					}
				}
			}
		}    

	}

	void ShadowMapUtil::CalculateCloseSphereFromFrustum(const Math::float4 points[8], Math::float4& outCenter, float& outRadius)
	{
		Math::float4 halfFarLongVec  = (points[0] - points[3]) * 0.5f;
		Math::float4 halfNearLongVec = (points[4] - points[7]) * 0.5f;
		float  squareFarRadius  = Math::float4::dot3(halfFarLongVec, halfFarLongVec);
		float  squareNearRadius = Math::float4::dot3(halfNearLongVec, halfNearLongVec);
		float  subZ = Math::n_abs( points[0].z() - points[4].z() );
		float  offsetZNear = 0.5f * ((squareFarRadius - squareNearRadius) / subZ + subZ);
		float  squareOffsetZNear = offsetZNear * offsetZNear;
		outCenter = Math::float4(0.0f, 0.0f, points[4].z() - offsetZNear, 1.0f);
		outRadius = Math::n_sqrt( squareOffsetZNear + squareNearRadius ) + 0.001f;
	}
}

