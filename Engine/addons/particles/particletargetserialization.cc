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
#include "particles/particletarget.h"

namespace Particles
{
	using namespace Serialization;

	const char* s_TargetName = "TargetName";
	const char* s_TargetTexRowSize = "TargetTexRowSize";
	const char* s_TargetTexColumnSize = "TargetTexColumnSize";
	const char* s_OrientType = "OrientType";
	const char* s_StretchScale = "StretchScale";

	class ParticleTargetSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ParticleTarget* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			if( 2== ver)
			{
				Load_2(obj, pReader);
				return;
			}
			if( 3== ver)
			{
				Load_3(obj, pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//--------------------------------------------------------------------------------
		void Load_3(ParticleTarget* obj, SerializeReader* pReader)
		{
			Load_2(obj, pReader);

			float stretch;
			pReader->SerializeFloat(s_StretchScale, stretch );
			obj->SetStretchScale(stretch );
		}
		//--------------------------------------------------------------------------------
		void Load_2(ParticleTarget* obj, SerializeReader* pReader)
		{
			Load_1(obj, pReader);

			int orienttype;
			pReader->SerializeInt(s_OrientType, orienttype );
			obj->SetOrientType( (ParticleTarget::OrientType)orienttype );
		}
		//------------------------------------------------------------------------
		void Load_1(ParticleTarget* obj, SerializeReader* pReader)
		{
			Util::String name;
			pReader->SerializeString(s_TargetName, name );
			obj->SetName( name );

			SizeT texRowSize, texColumnSize;
			pReader->SerializeInt(s_TargetTexRowSize, texRowSize );
			pReader->SerializeInt(s_TargetTexColumnSize, texColumnSize );
			obj->SetTexCoordSize(texRowSize, texColumnSize);
		}
		//------------------------------------------------------------------------
		void Save( const ParticleTarget* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeString(s_TargetName, obj->GetName() );
			pWriter->SerializeInt(s_TargetTexRowSize, obj->GetTexCoordRowSize() );
			pWriter->SerializeInt(s_TargetTexColumnSize, obj->GetTexCoordColumnSize() );
			pWriter->SerializeInt(s_OrientType, (int)obj->GetOrientType() );
			pWriter->SerializeFloat(s_StretchScale, obj->GetStretchScale() );
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ParticleTarget::GetVersion() const
	{
		return 3;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleTarget::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		ParticleTargetSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleTarget::Save( SerializeWriter* pWriter ) const
	{
		ParticleTargetSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ParticleTarget::CopyFrom( const ParticleTargetPtr& obj )
	{
		SetName( obj->GetName() );
		SetTexCoordSize( obj->GetTexCoordRowSize(), obj->GetTexCoordColumnSize() );
		SetOrientType( obj->GetOrientType() );
		SetStretchScale(obj->GetStretchScale());
	}

}