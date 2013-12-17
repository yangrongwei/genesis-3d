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
#ifndef __ANDROIDHEAP_H__
#define __ANDROIDHEAP_H__
#include "core/types.h"
#include "util/array.h"
#include "util/list.h"

namespace Android
{
	class AndroidHeap
{
public:
	/// static setup method (called by Core::SysFunc::Setup)
	static void Setup();
	/// constructor (name must be a static string!) 
	AndroidHeap(const char* name, size_t initialSize=64 * 1024);
	/// destructor
	~AndroidHeap();
	/// get heap name
	const char* GetName() const;
	/// allocate a block of memory from the heap
	void* Alloc(size_t size, size_t alignment=16);
	/// re-allocate a block of memory
	void* Realloc(void* ptr, size_t newSize);
	/// free a block of memory
	void Free(void* ptr);


	struct Stats
	{
		const char* name;
		int allocCount;
		int allocSize;
	};
	/// gather stats from all existing heaps
	static Util::Array<Stats> GetAllHeapStats();
private:
	/// default constructor not allowed
	AndroidHeap();

	const char* name;
	void*       heapZone;	
};

//------------------------------------------------------------------------------
/**
 */
inline const char*
AndroidHeap::GetName() const
{
    n_assert(0 != this->name);
    return this->name;
}

}

#endif