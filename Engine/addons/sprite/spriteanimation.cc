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
#include "spriteanimationclip.h"
#include "spriteanimation.h"


namespace Sprite
{
	__ImplementClass(SpriteAnimation,'SPAN',Core::RefCounted);
	const int SpriteAnimation::sUnknownCurrentFrame = InvalidIndex - 1;

	SpriteAnimation::SpriteAnimation()
		:mLoops(0)
		,mLoopCounter(0)
		,mUnitCounter(0.0f)
		,mSpeed(1.0f)
		,mCurrentFrame(sUnknownCurrentFrame)
		,mState(S_Stop)
	{

	}
	SpriteAnimation::~SpriteAnimation()
	{

	}

	void SpriteAnimation::Stop()
	{
		mLoopCounter = 0;
		mUnitCounter = 0;
		mCurrentFrame = sUnknownCurrentFrame;
		mState = S_Stop;
	}

	void SpriteAnimation::Replay()
	{
		mLoopCounter = 0;
		mUnitCounter = 0;
		mCurrentFrame = sUnknownCurrentFrame;
		mState = S_Playing;
	}

	void SpriteAnimation::Play()
	{
		if (S_Pause == mState)
		{
			mState = S_Playing;
		}
		else
		{
			Replay();
		}
	}

	void SpriteAnimation::Pause()
	{
		if (S_Playing == mState)
		{
			mState = S_Pause;
		}
	}

	void SpriteAnimation::SetSpeed(float speed)
	{
		mSpeed = (speed < 0.001f) ? 0.001f : speed;
	}

	void SpriteAnimation::SetClip(const GPtr<SpriteAnimationClip>& clip, int loops)
	{
		n_assert(clip.isvalid());
		mClip = clip;
		SetLoops(loops);
	}

	void SpriteAnimation::SetLoops(int loops)
	{
		mLoops = loops;
	}

	int SpriteAnimation::GetCurrentBlockIndex() const
	{
		if (0 > mCurrentFrame)
		{
			return InvalidIndex;
		}
		return mClip->GetFrame(mCurrentFrame).GetBlockIndex();
	}

	int SpriteAnimation::GetFrameCount() const
	{
		if (mClip)
		{
			return mClip->GetFrameCount();
		}
		return InvalidIndex;
	}

	void SpriteAnimation::CopyFrom(const SpriteAnimation& rh)
	{
		SetSpeed(rh.mSpeed);
		SetClip(rh.mClip, rh.mLoops);
	}

	Util::String SpriteAnimation::GetClipName() const
	{
		if (mClip)
		{
			return mClip->GetName();
		}
		return Util::String();
	}

	float SpriteAnimation::GetTotalUnits() const
	{
		return mClip->GetTotalUnits();
	}

	float SpriteAnimation::GetCurrentUnits() const
	{
		float units = mUnitCounter;
		while (units >= mClip->GetTotalUnits())
		{
			units -= mClip->GetTotalUnits();
		}
		return units;
	}

	void SpriteAnimation::SetCurrentFrame(int frameIndex)
	{
		mUnitCounter = mClip->GetBeginUnits(frameIndex);
		mCurrentFrame = mClip->GetFrameIndex(mUnitCounter, 0);
	}


	void SpriteAnimation::SetCurrentUnits(float units)
	{
		mUnitCounter = units;
		mCurrentFrame = mClip->GetFrameIndex(mUnitCounter, 0);
	}


	bool SpriteAnimation::Check(float time)
	{
#ifdef __SPRITE_CHECK__
		if (mClip->IsDestroyed())
		{
			int pre_frame = mCurrentFrame;
			mCurrentFrame = InvalidIndex;
			return (mCurrentFrame != pre_frame);
		}
#endif
		if (S_Playing == mState)
		{
			mUnitCounter += (time * mSpeed / mClip->GetTimePerUnit());
			while (mUnitCounter >= mClip->GetTotalUnits())
			{
				if (mLoops)
				{
					++mLoopCounter;
				}
				mUnitCounter -= mClip->GetTotalUnits();
			}
			int pre_frame = mCurrentFrame;
			if (mLoops && (mLoopCounter >= mLoops))
			{
				Stop();
			}
			else
			{
				mCurrentFrame = mClip->GetFrameIndex(mUnitCounter, mCurrentFrame);
			}
			return (mCurrentFrame != pre_frame);
		}
#ifdef __SPRITE_CHECK__
		else if (S_Pause == mState)
		{
			if (mCurrentFrame >= mClip->GetFrameCount())
			{
				mCurrentFrame = mClip->GetFrameCount() - 1;
			}
		}
#endif
		return false;
	}
}