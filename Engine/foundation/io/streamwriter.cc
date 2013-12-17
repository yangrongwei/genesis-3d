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
#include "io/streamwriter.h"

namespace IO
{
__ImplementClass(IO::StreamWriter, 'STWR', Core::RefCounted);

//------------------------------------------------------------------------------
/**
*/
StreamWriter::StreamWriter() :
    isOpen(false),
    streamWasOpen(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
StreamWriter::~StreamWriter()
{
    n_assert(!this->IsOpen());
}

//------------------------------------------------------------------------------
/**
    Attaches the writer to a stream. This will imcrement the refcount
    of the stream.
*/
void
StreamWriter::SetStream(const GPtr<Stream>& s)
{
    this->stream = s;
}

//------------------------------------------------------------------------------
/**
    Get pointer to the attached stream. If there is no stream attached,
    an assertion will be thrown. Use HasStream() to determine if a stream
    is attached.
*/
const GPtr<Stream>&
StreamWriter::GetStream() const
{
    return this->stream;
}

//------------------------------------------------------------------------------
/**
    Returns true if a stream is attached to the writer.
*/
bool
StreamWriter::HasStream() const
{
    return this->stream.isvalid();
}

//------------------------------------------------------------------------------
/**
*/
bool
StreamWriter::Open()
{
    n_assert(!this->isOpen);
    n_assert(this->stream.isvalid());
    n_assert(this->stream->CanWrite());
    if (this->stream->IsOpen())
    {
        n_assert((this->stream->GetAccessMode() == Stream::WriteAccess) || (this->stream->GetAccessMode() == Stream::ReadWriteAccess) || (this->stream->GetAccessMode() == Stream::AppendAccess));
        this->streamWasOpen = true;
        this->isOpen = true;
    }
    else
    {
        this->streamWasOpen = false;
        this->stream->SetAccessMode(Stream::WriteAccess);
        this->isOpen = this->stream->Open();
    }
    return this->isOpen;
}

//------------------------------------------------------------------------------
/**
*/
void
StreamWriter::Close()
{
    n_assert(this->isOpen);
    if ((!this->streamWasOpen) && stream->IsOpen())
    {
        stream->Close();
    }
    this->isOpen = false;
}

} // namespace IO
