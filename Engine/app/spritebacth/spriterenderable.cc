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
#include "spriterenderable.h"
#include "memory/memory.h"

using namespace Graphic;

namespace App
{
	const SizeT SpriteRenderInfo::s_verticsOneRect = 4; //绘制一个矩形所需的顶点数。
	const SizeT SpriteRenderInfo::s_indicesOneRect = 6;	//绘制一个矩形所需的索引数。
	const ColorF SpriteRenderInfo::ColorWhite = ColorF(1.0f, 1.0f, 1.0f, 1.0f);		
	const ColorF SpriteRenderInfo::ColorBlack = ColorF(0.0f, 0.0f, 0.0f, 1.0f);
	const ColorF SpriteRenderInfo::ColorRed = ColorF(1.0f, 0.0f, 0.0f, 1.0f);
	const ColorF SpriteRenderInfo::ColorGreen = ColorF(0.0f, 1.0f, 0.0f, 1.0f);
	const ColorF SpriteRenderInfo::ColorBlue = ColorF(0.0f, 0.0f, 1.0f, 1.0f);

	const ColorF SpriteRenderInfo::ColorOne = ColorF(1.0f, 1.0f, 1.0f, 1.0f);
	const ColorF SpriteRenderInfo::ColorZero = ColorF(0.0f, 0.0f, 0.0f, 0.0f);


	__ImplementClass(App::SpriteRenderInfo,'SPRE', Core::RefCounted);


	SpriteRenderInfo::SpriteRenderInfo()
		:m_primHandle(NULL)
		//,m_primGroup(NULL)
		//,m_vertexBuffer(NULL)
		,m_rectCount(0)
		,m_screenOffset(float2(0,0))
	{
	}
	SpriteRenderInfo::~SpriteRenderInfo()
	{
		_release();
	}


