#include "animation/animation_stdneb.h"
#include "ClipControl.h"
#include "AnimationLayer.h"
#include "Animation.h"
#include "AnimationUtil.h"
namespace Animations
{

	static const float MinSpeed = 0.0001f;
	static const float MinClipEnd = 0.001f; 
	inline float _cal_weight(float numerator, float denominator)
	{
		float a = numerator / denominator;
		a = Math::n_clamp(a, 0.0f, 1.0f);
		return a;
	}

	const float ClipControl::BlendTestMark = 0.001f;
	const float ClipControl::BlendTimeDefault = 0.3f;
	ClipControl::ClipControl()
		:m_WrapMode(PlayOnce)
		,m_Speed(1.0f)
		,m_Weight(1.0f)
		,m_OldWeight(1.0f)
		,m_BlendState(BlendOff)
		,m_UpdateState(US_Stop)
		,m_FadeTime(BlendTestMark)
		,m_BlendWeightTime(BlendTestMark)
		,m_FadeCounter(0.0f)
		,m_BlendWeightCounter(0.0f)
		,m_TimeCounter(0.0f)
		,m_CurrentWeight(0.0f)
		,m_CurrentWrapTime(0.0f)
		,m_Layer(NULL)
		,m_Clip(NULL)
	{

	}

	ClipControl::~ClipControl()
	{
		Destroy();
	}

	void ClipControl::BindLayer(AnimationLayerPtr layer)
	{
		if (m_Layer != NULL)
		{
			UnbindLayer();
		}
		
		m_Layer = layer;
		m_Layer->_AddControl(this);
	}

	void ClipControl::UnbindLayer()
	{
		if (m_Layer)
		{
			m_Layer->_RemoveActive(this);
			m_Layer->_RemoveControl(this);
			m_Layer = NULL;
		}
	}

	void ClipControl::MatchSkeleton(const Util::Array<Util::String>& boneNames)
	{
		int bone_count = boneNames.Size();
		m_SkeletonMatch.Resize(bone_count, InvalidBone);
		for(int ske_bone = 0; ske_bone < bone_count; ++ske_bone)
		{
			int ani_bone = m_Clip->GetNodeIndex(boneNames[ske_bone]);
			if (InvalidIndex != ani_bone)
			{
				m_SkeletonMatch[ske_bone] = ani_bone;
			}
		}
	}

	void ClipControl::Destroy()
	{
		UnbindLayer();
	}

	void ClipControl::Update(float time)
	{
		if (US_NoTickBegin < m_UpdateState )
		{
			return;
		}
		float a = time * m_Speed;
		m_TimeCounter += a;
		updateWrap();
		if (BlendOff != m_BlendState)
		{
			updateBlend(a);
			updateCurrentWeight();
		}

	}
	void ClipControl::SetNormalizeTime(float time)
	{
		SetTime(time *  m_Duration + m_StartTime);
	}

