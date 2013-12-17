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
#include "particles/targets/particlebillboardtarget.h"

namespace Particles
{
	using namespace Serialization;

	const char* s_BillBoardTargetType = "BillBoardTargetType";
	const char* s_BillBoardAlignType = "BillBoardAlignType";

	class BillBoardTargetSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ParticleBillBoardTarget* obj,  SVersion ver, SerializeReader* pReader)
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
		void Load_1(ParticleBillBoardTarget* obj, SerializeReader* pReader)
		{
			int type;
			pReader->SerializeInt(s_BillBoardTargetType, type );
			obj->SetBillBoardType( (ParticleBillBoardTarget::BillBoardType)type);
		}
		//------------------------------------------------------------------------
		void Load_2(ParticleBillBoardTarget* obj, SerializeReader* pReader)
		{
			int type;
			pReader->SerializeInt(s_BillBoardTargetType, type );
			obj->SetBillBoardType( (ParticleBillBoardTarget::BillBoardType)type);
			pReader->SerializeInt(s_BillBoardAlignType, type );
			obj->SetBillBoardAlignType( (ParticleBillBoardTarget::BillboardAlignType) type );
		}
		//------------------------------------------------------------------------
		void Save( const ParticleBillBoardTarget* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeInt(s_BillBoardTargetType, int( obj->GetBillBoardType() ) );
			pWriter->SerializeInt(s_BillBoardAlignType, int(obj->GetBillBoardAlignType()) );
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ParticleBillBoardTarget::GetVersion() const
	{
		return 2;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleBillBoardTarget::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		BillBoardTargetSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleBillBoardTarget::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		BillBoardTargetSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ParticleBillBoardTarget::CopyFrom( const ParticleTargetPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<ParticleBillBoardTarget> source = target.downcast<ParticleBillBoardTarget>();
		SetBillBoardType( source->GetBillBoardType() );
		SetBillBoardAlignType( source->GetBillBoardAlignType() );
	}

}