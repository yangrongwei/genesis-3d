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


/*
This class is not in using
*/
#ifndef __particletechnique_H__
#define __particletechnique_H__
#include "particles/particle_fwd_decl.h"
#include "particles/particleemitter.h"
#include "particles/particleaffector.h"
#include "particles/particletarget.h"
#include "particles/particle.h"
#include "particles/particlepool.h"
#include "foundation/util/scriptbind.h"
#include "particles/emitters/particleModelEmitter.h"


namespace Particles
{
	class ParticleTechnique: public Core::RefCounted, Serialization::ISerialize
	{
		__DeclareClass(ParticleTechnique);
		__ScriptBind
	public:
		ParticleTechnique();
		virtual ~ParticleTechnique();

		static GPtr<ParticleTechnique> NullTechnique;

		ParticleSystem* GetParentSystem(void) const;

		void SetParentSystem(ParticleSystem* parentSystem);

		//------------------------Property------------------------------------------------
		void SetName( const Util::String& name);
		const Util::String& GetName(void) const; 

		const Math::float3& GetPosition(void) const;
		void SetPosition(const Math::float3& pos);

		SizeT GetParticleQuota(void) const;
		void SetParticleQuota(SizeT quota);

		const Math::bbox& GetBoundingBox(void) const;
		void SetUseExternBoundingBox(bool useExtern);
		bool IsUseExternBoundingBox(void) const;
		void SetExternBoundingBox( const Math::bbox& externBB );	
		const Math::bbox& GetExternBoundingBox( void ) const;	
		void SetInnerBoundingBox( const Math::bbox& innnerBB);		


		//--------------------------Method----------------------------------------------
		bool IsActive(void) const;

		//[Add libin 2012.10.24]
		bool IsMoveWorldCoord(void) const;
		void SetMoveWorldCoord(bool bSet);

		bool IsLoadEmitterMesh(void) const;
		void SetLoadEmitterMesh(bool bset);

		Math::float3 GetDerivedPosition(void);
		Math::float3 GetDerivedScale(void);
		Math::quaternion GetDerivedRotation(void);
		Math::matrix44	GetParentMatrix() const;


		void ResetPool(int nQuota);

		void _prepareParticles();

		//--------------------------InterLoop----------------------------------------------
		void _onActivate(void);

		void _onDeactivate(void);

		void _update( Timing::Time frameTime, IndexT frameIndex );

		void _preparePool(void);

		void _addTime();

		void _emitParticles(void);

		void _preProcessParticles(void);

		void _processParticles(void);

		void _postProcessParticles(void);

		void _executeEmitParticles(ParticleEmitterPtr& emitter, SizeT requested);

		void _initParticleForEmission(Particle* particle);

		void _processAffectors(Particle* particle, bool firstActiveParticle);		
	
		bool _isExpired(Particle* particle, Timing::Time frameTime);

		void _switchToMoveWorldCoord(bool isWorld);

		//-----------------------Emitter-------------------------------------------------
		SizeT GetEmitterCount(void) const;

		const ParticleEmitterPtr& GetEmitter(IndexT i) const;

		IndexT FindEmitter( const ParticleEmitterPtr& emitter ) const;

		void AddEmitter( const ParticleEmitterPtr& emitter, IndexT index = -1 );

		void RemoveEmitter( const ParticleEmitterPtr& emitter );

		void RemoveEmitter( IndexT index);

		void RemoveAllEmitter(void);

		//-----------------------Affector-------------------------------------------------
		SizeT GetAffectorCount(void) const;

		const ParticleAffectorPtr& GetAffector(IndexT i) const;

		const ParticleAffectorPtr& GetAffectorByName( const Core::Rtti& pRtti ) const;

		IndexT FindAffector( const ParticleAffectorPtr& affector ) const;

		void AddAffector( const ParticleAffectorPtr& affector, IndexT index = -1 );

		void RemoveAffector( const ParticleAffectorPtr& affector );

		void RemoveAffector( IndexT index );

		void RemoveAllAffector(void);

		//------------------------target------------------------------------------------
		const ParticleTargetPtr& GetTarget(void) const;

		void SetTarget( const ParticleTargetPtr& );

		void RemoveTarget();

		/**
		*/
		Timing::Time GetEmitterTime();
		void  SetEmitterTime(Timing::Time emtTime);
		
#ifdef __GENESIS_EDITOR__	//	edtior use
	private:
		bool		mIsSavedInit;
		Math::MinMaxCurve mBoxX;
		Math::MinMaxCurve mBoxY;
		Math::MinMaxCurve mBoxZ;
		Math::MinMaxCurve mSpehereRadius;
		Math::MinMaxCurve mSphereHem;
		Math::MinMaxCurve mSphereSlice;
		Math::MinMaxCurve mConeRadius1;
		Math::MinMaxCurve mConeRadius2;
		Math::MinMaxCurve mConeAngle;
		Math::MinMaxCurve mConeHeight;
#endif
	protected:
		typedef Util::Array<ParticleEmitterPtr> ParticleEmitterList;
		typedef ParticleEmitterList::Iterator ParticleEmitterIterator;

