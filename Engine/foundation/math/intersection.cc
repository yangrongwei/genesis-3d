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
#include "stdneb.h"
#include "math/intersection.h"
#include <algorithm>
#include <limits>


namespace Math
{

//------------------------------------------------------------------------
//see dk sdk picking
bool
Intersection::Intersect( const Ray& ray, const float3& v0, const float3& v1, const float3& v2, scalar& fOut, scalar fTolerance )
{
	// Find vectors for two edges sharing vert0
	float3 edge1 = v1 - v0;
	float3 edge2 = v2 - v0;

	// Begin calculating determinant - also used to calculate U parameter
	float3 pvec = ray.Direction().crossProduct(edge2);

	// If determinant is near zero, ray lies in plane of triangle
	scalar det =  edge1.dotProduct(pvec);

	float3 tvec;

	if( det > 0 )
	{
		tvec = ray.Start() - v0;
	}
	else
	{
		tvec = v0 -  ray.Start();
		det = -det;
	}

	if( det < fTolerance )
		return false;

	// Calculate U parameter and test bounds
	scalar u = tvec.dotProduct(pvec);
	if( u < 0.0f || u > det )
		return false;

	// Prepare to test V parameter
	float3 qvec = tvec.crossProduct( edge1 );

	// Calculate V parameter and test bounds
	scalar v = ray.Direction().dotProduct( qvec);
	if( v < 0.0f || u + v > det )
		return false;

	// Calculate t, scale parameters, ray intersects triangle
	fOut =edge2.dotProduct( qvec );
	scalar fInvDet = 1.0f / det;
	fOut *= fInvDet;

	return true;

}
//------------------------------------------------------------------------

bool 
Intersection::Intersect( const Ray& ray1, const Ray& ray2, scalar& fOut1, scalar& fOut2, scalar fTolerance )
{
	const float3& dir1 = ray1.Direction();
	float3 c = dir1.crossProduct( ray2.Direction() );
	
	scalar clq = c.lengthsq();

	if ( n_fequal(clq, 0.0f,  fTolerance ) )
	{
		// 平行或者重合
		return false;
	}

	// 解方程组，得到两点射线上的最近点
	float3 pDiff = ray2.Start() - ray1.Start();

	float3 pDis_1 = pDiff.crossProduct( ray1.Direction() );
	float3 pDis_2 = pDiff.crossProduct( ray2.Direction() );

    scalar out1 = ( pDis_2.dotProduct( c ) ) / clq;
	scalar Out2 = ( pDis_1.dotProduct( c ) ) / clq;

	// 两个最近点的距离为0， 则相交
	float3 p1 = ray1.PointAt( out1 );
	float3 p2 = ray2.PointAt( Out2 );
	float3 lineseg = p2 - p1;
	scalar lineLength = lineseg.lengthsq();

	if ( n_fequal( lineLength, 0.0f, fTolerance) )
	{
		// 是否在射线的反方向
		if ( out1 < 0.0f || Out2 < 0.0f )
		{
			return false;
		}
		// intersect
		fOut1 = out1;
		fOut2 = Out2;
		return true;
	}
	else
	{
		return false;
	}

}
//------------------------------------------------------------------------
bool 
Intersection::Intersect( const Ray& ray1, const float3& lineBegin, const float3& lineEnd, scalar& fOut, scalar fTolerance )
{
	// 构建中一个射线
	float3 lineseg = lineEnd - lineBegin;

	if ( n_fequal(lineseg.lengthsq(), 0.0, fTolerance ) )
	{
		// 线退化为一个点。使用点的拾取
		if( Intersect(ray1, lineBegin, fTolerance  ) )
		{
			fOut = 0.0;
			return true;
		}
		else
		{
			return false;
		}
	}

	float3 normalDir = lineseg;
	normalDir.normalise();
	Ray ray2(lineBegin, normalDir );

	scalar fOut1;
	scalar fout2;

	if( Intersect(ray1, ray2, fOut1, fout2,  fTolerance) )
	{
		// 判断是在线段上还是在延长线上
		scalar linelength = lineseg.length();
		if(  fout2 < (linelength + fTolerance) )
		{
			fOut = fOut1;
			return true;
		}
	}

	return false;
}
//------------------------------------------------------------------------
bool 
Intersection::Intersect( const Ray& ray, const float3& p, scalar fTolerance )
{
	float3 dir = p - ray.Start();
	
	// 射线的反方向
	if ( dir.dotProduct( ray.Direction() ) < 0.0f )
	{
		return false;
	}

	float3 c = dir.crossProduct( ray.Direction() );
	scalar clq = c.lengthsq();

	if ( n_fequal(clq, 0.0f,  fTolerance ) )
	{
		// 平行或者重合
		return true;
	}
	else
	{
		return false;
	}
}

//------------------------------------------------------------------------
// Returns true if the ray stats inside the box or in front of the box
// if intersect, fOut1 is the first intersection;fOut2 is the second intersection
// from Ogre
bool 
Intersection::Intersect(const Ray& ray, const bbox& box, scalar& fOut1, scalar& fOut2)
{
	float3 bmin(box.pmin.x(), box.pmin.y(),box.pmin.z());
	float3 bmax(box.pmax.x(), box.pmax.y(),box.pmax.z());
	float3 rayorig = ray.Start();
	float3 raydir = ray.Direction();

	float3 absDir;
	absDir[0] = n_abs(raydir[0]);
	absDir[1] = n_abs(raydir[1]);
	absDir[2] = n_abs(raydir[2]);

	// Sort the axis, ensure check minimise floating error axis first
	int imax = 0, imid = 1, imin = 2;
	if (absDir[0] < absDir[2])
	{
		imax = 2;
		imin = 0;
	}
	if (absDir[1] < absDir[imin])
	{
		imid = imin;
		imin = 1;
	}
	else if (absDir[1] > absDir[imax])
	{
		imid = imax;
		imax = 1;
	}

	scalar start = 0, end = N_INFINITY;

#define _CALC_AXIS(i)                                       \
	do {                                                    \
	scalar denom = 1 / raydir[i];                         \
	scalar newstart = (bmin[i] - rayorig[i]) * denom;      \
	scalar newend = (bmax[i] - rayorig[i]) * denom;        \
	if (newstart > newend) std::swap(newstart, newend); \
	if (newstart > end || newend < start) return false; \
	if (newstart > start) start = newstart;             \
	if (newend < end) end = newend;                     \
	} while(0)

	// Check each axis in turn

	_CALC_AXIS(imax);

	if (absDir[imid] < std::numeric_limits<scalar>::epsilon())
	{
		// Parallel with middle and minimise axis, check bounds only
		if (rayorig[imid] < bmin[imid] || rayorig[imid] > bmax[imid] ||
			rayorig[imin] < bmin[imin] || rayorig[imin] > bmax[imin])
			return false;
	}
	else
	{
		_CALC_AXIS(imid);

		if (absDir[imin] < std::numeric_limits<scalar>::epsilon())
		{
			// Parallel with minimise axis, check bounds only
			if (rayorig[imin] < bmin[imin] || rayorig[imin] > bmax[imin])
				return false;
		}
		else
		{
			_CALC_AXIS(imin);
		}
	}
#undef _CALC_AXIS

	fOut1 = start;
	fOut2 = end;

	return true;
}
//------------------------------------------------------------------------
// return true if the sphere 0 intersect sphere 1
bool 
Intersection::Intersect(const Math::sphere& s0, const Math::sphere& s1 )
{
	point c_ = s0.p - s1.p;
	float3 c(c_.x(),c_.y(),c_.z() );

	float lengthsq = c.lengthsq();

	if ( n_sqrt( s0.r + s1.r ) > lengthsq )
		return true;
	else
		return false;
}

// return true if intersect
bool 
Intersection::Intersect(const sphere& sph, const frustum& fru)
{
	return Intersect (sph, fru.planes, frustum::NumPlanes);
}

bool
Intersection::Intersect(const sphere& sph, const plane* p, const int planeCount)
{
	for (int i = 0; i < planeCount; ++i)
	{
		float dist = p[i].distance(sph.p);
		if (dist - sph.r > 0) 
			return false; 
	}
	return true;
}

bool
Intersection::Intersect(const bbox& box, const sphere& sph)
{
	float4 vec4 = float4::minimize(float4::maximize(sph.p, box.pmin), box.pmax);

	float num3 = sph.p.x() - vec4.x();
	float num2 = sph.p.y() - vec4.y();
	float num = sph.p.z() - vec4.z();
	float num4 = ((num3 * num3) + (num2 * num2)) + (num * num);//sph 和 vec4的距离的平方

	return num <= (sph.r * sph.r);
}

}