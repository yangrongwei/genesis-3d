/****************************************************************************
Copyright (c) 2010, Radon Labs GmbH
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
#include "osxthread.h"
#include "threading/threadruntimeinfo.h"
namespace OSX
{
__ImplementClass(OSX::OSXThread, 'THRD', Core::RefCounted);
    
using namespace System;    
    
//------------------------------------------------------------------------------
/**
*/
OSXThread::OSXThread() :
    priority(Normal),
    stackSize(16384),
    coreId(Cpu::InvalidCoreId),
    threadState(Initial)
{
    // register with thread list
    #if NEBULA3_DEBUG
    OSXThread::criticalSection.Enter();
    this->threadListIterator = ThreadList.AddBack(this);
    OSXThread::criticalSection.Leave();
    #endif
}

//------------------------------------------------------------------------------
/**
*/
OSXThread::~OSXThread()
{
    if (this->IsRunning())
    {
        this->Stop();
    }
    
    // unregister from thread list
    #if NEBULA3_DEBUG
    n_assert(0 != this->threadListIterator);
    OSXThread::criticalSection.Enter();
    ThreadList.Remove(this->threadListIterator);
    OSXThread::criticalSection.Leave();
    this->threadListIterator = 0;
    #endif
}
    
//------------------------------------------------------------------------------
/**
*/
void
OSXThread::Start()
{
    n_assert(!this->IsRunning());
	n_assert(0 == this->threadHandle);
    
	pthread_create( &this->threadHandle,NULL,ThreadProc, (void*) this );
	n_assert(NULL != this->threadHandle);
    this->threadState = Running;
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
OSXThread::EmitWakeupSignal()
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
OSXThread::Stop()
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
    this->threadState = Stopped;
	this->threadHandle = 0;
}

//------------------------------------------------------------------------------
/**
    Returns true if the thread is currently running.
*/
bool
OSXThread::IsRunning() const
{
    return (Running == this->threadState);
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
OSXThread::DoWork()
{
    // empty
}
    
void* OSXThread::ThreadProc(void* self)
{
    n_assert(0 != self);
        
    OSXThread* threadObj = (OSXThread*) self;
        
    // must before  localStringAtomTable construct
    OSXThread::SetupMyThreadRunTime(threadObj->GetName().AsCharPtr());
        
    // for destroy localStringAtomTable before Win360Thread::DestoryThreadRunTime()
    {
#if NEBULA3_ENABLE_THREADLOCAL_STRINGATOM_TABLES
    // setup thread-local string atom table (will be discarded when thread terminates)
        LocalStringAtomTable localStringAtomTable;
#endif
        threadObj->threadStartedEvent.Signal();
        threadObj->DoWork();
    }
        
        
    OSXThread::DestoryThreadRunTime();
        
        
}
    
//------------------------------------------------------------------------------
/**
    Static method which returns the ThreadId of this thread.
*/
Threading::ThreadId
OSXThread::GetMyThreadId()
{
    return pthread_self();
}
    
//------------------------------------------------------------------------------
/**
    Give up time slice.
*/
void
OSXThread::YieldThread()
{
    //TODO:
    //n_error("OSXThread::YieldThread(): IMPLEMENT ME!");
}

//------------------------------------------------------------------------------
/**
 Static method which sets the name of this thread. This is called from
 within ThreadProc. The string pointed to must remain valid until
 the thread is terminated!
 */

void
OSXThread::SetupMyThreadRunTime(const char* n)
{
    Threading::ThreadRunTimeInfo::SetupMyThreadRunTime( n );
    
}
//------------------------------------------------------------------------
void
OSXThread::DestoryThreadRunTime( bool isMainThread /*= false*/ )
{
    Threading::ThreadRunTimeInfo::DestoryThreadRunTime( isMainThread );
}
//------------------------------------------------------------------------------
/**
    Returns an array with infos about all currently existing thread objects.
*/
#if NEBULA3_DEBUG
Array<OSXThread::ThreadDebugInfo>
OSXThread::GetRunningThreadDebugInfos()
{
    // NOTE: Portions of this loop aren't completely thread-safe
    // (getting the thread-name for instance), but since those
    // attributes don't change when the thread has been started
    // this shouldn't be a problem.
    Array<ThreadDebugInfo> infos;
    OSXThread::criticalSection.Enter();
    List<OSXThread*>::Iterator iter;
    for (iter = ThreadList.Begin(); iter != ThreadList.End(); iter++)
    {
        OSXThread* cur = *iter;
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
    OSXThread::criticalSection.Leave();
    return infos;
}
#endif
    
} // namespace OSX