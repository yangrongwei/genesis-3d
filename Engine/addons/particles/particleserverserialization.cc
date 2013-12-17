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
#include "particles/particleserver.h"
#include "particles/particlesystem.h"

namespace Particles
{
	using namespace Serialization;

	const char* s_TemplateParSystemCount = "TemplateParSystemCount";
	const char* s_TemplateParSystemName = "TemplateParSystemName";

	class ParticleSystemContainerSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ParticleSystemContainer* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(ParticleSystemContainer* obj, SerializeReader* pReader)
		{
			SizeT count;
			pReader->SerializeInt(s_TemplateParSystemCount, count );
			if ( count != 0 )
			{
				obj->mContainer.BeginBulkAdd();
				for ( IndexT index = 0; index < count; ++index )
				{
					Util::String name;
					pReader->SerializeString(s_TemplateParSystemName, name );
					ParticleSystemPtr parSystem = pReader->SerializeObject<ParticleSystem>();

					obj->mContainer.Add(name, parSystem );
				}
				obj->mContainer.EndBulkAdd();
			}


		}
		//------------------------------------------------------------------------
		void Save( const ParticleSystemContainer* obj, SerializeWriter* pWriter )
		{
			SizeT count = obj->mContainer.Size();

			pWriter->SerializeInt(s_TemplateParSystemCount, count );
			for ( IndexT index = 0; index < count; ++index )
			{
				const Util::StringAtom& name = obj->mContainer.KeyAtIndex( index );
				const ParticleSystemPtr& parSystem = obj->mContainer.ValueAtIndex( index ); 
				pWriter->SerializeString(s_TemplateParSystemName, name.AsString() );
				pWriter->SerializeObject( parSystem );
			}
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ParticleSystemContainer::GetVersion() const
	{
		return 1;	//
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleSystemContainer::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		ParticleSystemContainerSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleSystemContainer::Save( SerializeWriter* pWriter ) const
	{
		ParticleSystemContainerSerialization Serialize;
		Serialize.Save( this, pWriter );
	}


}