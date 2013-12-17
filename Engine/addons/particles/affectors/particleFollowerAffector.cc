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
#include "particleFollowerAffector.h"
#include "particles/particleaffector.h"
#include "particles/particle.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::ParticleFollowerAffector, CPFCC::AFFECTOR_FOLLOWER, Particles::ParticleAffector);

	const Math::scalar ParticleFollowerAffector::DEFAULT_MIN_DISTANCE = 5.0f;
	const Math::scalar ParticleFollowerAffector::DEFAULT_MAX_DISTANCE = 10.0f;
	//-----------------------------------------------------------------------
	ParticleFollowerAffector::ParticleFollowerAffector(void) : ParticleAffector(),
		mMinDistance(DEFAULT_MIN_DISTANCE),
		mMaxDistance(DEFAULT_MAX_DISTANCE),
		mPositionPreviousParticle(ConstDefine::FLOAT3_ZERO),
		mFirst(false)
	{
		mName = "FollowerAffector";
	}
	//-----------------------------------------------------------------------
	void ParticleFollowerAffector::_firstParticle( Particle* particle )
	{
		mFirst = true;
	}
	//-----------------------------------------------------------------------
	void ParticleFollowerAffector::_affect(Particle* particle)
	{	
		if(!GetEnable())
			return;
		if (!mFirst)
		{
			Math::scalar distance = particle->mPosition.distance(mPositionPreviousParticle);
			if (distance > mMinDistance && distance < mMaxDistance)
			{
				Math::scalar f = mMinDistance/distance;
				particle->mPosition = mPositionPreviousParticle + f * (particle->mPosition - mPositionPreviousParticle);
			}
		}

		mPositionPreviousParticle = particle->mPosition;
		mFirst = false;

	}
}