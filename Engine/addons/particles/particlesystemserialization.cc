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
#include "particles/particlesystem.h"
#include "particles/particletechnique.h"

namespace Particles
{
	using namespace Serialization;

	const char* s_ParticleSystemName = "ParticleSystemName";
	const char* s_ChildTechniqueCount = "ChildTechniqueCount";

	const char* s_IsPreLoop = "IsPreLoop";
	const char* s_PlayBackTime = "PlayBackTime";
	const char* s_Transparency = "Transparency";
	const char* s_PlayOnAwake = "PlayOnAwake";
	const char* s_PlayRateScale = "PlayRateScale";


	const char* s_SystemUseExternBB = "SystemUseExternBB";
	const char* s_SystemExternBB = "SystemExternBB";
	const char* s_SystemQuota = "SystemQuota";
	const char* s_SysEmitterCount = "EmitterCount";
	const char* s_SysAffectorCount = "AffectorCount";
	const char* s_SysTargetCount = "TargetCount";
	const char* s_SysIsMoveWorldCoor = "IsMoveWorldCoor";
	const char* s_ParticleFPS = "ParticleFPS";
	const char* s_sysLoop = "Loop";
	const char* s_sysDuration = "Duration";
	const char* s_sysDelay = "DelayTime";
	const char* s_sysUpdateUnVis = "UpdateUnVis";

