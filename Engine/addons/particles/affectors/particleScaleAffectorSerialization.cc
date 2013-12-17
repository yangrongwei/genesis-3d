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
#include "particles/affectors/particleScaleAffector.h"

namespace Particles
{
	using namespace Serialization;

	const static char* s_IsRandomScale = "RandomScale";
	const static char* s_IsAxialScale = "AxialScale";

	extern const char*		s_KeyFrameCount;
	extern const char*		s_CurveKey;
	extern const char*		s_CurveValue;

	class ScaleAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ScaleAffector* obj,  SVersion ver, SerializeReader* pReader )
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
			else if(3 == ver)
			{
				Load_3(obj,pReader);
				return;
			}
			else if(4 == ver)
			{
				Load_4(obj,pReader);
				return;
			}
			else if(5 == ver)
			{
				Load_5(obj,pReader);
				return;
			}
			else if(6 == ver)
			{
				Load_6(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(ScaleAffector* obj, SerializeReader* pReader)
		{	
		}
		//------------------------------------------------------------------------
		void Load_2(ScaleAffector* obj, SerializeReader* pReader)
		{			
		}
		//--------------------------------------------------------------------------------
		void Load_3(ScaleAffector* obj, SerializeReader* pReader)
		{
			bool isRnd;
			pReader->SerializeBool(s_IsRandomScale,isRnd);

			if(isRnd)
			{
				obj->getMinMaxCurve(Affector_ScaleX)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_ScaleY)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_ScaleZ)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_ScaleX)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_ScaleY)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_ScaleZ)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			Util::Array<Math::float2> keyframelist1;		
			Util::Array<Math::float2> keyframelist2;	
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Affector_ScaleX);
			_serializeLoadCurveOld(pReader, keyframelist1,  "ScaleXMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2,  "ScaleXMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);


			curve = obj->getMinMaxCurve(Affector_ScaleY);
			_serializeLoadCurveOld(pReader, keyframelist1,  "ScaleYMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2,  "ScaleYMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			curve = obj->getMinMaxCurve(Affector_ScaleZ);
			_serializeLoadCurveOld(pReader, keyframelist1,  "ScaleZmin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2,  "ScaleZMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);
		}
		//------------------------------------------------------------------------
		void Load_4(ScaleAffector* obj, SerializeReader* pReader)
		{
			bool isAxial;
			pReader->SerializeBool(s_IsAxialScale,isAxial);
			obj->SetAxialScale(isAxial);

			Load_3(obj,pReader);
		}
		//------------------------------------------------------------------------
		void Load_5(ScaleAffector* obj, SerializeReader* pReader)
		{
			bool isAxial;
			pReader->SerializeBool(s_IsAxialScale,isAxial);
			obj->SetAxialScale(isAxial);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_ScaleX),"ScaleX",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_ScaleY),"ScaleY",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_ScaleZ),"ScaleZ",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Load_6(ScaleAffector* obj, SerializeReader* pReader)
		{
			bool isAxial;
			pReader->SerializeBool(s_IsAxialScale,isAxial);
			obj->SetAxialScale(isAxial);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_ScaleX),"ScaleX",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_ScaleY),"ScaleY",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_ScaleZ),"ScaleZ",s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Save( const ScaleAffector* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeBool(s_IsAxialScale, obj->IsAxialScale() );

			_serializeSaveMinMaxCurve(pWriter,*((ScaleAffector* )obj)->getMinMaxCurve(Affector_ScaleX),"ScaleX",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ScaleAffector* )obj)->getMinMaxCurve(Affector_ScaleY),"ScaleY",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ScaleAffector* )obj)->getMinMaxCurve(Affector_ScaleZ),"ScaleZ",s_CurveKey);	
		}
	};
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ScaleAffector::GetVersion() const
	{
		return 6;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ScaleAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		ScaleAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ScaleAffector::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		ScaleAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ScaleAffector::CopyFrom( const ParticleAffectorPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<ScaleAffector> source = target.downcast<ScaleAffector>();

		SetAxialScale(source->IsAxialScale());
		_serializeCopyMinMaxCurve(source->mScaleX,this->mScaleX);
		_serializeCopyMinMaxCurve(source->mScaleY,this->mScaleY);
		_serializeCopyMinMaxCurve(source->mScaleZ,this->mScaleZ);
	}

}