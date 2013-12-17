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
#include "debug/debugcounter.h"
#include "debug/debugserver.h"

namespace Debug
{
__ImplementClass(Debug::DebugCounter, 'DBGC', Core::RefCounted);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
DebugCounter::DebugCounter() :
    value(0),
    history(1024)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
DebugCounter::~DebugCounter()
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
DebugCounter::Setup(const StringAtom& counterName)
{
    n_assert(counterName.IsValid());
    n_assert(!this->IsValid());

    this->critSect.Enter();
    this->name = counterName;
    this->history.Reset();
    this->value = 0;
    this->critSect.Leave();

    DebugServer::Instance()->RegisterDebugCounter(this);
}

//------------------------------------------------------------------------------
/**
*/
void
DebugCounter::Discard()
{
    n_assert(this->IsValid());
    DebugServer::Instance()->UnregisterDebugCounter(this);

    this->critSect.Enter();
    this->history.Reset();
    this->value = 0;
    this->name.Clear();
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
int
DebugCounter::GetSample() const
{
    int val = 0;
    this->critSect.Enter();
    if (!this->history.IsEmpty())
    {
        val = this->history.Back();
    }
    this->critSect.Leave();
    return val;
}

//------------------------------------------------------------------------------
/**
*/
Array<int>
DebugCounter::GetHistory() const
{
    this->critSect.Enter();
    Array<int> result = this->history.AsArray();
    this->critSect.Leave();
    return result;
}

} // namespace Debug