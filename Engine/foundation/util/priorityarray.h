#ifndef N_PRIORITYARRAY_H
#define N_PRIORITYARRAY_H
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

#include "core/types.h"

namespace Util
{

//------------------------------------------------------------------------------
template<class TYPE> class PriorityArray
{
public:
    /// constructor
    PriorityArray(int size);
    /// copy constructor
    PriorityArray(const PriorityArray<TYPE>& rhs);
    /// destructor
    ~PriorityArray();
    /// assignment operator
    PriorityArray<TYPE>& operator=(const PriorityArray<TYPE>& rhs);
    /// [] operator
    TYPE& operator[](int index) const;
    /// clear the array
    void Clear();
    /// add element to array
    void Add(const TYPE& elm, float pri);
    /// get number of elements in array
    int Size() const;
    /// return n'th array element
    TYPE& At(int index);
    /// return true if empty
    bool IsEmpty() const;

private:
    /// update the min pri element index
    void UpdateMinPriElementIndex();
    /// copy content
    void Copy(const PriorityArray<TYPE>& src);
    /// delete content
    void Delete();
    /// destroy an element (call destructor without freeing memory)
    void Destroy(TYPE* elm);

    /// an element class
    struct Element
    {
        TYPE element;
        float priority;
    };

    int numElements;
    int maxElements;
    int minPriElementIndex;
    Element* elements;
};

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
PriorityArray<TYPE>::PriorityArray(int size) :
    numElements(0),
    maxElements(size),
    minPriElementIndex(0)
{
    n_assert(size > 0);
    this->elements = n_new_array(Element, size);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
PriorityArray<TYPE>::Copy(const PriorityArray<TYPE>& src) :
    numElements(src.numElements),
    maxElements(src.maxElements),
    minPriElementIndex(src.minPriElementIndex)
{
    n_assert(0 == this->elements);
    this->elements = n_new_array(Element, this->maxElements);
    int i;
    for (i = 0; i < this->numElements; i++)
    {
        this->elements[i] = src.elements[i];
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
PriorityArray<TYPE>::Delete()
{
    this->numElements = 0;
    this->maxElements = 0;
    this->minPriElementIndex = 0;
    if (this->elements)
    {
        n_delete_array(this->elements);
        this->elements = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
PriorityArray<TYPE>::PriorityArray(const PriorityArray<TYPE>& rhs) :
    numElements(0),
    maxElements(0),
    minPriElementIndex(0),
    elements(0)
{
    this->Copy(rhs);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
PriorityArray<TYPE>::~PriorityArray()
{
    this->Delete();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
PriorityArray<TYPE>::Destroy(TYPE* elm)
{
    elm->~TYPE();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
PriorityArray<TYPE>::Clear()
{
    n_assert(this->elements);

    // call element destructors
    int i;
    for (i = 0; i < this->numElements; i++)
    {
        this->Destroy(&(this->elements[i].element));
    }
    this->numElements = 0;
    this->minPriElementIndex = 0;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
PriorityArray<TYPE>::UpdateMinPriElementIndex()
{
    int i;
    this->minPriElementIndex = 0;
    float minPri = this->elements[0].priority;
    for (i = 1; i < this->numElements; i++)
    {
        if (this->elements[i].priority < minPri)
        {
            minPri = this->elements[i].priority;
            this->minPriElementIndex = i;
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
PriorityArray<TYPE>::Add(const TYPE& elm, float pri)
{
    if (this->numElements < this->maxElements)
    {
        this->elements[this->numElements].element = elm;
        this->elements[this->numElements].priority = pri;
        this->numElements++;
        if (this->numElements == this->maxElements)
        {
            this->UpdateMinPriElementIndex();
        }
    }
    else
    {
        if (pri > this->elements[this->minPriElementIndex].priority)
        {
            this->elements[this->minPriElementIndex].element = elm;
            this->elements[this->minPriElementIndex].priority = pri;
            this->UpdateMinPriElementIndex();
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
int
PriorityArray<TYPE>::Size() const
{
    return this->numElements;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE&
PriorityArray<TYPE>::At(int index)
{
    n_assert((index >= 0) && (index < this->numElements));
    return this->elements[index].element;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE&
PriorityArray<TYPE>::operator[](int index) const
{
    n_assert((index >= 0) && (index < this->numElements));
    return this->elements[index].element;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
PriorityArray<TYPE>& 
PriorityArray<TYPE>::operator=(const PriorityArray<TYPE>& rhs)
{
    this->Delete();
    this->Copy(rhs);
    return *this;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
PriorityArray<TYPE>::IsEmpty() const
{
    return (0 == this->numElements);
}

} // namespace Util
//------------------------------------------------------------------------------
#endif

   
    