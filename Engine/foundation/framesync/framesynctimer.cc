/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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
#include "framesync/framesynctimer.h"
#include "framesync/framesynchandlerthread.h"

namespace FrameSync
{
__ImplementClass(FrameSync::FrameSyncTimer, 'FSYT', Core::RefCounted);
__ImplementThreadSingleton(FrameSync::FrameSyncTimer);

using namespace Timing;

//------------------------------------------------------------------------------
/**
*/
FrameSyncTimer::FrameSyncTimer() :
    time(0.0),
    ticks(0),
    frameTime(0.0),
    frameTicks(0),
    scaledTime(0.0),
    timeFactor(1.0),
    isValid(false)   
{
    __ConstructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
*/
FrameSyncTimer::~FrameSyncTimer()
{
    if (this->IsValid())
    {
        this->Discard();
    }
    __DestructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
    Query master time from the FrameSyncHandlerThread once at 
    creation time. This is safe but slow, but necessary to immediately
    provide a valid time stamp in the first frame.
*/
void
FrameSyncTimer::Setup()
{
    n_assert(!this->isValid);
    this->isValid = true;

    // do a slow first-time init
    this->UpdateTimePolling();

    // fix frame times to a reasonable value
    this->frameTime = 1.0 / 60.0;
    this->frameTicks = Timing::SecondsToTicks(this->frameTime);
}

//------------------------------------------------------------------------------
/**
*/
void
FrameSyncTimer::Discard()
{
    n_assert(this->isValid);
    this->isValid = false;
}

//------------------------------------------------------------------------------
/**
    Update the time by polling the FrameSyncHandlerThread singleton.
    This requires a CriticalSection to be taken and should not be used
    for threads which run in lockstep mode (i.e. the game thread or the
    render thread) since these will update their time automatically
    during the frame-sync-point.
*/
void
FrameSyncTimer::UpdateTimePolling()
{
    Time t = FrameSyncHandlerThread::Instance()->SafeGetMasterTime();
    this->Update(t);
}

//------------------------------------------------------------------------------
/**
*/
void
FrameSyncTimer::StartTime()
{
    FrameSyncHandlerThread::Instance()->StartMasterTime();
}

//------------------------------------------------------------------------------
/**
*/
void
FrameSyncTimer::StopTime()
{
    FrameSyncHandlerThread::Instance()->StopMasterTime();
}

//------------------------------------------------------------------------------
/**
*/
void
FrameSyncTimer::ResetTime()
{
    FrameSyncHandlerThread::Instance()->ResetMasterTime();
}

//------------------------------------------------------------------------------
/**
*/
bool
FrameSyncTimer::IsTimeRunning() const
{
    return FrameSyncHandlerThread::Instance()->IsMasterTimeRunning();
}

//------------------------------------------------------------------------------
/**
    This method will be called once per frame at the frame-sync-point
    of the FrameSyncHandlerThread. Note that this method will always be 
    called from the local thread, never from another thread, thus we don't
    need to care about thread-safety.
*/
void
FrameSyncTimer::Update(Time newTime)
{
    this->frameTime = newTime - this->time; 
    this->scaledTime = this->scaledTime + this->frameTime * this->timeFactor;    
    if (this->frameTime < 0.001)
    {
        this->frameTime = 0.001;
    }
    this->time = newTime;

    Tick newTicks = Timing::SecondsToTicks(newTime);
    this->frameTicks = newTicks - this->ticks;
    if (this->frameTicks < 1)
    {
        this->frameTicks = 1;
    }
    this->ticks = newTicks;
}

//------------------------------------------------------------------------------
/**
*/
Timing::Time 
FrameSyncTimer::GetScaledFrameTime() const
{
    return this->frameTime * this->timeFactor;
}

//------------------------------------------------------------------------------
/**
*/
IndexT
FrameSyncTimer::GetFrameCount() const
{
    return FrameSyncHandlerThread::Instance()->GetFrameCount();
}

} // namespace FrameSync