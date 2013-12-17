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
#include "particles/emitters/particleSphereSurfaceEmitter.h"

namespace Particles
{
	using namespace Serialization;

	const char* s_SSERadius = "Radius";
	const char* s_SSEInner = "InnerSphere";

	const char* s_SSEHemi = "Hemi";
	const char* s_SSESlice = "Slice";
	extern const char* s_KeyFrameCount;
	extern const char* s_CurveKey;
	extern const char* s_CurveValue;

	class SphereSurfaceEmitterSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( SphereSurfaceEmitter* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			else if (2 == ver )
			{
				Load_2(obj, pReader);
				return;
			}
			else if (3 == ver )
			{
				Load_3(obj, pReader);
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
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(SphereSurfaceEmitter* obj, SerializeReader* pReader)
		{

			Math::scalar radius;
			pReader->SerializeFloat(s_SSERadius, radius );
		}
		//------------------------------------------------------------------------
		void Load_2(SphereSurfaceEmitter* obj, SerializeReader* pReader)
		{
			Load_1(obj,pReader );

			bool inner;
			pReader->SerializeBool(s_SSEInner, inner );
		}
		//------------------------------------------------------------------------
		void Load_3(SphereSurfaceEmitter* obj, SerializeReader* pReader)
		{
			Util::Array<Math::float2> keyframelist;		
			Math::MinMaxCurve* curve = obj->getMinMaxCurve(Emitter_SphereRadius);
			_serializeLoadCurveOld(pReader, keyframelist, s_SSERadius, s_CurveKey);
			_setCurveOld(keyframelist,keyframelist,curve);
			curve->SetCurveState(Math::MinMaxCurve::Curve);

			curve = obj->getMinMaxCurve(Emitter_SphereHem);
			_serializeLoadCurveOld(pReader, keyframelist, s_SSEHemi, s_CurveKey);
			_setCurveOld(keyframelist,keyframelist,curve);	
			curve->SetCurveState(Math::MinMaxCurve::Curve);

			curve = obj->getMinMaxCurve(Emitter_SphereSlice);
			_serializeLoadCurveOld(pReader, keyframelist, s_SSESlice, s_CurveKey);
			_setCurveOld(keyframelist,keyframelist,curve);	
			curve->SetCurveState(Math::MinMaxCurve::Curve);
		}
		//------------------------------------------------------------------------
		void Load_4(SphereSurfaceEmitter* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_SphereRadius),s_SSERadius,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_SphereHem),s_SSEHemi,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_SphereSlice),s_SSESlice,s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Load_5(SphereSurfaceEmitter* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_SphereRadius),s_SSERadius,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_SphereHem),s_SSEHemi,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_SphereSlice),s_SSESlice,s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Save( const SphereSurfaceEmitter* obj, SerializeWriter* pWriter )
		{
			_serializeSaveMinMaxCurve(pWriter,*((SphereSurfaceEmitter* )obj)->getMinMaxCurve(Emitter_SphereRadius),s_SSERadius,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((SphereSurfaceEmitter* )obj)->getMinMaxCurve(Emitter_SphereHem),s_SSEHemi,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((SphereSurfaceEmitter* )obj)->getMinMaxCurve(Emitter_SphereSlice),s_SSESlice,s_CurveKey);
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion SphereSurfaceEmitter::GetVersion() const
	{
		return 5;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void SphereSurfaceEmitter::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		SphereSurfaceEmitterSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void SphereSurfaceEmitter::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		SphereSurfaceEmitterSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void SphereSurfaceEmitter::CopyFrom( const ParticleEmitterPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<SphereSurfaceEmitter> source = target.downcast<SphereSurfaceEmitter>();

		_serializeCopyMinMaxCurve(source->mRadiusCurve, this->mRadiusCurve);
		_serializeCopyMinMaxCurve(source->mHemCurve, this->mHemCurve);
		_serializeCopyMinMaxCurve(source->mSliceCurve, this->mSliceCurve);

	}

}