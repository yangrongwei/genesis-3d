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

#include "stdneb.h"
#include "net/tcpmessagecodec.h"
#include "io/binarywriter.h"
#include "io/binaryreader.h"
#include "io/memorystream.h"
#include "memory/memory.h"
//------------------------------------------------------------------------------
using namespace Util;
using namespace IO;

namespace Net
{

//------------------------------------------------------------------------------
/**
*/
TcpMessageCodec::TcpMessageCodec():
    receiveState(HeaderData),
    messageSize(0),
    headerPosition(0),
    messagePostition(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
TcpMessageCodec::~TcpMessageCodec()
{
    // closes and discards header and message streams if they exists...
    if (this->headerStream.isvalid())
    {
        if (this->headerStream->IsOpen())
        {
            this->headerStream->Close();
        }
        this->headerStream = 0;
    }
    if (this->messageStream.isvalid())
    {
        if (this->messageStream->IsOpen())
        {
            this->messageStream->Close();
        }
        this->messageStream = 0;
    }
}

//------------------------------------------------------------------------------
/**
    Writes a copy of the given stream to the given output stream with header
    informations at the beginning.
*/
void
TcpMessageCodec::EncodeToMessage(const GPtr<IO::Stream> &stream, const GPtr<IO::Stream> &output)
{
    GPtr<BinaryWriter> writer = BinaryWriter::Create();
    writer->SetStreamByteOrder(System::ByteOrder::Network);
    writer->SetStream(output);
    SizeT streamSize = stream->GetSize();
    stream->SetAccessMode(Stream::ReadAccess);
    output->SetAccessMode(Stream::WriteAccess);
    uchar* ptr = 0;
    if (writer->Open() && stream->Open())
    {
        writer->WriteUInt('TCPM');
        writer->WriteInt(streamSize);
        ptr = (uchar*) stream->Map();
        writer->WriteRawData(ptr,streamSize);
    }
    if (writer->IsOpen())
    {
        writer->Close();
    }
    if (stream->IsOpen())
    {
        stream->Close();
    }
}

//------------------------------------------------------------------------------
/**
    Puts a given stream to the internal buffer. This may result in new
    messages in the queue.
*/
void
TcpMessageCodec::DecodeStream(const GPtr<IO::Stream> &stream)
{
    stream->SetAccessMode(Stream::ReadAccess);
    GPtr<BinaryReader> reader = BinaryReader::Create();
    reader->SetStream(stream);
    if(reader->Open())
    {
        uchar byte;
        while(!reader->Eof())
        {
            // read byte
            byte = reader->ReadUChar();
            
            if(HeaderData == this->receiveState)
            {
                // read header until enough bytes arrived
                if(this->headerPosition == 0)
                {
                    this->headerStream = MemoryStream::Create();
                    this->headerStream->SetAccessMode(Stream::WriteAccess);
                    this->headerStream->Open();
                }
                
                if (headerStream->IsOpen())
                {
                    // write byte to headerstream
                    this->headerStream->Write(&byte,sizeof(byte));
                    headerPosition++;
                    
                    if (this->headerPosition == 8)
                    {
                        this->headerStream->Close();
                        n_assert(this->headerStream->GetSize() == 8);
                        // handle complete received header
                        this->headerStream->SetAccessMode(Stream::ReadAccess);
                        GPtr<BinaryReader> reader = BinaryReader::Create();
                        reader->SetStream(this->headerStream);
                        reader->SetStreamByteOrder(System::ByteOrder::Network);
                        n_assert(reader->Open());
                        // read header name 'TCPM'
                        uint tcpm = reader->ReadUInt();
                        if(tcpm == 'TCPM')
                        {
                            this->messageSize = reader->ReadInt();
                            this->messagePostition = 0;
                            this->receiveState = MessageData;
                        }
                        reader->Close();
                        this->headerPosition = 0;
                    }
                }
            }
            else if(MessageData == this->receiveState)
            {   
                // read message until all bytes arrived
                if (this->messagePostition == 0)
                {
                    this->messageStream = MemoryStream::Create();
                    this->messageStream->SetAccessMode(Stream::WriteAccess);
                    this->messageStream->Open();
                }
                
                if (this->messageStream->IsOpen())
                {
                    // write byte to messagestream
                    this->messageStream->Write(&byte,sizeof(byte));
                    messagePostition++;
                    
                    if(messagePostition == messageSize)
                    {
                        this->messageStream->Close();
                        n_assert(this->messageStream->GetSize() == messageSize);
                        // attach completely received mesage
                        this->messageStream->SetAccessMode(Stream::ReadAccess);
                        this->completedMessages.Append(this->messageStream);
                        this->messageStream = 0;
                        this->messagePostition = 0;
                        this->receiveState = HeaderData;
                    }
                }
            }
        }
    }
}

//------------------------------------------------------------------------------
/**
    Returns true if messages are available
*/
bool
TcpMessageCodec::HasMessages()
{
    return this->completedMessages.Size() > 0;
}

//------------------------------------------------------------------------------
/**
    Returns all created messages since the last call and clears message
    queue.
*/
Util::Array<GPtr<IO::Stream> >
TcpMessageCodec::DequeueMessages()
{
    Array<GPtr<Stream> > output;
    output.AppendArray(this->completedMessages);
    this->completedMessages.Clear();
    return output;
}
} // namespace Net