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
    @class IO::ZipFileEntry
  
    A file entry in a zip archive. The ZipFileEntry class is thread-safe,
    all public methods can be invoked from on the same object from different
    threads.
    
*/    
#include "io/stream.h"
#include "zlib/unzip.h"
#include "util/stringatom.h"

//------------------------------------------------------------------------------
namespace IO
{
class ZipFileEntry
{
public:
    /// constructor
    ZipFileEntry();
    /// destructor
    ~ZipFileEntry();
    
    /// get name of the file entry
    const Util::StringAtom& GetName() const;
    /// get the uncompressed file size in bytes
    IO::Stream::Size GetFileSize() const;

    /// open the zip file
    bool Open(const Util::String& password = "");
    /// close the zip file
    void Close();
    /// read the *entire* content into the provided memory buffer
    bool Read(void* buf, IO::Stream::Size bufSize) const;

private:
    friend class ZipArchive;
    
    /// setup the file entry object
    void Setup(const Util::StringAtom& name, unzFile zipFileHandle, Threading::CriticalSection* critSect);

    Threading::CriticalSection* archiveCritSect;
    Util::StringAtom name;
    unzFile zipFileHandle;    // handle on zip file
    unz_file_pos filePosInfo; // info about position in zip file
    uint uncompressedSize;    // uncompressed size of the file
};

//------------------------------------------------------------------------------
/**
*/
inline const Util::StringAtom&
ZipFileEntry::GetName() const
{
    return this->name;
}

//------------------------------------------------------------------------------
/**
*/
inline IO::Stream::Size
ZipFileEntry::GetFileSize() const
{
    return this->uncompressedSize;
}

} // namespace IO
//------------------------------------------------------------------------------

