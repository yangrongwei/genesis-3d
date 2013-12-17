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
    @class IO::ZipArchive
    
    Private helper class for ZipFileSystem to hold per-Zip-archive data.
    Uses the zlib and the minizip lib for zip file access.
    
    Multithreading: access to zlib archives needs to be serialized. A
    ZipArchive objects contains a critical section which it will hand down
    to ZipFileEntry objects.

*/
#include "io/archfs/archivebase.h"
#include "zlib/unzip.h"
#include "io/zipfs/zipfileentry.h"
#include "io/zipfs/zipdirentry.h"

//------------------------------------------------------------------------------
namespace IO
{
#if _ANDROID_
	using namespace Android;
#endif

class ZipArchive : public ArchiveBase
{
    __DeclareClass(ZipArchive);
public:
    /// constructor
    ZipArchive();
    /// destructor
    virtual ~ZipArchive();

    /// setup the archive from an URI
    bool Setup(const URI& uri);
    /// discard the archive
    void Discard();

    /// list all files in a directory in the archive
    Util::Array<Util::String> ListFiles(const Util::String& dirPathInArchive, const Util::String& pattern) const;
    /// list all subdirectories in a directory in the archive
    Util::Array<Util::String> ListDirectories(const Util::String& dirPathInArchive, const Util::String& pattern) const;
    /// convert a "file:" URI into a "zip:" URI pointing into this archive
    URI ConvertToArchiveURI(const URI& fileURI) const;
    /// convert an absolute path to local path inside archive, returns empty string if absPath doesn't point into this archive
    Util::String ConvertToPathInArchive(const Util::String& absPath) const;




	/// parse the table of contents into memory
	void ParseTableOfContents();
	/// add a new file entry, create missing dir entries on the way
	void AddEntry(const Util::String& path);
	/// find a file entry in the zip archive, return 0 if not exists
	const ZipFileEntry* FindFileEntry(const Util::String& pathInZipArchive) const;
	/// find a file entry in the zip archive, return 0 if not exists
	ZipFileEntry* FindFileEntry(const Util::String& pathInZipArchive);
	/// find a directory entry in the zip archive, return 0 if not exists
	const ZipDirEntry* FindDirEntry(const Util::String& pathInZipArchive) const;
private:
    friend class ZipFileSystem;
    friend class ZipFileStream;
#if _ANDROID_
	friend class AndroidArchiveFileSystem;
#endif

    Util::String rootPath;                      // location of the zip archive file
    unzFile zipFileHandle;                      // the zip file handle
    ZipDirEntry rootEntry;                      // the root entry of the zip archive
    Threading::CriticalSection archiveCritSect; // need to serialize access to archive from multiple threads!
};

} // namespace IO
//------------------------------------------------------------------------------
    