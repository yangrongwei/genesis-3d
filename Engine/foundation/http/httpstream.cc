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
#ifdef __WIN32__


#include "stdneb.h"
#include "http/httpstream.h"
#include "http/httpclientregistry.h"

// HttpStream not implemented on Wii
#if __NEBULA3_HTTP_FILESYSTEM__
namespace Http
{
__ImplementClass(Http::HttpStream, 'HTST', IO::MemoryStream);

//------------------------------------------------------------------------------
/**
*/
HttpStream::HttpStream()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
HttpStream::~HttpStream()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**
*/
bool
HttpStream::Open()
{
    n_assert(!this->IsOpen());
    bool retval = false;

    if (MemoryStream::Open())
    {
        n_printf("HttpStream: Opening '%s'...", this->uri.AsString().AsCharPtr());

        // create a HTTP client and open connection
        GPtr<HttpClient> httpClient = HttpClientRegistry::Instance()->ObtainConnection(this->uri);
        if (httpClient->IsConnected())
        {
            AccessMode oldAccessMode = this->accessMode;
            this->accessMode = WriteAccess;
            HttpStatus::Code res = httpClient->SendRequest(HttpMethod::Get, this->uri, this);
            this->accessMode = oldAccessMode;
            this->Seek(0, Stream::Begin);
            if (HttpStatus::OK == res)
            {
                n_printf("ok!\n");
                retval = true;
            }
            else
            {
				n_printf("failed! return code: %s\n", HttpStatus::ToHumanReadableString(res ).AsCharPtr() );
            }
            HttpClientRegistry::Instance()->ReleaseConnection(this->uri);
        }
		//如果错误，等待20毫秒重连尝试
		if( retval == false )
		{
			Sleep(20);

			// create a HTTP client and open connection
			GPtr<HttpClient> httpClient = HttpClientRegistry::Instance()->ObtainConnection(this->uri);
			if (httpClient->IsConnected())
			{
				AccessMode oldAccessMode = this->accessMode;
				this->accessMode = WriteAccess;
				HttpStatus::Code res = httpClient->SendRequest(HttpMethod::Get, this->uri, this);
				this->accessMode = oldAccessMode;
				this->Seek(0, Stream::Begin);
				if (HttpStatus::OK == res)
				{
					n_printf("ok!\n");
					retval = true;
				}
				else
				{
					n_printf("failed! return code: %s\n", HttpStatus::ToHumanReadableString(res ).AsCharPtr() );
				}
				HttpClientRegistry::Instance()->ReleaseConnection(this->uri);
			}
		}

		
    }
    return retval;
}

} // namespace Http
#endif // __WII__

#endif