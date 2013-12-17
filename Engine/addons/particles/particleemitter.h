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
#ifndef __particleemitter_H__
#define __particleemitter_H__
#include "particles/particle_fwd_decl.h"
#include "foundation/util/scriptbind.h"


namespace Particles
{
	class ParticleEmitter: public Core::RefCounted, Serialization::ISerialize
	{
		__DeclareClass( ParticleEmitter )
			__ScriptBind
	public:
		ParticleEmitter();
		virtual ~ParticleEmitter();

		static GPtr<ParticleEmitter> NullEmitter;

		ParticleSystem* GetParentSystem(void) const;
		void SetParentSystem( ParticleSystem* technique);

		bool IsActive(void) const;


		IndexT IncreaseRandomSeed(void) const;

		virtual SizeT CalculateRequestedParticles(Timing::Time mCurFrameTime);

		virtual SizeT _calculateRequestedParticles( Timing::Time timeElapsed );

		//---------------------------property---------------------------------------------

		void SetName( const Util::String& name);
		const Util::String& GetName(void) const; 

		void SetEnable(bool enable);
		bool IsEnable(void) const;

		// add new interface for curve  [11/16/2012 libin_pg]
		void SetParticleInitFromType(EmitFromType _emittype);
		EmitFromType GetParticleInitFromType(void) const;

		//---------------------------internal Loop---------------------------------------------
		virtual void _onActivate(void);

		virtual void _onDeactivate(void);

		virtual void _emit(Particle* particle);

		virtual void _initParticlePosition(Particle* particle);
		virtual void _initParticleDirection(Particle* particle);
		virtual void _initParticleVelocity(Particle* particle);
		virtual void _initParticleOrientation(Particle* particle);
		virtual void _initParticleMass(Particle* particle);
		virtual void _initParticleColour(Particle* particle);
		virtual void _initParticleTextureCoords(Particle* particle);
		virtual void _initParticleTimeToLive(Particle* particle);
		virtual void _initParticleDimensions(Particle* particle);
		virtual void _initParticleRotation(Particle* particle);


		bool			IsAxialVelocity() const;
		void			SetAxialVelocity(bool);

		bool			IsAxialSize() const;
		void			SetAxialSize(bool);

		virtual Math::MinMaxCurve* getMinMaxCurve(ParticleCurveType pct);


		/**
		*/
		void SetNormalDir(bool);
		bool IsNormalDir(void) const;

		void SetNormalSpeed(float speed);
		float GetNormalSpeed(void) const;


		void SetLoop(bool loop);
		bool GetLoop();
		//Duration translate to System
		void SetDuration(float duration);
		float GetDuration();
		//DelayTime translate to System
		void SetDelayTime(Timing::Time delayTime);
		Timing::Time GetDelayTime();
	private:
		bool mShapeVisible;
	public:
		void SetShapeVisible(bool);
		bool GetShapeVisible(void) const;

	protected:
		ParticleSystem* mParentSystem;
		bool mIsActive;
		mutable IndexT mRandomSeed;

		Util::String mName;
		bool mEnable;

		Math::MinMaxCurve	mMinMaxRate;

		Math::scalar mRemainder;


		Math::float3 mDirection, mUpVector;


		bool					mIsAxialVelocity;
		Math::MinMaxCurve	mMinMaxVelocityX;
		Math::MinMaxCurve	mMinMaxVelocityY;
		Math::MinMaxCurve	mMinMaxVelocityZ;

		Math::quaternion mMinOrientation, mMaxOrientation;
		Math::scalar mMinMass, mMaxMass;
		Math::ColorF mMinColor, mMaxColor;

		Math::MinMaxCurve		mMinMaxColorR;
		Math::MinMaxCurve		mMinMaxColorG;
		Math::MinMaxCurve		mMinMaxColorB;
		Math::MinMaxCurve		mMinMaxColorA;


		IndexT mMinTexCoordIndex, mMaxTexCoordIndex;

		Math::MinMaxCurve			mMinMaxLiveTime;

		Math::float3 mMinSize, mMaxSize;

