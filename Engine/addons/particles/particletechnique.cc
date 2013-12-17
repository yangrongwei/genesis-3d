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
#include "particles/particletechnique.h"
#include "particles/particlesystem.h"

namespace Particles
{
	__ImplementClass(Particles::ParticleTechnique, 'PART', Core::RefCounted)

		GPtr<ParticleTechnique> ParticleTechnique::NullTechnique(NULL);

	//------------------------------------------------------------------------
	ParticleTechnique::ParticleTechnique()
		: mParentSystem(NULL)
		, mName("Technique")
		, mIsActive(false)
		, mUseExternBB(false)
		, mLiveTime(0.0)
		, mCurFrameTime(0.0)
		, mFrameIndex(0)
		, mQuota( ConstDefine::DEFAULT_TECHNIQUE_QUOTA )
		, mPoolNeedIncrease(true)
		, mPosition( ConstDefine::FLOAT3_ZERO )
		, mIsMoveWorldCoord(false)
		, mIsLoadEmitterMesh(false)

	{
#ifdef __GENESIS_EDITOR__	//	edtior use
		mIsSavedInit = false;
		mBoxX.SetScalar(10.0f);
		mBoxY.SetScalar(10.0f);
		mBoxZ.SetScalar(10.0f);
		mSpehereRadius.SetScalar(0.1f);
		mSphereHem.SetScalar(90.0f);
		mSphereSlice.SetScalar(90.0f);
		mConeRadius1.SetScalar(5.0f);
		mConeRadius2.SetScalar(10.0f);
		mConeAngle.SetScalar(30.0f);
		mConeHeight.SetScalar(10.0f);
#endif
	}
	//------------------------------------------------------------------------
	ParticleTechnique::~ParticleTechnique()
	{

	}
	//------------------------------------------------------------------------
	Math::float3
		ParticleTechnique::GetDerivedPosition(void)
	{
		if (mParentSystem)
		{
			Math::float3 sysPos(mParentSystem->GetWorldMatrix().get_position().x(),
				mParentSystem->GetWorldMatrix().get_position().y(),
				mParentSystem->GetWorldMatrix().get_position().z());

			return sysPos;
		}

		return ConstDefine::FLOAT3_ZERO;
	}
	//------------------------------------------------------------------------
	Math::float3 ParticleTechnique::GetDerivedScale(void)
	{
		if (mParentSystem)
		{
			Math::float3 sysScale(mParentSystem->GetWorldMatrix().getrow0().x(),
				mParentSystem->GetWorldMatrix().getrow1().y(),
				mParentSystem->GetWorldMatrix().getrow2().z());

			return sysScale;
		}

		return Math::float3(1,1,1);
	}
	//------------------------------------------------------------------------
	Math::quaternion ParticleTechnique::GetDerivedRotation(void)
	{
		if (mParentSystem)
		{
			Math::quaternion quat = Math::matrix44::rotationmatrix(mParentSystem->GetWorldMatrix());
			return quat;
		}

		return Math::quaternion::identity();
	}
	//--------------------------------------------------------------------------------
	Math::matrix44 ParticleTechnique::GetParentMatrix() const
	{
		if (mParentSystem)
		{
			return mParentSystem->GetWorldMatrix();
		}
		return Math::matrix44::identity();
	}
	//------------------------------------------------------------------------ 
	void
		ParticleTechnique::SetParticleQuota(SizeT quota)
	{
		if ( quota <= 0 )
		{
			n_warning(" ParticleTechnique::SetParticleQuota, should bigger than 0");
			quota = 1; 
		}
		if ( quota > ConstDefine::MAX_TECHNIQUE_QUOTA )
		{
			n_warning(" ParticleTechnique::SetParticleQuota, should smaller than %d", ConstDefine::MAX_TECHNIQUE_QUOTA );
			quota = ConstDefine::MAX_TECHNIQUE_QUOTA;
		}
		mQuota = quota;
		mPoolNeedIncrease = true;
	}
	//------------------------------------------------------------------------
	void ParticleTechnique::_onActivate(void)
	{
		n_assert( !mIsActive );

		n_assert( !mPool.isvalid() )
			mPool = ParticlePool::Create();
		_preparePool();

		for ( IndexT index = 0; index < mEmitters.Size(); ++index )
		{
			mEmitters[index]->_onActivate();
		}
		for ( IndexT index = 0; index < mAffectors.Size(); ++index )
		{
			mAffectors[index]->_onActivate();
		}
		if ( mTarget )
		{
			mTarget->_onActivate();
		}

		mIsActive = true;
	}
	//------------------------------------------------------------------------
	void ParticleTechnique::_onDeactivate(void)
	{
		n_assert( mIsActive );

		for ( IndexT index = 0; index < mEmitters.Size(); ++index )
		{
			mEmitters[index]->_onDeactivate();
		}
		for ( IndexT index = 0; index < mAffectors.Size(); ++index )
		{
			mAffectors[index]->_onDeactivate();
		}
		if ( mTarget )
		{
			mTarget->_onDeactivate();
		}

		mPool = NULL;
		mPoolNeedIncrease = true;


		mIsActive = false;
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::_update( Timing::Time frameTime, IndexT frameIndex )
	{
		mCurFrameTime = frameTime;
		mLiveTime += mCurFrameTime;
		mFrameIndex = frameIndex;
		_preparePool();
		_addTime();

		_emitParticles();
		_preProcessParticles();
		_processParticles();
		_postProcessParticles();
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::_preparePool(void)
	{
		if ( mPoolNeedIncrease )
		{
			n_assert( mPool.isvalid() );
			mPool->DestroyAllVisualParticles();
			mPool->IncreaseVisualParticlePool( mQuota );
			mPoolNeedIncrease = false;
		}
	}
	//--------------------------------------------------------------------------------
	void ParticleTechnique::ResetPool(int nQuota)
	{
		mPool->DestroyAllVisualParticles();

		SetParticleQuota(nQuota);		
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::_addTime()
	{

	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::_emitParticles(void)
	{
		if ( mEmitters.IsEmpty() )
		{
			return;
		}

		for ( IndexT index = 0; index < mEmitters.Size(); ++index )
		{
			ParticleEmitterPtr& emitter = mEmitters[index];
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::_executeEmitParticles(ParticleEmitterPtr& emitter, SizeT requested)
	{
		n_assert( mPool.isvalid() );
		n_assert( emitter.isvalid() );

		if ( requested == 0 )
		{
			return;
		}

		for ( IndexT index = 0; index < requested; ++index )
		{
			Particle* particle = mPool->ReleaseParticle();

			if ( !particle )
			{
				return;
			}

			emitter->_emit( particle );
			_initParticleForEmission(particle);
		}
	}
	//------------------------------------------------------------------------
	void ParticleTechnique::_preProcessParticles(void)
	{
		for ( IndexT index = 0; index < mAffectors.Size(); ++index)
		{
			mAffectors[index]->_preProcessParticles();
		}
	}
	//------------------------------------------------------------------------
	void ParticleTechnique::_processParticles(void)
	{
		if ( mPool->IsEmpty() )
			return;

		Particle* particle = mPool->GetFirst();
		ParticleEmitter* emitter = 0;
		ParticleTechnique* technique = 0;
		bool firstParticle = true; 
		bool firstActiveParticle = true; 

		while ( !mPool->End() )
		{
			if (particle)
			{
				if ( !_isExpired(particle, mCurFrameTime) )
				{
					_processAffectors(particle, firstActiveParticle);

					firstActiveParticle = false;
				}
				else
				{
					//add by zhangjitao
					particle->mOrbitPositions.Reset();

					mPool->LockLatestParticle();
				}

				particle->mTimeToLive -= (Math::scalar)mCurFrameTime;

				particle->mTimeFraction = (particle->mTotalTimeToLive - particle->mTimeToLive)/particle->mTotalTimeToLive;
			}

			firstParticle = false;
			particle = mPool->GetNext();
		}
	}
	//-----------------------------------------------------------------------
	void ParticleTechnique::_initParticleForEmission(Particle* particle)
	{
		if ( !mAffectors.IsEmpty() )
		{
			for ( IndexT index = 0; index < mAffectors.Size(); ++index)
			{
				mAffectors[index]->_initParticleForEmission(particle);
			}
		}
	}
	//------------------------------------------------------------------------
	void ParticleTechnique::_processAffectors(Particle* particle, bool firstActiveParticle)
	{
		if ( !mAffectors.IsEmpty() )
		{
			for ( IndexT index = 0; index < mAffectors.Size(); ++index)
			{
				mAffectors[index]->_processParticle(particle, firstActiveParticle);
			}
		}
	}
	//------------------------------------------------------------------------
	void ParticleTechnique::_postProcessParticles(void)
	{
		for ( IndexT index = 0; index < mAffectors.Size(); ++index)
		{
			mAffectors[index]->_postProcessParticles();
		}
		if ( mTarget.isvalid() && mPool.isvalid())
		{
			mTarget->_updateTarget( mPool, mCurFrameTime );
		}
	}
	//------------------------------------------------------------------------
	void ParticleTechnique::_switchToMoveWorldCoord(bool isWorld)
	{
		if(mIsMoveWorldCoord == isWorld || NULL == mPool)
			return;
		Particle* particle = mPool->GetFirst();

		Math::matrix44 techMat = GetParentMatrix();
		if(!isWorld)
			techMat = Math::matrix44::inverse(techMat);
		while ( particle )
		{
			particle->mPosition = particle->mPosition.transformPoint(techMat);
			particle = mPool->GetNext();
		}

	}
	//------------------------------------------------------------------------
	const ParticleEmitterPtr& 
		ParticleTechnique::GetEmitter(IndexT index) const
	{
		if ( index >= 0 && index < mEmitters.Size() )
		{
			return mEmitters[index];
		}
		else
		{
			return ParticleEmitter::NullEmitter;
		}
	}
	//------------------------------------------------------------------------
	IndexT ParticleTechnique::FindEmitter( const ParticleEmitterPtr& emitter ) const
	{
		if ( emitter.isvalid() )
		{
			for ( IndexT i = 0; i < mEmitters.Size(); ++i)
			{
				if ( mEmitters[i] == emitter )
				{
					return i;
				}
			}
			n_error("ParticleTechnique::FindEmitter");
		}
		return InvalidIndex;
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::AddEmitter( const ParticleEmitterPtr& emitter, IndexT index)
	{
		if ( !emitter.isvalid() )
		{
			return;
		}


		if (index >= 0)
			mEmitters.Insert( index, emitter );
		else
			mEmitters.Append( emitter );


		if ( IsActive() )
		{
			emitter->_onActivate();
		}
#ifdef __GENESIS_EDITOR__	//	edtior use
		if(!mIsSavedInit)
			return;
		uint emtfourcc = emitter->GetClassFourCC().AsUInt();	
		switch(emtfourcc)
		{
		case CPFCC::EMITTER_BOX:
			emitter->getMinMaxCurve(Emitter_BoxSizeX)->CopyFrom(mBoxX);
			emitter->getMinMaxCurve(Emitter_BoxSizeY)->CopyFrom(mBoxY);
			emitter->getMinMaxCurve(Emitter_BoxSizeZ)->CopyFrom(mBoxZ);
			break;
		case CPFCC::EMITTER_SPHERESURFACE:
			emitter->getMinMaxCurve(Emitter_SphereRadius)->CopyFrom(mSpehereRadius);
			emitter->getMinMaxCurve(Emitter_SphereHem)->CopyFrom(mSphereHem);
			emitter->getMinMaxCurve(Emitter_SphereSlice)->CopyFrom(mSphereSlice);
			break;
		case CPFCC::EMITTER_CONE:
			emitter->getMinMaxCurve(Emitter_ConeRadiusInner)->CopyFrom(mConeRadius1);
			emitter->getMinMaxCurve(Emitter_ConeRadiusOuter)->CopyFrom(mConeRadius2);
			emitter->getMinMaxCurve(Emitter_ConeHeight)->CopyFrom(mConeHeight);
			emitter->getMinMaxCurve(Emitter_ConeAngle)->CopyFrom(mConeAngle);
			break;
		}	
#endif
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::RemoveEmitter( const ParticleEmitterPtr& emitter )
	{
		IndexT findIndex = FindEmitter(emitter);
		if ( findIndex != InvalidIndex )
		{
			RemoveEmitter(findIndex);
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::RemoveEmitter( IndexT index)
	{
		if ( index >= 0 && index < mEmitters.Size() )
		{
			ParticleEmitterPtr& emitter = mEmitters[index];
#ifdef __GENESIS_EDITOR__	//	edtior use
			mIsSavedInit = true;
			uint emtfourcc = emitter->GetClassFourCC().AsUInt();	
			switch(emtfourcc)
			{
			case CPFCC::EMITTER_BOX:
				mBoxX.CopyFrom(*emitter->getMinMaxCurve(Emitter_BoxSizeX));
				mBoxY.CopyFrom(*emitter->getMinMaxCurve(Emitter_BoxSizeY));
				mBoxZ.CopyFrom(*emitter->getMinMaxCurve(Emitter_BoxSizeZ));
				break;
			case CPFCC::EMITTER_SPHERESURFACE:
				mSpehereRadius.CopyFrom(*emitter->getMinMaxCurve(Emitter_SphereRadius));
				mSphereHem.CopyFrom(*emitter->getMinMaxCurve(Emitter_SphereHem));
				mSphereSlice.CopyFrom(*emitter->getMinMaxCurve(Emitter_SphereSlice));
				break;
			case CPFCC::EMITTER_CONE:
				mConeRadius1.CopyFrom(*emitter->getMinMaxCurve(Emitter_ConeRadiusInner));
				mConeRadius2.CopyFrom(*emitter->getMinMaxCurve(Emitter_ConeRadiusOuter));
				mConeHeight.CopyFrom(*emitter->getMinMaxCurve(Emitter_ConeHeight));
				mConeAngle.CopyFrom(*emitter->getMinMaxCurve(Emitter_ConeAngle));
				break;
			}	
#endif
			n_assert(emitter.isvalid());
			if ( emitter->IsActive() )
			{
				emitter->_onDeactivate();
			}
			mEmitters.EraseIndex( index );
		}

	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::RemoveAllEmitter(void)
	{
		for ( IndexT index = 0; index < mEmitters.Size(); ++index)
		{
			ParticleEmitterPtr& emitter = mEmitters[index];
			n_assert(emitter.isvalid());
			if ( emitter->IsActive() )
			{
				emitter->_onDeactivate();
			}
		}
		mEmitters.Clear();
	}
	//------------------------------------------------------------------------
	const ParticleAffectorPtr& 
		ParticleTechnique::GetAffector(IndexT index) const
	{
		if ( index >=0 && index < mAffectors.Size() )
		{
			return mAffectors[index];
		}
		else
		{
			return ParticleAffector::NullAffector;
		}
	}
	//--------------------------------------------------------------------------------
	const ParticleAffectorPtr& ParticleTechnique::GetAffectorByName( const Core::Rtti& pRtti ) const
	{		
		for ( IndexT i = 0; i < mAffectors.Size(); ++i)
		{
			if ( mAffectors[i]->GetRtti() == &pRtti )
			{
				return mAffectors[i];
			}
		}	
		return ParticleAffector::NullAffector;	
	}
	//------------------------------------------------------------------------
	IndexT 
		ParticleTechnique::FindAffector( const ParticleAffectorPtr& affector ) const
	{
		if ( affector.isvalid()  )
		{
			for ( IndexT i = 0; i < mAffectors.Size(); ++i)
			{
				if ( mAffectors[i] == affector )
				{
					return i;
				}
			}
			n_error("ParticleTechnique::FindAffector");
		}
		return InvalidIndex;
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::AddAffector( const ParticleAffectorPtr& affector, IndexT index)
	{
		if ( !affector.isvalid() )
		{
			return;
		}

		if ( affector->GetParentSystem() != NULL )
		{
			return;
		}

		if (index >= 0)
			mAffectors.Insert( index, affector );
		else
			mAffectors.Append( affector );


		if ( IsActive() )
		{
			affector->_onActivate();
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::RemoveAffector( const ParticleAffectorPtr& affector )
	{
		IndexT findIndex = FindAffector(affector);
		if ( findIndex != InvalidIndex )
		{
			RemoveAffector(findIndex);
		}
	}
	//------------------------------------------------------------------------
	void
		ParticleTechnique::RemoveAffector( IndexT index )
	{
		if ( index >= 0 && index < mAffectors.Size() )
		{
			ParticleAffectorPtr& affector = mAffectors[index];
			n_assert(affector.isvalid());
			if ( affector->IsActive() )
			{
				affector->_onDeactivate();
			}
			affector->SetParentSystem(NULL);
			mAffectors.EraseIndex( index );
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::RemoveAllAffector(void)
	{
		for ( IndexT index = 0; index < mAffectors.Size(); ++index)
		{
			ParticleAffectorPtr& affector = mAffectors[index];
			n_assert(affector.isvalid());
			if ( affector->IsActive() )
			{
				affector->_onDeactivate();
			}
			affector->SetParentSystem(NULL);
		}
		mAffectors.Clear();
	}
	//------------------------------------------------------------------------
	void 
		ParticleTechnique::SetTarget( const ParticleTargetPtr& target)
	{
		if ( target.isvalid() )
		{
			if ( target->GetParentSystem() != NULL )
			{
				return;
			}
		}

		if ( mTarget.isvalid() )
		{
			if ( mTarget->IsActive() )
			{
				mTarget->_onDeactivate();
			}
			mTarget->SetParentSystem(NULL);
			mTarget = NULL;
		}

		n_assert( !mTarget.isvalid() );
		mTarget = target;

		if ( mTarget.isvalid() )
		{
			if ( IsActive() )
			{
				mTarget->_onActivate();
			}
		}
	}
	//--------------------------------------------------------------------------------
	void ParticleTechnique::RemoveTarget()
	{

		if( !mTarget.isvalid())
			return;
		if ( mTarget->IsActive() )
		{
			mTarget->_onDeactivate();
		}
		mTarget->SetParentSystem(NULL);
		mTarget = NULL;
	}
	//------------------------------------------------------------------------
	void ParticleTechnique::Reset()
	{
		mLiveTime = 0;
		mFrameIndex = 0;
		mCurFrameTime = 0;
		ResetPool(mQuota);


	}


}

