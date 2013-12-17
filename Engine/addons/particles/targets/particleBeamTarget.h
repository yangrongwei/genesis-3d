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
#ifndef __PARTICLE_BEAM_TARGET_H__
#define __PARTICLE_BEAM_TARGET_H__
#include "particles/particle_fwd_decl.h"
#include "particles/particletarget.h"
#include "particles/particle.h"


namespace Particles
{
	class ParticleBeamTarget: public ParticleTarget
	{
		__DeclareSubClass(ParticleBeamTarget, ParticleTarget );

	public:
		ParticleBeamTarget();
		virtual ~ParticleBeamTarget();

		ParticleTarget::TargetType GetTargetType(void) const;		

		void _updateParticle_Common( Particle* particle,IndexT t, ParticleVertexData* particleVertex, ushort* indicies , IndexT particleIndex,float v0=0.0f,float v1=1.0f);

		template<typename T>
		SizeT _updateTarget_Beam(GPtr<ParticlePool>& pool, ParticleVertexData* particleVertex, ushort* indicies, const T&  op );

		void _updateTarget(GPtr<ParticlePool>& pool, Timing::Time frameTime);

		bool _preparePrimitiveGroup(SizeT& verticesSizeInByte, SizeT& indicesSizeInByte);

		void SetMaxElements(SizeT _size);
		SizeT GetMaxElements() const;

		void SetUpdateInterval(Math::scalar);
		Math::scalar GetUpdateInterval() const;

		void SetNoiseXMin(Math::scalar);
		Math::scalar GetNoiseXMin() const;

		void SetNoiseXMax(Math::scalar);
		Math::scalar GetNoiseXMax() const;

		void SetNoiseYMin(Math::scalar);
		Math::scalar GetNoiseYMin() const;

		void SetNoiseYMax(Math::scalar);
		Math::scalar GetNoiseYMax() const;

		void SetNoiseZMin(Math::scalar);
		Math::scalar GetNoiseZMin() const;

		void SetNoiseZMax(Math::scalar);
		Math::scalar GetNoiseZMax() const;

		void SetDestPosition(Math::float3 _destPos);
		Math::float3 GetDestPosition()const;

	protected:

		SizeT						mMaxElements;			
		Math::scalar				mUpdateInterval;		
		Timing::Time				mTime;					

		Math::scalar				mNoiseXMin;
		Math::scalar				mNoiseXMax;
		Math::scalar				mNoiseYMin;
		Math::scalar				mNoiseYMax;
		Math::scalar				mNoiseZMin;
		Math::scalar				mNoiseZMax;
		Math::float3				mDestPos;

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


	//------------------------------------------------------------------------
	inline void ParticleBeamTarget::SetMaxElements(SizeT _size)
	{
		mMaxElements = _size;
	}
	//------------------------------------------------------------------------
	inline SizeT ParticleBeamTarget::GetMaxElements() const
	{
		return mMaxElements;
	}
	//------------------------------------------------------------------------
	inline void ParticleBeamTarget::SetUpdateInterval(Math::scalar _interval)
	{
		mUpdateInterval = _interval;
	}
	//------------------------------------------------------------------------
	inline Math::scalar ParticleBeamTarget::GetUpdateInterval() const
	{
		return mUpdateInterval;
	}
	//------------------------------------------------------------------------
	inline void ParticleBeamTarget::SetNoiseXMin(Math::scalar _noiseXMin)
	{
		mNoiseXMin = _noiseXMin;
	}
	//------------------------------------------------------------------------
	inline Math::scalar ParticleBeamTarget::GetNoiseXMin() const
	{
		return mNoiseXMin;
	}
	//------------------------------------------------------------------------
	inline void ParticleBeamTarget::SetNoiseXMax(Math::scalar _noiseXMax)
	{
		mNoiseXMax = _noiseXMax;
	}
	//------------------------------------------------------------------------
	inline Math::scalar ParticleBeamTarget::GetNoiseXMax() const
	{
		return mNoiseXMax;
	}
	//------------------------------------------------------------------------

	inline void ParticleBeamTarget::SetNoiseYMin(Math::scalar _noiseYMin)
	{
		mNoiseYMin = _noiseYMin;
	}
	//------------------------------------------------------------------------
	inline Math::scalar ParticleBeamTarget::GetNoiseYMin() const
	{
		return mNoiseYMin;
	}
	//------------------------------------------------------------------------
	inline void ParticleBeamTarget::SetNoiseYMax(Math::scalar _noiseYMax)
	{
		mNoiseYMax = _noiseYMax;
	}
	//------------------------------------------------------------------------
	inline Math::scalar ParticleBeamTarget::GetNoiseYMax() const
	{
		return mNoiseYMax;
	}
	//------------------------------------------------------------------------

	inline void ParticleBeamTarget::SetNoiseZMin(Math::scalar _noiseZMin)
	{
		mNoiseZMin = _noiseZMin;
	}
	//------------------------------------------------------------------------
	inline Math::scalar ParticleBeamTarget::GetNoiseZMin() const
	{
		return mNoiseZMin;
	}
	//------------------------------------------------------------------------
	inline void ParticleBeamTarget::SetNoiseZMax(Math::scalar _noiseZMax)
	{
		mNoiseZMax = _noiseZMax;
	}
	//------------------------------------------------------------------------
	inline Math::scalar ParticleBeamTarget::GetNoiseZMax() const
	{
		return mNoiseZMax;
	}
	//------------------------------------------------------------------------
	inline void ParticleBeamTarget::SetDestPosition(Math::float3 _destPos)
	{
		mDestPos = _destPos;
	}
	//------------------------------------------------------------------------
	inline Math::float3 ParticleBeamTarget::GetDestPosition() const
	{
		return mDestPos;
	}
}

#endif // __PARTICLE_BEAM_TARGET_H__
