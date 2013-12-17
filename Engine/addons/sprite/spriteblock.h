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
#ifndef __SPRITE_BLOCK_H__
#define __SPRITE_BLOCK_H__
#include "foundation/util/string.h"
#include "sprite/spriteobject.h"
#include "foundation/math/size.h"
#include "foundation/math/point2d.h"

namespace Serialization
{
	class SerializeWriter;
	class SerializeReader;
}

namespace Sprite
{
	class SpriteBlock : public SpriteObject
	{
		__DeclareSubClass(SpriteBlock, SpriteObject)
	public:
		SpriteBlock();
		virtual ~SpriteBlock();

		virtual void Save(GPtr<Serialization::SerializeWriter>& pWriter) const;
		virtual void Load(const GPtr<Serialization::SerializeReader>& pReader);
		virtual void CopyFrom(const GPtr<SpriteObject>& obj);

		const Util::String& GetName() const;
		const Math::point2df& GetPoint() const;
		const Math::sizef& GetSize() const;
		const Math::float2& GetAnchor() const;

		int GetImageIndex() const;

		void SetName(const Util::String& name);
		void SetImageIndex(int index);
		void SetPoint(const Math::point2df& point);
		void SetSize(const Math::sizef& size);
		void SetAnchor(const Math::float2& anchor);

		void Destroy();
		bool IsDestroyed() const;

	private:
		Util::String mName;
		int mImageIndex;
		Math::point2df mPoint;
		Math::sizef mSize;
		/** anchorPoint is the point around which all transformations and positioning manipulations take place.
		The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
		But you can use values higher than (1,1) and lower than (0,0) too.
		The default anchorPoint is (0.5,0.5), so it starts in the center of the node.
		*/
		Math::float2 mAnchor;

		static const uint sVersion;
	};

	inline const Util::String& SpriteBlock::GetName() const
	{
		return mName;
	}

	inline const Math::point2df& SpriteBlock::GetPoint() const
	{
		return mPoint;
	}

	inline const Math::sizef& SpriteBlock::GetSize() const
	{
		return mSize;
	}

	inline const Math::float2& SpriteBlock::GetAnchor() const
	{
		return mAnchor;
	}
	inline int SpriteBlock::GetImageIndex() const
	{
#ifdef __SPRITE_CHECK__
		if (SpriteObject::DestroyFlagInt == mImageIndex)
		{
			return InvalidIndex;
		}
#endif
		return mImageIndex;
	}

	inline void SpriteBlock::SetName(const Util::String& name)
	{
		mName = name;
	}

	inline void SpriteBlock::SetImageIndex(int index)
	{
		mImageIndex = index;
		__SPRITE_OBJECT_CHANGE__
	}

	inline void SpriteBlock::SetPoint(const Math::point2df& point)
	{
		mPoint = point;
		__SPRITE_OBJECT_CHANGE__
	}

	inline void SpriteBlock::SetSize(const Math::sizef& size)
	{
		mSize = size;
		__SPRITE_OBJECT_CHANGE__
	}

	inline void SpriteBlock::SetAnchor(const Math::float2& anchor)
	{
		mAnchor = anchor;
		__SPRITE_OBJECT_CHANGE__
	}

	inline bool SpriteBlock::IsDestroyed() const
	{
		return (SpriteObject::DestroyFlagInt == mImageIndex);
	}
}

#endif //__SPRITE_BLOCK_H__