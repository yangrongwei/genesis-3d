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



#include "stdneb.h"
#include "timing/osx/osxtimer.h"
#include <time.h>
#include <sys/time.h>

namespace OSX
{
    OSXTimer::OSXTimer()
	:running(false),
    diffTime(0.0),
    stopTime(0)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     Start the timer. This will update the diffTime member to reflect
     the accumulated time when the timer was not running (basically the
     difference between this timer's time and the real system time).
     */
    void
    OSXTimer::Start()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        
        Timing::Time curTime   = ConvertLinuxTime(tv.tv_sec, tv.tv_usec);
        this->diffTime += curTime - this->stopTime;
        this->stopTime  = 0.0f;
        this->running   = true;
    }
    
    //------------------------------------------------------------------------------
    /**
     Stop the timer. This will record the current realtime, so that
     the next Start() can measure the time lost between Stop() and Start()
     which must be taken into account to keep track of the difference between
     this timer's time and realtime.
     */
    void
    OSXTimer::Stop()
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        
        this->stopTime = ConvertLinuxTime(tv.tv_sec, tv.tv_usec);
        this->running = false;
    }
    
    //------------------------------------------------------------------------------
    /**
     Reset the timer so that will start counting at zero again.
     */
    void
    OSXTimer::Reset()
    {
        bool wasRunning = this->running;
        if (wasRunning)
        {
            this->Stop();
        }
        this->stopTime = 0.0f;
        this->diffTime = 0.0f;
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
    OSXTimer::Running() const
    {
        return this->running;
    }
    
    Timing::Time
    OSXTimer::InternalTime() const
    {
        
        Timing::Time time;
        
        struct timeval tv;
        gettimeofday(&tv, NULL);
        
        if (this->running)
        {
            // we are running, query current time
            time = ConvertLinuxTime(tv.tv_sec, tv.tv_usec);
        }
        else
        {
            // we are stopped, use time at last stop
            time = this->stopTime;
        }
        
        // convert to local time
        time -= this->diffTime;
         
        return time;
    }
    
    //------------------------------------------------------------------------------
    /**
     This returns the timer's current time in seconds.
     */
    Timing::Time
    OSXTimer::GetTime() const
    {
        Timing::Time seconds = this->InternalTime();
        
        return (Timing::Time)seconds;
    }
    
    //------------------------------------------------------------------------------
    /**
     This returns the timer's current time in "ticks". A tick is defined
     as one millisecond (1/1000 seconds).
     */
    Timing::Tick
    OSXTimer::GetTicks() const
    {
        Timing::Time seconds = this->InternalTime();
        return (Timing::Tick)(1000 * seconds);
    }
    //------------------------------------------------------------------------------
    /**
     This returns the timer's current real time in seconds.
     */
    Timing::MicrosecondTick
    OSXTimer::GetusTicks()
    {
		struct timeval tv;
		gettimeofday(&tv, NULL);  
		// we are running, query current time
		return Timing::MicrosecondTick(tv.tv_sec) * 1000 * 1000 + Timing::MicrosecondTick(tv.tv_usec);
    }

    Timing::Time OSXTimer::ConvertLinuxTime(const long& sec, const long& nsec)
    {
        return (Timing::Time(sec) + Timing::Time(nsec) / (1000 * 1000) );
    }
    
}
