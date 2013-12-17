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
#ifndef STREAMBUFFERPOOL_H_
#define STREAMBUFFERPOOL_H_
#include "foundation/core/refcounted.h"
#include "foundation/util/array.h"
#include "graphicsystem/base/GraphicBufferData.h"
#include "graphicsystem/base/DataCollection.h"
namespace Graphic
{
	//
	// magage as stack.
	//
	class MemoryPool : public Core::RefCounted
	{
		__DeclareClass(MemoryPool);
	public:
		typedef MemoryBlock::byte buffer_type;
		typedef MemoryBlock::byte_ptr pointer;
		MemoryPool();
		~MemoryPool();
		void Setup(SizeT blockSize);
		void Destroy();
		void Clear();
		bool GetBlock(SizeT size, MemoryBlock& out);
		SizeT Size() const;
		//void Pop();

		static bool _checkBlcok(const MemoryBlock& check);
		//static bool _ckeckLast(const MemoryBlock& check);
		pointer _getPtr(int begin) const;
	protected:
		SizeT getFreeSize();
		void alloc(SizeT size);
		void free();
		struct block
		{
			int begin;
			int size;
		};
		typedef DataCollection<block> blocks;

		SizeT mSize;
		pointer mData;
		blocks mBlocks;
	};

	inline SizeT MemoryPool::Size() const
	{
		return mSize;
	}

	class StreamBufferPool : public Core::RefCounted
	{
		__DeclareClass(StreamBufferPool);
		typedef GPtr<MemoryPool> MemoryPoolPtr;
		typedef Util::Array<MemoryPoolPtr> MemoryPools;
	public:
		StreamBufferPool();
		~StreamBufferPool();
		MemoryBlock GetBlock(SizeT sizeInByte);
		void Setup(SizeT defaultSize, SizeT aditionSize);
		void Destory();
		DynamicBuffer& GetDynamicBuffer();

		bool _checkMemoryPool(const MemoryPool* pool) const;
	private:
		MemoryPoolPtr mDefualtPool;
		MemoryPools mAditionPools;
		MemoryPools mCustomPools;
		SizeT mDefualtSize;
		SizeT mAditionSize;
	};
}

#endif //STREAMBUFFERPOOL_H_