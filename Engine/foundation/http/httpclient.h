/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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
//------------------------------------------------------------------------------
/**
    @class Http::HttpClient
    
    Use a HTTP client to send HTTP requests to a HTTP server, and
    receive and decode HTTP responses. The HttpClient class
    is generally blocking. For non-blocking behaviour it's best
    to wrap the HttpClient into a thread.

*/    
#include "core/config.h"

// HttpClient not implemented on the Wii
#if __NEBULA3_HTTP_FILESYSTEM__
#include "core/refcounted.h"
#include "net/tcpclient.h"
#include "http/httpstatus.h"
#include "http/httpmethod.h"
#include "io/uri.h"
#include "io/stream.h"

//------------------------------------------------------------------------------
namespace Http
{
class HttpClient : public Core::RefCounted
{
    __DeclareClass(HttpClient);
public:
    /// constructor
    HttpClient();
    /// destructor
    virtual ~HttpClient();
    
    /// set the user-agent to use for HTTP requests
    void SetUserAgent(const Util::String& userAgent);
    /// get the user-agent
    const Util::String& GetUserAgent() const;

    /// establish a connection to a HTTP server
    bool Connect(const IO::URI& uri);
    /// disconnect from the server
    void Disconnect();
    /// return true if currently connected
    bool IsConnected() const;

    /// send request and write result to provided response content stream
    HttpStatus::Code SendRequest(HttpMethod::Code requestMethod, const IO::URI& uri, const GPtr<IO::Stream>& responseContentStream);

private:
    Util::String userAgent;
    GPtr<Net::TcpClient> tcpClient;
};

//------------------------------------------------------------------------------
/**
*/
inline void
HttpClient::SetUserAgent(const Util::String& agent)
{
    this->userAgent = agent;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::String&
HttpClient::GetUserAgent() const
{
    return this->userAgent;
}

} // namespace Http
//------------------------------------------------------------------------------
#endif // __WII__