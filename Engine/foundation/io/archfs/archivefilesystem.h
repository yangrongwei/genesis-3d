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
    @class IO::ArchiveFileSystem
    
    Top-level platform wrapper class of archive file systems. 
    
*/
#if __WIN32__ || __XBOX360__
#include "io/zipfs/zipfilesystem.h"
namespace IO
{
class ArchiveFileSystem : public ZipFileSystem
{
    __DeclareClass(ArchiveFileSystem);
    __DeclareImageSingleton(ArchiveFileSystem);
public:
    /// constructor
    ArchiveFileSystem();
    /// destructor
    virtual ~ArchiveFileSystem();
};
}
#elif __WII__
#include "io/wii/wiiarchivefilesystem.h"
namespace IO
{
class ArchiveFileSystem : public Wii::WiiArchiveFileSystem
{
    __DeclareClass(ArchiveFileSystem);
    __DeclareImageSingleton(ArchiveFileSystem);
public:
    /// constructor
    ArchiveFileSystem();
    /// destructor
    virtual ~ArchiveFileSystem();
};
}
#elif __PS3__
#include "io/ps3/ps3archivefilesystem.h"
namespace IO
{
class ArchiveFileSystem : public PS3::PS3ArchiveFileSystem
{
    __DeclareClass(ArchiveFileSystem);
    __DeclareImageSingleton(ArchiveFileSystem);
public:
    /// constructor
    ArchiveFileSystem();
    /// destructor
    virtual ~ArchiveFileSystem();
};
}
#elif __ANDROID__
#include "io/zipfs/zipfilesystem.h"
namespace IO
{
class ArchiveFileSystem :public ZipFileSystem
{
	__DeclareClass(ArchiveFileSystem);
	__DeclareImageSingleton(ArchiveFileSystem);
public:
	/// constructor
	ArchiveFileSystem();
	/// destructor
	virtual ~ArchiveFileSystem();
};
}
#elif __OSX__
#include "io/zipfs/zipfilesystem.h"
namespace IO
{
    class ArchiveFileSystem : public ZipFileSystem
    {
        __DeclareClass(ArchiveFileSystem);
        __DeclareImageSingleton(ArchiveFileSystem);
    public:
        /// constructor
        ArchiveFileSystem();
        /// destructor
        virtual ~ArchiveFileSystem();
    };
}
#else
#error "IO::ArchiveFileSystem not implemented on this platform!"
#endif