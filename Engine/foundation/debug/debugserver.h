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
    @class Debug::DebugServer
  
    The debug server singleton is visible from all threads and keeps track
    of debug timer and debug counters.
*/
#include "core/refcounted.h"
#include "core/singleton.h"
#include "threading/criticalsection.h"
#include "util/stringatom.h"

//------------------------------------------------------------------------------
namespace Debug
{
class DebugCounter;
class DebugTimer;

class DebugServer : public Core::RefCounted
{
    __DeclareClass(DebugServer);
    __DeclareImageSingleton(DebugServer);
public:
    /// constructor
    DebugServer();
    /// destructor
    virtual ~DebugServer();
    
    /// return true if debug server is open
    bool IsOpen() const;
    /// register a debug timer
    void RegisterDebugTimer(const GPtr<DebugTimer>& timer);
    /// unregister a debug timer
    void UnregisterDebugTimer(const GPtr<DebugTimer>& timer);
    /// register a debug counter
    void RegisterDebugCounter(const GPtr<DebugCounter>& counter);
    /// unregister a debug counter
    void UnregisterDebugCounter(const GPtr<DebugCounter>& counter);
    /// get all registered debug timers
    Util::Array<GPtr<DebugTimer> > GetDebugTimers() const;
    /// get all registered debug counters
    Util::Array<GPtr<DebugCounter> > GetDebugCounters() const;    
    /// get debug timer by name, returns invalid ptr if not exists
    GPtr<DebugTimer> GetDebugTimerByName(const Util::StringAtom& name) const;
    /// get debug counter by name, returns invalid ptr if not exists
    GPtr<DebugCounter> GetDebugCounterByName(const Util::StringAtom& name) const;
    
private:
    friend class DebugHandler;
    friend class DebugPageHandler;

    /// open the debug server
    void Open();
    /// close the debug server
    void Close();

    bool isOpen;
    Threading::CriticalSection critSect;
    Util::Dictionary<Util::StringAtom, GPtr<DebugTimer> > debugTimers;
    Util::Dictionary<Util::StringAtom, GPtr<DebugCounter> > debugCounters;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
DebugServer::IsOpen() const
{
    bool retval;
    this->critSect.Enter();
    retval = this->isOpen;
    this->critSect.Leave();
    return retval;
}

} // namespace Debug
//------------------------------------------------------------------------------
