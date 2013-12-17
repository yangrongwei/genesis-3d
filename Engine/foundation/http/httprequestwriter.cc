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

#if (__WIN32__||__APPLE__)

#include "stdneb.h"
#include "http/httprequestwriter.h"
#include "io/textwriter.h"

namespace Http
{
__ImplementClass(Http::HttpRequestWriter, 'HTRW', IO::StreamWriter);

using namespace Util;
using namespace IO;

//------------------------------------------------------------------------------
/**
*/
HttpRequestWriter::HttpRequestWriter() :
    httpMethod(HttpMethod::Get),
    userAgent("Mozilla")    // NOTE: web browser are picky about user agent strings, so use something common
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
bool
HttpRequestWriter::WriteRequestHeader()
{
    n_assert(this->IsOpen());
    n_assert(this->uri.IsValid());

    // attach a text writer to our stream
    GPtr<TextWriter> textWriter = TextWriter::Create();
    textWriter->SetStream(this->stream);
    if (textWriter->Open())
    {
        // write header
        textWriter->WriteFormatted("%s /%s HTTP/1.1\r\n", 
            HttpMethod::ToString(this->httpMethod).AsCharPtr(),
            this->uri.LocalPath().AsCharPtr());
        textWriter->WriteFormatted("Host: %s\r\n", this->uri.Host().AsCharPtr());
        textWriter->WriteFormatted("User-Agent: %s\r\n", this->userAgent.AsCharPtr());
        textWriter->WriteString("Keep-Alive: 300\r\n");
        textWriter->WriteString("Connection: keep-alive\r\n");
        textWriter->WriteString("\r\n");
        textWriter->Close();
        return true;
    }
    return false;
}

} // namespace Http

#endif