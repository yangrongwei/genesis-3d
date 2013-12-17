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
#include "resource/resinfo.h"
#include "resource/resourcemanager.h"

#include "spriteplayer.h"
#include "spritepackage.h"
#include "spritematerial.h"
#include "spritemesh.h"
#include "spriteblock.h"
#include "spriteanimation.h"
#include "spriteanimationclip.h"
#include "sprite/spriteimage.h"


namespace Sprite
{

	SpriteInfo::SpriteInfo()
		:mPackageResInfo(NULL)
#ifdef __SPRITE_CHECK__
		,mMaterialChangeCount(default_change_count)
#endif
	{

	}

	SpriteInfo::~SpriteInfo()
	{

	}

	void SpriteInfo::CreateVertex( const GPtr<SpriteBlock>& block, const utf8* str)
	{
		if(mVertexUnit.GetHandle().IsValid())
		{
			mVertexUnit.Destroy();
		}

		GPtr<SpritePackage> pack = mPackageResInfo->GetPackage();
		mBoundingBox = pack->GetMesh()->CreateVertex(mVertexUnit, pack->GetImage(block->GetImageIndex()), block);
	}

	void SpriteInfo::UpdateVertex(const GPtr<SpriteBlock>& block, const utf8* str)
	{
		if (0 <= block->GetImageIndex())
		{
			GPtr<SpritePackage> pack = mPackageResInfo->GetPackage();
			if(mVertexUnit.GetHandle().IsValid())
			{
				mBoundingBox = pack->GetMesh()->UpdateVertex(mVertexUnit, pack->GetImage(block->GetImageIndex()), block);
			}
			else
			{
				mBoundingBox = pack->GetMesh()->CreateVertex(mVertexUnit, pack->GetImage(block->GetImageIndex()), block);
			}
		}

	}

	void SpriteInfo::Set(const Resources::ResourceId& packId)
	{
		Destroy();
		mPackageResInfo = Resources::ResourceManager::Instance()->CreateSpritePackageResInfo(packId);	
	}

	Resources::ResourceId SpriteInfo::GetPackID() const
	{
		if (mPackageResInfo)
		{
			return mPackageResInfo->GetResID();
		}
		return Resources::ResourceId();
	}

	void SpriteInfo::Destroy()
	{
		mVertexUnit.Destroy();
	}

	GPtr<Resources::MaterialResInfo> SpriteInfo::GetMaterial() const
	{
		return mPackageResInfo->GetPackage()->GetMaterial()->GetMaterialRes();
	}

	void SpriteInfo::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		if (mPackageResInfo)
		{
			list.Append(Resources::ReferenceResource(mPackageResInfo->GetResID(), Resources::RR_Unknown));
			mPackageResInfo->GetPackage()->GetReferenceResourceId(list);
		}
	}


#ifdef __SPRITE_CHECK__
	bool SpriteInfo::CheckMaterial()
	{
		GPtr<SpriteMaterial> material = mPackageResInfo->GetPackage()->GetMaterial();
		if (mMaterialChangeCount != material->getChangeCount())
		{
			mMaterialChangeCount = material->getChangeCount();
			return true;
		}
		return false;
	}
#endif

	SpritePlayer::SpritePlayer()
		: mSpriteInfo(NULL)
		, mDirty(true)
		, mCurrentImageIndex(InvalidIndex)
#ifdef __SPRITE_CHECK__
		, mDefaultBlockChangeCount(default_change_count)
		, mAnimationChangeCount(default_change_count)
