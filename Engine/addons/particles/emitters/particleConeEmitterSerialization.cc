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
#include "particles/emitters/particleConeEmitter.h"
#include "particles/particleemitter.h"

namespace Particles
{
	using namespace Serialization;

	const char* s_ConeAngle = "ConeAngle";
	const char* s_ConeInnerRadius = "ConeInnerRadius";
	const char* s_ConeOuterRadius = "ConeOuterRadius";
	const char* s_ConeHeight = "ConeHeight";

	extern const char* s_KeyFrameCount;
	extern const char* s_CurveKey;
	extern const char* s_CurveValue;

	class ConeEmitterSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ConeEmitter* obj,  SVersion ver, SerializeReader* pReader )
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
		void Load_1(ConeEmitter* obj, SerializeReader* pReader)
		{
			Math::scalar mAngle;
			pReader->SerializeFloat(s_ConeAngle, mAngle );
			obj->SetConeAngle( mAngle);

			float		InnerRadius;
			pReader->SerializeFloat(s_ConeInnerRadius, InnerRadius );
			obj->SetConeInnerRadius( InnerRadius);

			float		OuterRadius;
			pReader->SerializeFloat(s_ConeOuterRadius, OuterRadius );
			obj->SetConeOuterRadius( OuterRadius);

			float		mConeHeight;
			pReader->SerializeFloat(s_ConeHeight, mConeHeight );
			obj->SetConeHeight( mConeHeight);
		}
		//------------------------------------------------------------------------
		void Load_2(ConeEmitter* obj, SerializeReader* pReader)
		{

		}
		//------------------------------------------------------------------------
		void Load_3(ConeEmitter* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_ConeRadiusInner),s_ConeInnerRadius,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_ConeRadiusOuter),s_ConeOuterRadius,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_ConeAngle),s_ConeAngle,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_ConeHeight),s_ConeHeight,s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Load_4(ConeEmitter* obj, SerializeReader* pReader)
		{
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ConeRadiusInner),s_ConeInnerRadius,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ConeRadiusOuter),s_ConeOuterRadius,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ConeAngle),s_ConeAngle,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ConeHeight),s_ConeHeight,s_CurveKey);
		}
		//------------------------------------------------------------------------
		void Save( const ConeEmitter* obj, SerializeWriter* pWriter )
		{
			_serializeSaveMinMaxCurve(pWriter,*((ConeEmitter* )obj)->getMinMaxCurve(Emitter_ConeRadiusInner),s_ConeInnerRadius,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ConeEmitter* )obj)->getMinMaxCurve(Emitter_ConeRadiusOuter),s_ConeOuterRadius,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ConeEmitter* )obj)->getMinMaxCurve(Emitter_ConeAngle),s_ConeAngle,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ConeEmitter* )obj)->getMinMaxCurve(Emitter_ConeHeight),s_ConeHeight,s_CurveKey);
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ConeEmitter::GetVersion() const
	{
		return 4;	//	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ConeEmitter::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		ConeEmitterSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ConeEmitter::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		ConeEmitterSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ConeEmitter::CopyFrom( const ParticleEmitterPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<ConeEmitter> source = target.downcast<ConeEmitter>();

		_serializeCopyMinMaxCurve(source->mCurveAngle, this->mCurveAngle);
		_serializeCopyMinMaxCurve(source->mCurveInnerRadius, this->mCurveInnerRadius);
		_serializeCopyMinMaxCurve(source->mCurveOuterRadius, this->mCurveOuterRadius);
		_serializeCopyMinMaxCurve(source->mCurveConeHeight, this->mCurveConeHeight);

	}

}