/****************************************************************************
Copyright (c) 2010,RadonLabs GmbH
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
#pragma once
//------------------------------------------------------------------------------
/**
    @class Math::frustum
    
    Defines a clipping frustum made of 6 planes.
*/
#include "math/plane.h"
#include "math/matrix44.h"
#include "math/bbox.h"
#include "math/point.h"
#include "math/clipstatus.h"
#ifdef __OSX__
#include "../rendersystem/config/RenderDeviceConfig.h"
#else
#include "rendersystem/config/RenderDeviceConfig.h"
#endif

//------------------------------------------------------------------------------
namespace Math
{
class frustum
{
public:
    /// plane indices
    enum PlaneIndex
    {
        Near = 0,
        Far,
        Left,
        Right,
        Top,
        Bottom,

        NumPlanes
    };

    /// default constructor
    frustum();
    ///// construct from view and projection matrix
    //frustum(const matrix44& invViewProj);
    ///// setup from view and proj matrix
    //void set(const matrix44& invViewProj);
	/// also view * proj
	void setmatrix(const matrix44& value);

    /// setup from transformed bounding box
    void set(const bbox& box, const matrix44& boxTransform);
    /// test if point is inside frustum
    bool inside(const point& p) const;
    /// get clip bitmask of point (0 if inside, (1<<PlaneIndex) if outside)
    uint clipmask(const point& p) const;
    /// clip line against view frustum
    ClipStatus::Type clip(const line& l, line& clippedLine) const;
    /// get clip status of a local bounding box
    ClipStatus::Type clipstatus(const bbox& box) const;
    /// get clip status of a transformed bounding box
    ClipStatus::Type clipstatus(const bbox& box, const matrix44& boxTransform) const;
    /// convert to any type
    template<typename T> T as() const;


	static void ComputeFrustumFromProjection( float4* pOutFarPoints,float n,float f,const Math::matrix44& pProjection,bool isPersp = true );

    static const int TopLeftFar = 0;
    static const int TopRightFar = 1;
    static const int BottomLeftFar = 2;
    static const int BottomRightFar = 3;
    static const int TopLeftNear = 4;
    static const int TopRightNear = 5;
    static const int BottomLeftNear = 6;
    static const int BottomRightNear = 7;

