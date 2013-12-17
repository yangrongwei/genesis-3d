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

#include "core/config.h"

namespace Memory
{
    
//------------------------------------------------------------------------------
/**
    Heap types are defined here. The main purpose for the different heap
    types is to decrease memory fragmentation and to improve cache
    usage by grouping similar data together. Platform ports may define
    platform-specific heap types, as long as only platform specific
    code uses those new heap types.
*/
enum HeapType
{
    DefaultHeap = 0,            // for stuff that doesn't fit into any category
    ObjectHeap,                 // standard heap for C++ objects
    ObjectArrayHeap,            // for objects that use the array new/delete operator
    ResourceHeap,               // heap for resource data (like animation buffers)
    ScratchHeap,                // for short-lived scratch memory (encode/decode buffers, etc...)
    StringDataHeap,             // special heap for string data
    StreamDataHeap,             // special heap for stream data like memory streams, zip file streams, etc...
    PhysicsHeap,                // physics engine allocations go here
    AppHeap,                    // for general Application layer stuff
    
    NumHeapTypes,
    InvalidHeapType,
};
    
//------------------------------------------------------------------------------
/**
    Heap pointers are defined here. Call ValidateHeap() to check whether
    a heap already has been setup, and to setup the heap if not.
*/
extern malloc_zone_t* Heaps[NumHeapTypes];

//------------------------------------------------------------------------------
/**
    This method is called by SysFunc::Setup() to setup the different heap
    types. This method can be tuned to define the start size of the 
    heaps and whether the heap may grow or not (non-growing heaps may
    be especially useful on console platforms without memory paging).
*/
extern void SetupHeaps();

//------------------------------------------------------------------------------
/**
    Returns a human readable name for a heap type.
*/
extern const char* GetHeapTypeName(HeapType heapType);
    
} // namespace Memory    
//------------------------------------------------------------------------------
