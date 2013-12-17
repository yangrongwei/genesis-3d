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
    @class Http::HttpClientRegistry
    
    The HttpClientRegistry provides a way to re-use existing connections
    to HTTP servers instead of setting up a HTTP connection for every 
    single HTTP request.     
*/
// HttpClientRegistry not implemented on the Wii
#if __NEBULA3_HTTP_FILESYSTEM__
#include "core/refcounted.h"
#include "core/singleton.h"
#include "http/httpclient.h"
#include "io/uri.h"
#include "util/dictionary.h"
#include "util/stringatom.h"

//------------------------------------------------------------------------------
namespace Http
{
class HttpClientRegistry : public Core::RefCounted
{
    __DeclareClass(HttpClientRegistry);
    __DeclareThreadSingleton(HttpClientRegistry);
public:
    /// constructor
    HttpClientRegistry();
    /// destructor
    virtual ~HttpClientRegistry();

    /// setup the client registry
    void Setup();
    /// discard the client registry, closes all open connections
    void Discard();
    /// return true if the object has been setup
    bool IsValid() const;

    /// open a connection to a HTTP server, reuse connection if already connected
    GPtr<HttpClient> ObtainConnection(const IO::URI& uri);
    /// give up connection to a HTTP server, this will NEVER disconnect!
    void ReleaseConnection(const IO::URI& uri);
    /// check if a connection to an HTTP server exists
    bool IsConnected(const IO::URI& uri) const;
    /// disconnect all connections with a zero use count
    void DisconnectIdle();

private:
    struct Connection
    {
        GPtr<HttpClient> httpClient;
        SizeT useCount;
    };

    Util::Dictionary<Util::StringAtom, Connection> connections;
    bool isValid;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
HttpClientRegistry::IsValid() const
{
    return this->isValid;
}

} // namespace Http
//------------------------------------------------------------------------------
#endif //__WII__    