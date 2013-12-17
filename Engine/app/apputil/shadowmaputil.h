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
#ifndef _H_SHADOWMAPUTIL_
#define _H_SHADOWMAPUTIL_
#include "math/matrix44.h"
//------------------------------------------------------------------------------
namespace AppUtil
{
	static int s_cascadePartitionsZeroToOne[8] = {10, 30, 50, 100, 100, 100, 100, 100};
	static float s_cascadePartitionsFrustum[8] = {100000.f, 100000.f, 100000.f, 100000.f, 100000.f, 100000.f, 100000.f, 100000.f};
	
	static float s_cascadePartitionsZeroToOne_x[5] = { 0.0f, 5.0f/100.0f, 15.0f/100.0f, 60.0f/100.0f, 1.0f };
	static float s_cascadePartitionsFrustum_x[8] = {100000.f, 100000.f, 100000.f, 100000.f, 100000.f, 100000.f, 100000.f, 100000.f};
	
	//TODO:this is only support in 32bit system 
	static const Math::float4 S_C_FLOAT4MAX(3.402823466e+38F, 3.402823466e+38F, 3.402823466e+38F, 3.402823466e+38F);
	static const Math::float4 S_C_FLOAT4MIN(-3.402823466e+38F, -3.402823466e+38F, -3.402823466e+38F, -3.402823466e+38F);
class ShadowMapUtil
{
public:
	/// this function simply converts the center and extents of an AABB into 8 points
    static void CalculateAABBPoints(Math::float4* aabbPoints, const Math::float4& sceneCenter, const Math::float4& sceneExtends);
	
	static void CreateFrustumPointsFromCascadeInterval( float fCascadeIntervalBegin, float fCascadeIntervalEnd, const Math::matrix44 &vProjection,Math::float4* pvCornerPointsWorld);

	// Compute the near and far plane by intersecting an Ortho Projection with the Scenes AABB.
	static void ComputeNearAndFar( float& fNearPlane, float& fFarPlane, Math::float4 vLightCameraOrthographicMin, Math::float4 vLightCameraOrthographicMax, Math::float4* pvPointsInCameraView );
	
	// Compute a sphere from the eight points of frustum
	static void CalculateCloseSphereFromFrustum(const Math::float4 points[8], Math::float4& outCenter, float& outRadius);
};

} // namespace AppUtil
//------------------------------------------------------------------------------
#endif // _H_SHADOWMAPUTIL_