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
#ifndef __SPRITE_MESH_H__
#define __SPRITE_MESH_H__
#include "foundation/core/refcounted.h"
#include "foundation/Util/array.h"
#include "foundation/math/size.h"
#include "foundation/math/float3.h"
#include "foundation/math/color.h"
#include "foundation/math/bbox.h"
#include "foundation/math/quaternion.h"
#include "foundation/math/ray.h"
#include "sprite/spritedef.h"
#include "sprite/spriteobject.h"
#include "sprite/spriteutils.h"

namespace Sprite
{
	class SpriteMesh : public SpriteObject
	{
		__DeclareSubClass(SpriteMesh, SpriteObject)
	public:

		virtual ~SpriteMesh();
		enum Arguments
		{
			ArgNone = BIT_FLAG_NONE,
			ArgBlock = BIT_FLAG(0),
			ArgString = BIT_FLAG(1),
		};

		virtual void Save(GPtr<Serialization::SerializeWriter>& pWriter) const;
		virtual void Load(const GPtr<Serialization::SerializeReader>& pReader);
		virtual void CopyFrom(const GPtr<SpriteObject>& obj);

		virtual Math::bbox CreateVertex(SpriteVertexUnit& sv, const GPtr<SpriteImage> image, const GPtr<SpriteBlock>& block);

		virtual Math::bbox UpdateVertex(SpriteVertexUnit& sv, const GPtr<SpriteImage> image, const GPtr<SpriteBlock>& block);

		Arguments GetArgumentsMark() const;

		const Util::String& GetName() const;

		virtual bool Intersect(const Math::Ray& localRay, Math::scalar& fout, Math::scalar fTolerance = N_TINY ){return false;};

	protected:
		SpriteMesh(Arguments mark);
		Arguments mMark;
		Util::String mName;
	private:
		SpriteMesh();
		static const uint sVersion;
	};

	inline SpriteMesh::Arguments SpriteMesh::GetArgumentsMark() const
	{
		return mMark;
	}

	inline const Util::String& SpriteMesh::GetName() const
	{
		return mName;
	}
	class SpriteRectMesh : public SpriteMesh
	{
		__DeclareSubClass(SpriteRectMesh, SpriteMesh)
	public:
		SpriteRectMesh();
		virtual ~SpriteRectMesh();

		virtual void Save(GPtr<Serialization::SerializeWriter>& pWriter) const;
		virtual void Load(const GPtr<Serialization::SerializeReader>& pReader);
		virtual void CopyFrom(const GPtr<SpriteObject>& obj);

		virtual Math::bbox CreateVertex(SpriteVertexUnit& sv, const GPtr<SpriteImage> image, const GPtr<SpriteBlock>& block);
		virtual Math::bbox UpdateVertex(SpriteVertexUnit& sv, const GPtr<SpriteImage> image, const GPtr<SpriteBlock>& block);

		float GetPixelPerUnit() const;
		void SetPixelPerUnit(float value);

		bool Intersect(const Math::Ray& localRay, Math::scalar& fout, Math::scalar fTolerance = N_TINY);
	private:
		struct _vertex_template 
		{
			Math::float3 pos;
		};

		void buildVertexTemplate() const;
		Math::bbox setVertexByTemplate(_sprite_vertex* vertices, const GPtr<SpriteImage>& image, const GPtr<SpriteBlock>& block);	

		float mPixelPerUnit;
		Math::quaternion mRotation;
		mutable MemoryBlock mVertexTemplate;

		Math::float3 mVertexBuffer[4];
		unsigned short mIndicBuffer[6];

		static const uint sVersion;
	};

	inline float SpriteRectMesh::GetPixelPerUnit() const
	{
		return mPixelPerUnit;
	}
}

#endif //__SPRITE_MESH_H__s