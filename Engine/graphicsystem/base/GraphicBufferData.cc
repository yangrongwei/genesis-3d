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
#include "GraphicBufferData.h"
#include "StreamBufferPool.h"
#include "GraphicSystem.h"

namespace Graphic
{

	MemoryBlock::byte_ptr MemoryBlock::_getPtr() const
	{
		n_assert(MemoryPool::_checkBlcok(*this));
		return mParent->_getPtr(mBegin);
	}

	void MemoryBlock::_reset()
	{
		//n_assert(MemoryPool::_ckeckLast(*this));
		//mParent->Pop();
		mParent = NULL;
		mBegin = 0;
		mSize = 0;
	}

	void Buffer::setupBlock(SizeT blockSize)
	{
		n_assert(!block.valid());
		GraphicSystem* gs = GraphicSystem::Instance();

		block = gs->_GetBlock(blockSize);
	}

	void Buffer::_reset() const
	{
		block._reset();
	}

	void VertexBufferData2::Setup(SizeT vertexCount, SizeT vertexSize, RenderBase::BufferData::Usage usage, RenderBase::PrimitiveTopology::Code topology, bool hasMemBlock)
	{
		base.usage = usage;
		base.topology = topology;
		base.vertexCount = vertexCount;
		if (hasMemBlock)
		{
			Super::setupBlock(vertexCount * vertexSize);
		}
	}

	void VertexBufferData2::SetVertices(void* from, SizeT elemCount)
	{
		n_assert(NULL != from);
		n_assert(block.size());
		n_assert(elemCount <= base.vertexCount);
		Memory::Copy(from, GetPtr(), elemCount * (block.size() / base.vertexCount));
	}

	void VertexBufferData2::_Bind() const
	{
		n_assert(0 == base.vertex.vertexComponentStreams.Size());
		if (block.valid())
		{
			RenderBase::VertexStream vertexStream;
			vertexStream.data = block._getPtr();
			vertexStream.offsetInByte = 0;
			vertexStream.elemSizeInByte = RenderBase::VertexComponent::BuildComponentsOffsetAndSize(base.vertex.vertexComponents);

			n_assert(vertexStream.elemSizeInByte * base.vertexCount <= block.size() || NULL == vertexStream.data);

			base.vertex.vertexComponentStreams.Append(vertexStream);
		}
	}
	void IndexBufferData2::SetIndices(void* from, SizeT elemCount)
	{
		n_assert(NULL != from);
		n_assert(block.size());
		n_assert(elemCount <= base.indexCount);
		Memory::Copy(from, GetPtr(), elemCount * (block.size() / base.indexCount));
	}

	void IndexBufferData2::Setup(SizeT indexCount, RenderBase::BufferData::Usage usage, RenderBase::IndexBufferData::IndexType type, bool hasMemBlock)
	{
		base.indexCount = indexCount;
		base.usage = usage;
		base.indexType = type;
		SizeT blockSize = indexCount * RenderBase::IndexBufferData::SizeOf(type);

		if (hasMemBlock)
		{
			Super::setupBlock(blockSize);
		}
	}

	void IndexBufferData2::_Bind() const
	{
		if (block.valid())
		{
			base.stream = block._getPtr();
		}
	}
}