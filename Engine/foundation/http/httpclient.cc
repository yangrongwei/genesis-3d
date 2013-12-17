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

// HttpClient is not implemented on the Wii
#if __NEBULA3_HTTP_FILESYSTEM__
#include "http/httpclient.h"
#include "http/httprequestwriter.h"
#include "http/httpresponsereader.h"

namespace Http
{
__ImplementClass(Http::HttpClient, 'HTCL', Core::RefCounted);

using namespace Util;
using namespace IO;
using namespace Net;

//------------------------------------------------------------------------------
/**
*/
HttpClient::HttpClient() :
    userAgent("Mozilla")    // NOTE: web browser are picky about user agent strings, so use something common
{
    this->tcpClient = TcpClient::Create();
    this->tcpClient->SetBlocking(true);
}

//------------------------------------------------------------------------------
/**
*/
HttpClient::~HttpClient()
{
    if (this->IsConnected())
    {
        this->Disconnect();
    }
    this->tcpClient = 0;
}

//------------------------------------------------------------------------------
/**
*/
bool
HttpClient::Connect(const URI& uri)
{
    n_assert(!this->IsConnected());
    n_assert(this->tcpClient->IsBlocking());

    // not connected yet, setup connection through HTTP server
    IpAddress ipAddress(uri);
    if (ipAddress.GetPort() == 0)
    {
        ipAddress.SetPort(80);
    }
    this->tcpClient->SetServerAddress(ipAddress);
    TcpClient::Result result = this->tcpClient->Connect();
    n_assert(result != TcpClient::Connecting);
    return (TcpClient::Success == result);
}

//------------------------------------------------------------------------------
/**
*/
void
HttpClient::Disconnect()
{
    if (this->IsConnected())
    {
        this->tcpClient->Disconnect();
    }
}

//------------------------------------------------------------------------------
/**
*/
bool
HttpClient::IsConnected() const
{
    return this->tcpClient->IsConnected();
}

//------------------------------------------------------------------------------
/**
*/
HttpStatus::Code 
HttpClient::SendRequest(HttpMethod::Code requestMethod, const URI& uri, const GPtr<Stream>& responseContentStream)
{
    n_assert(this->IsConnected());

    // write a proper HTTP request to the send stream
    GPtr<HttpRequestWriter> httpRequestWriter = HttpRequestWriter::Create();
    httpRequestWriter->SetMethod(requestMethod);
    httpRequestWriter->SetURI(uri);
    httpRequestWriter->SetUserAgent(this->userAgent);
    httpRequestWriter->SetStream(this->tcpClient->GetSendStream());
    if (httpRequestWriter->Open())
    {
        httpRequestWriter->WriteRequestHeader();
        httpRequestWriter->Close();
    }
    else
    {
        return HttpStatus::ServiceUnavailable;
    }

    // send off the http request, and wait for the response
    if (!this->tcpClient->Send())
    {
        // send failed
        return HttpStatus::ServiceUnavailable;
    }

    // wait for the response (we're working in blocking mode)
    if (!this->tcpClient->Recv())
    {
        // receive failed
        return HttpStatus::ServiceUnavailable;
    }

    // decode the HTTP response from the receive stream
    GPtr<HttpResponseReader> httpResponseReader = HttpResponseReader::Create();
    httpResponseReader->SetStream(this->tcpClient->GetRecvStream());
    if (httpResponseReader->Open())
    {
        httpResponseReader->ReadResponse();
        if (httpResponseReader->IsValidHttpResponse())
        {
            if (HttpStatus::OK == httpResponseReader->GetStatusCode())
            {
                SizeT contentLength = httpResponseReader->GetContentLength();
                if (contentLength > 0)
                {
                    uchar* buf = (uchar*) Memory::Alloc(Memory::ScratchHeap, contentLength);
                    SizeT bufPos = 0;
                    SizeT bytesToRead = contentLength;
                    bool done = false;
                    while (!done)
                    {
                        const GPtr<Stream>& recvStream = this->tcpClient->GetRecvStream();
                        SizeT bytesRead = recvStream->Read(&(buf[bufPos]), bytesToRead);
                        bytesToRead -= bytesRead;
                        bufPos += bytesRead;
                        if (bytesToRead > 0)
                        {
                            recvStream->Close();
                            this->tcpClient->Recv();
                            recvStream->Open();
                        }
                        else
                        {
                            done = true;
                        }
                    }
                    if (responseContentStream->IsOpen())
                    {
                        // if stream is already open, simply append the read data
                        responseContentStream->Write(buf, contentLength);
                    }
                    else
                    {
                        // response content stream not open, so open -> write -> close
                        responseContentStream->SetAccessMode(Stream::WriteAccess);
                        if (responseContentStream->Open())
                        {
                            responseContentStream->Write(buf, contentLength);
                            responseContentStream->Close();
                        }
                        else
                        {
                            n_error("HttpClient: Failed to open '%s' for writing!", uri.AsString().AsCharPtr());
                            return HttpStatus::ServiceUnavailable;
                        }
                    }
                    Memory::Free(Memory::ScratchHeap, buf);
                }
            }
        }
        httpResponseReader->Close();
        return httpResponseReader->GetStatusCode();
    }
    // fallthrough: error
    return HttpStatus::ServiceUnavailable;
}

} // namespace Http
#endif // __WII__

#endif