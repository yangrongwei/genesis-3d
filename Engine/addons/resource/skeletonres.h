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
#ifndef __skeletonres_H__
#define __skeletonres_H__

#include "resource/resource.h"
#include "util/stringatom.h"

namespace Resources
{
	typedef Util::StringAtom BoneID;
	struct SkelBone
	{
		ushort parentIndex;	//	root skeleton
		BoneID boneName;	//	must be valid
		Math::matrix44 inverseBindingMatrix;
	};

	class SkelTreeData : public Core::RefCounted
	{
		__DeclareClass(SkelTreeData);
	public:
		GPtr<SkelTreeData> parent;

		Util::String      name;

		Math::float4      pos;
		Math::quaternion  rot;
		Math::float4      scale;
	};

	typedef Util::Array<SkelBone> SkelBoneContainer;

	const SizeT MaxSkeletonBoneCount = 0xFFFF;

	class SkeletonRes: public Resources::Resource
	{
		__DeclareSubClass(SkeletonRes, Resource);
	public:
		SkeletonRes();
		virtual ~SkeletonRes();

		const SkelBoneContainer& GetSkelBones(void) const;

		const SizeT GetBonesCount() const;

		/**
		* AddSkelBone  add one bone
		* @param: const SkelBone & bone  
		* @return: bool  
		* @see: 
		* @remark:  if bigger than MaxSkeletonBoneCount, return false; bone.parentIndex and bone.boneName must be valid
		*/
		bool AddSkelBone( const SkelBone& bone);

		// @Resource::CalculateRuntimeSize
		virtual SizeT CalculateRuntimeSize(void) const;

		const Util::Array<Util::String>& GetSkelNames() const;

		const Util::Dictionary<IndexT, Util::String>& GetSkelKeyPairs() const;

		inline void ReserveSkelTree(SizeT size);

		bool AddSkelTreeData(GPtr<SkelTreeData>& pTreeData, const Util::String& parentName);

		const SizeT GetSkelTreeDataCount() const;

		Util::Dictionary< Util::String, GPtr<SkelTreeData> >& GetSkelTree();

		Util::Array< GPtr<SkelTreeData> >& GetSkelTreeArray();

		bool  IsSkelTreeEmpty();

		void SetSkelID( const Util::String skelId );

		const Util::String GetSkelID();

		void AddSkeletonPair();

	protected:
		// @Resource::SwapLoadImpl
		virtual bool SwapLoadImpl( const GPtr<Resource>& tempRes);
		// @Resource::UnLoadImpl
		virtual void UnLoadImpl(void);

		void Reserve(SizeT size );

		SkelBoneContainer mSkelBones;
		Util::Array<Util::String> mSkelNames;
		Util::Dictionary<IndexT, Util::String> mSkelKeyPair;


		Util::Dictionary< Util::String, GPtr<SkelTreeData> > mSkelTree;

		Util::Array< GPtr<SkelTreeData> > mSkelTreeArray;

		Util::String skelId;

		friend class SkeletonResLoader;
	};
	//------------------------------------------------------------------------
	inline
		const SkelBoneContainer& 
		SkeletonRes::GetSkelBones(void) const
	{
		return mSkelBones;
	}
	//------------------------------------------------------------------------
	inline
		void 
		SkeletonRes::Reserve(SizeT size )
	{
		n_assert( size <= MaxSkeletonBoneCount );
		if ( size > 0 )
		{
			mSkelBones.Reserve(size);
		}
	}

	inline const SizeT SkeletonRes::GetBonesCount() const
	{
		return mSkelBones.Size();
	}

	inline const Util::Array<Util::String>& SkeletonRes::GetSkelNames() const
	{
		return mSkelNames;
	}

	inline const Util::Dictionary<IndexT, Util::String>& SkeletonRes::GetSkelKeyPairs() const
	{
		return mSkelKeyPair;
	}

	inline void SkeletonRes::ReserveSkelTree(SizeT size)
	{
		n_assert( size <= MaxSkeletonBoneCount );
		mSkelTree.Reserve(size);

		mSkelTreeArray.Reserve(size);
	}

	inline const SizeT SkeletonRes::GetSkelTreeDataCount() const
	{
		return mSkelTree.Size();
	}

	inline Util::Dictionary< Util::String, GPtr<SkelTreeData> >& SkeletonRes::GetSkelTree() 
	{
		return mSkelTree;
	}

	inline Util::Array< GPtr<SkelTreeData> >& SkeletonRes::GetSkelTreeArray() 
	{
		return mSkelTreeArray;
	}

	inline bool SkeletonRes::IsSkelTreeEmpty()
	{
		return mSkelTree.IsEmpty();
	}
	inline const Util::String SkeletonRes::GetSkelID()
	{
		return skelId;
	}

}

#endif // __skeletonres_H__
