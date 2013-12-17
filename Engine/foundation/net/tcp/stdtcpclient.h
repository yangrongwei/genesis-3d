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
    @class Net::StdTcpClient
  
    A TcpClient object is used to communicate with a TcpServer. Any
    number of clients can connect to a TcpServer, each connected 
    client spawns a TcpClientConnection object on the server side
    which represents this client on the server. Sending and
    receiving data is handled through streams, streams offer
    the most flexible model to read and write data in different
    formats by connecting different stream readers and stream 
    writers. The idea is to write data to the send stream, and
    to send of the accumulated data in the send stream once
    by calling the Send() method. To receive data from the
    server, call the Recv() method which will either block
    until, or return true in non-blocking mode as soon as data
    is available. The received data will be written into the 
    receive stream, where the application can read it in any
    way it desires.
    
    (C) 2006 Radon Labs GmbH
*/    
#include "core/refcounted.h"
#include "net/socket/ipaddress.h"
#include "net/socket/socket.h"
#include "io/stream.h"

//------------------------------------------------------------------------------
namespace Net
{
class StdTcpClient : public Core::RefCounted
{
    __DeclareClass(StdTcpClient);
public:
    enum Result
    {
        Error,
        Success,
        Connecting,
    };
    /// constructor
    StdTcpClient();
    /// destructor
    virtual ~StdTcpClient();
    /// enable/disable blocking behaviour
    void SetBlocking(bool b);
    /// get blocking behaviour
    bool IsBlocking() const;
    /// set the server address to connect to
    void SetServerAddress(const IpAddress& addr);
    /// get the server address
    const IpAddress& GetServerAddress() const;
    /// establish a connection with the server
    Result Connect();
    /// disconnect from the server
    void Disconnect();
    /// return true if currently connected
    bool IsConnected();
    /// send accumulated content of send stream to server
    bool Send();
    /// access to send stream
    const GPtr<IO::Stream>& GetSendStream();
    /// receive data from server into recv stream
    bool Recv();
    /// access to recv stream
    const GPtr<IO::Stream>& GetRecvStream();

protected:
    GPtr<Socket> socket;
    IpAddress serverAddr;
    bool blocking;
    GPtr<IO::Stream> sendStream;
    GPtr<IO::Stream> recvStream;
    bool inConnectionState;
};

//------------------------------------------------------------------------------
/**
*/
inline void
StdTcpClient::SetBlocking(bool b)
{
    this->blocking = b;
    if (this->socket.isvalid())
    {
        this->socket->SetBlocking(b);
    }
}

//------------------------------------------------------------------------------
/**
*/
inline bool
StdTcpClient::IsBlocking() const
{
    return this->blocking;
}

//------------------------------------------------------------------------------
/**
*/
inline void
StdTcpClient::SetServerAddress(const IpAddress& addr)
{
    this->serverAddr = addr;
}

//------------------------------------------------------------------------------
/**
*/
inline const IpAddress&
StdTcpClient::GetServerAddress() const
{
    return this->serverAddr;
}

} // namespace Net
//------------------------------------------------------------------------------
