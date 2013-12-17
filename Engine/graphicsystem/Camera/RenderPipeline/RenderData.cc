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
#include "RenderData.h"
#include "graphicsystem/Material/materialinstance.h"
#include "graphicsystem/Renderable/Renderable.h"
#include "graphicsystem/Camera/RenderPipeline/VisibleNode.h"
#include "foundation/util/stl.h"

namespace Graphic
{
	// ------------------------------------ ≤ƒ÷ ≈≈–Ú ---------------------------------------------------
	template<bool opaque>
	class RenderDataSorter
	{
	public:
		RenderDataSorter(const RenderData* _data)
		{
			data = _data;
		}
		bool operator() (const int& l, const int& r) const;
	private:
		const RenderData* data;
	};
	template<bool opaque>
	bool RenderDataSorter<opaque>::operator() (const int& lIndrex, const int& rIndex) const
	{
		const RenderData& lhs = data[lIndrex];
		const RenderData& rhs = data[rIndex];

		if (lhs.renderable->GetMaterial()->GetRenderQueue().GetQueueIndex() != rhs.renderable->GetMaterial()->GetRenderQueue().GetQueueIndex())
		{
			return lhs.renderable->GetMaterial()->GetRenderQueue().GetQueueIndex() < rhs.renderable->GetMaterial()->GetRenderQueue().GetQueueIndex();
		}

		if (!opaque)
		{
			if (lhs.onwer->distance != rhs.onwer->distance)
			{
				return lhs.onwer->distance > rhs.onwer->distance;
			}
		}

		if (lhs.renderable->GetMaterial()->GetSort() != rhs.renderable->GetMaterial()->GetSort())
		{
			return lhs.renderable->GetMaterial()->GetSort() < rhs.renderable->GetMaterial()->GetSort();
		}
		if (lhs.renderable->GetMaterial()->GetShaderInstanceID() != rhs.renderable->GetMaterial()->GetShaderInstanceID())
		{
			return lhs.renderable->GetMaterial()->GetShaderInstanceID() < rhs.renderable->GetMaterial()->GetShaderInstanceID();
		}
		
		if (opaque)
		{
			return lhs.onwer->distance < rhs.onwer->distance;
		}
		return lIndrex < rIndex;
	}

	class ScreenDataSorter
	{
	public:
		ScreenDataSorter(const RenderData* _data)
		{
			data = _data;
		}
		bool operator()(const int& lIndrex, const int& rIndex) const;
	private:
		const RenderData* data;
	};
	bool ScreenDataSorter::operator() (const int& lIndrex, const int& rIndex) const
	{
		const RenderData& lhs = data[lIndrex];
		const RenderData& rhs = data[rIndex];
		return lhs.renderable->GetMaterial()->GetRenderQueue().GetQueueIndex() < rhs.renderable->GetMaterial()->GetRenderQueue().GetQueueIndex();
	}

	class DepthSorter
	{
	public:
		DepthSorter(const RenderData* _data)
		{
			data = _data;
		}
		bool operator()(const int& lIndrex, const int& rIndex) const;
	private:
		const RenderData* data;
	};
	bool DepthSorter::operator() (const int& lIndrex, const int& rIndex) const
	{
		const RenderData& lhs = data[lIndrex];
		const RenderData& rhs = data[rIndex];
		
		if (lhs.renderable->GetMaterial()->GetSort() != rhs.renderable->GetMaterial()->GetSort())
		{
			return lhs.renderable->GetMaterial()->GetSort() < rhs.renderable->GetMaterial()->GetSort();
		}
		if (lhs.renderable->GetMaterial()->GetShaderInstanceID() != rhs.renderable->GetMaterial()->GetShaderInstanceID())
		{
			return lhs.renderable->GetMaterial()->GetShaderInstanceID() < rhs.renderable->GetMaterial()->GetShaderInstanceID();
		}

		return lhs.onwer->distance < rhs.onwer->distance;
	}

	const SizeT RenderDataManager::sDefualtSize = 50;
	RenderDataManager::RenderDataManager()
		:mUseFor(Super::Unknown)
		,mCurrNode(NULL)
		,mIsMainCamera(false)
	{

	}

