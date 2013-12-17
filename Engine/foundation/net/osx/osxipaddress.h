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

#ifndef __OSXIPADDRESS_H__
#define __OSXIPADDRESS_H__

//#include <linux/in.h>
#include "core/types.h"
#include "io/uri.h"

//------------------------------------------------------------------------------
namespace OSX
{
	class OSXIpAddress
	{
	public:
		/// default constructor
		OSXIpAddress();
		/// copy constructor
		OSXIpAddress(const OSXIpAddress& rhs);
		/// construct from URI
		OSXIpAddress(const IO::URI& uri);
		/// construct from host name and port number
		OSXIpAddress(const Util::String& hostName, ushort portNumber);
		/// equality operator
		bool operator==(const OSXIpAddress& rhs) const;
		/// less-then operator
		bool operator<(const OSXIpAddress& rhs) const;
		/// greater-then operator
		bool operator>(const OSXIpAddress& rhs) const;
		/// extract host name and port number from URI
		void ExtractFromUri(const IO::URI& uri);
		/// set host name
		void SetHostName(const Util::String& hostName);
		/// get host name
		const Util::String& GetHostName() const;
		/// set port number
		void SetPort(ushort port);
		/// get port number
		ushort GetPort() const;
		/// get the ip address resulting from the host name as string
		const Util::String& GetHostAddr() const;
        
	private:
		friend class Win360Socket;
        
		/// construct from sockaddr_in struct
		//OSXIpAddress(const sockaddr_in& addr);
		/// set sockaddr_in directly
		//void SetSockAddr(const sockaddr_in& addr);
		/// get sockaddr_in field
		//const sockaddr_in& GetSockAddr() const;
		/// perform address resolution, understands special host names
		//static bool GetHostByName(const Util::String& hostName, in_addr& outAddr);
		/// return true if an address is an internet address (not class A,B,C)
		//static bool IsInetAddr(const in_addr* addr);
        
		Util::String hostName;
		Util::String addrAsString;
		//sockaddr_in addr;
	};
    
	//------------------------------------------------------------------------------
	/**
     */
	inline bool
    OSXIpAddress::operator==(const OSXIpAddress& rhs) const
	{
		return false;
	}
    
	//------------------------------------------------------------------------------
	/**
     */
	inline bool
    OSXIpAddress::operator<(const OSXIpAddress& rhs) const
	{
		return false;
	}
    
	//------------------------------------------------------------------------------
	/**
     */
	inline bool
    OSXIpAddress::operator>(const OSXIpAddress& rhs) const
	{
		return false;
	}
    
} // namespace Win360

#endif