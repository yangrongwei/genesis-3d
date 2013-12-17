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
#include "appframework/actormanager.h"
#include "graphicfeature/components/animationcomponent.h"
#include "graphicfeature/graphicsfeature.h"
#include "graphicfeature/graphicsfeatureprotocol.h"
#include "basegamefeature/managers/timesource.h"
#include "resource/resourceserver.h"
#include "animation/AnimationServer.h"
#include "animation/AnimationUtil.h"
#include "graphicfeature/components/skeletoncomponent.h"
#include "graphicfeature/components/skinnedmeshrendercomponent.h"
#include "graphicfeature/components/locatercomponent.h"

namespace App
{
	using namespace Graphic;


	__ImplementClass(AnimationComponent, 'ACPN', App::Component);

	GPtr<Resources::AnimationRes> AnimationComponent::NullRes(0);

	Math::matrix44 AnimationComponent::m_IndentityMatrix(Math::matrix44::identity());

	AnimationComponent::AnimationComponent()
		: m_bAnimInfosDirty(false),
		m_bAllLoaded(false),
		m_bHasAnyErrors(false),
		m_bHasBuildToRootX(false),
		m_bHasGotSkelTree(false),
		m_bFindUsedBones(false),
		m_nCurrentLayer(0),
		m_bHasBuildDefaultToRootX(false),
		m_bNeedAddDefaultAttach(false),
		m_Animation(NULL)
	{
		m_Animation = Animation::Create();
	}

	AnimationComponent::~AnimationComponent()
	{
		m_AnimInfos.animMap.Clear();
		m_SkelTree.Clear();

		m_Animation = NULL;
	}

	void AnimationComponent::OnActivate()
	{

		AnimationServer::Instance()->AttachAnimation(m_Animation);

		Actor::Check_Animation(this);
		Super::OnActivate();
	}

	void AnimationComponent::OnDeactivate()
	{
		this->StopAnimations();

		Super::OnDeactivate();
		AnimationServer::Instance()->DetachAnimaton(m_Animation);
	}

	void AnimationComponent::SetupCallbacks()
	{
		mActor->RegisterComponentCallback(this, BeginFrame);
		mActor->RegisterComponentCallback(this, EndFrame);
	}

	void AnimationComponent::SetupAcceptedMessages()
	{
		Super::SetupAcceptedMessages();
	}

	void AnimationComponent::HandleMessage(const GPtr<Messaging::Message> &msg)
	{
		Super::HandleMessage(msg);
	}

	void AnimationComponent::SetAnimationID(const Resources::ResourceId &animName, Resources::Priority priority)
	{
		if (!animName.IsValid())
		{
			return;
		}

		AnimationParamMap& animMap = m_AnimInfos.animMap;
		IndexT findAnim            = animMap.FindIndex(animName);

		if (findAnim != InvalidIndex)
		{
#ifdef __GENESIS_EDITOR__
			animMap.ValueAtIndex(findAnim).dirty = true;
			DirtyAnimInfos();
#endif

			return;
		}
		else
		{
			AnimResParam animParam;
			animParam.animRes  = NULL;
			animParam.dirty    = true;
			if (mActor && mActor->PriorityDefinition())
			{
				priority = mActor->GetPriority();
			}
			animParam.priority = priority;

			if(priority == Resources::ResourcePriority::Synchronization)
			{
				const Util::String resID = animName.AsString();
				GPtr<AnimationResInfo> pAnimInfo = Resources::ResourceManager::Instance()->CreateAnimationResInfo(resID, animParam.priority);
				if (pAnimInfo.isvalid() && pAnimInfo->GetRes().isvalid())
				{
					animParam.animRes = pAnimInfo->GetRes().downcast<AnimationRes>();

					if (animParam.animRes->GetState() == Resource::Loaded)
					{
						if(animParam.dirty)
						{
							AddAnimationRes(animParam.animRes);
							if (mActor != NULL)
							{
								SizeT count = animParam.animRes->GetClipCount();
								for (IndexT i = 0; i < count; ++i)
								{
									FindUsedBones(animParam.animRes->GetClip(i), NULL, mActor);

									IndexT ret = InvalidIndex;
									for(int index = 0; index < m_AnimationClips.Size(); ++index)
									{
										ResourceId clipName = m_AnimationClips[index]->GetName();
										if(animParam.animRes->GetClip(i)->GetName() == clipName)
										{
											ret = index;
											break;
										}
									}
									if (ret != InvalidIndex)
									{
										m_AnimationClips.EraseIndex(ret);
									}
								}	
							}													
							animParam.dirty = false;
						}

					}	
				}
				else
				{
					animParam.animRes = NULL;							
				}

				animMap.Add(animName, animParam);
				m_bFindUsedBones = true;
				m_bAllLoaded     = true;
				return;
			}

			animMap.Add(animName, animParam);
			DirtyAnimInfos();
			m_bAllLoaded = false;
		}
	}

	const Resources::ResourceId& AnimationComponent::GetAnimResID(IndexT iRes) const
	{
		if (iRes >= 0 && iRes < m_AnimInfos.animMap.Size())
		{
			return m_AnimInfos.animMap.KeyAtIndex(iRes);
		}

		return Resources::Resource::EmptyResID;
	}

	bool AnimationComponent::ReFindUsedBones(const GPtr<Actor>& pActor)
	{
		int keyValuePairIndex_Anim = m_UsedBonesIndex.FindIndex(m_CurrentAnimName);
		int keyValuePairIndex_Actor = 0;;

		if(keyValuePairIndex_Anim != -1)
		{
			keyValuePairIndex_Actor = m_UsedBonesIndex[m_CurrentAnimName].FindIndex(pActor);
		}

		if(keyValuePairIndex_Actor == -1 || keyValuePairIndex_Anim == -1)
		{
			bool ret = true;
			for (IndexT iClip = 0; iClip < m_Animation->GetAnimClipCount(); ++iClip)
			{
				ret &= FindUsedBones(m_Animation->GetAnimClips()[iClip], NULL, pActor);
			}

			return ret;
		}

		return true;
	}

