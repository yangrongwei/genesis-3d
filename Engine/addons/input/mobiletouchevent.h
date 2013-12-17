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
#ifndef __mobiletouchevent_H__
#define __mobiletouchevent_H__

#include "input/mobileinputevent.h"
#include "math/float2.h"
#include "util/array.h"

namespace Input
{
	class MobileTouchEvent : public Input::MoibleInputEvent
{
public:

	enum MotionType
	{
		MOTION_EVENT_ACTION_DOWN = 0,
		MOTION_EVENT_ACTION_UP,
		MOTION_EVENT_ACTION_MOVE,
		MOTION_EVENT_ACTION_CANCEL,

	};

	MobileTouchEvent();

	~MobileTouchEvent();

public:

	void SetMotionType(const MotionType type);

	const MotionType GetMotionType() const;

	void SetPointerPos(const IndexT pointerID, const Math::float2& pos);

	const Math::float2 GetPointerPos(const IndexT pointerID) const;

	const SizeT GetPointersCount() const;

	const IndexT GetPointerId(const IndexT index) const;

protected:

	void SetPointerId(const IndexT id);

	MotionType                             m_MotionType;

	Util::Dictionary<IndexT, Math::float2> m_PointersPos;
	Util::Array<IndexT>                    m_PointerIds;
};

inline MobileTouchEvent::MobileTouchEvent()
{
		m_PointersPos.Reserve(10);
}

inline MobileTouchEvent::~MobileTouchEvent()
{
	m_PointersPos.Clear();
}

inline void MobileTouchEvent::SetMotionType(const MotionType type)
{
	m_MotionType = type;
}

inline const MobileTouchEvent::MotionType MobileTouchEvent::GetMotionType() const
{
	return m_MotionType;
}

inline void MobileTouchEvent::SetPointerPos(const IndexT pointerID, const Math::float2& pos)
{
	m_PointersPos.Add(pointerID, pos);
	SetPointerId(pointerID);
}

inline const Math::float2 MobileTouchEvent::GetPointerPos(const IndexT pointerID) const
{
	return m_PointersPos[pointerID];
}

inline const SizeT MobileTouchEvent::GetPointersCount() const
{
	return m_PointersPos.Size();
}

inline void MobileTouchEvent::SetPointerId(const IndexT id)
{
	m_PointerIds.Append(id);
}

inline const IndexT MobileTouchEvent::GetPointerId(const IndexT index) const
{
	n_assert( index <= m_PointerIds.Size() - 1  );
	
	return m_PointerIds[index];
}

}

#endif