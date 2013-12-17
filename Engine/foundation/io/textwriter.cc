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
#include "io/textwriter.h"

namespace IO
{
__ImplementClass(IO::TextWriter, 'TXTW', IO::StreamWriter);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
TextWriter::TextWriter()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
TextWriter::~TextWriter()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**
*/
void
TextWriter::WriteChar(unsigned char c)
{
    this->stream->Write(&c, sizeof(c));
}

//------------------------------------------------------------------------------
/**
*/
void
TextWriter::WriteString(const String& str)
{
    this->stream->Write(str.AsCharPtr(), str.Length());
}

//------------------------------------------------------------------------------
/**
*/
void __cdecl
TextWriter::WriteFormatted(const char* fmtString, ...)
{
    va_list argList;
    va_start(argList, fmtString);
    String str;
    str.FormatArgList(fmtString, argList);
    this->stream->Write(str.AsCharPtr(), str.Length());
    va_end(argList);
}

//------------------------------------------------------------------------------
/**
*/
void
TextWriter::WriteLine(const String& line)
{
    this->WriteString(line);
    this->WriteChar('\n');
}

//------------------------------------------------------------------------------
/**
*/
void
TextWriter::WriteLines(const Array<String>& lines)
{
    IndexT i;
    for (i = 0; i < lines.Size(); i++)
    {
        this->WriteLine(lines[i]);
    }
}

} // namespace IO