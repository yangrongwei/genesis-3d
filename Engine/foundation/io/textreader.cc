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
#include "io/textreader.h"
#include <string.h>

namespace IO
{
__ImplementClass(IO::TextReader, 'TXTR', IO::StreamReader);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
TextReader::TextReader()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
TextReader::~TextReader()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**
*/
unsigned char
TextReader::ReadChar()
{
    unsigned char c;
    this->stream->Read(&c, sizeof(c));
    return c;
}

//------------------------------------------------------------------------------
/**
*/
String
TextReader::ReadLine()
{
    // read chunk until newline found
    String result;
    char tmp[2];
    tmp[1] = '\0';
    while(!this->stream->Eof())
    {
        if(1 != this->stream->Read(tmp, 1)) break;
        if(tmp[0] == '\n') break;
        result.Append(String(tmp));
    }
    return result;
}

//------------------------------------------------------------------------------
/**
*/
String
TextReader::ReadAll()
{
    String result;
    if (this->stream->GetSize() > 0)
    {
        this->stream->Seek(0, Stream::Begin);
        Stream::Size size = this->stream->GetSize();
        char* buf = (char*) Memory::Alloc(Memory::ScratchHeap, size + 1);
        Stream::Size bytesRead = this->stream->Read(buf, size);
        buf[bytesRead] = 0;
        result = buf;
        Memory::Free(Memory::ScratchHeap, buf);
    }
    return result;
}

//------------------------------------------------------------------------------
/**
*/
Array<String>
TextReader::ReadAllLines()
{
    Array<String> result;
    while (!stream->Eof())
    {
        result.Append(this->ReadLine());
    }
    return result;
}

} // namespace IO
