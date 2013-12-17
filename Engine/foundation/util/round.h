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
class Round
{
public:
    /// round up to nearest 2 bytes boundary
    static uint RoundUp2(uint val);
    /// round up to nearest 4 bytes boundary
    static uint RoundUp4(uint val);
    /// round up to nearest 8 bytes boundary
    static uint RoundUp8(uint val);
    /// round up to nearest 16 bytes boundary
    static uint RoundUp16(uint val);
    /// round up to nearest 32 bytes boundary
    static uint RoundUp32(uint val);    
    /// generic roundup
    static uint RoundUp(uint val, uint boundary);
};

//------------------------------------------------------------------------------
/**
*/
__forceinline uint
Round::RoundUp2(uint val)
{
    return ((uint)val + (2 - 1)) & ~(2 - 1);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline uint
Round::RoundUp4(uint val)
{
    return ((uint)val + (4 - 1)) & ~(4 - 1);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline uint
Round::RoundUp8(uint val)
{
    return ((uint)val + (8 - 1)) & ~(8 - 1);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline uint
Round::RoundUp16(uint val)
{
    return ((uint)val + (16 - 1)) & ~(16 - 1);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline uint
Round::RoundUp32(uint val)
{
    return ((uint)val + (32 - 1)) & ~(32 - 1);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline uint
Round::RoundUp(uint val, uint boundary)
{
    n_assert(0 != boundary);
    return (((val - 1) / boundary) + 1) * boundary;
}

} // namespace Util
//------------------------------------------------------------------------------
