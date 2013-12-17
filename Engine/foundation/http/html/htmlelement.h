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
#ifndef HTTP_HTMLELEMENT_H
#define HTTP_HTMLELEMENT_H
//------------------------------------------------------------------------------
/**
    @class Http::HtmlElement
    
    HTML markup elements.
*/
#include "core/types.h"
#include "util/string.h"

//------------------------------------------------------------------------------
namespace Http
{
class HtmlElement
{
public:
    /// elements
    enum Code
    {
        Html,                               //> <html>
        Head,                               //> <head>
        Title,                              //> <title>
        Body,                               //> <body>
        Heading1,                           //> <h1>
        Heading2,                           //> <h2>
        Heading3,                           //> <h3>
        Heading4,                           //> <h4>
        Heading5,                           //> <h5>
        Heading6,                           //> <h6>
        Paragraph,                          //> <p>
        UnorderedList,                      //> <ul>
        OrderedList,                        //> <ol>
        ListItem,                           //> <li>
        DefinitionList,                     //> <dl>
        DefinitionListTerm,                 //> <dt>
        DefinitionListDefinition,           //> <dd>
        BlockQuote,                         //> <blockquote>
        PreFormatted,                       //> <pre>
        Bold,                               //> <b>
        Italics,                            //> <i>
        Teletyper,                          //> <tt>
        Underscore,                         //> <u>
        Strike,                             //> <strike>
        Big,                                //> <big>
        Small,                              //> <small>
        Sup,                                //> <sup>
        Sub,                                //> <sub>
        Table,                              //> <table>
        TableRow,                           //> <tr>
        TableHeader,                        //> <th>
        TableData,                          //> <td>
        Anchor,                             //> <a>
        Image,                              //> <img>
        Object,                             //> <object>
        Form,                               //> <form>
        Input,                              //> <input>
        Div,                                //> <div>
        Span,                               //> <span>
        Style,                              //> <style>
        Font,                               //> <font>
        Script,                             //> <script>

        InvalidHtmlElement,
    };     
    
    /// convert to string
    static Util::String ToHtml(Code c);
};

} // namespace Http
//------------------------------------------------------------------------------
#endif
    