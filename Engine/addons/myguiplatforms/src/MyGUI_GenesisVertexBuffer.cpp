/*!
	@file
	@author		Albert Semenov
	@date		04/2009
*/
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
#include "MyGUI_GenesisVertexBuffer.h"
#include "memory/memory.h"
#include "graphicsystem/GraphicSystem.h"
#include "MyGUI_GenesisVertexBufferManager.h"

using namespace Graphic;
namespace MyGUI
{

	const size_t VERTEX_IN_QUAD = 6;
	const size_t RENDER_ITEM_STEEP_REALLOCK = 5 * VERTEX_IN_QUAD;
	//const size_t RENDER_ITEM_STEEP_REALLOCK = 0;
	GenesisVertexBuffer::GenesisVertexBuffer() 
		: mVertexCount(0)//(RENDER_ITEM_STEEP_REALLOCK)
		, mNeedVertexCount(0)
	{
		GenesisVertexBufferMgr::Instance()->AddVertexBuffer(this);
	}

	GenesisVertexBuffer::~GenesisVertexBuffer()
	{
		destroyVertexBuffer();
	}

	bool _createVertexComponent(Util::Array<RenderBase::VertexComponent>& vertexComponents)
	{
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Position, 0, RenderBase::VertexComponent::Float3));
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Color, 0, RenderBase::VertexComponent::ColorBGRA));
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::TexCoord, 0, RenderBase::VertexComponent::Float2));
		return false;
	}

	void GenesisVertexBuffer::createVertexBuffer()
	{
		n_assert(!m_primHandle.IsValid());
		static Util::Array<RenderBase::VertexComponent> vertexComponents;
		static bool ______x = _createVertexComponent(vertexComponents);
		mVertexBufferSize = mVertexCount * sizeof(Vertex);
		VertexBufferData2 vbd2;
		vbd2.GetVertexComponents() = vertexComponents;
		vbd2.Setup(mVertexCount, sizeof(Vertex), RenderBase::BufferData::Dynamic, RenderBase::PrimitiveTopology::TriangleList, false);

		m_primHandle = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, NULL);
		//m_primHandle = Graphic::GraphicSystem::Instance()->CreatePrimitiveGroup(RenderBase::PrimitiveTopology::TriangleList, Math::bbox::Zero, vb);

	}

	void GenesisVertexBuffer::destroyVertexBuffer()
	{
		GraphicSystem::Instance()->RemovePrimitive(m_primHandle);
		m_primHandle = RenderBase::PrimitiveHandle();
	}

	void GenesisVertexBuffer::resizeVertexBuffer()
	{
		mVertexCount = mNeedVertexCount + RENDER_ITEM_STEEP_REALLOCK;

		destroyVertexBuffer();
		createVertexBuffer();
	}

	void GenesisVertexBuffer::setVertexCount(size_t _count)
	{
		mNeedVertexCount = _count;
	}

	size_t GenesisVertexBuffer::getVertexCount()
	{
		return mNeedVertexCount;
	}
	Vertex* GenesisVertexBuffer::lock()
	{
		if (mNeedVertexCount > mVertexCount)
		{
			resizeVertexBuffer();
		}
		//return m_vBuffer;
		//RenderBase::PrimitiveGroup* pg = Graphic::GraphicSystem::Instance()->GetPrimitiveGroup(m_primHandle);
		//return pg->GetVertexBuffer()->Lock<Vertex>();
		mDynamicBuffer.SetSize(mVertexBufferSize);
		return mDynamicBuffer.GetBufferPtr<Vertex>();
	}
	void GenesisVertexBuffer::unlock()
	{
		//RenderBase::PrimitiveGroup* pg = Graphic::GraphicSystem::Instance()->GetPrimitiveGroup(m_primHandle);
		//pg->GetVertexBuffer()->Unlock();
		//pg->GetVertexBuffer()->Flush();
		Graphic::GraphicSystem::Instance()->UpdatePrimitiveHandle(m_primHandle, &mDynamicBuffer, NULL);
	}

} // namespace MyGUI
