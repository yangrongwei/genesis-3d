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
#ifndef __ray_H__
#define __ray_H__

#include "math/float3.h"
#include "math/matrix44.h"

namespace Math
{
	class Ray
	{
	public:
		Ray();
		
		Ray(const float3& origin, const float3& normalizeDir);
		
		const float3& Start() const;
		
		void Start(const float3& startPoint);

		const float3& Direction() const;
		void DirectionNormalize( const float3& normalizeDir );

		float3 PointAt(scalar t) const;

		float SqrDistance(const float3 &q) const;

		Ray Tramsform(const matrix44& m) const;

	protected:
		float3 mOrigin;
		float3 mDir;
	};
	//------------------------------------------------------------------------
	inline
	Ray::Ray()
	{

	}
	//------------------------------------------------------------------------
	inline
	Ray::Ray( const float3& origin, const float3& normalizeDir )
	{
		n_assert( float3::isNormalize(normalizeDir) );
		mOrigin = origin;
		mDir = normalizeDir;
	}
	//------------------------------------------------------------------------
	inline
	const float3& 
	Ray::Start() const
	{
		return mOrigin;
	}
	//------------------------------------------------------------------------
	inline
	void 
	Ray::Start(const float3& startPoint)
	{
		mOrigin = startPoint;
	}
	//------------------------------------------------------------------------
	inline 
	const float3&
	Ray::Direction() const
	{
		return mDir;
	}
	//------------------------------------------------------------------------
	inline 
	void 
	Ray::DirectionNormalize( const float3& normalizeDir )
	{
		n_assert( float3::isNormalize(normalizeDir) );
		mDir = normalizeDir;
	}
	//------------------------------------------------------------------------
	inline
	float3 
	Ray::PointAt(scalar t) const
	{
		return mOrigin + t * mDir;
	}
	//------------------------------------------------------------------------
	// <Geometric Tools for computer Graphics> P265
	inline
	float 
	Ray::SqrDistance (const float3 & q) const
	{
		float3 vectorSubtract = q - mOrigin; 

		float t1 = mDir.dotProduct(vectorSubtract); 
		float t2 = mDir.dotProduct(mDir); 

		n_assert( t2 != 0.0f );
		float t = t1 / t2; 

		float3 qPrime = PointAt (t);
		float3 pLength = q - qPrime;
		return pLength.lengthsq();
	}
	//------------------------------------------------------------------------
	inline
	Ray Ray::Tramsform(const matrix44& m) const
	{
		float3 origin = mOrigin.transformPoint(m);
		float3 normalizeDir = mDir.transformVector(m);
		normalizeDir.normalise();
		return Ray(origin,normalizeDir);
	}

}







#endif // __ray_H__