		bool							mIsAxialSize;
		Math::MinMaxCurve			mMinMaxSizeX;
		Math::MinMaxCurve			mMinMaxSizeY;
		Math::MinMaxCurve			mMinMaxSizeZ;

		Math::MinMaxCurve			mMinMaxRotationSpeed;

		Math::MinMaxCurve         mMinMaxInitRotaion;

		//- [Add LIBIN] Sprint16 2012-10-22
		//  [11/16/2012 libin_pg]
		EmitFromType			mInitFromType;
		bool							mIsNormalDir;
		float					mNormalSpeed;


		bool					mLoop;
		float					mDuration;
		Timing::Time			mDelayTime;
	public:
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		// copy 
		virtual void CopyFrom( const ParticleEmitterPtr& emitter );

	};
	//------------------------------------------------------------------------
	inline
		ParticleSystem* 
		ParticleEmitter::GetParentSystem(void) const
	{
		return mParentSystem;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleEmitter::SetParentSystem( ParticleSystem* technique)
	{
		mParentSystem = technique;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleEmitter::SetName( const Util::String& name)
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
		ParticleEmitter::GetName(void) const
	{
		return mName;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		ParticleEmitter::IsActive(void) const
	{
		return mIsActive;
	}
	//------------------------------------------------------------------------
	inline
		IndexT 
		ParticleEmitter::IncreaseRandomSeed(void) const
	{
		return ++mRandomSeed;
	}
	//------------------------------------------------------------------------
	inline
		bool
		ParticleEmitter::IsEnable(void) const
	{
		return mEnable;
	}
	//--------------------------------------------------------------------------------
	inline void ParticleEmitter::SetParticleInitFromType(EmitFromType _type)
	{
		mInitFromType = _type;
	}
	//--------------------------------------------------------------------------------
	inline EmitFromType ParticleEmitter::GetParticleInitFromType(void) const
	{
		return mInitFromType;
	}
	//--------------------------------------------------------------------------------
	inline bool		ParticleEmitter::IsAxialVelocity() const
	{
		return mIsAxialVelocity;
	}
	//--------------------------------------------------------------------------------
	inline void		ParticleEmitter::SetAxialVelocity(bool bset)
	{
		mIsAxialVelocity = bset;
	}
	//--------------------------------------------------------------------------------
	inline bool		ParticleEmitter::IsAxialSize() const
	{
		return mIsAxialSize;
	}
	//--------------------------------------------------------------------------------
	inline void		ParticleEmitter::SetAxialSize(bool bset)
	{
		mIsAxialSize = bset;
	}
	//--------------------------------------------------------------------------------
	inline void ParticleEmitter::SetNormalDir(bool bset)
	{
		mIsNormalDir = bset;
	}
	//--------------------------------------------------------------------------------
	inline bool ParticleEmitter::IsNormalDir(void) const
	{
		return mIsNormalDir;
	}
	//--------------------------------------------------------------------------------
	inline void ParticleEmitter::SetNormalSpeed(float speed)
	{
		mNormalSpeed = speed;
	}
	//--------------------------------------------------------------------------------
	inline float ParticleEmitter::GetNormalSpeed(void) const
	{
		return mNormalSpeed;
	}
	//----------------------------------------------------------------------------------
	inline 	void ParticleEmitter::SetShapeVisible(bool visible)
	{
		mShapeVisible = visible;
	}
	inline bool ParticleEmitter::GetShapeVisible(void) const
	{
		return mShapeVisible;
	}
	inline void ParticleEmitter::SetLoop(bool loop)
	{
		mLoop = loop;
	}
	inline bool ParticleEmitter::GetLoop()
	{
		return mLoop;
	}
	inline void ParticleEmitter::SetDuration(float duration)
	{
		mDuration = duration;
	}
	inline float ParticleEmitter::GetDuration()
	{
		return mDuration;
	}
	inline void ParticleEmitter::SetDelayTime(Timing::Time delayTime)
	{
		mDelayTime = delayTime;
	}
	inline Timing::Time ParticleEmitter::GetDelayTime()
	{
		return mDelayTime;
	}
}

#endif // __particleemitter_H__
