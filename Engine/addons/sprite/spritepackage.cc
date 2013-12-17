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
#include "spritedef.h"
#include "spritepackage.h"
#include "spritemesh.h"
#include "spriteblock.h"
#include "spriteanimationclip.h"
#include "spritematerial.h"
#include "spriteimage.h"

#include "resource/resinfo.h"
#include "resource/resourcemanager.h"
namespace Sprite
{
	const uint SpritePackage::sVersion = 1;
#define DEFINE_SERIAL_ITEM_NAME(name) static const char* g##name##Tag = #name

	//DEFINE_SERIAL_ITEM_NAME(ID);
	DEFINE_SERIAL_ITEM_NAME(ObjCount);

	__ImplementClass( Sprite::SpritePackage, 'SPPK', Core::RefCounted);

	SpritePackage::SpritePackage()
	{

	}

	SpritePackage::~SpritePackage()
	{

	}

	void SpritePackage::CopyFrom(const GPtr<SpritePackage>& obj)
	{
		SpritePackage* pack = obj.get();
		if (pack->mMesh)
		{
			if (!mMesh)
			{
				mMesh = SpriteRectMesh::Create();
			}

			mMesh->CopyFrom(pack->mMesh.upcast<SpriteObject>());
			mMesh->_SetParent(this);
		}
		else
		{
			mMesh = NULL;
		}

		if (pack->mMaterial)
		{
			if (!mMaterial)
			{
				mMaterial = SpriteMaterial::Create();
			}
			mMaterial->CopyFrom(pack->mMaterial.upcast<SpriteObject>());
			mMaterial->_SetParent(this);
		}
		else
		{
			mMaterial = NULL;
		}

		clear();

		Images::Iterator iit = pack->mImages.Begin();
		Images::Iterator iend = pack->mImages.End();
		while(iit != iend)
		{
			SpriteImagePtr ip = SpriteImage::Create();
			ip->CopyFrom((*iit).upcast<SpriteObject>());
			ip->_SetParent(this);
			mImages.Append(ip);
			++iit;
		}

		Blocks::Iterator bit = pack->mBlocks.Begin();
		Blocks::Iterator bend = pack->mBlocks.End();
		while(bit != bend)
		{
			SpriteBlockPtr sb = SpriteBlock::Create();
			sb->CopyFrom((*bit).upcast<SpriteObject>());
			sb->_SetParent(this);
			mBlocks.Append(sb);
			++bit;
		}

		AnimationClips::Iterator ait = pack->mAnimationClips.Begin();
		AnimationClips::Iterator aend = pack->mAnimationClips.End();
		while(ait != aend)
		{
			SpriteAnimationClipPtr sa = SpriteAnimationClip::Create();
			sa->CopyFrom((*ait).upcast<SpriteObject>());
			mAnimationClips.Append(sa);
			++ait;
		}

	}

