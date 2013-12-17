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

#include "stdneb.h"
#include "net/osx/osxipaddress.h"
//#include "net/osx/osxsocket.h"

namespace OSX
{
    using namespace Util;
    using namespace IO;
    
    //------------------------------------------------------------------------------
    /**
     */
    OSXIpAddress::OSXIpAddress()
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    OSXIpAddress::OSXIpAddress(const OSXIpAddress& rhs) :
    hostName(rhs.hostName),
    addrAsString(rhs.addrAsString)
    //addr(rhs.addr)
    {
        // empty
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    OSXIpAddress::OSXIpAddress(const String& hostName_, ushort portNumber_)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     */
    OSXIpAddress::OSXIpAddress(const URI& uri)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     Extract the host name and optionally the port number from the provided
     URI. If no port number is set in the URI, the current port number
     will be left as is. If the host name is empty, it will be set to
     "localhost".
     */
    void
    OSXIpAddress::ExtractFromUri(const URI& uri)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     Set the port number. Will be translated to network byte order internally.
     */
    void
    OSXIpAddress::SetPort(ushort port)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     Get the port number in host byte order.
     */
    ushort
    OSXIpAddress::GetPort() const
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
    OSXIpAddress::SetHostName(const String& n)
    {
        
    }
    
    //------------------------------------------------------------------------------
    /**
     Get the host name.
     */
    const String&
    OSXIpAddress::GetHostName() const
    {
        return this->hostName;
    }
    
    //------------------------------------------------------------------------------
    /**
     Return the in address as string.
     */
    const String&
    OSXIpAddress::GetHostAddr() const
    {
        return this->addrAsString;
    }
    
} // namespace Win360

