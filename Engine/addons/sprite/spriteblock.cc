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
#include "spriteblock.h"

namespace Sprite
{
	const uint SpriteBlock::sVersion = 1;

#define DEFINE_SERIAL_ITEM_NAME(name) static const char* g##name##Tag = #name

	DEFINE_SERIAL_ITEM_NAME(Name);
	DEFINE_SERIAL_ITEM_NAME(ImageIndex);
	DEFINE_SERIAL_ITEM_NAME(Point);
	DEFINE_SERIAL_ITEM_NAME(Size);
	DEFINE_SERIAL_ITEM_NAME(Anchor);

	__ImplementClass(SpriteBlock,'SPBL', SpriteObject);
	SpriteBlock::SpriteBlock()
		:mImageIndex(InvalidIndex)
		,mAnchor(0.5f, 0.5f)
	{

	}

	SpriteBlock::~SpriteBlock()
	{

	}
	void SpriteBlock::Destroy()
	{
		mImageIndex = SpriteObject::DestroyFlagInt;
		__SPRITE_OBJECT_CHANGE__
	}

	void SpriteBlock::Save(GPtr<Serialization::SerializeWriter>& pWriter) const
	{		
		pWriter->SerializeVersion(sVersion);
		__SaveSuper(pWriter);

		pWriter->SerializeString(gNameTag, mName);
		pWriter->SerializeInt(gImageIndexTag, mImageIndex);
		pWriter->SerializeFloat2(gPointTag, *((const Math::float2*)&mPoint));
		pWriter->SerializeFloat2(gSizeTag, *((const Math::float2*)&mSize));
		pWriter->SerializeFloat2(gAnchorTag, *((const Math::float2*)&mAnchor));
	}

	void SpriteBlock::Load(const GPtr<Serialization::SerializeReader>& pReader)
	{
		Serialization::SVersion version;
		pReader->SerializeVersion(version);

		__LoadSuper(pReader);

		pReader->SerializeString(gNameTag, mName);
		pReader->SerializeInt(gImageIndexTag, mImageIndex);
		pReader->SerializeFloat2(gPointTag, *((Math::float2*)&mPoint));
		pReader->SerializeFloat2(gSizeTag, *((Math::float2*)&mSize));
		pReader->SerializeFloat2(gAnchorTag, *((Math::float2*)&mAnchor));

	}

	void SpriteBlock::CopyFrom(const GPtr<SpriteObject>& obj)
	{
		Super::CopyFrom(obj);

		GPtr<SpriteBlock> sb = obj.downcast<SpriteBlock>();
		this->mName = sb->mName;
		this->mImageIndex = sb->mImageIndex;
		this->mPoint = sb->mPoint;
		this->mSize = sb->mSize;
		this->mAnchor = sb->mAnchor;
	}
}