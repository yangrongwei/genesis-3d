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
#include "particleBoxEmitter.h"
#include "particles/particleemitter.h"
#include "particles/particle.h"
#include "particles/particlesystem.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::BoxEmitter, Particles::CPFCC::EMITTER_BOX, Particles::ParticleEmitter);

	//-----------------------------------------------------------------------
	BoxEmitter::BoxEmitter():ParticleEmitter()
	{
		mMinColor = Particles::ConstDefine::DEFAULT_MAX_COLOR;
		mName = "BoxEmitter";		
		mInitFromType = EFT_SHELL;

		mCurveRangeX.SetScalar(1.0f);
		mCurveRangeY.SetScalar(1.0f);
		mCurveRangeZ.SetScalar(1.0f);

	};

	//-----------------------------------------------------------------------
	void BoxEmitter::_initParticlePosition(Particle* particle)
	{
		float percent = (float)mParentSystem->GetCurEmitTime();

		float fkfRangeX = mCurveRangeX.Calculate(percent);
		float fkfRangeY = mCurveRangeY.Calculate(percent);
		float fkfRangeZ = mCurveRangeZ.Calculate(percent);

		Math::float3 randomxyz = ConstDefine::FLOAT3_ZERO;
		if (mInitFromType == EFT_BODY)
		{
			randomxyz = Math::float3( Math::n_rand(-0.5f,0.5f) * fkfRangeX,
				Math::n_rand(-0.5f,0.5f) * fkfRangeY,
				Math::n_rand(-0.5f,0.5f) * fkfRangeZ );
		}
		else if(mInitFromType == EFT_SHELL)
		{
			randomxyz = Math::float3( Math::n_rand(-0.5f,0.5f) * fkfRangeX,
				Math::n_rand(-0.5f,0.5f) * fkfRangeY,
				Math::n_rand(-0.5f,0.5f) * fkfRangeZ);
			float randomsid = Math::n_rand(0,3);
			if(randomsid < 1.0f)
				randomxyz.x() = fkfRangeX * (Math::n_rand(-0.5f,0.5f)>0?0.5f:-0.5f);
			else if(randomsid < 2.0f)
				randomxyz.y() = fkfRangeY * (Math::n_rand(-0.5f,0.5f)>0?0.5f:-0.5f);
			else
				randomxyz.z() = fkfRangeZ * (Math::n_rand(-0.5f,0.5f)>0?0.5f:-0.5f);
		}
		if(mParentSystem->IsMoveWorldCoord())
		{
			randomxyz = randomxyz + mParentSystem->GetDerivedPosition();
		}
		particle->mPosition = randomxyz;
		particle->mOrbitPositions.Clear();
	}
	//-----------------------------------------------------------------------
	void BoxEmitter::_initParticleVelocity(Particle* particle)
	{
		if(!IsNormalDir() || EFT_BODY == mInitFromType)
		{
			Super::_initParticleVelocity(particle);
			return;
		}
		float percent = (float)mParentSystem->GetCurEmitTime();
		float fkfRangeX = mCurveRangeX.Calculate(percent)*0.5f;
		float fkfRangeY = mCurveRangeY.Calculate(percent)*0.5f;
		float fkfRangeZ = mCurveRangeZ.Calculate(percent)*0.5f;


		Math::float3 randomxyz = particle->mPosition;
		if(mParentSystem->IsMoveWorldCoord())
		{
			randomxyz -= mParentSystem->GetDerivedPosition();
			randomxyz = randomxyz.transformVector(Math::matrix44::inverse(mParentSystem->GetWorldMatrix()));
		}

		if(randomxyz.x() < -fkfRangeX + 1e-6)
		{
			particle->mDirection.x() = -mNormalSpeed;
			particle->mDirection.y() = 0;
			particle->mDirection.z() = 0;
		}
		else if(randomxyz.x() > fkfRangeX - 1e-6)
		{
			particle->mDirection.x() = mNormalSpeed;
			particle->mDirection.y() = 0;
			particle->mDirection.z() = 0;
		}
		else if(randomxyz.y() < -fkfRangeY + 1e-6)
		{
			particle->mDirection.x() = 0;
			particle->mDirection.y() = -mNormalSpeed;
			particle->mDirection.z() = 0;
		}
		else if(randomxyz.y() > fkfRangeY - 1e-6)
		{
			particle->mDirection.x() = 0;
			particle->mDirection.y() = mNormalSpeed;
			particle->mDirection.z() = 0;
		}
		else if(randomxyz.z() < -fkfRangeZ + 1e-6)
		{
			particle->mDirection.x() = 0;
			particle->mDirection.y() = 0;
			particle->mDirection.z() = -mNormalSpeed;
		}
		else
		{
			particle->mDirection.x() = 0;
			particle->mDirection.y() = 0;
			particle->mDirection.z() = mNormalSpeed;
		}
		if  (mParentSystem->IsMoveWorldCoord())
		{
			// rotate Direction
			particle->mDirection = particle->mDirection.transformVector(mParentSystem->GetWorldMatrix());
		}
	}
	//--------------------------------------------------------------------------------
	Math::MinMaxCurve* BoxEmitter::getMinMaxCurve(ParticleCurveType pct)
	{
		switch(pct)
		{
		case 	Emitter_BoxSizeX:
			return &mCurveRangeX;
		case	Emitter_BoxSizeY:
			return &mCurveRangeY;
		case	Emitter_BoxSizeZ:
			return &mCurveRangeZ;

		default:
			return 	Super::getMinMaxCurve(pct);
		}
	}

	//-----------------------------------------------------------------------
	Math::scalar BoxEmitter::GetXRange()
	{
		double time = mParentSystem->GetCurEmitTime();
		return mCurveRangeX.Calculate((float)time);
	}
	//-----------------------------------------------------------------------
	Math::scalar BoxEmitter::GetYRange() 
	{
		double time = mParentSystem->GetCurEmitTime();
		return mCurveRangeY.Calculate((float)time);
	}
	//-----------------------------------------------------------------------
	Math::scalar BoxEmitter::GetZRange()
	{
		double time = mParentSystem->GetCurEmitTime();
		return mCurveRangeZ.Calculate((float)time);
	}

	//-----------------------------------------------------------------------
	void BoxEmitter::SetXRange(const Math::scalar range)
	{
		if(Math::MinMaxCurve::Scalar == mCurveRangeX.GetCurveState())
		{
			mCurveRangeX.SetScalar(range);
		}
	}
	//-----------------------------------------------------------------------
	void BoxEmitter::SetYRange(const Math::scalar range)
	{
		if(Math::MinMaxCurve::Scalar == mCurveRangeY.GetCurveState())
		{
			mCurveRangeY.SetScalar(range);
		}
	}


	//-----------------------------------------------------------------------
	void BoxEmitter::SetZRange(const Math::scalar range)
	{
		if(Math::MinMaxCurve::Scalar == mCurveRangeZ.GetCurveState())
		{
			mCurveRangeZ.SetScalar(range);
		}
	}
}
