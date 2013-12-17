/****************************************************************************
Copyright (c) 2010, Radon Labs GmbH
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

//------------------------------------------------------------------------------
namespace OSX
{
class OSXCriticalSection
{
public:
    /// constructor
    OSXCriticalSection();
    /// destructor
    ~OSXCriticalSection();
    /// enter the critical section
    void Enter() const;
    /// leave the critical section
    void Leave() const;
private:
    mutable pthread_mutex_t mutex;
};

//------------------------------------------------------------------------------
/**
*/
inline
OSXCriticalSection::OSXCriticalSection()
{
    pthread_mutexattr_t mutexAttrs;
    pthread_mutexattr_init(&mutexAttrs);
    pthread_mutexattr_settype(&mutexAttrs, PTHREAD_MUTEX_RECURSIVE);    // allow nesting
    int res = pthread_mutex_init(&this->mutex, &mutexAttrs);
    n_assert(0 == res);
    pthread_mutexattr_destroy(&mutexAttrs);
}

//------------------------------------------------------------------------------
/**
*/
inline 
OSXCriticalSection::~OSXCriticalSection()
{
    int res = pthread_mutex_destroy(&this->mutex);
    n_assert(0 == res);
}

//------------------------------------------------------------------------------
/**
*/
inline void
OSXCriticalSection::Enter() const
{
    pthread_mutex_lock(&this->mutex);
}
    
//------------------------------------------------------------------------------
/**
*/
inline void
OSXCriticalSection::Leave() const
{
    pthread_mutex_unlock(&this->mutex);
}

} // namespace OSX