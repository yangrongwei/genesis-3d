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

#pragma once

#include "app/appframework/component.h"
#include "app/appframework/actor.h"
#include "resource/animationres.h"
#include "foundation/math/float3.h"
#include "foundation/math/quaternion.h"
#include "foundation/math/matrix44.h"
#include "foundation/math/float2.h"
#include "foundation/math/float4.h"
#include "animation/Animation.h"
#include "resource/skeletonres.h"

namespace App
{
	using namespace Animations;
	using namespace Resources;

	struct ClipInfo
	{
		int  begin;
		int  end;
		bool loop;

		Resources::ResourceId clipOldName;
		Resources::ResourceId clipNewName;
	};

	struct AttachedActorInfo 
	{
		Util::String attachedSkelName;
		Math::matrix44 attachedActorTrans;
	};

	class Actor;

	class AnimationComponent : public App::Component
	{
		__DeclareSubClass(AnimationComponent, App::Component);
	public:
		AnimationComponent();
		virtual ~AnimationComponent();

		/// @Component::OnActivate  called from Actor::ActivateComponents()
		virtual void OnActivate();

		/// @Component::OnDeactivate called from Actor::DeactivateComponents()
		virtual void OnDeactivate();

		/// @Component::SetupCallbacks setup callbacks for this component, call by Actor in OnActivate()
		virtual void SetupCallbacks();

		/// @Component::SetupAcceptedMessages override to register accepted messages
		virtual void SetupAcceptedMessages();

		/// @Component::SetupAcceptedMessages handle a single message
		virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

		void SetAnimationID(const Resources::ResourceId& animName, Resources::Priority priority = ResourcePriority::AnimationDefault);

		SizeT GetAnimResCount() const; 

		const Resources::ResourceId& GetAnimResID(IndexT iRes) const;

		const GPtr<Resources::AnimationRes>& GetCurrentAnimRes() const;

		const GPtr<Animations::Animation>& GetAnimation() const;

		const bool IsAllLoaded() const;

		const bool HasAnyErrors() const;

		void AddAnimationRes(GPtr<Resources::AnimationRes> &animRes);

		bool PlayAnimation(const Resources::ResourceId& name, int playMode = ClipControl::StopSameAnimLayer);

		void BlendingAnimation(const Resources::ResourceId& name, float weight, float time = 0.3);

		void ForceUpdate();

		void StopAnimations();

		bool StopAnimation(const Resources::ResourceId& name);

		bool PauseAnimation(const Resources::ResourceId& name);

		bool ResumeAnimation(const Resources::ResourceId& name);

		const Resources::ResourceId GetDefaultAnimName();

		void SetDefaultAnimName(const Resources::ResourceId& name);

		bool CrossFading(const Resources::ResourceId& name, int playMode = ClipControl::StopSameAnimLayer, float time = 0.3f);

		bool IsAnyAnimationPlaying();

		bool IsAnyAnimationPaused();

		bool IsAnimationPlaying(const Resources::ResourceId& name);

		bool IsAnimationPaused(const Resources::ResourceId& name);

		void SetWrapMode(const Resources::ResourceId& name, int wrapMode);

		int GetWrapMode(const Resources::ResourceId& name);

		void SetLayer(const Resources::ResourceId& name, int layer);

		IndexT GetLayer(const Resources::ResourceId& name);

		void SetTime(const Resources::ResourceId& name, float time);

		float GetTime(const Resources::ResourceId& name);

		void SetAnimationSpeed(const Resources::ResourceId& name, float speed);
		float GetAnimationSpeed(const Resources::ResourceId& name);

		void SetWeight(const Resources::ResourceId& name, float weight);
		float GetWeight(const Resources::ResourceId& name);

		void SetNormalizedTime(const Resources::ResourceId& name, float time);

		void SetAnimationEnable(const Resources::ResourceId& name, bool enable);

		const SizeT GetAnimationsCount() const;

		const Util::Array<ushort>& GetParentIndex() const;

		const Util::Array<Util::String>& GetParentNames() const;

		void SetBuildToRootX(bool built);

		bool HasBuildToRootX() const;

		bool BuildToRootX();

		const Util::Array<Math::matrix44>& GetToRootXTrans() const;

