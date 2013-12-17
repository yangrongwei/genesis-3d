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
#include "particleLimitAffector.h"
#include "particles/particleaffector.h"
#include "particles/particle.h"


namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::LimitAffector, CPFCC::AFFECTOR_LIMIT, Particles::ParticleAffector);	

	//-----------------------------------------------------------------------
	LimitAffector::LimitAffector(void) : ParticleAffector()
		, mSeparateAxis(false)
	{
		mName = "LimitAffector";
		mLimitX.SetScalar(0.0f);
		mLimitY.SetScalar(0.0f);
		mLimitZ.SetScalar(0.0f);

		mLimitValue.SetScalar(0.1f);
		//mColorMap
	}
	//-----------------------------------------------------------------------
	void LimitAffector::_affect(Particle* particle)
	{
		if(!GetEnable())
			return;
		if (particle)
		{

			float curTime = (particle->mTotalTimeToLive - particle->mTimeToLive)/particle->mTotalTimeToLive;

			//mAxisX
			float limitX = mLimitX.Calculate(curTime,particle->mRandom0);
			//mAxisY
			float limitY = mLimitY.Calculate(curTime,particle->mRandom1);
			//mAxisZ
			float limitZ = mLimitZ.Calculate(curTime,particle->mRandom2);

			//mDampen
			float _value = mLimitValue.Calculate(curTime,particle->mRandom3);


			Math::float3 velocity = particle->mDirection;

			if (mSeparateAxis)
			{
				Math::scalar length = velocity.length();

				length = LimitVelocity(length, limitX, _value);
				velocity.normalise();
				velocity = velocity * length;
			}
			else
			{
				velocity.x() = LimitVelocity(velocity.x(), limitX, _value);
				velocity.y() = LimitVelocity(velocity.y(), limitY, _value);
				velocity.z() = LimitVelocity(velocity.z(), limitZ, _value);
			}

			particle->mDirection = velocity;

		}

	}
	//------------------------------------------------------------------------
	float LimitAffector::LimitVelocity(float velocity, float _limit, float _value)
	{
		if(velocity > _limit)
			return _limit + (velocity - _limit)*(1.0f - _value);
		if(velocity < -_limit)
			return -_limit - (-_limit - velocity)*(1.0f - _value);
		return velocity;
	}
	//------------------------------------------------------------------------
	void LimitAffector::_preProcessParticles(void)
	{

	}

	//--------------------------------------------------------------------------------
	Math::MinMaxCurve* LimitAffector::getMinMaxCurve(ParticleCurveType axis)
	{
		switch(axis)
		{
		case 			Affector_LimitX:
			return  &mLimitX;
		case			Affector_LimitY:
			return &mLimitY;
		case			Affector_LimitZ:
			return &mLimitZ;
		case        Affector_LimitValue:
			return &mLimitValue;
		default:
			return Super::getMinMaxCurve(axis);					
		}
	}

}

