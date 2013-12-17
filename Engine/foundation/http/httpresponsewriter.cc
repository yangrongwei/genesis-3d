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
#include "http/httpresponsewriter.h"
#include "io/textwriter.h"

namespace Http
{
__ImplementClass(Http::HttpResponseWriter, 'HRSW', IO::StreamWriter);

using namespace IO;

//------------------------------------------------------------------------------
/**
*/
void
HttpResponseWriter::WriteResponse()
{
    GPtr<TextWriter> textWriter = TextWriter::Create();
    textWriter->SetStream(this->stream);
    if (textWriter->Open())
    {
        textWriter->WriteFormatted("HTTP/1.1 %s %s\r\n", 
            HttpStatus::ToString(this->statusCode).AsCharPtr(),
            HttpStatus::ToHumanReadableString(this->statusCode).AsCharPtr());
        if (this->contentStream.isvalid())
        {
            textWriter->WriteFormatted("Content-Length: %d\r\n", 
                this->contentStream->GetSize());
            if (this->contentStream->GetMediaType().AsString().IsValid())
            {
                textWriter->WriteFormatted("Content-Type: %s\r\n", 
                    this->contentStream->GetMediaType().AsString().AsCharPtr());
            }
        }
        else
        {
            textWriter->WriteString("Content-Length: 0\r\n");
        }
        textWriter->WriteString("\r\n");
        textWriter->Close();
    }

    // append content string
    if (this->contentStream.isvalid())
    {
        n_assert(this->contentStream->CanBeMapped());
        this->contentStream->SetAccessMode(IO::Stream::ReadAccess);
        if (this->contentStream->Open())
        {                 
            void* ptr = this->contentStream->Map();
            this->stream->Write(ptr, this->contentStream->GetSize());
            this->contentStream->Unmap();                                                          
            this->contentStream->Close();
        }             
    }
}

} // namespace Http

#endif