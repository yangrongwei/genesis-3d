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
#include "stdneb.h"
#include "foundation/memory/memory.h"
#include "spriteutils.h"

namespace Sprite
{
	MemoryBlock::MemoryBlock()
		:mData(NULL)
		,mSize(0)
	{

	}

	MemoryBlock::~MemoryBlock()
	{
		free();
	}

	void MemoryBlock::Resize(SizeT size)
	{
		free();
		alloc(size);
	}

	void MemoryBlock::Clear()
	{
		free();
	}

	void MemoryBlock::CopyTo(void* to)
	{
		Memory::Copy(mData, to, mSize);
	}

	void MemoryBlock::SetData(const void* data, SizeT len)
	{
		Memory::Copy(data, mData, len < mSize ? len : mSize);
	}

	void MemoryBlock::alloc(SizeT size)
	{
		n_assert(NULL == mData);
		n_assert(0 == mSize);
		mData = n_new_array(ubyte, size);
		mSize = size;
	}

	void MemoryBlock::free()
	{
		n_delete_array(mData);
		mData = NULL;
		mSize = 0;
	}

}