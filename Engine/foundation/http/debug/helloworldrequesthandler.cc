/****************************************************************************
Copyright (c) 2008, Radon Labs GmbH
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

#ifdef __WIN32__


#include "stdneb.h"
#include "http/debug/helloworldrequesthandler.h"
#include "http/html/htmlpagewriter.h"

namespace Debug
{
__ImplementClass(Debug::HelloWorldRequestHandler, 'HWRH', Http::HttpRequestHandler);

using namespace Http;

//------------------------------------------------------------------------------
/**
*/
HelloWorldRequestHandler::HelloWorldRequestHandler()
{
    // we need to set a human-readable name, a description, and
    // the URI root location:
    this->SetName("Hello World");
    this->SetDesc("a sample HttpRequestHandler");
    this->SetRootLocation("helloworld");
}

//------------------------------------------------------------------------------
/**
*/
void
HelloWorldRequestHandler::HandleRequest(const GPtr<HttpRequest>& request)
{
    // we could extract more information from the URI if we want, but
    // since this is the most simple HttpRequestHandler possible, we wont :)

    // in order to server a valid HTML page to the request's ResponseContentStream, 
    // we need to create a HtmlPageWriter and connect it to the 
    // ResponseContentStream, this is standard Nebula3 IO stuff...
    GPtr<HtmlPageWriter> htmlWriter = HtmlPageWriter::Create();
    htmlWriter->SetStream(request->GetResponseContentStream());
    htmlWriter->SetTitle("Hello World");
    if (htmlWriter->Open())
    {
        // write some standard text to HTML page
        htmlWriter->Text("Hello World");
        htmlWriter->Close();

        // finally set the HTTP status code
        request->SetStatus(HttpStatus::OK);
    }
    else
    {
        // this shouldn't happen, but if something goes wrong, the 
        // web browser should know as well
        request->SetStatus(HttpStatus::InternalServerError);
    }
}

} // namespace Debug

#endif