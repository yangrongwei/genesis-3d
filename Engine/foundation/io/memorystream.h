/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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
    @class IO::MemoryStream
    
    Implements a stream class which writes to and reads from system RAM. 
    Memory streams provide memory mapping for fast direct read/write access.
*/
#include "io/stream.h"

//------------------------------------------------------------------------------
namespace IO
{
class MemoryStream : public Stream
{
    __DeclareClass(MemoryStream);
public:
    /// constructor
    MemoryStream();
    /// destructor
    virtual ~MemoryStream();
    /// memory streams support reading
    virtual bool CanRead() const;
    /// memory streams support writing
    virtual bool CanWrite() const;
    /// memory streams support seeking
    virtual bool CanSeek() const;
    /// memory streams are mappable
    virtual bool CanBeMapped() const;
    /// set new size of the stream in bytes
    virtual void SetSize(Size s);
    /// get the size of the stream in bytes
    virtual Size GetSize() const;
    /// get the current position of the read/write cursor
    virtual Position GetPosition() const;
    /// open the stream
    virtual bool Open();
    /// close the stream
    virtual void Close();
    /// directly write to the stream
    virtual void Write(const void* ptr, Size numBytes);
    /// directly read from the stream
    virtual Size Read(void* ptr, Size numBytes);
    /// seek in stream
    virtual void Seek(Offset offset, SeekOrigin origin);
    /// return true if end-of-stream reached
    virtual bool Eof() const;
    /// map for direct memory-access
    virtual void* Map();
    /// unmap a mapped stream
    virtual void Unmap();
	/// copy data to memory 
	virtual Size Copy( void* ptr, Size numBytes )const;
    /// get a direct "raw" pointer to the data
    void* GetRawPointer() const;
	virtual bool IsHeader( void* headPtr, Size numBytes );

private:
    /// re-allocate the memory buffer
    void Realloc(Size s);
    /// return true if there's enough space for n more bytes
    bool HasRoom(Size numBytes) const;
    /// make room for at least n more bytes
    void MakeRoom(Size numBytes);

    static const Size InitialSize = 256;
    Size capacity;
    Size size;
    Position position;
    unsigned char* buffer;
};

} // namespace IO
//------------------------------------------------------------------------------
