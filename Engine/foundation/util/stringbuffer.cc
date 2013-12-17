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

#include "stdneb.h"
#include "util/stringbuffer.h"

#include <string.h>

namespace Util
{

//------------------------------------------------------------------------------
/**
*/
StringBuffer::StringBuffer() :
    chunkSize(0), 
    curPointer(0)
{
    // empty
}    

//------------------------------------------------------------------------------
/**
*/
StringBuffer::~StringBuffer()
{
    if (this->IsValid())
    {
        this->Discard();
    }
}

//------------------------------------------------------------------------------
/**
    NOTE: this method must be called before any threads are spawned.
*/
void
StringBuffer::Setup(SizeT size)
{
    n_assert(!this->IsValid());
    n_assert(size > 0);
    this->chunkSize = size;    
    this->AllocNewChunk();
}

//------------------------------------------------------------------------------
/**
*/
void
StringBuffer::Discard()
{
    n_assert(this->IsValid());
    IndexT i;
    for (i = 0; i < this->chunks.Size(); i++)
    {
        Memory::Free(Memory::StringDataHeap, this->chunks[i]);
        this->chunks[i] = 0;
    }
    this->chunks.Clear();
    this->chunkSize = 0;
    this->curPointer = 0;
}

//------------------------------------------------------------------------------
/**
*/
void
StringBuffer::AllocNewChunk()
{
    char* newChunk = (char*) Memory::Alloc(Memory::StringDataHeap, this->chunkSize);
    this->chunks.Append(newChunk);
    this->curPointer = newChunk;
}

//------------------------------------------------------------------------------
/**
    Copies a string to the end of the string buffer, returns pointer to
    copied string.
*/
const char*
StringBuffer::AddString(const char* str)
{
    n_assert(0 != str);
    n_assert(this->IsValid());

    // get string length, must be less then chunk size
    SizeT strLength = strlen(str) + 1;
    n_assert(strLength < this->chunkSize);

    // check if a new buffer must be allocated
    if ((this->curPointer + strLength) >= (this->chunks.Back() + this->chunkSize))
    {
        #if NEBULA3_ENABLE_GLOBAL_STRINGBUFFER_GROWTH
        this->AllocNewChunk();
        #else
        n_error("String buffer full when adding string '%s' (string buffer growth is disabled)!\n", str);
        #endif
    }

    // copy string into string buffer
    char* dstPointer = this->curPointer;
    strcpy(dstPointer, str);
    this->curPointer += strLength;
    return dstPointer;
}

} // namespace Util