    plane planes[NumPlanes];    //所有的平面的法线指向视锥体的外边。
};        

//------------------------------------------------------------------------------
/**
*/
inline
frustum::frustum()
{
    // empty
}

////------------------------------------------------------------------------------
///**
//*/
//inline 
//frustum::frustum(const matrix44& invViewProj)
//{
//    this->set(invViewProj);
//}

////------------------------------------------------------------------------------
///**
//    Setup frustum from invViewProj matrix (transform from projection space
//    into world space).
//*/
//inline void
//frustum::set(const matrix44& invViewProj)
//{
//    // frustum corners in projection space
//    point projPoints[8];
//    projPoints[TopLeftFar].set(-1.0f, 1.0f, 1.0f);
//    projPoints[TopRightFar].set(1.0f, 1.0f, 1.0f);
//    projPoints[BottomLeftFar].set(-1.0f, -1.0f, 1.0f);
//    projPoints[BottomRightFar].set(1.0f, -1.0f, 1.0f);
//
//    projPoints[TopLeftNear].set(-1.0f, 1.0f, 0.0f);
//    projPoints[TopRightNear].set(1.0f, 1.0f, 0.0f);
//    projPoints[BottomLeftNear].set(-1.0f, -1.0f, 0.0f);
//    projPoints[BottomRightNear].set(1.0f, -1.0f, 0.0);
//
//    // compute frustum corners in world space
//    point worldPoints[8];
//    IndexT i;
//    for (i = 0; i < 8; i++)
//    {
//		point& p = worldPoints[i];
//        p = matrix44::transform(invViewProj,projPoints[i]);
//        p *= 1.0f / p.w();
//    }
//
//    // setup planes
//    this->planes[Near].setup_from_points(worldPoints[TopRightNear], worldPoints[TopLeftNear], worldPoints[BottomLeftNear]);
//    this->planes[Far].setup_from_points(worldPoints[TopLeftFar], worldPoints[TopRightFar], worldPoints[BottomRightFar]);
//    this->planes[Left].setup_from_points(worldPoints[BottomLeftFar], worldPoints[BottomLeftNear], worldPoints[TopLeftNear]);
//    this->planes[Right].setup_from_points(worldPoints[TopRightFar], worldPoints[TopRightNear], worldPoints[BottomRightNear]);
//    this->planes[Top].setup_from_points(worldPoints[TopLeftNear], worldPoints[TopRightNear], worldPoints[TopRightFar]);
//    this->planes[Bottom].setup_from_points(worldPoints[BottomLeftFar], worldPoints[BottomRightFar], worldPoints[BottomRightNear]);
//}
//------------------------------------------------------------------------------
/**
*/
inline void
frustum::setmatrix(const matrix44& value)
{
	planes[Left].vec.x = -value.mx[3][0] - value.mx[0][0];
	planes[Left].vec.y = -value.mx[3][1] - value.mx[0][1];
	planes[Left].vec.z = -value.mx[3][2] - value.mx[0][2];
	planes[Left].vec.w = -value.mx[3][3] - value.mx[0][3];

	planes[Right].vec.x = - value.mx[3][0] + value.mx[0][0];
	planes[Right].vec.y = - value.mx[3][1] + value.mx[0][1];
	planes[Right].vec.z = - value.mx[3][2] + value.mx[0][2];
	planes[Right].vec.w = - value.mx[3][3] + value.mx[0][3];

	planes[Top].vec.x = - value.mx[3][0] + value.mx[1][0];
	planes[Top].vec.y = - value.mx[3][1] + value.mx[1][1];
	planes[Top].vec.z = - value.mx[3][2] + value.mx[1][2];
	planes[Top].vec.w = - value.mx[3][3] + value.mx[1][3];

	planes[Bottom].vec.x = - value.mx[3][0] - value.mx[1][0];
	planes[Bottom].vec.y = - value.mx[3][1] - value.mx[1][1];
	planes[Bottom].vec.z = - value.mx[3][2] - value.mx[1][2];
	planes[Bottom].vec.w = - value.mx[3][3] - value.mx[1][3];

	planes[Near].vec.x = - value.mx[2][0];
	planes[Near].vec.y = - value.mx[2][1];
	planes[Near].vec.z = - value.mx[2][2];
	planes[Near].vec.w = - value.mx[2][3];

	planes[Far].vec.x = - value.mx[3][0] + value.mx[2][0];
	planes[Far].vec.y = - value.mx[3][1] + value.mx[2][1];
	planes[Far].vec.z = - value.mx[3][2] + value.mx[2][2];
	planes[Far].vec.w = - value.mx[3][3] + value.mx[2][3];

	for (int i = 0; i < 6; i++)
	{
		plane& pl = planes[i];
		float num2 = n_sqrt(pl.vec.x * pl.vec.x + pl.vec.y * pl.vec.y + pl.vec.z * pl.vec.z );//pl.Normal.Length();
		//pl.Normal = (Vector3) (pl.Normal / num2);
		pl.vec.x /= num2;
		pl.vec.y /= num2;
		pl.vec.z /= num2;
		pl.vec.w /= num2;

		//pl.D /= num2;
	}

}

//------------------------------------------------------------------------------
/**
    Setup from a transformed bounding box.
*/
inline void
frustum::set(const bbox& box, const matrix44& boxTransform)
{
    // compute frustum corners in world space
    point localPoint;
    point worldPoints[8];
    IndexT i;
    for (i = 0; i < 8; i++)
    {
        // Top: pmax.y, Bottom: pmin.y, Left: pmin.x, Right: pmax.x, Far: pmax.z, Near: pmin.z
        switch (i)
        {
            // FIXME: replace with permute!
            case TopLeftFar:        localPoint.set(box.pmin.x(), box.pmax.y(), box.pmax.z()); break;
            case TopRightFar:       localPoint.set(box.pmax.x(), box.pmax.y(), box.pmax.z()); break;
            case BottomLeftFar:     localPoint.set(box.pmin.x(), box.pmin.y(), box.pmax.z()); break;
            case BottomRightFar:    localPoint.set(box.pmax.x(), box.pmin.y(), box.pmax.z()); break;
            case TopLeftNear:       localPoint.set(box.pmin.x(), box.pmax.y(), box.pmin.z()); break;
            case TopRightNear:      localPoint.set(box.pmax.x(), box.pmax.y(), box.pmin.z()); break;
            case BottomLeftNear:    localPoint.set(box.pmin.x(), box.pmin.y(), box.pmin.z()); break;
            case BottomRightNear:   localPoint.set(box.pmax.x(), box.pmin.y(), box.pmin.z()); break;
        }
        worldPoints[i] = matrix44::transform(boxTransform,localPoint);
    }

    // setup planes from transformed world space coordinates 
    this->planes[Near].setup_from_points(worldPoints[TopLeftNear], worldPoints[TopRightNear], worldPoints[BottomLeftNear]);
    this->planes[Far].setup_from_points(worldPoints[TopRightFar], worldPoints[TopLeftFar], worldPoints[BottomRightFar]);
    this->planes[Left].setup_from_points(worldPoints[BottomLeftNear], worldPoints[BottomLeftFar], worldPoints[TopLeftNear]);
    this->planes[Right].setup_from_points(worldPoints[BottomRightNear], worldPoints[TopRightNear], worldPoints[TopRightFar]);
    this->planes[Top].setup_from_points(worldPoints[TopRightNear], worldPoints[TopLeftNear], worldPoints[TopRightFar]);
    this->planes[Bottom].setup_from_points(worldPoints[BottomRightFar], worldPoints[BottomLeftFar], worldPoints[BottomRightNear]);
}

//------------------------------------------------------------------------------
/**
    Test if point is inside frustum.
*/
inline bool
frustum::inside(const point& p) const
{
    IndexT i;
    for (i = 0; i < NumPlanes; i++)
    {
        if (this->planes[i].dot(p) > 0.0f)
        {
            return false;
        }
    }
    return true;
}

//------------------------------------------------------------------------------
/**
    Get clipmask of point.
*/
inline uint
frustum::clipmask(const point& p) const
{
    uint clipMask = 0;
    IndexT i;
    for (i = 0; i < NumPlanes; i++)
    {
        if (this->planes[i].dot(p) > 0.0f)
        {
            clipMask |= 1<<i;
        }
    }
    return clipMask;
}

//------------------------------------------------------------------------------
/**
*/
inline ClipStatus::Type
frustum::clip(const line& l, line& clippedLine) const
{
    ClipStatus::Type clipStatus = ClipStatus::Inside;
    line l0(l);
    line l1;
    IndexT i;
    for (i = 0; i < NumPlanes; i++)
    {
        ClipStatus::Type planeClipStatus = this->planes[i].clip(l0, l1);
        if (ClipStatus::Outside == planeClipStatus)
        {
            return ClipStatus::Outside;
        }
        else if (ClipStatus::Clipped == planeClipStatus)
        {
            clipStatus = ClipStatus::Clipped;
        }
        l0 = l1;
    }
    clippedLine = l0;
    return clipStatus;
}

//------------------------------------------------------------------------------
/**
*/
inline ClipStatus::Type
frustum::clipstatus(const bbox& box) const
{
    uint andFlags = 0xffff;
    uint orFlags = 0;
    point p;
    IndexT i;
    for (i = 0; i < 8; i++)
    {
        // get corner point of bounding box
        switch (i)
        {
            // FIXME: REPLACE WITH PERMUTE!
            case 0:     p = box.pmin; break;
            case 1:     p.set(box.pmin.x(), box.pmax.y(), box.pmin.z()); break;
            case 2:     p.set(box.pmax.x(), box.pmax.y(), box.pmin.z()); break;
            case 3:     p.set(box.pmax.x(), box.pmin.y(), box.pmin.z()); break;
            case 4:     p = box.pmax; break;
            case 5:     p.set(box.pmin.x(), box.pmax.y(), box.pmax.z()); break;
            case 6:     p.set(box.pmin.x(), box.pmin.y(), box.pmax.z()); break;
            case 7:     p.set(box.pmax.x(), box.pmin.y(), box.pmax.z()); break;
        }

        // get clip mask of current box corner against frustum
        uint clipMask = this->clipmask(p);
        andFlags &= clipMask;
        orFlags  |= clipMask;
    }
    if (0 == orFlags)       return ClipStatus::Inside;
    else if (0 != andFlags) return ClipStatus::Outside;
    else                    return ClipStatus::Clipped;
}

//------------------------------------------------------------------------------
/**
    Returns the clip status of a transformed bounding box.
*/
inline ClipStatus::Type
frustum::clipstatus(const bbox& box, const matrix44& boxTransform) const
{
    uint andFlags = 0xffff;
    uint orFlags = 0;
    point localPoint, transformedPoint;
    IndexT i;
    for (i = 0; i < 8; i++)
    {
        // get corner point of bounding box
        switch (i)
        {
            // FIXME: REPLACE WITH PERMUTE!
            case 0:     localPoint = box.pmin; break;
            case 1:     localPoint.set(box.pmin.x(), box.pmax.y(), box.pmin.z()); break;
            case 2:     localPoint.set(box.pmax.x(), box.pmax.y(), box.pmin.z()); break;
            case 3:     localPoint.set(box.pmax.x(), box.pmin.y(), box.pmin.z()); break;
            case 4:     localPoint = box.pmax; break;
            case 5:     localPoint.set(box.pmin.x(), box.pmax.y(), box.pmax.z()); break;
            case 6:     localPoint.set(box.pmin.x(), box.pmin.y(), box.pmax.z()); break;
            case 7:     localPoint.set(box.pmax.x(), box.pmin.y(), box.pmax.z()); break;
        }

        // transform bounding box point
        transformedPoint = matrix44::transform(boxTransform,localPoint);

        // get clip mask of current box corner against frustum
        uint clipMask = this->clipmask(transformedPoint);
        andFlags &= clipMask;
        orFlags  |= clipMask;
    }
    if (0 == orFlags)       return ClipStatus::Inside;
    else if (0 != andFlags) return ClipStatus::Outside;
    else                    return ClipStatus::Clipped;
}

//-----------------------------------------------------------------------------
// Build a frustum from a persepective projection matrix.  The matrix may only
// contain a projection; any rotation, translation or scale will cause the
// constructed frustum to be incorrect.
//-----------------------------------------------------------------------------
inline void
frustum::ComputeFrustumFromProjection( float4* pOutFarPoints,float n,float f,const Math::matrix44& pProjection,bool isPersp )
{

	// Corners of the projection frustum in homogenous space.
	static float4 HomogenousPoints[8];
	HomogenousPoints[0].set(1.0f,  0.0f, 1.0f, 1.0f); // right (at far plane)
	HomogenousPoints[1].set(-1.0f,  0.0f, 1.0f, 1.0f);  // left
	HomogenousPoints[2].set(0.0f,  1.0f, 1.0f, 1.0f);// top
	HomogenousPoints[3].set(0.0f, -1.0f, 1.0f, 1.0f); // bottom
#if RENDERDEVICE_D3D9
	HomogenousPoints[4].set(0.0f, 0.0f, 0.0f, 1.0f);   // near
#endif
#if RENDERDEVICE_OPENGL || RENDERDEVICE_OPENGLES
	HomogenousPoints[4].set(0.0f, 0.0f, -1.0f, 1.0f);   // near
#endif
	HomogenousPoints[5].set(0.0f, 0.0f, 1.0f, 1.0f);	  // far

	matrix44 invProj = matrix44::inverse(pProjection);

	float4 frustumPoints[6];
	// Compute the frustum corners to view space.
	for( int i = 0; i < 6; i++ )
	{
		// Transform point.
		frustumPoints[i] = matrix44::transform( invProj,HomogenousPoints[i] );
	}

	if (isPersp)
	{
		// Compute the slopes.
		frustumPoints[0] = frustumPoints[0] * float4::reciprocal( frustumPoints[0] ).z();
		frustumPoints[1] = frustumPoints[1] * float4::reciprocal( frustumPoints[1] ).z();
		frustumPoints[2] = frustumPoints[2] * float4::reciprocal( frustumPoints[2] ).z();
		frustumPoints[3] = frustumPoints[3] * float4::reciprocal( frustumPoints[3] ).z();
	}
	float RightSlope,LeftSlope,TopSlope,BottomSlope,NearZ,FarZ;
	RightSlope = frustumPoints[0].x();
	LeftSlope = frustumPoints[1].x();
	TopSlope = frustumPoints[2].y();
	BottomSlope = frustumPoints[3].y();

	// Compute near and far.
	frustumPoints[4] = frustumPoints[4] * float4::reciprocal( frustumPoints[4] ).w();
	frustumPoints[5] = frustumPoints[5] * float4::reciprocal( frustumPoints[5] ).w();

	NearZ = frustumPoints[4].z();
	FarZ = frustumPoints[5].z();

	NearZ = n < n_abs(NearZ) ? NearZ : -n;
	FarZ = -f;

	if (isPersp)
	{

		float4 vRightTop = float4(RightSlope,TopSlope,1.0f,1.0f);
		float4 vLeftBottom = float4(LeftSlope,BottomSlope,1.0f,1.0f);
		float4 vLeftTop = float4(LeftSlope,TopSlope,1.0f,1.0f);
		float4 vRightBottom = float4(RightSlope,BottomSlope,1.0f,1.0f);
		float4 vNear = float4(NearZ,NearZ,NearZ,1.0f);
		float4 vFar = float4(FarZ,FarZ,FarZ,1.0f);

		float4 vRightTopNear = float4::multiply( vRightTop, vNear );
		float4 vRightTopFar = float4::multiply( vRightTop, vFar );
		float4 vLeftBottomNear = float4::multiply( vLeftBottom, vNear );
		float4 vLeftBottomFar = float4::multiply( vLeftBottom, vFar );

		float4 vLeftTopNear = float4::multiply( vLeftTop, vNear );
		float4 vLeftTopFar = float4::multiply( vLeftTop, vFar );
		float4 vRightBottomNear = float4::multiply( vRightBottom, vNear );
		float4 vRightBottomFar = float4::multiply( vRightBottom, vFar );

		pOutFarPoints[0] = vLeftTopFar; //TopLeftFar
		pOutFarPoints[1] = vRightTopFar;  //TopRightFar
		pOutFarPoints[2] = vLeftBottomFar;//BottomLeftFar
		pOutFarPoints[3] = vRightBottomFar; //BottomRightFar
		pOutFarPoints[4] = vLeftTopNear;   //TopLeftNear
		pOutFarPoints[5] = vRightTopNear;	  //TopRightNear
		pOutFarPoints[6] = vLeftBottomNear;  //BottomLeftNear
		pOutFarPoints[7] = vRightBottomNear;    //BottomRightNear
	}
	else
	{
		pOutFarPoints[0] = float4(LeftSlope,TopSlope,FarZ,1.f); //TopLeftFar
		pOutFarPoints[1] = float4(RightSlope,TopSlope,FarZ,1.f);  //TopRightFar
		pOutFarPoints[2] = float4(LeftSlope,BottomSlope,FarZ,1.f);//BottomLeftFar
		pOutFarPoints[3] = float4(RightSlope,BottomSlope,FarZ,1.f); //BottomRightFar
		pOutFarPoints[4] = float4(LeftSlope,TopSlope,NearZ,1.f);   //TopLeftNear
		pOutFarPoints[5] = float4(RightSlope,TopSlope,NearZ,1.f);	  //TopRightNear
		pOutFarPoints[6] = float4(LeftSlope,BottomSlope,NearZ,1.f);  //BottomLeftNear
		pOutFarPoints[7] = float4(RightSlope,BottomSlope,NearZ,1.f);    //BottomRightNear

	}
	return;
}

} // namespace Math
//------------------------------------------------------------------------------
    