		bool HasBuildToParentTrans();

		void AddAffectedNodes(const Resources::ResourceId& animName, const Util::String& nodeName, bool recursive = true);

		void RemoveAffectedNodes(const Resources::ResourceId& animName, const Util::String& nodeName, bool recursive = true);

		bool IsAnimNodeAffected(const Resources::ResourceId& stateName, const Util::String& nodeName);

		bool GetNodeTransform(const Util::String& nodeName, Math::matrix44& trans);

		void SetGetSkelTree(bool got);

		bool HasGotSkelTree() const;

		void SetSkelTree(Util::Dictionary< Util::String, GPtr<SkelTreeData> >& skelTree);

		const float GetDurationTime(const Resources::ResourceId& clipName);

		void RemoveClip(const Resources::ResourceId& clipName);

		const bool IsUpdate();

		bool IsToParentXEmpty();

		bool IsInAttachedList(GPtr<Actor> actor);

		bool IsInCanAttachedList(GPtr<Actor> actor);

		void AddAttachedActor(const GPtr<Actor>& pActor, const Util::String& name);

		void AddActorCanAttached(const GPtr<Actor>& pActor);

		const int GetCanAttachedActorCount();

		const GPtr<Actor>& GetCanAttachedActor(IndexT index);

		const int GetAttachedActorCount();

		const Util::Dictionary< GPtr<Actor>, AttachedActorInfo >& GetAttachedActors();

		void ClearAttachedActorList();

		void SetAttachedActors( Util::Dictionary< GPtr<Actor>, AttachedActorInfo >& attachedActors);

		Util::Dictionary< Util::Guid, AttachedActorInfo > GetTempAttachedActors();

		void SetTempAttachedActors(Util::Dictionary< Util::Guid, AttachedActorInfo > tempAttach);

		void SetTempAttachedActors( Util::Dictionary< IndexT, AttachedActorInfo > tempAttach );

		void AddDefaultAttachedActor();

		const Util::Array< GPtr<SkelTreeData> > GetSkelTreeData();

		void SetSkelTree(Util::Array< GPtr<SkelTreeData> >& skelTree);

		void ReFindSkelTree();

		void AddToAttachedActorList(const GPtr<Actor>& pActor, const Util::String& name);

		void RemoveAttachedActor(const GPtr<Actor>& pActor);

		void RemoveAttachedActor(const Util::String skelName);

		bool GetUsedBoneIndex(GPtr<Actor> pActor, Util::Dictionary<IndexT, IndexT>& usedBonesIndex);

		bool GetUnusedBoneIndex(GPtr<Actor> pActor, Util::Array<IndexT>& unusedBonesIndex);

		void FindAttachedActor(const GPtr<Actor>& pActor);

		void FindAttachedActor();

		float GetCurrentFrame();

		float GetCurrentFrame(const Resources::ResourceId& animName);

		int GetAnimFrameCount(const Resources::ResourceId& animName);

		int GetCurrentAnimFrameCount();

		const Resources::ResourceId& GetCurrentAnimation();

		void ClientAdd();

		void ClientSub();

		int GetClientCount() const;

		virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

		bool GetAnimLoaded(const Resources::ResourceId& animName);

		void AddLocaterCom(const GPtr<Actor>& pActor, const Util::String& attechedName);
		void LoadLocaterCom(const GPtr<Actor>& pActor, const Util::String& attechedName);
		void RemoveLocaterCom(const GPtr<Actor>& pActor);

	public:	//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// copy from other component
		virtual void CopyFrom( const GPtr<Component>& pComponent );

		virtual void SetupAllResource();
		virtual bool IsAllResourceLoaded();

	protected:
		/// @component::_OnBeginFrame called on begin of frame
		virtual void _OnBeginFrame();

		virtual void _OnEndFrame();

	private:
		void DirtyAnimInfos();

		void DelayProcess();

		bool GetAnimNodeTrans(const Util::String& name, Math::matrix44& trans);

		bool FindUsedBones(const GPtr<AnimationClip>& clip, const GPtr<SkeletonRes>& skelteon, const GPtr<Actor>& pActor);
		bool ReFindUsedBones(const GPtr<Actor>& pActor);


