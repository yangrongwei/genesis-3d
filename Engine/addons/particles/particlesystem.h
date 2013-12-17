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
#ifndef __particlesystem_H__
#define __particlesystem_H__
#include "particles/particle_fwd_decl.h"
#include "foundation/util/scriptbind.h"
#include "particles/particleemitter.h"
#include "particles/particleaffector.h"
#include "particles/particletarget.h"
#include "particles/particle.h"
#include "particles/emitters/particleModelEmitter.h"

namespace Particles
{
	class BoxEmitter;
	class SphereSurfaceEmitter;
	class ConeEmitter;
	class ModelEmitter;
	class ParticleBillBoardTarget;
	class ParticleBeamTarget;
	class ParticleDecalTarget;
	class ParticleEntityTarget;
	class RibbonTrailTarget;
	class ParticleTrailTarget;
	class ParticleSystem : public Core::RefCounted, Serialization::ISerialize
	{
		__DeclareClass(ParticleSystem);
		__ScriptBind
	public:
		ParticleSystem();
		virtual ~ParticleSystem(void);

		const static GPtr<ParticleSystem> NullParSystem;
		const static Timing::Time		 DefaultFrameTime;
		const static Timing::Time        MinFrameTime;

		//-------------------------------Method-----------------------------------------
		void Active(void);
		void DeActive(void);
		bool IsActive(void) const;

		bool IsDirtyPrim(IndexT) const;
		void SetDirtyPrim(IndexT, bool bset = true);

		//// the ParticleSystem's WorldPosition means the own's world position, like Actor or ParticleSystemComponent
		const Math::matrix44& GetWorldMatrix(void) const;
		void SetWorldMatrix( const Math::matrix44& m );

		void SetCameraMatrix(const Math::matrix44& m);
		const Math::matrix44& GetCameraMatrix(void) const;

		//--------------------------------property----------------------------------------
		void SetName( const Util::String& name);
		const Util::String& GetName(void) const; 

		//---------------------------------update---------------------------------------
		// called by app
		void Addtime(Timing::Time t, IndexT frameIndex);

		// called by ParticleServer
		void Update(void);

		//- [Add LIBIN] Sprint16 2012-10-22
		void SetPreLoop(bool bSet);
		bool IsPreLoop(void) const;

		float GetPreDelay(void) const;

		void SetPlayBackTime(float	time);
		float GetPlayBackTime(void) const;	

		void SetPlayRateScale(float rate);
		float GetPlayRateScale(void) const;

		void SetTransparency(ubyte	transp);
		ubyte GetTransparency(void) const;	

		void SetPlayOnAwake(bool isPlay, bool updatePlayState = false);
		bool GetPlayOnAwake() const;

		//------------------------------------------------------------------------
		void Play();
		void Pause();
		void Stop();
		void StepOne();
		void SetPlayTime(Timing::Time timePoint);
		Timing::Time GetPlayTime();
		bool IsPlaying();
		bool IsPaused();
		bool IsStepOne();
		bool IsStop();


		//particletechnique
		SizeT GetParticleQuota(void) const;
		void SetParticleQuota(SizeT quota);

		const Math::bbox& GetBoundingBox(void) const;
		void SetUseExternBoundingBox(bool useExtern);
		bool IsUseExternBoundingBox(void) const;
		void SetExternBoundingBox( const Math::bbox& externBB );	//	extern bb. set by extern
		const Math::bbox& GetExternBoundingBox( void ) const;	
		void SetLocalBoundingBox( const Math::bbox& innnerBB);		//	inner bb. if need, compute every frame
		bool IsMoveWorldCoord(void) const;
		void SetMoveWorldCoord(bool bSet);

		bool IsLoadEmitterMesh(void) const;
		void SetLoadEmitterMesh(bool bset);

		Math::float3 GetDerivedPosition(void);
		Math::float3 GetDerivedScale(void);
		Math::quaternion GetDerivedRotation(void);

		void _resetPool(int nQuota);
		void _prepareParticles();
		void _preparePool(void);

		void _emitParticles(void);

		void _preProcessParticles(void);

		void _processParticles(void);

		void _postProcessParticles(void);

		void _executeEmitParticles(ParticleEmitterPtr& emitter, SizeT requested);

		void _initParticleForEmission(Particle* particle);

