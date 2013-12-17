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

#include "net/tcpclient.h"
#include "net/tcpmessagecodec.h"
#include "io/memorystream.h"
#include "util/queue.h"

//------------------------------------------------------------------------------
namespace Net
{
class MessageClient : public TcpClient
{
    __DeclareClass(MessageClient);
public:
    /// constructor
    MessageClient();
    /// destructor
    virtual ~MessageClient();
    
    /// establish a connection with the server
    virtual Result Connect();
    /// disconnect from the server
    virtual void Disconnect();

    /// send accumulated content of send stream to server
    virtual bool Send();
    /// access to send stream
    virtual const GPtr<IO::Stream>& GetSendStream();
    /// receive data from server into recv stream
    virtual bool Recv();
    /// access to recv stream
    virtual const GPtr<IO::Stream>& GetRecvStream();

private:
    TcpMessageCodec codec;
    GPtr<IO::Stream> sendMessageStream;
    GPtr<IO::Stream> recvMessageStream;
    Util::Queue<GPtr<IO::Stream> > msgQueue;
};

//------------------------------------------------------------------------------
} // namespace Net