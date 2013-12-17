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
#ifndef _RENDERQUEUE_H_
#define _RENDERQUEUE_H_
#include "foundation/core/types.h"
#include "foundation/util/string.h"

namespace Graphic
{

	class RenderQueue
	{
	public:
		enum QueueType
		{
			eRQTNone = 0,
			eRQTBackGround = 1000,				
			eRQTOpaque = 2000,
			eRQTAlphaTest = 3000,
			eRQTAlphaBlend = 4000,
			eRQTGlass = 5000,
			eRQParticleDecal = 6000,
			eRQParticlePost = 7000,
			eRQTCustomDraw = 8000,
			eRQTDebugPrimitive = 9000,
			eRQTScreen = 10000,	//2d screen
			eRQ_Max = BIT_FLAG_16BIT_MAX,
		};
		~RenderQueue();
		RenderQueue();
		RenderQueue(QueueType type);
		RenderQueue(QueueType type, int16 sort);
		void SetQueue(QueueType type);
		void SetQueue(QueueType type, int16 sort);
		void ChangeSort(int16 sort);

		uint GetQueueIndex() const; 
		QueueType GetQueueType() const;
		int16 GetSort() const;

		/// convert from string
		static RenderQueue FromString(Util::String str);
		/// convert to string
		static Util::String ToString(RenderQueue rqt);

		RenderQueue& operator = (const RenderQueue& rh);

		enum QueueMask
		{
			SortDefault = 0,
			SortR = 30000,
			TypeBias = 16,
			LowMark = 0xffff0000,
			HightMark = 0x0000ffff
		};
	private:
		uint queue_index;
	};

	inline RenderQueue& RenderQueue::operator = (const RenderQueue& rh)
	{
		this->queue_index = rh.queue_index;
		return (*this);
	}

	inline void RenderQueue::SetQueue(QueueType type)
	{
		queue_index = ((uint)type) << TypeBias;
	}

	inline void RenderQueue::SetQueue(QueueType type, int16 sort)
	{
		n_assert(-SortR <= sort && sort <= SortR);
		queue_index = (((uint)type) << TypeBias) | (sort + SortR);
	}

	inline void RenderQueue::ChangeSort(int16 sort)
	{
		n_assert(-SortR <= sort && sort <= SortR);
		queue_index = (queue_index & LowMark) | (sort + SortR);
	}

	inline uint RenderQueue::GetQueueIndex() const
	{
		return queue_index;
	}

	inline RenderQueue::QueueType RenderQueue::GetQueueType() const
	{
		return (RenderQueue::QueueType)(queue_index >> TypeBias);
	}

	inline int16 RenderQueue::GetSort() const
	{
		return (int16)((queue_index & HightMark) - TypeBias);
	}
}


#endif //_RENDERQUEUE_H_