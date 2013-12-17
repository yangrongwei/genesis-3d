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
#include "http/html/htmlelement.h"

namespace Http
{

//------------------------------------------------------------------------------
/**
*/
Util::String
HtmlElement::ToHtml(Code c)
{
    switch (c)
    {
        case Html:                               return "html";
        case Head:                               return "head";
        case Title:                              return "title";
        case Body:                               return "body";
        case Heading1:                           return "h1";
        case Heading2:                           return "h2";
        case Heading3:                           return "h3";
        case Heading4:                           return "h4";
        case Heading5:                           return "h5";
        case Heading6:                           return "h6";
        case Paragraph:                          return "p";
        case UnorderedList:                      return "ul";
        case OrderedList:                        return "ol";
        case ListItem:                           return "li";
        case DefinitionList:                     return "dl";
        case DefinitionListTerm:                 return "dt";
        case DefinitionListDefinition:           return "dd";
        case BlockQuote:                         return "blockquote";
        case PreFormatted:                       return "pre";
        case Bold:                               return "b";
        case Italics:                            return "i";
        case Teletyper:                          return "tt";
        case Underscore:                         return "u";
        case Strike:                             return "strike";
        case Big:                                return "big";
        case Small:                              return "small";
        case Sup:                                return "sup";
        case Sub:                                return "sub";
        case Table:                              return "table";
        case TableRow:                           return "tr";
        case TableHeader:                        return "th";
        case TableData:                          return "td";
        case Anchor:                             return "a";
        case Image:                              return "img";
        case Object:                             return "object"; 
        case Form:                               return "form";
        case Input:                              return "input";
        case Div:                                return "div";
        case Span:                               return "span";
        case Style:                              return "style";
        case Font:                               return "font";
        case Script:                             return "script";
        default:
            n_error("HtmlElement::ToHtml(): invalid element code!");
            return "";
    }
}

} // namespace Http

#endif