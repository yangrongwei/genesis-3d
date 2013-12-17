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
#include "particles/particleemitter.h"
#include "particles/particle.h"
#include "particles/particlesystem.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::ParticleEmitter, 'PARE', Core::RefCounted)

		GPtr<ParticleEmitter> ParticleEmitter::NullEmitter(NULL);

	//------------------------------------------------------------------------
	ParticleEmitter::ParticleEmitter()
		: mParentSystem(NULL)
		, mName("Emitter")
		, mIsActive(false)
		, mEnable(true)
		, mRemainder(0)
		, mDirection(ConstDefine::DEFAULT_EMITTER_DIRECTION)
		, mMinOrientation(ConstDefine::QUATERNION_IDENTITY)
		, mMaxOrientation(ConstDefine::QUATERNION_IDENTITY)
		, mMinMass(ConstDefine::DEFAULT_MASS)
		, mMaxMass(ConstDefine::DEFAULT_MASS)
		, mMinColor(ConstDefine::DEFAULT_MIN_COLOR)
		, mMaxColor(ConstDefine::DEFAULT_MAX_COLOR)
		, mMinTexCoordIndex(ConstDefine::DEFAULT_TEXCOORD_INDEX)
		, mMaxTexCoordIndex(ConstDefine::DEFAULT_TEXCOORD_INDEX)
		, mMinSize(ConstDefine::DEFAULT_SIZE)
		, mMaxSize(ConstDefine::DEFAULT_SIZE)
		, mInitFromType(EFT_POINT)
		, mIsNormalDir(false)
		, mIsAxialSize(false)
		, mIsAxialVelocity(true)
		, mNormalSpeed(1.0f)
		,mShapeVisible(true)
	{
		mRandomSeed = GenerateRandomSeed( this );
		mUpVector  = Perpendicular(mDirection);
		mUpVector.normalise();

		mMinMaxRate.SetScalar(25.0f);
		mMinMaxSizeX.SetScalar(3.0f);
		mMinMaxSizeY.SetScalar(3.0f);
		mMinMaxSizeZ.SetScalar(3.0f);
		mMinMaxLiveTime.SetScalar(1.0f);
		mMinMaxVelocityX.SetCurveState(Math::MinMaxCurve::RandomScalar);
		mMinMaxVelocityY.SetCurveState(Math::MinMaxCurve::RandomScalar);
		mMinMaxVelocityZ.SetCurveState(Math::MinMaxCurve::RandomScalar);
		mMinMaxVelocityY.SetRandomScalar(Math::float2(5.0f,10.0f));
		mMinMaxVelocityX.SetRandomScalar(Math::float2(-3.0f,3.0f));
		mMinMaxVelocityZ.SetRandomScalar(Math::float2(-3.0f,3.0f));
		mMinMaxColorR.SetRandomScalar(Math::float2(0.5f,0.5f));
		mMinMaxColorG.SetRandomScalar(Math::float2(0.5f,0.5f));
		mMinMaxColorB.SetRandomScalar(Math::float2(0.5f,0.5f));
		mMinMaxColorA.SetRandomScalar(Math::float2(1.0f,1.0f));

		Util::Array<Math::float2> _list;
		Util::Array<bool> _type;
		_list.Append(Math::float2(0,1));
		_type.Append(true);
		_type.Append(true);
		mMinMaxColorA.SetCurveFromArray(_list,_type,_list,_type);
		_list.Clear();
		_list.Append(Math::float2(0,0.5));
		mMinMaxColorB.SetCurveFromArray(_list,_type,_list,_type);
		mMinMaxColorG.SetCurveFromArray(_list,_type,_list,_type);
		mMinMaxColorR.SetCurveFromArray(_list,_type,_list,_type);
	}
	//------------------------------------------------------------------------
	ParticleEmitter::~ParticleEmitter()
	{

	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::SetEnable(bool enable)
	{
		if ( mEnable != enable )
		{
			mEnable = enable;
		}
	}
	//------------------------------------------------------------------------
	SizeT 
		ParticleEmitter::CalculateRequestedParticles(Timing::Time mCurFrameTime)
	{
		return _calculateRequestedParticles(mCurFrameTime);
	}
	//------------------------------------------------------------------------
	SizeT 
		ParticleEmitter::_calculateRequestedParticles( Timing::Time timeElapsed )
	{
		SizeT  requestedParticles = 0;
		Timing::Time  delayTime = mParentSystem->GetCorrectTime();



		float fPreTime = 0.0f;



		if ( mEnable )
		{
			float percent = (float)mParentSystem->GetCurEmitTime();
			Math::scalar rate = mMinMaxRate.Calculate(percent,Math::n_rand(0.0f,1.0f));

			mRemainder += rate * (Math::scalar)timeElapsed;
			requestedParticles = (SizeT)mRemainder;

			mRemainder -= requestedParticles;
		}

		return requestedParticles;
	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_onActivate(void)
	{
		n_assert( !mIsActive );
		mIsActive = true;
	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_onDeactivate(void)
	{
		n_assert( mIsActive );
		mIsActive = false;
	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_emit(Particle* particle)
	{
		n_assert( particle );
		_initParticlePosition(particle);
		_initParticleDirection(particle);
		_initParticleVelocity(particle);
		_initParticleOrientation(particle);
		_initParticleMass(particle);
		_initParticleColour(particle);
		_initParticleTextureCoords(particle);
		_initParticleTimeToLive(particle);
		_initParticleDimensions(particle);
		_initParticleRotation(particle);


		particle->mRandom0 = Math::n_rand(0, 1);
		particle->mRandom1 = Math::n_rand(0, 1);
		particle->mRandom2 = Math::n_rand(0, 1);
		particle->mRandom3 = Math::n_rand(0, 1);
	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_initParticlePosition(Particle* particle)
	{
		n_assert( particle );
		particle->mPosition = Math::float3(0.0f,0.0f,0.0f);
		particle->mOrbitPositions.Clear();
		if(mParentSystem->IsMoveWorldCoord())
		{
			particle->mPosition = mParentSystem->GetDerivedPosition();
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_initParticleDirection(Particle* particle)
	{

	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_initParticleVelocity(Particle* particle)
	{
		n_assert( particle );

		float percent = (float)mParentSystem->GetCurEmitTime();
		float veloX = mMinMaxVelocityX.Calculate(percent,Math::n_rand(0.0f,1.0f));		

		if (mIsAxialVelocity)
		{

			float veloY =  mMinMaxVelocityY.Calculate(percent,Math::n_rand(0.0f,1.0f));
			float veloZ = mMinMaxVelocityZ.Calculate(percent,Math::n_rand(0.0f,1.0f));
			particle->mDirection = Math::float3(veloX, veloY, veloZ);
		}
		else
		{
			particle->mDirection = veloX;
		}

		if  (mParentSystem->IsMoveWorldCoord())
		{
			particle->mDirection = particle->mDirection.transformVector(mParentSystem->GetWorldMatrix());
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_initParticleOrientation(Particle* particle)
	{
		n_assert( particle );
		if ( mMinOrientation != mMaxOrientation )
		{
			particle->mOrientation = Math::quaternion::slerp( mMinOrientation, mMaxOrientation, 
				Util::RandomNumberTable::Rand( IncreaseRandomSeed() ) );
		}
		else
		{
			particle->mOrientation = mMinOrientation;
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_initParticleMass(Particle* particle)
	{
		n_assert( particle );
		if ( mMinMass != mMaxMass )
		{
			particle->mMass = Util::RandomNumberTable::Rand( IncreaseRandomSeed(), mMinMass, mMaxMass );
		}
		else
		{
			particle->mMass = mMinMass;
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_initParticleColour(Particle* particle)
	{
		n_assert( particle );

		float percent = (float)mParentSystem->GetCurEmitTime();

		float colorRand = Math::n_rand(0,1);
		ubyte colorR =  Math::n_scalartoByte(mMinMaxColorR.Calculate(percent,colorRand));
		ubyte colorG =  Math::n_scalartoByte(mMinMaxColorG.Calculate(percent,colorRand));
		ubyte colorB =  Math::n_scalartoByte(mMinMaxColorB.Calculate(percent,colorRand)) ;
		ubyte colorA =  Math::n_scalartoByte(mMinMaxColorA.Calculate(percent,colorRand));

		particle->mColor = Math::Color32(colorR, colorG, colorB, colorA );

	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_initParticleTextureCoords(Particle* particle)
	{
		n_assert( particle );
		if ( mMinTexCoordIndex != mMaxTexCoordIndex )
		{
			float scale = Util::RandomNumberTable::Rand( IncreaseRandomSeed() );
			particle->mTexCoordIndex =  IndexT( mMinTexCoordIndex + scale * ( mMaxTexCoordIndex - mMinTexCoordIndex ) );
		}
		else
		{
			particle->mTexCoordIndex = mMinTexCoordIndex;
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_initParticleTimeToLive(Particle* particle)
	{
		n_assert( particle );

		float percent = (float)mParentSystem->GetCurEmitTime();
		particle->mTotalTimeToLive = mMinMaxLiveTime.Calculate(percent,Math::n_rand(0.0f,1.0f));

		particle->mTimeToLive = particle->mTotalTimeToLive;

	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_initParticleDimensions(Particle* particle)
	{
		n_assert(particle);

		float percent = (float)mParentSystem->GetCurEmitTime();

		float sizeX = mMinMaxSizeX.Calculate(percent,Math::n_rand(0.0f,1.0f));
		if (mIsAxialSize)
		{
			float sizeY = mMinMaxSizeY.Calculate(percent,Math::n_rand(0.0f,1.0f));
			float sizeZ = mMinMaxSizeZ.Calculate(percent,Math::n_rand(0.0f,1.0f));
			particle->mSize = Math::float3(sizeX, sizeY, sizeZ);

		}
		else
		{
			particle->mSize = Math::float3(sizeX, sizeX, sizeX);
		}	
		particle->mInitSize = particle->mSize;
	}
	//------------------------------------------------------------------------
	void 
		ParticleEmitter::_initParticleRotation(Particle* particle)
	{
		n_assert(particle);

		float percent = (float)mParentSystem->GetCurEmitTime();

		float zRotation = mMinMaxInitRotaion.Calculate( percent,Math::n_rand(0.0f,1.0f));

		particle->mZRotation = zRotation * N_PI / 180;
	}
	//--------------------------------------------------------------------------------
	Math::MinMaxCurve* ParticleEmitter::getMinMaxCurve(ParticleCurveType pct)
	{
		switch(pct)
		{
		case 	Emitter_Rate:
			return &mMinMaxRate;
		case	Emitter_VelocityX:
			return &mMinMaxVelocityX;
		case	Emitter_VelocityY:
			return &mMinMaxVelocityY;
		case	Emitter_VelocityZ:
			return &mMinMaxVelocityZ;
		case	Emitter_ColorR:
			return &mMinMaxColorR;
		case	Emitter_ColorG:
			return &mMinMaxColorG;
		case	Emitter_ColorB:
			return &mMinMaxColorB;
		case	Emitter_ColorA:
			return &mMinMaxColorA;
		case  Emitter_Livetime:
			return &mMinMaxLiveTime;
		case Emitter_SizeX:
			return &mMinMaxSizeX;
		case Emitter_SizeY:
			return &mMinMaxSizeY;
		case Emitter_SizeZ:
			return &mMinMaxSizeZ;
		case Emitter_RotSpeed:
			return &mMinMaxRotationSpeed;
		case Emitter_InitRot:
			return &mMinMaxInitRotaion;
		default:
			return NULL;					
		}
	}
}