	void ClipControl::SetTime(float time)
	{
		updateWrap();
		float wrap_time = m_CurrentWrapTime;
		float bias = time - wrap_time;

		m_TimeCounter = time;
		if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingFadeIn))
		{
			m_FadeCounter += bias;
		}
		else if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingFadeOut))
		{
			m_FadeCounter += bias;
		}
		if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingWeight))
		{
			m_BlendWeightCounter += bias;
		}

	}
	void ClipControl::SetSpeed(float speed)
	{
		m_Speed = speed;
		if (m_Speed < MinSpeed)
		{
			m_Speed = MinSpeed;
		}

	}

	void ClipControl::updateBlend(float time)
	{
		if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingFadeIn))
		{
			m_FadeCounter += time;
			if (m_FadeCounter >= m_FadeTime)
			{
				m_FadeCounter = m_FadeTime;
				m_BlendState = BIT_FlAG_DELETE(m_BlendState, BlendingFadeIn);
			}
		}
		else if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingFadeOut))
		{
			m_FadeCounter += time;
			if (m_FadeCounter >= m_FadeTime)
			{
				stop();
				return;
			}
		}
		if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingWeight))
		{
			m_BlendWeightCounter += time;
			if (m_BlendWeightCounter >= m_BlendWeightTime)
			{
				m_BlendWeightCounter = m_BlendWeightTime;
				m_BlendState = BIT_FlAG_DELETE(m_BlendState, BlendingWeight);
			}
		}
	}
	void ClipControl::updateWrap()
	{
		switch (m_WrapMode)
		{
		case PlayOnce:
			{
				if(m_TimeCounter > m_Duration) 
				{
					stop();
				}
				m_CurrentWrapTime = m_TimeCounter + m_StartTime;
			}
			break;
		case PlayLoop:
			{
				m_CurrentWrapTime = Animations::Loop(m_TimeCounter, m_StartTime, m_EndTime);
			}
			break;
		case  PlayMirror:
			{
				m_CurrentWrapTime = Animations::Mirror(m_TimeCounter, m_StartTime, m_EndTime);
			}
			break;
		case PlayClamp:
			{
				if (m_TimeCounter >= m_EndTime)
				{
					m_UpdateState = US_End;
				}
				m_CurrentWrapTime = m_TimeCounter + m_StartTime;
			}
			break;
		default:
			{
				m_CurrentWrapTime = 0.0f;
			}
			break;
		}
	}
	void ClipControl::stop()
	{
		m_UpdateState = US_Stop;
		m_TimeCounter = 0.0f;

		m_FadeTime = BlendTestMark;
		m_BlendWeightTime = BlendTestMark;
		m_FadeCounter = 0.0f;
		m_BlendWeightCounter = 0.0f;
		m_OldWeight = m_Weight;
		m_CurrentWeight = 0.0f;
		m_CurrentWrapTime = 0.0f;
		m_BlendState = BlendOff;
		m_Layer->_RemoveActive(this);
	}

	void ClipControl::Pause()
	{
		m_UpdateState = US_Pause;
	}

	void ClipControl::play()
	{
		m_UpdateState = US_Playing;
	}

	void ClipControl::replay()
	{
		stop();
		play();
	}

	void ClipControl::Blend(float weight, float time /* = BlendTestMark */)
	{
		if (US_Pause == m_UpdateState)
		{
			play();
		}
		else if (US_Stop == m_UpdateState)
		{
			play();
			m_Layer->_AddActive(this);
		}
		else if (US_End == m_UpdateState)
		{
			replay();
		}

		if (time > BlendTestMark)
		{
			if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingWeight))
			{
				m_OldWeight = getCurrentBlendingWeight();
				m_Weight = weight;
				m_BlendWeightCounter = 0.0f;
				m_BlendWeightTime = time;
			}
			else
			{	
				m_OldWeight = m_Weight;
				m_Weight = weight;
				m_CurrentWeight = weight;
				m_BlendState = BIT_FlAG_APPEND(m_BlendState, BlendingWeight);
				m_BlendWeightCounter = 0.0f;
				m_BlendWeightTime = time;
			}
		}
		else
		{
			m_OldWeight = m_Weight;
			m_Weight = weight;
			m_CurrentWeight = weight;
			m_BlendWeightTime = BlendTestMark;
			m_BlendWeightCounter = BlendTestMark;
			m_BlendState = BIT_FlAG_DELETE(m_BlendState, BlendingWeight);
		}

	}

	void ClipControl::FadeIn(float time /* = BlendTestMark */)
	{

		switch(m_UpdateState)
		{
		case US_Pause:
			{
				play();
				return;
			}
			break;
		case US_Stop:
			{
				play();
			}
			break;
		case US_End:
			{
				replay();
			}
			break;
		case US_Playing:
			{
				return;
			}
			break;
		default:
			break;
		}
		m_Layer->_FadeOutOther(this, time);
		m_Layer->_AddActive(this);
		fadeIn(time);
	}

	void ClipControl::FadeOut(float time /* = BlendTestMark */)
	{
		switch(m_UpdateState)
		{
		case US_Pause:
			{
				play();
				fadeOut(time);
			}
			break;
		case US_Stop:
			{
			}
			break;
		case US_End:
			{
				fadeOut(time);
			}
			break;
		case US_Playing:
			{
				fadeOut(time);
			}
			break;
		default:
			break;
		}
	}

	void ClipControl::fadeIn(float time)
	{
		if (time > BlendTestMark)
		{
			if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingFadeIn))
			{
				m_FadeCounter = time * _cal_weight(m_FadeCounter, m_FadeTime);
			}
			else if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingFadeOut))
			{
				m_FadeCounter = time * (1.0f - _cal_weight(m_FadeCounter, m_FadeTime));
			}
			else
			{
				m_FadeCounter = 0.0f;
			}				
			m_BlendState = BIT_FlAG_APPEND(m_BlendState, BlendingFadeIn);
			m_FadeTime = time;
		}
		else
		{
			m_FadeTime = BlendTestMark;
			m_FadeCounter = BlendTestMark;
			m_BlendState = BIT_FlAG_DELETE(m_BlendState, BlendingFadeIn);
			m_CurrentWeight = m_Weight;
		}
		m_BlendState = BIT_FlAG_DELETE(m_BlendState, BlendingFadeOut);
	}
	void ClipControl::fadeOut(float time)
	{
		if (time > BlendTestMark)
		{
			if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingFadeIn))
			{
				m_FadeCounter = time * (1.0f - _cal_weight(m_FadeCounter, m_FadeTime));
			}
			else if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingFadeOut))
			{				
				m_FadeCounter = time * _cal_weight(m_FadeCounter, m_FadeTime);
			}
			else
			{
				m_BlendState = BIT_FlAG_APPEND(m_BlendState, BlendingFadeOut);
				m_FadeCounter = 0.0f;

			}
			m_FadeTime = time;
			m_BlendState = BIT_FlAG_DELETE(m_BlendState, BlendingFadeIn);
		}
		else
		{
			stop();
		}
	}

	float ClipControl::getCurrentBlendingWeight() const
	{
		return Math::n_lerp(m_OldWeight, m_Weight, _cal_weight(m_BlendWeightCounter, m_BlendWeightTime));
	}
	void ClipControl::updateCurrentWeight()
	{
		if (US_Stop == m_UpdateState)
		{
			m_CurrentWeight = 0.0f;
		}
		if (BlendOff == m_BlendState)
		{
			m_CurrentWeight = m_Weight;
			return;
		}
		if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingWeight))
		{
			m_CurrentWeight = getCurrentBlendingWeight();
		}
		else
		{
			m_CurrentWeight = m_Weight;
		}

		if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingFadeIn))
		{
			m_CurrentWeight *= _cal_weight(m_FadeCounter, m_FadeTime);	
		}
		else if (BIT_FLAG_IS_OPEN(m_BlendState, BlendingFadeOut))
		{
			m_CurrentWeight *= (1.0f - _cal_weight(m_FadeCounter, m_FadeTime));
		}
	}

	bool ClipControl::GetFrameData(float time, int bone_index, Math::float3& pos, Math::quaternion& rotate, Math::float3& scale) const
	{
		if (InvalidBone != m_SkeletonMatch[bone_index])
		{
			pos = m_Clip->GetAnimNodeTrans(time, m_SkeletonMatch[bone_index]);
			rotate = m_Clip->GetAnimNodeRotation(time, m_SkeletonMatch[bone_index]);
			scale = m_Clip->GetAnimNodeScale(time, m_SkeletonMatch[bone_index]);
			return true;
		}
		return false;
	}

	void ClipControl::GetFrameDataNoCheck(float time, Bone bone, Math::float3& pos, Math::quaternion& rotate, Math::float3& scale) const
	{
		pos = m_Clip->GetAnimNodeTrans(time, m_SkeletonMatch[bone]);
		rotate = m_Clip->GetAnimNodeRotation(time, m_SkeletonMatch[bone]);
		scale = m_Clip->GetAnimNodeScale(time, m_SkeletonMatch[bone]);
	}

	AnimationNode* ClipControl::GetNode(Bone bone) const
	{
		if (m_SkeletonMatch[bone] != InvalidBone)
		{
			return m_Clip->GetNode(bone).get_unsafe();
		}
		return NULL;
	}

	void ClipControl::SetClip(const AnimationClipPtr& clip)
	{
		m_Clip = clip;
		m_StartTime = clip->GetStartTime();
		m_EndTime = clip->GetEndTime();
		if (m_EndTime < MinClipEnd)
		{
			m_EndTime = MinClipEnd;
		}
		m_Duration = clip->GetClipDuration();
	}

	bool ClipControl::IsAffected(Bone bone) const
	{
		if (0 == m_AffectedBones.Size())
		{
			return true;
		}
		return InvalidIndex != m_AffectedBones.FindIndex(bone);
	}

	bool ClipControl::IsRunning() const
	{
		return US_Stop != m_UpdateState;
	}

	void ClipControl::AddAffectedBones(ClipControl* cc, const Util::Array<ushort>& boneTree, const Util::Array<Util::String>& boneNames, const Util::String& name, bool child)
	{
		n_assert(NULL != cc);
		n_assert(boneTree.Size() == boneNames.Size());
		IndexT bone_index = boneNames.FindIndex(name);
		if (InvalidIndex != bone_index)
		{
			if (child)
			{
				cc->addBoneTree(boneTree, bone_index);
			}
			else
			{
				cc->addAffectedBone((Bone)bone_index);
			}
		}
	}

	void ClipControl::RemoveAffectedBones(ClipControl* cc, const Util::Array<ushort>& boneTree, const Util::Array<Util::String>& boneNames, const Util::String& name, bool child)
	{
		n_assert(NULL != cc);
		n_assert(boneTree.Size() == boneNames.Size());
		IndexT bone_index = boneNames.FindIndex(name);
		if (InvalidIndex != bone_index)
		{
			if (child)
			{
				cc->removeBoneTree(boneTree, bone_index);
			}
			else
			{
				cc->removeAffectedBone((Bone)bone_index);
			}
		}
	}

	void ClipControl::clearAllAffectedBones()
	{
		m_AffectedBones.Clear();
	}
	void ClipControl::addAffectedBone(Bone bone)
	{
		if (InvalidBone == m_SkeletonMatch[bone])
		{
			return;
		}
		for (int i = 0; i < m_AffectedBones.Size(); ++i)
		{
			if (m_AffectedBones[i] == bone)
			{
				return;
			}
			else if (m_AffectedBones[i] > bone)
			{
				m_AffectedBones.Insert(i, bone);
			}
		}
		m_AffectedBones.Append(bone);
	}

	void ClipControl::addBoneTree(const Util::Array<ushort>& boneTree, Bone root)
	{
		Util::Array<Bone> array; 
		array.Append(root);
		findClidNodes(boneTree, root, array);
		Util::Array<Bone>::Iterator it = array.Begin();
		while(it != array.End())
		{
			addAffectedBone(*it);
			++it;
		}
	}

	void ClipControl::removeAffectedBone(Bone bone)
	{
		IndexT index = m_AffectedBones.FindIndex(bone);
		if (InvalidIndex != index)
		{
			m_AffectedBones.EraseIndex(index);
		}
	}

	void ClipControl::removeBoneTree(const Util::Array<ushort>& boneTree, Bone root)
	{
		Util::Array<Bone> array; 
		array.Append(root);
		findClidNodes(boneTree, root, array);
		Util::Array<Bone>::Iterator it = array.Begin();
		while(it != array.End())
		{
			removeAffectedBone(*it);
			++it;
		}
	}

	void ClipControl::findClidNodes(const Util::Array<ushort>& boneTree, Bone root, Util::Array<Bone>& array)
	{
		for (int bone = root + 1; bone < boneTree.Size(); ++bone)
		{
			if (boneTree[bone] == root)
			{
				array.Append(bone);
				findClidNodes(boneTree, bone, array);
			}
		}
	}


}