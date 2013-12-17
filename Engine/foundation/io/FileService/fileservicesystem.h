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
#pragma once
#include "core/refcounted.h"
#include "core/singleton.h"
#include "util/dictionary.h"
#include "io/uri.h"
#include "fsapi/lfs_api.h"
//------------------------------------------------------------------------------
namespace IO
{

class Archive;
class FileServiceSystem : public Core::RefCounted
{
#ifdef WIN32
    __DeclareClass(FileServiceSystem);
    __DeclareImageSingleton(FileServiceSystem);
#endif // WIN32
public:
    /// constructor
    FileServiceSystem();
    /// destructor
    virtual ~FileServiceSystem();

    /// setup the archive file system
    void Setup();
    /// discard the archive file system
    void Discard();
    /// return true if archive file system has been setup
    bool IsValid() const;

	/// download file from fileservice 
	FileService::FsHandle DownloadFile(const URI& uri, int& error);

	FileService::EAccessState FileAccessState(const FileService::FsHandle& hdl);

	void SetFileServiceDir(const Util::String& dir);
	const Util::String& GetFileServiceDir() const;

	void SetServerAddress(const Util::String& address);
	const Util::String& GetServerAddress() const;

	void SetCacheDir(const Util::String& dir);
	const Util::String& GetCacheDir() const;

protected:
    Threading::CriticalSection critSect;
	Util::Dictionary<Util::String,long long> filehandlemap;

	Util::String fileServiceDir;
	Util::String cacheDir;
	Util::String serverAddress;

    bool isValid;
};

//------------------------------------------------------------------------------
/**
*/
inline 
bool FileServiceSystem::IsValid() const
{
    return this->isValid;
}
inline
void FileServiceSystem::SetFileServiceDir(const Util::String& dir)
{
	fileServiceDir = dir;
}
inline
const Util::String& FileServiceSystem::GetFileServiceDir() const
{
	return fileServiceDir;
}
inline
void FileServiceSystem::SetServerAddress(const Util::String& address)
{
	serverAddress = address;
}

inline
const Util::String& FileServiceSystem::GetServerAddress() const
{
	return serverAddress;
}
inline
void FileServiceSystem::SetCacheDir(const Util::String& dir)
{
	cacheDir = dir;
}
inline
const Util::String& FileServiceSystem::GetCacheDir() const
{
	return cacheDir;
}

} // namespace IO
//------------------------------------------------------------------------------
