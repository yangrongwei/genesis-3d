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


#if WIN32


#include "stdneb.h"
#include "timing/win360/win360timer.h"

namespace Win360
{

//------------------------------------------------------------------------------
/**
*/
Win360Timer::Win360Timer() :
    running(false),
    diffTime(0),
    stopTime(0),
	timeMask(0)
{
	FindValidTimeMask();
}
//------------------------------------------------------------------------------
/**
    Start the timer. This will update the diffTime member to reflect
    the accumulated time when the timer was not running (basically the
    difference between this timer's time and the real system time).
*/
void
Win360Timer::Start()
{
    n_assert(!this->running);

	HANDLE thread = GetCurrentThread();
	DWORD_PTR oldMask = SetThreadAffinityMask(thread, timeMask);

    __int64 curRealTime;
    QueryPerformanceCounter((LARGE_INTEGER*) &curRealTime);
    this->diffTime += curRealTime - this->stopTime;
    this->stopTime = 0;
    this->running = true;

	SetThreadAffinityMask(thread, oldMask);
}

//------------------------------------------------------------------------------
/**
    Stop the timer. This will record the current realtime, so that
    the next Start() can measure the time lost between Stop() and Start()
    which must be taken into account to keep track of the difference between
    this timer's time and realtime.
*/
void
Win360Timer::Stop()
{
	HANDLE thread = GetCurrentThread();
	DWORD_PTR oldMask = SetThreadAffinityMask(thread, timeMask);

    n_assert(this->running);
    QueryPerformanceCounter((LARGE_INTEGER*) &this->stopTime);
    this->running = false;

	SetThreadAffinityMask(thread, oldMask);
}

//------------------------------------------------------------------------------
/**
    Reset the timer so that will start counting at zero again.
*/
void
Win360Timer::Reset()
{
    bool wasRunning = this->running;
    if (wasRunning)
    {
        this->Stop();
    }
    this->stopTime = 0;
    this->diffTime = 0;
    if (wasRunning)
    {
        this->Start();
    }
}

//------------------------------------------------------------------------------
/**
    Returns true if the timer is currently running.
*/
bool
Win360Timer::Running() const
{
    return this->running;
}

//------------------------------------------------------------------------------
/**
    This returns the internal local time as large integer.
*/
__int64
Win360Timer::InternalTime() const
{
    __int64 time;
    if (this->running)
    {
        QueryPerformanceCounter((LARGE_INTEGER*) &time);
    }
    else
    {
        time = this->stopTime;
    }
 
    time -= this->diffTime;

    return time;
}

//------------------------------------------------------------------------------
/**
    This returns the timer's current time in seconds.
*/
Timing::Time
Win360Timer::GetTime() const
{
	HANDLE thread = GetCurrentThread();
	DWORD_PTR oldMask = SetThreadAffinityMask(thread, timeMask);

    __int64 time = this->InternalTime();

    __int64 freq;
    QueryPerformanceFrequency((LARGE_INTEGER*) &freq);
 
    Timing::Time seconds = ((Timing::Time)time) / ((Timing::Time)freq);

	SetThreadAffinityMask(thread, oldMask);

    return seconds;
}

//------------------------------------------------------------------------------
/**
    This returns the timer's current time in seconds.
*/
Timing::MicrosecondTick
Win360Timer::GetusTicks()
{
	__int64 time;

	QueryPerformanceCounter((LARGE_INTEGER*) &time);

	__int64 freq;
	QueryPerformanceFrequency((LARGE_INTEGER*) &freq);

	Timing::MicrosecondTick microsecond = (Timing::MicrosecondTick)(time * 1000 / (freq / 1000));
	return microsecond;
}
//------------------------------------------------------------------------------
/**
    This returns the timer's current time in "ticks". A tick is defined
    as one millisecond (1/1000 seconds).
*/
Timing::Tick
Win360Timer::GetTicks() const
{

	HANDLE thread = GetCurrentThread();
	DWORD_PTR oldMask = SetThreadAffinityMask(thread, timeMask);


    __int64 time = this->InternalTime();

    __int64 freq;
    QueryPerformanceFrequency((LARGE_INTEGER*) &freq);

    __int64 ticks64 = time / (freq / 1000);

	SetThreadAffinityMask(thread, oldMask);

    return (Timing::Tick) ticks64;
}

//------------------------------------------------------------------------
/**
   找到合适的核用于高性能计数器的计算                                                                    
*/
void 
Win360Timer::FindValidTimeMask()
{
	DWORD_PTR procMask;
	DWORD_PTR sysMask;
	GetProcessAffinityMask(GetCurrentProcess(), &procMask, &sysMask);

	if (procMask == 0)
		procMask = 1;

	if( timeMask == 0 )
	{
		timeMask = 1;
		while( ( timeMask & procMask ) == 0 )
		{
			timeMask <<= 1;
		}
	}

}


} // namespace Win360

#endif