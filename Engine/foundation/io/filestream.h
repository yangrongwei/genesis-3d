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
    @class IO::FileStream
  
    A stream to which offers read/write access to filesystem files.
*/
#include "io/stream.h"
#include "util/string.h"
#include "io/filetime.h"
#include "io/fswrapper.h"

//------------------------------------------------------------------------------
namespace IO
{
class FileStream : public Stream
{
    __DeclareClass(FileStream);
public:
    /// constructor
    FileStream();
    /// destructor
    virtual ~FileStream();
    /// supports reading?
    virtual bool CanRead() const;
    /// supports writing?
    virtual bool CanWrite() const;
    /// supports seeking?
    virtual bool CanSeek() const;
    /// supports memory mapping (read-only)?
    virtual bool CanBeMapped() const;
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
    /// flush unsaved data
    virtual void Flush();
    /// return true if end-of-stream reached
    virtual bool Eof() const;
    /// map stream to memory
    virtual void* Map();
    /// unmap stream
    virtual void Unmap();
	virtual bool IsHeader( void* headPtr, Size numBytes ) ;

private:
    FSWrapper::Handle handle;
    void* mappedContent;
};

} // namespace IO
//------------------------------------------------------------------------------
