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
    @class Net::MessageClientConnection

    A wrapper class for the Net::TcpClientConnection.
    
    All data that is send by using Send() will streamed into a container, before
    it will send to the client. The message contains information
    about the full length of the data. This way the receiving site can handle
    messages that are splittet into chunks and may wait until a full message was received.

    The MessageClientConnection will concatenate incoming data chunks to full messages and
    Recv() will only return finished messages.

    (C) 2009 Radon Labs GmbH
*/
#include "net/tcpclientconnection.h"
#include "net/tcpmessagecodec.h"
#include "util/queue.h"

//------------------------------------------------------------------------------
namespace Net
{
class MessageClientConnection : public TcpClientConnection
{
    __DeclareClass(MessageClientConnection);
public:
    // Constructor
    MessageClientConnection();
    // Destructor
    virtual ~MessageClientConnection();
    
    /// connect using provided socket
    virtual bool Connect(const GPtr<Socket>& s);
    /// shutdown the connection
    virtual void Shutdown();

    /// send accumulated content of send stream to server
    virtual Socket::Result Send();
    /// directly send a stream to the server, often prevents a memory copy
    virtual Socket::Result Send(const GPtr<IO::Stream>& stream);
    /// access to send stream
    virtual const GPtr<IO::Stream>& GetSendStream();
    /// receive data from server into recv stream
    virtual Socket::Result Recv();
    /// access to recv stream
    virtual const GPtr<IO::Stream>& GetRecvStream();    

private:   
    GPtr<IO::Stream> sendMessageStream;
    GPtr<IO::Stream> recvMessageStream;
    Util::Queue<GPtr<IO::Stream> > msgQueue;
    TcpMessageCodec codec;
};
} // namespace Net