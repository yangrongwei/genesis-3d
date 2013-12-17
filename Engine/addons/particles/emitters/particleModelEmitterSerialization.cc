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
#include "particles/emitters/particleModelEmitter.h"
#include "particles/particleemitter.h"

namespace Particles
{
	using namespace Serialization;

	const char* s_MeshName = "MeshName";
	const char* s_EmitType = "EmitType";

	class ModelEmitterSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ModelEmitter* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(ModelEmitter* obj, SerializeReader* pReader)
		{
			Util::String meshName;
			pReader->SerializeString(s_MeshName, meshName );
			obj->SetMeshName( meshName);

			int emitType;
			pReader->SerializeInt(s_EmitType, emitType );
			obj->SetMeshEmitType( (MeshEmitType)emitType);
		}
		//------------------------------------------------------------------------
		void Save( const ModelEmitter* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeString(s_MeshName, obj->GetMeshName() );
			pWriter->SerializeInt(s_EmitType, obj->GetMeshEmitType() );
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ModelEmitter::GetVersion() const
	{
		return 1;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ModelEmitter::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		ModelEmitterSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ModelEmitter::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		ModelEmitterSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ModelEmitter::CopyFrom( const ParticleEmitterPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<ModelEmitter> source = target.downcast<ModelEmitter>();

		SetMeshName(source->GetMeshName());
		SetMeshEmitType(source->GetMeshEmitType());
	}

}