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
#include "particles/affectors/particleGravityAffector.h"

namespace Particles
{
	using namespace Serialization;

	const static char* s_Gravity = "Gravity";
	const static char* s_GravityPosition = "GravityPosition";

	const char*			 s_IsRandomGravity = "IsRandomGravity";
	const char*			 s_IsRandomGravityPos = "IsRandomGravityPos";
	extern const char* s_KeyFrameCount;
	extern const char* s_CurveKey;
	extern const char* s_CurveValue;

	class GravityAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( GravityAffector* obj,  SVersion ver, SerializeReader* pReader )
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
			else if( 3 == ver)
			{
				Load_3(obj,pReader);
				return;
			}
			else if(4 == ver)
			{
				Load_4(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(GravityAffector* obj, SerializeReader* pReader)
		{
			Math::scalar gravity;
			pReader->SerializeFloat(s_Gravity, gravity);

			Math::float3 gravityPos;
			pReader->SerializeFloat3(s_GravityPosition, gravityPos	);
		}
		//------------------------------------------------------------------------
		void Load_2(GravityAffector* obj, SerializeReader* pReader)
		{
			bool Isgravity;
			pReader->SerializeBool(s_IsRandomGravity, Isgravity);
			if(Isgravity)
			{
				obj->getMinMaxCurve(Affector_Gravity)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_Gravity)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			Util::Array<Math::float2> keyframelist1;		
			Util::Array<Math::float2> keyframelist2;		
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Affector_Gravity);
			_serializeLoadCurveOld(pReader, keyframelist1, "GravityMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, "GravityMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			bool Isgravitypos;
			pReader->SerializeBool(s_IsRandomGravityPos, Isgravitypos);
			if(s_IsRandomGravityPos)
			{
				obj->getMinMaxCurve(Affector_GravityX)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_GravityY)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_GravityZ)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_GravityX)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_GravityY)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_GravityZ)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			curve = obj->getMinMaxCurve(Affector_GravityX);
			_serializeLoadCurveOld(pReader, keyframelist1, "GravityPosXMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, "GravityPosXMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			curve = obj->getMinMaxCurve(Affector_GravityY);
			_serializeLoadCurveOld(pReader, keyframelist1, "GravityPosYMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, "GravityPosYMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			curve = obj->getMinMaxCurve(Affector_GravityZ);
			_serializeLoadCurveOld(pReader, keyframelist1, "GravityPosZMin", s_CurveKey);	
			_serializeLoadCurveOld(pReader, keyframelist2, "GravityPosZMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);
		}
		//------------------------------------------------------------------------
		void Load_3(GravityAffector* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_Gravity),"Gravity",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_GravityX),"GravityX",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_GravityY),"GravityY",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_GravityZ),"GravityZ",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Load_4(GravityAffector* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_Gravity),"Gravity",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_GravityX),"GravityX",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_GravityY),"GravityY",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_GravityZ),"GravityZ",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Save( const GravityAffector* obj, SerializeWriter* pWriter )
		{
			_serializeSaveMinMaxCurve(pWriter,*((GravityAffector* )obj)->getMinMaxCurve(Affector_Gravity),"Gravity",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((GravityAffector* )obj)->getMinMaxCurve(Affector_GravityX),"GravityX",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((GravityAffector* )obj)->getMinMaxCurve(Affector_GravityY),"GravityY",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((GravityAffector* )obj)->getMinMaxCurve(Affector_GravityZ),"GravityZ",s_CurveKey);

		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion GravityAffector::GetVersion() const
	{
		return 4;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void GravityAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		GravityAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void GravityAffector::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		GravityAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void GravityAffector::CopyFrom( const ParticleAffectorPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<GravityAffector> source = target.downcast<GravityAffector>();

		_serializeCopyMinMaxCurve(source->mMinMaxGravity,this->mMinMaxGravity);
		_serializeCopyMinMaxCurve(source->mMinMaxPosX,this->mMinMaxPosX);
		_serializeCopyMinMaxCurve(source->mMinMaxPosY,this->mMinMaxPosY);
		_serializeCopyMinMaxCurve(source->mMinMaxPosZ,this->mMinMaxPosZ);

	}

}