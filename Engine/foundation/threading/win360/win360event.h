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
class Win360Event
{
public:
    /// constructor
    Win360Event(bool manualReset=false);
    /// destructor
    ~Win360Event();
    /// signal the event
    void Signal();
    /// reset the event (only if manual reset)
    void Reset();
    /// wait for the event to become signalled
    void Wait() const;
    /// wait for the event with timeout in millisecs
    bool WaitTimeout(int ms) const;
    /// check if event is signalled
    bool Peek() const;
private:
    HANDLE event;
};

//------------------------------------------------------------------------------
/**
*/
inline
Win360Event::Win360Event(bool manualReset)
{
    this->event = CreateEvent(NULL, manualReset, FALSE, NULL);
    n_assert(0 != this->event);
}

//------------------------------------------------------------------------------
/**
*/
inline
Win360Event::~Win360Event()
{
    CloseHandle(this->event);
    this->event = 0;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Win360Event::Signal()
{
    SetEvent(this->event);
}

//------------------------------------------------------------------------------
/**
*/
inline void
Win360Event::Reset()
{
    ResetEvent(this->event);
}

//------------------------------------------------------------------------------
/**
*/
inline void
Win360Event::Wait() const
{
    WaitForSingleObject(this->event, INFINITE);
}

//------------------------------------------------------------------------------
/**
    Waits for the event to become signaled with a specified timeout
    in milli seconds. If the method times out it will return false,
    if the event becomes signalled within the timeout it will return 
    true.
*/
inline bool
Win360Event::WaitTimeout(int timeoutInMilliSec) const
{
    DWORD res = WaitForSingleObject(this->event, timeoutInMilliSec);
    return (WAIT_TIMEOUT == res) ? false : true;
}

//------------------------------------------------------------------------------
/**
    This checks if the event is signalled and returnes immediately.
*/
inline bool
Win360Event::Peek() const
{
    DWORD res = WaitForSingleObject(this->event, 0);
    return (WAIT_TIMEOUT == res) ? false : true;
}

} // namespace Win360
//------------------------------------------------------------------------------

