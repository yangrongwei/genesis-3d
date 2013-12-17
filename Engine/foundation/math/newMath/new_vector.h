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
#include "math/float4.h"

//------------------------------------------------------------------------------
namespace Math
{
class vector;


// win32 VC++ does not support passing aligned objects as value so far
// here is a bug-report at microsoft saying so:
// http://connect.microsoft.com/VisualStudio/feedback/ViewFeedback.aspx?FeedbackID=334581
typedef const vector& __VectorArg;



 

class vector : public float4
{
public:
    /// default constructor
    vector();
    /// construct from components
    vector(scalar x, scalar y, scalar z);
    /// construct from float4
    vector(const float4& rhs);
    /// construct from Ogre::Vector4
	vector(Ogre::Vector4 rhs);
    /// return the null vector
    static vector nullvec();
    /// return the standard up vector (0, 1, 0)
    static vector upvec();
    /// assignment operator
    void operator=(const vector& rhs);
    /// assign Ogre::Vector4
    void operator=(Ogre::Vector4 rhs);
    /// flip sign
    vector operator-() const;
    /// add vector inplace
    void operator+=(const vector& rhs);
    /// subtract vector inplace
    void operator-=(const vector& rhs);
    /// scale vector inplace
    void operator*=(scalar s);
    /// add 2 vectors
    vector operator+(const vector& rhs) const;
    /// subtract 2 vectors
    vector operator-(const vector& rhs) const;
    /// scale vector
    vector operator*(scalar s) const;
	/// scale vector by vector
	vector operator*(const vector& rhs) const;
	/// scale vector by vector
	vector operator/(const vector& rhs) const;
	/// scale vector by vector
	void operator*=(const vector& rhs);
	/// scale vector by vector
	void operator/=(const vector& rhs);
    /// equality operator
    bool operator==(const vector& rhs) const;
    /// inequality operator
    bool operator!=(const vector& rhs) const;
	// cross Product
	vector crossProduct(const vector& rkVector) const;
	// dot Product
	Math::scalar dotProduct(const vector& vec) const;
    /// set components
    void set(scalar x, scalar y, scalar z);
	static vector divide_xyz(const vector& lhs, const vector& rhs);

    friend class point;
};

//------------------------------------------------------------------------------
/**
*/
__forceinline
vector::vector() :
    float4(0.0f, 0.0f, 0.0f, 0.0f)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
vector::vector(scalar x, scalar y, scalar z) :
    float4(x, y, z, 0.0f)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
vector::vector(const float4& rhs) :
    float4(rhs)
{
    this->set_w(0.0f);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline
vector::vector(Ogre::Vector4 rhs) :
    float4(rhs)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
__forceinline vector
vector::nullvec()
{
    return vector(0.0f, 0.0f, 0.0f);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline vector
vector::upvec()
{
    return vector(0.0f, 1.0f, 0.0f);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
vector::operator=(const vector& rhs)
{
    this->vec = rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
vector::operator=(Ogre::Vector4 rhs)
{
    this->vec = rhs;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline vector
vector::operator-() const
{
	return -this->vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
vector::operator+=(const vector& rhs)
{
	this->vec += rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
vector::operator-=(const vector& rhs)
{
	this->vec -= rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline void
vector::operator*=(scalar s)
{
	this->vec *= s;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline vector
vector::operator+(const vector& rhs) const
{
	return this->vec + rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline vector
vector::operator-(const vector& rhs) const
{
	return this->vec - rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline vector
vector::operator*(scalar s) const
{
	return this->vec * s;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
vector::operator==(const vector& rhs) const
{
	return this->vec == rhs.vec;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
vector::operator!=(const vector& rhs) const
{
	return this->vec != rhs.vec;
}    

//------------------------------------------------------------------------------
/**
*/
__forceinline void
vector::set(scalar x, scalar y, scalar z)
{
    float4::set(x, y, z, 0.0f);
}

//------------------------------------------------------------------------
/// scale vector by vector
__forceinline vector
 vector::operator*(const vector& rhs) const
{
	return this->vec * rhs.vec;
}

//------------------------------------------------------------------------
/// scale vector by vector
__forceinline vector
	vector::operator/(const vector& rhs) const
{
	return this->vec / rhs.vec;
}
//------------------------------------------------------------------------
/// scale vector by vector
__forceinline void 
vector::operator*=(const vector& rhs)
{
	this->vec = this->vec * rhs.vec;
}
//------------------------------------------------------------------------
/// scale vector by vector
__forceinline void 
	vector::operator/=(const vector& rhs)
{
	this->vec /= rhs.vec;
}
//------------------------------------------------------------------------
__forceinline vector 
vector::crossProduct( const vector& rkVector ) const
{
	return vector(
		y() * rkVector.z() - z() * rkVector.y(),
		z() * rkVector.x() - x() * rkVector.z(),
		x() * rkVector.y() - y() * rkVector.x() );
}
//------------------------------------------------------------------------
__forceinline Math::scalar 
vector::dotProduct(const vector& vec) const
{
	return x() * vec.x() + y() * vec.y() + z() * vec.z();
}
//------------------------------------------------------------------------
__forceinline vector
vector::divide_xyz(const vector& lhs, const vector& rhs)
{
	return vector(lhs.x() / rhs.x(), lhs.y() / rhs.y(), lhs.z() / rhs.z());
}
} // namespace Math
//------------------------------------------------------------------------------
