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

#ifndef __fILE_MAP_H__
#define __fILE_MAP_H__
#include "PackDef.h"
#include "PackageUtil.h"
#include "FileFormat.h"
#include <vector>
#include <string>
namespace Pack
{
	class FileTable
	{
	public:
		const FileBlock* GetFileBlock(const char* fileName) const;
		void Clear();
	protected:
		struct _hash_elem
		{
			int index;
			_hash_elem()
				:index(INVALID_INDEX)
			{

			}
		};
		size_t _GetBlockIndex(HashCode hash) const;
		std::vector<std::string> m_NameCache;
		std::vector<FileBlock> m_FileInfos;
		std::vector<_hash_elem> m_HashTable;
	};

	inline size_t FileTable::_GetBlockIndex(HashCode hash) const
	{
		return hash % m_HashTable.size();
	}
}

#endif //__fILE_MAP_H__