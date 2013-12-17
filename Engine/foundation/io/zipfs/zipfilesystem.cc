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
#include "io/zipfs/zipfilesystem.h"
#include "io/ioserver.h"
#include "io/archfs/archive.h"
#include "io/zipfs/zipfilestream.h"

namespace IO
{
__ImplementClass(IO::ZipFileSystem, 'ZPFS', IO::ArchiveFileSystemBase);
__ImplementImageSingleton(IO::ZipFileSystem);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
ZipFileSystem::ZipFileSystem()
{
    __ConstructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
ZipFileSystem::~ZipFileSystem()
{
    if (this->IsValid())
    {
        this->Discard();
    }
    __DestructImageSingleton;
}

//------------------------------------------------------------------------------
/**
    Setup the ZipFileSystem. Registers the ZipFileStream class.
*/
void
ZipFileSystem::Setup()
{
    n_assert(!this->IsValid());
    ArchiveFileSystemBase::Setup();
    SchemeRegistry::Instance()->RegisterUriScheme("zip", ZipFileStream::RTTI);
}

//------------------------------------------------------------------------------
/**
*/
void
ZipFileSystem::Discard()
{
    n_assert(this->IsValid());
    SchemeRegistry::Instance()->UnregisterUriScheme("zip");
    ArchiveFileSystemBase::Discard();
}

//------------------------------------------------------------------------------
/**
    This method takes a normal file URI and checks if the local path
    of the URI is contained as file entry in any mounted zip archive. If yes
    ptr to the zip archive is returned, otherwise a 0 pointer. NOTE: if the 
    same path resides in several zip archives, it is currently not defined
    which one will be returned (the current implementation returns the
    first zip archive in alphabetical order which contains the file).
*/
GPtr<Archive>
ZipFileSystem::FindArchiveWithFile(const URI& uri) const
{
    // get the local path from the URI
    String localPath = AssignRegistry::Instance()->ResolveAssigns(uri).LocalPath();
    n_assert(localPath.IsValid());

    // check each mounted archive
    GPtr<ZipArchive> result;
    this->critSect.Enter();
    IndexT i;
    for (i = 0; (i < this->archives.Size()) && (!result.isvalid()); i++)
    {
        const GPtr<ZipArchive>& arch = this->archives.ValueAtIndex(i).cast<ZipArchive>();
        String pathInZipArchive = arch->ConvertToPathInArchive(localPath);
        if (pathInZipArchive.IsValid())
        {
            if (0 != arch->FindFileEntry(pathInZipArchive))
            {
                result = arch;
                break;
            }
        }
    }
    this->critSect.Leave(); 

    // result may be invalid pointer at this point
    return result.cast<Archive>();
}

//------------------------------------------------------------------------------
/**
    Same as FindArchiveWithFile(), but checks for a directory entry 
    in a zip file.
*/
GPtr<Archive>
ZipFileSystem::FindArchiveWithDir(const URI& uri) const
{
    // get the local path from the URI
    String localPath = AssignRegistry::Instance()->ResolveAssigns(uri).LocalPath();
    n_assert(localPath.IsValid());

    // check each mounted archive
    GPtr<ZipArchive> result;
    this->critSect.Enter();
    IndexT i;
    for (i = 0; (i < this->archives.Size()) && (!result.isvalid()); i++)
    {
        const GPtr<ZipArchive>& arch = this->archives.ValueAtIndex(i).cast<ZipArchive>();
        String pathInZipArchive = arch->ConvertToPathInArchive(localPath);
        if (pathInZipArchive.IsValid())
        {
            if (0 != arch->FindDirEntry(pathInZipArchive))
            {
                result = arch;
                break;
            }
        }
    }
    this->critSect.Leave(); 

    // result may be invalid pointer at this point
    return result.cast<Archive>();
}

} // namespace IO
