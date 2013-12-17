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
#include "particles/targets/particleEntityTarget.h"

namespace Particles
{
	using namespace Serialization;

	class EntityTargetSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ParticleEntityTarget* obj,  SVersion ver, SerializeReader* pReader)
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(ParticleEntityTarget* obj, SerializeReader* pReader)
		{

		}
		//------------------------------------------------------------------------
		void Save( const ParticleEntityTarget* obj, SerializeWriter* pWriter )
		{

		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ParticleEntityTarget::GetVersion() const
	{
		return 1;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleEntityTarget::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		EntityTargetSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleEntityTarget::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		EntityTargetSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ParticleEntityTarget::CopyFrom( const ParticleTargetPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<ParticleEntityTarget> source = target.downcast<ParticleEntityTarget>();
	}

}