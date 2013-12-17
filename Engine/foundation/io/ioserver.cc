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
#include "stdneb.h"
#include "io/ioserver.h"
#include "core/ptr.h"
#include "io/fswrapper.h"
#include "util/stack.h"
#include "util/crc.h"
#include "system/systeminfo.h"
#include "io/filestream.h"
#include "io/memorystream.h"
#include "io/archfs/archive.h"
#include "io/archfs/archivefilesystem.h"
#include "io/FileService/fileservicesystem.h"

#include "packageTool/PackageSystem.h"

namespace IO
{
__ImplementClass(IO::IoServer, 'IOSV', Core::RefCounted);
__ImplementThreadSingleton(IO::IoServer);

//Threading::CriticalSection IoServer::AssignCriticalSection;
//Threading::CriticalSection IoServer::SchemeCriticalSection;
Threading::CriticalSection IoServer::ArchiveCriticalSection;

//// begin by ZengZhuo 2011.11.4
//Threading::CriticalSection IoServer::fileServiceCriticalSection ;
//// end by ZengZhuo

bool IoServer::StandardArchivesMounted = false;

using namespace Core;
using namespace Util;

 
//------------------------------------------------------------------------------
/**
*/
IoServer::IoServer() :
    archiveFileSystemEnabled(true)
	//// [begin] by ZengZhuo 2011.11.4
	,fileServiceSystemEnabled(false)
	//// [end] by ZengZhuo

{
    __ConstructThreadSingleton;

    // the first IoServer created sets up the global assign registry
    //AssignCriticalSection.Enter();
    //if (!AssignRegistry::HasInstance())
    //{
    //    this->assignRegistry = AssignRegistry::Create();
    //    this->assignRegistry->Setup();
    //}
    //else
    //{
    //    // global assign registry already exists
    //    this->assignRegistry = AssignRegistry::Instance();
    //}
    //AssignCriticalSection.Leave();

    // the first IoServer sets up the global scheme registry
    //SchemeCriticalSection.Enter();
    //if (!SchemeRegistry::HasInstance())
    //{
    //    this->schemeRegistry = SchemeRegistry::Create();
    //    this->schemeRegistry->Setup();
    //}
    //else
    //{
    //    this->schemeRegistry = SchemeRegistry::Instance();
    //}    
    //SchemeCriticalSection.Leave();

    //ArchiveCriticalSection.Enter();
    //if (!ArchiveFileSystem::HasInstance())
    //{
    //    n_assert(!StandardArchivesMounted);
    //    this->archiveFileSystem = ArchiveFileSystem::Create();
    //    this->archiveFileSystem->Setup();
    //}
    //else
    //{
    //    this->archiveFileSystem = ArchiveFileSystem::Instance();
    //}
    //ArchiveCriticalSection.Leave();
}

//------------------------------------------------------------------------------
/**
*/
IoServer::~IoServer()
{
    //// unmount standard archives if this is the last instance
    //if (StandardArchivesMounted && (this->archiveFileSystem->GetRefCount() == 1))
    //{
    //    this->UnmountStandardArchives();
    //}
    //this->archiveFileSystem = 0;    
	
	this->fileServiceSystem = 0;

    //this->assignRegistry = 0;
    //this->schemeRegistry = 0;

    __DestructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void
IoServer::SetupFileService(const Util::String& fileServiceDir, const Util::String& cacheDir, const Util::String& serverAddress)
{
#ifdef __WIN32__

	n_assert(false == fileServiceSystemEnabled);
	n_assert(NULL == fileServiceSystem);

	this->fileServiceSystem = FileServiceSystem::Create() ;
	this->fileServiceSystem->SetFileServiceDir(fileServiceDir);
	this->fileServiceSystem->SetServerAddress(serverAddress);
	this->fileServiceSystem->SetCacheDir(cacheDir);
	this->fileServiceSystem->Setup();
	fileServiceSystemEnabled = this->fileServiceSystem->IsValid();//true;

#endif // __WIN32__

}

//------------------------------------------------------------------------------
/**
*/

GPtr<Stream>
IoServer::CreateFileStream(const URI& uri) const
{
    n_assert(!uri.IsEmpty());
    //n_assert(SchemeRegistry::Instance()->IsUriSchemeRegistered(uri.Scheme()));
    //SchemeRegistry* schemeRegistry = SchemeRegistry::Instance();

    // check if the URI points into a mounted archive

	//Util::String fn = uri.GetHostAndLocalPath() ;

	//// This piece of code is hacking... so do not care ...
 //   if (this->IsArchiveFileSystemEnabled())
 //   {
 //       URI newUri = ArchiveFileSystem::Instance()->ConvertFileToArchiveURIIfExists(uri);
 //       GPtr<Stream> stream = (Stream*) schemeRegistry->GetStreamClassByUriScheme(newUri.Scheme()).Create();
 //       stream->SetURI(newUri);
 //       return stream;
 //   }
 //   else
 //   {
        GPtr<Stream> stream = FileStream::Create();//(Stream*) schemeRegistry->GetStreamClassByUriScheme(uri.Scheme()).Create();
        stream->SetURI(uri);
        return stream;
    //}
}

//------------------------------------------------------------------------------
/**
*/
bool
IoServer::MountArchive(const URI& uri)
{
    //GPtr<Archive> archive = this->archiveFileSystem->Mount(uri);
    //return archive.isvalid();
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
IoServer::UnmountArchive(const URI& uri)
{
    //this->archiveFileSystem->Unmount(uri);
}

//------------------------------------------------------------------------------
/**
*/
bool
IoServer::IsArchiveMounted(const URI& uri) const
{
    //return this->archiveFileSystem->IsMounted(uri);
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
IoServer::MountStandardArchives()
{
    ArchiveCriticalSection.Enter();
    n_assert(!StandardArchivesMounted);
    StandardArchivesMounted = true;

    ArchiveCriticalSection.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
IoServer::UnmountStandardArchives()
{
    ArchiveCriticalSection.Enter();
    n_assert(StandardArchivesMounted);
    StandardArchivesMounted = false;

    ArchiveCriticalSection.Leave();
}

bool IoServer::IsFileServiceSystemEnabled() const
{
	return fileServiceSystemEnabled ;
}
//// [end] by ZengZhuo

//------------------------------------------------------------------------------
/**
    This method creates all missing directories in a path.
*/
bool
IoServer::CreateDirectory(const URI& uri) const
{
    n_assert(uri.Scheme() == "file");
    String path = uri.GetHostAndLocalPath();

    // build stack of non-existing dir components
    Stack<String> pathStack;
    while ((!path.IsEmpty()) && (!this->DirectoryExists(path)))
    {
        pathStack.Push(path);
        String nextPath = path.ExtractDirName();
        nextPath.TrimRight("/\\:");
        if ((nextPath == path) || FSWrapper::IsDeviceName(nextPath))
        {
            break;
        }
        path = nextPath;
    }

    // error in original path?
    if (path.IsEmpty())
    {
        return false;
    }

    // create missing directory components
    while (!pathStack.IsEmpty())
    {
        String curPath = pathStack.Pop();
        if (!FSWrapper::CreateDirectory(curPath))
        {
            return false;
        }
    }
    return true;
}

//------------------------------------------------------------------------------
/**
    This copies a file to another file.
*/
bool
IoServer::CopyFile(const URI& fromUri, const URI& toUri) const
{
    // transparent archive support...
    URI srcUri;
    //if (this->IsArchiveFileSystemEnabled())
    //{
    //    srcUri = ArchiveFileSystem::Instance()->ConvertFileToArchiveURIIfExists(fromUri);
    //}
    //else
    //{
        srcUri = fromUri;
    //}

    // if target file exists, remove read-only flag
    if (this->FileExists(toUri))
    {
        this->SetReadOnly(toUri, false);
    }

    // create file streams
    GPtr<Stream> srcStream = this->CreateFileStream(srcUri);
    srcStream->SetAccessMode(Stream::ReadAccess);
    if (srcStream->Open())
    {
        GPtr<Stream> toStream = this->CreateFileStream(toUri);
        toStream->SetAccessMode(Stream::WriteAccess);
        if (toStream->Open())
        {
            // allocate a buffer, and copy contents in a loop
            const int bufSize = 1024 * 1024;
            void* buffer = Memory::Alloc(Memory::ScratchHeap, bufSize);
            while (!srcStream->Eof())
            {
                Stream::Size bytesRead = srcStream->Read(buffer, bufSize);
                toStream->Write(buffer, bytesRead);
            }
            Memory::Free(Memory::ScratchHeap, buffer);
            toStream->Close();
        }
        else
        {
            n_error("IO::IoServer::CopyFile(): could not open target file '%s'", toUri.AsString().AsCharPtr());
            return false;
        }
        srcStream->Close();
    }
    else
    {
        n_error("IO::IoServer::CopyFile(): could not open source file '%s'", fromUri.AsString().AsCharPtr());
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------
/**
    This method computes the CRC checksum for a file.
*/
unsigned int
IoServer::ComputeFileCrc(const URI& uri) const
{
    unsigned int result = 0;

    // create a stream
    GPtr<Stream> stream = this->CreateFileStream(uri);
    stream->SetAccessMode(Stream::ReadAccess);
    if (stream->Open())
    {
        Crc crc;
        crc.Begin();
        const int bufSize = (1<<16);
        unsigned char* buffer = (unsigned char*) Memory::Alloc(Memory::ScratchHeap, bufSize);
        while (!stream->Eof())
        {
            Stream::Size bytesRead = stream->Read(buffer, bufSize);
            crc.Compute(buffer, bytesRead);
        }
        Memory::Free(Memory::ScratchHeap, buffer);
        crc.End();
        result = crc.GetResult();
        stream->Close();
    }
    else
    {
        n_error("IO::IoServer::ComputeFileCrc(): could not open file '%s'!", uri.AsString().AsCharPtr());
    }
    return result;
}

//------------------------------------------------------------------------------
/**
*/
bool
IoServer::DeleteFile(const URI& uri) const
{
    n_assert(uri.Scheme() == "file");
    const String path = uri.GetHostAndLocalPath();
    n_assert(path.IsValid());
    return FSWrapper::DeleteFile(path);
}

//------------------------------------------------------------------------------
/**
*/
bool
IoServer::DeleteDirectory(const URI& uri) const
{
    n_assert(uri.Scheme() == "file");
    const String path = uri.GetHostAndLocalPath();
    n_assert(path.IsValid());
    return FSWrapper::DeleteDirectory(path);
}

//------------------------------------------------------------------------------
/**
*/
bool
IoServer::FileExists(const URI& uri) const
{
    //// transparent archive support
    //if (this->IsArchiveFileSystemEnabled())
    //{
    //    GPtr<Archive> archive = ArchiveFileSystem::Instance()->FindArchiveWithFile(uri);
    //    if (archive.isvalid())
    //    {
    //        return true;
    //    }
    //}

    // doesn't exist as archive, check conventional filesystem
    const String path = uri.GetHostAndLocalPath();
    n_assert(path.IsValid());
    return FSWrapper::FileExists(path);
}

bool
IoServer::FileExists(const Util::StringAtom& path) const
{
	if (Pack::PackageSystem::PackageIsOpened())
	{
		return Pack::PackageSystem::IsFileExit(path.Value());
	}
	return FileExists(URI(path.Value()));
}

//------------------------------------------------------------------------------
/**
*/
bool
IoServer::DirectoryExists(const URI& uri) const
{
    // transparent archive support
    //if (this->IsArchiveFileSystemEnabled())
    //{
    //    if (uri.Scheme() == "file")
    //    {
    //        GPtr<Archive> archive = ArchiveFileSystem::Instance()->FindArchiveWithDir(uri);
    //        if (archive.isvalid())
    //        {
    //            return true;
    //        }
    //    }
    //}

    // doesn't exist as archive, check conventional filesystem
    const String path = uri.GetHostAndLocalPath();
    n_assert(path.IsValid());
    return FSWrapper::DirectoryExists(path);
}

//------------------------------------------------------------------------------
/**
*/
void
IoServer::DoWork()
{
#ifdef __WIN32__
	for (int i = asynCheckFiles.Size() - 1; i > -1; --i)
	{
		_check_file_info& info = asynCheckFiles[i];
		FileService::EAccessState state = fileServiceSystem->FileAccessState(info.fs_handle);
		switch (state)
		{
		case FileService::EAccessState_Downloading:
			{
			}
			break;
		case FileService::EAccessState_Error:
			{
				info.stream->SetHandled(true);
				asynCheckFiles.EraseIndex(i);
			}
			break;
		case FileService::EAccessState_OK:
			{
				readStream(info.stream);
				info.stream->SetHandled(true);
				asynCheckFiles.EraseIndex(i);
			}
			break;
		default:
			{
				info.stream->SetHandled(true);
				asynCheckFiles.EraseIndex(i);
			}
			break;
		}
	}
#endif
}

//------------------------------------------------------------------------------
/**
*/
bool 
IoServer::_WriteStream(const GPtr<IO::WriteStream>& msg)
{

	// create a destination file stream object
	GPtr<Stream> dstStream = NULL;
	if (msg->GetURI().IsValid())
	{
		dstStream = IO::IoServer::Instance()->CreateFileStream(msg->GetURI());	
	}
	else
	{
		dstStream = IO::IoServer::Instance()->CreateFileStream(URI(msg->GetFileName().Value()));
	}

	dstStream->SetAccessMode(Stream::WriteAccess);
	if (dstStream->Open())
	{
		/// @todo handle non-mappable stream
		const GPtr<Stream>& srcStream = msg->GetStream();
		n_assert(srcStream.isvalid());
		n_assert(srcStream->CanBeMapped());
		srcStream->SetAccessMode(Stream::ReadAccess);
		if (srcStream->Open())
		{
			void* ptr = srcStream->Map();
			dstStream->Write(ptr, srcStream->GetSize());
			srcStream->Unmap();
			srcStream->Close();
			msg->SetResult(true);

			dstStream->Close();
			return true;
		}     
		dstStream->Close();
	}
	return false;
}
//------------------------------------------------------------------------------
/**
*/
GPtr<Stream>
IoServer::ReadFileFromFileSystem(const Util::StringAtom& resourceId) const
{
	return ReadFileFromFileSystem(resourceId.Value());
}

GPtr<Stream>
IoServer::ReadFileFromFileSystem(const Util::String& resourceId) const
{
	return ReadFileFromFileSystem(resourceId.AsCharPtr());
}

GPtr<Stream>
IoServer::ReadFileFromFileSystem(const char* resourceId) const
{
	if (Pack::PackageSystem::PackageIsOpened())
	{
		GPtr<Stream> memStream = IO::MemoryStream::Create();
		bool result = Pack::PackageSystem::GetFileInPackageThreadSafe(resourceId, memStream);
		if (result)
		{
			return memStream;
		}
		return NULL;
	}
	return ReadFileFromDisk(URI(resourceId));
}

GPtr<Stream>
IoServer::ReadFileFromDisk(const IO::URI& uri) const
{
	GPtr<Stream> srcStream = CreateFileStream(uri);
	srcStream->SetAccessMode(Stream::ReadAccess);
	if (srcStream->Open())
	{		
		GPtr<Stream> memStream = IO::MemoryStream::Create();
		memStream->SetAccessMode(Stream::WriteAccess);
		if (memStream->Open())
		{
			SizeT srcSize = srcStream->GetSize();
			memStream->SetSize(srcSize);
			if (srcSize > 0)
			{
				void* ptr = memStream->Map();
				n_assert(0 != ptr);
				srcStream->Read(ptr, srcSize);
				memStream->Unmap();
			}
			memStream->Close();
			srcStream->Close();
			return srcStream;
		}
	}
	return NULL;
}

GPtr<Stream>
IoServer::ReadFile(const Util::String& path) const
{
	GPtr<Stream> result = ReadFileFromFileSystem(Util::StringAtom(path.AsCharPtr()));
	if (!result)
	{
		result = ReadFileFromDisk(URI(path.AsCharPtr()));
	}
	return result;
}

GPtr<Stream>
	IoServer::ReadFile(const char* resourceId) const
{
	GPtr<Stream> result = ReadFileFromFileSystem(resourceId);
	if (!result)
	{
		result = ReadFileFromDisk(URI(resourceId));
	}
	return result;
}

//------------------------------------------------------------------------------
/**
*/
bool
IoServer::_ReadStream(const ReadStreamPtr& msg)
{
	msg->SetResult(false);
	bool result = false;
	if (Pack::PackageSystem::PackageIsOpened())
	{
		result = Pack::PackageSystem::GetFileInPackage(msg->GetFileName().Value(), msg->GetStream());
		if (result)
		{
			msg->SetResult(result);
			msg->SetHandled(true);
			return result;
		}
	}

	const IO::URI& tmpUri = URI(msg->GetFileName().Value());
	if (IsFileServiceSystemEnabled())
	{
#if __WIN32__
		asynFsCheck(msg);
		return true;
#endif
	}

	result = readStream(msg);
	msg->SetHandled(true);
	return result;
}


//------------------------------------------------------------------------------
/**
*/
bool
IoServer::readStream(const ReadStreamPtr& msg)
{	
	GPtr<Stream> srcStream = CreateFileStream(URI(msg->GetFileName().Value()));
	srcStream->SetAccessMode(Stream::ReadAccess);
	if (srcStream->Open())
	{
		Stream::Size srcSize = srcStream->GetSize();
		if ( srcSize > 0 )
		{		
			/// @todo handle non-mappable stream!
			const GPtr<Stream>& dstStream = msg->GetStream();
			n_assert(dstStream.isvalid());
			n_assert(dstStream->CanBeMapped());
			dstStream->SetAccessMode(Stream::WriteAccess);
			//dstStream->SetURI(URI(msg->GetFileName().Value()));
			if (dstStream->Open())
			{
				dstStream->SetSize(srcSize);
				void* ptr = dstStream->Map();
				n_assert(0 != ptr);
				srcStream->Read(ptr, srcSize);
				dstStream->Unmap();
				dstStream->Close();
				msg->SetResult(true);
				srcStream->Close();
				return true;
			}
		}
		srcStream->Close();
	}
	return false;
}

//------------------------------------------------------------------------------
/**
*/
void
IoServer::asynFsCheck(const ReadStreamPtr& msg)
{
#if __WIN32__
	int error;
	_fs_handle hnd = fileServiceSystem->DownloadFile(URI(msg->GetFileName().Value()), error);

	if (0 == error)
	{	
		asynCheckFiles.Append(_check_file_info());
		_check_file_info& back = asynCheckFiles.Back();
		back.stream = msg;
		back.fs_handle = hnd;
	}
	else
	{
		msg->SetHandled(true);
	}
#endif
}

//------------------------------------------------------------------------------
/**
*/
void
IoServer::SetReadOnly(const URI& uri, bool readOnly) const
{
    n_assert(uri.Scheme() == "file");
    const String path = uri.GetHostAndLocalPath();
    n_assert(path.IsValid());
    FSWrapper::SetReadOnly(path, readOnly);
}

//------------------------------------------------------------------------------
/**
*/
bool
IoServer::IsReadOnly(const URI& uri) const
{
    n_assert(uri.Scheme() == "file");

    // transparent archive file system support
    //if (this->IsArchiveFileSystemEnabled())
    //{
    //    URI arcUri = ArchiveFileSystem::Instance()->ConvertFileToArchiveURIIfExists(uri);
    //    if (arcUri.Scheme() != "file")
    //    {
    //        // file exists in archive, archives are generally read only
    //        return true;
    //    }
    //}

    // file not in archive, handle conventionally
    const String path = uri.GetHostAndLocalPath();
    n_assert(path.IsValid());
    return FSWrapper::IsReadOnly(path);
}

//------------------------------------------------------------------------------
/**
*/
void
IoServer::SetFileWriteTime(const URI& uri, FileTime fileTime)
{
    n_assert(uri.Scheme() == "file");
    const String path = uri.GetHostAndLocalPath();
    n_assert(path.IsValid());
    FSWrapper::SetFileWriteTime(path, fileTime);
}

//------------------------------------------------------------------------------
/**
*/
FileTime
IoServer::GetFileWriteTime(const URI& uri) const
{
    n_assert(uri.Scheme() == "file");
    const String path = uri.GetHostAndLocalPath();
    n_assert(path.IsValid());
    return FSWrapper::GetFileWriteTime(path);
}

//------------------------------------------------------------------------------
/**
*/
Array<String>
IoServer::ListFiles(const URI& uri, const String& pattern, bool asFullPath) const
{
    n_assert(pattern.IsValid());
    Array<String> result;

    // transparent archive file system support
    //if (this->IsArchiveFileSystemEnabled())
    //{
    //    GPtr<Archive> archive = ArchiveFileSystem::Instance()->FindArchiveWithDir(uri);
    //    if (archive.isvalid())
    //    {
    //        String pathInArchive = archive->ConvertToPathInArchive(uri.LocalPath());
    //        result = archive->ListFiles(pathInArchive, pattern);
    //        if (asFullPath)
    //        {
    //            result = this->addPathPrefixToArray(uri.LocalPath(), result);
    //        }
    //        return result;
    //    }
    //}

    // fallthrough: not contained in archive, handle conventionally
    result = FSWrapper::ListFiles(uri.GetHostAndLocalPath(), pattern);
    if (asFullPath)
    {
        result = this->addPathPrefixToArray(uri.LocalPath(), result);
    }
    return result;
}

//------------------------------------------------------------------------------
/**
*/
Array<String>
IoServer::ListDirectories(const URI& uri, const String& pattern, bool asFullPath) const
{
    n_assert(pattern.IsValid());
    Array<String> result;

    // transparent archive file system support
    //if (this->IsArchiveFileSystemEnabled())
    //{
    //    GPtr<Archive> archive = ArchiveFileSystem::Instance()->FindArchiveWithDir(uri);
    //    if (archive.isvalid())
    //    {
    //        String pathInArchive = archive->ConvertToPathInArchive(uri.LocalPath());
    //        result = archive->ListDirectories(pathInArchive, pattern);
    //        if (asFullPath)
    //        {
    //            result = this->addPathPrefixToArray(uri.LocalPath(), result);
    //        }
    //        return result;
    //    }
    //}
    
    // fallthrough: not contained in archive, handle conventionally
    result = FSWrapper::ListDirectories(uri.GetHostAndLocalPath(), pattern);
    if (asFullPath)
    {
        result = this->addPathPrefixToArray(uri.LocalPath(), result);
    }
    return result;
}

//------------------------------------------------------------------------------
/**
*/
Array<String>
IoServer::addPathPrefixToArray(const String& prefix, const Array<String>& filenames) const
{
    Array<String> result;
    if (!filenames.IsEmpty())
    {
        result.Reserve(filenames.Size());
        IndexT i;
        for (i = 0; i < filenames.Size(); i++)
        {
            String path = prefix;
            path.Append("/");
            path.Append(filenames[i]);
            result.Append(path);
        }
    }
    return result;
}

} // namespace IO
