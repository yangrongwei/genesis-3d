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
   
#include "threading/interlocked.h"

//------------------------------------------------------------------------------
namespace Threading
{
class SafeFlag
{
public:
    /// constructor
    SafeFlag();
    /// set the flag
    void Set();
    /// clear the flag
    void Clear();
    /// test if the flag is set
    bool Test() const;
    /// test if flag is set, if yes, clear flag
    bool TestAndClearIfSet();

private:
    int volatile flag;
};

//------------------------------------------------------------------------------
/**
*/
inline
SafeFlag::SafeFlag() :
    flag(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline void
SafeFlag::Set()
{
    Interlocked::Exchange(&this->flag, 1);
}

//------------------------------------------------------------------------------
/**
*/
inline void
SafeFlag::Clear()
{
    Interlocked::Exchange(&this->flag, 0);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
SafeFlag::Test() const
{
    return (0 != this->flag);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
SafeFlag::TestAndClearIfSet()
{
    return (1 == Interlocked::CompareExchange(&this->flag, 0, 1));
}

} // namespace Threading
//------------------------------------------------------------------------------
