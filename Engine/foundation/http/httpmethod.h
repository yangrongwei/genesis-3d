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
#ifndef HTTP_HTTPMETHOD_H
#define HTTP_HTTPMETHOD_H
//------------------------------------------------------------------------------
/**
    @class Http::HttpMethod
    
    Http methods enumeration (GET, PUT, etc...).

*/
#include "util/string.h"

//------------------------------------------------------------------------------
namespace Http
{
class HttpMethod
{
public:
    /// http methods
    enum Code
    {
        Options,
        Get,
        Head,
        Post,
        Put,
        Delete,
        Trace,
        Connect,
        
        NumHttpMethods,
        InvalidHttpMethod,
    };
    
    /// convert from string
    static Code FromString(const Util::String& str);
    /// convert to string
    static Util::String ToString(Code c);
};

//------------------------------------------------------------------------------
/**
*/
inline HttpMethod::Code
HttpMethod::FromString(const Util::String& str)
{
    if (str == "OPTIONS") return Options;
    else if (str == "GET") return Get;
    else if (str == "HEAD") return Head;
    else if (str == "POST") return Post;
    else if (str == "PUT") return Put;
    else if (str == "DELETE") return Delete;
    else if (str == "TRACE") return Trace;
    else if (str == "CONNECT") return Connect;
    else
    {
        return InvalidHttpMethod;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline Util::String
HttpMethod::ToString(Code c)
{
    switch (c)
    {
        case Options:   return "OPTIONS";
        case Get:       return "GET";
        case Head:      return "HEAD";
        case Post:      return "POST";
        case Put:       return "PUT";
        case Delete:    return "DELETE";
        case Trace:     return "TRACE";
        case Connect:   return "CONNECT";
        default:
            return "InvalidHttpMethod";
    }
}

} // namespace Http
//------------------------------------------------------------------------------
#endif
    