#endif
	{

	}

	SpritePlayer::~SpritePlayer()
	{

	}

	void SpritePlayer::RemoveBlock()
	{
		if ((!mAnimation.isvalid()) || (SpriteAnimation::S_Stop == mAnimation->GetState()))
		{
			mCurrentImageIndex = InvalidIndex;
		}

		mDefaultBlock = NULL;
		mDirty = true;
	}

	void SpritePlayer::RemoveAnimation()
	{
		mAnimation = NULL;
		if (mDefaultBlock.isvalid())
		{
			mCurrentImageIndex = mDefaultBlock->GetImageIndex();
		}
		else
		{
			mCurrentImageIndex = InvalidIndex;
		}
		mDirty = true;
	}

	void SpritePlayer::Reset(SpriteInfo* info)
	{
		RemoveBlock();
		RemoveAnimation();
		mSpriteInfo = info;
	}

	void SpritePlayer::SetBlock(const Util::String& blockName)
	{
		if (blockName == "")
		{
			RemoveBlock();
		}
		n_assert(mSpriteInfo);
		if (mSpriteInfo->IsValid())
		{		
			GPtr<SpritePackage> package = mSpriteInfo->GetPackageResInfo()->GetPackage();
			GPtr<SpriteBlock> block = package->GetBlock(blockName);
			if (block)
			{
				mDefaultBlock = block;
				if (!mAnimation.isvalid() || SpriteAnimation::S_Stop == mAnimation->GetState())
				{		
					if (mDefaultBlock)
					{
						mCurrentImageIndex = mDefaultBlock->GetImageIndex();
						mSpriteInfo->CreateVertex(mDefaultBlock, NULL);
					}
					mDirty = true;
				}
#ifdef __SPRITE_CHECK__
				mDefaultBlockChangeCount = default_change_count;
#endif // __SPRITE_CHECK__
			}

		}
	}

	void SpritePlayer::SetAnimation(const Util::String& name, int loops /* = 0 */, float speed /* = 1.0f */)
	{		
		if (name == "")
		{
			RemoveAnimation();
		}
		n_assert(mSpriteInfo);
		if (mSpriteInfo->IsValid())
		{
			SpritePackage::SpriteAnimationClipPtr clip = mSpriteInfo->GetPackageResInfo()->GetPackage()->GetAnimation(name);
			if (clip)
			{
				if (!mAnimation)
				{
					mAnimation = SpriteAnimation::Create();
				}
				mAnimation->SetClip(clip, loops);
				mAnimation->SetSpeed(speed);
				mAnimation->Stop();

#ifdef __SPRITE_CHECK__
				mAnimationChangeCount = clip->getChangeCount();
#endif
				mDirty = true;
			}
		}
	}

	void SpritePlayer::SetAnimationSpeed(float speed)
	{
		if (mAnimation)
		{
			mAnimation->SetSpeed(speed);
		}
	}

	Util::String SpritePlayer::GetBlockName() const
	{
		if (mDefaultBlock)
		{
			return mDefaultBlock->GetName();
		}
		return Util::String();
	}
	Util::String SpritePlayer::GetAnimationName() const
	{
		if (mAnimation)
		{
			return mAnimation->GetClipName();
		}
		return Util::String();
	}

	int SpritePlayer::GetAnimationLoops() const
	{
		if (mAnimation)
		{
			return mAnimation->GetLoops();
		}
		return 0;
	}

	float SpritePlayer::GetAnimationSpeed() const
	{
		if (mAnimation)
		{
			return mAnimation->GetSpeed();
		}
		return 0;
	}

	void SpritePlayer::DeviceLost()
	{
		if (mAnimation)
		{
			updateAnimation();
		}
		else if (mDefaultBlock)
		{
			mSpriteInfo->UpdateVertex(mDefaultBlock, NULL);
		}
	}

	void SpritePlayer::Tick(float time)
	{
		if (mAnimation)
		{
#ifdef __SPRITE_CHECK__
			checkAnimation();
#endif
			if(mAnimation->Check(time))
			{
				updateAnimation();
			}
		}
#ifdef __SPRITE_CHECK__		
		if (mDefaultBlock)
		{
			checkDefualtBlock();
		}
#endif // __SPRITE_CHECK__
	}


	void SpritePlayer::updateAnimation()
	{
		mDirty = true;
		int image_index = InvalidIndex;
		int blockIndex = mAnimation->GetCurrentBlockIndex();
		if (0 > blockIndex)
		{
			if (SpriteAnimation::S_Stop == mAnimation->GetState() && mDefaultBlock)
			{
				mSpriteInfo->UpdateVertex(mDefaultBlock, NULL);
				image_index = mDefaultBlock->GetImageIndex();
#ifdef __SPRITE_CHECK__
				mDefaultBlockChangeCount = mDefaultBlock->GetImageIndex();
#endif
			}
		}
		else
		{	
			GPtr<SpriteBlock> pb = mSpriteInfo->GetPackageResInfo()->GetPackage()->GetBlock(blockIndex);
			mSpriteInfo->UpdateVertex(pb, NULL);
			image_index = pb->GetImageIndex();
		}

		mCurrentImageIndex = image_index;
	}

