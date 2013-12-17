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

#ifndef __FOUNDATION_SCOPED_PTR_H__
#define __FOUNDATION_SCOPED_PTR_H__

//  scoped_ptr mimics a built-in pointer except that it guarantees deletion
//  of the object pointed to, either on destruction of the scoped_ptr or via
//  an explicit reset(). scoped_ptr is a simple solution for simple needs;
//  use shared_ptr or std::auto_ptr if your needs are more complex.

#include "core/debug.h"				// - for n_assert
#include "memory/memory.h"			// - for check_delete 


	template<typename T> 
	class ScopedPtr // noncopyable
	{
	public:

		typedef T element_type;

		explicit ScopedPtr( T* p = 0 )
			: px( p ) 
		{
			// empty
		}

		~ScopedPtr()
		{
			checked_ndelete( px );
		}

		void reset(T* p = 0) 
		{			
			n_assert( p == 0 || p != px ); // catch self-reset errors
			this_type(p).swap(*this);
		}

		T& operator*() const 
		{
			n_assert( px != 0 );
			return *px;
		}

		T* operator->() const 
		{
			n_assert( px != 0 );
			return px;
		}

		T* get() const 
		{
			return px;
		}

		void swap(ScopedPtr & b)
		{
			T* tmp = b.px;
			b.px = px;
			px = tmp;
		}
	private:

		T* px;

		ScopedPtr(ScopedPtr const &);
		ScopedPtr & operator=(ScopedPtr const &);

		typedef ScopedPtr<T> this_type;

		void operator==( ScopedPtr const& ) const;
		void operator!=( ScopedPtr const& ) const;
	};


	template<typename Type>
	inline void ResetScopedPtrWithDefualtObject(ScopedPtr<Type>& scopedPtr)
	{
		scopedPtr.reset(n_new(Type));
	}

#endif // __FOUNDATION_SCOPED_PTR_H__
