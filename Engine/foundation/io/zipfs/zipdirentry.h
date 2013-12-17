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
    @class IO::ZipDirEntry

    A directory entry in a zip arcive. The ZipDirEntry class is thread-safe,
    all public methods can be invoked from on the same object from different
    threads.
*/
#include "core/types.h"
#include "io/zipfs/zipfileentry.h"

//------------------------------------------------------------------------------
namespace IO    
{
class ZipDirEntry
{
public:
    /// constructor
    ZipDirEntry();
    
    /// get the name of the dir entry
    const Util::StringAtom& GetName() const;
    /// find a direct child file entry, return 0 if not exists
    ZipFileEntry* FindFileEntry(const Util::StringAtom& name) const;
    /// find a direct child directory entry, return 0 if not exists
    ZipDirEntry* FindDirEntry(const Util::StringAtom& name) const;
    /// get directory entries
    const Util::Array<ZipDirEntry>& GetDirEntries() const;
    /// get file entries
    const Util::Array<ZipFileEntry>& GetFileEntries() const;
    
private:
    friend class ZipArchive;

    /// set the name of the dir entry
    void SetName(const Util::StringAtom& n);
    /// add a file child entry
    ZipFileEntry* AddFileEntry(const Util::StringAtom& name);
    /// add a directory child entry
    ZipDirEntry* AddDirEntry(const Util::StringAtom& name);

    Util::StringAtom name;
    Util::Array<ZipFileEntry> fileEntries;
    Util::Array<ZipDirEntry> dirEntries;
    Util::Dictionary<Util::StringAtom, IndexT> fileIndexMap;
    Util::Dictionary<Util::StringAtom, IndexT> dirIndexMap;
};

//------------------------------------------------------------------------------
/**
*/
inline void
ZipDirEntry::SetName(const Util::StringAtom& n)
{
    this->name = n;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::StringAtom&
ZipDirEntry::GetName() const
{
    return this->name;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::Array<ZipDirEntry>&
ZipDirEntry::GetDirEntries() const
{
    return this->dirEntries;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::Array<ZipFileEntry>&
ZipDirEntry::GetFileEntries() const
{
    return this->fileEntries;
}


} // namespace IO
//------------------------------------------------------------------------------

    