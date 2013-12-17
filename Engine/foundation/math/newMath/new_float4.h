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
#include "math/OgreMath/OgreVector4.h"

//------------------------------------------------------------------------------
namespace Math
{
class matrix44;
class float4;

// win32 VC++ does not support passing aligned objects as value so far
// here is a bug-report at microsoft saying so:
// http://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=334581
typedef const float4& __Float4Arg;


class float4
{
public:
    /// default constructor, NOTE: does NOT setup components!
    float4();
    /// construct from values
    float4(scalar x, scalar y, scalar z, scalar w);
    /// !!!! copy constructor forbidden, otherwise passing float4's to a function
    /// !!!! via Registers doesnt work
    //float4(const float4& rhs);
    /// construct from Ogre::Vector4
	float4(Ogre::Vector4 rhs);

    /// assignment operator
    void operator=(const float4 &rhs);
    /// assign an Ogre::Vector4
    void operator=(Ogre::Vector4 rhs);
    /// flip sign
    float4 operator-() const;
    /// inplace add
    void operator+=(const float4 &rhs);
    /// inplace sub
    void operator-=(const float4 &rhs);
    /// inplace scalar multiply
    void operator*=(scalar s);
    /// muliply by a vector component-wise
    void operator*=(const float4& rhs);
    /// add 2 vectors
    float4 operator+(const float4 &rhs) const;
    /// subtract 2 vectors
    float4 operator-(const float4 &rhs) const;
    /// multiply with scalar
    float4 operator*(scalar s) const;
    /// equality operator
    bool operator==(const float4 &rhs) const;
    /// inequality operator
    bool operator!=(const float4 &rhs) const;
	/// [] operator
    scalar& operator[](const IndexT &index);

    /// write content to unaligned memory through the write cache
    void storeu(scalar* ptr) const;
	/// load content from unaligned memory
	void loadu(const scalar* ptr);
    /// stream content to 16-byte-aligned memory circumventing the write-cache
    void stream(scalar* ptr) const;

    /// set content
    void set(scalar x, scalar y, scalar z, scalar w);
    /// set the x component
    void set_x(scalar x);
    /// set the y component
    void set_y(scalar y);
    /// set the z component
    void set_z(scalar z);
    /// set the w component
    void set_w(scalar w);

    /// read/write access to x component
    scalar& x();
    /// read/write access to y component
    scalar& y();
    /// read/write access to z component
    scalar& z();
    /// read/write access to w component
    scalar& w();
    /// read-only access to x component
    scalar x() const;
    /// read-only access to y component
    scalar y() const;
    /// read-only access to z component
    scalar z() const;
    /// read-only access to w component
    scalar w() const;

    /// return length of vector
    scalar length() const;
    /// return squared length of vector
    scalar lengthsq() const;
    /// return compononent-wise absolute
    float4 abs() const;

    /// return 1.0 / vec
    static float4 reciprocal(const float4 &v);
    /// component-wise multiplication
    static float4 multiply(const float4 &v0, const float4 &v1);
    /// return 3-dimensional cross product
    static float4 cross3(const float4 &v0, const float4 &v1);
    /// return 3d dot product of vectors
    static scalar dot3(const float4 &v0, const float4 &v1);
	/// return 4d dot product of vectors
	static scalar dot4(const float4 &v0, const float4 &v1);
    /// perform linear interpolation between 2 4d vectors
    static float4 lerp(const float4 &v0, const float4 &v1, scalar s);
    /// return 4d vector made up of largest components of 2 vectors
    static float4 maximize(const float4 &v0, const float4 &v1);
    /// return 4d vector made up of smallest components of 2 vectors
    static float4 minimize(const float4 &v0, const float4 &v1);
    /// return normalized version of 4d vector
    static float4 normalize(const float4 &v);
	/// return floor of every vec elements
	static float4 floor(const float4 &v);

	/// transform 4d vector by matrix44
#ifdef __VC__
	static __declspec(deprecated) float4 transform(const matrix44 &m, __Float4Arg v);
#else
	static  float4 transform(const matrix44 &m, __Float4Arg v);
#endif
	

    /// return true if any XYZ component is less-then
    static bool less3_any(const float4 &v0, const float4 &v1);
    /// return true if all XYZ components are less-then
    static bool less3_all(const float4 &v0, const float4 &v1);
    /// return true if any XYZ component is greater
    static bool greater3_any(const float4 &v0, const float4 &v1);
    /// return true if any XYZ component is greater-or-equal
    static bool greaterequal3_any(const float4 &v0, const float4 &v1);
    /// return true if all XYZ components are greater-or-equal
    static bool greaterequal3_all(const float4 &v0, const float4 &v1);
    /// return true if any XYZ component is equal
    static bool equal3_any(const float4 &v0, const float4 &v1);
    /// return true if all XYZ components are equal
    static bool equal3_all(const float4 &v0, const float4 &v1);

