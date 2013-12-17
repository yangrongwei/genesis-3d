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
#include "http/httprequestreader.h"
#include "io/textreader.h"

namespace Http
{
__ImplementClass(Http::HttpRequestReader, 'HRQR', IO::StreamReader);

using namespace Util;
using namespace IO;

//------------------------------------------------------------------------------
/**
*/
HttpRequestReader::HttpRequestReader() :
    isValidHttpRequest(false),
    httpMethod(HttpMethod::InvalidHttpMethod)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
bool
HttpRequestReader::ReadRequest()
{
    this->isValidHttpRequest = false;
        
    // attach a text reader to our stream and parse the request header
    GPtr<TextReader> textReader = TextReader::Create();
    textReader->SetStream(this->stream);
    if (textReader->Open())
    {
        // read the first line of the request
        // should be "METHOD PATH HTTP/1.1[CRLF]
        String headLine =  textReader->ReadLine();
        Array<String> headTokens = headLine.Tokenize(" ");
        if (headTokens.Size() != 3)
        {
            // malformed request header
            textReader->Close();
            return false;
        }

        // check if the HTTP version string looks alright
        if (!String::MatchPattern(headTokens[2], "HTTP/*"))
        {
            // malformed request header
            textReader->Close();
            return false;
        }

        // decode the HTTP method
        this->httpMethod = HttpMethod::FromString(headTokens[0]);

        // decode the remaining request header lines
        String host;
        bool endOfHeader = false;
        while (!textReader->Eof() && !endOfHeader)
        {
            String curLine = textReader->ReadLine();
            if (curLine.IsValid())
            {
                if (String::MatchPattern(curLine, "Host: *"))
                {
                    host = curLine;
                    host.SubstituteString("Host: ", "");
                }
            }
            else
            {
                endOfHeader = true;
            }
        }

        // build URI
        String uriString;
        uriString.Format("http://%s%s", host.AsCharPtr(), headTokens[1].AsCharPtr());
        this->requestURI = uriString;

        this->isValidHttpRequest = true;
        textReader->Close();
        return true;
    }
    return false;
}

} // namespace Http

#endif