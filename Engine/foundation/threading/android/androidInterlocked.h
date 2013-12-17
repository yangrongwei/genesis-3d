/****************************************************************************
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

#include "core/types.h"
#include <sys/atomics.h>

//------------------------------------------------------------------------------
namespace Android
{
class AndroidInterlocked
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
AndroidInterlocked::Increment(int volatile& var)
{
   __atomic_inc(&var);
   return var;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline int
AndroidInterlocked::Decrement(int volatile& var)
{
    __atomic_dec(&var);
	return var;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline int
AndroidInterlocked::Add(int volatile& var, int add)
{
    __sync_fetch_and_add(&var, add);
	return var;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline int
AndroidInterlocked::Exchange(int volatile* dest, int value)
{
    return __atomic_swap(value, dest);
}
//------------------------------------------------------------------------------
/**
*/
__forceinline int
AndroidInterlocked::CompareExchange(int volatile* dest, int exchange, int comparand)
{
     return __atomic_cmpxchg(comparand, exchange, dest);
}

} // namespace Win360
//------------------------------------------------------------------------------
