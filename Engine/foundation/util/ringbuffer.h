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
template <class TYPE> class RingBuffer
{
public:
    /// default constructor
    RingBuffer();
    /// constructor with size
    RingBuffer(SizeT capacity);
    /// copy constructor
    RingBuffer(const RingBuffer<TYPE>& rhs);
    /// destructor
    ~RingBuffer();
    /// assignment operator
    void operator=(const RingBuffer<TYPE>& rhs);
    /// index operator
    TYPE& operator[](IndexT index) const;
    
    /// set capacity (clear previous content)
    void SetCapacity(SizeT newCapacity);
    /// get capacity
    SizeT Capacity() const;
    /// get number of elements in ring buffer
    SizeT Size() const;
    /// add an element to the ring buffer
    void Add(const TYPE& elm);
    /// return true if ring buffer is empty
    bool IsEmpty() const;
    /// reset ring buffer, just reset the head/base indices without calling destructors
    void Reset();
    /// return reference to first element
    TYPE& Front() const;
    /// return reference to last element
    TYPE& Back() const;
    /// return all values as array
    Array<TYPE> AsArray() const;    
    /// get real linear underlying buffer
    TYPE* GetBuffer();
    /// get real linear underlying buffer
    const TYPE* GetBuffer() const;

private:
    /// allocate element buffer
    void Allocate(SizeT capacity);
    /// delete content
    void Delete();
    /// copy content
    void Copy(const RingBuffer<TYPE>& src);

    SizeT capacity;
    SizeT size;
    IndexT baseIndex;
    IndexT headIndex;
    TYPE* elements;
};

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
RingBuffer<TYPE>::Allocate(SizeT c)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(0 == this->elements);
    n_assert(c > 0);
    #endif
    this->capacity = c;
    this->size = 0;
    this->baseIndex = 0;
    this->headIndex = 0;
    this->elements = n_new_array(TYPE, c);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
RingBuffer<TYPE>::Delete()
{
    this->capacity = 0;
    this->size = 0;
    this->baseIndex = 0;
    this->headIndex = 0;
    if (0 != this->elements)
    {
        n_delete_array(this->elements);
        this->elements = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
RingBuffer<TYPE>::Copy(const RingBuffer<TYPE>& rhs)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(0 == this->elements);
    #endif
    this->Allocate(rhs.capacity);
    this->size = rhs.size;
    this->baseIndex = rhs.baseIndex;
    this->headIndex = rhs.headIndex;
    IndexT i;
    for (i = 0; i < rhs.Size(); i++)
    {
        (*this)[i] = rhs[i];
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
RingBuffer<TYPE>::RingBuffer() :
    capacity(0),
    size(0),
    baseIndex(0),
    headIndex(0),
    elements(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
RingBuffer<TYPE>::RingBuffer(SizeT c) :
    elements(0)
{
    this->Allocate(c);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
RingBuffer<TYPE>::RingBuffer(const RingBuffer<TYPE>& rhs) :
    elements(0)
{
    this->Copy(rhs);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
RingBuffer<TYPE>::~RingBuffer()
{
    this->Delete();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
RingBuffer<TYPE>::operator=(const RingBuffer<TYPE>& rhs)
{
    this->Delete();
    this->Copy(rhs);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> TYPE&
RingBuffer<TYPE>::operator[](IndexT index) const
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(this->elements && (index < this->size));
    #endif
    IndexT absIndex = index + this->baseIndex;
    if (absIndex >= this->capacity)
    {
        // wrap-around
        absIndex -= this->capacity;
    }
    return this->elements[absIndex];
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> TYPE&
RingBuffer<TYPE>::Front() const
{
    return (*this)[0];
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> TYPE&
RingBuffer<TYPE>::Back() const
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(this->size > 0);
    #endif
    return (*this)[this->size - 1];
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> bool
RingBuffer<TYPE>::IsEmpty() const
{
    return (0 == this->size);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
RingBuffer<TYPE>::Reset()
{
    this->size = 0;
    this->baseIndex = 0;
    this->headIndex = 0;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
RingBuffer<TYPE>::SetCapacity(SizeT newCapacity)
{
    this->Delete();
    this->Allocate(newCapacity);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> SizeT
RingBuffer<TYPE>::Capacity() const
{
    return this->capacity;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> SizeT
RingBuffer<TYPE>::Size() const
{
    return this->size;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
RingBuffer<TYPE>::Add(const TYPE& elm)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(0 != this->elements);
    #endif

    // write new element
    this->elements[this->headIndex++] = elm;

    // check if head index should wrap around
    if (this->headIndex >= this->capacity)
    {
        this->headIndex = 0;
    }

    // if we are full, we need to advance the base index
    if (this->size == this->capacity)
    {
        this->baseIndex++;
        if (this->baseIndex >= this->capacity)
        {
            // wraparound base index
            this->baseIndex = 0;
        }
    }
    else
    {
        // not full yet, increment size member
        this->size++;
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> Array<TYPE>
RingBuffer<TYPE>::AsArray() const
{
    Array<TYPE> result(this->size, 0);
    IndexT i;
    for (i = 0; i < this->size; i++)
    {
        result.Append((*this)[i]);
    }
    return result;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE* 
RingBuffer<TYPE>::GetBuffer()
{
    n_assert(this->elements);
    return this->elements;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
const TYPE* 
RingBuffer<TYPE>::GetBuffer() const
{
    n_assert(this->elements);
    return this->elements;
}

} // namespace Util
//------------------------------------------------------------------------------
