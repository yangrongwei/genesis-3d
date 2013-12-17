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

#include "math/matrix44.h"
#include "math/float3.h"
#include "math/quaternion.h"

//#include "AnimationState.h"
#include "resource/skeletonres.h"

#include "animation/AnimationLayer.h"
#include "animation/ClipControl.h"
//#include "animation/AnimationState.h"

namespace Animations
{
	struct CheckedNode
	{
		Util::String	  nodeName;
		ushort			  parentIndex;
		Math::float3      defPosition;
		Math::quaternion  defRotation;
		Math::float3      defScale;
	};

	class Animation : public Core::RefCounted
	{
		__DeclareClass(Animation);

	public:
		typedef Util::Array< GPtr<AnimationClip> >  AnimClips;
		typedef Util::Array< ClipControl*>  ClipControls;
		typedef Util::Array< AnimationLayer* >  AnimationLayers;

		enum QueueMode
		{
			CompleteOthers = 0, 
			PlayNow = 2
		};

		Animation();
		~Animation();

		void   AddAnimClip(const GPtr<AnimationClip>& animClip);
		void   RemoveAnimClip(const Resources::ResourceId& clipName);

		AnimClips&  GetAnimClips();

		int GetAnimClipCount() const; 

		void PlayAnim(const Resources::ResourceId& name, int playMode = ClipControl::StopSameAnimLayer);

		void Stop();
		void Stop(const Resources::ResourceId& name);

		bool IsPlaying();
		bool IsPaused();
		bool IsPlaying(const Resources::ResourceId& name);
		bool IsPaused(const Resources::ResourceId& name);

		void CrossFading(const Resources::ResourceId& name, int playMode, float fadingTime = 0.3);

		void  Blending(const Resources::ResourceId& name, float targetWeight, float time);

		void SetWrapMode(const Resources::ResourceId& name, int wrapMode);
		int	 GetWrapMode(const Resources::ResourceId& name);

		void SetLayer(const Resources::ResourceId& name, int layer);
		int  GetLayer(const Resources::ResourceId& name);

		void SetPlayRate(const Resources::ResourceId& name, float rate);

		void SetNormalizedTime(const Resources::ResourceId& name, float time);

		void  SetWeight(const Resources::ResourceId& name, float weight);
		float GetWeight(const Resources::ResourceId& name);

		void SetEnable(const Resources::ResourceId& name, bool enable);
		bool IsEnable(const Resources::ResourceId& name);

		void  SetTime(const Resources::ResourceId& name, float time);
		float GetWrapTime(const Resources::ResourceId& name);

		ClipControl* GetClipControl(const Resources::ResourceId& name) const;
		Util::Array<Math::matrix44>& GetToParentTrans();
		const Util::Array<ushort>& GetNodeParentIndexVec() const;
		const Util::Array<Util::String>& GetNodeNameVec()  const;

		bool  UpdateAnimation(float time);

		void  AddAffectedNodes(const Resources::ResourceId& stateName, const Util::String& nodeName, bool recursive);
		void  RemoveAffectedNodes(const Resources::ResourceId& stateName, const Util::String& nodeName, bool recursive);

		const bool IsUpdate() const;

		void  Pause(const Resources::ResourceId& name);
		void  Resume(const Resources::ResourceId& name);

		bool IsAnimNodeAffected(const Resources::ResourceId& stateName, const Util::String& nodeName);

		void ClientAdd();

		void ClientSub();

		int GetClientCount() const;

		bool BuildDefaultToRootTrans();

		const Util::Dictionary<Util::String, Math::matrix44>& GetDefaultToRootX() const;

		//Set skelnode tree, build CheckedNode¡¢NodeName and NodeParentIndex array
		void SetSkelTree(const Util::Array< GPtr<Resources::SkelTreeData> >& skelTree);

	private:

		enum NoName
		{
			DefaultLayer = 0,
		};

		void sample();
		void buildControl(AnimationClip* clip, AnimationLayer* layer);
		AnimationLayer* buildLayer(int index);
		AnimationLayer* findLayer(int index) const;
		AnimationClip* findClip(const Resources::ResourceId& name) const;
		ClipControl* findControl(const Resources::ResourceId& name) const;
		int findClipIndex(const Resources::ResourceId& name) const;
		void buildLayerWeight(const ClipControls& activeControls, int nodeCount);
		template<bool check_layer>
		void blendControl(const ClipControl* cc, int nodeCount);
		void blendFrameData(int bone_index, float take_in_free, const Math::float3& pos, const Math::quaternion& rotate, const Math::float3& scale);
		void clearClipControls();
		void clearAnimClips();
		void clearLayers();


		AnimClips            m_AnimClips;
		ClipControls		 m_ClipControls;
		AnimationLayers		 m_AnimationLayers;	

		Util::Array<ushort>				m_NodeParentIndexVec;
		Util::Array<Util::String>		m_NodeNameVec;
		Util::Array< CheckedNode >		m_CheckedNodeList;
		Util::Dictionary<Util::String, Math::matrix44>	  m_DefaultToRootX;

		//--------------------------------- temp data. ---------------------------------
		Util::Array<Math::matrix44>   m_ToParentTrans;
		Util::Array<Math::float3>     m_SampledTrans;
		Util::Array<Math::float3>     m_SampledScale;
		Util::Array<Math::quaternion> m_SampledRotation;
		Util::Array<float>			  m_FreeWeights;
		Util::Array<float>			  m_LayerWeights;
		//-------------------------------------------------------------------------------


		GPtr<AnimationClip>			m_CurrentAnimClip;
		int		m_ClientCount;//Use for record this animation's user count
		bool	m_bUpdateResult;
		bool	m_bDirty;

	};

	inline Animation::AnimClips& Animation::GetAnimClips()
	{
		return m_AnimClips;
	}

	inline Util::Array<Math::matrix44>& Animation::GetToParentTrans()
	{
		return m_ToParentTrans;
	}

	inline ClipControl* Animation::GetClipControl(const Resources::ResourceId& name) const
	{
		return findControl(name);
	}

	inline const Util::Array<ushort>& Animation::GetNodeParentIndexVec() const
	{
		return m_NodeParentIndexVec;
	}

	inline const Util::Array<Util::String>& Animation::GetNodeNameVec() const
	{
		return m_NodeNameVec;
	}

	inline const bool Animation::IsUpdate() const
	{
		return m_bUpdateResult;
	}

	inline void Animation::ClientAdd()
	{
		++m_ClientCount;
	}

	inline void Animation::ClientSub()
	{
		--m_ClientCount;
		n_assert(-1 < m_ClientCount);
	}

	inline int Animation::GetClientCount() const
	{
		return m_ClientCount;
	}

	inline const Util::Dictionary<Util::String, Math::matrix44>& Animation::GetDefaultToRootX() const
	{
		return m_DefaultToRootX;
	}

}