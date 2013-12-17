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
#ifndef HTTP_HTTPSERVER_H
#define HTTP_HTTPSERVER_H
//------------------------------------------------------------------------------
/**
    @class Http::HttpServer
    
    Implements an extremly simple standalone HTTP server with attached
    HttpRequestHandlers. Can be used to serve debug information about the 
    Nebula3 application to web browsers.

*/
#include "core/refcounted.h"
#include "core/singleton.h"
#include "net/tcpserver.h"
#include "net/socket/ipaddress.h"
#include "io/textreader.h"
#include "io/textwriter.h"
#include "http/httpresponsewriter.h"
#include "http/httprequesthandler.h"
#include "http/defaulthttprequesthandler.h"

//------------------------------------------------------------------------------
namespace Http
{
class HttpServer : public Core::RefCounted
{
    __DeclareClass(HttpServer);
    __DeclareThreadSingleton(HttpServer);
public:
    /// constructor
    HttpServer();
    /// destructor
    virtual ~HttpServer();
    
    /// set port number for http service
    void SetPort(ushort p);
    /// get port number of http service
    ushort GetPort() const;
    /// turn single-thread mode on/off (useful for debugging), default is off
    void SetSingleThreadMode(bool b);
    /// get single-thread mode
    bool IsSingleThreadMode() const;
    /// open the http server
    bool Open();
    /// close the http server
    void Close();
    /// return true if server is open
    bool IsOpen() const;
    /// attach a request handler to the server
    void AttachRequestHandler(const GPtr<HttpRequestHandler>& h);
    /// remove a request handler from the server
    void RemoveRequestHandler(const GPtr<HttpRequestHandler>& h);
    /// get registered request handlers
    Util::Array<GPtr<HttpRequestHandler> > GetRequestHandlers() const;
    /// call this method frequently to serve http connections
    void OnFrame();

private:
    /// handle an HttpRequest
    bool HandleHttpRequest(const GPtr<Net::TcpClientConnection>& clientConnection);
    /// build an HttpResponse for a handled http request
    bool BuildHttpResponse(const GPtr<Net::TcpClientConnection>& clientConnection, const GPtr<HttpRequest>& httpRequest);

    struct PendingRequest
    {
        GPtr<Net::TcpClientConnection> clientConnection;
        GPtr<HttpRequest> httpRequest;
    };

    Util::Dictionary<Util::String, GPtr<HttpRequestHandler> > requestHandlers;
    GPtr<DefaultHttpRequestHandler> defaultRequestHandler;    
    Net::IpAddress ipAddress;
    GPtr<Net::TcpServer> tcpServer;
    Util::Array<PendingRequest> pendingRequests;
    bool isOpen;
    bool isSingleThreadMode;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
HttpServer::IsOpen() const
{
    return this->isOpen;
}

//------------------------------------------------------------------------------
/**
    Switch on single thread mode, default is off. In single thread mode,
    http requests will be processed immediately in the OnFrame() method,
    not added to the request handler for asynchronous processing. This
    may be useful for debugging, but is dangerous/impossible if HTTP
    request handlers live in different threads!!!
*/
inline void
HttpServer::SetSingleThreadMode(bool b)
{
    n_assert(!this->isOpen);
    this->isSingleThreadMode = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
HttpServer::IsSingleThreadMode() const
{
    return this->isSingleThreadMode;
}

//------------------------------------------------------------------------------
/**
*/
inline void
HttpServer::SetPort(ushort p)
{
    this->ipAddress.SetPort(p);
}

//------------------------------------------------------------------------------
/**
*/
inline ushort
HttpServer::GetPort() const
{
    return this->ipAddress.GetPort();
}

//------------------------------------------------------------------------------
/**
*/
inline Util::Array<GPtr<HttpRequestHandler> >
HttpServer::GetRequestHandlers() const
{
    return this->requestHandlers.ValuesAsArray();
}

} // namespace Http
//------------------------------------------------------------------------------
#endif
    