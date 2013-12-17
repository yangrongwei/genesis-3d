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
namespace Win360
{
class Win360Interlocked
{
public:
    /// interlocked increment, return result
    static int Increment(int volatile& var);
    /// interlocked decrement, return result
    static int Decrement(int volatile& var);
    /// interlocked add
    static int Add(int volatile& var, int add);
    /// interlocked exchange
    static int Exchange(int volatile* dest, int value);
    /// interlocked compare-exchange
    static int CompareExchange(int volatile* dest, int exchange, int comparand);
};

//------------------------------------------------------------------------------
/**
*/
__forceinline int
Win360Interlocked::Increment(int volatile& var)
{
    return _InterlockedIncrement((volatile LONG*)&var);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline int
Win360Interlocked::Decrement(int volatile& var)
{
    return _InterlockedDecrement((volatile LONG*)&var);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline int
Win360Interlocked::Add(int volatile& var, int add)
{
    return _InterlockedExchangeAdd((volatile LONG*)&var, add);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline int
Win360Interlocked::Exchange(int volatile* dest, int value)
{
    return _InterlockedExchange((volatile LONG*)dest, value);
}

//------------------------------------------------------------------------------
/**
*/
__forceinline int
Win360Interlocked::CompareExchange(int volatile* dest, int exchange, int comparand)
{
    return _InterlockedCompareExchange((volatile LONG*)dest, exchange, comparand);
}

} // namespace Win360
//------------------------------------------------------------------------------
