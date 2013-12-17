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
#ifndef __SPRITE_PLAYER_H__
#define __SPRITE_PLAYER_H__

#include "math/bbox.h"
#include "resource/resource.h"
#include "sprite/spritedef.h"
#include "sprite/spritevertex.h"
#include "math/color.h"


namespace Resources
{
	class SpritePackageResInfo;
	class MaterialResInfo;
	class TextureResInfo;
}

namespace Serialization
{
	class SerializeWriter;
	class SerializeReader;
}

namespace Sprite
{	
	class SpriteMesh;
	class SpriteAnimation;
	class SpriteBlock;
	class SpriteImage;

	class SpriteInfo
	{
	public:
		SpriteInfo();
		~SpriteInfo();
		void Set(const Resources::ResourceId& packId);

		void CreateVertex(const GPtr<SpriteBlock>& block, const utf8* str);

		void UpdateVertex(const GPtr<SpriteBlock>& block, const utf8* str);

		void Destroy();

		Resources::ResourceId GetPackID() const;

		const Math::bbox& GetBoundingBox() const;

		const RenderBase::PrimitiveHandle& GetPrimitiveHandle() const;

		const GPtr<Resources::SpritePackageResInfo>& GetPackageResInfo() const;

		GPtr<Resources::MaterialResInfo> GetMaterial() const;

		void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		bool IsValid() const;

#ifdef __SPRITE_CHECK__
		bool CheckMaterial();
#endif
	private:
		GPtr<Resources::SpritePackageResInfo> mPackageResInfo;
		SpriteVertexUnit mVertexUnit;
		Math::bbox mBoundingBox;

#ifdef __SPRITE_CHECK__
		change_count mMaterialChangeCount; 
#endif
	};


	inline const Math::bbox& SpriteInfo::GetBoundingBox() const
	{
		return mBoundingBox;
	}

	inline const GPtr<Resources::SpritePackageResInfo>& SpriteInfo::GetPackageResInfo() const
	{
		return mPackageResInfo;
	}

	inline const RenderBase::PrimitiveHandle& SpriteInfo::GetPrimitiveHandle() const
	{
		return mVertexUnit.GetHandle();
	}

	inline bool SpriteInfo::IsValid() const
	{
		return mPackageResInfo.isvalid();
	}


	class SpritePlayer
	{
	public:
		SpritePlayer();
		~SpritePlayer();

		void SetBlock(const Util::String& blockName);

		void SetAnimation(const Util::String& name, int loops = 0, float speed = 1.0f);

		void RemoveBlock();

		void RemoveAnimation();

		void Reset(SpriteInfo* info);

		void SetAnimationSpeed(float speed);

		Util::String GetBlockName() const;
		Util::String GetAnimationName() const;
		int GetAnimationLoops() const;
		float GetAnimationSpeed() const;
		bool IsAnimationPlaying() const;

		void Tick(float time);

		void Replay();

		void Play();

		void Pause();

		void Stop();

		bool CanDraw() const;

		GPtr<SpriteImage> GetImage() const;

		void Dirty();

		bool IsDirty() const;

		void RemoveDirtyFlag();

		bool IsSetup() const;

		bool HasBlcok() const;

		bool HasAnimation() const;

		int GetFrameCount() const;

		int GetCurrentFrameIndex() const;

		void SetCurrentFrame(int frameIndex);

		float GetTotalUnits() const;

		float GetCurrentUnits() const;

		void SetCurrentUnits(float units);

		void DeviceLost();

	private:
		void updateAnimation();
#ifdef __SPRITE_CHECK__
		void checkAnimation();
		void checkDefualtBlock();
		change_count mDefaultBlockChangeCount; 
		change_count mAnimationChangeCount; 
#endif
		SpriteInfo* mSpriteInfo;
		GPtr<SpriteAnimation> mAnimation;
		GPtr<SpriteBlock> mDefaultBlock;
		int				 mCurrentImageIndex;
		bool mDirty;
	};

	inline bool SpritePlayer::IsDirty() const
	{
		return mDirty;
	}

	inline void SpritePlayer::RemoveDirtyFlag()
	{
		mDirty = false;
	}

	inline void SpritePlayer::Dirty()
	{
		mDirty = true;
	}

	inline bool SpritePlayer::IsSetup() const
	{
		return (NULL != mSpriteInfo);
	}

	inline bool SpritePlayer::CanDraw() const
	{
		return InvalidIndex != mCurrentImageIndex;
	}

	inline bool SpritePlayer::HasBlcok() const
	{
		return mDefaultBlock.isvalid();
	}

	inline bool SpritePlayer::HasAnimation() const
	{
		return mAnimation.isvalid();
	}
}

#endif //__SPRITE_PLAYER_H__