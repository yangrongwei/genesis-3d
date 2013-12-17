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
#include "serialization/serialize.h"
#include "rendersystem/base/VertexComponent.h"
#include "meshbuilder/parallelogrambuilder.h"
#include "graphicsystem/base/GraphicBufferData.h"
#include "graphicsystem/GraphicSystem.h"
#include "resource/resinfo.h"
#include "foundation/math/intersection.h"

#include "spritemesh.h"
#include "spritevertex.h"
#include "spriteblock.h"
#include "spriteimage.h"
#include "spritepackage.h"

namespace Sprite
{
	using namespace Math;
	class _sprite_vertex
	{
	public:
		float3 position;    //
		float2 tex_uv;
		static const SizeT vertex_bias_in_byte = 0;
		//static const SizeT normal_bias_in_byte = sizeof(float3);
		static const Util::Array<RenderBase::VertexComponent>& GetVertexComponents()
		{
			if (0 == sVertexComponents.Size())
			{
				sVertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::Position,0, RenderBase::VertexComponent::Float3));
				sVertexComponents.Append(RenderBase::VertexComponent(RenderBase::VertexComponent::TexCoord,0, RenderBase::VertexComponent::Float2));
			}

			return sVertexComponents;
		}
	private:
		static Util::Array<RenderBase::VertexComponent> sVertexComponents;
	};
	Util::Array<RenderBase::VertexComponent> _sprite_vertex::sVertexComponents;

	template<typename Vertex>
	inline void _setupVertexIndex(Graphic::VertexBufferData2& vbd2, SizeT vertex_count, Graphic::IndexBufferData2& ibd2, SizeT index_count, bool dynamic_vertex)
	{
		vbd2.Setup(vertex_count, sizeof(Vertex), 
			dynamic_vertex ? RenderBase::BufferData::Dynamic : RenderBase::BufferData::Static, 
			RenderBase::PrimitiveTopology::TriangleList, true);

		ibd2.Setup(index_count, RenderBase::BufferData::Static, RenderBase::IndexBufferData::Int16, true);
	}

	const uint SpriteMesh::sVersion = 1;
	const uint SpriteRectMesh::sVersion = 1;

