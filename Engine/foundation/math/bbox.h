/****************************************************************************
Copyright (c) 2004, Radon Labs GmbH
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
#ifndef MATH_BBOX_H
#define MATH_BBOX_H
//------------------------------------------------------------------------------
/**
    @class Math::bbox

    Nebula's bounding box class.

    @todo: UNTESTED!

*/
#include "math/point.h"
#include "math/vector.h"
#include "math/matrix44.h"
#include "math/line.h"
#include "math/plane.h"
#include "math/clipstatus.h"
#include "util/array.h"

//------------------------------------------------------------------------------
namespace Math
{
class bbox
{
public:
    /// clip codes
    enum 
    {
        ClipLeft   = (1<<0),
        ClipRight  = (1<<1),
        ClipBottom = (1<<2),
        ClipTop    = (1<<3),
        ClipNear   = (1<<4),
        ClipFar    = (1<<5),
    };

    /// constructor 1
    bbox();
    /// constructor 3
	explicit bbox(const point& center, const vector& extents);   
	/// constructor 3
	explicit bbox(const point& min, const point& max);
    /// construct bounding box from matrix44
    bbox(const matrix44& m);
	/// equality operator
	bool operator==(const bbox& rhs) const;
	/// inequality operator
	bool operator!=(const bbox& rhs) const;
    /// get center of box
    point center() const;
    /// get extents of box
    vector extents() const;
    /// get size of box
    vector size() const;
    /// get diagonal size of box
    scalar diagonal_size() const;
    /// set from matrix44
    void set(const matrix44& m);
    /// set from center point and extents
    void set(const point& center, const vector& extents);
	/// set pmin and pmax
	void set(const point& min, const point& max);
    /// begin extending the box
    void begin_extend();
    /// extend the box
    void extend(const point& p);
    /// extend the box
    void extend(const bbox& box);
    /// this resets the bounding box size to zero if no extend() method was called after begin_extend()
    void end_extend();
    /// transform bounding box
    void transform(const matrix44& m);
    /// check for intersection with axis aligned bounding box
    bool intersects(const bbox& box) const;
    /// check if this box completely contains the parameter box
    bool contains(const bbox& box) const;
    /// return true if this box contains the position
    bool contains(const point& p) const;
    /// check for intersection with other bounding box
    ClipStatus::Type clipstatus(const bbox& other) const;
    /// check for intersection with projection volume
    ClipStatus::Type clipstatus(const matrix44& viewProjection) const;
    /// create a matrix which transforms a unit cube to this bounding box
    matrix44 to_matrix44() const;
    /// return one of the 8 corner points
    point corner_point(int index) const;
    /// return side planes in clip space
    void get_clipplanes(const matrix44& viewProjection, Util::Array<plane>& outPlanes) const;
	/// 点到盒的最近距离的平方
	scalar distancesq(const Math::vector &p) const;
	/// convert to any type
    template<typename T> T as() const;
	
	static const bbox Zero; 

