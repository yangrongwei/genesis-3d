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
#include "StreamBufferPool.h"
#include "graphicsystem/GraphicSystem.h"

namespace Graphic
{

	__ImplementClass(MemoryPool,'MMPL',Core::RefCounted)

		MemoryPool::MemoryPool()
		:mData(NULL)
		,mSize(0)
	{

	}
	MemoryPool::~MemoryPool()
	{
		n_assert(mBlocks.Count() == 0);
		n_assert(NULL == mData);
		n_assert(0 == mSize);
	}

	void MemoryPool::Setup(SizeT blockSize)
	{
		n_assert(mBlocks.Count() == 0);
		n_assert(NULL == mData);
		n_assert(0 == mSize);
		alloc(blockSize);
	}

	void MemoryPool::Destroy()
	{
		free();
	}

	void MemoryPool::Clear()
	{
		mBlocks.Clear();
	}

	MemoryPool::pointer MemoryPool::_getPtr(int begin) const
	{
		n_assert(mSize > begin);
		return mData + begin;
	}


	bool MemoryPool::GetBlock(SizeT size, MemoryBlock& out)
	{
		SizeT freeSize = getFreeSize();

		if (freeSize < size)
		{
			return false;
		}
		blocks::ValueType& bl = mBlocks.PushBack();
		bl.begin = mSize - freeSize;
		bl.size = size;
		out._set(this, bl.begin, bl.size);
		return true;		
	}

	bool MemoryPool::_checkBlcok(const MemoryBlock& check)
	{
		if (check.mParent)
		{
			const StreamBufferPool* sbp = GraphicSystem::Instance()->_GetPool();
			if (sbp->_checkMemoryPool(check.mParent))
			{
				blocks::ConstIterator it = check.mParent->mBlocks.Begin();
				blocks::ConstIterator end = check.mParent->mBlocks.End();
				while(it != end)
				{
					if ((it->begin == check.mBegin) && (it->size == check.mSize))
					{
						return true;
					}
					++it;
				}
			}
		}
		return false;
	}

	SizeT MemoryPool::getFreeSize()
	{		
		blocks::ConstIterator back = mBlocks.Back();
		if (back)
		{
			return mSize - (back->begin + back->size);
		}
		else
		{
			return mSize;
		}
	}

	void MemoryPool::alloc(SizeT size)
	{
		n_assert(0 == mSize);
		n_assert(NULL == mData);
		mData = n_new_array(buffer_type, size);
		mSize = size;
	}

	void MemoryPool::free()
	{
		n_delete_array(mData);
		mData = NULL;
		mSize = 0;
		mBlocks.Clear();
	}


	__ImplementClass(StreamBufferPool,'SBPL',Core::RefCounted)

		StreamBufferPool::StreamBufferPool()
	{

	}

	StreamBufferPool::~StreamBufferPool()
	{
		n_assert(!mDefualtPool.isvalid());
		n_assert(mAditionPools.Size() == 0);
		n_assert(mCustomPools.Size() == 0);
	}

	MemoryBlock StreamBufferPool::GetBlock(SizeT sizeInByte)
	{
		n_assert(mDefualtPool.isvalid());
		n_assert(sizeInByte > 0);
		MemoryBlock block;
		if (!mDefualtPool->GetBlock(sizeInByte, block))
		{
			if (sizeInByte > mAditionSize)
			{
				if (0 == mCustomPools.Size())
				{
					MemoryPoolPtr custom = MemoryPool::Create();
					custom->Setup(sizeInByte);
					mCustomPools.Append(custom);
				}
				if (!mCustomPools[0]->GetBlock(sizeInByte, block))
				{
					mCustomPools[0]->Destroy();
					mCustomPools[0]->Setup(sizeInByte);
					if (!mCustomPools[0]->GetBlock(sizeInByte, block))
					{
						n_error("error: get buffer false");
					}
				}
			}
			else
			{
				bool result = false;
				MemoryPools::Iterator it = mAditionPools.Begin();
				MemoryPools::Iterator end = mAditionPools.End();
				while(it != end)
				{
					result = (*it)->GetBlock(sizeInByte, block);
					if (result)
					{
						break;
					}
				}
				if (!result)
				{
					MemoryPoolPtr add = MemoryPool::Create();
					add->Setup(mAditionSize);
					mAditionPools.Append(add);
					if (!add->GetBlock(sizeInByte, block))
					{
						n_error("error: get buffer false");
					}
				}
			}
		}
		return block;
	}

	void StreamBufferPool::Setup(SizeT defaultSize, SizeT aditionSize)
	{
		n_assert(mAditionPools.Size() == 0);
		n_assert(!mDefualtPool.isvalid());
		n_assert(mCustomPools.Size() == 0);

		mDefualtSize = defaultSize;
		mAditionSize = aditionSize;

		mDefualtPool = MemoryPool::Create();
		mDefualtPool->Setup(defaultSize);
	}

	void StreamBufferPool::Destory()
	{
		mDefualtPool->Destroy();
		mDefualtPool = NULL;
		MemoryPools::Iterator it = mAditionPools.Begin();
		MemoryPools::Iterator end = mAditionPools.End();
		while(it != end)
		{
			(*it)->Destroy();
		}
		mAditionPools.Clear();
		MemoryPools::Iterator it2 = mCustomPools.Begin();
		MemoryPools::Iterator end2 = mCustomPools.End();
		while(it2 != end2)
		{
			(*it2)->Destroy();
		}
		mCustomPools.Clear();
		mDefualtSize = 0;
		mAditionSize = 0;
	}

	bool StreamBufferPool::_checkMemoryPool(const MemoryPool* pool) const
	{
		if(mDefualtPool.get() == pool)
		{
			return true;
		}
		MemoryPools::Iterator it = mAditionPools.Begin();
		MemoryPools::Iterator end = mAditionPools.End();
		while(it != end)
		{
			if(it->get() == pool)
			{
				return true;
			}
		}
		MemoryPools::Iterator it2 = mCustomPools.Begin();
		MemoryPools::Iterator end2 = mCustomPools.End();
		while(it2 != end2)
		{
			if(it2->get() == pool)
			{
				return true;
			}
		}
		return false;
	}
}
