#pragma once
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

#include "core/types.h"
#include "threading/criticalsection.h"

//------------------------------------------------------------------------------
namespace Android
{
class AndroidThreadBarrier
{
public:
    /// constructor
    AndroidThreadBarrier();
    /// destructor
    ~AndroidThreadBarrier();
    /// setup the object with the number of threads
    void Setup(SizeT numThreads);
    /// return true if the object has been setup
    bool IsValid() const;
    /// enter thread barrier, return false if not all threads have arrived yet
    bool Arrive();
    /// call after Arrive() returns false to wait for other threads
    void Wait();
    /// call after Arrive() returns true to resume all threads
    void SignalContinue();

private:
    Threading::CriticalSection critSect;
    long numThreads;
    volatile long outstandingThreads;
 
    bool isValid;
};

//------------------------------------------------------------------------------
/**
*/
inline
AndroidThreadBarrier::AndroidThreadBarrier() :
    numThreads(0),
    outstandingThreads(0),
    isValid(false)
{
    
}

//------------------------------------------------------------------------------
/**
*/
inline
AndroidThreadBarrier::~AndroidThreadBarrier()
{
    
}

//------------------------------------------------------------------------------
/**
*/
inline void
AndroidThreadBarrier::Setup(SizeT num)
{
    n_assert(!this->isValid);
    this->numThreads = num;
    this->outstandingThreads = num;
    this->isValid = true;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
AndroidThreadBarrier::IsValid() const
{
    return this->isValid;
}

//------------------------------------------------------------------------------
/**
    Notify arrival at thread-sync point, return false if not all threads
    have arrived yet, and true if all threads have arrived. If the
    method returns false, you should immediately call Wait(), if the
    method returns true, the caller has a chance to perform some actions
    which should happen before threads continue, and then call the
    SignalContinue() method.
*/
inline bool
AndroidThreadBarrier::Arrive()
{
    this->critSect.Enter();
    n_assert(this->outstandingThreads > 0);
    this->outstandingThreads--;
    return (0 == this->outstandingThreads);
}

//------------------------------------------------------------------------------
/**
    This method should be called when Arrive() returns false. It will
    put the thread to sleep because not all threads have arrived yet.
    When the method returns, all threads have arrived at the sync point.

    NOTE: sometimes both the render and the main thread arrive here
    with the outstandingThreads member set to 1 (from two) causing
    both thread to be waiting idefinitely.
*/
inline void
AndroidThreadBarrier::Wait()
{
    
}

//------------------------------------------------------------------------------
/**
    This method should be called after Arrive() returns true. This means
    that all threads have arrived at the sync point and execution of all
    threads may resume.
*/
inline void
AndroidThreadBarrier::SignalContinue()
{
    this->outstandingThreads = this->numThreads;
   
    this->critSect.Leave();
}

} // namespace Win360
//------------------------------------------------------------------------------
    