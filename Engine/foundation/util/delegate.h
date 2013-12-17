#pragma once
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

#include "core/types.h"

//------------------------------------------------------------------------------
namespace Util
{
template<class ARGTYPE> class Delegate
{
public:
    /// constructor
    Delegate();
    /// invokation operator
    void operator()(ARGTYPE arg) const;
    /// setup a new delegate from a method call
    template<class CLASS, void (CLASS::*METHOD)(ARGTYPE)> static Delegate<ARGTYPE> FromMethod(CLASS* objPtr);
    /// setup a new delegate from a function call
    template<void(*FUNCTION)(ARGTYPE)> static Delegate<ARGTYPE> FromFunction();

private:
    /// method pointer typedef
    typedef void (*StubType)(void*, ARGTYPE);
    /// static method-call stub 
    template<class CLASS, void(CLASS::*METHOD)(ARGTYPE)> static void MethodStub(void* objPtr, ARGTYPE arg);
    /// static function-call stub
    template<void(*FUNCTION)(ARGTYPE)> static void FunctionStub(void* dummyPtr, ARGTYPE arg);

    void* objPtr;
    StubType stubPtr;
};

//------------------------------------------------------------------------------
/**
*/
template<class ARGTYPE>
Delegate<ARGTYPE>::Delegate() :
    objPtr(0),
    stubPtr(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class ARGTYPE> void
Delegate<ARGTYPE>::operator()(ARGTYPE arg) const
{
    (*this->stubPtr)(this->objPtr, arg);
}

//------------------------------------------------------------------------------
/**
*/
template<class ARGTYPE>
template<class CLASS, void (CLASS::*METHOD)(ARGTYPE)>
Delegate<ARGTYPE>
Delegate<ARGTYPE>::FromMethod(CLASS* objPtr_)
{
    Delegate<ARGTYPE> del;
    del.objPtr = objPtr_;
    del.stubPtr = &MethodStub<CLASS,METHOD>;
    return del;
}

//------------------------------------------------------------------------------
/**
*/
template<class ARGTYPE>
template<void(*FUNCTION)(ARGTYPE)>
Delegate<ARGTYPE>
Delegate<ARGTYPE>::FromFunction()
{
    Delegate<ARGTYPE> del;
    del.objPtr = 0;
    del.stubPtr = &FunctionStub<FUNCTION>;
    return del;
}

//------------------------------------------------------------------------------
/**
*/
template<class ARGTYPE>
template<class CLASS, void (CLASS::*METHOD)(ARGTYPE)>
void
Delegate<ARGTYPE>::MethodStub(void* objPtr_, ARGTYPE arg_)
{
    CLASS* obj = static_cast<CLASS*>(objPtr_);
    (obj->*METHOD)(arg_);
}

//------------------------------------------------------------------------------
/**
*/
template<class ARGTYPE>
template<void(*FUNCTION)(ARGTYPE)>
void
Delegate<ARGTYPE>::FunctionStub(void* dummyPtr, ARGTYPE arg_)
{
    (*FUNCTION)(arg_);
}

} // namespace Util
//------------------------------------------------------------------------------
