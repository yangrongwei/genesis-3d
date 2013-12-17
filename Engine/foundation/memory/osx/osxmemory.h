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
#include "core/debug.h"
#include "memory/osx/osxmemoryconfig.h"

namespace Memory
{
extern int volatile TotalAllocCount;
extern int volatile TotalAllocSize;
extern int volatile HeapTypeAllocCount[NumHeapTypes];
extern int volatile HeapTypeAllocSize[NumHeapTypes];
extern bool volatile MemoryLoggingEnabled;
extern unsigned int volatile MemoryLoggingThreshold;
extern HeapType volatile MemoryLoogingHeapType;
    
//------------------------------------------------------------------------------
/**
    Global memory functions.
 */
/// allocate a chunk of memory
extern void* Alloc(HeapType heapType, size_t size, size_t alignment=16);
/// re-allocate a chunk of memory
extern void* Realloc(HeapType heapType, void* ptr, size_t size);
/// free a chunk of memory
extern void Free(HeapType heapType, void* ptr);
/// duplicate a C-string (obsolete)
extern char* DuplicateCString(const char* from);
/// check if 2 memory regions are overlapping
extern bool IsOverlapping(const unsigned char* srcPtr, size_t srcSize, const unsigned char* dstPtr, size_t dstSize);
/// copy a chunk of memory
extern void Copy(const void* from, void* to, size_t numBytes);
/// overwrite a chunk of memory with zero
extern void Clear(void* ptr, size_t numBytes);
/// fill memory with a specific byte
extern void Fill(void* ptr, size_t numBytes, unsigned char value);
///Copy data from a system memory buffer to graphics resource memory. Some platforms may need special handling of this case
extern void CopyToGraphicsMemory(const void* from, void* to, size_t numBytes);
//------------------------------------------------------------------------------
/**
    Get the system's total current memory, this does not only include
    Nebula3's memory allocations but the memory usage of the entire system.
*/
struct TotalMemoryStatus
{
    unsigned int totalPhysical;
    unsigned int availPhysical;
    unsigned int totalVirtual;
    unsigned int availVirtual;
};
extern TotalMemoryStatus GetTotalMemoryStatus();
    
//------------------------------------------------------------------------------
/**
    Debug and memory validation functions.
*/
#if NEBULA3_MEMORY_STATS
/// enable memory logging
void EnableMemoryLogging(unsigned int threshold, HeapType = InvalidHeapType);
/// disable memory logging
void DisableMemoryLogging();
/// toggle memory logging
void ToggleMemoryLogging(unsigned int threshold, HeapType = InvalidHeapType);
#endif
    
#if NEBULA3_MEMORY_ADVANCED_DEBUGGING
/// check memory lists for consistency
extern bool ValidateMemory();
/// dump current memory status to log file
extern void Checkpoint(const char* msg);
/// dump memory leaks
void DumpMemoryLeaks();
#endif
    
#if NEBULA3_MEMORY_ADVANCED_DEBUGGING
#define __MEMORY_CHECKPOINT(s) Memory::Checkpoint(##s)
#else
#define __MEMORY_CHECKPOINT(s)
#endif
    
    // FIXME: Memory-Validation disabled for now
#define __MEMORY_VALIDATE(s)
} // namespace Memory

#ifdef new
#undef new
#endif

#ifdef delete
#undef delete
#endif

//------------------------------------------------------------------------------
/**
 Replacement global new/delete operators.
 */
#ifndef __OSX__
extern void* operator new(size_t size);
extern void* operator new(size_t size, size_t align);

extern void* operator new[](size_t size);
extern void* operator new[](size_t size, size_t align);

extern void operator delete(void* p);
extern void operator delete[](void* p);
#endif


#define n_new(type) new type
#define n_new_array(type,size) new type[size]
#define n_delete(ptr) delete ptr
#define n_delete_array(ptr) delete[] ptr
//------------------------------------------------------------------------------


