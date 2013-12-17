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
#include "QuadRenderable.h"
#include "foundation/meshbuilder/parallelogrambuilder.h"
#include "GraphicSystem.h"

namespace Graphic
{

	using namespace Math;
	using namespace RenderBase;
	struct _vertex
	{
	public:
		Math::float3 position;
		Math::float2 uv;
	};

	__ImplementClass(QuadRenderable,'QRGS',Core::RefCounted)

		QuadRenderable::QuadRenderable()
		: m_Width(1),
		m_Height(1)
	{
		m_handle = RenderBase::PrimitiveHandle();
		GraphicSystem::Instance()->AddQuadRenderable(this);
	}
	QuadRenderable::~QuadRenderable()
	{
		Discard();
	}

	void QuadRenderable::Discard()
	{		
		if (m_handle.IsValid())
		{
			GraphicSystem::Instance()->RemovePrimitive(m_handle);
			m_handle = RenderBase::PrimitiveHandle();
		}
	}

	void QuadRenderable::Setup(int width, int height)
	{
		GraphicSystem* gs = GraphicSystem::Instance();

		Discard();
		m_Width  = width;
		m_Height = height;

		float widthPixel = gs->GetHorizontalTexelOffset() * 2.0f / width;
		float heightPixel = gs->GetVerticalTexelOffset() * 2.0f / height;
		n_assert(!m_handle.IsValid());

		VertexBufferData2 vbd2;
		IndexBufferData2 ibd2;

		RenderBase::VertexComponents& vertexComponents = vbd2.GetVertexComponents();
		vertexComponents.Append(VertexComponent(VertexComponent::Position,0, VertexComponent::Float3));
		vertexComponents.Append(VertexComponent(VertexComponent::TexCoord,0, VertexComponent::Float2));
		n_assert(!m_handle.IsValid());

		vbd2.Setup(RECT_VERTEX_COUNT, sizeof(_vertex), 
			RenderBase::BufferData::Static, RenderBase::PrimitiveTopology::TriangleList, true);
		ibd2.Setup(RECT_INDICES_COUNT, RenderBase::BufferData::Static, RenderBase::IndexBufferData::Int16, true);

		_vertex* vs = vbd2.GetBufferPtr<_vertex>();
		vs[0].uv = Math::float2(0,0);
		vs[1].uv = Math::float2(1,0);
		vs[2].uv = Math::float2(0,1);
		vs[3].uv = Math::float2(1,1);
		// offset vertices
		float3 top(0.0f, 1.0f, 0.0f);
		float3 right(1.0f, 0.0f, 0.0f);
		float3 center(0.0f, 0.0f, 0.0f);
		MeshBuilder::ParallelogramBuilder::Set(vs, top, right, center, 0);

		for (int i = 0; i < RECT_VERTEX_COUNT; i++)
		{
			vs[i].position.x() += widthPixel;
			vs[i].position.y() -= heightPixel;
		}

		ushort* indices = ibd2.GetBufferPtr<ushort>();
		MeshBuilder::ParallelogramBuilder::SetIndices(indices);

		m_handle = gs->CreatePrimitiveHandle(&vbd2, &ibd2);

	}
}
