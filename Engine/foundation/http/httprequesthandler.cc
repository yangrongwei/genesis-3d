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
#include "http/httprequesthandler.h"

namespace Http
{
__ImplementClass(Http::HttpRequestHandler, 'HRHD', Core::RefCounted);

using namespace IO;
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
HttpRequestHandler::HttpRequestHandler()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
HttpRequestHandler::~HttpRequestHandler()
{
    this->pendingRequests.SetSignalOnEnqueueEnabled(false);
    // empty
}

//------------------------------------------------------------------------------
/**
    Put a http request into the request handlers message queue. This method
    is meant to be called from another thread.
*/
void
HttpRequestHandler::PutRequest(const GPtr<HttpRequest>& httpRequest)
{
    this->pendingRequests.Enqueue(httpRequest);
}

//------------------------------------------------------------------------------
/**
    Handle all pending http requests in the pending queue. This method
    must be called frequently from the thread which created this
    request handler.
*/
void
HttpRequestHandler::HandlePendingRequests()
{
    this->pendingRequests.DequeueAll(this->curWorkRequests);
    IndexT i;
    for (i = 0; i < this->curWorkRequests.Size(); i++)
    {
        this->HandleRequest(this->curWorkRequests[i]);
        this->curWorkRequests[i]->SetHandled(true);
    }
}

//------------------------------------------------------------------------------
/**
    Overwrite this method in your subclass. This method will be called by the
    HttpServer if AcceptsRequest() returned true. The request handler should
    properly process the request by filling the responseContentStream with
    data (for instance a HTML page), set the MediaType on the 
    responseContentStream (for instance "text/html") and return with a
    HttpStatus code (usually HttpStatus::OK).
*/
void
HttpRequestHandler::HandleRequest(const GPtr<HttpRequest>& request)
{
    request->SetStatus(HttpStatus::NotFound);
}

} // namespace Http

#endif