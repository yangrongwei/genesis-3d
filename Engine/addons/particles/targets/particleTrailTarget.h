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
#ifndef __PARTICLE_TRAIL_TARGET_H__
#define __PARTICLE_TRAIL_TARGET_H__
#include "particles/particle_fwd_decl.h"
#include "particles/particletarget.h"
#include "particles/particle.h"

namespace Particles
{
	class ParticleTrailTarget : public ParticleTarget
	{
		__DeclareSubClass(ParticleTrailTarget, ParticleTarget );

	public:
		ParticleTrailTarget();
		virtual ~ParticleTrailTarget();

		ParticleTarget::TargetType GetTargetType(void) const;

		void _updateParticle_Common( Particle* particle,IndexT t, ParticleVertexData* particleVertex, ushort* indicies , IndexT particleIndex, float v0 = 0.0f, float v1 = 1.0f );

		template<typename T>
		SizeT _updateTarget_Trail(GPtr<ParticlePool>& pool, ParticleVertexData* particleVertex, ushort* indicies, const T&  op );

		void _updateTarget(GPtr<ParticlePool>& pool, Timing::Time frameTime);

		bool _preparePrimitiveGroup(SizeT& verticesSizeInByte, SizeT& indicesSizeInByte);

		void SetMaxElements(SizeT _size);
		SizeT GetMaxElements() const;

		void SetTrailLength(float _length);
		float GetTrailLength() const;

		void SetAlphaLife(float _alphaLife);
		float GetAlphaLife() const;

		void SetAmplitude(float amplitude);
		float GetAmplitude() const;

		void SetWaveLength(float waveLength);
		float GetWaveLength() const;

		void SetAmplitudeLife(float life);
		float GetAmplitudeLife() const;

		virtual Math::MinMaxCurve* getMinMaxCurve(ParticleCurveType pct);

	private:
		SizeT				mMaxElements;
		float               mTrailLength;				
		Math::scalar		mAlphaLife;						
		Math::scalar		mAmplitude;					
		Math::scalar		mWaveLength;					
		Math::scalar		mAmplitudeLife;				

		Math::MinMaxCurve			mLineColorA;
		Math::MinMaxCurve			mLineColorR;
		Math::MinMaxCurve			mLineColorG;
		Math::MinMaxCurve			mLineColorB;

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
	inline void ParticleTrailTarget::SetMaxElements(SizeT _size)
	{
		mMaxElements = _size;
	}
	//--------------------------------------------------------------------------------------
	inline SizeT ParticleTrailTarget::GetMaxElements() const
	{
		return mMaxElements;
	}
	//--------------------------------------------------------------------------------------
	inline void ParticleTrailTarget::SetTrailLength(float _length)
	{
		mTrailLength = _length;
	}
	//--------------------------------------------------------------------------------------
	inline float ParticleTrailTarget::GetTrailLength() const
	{
		return mTrailLength;
	}
	//--------------------------------------------------------------------------------------
	inline void ParticleTrailTarget::SetAlphaLife(float _alphaLife)
	{
		mAlphaLife = Math::n_clamp(_alphaLife,0.0f,1.0f);
	}
	//---------------------------------------------------------------------------------------
	inline float ParticleTrailTarget::GetAlphaLife() const
	{
		return mAlphaLife;
	}
	//--------------------------------------------------------------------------------------
	inline void ParticleTrailTarget::SetAmplitude(float amplitude)
	{
		mAmplitude = amplitude;
	}
	//---------------------------------------------------------------------------------------
	inline float ParticleTrailTarget::GetAmplitude() const
	{
		return mAmplitude;
	}
	//--------------------------------------------------------------------------------------
	inline void ParticleTrailTarget::SetWaveLength(float waveLength)
	{
		mWaveLength = waveLength;
	}
	//---------------------------------------------------------------------------------------
	inline float ParticleTrailTarget::GetWaveLength() const
	{
		return mWaveLength;
	}
	//--------------------------------------------------------------------------------------
	inline void ParticleTrailTarget::SetAmplitudeLife(float life)
	{
		mAmplitudeLife = life;
	}
	//---------------------------------------------------------------------------------------
	inline float ParticleTrailTarget::GetAmplitudeLife() const
	{
		return mAmplitudeLife;
	}
}

#endif // __PARTICLE_RIBBON_TARGET_H__