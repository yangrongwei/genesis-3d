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

namespace Particles
{
	using namespace Serialization;

	const char* s_TechniqueName = "TechniqueName";
	const char* s_TechniquePosition = "TechniquePosition";
	const char* s_TechniqueUseExternBB = "TechniqueUseExternBB";
	const char* s_TechniqueExternBB = "TechniqueExternBB";
	const char* s_TechniqueQuota = "TechniqueQuota";
	const char* s_EmitterCount = "EmitterCount";
	const char* s_AffectorCount = "AffectorCount";
	const char* s_TargetCount = "TargetCount";

	const char* s_IsMoveWorldCoor = "IsMoveWorldCoor";

	class ParticleTechniqueSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ParticleTechnique* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			if ( 2 == ver )
			{
				Load_2(obj, pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_2(ParticleTechnique* obj, SerializeReader* pReader)
		{

			bool moveType;
			pReader->SerializeBool(s_IsMoveWorldCoor, moveType );
			obj->SetMoveWorldCoord( moveType );

			Load_1(obj, pReader);
		}
		//------------------------------------------------------------------------
		void Load_1(ParticleTechnique* obj, SerializeReader* pReader)
		{
			Util::String name;
			pReader->SerializeString( s_TechniqueName, name );
			obj->SetName( name );

			Math::float3 pos;
			pReader->SerializeFloat3( s_TechniquePosition, pos );
			obj->SetPosition( pos );

			bool useExternBB;
			pReader->SerializeBool( s_TechniqueUseExternBB, useExternBB );
			obj->SetUseExternBoundingBox( useExternBB );

			Math::bbox bb;
			pReader->SerializeBBox( s_TechniqueExternBB, bb );
			obj->SetExternBoundingBox( bb );

			SizeT quota;
			pReader->SerializeInt( s_TechniqueQuota, quota );
			obj->SetParticleQuota( quota );

			SizeT emmiterCount;
			pReader->SerializeInt( s_EmitterCount,  emmiterCount);
			for ( IndexT index = 0; index < emmiterCount; ++index )
			{
				ParticleEmitterPtr emitter = pReader->SerializeObject<ParticleEmitter>();
				n_assert( emitter.isvalid() );
				obj->AddEmitter( emitter );

				if ( emitter->IsA( Particles::ModelEmitter::RTTI ) )
					obj->SetLoadEmitterMesh(false);
			}

			SizeT affectorCount;
			pReader->SerializeInt( s_AffectorCount,  affectorCount);
			for( IndexT index = 0; index < affectorCount; ++index )
			{
				ParticleAffectorPtr affector =  pReader->SerializeObject<ParticleAffector>();
				n_assert( affector.isvalid() );
				obj->AddAffector( affector );
			}

			SizeT targetCount;
			pReader->SerializeInt( s_TargetCount, targetCount );
			if ( targetCount == 1 )
			{
				ParticleTargetPtr target = pReader->SerializeObject<ParticleTarget>();
				n_assert( target.isvalid() );
				obj->SetTarget( target );
			}


		}
		//------------------------------------------------------------------------
		void Save( const ParticleTechnique* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeBool( s_IsMoveWorldCoor, obj->IsMoveWorldCoord() );

			pWriter->SerializeString( s_TechniqueName, obj->GetName() );
			pWriter->SerializeFloat3( s_TechniquePosition, obj->GetPosition() );
			pWriter->SerializeBool( s_TechniqueUseExternBB, obj->IsUseExternBoundingBox() );
			pWriter->SerializeBBox( s_TechniqueExternBB, obj->GetExternBoundingBox() );
			pWriter->SerializeInt( s_TechniqueQuota, obj->GetParticleQuota() );

			SizeT emmiterCount = obj->GetEmitterCount();
			pWriter->SerializeInt( s_EmitterCount,  emmiterCount);
			for ( IndexT index = 0; index < emmiterCount; ++index )
			{
				const ParticleEmitterPtr& emitter = obj->GetEmitter( index );
				pWriter->SerializeObject( emitter );
			}

			SizeT affectorCount = obj->GetAffectorCount();
			pWriter->SerializeInt( s_AffectorCount,  affectorCount);
			for( IndexT index = 0; index < affectorCount; ++index )
			{
				const ParticleAffectorPtr& affector = obj->GetAffector(index);
				pWriter->SerializeObject( affector );
			}

			const ParticleTargetPtr& target = obj->GetTarget();
			if ( target.isvalid() )
			{
				pWriter->SerializeInt( s_TargetCount, 1 );
				pWriter->SerializeObject( target );
			}
			else
			{
				pWriter->SerializeInt( s_TargetCount, 0 );
			}
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ParticleTechnique::GetVersion() const
	{
		return 2;	//
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleTechnique::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		ParticleTechniqueSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleTechnique::Save( SerializeWriter* pWriter ) const
	{
		ParticleTechniqueSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ParticleTechnique::CopyFrom( const GPtr<ParticleTechnique>& technique )
	{
		SetName( technique->GetName() );
		SetPosition( technique->GetPosition() );
		SetUseExternBoundingBox( technique->IsUseExternBoundingBox() );
		SetExternBoundingBox( technique->GetExternBoundingBox() );
		SetParticleQuota( technique->GetParticleQuota() );
		SetMoveWorldCoord(technique->IsMoveWorldCoord());

		SizeT emmiterCount = technique->GetEmitterCount();
		for ( IndexT index = 0; index < emmiterCount; ++index )
		{
			const ParticleEmitterPtr& emitter = technique->GetEmitter( index );

			ParticleEmitterPtr dest = Clone( emitter );
			AddEmitter( dest );
		}

		SizeT affectorCount = technique->GetAffectorCount();
		for( IndexT index = 0; index < affectorCount; ++index )
		{
			const ParticleAffectorPtr& affector = technique->GetAffector(index);

			ParticleAffectorPtr dest = Clone( affector );
			AddAffector( dest );
		}

		const ParticleTargetPtr& target = technique->GetTarget();
		if ( target.isvalid() )
		{
			ParticleTargetPtr dest = Clone( target );
			SetTarget( dest );
		}
	}
}