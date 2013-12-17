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
#include "particles/affectors/particleColorAffector.h"

namespace Particles
{
	using namespace Serialization;

	const static char* s_ColorCount = "ColorCount";
	const static char* s_ColorKey = "ColorKey";
	const static char* s_ColorValue = "ColorValue";
	const static char* s_TimeAlpha = "TimeAlpha";
	const static char* s_MinAlpha = "MinAlpha";
	const static char* s_MaxAlpha = "MaxAlpha";
	const static char* s_AlphaCount = "AlphaCount";
	const static char* s_AlphaValue = "AlphaValue";
	const static char* s_ColorRandom = "ColorRandom";
	const static char*	s_ColorControlType = "ColorControlType";
	extern const char* s_KeyFrameCount;
	extern const char* s_CurveKey;
	extern const char* s_CurveValue;

	class ColorAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ColorAffector* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			else if(2 == ver)
			{
				Load_2(obj, pReader);
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
			else if(7 == ver)
			{
				Load_7(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_7(ColorAffector* obj, SerializeReader* pReader)
		{
			int mColorControlType;
			pReader->SerializeInt(s_ColorControlType, mColorControlType );
			obj->SetColorContrlType((ColorContrlType)mColorControlType);

			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_ColorR),"colorR",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_ColorG),"colorG",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_ColorB),"colorB",s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Affector_ColorA),"colorA",s_CurveKey);

		}
		//------------------------------------------------------------------------
		void Load_6(ColorAffector* obj, SerializeReader* pReader)
		{
			int mColorControlType;
			pReader->SerializeInt(s_ColorControlType, mColorControlType );
			obj->SetColorContrlType((ColorContrlType)mColorControlType);

			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_ColorR),"colorR",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_ColorG),"colorG",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_ColorB),"colorB",s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Affector_ColorA),"colorA",s_CurveKey);

		}
		//------------------------------------------------------------------------
		void Load_5(ColorAffector* obj, SerializeReader* pReader)
		{
			bool colorRandom;
			pReader->SerializeBool(s_ColorRandom,colorRandom);
			if(colorRandom)
			{
				obj->getMinMaxCurve(Affector_ColorR)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_ColorG)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_ColorB)->SetCurveState(Math::MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Affector_ColorA)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Affector_ColorR)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_ColorG)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_ColorB)->SetCurveState(Math::MinMaxCurve::Curve);
				obj->getMinMaxCurve(Affector_ColorA)->SetCurveState(Math::MinMaxCurve::Curve);
			}
			Load_4(obj,pReader);
		}
		//------------------------------------------------------------------------
		void Load_3(ColorAffector* obj, SerializeReader* pReader)
		{
			SizeT colorcount;
			pReader->SerializeInt(s_ColorCount, colorcount );

			for ( IndexT index = 0; index < colorcount; ++index )
			{
				Math::scalar colorkey;
				Math::float4 colorvalue;
				pReader->SerializeFloat(s_ColorKey, colorkey);
				pReader->SerializeFloat4(s_ColorValue, colorvalue );
			}

			bool timeAlpha;
			pReader->SerializeBool(s_TimeAlpha,timeAlpha);

			float minAlpha;
			pReader->SerializeFloat(s_MinAlpha,minAlpha);

			float maxAlpha;
			pReader->SerializeFloat(s_MaxAlpha,maxAlpha);

			SizeT alphaCount;
			pReader->SerializeInt(s_AlphaCount,alphaCount);

			for ( IndexT index = 0; index < alphaCount; ++index )
			{
				float alpha;
				pReader->SerializeFloat(s_AlphaValue,alpha);
			}
		}
		//------------------------------------------------------------------------
		void Load_2(ColorAffector* obj, SerializeReader* pReader)
		{
			SizeT colorcount;
			pReader->SerializeInt(s_ColorCount, colorcount );

			for ( IndexT index = 0; index < colorcount; ++index )
			{
				Math::scalar colorkey;
				Math::float4 colorvalue;
				pReader->SerializeFloat(s_ColorKey, colorkey);
				pReader->SerializeFloat4(s_ColorValue, colorvalue );
			}

			bool timeAlpha;
			pReader->SerializeBool(s_TimeAlpha,timeAlpha);

			float minAlpha;
			pReader->SerializeFloat(s_MinAlpha,minAlpha);

			float maxAlpha;
			pReader->SerializeFloat(s_MaxAlpha,maxAlpha);

		}
		//------------------------------------------------------------------------
		void Load_1(ColorAffector* obj, SerializeReader* pReader)
		{
			SizeT colorcount;
			pReader->SerializeInt(s_ColorCount, colorcount );

			for ( IndexT index = 0; index < colorcount; ++index )
			{
				Math::scalar colorkey;
				Math::float4 colorvalue;
				pReader->SerializeFloat(s_ColorKey, colorkey);
				pReader->SerializeFloat4(s_ColorValue, colorvalue );
			}
		}
		//------------------------------------------------------------------------
		void Load_4(ColorAffector* obj, SerializeReader* pReader)
		{
			int mColorControlType;
			pReader->SerializeInt(s_ColorControlType, mColorControlType );
			obj->SetColorContrlType((ColorContrlType)mColorControlType);

			Util::Array<Math::float2> keyframelist1;
			Util::Array<Math::float2> keyframelist2;	
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Affector_ColorR);
			_serializeLoadCurveOld(pReader, keyframelist1, "colorRMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2,  "colorRMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			curve = obj->getMinMaxCurve(Affector_ColorG);
			_serializeLoadCurveOld(pReader, keyframelist1,  "colorGMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, "colorGMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			curve = obj->getMinMaxCurve(Affector_ColorB);
			_serializeLoadCurveOld(pReader, keyframelist1, "colorBMin", s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, "colorBMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			curve = obj->getMinMaxCurve(Affector_ColorA);
			_serializeLoadCurveOld(pReader, keyframelist1,  "colorAMin", s_CurveKey);	
			_serializeLoadCurveOld(pReader, keyframelist2, "colorAMax", s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);
		}
		//------------------------------------------------------------------------
		void Save( const ColorAffector* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeInt(s_ColorControlType, (int)obj->GetColorContrlType() );

			_serializeSaveMinMaxCurve(pWriter,*((ColorAffector* )obj)->getMinMaxCurve(Affector_ColorR),"colorR",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ColorAffector* )obj)->getMinMaxCurve(Affector_ColorG),"colorG",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ColorAffector* )obj)->getMinMaxCurve(Affector_ColorB),"colorB",s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ColorAffector* )obj)->getMinMaxCurve(Affector_ColorA),"colorA",s_CurveKey);

		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ColorAffector::GetVersion() const
	{
		return 7;	//	the current version is 7
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ColorAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		ColorAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ColorAffector::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		ColorAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ColorAffector::CopyFrom( const ParticleAffectorPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<ColorAffector> source = target.downcast<ColorAffector>();

		SetColorContrlType(source->GetColorContrlType());

		_serializeCopyMinMaxCurve(source->mMinMaxColorR,this->mMinMaxColorR);
		_serializeCopyMinMaxCurve(source->mMinMaxColorG,this->mMinMaxColorG);
		_serializeCopyMinMaxCurve(source->mMinMaxColorB,this->mMinMaxColorB);
		_serializeCopyMinMaxCurve(source->mMinMaxColorA,this->mMinMaxColorA);
	}


}