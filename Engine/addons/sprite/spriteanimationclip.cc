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


namespace Sprite 
{

#define DEFINE_SERIAL_ITEM_NAME(name) static const char* g##name##Tag = #name
	const uint SpriteAnimationClip::sVersion = 1;
	const float SpriteAnimationClip::sMinTotalUnits = 1.0f;
	const float SpriteAnimationClip::sDestroyFlagTimePerUnits = 100000000000.0f;
	DEFINE_SERIAL_ITEM_NAME(Name);
	DEFINE_SERIAL_ITEM_NAME(FrameCount);
	DEFINE_SERIAL_ITEM_NAME(BlockIndex);
	DEFINE_SERIAL_ITEM_NAME(Units);
	DEFINE_SERIAL_ITEM_NAME(TimePerUnits);

	__ImplementClass(SpriteAnimationClip,'SPAC', SpriteObject);

	SpriteAnimationClip::SpriteAnimationClip()
		:mTotalUnits(sMinTotalUnits)
		,mTimePerUnits(0.0f)
	{

	}
	SpriteAnimationClip::~SpriteAnimationClip()
	{

	}

	float SpriteAnimationClip::GetBeginUnits(int frameIndex) const
	{
		if (mFrames.Size() > 0)
		{
			int index = frameIndex % mFrames.Size();
			if (index < 0)
			{
				index += mFrames.Size();
			}
			return mFrames[index].begin_unit;
		}
		return 0.0f;
	}

	int SpriteAnimationClip::GetFrameIndex(float units, int suggestBegin) const
	{
		n_assert(units >=0);
		if (0 == mFrames.Size())
		{
			return InvalidIndex;
		}
		int i = suggestBegin;
		int i_next = i + 1;
		while(i_next < mFrames.Size())
		{
			if (mFrames[i].begin_unit <= units && units < mFrames[i_next].begin_unit)
			{
				return i;
			}
			++i;
			++i_next;
		}
		if (mFrames.Back().begin_unit <= units )//比较最后一帧。
		{
			return mFrames.Size() - 1;
		}
		if (suggestBegin >= mFrames.Size())//防止数据溢出
		{
			suggestBegin = mFrames.Size() - 1;
		}
		i = 0;
		while(true)//从头开始检索
		{
			if (mFrames[i + 1].begin_unit > units)
			{
				return i;
			}
			++i;
		}
		return InvalidIndex;
	}

	void SpriteAnimationClip::InsertFrame(int pos, const SpriteFrame& frame)
	{
		_frame fr;
		fr.frame = frame;
		mFrames.Insert(pos, fr);
		updateCache();
	}

	void SpriteAnimationClip::ChangeFrame(int pos, const SpriteFrame& frame)
	{
		if (0 <= pos && pos < mFrames.Size())
		{
			mFrames[pos].frame = frame;
			updateCache();
		}
	}

	void SpriteAnimationClip::RemoveFrame(int pos)
	{
		mFrames.EraseIndex(pos);
		updateCache();
	}

	void SpriteAnimationClip::ClearAllFrames()
	{
		mFrames.Clear();
		updateCache();
	}

	void SpriteAnimationClip::updateCache()
	{
		mTotalUnits = 0;
		Frames::Iterator it = mFrames.Begin();
		Frames::Iterator end = mFrames.End();

		while(it != end)
		{
			it->begin_unit = mTotalUnits;
			mTotalUnits += it->frame.GetUnits();
			++it;
		}
		if (mTotalUnits < sMinTotalUnits)
		{
			mTotalUnits = sMinTotalUnits;
		}
	}

	void SpriteAnimationClip::_RebuildFrames(int block_del_index)
	{
		for (int i = 0; i < mFrames.Size(); ++i)
		{
			if (mFrames[i].frame.GetBlockIndex() == block_del_index)
			{
				mFrames[i].frame.SetBlockIndex(InvalidIndex);
			}
			else if(mFrames[i].frame.GetBlockIndex() > block_del_index)
			{
				mFrames[i].frame.SetBlockIndex(mFrames[i].frame.GetBlockIndex()-1);
			}
		}
	}

	void SpriteAnimationClip::Save(GPtr<Serialization::SerializeWriter>& pWriter) const
	{
		pWriter->SerializeVersion(sVersion);
		__SaveSuper(pWriter);

		pWriter->SerializeString(gNameTag, mName);
		pWriter->SerializeInt(gFrameCountTag, mFrames.Size());
		pWriter->SerializeFloat(gTimePerUnitsTag, mTimePerUnits);
		for (int i = 0; i < mFrames.Size(); ++i)
		{
			pWriter->SerializeInt(gBlockIndexTag, mFrames[i].frame.GetBlockIndex());
			pWriter->SerializeFloat(gUnitsTag, mFrames[i].frame.GetUnits());
		}
	}

	void SpriteAnimationClip::Load(const GPtr<Serialization::SerializeReader>& pReader)
	{
		Serialization::SVersion version;
		pReader->SerializeVersion(version);
		__LoadSuper(pReader);

		pReader->SerializeString(gNameTag, mName);
		int count = 0;
		pReader->SerializeInt(gFrameCountTag, count);
		pReader->SerializeFloat(gTimePerUnitsTag, mTimePerUnits);
		for (int i = 0; i < count; ++i)
		{
			mFrames.Append(_frame());
			pReader->SerializeInt(gBlockIndexTag, mFrames.Back().frame.mBlockIndex);
			pReader->SerializeFloat(gUnitsTag, mFrames.Back().frame.mUnits);
		}
		updateCache();
	}

	void SpriteAnimationClip::CopyFrom(const GPtr<SpriteObject>& obj)
	{
		Super::CopyFrom(obj);
		GPtr<SpriteAnimationClip> sub = obj.downcast<SpriteAnimationClip>();

		mName = sub->mName;
		mFrames = sub->mFrames;
		mTimePerUnits = sub->mTimePerUnits;
		updateCache();
	}
}