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
#ifndef __intersection_H__
#define __intersection_H__
#include "math/ray.h"
#include "math/sphere_.h"
#include "math/bbox.h"
#include "math/plane.h"
#include "math/frustum.h"


namespace Math
{
	class Intersection
	{
	public:
		// Returns true if intersected
		// if intersected, fOut returns the first intersection point of the ray 
		static bool Intersect( const Ray& ray, const float3& v0, const float3& v1, const float3& v2, scalar& fOut, scalar fTolerance = N_TINY );

		//// Return true if the ray1 intersect ray2
		//// if intersected, fOut1 returns the intersection point of the ray1 
		//// if intersected, fOut2 returns the intersection point of the ray2 
		static bool Intersect( const Ray& ray1, const Ray& ray2, scalar& fOut1, scalar& fOut2, scalar fTolerance = N_TINY );

		//// return true if the ray intersect line segment
		//// if intersect, fOut returns the intersection point of the ray
		static bool Intersect( const Ray& ray, const float3& lineBegin, const float3& lineEnd,scalar& fOut, scalar fTolerance = N_TINY );

		//// return ture if the ray Intersect the point.
		static bool Intersect( const Ray& ray, const float3& p, scalar fTolerance = N_TINY);

		// Returns true if the ray stats inside the box or in front of the sphere
		// if intersect, fOut1 is the first intersection;fOut2 is the second intersection
		static bool Intersect(const Ray& ray, const bbox& box, scalar& fOut1, scalar& fOut2);

		// return true if the sphere 0 intersect sphere 1
		static bool Intersect(const sphere& s0, const sphere& s1 );

		static bool Intersect(const bbox& box, const sphere& sph);

		static bool Intersect(const sphere& sph, const frustum& fru);

		static bool Intersect(const sphere& sph, const plane* p, const int planeCount);

	};

}





#endif // __intersection_H__