	void SpritePackage::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		if (mMaterial)
		{
			list.Append(Resources::ReferenceResource(mMaterial->GetMaterialID(), Resources::RR_Material));
		}
		for (int i = 0; i < mImages.Size(); ++i)
		{
			SpriteImage::TextureResPtr textureRes = mImages[i]->GetTextureRes();
			if (textureRes.isvalid())
			{
				list.Append(Resources::ReferenceResource(textureRes->GetResID(), Resources::RR_Unknown));
			}
		}
	}

	const SpritePackage::SpriteMaterialPtr& SpritePackage::GetMaterial() const
	{
		return mMaterial;
	}
	SpritePackage::SpriteMaterialPtr& SpritePackage::GetMaterial()
	{
		return mMaterial;
	}

	const SpritePackage::SpriteMeshPtr& SpritePackage::GetMesh() const
	{
		return mMesh;
	}

	SpritePackage::SpriteAnimationClipPtr SpritePackage::GetAnimation(const Util::String& name) const
	{
		AnimationClips::Iterator it = mAnimationClips.Begin();
		AnimationClips::Iterator end = mAnimationClips.End();
		while(it != end)
		{
			if ((*it)->GetName() == name)
			{
				return *it;
			}
			++it;
		}
		return NULL;
	}

	SpritePackage::SpriteBlockPtr SpritePackage::GetBlock(const Util::String& name) const
	{
		Blocks::Iterator it = mBlocks.Begin();
		Blocks::Iterator end = mBlocks.End();
		while(it != end)
		{
			if ((*it)->GetName() == name)
			{
				return *it;
			}
			++it;
		}
		return NULL;
	}

	SpritePackage::SpriteImagePtr SpritePackage::GetImage(const Util::String& name) const
	{
		Images::Iterator it = mImages.Begin();
		Images::Iterator end = mImages.End();
		while(it != end)
		{
			if ((*it)->GetName() == name)
			{
				return *it;
			}
			++it;
		}
		return NULL;
	}

	SpritePackage::SpriteAnimationClipPtr SpritePackage::GetAnimation( int index ) const
	{
		if (0 <= index && index < mAnimationClips.Size())
		{
			return mAnimationClips[index];
		}
		return NULL;
	}

	SpritePackage::SpriteBlockPtr SpritePackage::GetBlock(int index) const
	{
		if (0 <= index && index < mBlocks.Size())
		{
			return mBlocks[index];
		}
		return NULL;
	}

	SpritePackage::SpriteImagePtr SpritePackage::GetImage(int index) const
	{
		if (0 <= index && index < mImages.Size())
		{
			return mImages[index];
		}
		return NULL;
	}

	template<typename T>
	int __find(int begin, const Util::Array<T>& array, const Util::String key)
	{
		for (int i = begin; i < array.Size(); ++i)
		{
			if (array[i]->GetName() == key)
			{
				return i;
			}
		}
		return InvalidIndex;
	}

	int SpritePackage::GetBlockIndex(const Util::String& name) const
	{
		return __find(0, mBlocks, name);
	}

	int SpritePackage::GetImageIndex(const Util::String& name) const
	{
		return __find(0, mImages, name);
	}

	void SpritePackage::SetMaterial(SpriteMaterialPtr material)
	{
		material->_SetParent(this);
		mMaterial = material;
	}

	void SpritePackage::SetMesh(SpriteMeshPtr mesh)
	{
		mesh->_SetParent(this);
		mMesh = mesh;
	}

	void SpritePackage::AddAnimation(SpriteAnimationClipPtr clip)
	{
		clip->_SetParent(this);
		mAnimationClips.Append(clip);
	}

	void SpritePackage::AddBlock(SpriteBlockPtr block)
	{
		block->_SetParent(this);
		mBlocks.Append(block);
	}

	void SpritePackage::AddImage(SpriteImagePtr image)
	{
		image->_SetParent(this);
		mImages.Append(image);
	}

	void SpritePackage::RemoveImage(const Util::String& name)
	{
		int index = 0;
		while(true)
		{
			index = __find(index, mImages, name);
			if (InvalidIndex != index)
			{
				rebuildBlocks(index);
				mImages[index]->_SetParent(NULL);
				mImages.EraseIndex(index);				
			}
			else
			{
				break;
			}
		}
	}

	void SpritePackage::RemoveImage( int index )
	{
		if (index >= 0 && index < mImages.Size())
		{
			rebuildBlocks(index);
			mImages[index]->_SetParent(NULL);
			mImages.EraseIndex(index);
		}
	}

	void SpritePackage::RemoveBlock(const Util::String& name)
	{
		int index = 0;
		while(true)
		{
			index = __find(index, mBlocks, name);

			if (InvalidIndex != index)
			{
				rebuildClips(index);
				mBlocks[index]->Destroy();
				mBlocks.EraseIndex(index);				
			}
			else
			{
				break;
			}
		}
	}

	void SpritePackage::RemoveBlock( int index )
	{
		if (index >= 0 && index < mBlocks.Size())
		{
			rebuildClips(index);
			mBlocks[index]->Destroy();
			mBlocks[index]->_SetParent(NULL);
			mBlocks.EraseIndex(index);

		}
	}

	void SpritePackage::RemoveAnimation(const Util::String& name)
	{
		int index = 0;
		while(true)
		{
			index = __find(index, mAnimationClips, name);
			if (InvalidIndex != index)
			{
				mAnimationClips[index]->Destroy();
				mAnimationClips[index]->_SetParent(NULL);
				mAnimationClips.EraseIndex(index);				
			}
			else
			{
				break;
			}
		}
	}

	void SpritePackage::RemoveAnimation( int animClipIndex )
	{
		if (animClipIndex >= 0 && animClipIndex < mAnimationClips.Size())
		{
			mAnimationClips[animClipIndex]->Destroy();
			mAnimationClips[animClipIndex]->_SetParent(NULL);
			mAnimationClips.EraseIndex(animClipIndex);
		}
	}
#ifdef __SPRITE_CHECK__
	void SpritePackage::_Dirty()
	{

		Blocks::Iterator iit = mBlocks.Begin();
		Blocks::Iterator iend = mBlocks.End();
		while(iit != iend)
		{
			(*iit)->objectChange();
			++iit;
		}

		AnimationClips::Iterator ait = mAnimationClips.Begin();
		AnimationClips::Iterator aend = mAnimationClips.End();
		while(ait != aend)
		{
			(*ait)->objectChange();
			++ait;
		}
	}
