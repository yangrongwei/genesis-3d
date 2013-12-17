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
//------------------------------------------------------------------------------
/**
    @class Http::HttpRequestWriter
    
    Writes a valid HTTP request header to a stream.

*/
#include "io/streamwriter.h"
#include "http/httpmethod.h"

//------------------------------------------------------------------------------
namespace Http
{
class HttpRequestWriter : public IO::StreamWriter
{
    __DeclareClass(HttpRequestWriter);
public:
    /// constructor
    HttpRequestWriter();
    
    /// set HTTP Method
    void SetMethod(HttpMethod::Code httpMethod);
    /// set the URI of the request
    void SetURI(const IO::URI& uri);
    /// set optional User-Agent string
    void SetUserAgent(const Util::String& userAgent);
    /// write the request header to the stream
    bool WriteRequestHeader();

private:
    HttpMethod::Code httpMethod;
    IO::URI uri;
    Util::String userAgent;
};

//------------------------------------------------------------------------------
/**
*/
inline void
HttpRequestWriter::SetMethod(HttpMethod::Code m)
{
    this->httpMethod = m;
}

//------------------------------------------------------------------------------
/**
*/
inline void
HttpRequestWriter::SetURI(const IO::URI& u)
{
    this->uri = u;
}

//------------------------------------------------------------------------------
/**
*/
inline void
HttpRequestWriter::SetUserAgent(const Util::String& agent)
{
    this->userAgent = agent;
}

} // namespace Http
//------------------------------------------------------------------------------
