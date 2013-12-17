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
#ifndef __SPRITE_PACKAGE_H__
#define __SPRITE_PACKAGE_H__
#include "foundation/core/refcounted.h"
#include "foundation/util/array.h"

namespace Serialization
{
	class SerializeWriter;
	class SerializeReader;
}

namespace Resources
{
	struct ReferenceResource;
}
namespace Sprite
{
	class SpriteObject;
	class SpriteMesh;
	class SpriteBlock;
	class SpriteAnimationClip;
	class SpriteMaterial;
	class SpriteImage;
	class SpritePackage : public Core::RefCounted
	{
		__DeclareClass(SpritePackage)
	public:
		SpritePackage();
		virtual ~SpritePackage();
		typedef GPtr<SpriteObject> SpriteObjectPtr;
		typedef GPtr<SpriteBlock> SpriteBlockPtr;
		typedef GPtr<SpriteMaterial> SpriteMaterialPtr;
		typedef GPtr<SpriteImage> SpriteImagePtr;
		typedef GPtr<SpriteAnimationClip> SpriteAnimationClipPtr;
		typedef GPtr<SpriteMesh> SpriteMeshPtr;

		void CopyFrom(const GPtr<SpritePackage>& obj);

		void SetMesh(SpriteMeshPtr mesh);
		void SetMaterial(SpriteMaterialPtr material);

		void AddImage(SpriteImagePtr image);
		void AddAnimation(SpriteAnimationClipPtr clip);
		void AddBlock(SpriteBlockPtr block);

		const SpriteMaterialPtr& GetMaterial() const;
		SpriteMaterialPtr& GetMaterial();
		const SpriteMeshPtr& GetMesh() const;

		int GetAnimationClipCount() const;
		int GetImageCount() const;
		int GetBlockCount() const;

		SpriteAnimationClipPtr GetAnimation(int index) const;
		SpriteAnimationClipPtr GetAnimation(const Util::String& name) const;
		SpriteBlockPtr GetBlock(const Util::String& name) const;
		SpriteImagePtr GetImage(const Util::String& name) const;

		SpriteBlockPtr GetBlock(int index) const;
		SpriteImagePtr GetImage(int index) const;

		int GetBlockIndex(const Util::String& name) const;
		int GetImageIndex(const Util::String& name) const;


		void RemoveImage(const Util::String& name);
		void RemoveImage(int index);

		void RemoveBlock(const Util::String& name);
		void RemoveBlock(int index);

		void RemoveAnimation(const Util::String& name);
		void RemoveAnimation(int animClipIndex);

		void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		void save(GPtr<Serialization::SerializeWriter>& pWriter) const;
		void load(const GPtr<Serialization::SerializeReader>& pReader);
#ifdef __SPRITE_CHECK__
		void _Dirty();
#endif
	private:

		typedef Util::Array<SpriteBlockPtr> Blocks;
		typedef Util::Array<SpriteImagePtr> Images;
		typedef Util::Array<SpriteAnimationClipPtr> AnimationClips;

		void clear();

		void rebuildBlocks(int image_del_index);

		void rebuildClips(int block_del_index);

		void saveObject(GPtr<Serialization::SerializeWriter>& pWriter, const SpriteObjectPtr& object) const;
		SpriteObjectPtr loadObject(const GPtr<Serialization::SerializeReader>& pReader);

		SpriteMeshPtr mMesh;
		SpriteMaterialPtr mMaterial;

		Images mImages;
		Blocks mBlocks;
		AnimationClips mAnimationClips;
		static const uint sVersion;
	};
}

#endif //__SPRITE_PACKAGE_H__