#endif

	void SpritePackage::clear()
	{
#ifdef __SPRITE_CHECK__
		Blocks::Iterator iit = mBlocks.Begin();
		Blocks::Iterator iend = mBlocks.End();
		while(iit != iend)
		{
			(*iit)->Destroy();
			++iit;
		}

		AnimationClips::Iterator ait =mAnimationClips.Begin();
		AnimationClips::Iterator aend = mAnimationClips.End();
		while(ait != aend)
		{
			(*ait)->Destroy();
			++ait;
		}
#endif
		mImages.Clear();
		mBlocks.Clear();
		mAnimationClips.Clear();
	}

	void SpritePackage::rebuildBlocks(int image_del_index)
	{
		for (int i = 0; i < mBlocks.Size(); ++i)
		{
			if (mBlocks[i]->GetImageIndex() == image_del_index)
			{
				mBlocks[i]->SetImageIndex(InvalidIndex);
			}
			else if(mBlocks[i]->GetImageIndex() > image_del_index)
			{
				mBlocks[i]->SetImageIndex(mBlocks[i]->GetImageIndex() - 1);
			}
		}
	}

	void SpritePackage::rebuildClips(int block_del_index)
	{
		for (int i = 0; i < mAnimationClips.Size(); ++i)
		{
			mAnimationClips[i]->_RebuildFrames(block_del_index);
		}
	}

	void SpritePackage::save(GPtr<Serialization::SerializeWriter>& pWriter) const
	{
		//
		//pWriter->BeginFileSerialize();

		pWriter->BeginSerializeObject(GetClassFourCC());//fourcc
		pWriter->SerializeVersion(sVersion);

		n_assert(mMesh);
		n_assert(mMaterial);
		int obj_count = 2 + mImages.Size() + mBlocks.Size() + mAnimationClips.Size();

		pWriter->SerializeInt(gObjCountTag, obj_count);

		saveObject(pWriter, mMesh.upcast<SpriteObject>());

		saveObject(pWriter, mMaterial.upcast<SpriteObject>());

		for (int i = 0; i < mImages.Size(); ++i)
		{
			saveObject(pWriter, mImages[i].upcast<SpriteObject>());
		}

		for (int i = 0; i < mBlocks.Size(); ++i)
		{
			saveObject(pWriter, mBlocks[i].upcast<SpriteObject>());
		}

		for (int i = 0; i < mAnimationClips.Size(); ++i)
		{
			saveObject(pWriter, mAnimationClips[i].upcast<SpriteObject>());
		}


		pWriter->EndSerializeObject();
		//pWriter->EndFileSerialize();
	}

	void SpritePackage::load(const GPtr<Serialization::SerializeReader>& pReader)
	{
		pReader->BeginFileSerialize();

		Util::FourCC fourcc;
		pReader->BeginSerializeObject(fourcc);
		Serialization::SVersion version;
		pReader->SerializeVersion(version);

		if (fourcc == GetClassFourCC())
		{
			int obj_count = 0;
			pReader->SerializeInt(gObjCountTag, obj_count);
			for (int i = 0; i < obj_count; ++i)
			{
				SpriteObjectPtr obj = loadObject(pReader);
				obj->_SetParent(this);
				if(obj->IsA(SpriteBlock::RTTI))
				{	
					mBlocks.Append(obj.downcast<SpriteBlock>());
				} 
				else if(obj->IsA(SpriteImage::RTTI))
				{
					mImages.Append(obj.downcast<SpriteImage>());
				}
				else if(obj->IsA(SpriteAnimationClip::RTTI))
				{
					mAnimationClips.Append(obj.downcast<SpriteAnimationClip>());
				}
				else if (obj->IsA(SpriteMesh::RTTI))
				{
					mMesh = obj.downcast<SpriteMesh>();
					mMesh->_SetParent(this);
				}
				else if(obj->IsA(SpriteMaterial::RTTI))
				{
					mMaterial = obj.downcast<SpriteMaterial>();
				}	 
			}
		}

		pReader->EndSerializeObject();
		pReader->EndFileSerialize();
	}

	void SpritePackage::saveObject(GPtr<Serialization::SerializeWriter>& pWriter, const SpriteObjectPtr& object) const
	{
		pWriter->BeginSerializeObject(object->GetClassFourCC());//fourcc
		object->Save(pWriter);
		pWriter->EndSerializeObject();
	}

	SpritePackage::SpriteObjectPtr SpritePackage::loadObject(const GPtr<Serialization::SerializeReader>& pReader)
	{
		SpriteObjectPtr obj = pReader->BeginSerializeObjectT<SpriteObject>();//fourcc
		obj->Load(pReader);
		pReader->EndSerializeObject();

		return obj;
	}

	int SpritePackage::GetAnimationClipCount() const
	{
		return mAnimationClips.Size();
	}

	int SpritePackage::GetImageCount() const
	{
		return mImages.Size();
	}

	int SpritePackage::GetBlockCount() const
	{
		return mBlocks.Size();
	}

}