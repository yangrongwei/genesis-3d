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
    @class Win360::Win360MemoryPool
    
    A simple thread-safe memory pool. Memory pool items are 16-byte aligned.
    
    FIXME:
    - debug: overwrite memory blocks with pattern 
    - debug: check for double-free
    - debug: check for mem-leaks
    - debug: list memory pools in Debug HTML page!

*/
#include "core/types.h"
#include "threading/criticalsection.h"

//------------------------------------------------------------------------------
namespace Win360
{
class Win360MemoryPool
{
public:
    /// constructor
    Win360MemoryPool();
    /// destructor
    ~Win360MemoryPool();
    /// compute the actual block size including alignment and management data
    static uint ComputeAlignedBlockSize(uint blockSize);
    /// setup the memory pool
    void Setup(Memory::HeapType heapType, uint blockSize, uint numBlocks);
    /// allocate a block from the pool (NOTE: returns 0 if pool exhausted!)
    void* Alloc();
    /// deallocate a block from the pool
    void Free(void* ptr);
    /// return true if block is owned by this pool
    bool IsPoolBlock(void* ptr) const;
    /// get number of allocated blocks in pool
    uint GetNumBlocks() const;
    /// get block size
    uint GetBlockSize() const;
    /// get aligned block size
    uint GetAlignedBlockSize() const;
    /// get pool size
    uint GetPoolSize() const;
    /// get current allocation count
    #if NEBULA3_MEMORY_STATS
    uint GetAllocCount() const;
    #endif

private:
    static const uint FreeBlockPattern = 0xFE;
    static const uint NewBlockPattern = 0xFD;
    static const int  BlockAlign = 16;

    Memory::HeapType heapType;
    uint blockSize;
    uint alignedBlockSize;
    uint poolSize;
    uint numBlocks;
    #if NEBULA3_MEMORY_STATS
    volatile long allocCount;
    #endif
    
    SLIST_HEADER listHead;
    ubyte* poolStart;       // first valid block header is at poolStart + (align - sizeof(SLIST_ENTRY))
    ubyte* poolEnd;
};

//------------------------------------------------------------------------------
/**
*/
#if NEBULA3_MEMORY_STATS
inline uint
Win360MemoryPool::GetAllocCount() const
{
    return this->allocCount;
}
#endif

//------------------------------------------------------------------------------
/**
*/
inline uint
Win360MemoryPool::ComputeAlignedBlockSize(uint blockSize)
{
    uint blockSizeWithHeader = blockSize + sizeof(PSLIST_ENTRY);
    uint padding = (BlockAlign - (blockSizeWithHeader % BlockAlign)) % BlockAlign;
    return (blockSizeWithHeader + padding);
}

//------------------------------------------------------------------------------
/**
*/
inline uint
Win360MemoryPool::GetNumBlocks() const
{
    return this->numBlocks;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
Win360MemoryPool::GetBlockSize() const
{
    return this->blockSize;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
Win360MemoryPool::GetAlignedBlockSize() const
{
    return this->alignedBlockSize;
}

//------------------------------------------------------------------------------
/**
*/
inline uint
Win360MemoryPool::GetPoolSize() const
{
    return this->poolSize;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Win360MemoryPool::IsPoolBlock(void* ptr) const
{
    return (ptr >= this->poolStart) && (ptr < this->poolEnd);
}

} // namespace Win360
//------------------------------------------------------------------------------
    