		typedef Util::Array<ParticleAffectorPtr> ParticleAffectorList;
		typedef ParticleAffectorList::Iterator ParticleAffectorIterator;

		ParticleSystem*			mParentSystem;
		bool					mIsActive;
		Timing::Time			mLiveTime;		
		Timing::Time			mCurFrameTime;	
		IndexT					mFrameIndex;

		Util::String			mName;

		Math::float3			mPosition;

		bool					mUseExternBB;
		Math::bbox				mExternBB;
		Math::bbox				mInnerBB;

		SizeT					mQuota;
		bool					mPoolNeedIncrease;
		ParticlePoolPtr			mPool;

		bool					mIsMoveWorldCoord;

		ParticleEmitterList		mEmitters;
		ParticleAffectorList	mAffectors;
		ParticleTargetPtr		mTarget;


		bool					mIsLoadEmitterMesh;

	public:
		void Reset();
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		// copy 
		virtual void CopyFrom( const GPtr<ParticleTechnique>& technique );
	};
	//------------------------------------------------------------------------
	inline
	ParticleSystem* 
	ParticleTechnique::GetParentSystem(void) const
	{
		return mParentSystem;
	}
	//------------------------------------------------------------------------
	inline
	void 
	ParticleTechnique::SetParentSystem(ParticleSystem* parentSystem)
	{
		mParentSystem = parentSystem;
	}
	//------------------------------------------------------------------------
	inline
	void 
	ParticleTechnique::SetName( const Util::String& name)
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
	ParticleTechnique::GetName(void) const
	{
		return mName;
	}
	//------------------------------------------------------------------------
	inline
	bool 
	ParticleTechnique::IsActive(void) const
	{
		return mIsActive;
	}
	//------------------------------------------------------------------------
	inline
	const Math::float3& 
	ParticleTechnique::GetPosition(void) const
	{
		return mPosition;
	}
	//------------------------------------------------------------------------
	inline
	void 
	ParticleTechnique::SetPosition(const Math::float3& pos)
	{
		mPosition = pos;
	}
	//------------------------------------------------------------------------
	inline
	SizeT 
	ParticleTechnique::GetParticleQuota(void) const
	{
		return mQuota;		
	}
	inline
	const Math::bbox& 
	ParticleTechnique::GetBoundingBox(void) const
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
	ParticleTechnique::SetUseExternBoundingBox(bool useExtern)
	{
		mUseExternBB = useExtern;
	}
	//------------------------------------------------------------------------
	inline
	bool 
	ParticleTechnique::IsUseExternBoundingBox(void) const
	{
		return mUseExternBB;
	}
	//------------------------------------------------------------------------
	inline
	void 
	ParticleTechnique::SetExternBoundingBox( const Math::bbox& externBB )
	{
		mExternBB = externBB;
	}
	//------------------------------------------------------------------------
	inline
	const Math::bbox& 
	ParticleTechnique::GetExternBoundingBox( void ) const
	{
		return mExternBB;
	}
	//------------------------------------------------------------------------
	inline
	void 
	ParticleTechnique::SetInnerBoundingBox( const Math::bbox& innnerBB)
	{
		mInnerBB = innnerBB;
	}
	//------------------------------------------------------------------------
	inline
	SizeT 
	ParticleTechnique::GetEmitterCount(void) const
	{
		return mEmitters.Size();
	}
	//------------------------------------------------------------------------
	inline
	SizeT 
	ParticleTechnique::GetAffectorCount(void) const
	{
		return mAffectors.Size();
	}

	//------------------------------------------------------------------------
	inline
	const ParticleTargetPtr& 
	ParticleTechnique::GetTarget(void) const
	{
		return mTarget;
	}
	//------------------------------------------------------------------------
	inline
	bool 
	ParticleTechnique::_isExpired(Particle* particle, Timing::Time frameTime)
	{
		return particle->mTimeToLive < frameTime;
	}
	//-------------------------------------------------------------------------
	inline Timing::Time ParticleTechnique::GetEmitterTime()
	{
		return mLiveTime;
	}
	//-------------------------------------------------------------------------
	inline void  ParticleTechnique::SetEmitterTime(Timing::Time emtTime)
	{
		mLiveTime = emtTime;
	}
	//--------------------------------------------------------------------------------
	inline bool  ParticleTechnique::IsMoveWorldCoord(void) const
	{
		return mIsMoveWorldCoord;
	}
	//--------------------------------------------------------------------------------
	inline void  ParticleTechnique::SetMoveWorldCoord(bool bSet)
	{
		_switchToMoveWorldCoord(bSet);
		mIsMoveWorldCoord = bSet;
	}
	//--------------------------------------------------------------------------------
	inline bool  ParticleTechnique::IsLoadEmitterMesh(void) const
	{
		return mIsLoadEmitterMesh;
	}
	inline void  ParticleTechnique::SetLoadEmitterMesh(bool bset)
	{
		mIsLoadEmitterMesh = bset;
	}
	//--------------------------------------------------------------------------------
}







#endif // __particletechnique_H__
