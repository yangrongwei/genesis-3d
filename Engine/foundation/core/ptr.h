/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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
    @class Ptr

    Nebula3's smart pointer class which manages the life time of RefCounted
    objects. Can be used like a normal C++ pointer in most cases.

    NOTE: the Ptr class is not part of the Core namespace for
    convenience reasons.
*/
#include "core/types.h"

// platform secific stuff for handling/suppress "unused-argument"-warnings
#if NEBULA3_DEBUG
#if (__XBOX360__ || __WIN32__)
#pragma warning( push )
// warnung unused param
#pragma warning(disable: 4189)
#endif
#if __PS3__
#define NEBULA3_UNUSED_ATTR __attribute__ ((unused))
#else
#define NEBULA3_UNUSED_ATTR
#endif
#endif // NEBULA3_DEBUG

//------------------------------------------------------------------------------
template<class TYPE>
class GPtr
{
public:
    /// constructor
    GPtr();
    /// construct from C++ pointer
    GPtr(TYPE* p);
    /// construct from smart pointer
    GPtr(const GPtr<TYPE>& p);
    /// destructor
    ~GPtr();
    /// assignment operator
    void operator=(const GPtr<TYPE>& rhs);
    /// assignment operator
    void operator=(TYPE* rhs);
    /// equality operator
    bool operator==(const GPtr<TYPE>& rhs) const;
    /// inequality operator
    bool operator!=(const GPtr<TYPE>& rhs) const;
    /// shortcut equality operator
    bool operator==(const TYPE* rhs) const;
    /// shortcut inequality operator
    bool operator!=(const TYPE* rhs) const;
	/// shortcut less operator
	bool operator<(const GPtr<TYPE>& rhs) const;
	/// shortcut greator operator
	bool operator>(const GPtr<TYPE>& rhs) const;
    /// safe -> operator
    TYPE* operator->() const;
    /// safe dereference operator
    TYPE& operator*() const;
    /// safe pointer cast operator
    operator TYPE*() const;
	/// safe type to bool
	operator bool() const;
    /// type-safe downcast operator to other smart pointer
    template<class DERIVED> const GPtr<DERIVED>& downcast() const;
    /// type-safe upcast operator to other smart pointer
    template<class BASE> const GPtr<BASE>& upcast() const;
    /// unsafe(!) cast to anything, unless classes have no inheritance-relationship,
    /// call upcast/downcast instead, they are type-safe
    template<class OTHERTYPE> const GPtr<OTHERTYPE>& cast() const;
    /// check if pointer is valid
    bool isvalid() const;
    /// return direct pointer (asserts if null pointer)
    TYPE* get() const;
    /// return direct pointer (returns null pointer)
    TYPE* get_unsafe() const;

	void swap(GPtr<TYPE>& other);

private:
    TYPE* ptr;
};

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
GPtr<TYPE>::GPtr() :
    ptr(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
GPtr<TYPE>::GPtr(TYPE* p) :
    ptr(p)
{
    if (0 != this->ptr)
    {
        this->ptr->AddRef();
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
GPtr<TYPE>::GPtr(const GPtr<TYPE>& p) :
    ptr(p.ptr)
{
    if (0 != this->ptr)
    {
        this->ptr->AddRef();
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
GPtr<TYPE>::~GPtr()
{
    if (0 != this->ptr)
    {
        this->ptr->Release();
        this->ptr = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
GPtr<TYPE>::operator=(const GPtr<TYPE>& rhs)
{
    if (this->ptr != rhs.ptr)
    {
        if (this->ptr)
        {
            this->ptr->Release();
        }
        this->ptr = rhs.ptr;
        if (this->ptr)
        {
            this->ptr->AddRef();
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
GPtr<TYPE>::operator=(TYPE* rhs)
{
    if (this->ptr != rhs)
    {
        if (this->ptr)
        {
            this->ptr->Release();
        }
        this->ptr = rhs;
        if (this->ptr)
        {
            this->ptr->AddRef();
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
GPtr<TYPE>::operator==(const GPtr<TYPE>& rhs) const
{
    return (this->ptr == rhs.ptr);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
GPtr<TYPE>::operator!=(const GPtr<TYPE>& rhs) const
{
    return (this->ptr != rhs.ptr);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
GPtr<TYPE>::operator==(const TYPE* rhs) const
{
    return (this->ptr == rhs);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
GPtr<TYPE>::operator!=(const TYPE* rhs) const
{
    return (this->ptr != rhs);
}
//------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool 
GPtr<TYPE>::operator<(const GPtr<TYPE>& rhs) const
{
	return (this->ptr < rhs.ptr);
}
//------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool 
GPtr<TYPE>::operator>(const GPtr<TYPE>& rhs) const
{
	return (this->ptr > rhs.ptr);
}
//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE*
GPtr<TYPE>::operator->() const
{
    n_assert2(this->ptr, "NULL pointer access in Ptr::operator->()!");
    return this->ptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE&
GPtr<TYPE>::operator*() const
{
    n_assert2(this->ptr, "NULL pointer access in Ptr::operator*()!");
    return *this->ptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
GPtr<TYPE>::operator TYPE*() const
{
    n_assert2(this->ptr, "NULL pointer access in Ptr::operator TYPE*()!");
    return this->ptr;
}
//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
GPtr<TYPE>::operator bool() const
{
	return (0 != this->ptr);
}
//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
template<class DERIVED> const GPtr<DERIVED>&
GPtr<TYPE>::downcast() const
{
#if (NEBULA3_DEBUG == 1)
	// debug 的情况下，加上检查。编译器只会在编译器判断derived是从base继承的。但并不会在运行期判断实际的指针
	// 加上Assert。Release版本暂时不进行处理
	n_assert( this->ptr->GetRtti()->IsDerivedFrom(DERIVED::RTTI) );

    // if DERIVED is not a derived class of TYPE, compiler complains here
    // compile-time inheritance-test
    NEBULA3_UNUSED_ATTR const DERIVED *derived = static_cast<const DERIVED*>(this->ptr);
#endif
    return *reinterpret_cast<const GPtr<DERIVED>*>(this);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
template<class BASE> const GPtr<BASE>&
GPtr<TYPE>::upcast() const
{
#if (NEBULA3_DEBUG == 1)
    // if BASE is not a base-class of TYPE, compiler complains here
    // compile-time inheritance-test
    NEBULA3_UNUSED_ATTR const BASE *base = this->ptr;
#endif
    return *reinterpret_cast<const GPtr<BASE>*>(this);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
template<class OTHERTYPE> const GPtr<OTHERTYPE>&
GPtr<TYPE>::cast() const
{
    // note: this is an unsafe cast
    return *reinterpret_cast<const GPtr<OTHERTYPE>*>(this);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
GPtr<TYPE>::isvalid() const
{
    return (0 != this->ptr);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE*
GPtr<TYPE>::get() const
{
    n_assert2(this->ptr, "NULL pointer access in Ptr::get()!");
    return this->ptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE*
GPtr<TYPE>::get_unsafe() const
{
    return this->ptr;
}
//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
GPtr<TYPE>::swap(GPtr<TYPE>& other) 
{
	TYPE* temp = other.ptr;
	other.ptr = this->ptr;
	this->ptr = temp;
}

//------------------------------------------------------------------------------

#if (__XBOX360__ || __WIN32__) && NEBULA3_DEBUG
#pragma warning( pop )
#endif
#ifdef NEBULA3_UNUSED_ATTR
#undef NEBULA3_UNUSED_ATTR
#endif
