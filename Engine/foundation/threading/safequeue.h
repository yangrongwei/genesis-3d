#pragma once
/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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

#include "util/queue.h"
#include "threading/criticalsection.h"
#include "threading/event.h"

//------------------------------------------------------------------------------
namespace Threading
{
template<class TYPE> class SafeQueue : protected Util::Queue<TYPE>
{
public:
    /// constructor
    SafeQueue();
    /// copy constructor
    SafeQueue(const SafeQueue<TYPE>& rhs);

    /// assignment operator
    void operator=(const SafeQueue<TYPE>& rhs);
    /// enable/disable signalling on Enqueue() (default is enabled)
    void SetSignalOnEnqueueEnabled(bool b);
    /// return signalling-on-Enqueue() flag
    bool IsSignalOnEnqueueEnabled() const;
    /// returns number of elements in the queue
    SizeT Size() const;
    /// return true if queue is empty
    bool IsEmpty() const;
    /// remove all elements from the queue
    void Clear();
    /// add element to the back of the queue
    void Enqueue(const TYPE& e);
    /// enqueue an array of elements
    void EnqueueArray(const Util::Array<TYPE>& a);
    /// remove the element from the front of the queue
    TYPE Dequeue();
    /// dequeue all events (only requires one lock)
    void DequeueAll(Util::Array<TYPE>& outArray);
	/// dequeue all events by swap(only requires one lock)
	void DequeueAllBySwap(Util::Array<TYPE>& outArray);

    /// access to element at front of queue without removing it
    TYPE Peek() const;
    /// wait until queue contains at least one element
    void Wait();
    /// wait until queue contains at least one element, or time-out happens
    void WaitTimeout(int ms);
    /// signal the internal event, so that Wait() will return
    void Signal();
    /// erase all matching elements
    void EraseMatchingElements(const TYPE& e);

protected:
    CriticalSection criticalSection;
    Event enqueueEvent;
    bool signalOnEnqueueEnabled;
};

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
SafeQueue<TYPE>::SafeQueue() :
    signalOnEnqueueEnabled(true)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
SafeQueue<TYPE>::SafeQueue(const SafeQueue<TYPE>& rhs)
{
    this->criticalSection.Enter();
    this->queueArray = rhs.queueArray;
    this->signalOnEnqueueEnabled = rhs.signalOnEnqueueEnabled;
    this->criticalSection.Leave();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
SafeQueue<TYPE>::operator=(const SafeQueue<TYPE>& rhs)
{
    this->criticalSection.Enter();
    this->queueArray = rhs.queueArray;
    this->signalOnEnqueueEnabled = rhs.signalOnEnqueueEnabled;
    this->criticalSection.Leave();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
SafeQueue<TYPE>::SetSignalOnEnqueueEnabled(bool b)
{
    this->criticalSection.Enter();
    this->signalOnEnqueueEnabled = b;
    this->criticalSection.Leave();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
SafeQueue<TYPE>::Clear()
{
    this->criticalSection.Enter();
    this->queueArray.Clear();
    this->criticalSection.Leave();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> SizeT
SafeQueue<TYPE>::Size() const
{
    return this->queueArray.Size();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> bool
SafeQueue<TYPE>::IsEmpty() const
{
    this->criticalSection.Enter();
    bool isEmpty = this->queueArray.IsEmpty();
    this->criticalSection.Leave();
    return isEmpty;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
SafeQueue<TYPE>::Enqueue(const TYPE& e)
{
    this->criticalSection.Enter();
    this->queueArray.Append(e);
    this->criticalSection.Leave();
    if (this->signalOnEnqueueEnabled)
    {
        this->enqueueEvent.Signal();
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
SafeQueue<TYPE>::EnqueueArray(const Util::Array<TYPE>& a)
{
    this->criticalSection.Enter();
    this->queueArray.AppendArray(a);
    this->criticalSection.Leave();
    if (this->signalOnEnqueueEnabled)
    {
        this->enqueueEvent.Signal();
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> TYPE
SafeQueue<TYPE>::Dequeue()
{
    this->criticalSection.Enter();
    TYPE e = this->queueArray.Front();
    this->queueArray.EraseIndex(0);
    this->criticalSection.Leave();
    return e;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
SafeQueue<TYPE>::DequeueAll(Util::Array<TYPE>& outArray)
{
    this->criticalSection.Enter();
    outArray = this->queueArray;
    this->queueArray.Clear();
    this->criticalSection.Leave();
}
//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
	SafeQueue<TYPE>::DequeueAllBySwap(Util::Array<TYPE>& outArray)
{
	this->criticalSection.Enter();
	outArray.Swap(this->queueArray);
	this->criticalSection.Leave();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> TYPE
SafeQueue<TYPE>::Peek() const
{
    this->criticalSection.Enter();
    TYPE e = this->queueArray.Front();
    this->criticalSection.Leave();
    return e;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
SafeQueue<TYPE>::Wait()
{
    if (this->signalOnEnqueueEnabled && this->IsEmpty())
    {
        this->enqueueEvent.Wait();
    }
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
SafeQueue<TYPE>::WaitTimeout(int ms)
{
    if (this->signalOnEnqueueEnabled && this->IsEmpty())
    {
        this->enqueueEvent.WaitTimeout(ms);
    }
}

//------------------------------------------------------------------------------
/**
    This signals the internal event object, on which Wait() may be waiting.
    This method may be useful to wake up a thread waiting for events
    when it should stop.
*/
template<class TYPE> void
SafeQueue<TYPE>::Signal()
{
    this->enqueueEvent.Signal();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE> void
SafeQueue<TYPE>::EraseMatchingElements(const TYPE& e)
{
    this->criticalSection.Enter();
    IndexT i;
    for (i = this->queueArray.Size() - 1; i >= 0; i--)
    {
        if (e == this->queueArray[i])
        {
            this->queueArray.EraseIndex(i);
        }
    }
    this->criticalSection.Leave();
}

} // namespace Threading
//------------------------------------------------------------------------------

    