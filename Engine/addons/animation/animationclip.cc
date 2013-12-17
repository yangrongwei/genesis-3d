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

#include "animation/animation_stdneb.h"
#include "animation/animationclip.h"
#include "animation/AnimationUtil.h"


namespace Animations
{
	GPtr<AnimationClip> AnimationClip::NullClip(0);

	__ImplementClass( Animations::AnimationClip, 'ANCL', Core::RefCounted);

	//------------------------------------------------------------------------
	AnimationClip::AnimationClip()
	{
		m_ClipStartTime = 0.0f;
		m_ClipEndTime   = 0.0f;
		m_ClipDuration  = 0.0f;

	}
	//------------------------------------------------------------------------
	AnimationClip::~AnimationClip()
	{
		mAnimNodes.Clear();
	}
	//------------------------------------------------------------------------
	void 
		AnimationClip::SetName(const Resources::ResourceId& name)
	{
		n_assert( !name.AsString().IsEmpty() );
		if ( !name.AsString().IsEmpty() )
		{
			mName = name;
		}
	}
	//------------------------------------------------------------------------ 
	const GPtr<AnimationNode>& 
		AnimationClip::GetNode(IndexT index) const
	{
		if ( index >=0 && index < mAnimNodes.Size() )
		{
			return mAnimNodes[index].pNode;
		}
		else
		{
			return AnimationNode::NullNode;
		}
	}
	//------------------------------------------------------------------------ 
	const GPtr<AnimationNode>& 
		AnimationClip::GetNode( const AnimNodeID& id ) const
	{
		IndexT findIndex = m_ParentNameVec.FindIndex(id.AsString());
		if ( findIndex != InvalidIndex )
		{
			return mAnimNodes[findIndex].pNode;
		}
		else
		{
			return AnimationNode::NullNode;
		}
	}
	//------------------------------------------------------------------------ 
	GPtr<AnimationNode>&
		AnimationClip::GetNode(IndexT index)
	{
		if ( index >=0 && index < mAnimNodes.Size() )
		{
			return mAnimNodes[index].pNode;
		}
		else
		{
			return AnimationNode::NullNode;
		}
	}
	//------------------------------------------------------------------------
	bool 
		AnimationClip::AddNode( const GPtr<AnimationNode>& node , bool bReplace /*= false*/ )
	{
		if ( !node.isvalid() )
			return false;

		if ( !node->GetID().IsValid() )
			return false;

		IndexT findIndex = m_ParentNameVec.FindIndex( node->GetID().AsString() );
		if ( findIndex == InvalidIndex )
		{
			AnimNodePair animPair;
			animPair.name  = node->GetID();
			animPair.pNode = node;
			mAnimNodes.Append(animPair);
			m_ParentIndexVec.Append(node->GetParentIndex());
			m_ParentNameVec.Append(node->GetID().AsString());
			m_ParentNameHashMap.Add(node->GetID().AsString(), m_ParentNameVec.Size()-1);

			mAnimNodesMap.Add(node->GetID().AsString(), node);

			if (node->GetParentIndex() == 65535)
			{
				node->m_Parent = NULL;
			}
			else
			{
				ushort parentIndex = node->GetParentIndex();
				node->m_Parent     = mAnimNodes[parentIndex].pNode;
			}

			return true;
		}
		else
		{
			if ( bReplace )
			{
				mAnimNodes[findIndex].pNode = node;
				return true;
			}
		}

		return false;
	}
	//------------------------------------------------------------------------ 
	void 
		AnimationClip::RemoveNode(IndexT index)
	{
		if ( index >=0 && index < mAnimNodes.Size() )
		{
			mAnimNodes.EraseIndex(index);
		}
	}
	//------------------------------------------------------------------------ 
	void 
		AnimationClip::RemoveNode(const AnimNodeID& id)
	{
		IndexT findIndex = m_ParentNameVec.FindIndex(id.AsString());
		if ( findIndex != InvalidIndex )
		{
			mAnimNodes.EraseIndex(findIndex);
		}
	}
	//------------------------------------------------------------------------
	SizeT AnimationClip::CalculateRuntimeSize() const
	{
		SizeT size = mName.AsString().Length();
		for ( IndexT index = 0; index < mAnimNodes.Size(); ++index )
		{
			size += mAnimNodes[index].pNode->CalculateRuntimeSize();
		}
		return size;
	}

