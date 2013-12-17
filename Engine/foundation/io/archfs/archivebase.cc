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

#include "stdneb.h"
#include "io/archfs/archivebase.h"

namespace IO
{
__ImplementClass(IO::ArchiveBase, 'ARCB', Core::RefCounted);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
ArchiveBase::ArchiveBase() :
    isValid(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
ArchiveBase::~ArchiveBase()
{
    n_assert(!this->IsValid());
}

//------------------------------------------------------------------------------
/**
    Setup the archive object from an URI pointing to an archive file. This
    method may return false if something went wrong (archive file not
    found, or wrong format).
*/
bool
ArchiveBase::Setup(const URI& archiveFileURI)
{
    n_assert(!this->IsValid());
    this->uri = archiveFileURI;
    this->isValid = true;
    return true;
}

//------------------------------------------------------------------------------
/**
*/
void
ArchiveBase::Discard()
{
    n_assert(this->IsValid());
    this->isValid = false;
}

//------------------------------------------------------------------------------
/**
    List all files in an archive directory. Override this method in a subclass!
*/
Array<String>
ArchiveBase::ListFiles(const String& dirPathInArchive, const String& pattern) const
{
    Array<String> emptyArray;
    return emptyArray;
}

//------------------------------------------------------------------------------
/**
    List all directories in an archive directory. Override this method in a 
    subclass!
*/
Array<String>
ArchiveBase::ListDirectories(const String& dirPathInArchive, const String& pattern) const
{
    Array<String> emptyArray;
    return emptyArray;
}

//------------------------------------------------------------------------------
/**
    This method should convert a "file:" URI into an URI suitable for
    an archive specific stream class.

    Override this method in a subclass!
*/
URI
ArchiveBase::ConvertToArchiveURI(const URI& fileURI) const
{
    return fileURI;
}

//------------------------------------------------------------------------------
/**
    This method should convert an absolute file system path into a
    local path in the archive suitable for ListFiles() and ListDirectories().

    Override this method in a subclass!
*/
String
ArchiveBase::ConvertToPathInArchive(const String& absPath) const
{
    return absPath;
}

} // namespace IO
