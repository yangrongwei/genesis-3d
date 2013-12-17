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
#include "io/filestream.h"

namespace IO
{
__ImplementClass(IO::FileStream, 'FSTR', IO::Stream);

using namespace Util;
using namespace Core;

//------------------------------------------------------------------------------
/**
*/
FileStream::FileStream() :
    handle(0),
    mappedContent(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
FileStream::~FileStream()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**
*/
bool
FileStream::CanRead() const
{
    return true;
}

//------------------------------------------------------------------------------
/**
*/
bool
FileStream::CanWrite() const
{
    return true;
}

//------------------------------------------------------------------------------
/**
*/
bool
FileStream::CanSeek() const
{
    return true;
}

//------------------------------------------------------------------------------
/**
    FileStreams support mapping (only read access for now).
*/
bool
FileStream::CanBeMapped() const
{
    return true;
}

//------------------------------------------------------------------------------
/**
*/
Stream::Size
FileStream::GetSize() const
{
    n_assert(0 != this->handle);
    return FSWrapper::GetFileSize(this->handle);
}

//------------------------------------------------------------------------------
/**
*/
Stream::Position
FileStream::GetPosition() const
{
    n_assert(0 != this->handle);
    return FSWrapper::Tell(this->handle);
}

//------------------------------------------------------------------------------
/**
*/
bool
FileStream::Open()
{
    n_assert(!this->IsOpen());
    n_assert(0 == this->handle);
    n_assert(this->uri.Scheme() == "file");
    n_assert(this->uri.LocalPath().IsValid());
    if (Stream::Open())
    {
        this->handle = FSWrapper::OpenFile(this->uri.GetHostAndLocalPath(), this->accessMode, this->accessPattern);
        if (0 != this->handle)
        {
            return true;
        }
    }

    // fallthrough: failure
    Stream::Close();
    return false;
}

//------------------------------------------------------------------------------
/**
*/
void
FileStream::Close()
{
    n_assert(this->IsOpen());
    n_assert(0 != this->handle);
    if (this->IsMapped())
    {
        this->Unmap();
    }
    FSWrapper::CloseFile(this->handle);
    this->handle = 0;
    Stream::Close();
}

//------------------------------------------------------------------------------
/**
*/
void
FileStream::Write(const void* ptr, Size numBytes)
{
    n_assert(!this->IsMapped());
    if (numBytes > 0)
    {
        n_assert(this->IsOpen());
        n_assert(0 != this->handle);
        n_assert(0 != ptr);
        FSWrapper::Write(this->handle, ptr, numBytes);
    }
}

//------------------------------------------------------------------------------
/**
*/
Stream::Size
FileStream::Read(void* ptr, Size numBytes)
{
    n_assert(!this->IsMapped());
    n_assert(this->IsOpen());
    n_assert(0 != this->handle);
    n_assert(0 != ptr);
	
	if ( numBytes == 0 )
		return 0;

	return FSWrapper::Read(this->handle, ptr, numBytes);
}

//------------------------------------------------------------------------------
/**
*/
void
FileStream::Seek(Offset offset, SeekOrigin origin)
{
    n_assert(!this->IsMapped());
    n_assert(this->IsOpen());
    n_assert(0 != this->handle);
    FSWrapper::Seek(this->handle, offset, origin);
}

//------------------------------------------------------------------------------
/**
*/
void
FileStream::Flush()
{
    n_assert(!this->IsMapped());
    n_assert(this->IsOpen());
    n_assert(0 != this->handle);
    FSWrapper::Flush(this->handle);
}

//------------------------------------------------------------------------------
/**
*/
bool
FileStream::Eof() const
{
    n_assert(!this->IsMapped());
    n_assert(this->IsOpen());
    n_assert(0 != this->handle);
    return FSWrapper::Eof(this->handle);
}

//------------------------------------------------------------------------------
/**
*/
void*
FileStream::Map()
{
    n_assert(0 == this->mappedContent);
    
    Size size = this->GetSize();
    n_assert(size > 0);
    this->mappedContent = Memory::Alloc(Memory::ScratchHeap, size);
    this->Seek(0, Begin);
    Size readSize = this->Read(this->mappedContent, size);
    n_assert(readSize == size);
    Stream::Map();
    return this->mappedContent;
}

//------------------------------------------------------------------------------
/**
*/
void
FileStream::Unmap()
{
    n_assert(0 != this->mappedContent);
    Stream::Unmap();
    Memory::Free(Memory::ScratchHeap, this->mappedContent);
    this->mappedContent = 0;
}

bool
	FileStream::IsHeader( void* headPtr, Size numBytes ) 
{
	static char buff[100] = {0};
	memset(buff,0,sizeof(buff));
	n_assert(sizeof(buff) >= numBytes);
	
	Read(buff,numBytes);
	Seek(0,Stream::Begin);
	bool b = (0 == memcmp(buff,headPtr,numBytes));
	
	return b;
}

} // namespace IO
