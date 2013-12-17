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

#ifndef __FILEDATA__
#define __FILEDATA__

#include "core/refcounted.h"
#include "core/ptr.h"
#include "util/string.h"
#include "PackDef.h"

namespace Pack
{
	class FileData : public Core::RefCounted
{
	 __DeclareClass(FileData);

public:

	FileData();

	~FileData();

public:

	void  Open();

	void* GetMemory() const;

	void  ReleaseMemory() const;

	SizeT GetSize()   const;

	void  SetFilePath(const Util::String& path);

	const Util::String& GetFilePath() const;

private:

	GPtr<IO::Stream>   m_pFileStream;
  	Util::String   m_FilePath;

};

inline void FileData::SetFilePath(const Util::String& path)
{
	n_assert(!path.IsEmpty());

	m_FilePath = path;
}

inline const Util::String& FileData::GetFilePath() const
{
	return m_FilePath;
}

}


#endif