	public:
		bool HasBuildDefaultToRootX();
		bool BuildDefaultToRootX();
		const Util::Dictionary<Util::String, Math::matrix44>& GetDefaultToRootX() const;

	protected:
		struct AnimResParam
		{
			AnimResParam()
				: dirty(false),
				animRes(NULL),
				priority(Resources::ResourcePriority::AnimationDefault)
			{

			}

			GPtr<Resources::AnimationRes> animRes;
			bool                         dirty;
			Resources::Priority          priority;
		};

		typedef Util::Dictionary< Resources::ResourceId, AnimResParam > AnimationParamMap;

		struct AnimationInfos
		{
			AnimationInfos()
				: dirty(false),
				allLoaded(false)
			{

			}

			AnimationParamMap animMap;
			bool              dirty;
			bool              allLoaded;
		};

		struct AnimStateParam
		{
			AnimStateParam()
				: playingRate(1.0),
				localTime(0.0),
				speed(1.0),
				layer(0),
				wrapMode(2),
				blendMode(0),
				isNeedBlending(false),
				isNeedCrossFading(false),
				isSetWrapMode(false),
				isSetLayer(false),
				isSetSpeed(false),
				isSetWeight(false),
				isSetNormalizedTime(false),
				isSetEnable(false),
				isPlay(false),
				isSetTime(false),
				isSetBlendMode(false)

			{

			}

			float fadingTime;
			float targetWeight;
			float curWeight;
			int   playMode;
			int   wrapMode;
			int   blendMode;
			int   layer;
			bool  enable;

			float playingRate;
			float localTime;
			float normalizedTime;
			float speed;

			bool  isNeedBlending;
			bool  isNeedCrossFading;
			bool  isSetWrapMode;
			bool  isPlay;
			bool  isSetLayer;
			bool  isSetSpeed;
			bool  isSetWeight;
			bool  isSetNormalizedTime;
			bool  isSetEnable;
			bool  isSetTime;
			bool  isSetBlendMode;

			Resources::ResourceId name;

			Util::Dictionary<Util::String, bool> affectedNodes;

		};

		typedef Util::Dictionary<Resources::ResourceId, AnimStateParam> AnimStateParamMap;

		AnimationInfos m_AnimInfos;


		AnimStateParamMap m_AnimStateParam;
		Resources::ResourceId      m_CurrentAnimName;
		Resources::ResourceId	  m_DefaultAnimName;
		IndexT            m_nCurrentLayer;

		Util::Array<ClipInfo> m_ClipInfos;

		GPtr<Animations::Animation>              m_Animation;

		Util::Array<ushort>         m_ParentIndexVec;
		Util::Array<Util::String>   m_ParentNameVec;

		Util::Array<Math::matrix44> m_ToRootX;

		Util::Dictionary< Util::String, GPtr<SkelTreeData> > m_SkelTree;

		Util::Dictionary< GPtr<Actor>, AttachedActorInfo > m_AttachedActors;
		Util::Dictionary< GPtr<Actor>, Math::matrix44 > m_AttachedActorsTrans;

		//when load animCom, other Actors' load is noe complete, need save some useful information
		Util::Dictionary< Util::Guid, AttachedActorInfo > m_TempAttachedActors;

		Util::Array< GPtr<Actor> > m_CanAttachedActor;

		Util::Array< GPtr<SkelTreeData> > m_SkelTreeArray;

		bool m_bAnimInfosDirty;
		bool m_bAllLoaded;
		bool m_bHasAnyErrors;
		bool m_bHasBuildToRootX;
		bool m_bHasGotSkelTree;
		bool m_bSplitClip;
		bool m_bFindUsedBones;
		bool m_bHasBuildDefaultToRootX;

		bool m_bNeedAddDefaultAttach;

		Util::Array< GPtr<AnimationClip> > m_AnimationClips;

		struct BoneMatrix
		{
			Util::Dictionary<IndexT, IndexT> used;
			Util::Array<IndexT> unused;
		};
		Util::Dictionary< Resources::ResourceId, Util::Dictionary< GPtr<Actor>, BoneMatrix > > m_UsedBonesIndex;

	public:

		static GPtr<Resources::AnimationRes> NullRes;

		static Math::matrix44               m_IndentityMatrix;
	};

