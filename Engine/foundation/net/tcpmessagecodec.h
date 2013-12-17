#pragma once
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

//------------------------------------------------------------------------------
/**
    @class Net::TcpMessageCodec

    Helperclass that provides function to encode and decode sreams into messages.
    
    The encoder adds header informations at the beginning of the stream,
    that includes the complete size of the stream. Call EncodeToMessage at the
    sending site.

    The decoder reads sequential incoming streams and append the data
    to an internal buffer. It concatenates the incoming streams to
    a list of streams containing complete messages.
    Call DecodeStream at the receiving site and check for completed messsages
    with GetMessages.

    (C) 2009 Radon Labs
*/
#include "io/memorystream.h"
#include "io/binaryreader.h"

//------------------------------------------------------------------------------
namespace Net
{
class TcpMessageCodec
{
public:
    /// Constructor
    TcpMessageCodec();
    /// Destructor
    virtual ~TcpMessageCodec();

    /// Attachs header information to the stream and returns a copy with header
    void EncodeToMessage(const GPtr<IO::Stream> & stream, const GPtr<IO::Stream> &output);  
    /// Decodes a given Stream. Check for HasMessages() if this completes a message.
    void DecodeStream(const GPtr<IO::Stream> & stream);
    /// Returns true, if there are messages in the internal message queue.
    bool HasMessages();
    /// Gets the list of all created messages since the last call of this function
    Util::Array<GPtr<IO::Stream> > DequeueMessages();

private: 
    /// what data is currently expected from the decoder
    enum ReceiveState
    {
        HeaderData,
        MessageData
    };
    
    ReceiveState receiveState;
    GPtr<IO::Stream> headerStream;
    GPtr<IO::Stream> messageStream;
    SizeT messageSize;
    IndexT headerPosition;
    IndexT messagePostition;
    Util::Array<GPtr<IO::Stream> > completedMessages;
};
//------------------------------------------------------------------------------
} // namespace Net