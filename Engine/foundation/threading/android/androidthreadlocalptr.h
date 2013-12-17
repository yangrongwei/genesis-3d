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

#ifndef __ANDROIDTHREADLOCALPTR_H__
#define __ANDROIDTHREADLOCALPTR_H__


#include "core/types.h"

//------------------------------------------------------------------------------
namespace Android
{
	template<typename TYPE>
	class AndroidThreadLocalPtr
	{
	public:
		/// default constructor
		AndroidThreadLocalPtr();
		/// destructor
		~AndroidThreadLocalPtr();
		/// set content
		void set(TYPE* p);
		/// get content
		TYPE* get() const;
		/// test if content is valid
		bool isvalid() const;
	private:
		pthread_key_t key;
	};

	//------------------------------------------------------------------------------
	/**
	*/
	template<typename TYPE>
	AndroidThreadLocalPtr<TYPE>::AndroidThreadLocalPtr() :
	key(0)
	{
		int res = pthread_key_create(&this->key, NULL);
		n_assert(0 == res);
		pthread_setspecific(this->key, 0);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	template<typename TYPE>
	AndroidThreadLocalPtr<TYPE>::~AndroidThreadLocalPtr()
	{
		int res = pthread_key_delete(this->key);
		n_assert(0 == res);
		this->key = 0;
	}

	//------------------------------------------------------------------------------
	/**
	*/
	template<typename TYPE> void
		AndroidThreadLocalPtr<TYPE>::set(TYPE* p)
	{
		pthread_setspecific(this->key, p);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	template<typename TYPE> TYPE*
		AndroidThreadLocalPtr<TYPE>::get() const
	{
		return (TYPE*) pthread_getspecific(this->key);
	}

	//------------------------------------------------------------------------------
	/**
	*/
	template<typename TYPE> bool
		AndroidThreadLocalPtr<TYPE>::isvalid() const
	{
		return (0 != pthread_getspecific(this->key));
	}

} // namespace OSX

#endif