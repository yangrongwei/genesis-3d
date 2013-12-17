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

#if (__WIN32__||__APPLE__)


#include "stdneb.h"
#include "http/httpnzstream.h"
#include "http/httpclientregistry.h"
#include "zlib/zlib.h"

// HttpStream not implemented on Wii
#if __NEBULA3_HTTP_FILESYSTEM__
namespace Http
{
__ImplementClass(Http::HttpNzStream, 'HZST', IO::MemoryStream);

using namespace Util;
using namespace IO;

//------------------------------------------------------------------------------
/**
*/
HttpNzStream::HttpNzStream()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
HttpNzStream::~HttpNzStream()
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
HttpNzStream::Open()
{
    n_assert(!this->IsOpen());
    bool retval = false;

    // build a modified URI
    String nzUriStr = this->uri.AsString();
    nzUriStr.Append(".nz");
    URI nzUri(nzUriStr);

    n_printf("HttpNzStream: Opening '%s'...", nzUri.AsString().AsCharPtr());

    // create a HTTP client and open connection
    GPtr<HttpClient> httpClient = HttpClientRegistry::Instance()->ObtainConnection(nzUri);
    if (httpClient->IsConnected())
    {
        // create a memory stream which contains the compressed data
        GPtr<MemoryStream> srcStream = MemoryStream::Create();
        srcStream->SetAccessMode(Stream::WriteAccess);
        HttpStatus::Code res = httpClient->SendRequest(HttpMethod::Get, nzUri, srcStream.upcast<Stream>());
        if (HttpStatus::OK == res)
        {
            // access to compressed source data
            srcStream->SetAccessMode(Stream::ReadAccess);
            srcStream->Open();
            uint* srcPtr = (uint*) srcStream->Map();
            uLong srcDataSize = srcStream->GetSize() - 8;   // 8 is sizeof header

            // check magic number and get uncompressed size
            if (srcPtr[0] != 'NZ__')
            {
                n_error("HttpNzStream: stream '%s' is not in .nz format!\n", nzUri.AsString().AsCharPtr());
            }
            
            // decompress into self
            SizeT inflatedSize = srcPtr[1];
            this->SetSize(inflatedSize);
            MemoryStream::Open();
            void* dstPtr = this->Map();

            uLongf destLen = inflatedSize;
            int res = uncompress((Bytef*)dstPtr, &destLen, (const Bytef*)&(srcPtr[2]), srcDataSize);
            n_assert(Z_OK == res);

            this->Unmap();
            srcStream->Unmap();
            srcStream->Close();
            srcStream = 0;

            n_printf("ok!\n");
            retval = true;
        }
        else
        {
            n_printf("failed!\n");
        }
    }
    HttpClientRegistry::Instance()->ReleaseConnection(this->uri);
    return retval;
}

} // namespace Http
#endif // __WII__

#endif