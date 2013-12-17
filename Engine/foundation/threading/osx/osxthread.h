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
#pragma once

#include "core/refcounted.h"
#include "threading/threadid.h"
#include "system/cpu.h"
#include "osxEvent.h"
//------------------------------------------------------------------------------
namespace OSX
{
class OSXThread : public Core::RefCounted
{
    __DeclareClass(OSXThread);
public:
    /// thread priorities
    enum Priority
    {
        Low,
        Normal,
        High,
    };
    
    /// constructor
    OSXThread();
    /// destructor
    virtual ~OSXThread();
    /// set the thread priority
    void SetPriority(Priority p);
    /// get the thread priority
    Priority GetPriority() const;
    /// set cpu core on which the thread should be running
    void SetCoreId(System::Cpu::CoreId coreId);
    /// get the cpu core on which the thread should be running
    System::Cpu::CoreId GetCoreId() const;
    /// set stack size in bytes (default is 4 KByte)
    void SetStackSize(SizeT s);
    /// get stack size
    SizeT GetStackSize() const;
    /// set thread name
    void SetName(const Util::String& n);
    /// get thread name
    const Util::String& GetName() const;
    /// start executing the thread code, returns when thread has actually started
    void Start();
    /// request threading code to stop, returns when thread has actually finished
    void Stop();
    /// return true if thread has been started
    bool IsRunning() const;
    
    /// yield the thread (gives up current time slice)
    static void YieldThread();
    
    static void SetupMyThreadRunTime( const char* threadName );
    static void DestoryThreadRunTime( bool isMainThread = false );
    /// get the thread ID of this thread
    static Threading::ThreadId GetMyThreadId();
    
    #if NEBULA3_DEBUG
    /*
    struct ThreadDebugInfo
    {
        Util::String threadName;
        PS3Thread::Priority threadPriority;
        System::Cpu::CoreId threadCoreId;
        SizeT threadStackSize;
    };
    /// query thread stats (debug mode only)
    static Util::Array<ThreadDebugInfo> GetRunningThreadDebugInfos();        
    */
    #endif
    
protected:
    /// override this method if your thread loop needs a wakeup call before stopping
    virtual void EmitWakeupSignal();
    /// this method runs in the thread context
    virtual void DoWork();
    /// check if stop is requested, call from DoWork() to see if the thread proc should quit
    bool ThreadStopRequested() const;
    
private:
    /// thread states
    enum ThreadState
    {
        Initial,
        Running,
        Stopped,
    };
    static void* ThreadProc(void* self);
    pthread_t threadHandle;
    OSXEvent threadStartedEvent;
    OSXEvent stopRequestEvent;
    Priority priority;
    SizeT stackSize;
    Util::String name;
    System::Cpu::CoreId coreId;
    ThreadState volatile threadState;
    
#if NEBULA3_DEBUG
    static Threading::CriticalSection criticalSection;
    static Util::List<OSXThread*> ThreadList;
    Util::List<OSXThread*>::Iterator threadListIterator;
#endif
};
    
//------------------------------------------------------------------------------
/**
*/
inline void
OSXThread::SetPriority(Priority p)
{
    this->priority = p;
}
    
//------------------------------------------------------------------------------
/**
 */
inline OSXThread::Priority
OSXThread::GetPriority() const
{
    return this->priority;
}
    
//------------------------------------------------------------------------------
/**
 */
inline void
OSXThread::SetStackSize(SizeT s)
{
    this->stackSize = s;
}
    
//------------------------------------------------------------------------------
/**
 */
inline SizeT
OSXThread::GetStackSize() const
{
    return this->stackSize;
}
    
//------------------------------------------------------------------------------
/**
    If the derived DoWork() method is running in a loop it must regularly
    check if the process wants the thread to terminate by calling
    ThreadStopRequested() and simply return if the result is true. This
    will cause the thread to shut down.
 */
inline bool
OSXThread::ThreadStopRequested() const
{
    return this->stopRequestEvent.Peek();
}
    
//------------------------------------------------------------------------------
/**
    Set the thread's name.
*/
inline void
OSXThread::SetName(const Util::String& n)
{
    n_assert(n.IsValid());
    this->name = n;
}
    
//------------------------------------------------------------------------------
/**
    Get the thread's name. This is the vanilla method which
    returns the name member.
*/
inline const Util::String&
OSXThread::GetName() const
{
    return this->name;
}
    
//------------------------------------------------------------------------------
/**
*/
inline void
OSXThread::SetCoreId(System::Cpu::CoreId id)
{
    this->coreId = id;
}
    
//------------------------------------------------------------------------------
/**
 */
inline System::Cpu::CoreId
OSXThread::GetCoreId() const
{
    return this->coreId;
}
    
} // namespace OSX
//------------------------------------------------------------------------------
