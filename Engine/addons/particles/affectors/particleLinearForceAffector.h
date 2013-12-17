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
#ifndef __PARTICLE_LINEARFORCE_AFFECTOR_H__
#define __PARTICLE_LINEARFORCE_AFFECTOR_H__
#include "particles/particle_fwd_decl.h"
#include "particles/particleaffector.h"

namespace Particles
{
	class LinearForceAffector: public ParticleAffector
	{
		__DeclareSubClass( LinearForceAffector, ParticleAffector);
	public:
		enum ForceApplication
		{
			FA_AVERAGE,
			FA_ADD
		};

	public:

		LinearForceAffector();
		virtual ~LinearForceAffector(){};

		const SpaceCoordType& GetSpaceCoordType(void) const;
		void	SetSpaceCoordType(const SpaceCoordType& sct);

		ForceApplication GetForceApplication(void) const;
		void SetForceApplication(ForceApplication forceApplication);
		void SetForceApplication(ushort forceApplication);

		virtual void _affect(Particle* particle);

		virtual void _preProcessParticles(void);

		inline Math::scalar GetTimeStep(void) const;

		inline void SetTimeStep(Math::scalar timeStep);

		virtual Math::MinMaxCurve* getMinMaxCurve(ParticleCurveType pct);

	protected:
		Math::float3 mScaledVector;
		ForceApplication mForceApplication;
		Math::scalar mTimeSinceLastUpdate;
		Math::scalar mTimeStep;

		SpaceCoordType	mSpaceCoord;
		Math::MinMaxCurve		mForceVectorX;
		Math::MinMaxCurve		mForceVectorY;
		Math::MinMaxCurve		mForceVectorZ;

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
	inline LinearForceAffector::ForceApplication LinearForceAffector::GetForceApplication(void) const
	{
		return mForceApplication;
	}
	//-----------------------------------------------------------------------
	inline void LinearForceAffector::SetForceApplication(LinearForceAffector::ForceApplication forceApplication)
	{
		mForceApplication = forceApplication;
	}
	//-----------------------------------------------------------------------
	inline void LinearForceAffector::SetForceApplication(ushort forceApplication)
	{
		mForceApplication = (LinearForceAffector::ForceApplication)forceApplication;
	}
	//-----------------------------------------------------------------------
	inline Math::scalar LinearForceAffector::GetTimeStep(void) const
	{
		return mTimeStep;
	}
	//-----------------------------------------------------------------------
	inline void LinearForceAffector::SetTimeStep(Math::scalar timeStep)
	{
		mTimeStep = timeStep;
		mTimeSinceLastUpdate = timeStep;
	}
	//--------------------------------------------------------------------------------
	inline const  SpaceCoordType& LinearForceAffector::GetSpaceCoordType(void) const
	{
		return mSpaceCoord;
	}
	//--------------------------------------------------------------------------------
	inline void	 LinearForceAffector::SetSpaceCoordType(const SpaceCoordType& sct)
	{
		mSpaceCoord = sct;
	}
}



#endif
