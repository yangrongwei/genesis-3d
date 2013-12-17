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

#pragma once
#ifndef HTTP_HTTPSERVERPROXY_H
#define HTTP_HTTPSERVERPROXY_H
//------------------------------------------------------------------------------
/**
    @class Http::HttpServerProxy
    
    Client-side proxy of the HttpServer. Client threads create and
    attach HttpRequestHandlers to their HttpServerProxy. The HttpServerProxy 
    receives incoming http requests from the http thread, and lets
    its HttpRequestHandlers process the request in the client thread's
    context, then sends the result back to the http thread.
*/
#include "core/refcounted.h"
#include "core/singleton.h"
#include "http/httprequesthandler.h"

//------------------------------------------------------------------------------
namespace Http
{
class HttpServerProxy : public Core::RefCounted
{
    __DeclareClass(HttpServerProxy);
    __DeclareThreadSingleton(HttpServerProxy);
public:
    /// constructor
    HttpServerProxy();
    /// destructor
    virtual ~HttpServerProxy();

    /// open the server proxy
    void Open();
    /// close the server proxy
    void Close();
    /// return true if open
    bool IsOpen() const;

    /// attach a request handler to the server
    void AttachRequestHandler(const GPtr<Http::HttpRequestHandler>& h);
    /// remove a request handler from the server
    void RemoveRequestHandler(const GPtr<Http::HttpRequestHandler>& h);
    /// handle pending http requests, call this method frequently
    void HandlePendingRequests();

private:
    Util::Array<GPtr<HttpRequestHandler> > requestHandlers;
    bool isOpen;
};        

//------------------------------------------------------------------------------
/**
*/
inline bool
HttpServerProxy::IsOpen() const
{
    return this->isOpen;
}

} // namespace Http
//------------------------------------------------------------------------------
#endif
    