		void _processAffectors(Particle* particle, bool firstActiveParticle);		

		bool _isExpired(Particle* particle, Timing::Time frameTime);

		void _switchToMoveWorldCoord(bool isWorld);

		SizeT GetAffectorCount(void) const;

		const ParticleAffectorPtr& GetAffector(IndexT i) const;

		void AddAffector( const ParticleAffectorPtr& affector, IndexT index = -1 );

		void RemoveAffector( IndexT index );

		void RemoveAllAffector(void);

		const ParticleEmitterPtr& GetEmitter() const;
		void SetEmitter( const ParticleEmitterPtr& );

		void RemoveEmitter();
		//------------------------target------------------------------------------------
		const ParticleTargetPtr& GetTarget(void) const;

		void SetTarget( const ParticleTargetPtr& );

		void RemoveTarget();

		/**
		*/
		Timing::Time GetEmitterTime();
		void  SetEmitterTime(Timing::Time emtTime);

		Timing::Time GetCurrentFrameTime();
		Timing::Time GetCurEmitTime();
		Timing::Time GetCorrectTime(void) const;
		void SetDelayTime(Timing::Time startTime );
		/// used for ui
		Timing::Time GetDelayTime(void) const;

		void SetLoop(bool loop);
		const bool GetLoop() const;
		void SetDuration(Timing::Time loopTime);
		const Timing::Time GetDuration() const;
		void ResetLoop();

		bool IsPoolInvaild() { return mPool.isvalid(); }
		SizeT GetParticleFPS() const;
		void SetParticleFPS(SizeT fps);
		void SetUpdateUnVis(bool _update);
		const bool GetUpdateUnVis() const;
		void _NeedUpdate();

#ifdef __GENESIS_EDITOR__	//	edtior use
	private:
		GPtr<BoxEmitter>				mCubeEmitter;
		GPtr<SphereSurfaceEmitter>		mSphereEmitter;
		GPtr<ConeEmitter>				mConeEmitter;
		GPtr<ModelEmitter>				mModelEmitter;
		GPtr<ParticleBillBoardTarget>   mBillBoardTarget;
		GPtr<RibbonTrailTarget>			mRibbonTarget;
#endif
	protected:
		void _onActive(void);
		void _onDeactive(void);
		void _InitTime();

		void _repeatUpdate(float);
		void _techUpdate(Timing::Time frameTime,IndexT frameIndex );

	protected:
		bool					mIsActive;
		bool					mPlayOnAwake;
		bool					mIsPlaying;
		bool					mIsStop;
		bool					mbStepOne;

		float					mPreDelay;             

		bool					mIsPreLoop;				
		float					mPlayBackTime;			
		float					mPlayRateScale;				
		ubyte					mTransparency;			

		Timing::Time			mCurFrameTime;	//	current frame time
		IndexT					mFrameIndex;
		IndexT					mLastUpdateFrameIndex;

		Math::matrix44			mWorldMatrix;
		Math::matrix44			mCameraMatrix;

		Util::String			mName;
		bool					mNeedUpdate;

		friend class ParticleServer;

		//particletechnique
		typedef Util::Array<ParticleAffectorPtr> ParticleAffectorList;
		typedef ParticleAffectorList::Iterator ParticleAffectorIterator;

		Timing::Time			mLiveTime;		//	emitter's live time

		bool					mUseExternBB;
		Math::bbox				mExternBB;
		Math::bbox				mInnerBB;

		SizeT					mQuota;

		bool					mPoolNeedIncrease;
		ParticlePoolPtr			mPool;

		bool					mIsMoveWorldCoord;

		ParticleEmitterPtr		mEmitter;
		ParticleAffectorList	mAffectors;
		ParticleTargetPtr		mTarget;

		bool					mIsLoadEmitterMesh;

		bool					mLoop;
		Timing::Time			mDelayTime;
		Timing::Time		    mDuration;

		Timing::Time	mspf;
		SizeT			mfps;
		Timing::Time	mCurrentTimeForFps;


		bool					mUpdateUnVis;
		bool					mUpdateTarget;
	public:
		void Reset();
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		// copy 
		virtual void CopyFrom( const ParticleSystemPtr& parSystem );
	};
	//------------------------------------------------------------------------
	inline 
		bool 
		ParticleSystem::IsActive(void) const
	{
		return mIsActive;
	}