#define DEFINE_SERIAL_ITEM_NAME(name) static const char* g##name##Tag = #name

	DEFINE_SERIAL_ITEM_NAME(Name);
	DEFINE_SERIAL_ITEM_NAME(Version);
	DEFINE_SERIAL_ITEM_NAME(PixelPerUnit);//int mPixelPerUnit;
	DEFINE_SERIAL_ITEM_NAME(Rotation);//Math::quaternion mRotation;

	__ImplementClass(SpriteMesh,'SPME',SpriteObject);

	SpriteMesh::~SpriteMesh()
	{

	}

	SpriteMesh::SpriteMesh()
		:mMark(ArgNone)
	{

	}

	SpriteMesh::SpriteMesh(Arguments mark)
		:mMark(mark)
	{
	}

	void SpriteMesh::Save(GPtr<Serialization::SerializeWriter>& pWriter) const
	{
		pWriter->SerializeVersion(sVersion);

		__SaveSuper(pWriter);
		pWriter->SerializeString(gNameTag, mName);
	}

	void SpriteMesh::Load(const GPtr<Serialization::SerializeReader>& pReader)
	{
		Serialization::SVersion version;
		pReader->SerializeVersion(version);
		__LoadSuper(pReader);

		pReader->SerializeString(gNameTag, mName);
	}

	void SpriteMesh::CopyFrom(const GPtr<SpriteObject>& obj)
	{
		Super::CopyFrom(obj);
		GPtr<SpriteMesh> sub = obj.downcast<SpriteMesh>();
		mMark = sub->mMark;
		mName = sub->mName;
	}


	Math::bbox SpriteMesh::CreateVertex(SpriteVertexUnit& sv, const GPtr<SpriteImage> image, const GPtr<SpriteBlock>& block)
	{
		/// empty.
		return Math::bbox::Zero;
	}

	Math::bbox SpriteMesh::UpdateVertex(SpriteVertexUnit& sv, const GPtr<SpriteImage> image, const GPtr<SpriteBlock>& block)
	{
		/// empty.
		return Math::bbox::Zero;
	}

	__ImplementClass(SpriteRectMesh,'SRME',SpriteMesh);
	SpriteRectMesh::SpriteRectMesh()
		:Super(Super::ArgBlock)
		,mPixelPerUnit(32.0f)  ///hack code yuan qing guo 
	{

	}

	SpriteRectMesh::~SpriteRectMesh()
	{

	}

	void SpriteRectMesh::Save(GPtr<Serialization::SerializeWriter>& pWriter) const
	{
		pWriter->SerializeVersion(sVersion);
		__SaveSuper(pWriter);
		pWriter->SerializeFloat(gPixelPerUnitTag, mPixelPerUnit);
		pWriter->SerializeQuaternion(gRotationTag, mRotation);
	}

	void SpriteRectMesh::Load(const GPtr<Serialization::SerializeReader>& pReader)
	{
		Serialization::SVersion version;
		pReader->SerializeVersion(version);

		__LoadSuper(pReader);

		pReader->SerializeFloat(gPixelPerUnitTag, mPixelPerUnit);
		pReader->SerializeQuaternion(gRotationTag, mRotation);
	}

	void SpriteRectMesh::SetPixelPerUnit(float value)
	{
		mPixelPerUnit = value;
		__SPRITE_OBJECT_CHANGE__
			__SPRITE_CHANGE__
	}

	void SpriteRectMesh::CopyFrom(const GPtr<SpriteObject>& obj)
	{
		Super::CopyFrom(obj);
		GPtr<SpriteRectMesh> sub = obj.downcast<SpriteRectMesh>();

		mPixelPerUnit = sub->mPixelPerUnit;
		mRotation = sub->mRotation;
		mVertexTemplate.Clear();
	}


	Math::bbox SpriteRectMesh::CreateVertex(SpriteVertexUnit& sv, const GPtr<SpriteImage> image, const GPtr<SpriteBlock>& block)
	{
		if (0 == mVertexTemplate.GetSize())
		{
			buildVertexTemplate();
		}

		SizeT vertex_count = RECT_VERTEX_COUNT;
		SizeT index_count = RECT_INDICES_COUNT;

		Graphic::VertexBufferData2 vbd2;
		Graphic::IndexBufferData2 ibd2;
		_setupVertexIndex<_sprite_vertex>(vbd2, vertex_count, ibd2, index_count, true);

		_sprite_vertex* vertices = vbd2.GetBufferPtr<_sprite_vertex>();//_SimpleVertex vertices[RECT_VERTEX_COUNT];
		vbd2.GetVertexComponents() = _sprite_vertex::GetVertexComponents();
		bbox box = setVertexByTemplate(vertices, image, block);

		ushort* indices = ibd2.GetBufferPtr<ushort>();//ushort indices[RECT_INDICES_COUNT];
		MeshBuilder::ParallelogramBuilder::SetIndices(indices);
		RenderBase::PrimitiveHandle handle = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);

		sv.Setup(handle, vertex_count, index_count);

		return box;
	}

	Math::bbox SpriteRectMesh::UpdateVertex(SpriteVertexUnit& sv, const GPtr<SpriteImage> image, const GPtr<SpriteBlock>& block)
	{
		if (0 == mVertexTemplate.GetSize())
		{
			buildVertexTemplate();
		}

		Graphic::DynamicBuffer dvb;
		dvb.SetSize(RECT_VERTEX_COUNT * sizeof(_sprite_vertex));

		_sprite_vertex* vertices = dvb.GetBufferPtr<_sprite_vertex>();//_SimpleVertex vertices[RECT_VERTEX_COUNT];

		bbox box = setVertexByTemplate(vertices, image, block);

		RenderBase::PrimitiveHandle handle = sv.GetHandle();
		Graphic::GraphicSystem::Instance()->UpdatePrimitiveHandle(handle, &dvb, NULL);

		return box;
	}

	void SpriteRectMesh::buildVertexTemplate() const
	{
		SizeT vertex_count = RECT_VERTEX_COUNT;

		mVertexTemplate.Resize(vertex_count * sizeof(_vertex_template));		

		_vertex_template* vertices = mVertexTemplate.As<_vertex_template>();

		float3 top(0.0f, 0.5f, 0.0f);
		float3 right( 0.5f, 0.0f, 0.0f);
		float3 origin(0.5f, 0.5f, 0.0f);
		MeshBuilder::ParallelogramBuilder::Set(vertices, top, right, origin, 0);

		//if(mRotation != quaternion::identity())
		//{
		//	matrix44 tran = matrix44::rotationquaternion(mRotation);
		//	MeshBuilder::TransformPositions(vertices, vertex_count, sizeof(_vertex_template), 0, tran);
		//	MeshBuilder::TransformNormals(vertices, vertex_count, sizeof(_vertex_template), _vertex_template::normal_bias_in_byte, tran);
		//}
	}

	inline float3 __set_position(const float3& t_pos, const sizef& rect_size, const float2& anchor)
	{
		return float3((t_pos.x() - anchor.x()) * rect_size.width, (t_pos.y() - anchor.y()) * rect_size.height, t_pos.z());
	}

	Math::bbox SpriteRectMesh::setVertexByTemplate(_sprite_vertex* vertices, const GPtr<SpriteImage>& image, const GPtr<SpriteBlock>& block)
	{
		_vertex_template* v_template = mVertexTemplate.As<_vertex_template>();

		sizef rect_size = block->GetSize() * (image->GetPixelSize() / mPixelPerUnit);
		const float2& anchor = block->GetAnchor();

		vertices[0].position = mVertexBuffer[0] = __set_position(v_template[0].pos, rect_size, anchor);
		vertices[1].position = mVertexBuffer[1] = __set_position(v_template[1].pos, rect_size, anchor);
		vertices[2].position = mVertexBuffer[2] = __set_position(v_template[2].pos, rect_size, anchor);
		vertices[3].position = mVertexBuffer[3] = __set_position(v_template[3].pos, rect_size, anchor);

		if(mRotation != quaternion::identity())
		{
			matrix44 tran = matrix44::rotationquaternion(mRotation);
			MeshBuilder::TransformPositions(vertices, RECT_VERTEX_COUNT, sizeof(_vertex_template), 0, tran);
		}
		bbox box;
		box.begin_extend();
		box.extend(point(vertices[0].position.x(), vertices[0].position.y(), vertices[0].position.z()));
		box.extend(point(vertices[1].position.x(), vertices[1].position.y(), vertices[1].position.z()));
		box.extend(point(vertices[2].position.x(), vertices[2].position.y(), vertices[2].position.z()));
		box.extend(point(vertices[3].position.x(), vertices[3].position.y(), vertices[3].position.z()));
		box.end_extend();

		const sizef& size = block->GetSize();
		const point2df& pointMin = block->GetPoint();
		point2df pointMax = point2df(pointMin.left + size.width, pointMin.top + size.height);

		vertices[0].tex_uv = float2(pointMin.left, pointMin.top);
		vertices[1].tex_uv = float2(pointMax.left, pointMin.top);
		vertices[2].tex_uv = float2(pointMin.left, pointMax.top);
		vertices[3].tex_uv = float2(pointMax.left, pointMax.top);

		mIndicBuffer[0] = 0;
		mIndicBuffer[1] = 1;
		mIndicBuffer[2] = 2;
		mIndicBuffer[3] = 1;
		mIndicBuffer[4] = 3;
		mIndicBuffer[5] = 2;

		return box;
	}

	bool SpriteRectMesh::Intersect( const Math::Ray& localRay, Math::scalar& fout, scalar fTolerance /*= N_TINY*/ )
	{
		if (0 == mVertexTemplate.GetSize())
		{
			return false;
		}

		bool isPicked = false;
		for ( IndexT i = 0; i < 6;)
		{
			scalar f;
			ushort index0 = mIndicBuffer[i];
			ushort index1 = mIndicBuffer[i+1];
			ushort index2 = mIndicBuffer[i+2];
			float3 p1(mVertexBuffer[index0].x(), mVertexBuffer[index0].y(), mVertexBuffer[index0].z());
			float3 p2(mVertexBuffer[index1].x(), mVertexBuffer[index1].y(), mVertexBuffer[index1].z());
			float3 p3(mVertexBuffer[index2].x(), mVertexBuffer[index2].y(), mVertexBuffer[index2].z());
			if ( Math::Intersection::Intersect(localRay, p1, p2, p3, f, fTolerance ) )
			{
				isPicked = true;
				fout = (f < fout ? f : fout);
			}
			i += 3;
		}

		return isPicked;
	}

}