	inline SizeT AnimationComponent::GetAnimResCount() const
	{
		return m_AnimInfos.animMap.Size();
	}

	inline void AnimationComponent::DirtyAnimInfos()
	{
		m_bAnimInfosDirty = true;
		m_AnimInfos.dirty = true;
		m_bFindUsedBones = false;
	}

	inline const Resources::ResourceId AnimationComponent::GetDefaultAnimName()
	{
		return m_DefaultAnimName;
	}

	inline void AnimationComponent::SetDefaultAnimName( const Resources::ResourceId& name )
	{
		m_DefaultAnimName = name;
	}

	inline const GPtr<Animations::Animation>& AnimationComponent::GetAnimation() const
	{
		return m_Animation;
	}

	inline const bool AnimationComponent::IsAllLoaded() const
	{
		return m_bAllLoaded;
	}

	inline const bool AnimationComponent::HasAnyErrors() const
	{
		return m_bHasAnyErrors;
	}

	inline const Util::Array<ushort>& AnimationComponent::GetParentIndex() const
	{
		return m_ParentIndexVec;
	}

	inline const Util::Array<Util::String>& AnimationComponent::GetParentNames() const
	{
		return m_ParentNameVec;
	}

	inline void AnimationComponent::SetBuildToRootX(bool built)
	{
		m_bHasBuildToRootX = built;
	}

	inline bool AnimationComponent::HasBuildToRootX() const
	{
		return m_bHasBuildToRootX;
	}

	inline const Util::Array<Math::matrix44>& AnimationComponent::GetToRootXTrans() const
	{
		return m_ToRootX;
	}

	inline bool AnimationComponent::HasBuildToParentTrans()
	{
		Util::Array<Math::matrix44>& toParent = m_Animation->GetToParentTrans();

		if (toParent.IsEmpty())
		{
			return false;
		}
		else
			return true;
	}

	inline void AnimationComponent::SetGetSkelTree(bool got)
	{
		m_bHasGotSkelTree = got;
	}

	inline bool AnimationComponent::HasGotSkelTree() const
	{
		return m_bHasGotSkelTree;
	}

	inline void AnimationComponent::ClientAdd()
	{
		n_assert(m_Animation.isvalid())
			m_Animation->ClientAdd();
	}

	inline void AnimationComponent::ClientSub()
	{
		n_assert(m_Animation.isvalid())
			m_Animation->ClientSub();
	}

	inline int AnimationComponent::GetClientCount() const
	{
		n_assert(m_Animation.isvalid())
			return m_Animation->GetClientCount();
	}

	inline const bool AnimationComponent::IsUpdate()
	{
		if (m_Animation.isvalid())
		{
			return m_Animation->IsUpdate();
		}
		else
		{
			return false;
		}
	}

	inline bool AnimationComponent::IsToParentXEmpty()
	{
		Util::Array<Math::matrix44>& toParent = m_Animation->GetToParentTrans();

		return toParent.IsEmpty();
	}

	inline bool AnimationComponent::IsInAttachedList(GPtr<Actor> actor)
	{
		return m_AttachedActors.Contains(actor);
	}

	inline const Util::Dictionary< GPtr<Actor>, AttachedActorInfo >& AnimationComponent::GetAttachedActors()
	{
		return m_AttachedActors;
	}

	inline const int AnimationComponent::GetCanAttachedActorCount()
	{
		return m_CanAttachedActor.Size();
	}

	inline const int AnimationComponent::GetAttachedActorCount()
	{
		return m_AttachedActors.Size();
	}

	inline bool AnimationComponent::HasBuildDefaultToRootX()
	{
		return m_bHasBuildDefaultToRootX;
	}

	inline const Util::Dictionary<Util::String, Math::matrix44>& AnimationComponent::GetDefaultToRootX() const
	{
		return m_Animation->GetDefaultToRootX();
	}

	inline const Util::Array< GPtr<SkelTreeData> > AnimationComponent::GetSkelTreeData()
	{
		if(m_SkelTreeArray.Size() == 0)
		{
			ReFindSkelTree();
		}
		return m_SkelTreeArray;
	}

	inline const Resources::ResourceId& AnimationComponent::GetCurrentAnimation()
	{
		return m_CurrentAnimName;
	}

}
