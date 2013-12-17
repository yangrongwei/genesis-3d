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

//------------------------------------------------------------------------------
namespace Util
{
template<class TYPE> class FixedTable
{
public:
    /// default constructor
    FixedTable();
    /// constructor with size
    FixedTable(SizeT w, SizeT h);
    /// constructor with size and initialized contents
    FixedTable(SizeT w, SizeT h, const TYPE& val);
    /// copy constructor
    FixedTable(const FixedTable<TYPE>& rhs);
    /// destructor
    ~FixedTable();
    /// assignment operator
    void operator=(const FixedTable<TYPE>& rhs);
    /// equality operator
    bool operator==(const FixedTable<TYPE>& rhs) const;
    /// inequality operator
    bool operator!=(const FixedTable<TYPE>& rhs) const;
    
    /// set width and height (clears existing content)
    void SetSize(SizeT w, SizeT h);
    /// get width
    SizeT Width() const;
    /// get height
    SizeT Height() const;
    /// clear the table with value
    void Clear(const TYPE& val);

    /// set value at [x,y] position
    void Set(IndexT x, IndexT y, const TYPE& val);
    /// access value at [x,y] position
    TYPE& At(IndexT x, IndexT y) const;

private:
    /// delete content
    void Delete();
    /// allocate for given size
    void Allocate(SizeT w, SizeT h);
    /// copy content
    void Copy(const FixedTable<TYPE>& src);

    SizeT width;
    SizeT height;
    TYPE* elements;
};

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
FixedTable<TYPE>::FixedTable() :
    width(0),
    height(0),
    elements(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
FixedTable<TYPE>::Delete()
{
    if (this->elements)
    {
        n_delete_array(this->elements);
        this->elements = 0;
    }
    this->width = 0;
    this->height = 0;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
FixedTable<TYPE>::Allocate(SizeT w, SizeT h)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert(0 == this->elements);
    #endif
    if ((w > 0) && (h > 0))
    {
        this->elements = n_new_array(TYPE, w * h);
    }
    this->width = w;
    this->height = h;
}

//------------------------------------------------------------------------------
/**
    NOTE: only works on deleted table. This is intended.
*/
template<class TYPE>
void
FixedTable<TYPE>::Copy(const FixedTable<TYPE>& rhs)
{
    if (this != &rhs)
    {
        this->Allocate(rhs.width, rhs.height);
        IndexT y;
        for (y = 0; y < this->height; y++)
        {
            IndexT x;
            for (x = 0; x < this->width; x++)
            {
                int flatIndex = y * this->width + x;
                this->elements[flatIndex] = rhs.elements[flatIndex];
            }
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
FixedTable<TYPE>::Clear(const TYPE& val)
{
    IndexT y;
    for (y = 0; y < this->height; y++)
    {
        IndexT x;
        for (x = 0; x < this->width; x++)
        {
            int flatIndex = y * this->width + x;
            this->elements[flatIndex] = val;
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
FixedTable<TYPE>::FixedTable(SizeT w, SizeT h) :
    width(0),
    height(0),
    elements(0)
{
    this->Allocate(w, h);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
FixedTable<TYPE>::FixedTable(SizeT w, SizeT h, const TYPE& val) :
    width(0),
    height(0),
    elements(0)
{
    this->Allocate(w, h);
    this->Clear(val);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
FixedTable<TYPE>::FixedTable(const FixedTable<TYPE>& rhs) :
    width(0),
    height(0),
    elements(0)
{
    this->Copy(rhs);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
FixedTable<TYPE>::~FixedTable()
{
    this->Delete();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
FixedTable<TYPE>::operator=(const FixedTable<TYPE>& rhs)
{
    this->Delete();
    this->Copy(rhs);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
FixedTable<TYPE>::operator==(const FixedTable<TYPE>& rhs) const
{
    if ((this->width == rhs.width) && (this->height == rhs.height))
    {
        // check elements
        IndexT y;
        for (y = 0; y < this->height; y++)
        {
            IndexT x;
            for (x = 0; x < this->width; x++)
            {
                int flatIndex = y * this->width + x;
                if (this->elements[flatIndex] != rhs.elements[flatIndex])
                {
                    return false;
                }
            }
        }
        return true;
    }
    else
    {
        // different size
        return false;
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
FixedTable<TYPE>::operator!=(const FixedTable<TYPE>& rhs) const
{
    return !(*this == rhs);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
FixedTable<TYPE>::SetSize(SizeT w, SizeT h)
{
    this->Delete();
    this->Allocate(w, h);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
SizeT
FixedTable<TYPE>::Width() const
{
    return this->width;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
SizeT
FixedTable<TYPE>::Height() const
{
    return this->height;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
FixedTable<TYPE>::Set(IndexT x, IndexT y, const TYPE& val)
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert((x >= 0) && (x < this->width));
    n_assert(y < this->height);
    n_assert(0 != this->elements);    
    #endif
    int flatIndex = y * this->width + x;
    this->elements[flatIndex] = val;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE&
FixedTable<TYPE>::At(IndexT x, IndexT y) const
{
    #if NEBULA3_BOUNDSCHECKS
    n_assert((x >= 0) && (x < this->width));
    n_assert(y < this->height);
    n_assert(0 != this->elements);
    #endif
    int flatIndex = y * this->width + x;
    return this->elements[flatIndex];
}

} // namespace Util
//------------------------------------------------------------------------------
