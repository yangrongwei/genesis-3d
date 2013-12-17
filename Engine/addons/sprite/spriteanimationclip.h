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
#ifndef __SPRITE_ANIMATION_CLIP_H__
#define __SPRITE_ANIMATION_CLIP_H__
#include "sprite/spriteobject.h"
#include "foundation/util/array.h"
#include "foundation/util/string.h"
#include "addons/sprite/spriteframe.h"

namespace Serialization
{
	class SerializeWriter;
	class SerializeReader;
}

namespace Sprite
{
	class SpriteAnimationClip : public SpriteObject
	{
		__DeclareSubClass(SpriteAnimationClip, SpriteObject)
	public:
		SpriteAnimationClip();
		virtual ~SpriteAnimationClip();

		virtual void Save(GPtr<Serialization::SerializeWriter>& pWriter) const;
		virtual void Load(const GPtr<Serialization::SerializeReader>& pReader);
		virtual void CopyFrom(const GPtr<SpriteObject>& obj);

		float GetBeginUnits(int frameIndex) const;
		int GetFrameIndex(float units, int suggestBegin) const;
		const SpriteFrame& GetFrame(int index) const;
		int GetFrameCount() const;

		void InsertFrame(int pos, const SpriteFrame& frame);
		void ChangeFrame(int pos, const SpriteFrame& frame);
		void RemoveFrame(int pos);
		void ClearAllFrames();

		const Util::String& GetName() const;
		void SetName(const Util::String& name);

		float GetTimePerUnit() const;
		void SetTimePerUnit(float tpu);

		float GetTotalUnits() const;
		float GetTotalTimes() const;

		void Destroy();
		bool IsDestroyed() const;

		void _RebuildFrames(int block_del_index);
	private:
		struct _frame
		{
			SpriteFrame frame;
			mutable float begin_unit;
			inline _frame()
				:begin_unit(0)
			{

			}
		};
		typedef Util::Array<_frame> Frames;
		void updateCache();

		Util::String mName;
		Frames mFrames;
		float mTotalUnits;
		float mTimePerUnits;

		static const uint sVersion;
		static const float sMinTotalUnits;
		static const float sDestroyFlagTimePerUnits;
	};

	inline const Util::String& SpriteAnimationClip::GetName() const
	{
		return mName;
	}

	inline void SpriteAnimationClip::SetName(const Util::String& name)
	{
		mName = name;
	}
	inline const SpriteFrame& SpriteAnimationClip::GetFrame(int index) const
	{
		n_assert(0 <= index);
		n_assert(index < mFrames.Size());
		return mFrames[index].frame;
	}

	inline int SpriteAnimationClip::GetFrameCount() const
	{
		return mFrames.Size();
	}

	inline float SpriteAnimationClip::GetTimePerUnit() const
	{
		return mTimePerUnits;
	}

	inline void SpriteAnimationClip::SetTimePerUnit(float tpu)
	{
		mTimePerUnits = tpu;
	}

	inline float SpriteAnimationClip::GetTotalUnits() const
	{
		return mTotalUnits;
	}

	inline float SpriteAnimationClip::GetTotalTimes() const
	{
		return mTotalUnits * mTimePerUnits;
	}

	inline void SpriteAnimationClip::Destroy()
	{
		mTimePerUnits = sDestroyFlagTimePerUnits;
	}

	inline bool SpriteAnimationClip::IsDestroyed() const
	{
		return mTimePerUnits == sDestroyFlagTimePerUnits;
	}
}

#endif //__SPRITE_ANIMATION_CLIP_H__