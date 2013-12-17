#pragma once
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

#include "core/types.h"
#include "util/array.h"
#include <deque>
#include <algorithm>

//------------------------------------------------------------------------------
namespace Util
{
template<class TYPE> class Queue
{
public:
    /// constructor
    Queue();
    /// copy constructor
    Queue(const Queue<TYPE>& rhs);

    /// assignment operator
    void operator=(const Queue<TYPE>& rhs);
    /// access element by index, 0 is the frontmost element (next to be dequeued)
    TYPE& operator[](IndexT index) const;
    /// equality operator
    bool operator==(const Queue<TYPE>& rhs) const;
    /// inequality operator
    bool operator!=(const Queue<TYPE>& rhs) const;
    /// increase capacity to fit N more elements into the queue
    void Reserve(SizeT num);
    /// returns number of elements in the queue
    SizeT Size() const;
    /// return true if queue is empty
    bool IsEmpty() const;
    /// remove all elements from the queue
    void Clear();
    /// return true if queue contains element
    bool Contains(const TYPE& e) const;

    /// add element to the back of the queue
    void Enqueue(const TYPE& e);
    /// remove the element from the front of the queue
    TYPE Dequeue();
    /// access to element at front of queue without removing it
    TYPE& Peek() const;

protected:
    Array<TYPE> queueArray;
};

// queue的性能较差。用Stl::deque 重新实现一份
template<class TYPE, class _Container = std::deque<TYPE> > 
class StlQueue
{
public:
	/// constructor
	StlQueue();
	/// copy constructor
	StlQueue(const StlQueue<TYPE>& rhs);

	/// assignment operator
	void operator=(const StlQueue<TYPE>& rhs);
	/// access element by index, 0 is the frontmost element (next to be dequeued)
	const TYPE& operator[](IndexT index) const;
	TYPE& operator[](IndexT index); 
	/// equality operator
	bool operator==(const StlQueue<TYPE>& rhs) const;
	/// inequality operator
	bool operator!=(const StlQueue<TYPE>& rhs) const;
	/// increase capacity to fit N more elements into the queue
	void Reserve(SizeT num);
	/// returns number of elements in the queue
	SizeT Size() const;
	/// return true if queue is empty
	bool IsEmpty() const;
	/// remove all elements from the queue
	void Clear();
	/// return true if queue contains element
	bool Contains(const TYPE& e) const;

	/// add element to the back of the queue
	void Enqueue(const TYPE& e);
	/// remove the element from the front of the queue
	TYPE Dequeue();
	/// access to element at front of queue without removing it
	const TYPE& Peek() const;
	TYPE& Peek();

protected:
	_Container queueArray;
};

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
Queue<TYPE>::Queue()
{
    // empty
}

template<class TYPE, class _Container>
StlQueue<TYPE, _Container>::StlQueue()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
Queue<TYPE>::Queue(const Queue<TYPE>& rhs)
{
    this->queueArray = rhs.queueArray;
}

template<class TYPE, class _Container>
StlQueue<TYPE, _Container>::StlQueue(const StlQueue<TYPE>& rhs)
{
	this->queueArray = rhs.queueArray;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
Queue<TYPE>::operator=(const Queue<TYPE>& rhs)
{
    this->queueArray = rhs.queueArray;
}

template<class TYPE, class _Container>
void
StlQueue<TYPE, _Container>::operator=(const StlQueue<TYPE>& rhs)
{
	this->queueArray = rhs.queueArray;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE&
Queue<TYPE>::operator[](IndexT index) const
{
    return this->queueArray[index];
}

template<class TYPE, class _Container>
const TYPE&
StlQueue<TYPE, _Container>::operator[](IndexT index) const
{
#if NEBULA3_BOUNDSCHECKS
	return this->queueArray.at(index);
#else
	return this->queueArray[index];
#endif
}

template<class TYPE, class _Container>
TYPE&
StlQueue<TYPE, _Container>::operator[](IndexT index)
{
#if NEBULA3_BOUNDSCHECKS
	return this->queueArray.at(index);
#else
	return this->queueArray[index];
#endif
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
Queue<TYPE>::operator==(const Queue<TYPE>& rhs) const
{
    return this->queueArray == rhs.queueArray;
}

template<class TYPE, class _Container>
bool
StlQueue<TYPE, _Container>::operator==(const StlQueue<TYPE>& rhs) const
{
	return this->queueArray == rhs.queueArray;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
Queue<TYPE>::operator!=(const Queue<TYPE>& rhs) const
{
    return this->queueArray != rhs.queueArray;
}

template<class TYPE, class _Container>
bool
StlQueue<TYPE, _Container>::operator!=(const StlQueue<TYPE>& rhs) const
{
	return this->queueArray != rhs.queueArray;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
Queue<TYPE>::Contains(const TYPE& e) const
{
    return (InvalidIndex != this->queueArray.FindIndex(e));
}

template<class TYPE, class _Container>
bool
StlQueue<TYPE, _Container>::Contains(const TYPE& e) const
{
	return std::find( this->queueArray.begin(), this->queueArray.end(), e ) != this->queueArray.end();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
Queue<TYPE>::Clear()
{
    this->queueArray.Clear();
}

template<class TYPE, class _Container>
void
StlQueue<TYPE, _Container>::Clear()
{
	this->queueArray.clear();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
Queue<TYPE>::Reserve(SizeT num)
{
    this->queueArray.Reserve(num);
}

template<class TYPE, class _Container>
void
StlQueue<TYPE, _Container>::Reserve(SizeT num)
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
SizeT
Queue<TYPE>::Size() const
{
    return this->queueArray.Size();
}

template<class TYPE, class _Container>
SizeT
StlQueue<TYPE, _Container>::Size() const
{
	return this->queueArray.size();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
bool
Queue<TYPE>::IsEmpty() const
{
    return this->queueArray.IsEmpty();
}

template<class TYPE, class _Container>
bool
StlQueue<TYPE, _Container>::IsEmpty() const
{
	return this->queueArray.empty();
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
void
Queue<TYPE>::Enqueue(const TYPE& e)
{
    this->queueArray.Append(e);
}

template<class TYPE, class _Container>
void
StlQueue<TYPE, _Container>::Enqueue(const TYPE& e)
{
	this->queueArray.push_back(e);
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE
Queue<TYPE>::Dequeue()
{
    TYPE e = this->queueArray.Front();
    this->queueArray.EraseIndex(0);
    return e;
}

template<class TYPE, class _Container>
TYPE
StlQueue<TYPE, _Container>::Dequeue()
{
	TYPE e = this->queueArray.front();
	this->queueArray.pop_front();
	return e;
}

//------------------------------------------------------------------------------
/**
*/
template<class TYPE>
TYPE&
Queue<TYPE>::Peek() const
{
    return this->queueArray.Front();
}

template<class TYPE, class _Container>
const TYPE&
StlQueue<TYPE, _Container>::Peek() const
{
	return this->queueArray.front();
}
template<class TYPE, class _Container>
TYPE&
StlQueue<TYPE, _Container>::Peek()
{
	return this->queueArray.front();
}


} // namespace Util
//------------------------------------------------------------------------------
