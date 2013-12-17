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
    @class IO::StreamWriter
  
    Stream writer classes provide a specialized write-interface for a stream.
    This is the abstract base class for all stream writers. It is possible
    to attach any number of readers and writers to the same stream.

*/
#include "core/refcounted.h"
#include "core/ptr.h"
#include "io/stream.h"

//------------------------------------------------------------------------------
namespace IO
{
class StreamWriter : public Core::RefCounted
{
    __DeclareClass(StreamWriter);
public:
    /// constructor
    StreamWriter();
    /// destructor
    virtual ~StreamWriter();
    /// set stream to write to
    void SetStream(const GPtr<Stream>& s);
    /// get currently set stream 
    const GPtr<Stream>& GetStream() const;
    /// return true if a stream is set
    bool HasStream() const;
    /// begin reading from the stream
    virtual bool Open();
    /// end reading from the stream
    virtual void Close();
    /// return true if currently open
    bool IsOpen() const;

protected:
    GPtr<Stream> stream;
    bool isOpen;
    bool streamWasOpen;
};

//------------------------------------------------------------------------------
/**
*/
inline
bool
StreamWriter::IsOpen() const
{
    return this->isOpen;
}

} // namespace IO
//------------------------------------------------------------------------------