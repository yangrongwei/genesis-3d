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
#include "particles/affectors/particleMovementAffector.h"

namespace Particles
{
	using namespace Serialization;

	const static char* s_Gravity = "Movement";
	const static char* s_GravityPosition = "MovementPosition";

	extern const char* s_KeyFrameCount;
	extern const char* s_CurveKey;
	extern const char* s_CurveValue;

	class MovementAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( MovementAffector* obj,  SVersion ver, SerializeReader* pReader )
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
		void Load_1(MovementAffector* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_MovementSpeed),"Movement",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_MovementX),"MovementX",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_MovementY),"MovementY",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_MovementZ),"MovementZ",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Load_2(MovementAffector* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_MovementSpeed),"Movement",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_MovementX),"MovementX",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_MovementY),"MovementY",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_MovementZ),"MovementZ",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Save( const MovementAffector* obj, SerializeWriter* pWriter )
		{
			_serializeSaveMinMaxCurve(pWriter,*((MovementAffector* )obj)->getMinMaxCurve(Affector_MovementSpeed),"Movement",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((MovementAffector* )obj)->getMinMaxCurve(Affector_MovementX),"MovementX",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((MovementAffector* )obj)->getMinMaxCurve(Affector_MovementY),"MovementY",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((MovementAffector* )obj)->getMinMaxCurve(Affector_MovementZ),"MovementZ",s_CurveKey);

		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion MovementAffector::GetVersion() const
	{
		return 2;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void MovementAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		MovementAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void MovementAffector::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		MovementAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void MovementAffector::CopyFrom( const ParticleAffectorPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<MovementAffector> source = target.downcast<MovementAffector>();

		_serializeCopyMinMaxCurve(source->mMinMaxSpeed,this->mMinMaxSpeed);
		_serializeCopyMinMaxCurve(source->mMinMaxPosX,this->mMinMaxPosX);
		_serializeCopyMinMaxCurve(source->mMinMaxPosY,this->mMinMaxPosY);
		_serializeCopyMinMaxCurve(source->mMinMaxPosZ,this->mMinMaxPosZ);

	}

}