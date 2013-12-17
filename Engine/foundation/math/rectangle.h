/****************************************************************************
Copyright (c) 2003, Radon Labs GmbH
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
#ifndef MATH_RECTANGLE_H
#define MATH_RECTANGLE_H
//------------------------------------------------------------------------------
/**
    @class Math::rectangle

    A 2d rectangle class.
*/
#include "core/types.h"

//------------------------------------------------------------------------------
namespace Math
{
template<class TYPE> class rectangle
{
public:
    /// default constructor
    rectangle();
    /// constructor 1
    rectangle(TYPE l, TYPE t, TYPE r, TYPE b);
    /// set content
    void set(TYPE l, TYPE t, TYPE r, TYPE b);
    /// return true if point is inside
    bool inside(TYPE x, TYPE y) const;
    /// return width
    TYPE width() const;
    /// return height
    TYPE height() const;
    /// return center x
    TYPE centerX() const;
    /// return center y
    TYPE centerY() const;

    TYPE left;
    TYPE top;
    TYPE right;
    TYPE bottom;
};

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
rectangle<TYPE>::rectangle()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
rectangle<TYPE>::rectangle(TYPE l, TYPE t, TYPE r, TYPE b) :
    left(l),
    top(t),
    right(r),
    bottom(b)
{
    n_assert(this->left <= this->right);
    n_assert(this->top <= this->bottom);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
rectangle<TYPE>::set(TYPE l, TYPE t, TYPE r, TYPE b)
{
    n_assert(l <= r);
    n_assert(t <= b);
    this->left = l;
    this->top = t;
    this->right = r;
    this->bottom = b;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> bool
rectangle<TYPE>::inside(TYPE x, TYPE y) const
{
    return (this->left <= x) && (x <= this->right) && (this->top <= y) && (y <= this->bottom);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> TYPE
rectangle<TYPE>::width() const
{
    return this->right - this->left;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> TYPE
rectangle<TYPE>::height() const
{
    return this->bottom - this->top;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> TYPE
rectangle<TYPE>::centerX() const
{
    return (this->left + this->right) / 2;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> TYPE
rectangle<TYPE>::centerY() const
{
    return (this->top + this->bottom) / 2;
}
} // namespace Math
//------------------------------------------------------------------------------
#endif