#ifdef __SPRITE_CHECK__
	void SpritePlayer::checkAnimation()
	{
		if (mAnimationChangeCount != mAnimation->GetClip()->getChangeCount())
		{
			mAnimationChangeCount = mAnimation->GetClip()->getChangeCount();
			mAnimation->_DirtyFrameCache();
		}

		if (mAnimation->GetClip()->IsDestroyed())
		{
			SpritePackage::SpriteAnimationClipPtr clip = mSpriteInfo->GetPackageResInfo()->GetPackage()->GetAnimation(mAnimation->GetClip()->GetName());
			if (clip)//恢复
			{
				SpriteAnimation::State oldState = mAnimation->GetState();
				mAnimation->SetClip(clip, mAnimation->GetLoops());
				mDirty = true;
				if (SpriteAnimation::S_Pause == oldState || SpriteAnimation::S_Playing == oldState)
				{
					mAnimation->Play();
				}
			}
		}
	}

	void SpritePlayer::checkDefualtBlock()
	{
		if (mDefaultBlock->IsDestroyed())
		{
			SpritePackage::SpriteBlockPtr sb = mSpriteInfo->GetPackageResInfo()->GetPackage()->GetBlock(mDefaultBlock->GetName());
			if (sb)//资源恢复。
			{
				mDefaultBlock = sb;
				mDefaultBlockChangeCount = default_change_count;
			}
		}

		if (mDefaultBlockChangeCount != mDefaultBlock->getChangeCount())
		{
			mDirty = true;
			if (NULL == mAnimation || SpriteAnimation::S_Stop == mAnimation->GetState())
			{
				mCurrentImageIndex = mDefaultBlock->GetImageIndex();		
				mSpriteInfo->UpdateVertex(mDefaultBlock, NULL);
			}
			mDefaultBlockChangeCount = mDefaultBlock->getChangeCount();

		}
	}
#endif // __SPRITE_CHECK__

	void SpritePlayer::Replay()
	{
		if (mAnimation)
		{
			mAnimation->Replay();
		}
	}

	void SpritePlayer::Play()
	{
		if (mAnimation)
		{
			mAnimation->Play();
		}
	}

	void SpritePlayer::Pause()
	{
		if (mAnimation)
		{
			mAnimation->Pause();
		}
	}

	int SpritePlayer::GetFrameCount() const
	{
		if (mAnimation)
		{
			return mAnimation->GetFrameCount();
		}
		return InvalidIndex;
	}

	int SpritePlayer::GetCurrentFrameIndex() const
	{
		if (mAnimation)
		{
			return mAnimation->GetCurrentFrameIndex();
		}
		return InvalidIndex;
	}

	void SpritePlayer::SetCurrentFrame(int frameIndex)
	{
		if (mAnimation)
		{
			mAnimation->SetCurrentFrame(frameIndex);
			updateAnimation();
		}
	}

	GPtr<SpriteImage> SpritePlayer::GetImage() const
	{
		if (0 <= mCurrentImageIndex)
		{
			return mSpriteInfo->GetPackageResInfo()->GetPackage()->GetImage(mCurrentImageIndex);
		}
		return NULL;
	}

	float SpritePlayer::GetTotalUnits() const
	{
		if (mAnimation)
		{
			return mAnimation->GetTotalUnits();
		}
		return 0.0f;
	}

	float SpritePlayer::GetCurrentUnits() const
	{
		if (mAnimation)
		{
			return mAnimation->GetCurrentUnits();
		}
		return 0.0f;
	}

	void SpritePlayer::SetCurrentUnits(float units)
	{
		if (mAnimation)
		{
			mAnimation->SetCurrentUnits(units);
			updateAnimation();
		}
	}

	void SpritePlayer::Stop()
	{
		if (mAnimation)
		{
			mAnimation->Stop();
		}
		if (mDefaultBlock)
		{
			mCurrentImageIndex = mDefaultBlock->GetImageIndex();
#ifdef __SPRITE_CHECK__		
			checkDefualtBlock();
#endif // __SPRITE_CHECK__
			mSpriteInfo->UpdateVertex(mDefaultBlock, NULL);
		}
		else
		{
			mCurrentImageIndex = InvalidIndex;
		}
		mDirty = true;


	}

	bool SpritePlayer::IsAnimationPlaying() const
	{
		if (mAnimation)
		{
			return mAnimation->IsPlaying();
		}
		else
		{
			return false;
		}
	}

}