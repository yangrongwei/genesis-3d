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


#ifndef __CLIP_CONTROL_H__
#define __CLIP_CONTROL_H__
#include "core/types.h"
#include "animationclip.h"
namespace Animations
{

	class AnimationClip;
	class AnimationLayer;
	class Animation;
	typedef ushort Bone;
	const Bone InvalidBone = BIT_FLAG_16BIT_MAX;
	class ClipControl
	{
	public:
		typedef AnimationClip* AnimationClipPtr;
		typedef Animation* AnimationPtr;
		typedef AnimationLayer* AnimationLayerPtr;
		ClipControl();
		~ClipControl();
		enum WrapMode
		{
			PlayUnknown  = 0,
			PlayOnce     = 1,
			PlayLoop     = 2,
			PlayMirror	 = 4,
			PlayClamp    = 8,
			PlayDefault  = PlayLoop,
	
		};

		enum PlayMode
		{
			StopSameAnimLayer = 0,
			StopAllAnim = 4
		};

		enum BlendState
		{
			BlendOff = BIT_FLAG_NONE,
			BlendingFadeIn = BIT_FLAG(0),
			BlendingFadeOut = BIT_FLAG(1),
			BlendingWeight = BIT_FLAG(2),
		};

		enum UpdateState
		{	
			US_Playing,
			US_End,
			US_NoTickBegin,
			US_Pause,
			US_Stop,
		};

		void MatchSkeleton(const Util::Array<Util::String>& boneNames);

		void BindLayer(AnimationLayerPtr layer);
		void UnbindLayer();
		void Destroy();
		void Update(float time);
		void SetTime(float time);
		void SetNormalizeTime(float time);
		void Blend(float weight, float time = BlendTimeDefault);
		void FadeIn(float time = BlendTimeDefault);
		void FadeOut(float time = BlendTimeDefault);

		void Pause();
		void Replay(float time = BlendTimeDefault);

		void SetClip(const AnimationClipPtr& clip);
		void SetSpeed(float speed);
		void SetWeight(float weight);
		void SetWrapMode(int wrap);

		AnimationClipPtr GetClip() const;
		float GetSpeed() const;
		float GetWeight() const;
		int GetWrapMode() const;
		UpdateState GetState() const;

		float GetCurrentWrapTime() const;
		float GetCurrentWeight() const;
		AnimationNode* GetNode(Bone bone) const;
		const Util::Array<Bone>& GetAffectedBones() const;
		AnimationLayerPtr GetLayer() const;

		bool GetFrameData(float time, int bone_index, Math::float3& pos, Math::quaternion& rotate, Math::float3& scale) const;
		void GetFrameDataNoCheck(float time, Bone bone, Math::float3& pos, Math::quaternion& rotate, Math::float3& scale) const;

		bool ContainBoneInfo(int bone_index) const;
		bool IsAffected(Bone bone) const;
		bool IsRunning() const;
		static void AddAffectedBones(ClipControl* cc, const Util::Array<ushort>& boneTree, const Util::Array<Util::String>& boneNames, const Util::String& name, bool child);
		static void RemoveAffectedBones(ClipControl* cc, const Util::Array<ushort>& boneTree, const Util::Array<Util::String>& boneNames, const Util::String& name, bool child);
		static const float BlendTestMark;
		static const float BlendTimeDefault;
	private:
		void addAffectedBone(Bone bone);
		void addBoneTree(const Util::Array<ushort>& boneTree, Bone root);
		void removeAffectedBone(Bone bone);
		void removeBoneTree(const Util::Array<ushort>& boneTree, Bone root);
		void clearAllAffectedBones();
		void updateBlend(float time);
		void updateWrap();
		void stop();
		void play();
		void replay();
		void fadeIn(float time);
		void fadeOut(float time);
		float getCurrentBlendingWeight() const;
		void updateCurrentWeight();
		static void findClidNodes(const Util::Array<ushort>& boneTree, Bone root, Util::Array<Bone>& array);

		AnimationClipPtr m_Clip;
		AnimationLayerPtr m_Layer;
		float m_StartTime;
		float m_EndTime;
		float m_Duration;
		Util::Array<Bone> m_SkeletonMatch;//match with animation bones
		// setting
		Util::Array<Bone> m_AffectedBones;
		WrapMode m_WrapMode;
		float m_Speed;
		float m_Weight;
		BlendState m_BlendState;
		UpdateState m_UpdateState;

		// tmp data.
		float m_FadeTime;
		float m_BlendWeightTime;
		float m_OldWeight;

		float m_FadeCounter;
		float m_BlendWeightCounter;
		float m_TimeCounter;

		float m_CurrentWeight;
		float m_CurrentWrapTime;
	};

	inline AnimationLayer* ClipControl::GetLayer() const
	{
		return m_Layer;
	}

	inline AnimationClip* ClipControl::GetClip() const
	{
		return m_Clip;
	}
	inline float ClipControl::GetSpeed() const
	{
		return m_Speed;
	}

	inline void ClipControl::SetWeight(float weight)
	{
		m_Weight = weight;
	}

	inline float ClipControl::GetWeight() const
	{
		return m_Weight;
	}
	
	inline void ClipControl::SetWrapMode(int wrap)
	{
		m_WrapMode = (WrapMode)wrap;
	}

	inline int ClipControl::GetWrapMode() const
	{
		return (int)m_WrapMode;
	}

	inline float ClipControl::GetCurrentWeight() const
	{
		return m_CurrentWeight;
	}

	inline float ClipControl::GetCurrentWrapTime() const
	{
		return m_CurrentWrapTime;
	}

	inline const Util::Array<Bone>& ClipControl::GetAffectedBones() const
	{
		return m_AffectedBones;
	}

	inline bool ClipControl::ContainBoneInfo(int bone_index) const
	{
		return m_SkeletonMatch[bone_index] != InvalidBone;
	}

	inline ClipControl::UpdateState ClipControl::GetState() const
	{
		return m_UpdateState;
	}
}

#endif //__CLIP_CONTROL_H__

