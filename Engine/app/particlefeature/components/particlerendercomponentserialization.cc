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
#include "particlefeature/components/particlerendercomponent.h"

namespace App
{
	const char* s_ParticleSysName = "ParticleSysName";
	const char* s_ParticleTplFileName = "ParticleTplFileName";
	const char* s_ParticleMeshID = "MeshID";
	const char* s_ParticleTemplateID = "TemplateID";
	const char* s_ParticleMeshLoadPriority = "Priority";
	const char* s_stringEmpty = "Empty";

	class ParticleRenderComponentSerialization
	{
	public:
		ParticleRenderComponentSerialization()
		{

		}
		void Load( ParticleRenderComponent* obj, Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader, args);
				return;
			}
			if( 2 == ver)
			{
				Load_2(obj, pReader, args);
				return;
			}
			if ( 3 == ver )
			{
				Load_3(obj, pReader, args);
				return;
			}
			n_error(" ParticleRenderComponentSerialization::Load unknonw version " );
		}

		void Load_1( ParticleRenderComponent* obj, AppReader* pReader, const Serialization::SerializationArgs* args )
		{
			GPtr<Particles::ParticleSystem> parSystem = pReader->SerializeObject<Particles::ParticleSystem>();
			obj->SetParticleSystem(parSystem);
		}

		void Load_2( ParticleRenderComponent* obj, AppReader* pReader, const Serialization::SerializationArgs* args )
		{

			Util::String templateID;
			pReader->SerializeString(s_ParticleTemplateID, templateID );
			Load_1( obj, pReader, args);
			obj->SetTemplateID(templateID);
		}

		void Load_3( ParticleRenderComponent* obj, AppReader* pReader, const Serialization::SerializationArgs* args )
		{
			Util::String meshID;
			pReader->SerializeString(s_ParticleMeshID, meshID );

			if ( !meshID.IsEmpty())
				obj->SetMeshID(meshID);

			Load_2( obj, pReader, args);
		}

		void Save( const ParticleRenderComponent* obj , AppWriter* pWriter )
		{
			pWriter->SerializeString(s_ParticleMeshID, obj->GetMeshID().AsString() );
			pWriter->SerializeString(s_ParticleTemplateID, obj->GetTemplateID().AsString());

			const GPtr<Particles::ParticleSystem>& parSystem = obj->GetParticleSystem(); 
			pWriter->SerializeObject( parSystem );
		}
	};

}

namespace App
{

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version ParticleRenderComponent::GetVersion() const
	{
		// return 1;	
		// return 2;
		return 3;
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleRenderComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		ParticleRenderComponentSerialization Serialize;
		Serialize.Load( this, ver, pReader,args );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleRenderComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		ParticleRenderComponentSerialization Serialize;
		Serialize.Save(this,  pWriter );
	}

}