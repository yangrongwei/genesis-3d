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
#include "stdneb.h"
#include "io/debug/consolepagehandler.h"
#include "io/console.h"
#include "http/html/htmlpagewriter.h"

namespace Debug
{
__ImplementClass(Debug::ConsolePageHandler, 'COPH', Http::HttpRequestHandler);

using namespace Http;
using namespace IO;
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
ConsolePageHandler::ConsolePageHandler()
{
    // setup request handler
    this->SetName("Console");
    this->SetDesc("show console log");
    this->SetRootLocation("console");

    // attach a history console handler which keeps track of log messages
    this->historyConsoleHandler = HistoryConsoleHandler::Create();
    Console::Instance()->AttachHandler(this->historyConsoleHandler.upcast<ConsoleHandler>());
}

//------------------------------------------------------------------------------
/**
*/
ConsolePageHandler::~ConsolePageHandler()
{
    this->historyConsoleHandler = 0;
}

//------------------------------------------------------------------------------
/**
*/
void
ConsolePageHandler::HandleRequest(const GPtr<HttpRequest>& request)
{
    GPtr<HtmlPageWriter> htmlWriter = HtmlPageWriter::Create();
    htmlWriter->SetStream(request->GetResponseContentStream());
    htmlWriter->SetTitle("Console Log");
    if (htmlWriter->Open())
    {
        htmlWriter->Element(HtmlElement::Heading1, "Console Log");

        // get current console log history
        const RingBuffer<String>& history = this->historyConsoleHandler->GetHistory();
        SizeT num = history.Size();
        IndexT i;
        for (i = 0; i < num; i++)
        {
            htmlWriter->Text(history[i]);
            htmlWriter->LineBreak();
        }
        htmlWriter->Close();
        request->SetStatus(HttpStatus::OK);
    }
    else
    {
        request->SetStatus(HttpStatus::InternalServerError);
    }
}

} // namespace IO
