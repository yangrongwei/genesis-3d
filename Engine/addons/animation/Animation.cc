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
#include "animation/Animation.h"
#include "animation/AnimationUtil.h"

#include <functional>


#define _VEC_ITERATOR(TYPE, VECTOR, ELEM) \
	Util::Array< TYPE >::Iterator ELEM = VECTOR.Begin();\
	Util::Array< TYPE >::Iterator __end = VECTOR.End();
#define _FOREACH(ELEM)\
	while (ELEM != __end)\
{

#define _FOREACH_VECTOR_BEGIN(TYPE, VECTOR, ELEM) \
	_VEC_ITERATOR(TYPE, VECTOR, ELEM) \
	_FOREACH(ELEM)
#define  _FOREACH_VECTOR_END(ELEM) \
	++ ELEM;\
}

namespace Animations
{
	static const float TINY_WEIGHT = 0.0001f;
	static const float NO_WEIGHT = 0.0f;
	static const float FULL_WEIGHT = 1.0f;
	inline void _quaternion_add_blend(Math::quaternion& target, const Math::quaternion& from, float weight)
	{
		float sign = Math::n_sgn(from.dot(target));
		float qx = from.x() * weight * sign;
		float qy = from.y() * weight * sign; 
		float qz = from.z() * weight * sign;
		float qw = from.w() * weight * sign;
		target.set_x(target.x() + qx );
		target.set_y(target.y() + qy );
		target.set_z(target.z() + qz );
		target.set_w(target.w() + qw );
	}

	struct CompareLayers : public std::binary_function<const AnimationLayer*, const AnimationLayer*, std::size_t>
	{
		bool operator() (const AnimationLayer* lhs, const AnimationLayer* rhs) const
		{
			return lhs->GetLayerIndex() < rhs->GetLayerIndex();
		}
	};

	__ImplementClass( Animations::Animation, 'ANIM', Core::RefCounted);

	Animation::Animation()
		: m_bUpdateResult(false)
		, m_ClientCount(0)
		, m_bDirty(true)
	{
	}

	Animation::~Animation()
	{
		clearAnimClips();
		clearClipControls();
		clearLayers();
		m_ToParentTrans.Clear();
		m_SampledTrans.Clear();
		m_SampledScale.Clear();
		m_SampledRotation.Clear();
	}

	void Animation::AddAnimClip(const GPtr<AnimationClip> &animClip)
	{
		RemoveAnimClip(animClip->GetName());

		m_AnimClips.Append(animClip);

		if (0 == m_AnimationLayers.Size())
		{
			buildLayer(DefaultLayer);
		}
		buildControl(animClip.get(), m_AnimationLayers[DefaultLayer]);
	}

	void Animation::RemoveAnimClip(const Resources::ResourceId& clipName)
	{
		int index = findClipIndex(clipName);
		if (InvalidIndex != index)
		{	
			m_ClipControls[index]->Destroy();
			m_AnimClips.EraseIndex(index);
			n_delete(m_ClipControls[index]);
			m_ClipControls.EraseIndex(index);
		}
	}

	int Animation::GetAnimClipCount() const
	{
		return m_AnimClips.Size();
	}

