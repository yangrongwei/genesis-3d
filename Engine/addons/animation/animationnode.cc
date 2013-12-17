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
#include "animation/animationnode.h"

namespace Animations
{
	// do not modify 'ANDS', will be storage
	__ImplementClass( Animations::AnimationNode, 'ANDS', Core::RefCounted);
	GPtr<AnimationNode> AnimationNode::NullNode(0);
	//------------------------------------------------------------------------
	AnimationNode::AnimationNode()
	{
		m_StateMask = 0.0f;
		m_ParentIndex = 0;
	}
	//------------------------------------------------------------------------
	AnimationNode::~AnimationNode()
	{
		mTransCurve.ClearFrames();
		mScaleCurve.ClearFrames();
		mRotateCurve.ClearFrames();
	}
	//------------------------------------------------------------------------
	float AnimationNode::GetBeginTime(void) const
	{
		float t = Math::n_min( mTransCurve.GetBeginTime(), mScaleCurve.GetBeginTime() );
		t = Math::n_min( t, mRotateCurve.GetBeginTime() );
		return t;
	}
	//------------------------------------------------------------------------
	float AnimationNode::GetEndTime(void) const
	{
		float t = Math::n_max( mTransCurve.GetEndTime(), mScaleCurve.GetEndTime() );
		t = Math::n_max( t, mRotateCurve.GetEndTime() );
		return t;
	}
	//------------------------------------------------------------------------
	SizeT AnimationNode::CalculateRuntimeSize() const
	{
		SizeT size = 0;
		{
			size += sizeof( TransCurve );
			const TransCurve::Container& container = mTransCurve.GetContainer();
			size += ( container.Size() * sizeof( TransCurve::Container::value_type ) );
		}
		{
			size += sizeof( ScaleCurve );
			const ScaleCurve::Container& container = mScaleCurve.GetContainer();
			size += ( container.Size() * sizeof( ScaleCurve::Container::value_type ) );
		}
		{
			size += sizeof( RotateCurve );
			const RotateCurve::Container& container = mRotateCurve.GetContainer();
			size += ( container.Size() * sizeof( RotateCurve::Container::value_type ) );
		}

		return size;
	}

	const Math::float3& AnimationNode::GetNodeTransByIndex( IndexT index ) const
	{
		int keyFrameCount = mTransCurve.GetKeyFrameCount();
		if(index >= keyFrameCount || index < 0)
			return m_DefaultTrans;
		else
			return mTransCurve.GetKeyFrame(index).GetValue();
	}

	const Math::float3& AnimationNode::GetNodeScaleByIndex( IndexT index ) const
	{
		int keyFrameCount = mScaleCurve.GetKeyFrameCount();
		if(index >= keyFrameCount || index < 0)
			return m_DefaultScale;
		else
			return mScaleCurve.GetKeyFrame(index).GetValue();
	}

	const Math::quaternion& AnimationNode::GetNodeRotByIndex( IndexT index ) const
	{
		int keyFrameCount = mRotateCurve.GetKeyFrameCount();
		if(index >= keyFrameCount || index < 0)
			return m_DefaultRot;
		else
			return mRotateCurve.GetKeyFrame(index).GetValue();
	}

}
