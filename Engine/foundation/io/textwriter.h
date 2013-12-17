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
#ifndef IO_TEXTWRITER_H
#define IO_TEXTWRITER_H
//------------------------------------------------------------------------------
/**
    @class IO::TextWriter
    
    A friendly interface for writing text data to a stream.
*/
#include "io/streamwriter.h"

//------------------------------------------------------------------------------
namespace IO
{
class TextWriter : public StreamWriter
{
    __DeclareClass(TextWriter);
public:
    /// constructor
    TextWriter();
    /// destructor
    virtual ~TextWriter();
    /// write a single character
    void WriteChar(unsigned char c);
    /// write a string
    void WriteString(const Util::String& str);
    /// write some formatted text
    void WriteFormatted(const char* fmtString, ...);
    /// write a line of text and append a new-line
    void WriteLine(const Util::String& line);
    /// write a number of lines, separated by new-lines
    void WriteLines(const Util::Array<Util::String>& lines);
    /// generic writer method
    template<typename T> void Write(const T& t);
};

} // namespace IO
//------------------------------------------------------------------------------
#endif