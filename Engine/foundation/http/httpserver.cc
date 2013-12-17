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
#include "http/httpserver.h"
#include "http/httprequestreader.h"
#include "io/memorystream.h"

namespace Http
{
__ImplementClass(Http::HttpServer, 'HTPS', Core::RefCounted);
__ImplementThreadSingleton(Http::HttpServer);

using namespace Util;
using namespace Net;
using namespace IO;

//------------------------------------------------------------------------------
/**
*/
HttpServer::HttpServer() :
    isOpen(false),
    isSingleThreadMode(false)
{
    __ConstructThreadSingleton;
    this->ipAddress.SetHostName("any");
    this->ipAddress.SetPort(2100);
}

//------------------------------------------------------------------------------
/**
*/
HttpServer::~HttpServer()
{
    n_assert(!this->IsOpen());
    __DestructThreadSingleton;        
}

//------------------------------------------------------------------------------
/**
*/
bool
HttpServer::Open()
{
    n_assert(!this->isOpen);
    this->isOpen = true;
    
    // setup a new TcpServer object
    this->tcpServer = TcpServer::Create();
    this->tcpServer->SetAddress(this->ipAddress);
    bool success = this->tcpServer->Open();

    // create the default http request handler
    this->defaultRequestHandler = DefaultHttpRequestHandler::Create();
    return success;
}

//------------------------------------------------------------------------------
/**
*/
void
HttpServer::Close()
{
    n_assert(this->isOpen);

    // clear pending requests
    this->pendingRequests.Clear();

    // destroy the default http request handler
    this->defaultRequestHandler = 0;

    // remove request handlers
    this->requestHandlers.Clear();

    // shutdown TcpServer
    this->tcpServer->Close();
    this->tcpServer = 0;
    this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
*/
void
HttpServer::AttachRequestHandler(const GPtr<HttpRequestHandler>& requestHandler)
{
    n_assert(requestHandler.isvalid());
    n_assert(this->isOpen);
    n_assert(!this->requestHandlers.Contains(requestHandler->GetRootLocation()));
    this->requestHandlers.Add(requestHandler->GetRootLocation(), requestHandler);
}

//------------------------------------------------------------------------------
/**
*/
void
HttpServer::RemoveRequestHandler(const GPtr<HttpRequestHandler>& requestHandler)
{
    n_assert(requestHandler.isvalid());
    n_assert(this->isOpen);
    this->requestHandlers.Erase(requestHandler->GetRootLocation());
}

//------------------------------------------------------------------------------
/**
*/
void
HttpServer::OnFrame()
{
    n_assert(this->isOpen);

    // handle pending client requests
    Array<GPtr<TcpClientConnection> > recvConns = this->tcpServer->Recv();
    IndexT i;
    for (i = 0; i < recvConns.Size(); i++)
    {
        if (!this->HandleHttpRequest(recvConns[i]))
        {
            recvConns[i]->Shutdown();
        }
    }

    // handle processed http requests
    for (i = 0; i < this->pendingRequests.Size();)
    {
        const GPtr<HttpRequest>& httpRequest = this->pendingRequests[i].httpRequest;
        if (httpRequest->Handled())
        {
            const GPtr<TcpClientConnection>& conn = this->pendingRequests[i].clientConnection;
            if (this->BuildHttpResponse(conn, httpRequest))
            {
                conn->Send();
            }
            this->pendingRequests.EraseIndex(i);
        }
        else
        {
            i++;
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
bool
HttpServer::HandleHttpRequest(const GPtr<TcpClientConnection>& clientConnection)  
{
    // decode the request
    GPtr<HttpRequestReader> httpRequestReader = HttpRequestReader::Create();
    httpRequestReader->SetStream(clientConnection->GetRecvStream());
    if (httpRequestReader->Open())
    {
        httpRequestReader->ReadRequest();
        httpRequestReader->Close();
    }
    if (httpRequestReader->IsValidHttpRequest())
    {
        URI requestURI = httpRequestReader->GetRequestURI();
    
        // create a content stream for the response
        GPtr<MemoryStream> responseContentStream = MemoryStream::Create();
        
        // build a HttpRequest object
        GPtr<HttpRequest> httpRequest = HttpRequest::Create();
        httpRequest->SetMethod(httpRequestReader->GetHttpMethod());
        httpRequest->SetURI(httpRequestReader->GetRequestURI());
        httpRequest->SetResponseContentStream(responseContentStream.upcast<Stream>());
        httpRequest->SetStatus(HttpStatus::NotFound);

        // find a request handler which accepts the request
        GPtr<HttpRequestHandler> requestHandler;
        Array<String> tokens = requestURI.LocalPath().Tokenize("/");
        if (tokens.Size() > 0)
        {
            if (this->requestHandlers.Contains(tokens[0]))
            {
                requestHandler = this->requestHandlers[tokens[0]];
            }
        }
        if (requestHandler.isvalid())
        {
            // handle the request, default is asynchronous handling 
            // (request is added to request handler with PutRequest()
            // and processed when the thread where the request handler
            // lives calls HandlePendingRequests()
            // in SingleThread mode, the request will be processed immediately,
            // but this is a death-receipt if request handlers live on
            // different threads!!!
            if (this->IsSingleThreadMode())
            {
                // handle request immediately
                requestHandler->HandleRequest(httpRequest);
                httpRequest->SetHandled(true);
            }
            else
            {
                // asynchronously handle the request
                requestHandler->PutRequest(httpRequest);
            }
        }
        else
        {
            // no request handler accepts the request, let the default
            // request handler handle the request
            this->defaultRequestHandler->HandleRequest(httpRequest);
            httpRequest->SetHandled(true);
        }

        // append request to pending queue
        PendingRequest pendingRequest;
        pendingRequest.clientConnection = clientConnection;
        pendingRequest.httpRequest = httpRequest;
        this->pendingRequests.Append(pendingRequest);

        return true;
    }
    else
    {
        // the received data was not a valid HTTP request
        return false;
    }
}

//------------------------------------------------------------------------------
/**
*/
bool
HttpServer::BuildHttpResponse(const GPtr<TcpClientConnection>& conn, const GPtr<HttpRequest>& httpRequest)
{
    GPtr<HttpResponseWriter> responseWriter = HttpResponseWriter::Create();
    responseWriter->SetStream(conn->GetSendStream());
    responseWriter->SetStatusCode(httpRequest->GetStatus());
    if (HttpStatus::OK != httpRequest->GetStatus())
    {
        // an error occured, need to write an error message to the response stream
        GPtr<TextWriter> textWriter = TextWriter::Create();
        textWriter->SetStream(httpRequest->GetResponseContentStream());
        textWriter->Open();
        textWriter->WriteFormatted("%s %s", HttpStatus::ToString(httpRequest->GetStatus()).AsCharPtr(), HttpStatus::ToHumanReadableString(httpRequest->GetStatus()).AsCharPtr());
        textWriter->Close();
        httpRequest->GetResponseContentStream()->SetMediaType(MediaType("text/plain"));
    }
    if (httpRequest->GetResponseContentStream()->GetSize() > 0)
    {
        httpRequest->GetResponseContentStream()->GetMediaType().IsValid();
        responseWriter->SetContent(httpRequest->GetResponseContentStream());
    }
    // do nothing, if stream isn't valid
    if (responseWriter->GetStream().isvalid())
    {
        responseWriter->Open();
        responseWriter->WriteResponse();
        responseWriter->Close();                 
        return true;
    }    
    return false;
}

} // namespace Http

#endif
