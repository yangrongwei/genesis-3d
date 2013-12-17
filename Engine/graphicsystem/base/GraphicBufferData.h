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
#ifndef __GRAPHICBUFFERDATA_H__
#define __GRAPHICBUFFERDATA_H__
#include "rendersystem/base/BufferData.h"
namespace Graphic
{
	class MemoryPool;
	class MemoryBlock
	{
	public:
		typedef uchar byte;
		typedef byte* byte_ptr;
		MemoryBlock();
		bool valid() const;
		SizeT size() const;

		//internal call

		void _set(MemoryPool* pool, SizeT begin, SizeT size);
		byte_ptr _getPtr() const;
		void _reset();
		MemoryPool* _getPool() const;
		friend class MemoryPool;
	private:
		MemoryPool* mParent;
		SizeT mBegin;
		SizeT mSize;
	};

	inline MemoryBlock::MemoryBlock()
		:mParent(NULL)
		,mBegin(0)
		,mSize(0)
	{

	}

	inline SizeT MemoryBlock::size() const
	{
		return mSize;
	}

	inline bool MemoryBlock::valid() const
	{
		return (NULL != mParent);
	}

	inline void MemoryBlock::_set(MemoryPool* pool, SizeT begin, SizeT size)
	{
		this->mParent = pool;
		this->mBegin = begin;
		this->mSize = size;
	}

	inline MemoryPool* MemoryBlock::_getPool() const
	{
		return mParent;
	}

	class Buffer
	{
	public:
		template<typename Type> 
		Type* GetBufferPtr() const;
		void* GetPtr() const;

		void _reset() const;
		const MemoryBlock& _getBlock() const;
	protected:
		Buffer();
		void setupBlock(SizeT blockSize);
		mutable MemoryBlock block;
	};
	inline Buffer::Buffer()
	{

	}

	template<typename Type>
	Type* Buffer::GetBufferPtr() const
	{
		return reinterpret_cast<Type*>(this->block._getPtr());
	}

	inline void* Buffer::GetPtr() const
	{
		return this->block._getPtr();
	}

	inline const MemoryBlock& Buffer::_getBlock() const
	{
		return block;
	}


	class DynamicBuffer : public Buffer
	{
	public:
		DynamicBuffer();

		void SetSize(SizeT blockSize);
	private:
		typedef Buffer Super;
	};

	inline DynamicBuffer::DynamicBuffer()
	{

	}

	inline void DynamicBuffer::SetSize(SizeT blockSize)
	{
		Super::setupBlock(blockSize);
	}


	//[zhongdaohuan]
	//在设计中，VertexBufferData2 （或IndexBufferData2或DynamicBuffer）同时只能有一个对象处于激活状态，
	//必须立即声明，立即使用。否则不保证正确性。所谓使用就是调用
	//CreatePrimitiveHandle(const VertexBufferData2* vbd2, const IndexBufferData2* ibd2 /* = NULL */)
	//或UpdatePrimitiveHandle(RenderBase::PrimitiveHandle& handle, const DynamicBuffer* vertices, const DynamicBuffer* indices /* = NULL */)
	//所以下面的逻辑没有问题。
	class VertexBufferData2 : public Buffer
	{
	public:
		void Setup(SizeT vertexCount, SizeT vertexSize, RenderBase::BufferData::Usage usage, RenderBase::PrimitiveTopology::Code topology, bool hasMemBlock);
		void SetVertices(void* from, SizeT elemCount);
		RenderBase::VertexComponents& GetVertexComponents();

		void _Bind() const;
		const RenderBase::VertexBufferData& _GetVertexBufferData() const;
	protected:
		typedef Buffer Super;
		mutable RenderBase::VertexBufferData base;
	};

	inline RenderBase::VertexComponents& VertexBufferData2::GetVertexComponents()
	{
		return this->base.vertex.vertexComponents;
	}

	inline const RenderBase::VertexBufferData& VertexBufferData2::_GetVertexBufferData() const
	{
		return base;
	}
	//[zhongdaohuan]
	//在设计中，VertexBufferData2 （或IndexBufferData2或DynamicBuffer）同时只能有一个对象处于激活状态，
	//必须立即声明，立即使用。否则不保证正确性。所谓使用就是调用
	//CreatePrimitiveHandle(const VertexBufferData2* vbd2, const IndexBufferData2* ibd2 /* = NULL */)
	//或UpdatePrimitiveHandle(RenderBase::PrimitiveHandle& handle, const DynamicBuffer* vertices, const DynamicBuffer* indices /* = NULL */)
	//所以下面的逻辑没有问题。
	class IndexBufferData2 : public Buffer
	{
	public:

		void Setup(SizeT indexCount, RenderBase::BufferData::Usage usage, RenderBase::IndexBufferData::IndexType type, bool hasMemBlock);
		void SetIndices(void* from, SizeT elemCount);
		void _Bind() const;
		const RenderBase::IndexBufferData& _GetIndexBufferData() const;
	protected:		
		typedef Buffer Super;
		mutable RenderBase::IndexBufferData base;
	};

	inline const RenderBase::IndexBufferData& IndexBufferData2::_GetIndexBufferData() const
	{
		return base;
	}



}

#endif //__GRAPHICBUFFERDATA_H__