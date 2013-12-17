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
#include "particles/affectors/particleLimitAffector.h"

namespace Particles
{
	using namespace Serialization;

	const static char* s_SeparateAxis = "SeparateAxis";
	const static char* s_Dampen = "Dampen";
	const static char* s_MinMaxState = "MinMaxState";

	const static char* s_KeyFrameCount = "KeyFrameCount";
	const static char* s_CurveKey = "CurveKey";
	const static char* s_CurveValue = "CurveValue";

	const static char* s_RandomAxis = "RandomAxis";

	const static char* s_DampenXMin = "DampenXMin";
	const static char* s_DampenXMax = "DampenXMax";

	const static char* s_DampenYMin = "DampenXMin";
	const static char* s_DampenYMax = "DampenXMax";

	const static char* s_DampenZMin = "DampenZMin";
	const static char* s_DampenZMax = "DampenZMax";

	const static char* s_DampenMAGMin = "DampenMAGMin";
	const static char* s_DampenMAGMax = "DampenMAGMax";

	const static char* s_DampenRandom = "RandomDampen";


	class DampenAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( LimitAffector* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}	
			else if( 2 == ver)
			{
				Load_2(obj, pReader);
				return;
			}
			else if( 3 == ver)
			{
				Load_3(obj,pReader);
				return;
			}
			else if( 4 == ver)
			{
				Load_4(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}	

		//------------------------------------------------------------------------
		void Load_1(LimitAffector* obj, SerializeReader* pReader)
		{
			bool rnd;
			pReader->SerializeBool(s_RandomAxis,rnd);
			if(rnd)
			{
				obj->getMinMaxCurve(Affector_LimitX)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_LimitY)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_LimitZ)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_LimitX)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_LimitY)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_LimitZ)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			float dampen;
			pReader->SerializeFloat(s_Dampen,dampen);
			//obj->SetDampen(dampen);

			Util::Array<Math::float2> keyframelist1;		
			Util::Array<Math::float2> keyframelist2;		
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Affector_LimitX);
			_serializeLoadCurveOld(pReader, keyframelist1, s_DampenXMin, s_CurveKey);	
			_serializeLoadCurveOld(pReader, keyframelist2, s_DampenXMax, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	


			curve = obj->getMinMaxCurve(Affector_LimitY);
			_serializeLoadCurveOld(pReader, keyframelist1, s_DampenYMin, s_CurveKey);		
			_serializeLoadCurveOld(pReader, keyframelist2, s_DampenYMax, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);		


			curve = obj->getMinMaxCurve(Affector_LimitZ);
			_serializeLoadCurveOld(pReader, keyframelist1, s_DampenZMin, s_CurveKey);	
			_serializeLoadCurveOld(pReader, keyframelist2, s_DampenZMax, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);
		}
		//ver2--------------------------------------------------------------------
		void Load_2(LimitAffector* obj, SerializeReader* pReader)
		{
			bool rnd;
			pReader->SerializeBool(s_RandomAxis,rnd);
			if(rnd)
			{
				obj->getMinMaxCurve(Affector_LimitX)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_LimitY)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_LimitZ)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_LimitX)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_LimitY)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_LimitZ)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			pReader->SerializeBool(s_DampenRandom,rnd);
			if(rnd)
			{
				obj->getMinMaxCurve(Affector_LimitValue)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_LimitValue)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			Util::Array<Math::float2> keyframelist1;
			Util::Array<Math::float2> keyframelist2;		
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Affector_LimitX);
			_serializeLoadCurveOld(pReader, keyframelist1, s_DampenXMin, s_CurveKey);		
			_serializeLoadCurveOld(pReader, keyframelist2, s_DampenXMax, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);			


			curve = obj->getMinMaxCurve(Affector_LimitY);
			_serializeLoadCurveOld(pReader, keyframelist1, s_DampenYMin, s_CurveKey);		
			_serializeLoadCurveOld(pReader, keyframelist2, s_DampenYMax, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);		

			curve = obj->getMinMaxCurve(Affector_LimitZ);
			_serializeLoadCurveOld(pReader, keyframelist1, s_DampenZMin, s_CurveKey);		
			_serializeLoadCurveOld(pReader, keyframelist2, s_DampenZMax, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	

			curve = obj->getMinMaxCurve(Affector_LimitValue);
			_serializeLoadCurveOld(pReader, keyframelist1, s_DampenMAGMin, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_DampenMAGMax, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);
		}
		//------------------------------------------------------------------------
		void Load_3(LimitAffector* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_LimitX),"DampenX",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_LimitY),"DampenY",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_LimitZ),"DampenZ",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_LimitValue),"DampenMAG",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Load_4(LimitAffector* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_LimitX),"DampenX",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_LimitY),"DampenY",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_LimitZ),"DampenZ",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_LimitValue),"DampenMAG",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Save( const LimitAffector* obj, SerializeWriter* pWriter )
		{
			_serializeSaveMinMaxCurve(pWriter,*((LimitAffector* )obj)->getMinMaxCurve(Affector_LimitX),"DampenX",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((LimitAffector* )obj)->getMinMaxCurve(Affector_LimitY),"DampenY",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((LimitAffector* )obj)->getMinMaxCurve(Affector_LimitZ),"DampenZ",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((LimitAffector* )obj)->getMinMaxCurve(Affector_LimitValue),"DampenMAG",s_CurveKey);
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion LimitAffector::GetVersion() const
	{
		return 4;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void LimitAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		DampenAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void LimitAffector::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		DampenAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void LimitAffector::CopyFrom( const ParticleAffectorPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<LimitAffector> source = target.downcast<LimitAffector>();

		_serializeCopyMinMaxCurve(source->mLimitX,this->mLimitX);
		_serializeCopyMinMaxCurve(source->mLimitY,this->mLimitY);
		_serializeCopyMinMaxCurve(source->mLimitZ,this->mLimitZ);
		_serializeCopyMinMaxCurve(source->mLimitValue,this->mLimitValue);
	}


}