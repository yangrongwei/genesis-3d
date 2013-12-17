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
#ifndef __animationclip_H__
#define __animationclip_H__

#include "animation/animationnode.h"
#include "resource/resource.h"

namespace Animations
{
	/*
	1¡¢An AnimationClip represent a animation section. e.g "walk","run"
	2¡¢An AnimationClip can has many AnimationNodes¡£That means this animation need control lots of nodes to compute
	*/

	struct AnimNodePair
	{
		AnimNodeID         name;
		GPtr<AnimationNode> pNode;
	};

	class AnimationClip: public Core::RefCounted
	{
		__DeclareClass(AnimationClip);
	public:
		enum WrapMode
		{
			ONCE     = 1,
			LOOP     = 2,
			PINGPONG = 4,
			ClAMP    = 8
		};


		AnimationClip();
		virtual ~AnimationClip();

		/// get name of this animation clip
		const Resources::ResourceId& GetName(void) const;

		/// !!!!!!! It's Dangerous.  Becare for Call this !!!!!!!!!!.    set name of this animation clip. name can not be empty
		void SetName(const Resources::ResourceId& name);

		/// get node count
		SizeT GetNodeCount(void);

		/// if node exist by id
		bool HasNode( const AnimNodeID& id ) const;

		/// get node by index. return null if invalid index
		const GPtr<AnimationNode>& GetNode(IndexT index) const;

		GPtr<AnimationNode>& GetNode(IndexT index);

		/// get node by id. return null if invalid id
		const GPtr<AnimationNode>& GetNode( const AnimNodeID& id ) const;

		/// get node index using hash table. return -1 if invalid id
		const int GetNodeIndex( const AnimNodeID& id ) const;

		/// add node. Failed if node is invalid.  
		/// if node'id is repeat and bReplace is false, will Failed.
		/// if node'id is repeat and bReplace is true, will replace the old node. 
		bool AddNode( const GPtr<AnimationNode>& node , bool bReplace = false );

		/// remove node by index. Note: after remove, other index may be invalid
		void RemoveNode(IndexT index);

		/// remove node by ID
		void RemoveNode(const AnimNodeID& id);

		/// Calculate Runtime Size
		virtual SizeT CalculateRuntimeSize() const;

		void   SetSampleRate(float rate);
		const float  GetSampleRate() const;

		float  GetStartTime();
		float  GetEndTime();
		const float  GetClipDuration() const;

		Math::float3     GetAnimNodeTrans(float time, int node);
		Math::float3     GetAnimNodeScale(float time, int node);
		Math::quaternion GetAnimNodeRotation(float time, int node);

		Math::float3     GetAnimNodeTrans(int key, int node);
		Math::float3     GetAnimNodeScale(int key, int node);
		Math::quaternion GetAnimNodeRotation(int key, int node);

		const Util::Array<ushort>& GetParentIndexVec() const;
		const Util::Array<Util::String>& GetParentNameVec()  const;

		bool IsChildOrSameAnimNode(const Util::String& rootName, const Util::String& curName);

		void Duplicate(const GPtr<AnimationClip>& clip);

		void SetAnimNodesMap(const Util::Dictionary< AnimNodeID , GPtr<AnimationNode> >& nodesMap);
		void SetAnimNodes(const Util::Array< AnimNodePair >& animNodes);
		void SetParenIndexVec(const Util::Array<ushort>& parent);
		void SetParentNameVec(const Util::Array<Util::String>& parent);
		void SetParentNameHashMap(const Util::HashTable<Util::String, IndexT>& parentHashMap);

	protected:
		Resources::ResourceId mName;	//	clip name
		Util::Dictionary< AnimNodeID , GPtr<AnimationNode> > mAnimNodesMap;
		Util::Array< AnimNodePair > mAnimNodes;


		float        m_ClipStartTime;
		float        m_ClipEndTime;
		float        m_ClipDuration;
		float        m_ClipSampleRate;


		Util::Array<ushort> m_ParentIndexVec;
		Util::Array<Util::String> m_ParentNameVec;
		Util::HashTable< Util::String, IndexT > m_ParentNameHashMap;

	public:
		static GPtr<AnimationClip> NullClip;
	};
	//------------------------------------------------------------------------
	inline
		const Resources::ResourceId& 
		AnimationClip::GetName(void) const
	{
		return mName;
	}
	//------------------------------------------------------------------------
	inline 
		SizeT 
		AnimationClip::GetNodeCount(void)
	{
		return mAnimNodes.Size();
	}
	//------------------------------------------------------------------------
	inline
		bool 
		AnimationClip::HasNode( const AnimNodeID& id ) const
	{
		IndexT index = m_ParentNameVec.FindIndex(id.AsString());

		if (index != InvalidIndex)
		{
			return true;
		}
		else
			return false;
	}


	inline const Util::Array<ushort>& AnimationClip::GetParentIndexVec() const
	{
		return m_ParentIndexVec;
	}

	//------------------------------------------------------------------------
	inline const Util::Array<Util::String>& AnimationClip::GetParentNameVec() const
	{
		return m_ParentNameVec;
	}

	//------------------------------------------------------------------------
	inline void AnimationClip::SetSampleRate(float rate)
	{
		m_ClipSampleRate = rate;
	}

	//------------------------------------------------------------------------
	inline const float AnimationClip::GetSampleRate() const
	{
		return m_ClipSampleRate;
	}

	//------------------------------------------------------------------------
	inline void AnimationClip::SetAnimNodesMap(const Util::Dictionary<AnimNodeID,GPtr<AnimationNode> > &nodesMap)
	{
		mAnimNodesMap = nodesMap;
	}

	//------------------------------------------------------------------------
	inline void AnimationClip::SetAnimNodes(const Util::Array<AnimNodePair> &animNodes)
	{
		mAnimNodes = animNodes;
	}

	//------------------------------------------------------------------------
	inline void AnimationClip::SetParenIndexVec(const Util::Array<ushort> &parent)
	{
		m_ParentIndexVec = parent;
	}

	//------------------------------------------------------------------------
	inline void AnimationClip::SetParentNameVec(const Util::Array<Util::String> &parent)
	{
		m_ParentNameVec = parent;
	}

	//------------------------------------------------------------------------
	inline void AnimationClip::SetParentNameHashMap(const Util::HashTable<Util::String, IndexT> &parentHashMap)
	{
		m_ParentNameHashMap = parentHashMap;
	}

	//------------------------------------------------------------------------
	inline void AnimationClip::Duplicate(const GPtr<AnimationClip>& clip)
	{
		clip->SetAnimNodesMap(mAnimNodesMap);
		clip->SetAnimNodes(mAnimNodes);
		clip->SetParenIndexVec(m_ParentIndexVec);
		clip->SetParentNameVec(m_ParentNameVec);
		clip->SetParentNameHashMap(m_ParentNameHashMap);
		clip->SetSampleRate(m_ClipSampleRate);
	}

	//------------------------------------------------------------------------
	inline const float AnimationClip::GetClipDuration() const
	{
		return m_ClipDuration;
	}


}

#endif // __animationclip_H__
