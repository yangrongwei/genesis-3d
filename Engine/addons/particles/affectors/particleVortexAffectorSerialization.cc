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
#include "particles/affectors/particleVortexAffector.h"

namespace Particles
{
	using namespace Serialization;

	const static char* s_RotationSpeed = "RotationSpeed";
	const static char* s_RotationVector = "RotationVector";

	const char* 	s_IsVortexRandomRotationSpeed = "IsVortexRandomRotationSpeed";
	const char* 	s_IsVortexRandomNormal = "IsVortexRandomNormal";

	extern const char* s_KeyFrameCount;
	extern const char* s_CurveKey;
	extern const char* s_CurveValue;

	class VortexAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( VortexAffector* obj,  SVersion ver, SerializeReader* pReader )
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
			else if( 4 == ver)
			{
				Load_4(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(VortexAffector* obj, SerializeReader* pReader)
		{
			Math::scalar DynRotationSpeed;
			pReader->SerializeFloat(s_RotationSpeed, DynRotationSpeed );

			Math::vector RotationVector;
			pReader->SerializeFloat4(s_RotationVector, RotationVector );
		}
		//------------------------------------------------------------------------
		void Load_2(VortexAffector* obj, SerializeReader* pReader)
		{
			bool IsRotationSpeed;
			pReader->SerializeBool(s_IsVortexRandomRotationSpeed, IsRotationSpeed );
			if(IsRotationSpeed)
			{
				obj->getMinMaxCurve(Affector_Vortex)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_Vortex)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			Util::Array<Math::float2> keyframelist1;		
			Util::Array<Math::float2> keyframelist2;		
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Affector_Vortex);
			_serializeLoadCurveOld(pReader, keyframelist1, s_RotationSpeed, s_CurveKey);	
			_serializeLoadCurveOld(pReader, keyframelist2, s_RotationSpeed, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);		

			bool IsRandomNormal;
			pReader->SerializeBool(s_IsVortexRandomNormal, IsRandomNormal );

			if(IsRandomNormal)
			{
				obj->getMinMaxCurve(Affector_VortexX)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_VortexY)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_VortexZ)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_VortexX)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_VortexY)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_VortexZ)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			curve = obj->getMinMaxCurve(Affector_VortexX);
			_serializeLoadCurveOld(pReader, keyframelist1, s_RotationVector, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_RotationVector, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	

			curve = obj->getMinMaxCurve(Affector_VortexY);
			_serializeLoadCurveOld(pReader, keyframelist1, s_RotationVector, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_RotationVector, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);		

			curve = obj->getMinMaxCurve(Affector_VortexZ);
			_serializeLoadCurveOld(pReader, keyframelist1, s_RotationVector, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_RotationVector, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	
		}
		//-----------------------------------------------------------------------
		void Load_3(VortexAffector* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_Vortex),"Vortex",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_VortexX),"VortexX",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_VortexY),"VortexY",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_VortexZ),"VortexZ",s_CurveKey);
		}
		//-----------------------------------------------------------------------
		void Load_4(VortexAffector* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_Vortex),"Vortex",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_VortexX),"VortexX",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_VortexY),"VortexY",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_VortexZ),"VortexZ",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Save( const VortexAffector* obj, SerializeWriter* pWriter )
		{
			_serializeSaveMinMaxCurve(pWriter,*((VortexAffector* )obj)->getMinMaxCurve(Affector_Vortex),"Vortex",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((VortexAffector* )obj)->getMinMaxCurve(Affector_VortexX),"VortexX",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((VortexAffector* )obj)->getMinMaxCurve(Affector_VortexY),"VortexY",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((VortexAffector* )obj)->getMinMaxCurve(Affector_VortexZ),"VortexZ",s_CurveKey);
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion VortexAffector::GetVersion() const
	{
		return 4;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void VortexAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		VortexAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void VortexAffector::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		VortexAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void VortexAffector::CopyFrom( const ParticleAffectorPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<VortexAffector> source = target.downcast<VortexAffector>();

		_serializeCopyMinMaxCurve(source->mMinMaxRotationSpeed,this->mMinMaxRotationSpeed);
		_serializeCopyMinMaxCurve(source->mMinMaxNormalX,this->mMinMaxNormalX);
		_serializeCopyMinMaxCurve(source->mMinMaxNormalY,this->mMinMaxNormalY);
		_serializeCopyMinMaxCurve(source->mMinMaxNormalZ,this->mMinMaxNormalZ);
	}

}