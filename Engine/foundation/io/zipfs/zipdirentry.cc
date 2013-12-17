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
#include "io/zipfs/zipdirentry.h"

namespace IO
{
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
ZipDirEntry::ZipDirEntry()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Adds a new file entry object to the internal dictionary. NOTE:
    this method will not check whether the entry already exists for 
    performance reasons (doing this would force the dictionary to be
    sorted after every insert).

    The method returns a reference of the actually added file entry.
*/
ZipFileEntry*
ZipDirEntry::AddFileEntry(const StringAtom& name)
{
    ZipFileEntry dummy;
    this->fileEntries.Append(dummy);
    this->fileIndexMap.Add(name, this->fileEntries.Size() - 1);
    return &(this->fileEntries.Back());
}

//------------------------------------------------------------------------------
/**
    Adds a new directory entry object to the internal dictionary. NOTE:
    this method will not check whether the entry already exists for 
    performance reasons (doing this would force the dictionary to be
    sorted after every insert).

    The method returns a reference to the actually added DirEntry. 
*/
ZipDirEntry*
ZipDirEntry::AddDirEntry(const StringAtom& name)
{
    ZipDirEntry dummy;
    this->dirEntries.Append(dummy);
    this->dirEntries.Back().SetName(name);
    this->dirIndexMap.Add(name, this->dirEntries.Size() - 1);
    return &(this->dirEntries.Back());
}

//------------------------------------------------------------------------------
/**
*/
ZipFileEntry*
ZipDirEntry::FindFileEntry(const StringAtom& name) const
{
    n_assert(name.IsValid());
    IndexT index = this->fileIndexMap.FindIndex(name);
    if (InvalidIndex == index)
    {
        return 0;
    }
    else
    {
        return &(this->fileEntries[this->fileIndexMap.ValueAtIndex(index)]);
    }
}

//------------------------------------------------------------------------------
/**
*/
ZipDirEntry*
ZipDirEntry::FindDirEntry(const StringAtom& name) const
{
    n_assert(name.IsValid());
    IndexT index = this->dirIndexMap.FindIndex(name);
    if (InvalidIndex == index)
    {
        return 0;
    }
    else
    {
        return &(this->dirEntries[this->dirIndexMap.ValueAtIndex(index)]);
    }
}

} // namespace IO
