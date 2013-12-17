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

#if (__WIN32__ || __XBOX360__)
#include "net/win360/win360socket.h"
namespace Net
{
class Socket : public Win360::Win360Socket
{
    __DeclareClass(Socket);
};
}
#elif __WII__
// class doesn't exist on Wii
#elif __PS3__
#include "net/ps3/ps3socket.h"
namespace Net
{
class Socket : public PS3::PS3Socket
{
    __DeclareClass(Socket);
};
}
#elif __ANDROID__
#include "net/android/androidsocket.h"
namespace Net
{
	class Socket : public Android::AndroidSocket
	{
		__DeclareClass(Socket);
	};
}
#elif __OSX__
#include "net/osx/osxsocket.h"
namespace Net
{
	class Socket : public OSX::OSXSocket
	{
		__DeclareClass(Socket);
	};
}
#else
#error "Socket class not implemented on this platform"
#endif
//------------------------------------------------------------------------------
