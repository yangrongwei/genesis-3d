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

#if (__WIN32__ || __APPLE__)


#include "stdneb.h"
#include "http/html/htmlpagewriter.h"

namespace Http
{
__ImplementClass(Http::HtmlPageWriter, 'HMPW', IO::StreamWriter);

using namespace Util;
using namespace IO;

//------------------------------------------------------------------------------
/**
*/
HtmlPageWriter::HtmlPageWriter()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
HtmlPageWriter::~HtmlPageWriter()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
bool
HtmlPageWriter::Open()
{
    if (StreamWriter::Open())
    {
        // create an XmlWriter and attach it to our stream
        this->xmlWriter = XmlWriter::Create();
        this->xmlWriter->SetStream(this->stream);
        this->xmlWriter->Open();
        
        this->Begin(HtmlElement::Html);
        this->Begin(HtmlElement::Head);
        this->Begin(HtmlElement::Title);
        this->Text(this->title);
        this->End(HtmlElement::Title);
        this->End(HtmlElement::Head);
        this->Begin(HtmlElement::Body);

        return true;
    }
    else
    {
        return false;
    }
}

//------------------------------------------------------------------------------
/**
*/
void
HtmlPageWriter::Close()
{
    n_assert(this->IsOpen());

    // close HTML page
    this->End(HtmlElement::Body);
    this->End(HtmlElement::Html);
    n_assert(elementStack.IsEmpty());

    // close XML writer
    this->xmlWriter->Close();
    this->xmlWriter = 0;

    // set MIME type on our stream
    this->stream->SetMediaType(MediaType("text/html"));    

    // call parent class
    StreamWriter::Close();
}

//------------------------------------------------------------------------------
/**
    Adds an attribute for the next HTML element. Any number of attributes
    can be defined before calling Begin(). The attribute stack will be cleared
    as Begin() returns.
*/
void
HtmlPageWriter::AddAttr(const String& name, const String& value)
{
    n_assert(this->IsOpen());
    n_assert(name.IsValid());
    n_assert(value.IsValid());
    this->attrs.Append(KeyValuePair<String,String>(name, value));
}

//------------------------------------------------------------------------------
/**
    Begin a generic HTML element. Elements can be nested.
*/
void
HtmlPageWriter::Begin(HtmlElement::Code element)
{
    n_assert(this->IsOpen());
    this->elementStack.Push(element);
    this->xmlWriter->BeginNode(HtmlElement::ToHtml(element));
    IndexT i;
    for (i = 0; i < this->attrs.Size(); i++)
    {
        this->xmlWriter->SetString(this->attrs[i].Key(), this->attrs[i].Value());
    }
    this->attrs.Clear();
}

//------------------------------------------------------------------------------
/**
    End a generic HTML element. The element must match the last Begin() call!
*/
void
HtmlPageWriter::End(HtmlElement::Code element)
{
    n_assert(this->IsOpen());
    n_assert(!this->elementStack.IsEmpty());
    n_assert(this->elementStack.Peek() == element);
    this->elementStack.Pop();
    this->xmlWriter->EndNode();
}

//------------------------------------------------------------------------------
/**
*/
void
HtmlPageWriter::LineBreak()
{
    n_assert(this->IsOpen());
    this->xmlWriter->BeginNode("br");
    this->xmlWriter->EndNode();
}

//------------------------------------------------------------------------------
/**
*/
void
HtmlPageWriter::HorizontalRule()
{
    n_assert(this->IsOpen());
    this->xmlWriter->BeginNode("hr");
    this->xmlWriter->EndNode();
}

//------------------------------------------------------------------------------
/**
*/
void
HtmlPageWriter::Text(const Util::String& str)
{
    this->xmlWriter->WriteContent(str);
}

//------------------------------------------------------------------------------
/**
*/
void
HtmlPageWriter::Element(HtmlElement::Code e, const Util::String& text)
{
    this->Begin(e);
    this->Text(text);
    this->End(e);
}

//------------------------------------------------------------------------------
/**
*/
void
HtmlPageWriter::TableRow2(const String& col0, const String& col1)
{
    this->Begin(HtmlElement::TableRow);
    this->Element(HtmlElement::TableData, col0);
    this->Element(HtmlElement::TableData, col1);
    this->End(HtmlElement::TableRow);   
}

} // namespace Http

#endif