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
#include "stdneb.h"
#include "memory/android/androidheap.h"

namespace Android
{
void AndroidHeap::Setup()
{

}

AndroidHeap::AndroidHeap(const char* heapName, size_t initialSize)
{
	n_assert(0 != heapName);
	this->name = heapName;
	this->heapZone = malloc(initialSize);
}

AndroidHeap::~AndroidHeap()
{
	free(this->heapZone);
	this->heapZone = NULL;
}

void* AndroidHeap::Alloc(size_t size, size_t alignment)
{
	void* allocPtr = malloc(size);

	return allocPtr;
}

void* AndroidHeap::Realloc(void* ptr, size_t newSize)
{
	void* allocPtr = realloc(ptr, newSize);

	return allocPtr;
}

void AndroidHeap::Free(void* ptr)
{
	free(this->heapZone);
}

Util::Array<AndroidHeap::Stats> AndroidHeap::GetAllHeapStats()
{
	//- TODO COMPLETE LATER
	Util::Array<AndroidHeap::Stats> result;

	Stats stats;
	stats.name       = "no android heap ";
	stats.allocCount = 0;
	stats.allocSize  = 0;        
	result.Append(stats);
	
	return result;
}

}