	class ParticleSystemSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ParticleSystem* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			else if ( 2 == ver )
			{
				Load_2(obj, pReader);
				return;
			}
			else if ( 3 == ver )
			{
				Load_3(obj, pReader);
				return;
			}
			else if(4 == ver)
			{
				Load_4(obj, pReader);
				return;
			}
			else if(5 == ver)
			{
				Load_5(obj,pReader);
				return;
			}
			else if(6 == ver)
			{
				Load_6(obj,pReader);
				return;
			}
			else if(7 == ver)
			{
				Load_7(obj,pReader);
				return;
			}
			else if(8 == ver)
			{
				Load_8(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(ParticleSystem* obj, SerializeReader* pReader)
		{
			Util::String name;
			pReader->SerializeString(s_ParticleSystemName, name );
			obj->SetName( name );

			SizeT parSystemCount = 0;
			pReader->SerializeInt( s_ChildTechniqueCount, parSystemCount );
			for ( IndexT index = 0; index < parSystemCount; ++index )
			{
				GPtr<ParticleTechnique> parSystem = pReader->SerializeObject<ParticleTechnique>();

				obj->SetUseExternBoundingBox( parSystem->IsUseExternBoundingBox() );
				obj->SetExternBoundingBox( parSystem->GetExternBoundingBox() );
				int quota =  parSystem->GetParticleQuota();
				obj->SetMoveWorldCoord(parSystem->IsMoveWorldCoord());

				SizeT emmiterCount = parSystem->GetEmitterCount();
				for ( IndexT index = 0; index < emmiterCount; ++index )
				{
					const ParticleEmitterPtr& emitter = parSystem->GetEmitter( index );

					ParticleEmitterPtr dest = Clone( emitter );
					obj->SetEmitter( dest );
					obj->SetLoop(dest->GetLoop());
					obj->SetDelayTime(dest->GetDelayTime());
					obj->SetDuration(dest->GetDuration());
					if ( emitter->IsA( Particles::ModelEmitter::RTTI ) )
						obj->SetLoadEmitterMesh(false);
				}


				SizeT affectorCount = parSystem->GetAffectorCount();
				for( IndexT index = 0; index < affectorCount; ++index )
				{
					const ParticleAffectorPtr& affector = parSystem->GetAffector(index);

					ParticleAffectorPtr dest = Clone( affector );
					obj->AddAffector( dest );
				}

				const ParticleTargetPtr& target = parSystem->GetTarget();
				if ( target.isvalid() )
				{
					ParticleTargetPtr dest = Clone( target );
					obj->SetTarget( dest );
				}

				obj->SetParticleQuota( quota);
			}

		}
		//  [10/29/2012 libin_pg]
		void Load_2(ParticleSystem* obj, SerializeReader* pReader)
		{
			bool PreLoop;
			pReader->SerializeBool(s_IsPreLoop, PreLoop );
			obj->SetPreLoop( PreLoop );

			float PlayBackTime;
			pReader->SerializeFloat(s_PlayBackTime, PlayBackTime );
			obj->SetPlayBackTime( PlayBackTime );

			int Transparency;
			pReader->SerializeInt(s_Transparency, Transparency );
			obj->SetTransparency( (ubyte)Transparency );

			Load_1(obj, pReader);
		}
		//------------------------------------------------------------------------
		void Load_3(ParticleSystem* obj, SerializeReader* pReader)
		{
			bool playOnAwake;
			pReader->SerializeBool(s_PlayOnAwake, playOnAwake );
#ifdef __GENESIS_EDITOR__
			obj->SetPlayOnAwake( playOnAwake);
#else
			obj->SetPlayOnAwake( playOnAwake, true );
#endif

			Load_2(obj, pReader);
		}
		//------------------------------------------------------------------------
		void Load_4(ParticleSystem* obj, SerializeReader* pReader)
		{
			float rateScale;
			pReader->SerializeFloat(s_PlayRateScale,rateScale);
			obj->SetPlayRateScale(rateScale);
			Load_3(obj, pReader);
		}
		//------------------------------------------------------------------------
		void Load_5(ParticleSystem* obj, SerializeReader* pReader)
		{
			float rateScale;
			pReader->SerializeFloat(s_PlayRateScale,rateScale);
			obj->SetPlayRateScale(rateScale);

			bool playOnAwake;
			pReader->SerializeBool(s_PlayOnAwake, playOnAwake );
#ifdef __GENESIS_EDITOR__
			obj->SetPlayOnAwake( playOnAwake);
#else
			obj->SetPlayOnAwake( playOnAwake, true );
#endif
			bool PreLoop;
			pReader->SerializeBool(s_IsPreLoop, PreLoop );
			obj->SetPreLoop( PreLoop );

			float PlayBackTime;
			pReader->SerializeFloat(s_PlayBackTime, PlayBackTime );
			obj->SetPlayBackTime( PlayBackTime );

			int Transparency;
			pReader->SerializeInt(s_Transparency, Transparency );
			obj->SetTransparency( (ubyte)Transparency );


			Util::String name;
			pReader->SerializeString(s_ParticleSystemName, name );
			obj->SetName( name );

			bool moveType;
			pReader->SerializeBool(s_SysIsMoveWorldCoor, moveType );
			obj->SetMoveWorldCoord( moveType );


			bool useExternBB;
			pReader->SerializeBool( s_SystemUseExternBB, useExternBB );
			obj->SetUseExternBoundingBox( useExternBB );

			Math::bbox bb;
			pReader->SerializeBBox( s_SystemExternBB, bb );
			obj->SetExternBoundingBox( bb );

			SizeT quota;
			pReader->SerializeInt( s_SystemQuota, quota );

			ParticleEmitterPtr emitter = pReader->SerializeObject<ParticleEmitter>();
			n_assert( emitter.isvalid() );
			obj->SetEmitter( emitter );
			obj->SetLoop(emitter->GetLoop());
			obj->SetDelayTime(emitter->GetDelayTime());
			obj->SetDuration(emitter->GetDuration());
			if ( emitter->IsA( Particles::ModelEmitter::RTTI ) )
				obj->SetLoadEmitterMesh(false);

			SizeT affectorCount;
			pReader->SerializeInt( s_SysAffectorCount,  affectorCount);
			for( IndexT index = 0; index < affectorCount; ++index )
			{
				ParticleAffectorPtr affector =  pReader->SerializeObject<ParticleAffector>();
				n_assert( affector.isvalid() );
				obj->AddAffector( affector );
			}

			ParticleTargetPtr target = pReader->SerializeObject<ParticleTarget>();
			n_assert( target.isvalid() );
			obj->SetTarget( target );

			obj->SetParticleQuota( quota );
		}
		void Load_6(ParticleSystem* obj, SerializeReader* pReader)
		{
			float rateScale;
			pReader->SerializeFloat(s_PlayRateScale,rateScale);
			obj->SetPlayRateScale(rateScale);

			bool playOnAwake;
			pReader->SerializeBool(s_PlayOnAwake, playOnAwake );
#ifdef __GENESIS_EDITOR__
			obj->SetPlayOnAwake( playOnAwake);
#else
			obj->SetPlayOnAwake( playOnAwake, true );
#endif
			bool PreLoop;
			pReader->SerializeBool(s_IsPreLoop, PreLoop );
			obj->SetPreLoop( PreLoop );

			float PlayBackTime;
			pReader->SerializeFloat(s_PlayBackTime, PlayBackTime );
			obj->SetPlayBackTime( PlayBackTime );

			int Transparency;
			pReader->SerializeInt(s_Transparency, Transparency );
			obj->SetTransparency( (ubyte)Transparency );


			Util::String name;
			pReader->SerializeString(s_ParticleSystemName, name );
			obj->SetName( name );

			bool moveType;
			pReader->SerializeBool(s_SysIsMoveWorldCoor, moveType );
			obj->SetMoveWorldCoord( moveType );


			bool useExternBB;
			pReader->SerializeBool( s_SystemUseExternBB, useExternBB );
			obj->SetUseExternBoundingBox( useExternBB );

			Math::bbox bb;
			pReader->SerializeBBox( s_SystemExternBB, bb );
			obj->SetExternBoundingBox( bb );

			SizeT fps;
			pReader->SerializeInt(s_ParticleFPS,fps);
			obj->SetParticleFPS(fps);

			ParticleEmitterPtr emitter = pReader->SerializeObject<ParticleEmitter>();
			n_assert( emitter.isvalid() );
			obj->SetEmitter( emitter );
			obj->SetLoop(emitter->GetLoop());
			obj->SetDelayTime(emitter->GetDelayTime());
			obj->SetDuration(emitter->GetDuration());
			if ( emitter->IsA( Particles::ModelEmitter::RTTI ) )
				obj->SetLoadEmitterMesh(false);

			SizeT affectorCount;
			pReader->SerializeInt( s_SysAffectorCount,  affectorCount);
			for( IndexT index = 0; index < affectorCount; ++index )
			{
				ParticleAffectorPtr affector =  pReader->SerializeObject<ParticleAffector>();
				n_assert( affector.isvalid() );
				obj->AddAffector( affector );
			}

			ParticleTargetPtr target = pReader->SerializeObject<ParticleTarget>();
			n_assert( target.isvalid() );
			obj->SetTarget( target );

			SizeT quota;
			pReader->SerializeInt( s_SystemQuota, quota );
			obj->SetParticleQuota( quota );
		}
		void Load_7(ParticleSystem* obj, SerializeReader* pReader)
		{
			float rateScale;
			pReader->SerializeFloat(s_PlayRateScale,rateScale);
			obj->SetPlayRateScale(rateScale);

			bool playOnAwake;
			pReader->SerializeBool(s_PlayOnAwake, playOnAwake );
#ifdef __GENESIS_EDITOR__
			obj->SetPlayOnAwake( playOnAwake);
#else
			obj->SetPlayOnAwake( playOnAwake, true );
#endif
			bool PreLoop;
			pReader->SerializeBool(s_IsPreLoop, PreLoop );
			obj->SetPreLoop( PreLoop );

			float PlayBackTime;
			pReader->SerializeFloat(s_PlayBackTime, PlayBackTime );
			obj->SetPlayBackTime( PlayBackTime );

			int Transparency;
			pReader->SerializeInt(s_Transparency, Transparency );
			obj->SetTransparency( (ubyte)Transparency );


			Util::String name;
			pReader->SerializeString(s_ParticleSystemName, name );
			obj->SetName( name );

			bool moveType;
			pReader->SerializeBool(s_SysIsMoveWorldCoor, moveType );
			obj->SetMoveWorldCoord( moveType );


			bool useExternBB;
			pReader->SerializeBool( s_SystemUseExternBB, useExternBB );
			obj->SetUseExternBoundingBox( useExternBB );

			Math::bbox bb;
			pReader->SerializeBBox( s_SystemExternBB, bb );
			obj->SetExternBoundingBox( bb );

			SizeT fps;
			pReader->SerializeInt(s_ParticleFPS,fps);
			obj->SetParticleFPS(fps);

			ParticleEmitterPtr emitter = pReader->SerializeObject<ParticleEmitter>();
			n_assert( emitter.isvalid() );
			obj->SetEmitter( emitter );
			if ( emitter->IsA( Particles::ModelEmitter::RTTI ) )
				obj->SetLoadEmitterMesh(false);

			SizeT affectorCount;
			pReader->SerializeInt( s_SysAffectorCount,  affectorCount);
			for( IndexT index = 0; index < affectorCount; ++index )
			{
				ParticleAffectorPtr affector =  pReader->SerializeObject<ParticleAffector>();
				n_assert( affector.isvalid() );
				obj->AddAffector( affector );
			}

			ParticleTargetPtr target = pReader->SerializeObject<ParticleTarget>();
			n_assert( target.isvalid() );
			obj->SetTarget( target );

			SizeT quota;
			pReader->SerializeInt( s_SystemQuota, quota );
			obj->SetParticleQuota( quota );

			bool loop;
			pReader->SerializeBool(s_sysLoop,loop);
			obj->SetLoop(loop);

			float duration;
			pReader->SerializeFloat(s_sysDuration,duration);
			obj->SetDuration(duration);

			float delay;
			pReader->SerializeFloat(s_sysDelay,delay);
			obj->SetDelayTime(delay);
		}
		void Load_8(ParticleSystem* obj, SerializeReader* pReader)
		{
			Load_7(obj,pReader);
			bool updateUnVis;
			pReader->SerializeBool(s_sysUpdateUnVis,updateUnVis);
			obj->SetUpdateUnVis(updateUnVis);
		}
		//------------------------------------------------------------------------
		void Save( const ParticleSystem* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeFloat(s_PlayRateScale,obj->GetPlayRateScale());
			pWriter->SerializeBool(s_PlayOnAwake, obj->GetPlayOnAwake() );
			pWriter->SerializeBool(s_IsPreLoop, obj->IsPreLoop() );
			pWriter->SerializeFloat(s_PlayBackTime, obj->GetPlayBackTime() );
			pWriter->SerializeInt(s_Transparency, obj->GetTransparency() );

			pWriter->SerializeString(s_ParticleSystemName, obj->GetName() );


			pWriter->SerializeBool( s_SysIsMoveWorldCoor, obj->IsMoveWorldCoord() );


			pWriter->SerializeBool( s_SystemUseExternBB, obj->IsUseExternBoundingBox() );
			pWriter->SerializeBBox( s_SystemExternBB, obj->GetExternBoundingBox() );
			pWriter->SerializeInt(s_ParticleFPS,obj->GetParticleFPS());

			const ParticleEmitterPtr& emitter = obj->GetEmitter();
			pWriter->SerializeObject( emitter );


			SizeT affectorCount = obj->GetAffectorCount();
			pWriter->SerializeInt( s_SysAffectorCount,  affectorCount);
			for( IndexT index = 0; index < affectorCount; ++index )
			{
				const ParticleAffectorPtr& affector = obj->GetAffector(index);
				pWriter->SerializeObject( affector );
			}

			const ParticleTargetPtr& target = obj->GetTarget();
			pWriter->SerializeObject(target);

			pWriter->SerializeInt( s_SystemQuota, obj->GetParticleQuota() );		
			pWriter->SerializeBool(s_sysLoop,obj->GetLoop());
			pWriter->SerializeFloat(s_sysDuration,(float)obj->GetDuration());
			pWriter->SerializeFloat(s_sysDelay,(float)obj->GetDelayTime());
			pWriter->SerializeBool(s_sysUpdateUnVis,obj->GetUpdateUnVis());
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ParticleSystem::GetVersion() const
	{
		return 8;
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleSystem::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		ParticleSystemSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleSystem::Save( SerializeWriter* pWriter ) const
	{
		ParticleSystemSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ParticleSystem::CopyFrom( const ParticleSystemPtr& parSystem )
	{
		n_assert( parSystem.isvalid() ); 
		SetPlayRateScale(parSystem->GetPlayRateScale());
		SetName( parSystem->GetName() );
		SetPreLoop(parSystem->IsPreLoop() );
		SetPlayBackTime(parSystem->GetPlayBackTime() );
		SetTransparency( parSystem->GetTransparency() );

		bool playOnAwake = parSystem->GetPlayOnAwake();

#ifdef __GENESIS_EDITOR__
		SetPlayOnAwake(playOnAwake);
#else
		SetPlayOnAwake(playOnAwake, true);
#endif

		SetUseExternBoundingBox( parSystem->IsUseExternBoundingBox() );
		SetExternBoundingBox( parSystem->GetExternBoundingBox() );
		SetMoveWorldCoord(parSystem->IsMoveWorldCoord());
		SetParticleFPS(parSystem->GetParticleFPS());
		const ParticleEmitterPtr& emitter = parSystem->GetEmitter();

		ParticleEmitterPtr dest = Clone( emitter );
		SetEmitter( dest );

		SizeT affectorCount = parSystem->GetAffectorCount();
		for( IndexT index = 0; index < affectorCount; ++index )
		{
			const ParticleAffectorPtr& affector = parSystem->GetAffector(index);

			ParticleAffectorPtr dest = Clone( affector );
			AddAffector( dest );
		}

		const ParticleTargetPtr& target = parSystem->GetTarget();
		if ( target.isvalid() )
		{
			ParticleTargetPtr dest = Clone( target );
			SetTarget( dest );
		}

		SetParticleQuota( parSystem->GetParticleQuota() );

		SetDuration(parSystem->GetDuration());
		SetLoop(parSystem->GetLoop());
		SetDelayTime(parSystem->GetDelayTime());
		SetUpdateUnVis(parSystem->GetUpdateUnVis());
	}

}