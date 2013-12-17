#pragma once
/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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
    @class Net::StdTcpClientConnection
  
    A TcpClientConnection represents a connected TcpClient on the
    server side. TcpClientConnection objects are created and maintained
    by a TcpServer object over the lifetime of a client connection.
    TcpClientConnection objects are used to communicate directly with
    the specific client represented by the connection object. 

    TcpClientConnection objects are generally non-blocking. To receive
    data from the client, call the Recv() method until it returns true,
    this indicates that received data is available in the RecvStream. To
    read data from the RecvStream attach a StreamReader which matches the
    data format your expecting from the client (e.g. BinaryReader, TextReader,
    XmlReader, etc...). To send data back to the client just do the reverse:
    write data to the SendStream, and at any time call the Send() method which
    will send all data accumulated in the SendStream to the client.
    
    (C) 2006 Radon Labs GmbH
*/    
#include "core/refcounted.h"
#include "net/socket/ipaddress.h"
#include "io/stream.h"
#include "net/socket/socket.h"

//------------------------------------------------------------------------------
namespace Net
{
class StdTcpClientConnection : public Core::RefCounted
{
    __DeclareClass(StdTcpClientConnection);
public:
    /// constructor
    StdTcpClientConnection();
    /// destructor
    virtual ~StdTcpClientConnection();
    /// connect using provided socket
    virtual bool Connect(const GPtr<Socket>& s);
    /// get the connection status
    bool IsConnected() const;
    /// shutdown the connection
    virtual void Shutdown();
    /// get the client's ip address
    const IpAddress& GetClientAddress() const;
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

protected:
    GPtr<Socket> socket;
    GPtr<IO::Stream> sendStream;
    GPtr<IO::Stream> recvStream;
};

} // namespace Net
//------------------------------------------------------------------------------