    /// return true if any XYZW component is less-then
    static bool less4_any(const float4 &v0, const float4 &v1);
    /// unpack the first element from a Ogre::Vector4
	static float unpack_x(Ogre::Vector4 v);
    /// unpack the second element from a Ogre::Vector4
    static float unpack_y(Ogre::Vector4 v);
    /// unpack the third element from a Ogre::Vector4
    static float unpack_z(Ogre::Vector4 v);
    /// unpack the fourth element from a Ogre::Vector4
    static float unpack_w(Ogre::Vector4 v);

	Ogre::Vector4 vec;
};

//------------------------------------------------------------------------------
/**
*/
__forceinline
float4::float4() 
	: vec(0.0f,0.0f,0.0f,0.0f)
{
    //  empty
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
float4::float4(scalar x, scalar y, scalar z, scalar w)
{
    this->vec = Ogre::Vector4(x, y, z, w);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
float4::float4(Ogre::Vector4 rhs) :
    vec(rhs)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::operator=(const float4 &rhs)
{
    this->vec = rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::operator=(Ogre::Vector4 rhs)
{
    this->vec = rhs;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
float4::operator==(const float4 &rhs) const
{
    return this->vec == rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
float4::operator!=(const float4 &rhs) const
{
	return this->vec != rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar&
float4::operator[](const IndexT &index)
{
#if NEBULA3_BOUNDSCHECKS
    n_assert((index>=0) && (index<=3));
#endif
	return this->vec[index];
}

//------------------------------------------------------------------------------
/**
    Store to non-aligned float pointer.
*/
__forceinline void
float4::storeu(scalar* ptr) const
{
	memcpy(ptr,(void*)this->vec.ptr(),sizeof(float4));
}

//------------------------------------------------------------------------------
/**
    Load 4 floats from unaligned memory.
*/
__forceinline void
float4::loadu(const scalar* ptr)
{
    memcpy((void*)this->vec.ptr(),ptr,sizeof(float4));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::stream(scalar* ptr) const
{
	memcpy(ptr,(void*)this->vec.ptr(),sizeof(float4));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::operator-() const
{
	return -this->vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::operator*(scalar t) const
{
	return this->vec * t;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::operator*=(const float4& rhs)
{
	this->vec *= rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::operator+=(const float4 &rhs)
{
	this->vec += rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::operator-=(const float4 &rhs)
{
	this->vec = this->vec - rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::operator*=(scalar s)
{
	this->vec *= s;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::operator+(const float4 &rhs) const
{
	return this->vec + rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::operator-(const float4 &rhs) const
{
	return this->vec - rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::set(scalar x, scalar y, scalar z, scalar w)
{
	this->vec = Ogre::Vector4(x,y,z,w);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar&
float4::x()
{
    return this->vec.x;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
float4::x() const
{
    return float4::unpack_x(this->vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar&
float4::y()
{
    return this->vec.y;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
float4::y() const
{
    return float4::unpack_y(this->vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar&
float4::z()
{
    return this->vec.z;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
float4::z() const
{
    return float4::unpack_z(this->vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar&
float4::w()
{
    return this->vec.w;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
float4::w() const
{
    return float4::unpack_w(this->vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::set_x(scalar x)
{
    this->vec.x = x;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::set_y(scalar y)
{
	this->vec.y = y;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::set_z(scalar z)
{
	this->vec.z = z;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
float4::set_w(scalar w)
{
	this->vec.w = w;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
float4::length() const
{
	return Ogre::Vector3(this->vec.x,this->vec.y,this->vec.z).length();
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
float4::lengthsq() const
{
	return Ogre::Vector3(this->vec.x,this->vec.y,this->vec.z).squaredLength();
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::reciprocal(const float4 &v)
{
	return 1/v.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::multiply(const float4 &v0, const float4 &v1)
{
	return float4(v0.vec * v1.vec);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::abs() const
{
	return float4(fabsf(this->vec.x),fabsf(this->vec.y),fabsf(this->vec.z),fabsf(this->vec.w));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::cross3(const float4 &v0, const float4 &v1)
{
	return float4(Ogre::Vector4(Ogre::Vector3(v0.vec.x,v0.vec.y,v0.vec.z).crossProduct(Ogre::Vector3(v1.vec.x,v1.vec.y,v1.vec.z))));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
float4::dot3(const float4 &v0, const float4 &v1)
{
	return Ogre::Vector3(v0.vec.x,v0.vec.y,v0.vec.z).dotProduct(Ogre::Vector3(v1.vec.x,v1.vec.y,v1.vec.z));
}

//------------------------------------------------------------------------------
/**
*/
__forceinline scalar
float4::dot4(const float4 &v0, const float4 &v1)
{
	return v0.vec.x * v1.vec.x + v0.vec.y * v1.vec.y + v0.vec.z * v1.vec.z + v0.vec.w * v1.vec.w;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::lerp(const float4 &v0, const float4 &v1, scalar s)
{
	float4 Result;

	Result.set_x(v0.vec.x + s * (v1.vec.x - v0.vec.x));
	Result.set_y(v0.vec.y + s * (v1.vec.y - v0.vec.y));
	Result.set_z(v0.vec.z + s * (v1.vec.z - v0.vec.z));
	Result.set_w(v0.vec.w + s * (v1.vec.w - v0.vec.w));

	return Result;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::maximize(const float4 &v0, const float4 &v1)
{
	float4 result;
	result.set_x(v0.vec.x > v1.vec.x ? v0.vec.x : v1.vec.x);
	result.set_y(v0.vec.y > v1.vec.y ? v0.vec.y : v1.vec.y);
	result.set_z(v0.vec.z > v1.vec.z ? v0.vec.z : v1.vec.z);
	result.set_w(v0.vec.w > v1.vec.w ? v0.vec.w : v1.vec.w);
	return result;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::minimize(const float4 &v0, const float4 &v1)
{
	float4 result;
	result.set_x(v0.vec.x < v1.vec.x ? v0.vec.x : v1.vec.x);
	result.set_y(v0.vec.y < v1.vec.y ? v0.vec.y : v1.vec.y);
	result.set_z(v0.vec.z < v1.vec.z ? v0.vec.z : v1.vec.z);
	result.set_w(v0.vec.w < v1.vec.w ? v0.vec.w : v1.vec.w);
	return result;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float4
float4::normalize(const float4 &v)
{
    if (float4::equal3_all(v, float4(0,0,0,0))) return v;
	else
	{
		scalar fLength = Ogre::Math::Sqrt( v.vec.x * v.vec.x + v.vec.y * v.vec.y + v.vec.z * v.vec.z + v.vec.w + v.vec.w );
		// Will also work for zero-sized vectors, but will change nothing
		if ( fLength > 1e-08 )
		{
			float4 retv = v;
			scalar fInvLength = 1.0f / fLength;
			retv.vec.x *= fInvLength;
			retv.vec.y *= fInvLength;
			retv.vec.z *= fInvLength;
			retv.vec.w *= fInvLength;
			return retv;
		}
		return v;
	}
    
}
//------------------------------------------------------------------------------
/**
*/
__forceinline bool
float4::less4_any(const float4 &v0, const float4 &v1)
{
    return (v0.vec.x < v1.vec.x || v0.vec.y < v1.vec.y || v0.vec.z < v1.vec.z || v0.vec.w < v1.vec.w);
}
//------------------------------------------------------------------------------
/**
*/
__forceinline bool
float4::less3_any(const float4 &v0, const float4 &v1)
{
    return (v0.vec.x < v1.vec.x || v0.vec.y < v1.vec.y || v0.vec.z < v1.vec.z);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
float4::less3_all(const float4 &v0, const float4 &v1)
{
    return (v0.vec.x < v1.vec.x && v0.vec.y < v1.vec.y && v0.vec.z < v1.vec.z);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
float4::greater3_any(const float4 &v0, const float4 &v1)
{
    return (v0.vec.x > v1.vec.x || v0.vec.y > v1.vec.y || v0.vec.z > v1.vec.z);
}


//------------------------------------------------------------------------------
/**
*/
__forceinline bool
float4::greaterequal3_all(const float4 &v0, const float4 &v1)
{
    return (v0.vec.x >= v1.vec.x && v0.vec.y >= v1.vec.y && v0.vec.z >= v1.vec.z);
}


//------------------------------------------------------------------------------
/**
*/
__forceinline bool
float4::equal3_all(const float4 &v0, const float4 &v1)
{
    return (v0.vec.x == v1.vec.x && v0.vec.y == v1.vec.y && v0.vec.z == v1.vec.z);
}


//------------------------------------------------------------------------------
/**
*/
__forceinline float
float4::unpack_x(Ogre::Vector4 v)
{
	return v.x;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float
float4::unpack_y(Ogre::Vector4 v)
{
	return v.y;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float
float4::unpack_z(Ogre::Vector4 v)
{
	return v.z;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline float
float4::unpack_w(Ogre::Vector4 v)
{
	return v.w;
}

__forceinline float4
float4::floor(const float4 &v)
{
	float4 result;
	result.set(floorf(v.x()),floorf(v.y()),floorf(v.z()),floorf(v.w()));
	return result;
}

} // namespace Math
//------------------------------------------------------------------------------








