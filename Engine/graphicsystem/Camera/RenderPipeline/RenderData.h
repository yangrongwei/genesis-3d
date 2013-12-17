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
#ifndef _RNEDERDATA_H_
#define _RNEDERDATA_H_
#include "graphicsystem/base/DataCollection.h"
namespace Graphic
{
	class RenderObject;
	class Renderable;
	struct VisibleNode;

	struct RenderData
	{
	public:		
		enum Type
		{
			Background,
			Opaque,
			Alpha,
			Glass,
			ParticleDecal,
			ParticlePost,
			Custom,
			Screen,	//2d screen
			TypeCount
		};
		VisibleNode* onwer;
		Renderable* renderable;
	};

	class RenderDataCollection
	{	
	public:
		enum UseFor
		{
			Unknown,
			Shadow,
			Normal,
		};
		virtual void Push(Renderable* renderable) = 0;
		virtual UseFor GetUseFor() const = 0;
	};
	typedef DataCollection<RenderData> RenderDataArray;
	typedef DataCollection<int> RenderDataIndexArray;
	class RenderDataManager : public RenderDataCollection
	{
	public:		
		typedef RenderDataCollection Super;
		virtual void Push(Renderable* renderable);
		virtual Super::UseFor GetUseFor() const;
		RenderDataManager();
		void SetCurrentNode(VisibleNode* node);
		void Sort();
		void SetUseFor(Super::UseFor uf);
		void Reset(bool isMain);
		RenderDataArray& GetRenderDatas();
		RenderDataIndexArray& GetRenderDataIndices(RenderData::Type part_index);
	private:
		template<bool Opaque>
		void _sort(RenderDataIndexArray& cache);
		void _sortScreen(RenderDataIndexArray& cache);
		void _sortDepth(RenderDataIndexArray& cache);
		VisibleNode* mCurrNode;
		RenderDataArray mRenderDatas;
		RenderDataIndexArray mSorteCaches[RenderData::TypeCount];
		bool mIsMainCamera;
		RenderDataCollection::UseFor mUseFor;
		static const SizeT sDefualtSize;
	};

	inline void RenderDataManager::SetCurrentNode(VisibleNode* node)
	{
		mCurrNode = node;
	}

	inline RenderDataIndexArray& RenderDataManager::GetRenderDataIndices(RenderData::Type part_index)
	{
		n_assert(0 <= part_index && part_index < RenderData::TypeCount);
		return mSorteCaches[part_index];
	}

	inline RenderDataArray& RenderDataManager::GetRenderDatas()
	{
		return mRenderDatas;
	}

	inline void RenderDataManager::SetUseFor(Super::UseFor uf)
	{
		mUseFor = uf;
	}
}

#endif //_RNEDERDATA_H_