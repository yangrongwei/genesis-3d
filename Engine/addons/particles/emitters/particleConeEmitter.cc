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
#include "particleConeEmitter.h"
#include "particles/particlesystem.h"
#include "particles/particleemitter.h"
#include "particles/particle.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::ConeEmitter, Particles::CPFCC::EMITTER_CONE, Particles::ParticleEmitter);

	//-----------------------------------------------------------------------
	ConeEmitter::ConeEmitter():ParticleEmitter()		
	{
		mMinColor = Particles::ConstDefine::DEFAULT_MAX_COLOR;

		mName = "ConeEmitter";		
		mInitFromType = EFT_SHELL;

		mCurveAngle.SetScalar(30.0f);
		mCurveConeHeight.SetScalar(5.0f);
		mCurveOuterRadius.SetScalar(1.0f);
		mCurveInnerRadius.SetScalar(0.5f);
	};

	//-----------------------------------------------------------------------
	void ConeEmitter::_initParticlePosition(Particle* particle)
	{
		float percent = (float)mParentSystem->GetCurEmitTime();

		float fkfAngle = mCurveAngle.Calculate(percent);
		float fkfConeHeight = mCurveConeHeight.Calculate(percent);
		float fkfOuterRadius = mCurveOuterRadius.Calculate(percent);
		float fkfInnerRadius = mCurveInnerRadius.Calculate(percent);

		float a = Math::n_deg2rad(fkfAngle);

		if ( fkfConeHeight > 0.0f && a < 0)
		{
			float sqrtSum = Math::n_sqrt( fkfConeHeight*fkfConeHeight + fkfInnerRadius * fkfInnerRadius );
			float rad = -Math::n_acos(fkfConeHeight / sqrtSum);

			if ( a < rad)
			{
				a = rad;
			}
		}

		float tHeight =  Math::n_rand(0, fkfConeHeight);
		float tRadius = Math::n_tan(a) * tHeight;
		Math::float3 pos = ConstDefine::FLOAT3_ZERO;


		if ( mInitFromType == EFT_SHELL)
		{
			tRadius +=  fkfOuterRadius;
			tRadius = Math::n_max(tRadius, 0.0f);
		}
		else if (mInitFromType == EFT_CONEBODY)
		{
			float fRadius = Math::n_max(tRadius + fkfOuterRadius,0.0f);
			tRadius = Math::n_rand( 0.0f,  fRadius);
		}
		else if (mInitFromType == EFT_POINT)
		{
			float fRadius = Math::n_max(tRadius + fkfInnerRadius,0.0f);
			tRadius = Math::n_rand( 0.0f,  tRadius + fkfInnerRadius);
		}
		else if (mInitFromType == EFT_BODY)
		{
			float fRadius1 = Math::n_max(tRadius + fkfInnerRadius,0.0f);
			float fRadius2 = Math::n_max(tRadius + fkfOuterRadius,0.0f);
			tRadius = Math::n_rand( fRadius1,  fRadius2);
		}


		Math::scalar angle  = Math::n_rand(0,N_PI_DOUBLE);
		float mX = Math::n_cos(angle);
		float mZ = Math::n_sin(angle);

		pos =  particle->mOrientation * Math::float3(mX * tRadius, 0.0f, mZ * tRadius) + Math::float3(0.0f, tHeight, 0.0f);

		if (mIsNormalDir)
		{
			Math::float3 conePoint = ConstDefine::FLOAT3_ZERO;

			conePoint.y()  =  fkfOuterRadius/(2.0f * Math::n_tan(a/2)) ;

			particle->mDirection = Math::float3::normalize(pos- conePoint);
			if ( fkfAngle < 1.0f || fkfAngle > 179.0f )
			{
				conePoint = ConstDefine::FLOAT3_ZERO;
				Math::float3 nor = pos - conePoint;
				nor.y() = 0.0f;
				nor.normalise();
				particle->mDirection = nor;
			}
		}
		particle->mDirection *= mNormalSpeed;

		if ( mParentSystem->IsMoveWorldCoord() )
		{
			Math::matrix44 tMatrix = mParentSystem->GetWorldMatrix();
			pos = pos.transformPoint(tMatrix);
			particle->mDirection = particle->mDirection.transformVector(mParentSystem->GetWorldMatrix());
		}
		particle->mPosition = pos;
		particle->mOrbitPositions.Clear();
	}
	//-----------------------------------------------------------------------
	void ConeEmitter::_initParticleVelocity(Particle* particle)
	{
		if(!IsNormalDir() || EFT_BODY == mInitFromType)
		{
			Super::_initParticleVelocity(particle);
		}
	}
	//--------------------------------------------------------------------------------
	Math::MinMaxCurve* ConeEmitter::getMinMaxCurve(ParticleCurveType pct)
	{
		switch(pct)
		{
		case 	Emitter_ConeRadiusInner:
			return &mCurveInnerRadius;
		case	Emitter_ConeRadiusOuter:
			return &mCurveOuterRadius;
		case	Emitter_ConeAngle:
			return &mCurveAngle;
		case Emitter_ConeHeight:
			return & mCurveConeHeight;

		default:
			return 	Super::getMinMaxCurve(pct);	
		}
	}


	//--------------------------------------------------------------------------------
	void ConeEmitter::SetConeAngle(float _ang)
	{
		if(Math::MinMaxCurve::Scalar == mCurveAngle.GetCurveState())
		{
			mCurveAngle.SetScalar(_ang);
		}
	}
	//--------------------------------------------------------------------------------
	float ConeEmitter::GetConeAngle(void) 
	{
		double time = mParentSystem->GetCurEmitTime();
		return mCurveAngle.Calculate((float)time);
	}
	//--------------------------------------------------------------------------------
	void ConeEmitter::SetConeInnerRadius(float _radius)
	{
		if(Math::MinMaxCurve::Scalar == mCurveInnerRadius.GetCurveState())
		{
			mCurveInnerRadius.SetScalar(_radius);
		}
	}
	//--------------------------------------------------------------------------------
	float ConeEmitter::GetConeInnerRadius(void)
	{
		double time = mParentSystem->GetCurEmitTime();
		return mCurveInnerRadius.Calculate((float)time);
	}
	//--------------------------------------------------------------------------------
	void ConeEmitter::SetConeOuterRadius(float _radius)
	{
		if(Math::MinMaxCurve::Scalar == mCurveOuterRadius.GetCurveState())
		{
			mCurveOuterRadius.SetScalar(_radius);
		}
	}
	//--------------------------------------------------------------------------------
	float ConeEmitter::GetConeOuterRadius(void)
	{
		double time = mParentSystem->GetCurEmitTime();
		return mCurveOuterRadius.Calculate((float)time);
	}
	//--------------------------------------------------------------------------------
	void ConeEmitter::SetConeHeight(float _height)
	{
		if(Math::MinMaxCurve::Scalar == mCurveConeHeight.GetCurveState())
		{
			mCurveConeHeight.SetScalar(_height);
		}
	}
	//--------------------------------------------------------------------------------
	float ConeEmitter::GetConeHeight(void)
	{
		double time = mParentSystem->GetCurEmitTime();
		return mCurveConeHeight.Calculate((float)time);
	}
}

