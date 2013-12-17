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

#include "resource/resource_stdneb.h"
#include "resource/skeletonres.h"

namespace Resources
{
	__ImplementClass(Resources::SkeletonRes,'SKLR', Resources::Resource);
	__ImplementClass(Resources::SkelTreeData, 'SLTR', Core::RefCounted);
	//------------------------------------------------------------------------
	SkeletonRes::SkeletonRes()
	{

	}
	//------------------------------------------------------------------------
	SkeletonRes::~SkeletonRes()
	{

	}
	//------------------------------------------------------------------------
	bool
		SkeletonRes::AddSkelBone( const SkelBone& bone)
	{
		// bone count limit
		if ( (mSkelBones.Size() < MaxSkeletonBoneCount) && bone.boneName.IsValid() )
		{
			// root bone
			/*if ( bone.parentIndex == MaxSkeletonBoneCount )
			{
			mSkelBones.Append(bone);	
			return true;
			}
			else if ( bone.parentIndex < mSkelBones.Size() )
			{
			// Depth-First
			mSkelBones.Append(bone);	
			return true;
			}*/

			mSkelBones.Append(bone);
			mSkelNames.Append(bone.boneName.AsString());
			return true;
		}

		return false;
	}
	//------------------------------------------------------------------------
	SizeT 
		SkeletonRes::CalculateRuntimeSize(void) const
	{
		SizeT size = sizeof( SkelBone ) * mSkelBones.Size();
		size += Super::CalculateRuntimeSize();
		return size;
	}
	//------------------------------------------------------------------------
	bool 
		SkeletonRes::SwapLoadImpl( const GPtr<Resource>& tempRes )
	{
		n_assert( tempRes.isvalid() );
		if ( tempRes->GetRtti() == this->GetRtti() )
		{
			GPtr<SkeletonRes> tempSkel = tempRes.downcast<SkeletonRes>();
			n_assert( tempSkel.isvalid() );

			mSkelBones.Swap( tempSkel->mSkelBones );
			mSkelNames.Swap( tempSkel->mSkelNames );
			mSkelTree.Swap( tempSkel->mSkelTree );
			skelId = tempSkel->skelId;

			mSkelTreeArray.Swap( tempSkel->mSkelTreeArray );

			for (IndexT i = 0; i < mSkelNames.Size(); ++i)
			{
				mSkelKeyPair.Add(i, mSkelNames[i]);
			}

			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------
	void 
		SkeletonRes::UnLoadImpl(void)
	{
		mSkelBones.Clear();
		mSkelTree.Clear();
		mSkelTreeArray.Clear();
	}
	//------------------------------------------------------------------------
	bool
		SkeletonRes::AddSkelTreeData(GPtr<SkelTreeData>& pTreeData, const Util::String& parentName)
	{
		if ( (mSkelTree.Size() < MaxSkeletonBoneCount) && pTreeData->name.IsValid() )
		{
			mSkelTree.Add(pTreeData->name, pTreeData);

			IndexT found = mSkelTree.FindIndex(parentName);
			if ( found == InvalidIndex )
			{
				pTreeData->parent = NULL;
			}
			else
			{
				const GPtr<SkelTreeData>& pParentData = mSkelTree.ValueAtIndex(found);
				pTreeData->parent = pParentData;
			}


			mSkelTreeArray.Append(pTreeData);

			pTreeData->parent = NULL;

			for(int i = 0; i<mSkelTreeArray.Size(); ++i)
			{
				if(parentName == mSkelTreeArray[i]->name)
				{
					pTreeData->parent = mSkelTreeArray[i];
					break;
				}
			}

			return true;
		}

		return false;
	}

	void SkeletonRes::SetSkelID( const Util::String skelId )
	{
		this->skelId = skelId;
	}

	void SkeletonRes::AddSkeletonPair()
	{
		if (mSkelKeyPair.IsEmpty())
		{
			for (IndexT i = 0; i < mSkelNames.Size(); ++i)
			{
				mSkelKeyPair.Add(i, mSkelNames[i]);
			}
		}

	}

}
