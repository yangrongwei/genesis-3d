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

#ifdef __ANDROID__
#include "stdneb.h"
#include "threading/android/androidThread.h"
#include "system/systeminfo.h"
#include "core/sysfunc.h"

#include <asm-generic/errno-base.h>

namespace Android
{
__ImplementClass(Android::AndroidThread, 'THRD', Core::RefCounted);

using namespace Util;
using namespace System;

#if NEBULA3_DEBUG
Threading::CriticalSection AndroidThread::criticalSection;
List<AndroidThread*> AndroidThread::ThreadList;
#endif

//------------------------------------------------------------------------------
/**
*/
AndroidThread::AndroidThread() :
	threadHandle(0),
    priority(Normal),
    stackSize(65536),
    coreId(Cpu::InvalidCoreId)
{
    // register with thread list
    #if NEBULA3_DEBUG
        AndroidThread::criticalSection.Enter();
        this->threadListIterator = ThreadList.AddBack(this);
        AndroidThread::criticalSection.Leave();
    #endif
}

//------------------------------------------------------------------------------
/**
*/
AndroidThread::~AndroidThread()
{
    if (this->IsRunning())
    {
        this->Stop();
    }

    // unregister from thread list
    #if NEBULA3_DEBUG
        n_assert(0 != this->threadListIterator);
        AndroidThread::criticalSection.Enter();
        ThreadList.Remove(this->threadListIterator);
        AndroidThread::criticalSection.Leave();
        this->threadListIterator = 0;
    #endif
}

//------------------------------------------------------------------------------
/**
    Start the thread, this creates a Win32 thread and calls the static
    ThreadProc, which in turn calls the virtual DoWork() class of this object.
    The method waits for the thread to start and then returns.
*/
void
AndroidThread::Start()
{
	n_assert(!this->IsRunning());
	n_assert(0 == this->threadHandle);

	pthread_create( &this->threadHandle,NULL,ThreadProc, (void*) this );
	n_assert(NULL != this->threadHandle);

	// wait for the thread to start
	this->threadStartedEvent.Wait();
}

//------------------------------------------------------------------------------
/**
    This method is called by Thread::Stop() after setting the 
    stopRequest event and before waiting for the thread to stop. If your
    thread runs a loop and waits for jobs it may need an extra wakeup
    signal to stop waiting and check for the ThreadStopRequested() event. In
    this case, override this method and signal your event object.
*/
void
AndroidThread::EmitWakeupSignal()
{
    // empty, override in subclass!
}

//------------------------------------------------------------------------------
/**
    This stops the thread by signalling the stopRequestEvent and waits for the
    thread to actually quit. If the thread code runs in a loop it should use the 
    IsStopRequested() method to see if the thread object wants it to shutdown. 
    If so DoWork() should simply return.
*/
void
AndroidThread::Stop()
{
	n_assert(this->IsRunning());
	n_assert(0 != this->threadHandle);

	// signal the thread to stop
	this->stopRequestEvent.Signal();

	// call the wakeup-thread method, may be derived in a subclass
	// if the threads needs to be woken up, it is important that this
	// method is called AFTER the stopRequestEvent is signalled!
	this->EmitWakeupSignal();

	void* threadResult;
	pthread_join(this->threadHandle, &threadResult);

	this->threadHandle = 0;
}

//------------------------------------------------------------------------------
/**
    Returns true if the thread is currently running.
*/
bool
AndroidThread::IsRunning() const
{
	if (this->threadHandle != NULL)
	{
		return pthread_kill(this->threadHandle, 0) != ESRCH;
	}
    else
	{
		return false;
	}

}

//------------------------------------------------------------------------------
/**
    This method should be derived in a Thread subclass and contains the
    actual code which is run in the thread. The method must not call
    C-Lib functions under Win32. To terminate the thread, just return from
    this function. If DoWork() runs in an infinite loop, call ThreadStopRequested()
    to check whether the Thread object wants the thread code to quit.
*/
void
AndroidThread::DoWork()
{
    // empty
}

void* AndroidThread::ThreadProc(void* self)
{
	n_assert(0 != self);

	AndroidThread* threadObj = (AndroidThread*) self;

	// must before  localStringAtomTable construct
	AndroidThread::SetupMyThreadRunTime(threadObj->GetName().AsCharPtr());

	// for destroy localStringAtomTable before Win360Thread::DestoryThreadRunTime()
	{
#if NEBULA3_ENABLE_THREADLOCAL_STRINGATOM_TABLES
		// setup thread-local string atom table (will be discarded when thread terminates)
		LocalStringAtomTable localStringAtomTable;
#endif
		threadObj->threadStartedEvent.Signal();
		threadObj->DoWork();
	}


	AndroidThread::DestoryThreadRunTime();

	
}


//------------------------------------------------------------------------------
/**
    Internal static helper method. This is called by CreateThread() and
    simply calls the virtual DoWork() method on the thread object.
*/


//------------------------------------------------------------------------------
/**
    Static method which sets the name of this thread. This is called from
    within ThreadProc. The string pointed to must remain valid until
    the thread is terminated!
*/

void
AndroidThread::SetupMyThreadRunTime(const char* n)
{
	Threading::ThreadRunTimeInfo::SetupMyThreadRunTime( n );

}
//------------------------------------------------------------------------
void 
AndroidThread::DestoryThreadRunTime( bool isMainThread /*= false*/ )
{
	Threading::ThreadRunTimeInfo::DestoryThreadRunTime( isMainThread );
}

//------------------------------------------------------------------------------
/**
    Static method to obtain the current thread name from anywhere
    in the thread's code.
*/
const char*
AndroidThread::GetMyThreadName()
{
	Threading::ThreadRunTimeInfo* pInfo = Threading::ThreadRunTimeInfo::GetMyThreadRuntime();
	n_assert( pInfo );
	return pInfo->mThreadName;
}

//------------------------------------------------------------------------------
/**
    Static method which returns the ThreadId of this thread.
*/
Threading::ThreadId
AndroidThread::GetMyThreadId()
{
    return pthread_self();
}

//------------------------------------------------------------------------------
/**
    The yield function is empty on Win32 and Xbox360.
*/
void
AndroidThread::YieldThread()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Returns an array with infos about all currently existing thread objects.
*/
#if NEBULA3_DEBUG
Array<AndroidThread::ThreadDebugInfo>
AndroidThread::GetRunningThreadDebugInfos()
{
    // NOTE: Portions of this loop aren't completely thread-safe
    // (getting the thread-name for instance), but since those
    // attributes don't change when the thread has been started
    // this shouldn't be a problem.
    Array<ThreadDebugInfo> infos;
    AndroidThread::criticalSection.Enter();
    List<AndroidThread*>::Iterator iter;
    for (iter = ThreadList.Begin(); iter != ThreadList.End(); iter++)
    {
        AndroidThread* cur = *iter;
        if (cur->IsRunning())
        {
            ThreadDebugInfo info;
            info.threadName = cur->GetName();
            info.threadPriority = cur->GetPriority();
            info.threadCoreId = cur->GetCoreId();
            info.threadStackSize = cur->GetStackSize();
            infos.Append(info);
        }
    }
    AndroidThread::criticalSection.Leave();
    return infos;
}

#endif

} // namespace Android
#endif