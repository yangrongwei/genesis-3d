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
#include "particles/affectors/particleLinearForceAffector.h"

namespace Particles
{
	using namespace Serialization;

	const static char* s_ForceVector = "ForceVector";
	const static char* s_TimeStep = "TimeStep";
	const static char* s_ForceApp = "ForceApp";

	const char* s_SpaceCoord = "SpaceCoord";
	const char* s_RandomForce = "RandomForce";

	extern const char* s_KeyFrameCount;
	extern const char* s_CurveKey;
	extern const char* s_CurveValue;

	class LinearForceAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( LinearForceAffector* obj,  SVersion ver, SerializeReader* pReader )
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
			else if(3 == ver)
			{
				Load_3(obj, pReader);
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
		void Load_1(LinearForceAffector* obj, SerializeReader* pReader)
		{
			Math::float3 forcevector;
			pReader->SerializeFloat3(s_ForceVector, forcevector);

			Math::scalar timestep;
			pReader->SerializeFloat(s_TimeStep, timestep);
			obj->SetTimeStep(timestep);

			int forceapp;
			pReader->SerializeInt(s_ForceApp, forceapp);
			obj->SetForceApplication(forceapp);
		}
		//--------------------------------------------------------------------------------
		void Load_2(LinearForceAffector* obj, SerializeReader* pReader)
		{
			int coordtype;
			pReader->SerializeInt(s_SpaceCoord, coordtype);
			obj->SetSpaceCoordType((SpaceCoordType)coordtype);

			bool Israndom;
			pReader->SerializeBool(s_RandomForce, Israndom);

			if(Israndom)
			{
				obj->getMinMaxCurve(Affector_ForceX)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_ForceY)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_ForceZ)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_ForceX)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_ForceY)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_ForceZ)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			Util::Array<Math::float2> keyframelist1;		
			Util::Array<Math::float2> keyframelist2;		
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Affector_ForceX);
			_serializeLoadCurveOld(pReader, keyframelist1, "ForceXMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2,  "ForceXMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);


			curve = obj->getMinMaxCurve(Affector_ForceY);
			_serializeLoadCurveOld(pReader, keyframelist1,  "ForceYMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2,  "ForceYMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			curve = obj->getMinMaxCurve(Affector_ForceZ);
			_serializeLoadCurveOld(pReader, keyframelist1,  "ForceZMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2,  "ForceZMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);
		}
		//--------------------------------------------------------------------------------
		void Load_3(LinearForceAffector* obj, SerializeReader* pReader)
		{
			int coordtype;
			pReader->SerializeInt(s_SpaceCoord, coordtype);
			obj->SetSpaceCoordType((SpaceCoordType)coordtype);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_ForceX),"ForceX",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_ForceY),"ForceY",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_ForceZ),"ForceZ",s_CurveKey);
		}
		//--------------------------------------------------------------------------------
		void Load_4(LinearForceAffector* obj, SerializeReader* pReader)
		{
			int coordtype;
			pReader->SerializeInt(s_SpaceCoord, coordtype);
			obj->SetSpaceCoordType((SpaceCoordType)coordtype);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_ForceX),"ForceX",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_ForceY),"ForceY",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_ForceZ),"ForceZ",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Save( const LinearForceAffector* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeInt(s_SpaceCoord, (int)obj->GetSpaceCoordType() );		

			_serializeSaveMinMaxCurve(pWriter,*((LinearForceAffector* )obj)->getMinMaxCurve(Affector_ForceX),"ForceX",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((LinearForceAffector* )obj)->getMinMaxCurve(Affector_ForceY),"ForceY",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((LinearForceAffector* )obj)->getMinMaxCurve(Affector_ForceZ),"ForceZ",s_CurveKey);
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion LinearForceAffector::GetVersion() const
	{
		return 4;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void LinearForceAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		LinearForceAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void LinearForceAffector::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		LinearForceAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void LinearForceAffector::CopyFrom( const ParticleAffectorPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<LinearForceAffector> source = target.downcast<LinearForceAffector>();

		SetSpaceCoordType(source->mSpaceCoord);

		_serializeCopyMinMaxCurve(source->mForceVectorX,this->mForceVectorX);
		_serializeCopyMinMaxCurve(source->mForceVectorY,this->mForceVectorY);
		_serializeCopyMinMaxCurve(source->mForceVectorZ,this->mForceVectorZ);
	}

}