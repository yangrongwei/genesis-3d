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
#ifndef __PARTICLE_RANDOMISER_AFFECTOR_H__
#define __PARTICLE_RANDOMISER_AFFECTOR_H__
#include "particles/particle_fwd_decl.h"
#include "particles/particleaffector.h"

namespace Particles
{
	class RandomiserAffector: public ParticleAffector
	{
		__DeclareSubClass( RandomiserAffector, ParticleAffector);

	public:
		static const Math::float3 DEFAULT_MAX_DEVIATION;
		static const Math::scalar DEFAULT_TIME_STEP;
		static const bool DEFAULT_RANDOM_DIRECTION;

	public:

		RandomiserAffector();
		virtual ~RandomiserAffector(){};

		Math::scalar GetMaxDeviationX(void) const;
		void SetMaxDeviationX(const Math::scalar maxDeviationX);

		Math::scalar GetMaxDeviationY(void) const;
		void SetMaxDeviationY(const Math::scalar maxDeviationZ);

		Math::scalar GetMaxDeviationZ(void) const;
		void SetMaxDeviationZ(const Math::scalar maxDeviationZ);

		Math::scalar GetTimeStep(void) const;
		void SetTimeStep(const Math::scalar timeStep);

		bool IsRandomDirection(void) const;
		void SetRandomDirection(bool randomDirection);

		virtual void _preProcessParticles();

		virtual void _affect(Particle* particle);

		virtual void _postProcessParticles();

	protected:
		Math::scalar mMaxDeviationX;
		Math::scalar mMaxDeviationY;
		Math::scalar mMaxDeviationZ;
		Math::scalar mTimeSinceLastUpdate;
		Math::scalar mTimeStep;
		bool mRandomDirection;
		bool mUpdate;


	public:
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		// copy 
		virtual void CopyFrom( const ParticleAffectorPtr& affector );
	};


	//-----------------------------------------------------------------------
	inline Math::scalar RandomiserAffector::GetMaxDeviationX(void) const
	{
		return mMaxDeviationX;
	}
	//-----------------------------------------------------------------------
	inline void RandomiserAffector::SetMaxDeviationX(Math::scalar maxDeviationX)
	{
		mMaxDeviationX = maxDeviationX;
	}
	//-----------------------------------------------------------------------
	inline Math::scalar RandomiserAffector::GetMaxDeviationY(void) const
	{
		return mMaxDeviationY;
	}
	//-----------------------------------------------------------------------
	inline void RandomiserAffector::SetMaxDeviationY(Math::scalar maxDeviationY)
	{
		mMaxDeviationY = maxDeviationY;
	}
	//-----------------------------------------------------------------------
	inline Math::scalar RandomiserAffector::GetMaxDeviationZ(void) const
	{
		return mMaxDeviationZ;
	}
	//-----------------------------------------------------------------------
	inline void RandomiserAffector::SetMaxDeviationZ(Math::scalar maxDeviationZ)
	{
		mMaxDeviationZ = maxDeviationZ;
	}
	//-----------------------------------------------------------------------
	inline Math::scalar RandomiserAffector::GetTimeStep(void) const
	{
		return mTimeStep;
	}
	//-----------------------------------------------------------------------
	inline void RandomiserAffector::SetTimeStep(Math::scalar timeStep)
	{
		mTimeStep = timeStep;
		mTimeSinceLastUpdate = timeStep;
	}
	//-----------------------------------------------------------------------
	inline bool RandomiserAffector::IsRandomDirection(void) const
	{
		return mRandomDirection;
	}
	//-----------------------------------------------------------------------
	inline void RandomiserAffector::SetRandomDirection(bool randomDirection)
	{
		mRandomDirection = randomDirection;
	}
}
#endif