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
#ifndef __PARTICLE_RIBBONTRAIL_TARGET_H__
#define __PARTICLE_RIBBONTRAIL_TARGET_H__
#include "particles/particle_fwd_decl.h"
#include "particles/particletarget.h"
#include "particles/particle.h"

namespace Particles
{
	class RibbonTrailTarget: public ParticleTarget
	{
		__DeclareSubClass(RibbonTrailTarget, ParticleTarget );

		//----------------------------------------------------------------------


	public:
		RibbonTrailTarget();
		virtual ~RibbonTrailTarget();

		ParticleTarget::TargetType GetTargetType(void) const;

		void _updateParticle_Common( Particle* particle,IndexT t, ParticleVertexData* particleVertex, ushort* indicies , IndexT particleIndex, float v0 = 0.0f, float v1 = 1.0f );

		template<typename T>
		SizeT _updateTarget_Trail(GPtr<ParticlePool>& pool, ParticleVertexData* particleVertex, ushort* indicies, const T&  op );

		void _updateTarget(GPtr<ParticlePool>& pool, Timing::Time frameTime);

		bool _preparePrimitiveGroup(SizeT& verticesSizeInByte, SizeT& indicesSizeInByte);

		void SetMaxElements(SizeT _size);
		SizeT GetMaxElements() const;

		void SetColorChange(const Math::float4& _distance);
		const Math::float4& GetColorChange() const;

		void SetTrailLength(Math::scalar _length);
		Math::scalar GetTrailLength() const;

		void SetColorGraded(bool _grade);
		bool IsColorGraded() const;


	protected:
		
		bool m_TransformChanged;
		bool m_ColorGraded;

		SizeT				mMaxElements;
		Math::scalar        mTrailLength;					
		Math::scalar		mPerLength;

		Util::Array<Math::float3> mPositions;					
		Timing::Time              mTimeSpace;					
		Math::scalar			  mUpdateInternal;

		Math::float4		mColorChange;

		SizeT				mCurQuato;

	public:
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		// copy 
		virtual void CopyFrom( const ParticleTargetPtr& target );


	};

	//--------------------------------------------------------------------------------------
	inline void RibbonTrailTarget::SetMaxElements(SizeT _size)
	{
		mMaxElements = _size;
		mPerLength = (Math::scalar)(mTrailLength * 1.0f/mMaxElements);
	}
	//--------------------------------------------------------------------------------------
	inline SizeT RibbonTrailTarget::GetMaxElements() const
	{
		return mMaxElements;
	}

	//--------------------------------------------------------------------------------------
	inline void RibbonTrailTarget::SetColorChange(const Math::float4& _distance)
	{
		mColorChange = _distance;
	}
	//--------------------------------------------------------------------------------------
	inline const Math::float4& RibbonTrailTarget::GetColorChange() const
	{
		return mColorChange;
	}
	//--------------------------------------------------------------------------------------
	inline void RibbonTrailTarget::SetTrailLength(Math::scalar _length)
	{
		mTrailLength = _length;
		mPerLength = (Math::scalar)(mTrailLength * 1.0f /mMaxElements);
	}
	//--------------------------------------------------------------------------------------
	inline Math::scalar RibbonTrailTarget::GetTrailLength() const
	{
		return mTrailLength;
	}
	//--------------------------------------------------------------------------------------
	inline void RibbonTrailTarget::SetColorGraded(bool _grade)
	{
		m_ColorGraded = _grade;
	}
	//--------------------------------------------------------------------------------------
	inline bool RibbonTrailTarget::IsColorGraded() const
	{
		return m_ColorGraded;
	}
}

#endif // __PARTICLE_RIBBONTRAIL_TARGET_H__