	float AnimationClip::GetStartTime()
	{
		for (IndexT i = 0; i<mAnimNodes.Size(); ++i)
		{
			GPtr<AnimationNode> AnimNode = mAnimNodes[i].pNode;

			float startTime = AnimNode->GetBeginTime();
			AnimNode->SetNodeBeginTime(startTime);

			m_ClipStartTime = Math::n_min(m_ClipStartTime, startTime);
		}

		return m_ClipStartTime;
	}

	float AnimationClip::GetEndTime()
	{
		for (IndexT i = 0; i<mAnimNodes.Size(); ++i)
		{
			GPtr<AnimationNode> AnimNode = mAnimNodes[i].pNode;

			float endTime = AnimNode->GetEndTime();
			AnimNode->SetNodeEndTime(endTime);

			m_ClipEndTime = Math::n_max(m_ClipEndTime, endTime);
		}

		m_ClipDuration = m_ClipEndTime - m_ClipStartTime;

		return m_ClipEndTime;
	}

	Math::float3 AnimationClip::GetAnimNodeTrans(float time, int node)
	{
		GPtr<AnimationNode>& animNode = mAnimNodes[node].pNode;

		float beginTime = animNode->GetTransCurve().GetBeginTime();
		float endTime   = animNode->GetTransCurve().GetEndTime();

		if(time <= beginTime)
		{
			//use first frame
			Math::float3 result = animNode->GetNodeTransByIndex(0);
			return result;
		}
		else if(time >= endTime)
		{
			//use last frame
			IndexT lastIndex = animNode->GetTransCurve().GetKeyFrameCount() - 1;
			Math::float3 result = animNode->GetNodeTransByIndex(lastIndex);
			return result;
		}

		if (animNode.isvalid())
		{
			TransCurve& trans = animNode->GetTransCurve();

			if (! trans.IsEmpty())
			{
				Math::float3 result = trans.EvaluateFloat3(time).GetValue();

				return result;
			}
			else
			{
				Math::float3 result = animNode->GetDefaultNodeTrans();
				return result;
			}


		}
		else
			return Math::float3(0.0, 0.0, 0.0);
	}

	Math::float3 AnimationClip::GetAnimNodeTrans(int key, int node)
	{
		GPtr<AnimationNode>& animNode = mAnimNodes[node].pNode;

		if (animNode.isvalid())
		{
			TransCurve& trans = animNode->GetTransCurve();

			if (! trans.IsEmpty())
			{
				Math::float3 result = trans.GetKeyFrame(key).GetValue();

				return result;
			}
			else
			{
				Math::float3 result = animNode->GetDefaultNodeTrans();
				return result;
			}
		}
		else
			return Math::float3(0.0, 0.0, 0.0);
	}

	Math::float3 AnimationClip::GetAnimNodeScale(float time, int node)
	{
		GPtr<AnimationNode>& animNode = mAnimNodes[node].pNode;

		float beginTime = animNode->GetScaleCurve().GetBeginTime();
		float endTime   = animNode->GetScaleCurve().GetEndTime();

		if(time <= beginTime)
		{
			//use first frame
			Math::float3 result = animNode->GetNodeScaleByIndex(0);
			return result;
		}
		else if(time >= endTime)
		{
			//use last frame
			IndexT lastIndex = animNode->GetScaleCurve().GetKeyFrameCount() - 1;
			Math::float3 result = animNode->GetNodeScaleByIndex(lastIndex);
			return result;
		}

		if (animNode.isvalid())
		{
			ScaleCurve& scale = animNode->GetScaleCurve();

			if (! scale.IsEmpty())
			{
				Math::float3 result = scale.EvaluateFloat3(time).GetValue();

				return result;
			}
			else
			{
				Math::float3 result = animNode->GetDefaultNodeScale();
				return result;
			}
		}
		else
			return Math::float3(1.0, 1.0, 1.0);
	}

