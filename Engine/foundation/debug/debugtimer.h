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

#pragma once
//------------------------------------------------------------------------------
/**
    @class Debug::DebugTimer
    
    A debug timer for measuring time spent in code blocks.
*/
#include "core/refcounted.h"
#include "timing/timer.h"
#include "util/stringatom.h"
#include "util/ringbuffer.h"
#include "threading/criticalsection.h"

//------------------------------------------------------------------------------
#if NEBULA3_ENABLE_PROFILING
#define _declare_timer(timer) GPtr<Debug::DebugTimer> timer;
#define _declare_static_timer(timer) static GPtr<Debug::DebugTimer> timer;
#define _setup_timer(timer) {timer = Debug::DebugTimer::Create(); timer->Setup(Util::StringAtom(#timer));}
#define _setup_timer_singleton(timer) {timer = Debug::DebugTimer::CreateAsSingleton(Util::StringAtom(#timer));}
#define _setup_timer_singleton_name(timer, timerName) {timer = Debug::DebugTimer::CreateAsSingleton(Util::StringAtom(#timerName));}
#define _discard_timer_singleton(timer) {Debug::DebugTimer::DestroySingleton(Util::StringAtom(#timer));}
#define _discard_timer(timer) timer->Discard(); timer = 0;
#define _start_timer(timer) timer->Start();
#define _pause_timer(timer) timer->Pause();
#define _stop_timer(timer) timer->Stop();
#define _start_accum_timer(timer) timer->StartAccum();
#define _stop_accum_timer(timer) timer->StopAccum();
#define _reset_accum_timer(timer) timer->ResetAccum();
#else
#define _declare_timer(timer)
#define _setup_timer(timer)
#define _discard_timer(timer)
#define _start_timer(timer)
#define _pause_timer(timer)
#define _stop_timer(timer)
#endif

//------------------------------------------------------------------------------
namespace Debug
{
class DebugTimer : public Core::RefCounted
{
    __DeclareClass(DebugTimer);
public:
    /// constructor
    DebugTimer();
    /// destructor
    virtual ~DebugTimer();

    /// setup the timer
    void Setup(const Util::StringAtom& timerName);
    /// discard the timer
    void Discard();
    /// return true if this timer has been setup
    bool IsValid() const;
    
    /// start or continue the timer
    void Start();
    /// pause the timer
    void Pause();
    /// stop the timer, writes sample to history
    void Stop();

    /// start or continue the timer
    void StartAccum();    
    /// stop the timer, writes sample to history
    void StopAccum();
    /// stop the timer, writes sample to history
    void ResetAccum();
    
    /// get the timer name
    const Util::StringAtom& GetName() const;
    /// get the most current sample
    Timing::Time GetSample() const;
    /// get the timer's history
    Util::Array<Timing::Time> GetHistory() const;

    /// create as singleton
    static GPtr<DebugTimer> CreateAsSingleton(const Util::StringAtom& timerName);
    /// create as singleton
    static void DestroySingleton(const Util::StringAtom& timerName);

private:
    Threading::CriticalSection critSect;
    Util::StringAtom name;
    Timing::Timer timer;
    Timing::Time accumTime;
    Timing::Time startTime;
    Timing::Time resultTime;
    Util::RingBuffer<Timing::Time> history;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
DebugTimer::IsValid() const
{
    return this->name.IsValid();
}

//------------------------------------------------------------------------------
/**
*/
inline void
DebugTimer::Start()
{
    this->timer.Start();
}

//------------------------------------------------------------------------------
/**
*/
inline void
DebugTimer::Pause()
{
    this->timer.Stop();
}

//------------------------------------------------------------------------------
/**
*/
inline void
DebugTimer::Stop()
{
    this->timer.Stop();
    this->critSect.Enter();
    this->history.Add(this->timer.GetTime() * 1000.0f);
    this->critSect.Leave();
    this->timer.Reset();
}

//------------------------------------------------------------------------------
/**
*/
inline void
DebugTimer::StartAccum()
{
    this->timer.Start();
    this->startTime = this->timer.GetTime();
}

//------------------------------------------------------------------------------
/**
*/
inline void
DebugTimer::StopAccum()
{
    Timing::Time stop = this->timer.GetTime();
    Timing::Time diff = stop - this->startTime;
    this->accumTime += diff;
    this->timer.Stop();
}

//------------------------------------------------------------------------------
/**
*/
inline void
DebugTimer::ResetAccum()
{
    if (this->timer.Running())
    {
        this->timer.Stop();
    }
    if (this->accumTime != 0.0)
    {
        this->resultTime = this->accumTime;        
        this->critSect.Enter();
        this->history.Add(this->resultTime * 1000.0f);
        this->critSect.Leave();
        this->timer.Reset();
        this->accumTime = 0.0;
    }    
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::StringAtom&
DebugTimer::GetName() const
{
    return this->name;
}

} // namespace Debug
//------------------------------------------------------------------------------
