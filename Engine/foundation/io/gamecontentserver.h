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

#pragma once
//------------------------------------------------------------------------------
/**
    @class IO::GameContentServer
    
    The game content server initializes access to game content on console
    platforms. The GameContentServer must be created by the main thread
    before the first IoServer is created.
*/
#include "core/config.h"
#if (__WIN32__ || __XBOX360__ || __WII__ || __OSX__ || __ANDROID__)
#include "io/base/gamecontentserverbase.h"
namespace IO
{
class GameContentServer : public Base::GameContentServerBase
{
    __DeclareClass(GameContentServer);
    __DeclareImageSingleton(GameContentServer);
public:
    /// constructor
    GameContentServer();
    /// destructor
    virtual ~GameContentServer();
};
}
#elif __PS3__
#include "io/ps3/ps3gamecontentserver.h"
namespace IO
{
class GameContentServer : public PS3::PS3GameContentServer
{
    __DeclareClass(GameContentServer);
    __DeclareImageSingleton(GameContentServer);
public:
    /// constructor
    GameContentServer();
    /// destructor
    virtual ~GameContentServer();
};
}
#else
#error "IO::GameContentServer not implemented on this platform!"
#endif

