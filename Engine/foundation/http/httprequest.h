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
#ifndef HTTP_HTTPREQUEST_H
#define HTTP_HTTPREQUEST_H
//------------------------------------------------------------------------------
/**
    @class Http::HttpRequest
    
    Encapsulates a complete Http request into a message.

*/
#include "messaging/message.h"
#include "http/httpmethod.h"
#include "http/httpstatus.h"
#include "io/uri.h"

//------------------------------------------------------------------------------
namespace Http
{
class HttpRequest : public Messaging::Message
{
    __DeclareClass(HttpRequest);
    __DeclareMsgId;
public:
    /// constructor
    HttpRequest();
    /// destructor
    virtual ~HttpRequest();
    
    /// set the Http method (GET, PUT, etc...)
    void SetMethod(HttpMethod::Code requestMethod);
    /// get the Http method
    HttpMethod::Code GetMethod() const;
    /// set the request URI
    void SetURI(const IO::URI& requestUri);
    /// get the request URI
    const IO::URI& GetURI() const;
    /// set the response content stream
    void SetResponseContentStream(const GPtr<IO::Stream>& responseContentStream);
    /// get the response content stream
    const GPtr<IO::Stream>& GetResponseContentStream() const;
    /// set the http status (set by HttpRequestHandler)
    void SetStatus(HttpStatus::Code status);
    /// get the http status 
    HttpStatus::Code GetStatus() const;

private:
    HttpMethod::Code method;
    IO::URI uri;
    GPtr<IO::Stream> responseContentStream;
    HttpStatus::Code status;
};

//------------------------------------------------------------------------------
/**
*/
inline void
HttpRequest::SetMethod(HttpMethod::Code m)
{
    this->method = m;
}

//------------------------------------------------------------------------------
/**
*/
inline HttpMethod::Code
HttpRequest::GetMethod() const
{
    return this->method;
}

//------------------------------------------------------------------------------
/**
*/
inline void
HttpRequest::SetURI(const IO::URI& u)
{
    this->uri = u;
}

//------------------------------------------------------------------------------
/**
*/
inline const IO::URI&
HttpRequest::GetURI() const
{
    return this->uri;
}

//------------------------------------------------------------------------------
/**
*/
inline void
HttpRequest::SetResponseContentStream(const GPtr<IO::Stream>& s)
{
    this->responseContentStream = s;
}

//------------------------------------------------------------------------------
/**
*/
inline const GPtr<IO::Stream>&
HttpRequest::GetResponseContentStream() const
{
    return this->responseContentStream;
}

//------------------------------------------------------------------------------
/**
*/
inline void
HttpRequest::SetStatus(HttpStatus::Code s)
{
    this->status = s;
}

//------------------------------------------------------------------------------
/**
*/
inline HttpStatus::Code
HttpRequest::GetStatus() const
{
    return this->status;
}

} // namespace Http
//------------------------------------------------------------------------------
#endif
    