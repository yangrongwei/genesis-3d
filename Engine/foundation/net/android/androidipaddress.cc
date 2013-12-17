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
#include "net/android/androidipaddress.h"
#include "net/android/androidsocket.h"

namespace Android
{
using namespace Util;
using namespace IO;

//------------------------------------------------------------------------------
/**
*/
AndroidIpAddress::AndroidIpAddress()
{
   
}

//------------------------------------------------------------------------------
/**
*/
AndroidIpAddress::AndroidIpAddress(const AndroidIpAddress& rhs) :
    hostName(rhs.hostName),
    addrAsString(rhs.addrAsString),
    addr(rhs.addr)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
AndroidIpAddress::AndroidIpAddress(const String& hostName_, ushort portNumber_)
{
    
}

//------------------------------------------------------------------------------
/**
*/
AndroidIpAddress::AndroidIpAddress(const URI& uri)
{
	
}

//------------------------------------------------------------------------------
/**
*/
AndroidIpAddress::AndroidIpAddress(const sockaddr_in& sa)
{
   
}

//------------------------------------------------------------------------------
/**
    Set the address directly from a sockaddr_in struct. This will
    set the host name to the string representation of the 
    host address.
*/
void
AndroidIpAddress::SetSockAddr(const sockaddr_in& sa)
{
    
}

//------------------------------------------------------------------------------
/**
    Get the sockaddr_in struct, which has either been set directly
    with SetSockAddr() or indirectly through host name, port number
    or from an URI.
*/
const sockaddr_in&
AndroidIpAddress::GetSockAddr() const
{
    return this->addr;
}

//------------------------------------------------------------------------------
/**
    Extract the host name and optionally the port number from the provided
    URI. If no port number is set in the URI, the current port number
    will be left as is. If the host name is empty, it will be set to
    "localhost".
*/
void
AndroidIpAddress::ExtractFromUri(const URI& uri)
{
    
}

//------------------------------------------------------------------------------
/**
    Set the port number. Will be translated to network byte order internally.
*/
void
AndroidIpAddress::SetPort(ushort port)
{
    
}

//------------------------------------------------------------------------------
/**
    Get the port number in host byte order.
*/
ushort
AndroidIpAddress::GetPort() const
{
    return 0;
}

//------------------------------------------------------------------------------
/**
    Set the host name, and immediately convert it to an ip address. This 
    accepts the special hostnames "any", "broadcast", "localhost", "self" 
    and "inetself". The result ip address can be returned in string form
    with the method GetAddrAsString().
*/
void
AndroidIpAddress::SetHostName(const String& n)
{
   
}

//------------------------------------------------------------------------------
/**
    Get the host name.
*/
const String&
AndroidIpAddress::GetHostName() const
{
    return this->hostName;
}

//------------------------------------------------------------------------------
/**
    Return the in address as string.
*/
const String&
AndroidIpAddress::GetHostAddr() const
{
    return this->addrAsString;
}

//------------------------------------------------------------------------------
/**
    This resolves a host name into a IPv4 ip address. The ip address is
    returned in network byte order in the hostAddress argument. The return value
    indicates whether the operation was successful. The following special hostnames 
    can be defined:

    - "any"         resolves to INADDR_ANY (0.0.0.0)
    - "broadcast"   resolves to INADDR_BROADCAST (255.255.255.255)
    - "localhost"   resolves to 127.0.0.1
    - "self"        (NOT IMPLEMENTED ON XBOX360) resolves to the first address of this host
    - "inetself"    (NOT IMPLEMENTED ON XBOX360) resolves to the first address which is not a LAN address

    An empty host name is invalid. A hostname can also be an address string
    of the form xxx.yyy.zzz.www.

    NOTE: resolving host names and host addresses is not supported
    on the Xbox360, this basically means that an Xbox360 devkit can function
    as a server, but not as a client (this is fine for most debugging purposes).
*/
bool
AndroidIpAddress::GetHostByName(const Util::String& hostName, in_addr& outAddr)
{
   return false;
}

//------------------------------------------------------------------------------
/**
    This method checks if the provided address is an "internet" address,
    not a LAN address (not a class A, B or C network address).
*/
bool
AndroidIpAddress::IsInetAddr(const in_addr* addr)
{
    return false;
}

} // namespace Win360
#endif