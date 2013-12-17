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
#include "resource/resourcemanager.h"
#include "spritematerial.h"
#include "spriteimage.h"
#include "spritepackage.h"
namespace Sprite
{
	static const Graphic::ShaderParamString& gDiffuseParam = "_diffuseMap";

#define DEFINE_SERIAL_ITEM_NAME(name) static const char* g##name##Tag = #name
	const uint SpriteImage::sVersion = 1;
	DEFINE_SERIAL_ITEM_NAME(TexID);
	DEFINE_SERIAL_ITEM_NAME(Name);
	DEFINE_SERIAL_ITEM_NAME(PixelSize);
	DEFINE_SERIAL_ITEM_NAME(RowNum);
	DEFINE_SERIAL_ITEM_NAME(ColNum);

	__ImplementClass(SpriteImage,'SPIM', SpriteObject);

	SpriteImage::SpriteImage()
		:mRowNum(1)
		,mColNum(1)
	{

	}

	SpriteImage::~SpriteImage()
	{

	}

	void SpriteImage::RemoveTextureID()
	{
		__SPRITE_OBJECT_CHANGE__
			__SPRITE_CHANGE__
			mTextureRes = NULL;
	}

	void SpriteImage::PushTexture()
	{
		//if (mTextureRes)
		//{
		GPtr<SpriteMaterial>& spmt = mParent->GetMaterial();
		spmt->GetMaterialRes()->GetHandle()->SetTexture(gDiffuseParam, mTextureRes);
		//}

	}


	void SpriteImage::_setTextureID(const Resources::ResourceId& id, Resources::Priority priority)
	{
		mTextureRes = Resources::ResourceManager::Instance()->CreateTextureInfo(id, priority);
	}

	void SpriteImage::SetTextureID(const Resources::ResourceId& id, const Math::sizef& size, Resources::Priority priority)
	{
		__SPRITE_OBJECT_CHANGE__
			_setTextureID(id, priority);
		SetPixelSize(size);
	}

	void SpriteImage::Save(GPtr<Serialization::SerializeWriter>& pWriter) const
	{
		pWriter->SerializeVersion(sVersion);
		__SaveSuper(pWriter);

		pWriter->SerializeString(gNameTag, mName);
		pWriter->SerializeInt(gRowNumTag, mRowNum);
		pWriter->SerializeInt(gColNumTag, mColNum);
		pWriter->SerializeFloat2(gPixelSizeTag, *((const Math::float2*)(&mPixelSize)));
		Util::String texID("");
		if (mTextureRes && mTextureRes->GetResID().IsValid())
		{
			texID = mTextureRes->GetResID().Value();
		}
		pWriter->SerializeString(gTexIDTag, texID);
	}

	void SpriteImage::Load(const GPtr<Serialization::SerializeReader>& pReader)
	{
		Serialization::SVersion version;
		pReader->SerializeVersion(version);
		__LoadSuper(pReader);
		pReader->SerializeString(gNameTag, mName);
		pReader->SerializeInt(gRowNumTag, mRowNum);
		pReader->SerializeInt(gColNumTag, mColNum);
		pReader->SerializeFloat2(gPixelSizeTag, *((Math::float2*)(&mPixelSize)));

		Util::String id;
		pReader->SerializeString(gTexIDTag, id);
		if (id.Length() > 0)
		{
			_setTextureID(id, 1);
		}
	}

	void SpriteImage::CopyFrom(const GPtr<SpriteObject>& obj)
	{
		Super::CopyFrom(obj);
		GPtr<SpriteImage> sub = obj.downcast<SpriteImage>();

		mTextureRes = sub->mTextureRes;
		mName = sub->mName;
		mPixelSize = sub->mPixelSize;
		mRowNum = sub->mRowNum;
		mColNum = sub->mColNum;
	}
}