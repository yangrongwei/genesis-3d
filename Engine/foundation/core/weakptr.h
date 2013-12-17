/****************************************************************************
Copyright (c) 2008, Radon Labs GmbH
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
    @class WeakPtr
    
    A smart pointer which does not change the reference count of the
    target object. Use this to prevent cyclic dependencies between
    objects. NOTE: The weak ptr only has a subset of methods of GPtr<>.
*/
#include "core/ptr.h"

//------------------------------------------------------------------------------
template<class TYPE>
class WeakPtr
{
public:
    /// constructor
    WeakPtr();
    /// construct from C++ pointer
    WeakPtr(TYPE* p);
    /// construct from GPtr<> pointer
    WeakPtr(const GPtr<TYPE>& p);
    /// construct from WeakPtr<> pointer
    WeakPtr(const WeakPtr<TYPE>& p);
    /// destructor
    ~WeakPtr();
    /// assignment operator from GPtr<>
    void operator=(const GPtr<TYPE>& rhs);
    /// assignment operator from WeakPtr<>
    void operator=(const WeakPtr<TYPE>& rhs);
    /// assignment operator
    void operator=(TYPE* rhs);
    /// safe -> operator
    TYPE* operator->() const;
    /// safe dereference operator
    TYPE& operator*() const;
    /// safe pointer cast operator
    operator TYPE*() const;
    /// check if pointer is valid
    bool isvalid() const;
    /// return direct pointer (asserts if null pointer)
    TYPE* get() const;
    /// return direct pointer (returns null pointer)
    TYPE* get_unsafe() const;

private:
    TYPE* ptr;
};

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
WeakPtr<TYPE>::WeakPtr() : 
    ptr(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
WeakPtr<TYPE>::WeakPtr(TYPE* p) : 
    ptr(p)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
WeakPtr<TYPE>::WeakPtr(const GPtr<TYPE>& p) : 
    ptr(p.get_unsafe())
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
WeakPtr<TYPE>::WeakPtr(const WeakPtr<TYPE>& p) : 
    ptr(p.ptr)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
WeakPtr<TYPE>::~WeakPtr()
{
    this->ptr = 0;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
WeakPtr<TYPE>::operator=(const GPtr<TYPE>& rhs)
{
    this->ptr = rhs.get_unsafe();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
WeakPtr<TYPE>::operator=(const WeakPtr<TYPE>& rhs)
{
    this->ptr = rhs.ptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
WeakPtr<TYPE>::operator=(TYPE* rhs)
{
    this->ptr = rhs;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE*
WeakPtr<TYPE>::operator->() const
{
    n_assert2(this->ptr, "NULL pointer access in WeakPtr::operator->()!");
    return this->ptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE&
WeakPtr<TYPE>::operator*() const
{
    n_assert2(this->ptr, "NULL pointer access in WeakPtr::operator*()!");
    return *this->ptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
WeakPtr<TYPE>::operator TYPE*() const
{
    n_assert2(this->ptr, "NULL pointer access in WeakPtr::operator TYPE*()!");
    return this->ptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool 
WeakPtr<TYPE>::isvalid() const
{
    return (0 != this->ptr);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE*
WeakPtr<TYPE>::get() const
{
    n_assert2(this->ptr, "NULL pointer access in WeakPtr::get()!");
    return this->ptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE*
WeakPtr<TYPE>::get_unsafe() const
{
    return this->ptr;
}
//------------------------------------------------------------------------------
