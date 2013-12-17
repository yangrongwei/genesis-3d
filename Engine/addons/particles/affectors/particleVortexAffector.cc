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
#include "particleVortexAffector.h"
#include "particles/particleaffector.h"
#include "particles/particle.h"
#include "particles/particlesystem.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::VortexAffector, CPFCC::AFFECTOR_VORTEX, Particles::ParticleAffector);

	// Constants
	const Math::scalar VortexAffector::DEFAULT_ROTATION_SPEED = 1.0f;
	//-----------------------------------------------------------------------
	VortexAffector::VortexAffector(void) : ParticleAffector()
	{
		mName = "VortexAffector";
	}
	//------------------------------------------------------------------------
	void VortexAffector::_preProcessParticles(void)
	{
	}
	//-----------------------------------------------------------------------
	void VortexAffector::_affect(Particle* particle)
	{
		if(!GetEnable())
			return;
		float percent = (particle->mTotalTimeToLive - particle->mTimeToLive)/particle->mTotalTimeToLive;
		Math::vector normal(mMinMaxNormalX.Calculate(percent,particle->mRandom0),
			mMinMaxNormalY.Calculate(percent,particle->mRandom1),
			mMinMaxNormalZ.Calculate(percent,particle->mRandom2) );

		float rotSpeed = mMinMaxRotationSpeed.Calculate(percent,particle->mRandom3);

		Math::quaternion mRotation = Math::quaternion::rotationaxis(Math::float4::normalize(normal), rotSpeed * (Math::scalar)mParentSystem->GetCurrentFrameTime());

		Math::float3 local = particle->mPosition;
		particle->mPosition = mRotation * local;

		particle->mDirection = mRotation * particle->mDirection;

		particle->mOrientation =  Math::quaternion::multiply(particle->mOrientation ,mRotation);


	}
	//--------------------------------------------------------------------------------
	Math::MinMaxCurve*  VortexAffector::getMinMaxCurve(ParticleCurveType pct)
	{
		switch(pct)
		{
		case Affector_Vortex:
			return &mMinMaxRotationSpeed;
		case Affector_VortexX:
			return &mMinMaxNormalX;
		case Affector_VortexY:
			return &mMinMaxNormalY;
		case Affector_VortexZ:
			return &mMinMaxNormalZ;
		default:
			return Super::getMinMaxCurve(pct);
		}
	}

}
