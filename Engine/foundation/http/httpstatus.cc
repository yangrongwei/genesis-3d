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
#include "http/httpstatus.h"

namespace Http
{
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
HttpStatus::Code
HttpStatus::FromString(const Util::String& str)
{
    if (str == "100")      return Continue;
    else if (str == "200") return OK;
    else if (str == "400") return BadRequest;
    else if (str == "403") return Forbidden;
    else if (str == "404") return NotFound;
    else if (str == "405") return MethodNotAllowed;
    else if (str == "406") return NotAcceptable;
    else if (str == "500") return InternalServerError;
    else if (str == "503") return ServiceUnavailable;
    else
    {
        return InvalidHttpStatus;
    }
}

//------------------------------------------------------------------------------
/**
*/
String
HttpStatus::ToString(Code c)
{
    switch (c)
    {
        case Continue:                      return "100";
        case OK:                            return "200";
        case BadRequest:                    return "400";
        case Forbidden:                     return "403";
        case NotFound:                      return "404";
        case InternalServerError:           return "500";
        case NotImplemented:                return "501";
        case ServiceUnavailable:            return "503";
        default:
            n_error("Invalid HTTP status code!");
            return "";
    }
}

//------------------------------------------------------------------------------
/**
*/
String
HttpStatus::ToHumanReadableString(Code c)
{
    switch (c)
    {
        case Continue:                      return "Continue";
        case OK:                            return "OK";
        case BadRequest:                    return "Bad Request";
        case Forbidden:                     return "Forbidden";
        case NotFound:                      return "Not Found";
        case InternalServerError:           return "Internal Server Error";
        case NotImplemented:                return "Not Implemented";
        case ServiceUnavailable:            return "Service Unavailable";
        default:
            return "Invalid Status Code";
    }
}

} // namespace Http

#endif