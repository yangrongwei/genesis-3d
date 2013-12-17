/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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
#include "core/types.h"
#include "math/scalar.h"
#include "math/float4.h"
#include "math/line.h"
#include "math/clipstatus.h"
//#include "math/float3.h"
//------------------------------------------------------------------------------
namespace Math
{
class matrix44;
class plane;
//class float3;

// win32 VC++ does not support passing aligned objects as value so far
// here is a bug-report at microsoft saying so:
// http://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=334581
typedef const plane& __PlaneArg;
 

class plane
{
public:
    /// default constructor, NOTE: does NOT setup componenets!
    plane();
    /// !!!! copy constructor forbidden, otherwise passing plane's to a function
    /// !!!! via Registers doesnt work
    //plane(const plane& rhs);
    /// construct from components
    plane(scalar a, scalar b, scalar c, scalar d);
    /// construct from points
    plane(const float4& p0, const float4& p1, const float4& p2);
    /// construct from point and normal
    plane(const float4& p, const float4& n);
    /// construct from Ogre::Vector4
	plane(Ogre::Vector4 rhs);

    /// setup from points
    void setup_from_points(const float4& point1, const float4& point2, const float4& point3);
    /// setup from point and normal
    void setup_from_point_and_normal(const float4& p, const float4& n);
    /// set componenets
    void set(scalar a, scalar b, scalar c, scalar d);
    /// set the x component
    void set_a(scalar a);
    /// set the y component
    void set_b(scalar b);
    /// set the z component
    void set_c(scalar c);
    /// set the w component
    void set_d(scalar d);

    /// read/write access to A component
    scalar& a();
    /// read/write access to B component
    scalar& b();
    /// read/write access to C component
    scalar& c();
    /// read/write access to D component
    scalar& d();
    /// read-only access to A component
    scalar a() const;
    /// read-only access to B component
    scalar b() const;
    /// read-only access to C component
    scalar c() const;
    /// read-only access to D component
    scalar d() const;

    /// compute dot product of plane and vector
    scalar dot(const float4& v) const;
    /// find intersection with line
    bool intersectline(const float4& startPoint, const float4& endPoint, float4& outIntersectPoint) const;
    /// clip line against this plane
    ClipStatus::Type clip(const line& l, line& outClippedLine) const;
    /// normalize plane components a,b,c

	/// distance to point
	float distance(const point& pl) const;

    static plane normalize(const plane& p);
    /// transform plane by inverse transpose of transform
#ifdef __VC__
	static __declspec(deprecated) plane transform( const matrix44& m, __PlaneArg p);
#else
	static plane transform( const matrix44& m, __PlaneArg p);
#endif
    

