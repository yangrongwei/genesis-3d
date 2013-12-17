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
#ifndef HTTP_HTTPREQUESTHANDLER_H
#define HTTP_HTTPREQUESTHANDLER_H
//------------------------------------------------------------------------------
/**
    @class Http::HttpRequestHandler
    
    HttpRequestHandlers are attached to the HttpServer and process
    incoming HTTP requests. When an Http request comes in, the
    HttpServer asks every attached HttpRequestHandler until the first one
    accepts the request. If the HttpRequestHandler accepts the request
    its HandleRequest() method will be called with a pointer to a content
    stream. The request handler is expected to write the response to the
    content stream (IMPORTANT: don't forget to set the MediaType on the stream!)
    and return with a HttpStatus code.
*/
#include "core/refcounted.h"
#include "http/httprequest.h"
#include "io/uri.h"
#include "io/stream.h"
#include "util/string.h"
#include "threading/safequeue.h"

//------------------------------------------------------------------------------
namespace Http
{
class HttpRequestHandler : public Core::RefCounted
{
    __DeclareClass(HttpRequestHandler);
public:
    /// constructor
    HttpRequestHandler();
    /// destructor
    virtual ~HttpRequestHandler();

    /// get a human readable name of the request handler
    const Util::String& GetName() const;
    /// get a human readable description of the request handler
    const Util::String& GetDesc() const;
    /// get a resource location path which is accepted by the handler (e.g. "/display")
    const Util::String& GetRootLocation() const;

protected:
    friend class HttpServer;
    friend class HttpServerProxy;

    /// handle a http request, overwrite this method in you subclass
    virtual void HandleRequest(const GPtr<HttpRequest>& request);
    /// handle all pending requests, called by local-thread's HttpServerProxy
    void HandlePendingRequests();
    /// put a request to the pending queue, called by HttpServer thread
    void PutRequest(const GPtr<HttpRequest>& httpRequest);
    /// set human readable name of the request handler
    void SetName(const Util::String& n);
    /// set human readable description
    void SetDesc(const Util::String& d);
    /// set the root location of the request handler
    void SetRootLocation(const Util::String& l);

    Util::String name;
    Util::String desc;
    Util::String rootLocation;
    Threading::SafeQueue<GPtr<HttpRequest> > pendingRequests;
    Util::Array<GPtr<HttpRequest> > curWorkRequests;
};

//------------------------------------------------------------------------------
/**
*/
inline void
HttpRequestHandler::SetName(const Util::String& n)
{
    this->name = n;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
HttpRequestHandler::GetName() const
{
    return this->name;
}

//------------------------------------------------------------------------------
/**
*/
inline void
HttpRequestHandler::SetDesc(const Util::String& d)
{
    this->desc = d;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
HttpRequestHandler::GetDesc() const
{
    return this->desc;
}

//------------------------------------------------------------------------------
/**
*/
inline void
HttpRequestHandler::SetRootLocation(const Util::String& l)
{
    this->rootLocation = l;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
HttpRequestHandler::GetRootLocation() const
{
    return this->rootLocation;
}

} // namespace Http
//------------------------------------------------------------------------------
#endif

