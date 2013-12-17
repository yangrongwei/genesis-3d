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

#include "FileTable.h"
#include <string>
namespace Pack
{
	//inline bool __equal(const char* ls, const char* rs)
	//{
	//	Asset(ls);
	//	Asset(rs);
	//	while(*ls != 0 && *rs != 0)
	//	{
	//		if (*ls != *rs)
	//		{
	//			return false;
	//		}
	//		++ls;
	//		++rs;
	//	}
	//	return (*ls == 0 && *rs == 0);
	//}

	const FileBlock* FileTable::GetFileBlock(const char* fileName) const
	{
		const HashCode hash = GetHashCode(fileName);
		size_t hashStart = _GetBlockIndex(hash);
		size_t hashPos = hashStart;

		while (INVALID_INDEX != m_HashTable[hashPos].index)
		{
			int index = m_HashTable[hashPos].index;

			if (m_FileInfos[index].hashName == hash)
			{
				if (m_NameCache.size())
				{
					if (m_NameCache[index] != fileName)
					{
						ThrowWarning("haha,you are so lucky, there is one hash conflict:\n");
						ThrowWarning(fileName);
						ThrowWarning("\n");
						ThrowWarning(m_NameCache[index].c_str());
						ThrowWarning("\n");
					}
				}
				return &(m_FileInfos[index]);
			}

			hashPos = _GetBlockIndex(hashPos + 1);
			if (hashPos == hashStart)
			{
				return nullptr;
			}
		}
		return nullptr;
	}

	void FileTable::Clear()
	{
		m_NameCache.clear();
		m_FileInfos.clear();
		m_HashTable.clear();
	}
}