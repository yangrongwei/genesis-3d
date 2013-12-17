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
    @class IO::ZipFileSystem
    
    An archive filesystem wrapper for ZIP files. 

    Uses the zlib and the minizip package under the hood.

    Limitations:
    * No write access.
    * No seek on compressed data, the ZipFileSystem will generally decompress 
      an entire file into memory at once, so that the ZipStreamClass can
      provide random access on the decompressed data. Thus the typical 
      "audio streaming scenario" is not possible from zip files (that's
      what XACT's sound banks is there for anyway ;)

    How to fix the no-seek problem:
    * zlib processes datas in chunks, and cannot seek randomly within 
      a chunk, and the chunk size is dependent on the compress application
      being used to create the zip file(?), if those internals are known,
      it would be possible to write a chunked filesystem which keeps
      buffered chunks around for each client, probably not worth the effort.
    * Another appoach would be to split stream-files into "chunk-files"
      before compressing, and to read the next complete chunk files
      when new data is needed. This approach doesn't require changes to 
      the strip filesystem.
*/
#include "io/archfs/archivefilesystembase.h"

//------------------------------------------------------------------------------
namespace IO
{
class ZipArchive;

class ZipFileSystem : public ArchiveFileSystemBase
{
    __DeclareClass(ZipFileSystem);
    __DeclareImageSingleton(ZipFileSystem);
public:
    /// constructor
    ZipFileSystem();
    /// destructor
    virtual ~ZipFileSystem();

    /// setup the archive file system
    void Setup();
    /// discard the archive file system
    void Discard();

    /// find first archive which contains the file path
    GPtr<Archive> FindArchiveWithFile(const URI& fileUri) const;
    /// find first archive which contains the directory path
    GPtr<Archive> FindArchiveWithDir(const URI& dirUri) const;
};

} // namespace IO
//------------------------------------------------------------------------------
    
    
    