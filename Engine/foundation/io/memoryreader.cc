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
#include "stdneb.h"
#include "io/memoryreader.h"
#include "math/scalar.h"
namespace IO
{
__ImplementClass(IO::MemoryReader, 'MMRD', IO::Stream);

//------------------------------------------------------------------------------
/**
*/
MemoryReader::MemoryReader() :
    capacity(0),
    size(0),
    position(0),
    buffer(NULL)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
MemoryReader::~MemoryReader()
{
    // close the stream if still open
    if (this->IsOpen())
    {
        this->Close();
    }

    // release memory buffer if allocated
    if ( NULL != this->buffer)
        this->buffer = NULL;

}
//------------------------------------------------------------------------------
Stream::Size
MemoryReader::GetSize() const
{
    return this->size;
}
//------------------------------------------------------------------------------
Stream::Position
MemoryReader::GetPosition() const
{
    return this->position;
}
//------------------------------------------------------------------------------
bool MemoryReader::Open()
{
    n_assert(!this->IsOpen());
    
    // nothing to do here, allocation happens in the first Write() call
    // if necessary, all we do is reset the read/write position to the
    // beginning of the stream
    if (Stream::Open())
    {
		this->position = 0;
        return true;
    }
    return false;
}

//------------------------------------------------------------------------------
/**
    Close the stream. The contents of the stream will remain intact until
    destruction of the object, so that the same data may be accessed 
    or modified during a later session. 
*/
void
MemoryReader::Close()
{
    n_assert(this->IsOpen());
    Stream::Close();
}

//------------------------------------------------------------------------------
/**
*/
void
MemoryReader::Write(const void* ptr, Size numBytes)
{
    n_assert(this->IsOpen());
    n_assert(ReadWriteAccess == this->accessMode);
    n_assert((this->position >= 0) && (this->position <= this->size));

	buffer = (unsigned char*)ptr;
	size = numBytes;
	capacity = numBytes;

    this->position += numBytes;
    if (this->position > this->size)
    {
        this->size = this->position;
    }
}

//------------------------------------------------------------------------------
/**
*/
Stream::Size
MemoryReader::Read(void* ptr, Size numBytes)
{
    n_assert(this->IsOpen());
    n_assert((ReadWriteAccess == this->accessMode))
    n_assert((this->position >= 0) && (this->position <= this->size));

    // check if end-of-stream is near
    Size readBytes = numBytes <= this->size - this->position ? numBytes : this->size - this->position;
    n_assert((this->position + readBytes) <= this->size);
    if (readBytes > 0)
    {
        Memory::Copy(this->buffer + this->position, ptr, readBytes);
        this->position += readBytes;
    }
    return readBytes;
}

//------------------------------------------------------------------------------
/**
*/
void
MemoryReader::Seek(Offset offset, SeekOrigin origin)
{
    n_assert(this->IsOpen());
    n_assert(!this->IsMapped()); 
    n_assert((this->position >= 0) && (this->position <= this->size));
    switch (origin)
    {
        case Begin:
            this->position = offset;
            break;
        case Current:
            this->position += offset;
            break;
        case End:
            this->position = this->size + offset;
            break;
    }

    // make sure read/write position doesn't become invalid
    this->position = Math::n_iclamp(this->position, 0, this->size);
}

//------------------------------------------------------------------------------
/**
*/
bool
MemoryReader::Eof() const
{
    n_assert(this->IsOpen());
    n_assert((this->position >= 0) && (this->position <= this->size));
    return (this->position == this->size);
}

//------------------------------------------------------------------------------
/**
*/
bool
MemoryReader::HasRoom(Size numBytes) const
{
    return ((this->position + numBytes) <= this->capacity);
}
//------------------------------------------------------------------------------
/**
    Get a direct pointer to the raw data. This is a convenience method
    and only works for memory streams.
    NOTE: writing new data to the stream may/will result in an invalid
    pointer, don't keep the returned pointer around between writes!
*/
void*
MemoryReader::GetRawPointer() const
{
    n_assert( NULL != this->buffer );
    return this->buffer;
}

} // namespace IO
