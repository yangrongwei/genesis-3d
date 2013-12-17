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
#ifndef __SPRITE_ANIMATION_H__
#define __SPRITE_ANIMATION_H__
#include "foundation/core/refcounted.h"
#include "foundation/util/array.h"
#include "addons/sprite/spriteframe.h"

namespace Sprite
{
	class SpriteAnimationClip;
	class SpriteBlock;
	class SpriteAnimation : public Core::RefCounted
	{
		__DeclareClass(SpriteAnimation)
	public:
		typedef GPtr<SpriteAnimationClip> SpriteAnimationClipPtr;
		enum State
		{
			S_Unknown,
			S_Pause,
			S_Playing,
			S_Stop,
		};
		SpriteAnimation();
		virtual ~SpriteAnimation();

		void SetSpeed(float speed);

		void SetClip(const GPtr<SpriteAnimationClip>& clip, int loops);

		void SetLoops(int loops);

		//if frame change return true, else return false
		bool Check(float time);

		void Replay();

		void Play();

		void Pause();

		void Stop();

		bool IsPlaying() const;

		State GetState() const;

		int GetCurrentBlockIndex() const;

		void CopyFrom(const SpriteAnimation& rh);

		Util::String GetClipName() const;

		int GetLoops() const;

		float GetSpeed() const;

		int GetFrameCount() const;

		int GetCurrentFrameIndex() const;

		void SetCurrentFrame(int frameIndex);

		float GetTotalUnits() const;

		float GetCurrentUnits() const;

		void SetCurrentUnits(float units);

		const SpriteAnimationClipPtr& GetClip() const;

#ifdef __SPRITE_CHECK__
		void _DirtyFrameCache();
#endif

	private:
		void updateFrame();
		SpriteAnimationClipPtr mClip;
		int mLoops;
		float mSpeed;
		int mCurrentFrame;

		State mState;
		int mLoopCounter;
		float mUnitCounter;
		static const int sUnknownCurrentFrame;
	};

	inline int SpriteAnimation::GetLoops() const
	{
		return mLoops;
	}

	inline float SpriteAnimation::GetSpeed() const
	{
		return mSpeed;
	}

	inline int SpriteAnimation::GetCurrentFrameIndex() const
	{
		return mCurrentFrame;
	}

	inline bool SpriteAnimation::IsPlaying() const
	{
		return (mState == S_Playing ? true : false);
	}

	inline SpriteAnimation::State SpriteAnimation::GetState() const
	{
		return mState;
	}

	inline const SpriteAnimation::SpriteAnimationClipPtr&
		SpriteAnimation::GetClip() const
	{
		return mClip;
	}

#ifdef __SPRITE_CHECK__
	inline void SpriteAnimation::_DirtyFrameCache()
	{
		mCurrentFrame = sUnknownCurrentFrame;
	}
#endif
}

#endif //__SPRITE_ANIMATION_H__