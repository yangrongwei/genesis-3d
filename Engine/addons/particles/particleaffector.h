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
#ifndef __particleaffector_H__
#define __particleaffector_H__
#include "particles/particle_fwd_decl.h"
#include "foundation/util/scriptbind.h"

namespace Particles
{
	class ParticleAffector: public Core::RefCounted , Serialization::ISerialize
	{
		__DeclareClass(ParticleAffector);
		__ScriptBind

	public:

		enum AffectType
		{
			AT_DEFAULT,
			AT_INCREASE,
			AT_DECREASE
		};


		ParticleAffector();
		virtual ~ParticleAffector();
		static GPtr<ParticleAffector> NullAffector;

		ParticleSystem* GetParentSystem(void) const;

		void SetParentSystem( ParticleSystem* technique);

		bool IsActive(void) const;

		Math::float3 GetDerivedPosition(void);

		const AffectType GetAffectType(void) const ;
		void SetAffectType(const AffectType affectSpecialisation);

		void SetEnable(bool enable);
		bool GetEnable(void) const;

		//---------------------------property---------------------------------------------

		void SetName( const Util::String& name);
		const Util::String& GetName(void) const; 

		//---------------------------internal Loop---------------------------------------------
		virtual void _onActivate(void);

		virtual void _onDeactivate(void);

		virtual void _initParticleForEmission(Particle* particle);

		virtual void _preProcessParticles(void);

		virtual void _processParticle( Particle* particle, bool firstParticle);

		virtual void _postProcessParticles();

		virtual void _firstParticle( Particle* particle ); 

		virtual void _affect(Particle* particle );

		virtual void _affectPositon(Particle* particle);

		Math::scalar _calculateAffectSpecialisationFactor (Particle* particle);

		virtual Math::MinMaxCurve* getMinMaxCurve(ParticleCurveType pct);

	protected:
		ParticleSystem* mParentSystem;
		Util::String mName;
		bool mIsActive;
		bool mEnable;

		AffectType mAffectType;


	public:
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		// copy 
		virtual void CopyFrom( const ParticleAffectorPtr& affector );
	};
	//------------------------------------------------------------------------
	inline
		ParticleSystem* 
		ParticleAffector::GetParentSystem(void) const
	{
		return mParentSystem;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleAffector::SetParentSystem( ParticleSystem* technique)
	{
		mParentSystem = technique;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		ParticleAffector::IsActive(void) const
	{
		return mIsActive;
	}
	//-----------------------------------------------------------------------
	inline
		void
		ParticleAffector::SetEnable(bool enable)
	{
		mEnable = enable;
	}
	//-----------------------------------------------------------------------
	inline
		bool
		ParticleAffector::GetEnable(void) const
	{
		return mEnable;
	}
	//------------------------------------------------------------------------
	inline
		void ParticleAffector::SetName( const Util::String& name)
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
		ParticleAffector::GetName(void) const
	{
		return mName;
	}
	//------------------------------------------------------------------------

	inline const ParticleAffector::AffectType ParticleAffector::GetAffectType(void) const 
	{
		return mAffectType;
	}
	//-------------------------------------------------------------------------
	inline void ParticleAffector::SetAffectType(const ParticleAffector::AffectType affectSpecialisation) 
	{
		mAffectType = affectSpecialisation;
	}
	//------------------------------------------------------------------------
	inline void ParticleAffector::_initParticleForEmission(Particle* particle)
	{
		//empty
	}
}







#endif // __particleaffector_H__
