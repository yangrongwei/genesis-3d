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
#include "memory/android/androidmemoryconfig.h"

namespace Memory
{
void* Heaps[NumHeapTypes];

//------------------------------------------------------------------------------
/**
    Setup the global heaps.
*/

void SetupHeaps()
{
	const size_t megaByte = 1024 * 1024;
	unsigned int i;
	for (i = 0; i < NumHeapTypes; i++)
	{
		size_t startSize = 0;
		switch (i)
		{
		case DefaultHeap:       startSize = 2 * megaByte; break;
		case ObjectHeap:        startSize = 32 * megaByte; break;
		case ObjectArrayHeap:   startSize = 64 * megaByte; break;
		case ResourceHeap:      startSize = 8 * megaByte; break;
		case ScratchHeap:       startSize = 4 * megaByte; break;
		case StringDataHeap:    startSize = 1 * megaByte; break;
		case StreamDataHeap:    startSize = 32 * megaByte; break;
		case PhysicsHeap:       startSize = 1 * megaByte; break;
		case AppHeap:           startSize = 1 * megaByte; break;

		default:
			break;
		}

	}
}

//------------------------------------------------------------------------------
/**
*/
const char*
	GetHeapTypeName(HeapType heapType)
{
	switch (heapType)
	{
	case DefaultHeap:               return "Default Heap";
	case ObjectHeap:                return "Object Heap";
	case ObjectArrayHeap:           return "Object Array Heap";
	case ResourceHeap:              return "Resource Heap";
	case ScratchHeap:               return "Scratch Heap";
	case StringDataHeap:            return "String Data Heap";
	case StreamDataHeap:            return "Stream Data Heap";
	case PhysicsHeap:               return "Physics Heap";
	case AppHeap:                   return "App Heap";

	default:
		return 0;
	}
}

}