	RenderDataCollection::UseFor RenderDataManager::GetUseFor() const
	{
		return mUseFor;
	}

	void RenderDataManager::Push(Renderable* renderable)
	{
		RenderQueue::QueueType renderQueueType = renderable->GetMaterial()->GetRenderQueue().GetQueueType();
		int partIndex = 0;
		switch ( renderQueueType )
		{
		case RenderQueue::eRQTBackGround:
			{
				partIndex = RenderData::Background;
			}
			break;
		case RenderQueue::eRQTOpaque:
		case RenderQueue::eRQTAlphaTest:
			{
				partIndex = RenderData::Opaque;
			}
			break;
		case RenderQueue::eRQTAlphaBlend:
			{
				partIndex = RenderData::Alpha;
			}
			break;
		case RenderQueue::eRQTGlass:
			{
				if (mIsMainCamera)
				{
					partIndex = RenderData::Glass;
				}
				else
				{
					return;
				}
			}
			break;
		case RenderQueue::eRQParticleDecal:
			{
				if (mIsMainCamera)
				{
					partIndex = RenderData::ParticleDecal;
				}
				else
				{
					return;
				}
			}
			break;
		case RenderQueue::eRQParticlePost:
			{
				if (mIsMainCamera)
				{
					partIndex = RenderData::ParticlePost;
				}
				else
				{
					return;
				}
			}
			break;
		case RenderQueue::eRQTCustomDraw:
			{
				if (mIsMainCamera)
				{
					partIndex = RenderData::Custom;
				}
				else
				{
					return;
				}
			}
		case RenderQueue::eRQTDebugPrimitive:
			{
				partIndex = RenderData::Custom;
			}
			break;
		case RenderQueue::eRQTScreen:
			{		
				if (mIsMainCamera)
				{
					partIndex = RenderData::Screen;
				}
				else
				{
					return;
				}
			}
			break;
		default:
			{
				RenderQueue rq = renderable->GetMaterial()->GetRenderQueue();
				n_warning("unknown render queue(type:%d, sort: %d) of material(%s).", (int)rq.GetQueueType(), (int)rq.GetSort(), renderable->GetMaterial()->GetMaterialID().AsString().AsCharPtr());
				return;
			}

		}
		mSorteCaches[partIndex].PushBack(mRenderDatas.Count());
		RenderData& data = mRenderDatas.PushBack();
		data.onwer = mCurrNode;
		data.renderable = renderable;
	}

	void RenderDataManager::Sort()
	{
		switch(mUseFor)
		{
		case Super::Normal:
			{
				_sort<true>(mSorteCaches[RenderData::Opaque]);
				_sort<false>(mSorteCaches[RenderData::Alpha]);
				if (mSorteCaches->Count())
				{
					_sortScreen(mSorteCaches[RenderData::Screen]);
				}
				break;
			}
		case Super::Shadow:
			{
				_sortDepth(mSorteCaches[RenderData::Opaque]);
				break;
			}
		default:
			break;
		}


	}

	void RenderDataManager::Reset(bool isMain) 
	{
		mRenderDatas.Clear();
		for (int i = 0; i < RenderData::TypeCount; ++i)
		{
			mSorteCaches[i].Clear();
		}
		mIsMainCamera = isMain;
	}


	template<bool Opaque>
	void RenderDataManager::_sort(RenderDataIndexArray& cache)
	{
		RenderDataSorter<Opaque> sorter(mRenderDatas.Begin());
		Util::STL::sort(cache.Begin(), cache.End(), sorter);
	}
	void RenderDataManager::_sortScreen(RenderDataIndexArray& cache)
	{
		ScreenDataSorter sorter(mRenderDatas.Begin());
		Util::STL::sort(cache.Begin(), cache.End(), sorter);
	}
	void RenderDataManager::_sortDepth(RenderDataIndexArray& cache)
	{
		DepthSorter sorter(mRenderDatas.Begin());
		Util::STL::sort(cache.Begin(), cache.End(), sorter);
	}
}