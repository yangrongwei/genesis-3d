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

#if (__WIN32__||__APPLE__)

#include "stdneb.h"
#include "core/coreserver.h"
#include "http/defaulthttprequesthandler.h"
#include "timing/calendartime.h"
#include "http/html/htmlpagewriter.h"
#include "http/httpserver.h"
#include "http/httpinterface.h"

namespace Http
{
__ImplementClass(Http::DefaultHttpRequestHandler, 'DHRH', Http::HttpRequestHandler);

using namespace Core;
using namespace Util;
using namespace Timing;

//------------------------------------------------------------------------------
/**
*/
void
DefaultHttpRequestHandler::HandleRequest(const GPtr<HttpRequest>& request)
{
    // don't accept anything then Get
    if (HttpMethod::Get != request->GetMethod())
    {
        request->SetStatus(HttpStatus::NotImplemented);
        return;
    }
    
    // HttpInterface may not be present on some platforms
    StringAtom companyName("unknown");
    StringAtom appName("unknown");
    StringAtom rootDir("unknown");
    if (HttpInterface::HasInstance())
    {
        companyName = HttpInterface::Instance()->GetCompanyName();
        appName = HttpInterface::Instance()->GetAppName();
        rootDir = HttpInterface::Instance()->GetRootDirectory();
    }
    
    // always show the home page
    GPtr<HtmlPageWriter> htmlWriter = HtmlPageWriter::Create();
    htmlWriter->SetStream(request->GetResponseContentStream());
    htmlWriter->SetTitle("Genesis Application");
    if (htmlWriter->Open())
    {
        htmlWriter->Element(HtmlElement::Heading1, "Main Page");
        htmlWriter->Element(HtmlElement::Heading3, "Application Info");
        htmlWriter->Begin(HtmlElement::Table);
            htmlWriter->Begin(HtmlElement::TableRow); 
                htmlWriter->Element(HtmlElement::TableData, "Company Name:");
                htmlWriter->Element(HtmlElement::TableData, companyName.Value());
            htmlWriter->End(HtmlElement::TableRow);
            htmlWriter->Begin(HtmlElement::TableRow); 
                htmlWriter->Element(HtmlElement::TableData, "Application Name:");
                htmlWriter->Element(HtmlElement::TableData, appName.Value());
            htmlWriter->End(HtmlElement::TableRow);
            htmlWriter->Begin(HtmlElement::TableRow); 
                htmlWriter->Element(HtmlElement::TableData, "Root Directory:");
                htmlWriter->Element(HtmlElement::TableData, rootDir.Value());        
            htmlWriter->End(HtmlElement::TableRow);
            htmlWriter->Begin(HtmlElement::TableRow); 
                htmlWriter->Element(HtmlElement::TableData, "Calendar Time:");
                htmlWriter->Element(HtmlElement::TableData, CalendarTime::Format("{WEEKDAY} {DAY}.{MONTH}.{YEAR} {HOUR}:{MINUTE}:{SECOND}", CalendarTime::GetLocalTime()));
            htmlWriter->End(HtmlElement::TableRow);
        htmlWriter->End(HtmlElement::Table);

        // list registered HttpRequestHandlers
        htmlWriter->Element(HtmlElement::Heading3, "Available Pages");        
        Array<GPtr<HttpRequestHandler> > handlers = HttpServer::Instance()->GetRequestHandlers();
        if (handlers.Size() > 0)
        {
            htmlWriter->Begin(HtmlElement::UnorderedList);
            IndexT i;
            for (i = 0; i < handlers.Size(); i++)
            {
                const GPtr<HttpRequestHandler>& handler = handlers[i];
                htmlWriter->Begin(HtmlElement::ListItem);
                htmlWriter->AddAttr("href", handler->GetRootLocation());
                htmlWriter->Element(HtmlElement::Anchor, handler->GetName());
                htmlWriter->Text(String(" - ") + handler->GetDesc());
                htmlWriter->End(HtmlElement::ListItem);
            }
            htmlWriter->End(HtmlElement::UnorderedList);
        }
        htmlWriter->Close();
        request->SetStatus(HttpStatus::OK);
    }
    else
    {
        request->SetStatus(HttpStatus::InternalServerError);
    }
}

} // namespace Http

#endif