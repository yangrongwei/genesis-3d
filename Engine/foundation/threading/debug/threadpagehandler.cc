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
#include "threading/debug/threadpagehandler.h"
#include "threading/thread.h"
#include "http/html/htmlpagewriter.h"

namespace Debug
{
__ImplementClass(Debug::ThreadPageHandler, 'TPGH', Http::HttpRequestHandler);

using namespace IO;
using namespace Http;
using namespace Util;
using namespace Threading;

//------------------------------------------------------------------------------
/**
*/
ThreadPageHandler::ThreadPageHandler()
{
    this->SetName("Threads");
    this->SetDesc("display running threads");
    this->SetRootLocation("thread");
}

//------------------------------------------------------------------------------
/**
*/
void
ThreadPageHandler::HandleRequest(const GPtr<HttpRequest>& request) 
{
    n_assert(HttpMethod::Get == request->GetMethod());

    // configure a HTML page writer
    GPtr<HtmlPageWriter> htmlWriter = HtmlPageWriter::Create();
    htmlWriter->SetStream(request->GetResponseContentStream());
    htmlWriter->SetTitle("Genesis Thread Info");
    if (htmlWriter->Open())
    {
        htmlWriter->Element(HtmlElement::Heading1, "Genesis Threads");
        htmlWriter->AddAttr("href", "/index.html");
        htmlWriter->Element(HtmlElement::Anchor, "Home");

        // if not compiled with NEBULA_DEBUG, display a message
        #if (NEBULA3_DEBUG == 0)
        htmlWriter->LineBreak();
        htmlWriter->LineBreak();
        htmlWriter->Text("Thread list not available because application was not compiled with debug information!");
        #else
        htmlWriter->Element(HtmlElement::Heading3, "Running Threads");
        Array<Thread::ThreadDebugInfo> threadInfos = Thread::GetRunningThreadDebugInfos();

        htmlWriter->AddAttr("border", "1");
        htmlWriter->AddAttr("rules", "cols");
        htmlWriter->Begin(HtmlElement::Table);
            htmlWriter->AddAttr("bgcolor", "lightsteelblue");
            htmlWriter->Begin(HtmlElement::TableRow);
                htmlWriter->Element(HtmlElement::TableHeader, "Thread Name");
                htmlWriter->Element(HtmlElement::TableHeader, "Priority");
                htmlWriter->Element(HtmlElement::TableHeader, "CPU Core");
                htmlWriter->Element(HtmlElement::TableHeader, "Stack Size");
            htmlWriter->End(HtmlElement::TableRow);

            IndexT i;
            for (i = 0; i < threadInfos.Size(); i++)
            {
                const Thread::ThreadDebugInfo& curThreadInfo = threadInfos[i];
                htmlWriter->Begin(HtmlElement::TableRow);
                    htmlWriter->Element(HtmlElement::TableData, curThreadInfo.threadName);
                    String pri = "UNKNOWN";
                    switch (curThreadInfo.threadPriority)
                    {
                        case Thread::Low:       pri = "Low"; break;
                        case Thread::Normal:    pri = "Normal"; break;
                        case Thread::High:      pri = "High"; break;
                    }
                    htmlWriter->Element(HtmlElement::TableData, pri);
                    htmlWriter->Element(HtmlElement::TableData, String::FromInt(curThreadInfo.threadCoreId));
                    htmlWriter->Element(HtmlElement::TableData, String::FromInt(curThreadInfo.threadStackSize));
                htmlWriter->End(HtmlElement::TableRow);
            }
        htmlWriter->End(HtmlElement::Table);
        #endif
        htmlWriter->Close();
        request->SetStatus(HttpStatus::OK);
    }
    else
    {
        request->SetStatus(HttpStatus::InternalServerError);
    }
}

} // namespace Debug
