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
    @class Net::StdTcpServer

    A TcpServer opens a socket and listens for connecting TcpClients. This
    listen process happens in its own listener-thread and thus doesn't block
    the application. Each connected client is represented through a
    TcpClientConnection object which can be used by the application
    to communicate with a specific client.

    (C) 2006 Radon Labs GmbH
*/
#include "core/refcounted.h"
#include "threading/thread.h"
#include "util/array.h"
#include "net/tcpclientconnection.h"
#include "net/socket/socket.h"
#include "threading/criticalsection.h"

//------------------------------------------------------------------------------
namespace Net
{
class StdTcpServer : public Core::RefCounted
{
    __DeclareClass(StdTcpServer);
public:
    /// constructor
    StdTcpServer();
    /// destructor
    virtual ~StdTcpServer();
    /// set address, hostname can be "any", "self" or "inetself"
    void SetAddress(const IpAddress& addr);
    /// get address
    const IpAddress& GetAddress() const;
    /// set client connection class
    void SetClientConnectionClass(const Core::Rtti& type);
    /// get client connection class
    const Core::Rtti& GetClientConnectionClass();
    /// open the server
    bool Open();
    /// close the server
    void Close();
    /// return true if server is open
    bool IsOpen() const;
    /// poll clients connections for received data, call this frequently!
    Util::Array<GPtr<TcpClientConnection> > Recv();
    /// broadcast a message to all clients
    bool Broadcast(const GPtr<IO::Stream>& msg);

private:
    /// a private listener thread class
    class ListenerThread : public Threading::Thread
    {
        __DeclareClass(ListenerThread);
    public:
        /// set pointer to parent tcp server
        void SetTcpServer(StdTcpServer* tcpServer);
        /// set ip address
        void SetAddress(const IpAddress& a);
        /// set client connection class
        void SetClientConnectionClass(const Core::Rtti& type);
    private:
        /// implements the actual listener method
        virtual void DoWork();
        /// send a wakeup signal
        virtual void EmitWakeupSignal();

        GPtr<StdTcpServer> tcpServer;
        IpAddress ipAddress;
        GPtr<Socket> socket;
        const Core::Rtti* connectionClassRtti;
    };
    friend class ListenerThread;
    /// add a client connection (called by the listener thread)
    void AddClientConnection(const GPtr<TcpClientConnection>& connection);

    IpAddress ipAddress;
    GPtr<ListenerThread> listenerThread;
    bool isOpen;
    Util::Array<GPtr<TcpClientConnection> > clientConnections;
    Threading::CriticalSection connectionCritSect;
    const Core::Rtti* connectionClassRtti;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
StdTcpServer::IsOpen() const
{
    return this->isOpen;
}

//------------------------------------------------------------------------------
/**
*/
inline void
StdTcpServer::SetAddress(const IpAddress& addr)
{
    this->ipAddress = addr;
}

//------------------------------------------------------------------------------
/**
*/
inline const IpAddress&
StdTcpServer::GetAddress() const
{
    return this->ipAddress;
}

//------------------------------------------------------------------------------
/**
*/
inline void
StdTcpServer::SetClientConnectionClass(const Core::Rtti& type)
{
    this->connectionClassRtti = &type;
}

//------------------------------------------------------------------------------
/**	
*/
inline const Core::Rtti&
StdTcpServer::GetClientConnectionClass()
{
    return *this->connectionClassRtti;
}
} // namespace Net
//------------------------------------------------------------------------------