	void Animation::SetLayer(const Resources::ResourceId& name, int layer)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			AnimationLayer* al = findLayer(layer);
			if (NULL == al)
			{
				al = buildLayer(layer);
			}			
			cc->BindLayer(al);
		}
	}

	int Animation::GetLayer(const Resources::ResourceId& name)
	{
		ClipControl* cc = findControl(name);

		if (cc)
		{
			return cc->GetLayer()->GetLayerIndex();
		}

		return (int)DefaultLayer;
	}

	void Animation::SetPlayRate(const Resources::ResourceId& name, float rate)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			cc->SetSpeed(rate);
		}
	}

	void Animation::SetWeight(const Resources::ResourceId& name, float weight)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			cc->SetWeight(weight);
		}
	}

	float Animation::GetWeight(const Resources::ResourceId& name)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			return cc->GetWeight();
		}

		return 0.0f;
	}

	void Animation::SetWrapMode(const Resources::ResourceId& name, int wrapMode)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			cc->SetWrapMode(wrapMode);
		}
	}

	int Animation::GetWrapMode(const Resources::ResourceId& name)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			return cc->GetWrapMode();
		}
		return (int)ClipControl::PlayUnknown;
	}


	void Animation::PlayAnim(const Resources::ResourceId &name, int playMode)
	{
		CrossFading(name, playMode, 0.0f);
	}

	void Animation::Stop()
	{
		_FOREACH_VECTOR_BEGIN(ClipControl*, m_ClipControls, node)	
			(*node)->FadeOut(0.0f);		
		_FOREACH_VECTOR_END(node);

		m_ToParentTrans.Clear(false);
	}

	void Animation::Stop(const Resources::ResourceId& name)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			cc->FadeOut(0.0f);
		}
	}

	void Animation::Pause(const Resources::ResourceId& name)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			cc->Pause();
		}
	}

	void Animation::Resume(const Resources::ResourceId& name)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			//cc->FadeOut(0.0f);
			cc->FadeIn(0.0f);
		}
	}

	bool Animation::IsPlaying()
	{
		_FOREACH_VECTOR_BEGIN(ClipControl*, m_ClipControls, node)	
			if(ClipControl::US_Playing == (*node)->GetState() || ClipControl::US_End == (*node)->GetState())
			{
				return true;
			}
		_FOREACH_VECTOR_END(node);
		return false;
	}

	bool Animation::IsPaused()
	{
		_FOREACH_VECTOR_BEGIN(ClipControl*, m_ClipControls, node)	
			if(ClipControl::US_Pause == (*node)->GetState())
			{
				return true;
			}
		_FOREACH_VECTOR_END(node);
		return false;
	}

	bool Animation::IsPlaying(const Resources::ResourceId& name)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			return (ClipControl::US_Playing == cc->GetState() || ClipControl::US_End == cc->GetState());
		}
		return false;
	}

	bool Animation::IsPaused(const Resources::ResourceId& name)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			return ClipControl::US_Pause == cc->GetState();
		}
		return false;
	}

	void Animation::CrossFading(const Resources::ResourceId &name, int playMode, float fadingTime)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			AnimationLayer* layer = cc->GetLayer();
			m_bDirty = true;
			if (ClipControl::StopAllAnim == playMode)
			{
				AnimationLayers::Iterator it = m_AnimationLayers.Begin();
				while(it != m_AnimationLayers.End())
				{
					if (*it != layer)
					{
						layer->FadeOutAll(fadingTime);
					}					
					++it;
				}
				cc->FadeIn(fadingTime);
			}
			else if (ClipControl::StopSameAnimLayer == playMode)
			{
				cc->FadeIn(fadingTime);
			}
		}
	}

	void Animation::Blending(const Resources::ResourceId &name, float targetWeight, float time)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			m_bDirty = true;
			cc->Blend(targetWeight, time);
		}
	}

	bool Animation::UpdateAnimation(float time)
	{

		m_bUpdateResult = false;
		AnimationLayers::Iterator it = m_AnimationLayers.Begin();
		while (it != m_AnimationLayers.End())
		{
			if ((*it)->Update(time))
			{
				m_bUpdateResult = true;
			}			
			++it;
		}

		if (m_ClientCount == 0)
		{
			m_bUpdateResult = false;
			return false;
		}

		if (m_bUpdateResult)
		{
			sample();
		}
		else
		{
			m_ToParentTrans.Clear(false);
		}
		
		return m_bUpdateResult;
	}

	void Animation::SetTime(const Resources::ResourceId& name, float time)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			cc->SetTime(time);
		}
	}

	float Animation::GetWrapTime(const Resources::ResourceId& name)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			return cc->GetCurrentWrapTime();
		}

		return 0.0f;
	}

	void Animation::SetNormalizedTime(const Resources::ResourceId& name, float time)
	{
		ClipControl* cc = findControl(name);
		if (cc)
		{
			cc->SetNormalizeTime(time);
		}	
	}

	void Animation::SetEnable(const Resources::ResourceId& name, bool enable)
	{
		///lazy man.
	}

	bool Animation::IsEnable(const Resources::ResourceId& name)
	{
		///lazy man.
		return false;
	}

	void Animation::AddAffectedNodes(const Resources::ResourceId &stateName, const Util::String& nodeName, bool recursive)
	{
		ClipControl* cc = findControl(stateName);
		if (cc)
		{
			ClipControl::AddAffectedBones(cc, m_NodeParentIndexVec, m_NodeNameVec, nodeName, recursive);
		}
	}

	void Animation::RemoveAffectedNodes(const Resources::ResourceId& stateName, const Util::String& nodeName, bool recursive)
	{
		ClipControl* cc = findControl(stateName);
		if (cc)
		{
			ClipControl::RemoveAffectedBones(cc, m_NodeParentIndexVec, m_NodeNameVec, nodeName, recursive);
		}
	}

	bool Animation::IsAnimNodeAffected( const Resources::ResourceId& stateName, const Util::String& nodeName )
	{
		IndexT index = m_NodeNameVec.FindIndex(nodeName);
		if (InvalidIndex != index)
		{
			ClipControl* cc = findControl(stateName);
			if (cc)
			{
				return cc->IsAffected((Bone)index);
			}
		}
		return false;
	}

	bool Animation::BuildDefaultToRootTrans()
	{
		Math::float3     trans;
		Math::float3     scale;
		Math::quaternion rotation;

		m_DefaultToRootX.Clear();
		Util::Array<Math::matrix44>   defaultToParentTrans;
		Util::Array<Math::float3>     defaultTrans;
		Util::Array<Math::float3>     defaultScale;
		Util::Array<Math::quaternion> defaultRotation;

		int nodeCount = m_CheckedNodeList.Size();

		defaultTrans.Resize(nodeCount, Math::float3(0.0, 0.0, 0.0));
		defaultScale.Resize(nodeCount, Math::float3(0.0, 0.0, 0.0));
		defaultRotation.Resize(nodeCount, Math::quaternion(0.0, 0.0, 0.0, 0.0));

		//Use m_CheckedNodeList's nodeName£¬find nodes in animClip
		for(int iNode = 0; iNode<nodeCount; ++iNode)
		{
			trans    = Math::float3(m_CheckedNodeList[iNode].defPosition.x(),m_CheckedNodeList[iNode].defPosition.y(),m_CheckedNodeList[iNode].defPosition.z());
			scale    = Math::float3(m_CheckedNodeList[iNode].defScale.x(),m_CheckedNodeList[iNode].defScale.y(),m_CheckedNodeList[iNode].defScale.z());
			rotation = m_CheckedNodeList[iNode].defRotation;

			defaultTrans[iNode] = trans;
			defaultScale[iNode] = scale;

			float sign = Math::n_sgn(rotation.dot(defaultRotation[iNode]));

			float qx = rotation.x() * sign;
			float qy = rotation.y() * sign; 
			float qz = rotation.z() * sign;
			float qw = rotation.w() * sign;


			defaultRotation[iNode].set_x( defaultRotation[iNode].x() + qx );
			defaultRotation[iNode].set_y( defaultRotation[iNode].y() + qy );
			defaultRotation[iNode].set_z( defaultRotation[iNode].z() + qz );
			defaultRotation[iNode].set_w( defaultRotation[iNode].w() + qw );

			if(defaultRotation[iNode].length() != 0)
				defaultRotation[iNode] = defaultRotation[iNode].normalize(defaultRotation[iNode]);

			Math::float4   trans4(defaultTrans[iNode].x(), defaultTrans[iNode].y(), defaultTrans[iNode].z(), 1.0);
			Math::float4   scale4(defaultScale[iNode].x(), defaultScale[iNode].y(), defaultScale[iNode].z(), 1.0);

			Math::matrix44 toParent = Math::matrix44::transformation(
				scale4, defaultRotation[iNode], trans4);

			defaultToParentTrans.Append(toParent);

			//transform ToParent to ToRoot
			ushort indiceNodeParent = m_CheckedNodeList[iNode].parentIndex;
			if (indiceNodeParent != InvalidBone)
			{
				Math::matrix44 toRootX = Math::matrix44::multiply( defaultToParentTrans[indiceNodeParent], defaultToParentTrans[iNode] );
				defaultToParentTrans[iNode] = toRootX;
				m_DefaultToRootX.Add(m_CheckedNodeList[iNode].nodeName, toRootX);
			}
			else if (indiceNodeParent == InvalidBone)
			{
				//toParent[iNode] =  Math::matrix44::multiply(rotx, toParent[iNode]);
				m_DefaultToRootX.Add(m_CheckedNodeList[iNode].nodeName, defaultToParentTrans[iNode] );

			}

		}

		defaultToParentTrans.Clear(true);
		defaultTrans.Clear(true);
		defaultScale.Clear(true);
		defaultRotation.Clear(true);

		if(!m_DefaultToRootX.IsEmpty())
			return true;
		else
			return false;
	}

	void Animation::SetSkelTree( const Util::Array< GPtr<Resources::SkelTreeData> >& skelTree )
	{
		//clean data
		m_NodeNameVec.Clear(false);
		m_NodeParentIndexVec.Clear(false);
		m_CheckedNodeList.Clear(false);

		//init m_CheckedNodeList
		CheckedNode tempNode;
		m_CheckedNodeList.Resize(skelTree.Size(),tempNode);

		//find in skelTree£¬build NodeNameVec and NodeParentIndexVec
		for(int i = 0; i<skelTree.Size();++i)
		{
			m_CheckedNodeList[i].nodeName = skelTree[i]->name;
			m_NodeNameVec.Append(skelTree[i]->name);

			ushort parentIndex = InvalidBone;
			if(skelTree[i]->parent.isvalid())
			{
				Util::String parentName = skelTree[i]->parent->name;
				for(int nodeIndex = 0; nodeIndex<i; ++nodeIndex)
				{
					if(m_CheckedNodeList[nodeIndex].nodeName == parentName)
					{
						parentIndex = nodeIndex;
						break;
					}
				}
			}
			m_CheckedNodeList[i].parentIndex = parentIndex;
			m_NodeParentIndexVec.Append(parentIndex);

			//set skeleton's default transform
			m_CheckedNodeList[i].defPosition = Math::float3(skelTree[i]->pos.x(),skelTree[i]->pos.y(),skelTree[i]->pos.z());
			m_CheckedNodeList[i].defRotation = skelTree[i]->rot;
			m_CheckedNodeList[i].defScale = Math::float3(skelTree[i]->scale.x(),skelTree[i]->scale.y(),skelTree[i]->scale.z());
		}

		ClipControls::Iterator it = m_ClipControls.Begin();
		while(it != m_ClipControls.End())
		{
			(*it)->MatchSkeleton(m_NodeNameVec);
			++it;
		}
	}


	bool _alloc_weight(float* free_weights, int bone_index, float get_from_free, float& out_take_away)
	{
		float& free = free_weights[bone_index];
		if (free > NO_WEIGHT)
		{
			float take_away = free * get_from_free;
			if (take_away > TINY_WEIGHT)
			{
				if (take_away > free)
				{
					out_take_away = free;
					free = NO_WEIGHT;
				}
				else
				{
					free -= take_away;
					out_take_away = take_away;
				}
				return true;
			}			
		}
		out_take_away = NO_WEIGHT;
		return false;
	}

	void Animation::blendFrameData(int bone_index, float take_in_free, 
		const Math::float3& pos, const Math::quaternion& rotate, const Math::float3& scale)
	{
		float take_away = NO_WEIGHT;
		if(_alloc_weight(&m_FreeWeights[0], bone_index, take_in_free, take_away))
		{
			m_SampledTrans[bone_index] += (pos * take_away);
			m_SampledScale[bone_index] += (scale * take_away);
			_quaternion_add_blend(m_SampledRotation[bone_index], rotate, take_away);
		}
	}
	template<bool check_layer>
	void Animation::blendControl(const ClipControl* cc, int nodeCount)
	{
		Math::float3     trans;
		Math::float3     scale;
		Math::quaternion rotation;

		float wrap_time = cc->GetCurrentWrapTime();
		float weight = cc->GetCurrentWeight();

		const Util::Array<Bone>& bones = cc->GetAffectedBones();
		if (bones.Size())
		{
			for (int i = 0; i < bones.Size(); ++i)
			{
				Bone bone = bones[i];
				if(m_FreeWeights[bone] > NO_WEIGHT)
				{		
					cc->GetFrameDataNoCheck(wrap_time, bone, trans, rotation, scale);
					if (check_layer)
					{
						if (m_LayerWeights[bone] > NO_WEIGHT)
						{
							blendFrameData(bone, weight / m_LayerWeights[bone], trans, rotation, scale);
						}
					}
					else
					{
						blendFrameData(bone, weight, trans, rotation, scale);
					}
				}
			}
		}
		else
		{
			for (int bone_index = 0; bone_index < nodeCount; ++bone_index)
			{
				if(m_FreeWeights[bone_index] > NO_WEIGHT && cc->GetFrameData(wrap_time, bone_index, trans, rotation, scale))
				{
					if (check_layer)
					{
						if (m_LayerWeights[bone_index] > NO_WEIGHT)
						{
							blendFrameData(bone_index, weight / m_LayerWeights[bone_index], trans, rotation, scale);
						}
					}
					else
					{
						blendFrameData(bone_index, weight, trans, rotation, scale);
					}
				}
			}	
		}
	}

	void Animation::buildLayerWeight(const ClipControls& activeControls, int nodeCount)
	{
		m_LayerWeights.Clear(false);
		m_LayerWeights.Resize(nodeCount, 0.0f);
		ClipControls::Iterator it = activeControls.Begin();
		while(it != activeControls.End())
		{					
			float weight = (*it)->GetCurrentWeight();
			const Util::Array<Bone>& bones = (*it)->GetAffectedBones();
			if (bones.Size())
			{
				for (int i = 0; i < bones.Size(); ++i)
				{
					Bone bone = bones[i];
					m_LayerWeights[bone] += weight;
				}
			}
			else
			{
				for (int bone_index = 0; bone_index < nodeCount; ++bone_index)
				{
					if ((*it)->ContainBoneInfo(bone_index))
					{
						m_LayerWeights[bone_index] += weight;
					}			
				}
			}
			++it;
		}
	}

	void Animation::sample()
	{
		int nodeCount = m_NodeNameVec.Size();

		m_ToParentTrans.Clear(false);
		m_SampledTrans.Clear(false);
		m_SampledScale.Clear(false);
		m_SampledRotation.Clear(false);
		m_FreeWeights.Clear(false);

		m_SampledTrans.Resize(nodeCount, Math::float3(0.0f, 0.0f, 0.0f));
		m_SampledScale.Resize(nodeCount, Math::float3(0.0f, 0.0f, 0.0f));
		m_SampledRotation.Resize(nodeCount, Math::quaternion(0.0f, 0.0f, 0.0f,0.0f));
		m_FreeWeights.Resize(nodeCount, 1.0f);

		for (int i = m_AnimationLayers.Size() - 1; i >= 0; --i)
		{
			AnimationLayer* layer = m_AnimationLayers[i];
			ClipControls& activeControls = layer->GetActiveList();
			if (activeControls.Size() == 1)
			{
				blendControl<false>(activeControls[0], nodeCount);
			}
			else if (activeControls.Size() >= 1)
			{
				buildLayerWeight(activeControls, nodeCount);

				ClipControls::Iterator it = activeControls.Begin();
				while(it != activeControls.End())
				{	
					blendControl<true>(*it, nodeCount);
					++it;
				}
			}
		}
		for (int iNode = 0; iNode < nodeCount; ++iNode)
		{
			if (m_FreeWeights[iNode] > NO_WEIGHT)
			{
				m_SampledTrans[iNode] += (m_CheckedNodeList[iNode].defPosition * m_FreeWeights[iNode]);
				m_SampledScale[iNode] += (m_CheckedNodeList[iNode].defScale * m_FreeWeights[iNode]);
				_quaternion_add_blend(m_SampledRotation[iNode], m_CheckedNodeList[iNode].defRotation, m_FreeWeights[iNode]);
			}

			if(m_SampledRotation[iNode].length() != 0)
				m_SampledRotation[iNode] = m_SampledRotation[iNode].normalize(m_SampledRotation[iNode]);

			Math::float4   trans4(m_SampledTrans[iNode].x(), m_SampledTrans[iNode].y(), m_SampledTrans[iNode].z(), 1.0);
			Math::float4   scale4(m_SampledScale[iNode].x(), m_SampledScale[iNode].y(), m_SampledScale[iNode].z(), 1.0);

			Math::matrix44 toParent = Math::matrix44::transformation(
				scale4, m_SampledRotation[iNode], trans4);	
			m_ToParentTrans.Append(toParent);
		}
	}

	void Animation::clearClipControls()
	{
		_FOREACH_VECTOR_BEGIN(ClipControl*, m_ClipControls, node)	
			n_delete (*node);
		_FOREACH_VECTOR_END(node);

		m_ClipControls.Clear();
	}

	void Animation::clearAnimClips()
	{		
		m_AnimClips.Clear();
	}

	void Animation::clearLayers()
	{
		_FOREACH_VECTOR_BEGIN(AnimationLayer*, m_AnimationLayers, node)	
			n_delete (*node);
		_FOREACH_VECTOR_END(node);
		m_AnimationLayers.Clear();
	}

	void Animation::buildControl(AnimationClip* clip, AnimationLayer* layer)
	{
		ClipControl* cc = n_new(ClipControl);
		m_ClipControls.Append(cc);
		cc->SetClip(clip);
		cc->BindLayer(layer);
		if (m_NodeNameVec.Size())
		{
			cc->MatchSkeleton(m_NodeNameVec);
		}
	}

	AnimationLayer* Animation::buildLayer(int index)
	{
		n_assert(NULL == findLayer(index));
		AnimationLayer* al = n_new(AnimationLayer);
		al->SetLayerIndex(index);
		m_AnimationLayers.Append(al);		
		Util::CustomSortArray<AnimationLayer*, CompareLayers>(m_AnimationLayers);
		return al;
	}

	AnimationLayer* Animation::findLayer(int index) const
	{
		_FOREACH_VECTOR_BEGIN(AnimationLayer*, m_AnimationLayers, node)	
			if((*node)->GetLayerIndex() == index)
			{
				return *node;
			}
		_FOREACH_VECTOR_END(node);
		return NULL;
	}

	AnimationClip* Animation::findClip(const Resources::ResourceId& name) const
	{
		_FOREACH_VECTOR_BEGIN(GPtr<AnimationClip>, m_AnimClips, node)	
			if((*node)->GetName() == name)
			{
				return (*node).get_unsafe();
			}
		_FOREACH_VECTOR_END(node);

		return NULL;
	}

	ClipControl* Animation::findControl(const Resources::ResourceId& name) const
	{
		_FOREACH_VECTOR_BEGIN(ClipControl*, m_ClipControls, node)	
			if((*node)->GetClip()->GetName() == name)
			{
				return (*node);
			}
		_FOREACH_VECTOR_END(node);
		return NULL;
	}

	int Animation::findClipIndex(const Resources::ResourceId& name) const
	{
		for (int i = 0; i < m_AnimClips.Size(); ++i)
		{
			if (m_AnimClips[i]->GetName() == name)
			{
				return i;
			}
		}
		return InvalidIndex;
	}
}