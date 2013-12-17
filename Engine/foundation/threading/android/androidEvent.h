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
#ifndef __ANDROIDEVENT_H__
#define __ANDROIDEVENT_H__
#include "linuxevent.h"

//------------------------------------------------------------------------------
namespace Android
{

class AndroidEvent
{
public:
    /// constructor
    AndroidEvent(bool manualReset = false);
    /// destructor
    ~AndroidEvent();
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
AndroidEvent::AndroidEvent(bool manualReset)
{
	this->event = Linux_CreateEvent(NULL, manualReset, false, NULL);
	n_assert(0 != this->event);
}

//------------------------------------------------------------------------------
/**
*/
inline
AndroidEvent::~AndroidEvent()
{
	Linux_CloseHandle(this->event);
	this->event = 0;
}

//------------------------------------------------------------------------------
/**
*/
inline void
AndroidEvent::Signal()
{
   Linux_SetEvent(this->event);
}

//------------------------------------------------------------------------------
/**
*/
inline void
AndroidEvent::Reset()
{
   Linux_ResetEvent(this->event);
}

//------------------------------------------------------------------------------
/**
*/
inline void
AndroidEvent::Wait() const
{
	Linux_WaitForSingleObject(this->event, INFINITE);
}

//------------------------------------------------------------------------------
/**
    Waits for the event to become signaled with a specified timeout
    in milli seconds. If the method times out it will return false,
    if the event becomes signalled within the timeout it will return 
    true.
*/
inline bool
AndroidEvent::WaitTimeout(int timeoutInMilliSec) const
{
   int res = Linux_WaitForSingleObject(this->event, timeoutInMilliSec);
   return (WAIT_TIMEOUT == res) ? false : true;
}

//------------------------------------------------------------------------------
/**
    This checks if the event is signalled and returnes immediately.
*/
inline bool
AndroidEvent::Peek() const
{
	int res = Linux_WaitForSingleObject(this->event, 0);
	return (WAIT_TIMEOUT == res) ? false : true;
}


} // namespace Win360

#endif
//------------------------------------------------------------------------------

