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
#ifdef __ANDROID__
#include "stdneb.h"
#include "net/socket/socket.h"
#include "androidsocket.h"

namespace Android
{
__ImplementClass(Android::AndroidSocket, 'XSCK', Core::RefCounted);
using namespace Util;

bool AndroidSocket::NetworkInitialized = false;

//------------------------------------------------------------------------------
/**
*/
AndroidSocket::AndroidSocket() :
    error(ErrorNone),
    isBlocking(true),
    isBound(false)
{
    
}

//------------------------------------------------------------------------------
/**
*/
AndroidSocket::~AndroidSocket()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**
    This is a one-time init for the Windows Sockets system. The method
    is called from SysFunc::Setup() once at startup before any threads
    are launched.
*/
void
AndroidSocket::InitNetwork()
{
   
}   

//------------------------------------------------------------------------------
/**
*/
bool
AndroidSocket::Open(Protocol protocol)
{
	return false;
}


//------------------------------------------------------------------------------
/**
*/
void
AndroidSocket::Close()
{
    
}

//------------------------------------------------------------------------------
/**
    Set a boolean option on the socket. This is a private helper
    function.
*/
void
AndroidSocket::SetBoolOption(int optName, bool val)
{
   
}

//------------------------------------------------------------------------------
/**
    Get a boolean option on the socket. This is a private helper
    function.
*/
bool
AndroidSocket::GetBoolOption(int optName)
{
    return false;
}

//------------------------------------------------------------------------------
/**
    Set an int socket option. This is a private helper function.
*/
void
AndroidSocket::SetIntOption(int optName, int val)
{
    
}

//------------------------------------------------------------------------------
/**
    Get an int socket option. This is a private helper function.
*/
int
AndroidSocket::GetIntOption(int optName)
{
    
    return -1;
}

//------------------------------------------------------------------------------
/**
    Set the socket to blocking mode.
*/
void
AndroidSocket::SetBlocking(bool b)
{
   
}

//------------------------------------------------------------------------------
/**
    Bind the socket to its ip address set with SetAddress() and
    SetPort(). After binding the socket to an address, call
    the Listen() method to wait for incoming connections. This method
    only makes sense for server sockets.
*/
bool
AndroidSocket::Bind()
{
    return false;
}

//------------------------------------------------------------------------------
/**
    Wait for incoming connections to a server socket. Call this 
    method on server side after binding the socket to its address.
*/
bool
AndroidSocket::Listen()
{
    return false;
}

//------------------------------------------------------------------------------
/**
    Accept an incoming connection to a server socket. This will spawn
    a new socket for the connection which will be returned in the provided
    pointer reference. The address of the returned socket will be set to
    the address of the "connecting entity".
*/
bool
AndroidSocket::Accept(GPtr<Net::Socket>& outSocket)
{   
    return false;
}

//------------------------------------------------------------------------------
/**
    Connect to a server socket. This method is called by a client socket
    to connect to a server socket identified by the socket object's address.
    A non-blocking socket will return immediately with WouldBlock, since the
    connection cannot be established immediately. In this case, just continue
    to call Connect() until the method returns Success, or alternative, check
    the IsConnected() method, which will also return true once the connection
    has been establish.
*/
AndroidSocket::Result
AndroidSocket::Connect()
{
  
    return Success;
}

//------------------------------------------------------------------------------
/**
    This tests if the socket is actually connected by doing a select()
    on the socket to probe for writability. So the IsConnected() method
    basically checks whether data can be sent through the socket.
*/
bool
AndroidSocket::IsConnected()
{
   return false;
}

//------------------------------------------------------------------------------
/**
    Send raw data into the socket. Note that depending on the buffer size
    of the underlying socket implementation and other sockets, the method
    may not be able to send all provided data. In this case, the returned 
    content of bytesSent will be less then numBytes, even though the
    return value will be Success. It is up to the caller to handle the
    extra data which hasn't been sent with the current call.
*/
AndroidSocket::Result
AndroidSocket::Send(const void* buf, SizeT numBytes, SizeT& bytesSent)
{
    return Success;
}

//------------------------------------------------------------------------------
/**
    This method checks if the socket has received data available. Use
    this method in a loop with Recv() to get all data waiting at the
    socket. This method will never block.
*/
bool
AndroidSocket::HasRecvData()
{
    return false;
}

//------------------------------------------------------------------------------
/**
    Receive raw data from a socket and write the received data into the
    provided buffer. On a blocking socket this method will block until
    data arrives at the socket. A non-blocking socket would immediately return in
    this case with a WouldBlock result. When valid data has been received
    the method will return with a Success result and the bytesReceived argument
    will contain the number of received bytes. It is not guaranteed that a single
    receive will return all data waiting on the socket. To make sure that the
    socket is really empty, call Recv() in a loop until HasRecvData()
    returns false.
    When the socket has been gracefully closed by the other side, the method will 
    return with a Closed return value. Everything else will return with an Error 
    return code. Call GetErrorCode() or GetErrorString() to find out more in this case.
*/
AndroidSocket::Result
AndroidSocket::Recv(void* buf, SizeT bufSize, SizeT& bytesReceived)
{
   return Success;
}

//------------------------------------------------------------------------------
/**
    FIXME: this is the send method for connectionless sockets using the 
    UDP protocol.
*/
AndroidSocket::Result
AndroidSocket::SendTo(const void* /*buf*/, SizeT /*numBytes*/, uint /*addr*/, ushort /*port*/, SizeT& /*bytesSent*/)
{
    n_error("AndroidSocket::SendTo(): IMPLEMENT ME!");
    return Error;
}

//------------------------------------------------------------------------------
/**
    FIXME: this is the recv method for connectionless socket using the UDP
    protocol.
*/
AndroidSocket::Result
AndroidSocket::RecvFrom(void* /*buf*/, SizeT /*bufSize*/, uint /*addr*/, ushort /*port*/, SizeT& /*bytesReceived*/)
{
    n_error("AndroidSocket::RecvFrom(): IMPLEMENT ME!");
    return Error;
}

//------------------------------------------------------------------------------
/**
    Sets the internal error code to NoError.
*/
void
AndroidSocket::ClearError()
{
    this->error = ErrorNone;
}

//------------------------------------------------------------------------------
/**
    Sets the internal error code to WSAGetLastError().
*/
void
AndroidSocket::SetToLastWSAError()
{
   
}

//------------------------------------------------------------------------------
/**
    Sets the provided WSA error as error code.
*/
void
AndroidSocket::SetWSAError(int wsaError)
{
   
}

//------------------------------------------------------------------------------
/**
    This method converts an Windows Socket error code into a
    portable error code used by AndroidSocket.
*/
AndroidSocket::ErrorCode
AndroidSocket::WSAErrorToErrorCode(int wsaErrorCode)
{
    
}

//------------------------------------------------------------------------------
/**
    Convert an error code to a human readable error message.
*/
String
AndroidSocket::ErrorAsString(ErrorCode err)
{
    switch (err)
    {
        case ErrorNone:                      return "No error.";
        case ErrorUnknown:                   return "Unknown error (not mapped by AndroidSocket class).";
        case ErrorInterrupted:               return "Interrupted function call.";
        case ErrorPermissionDenied:          return "Permission denied.";
        case ErrorBadAddress:                return "Bad address.";
        case ErrorInvalidArgument:           return "Invalid argument.";
        case ErrorTooManyOpenFiles:          return "Too many open files (sockets).";
        case ErrorWouldBlock:                return "Operation would block.";
        case ErrorInProgress:                return "Operation now in progress.";
        case ErrorAlreadyInProgress:         return "Operation already in progress.";
        case ErrorNotASocket:                return "Socket operation on non-socket.";
        case ErrorDestAddrRequired:          return "Destination address required";
        case ErrorMsgTooLong:                return "Message too long.";
        case ErrorInvalidProtocol:           return "Protocol wrong type for socket.";
        case ErrorBadProtocolOption:         return "Bad protocal option.";
        case ErrorProtocolNotSupported:      return "Protocol not supported.";
        case ErrorSocketTypeNotSupported:    return "Socket type not supported.";
        case ErrorOperationNotSupported:     return "Operation not supported.";
        case ErrorProtFamilyNotSupported:    return "Protocol family not supported.";
        case ErrorAddrFamilyNotSupported:    return "Address family not supported by protocol family.";
        case ErrorAddrInUse:                 return "Address already in use.";
        case ErrorAddrNotAvailable:          return "Cannot assign requested address.";
        case ErrorNetDown:                   return "Network is down.";
        case ErrorNetUnreachable:            return "Network is unreachable.";
        case ErrorNetReset:                  return "Network dropped connection on reset.";
        case ErrorConnectionAborted:         return "Software caused connection abort.";
        case ErrorConnectionReset:           return "Connection reset by peer.";
        case ErrorNoBufferSpace:             return "No buffer space available.";
        case ErrorIsConnected:               return "Socket is already connected.";
        case ErrorNotConnected:              return "Socket is not connected.";
        case ErrorIsShutdown:                return "Cannot send after socket shutdown.";
        case ErrorIsTimedOut:                return "Connection timed out.";
        case ErrorConnectionRefused:         return "Connection refused.";
        case ErrorHostDown:                  return "Host is down.";
        case ErrorHostUnreachable:           return "No route to host.";
        case ErrorTooManyProcesses:          return "Too many processes.";
        case ErrorSystemNotReady:            return "Network subsystem is unavailable.";
        case ErrorVersionNotSupported:       return "Winsock.dll version out of range.";
        case ErrorNotInitialized:            return "Successful WSAStartup not yet performed.";
        case ErrorDisconnecting:             return "Graceful shutdown in progress.";
        case ErrorTypeNotFound:              return "Class type not found.";
        case ErrorHostNotFound:              return "Host not found.";
        case ErrorTryAgain:                  return "Nonauthoritative host not found.";
        case ErrorNoRecovery:                return "This is a nonrecoverable error.";
        case ErrorNoData:                    return "Valid name, no data record of requested type.";
        default:
            n_error("AndroidSocket::ErrorAsString(): unhandled error code!");
            return "";
    }
}

//------------------------------------------------------------------------------
/**
*/
String
AndroidSocket::WSAErrorToString(int wsaError)
{
    return "";
}

//------------------------------------------------------------------------------
/**
*/
String
AndroidSocket::GetErrorString() const
{
    return ErrorAsString(this->error);
}

//------------------------------------------------------------------------------
/**
*/
bool 
AndroidSocket::IsNetworkInitialized()
{
    return NetworkInitialized;
}
} // namespace Win360
#endif