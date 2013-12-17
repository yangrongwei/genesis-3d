#pragma once
/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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
template<unsigned int NUMBITS> class BitField
{
public:
    /// constructor
    BitField();
    /// copy constructor
    BitField(const BitField<NUMBITS>& rhs);
    
    /// assignment operator
    void operator=(const BitField<NUMBITS>& rhs);
    /// equality operator
    bool operator==(const BitField<NUMBITS>& rhs) const;
    /// inequality operator
    bool operator!=(const BitField<NUMBITS>& rhs) const;
    
    /// clear content
    void Clear();
    /// return true if all bits are 0
    bool IsNull() const;
    /// set a bit by index
    void SetBit(IndexT bitIndex);
    /// clear a bit by index
    void ClearBit(IndexT bitIndex);
    
    /// set bitfield to OR combination
    static BitField<NUMBITS> Or(const BitField<NUMBITS>& b0, const BitField<NUMBITS>& b1);
    /// set bitfield to AND combination
    static BitField<NUMBITS> And(const BitField<NUMBITS>& b0, const BitField<NUMBITS>& b1);

private:
    static const int size = ((NUMBITS + 31) / 32);
    uint bits[size];
};

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS>
BitField<NUMBITS>::BitField()
{
    IndexT i;
    for (i = 0; i < size; i++)
    {
        this->bits[i] = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS>
BitField<NUMBITS>::BitField(const BitField<NUMBITS>& rhs)
{
    IndexT i;
    for (i = 0; i < size; i++)
    {
        this->bits[i] = rhs.bits[i];
    }
}

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS> void
BitField<NUMBITS>::operator=(const BitField<NUMBITS>& rhs)
{
    IndexT i;
    for (i = 0; i < size; i++)
    {
        this->bits[i] = rhs.bits[i];
    }
}

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS> bool
BitField<NUMBITS>::operator==(const BitField<NUMBITS>& rhs) const
{
    IndexT i;
    for (i = 0; i < size; i++)
    {
        if (this->bits[i] != rhs.bits[i])
        {
            return false;
        }
    }
    return true;
}

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS> bool
BitField<NUMBITS>::operator!=(const BitField<NUMBITS>& rhs) const
{
    return !(*this == rhs);
}

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS> void
BitField<NUMBITS>::Clear()
{
    IndexT i;
    for (i = 0; i < size; i++)
    {
        this->bits[i] = 0;
    }
}

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS> bool
BitField<NUMBITS>::IsNull() const
{
    IndexT i;
    for (i = 0; i < size; i++)
    {
        if (this->bits[i] != 0)
        {
            return false;
        }
    }
    return true;
}

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS> void
BitField<NUMBITS>::SetBit(IndexT i)
{
    n_assert(i < NUMBITS);
    this->bits[i / 32] |= (1 << (i % 32));
}

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS> void
BitField<NUMBITS>::ClearBit(IndexT i)
{
    n_assert(i < NUMBITS);
    this->bits[i / 32] &= ~(1 << (i % 32));
}

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS> BitField<NUMBITS>
BitField<NUMBITS>::Or(const BitField<NUMBITS>& b0, const BitField<NUMBITS>& b1)
{
    BitField<NUMBITS> res;
    IndexT i;
    for (i = 0; i < size; i++)
    {
        res.bits[i] = b0.bits[i] | b1.bits[i];
    }
    return res;
}

//------------------------------------------------------------------------------
/**
*/
template<unsigned int NUMBITS> BitField<NUMBITS>
BitField<NUMBITS>::And(const BitField<NUMBITS>& b0, const BitField<NUMBITS>& b1)
{
    BitField<NUMBITS> res;
    IndexT i;
    for (i = 0; i < size; i++)
    {
        res.bits[i] = b0.bits[i] & b1.bits[i];
    }
    return res;
}

} // namespace Util
//------------------------------------------------------------------------------

    