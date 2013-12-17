/****************************************************************************
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

#ifndef __ANDROIDSOCKET_H__
#define __ANDROIDSOCKET_H__

#include "core/refcounted.h"
#include "net/socket/ipaddress.h"

namespace Net
{
    class Socket;
}

//------------------------------------------------------------------------------
namespace OSX
{
    class OSXSocket : public Core::RefCounted
    {
        __DeclareClass(OSXSocket);
    public:
        /// protocol types
        enum Protocol
        {
            TCP,            // a reliable TCP connection
            UDP,            // unreliable UDP connection
        };
        
        // return values
        enum Result
        {
            Error = 0,      // an error occured, call GetErrorCode() or GetErrorString() for more info
            Success,        // everything ok
            WouldBlock,     // operation on non-blocking socket is not complete
            Closed,         // connection has been gracefully closed
        };
        
        /// error codes
        enum ErrorCode
        {
            ErrorNone,                   // no error occured
            ErrorUnknown,                // an "unknown" error occured
            ErrorInterrupted,            // WSAEINTR
            ErrorPermissionDenied,       // WSAEACCESS
            ErrorBadAddress,             // WSAEFAULT
            ErrorInvalidArgument,        // WSAEINVAL
            ErrorTooManyOpenFiles,       // WSAEMFILE
            ErrorWouldBlock,             // WSAEWOULDBLOCK
            ErrorInProgress,             // WSAEINPROGRESS
            ErrorAlreadyInProgress,      // WSAEALREADY
            ErrorNotASocket,             // WSAENOTSOCK
            ErrorDestAddrRequired,       // WSAEDESTADDRREQ
            ErrorMsgTooLong,             // WSAEMSGSIZE
            ErrorInvalidProtocol,        // WSAEPROTOTYPE
            ErrorBadProtocolOption,      // WSAENOPROTOOPT
            ErrorProtocolNotSupported,   // WSEAPROTONOSUPPORT
            ErrorSocketTypeNotSupported, // WSAESOCKTNOSUPPORT
            ErrorOperationNotSupported,  // WSAEOPNOTSUPP
            ErrorProtFamilyNotSupported, // WSAEPFNOSUPPORT
            ErrorAddrFamilyNotSupported, // WSAEAFNOSUPPORT
            ErrorAddrInUse,              // WSAEADDRINUSE
            ErrorAddrNotAvailable,       // WSAEADDRNOTAVAIL
            ErrorNetDown,                // WSAENETDOWN
            ErrorNetUnreachable,         // WSAENETUNREACH
            ErrorNetReset,               // WSAENETRESET
            ErrorConnectionAborted,      // WSAECONNABORTED
            ErrorConnectionReset,        // WSAECONNRESET
            ErrorNoBufferSpace,          // WSAENOBUFS
            ErrorIsConnected,            // WSAEISCONN
            ErrorNotConnected,           // WSAENOTCONNECTED
            ErrorIsShutdown,             // WSAESHUTDOWN
            ErrorIsTimedOut,             // WSAETIMEDOUT
            ErrorConnectionRefused,      // WSAECONNREFUSED
            ErrorHostDown,               // WSAEHOSTDOWN
            ErrorHostUnreachable,        // WSAEHOSTUNREACH
            ErrorTooManyProcesses,       // WSAEPROCLIM
            ErrorSystemNotReady,         // WSAESYSNOTREADY
            ErrorVersionNotSupported,    // WSAEVERNOTSUPPORTED
            ErrorNotInitialized,         // WSAENOTINITIALISED
            ErrorDisconnecting,          // WSAEDISCONN
            ErrorTypeNotFound,           // WSAETYPE_NOT_FOUND
            ErrorHostNotFound,           // WSAEHOST_NOT_FOUND
            ErrorTryAgain,               // WSAETRY_AGAIN
            ErrorNoRecovery,             // WSAENO_RECOVERY
            ErrorNoData,                 // WSAENO_DATA
        };
        
        /// constructor
        OSXSocket();
        /// destructor
        virtual ~OSXSocket();
        /// static initializer method (called by SysFunc::Setup())
        static void InitNetwork();
        /// is network initialized
        static bool IsNetworkInitialized();
        
        /// open the socket
        bool Open(Protocol p);
        /// close the socket
        void Close();
        /// return true if the socket is open
        bool IsOpen() const;
        /// get the last error code
        ErrorCode GetErrorCode() const;
        /// get the last error string
        Util::String GetErrorString() const;
        
        /// set internet address of socket
        void SetAddress(const Net::IpAddress& a);
        /// get internet address of socket
        const Net::IpAddress& GetAddress() const;
        
        /// set the broadcast flag (SO_BROADCAST)
        void SetBroadcast(bool b);
        /// get the broadcast flag
        bool GetBroadcast();
        /// set the keepalive flag (SO_KEEPALIVE)
        void SetKeepAlive(bool b);
        /// get the keepalive flag
        bool GetKeepAlive();
        /// set reuseaddr flag (SO_REUSEADDR)
        void SetReUseAddr(bool b);
        /// get reuseaddr flag
        bool GetReUseAddr();
        /// set nodelay flag (TCP_NODELAY)
        void SetNoDelay(bool b);
        /// get nodelay flag
        bool GetNoDelay();
        /// set receive buffer size
        void SetRecvBufSize(SizeT s);
        /// get receive buffer size
        SizeT GetRecvBufSize();
        /// set send buffer size
        void SetSendBufSize(SizeT s);
        /// get send buffer size
        SizeT GetSendBufSize();
        /// set blocking mode (FIONBIO)
        void SetBlocking(bool b);
        /// get blocking mode
        bool GetBlocking() const;
        /// get the maximum message size that can be sent atomically
        SizeT GetMaxMsgSize();
        
        /// bind socket to ip address
        bool Bind();
        /// return true if the socket is bound to an address
        bool IsBound() const;
        /// listen for incoming connections (for server sockets)
        bool Listen();
        /// accept incoming connection, return a new socket (for server sockets)
        bool Accept(GPtr<Net::Socket>& outSocket);
        /// connect to the sockets address (for client sockets)
        Result Connect();
        /// test if the socket is currently connected
        bool IsConnected();
        /// send raw data into the socket
        Result Send(const void* buf, SizeT numBytes, SizeT& bytesSent);
        /// return true if recv data is available at the socket
        bool HasRecvData();
        /// receive raw data from the socket
        Result Recv(void* buf, SizeT bufSize, SizeT& bytesReceived);
        /// send raw data to address for connectionless sockets
        Result SendTo(const void* buf, SizeT numBytes, uint addr, ushort port, SizeT& bytesSent);
        /// receive raw data from address for connectionless sockets
        Result RecvFrom(void* buf, SizeT bufSize, uint addr, ushort port, SizeT& bytesReceived);
        
    private:
        friend class Win360IpAddress;
        
        /// open with an existing socket (called by Accept())
        //void OpenWithExistingSocket(SOCKET s);
        /// clear the last error code
        void ClearError();
        /// set error code to WSAGetLastError();
        void SetToLastWSAError();
        /// set WSA error code
        void SetWSAError(int wsaError);
        /// convert a WSA error code to internal error code
        static ErrorCode WSAErrorToErrorCode(int wsaError);
        /// convert error code to human readable string
        static Util::String ErrorAsString(ErrorCode err);
        /// convert WSA error code directly to string
        static Util::String WSAErrorToString(int wsaError);
        /// set a bool socket option
        void SetBoolOption(int optName, bool val);
        /// get a bool socket option
        bool GetBoolOption(int optName);
        /// set an integer socket option
        void SetIntOption(int optName, int val);
        /// get an integer socket option
        int GetIntOption(int optName);
        
        static bool NetworkInitialized;
        ErrorCode error;
        //SOCKET sock;
        Net::IpAddress addr;
        bool isBlocking;
        bool isBound;
    };
    
    //------------------------------------------------------------------------------
    /**
     */
    inline bool
    OSXSocket::IsOpen() const
    {
        return false;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline bool
    OSXSocket::IsBound() const
    {
        return this->isBound;
    }
    
    //------------------------------------------------------------------------------
    /**
     Set internet address of socket.
     */
    inline void
    OSXSocket::SetAddress(const Net::IpAddress& a)
    {
        this->addr = a;
    }
    
    //------------------------------------------------------------------------------
    /**
     Get internet address of socket.
     */
    inline const Net::IpAddress&
    OSXSocket::GetAddress() const
    {
        return this->addr;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline void
    OSXSocket::SetBroadcast(bool b)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline bool
    OSXSocket::GetBroadcast()
    {
        return false;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline void
    OSXSocket::SetKeepAlive(bool b)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline bool
    OSXSocket::GetKeepAlive()
    {
        return false;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline void
    OSXSocket::SetReUseAddr(bool b)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline bool
    OSXSocket::GetReUseAddr()
    {
        return false;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline void
    OSXSocket::SetNoDelay(bool b)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline bool
    OSXSocket::GetNoDelay()
    {
        return false;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline void
    OSXSocket::SetRecvBufSize(SizeT s)
    {
        ;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline SizeT
    OSXSocket::GetRecvBufSize()
    {
        return -1;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline void
    OSXSocket::SetSendBufSize(SizeT s)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline SizeT
    OSXSocket::GetSendBufSize()
    {
        return -1;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline SizeT
    OSXSocket::GetMaxMsgSize()
    {
        return -1;
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    inline bool
    OSXSocket::GetBlocking() const
    {
        return this->isBlocking;
    }
    
} // namespace OSX


#endif