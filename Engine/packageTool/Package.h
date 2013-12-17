/****************************************************************************
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

#ifndef __FILEDATAMGR__
#define __FILEDATAMGR__

#include "core/refcounted.h"
#include "core/ptr.h"
#include "packageTool/FileFormat.h"
#include "packageTool/FileTable.h"
#include "packageTool/PackDef.h"
#include "io/zipfs/ziparchive.h"
namespace IO
{
	class FileData;
}
namespace Pack
{

class Package
{

public:

	Package();

	~Package();

public:

	bool ReadFile(GPtr<IO::Stream>& pStream, const char* fileName) const;

	bool ReadFileThreadSafe(GPtr<IO::Stream>& pStream, const char* fileName) const;

	bool IsFileExit(const char* fileName) const;

	bool Open();

	void Close();

#if __ANDROID__
	bool OpenInAPK(const char* APKName);
#endif

	bool IsOpened() const;
protected:
	bool _ReadFile(GPtr<IO::Stream>& srcStream, GPtr<IO::Stream>& pStream, const char* fileName) const;

	bool m_Opened;
	mutable GPtr<IO::Stream>  m_pFileStream;

	//用来创建package时所用的hash table
	FileTable m_FileTable;

	size_t m_DiskBlockCount;

	size_t m_DiskBlockSize;

	//文件的起始地址
	size_t m_FileBeginPos;


	GPtr<IO::ZipArchive> m_ZipArchive;


#if __ANDROID__
	bool m_bInApk;
#endif
};
inline bool Package::IsOpened() const
{
	return m_Opened;
}
}

#endif