	bool AnimationComponent::GetUsedBoneIndex(GPtr<Actor> pActor, Util::Dictionary<IndexT, IndexT>& usedBonesIndex)
	{
		bool found = ReFindUsedBones(pActor);
		if(found)
		{
			usedBonesIndex = m_UsedBonesIndex[m_CurrentAnimName][pActor].used;
			return true;
		}
		else
		{
			return false;
		}
	}

	bool AnimationComponent::GetUnusedBoneIndex(GPtr<Actor> pActor, Util::Array<IndexT>& unusedBonesIndex)
	{
		bool found = ReFindUsedBones(pActor);
		if(found)
		{
			unusedBonesIndex = m_UsedBonesIndex[m_CurrentAnimName][pActor].unused;
			return true;
		}
		else
		{
			return false;
		}
	}

	void AnimationComponent::_OnBeginFrame()
	{

		if (m_bAnimInfosDirty)
		{
			bool hasAnimDirty = false;

			if (m_AnimInfos.dirty)
			{
				int unLoadedCount = m_AnimInfos.animMap.Size();
				int failedLoadedCount = 0;

				for (IndexT iRes = 0; iRes<m_AnimInfos.animMap.Size(); ++iRes)
				{
					AnimResParam& animParam             = m_AnimInfos.animMap.ValueAtIndex(iRes);
					const Resources::ResourceId& animID = m_AnimInfos.animMap.KeyAtIndex(iRes);

					if (animParam.animRes.isvalid())
					{
						if (animParam.animRes->GetState() == Resource::Loaded)
						{
							if(animParam.dirty)
							{
								AddAnimationRes(animParam.animRes);
								animParam.dirty = false;
							}
							unLoadedCount--;			
						}
						else
						{
							if (animParam.animRes->GetState() == Resource::Failed)
							{
								failedLoadedCount++;
							}
						}
					}
					else
					{
						const Util::String resID = animID.AsString();

						GPtr<AnimationResInfo> pAnimInfo = Resources::ResourceManager::Instance()->CreateAnimationResInfo(resID, animParam.priority);
						if (pAnimInfo.isvalid() && pAnimInfo->GetRes().isvalid())
						{
							animParam.animRes = pAnimInfo->GetRes().downcast<AnimationRes>();

							if (animParam.animRes->GetState() == Resource::Loaded)
							{
								if(animParam.dirty)
								{
									AddAnimationRes(animParam.animRes);
									animParam.dirty = false;
								}
								unLoadedCount--;
							}
							else
							{
								if (animParam.animRes->GetState() == Resource::Failed)
								{
									failedLoadedCount++;
								}
							}
						}
						else
						{
							animParam.animRes = NULL;							
						}
					}
				}

				m_bAllLoaded = false;
				if (unLoadedCount == 0 || unLoadedCount == failedLoadedCount)
				{
					m_AnimInfos.dirty     = false;
					m_AnimInfos.allLoaded = true;

					m_bAllLoaded = true;

					DelayProcess();

				}
			}

			hasAnimDirty |= m_AnimInfos.dirty;

			m_bAnimInfosDirty = hasAnimDirty;
		}

		if (!m_bFindUsedBones && m_bAllLoaded)
		{
			bool hasAllFound = true;
			for (IndexT iClip = 0; iClip < m_AnimationClips.Size(); ++iClip)
			{
				hasAllFound &= FindUsedBones(m_AnimationClips[iClip], NULL, mActor);
			}

			if(hasAllFound)
			{
				m_AnimationClips.Clear();
				m_bFindUsedBones = true;
			}

		}

		if(m_bNeedAddDefaultAttach)
		{
			if(!m_SkelTree.IsEmpty())
			{
				AddDefaultAttachedActor();
			}
		}
	}

	void AnimationComponent::_OnEndFrame()
	{
		m_bHasBuildToRootX = false;
	}

	void AnimationComponent::AddAnimationRes(GPtr<Resources::AnimationRes> &animRes)
	{
		SizeT count = animRes->GetClipCount();

		for (IndexT iClip = 0; iClip<count; ++iClip)
		{
			const GPtr<AnimationClip>& animClipTemp = animRes->GetClip(iClip);
			GPtr<AnimationClip> animClip = AnimationClip::Create();
			animClipTemp->AnimationClip::Duplicate(animClip);
			animClip->SetName(animRes->GetResourceId().AsString());

			if (animClip.isvalid())
			{
				m_Animation->AddAnimClip(animClip);
				m_AnimationClips.Append(animClip);

				if (animClip->GetName() == m_CurrentAnimName)
				{
					m_bFindUsedBones = false;
				}
				
			}
		}


	}

