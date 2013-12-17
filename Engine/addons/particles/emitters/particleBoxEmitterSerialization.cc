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
#include "particles/emitters/particleBoxEmitter.h"

namespace Particles
{
	using namespace Serialization;

	const char* s_Height = "Height";
	const char* s_Width = "Width";
	const char* s_Depth = "Depth";

	const char* s_XRange = "XRange";
	const char* s_YRange = "YRange";
	const char* s_ZRange = "ZRange";

	const char* s_NormalSpeed = "NormalSpeed";

	extern const char* s_KeyFrameCount;
	extern const char* s_CurveKey;
	extern const char* s_CurveValue;

	class BoxEmitterSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( BoxEmitter* obj,  SVersion ver, SerializeReader* pReader )
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
		void Load_6(BoxEmitter* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_BoxSizeX),s_XRange,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_BoxSizeY),s_YRange,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_BoxSizeZ),s_ZRange,s_CurveKey);
		}
		//-----------------------------------------------------------------------
		void Load_4(BoxEmitter* obj, SerializeReader* pReader)
		{
			Math::scalar zSpeed;
			pReader->SerializeFloat(s_NormalSpeed, zSpeed );
			obj->SetNormalSpeed(zSpeed);

			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_BoxSizeX),s_XRange,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_BoxSizeY),s_YRange,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_BoxSizeZ),s_ZRange,s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Load_5(BoxEmitter* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_BoxSizeX),s_XRange,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_BoxSizeY),s_YRange,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_BoxSizeZ),s_ZRange,s_CurveKey);
		}
		//-----------------------------------------------------------------------
		void Load_1(BoxEmitter* obj, SerializeReader* pReader)
		{

		}
		//--------------------------------------------------------------------------------
		void Load_2(BoxEmitter* obj, SerializeReader* pReader)
		{
			Util::Array<Math::float2> keyframelist1;	
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Emitter_BoxSizeX);
			curve->SetCurveState(Math::MinMaxCurve::Curve);
			_serializeLoadCurveOld(pReader, keyframelist1, s_XRange, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist1,curve);			


			curve = obj->getMinMaxCurve(Emitter_BoxSizeY);
			curve->SetCurveState(Math::MinMaxCurve::Curve);
			_serializeLoadCurveOld(pReader, keyframelist1, s_YRange, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist1,curve);


			curve = obj->getMinMaxCurve(Emitter_BoxSizeZ);
			_serializeLoadCurveOld(pReader, keyframelist1, s_ZRange, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist1,curve);		
			curve->SetCurveState(Math::MinMaxCurve::Curve);
		}
		//-----------------------------------------------------------------------
		void Load_3(BoxEmitter* obj, SerializeReader* pReader)
		{
			Math::scalar zSpeed;
			pReader->SerializeFloat(s_NormalSpeed, zSpeed );
			obj->SetNormalSpeed(zSpeed);
			Load_2(obj,pReader);
		}
		//------------------------------------------------------------------------
		void Save( const BoxEmitter* obj, SerializeWriter* pWriter )
		{
			_serializeSaveMinMaxCurve(pWriter,*((BoxEmitter* )obj)->getMinMaxCurve(Emitter_BoxSizeX),s_XRange,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((BoxEmitter* )obj)->getMinMaxCurve(Emitter_BoxSizeY),s_YRange,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((BoxEmitter* )obj)->getMinMaxCurve(Emitter_BoxSizeZ),s_ZRange,s_CurveKey);
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion BoxEmitter::GetVersion() const
	{
		return 6;	//
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void BoxEmitter::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		BoxEmitterSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void BoxEmitter::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		BoxEmitterSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void BoxEmitter::CopyFrom( const ParticleEmitterPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<BoxEmitter> source = target.downcast<BoxEmitter>();
		_serializeCopyMinMaxCurve(source->mCurveRangeX, this->mCurveRangeX);
		_serializeCopyMinMaxCurve(source->mCurveRangeY, this->mCurveRangeY);
		_serializeCopyMinMaxCurve(source->mCurveRangeZ, this->mCurveRangeZ);
	}

}