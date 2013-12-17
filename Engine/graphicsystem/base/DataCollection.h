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
#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_
//#include "foundation/util/fixedarray.h"
#include "foundation/core/types.h"
#include "foundation/memory/memory.h"

namespace Graphic
{
	template<typename T>
	class DataCollection
	{
	public:
		typedef T ValueType;
		typedef ValueType* Iterator;
		typedef const ValueType* ConstIterator;

		DataCollection();
		DataCollection(SizeT bufferSize);	
		~DataCollection();
		ValueType& PushBack();
		void PushBack(const ValueType& value);		
		ConstIterator Back() const;
		void Pop();
		void Clear();
		void ClearWithBuffer();

		SizeT Count() const;
		void Resize(SizeT newSize);
		Iterator Begin();
		Iterator End();
		ConstIterator Begin() const;

		ConstIterator End() const;
		T& operator[](IndexT index) const;
	protected:
		void grow();
		void free();
		void alloc(SizeT s);

		T* elements;
		SizeT count;
		SizeT capacity;
	private:
		static const SizeT MinGrowSize = 16;
		static const SizeT MaxGrowSize = 65536; // FIXME: big grow size needed for mesh tools


		DataCollection(DataCollection const &);
		DataCollection & operator=(DataCollection const &);
		void operator==( DataCollection const& ) const;
		void operator!=( DataCollection const& ) const;
	};

	template<typename T>
	DataCollection<T>::DataCollection()
		: count(0)
		, capacity(0)
		, elements(NULL)
	{
	}
	template<typename T>
	DataCollection<T>::DataCollection(SizeT bufferSize)
		: count(0)
		, elements(NULL) 
	{
		alloc(bufferSize);
	}

	template<typename T>
	DataCollection<T>::~DataCollection()
	{
		this->free();
		this->count = 0;
	}

	template<typename T>
	void DataCollection<T>::Clear()
	{
		this->count = 0;
	}

	template<typename T>
	void DataCollection<T>::ClearWithBuffer()
	{
		this->free();
		this->count = 0;
	}

	template<typename T>
	SizeT DataCollection<T>::Count() const
	{
		return this->count;
	}

	template<typename T>
	typename 
		DataCollection<T>::ValueType& DataCollection<T>::PushBack()
	{
		if (this->count >= this->capacity)
		{
			this->grow();
		}
		SizeT index = this->count;
		++(this->count);
		return this->elements[index];
	}

	template<typename T>
	void DataCollection<T>::PushBack(const ValueType& value)
	{
		if (this->count >= this->capacity)
		{
			grow();
		}
		this->elements[this->count] = value;
		++(this->count);
	}
	template<typename T>	
	void DataCollection<T>::Pop()
	{
		n_assert(0 < this->count);
		--this->count;
	}

	template<class T>
	void DataCollection<T>::Resize(SizeT newSize)
	{
		// allocate new array and copy over old elements
		T* newElements = 0;
		if (newSize > 0)
		{
			newElements = n_new_array(T, newSize);
			SizeT numCopy = (this->capacity < newSize) ? this->capacity : newSize;
			Memory::Copy(this->elements, newElements, numCopy * sizeof(T));
		}

		// delete old elements
		this->free();

		// set content to new elements
		this->elements = newElements;
		this->capacity = newSize;
	}

	template<typename T>
	void DataCollection<T>::grow()
	{			
		SizeT growBy = capacity >> 1;
		if (0 == growBy)
		{
			growBy = MinGrowSize;
		}
		else if (growBy > MaxGrowSize)
		{
			growBy = MaxGrowSize;
		}
		Resize(growBy + capacity);
	}

	template<class T> 
	void DataCollection<T>::free()
	{
		if (this->elements)
		{
			n_delete_array(this->elements);
			this->elements = NULL;
		}
		this->capacity = 0;
	}

	template<class T> 
	void DataCollection<T>::alloc(SizeT s)
	{
		n_assert(0 == this->elements) 
			if (s > 0)
			{
				this->elements = n_new_array(T, s);
			}
			this->capacity = s;
	}

	template<typename T>
	typename 
		DataCollection<T>::Iterator DataCollection<T>::Begin()
	{
		return elements;
	}
	template<typename T>
	typename 
		DataCollection<T>::Iterator DataCollection<T>::End()
	{
		return elements + this->count;
	}
	template<typename T>
	typename 
		DataCollection<T>::ConstIterator DataCollection<T>::Back() const
	{
		if (this->count)
		{
			return elements + (this->count - 1);
		}
		else
		{
			return NULL;
		}
	}

	template<typename T>
	typename 
		DataCollection<T>::ConstIterator DataCollection<T>::Begin() const
	{
		return elements;
	}
	template<typename T>
	typename 
		DataCollection<T>::ConstIterator DataCollection<T>::End() const
	{
		return elements + this->count;
	}
	template<typename T>

	T& DataCollection<T>::operator[](IndexT index) const
	{
		return elements[index];
	}
}


#endif //_DATAMANAGER_H_