	//------------------------------------------------------------------------
	inline
		void 
		ParticleSystem::SetName( const Util::String& name)
	{
		if ( name.IsEmpty() )
		{
			return;
		}
		mName = name;
	}
	//------------------------------------------------------------------------
	inline
		const Util::String& 
		ParticleSystem::GetName(void) const
	{
		return mName;
	}
	//------------------------------------------------------------------------
	inline
		const Math::matrix44& 
		ParticleSystem::GetWorldMatrix(void) const
	{
		return mWorldMatrix;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleSystem::SetWorldMatrix( const Math::matrix44& m  )
	{
		mWorldMatrix = m;
	}
	//------------------------------------------------------------------------
	inline
		void ParticleSystem::SetCameraMatrix(const Math::matrix44& m)
	{
		mCameraMatrix = m;
	}
	//------------------------------------------------------------------------
	inline
		const Math::matrix44& 
		ParticleSystem::GetCameraMatrix(void) const
	{
		return mCameraMatrix;
	}
	//------------------------------------------------------------------------
	inline void ParticleSystem::SetPreLoop(bool bSet)
	{
		mIsPreLoop = bSet;
		if (!mIsPreLoop)
		{
			mPreDelay = 0.0f;
		}
	}
	//--------------------------------------------------------------------------------
	inline bool ParticleSystem::IsPreLoop(void) const
	{
		return mIsPreLoop;
	}
	//--------------------------------------------------------------------------------
	inline float ParticleSystem::GetPreDelay(void) const
	{
		return mPreDelay;
	}
	//--------------------------------------------------------------------------------
	inline void ParticleSystem::SetPlayBackTime(float	time)
	{
		mPlayBackTime = time;
	}
	//--------------------------------------------------------------------------------
	inline float ParticleSystem::GetPlayBackTime(void) const
	{
		return mPlayBackTime;
	}

	//--------------------------------------------------------------------------------
	inline void ParticleSystem::SetPlayRateScale(float	rate)
	{
		mPlayRateScale = rate;
	}
	//--------------------------------------------------------------------------------
	inline float ParticleSystem::GetPlayRateScale(void) const
	{
		return mPlayRateScale;
	}

	//--------------------------------------------------------------------------------
	inline ubyte ParticleSystem::GetTransparency(void) const
	{
		return mTransparency;
	}
	//--------------------------------------------------------------------------------
	inline void ParticleSystem::SetTransparency(ubyte	transp)
	{
		mTransparency = transp;
	}
	//--------------------------------------------------------------------------------
	inline void ParticleSystem::Play()
	{
		mIsPlaying = true;
		mIsStop = false;
	}
	//--------------------------------------------------------------------------------
	inline void ParticleSystem::Pause()
	{
		mIsPlaying = false;
		mIsStop = false;
	}
	//--------------------------------------------------------------------------------
	inline void ParticleSystem::StepOne()
	{
		mbStepOne = true;
	}
	//--------------------------------------------------------------------------------
	inline Timing::Time ParticleSystem::GetPlayTime()
	{
		//	return mLiveTime;
		return -1.0f;
	}
	//--------------------------------------------------------------------------------
	inline bool ParticleSystem::IsPlaying()
	{
		return mIsPlaying;
	}
	//--------------------------------------------------------------------------------
	inline bool ParticleSystem::IsPaused()
	{
		return !mIsPlaying && !mIsStop;
	}
	//--------------------------------------------------------------------------------
	inline bool ParticleSystem::IsStepOne()
	{
		return mbStepOne;
	}
	//------------------------------------------------------------------------
	inline bool ParticleSystem::IsStop()
	{
		return mIsStop;
	}
	//------------------------------------------------------------------------
	inline void ParticleSystem::SetPlayOnAwake(bool isPlay, bool updatePlayState)
	{
		mPlayOnAwake = isPlay;
		if (updatePlayState)
		{
			mIsPlaying = mPlayOnAwake;
		}
	}
	//------------------------------------------------------------------------
	inline bool ParticleSystem::GetPlayOnAwake() const
	{
		return mPlayOnAwake;
	}
	//technique---------------------------------------------------------------
	//------------------------------------------------------------------------
	inline
		SizeT 
		ParticleSystem::GetParticleQuota(void) const
	{
		return mQuota;		
	}
	inline
		const Math::bbox& 
		ParticleSystem::GetBoundingBox(void) const
	{
		if ( mUseExternBB )
		{
			return mExternBB;
		}
		else
		{
			return mInnerBB;
		}
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleSystem::SetUseExternBoundingBox(bool useExtern)
	{
		mUseExternBB = useExtern;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		ParticleSystem::IsUseExternBoundingBox(void) const
	{
		return mUseExternBB;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleSystem::SetExternBoundingBox( const Math::bbox& externBB )
	{
		mExternBB = externBB;
	}
	//------------------------------------------------------------------------
	inline
		const Math::bbox& 
		ParticleSystem::GetExternBoundingBox( void ) const
	{
		return mExternBB;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleSystem::SetLocalBoundingBox( const Math::bbox& innnerBB)
	{
		mInnerBB = innnerBB;
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		ParticleSystem::GetAffectorCount(void) const
	{
		return mAffectors.Size();
	}
	//------------------------------------------------------------------------
	inline
		const ParticleTargetPtr& 
		ParticleSystem::GetTarget(void) const
	{
		return mTarget;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		ParticleSystem::_isExpired(Particle* particle, Timing::Time frameTime)
	{
		return particle->mTimeToLive < frameTime;
	}
	//-------------------------------------------------------------------------
	inline Timing::Time ParticleSystem::GetEmitterTime()
	{
		return mLiveTime;
	}
	//-------------------------------------------------------------------------
	inline Timing::Time ParticleSystem::GetCurrentFrameTime()
	{
		return mCurFrameTime;
	}
	//-------------------------------------------------------------------------
	inline void  ParticleSystem::SetEmitterTime(Timing::Time emtTime)
	{
		mLiveTime = emtTime;
	}
	//--------------------------------------------------------------------------------
	inline bool  ParticleSystem::IsMoveWorldCoord(void) const
	{
		return mIsMoveWorldCoord;
	}
	//--------------------------------------------------------------------------------
	inline void  ParticleSystem::SetMoveWorldCoord(bool bSet)
	{
		_switchToMoveWorldCoord(bSet);
		mIsMoveWorldCoord = bSet;
	}
	//--------------------------------------------------------------------------------
	inline bool  ParticleSystem::IsLoadEmitterMesh(void) const
	{
		return mIsLoadEmitterMesh;
	}
	inline void  ParticleSystem::SetLoadEmitterMesh(bool bset)
	{
		mIsLoadEmitterMesh = bset;
	}
	//--------------------------------------------------------------------------------
	inline SizeT  ParticleSystem::GetParticleFPS(void) const
	{
		return mfps;
	}
	inline void  ParticleSystem::SetParticleFPS(SizeT fps)
	{
		mfps = fps;
		mspf = 1.0f/fps;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleSystem::SetDelayTime(Timing::Time startTime )
	{
		mDelayTime = startTime;
	}
	inline
		Timing::Time
		ParticleSystem::GetDelayTime(void) const
	{
		return mDelayTime;
	}
	//------------------------------------------------------------------------
	inline
		void
		ParticleSystem::SetLoop(bool loop)
	{
		mLoop = loop;
		mLiveTime = 0.0f;
	}
	//------------------------------------------------------------------------
	inline
		const bool
		ParticleSystem::GetLoop() const
	{
		return mLoop;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleSystem::SetDuration(Timing::Time loopTime)
	{
		mDuration = (float)loopTime;
		mLiveTime = 0.0f;
	}
	//-----------------------------------------------------------------------
	inline
		void
		ParticleSystem::ResetLoop()
	{
		mLiveTime = 0.0f;
	}
	//------------------------------------------------------------------------
	inline
		const Timing::Time
		ParticleSystem::GetDuration() const
	{
		return mDuration;
	}
	//-------------------------------------------------------------------------
	inline void ParticleSystem::_NeedUpdate()
	{
		mNeedUpdate = true;
	}
	//--------------------------------------------------------------------------
	inline void ParticleSystem::SetUpdateUnVis(bool _update)
	{
		mUpdateUnVis = _update;
	}
	//--------------------------------------------------------------------------
	inline const bool ParticleSystem::GetUpdateUnVis() const
	{
		return mUpdateUnVis;
	}
}

#endif // __particlesystem_H__
