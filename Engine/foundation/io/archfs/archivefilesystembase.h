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
    @class Base::ArchiveFileSystemBase
    
    Base class for archive file system wrappers.

*/
#include "core/refcounted.h"
#include "core/singleton.h"
#include "util/dictionary.h"
#include "io/uri.h"
#include "threading/criticalsection.h"

//------------------------------------------------------------------------------
namespace IO
{
class Archive;

class ArchiveFileSystemBase : public Core::RefCounted
{
    __DeclareClass(ArchiveFileSystemBase);
    __DeclareImageSingleton(ArchiveFileSystemBase);
public:
    /// constructor
    ArchiveFileSystemBase();
    /// destructor
    virtual ~ArchiveFileSystemBase();

    /// setup the archive file system
    void Setup();
    /// discard the archive file system
    void Discard();
    /// return true if archive file system has been setup
    bool IsValid() const;
    
    /// mount an archive
    virtual GPtr<Archive> Mount(const URI& uri);
    /// unmount an archive by URI
    virtual void Unmount(const URI& uri);
    /// unmount an archive by pointer
    virtual void Unmount(const GPtr<Archive>& archive);
    /// return true if an archive is mounted
    bool IsMounted(const URI& uri) const;
    
    /// get an array of all mounted archives
    Util::Array<GPtr<Archive> > GetMountedArchives() const;
    /// find a zip archive by its URI, returns invalid ptr if not mounted
    GPtr<Archive> FindArchive(const URI& uri) const;

    /// find first archive which contains the file path
    virtual GPtr<Archive> FindArchiveWithFile(const URI& fileUri) const;
    /// find first archive which contains the directory path
    virtual GPtr<Archive> FindArchiveWithDir(const URI& dirUri) const;
    /// transparently convert a URI pointing to a file into a matching archive URI
    URI ConvertFileToArchiveURIIfExists(const URI& uri) const;
    /// transparently convert a URI pointing to a directory into a matching archive URI    
    URI ConvertDirToArchiveURIIfExists(const URI& uri) const;

protected:
    Threading::CriticalSection critSect;
    Util::Dictionary<Util::String, GPtr<Archive> > archives;
    bool isValid;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
ArchiveFileSystemBase::IsValid() const
{
    return this->isValid;
}

} // namespace IO
//------------------------------------------------------------------------------
