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

#pragma once
#ifndef WIN360_WIN360TIMER_H
#define WIN360_WIN360TIMER_H
//------------------------------------------------------------------------------
/**
    @class Win360::Win360Timer
    
    Win32/Xbox360 implementation of the Time::Timer class. Uses 
    the QueryPerformanceCounter() functions.

    @todo solve multiprocessor issues of QueryPerformanceCounter()
    (different processors may return different PerformanceFrequency
    values, thus, threads should be prevented from switching between
    processors with thread affinities).
*/
#include "core/types.h"
#include "timing/time.h"

//------------------------------------------------------------------------------
namespace Win360
{
class Win360Timer
{
public:
    /// constructor
    Win360Timer();
    /// start/continue the timer
    void Start();
    /// stop the timer
    void Stop();
    /// reset the timer
    void Reset();
    /// return true if currently running
    bool Running() const;
    /// get current time in seconds
    Timing::Time GetTime() const;
    /// get current time in ticks
    Timing::Tick GetTicks() const;
	/// get the real time
	static Timing::MicrosecondTick GetusTicks();

private:
    /// return internal time as 64 bit integer
    __int64 InternalTime() const;

    bool running;
    __int64 diffTime;  // accumulated time when the timer was not running
    __int64 stopTime;  // when was the timer last stopped?

	void FindValidTimeMask();

	ulong timeMask;	//	用于设置线程的核
};

} // namespace Win360
//------------------------------------------------------------------------------
#endif
   