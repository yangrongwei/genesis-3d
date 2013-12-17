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

#include "stdneb.h"
#include "debug/debugtimer.h"
#include "debug/debugserver.h"

namespace Debug
{
__ImplementClass(Debug::DebugTimer, 'DBGT', Core::RefCounted);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
DebugTimer::DebugTimer() :
    accumTime(0.0),
    startTime(0.0),
    resultTime(0.0),
    history(128)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
DebugTimer::~DebugTimer()
{
    // we may need de-construct if the critical section is still taken
    this->critSect.Enter();
    n_assert(!this->IsValid());
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
DebugTimer::Setup(const StringAtom& timerName)
{
    n_assert(timerName.IsValid());
    n_assert(!this->IsValid());

    this->critSect.Enter();
    this->name = timerName;
    this->history.Reset();
    this->timer.Reset();
    this->critSect.Leave();

    DebugServer::Instance()->RegisterDebugTimer(this);
}

//------------------------------------------------------------------------------
/**
*/
void
DebugTimer::Discard()
{
    n_assert(this->IsValid());
    DebugServer::Instance()->UnregisterDebugTimer(this);

    this->critSect.Enter();
    this->history.Reset();
    this->timer.Reset();
    this->name.Clear();
    this->critSect.Leave();
}
        
//------------------------------------------------------------------------------
/**
*/
Timing::Time
DebugTimer::GetSample() const
{
    Timing::Time time = 0.0;
    this->critSect.Enter();
    if (!this->history.IsEmpty())
    {
        time = this->history.Back();
    }
    this->critSect.Leave();
    return time;
}

//------------------------------------------------------------------------------
/**
*/
Array<Timing::Time>
DebugTimer::GetHistory() const
{
    this->critSect.Enter();
    Array<Timing::Time> result = this->history.AsArray();
    this->critSect.Leave();
    return result;
}

//------------------------------------------------------------------------------
/**
*/
GPtr<DebugTimer>
DebugTimer::CreateAsSingleton(const Util::StringAtom& timerName)
{
    GPtr<DebugTimer> timerPtr = DebugServer::Instance()->GetDebugTimerByName(timerName);
    if (!timerPtr.isvalid())
    {
        timerPtr = DebugTimer::Create();
        timerPtr->Setup(timerName);
    }
    return timerPtr;
}

//------------------------------------------------------------------------------
/**
*/
void 
DebugTimer::DestroySingleton(const Util::StringAtom& timerName)
{
    GPtr<DebugTimer> timerPtr = DebugServer::Instance()->GetDebugTimerByName(timerName);
    if (timerPtr.isvalid())
    {
        timerPtr->Discard();        
    }
}
} // namespace Debug
