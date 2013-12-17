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
    @class IO::ArchiveBase
    
    Base class of file archives. Subclasses of this class implemented support
    for specific archive formats, like zip.

*/
#include "core/refcounted.h"
#include "io/uri.h"

//------------------------------------------------------------------------------
namespace IO
{
class ArchiveBase : public Core::RefCounted
{
    __DeclareClass(ArchiveBase);
public:
    /// constructor
    ArchiveBase();
    /// destructor
    virtual ~ArchiveBase();

    /// setup the archive from an URI (without file extension)
    bool Setup(const URI& archiveURI);
    /// discard the archive
    void Discard();
    /// return true if archive is valid
    bool IsValid() const;
    /// get the URI of the archive
    const URI& GetURI() const;

    /// list all files in a directory in the archive
    Util::Array<Util::String> ListFiles(const Util::String& dirPathInArchive, const Util::String& pattern) const;
    /// list all subdirectories in a directory in the archive
    Util::Array<Util::String> ListDirectories(const Util::String& dirPathInArchive, const Util::String& pattern) const;
    /// convert a "file:" URI into a archive-specific URI pointing into this archive
    URI ConvertToArchiveURI(const URI& fileURI) const;
    /// convert an absolute path to local path inside archive, returns empty string if absPath doesn't point into this archive
    Util::String ConvertToPathInArchive(const Util::String& absPath) const;

protected:
    bool isValid;
    URI uri;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
ArchiveBase::IsValid() const
{
    return this->isValid;
}

//------------------------------------------------------------------------------
/**
*/
inline const URI&
ArchiveBase::GetURI() const
{
    return this->uri;
}

} // namespace IO
//------------------------------------------------------------------------------


    