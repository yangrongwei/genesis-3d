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

#ifndef __animationnode_H__
#define __animationnode_H__
#include "core/refcounted.h"
#include "math/curve.h"
#include "util/stringatom.h"


namespace Animations
{
	typedef Math::Float3fCurve    TransCurve;
	typedef Math::Float3fCurve    ScaleCurve;
	typedef Math::QuaternionCurve RotateCurve;

	///In one game,depends on made in 3dsmax or maya, the node names are usually same
	typedef Util::StringAtom AnimNodeID;

	class AnimationNode: public Core::RefCounted
	{
		__DeclareClass(AnimationNode);
	public:
		AnimationNode();
		virtual ~AnimationNode();

		/// get the ID of AnimationNode
		const AnimNodeID& GetID(void) const;

		/// set the ID of AnimationNode
		void SetID(const AnimNodeID& id);

		/// get the translate Curve
		const TransCurve& GetTransCurve(void) const;

		/// get the translate curve
		TransCurve& GetTransCurve(void);

		/// set the translate curve
		void SetTransCurve(const TransCurve& curve);

		/// get the scale curve
		const ScaleCurve& GetScaleCurve(void) const;

		/// get the scale curve
		ScaleCurve& GetScaleCurve(void);

		/// set the scale curve
		void SetScaleCurve(const ScaleCurve& curve);

		/// get the rotate curve
		const RotateCurve& GetRotateCurve(void) const;

		/// get the rotate curve
		RotateCurve& GetRotateCurve(void);

		/// set the rotate curve
		void SetRotateCurve(const RotateCurve& curve);

		/// the min of the begin time of each curve
		float GetBeginTime(void) const;

		/// the max of the end time of each curve
		float GetEndTime(void) const;

		/// Calculate Runtime Size
		virtual SizeT CalculateRuntimeSize() const;

		/// Set Parent Index
		void  SetParentIndex(unsigned short index);

		/// Get Parent Index
		const unsigned short GetParentIndex() const;

		/// Set Node BeginTime
		void SetNodeBeginTime(float time);

		/// Set Node EndTime
		void SetNodeEndTime(float time);

		float GetNodeTimeSpan();

		const float GetNodeBeginTime() const;

		const float GetNodeEndTime() const;

		void SetDefaultNodeTrans(const Math::float3& trans);

		void SetDefaultNodeScale(const Math::float3& scale);

		void SetDefaultNodeRot(const Math::quaternion& rot);

		const Math::float3& GetDefaultNodeTrans() const;

		const Math::float3& GetDefaultNodeScale() const;

		const Math::quaternion& GetDefaultNodeRot() const;

		void SetMask(unsigned int mask);

		const unsigned int& GetMask() const;

		const Math::float3& GetNodeTransByIndex(IndexT index) const;

		const Math::float3& GetNodeScaleByIndex(IndexT index) const;

		const Math::quaternion& GetNodeRotByIndex(IndexT index) const;

	protected:
		AnimNodeID mID;
		TransCurve mTransCurve;
		ScaleCurve mScaleCurve;
		RotateCurve mRotateCurve;

		Math::float3     m_DefaultTrans;
		Math::float3     m_DefaultScale;
		Math::quaternion m_DefaultRot;

		unsigned short m_ParentIndex;
		unsigned int   m_StateMask;

		float m_BeginTime;
		float m_EndTime;

	public:
		static GPtr<AnimationNode> NullNode;

		GPtr<AnimationNode> m_Parent;
	};
	//------------------------------------------------------------------------
	inline
		const AnimNodeID& 
		AnimationNode::GetID(void) const
	{
		return mID;
	}
	//------------------------------------------------------------------------
	inline 
		void 
		AnimationNode::SetID(const AnimNodeID& id)
	{
		mID = id;
	}
	//------------------------------------------------------------------------
	inline 
		const TransCurve& 
		AnimationNode::GetTransCurve(void) const
	{
		return mTransCurve;
	}
	//------------------------------------------------------------------------
	inline 
		TransCurve& 
		AnimationNode::GetTransCurve(void)
	{
		return mTransCurve;
	}
	//------------------------------------------------------------------------
	inline 
		void 
		AnimationNode::SetTransCurve(const TransCurve& curve)
	{
		mTransCurve = curve;
	}
	//------------------------------------------------------------------------
	inline 
		const ScaleCurve& 
		AnimationNode::GetScaleCurve(void) const
	{
		return mScaleCurve;
	}
	//------------------------------------------------------------------------
	inline 
		ScaleCurve& 
		AnimationNode::GetScaleCurve(void)
	{
		return mScaleCurve;
	}
	//------------------------------------------------------------------------
	inline 
		void 
		AnimationNode::SetScaleCurve(const ScaleCurve& curve)
	{
		mScaleCurve = curve;
	}
	//------------------------------------------------------------------------
	inline 
		const RotateCurve& 
		AnimationNode::GetRotateCurve(void) const
	{
		return mRotateCurve;
	}
	//------------------------------------------------------------------------
	inline 
		RotateCurve& 
		AnimationNode::GetRotateCurve(void)
	{
		return mRotateCurve;
	}
	//------------------------------------------------------------------------
	inline 
		void 
		AnimationNode::SetRotateCurve(const RotateCurve& curve)
	{
		mRotateCurve = curve;
	}

	//------------------------------------------------------------------------
	inline void AnimationNode::SetParentIndex(unsigned short index)
	{
		m_ParentIndex = index;
	}

	//------------------------------------------------------------------------
	inline const unsigned short AnimationNode::GetParentIndex() const
	{
		return m_ParentIndex;
	}

	//------------------------------------------------------------------------
	inline void AnimationNode::SetNodeBeginTime(float time)
	{
		m_BeginTime = time;
	}

	//------------------------------------------------------------------------
	inline void AnimationNode::SetNodeEndTime(float time)
	{
		m_EndTime = time;
	}

	//------------------------------------------------------------------------
	inline float AnimationNode::GetNodeTimeSpan()
	{
		return m_EndTime - m_BeginTime;
	}

	//------------------------------------------------------------------------
	inline const float AnimationNode::GetNodeBeginTime() const
	{
		return m_BeginTime;
	}

	//------------------------------------------------------------------------
	inline const float AnimationNode::GetNodeEndTime() const
	{
		return m_EndTime;
	}

	//------------------------------------------------------------------------
	inline void AnimationNode::SetDefaultNodeTrans(const Math::float3 &trans)
	{
		m_DefaultTrans = trans;
	}

	//------------------------------------------------------------------------
	inline void AnimationNode::SetDefaultNodeScale(const Math::float3& scale)
	{
		m_DefaultScale = scale;
	}

	//------------------------------------------------------------------------
	inline void AnimationNode::SetDefaultNodeRot(const Math::quaternion &rot)
	{
		m_DefaultRot = rot;
	}

	//------------------------------------------------------------------------
	inline const Math::float3& AnimationNode::GetDefaultNodeTrans() const
	{
		return m_DefaultTrans;
	}

	//------------------------------------------------------------------------
	inline const Math::float3& AnimationNode::GetDefaultNodeScale() const
	{
		return m_DefaultScale;
	}

	//------------------------------------------------------------------------
	inline const Math::quaternion& AnimationNode::GetDefaultNodeRot() const
	{
		return m_DefaultRot;
	}

	//------------------------------------------------------------------------
	inline void AnimationNode::SetMask(unsigned int mask)
	{
		m_StateMask = mask;
	}

	//------------------------------------------------------------------------
	inline const unsigned int& AnimationNode::GetMask() const
	{
		return m_StateMask;
	}
}

#endif // __animationnode_H__