    point pmin;
    point pmax;
};

//------------------------------------------------------------------------------
/**
*/
inline
bbox::bbox() :
    pmin(-0.5f, -0.5f, -0.5f),
    pmax(+0.5f, +0.5f, +0.5f)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
bbox::bbox(const point& center, const vector& extents)
{
    this->pmin = center - extents;
    this->pmax = center + extents;
}
//------------------------------------------------------------------------------
/**
*/
inline
bbox::bbox(const point& min, const point& max)
{
	this->pmin = min;
	this->pmax = max;
}
//------------------------------------------------------------------------
/// equality operator
inline bool 
bbox::operator==(const bbox& rhs) const
{
	return (this->pmin == rhs.pmin) && (this->pmax == rhs.pmax);
}
/// inequality operator
inline bool 
bbox::operator!=(const bbox& rhs) const
{
	return (this->pmin != rhs.pmin) || (this->pmax != rhs.pmax);
}
//------------------------------------------------------------------------------
/**
    Construct a bounding box around a 4x4 matrix. The translational part
    defines the center point, and the x,y,z vectors of the matrix
    define the extents.
*/
inline void
bbox::set(const matrix44& m)
{
    // get extents
    vector extents = ( m.get_xaxis().abs() + m.get_yaxis().abs() + m.get_zaxis().abs() ) * 0.5f;
    point center = m.get_position();
    this->pmin = center - extents;
    this->pmax = center + extents;
}
//------------------------------------------------------------------------------
/**
*/
inline void 
bbox::set(const point& min, const point& max)
{
	this->pmin = min;
	this->pmax = max;
}
//------------------------------------------------------------------------------
/**
*/
inline
bbox::bbox(const matrix44& m)
{
    this->set(m);
}

//------------------------------------------------------------------------------
/**
*/
inline point
bbox::center() const
{
    return this->pmin + ((this->pmax - this->pmin) * 0.5f);
}

//------------------------------------------------------------------------------
/**
*/
inline vector
bbox::extents() const
{
    return (this->pmax - this->pmin) * 0.5f;
}

//------------------------------------------------------------------------------
/**
*/
inline vector
bbox::size() const
{
    return this->pmax - this->pmin;
}

//------------------------------------------------------------------------------
/**
*/
inline void
bbox::set(const point& center, const vector& extents)
{
    this->pmin = center - extents;
    this->pmax = center + extents;
}

//------------------------------------------------------------------------------
/**
*/
inline void
bbox::begin_extend()
{
    this->pmin.set(N_FLOAT32_MAX, N_FLOAT32_MAX, N_FLOAT32_MAX);
    this->pmax.set(N_FLOAT32_MIN, N_FLOAT32_MIN, N_FLOAT32_MIN);
}

//------------------------------------------------------------------------------
/**
    This just checks whether the extend() method has actually been called after
    begin_extend() and just sets vmin and vmax to the null vector if it hasn't.
*/
inline
void
bbox::end_extend()
{
    if ((this->pmin == point(N_FLOAT32_MAX, N_FLOAT32_MAX, N_FLOAT32_MAX)) &&
        (this->pmax == point(N_FLOAT32_MIN, N_FLOAT32_MIN, N_FLOAT32_MIN)))
    {
        this->pmin.set(0.0f, 0.0f, 0.0f);
        this->pmax.set(0.0f, 0.0f, 0.0f);
    }
}

//------------------------------------------------------------------------------
/**
*/
inline void
bbox::extend(const point& p)
{
    this->pmin = float4::minimize(this->pmin, p);
    this->pmax = float4::maximize(this->pmax, p);
}

//------------------------------------------------------------------------------
/**
*/
inline
void
bbox::extend(const bbox& box)
{
    this->pmin = float4::minimize(this->pmin, box.pmin);
    this->pmax = float4::maximize(this->pmax, box.pmax);
}

//------------------------------------------------------------------------------
/**
    Transforms this axis aligned bounding by the 4x4 matrix. This bounding
    box must be axis aligned with the matrix, the resulting bounding
    will be axis aligned in the matrix' "destination" space.

    E.g. if you have a bounding box in model space 'modelBox', and a
    'modelView' matrix, the operation
    
    modelBox.transform(modelView)

    would transform the bounding box into view space.
*/
inline void
bbox::transform(const matrix44& m)
{
    Math::point temp;
    Math::point minP(1000000, 1000000,1000000);
    Math::point maxP(-1000000, -1000000, -1000000);        
    IndexT i; 
        
    for(i = 0; i < 8; ++i)
    {
        // Transform and check extents
        temp = Math::matrix44::transform( m, corner_point(i));
        if (temp.x() > maxP.x())   maxP.x() = temp.x();
        if (temp.y() > maxP.y())   maxP.y() = temp.y();
        if (temp.z() > maxP.z())   maxP.z() = temp.z();
        if (temp.x() < minP.x())   minP.x() = temp.x();
        if (temp.y() < minP.y())   minP.y() = temp.y();
        if (temp.z() < minP.z())   minP.z() = temp.z();
    }    

    this->pmin = minP;
    this->pmax = maxP;
}

//------------------------------------------------------------------------------
/**
    Check for intersection of 2 axis aligned bounding boxes. The 
    bounding boxes must live in the same coordinate space.
*/
inline bool
bbox::intersects(const bbox& box) const
{
    bool lt = float4::less3_any(this->pmax, box.pmin);
    bool gt = float4::greater3_any(this->pmin, box.pmax);
    return !(lt || gt);
}

//------------------------------------------------------------------------------
/**
    Check if the parameter bounding box is completely contained in this
    bounding box.
*/
inline bool
bbox::contains(const bbox& box) const
{
    bool lt = float4::less3_all(this->pmin, box.pmin);
    bool ge = float4::greaterequal3_all(this->pmax, box.pmax);
    return lt && ge;
}

//------------------------------------------------------------------------------
/**
    Check if position is inside bounding box.
*/
inline bool
bbox::contains(const point& p) const
{
    bool lt = float4::less3_all(this->pmin, p);
    bool ge = float4::greaterequal3_all(this->pmax, p);
    return lt && ge;
}

//------------------------------------------------------------------------------
/**
    Create a transform matrix which would transform a unit cube to this
    bounding box.
*/
inline matrix44
bbox::to_matrix44() const
{
    matrix44 m = matrix44::scaling(this->size() * 0.5f);
    float4 pos = this->center();
    m.setrow3(pos);
    return m;
}

//------------------------------------------------------------------------------
/**
*/
inline scalar
bbox::diagonal_size() const
{
    return (this->pmax - this->pmin).length();
}

} // namespace Math
//------------------------------------------------------------------------------
#endif
