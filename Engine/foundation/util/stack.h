#pragma once
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

#include "core/types.h"
#include "util/array.h"

//------------------------------------------------------------------------------
namespace Util
{
template<class TYPE> class Stack
{
public:
    /// constructor
    Stack();
    /// copy constructor
    Stack(const Stack<TYPE>& rhs);
 
    /// assignment operator
    void operator=(const Stack<TYPE>& rhs);
    /// access element by index, 0 is the topmost element
    TYPE& operator[](IndexT index) const;
    /// equality operator
    bool operator==(const Stack<TYPE>& rhs) const;
    /// inequality operator
    bool operator!=(const Stack<TYPE>& rhs) const;
    /// returns number of elements on stack
    SizeT Size() const;
    /// returns true if stack is empty
    bool IsEmpty() const;
    /// remove all elements from the stack
    void Clear();
    /// return true if stack contains element
    bool Contains(const TYPE& e) const;

    /// push an element on the stack
    void Push(const TYPE& e);
    /// get reference of topmost element of stack, without removing it
    TYPE& Peek() const;
    /// get topmost element of stack, remove element
    TYPE Pop();

private:
    Array<TYPE> stackArray;
};

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
Stack<TYPE>::Stack()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
Stack<TYPE>::Stack(const Stack<TYPE>& rhs)
{
    this->stackArray = rhs.stackArray;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
Stack<TYPE>::operator=(const Stack<TYPE>& rhs)
{
    this->stackArray = rhs.stackArray;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE&
Stack<TYPE>::operator[](IndexT index) const
{
    return this->stackArray[this->stackArray.Size() - 1 - index];
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
Stack<TYPE>::operator==(const Stack<TYPE>& rhs) const
{
    return this->stackArray == rhs.stackArray;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
Stack<TYPE>::operator!=(const Stack<TYPE>& rhs) const
{
    return this->stackArray != rhs.stackArray;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
Stack<TYPE>::Contains(const TYPE& e) const
{
    return (InvalidIndex != this->stackArray.FindIndex(e));
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
Stack<TYPE>::Clear()
{
    this->stackArray.Clear();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
SizeT
Stack<TYPE>::Size() const
{
    return this->stackArray.Size();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
Stack<TYPE>::IsEmpty() const
{
    return this->stackArray.IsEmpty();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
Stack<TYPE>::Push(const TYPE& e)
{
    this->stackArray.Append(e);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE&
Stack<TYPE>::Peek() const
{
    return this->stackArray.Back();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE
Stack<TYPE>::Pop()
{
    TYPE e = this->stackArray.Back();
    this->stackArray.EraseIndex(this->stackArray.Size() - 1);
    return e;
}

} // namespace Util
//------------------------------------------------------------------------------
