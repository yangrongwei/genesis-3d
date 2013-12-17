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
#pragma once
//------------------------------------------------------------------------------
/**
    @class IO::IoServer
  
    The central server object of the IO subsystem offers the following
    services:

    * associate stream classes with URI schemes
    * create the right stream object for a given URI
    * transparant (ZIP) archive support
    * path assign management
    * global filesystem manipulation and query methods

*/
#include "core/refcounted.h"
#include "core/singleton.h"
#include "util/array.h"
#include "util/string.h"
#include "util/hashtable.h"
#include "io/filetime.h"
#include "io/assign.h"
#include "util/stringatom.h"
#include "io/assignregistry.h"
#include "io/schemeregistry.h"
#include "io/iointerfaceprotocol.h"
#include "fileservice/fileservicesystem.h"
#include "packageTool/PackageSystem.h"
//------------------------------------------------------------------------------
namespace IO
{

class ArchiveFileSystem;

//// [begin] by ZengZhuo 2011.11.4
class FileServiceSystem;
//// [end] by ZengZhuo

class Stream;
class URI;

class IoServer : public Core::RefCounted
{
    __DeclareClass(IoServer);
    __DeclareThreadSingleton(IoServer);
public:
	typedef GPtr<IO::ReadStream> ReadStreamPtr;
    /// constructor
    IoServer();
    /// destructor
    virtual ~IoServer();

	void DoWork();

	/// setup FileService
	void SetupFileService(const Util::String& fileServiceDir, const Util::String& cacheDir, const Util::String& serverAddress);
    /// mount a file archive (without archive file extension!)
    bool MountArchive(const URI& uri);
    /// unmount a file archive (without archive file extension!)
    void UnmountArchive(const URI& uri);
    /// return true if a archive is mounted (without archive file extension!)
    bool IsArchiveMounted(const URI& uri) const;
    /// enable/disable transparent archive filesystem layering (default is yes)
    void SetArchiveFileSystemEnabled(bool b);
    /// return true if transparent archive filesystem is enabled
    bool IsArchiveFileSystemEnabled() const;
    /// mount standard archives (e.g. home:export.zip and home:export_$(platform).zip)
    void MountStandardArchives();
    /// unmount standard archives
    void UnmountStandardArchives();

	bool IsFileServiceSystemEnabled() const;
	//// [end] by ZengZhuo

    /// create a stream object for the given uri
    GPtr<Stream> CreateFileStream(const URI& uri) const;



    /// create all missing directories in the path
    bool CreateDirectory(const URI& uri) const;
    /// delete an empty directory
    bool DeleteDirectory(const URI& path) const;
    /// return true if directory exists
    bool DirectoryExists(const URI& path) const;

	GPtr<Stream> ReadFileFromFileSystem(const Util::StringAtom& resourceId) const;

	GPtr<Stream> ReadFileFromFileSystem(const char* resourceId) const;

	GPtr<Stream> ReadFileFromFileSystem(const Util::String& resourceId) const;

	GPtr<Stream> ReadFileFromDisk(const IO::URI& uri) const;

	//if can't be found in file system, try in disk.
	GPtr<Stream> ReadFile(const Util::String& path) const;

	GPtr<Stream> ReadFile(const char* resourceId) const;

    /// copy a file
    bool CopyFile(const URI& from, const URI& to) const;
    /// delete a file
    bool DeleteFile(const URI& path) const;
    /// return true if file exists
    bool FileExists(const URI& path) const;
	bool FileExists(const Util::StringAtom& path) const;
    /// set the readonly status of a file
    void SetReadOnly(const URI& path, bool b) const;
    /// return read only status of a file
    bool IsReadOnly(const URI& path) const;
    /// get the CRC checksum of a file
    unsigned int ComputeFileCrc(const URI& path) const;
    /// set the write-time of a file
    void SetFileWriteTime(const URI& path, FileTime fileTime);
    /// return the last write-time of a file
    FileTime GetFileWriteTime(const URI& path) const;

    /// list all files matching a pattern in a directory
    Util::Array<Util::String> ListFiles(const URI& dir, const Util::String& pattern, bool asFullPath=false) const;
    /// list all subdirectories matching a pattern in a directory
    Util::Array<Util::String> ListDirectories(const URI& dir, const Util::String& pattern, bool asFullPath=false) const;

	/// WriteStream 
	bool _WriteStream(const GPtr<IO::WriteStream>& msg);
	/// ReadStream 
	bool _ReadStream(const ReadStreamPtr& msg);
private:
	struct _check_file_info;
	typedef FileService::FsHandle _fs_handle;
	typedef Util::Array<_check_file_info> AsynCheckFiles;

    /// helper function to add path prefix to file or dir names in array
    Util::Array<Util::String> addPathPrefixToArray(const Util::String& prefix, const Util::Array<Util::String>& filenames) const;

	void asynFsCheck(const ReadStreamPtr& msg);

	bool readStream(const ReadStreamPtr& msg);

	bool readStream(GPtr<Stream>& stream);

	struct _check_file_info
	{
		ReadStreamPtr stream;
		_fs_handle fs_handle; 
		_check_file_info()
			:stream(NULL)
			,fs_handle(0)
		{

		}
	};



    //GPtr<ArchiveFileSystem> archiveFileSystem;
	GPtr<FileServiceSystem> fileServiceSystem ;
	//GPtr<AssignRegistry> assignRegistry;
	//GPtr<SchemeRegistry> schemeRegistry;
	AsynCheckFiles asynCheckFiles;

	bool fileServiceSystemEnabled;
    bool archiveFileSystemEnabled;

    static Threading::CriticalSection ArchiveCriticalSection;
    //static Threading::CriticalSection fileServiceCriticalSection;
    static bool StandardArchivesMounted;
    //static Threading::CriticalSection AssignCriticalSection;
    //static Threading::CriticalSection SchemeCriticalSection;
};

//------------------------------------------------------------------------------
/**
    NOTE: on platforms which provide transparent archive access this method
    is point less (the archiveFileSystemEnabled flag will be ignored, and
    IsArchiveFileSystemEnabled() will always return false).
*/
inline void
IoServer::SetArchiveFileSystemEnabled(bool b)
{
    this->archiveFileSystemEnabled = b;
}

//------------------------------------------------------------------------------
/**
    NOTE: on platforms which provide transparent archive access through
    the OS (like on PS3) this method will always return false. This saves
    some unecessary overhead in the Nebula3 IoServer.
*/
inline bool
IoServer::IsArchiveFileSystemEnabled() const
{
    #if NEBULA3_NATIVE_ARCHIVE_SUPPORT
        return false;
    #else
        return this->archiveFileSystemEnabled;
    #endif
}

} // namespace IO
//------------------------------------------------------------------------------
