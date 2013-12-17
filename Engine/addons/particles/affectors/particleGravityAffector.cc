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
#include "particleGravityAffector.h"
#include "particles/particleaffector.h"
#include "particles/particlesystem.h"
#include "particles/particle.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::GravityAffector, CPFCC::AFFECTOR_GRAVITY, Particles::ParticleAffector);

	const Math::scalar GravityAffector::DEFAULT_GRAVITY = 1.0f;
	const Math::scalar GravityAffector::GRAVITY_MASS = 30.0f;
	//-----------------------------------------------------------------------
	GravityAffector::GravityAffector() : ParticleAffector()
	{

		mName = "GravityAffector";
	}
	//-----------------------------------------------------------------------
	void GravityAffector::_affect(Particle* particle)
	{		
		if(!GetEnable())
			return;
		float percent = (particle->mTotalTimeToLive - particle->mTimeToLive)/particle->mTotalTimeToLive;

		Math::float3	gravityDir(mMinMaxPosX.Calculate(percent,particle->mRandom0)
			, mMinMaxPosY.Calculate(percent,particle->mRandom1)
			, mMinMaxPosZ.Calculate(percent,particle->mRandom2)  );

		gravityDir = gravityDir - particle->mPosition;

		gravityDir.normalise();

		float  gravity = mMinMaxGravity.Calculate(percent,particle->mRandom3);

		Math::scalar _curTime = (Math::scalar)mParentSystem->GetCurrentFrameTime();
		particle->mDirection += gravity  * gravityDir * _curTime * _calculateAffectSpecialisationFactor(particle);

	}
	//--------------------------------------------------------------------------------
	Math::MinMaxCurve* GravityAffector::getMinMaxCurve(ParticleCurveType pct)
	{
		switch(pct)
		{
		case 	Affector_GravityX:
			return &mMinMaxPosX;
		case 	Affector_GravityY:
			return &mMinMaxPosY;
		case 	Affector_GravityZ:
			return &mMinMaxPosZ;
		case 	Affector_Gravity:
			return &mMinMaxGravity;
		default:
			return NULL;					
		}
	}
}