	void SpriteRenderInfo::InitBuffer(SizeT count, const RectF rect[], const RectF rect_uv[], const ColorF& color)
	{
		if (m_rectCount)
		{
			_release();
		}
		m_rectCount = count;

		VertexBufferData2 vbd2;
		IndexBufferData2 ibd2;

		RenderBase::VertexComponents& vertexComponents = vbd2.GetVertexComponents();
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Position, 0, RenderBase::VertexComponent::Float2));
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::TexCoord, 0, RenderBase::VertexComponent::Float2));
		vertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::TexCoord, 1, RenderBase::VertexComponent::Float4));

		vbd2.Setup(m_rectCount * s_verticsOneRect, sizeof(_vertex_info), 
			RenderBase::BufferData::Static, RenderBase::PrimitiveTopology::TriangleList, true);

		ibd2.Setup(m_rectCount * s_indicesOneRect, RenderBase::BufferData::Static, RenderBase::IndexBufferData::Int16, true);
		_vertex_info* vertex_info = vbd2.GetBufferPtr<_vertex_info>();
		ushort* indices = ibd2.GetBufferPtr<ushort>();

		int temp = 0;
		for (int i = 0; i < count; ++i)
		{

			_setVertexInfo(vertex_info + i * s_verticsOneRect, rect[i], rect_uv[i], color);
			int temp2 = i * s_verticsOneRect;
			indices[temp++] = temp2;
			indices[temp++] = temp2 + 1;
			indices[temp++] = temp2 + 2;

			indices[temp++] = temp2 + 2;
			indices[temp++] = temp2 + 1;
			indices[temp++] = temp2 + 3;
		}
		m_primHandle = GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
	}

	void SpriteRenderInfo::UpdateBuffer(SizeT count, const RectF rect[], const RectF rect_uv[], const ColorF& color /* = ColorOne */)
	{
		n_assert(count <= m_rectCount);
		Graphic::DynamicBuffer dynamic_buffer;
		dynamic_buffer.SetSize(m_rectCount * s_verticsOneRect * sizeof(_vertex_info));
		_vertex_info* vertex_info = dynamic_buffer.GetBufferPtr<_vertex_info>();

		for (int i = 0; i < count; ++i)
		{
			_setVertexInfo(vertex_info + i * s_verticsOneRect, rect[i], rect_uv[i], color);
		}
		Graphic::GraphicSystem::Instance()->UpdatePrimitiveHandle(m_primHandle, &dynamic_buffer, NULL);
	}
	void SpriteRenderInfo::SetRectInScreen(const RectF& rect, SizeT index)
	{
		//assert(index >= 0);
		//assert(index < m_rectCount);

		//_vertex_info* info_ptr = _getVertexBegin(index);
		//info_ptr->x = rect.left;
		//info_ptr->y = rect.top;

		//++info_ptr;
		//info_ptr->x = rect.right;
		//info_ptr->y = rect.top;

		//++info_ptr;
		//info_ptr->x = rect.left;
		//info_ptr->y = rect.bottom;

		//++info_ptr;
		//info_ptr->x = rect.right;
		//info_ptr->y = rect.bottom;

	}
	void SpriteRenderInfo::SetRectInTexture(const RectF& rect_uv, SizeT index)
	{
		//assert(index >= 0);
		//assert(index < m_rectCount);

		//_vertex_info* info_ptr = _getVertexBegin(index);
		//
		//info_ptr->u = rect_uv.left;
		//info_ptr->v = rect_uv.top;
		//
		//++info_ptr;
		//info_ptr->u = rect_uv.right;
		//info_ptr->v = rect_uv.top;

		//++info_ptr;
		//info_ptr->u = rect_uv.left;
		//info_ptr->v = rect_uv.bottom;

		//++info_ptr;
		//info_ptr->u = rect_uv.right;
		//info_ptr->v = rect_uv.bottom;

	}

	void  SpriteRenderInfo::SetColor(const ColorF& color)
	{
		//assert(NULL != m_vertexBuffer);
		//_vertex_info* info = (_vertex_info*)m_vertexBuffer->GetVertexDataPtr();
		//_vertex_info* end = info + m_rectCount * s_verticsOneRect;
		//while (info <= end)
		//{
		//	info->color = color;
		//	++info;
		//}
	}

	void SpriteRenderInfo::_setVertexInfo(_vertex_info* info_ptr, const RectF& rect, const RectF& rect_uv, const ColorF& color)
	{ 
		//n_printf("\nvb: ");
		info_ptr->x = rect.left;
		info_ptr->y = rect.top;
		info_ptr->u = rect_uv.left;
		info_ptr->v = rect_uv.top;
		info_ptr->color = color;
		//n_printf("\n %d,%d##", (int)info_ptr->x, (int)info_ptr->y);

		++info_ptr;
		info_ptr->x = rect.right;
		info_ptr->y = rect.top;
		info_ptr->u = rect_uv.right;
		info_ptr->v = rect_uv.top;
		info_ptr->color = color;
		//n_printf("%d,%d##", (int)info_ptr->x, (int)info_ptr->y);

		++info_ptr;
		info_ptr->x = rect.left;
		info_ptr->y = rect.bottom;
		info_ptr->u = rect_uv.left;
		info_ptr->v = rect_uv.bottom;
		info_ptr->color = color;
		//n_printf("%d,%d##", (int)info_ptr->x, (int)info_ptr->y);

		++info_ptr;
		info_ptr->x = rect.right;
		info_ptr->y = rect.bottom;
		info_ptr->u = rect_uv.right;
		info_ptr->v = rect_uv.bottom;
		info_ptr->color = color;
		//n_printf("%d,%d,", (int)info_ptr->x, (int)info_ptr->y);
	}
	void SpriteRenderInfo::_release()
	{
		GraphicSystem::Instance()->RemovePrimitive(m_primHandle);
		m_primHandle = RenderBase::PrimitiveHandle();
	}
}