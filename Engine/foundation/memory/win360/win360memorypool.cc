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

#if WIN32


#include "stdneb.h"
#include "memory/win360/win360memorypool.h"
#include "util/string.h"

namespace Win360
{
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
Win360MemoryPool::Win360MemoryPool() :
    heapType(Memory::InvalidHeapType),
    blockSize(0),
    alignedBlockSize(0),
    poolSize(0),
    numBlocks(0),
    #if NEBULA3_MEMORY_STATS
    allocCount(0),
    #endif
    poolStart(0),
    poolEnd(0)
{
    Memory::Clear(&this->listHead, sizeof(this->listHead));
}

//------------------------------------------------------------------------------
/**
*/
Win360MemoryPool::~Win360MemoryPool()
{
    #if NEBULA3_MEMORY_STATS
    if (this->allocCount != 0)
    {
        String str;
        str.Format("Win360MemoryPool: %d memory leaks in pool '0x%08x'!\n", this->allocCount, (uint)this);
        Core::SysFunc::DebugOut(str.AsCharPtr());
    }
    #endif

    // discard memory pool
    Memory::Free(this->heapType, this->poolStart);
    this->poolStart = 0;
    this->poolEnd = 0;
}

//------------------------------------------------------------------------------
/**
    NOTE: name must be a static string!
*/
void
Win360MemoryPool::Setup(Memory::HeapType heapType_, uint blockSize_, uint numBlocks_)
{
    n_assert(0 == this->poolStart);
    n_assert(0 == this->poolEnd);
    this->blockSize = blockSize_;
    this->numBlocks = numBlocks_;
    this->heapType = heapType_;

    #if NEBULA3_MEMORY_STATS
    this->allocCount = 0;
    #endif

    // compute block size with sizeof(*) header
    this->alignedBlockSize = ComputeAlignedBlockSize(this->blockSize);
    this->poolSize = (this->numBlocks * this->alignedBlockSize) + BlockAlign;

    // setup pool memory block, each entry in the block has a header
    // with a pointer to the next block, the actual start of the memory block
    // is 16-byte-aligned
    this->poolStart = (ubyte*) Memory::Alloc(this->heapType, this->poolSize);
    this->poolEnd = this->poolStart + this->poolSize;
    
    // setup forward-linked free-block-list
    Memory::Clear(&this->listHead, sizeof(listHead));
    PSLIST_ENTRY listEntry = (PSLIST_ENTRY) (this->poolStart + (BlockAlign - sizeof(SLIST_ENTRY)));
    uint i;
    for (i = 0; i < this->numBlocks; i++)
    {
        InterlockedPushEntrySList(&this->listHead, listEntry);
        listEntry += this->alignedBlockSize / sizeof(SLIST_ENTRY);
    }
}

//------------------------------------------------------------------------------
/**
*/
void*
Win360MemoryPool::Alloc()
{
    #if NEBULA3_MEMORY_STATS
    _InterlockedIncrement(&this->allocCount);
    #endif
    // get the next free block from the free list and fixup the free list
    PSLIST_ENTRY entry = InterlockedPopEntrySList(&this->listHead);
    if (0 == entry)
    {
        return 0;
    }
    void* ptr = (void*) (((ubyte*)entry) + sizeof(SLIST_ENTRY));

    // fill with debug pattern
    #if NEBULA3_DEBUG
    Memory::Fill(ptr, this->blockSize, NewBlockPattern);
    #endif

    return ptr;
}

//------------------------------------------------------------------------------
/**
*/
void
Win360MemoryPool::Free(void* ptr)
{
    #if NEBULA3_MEMORY_STATS
    n_assert(this->allocCount > 0);
    _InterlockedDecrement(&this->allocCount);
    #endif
    // get pointer to header and fixup free list
    PSLIST_ENTRY entry = (PSLIST_ENTRY) (((ubyte*)ptr) - sizeof(SLIST_ENTRY));
    InterlockedPushEntrySList(&this->listHead, entry);

    // fill free'd block with debug pattern
    #if NEBULA3_DEBUG
    Memory::Fill(ptr, this->blockSize, FreeBlockPattern);
    #endif
}

} // namespace Win360


#endif