	Math::float3 AnimationClip::GetAnimNodeScale(int key, int node)
	{
		GPtr<AnimationNode>& animNode = mAnimNodes[node].pNode;

		if (animNode.isvalid())
		{
			ScaleCurve& scale = animNode->GetScaleCurve();

			if (! scale.IsEmpty())
			{
				Math::float3 result = scale.GetKeyFrame(key).GetValue();

				return result;
			}
			else
			{
				Math::float3 result = animNode->GetDefaultNodeScale();
				return result;
			}
		}
		else
			return Math::float3(0.0, 0.0, 0.0);
	}

	Math::quaternion AnimationClip::GetAnimNodeRotation(float time, int node)
	{
		GPtr<AnimationNode>& animNode = mAnimNodes[node].pNode;

		float beginTime = animNode->GetRotateCurve().GetBeginTime();
		float endTime   = animNode->GetRotateCurve().GetEndTime();

		if(time <= beginTime)
		{
			//use first frame
			Math::quaternion result = animNode->GetNodeRotByIndex(0);
			return result;
		}
		else if(time >= endTime)
		{
			//use last frame
			IndexT lastIndex = animNode->GetRotateCurve().GetKeyFrameCount() - 1;
			Math::quaternion result = animNode->GetNodeRotByIndex(lastIndex);
			return result;
		}

		if (animNode.isvalid())
		{
			RotateCurve& rot = animNode->GetRotateCurve();
			if (! rot.IsEmpty())
			{
				Math::quaternion result = rot.EvaluateQuaternion(time).GetValue();

				return result;
			}
			else
			{
				Math::quaternion result = animNode->GetDefaultNodeRot();
				return result;
			}

		}
		else
			return Math::quaternion(0.0, 0.0, 0.0, 1.0);
	}

	Math::quaternion AnimationClip::GetAnimNodeRotation(int key, int node)
	{
		GPtr<AnimationNode>& animNode = mAnimNodes[node].pNode;


		if (animNode.isvalid())
		{
			RotateCurve& rot = animNode->GetRotateCurve();

			if (! rot.IsEmpty())
			{
				Math::quaternion result = rot.GetKeyFrame(key).GetValue();

				return result;
			}
			else
			{
				Math::quaternion result = animNode->GetDefaultNodeRot();
				return result;
			}
		}
		else
			return Math::quaternion(0.0, 0.0, 0.0, 1.0);
	}

	bool AnimationClip::IsChildOrSameAnimNode(const Util::String &rootName, const Util::String &curName)
	{
		GPtr<AnimationNode> pCurNode  = mAnimNodesMap[curName];
		GPtr<AnimationNode> pRootNode = mAnimNodesMap[rootName];

		while (pCurNode.isvalid())
		{
			if (pCurNode->GetID().AsString() == rootName)
			{
				return true;
			}

			pCurNode = pCurNode->m_Parent;

		}

		return false;
	}

	const int AnimationClip::GetNodeIndex( const AnimNodeID& id ) const
	{
		bool hasNode = m_ParentNameHashMap.Contains(id.AsString());
		if(hasNode)
		{
			IndexT findIndex = m_ParentNameHashMap[id.AsString()];
			if(findIndex >= 0 && findIndex < m_ParentNameVec.Size())
			{
				if(m_ParentNameVec[findIndex] == id.AsString())
				{
					return findIndex;
				}
			}
		}
		return InvalidIndex;
	}


}