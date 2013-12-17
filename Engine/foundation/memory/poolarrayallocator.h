/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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
//------------------------------------------------------------------------------
/**
    @class Memory::PoolArrayAllocator
  
    Allocates small memory blocks from an array of fixed-size memory pools.
    Bigger allocation go directly through to a heap. Note that when
    freeing a memory block, there are 2 options: one with providing
    the size of the memory block (which is probably a bit faster) and
    one conventional without providing the size.
*/
#include "memory/memorypool.h"

//------------------------------------------------------------------------------
namespace Memory
{
class PoolArrayAllocator
{
public:
    /// number of pools
    static const SizeT NumPools = 8;

    /// constructor
    PoolArrayAllocator();
    /// destructor
    ~PoolArrayAllocator();
    
    /// setup the pool allocator, name must be a static string!
    void Setup(const char* name, Memory::HeapType heapType, uint poolSizes[NumPools]);
    /// allocate a block of memory from the pool
    void* Alloc(SizeT size);
    /// free a block of memory from the pool array with original block size
    void Free(void* ptr, SizeT size);
    /// free a block of memory from the pool array
    void Free(void* ptr);
    /// access to memory pool at pool index (for debugging)
    const MemoryPool& GetMemoryPool(IndexT index) const;

    #if NEBULA3_MEMORY_STATS
    /// dump number of memory allocations (if > 0)
    void Dump();
    #endif

private:
    Memory::HeapType heapType;
    const char* name;
    MemoryPool memoryPools[NumPools];
};

} // namespace Memory
//------------------------------------------------------------------------------