	bool AnimationComponent::PlayAnimation(const Resources::ResourceId &name, int playMode)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimStateParam asParam;
			asParam.playMode = playMode;
			asParam.isPlay   = true;
			asParam.name     = name;

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.playMode = playMode;
				existedAS.isPlay   = true;
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}


			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded )
			{
				m_Animation->PlayAnim(name, playMode);

				if (m_CurrentAnimName != name)
				{
					m_CurrentAnimName = name;
					ClipControl* cc = m_Animation->GetClipControl(m_CurrentAnimName);

					if (cc)
					{
						AnimationClip* clip = cc->GetClip();
						if (clip)
						{
							m_ParentIndexVec = m_Animation->GetNodeParentIndexVec();
							m_ParentNameVec  = m_Animation->GetNodeNameVec();
						}
					}
				}

				m_bHasAnyErrors = false;

				return true;
			}

			m_bHasAnyErrors = true;

			return false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return false;
		}

	}

	const GPtr<Resources::AnimationRes>& AnimationComponent::GetCurrentAnimRes() const
	{
		const AnimationParamMap& animMap = m_AnimInfos.animMap;
		IndexT findAnim                  = animMap.FindIndex("m_CurrentAnimName+");

		if (findAnim != InvalidIndex)
		{
			const AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			return animParam.animRes;
		}
		else
		{	
			return NullRes;
		}
	}

	//Get played animation's current frame
	float AnimationComponent::GetCurrentFrame(const Resources::ResourceId& animName )
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(animName);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				ClipControl* cc = m_Animation->GetClipControl(animName);
				if (cc)
				{
					float frame = GetTime(animName) * cc->GetClip()->GetSampleRate();
					return frame;
				}
			}
			return -1;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", animName.Value());
			return -1;
		}		
	}

	//Get played animation's current frame
	float AnimationComponent::GetCurrentFrame()
	{
		return GetCurrentFrame(m_CurrentAnimName);	
	}

	int AnimationComponent::GetAnimFrameCount( const Resources::ResourceId& animName )
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(animName);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				ClipControl* cc = m_Animation->GetClipControl(animName);
				if (cc)
				{
					float frame = cc->GetClip()->GetClipDuration() * cc->GetClip()->GetSampleRate();
					return (int)frame;
				}
			}
			return -1;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", animName.Value());
			return -1;
		}
	}

	int AnimationComponent::GetCurrentAnimFrameCount()
	{
		return GetAnimFrameCount(m_CurrentAnimName);	
	}

	void AnimationComponent::BlendingAnimation(const Resources::ResourceId &name, float weight, float time)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		weight = ClampWeightRange(weight);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->Blending(name, weight, time);

				if (m_CurrentAnimName != name)
				{
					m_CurrentAnimName = name;
					ClipControl* cc = m_Animation->GetClipControl(m_CurrentAnimName);

					if (cc)
					{
						AnimationClip* clip =  cc->GetClip();
						if (clip)
						{
							m_ParentIndexVec = m_Animation->GetNodeParentIndexVec();
							m_ParentNameVec  = m_Animation->GetNodeNameVec();
						}
					}
				}
			}

			AnimStateParam asParam;
			asParam.targetWeight   = weight;
			asParam.fadingTime     = time;
			asParam.isNeedBlending = true;
			asParam.name           = name;

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.name			  = name;
				existedAS.targetWeight	  = weight;
				existedAS.fadingTime	  = time;
				existedAS.isNeedBlending  = true;
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return;
		}

	}

	void AnimationComponent::AddAffectedNodes(const Resources::ResourceId& animName, const Util::String& nodeName, bool recursive)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(animName);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded )
			{

				m_Animation->AddAffectedNodes(animName, nodeName, recursive);

			}
			else
			{
				AnimStateParam asParam;

				asParam.affectedNodes.Add(nodeName, recursive);

				IndexT findAS = m_AnimStateParam.FindIndex(animName);
				if (findAS != InvalidIndex)
				{
					AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);

					IndexT findExistedNode = existedAS.affectedNodes.FindIndex(nodeName);

					if (findExistedNode != InvalidIndex)
					{
						existedAS.affectedNodes.ValueAtIndex(findExistedNode) = recursive;
					}
					else
					{
						existedAS.affectedNodes.Add(nodeName, recursive);
					}

				} 
				else
				{
					m_AnimStateParam.Add(animName, asParam);
				}
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", animName.Value());

			m_bHasAnyErrors = true;

			return;
		}


	}

	void AnimationComponent::RemoveAffectedNodes(const Resources::ResourceId& animName, const Util::String& nodeName, bool recursive)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(animName);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded )
			{

				m_Animation->RemoveAffectedNodes(animName, nodeName, recursive);

			}

		}
		else
		{
			n_warning("there is no '%s' animation! \n", animName.Value());

			return;
		}
	}

	bool AnimationComponent::IsAnimNodeAffected(const Resources::ResourceId& animName, const Util::String& nodeName)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(animName);

		bool ret = false;

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded )
			{

				ret = m_Animation->IsAnimNodeAffected(animName, nodeName);

			}

		}
		else
		{
			n_warning("there is no '%s' animation! \n", animName.Value());

		}

		return ret;
	}

	void AnimationComponent::StopAnimations()
	{
		if ( m_Animation.isvalid() )
		{
			m_Animation->Stop();
		}
	}

	void AnimationComponent::ForceUpdate()
	{
		m_Animation->UpdateAnimation((float)GameTime::Instance()->GetFrameTime());
	}

	bool AnimationComponent::StopAnimation(const Resources::ResourceId& name)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{


			AnimStateParam asParam;
			asParam.name = name;
			asParam.isPlay = false;
			asParam.isNeedCrossFading = false;

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS   = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.isPlay			= false;
				existedAS.isNeedCrossFading = false;
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}

			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid())
			{
				m_Animation->Stop(name);

				m_bHasAnyErrors = false;
				return true;
			}

			m_bHasAnyErrors = true;

			return false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return false;
		}
	}

	bool AnimationComponent::PauseAnimation(const Resources::ResourceId& name)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->Pause(name);

				return true;
			}
			else
			{
				AnimStateParam asParam;
				asParam.name = name;

				IndexT findAS = m_AnimStateParam.FindIndex(name);
				if (findAS != InvalidIndex)
				{
					return false;
				} 
				else
				{
					m_AnimStateParam.Add(name, asParam);
				}
			}

			m_bHasAnyErrors = false;

			return false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return false;
		}
	}

	bool AnimationComponent::ResumeAnimation(const Resources::ResourceId& name)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->Resume(name);

				return true;
			}
			else
			{
				AnimStateParam asParam;
				asParam.name = name;

				IndexT findAS = m_AnimStateParam.FindIndex(name);
				if (findAS != InvalidIndex)
				{
					return false;
				} 
				else
				{
					m_AnimStateParam.Add(name, asParam);
				}
			}

			m_bHasAnyErrors = false;

			return false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return false;
		}
	}

	void AnimationComponent::DelayProcess()
	{
		SizeT count = m_AnimStateParam.Size();

		for (int i = 0; i<count; ++i)
		{
			AnimStateParam& asParam = m_AnimStateParam.ValueAtIndex(i);

			if (asParam.isPlay)
			{
				PlayAnimation(asParam.name, asParam.playMode);		
			}

			if (asParam.isNeedBlending)
			{
				BlendingAnimation(asParam.name, asParam.targetWeight, asParam.fadingTime);
			}

			if (asParam.isNeedCrossFading)
			{
				CrossFading(asParam.name, asParam.playMode, asParam.fadingTime);
			}

			if (asParam.isSetLayer)
			{
				SetLayer(asParam.name, asParam.layer);
			}

			if (asParam.isSetNormalizedTime)
			{
				SetNormalizedTime(asParam.name, asParam.normalizedTime);
			}

			if (asParam.isSetSpeed)
			{
				SetAnimationSpeed(asParam.name, asParam.speed);
			}

			if (asParam.isSetWeight)
			{
				SetWeight(asParam.name, asParam.curWeight);
			}

			if (asParam.isSetWrapMode)
			{
				SetWrapMode(asParam.name, asParam.wrapMode);
			}

			if (asParam.isSetEnable)
			{
				SetAnimationEnable(asParam.name, asParam.enable);
			}

			if (asParam.isSetTime)
			{
				SetTime(asParam.name, asParam.localTime);
			}

			for (IndexT iNode = 0; iNode<asParam.affectedNodes.Size(); ++iNode)
			{
				AddAffectedNodes(asParam.name, asParam.affectedNodes.KeyAtIndex(iNode), asParam.affectedNodes.ValueAtIndex(iNode));
			}
		}
	}

	bool AnimationComponent::CrossFading(const Resources::ResourceId &name, int playMode, float time)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{

			AnimStateParam asParam;
			asParam.playMode          = playMode;
			asParam.fadingTime        = time;
			asParam.name              = name;
			asParam.isNeedCrossFading = true;

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS   = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.name				= name;
				existedAS.playMode			= playMode;
				existedAS.fadingTime		= time;
				existedAS.isNeedCrossFading = true;
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}

			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->CrossFading(name, playMode, time);

				if (m_CurrentAnimName != name)
				{
					m_CurrentAnimName = name;
					ClipControl* cc = m_Animation->GetClipControl(m_CurrentAnimName);

					if (cc)
					{
						AnimationClip* clip =  cc->GetClip();
						if (clip)
						{
							m_ParentIndexVec = m_Animation->GetNodeParentIndexVec();
							m_ParentNameVec  = m_Animation->GetNodeNameVec();
						}
					}
				}

				m_bHasAnyErrors = false;
				return true;
			}

			m_bHasAnyErrors = true;

			return false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return false;
		}
	}

	bool AnimationComponent::IsAnyAnimationPlaying()
	{
		SizeT count = m_Animation->GetAnimClipCount();

		bool isPlaying = false;

		if (count)
		{
			isPlaying = m_Animation->IsPlaying();

			return isPlaying;
		}
		else
		{
			return isPlaying;
		}
	}

	bool AnimationComponent::IsAnyAnimationPaused()
	{
		SizeT count = m_Animation->GetAnimClipCount();

		bool isPaused = false;

		if (count)
		{
			isPaused = m_Animation->IsPaused();

			return isPaused;
		}
		else
		{
			return isPaused;
		}
	}

	bool AnimationComponent::IsAnimationPlaying(const Resources::ResourceId& name)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		bool isPlaying = false;

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				isPlaying = m_Animation->IsPlaying(name);

				return isPlaying;
			}
			else
			{
				AnimStateParam asParam;
				asParam.name = name;

				IndexT findAS = m_AnimStateParam.FindIndex(name);
				if (findAS != InvalidIndex)
				{
					return false; 
				} 
				else
				{
					m_AnimStateParam.Add(name, asParam);

					return false;
				}
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return false;
		}
	}

	bool AnimationComponent::IsAnimationPaused(const Resources::ResourceId& name)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		bool isPaused = false;

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				isPaused = m_Animation->IsPaused(name);

				return isPaused;
			}
			else
			{
				AnimStateParam asParam;
				asParam.name = name;

				IndexT findAS = m_AnimStateParam.FindIndex(name);
				if (findAS != InvalidIndex)
				{
					return false; 
				} 
				else
				{
					m_AnimStateParam.Add(name, asParam);

					return false;
				}
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return false;
		}
	}


	void AnimationComponent::SetWrapMode(const Resources::ResourceId &name, int wrapMode)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->SetWrapMode(name, wrapMode);
			}

			AnimStateParam asParam;
			asParam.name		  = name;
			asParam.wrapMode      = wrapMode;
			asParam.isSetWrapMode = true;	

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.name			  = name;
				existedAS.wrapMode		  = wrapMode;
				existedAS.isSetWrapMode   = true;
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return;
		}
	}


	int AnimationComponent::GetWrapMode(const Resources::ResourceId& name)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				return m_Animation->GetWrapMode(name);
			}
			else
			{
				IndexT findAS = m_AnimStateParam.FindIndex(name);
				if (findAS != InvalidIndex)
				{
					AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
					return existedAS.wrapMode;
				} 
				else
				{
					return 2;
				}
			}

		}
		return 2;
	}

	void AnimationComponent::SetLayer(const Resources::ResourceId& name, int layer)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->SetLayer(name, layer);
			}

			AnimStateParam asParam;
			asParam.name	   = name;
			asParam.layer      = layer;
			asParam.isSetLayer = true;	

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.name            = name;
				existedAS.layer			  = layer;
				existedAS.isSetLayer	  = true;
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return;
		}
	}

	void AnimationComponent::SetTime(const Resources::ResourceId& name, float time)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->SetTime(name, time);
			}

			AnimStateParam asParam;
			asParam.name	   = name;
			asParam.localTime  = time;
			asParam.isSetTime  = true;	

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.name            = name;
				existedAS.localTime		  = time;
				existedAS.isSetTime	      = true;
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return;
		}
	}

	float AnimationComponent::GetTime(const Resources::ResourceId& name)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		float weight = 0.0f;

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				weight = m_Animation->GetWrapTime(name);
			}

		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());
		}

		return weight;
	}

	IndexT AnimationComponent::GetLayer(const Resources::ResourceId& name) 
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		IndexT layer = 0;

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				layer = m_Animation->GetLayer(name);
			}

		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());
		}

		return layer;
	}

	void AnimationComponent::SetAnimationSpeed(const Resources::ResourceId &name, float speed)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->SetPlayRate(name, speed);
			}

			AnimStateParam asParam;
			asParam.name	   = name;
			asParam.speed      = speed;
			asParam.isSetSpeed = true;	

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.name			  = name;
				existedAS.speed			  = speed;
				existedAS.isSetSpeed	  = true;
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return;
		}
	}

	void AnimationComponent::SetWeight(const Resources::ResourceId& name, float weight)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		weight = ClampWeightRange(weight);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->SetWeight(name, weight);
			}

			AnimStateParam asParam;
			asParam.name	    = name;
			asParam.curWeight   = weight;
			asParam.isSetWeight = true;	

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.name			  = name;
				existedAS.curWeight		  = weight;
				existedAS.isSetWeight	  = true;
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return;
		}
	}

	float AnimationComponent::GetWeight(const Resources::ResourceId& name)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		float weight = 0.0f;

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				weight = m_Animation->GetWeight(name);
			}

		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());
		}

		return weight;
	}

	void AnimationComponent::SetNormalizedTime(const Resources::ResourceId &name, float time)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->SetNormalizedTime(name, time);
			}

			AnimStateParam asParam;
			asParam.name				= name;
			asParam.normalizedTime		= time;
			asParam.isSetNormalizedTime = true;	

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS	  = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.name				  = name;
				existedAS.normalizedTime	  = time;
				existedAS.isSetNormalizedTime = true;	
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return;
		}
	}

	void AnimationComponent::SetAnimationEnable(const Resources::ResourceId& name, bool enable)
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				m_Animation->SetEnable(name, enable);
			}

			AnimStateParam asParam;
			asParam.name	    = name;
			asParam.enable		= enable;
			asParam.isSetEnable = true;	

			IndexT findAS = m_AnimStateParam.FindIndex(name);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.name			  = name;
				existedAS.enable		  = enable;
				existedAS.isSetEnable     = true;	
			} 
			else
			{
				m_AnimStateParam.Add(name, asParam);
			}

			m_bHasAnyErrors = false;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());

			m_bHasAnyErrors = true;

			return;
		}
	}

	const SizeT AnimationComponent::GetAnimationsCount() const
	{
		return m_AnimInfos.animMap.Size();
	}

	bool AnimationComponent::BuildToRootX()
	{

		Util::Array<Math::matrix44>& toParent = m_Animation->GetToParentTrans();

		if (toParent.IsEmpty() || m_ParentIndexVec.IsEmpty())
		{
			m_ParentIndexVec = m_Animation->GetNodeParentIndexVec();
			m_ParentNameVec = m_Animation->GetNodeNameVec();
			if(m_ParentIndexVec.IsEmpty() || m_ParentNameVec.IsEmpty())
				return false;
		}

		if ( !toParent.IsEmpty() && !IsUpdate() && !m_ToRootX.IsEmpty())
		{
			return true;
		}

		m_ToRootX.Clear(false);

		for (IndexT iNode = 0; iNode < toParent.Size(); ++iNode)
		{
			ushort indiceNodeParent = m_ParentIndexVec[iNode];

			if (indiceNodeParent != 0xFFFF)
			{
				Math::matrix44 toRootX = Math::matrix44::multiply( m_ToRootX[indiceNodeParent], toParent[iNode] );
				m_ToRootX.Append(toRootX);
			}
			else if (indiceNodeParent == 0xFFFF)
			{
				m_ToRootX.Append( toParent[iNode] );

			}
		}

		return true;
	}

	bool AnimationComponent::GetNodeTransform(const Util::String& nodeName, Math::matrix44& trans)
	{
		if (!m_bHasBuildToRootX)
		{
			//return false;
		}

		Util::Array<Math::matrix44>& toParent = m_Animation->GetToParentTrans();
		if(toParent.IsEmpty() && !IsAnyAnimationPaused() && !IsAnyAnimationPlaying())
		{
			//When every animation is stopped, create skeleton's default ToRoot, to make sure correct attach
			if(!HasBuildDefaultToRootX())
				BuildDefaultToRootX();

			Util::Dictionary<Util::String, Math::matrix44> defaultToRootX = m_Animation->GetDefaultToRootX();

			IndexT foundIndex = defaultToRootX.FindIndex(nodeName);
			if(foundIndex != InvalidIndex && foundIndex < defaultToRootX.Size())
			{
				trans = defaultToRootX.ValueAtIndex(foundIndex);
				return true;
			}
			else
			{
				return false;
			}
		}

		IndexT found = m_ParentNameVec.FindIndex(nodeName);

		if(found >= m_ToRootX.Size() )
		{
			return false;
		}
		else if (found != InvalidIndex)
		{
			trans = m_ToRootX[found];
			return true;
		} 
		else
		{
			if (m_bHasGotSkelTree && m_SkelTree.IsEmpty())
			{
				n_assert("No Such Node !");
				return false;
			} 
			else if (! m_bHasGotSkelTree)
			{
				return false;
			}
			else if ( m_bHasGotSkelTree && !m_SkelTree.IsEmpty())
			{
				found = m_SkelTree.FindIndex(nodeName);

				if (found == InvalidIndex)
				{
					n_assert("No Such Node !");
					return false;
				} 
				else
				{

					bool ret = GetAnimNodeTrans(nodeName, trans);

					return ret;
				}
			}

			return false;
		}
	}

	bool AnimationComponent::GetAnimNodeTrans(const Util::String& name, Math::matrix44& trans)
	{
		IndexT found = m_ParentNameVec.FindIndex(name);

		if (found != InvalidIndex)
		{
			trans =  Math::matrix44::multiply(m_ToRootX[found], trans);

			return true;
		} 
		else
		{
			Math::matrix44 parent;

			found = m_SkelTree.FindIndex(name);

			GPtr<SkelTreeData>& pData = m_SkelTree.ValueAtIndex(found);

			parent = Math::matrix44::transformation(pData->scale, pData->rot, pData->pos);

			trans = Math::matrix44::multiply(parent, trans);

			if (pData->parent.isvalid())
			{
				GetAnimNodeTrans( pData->parent->name, trans );
			} 

			return true;
		}
	}

	void AnimationComponent::SetSkelTree(Util::Dictionary< Util::String, GPtr<SkelTreeData> >& skelTree)
	{
		m_SkelTree = skelTree;
		m_bHasBuildDefaultToRootX = false;
	}

	void AnimationComponent::SetSkelTree( Util::Array< GPtr<SkelTreeData> >& skelTree )
	{
		m_SkelTreeArray = skelTree;
		m_Animation->SetSkelTree(skelTree);
		m_bHasBuildDefaultToRootX = false;
	}

	const float AnimationComponent::GetDurationTime(const Resources::ResourceId& Name)
	{
		ClipControl* cc = m_Animation->GetClipControl(Name);

		if (cc)
		{
			AnimationClip* pClip = cc->GetClip();
			if (pClip)
			{
				return pClip->GetClipDuration();
			}
		}

		return 0.0f;
	}

	void AnimationComponent::RemoveClip(const Resources::ResourceId& clipName)
	{
		StopAnimation(clipName);

		AnimationParamMap& animMap = m_AnimInfos.animMap;
		IndexT findAnim            = animMap.FindIndex(clipName);

		if (findAnim != InvalidIndex)
		{
			IndexT findAS = m_AnimStateParam.FindIndex(clipName);
			if (findAS != InvalidIndex)
			{
				AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
				existedAS.isSetSpeed	  = false;
				existedAS.isSetWrapMode	  = false;
			}
			animMap.EraseAtIndex(findAnim);
			m_Animation->RemoveAnimClip(clipName);
		}
		else
		{
			n_warning("Clip dose not exist!");
		}
	}

	float AnimationComponent::GetAnimationSpeed( const Resources::ResourceId& name )
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(name);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() == Resource::Loaded)
			{
				ClipControl* cc = m_Animation->GetClipControl(name);
				if (cc)
				{
					return cc->GetSpeed();
				}
			}
			else
			{
				IndexT findAS = m_AnimStateParam.FindIndex(name);
				if (findAS != InvalidIndex)
				{
					AnimStateParam& existedAS = m_AnimStateParam.ValueAtIndex(findAS);
					return existedAS.speed;
				} 
			}
			return 1;
		}
		else
		{
			n_warning("there is no '%s' animation! \n", name.Value());
			return 1;
		}
	}

	//------------------------------------------------------------------------
	void AnimationComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;
		// TODO:

		GPtr<AnimationComponent> pSource = pComponent.downcast<AnimationComponent>();
		n_assert(pSource.isvalid());

		const SizeT animCount = pSource->GetAnimationsCount();

		for (IndexT i = 0; i<animCount; ++i)
		{
			const Resources::ResourceId& animId = pSource->GetAnimResID(i);
			this->SetAnimationID(animId, 0);

			int warpMode = pSource->GetWrapMode(animId.AsString());
			this->SetWrapMode(animId.AsString(), warpMode);

			float speed = pSource->GetAnimationSpeed(animId.AsString());
			this->SetAnimationSpeed(animId.AsString(), speed);
		}

		this->SetDefaultAnimName(pSource->GetDefaultAnimName());
	}

	bool AnimationComponent::IsAllResourceLoaded()
	{
		return m_bAllLoaded;
	}

	void AnimationComponent::SetupAllResource()
	{
		//TODO:
		return;
	}

	void AnimationComponent::AddAttachedActor(const GPtr<Actor>& pActor, const Util::String& name)
	{
		if(!pActor.isvalid())
		{
			n_warning("Invalid actor cannot be attached.");
			return;
		}

		IndexT found = m_AttachedActors.FindIndex(pActor);

		if (found != InvalidIndex)
		{
			Util::String& nodeName = m_AttachedActors.ValueAtIndex(found).attachedSkelName;

			if (name != nodeName)
			{
				nodeName = name;
			}
		}
		else
		{
			AttachedActorInfo attachedActor;
			attachedActor.attachedSkelName = name;
			attachedActor.attachedActorTrans =  pActor->GetTransform();
			m_AttachedActors.Add(pActor, attachedActor);	
		}

		AddLocaterCom(pActor, name);

	}


	void AnimationComponent::AddToAttachedActorList( const GPtr<Actor>& pActor, const Util::String& name )
	{
		if(!pActor.isvalid())
		{
			n_warning("Invalid actor cannot be attached.");
			return;
		}

		IndexT found = m_AttachedActors.FindIndex(pActor);

		if (found != InvalidIndex)
		{
			return;
		}
		else
		{
			AttachedActorInfo attachedActor;
			attachedActor.attachedSkelName = name;
			attachedActor.attachedActorTrans =  pActor->GetTransform();
			m_AttachedActors.Add(pActor, attachedActor);	
		}
	}

	void AnimationComponent::RemoveAttachedActor(const GPtr<Actor>& pActor)
	{
		if(!pActor.isvalid())
		{
			n_warning("Cannot remove a invalid actor.");
			return;
		}

		IndexT found = m_AttachedActors.FindIndex(pActor);

		if (found != InvalidIndex)
		{
			//delete locaterCom
			RemoveLocaterCom(pActor);

			m_AttachedActors.EraseAtIndex(found);
		}
	}

	void AnimationComponent::RemoveAttachedActor( const Util::String skelName )
	{
		for(int i=m_AttachedActors.Size()-1; i>=0; --i)
		{
			if(m_AttachedActors.ValueAtIndex(i).attachedSkelName == skelName)
			{
				Actor* pActor = m_AttachedActors.KeyAtIndex(i);

				//delete locaterCom
				RemoveLocaterCom(pActor);

				m_AttachedActors.EraseAtIndex(i);
			}
		}
	}

	bool AnimationComponent::FindUsedBones(const GPtr<AnimationClip>& clip, const GPtr<SkeletonRes>& skelteon, const GPtr<Actor>& pActor)
	{

		GPtr<Component> skeleton = pActor->FindComponent(SkeletonComponent::RTTI);

		if(skeleton.isvalid())
		{
			GPtr<SkeletonComponent> pSkeletonCom   = skeleton.downcast<SkeletonComponent>();

			if(pSkeletonCom->IsSkelDirty())
			{
				return false;
			}

			const GPtr<SkeletonRes>& skeletonRes   = pSkeletonCom->GetSkeleton();

			if (skeletonRes.isvalid() && (skeletonRes->GetState() == Resource::Loaded))
			{
				if (! this->HasGotSkelTree() && !skeletonRes->IsSkelTreeEmpty())
				{
					this->SetSkelTree(skeletonRes->GetSkelTree());
					this->SetSkelTree(skeletonRes->GetSkelTreeArray());

					this->SetGetSkelTree(true);
				}
				const Util::Array<Util::String>& SkelNames       = skeletonRes->GetSkelNames();
				const Util::Array<ushort>& ParentIndex           = m_Animation->GetNodeParentIndexVec();
				const Util::Array<Util::String>& ParentNames     = m_Animation->GetNodeNameVec();
				const SizeT bonesCount                           = skeletonRes->GetBonesCount();
				Util::Dictionary<IndexT, Util::String> SkelPairs = skeletonRes->GetSkelKeyPairs();

				Util::Dictionary<IndexT, IndexT> usedboneIndex;
				Util::Array<IndexT> unusedboneIndex;

				for (IndexT iNode = 0; iNode < ParentIndex.Size(); ++iNode)
				{
					IndexT index = SkelNames.FindIndex(ParentNames[iNode]);

					if (index != InvalidIndex)
					{
						usedboneIndex.Add(iNode, index);
						SkelPairs.Erase(index);
					}
				}

				for (IndexT iBone = 0; iBone < SkelPairs.Size(); ++iBone)
				{
					IndexT remainBone = SkelNames.FindIndex(SkelPairs.ValueAtIndex(iBone));
					unusedboneIndex.Append(remainBone);
				}

				BoneMatrix boneMatrix;

				boneMatrix.used   = usedboneIndex;
				boneMatrix.unused = unusedboneIndex;

				IndexT found = m_UsedBonesIndex.FindIndex(clip->GetName());

				Util::Dictionary<GPtr<Actor>, BoneMatrix> actorBonesMatrix;
				actorBonesMatrix.Add(pActor, boneMatrix);
				if (found == InvalidIndex)
				{

					m_UsedBonesIndex.Add(clip->GetName(), actorBonesMatrix);
				}
				else
				{
					IndexT foundActor = m_UsedBonesIndex[clip->GetName()].FindIndex(pActor);
					if (foundActor == InvalidIndex)
					{

						m_UsedBonesIndex[clip->GetName()].Add(pActor, boneMatrix);
					}
					else
					{
						m_UsedBonesIndex[clip->GetName()] = actorBonesMatrix;
					}
				}
			}
		}

		bool hasFound = true;

		int childCount = pActor->GetChildCount();
		for(int childIndex=0; childIndex<childCount; ++childIndex)
		{
			GPtr<Actor> childActor = pActor->GetChild(childIndex);
			hasFound &= FindUsedBones(clip, NULL, childActor);
		}

		return hasFound;
	}

	void AnimationComponent::FindAttachedActor(const GPtr<Actor>& pActor)
	{
		if(!pActor.isvalid())
		{
			n_warning("Invalid actor.");
			return;
		}

		m_AttachedActors.Clear();

		//Find can attached actor
		int childCount = pActor->GetChildCount();

		for(int i = 0; i<childCount; ++i)
		{
			GPtr<Actor> childActor = pActor->GetChild(i);

			IndexT found = m_CanAttachedActor.FindIndex(childActor);
			if(found == InvalidIndex)
			{
				GPtr<Component> skeleton = childActor->FindComponent(SkeletonComponent::RTTI);
				GPtr<Component> skinmesh = childActor->FindComponent(SkinnedMeshRenderComponent::RTTI);
				//If actor has skeleton animation, it can not be attached
				if(!skeleton.isvalid() && !skinmesh.isvalid())
				{
					AddActorCanAttached(childActor);
				}
			}	
		}

		//Update the canattachedActors List
		for(int i = m_CanAttachedActor.Size()-1; i >=0; i--)
		{
			GPtr<Actor> actor = m_CanAttachedActor[i];
			if(NULL == actor)
				m_CanAttachedActor.EraseIndex(i);
			else
			{
				int fastid = actor->GetFastId();
				IndexT found = pActor->FindChildIndex(fastid);
				if(found == InvalidIndex)
					m_CanAttachedActor.EraseIndex(i);
			}
		}

		for(int i = 0; i<m_CanAttachedActor.Size(); ++i)
		{
			GPtr<Actor> childActor = m_CanAttachedActor[i];
			if(childActor.isvalid())
			{
				GPtr<Component> locater = childActor->FindComponent(LocaterComponent::RTTI);
				if(locater.isvalid())
				{
					GPtr<LocaterComponent> locaterCom = locater.downcast<LocaterComponent>();
					AttachedActorInfo attachedActor;
					attachedActor.attachedSkelName = locaterCom->GetAttachedSkelName();

					m_AttachedActors.Add(childActor, attachedActor);
				}
			}

		}

	}

	void AnimationComponent::FindAttachedActor()
	{
		//Use actor's GUID refind actor
		if(m_TempAttachedActors.Size() > 0)
		{
			m_AttachedActors.Clear();
			for(int i=0; i<m_TempAttachedActors.Size(); ++i)
			{
				Util::Guid guid = m_TempAttachedActors.KeyAtIndex(i);
				Actor *pActor = ActorManager::Instance()->FindActiveActorByGUID(guid);
				if(pActor == NULL)
					pActor = ActorManager::Instance()->FindActorByGUID(guid);
				m_AttachedActors.Add(pActor, m_TempAttachedActors.ValueAtIndex(i));

				///////////////////////////////////////////////
				//Use loaded attach data create LocaterComponent
				////////////////////////////////////////////////
				LoadLocaterCom(pActor, m_TempAttachedActors.ValueAtIndex(i).attachedSkelName);
			}
			m_TempAttachedActors.Clear();
		}

		FindAttachedActor(mActor);
	}


	void AnimationComponent::SetAttachedActors(Util::Dictionary<  GPtr<Actor>, AttachedActorInfo >& attachedActors)
	{
		m_AttachedActors = attachedActors;
	}

	void AnimationComponent::AddActorCanAttached( const GPtr<Actor>& pActor )
	{

		IndexT found = m_CanAttachedActor.FindIndex(pActor);

		if (found == InvalidIndex)
		{
			m_CanAttachedActor.Append(pActor);
		}
	}

	const GPtr<Actor>& AnimationComponent::GetCanAttachedActor( IndexT index )
	{
		if(index >= 0 && index < m_CanAttachedActor.Size())
		{
			return m_CanAttachedActor[index];
		}

		return App::Actor::NullActor;
	}

	void AnimationComponent::AddDefaultAttachedActor()
	{
		if(m_SkelTree.IsEmpty())
		{
			m_bNeedAddDefaultAttach = true;
		}
		else
		{
			FindAttachedActor();
			for(int i=0; i<m_CanAttachedActor.Size(); ++i)
			{
				const Util::String& name = m_CanAttachedActor[i]->GetName();

				IndexT foundIndex = m_SkelTree.FindIndex(name);
				if(foundIndex != InvalidIndex)
				{
					AddAttachedActor(m_CanAttachedActor[i], name);
				}
			}
			m_bNeedAddDefaultAttach = false;
		}

	}

	bool AnimationComponent::IsInCanAttachedList(GPtr<Actor> actor)
	{
		if(!actor.isvalid())
		{
			n_warning("Invalid actor.");
			return false;
		}

		if(m_CanAttachedActor.FindIndex(actor) != InvalidIndex)
			return true;
		GPtr<App::Component> skeleton = actor->FindComponent(App::SkeletonComponent::RTTI);
		GPtr<App::Component> skinmesh = actor->FindComponent(SkinnedMeshRenderComponent::RTTI);
		//If actor has skeleton animation, it can not be attached
		if(!skeleton.isvalid() && !skinmesh.isvalid())
		{
			return true;
		}
		return false;
	}

	void AnimationComponent::ClearAttachedActorList()
	{
		m_AttachedActors.Clear();
	}

	Util::Dictionary< Util::Guid, AttachedActorInfo > AnimationComponent::GetTempAttachedActors()
	{
		return m_TempAttachedActors;
	}

	void AnimationComponent::SetTempAttachedActors( Util::Dictionary< Util::Guid, AttachedActorInfo > tempAttach )
	{
		m_TempAttachedActors = tempAttach;
	}

	void AnimationComponent::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
	{
		const AnimationParamMap& animMap = m_AnimInfos.animMap;
		SizeT nCount = animMap.Size();
		Util::Array<Util::String> refIds;
		for (int i = 0; i < nCount; ++i)
		{
			list.Append(ReferenceResource());
			list.Back().id = animMap.KeyAtIndex(i);
		}
		Super::GetReferenceResourceId(list);
	}


	bool AnimationComponent::BuildDefaultToRootX()
	{
		bool ret = m_Animation->BuildDefaultToRootTrans();
		if(ret)
		{	
			m_bHasBuildDefaultToRootX = true;
			return true;
		}
		else
		{
			m_bHasBuildDefaultToRootX = false;
			return false;
		}
	}

	void AnimationComponent::AddLocaterCom( const GPtr<Actor>& pActor, const Util::String& attechedName)
	{
		if(!pActor.isvalid())
		{
			n_warning("Invalid actor cannot add LocaterComponent.");
			return;
		}

		GPtr<Component> locaterCom;
		locaterCom = pActor->FindComponent( LocaterComponent::RTTI );

		if( !locaterCom.isvalid())//add and reset Locater
		{
			GPtr<LocaterComponent> locaterComponent = LocaterComponent::Create();
			locaterCom = locaterComponent.upcast<Component>();
			pActor->AttachComponent(locaterCom);
			locaterComponent->SetAttachedSkelName(attechedName);

			locaterComponent->SetupLocater();
		}
		else //when load Locater
		{
			GPtr<LocaterComponent> locaterComponent = locaterCom.downcast<LocaterComponent>();
			locaterComponent->SetAttachedSkelName(attechedName);

			locaterComponent->SetupLocater();
		}
	}

	void AnimationComponent::LoadLocaterCom( const GPtr<Actor>& pActor, const Util::String& attechedName)
	{
		if(!pActor.isvalid())
		{
			n_warning("Invalid actor.");
			return;
		}

		GPtr<Component> locaterCom;
		locaterCom = pActor->FindComponent( LocaterComponent::RTTI );

		if( !locaterCom.isvalid())//add and reset Locater
		{
			GPtr<LocaterComponent> locaterComponent = LocaterComponent::Create();
			locaterCom = locaterComponent.upcast<Component>();
			pActor->AttachComponent(locaterCom);
			locaterComponent->SetAttachedSkelName(attechedName);

			locaterComponent->SetupLocater();
		}
		else //when load Locater
		{
			GPtr<LocaterComponent> locaterComponent = locaterCom.downcast<LocaterComponent>();
			locaterComponent->SetAttachedSkelName(attechedName);
		}
	}

	void AnimationComponent::RemoveLocaterCom(const GPtr<Actor>& pActor)
	{
		if(!pActor.isvalid())
		{
			n_warning("Invalid actor.");
			return;
		}

		GPtr<Component> locaterCom;
		locaterCom = pActor->FindComponent( LocaterComponent::RTTI );

		if(locaterCom.isvalid())
		{
			GPtr<LocaterComponent> locaterComponent = locaterCom.downcast<LocaterComponent>();
			locaterComponent->SetupLocater();
			pActor->RemoveComponent(locaterCom);
		}
	}

	void AnimationComponent::ReFindSkelTree()
	{
		if (! this->HasGotSkelTree())
		{
			int childCount = mActor->GetChildCount();
			for(int childIndex=0; childIndex<childCount; ++childIndex)
			{
				GPtr<Actor> childActor = mActor->GetChild(childIndex);

				GPtr<Component> skeleton = childActor->FindComponent(SkeletonComponent::RTTI);

				if(skeleton.isvalid())
				{
					GPtr<SkeletonComponent> pSkeletonCom   = skeleton.downcast<SkeletonComponent>();
					const GPtr<SkeletonRes>& skeletonRes   = pSkeletonCom->GetSkeleton();

					if (skeletonRes.isvalid() && (skeletonRes->GetState() == Resource::Loaded) && !skeletonRes->IsSkelTreeEmpty())
					{
						this->SetSkelTree(skeletonRes->GetSkelTree());
						this->SetSkelTree(skeletonRes->GetSkelTreeArray());

						this->SetGetSkelTree(true);
						break;
					}
				}
			}
		}
	}

	bool AnimationComponent::GetAnimLoaded( const Resources::ResourceId& animName )
	{
		AnimationParamMap& animMap = m_AnimInfos.animMap;

		IndexT findAnim = animMap.FindIndex(animName);

		if (findAnim != InvalidIndex)
		{
			AnimResParam& animParam = m_AnimInfos.animMap.ValueAtIndex(findAnim);

			if (animParam.animRes.isvalid() && animParam.animRes->GetState() != Resource::Failed)
			{
				if(animParam.animRes->GetResourceId() == ResourceManager::DefaultAnimationID)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}

		return false;
	}


}




