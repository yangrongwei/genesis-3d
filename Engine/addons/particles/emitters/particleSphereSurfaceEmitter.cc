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
#include "particleSphereSurfaceEmitter.h"
#include "particles/particleemitter.h"
#include "particles/particlesystem.h"
#include "particles/particle.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::SphereSurfaceEmitter, Particles::CPFCC::EMITTER_SPHERESURFACE, Particles::ParticleEmitter);

	const Math::scalar SphereSurfaceEmitter::DEFAULT_RADIUS = 10.0f;

	//-----------------------------------------------------------------------
	SphereSurfaceEmitter::SphereSurfaceEmitter():ParticleEmitter()
	{
		mMinColor = Particles::ConstDefine::DEFAULT_MAX_COLOR;
		mName = "SphereSurfaceEmitter";		
		mInitFromType = EFT_BODY;

		mRadiusCurve.SetScalar(10.0f);
		mHemCurve.SetScalar(0.0f);
		mSliceCurve.SetScalar(0.0f);
	};

	//-----------------------------------------------------------------------
	void SphereSurfaceEmitter::_initParticlePosition(Particle* particle)
	{
		float percent = (float)mParentSystem->GetCurEmitTime();

		float fkfRadius = mRadiusCurve.Calculate(percent);
		float tRadius = fkfRadius;

		float fkfHem = mHemCurve.Calculate(percent);
		float tHemZ = Math::n_deg2rad(fkfHem);
		float randomHemi = Math::n_rand( tHemZ,  N_PI);

		float fkfSlice = mSliceCurve.Calculate(percent);
		float tSliceY = Math::n_deg2rad( fkfSlice);

		/// hemi
		float rotzY = -Math::n_cos(randomHemi);
		float rotzX = -1.0f * Math::n_sin(randomHemi);
		Math::float3 xyPos(rotzX, rotzY, 0.0f);

		tSliceY = Math::n_rand( tSliceY,  N_PI_DOUBLE);

		Math::quaternion  quat = Math::quaternion::rotationaxis(Math::vector(0,1.0f,0), tSliceY);
		Math::float3 tPos = quat * xyPos;
		tPos.normalise();

		if ( mInitFromType == EFT_SHELL)
		{
			particle->mPosition = tPos * tRadius;
		}
		else if ( mInitFromType == EFT_BODY)
		{

			float oldRadius = tRadius;
			tRadius = tRadius * fabs(rotzX);

			Math::float2 normalizeXZ = Math::float2(tPos.x(), tPos.z());
			normalizeXZ = Math::float2::normalize(normalizeXZ);
			float random = Math::n_rand(0, tRadius);
			particle->mPosition = Math::float3(normalizeXZ.x()*random, tPos.y() * oldRadius, normalizeXZ.y()*random) ;
		}
		if(mParentSystem->IsMoveWorldCoord())
		{
			particle->mPosition += mParentSystem->GetDerivedPosition();
		}
		particle->mOrbitPositions.Clear();
	}
	//-----------------------------------------------------------------------
	void SphereSurfaceEmitter::_initParticleVelocity(Particle* particle)
	{
		if(!IsNormalDir() || EFT_BODY == mInitFromType)
		{
			Super::_initParticleVelocity(particle);
			return;
		}
		Math::float3 randomxyz = particle->mPosition;
		if(mParentSystem->IsMoveWorldCoord())
		{
			randomxyz -= mParentSystem->GetDerivedPosition();
			randomxyz = randomxyz.transformVector(Math::matrix44::inverse(mParentSystem->GetWorldMatrix()));
		}
		randomxyz.normalise();
		particle->mDirection = randomxyz * mNormalSpeed;
		if  (mParentSystem->IsMoveWorldCoord())
		{
			particle->mDirection = particle->mDirection.transformVector(mParentSystem->GetWorldMatrix());
		}
	}
	//--------------------------------------------------------------------------------
	Math::MinMaxCurve* SphereSurfaceEmitter::getMinMaxCurve(ParticleCurveType pct)
	{
		switch(pct)
		{
		case 	Emitter_SphereRadius:
			return &mRadiusCurve;
		case	Emitter_SphereHem:
			return &mHemCurve;
		case	Emitter_SphereSlice:
			return &mSliceCurve;

		default:
			return 	Super::getMinMaxCurve(pct);	
		}
	}

	////-----------------------------------------------------------------------
	Math::scalar SphereSurfaceEmitter::GetRadius(void)
	{
		double time = mParentSystem->GetCurEmitTime();
		return mRadiusCurve.Calculate((float)time);
	}
	//-----------------------------------------------------------------------
	void SphereSurfaceEmitter::SetRadius(Math::scalar radius)
	{
		if(Math::MinMaxCurve::Scalar == mRadiusCurve.GetCurveState())
		{
			mRadiusCurve.SetScalar(radius);
		}
	}
	////-----------------------------------------------------------------------
	Math::scalar SphereSurfaceEmitter::GetSphereHem()
	{
		double time = mParentSystem->GetCurEmitTime();
		return mHemCurve.Calculate((float)time);
	}
	//-----------------------------------------------------------------------
	Math::scalar SphereSurfaceEmitter::GetSphereSlice()
	{
		double time = mParentSystem->GetCurEmitTime();
		return mSliceCurve.Calculate((float)time);
	}

}
