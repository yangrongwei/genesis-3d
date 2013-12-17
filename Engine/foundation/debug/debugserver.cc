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
#include "debug/debugserver.h"
#include "debug/debugtimer.h"
#include "debug/debugcounter.h"

namespace Debug
{
__ImplementClass(Debug::DebugServer, 'DBGS', Core::RefCounted);
__ImplementImageSingleton(Debug::DebugServer);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
DebugServer::DebugServer() :
    isOpen(false)
{
    __ConstructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
DebugServer::~DebugServer()
{
    n_assert(!this->isOpen);
    __DestructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void
DebugServer::Open()
{
    this->critSect.Enter();
    n_assert(!this->isOpen);
    this->isOpen = true;
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
DebugServer::Close()
{
    this->critSect.Enter();
    n_assert(this->isOpen);
    this->debugTimers.Clear();
    this->debugCounters.Clear();
    this->isOpen = false;
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
DebugServer::RegisterDebugTimer(const GPtr<DebugTimer>& timer)
{
    this->critSect.Enter();
    n_assert(this->isOpen);
    n_assert(!this->debugTimers.Contains(timer->GetName()));
    this->debugTimers.Add(timer->GetName(), timer);
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
DebugServer::UnregisterDebugTimer(const GPtr<DebugTimer>& timer)
{
    this->critSect.Enter();
    n_assert(this->isOpen);
    n_assert(this->debugTimers.Contains(timer->GetName()));
    this->debugTimers.Erase(timer->GetName());
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
DebugServer::RegisterDebugCounter(const GPtr<DebugCounter>& counter)
{
    this->critSect.Enter();
    n_assert(this->isOpen);
    n_assert(!this->debugCounters.Contains(counter->GetName()));
    this->debugCounters.Add(counter->GetName(), counter);
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
DebugServer::UnregisterDebugCounter(const GPtr<DebugCounter>& counter)
{
    this->critSect.Enter();
    n_assert(this->isOpen);
    n_assert(this->debugCounters.Contains(counter->GetName()));
    this->debugCounters.Erase(counter->GetName());
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
Array<GPtr<DebugTimer> >
DebugServer::GetDebugTimers() const
{
    this->critSect.Enter();
    Array<GPtr<DebugTimer> > result = this->debugTimers.ValuesAsArray();
    this->critSect.Leave();
    return result;
}

//------------------------------------------------------------------------------
/**
*/
Array<GPtr<DebugCounter> >
DebugServer::GetDebugCounters() const
{
    this->critSect.Enter();
    Array<GPtr<DebugCounter> > result = this->debugCounters.ValuesAsArray();
    this->critSect.Leave();
    return result;
}

//------------------------------------------------------------------------------
/**
*/
GPtr<DebugTimer>
DebugServer::GetDebugTimerByName(const StringAtom& name) const
{
    GPtr<DebugTimer> result;
    this->critSect.Enter();
    if (this->debugTimers.Contains(name))
    {
        result = this->debugTimers[name];
    }
    this->critSect.Leave();
    return result;
}

//------------------------------------------------------------------------------
/**
*/
GPtr<DebugCounter>
DebugServer::GetDebugCounterByName(const StringAtom& name) const
{
    GPtr<DebugCounter> result;
    this->critSect.Enter();
    if (this->debugCounters.Contains(name))
    {
        result = this->debugCounters[name];
    }
    this->critSect.Leave();
    return result;
}

} // namespace Debug
