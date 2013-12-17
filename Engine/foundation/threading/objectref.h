#pragma once
/****************************************************************************
Copyright (c) 2010, Radon Labs GmbH
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

#include "core/refcounted.h"

//------------------------------------------------------------------------------
namespace Threading
{
class ObjectRef : public Core::RefCounted
{
    __DeclareClass(ObjectRef);
public:
    /// constructor
    ObjectRef();
    /// destructor
    virtual ~ObjectRef();
    
    /// return true if the ObjectRef points to a valid object
    bool IsValid() const;
    /// validate the ref with a pointer to a target object (must be RefCounted)
    template<class TYPE> void Validate(TYPE* obj);
    /// invalidate the ref
    void Invalidate();
    /// get pointer to object
    template<class TYPE> TYPE* Ref() const;

private:
    Core::RefCounted* volatile ref;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
ObjectRef::IsValid() const
{
    return (0 != this->ref);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> inline void
ObjectRef::Validate(TYPE* obj)
{
    n_assert(0 != obj);
    n_assert(obj->IsA(TYPE::RTTI));
    n_assert(0 == this->ref);
    obj->AddRef();
    Interlocked::Exchange((volatile int*)&this->ref, (int)obj);
}

//------------------------------------------------------------------------------
/**
*/
inline void
ObjectRef::Invalidate()
{
    n_assert(0 != this->ref);
    this->ref->Release();
    Interlocked::Exchange((volatile int*)&this->ref, 0);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> inline TYPE*
ObjectRef::Ref() const
{
    n_assert(0 != this->ref);
    n_assert(this->ref->IsA(TYPE::RTTI));
    return (TYPE*) this->ref;
}

} // namespace Threading
//------------------------------------------------------------------------------
    