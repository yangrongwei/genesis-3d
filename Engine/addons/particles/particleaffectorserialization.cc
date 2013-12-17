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
#include "particles/particleaffector.h"

namespace Particles
{
	using namespace Serialization;

	const char* s_AffectorName = "AffectorName";
	const char* s_AffectSpecialisation = "AffectSpecialisation";
	const char* s_AffectorEnable = "AffectorEnable";

	class ParticleAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ParticleAffector* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			else if(2 == ver)
			{
				Load_2(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(ParticleAffector* obj, SerializeReader* pReader)
		{
			Util::String name;
			pReader->SerializeString( s_AffectorName, name );
			obj->SetName( name );

			int specialisation;
			pReader->SerializeInt( s_AffectSpecialisation , specialisation);
			obj->SetAffectType((ParticleAffector::AffectType)specialisation);
		}
		void Load_2(ParticleAffector* obj, SerializeReader* pReader)
		{
			bool active;
			pReader->SerializeBool(s_AffectorEnable,active);
			obj->SetEnable(active);
			Load_1(obj,pReader);
		}
		//------------------------------------------------------------------------
		void Save( const ParticleAffector* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeBool(s_AffectorEnable,obj->GetEnable());
			pWriter->SerializeString( s_AffectorName, obj->GetName() );	
			pWriter->SerializeInt( s_AffectSpecialisation, (int)obj->GetAffectType());
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ParticleAffector::GetVersion() const
	{
		return 2;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		ParticleAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleAffector::Save( SerializeWriter* pWriter ) const
	{
		ParticleAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ParticleAffector::CopyFrom( const ParticleAffectorPtr& affector )
	{
		n_assert( affector.isvalid() );
		SetName( affector->GetName() );
		SetEnable(affector->GetEnable());
		SetAffectType( affector->GetAffectType());
	}

}