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
#ifndef IO_STREAM_H
#define IO_STREAM_H
//------------------------------------------------------------------------------
/**
    @class IO::Stream
    
    Offers an abstract interface for read/write access to a sequence of bytes.
    Base class for all classes which need to provide a read/write interface
    to data, like a FileStream, a MemoryStream, etc...
    
    Stream objects can be accessed directly, or through stream reader and
    writer classes, which offer specific read/writing interfaces to streams.
*/
#include "core/refcounted.h"
#include "io/uri.h"
#include "threading/criticalsection.h"
#include "io/mediatype.h"

//------------------------------------------------------------------------------
namespace IO
{
	// - forward declare 
	class Stream;
	typedef GPtr<Stream> TStreamPtr;

class Stream : public Core::RefCounted
{
    __DeclareClass(Stream);
public:
    /// typedefs
    typedef int Position;       // DON'T DEFINE AS UNSIGNED!
    typedef int Offset;         // DON'T DEFINE AS UNSIGNED!
    typedef int Size;           // DON'T DEFINE AS UNSIGNED!

    /// access modes
    enum AccessMode
    {
        ReadAccess,
        WriteAccess,
        AppendAccess,
        ReadWriteAccess,
    };

    /// access prefered pattern
    enum AccessPattern
    {
        Random,
        Sequential,
    };

    /// seek origins
    enum SeekOrigin
    {
        Begin,
        Current,
        End,
    };
    /// constructor
    Stream();
    /// destructor
    virtual ~Stream();
    /// set stream location as URI
    void SetURI(const URI& u);
    /// get stream URI
    const URI& GetURI() const;
    /// return true if the stream supports reading
    virtual bool CanRead() const;
    /// return true if the stream supports writing
    virtual bool CanWrite() const;
    /// return true if the stream supports seeking
    virtual bool CanSeek() const;
    /// return true if the stream provides direct memory access
    virtual bool CanBeMapped() const;
    /// set a new size for the stream
    virtual void SetSize(Size s);
    /// get the size of the stream in bytes
    virtual Size GetSize() const;
    /// get the current position of the read/write cursor
    virtual Position GetPosition() const;
    /// set the access mode of the stream (default is ReadAccess)
    void SetAccessMode(AccessMode m);
    /// get the access mode of the stream
    AccessMode GetAccessMode() const;
    /// set the prefered access pattern (default is Sequential)
    void SetAccessPattern(AccessPattern p);
    /// get the prefered access pattern
    AccessPattern GetAccessPattern() const;
    /// set optional media type of stream content
    void SetMediaType(const MediaType& t);
    /// get optional media type
    const MediaType& GetMediaType() const;
    /// open the stream
    virtual bool Open();
    /// close the stream
    virtual void Close();
    /// return true if currently open
    bool IsOpen() const;
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
	/// copy data to memory 
	virtual Size Copy( void* ptr, Size numBytes )const;
    /// return true if stream is currently mapped to memory
    bool IsMapped() const;
	/// return true if stream header is the same to headerPtr
	virtual bool IsHeader( void* headPtr, Size numBytes );
        
protected:
    URI uri;
    AccessMode accessMode;
    AccessPattern accessPattern;
    bool isOpen;
    bool isMapped;
    MediaType mediaType;
};

} // namespace IO
//------------------------------------------------------------------------------
#endif