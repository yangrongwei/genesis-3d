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
#include "spritematerial.h"
#include "spritepackage.h"
#include "resource/resinfo.h"
#include "resource/resourcemanager.h"

namespace Sprite
{
#define DEFINE_SERIAL_ITEM_NAME(name) static const char* g##name##Tag = #name
	const uint SpriteMaterial::sVersion = 1;
	DEFINE_SERIAL_ITEM_NAME(MatID);
	DEFINE_SERIAL_ITEM_NAME(Name);
	__ImplementClass(SpriteMaterial,'SPMT', SpriteObject);

	SpriteMaterial::SpriteMaterial()
	{

	}

	SpriteMaterial::~SpriteMaterial()
	{

	}

	void SpriteMaterial::SetMaterialID(const Resources::ResourceId& id)
	{
		mMaterialRes = Resources::ResourceManager::Instance()->CreateMaterialInfoByMatID(id);
		mMaterialRes->SetSave(false);

		__SPRITE_OBJECT_CHANGE__
			__SPRITE_CHANGE__
	}

	Resources::ResourceId SpriteMaterial::GetMaterialID() const
	{
		if (mMaterialRes)
		{
			return mMaterialRes->GetMatID();
		}
		return Resources::ResourceId();
	}

	void SpriteMaterial::Save(GPtr<Serialization::SerializeWriter>& pWriter) const
	{
		pWriter->SerializeVersion(sVersion);
		__SaveSuper(pWriter);

		pWriter->SerializeString(gNameTag, mName);
		pWriter->SerializeString(gMatIDTag, mMaterialRes->GetMatID().AsString());
	}

	void SpriteMaterial::Load(const GPtr<Serialization::SerializeReader>& pReader)
	{
		Serialization::SVersion version;
		pReader->SerializeVersion(version);

		__LoadSuper(pReader);
		pReader->SerializeString(gNameTag, mName);
		Util::String id;
		pReader->SerializeString(gMatIDTag, id);
		SetMaterialID(id);
	}

	void SpriteMaterial::CopyFrom(const GPtr<SpriteObject>& obj)
	{
		Super::CopyFrom(obj);
		GPtr<SpriteMaterial> sub = obj.downcast<SpriteMaterial>();
		if (sub->mMaterialRes)
		{
			SetMaterialID(sub->mMaterialRes->GetMatID());
		}
		else
		{
			mMaterialRes = NULL;
		}
		mName = sub->mName;
	}
}