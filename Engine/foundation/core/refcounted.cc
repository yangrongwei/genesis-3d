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
#include "stdneb.h"
#include "core/refcounted.h"

namespace Core
{
__ImplementRootClass(Core::RefCounted, 'REFC');

#if NEBULA3_DEBUG
using namespace Util;

Threading::CriticalSection RefCounted::criticalSection;
int RefCounted::isInCreate = 0;
RefCountedList RefCounted::list;
#endif

//------------------------------------------------------------------------------
/**
*/
RefCounted::~RefCounted()
{
    n_assert(0 == this->refCount);
    #if NEBULA3_DEBUG
        n_assert(!this->destroyed);
        n_assert(0 != this->listIterator);
        criticalSection.Enter();
        list.Remove(this->listIterator);
        criticalSection.Leave();
        this->listIterator = 0;
        this->destroyed = true;
    #endif
}

//------------------------------------------------------------------------------
/**
    This method should be called as the very last before an application 
    exits.
*/
void
RefCounted::DumpRefCountingLeaks()
{
    #if NEBULA3_DEBUG
    list.DumpLeaks();    
    #endif
}

//------------------------------------------------------------------------------
/**
    Gather per-class stats.
*/
#if NEBULA3_DEBUG
Dictionary<String,RefCounted::Stats>
RefCounted::GetOverallStats()
{
    Dictionary<String,Stats> result;
    criticalSection.Enter();
    // iterate over refcounted list
    RefCountedList::Iterator iter;
    for (iter = list.Begin(); iter != list.End(); iter++)
    {
        RefCounted* cur = *iter;
        if (!result.Contains(cur->GetClassName()))
        {
            Stats newStats;
            newStats.className   = cur->GetClassName();
            newStats.classFourCC = cur->GetClassFourCC();
            newStats.numObjects  = 1;
            newStats.overallRefCount = cur->GetRefCount();
            newStats.instanceSize = cur->GetRtti()->GetInstanceSize();
            result.Add(cur->GetClassName(), newStats);
        }
        else
        {
            Stats& stats = result[cur->GetClassName()];
            stats.numObjects++;
            stats.overallRefCount += cur->GetRefCount();
        }
    }
    criticalSection.Leave();
    return result;
}
#endif

} // namespace Foundation