	Ogre::Vector4 vec;
private:
    friend class matrix44;

	
};

//------------------------------------------------------------------------------
/**
*/
inline
plane::plane()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
plane::plane(scalar a, scalar b, scalar c, scalar d)
{
    this->vec = Ogre::Vector4(a, b, c, d);
}

//------------------------------------------------------------------------------
/**
*/
inline
plane::plane(const float4& p0, const float4& p1, const float4& p2)
{
    this->setup_from_points(p0, p1, p2);
}

//------------------------------------------------------------------------------
/**
*/
inline
plane::plane(const float4& p0, const float4& n)
{
    this->setup_from_point_and_normal(p0, n);
}

//------------------------------------------------------------------------------
/**
*/
inline
plane::plane(Ogre::Vector4 rhs) :
    vec(rhs)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline void
plane::setup_from_points(const float4& point1, const float4& point2, const float4& point3)
{
	//float4 Result;
	//Ogre::Vector3 N;
	//float4 D;

	//Ogre::Vector3 V21 = Ogre::Vector3(p0.x(),p0.y(),p0.z()) - Ogre::Vector3(p1.x(),p1.y(),p1.z());
	//Ogre::Vector3 V31 = Ogre::Vector3(p0.x(),p0.y(),p0.z()) - Ogre::Vector3(p2.x(),p2.y(),p2.z());

	//N = V21.crossProduct(V31);
	//N = N.normalise();

	////D = XMPlaneDotNormal(N, p1);
	//D.set_x(N.dotProduct(Ogre::Vector3(p1.x(),p1.y(),p1.z())));
	//D.set_y(N.dotProduct(Ogre::Vector3(p1.x(),p1.y(),p1.z())));
	//D.set_z(N.dotProduct(Ogre::Vector3(p1.x(),p1.y(),p1.z())));
	//D.set_w(N.dotProduct(Ogre::Vector3(p1.x(),p1.y(),p1.z())));
	//Result.set_x(N.x);
	//Result.set_y(N.y);
	//Result.set_z(N.z);
	//Result.set_w(-D.w());


	//this->vec = Result.vec;
 //   //this->vec = XMPlaneFromPoints(p0.vec, p1.vec, p2.vec);

	float num10 = point2.x() - point1.x();
	float num9 = point2.y() - point1.y();
	float num8 = point2.z() - point1.z();
	float num7 = point3.x() - point1.x();
	float num6 = point3.y() - point1.y();
	float num5 = point3.z() - point1.z();
	float num4 = (num9 * num5) - (num8 * num6);
	float num3 = (num8 * num7) - (num10 * num5);
	float num2 = (num10 * num6) - (num9 * num7);
	float num11 = ((num4 * num4) + (num3 * num3)) + (num2 * num2);
	float num = 1.0f / n_sqrt(num11);
	this->vec.x = num4 * num;
	this->vec.y = num3 * num;
	this->vec.z = num2 * num;
	this->vec.w = -(this->vec.x * point1.x() + this->vec.y * point1.y() + this->vec.z * point1.z());


}

//------------------------------------------------------------------------------
/**
*/
inline void
plane::setup_from_point_and_normal(const float4& p, const float4& n)
{
	float4 Result(0.0f,0.0f,0.0f,0.0f);

	Result.set_x(n.x());
	Result.set_y(n.y());
	Result.set_z(n.z());
	float temp = p.x() * n.x() + p.y() * n.y() + p.z() * n.z();
	Result.set_w(-temp);

	this->vec = Result.vec;
}

//------------------------------------------------------------------------------
/**
*/
inline void
plane::set(scalar a, scalar b, scalar c, scalar d)
{
    this->vec = Ogre::Vector4(a, b, c, d);
}

//------------------------------------------------------------------------------
/**
*/
inline scalar&
plane::a()
{
    return this->vec.x;
}

//------------------------------------------------------------------------------
/**
*/
inline scalar
plane::a() const
{
    return this->vec.x;
}

//------------------------------------------------------------------------------
/**
*/
inline scalar&
plane::b()
{
    return this->vec.y;

}

//------------------------------------------------------------------------------
/**
*/ 
inline scalar
plane::b() const
{
    return this->vec.y;
}

//------------------------------------------------------------------------------
/**
*/
inline scalar&
plane::c()
{
    return this->vec.z;
}

//------------------------------------------------------------------------------
/**
*/
inline scalar
plane::c() const
{
    return this->vec.z;
}

//------------------------------------------------------------------------------
/**
*/
inline scalar&
plane::d()
{
    return this->vec.w;
}

//------------------------------------------------------------------------------
/**
*/
inline scalar
plane::d() const
{
	return this->vec.w;
}

//------------------------------------------------------------------------------
/**
*/
inline scalar
plane::dot(const float4& v) const
{
	return float4::dot4(float4(vec),v);
    //return float4::unpack_x(XMPlaneDot(this->vec, v.vec));
}

//------------------------------------------------------------------------------
/** TODO: this function does not verified by now
 ** Warning: this function is assumed that the plane w is 0.0f,it passed ogrin point
*/
inline bool
plane::intersectline(const float4& startPoint, const float4& endPoint, float4& outIntersectPoint) const
{
	Ogre::Vector4 d = Ogre::Vector4(endPoint.vec.x,endPoint.vec.y,endPoint.vec.z,1.0) - Ogre::Vector4(startPoint.vec.x,startPoint.vec.y,startPoint.vec.z,1.0);
	float denom = vec.dotProduct(d);
	if (fabsf(denom) < std::numeric_limits<scalar>::epsilon())
	{
		//Parallel
		return false;
	}
	else
	{
		scalar nom = vec.dotProduct(Ogre::Vector4(startPoint.vec.x,startPoint.vec.y,startPoint.vec.z,0.0)) + vec.w;
		scalar t = -(nom/denom);
		if (t >= 0 && t <= 1)
		{
			Ogre::Vector3 intersectp = Ogre::Vector3(startPoint.x(),startPoint.y(),startPoint.z()) + t * Ogre::Vector3(d.x,d.y,d.z);
			outIntersectPoint.set_x(intersectp.x);
			outIntersectPoint.set_y(intersectp.y);
			outIntersectPoint.set_z(intersectp.z);
			outIntersectPoint.set_w(1.0f);
			return true; 
		}
		else
			return false;
		
	}
	/*
    outIntersectPoint = XMPlaneIntersectLine(this->vec, startPoint.vec, endPoint.vec);
    if (XMPlaneIsNaN(outIntersectPoint.vec))
    {
        return false;
    }
    else
    {
        return true;
    }
    */
}

//------------------------------------------------------------------------------
/**
*/
inline plane
plane::normalize(const plane& p)
{
	plane ret;
	ret.vec = float4::normalize(float4(p.vec)).vec;
	return ret;
	//return float4::normalize(float4(p.vec));
}
//------------------------------------------------------------------------------
/**
*/
inline void 
plane::set_a(scalar a)
{
    this->vec.x = a;
}

//------------------------------------------------------------------------------
/**
*/
inline void 
plane::set_b(scalar b)
{
	this->vec.y = b;
    //this->vec = XMVectorSetYPtr(this->vec, &b);
}

//------------------------------------------------------------------------------
/**
*/
inline void 
plane::set_c(scalar c)
{
	this->vec.z = c;
    //this->vec = XMVectorSetZPtr(this->vec, &c);
}

//------------------------------------------------------------------------------
/**
*/
inline void 
plane::set_d(scalar d)
{
	this->vec.w = d;
    //this->vec = XMVectorSetWPtr(this->vec, &d);
}

//------------------------------------------------------------------------------
/**
*/
inline ClipStatus::Type
plane::clip(const line& l, line& clippedLine) const
{
    n_assert(&l != &clippedLine);
    float d0 = this->dot(l.start());
    float d1 = this->dot(l.end());
    if ((d0 >= N_TINY) && (d1 >= N_TINY))
    {
        // start and end point above plane
        clippedLine = l;
        return ClipStatus::Inside;
    }
    else if ((d0 < N_TINY) && (d1 < N_TINY))
    {
        // start and end point below plane
        return ClipStatus::Outside;
    }
    else
    {
        // line is clipped
        point clipPoint;
        this->intersectline(l.start(), l.end(), clipPoint);
        if (d0 >= N_TINY)
        {
            clippedLine.set(l.start(), clipPoint);
        }
        else
        {
            clippedLine.set(clipPoint, l.end());
        }
        return ClipStatus::Clipped;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline float
plane::distance(const point& po) const
{
	return a() * po.x() + b() * po.y() + c() * po.z() + d();
}

} // namespace Math
//------------------------------------------------------------------------------
