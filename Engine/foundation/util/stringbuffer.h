#pragma once
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

#include "core/types.h"
#include "util/array.h"

//------------------------------------------------------------------------------
namespace Util
{
class StringBuffer
{
public:
    /// constructor
    StringBuffer();
    /// destructor
    ~StringBuffer();
    
    /// setup the string buffer with size in bytes
    void Setup(SizeT size);
    /// discard the string buffer
    void Discard();
    /// return true if string buffer has been setup
    bool IsValid() const;

    /// add a string to the end of the string buffer, return pointer to string
    const char* AddString(const char* str);
    /// DEBUG: return next string in string buffer
    const char* NextString(const char* prev);
    /// DEBUG: get number of allocated chunks
    SizeT GetNumChunks() const;

private:
    /// allocate a new chunk
    void AllocNewChunk();

    Util::Array<char*> chunks;
    SizeT chunkSize;    
    char* curPointer;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
StringBuffer::IsValid() const
{
    return (0 != this->curPointer);
}

//------------------------------------------------------------------------------
/**
*/
inline SizeT
StringBuffer::GetNumChunks() const
{
    return this->chunks.Size();
}

} // namespace Util;
//------------------------------------------------------------------------------
