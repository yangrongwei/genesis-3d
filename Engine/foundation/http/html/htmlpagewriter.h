/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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
#ifndef HTTP_HTMLPAGEWRITER_H
#define HTTP_HTMLPAGEWRITER_H
//------------------------------------------------------------------------------
/**
    @class Http::HtmlPageWriter
    
    A stream writer which supports writing a HTML-formatted page into a stream.
*/
#include "io/streamwriter.h"
#include "http/html/htmlelement.h"
#include "io/xmlwriter.h"
#include "util/array.h"
#include "util/stack.h"

//------------------------------------------------------------------------------
namespace Http
{
class HtmlPageWriter : public IO::StreamWriter
{
    __DeclareClass(HtmlPageWriter);
public:
    /// constructor
    HtmlPageWriter();
    /// destructor
    virtual ~HtmlPageWriter();
    /// set the title of the page
    void SetTitle(const Util::String& title);
    /// begin writing the stream
    virtual bool Open();
    /// end writing the stream
    virtual void Close();

    /// add an attribute for the next element
    void AddAttr(const Util::String& name, const Util::String& value);
    /// begin a generic element
    void Begin(HtmlElement::Code e);
    /// end a generic element
    void End(HtmlElement::Code e);
    /// shortcut for Begin()/Text()/End()
    void Element(HtmlElement::Code e, const Util::String& text);
    /// write a line break
    void LineBreak();
    /// write a horizontal rule
    void HorizontalRule();
    /// add inline text
    void Text(const Util::String& t);

    /// write a 2-element table row
    void TableRow2(const Util::String& col0, const Util::String& col1);

private:
    Util::String title;
    GPtr<IO::XmlWriter> xmlWriter;
    Util::Array<Util::KeyValuePair<Util::String,Util::String> > attrs;
    Util::Stack<HtmlElement::Code> elementStack;
};

//------------------------------------------------------------------------------
/**
*/
inline void
HtmlPageWriter::SetTitle(const Util::String& t)
{
    this->title = t;
}

} // namespace Http
//------------------------------------------------------------------------------
#endif
    