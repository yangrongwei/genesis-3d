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
#include "particleRandomiserAffector.h"
#include "particles/particlesystem.h"
#include "particles/particleaffector.h"
#include "particles/particle.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::RandomiserAffector, CPFCC::AFFECTOR_RANDOMISER, Particles::ParticleAffector);
	const Math::float3 RandomiserAffector::DEFAULT_MAX_DEVIATION = ConstDefine::FLOAT3_ZERO;
	const Math::scalar RandomiserAffector::DEFAULT_TIME_STEP = 0.2f;
	const bool RandomiserAffector::DEFAULT_RANDOM_DIRECTION = true;

	//-----------------------------------------------------------------------
	RandomiserAffector::RandomiserAffector(void) : 
	ParticleAffector(),
		mMaxDeviationX(DEFAULT_MAX_DEVIATION.x()),
		mMaxDeviationY(DEFAULT_MAX_DEVIATION.y()),
		mMaxDeviationZ(DEFAULT_MAX_DEVIATION.z()),
		mTimeSinceLastUpdate(DEFAULT_TIME_STEP),
		mTimeStep(DEFAULT_TIME_STEP),
		mUpdate(true),
		mRandomDirection(DEFAULT_RANDOM_DIRECTION)
	{
		mName = "RandomiserAffector";
	}
	//-----------------------------------------------------------------------
	void RandomiserAffector::_preProcessParticles()
	{
		if (mParentSystem->GetEmitter())
		{
			mTimeSinceLastUpdate += (Math::scalar)mParentSystem->GetCurrentFrameTime();
			if (mTimeSinceLastUpdate > mTimeStep)
			{
				mTimeSinceLastUpdate -= mTimeStep;
				mUpdate = true;
			}
		}
	}
	//-----------------------------------------------------------------------
	void RandomiserAffector::_affect(Particle* particle)
	{
		if(!GetEnable())
			return;
		if (mUpdate)
		{
			if (mRandomDirection)
			{
				particle->mDirection += Math::float3(Math::n_rand(-mMaxDeviationX, mMaxDeviationX),
					Math::n_rand(-mMaxDeviationY, mMaxDeviationY),
					Math::n_rand(-mMaxDeviationZ, mMaxDeviationZ));
			}
			else
			{
				particle->mPosition += particle->mSize * Math::float3(Math::n_rand(-mMaxDeviationX, mMaxDeviationX),
					Math::n_rand(-mMaxDeviationY, mMaxDeviationY),
					Math::n_rand(-mMaxDeviationZ, mMaxDeviationZ));
			}
		}
	}
	//-----------------------------------------------------------------------
	void RandomiserAffector::_postProcessParticles()
	{
		mUpdate = false;
	}

}