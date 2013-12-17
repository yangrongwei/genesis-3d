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
#include "particles/targets/particleTrailTarget.h"

namespace Particles
{
	using namespace Serialization;

	const  char* s_ElementCount = "ElementCount";
	const  char* s_TrailLen = "TrailLength";
	const  char* s_StartColor = "StartColor";
	const  char* s_EndColor = "EndColor";
	const  char* s_LineColorA = "ColorA";
	const  char* s_LineColorR = "ColorR";
	const  char* s_LineColorG = "ColorG";
	const  char* s_LineColorB = "ColorB";
	const  char* s_AlphaLife = "AlphaLife";
	const  char* s_Amplitude = "Amplitude";
	const  char* s_WaveLength = "WaveLength";
	const  char* s_AmplitudeLife = "AmplitudeLife";
	extern const char* s_CurveKey;


	class ParticleTrailTargetSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ParticleTrailTarget* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			else if( 2 == ver)
			{
				Load_2(obj,pReader);
				return;
			}
			else if( 3 == ver)
			{
				Load_3(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(ParticleTrailTarget* obj, SerializeReader* pReader)
		{
		}
		//------------------------------------------------------------------------
		void Load_2(ParticleTrailTarget* obj, SerializeReader* pReader)
		{
			SizeT elementsCount;
			pReader->SerializeInt(s_ElementCount, elementsCount );
			obj->SetMaxElements( elementsCount);

			float traillen;
			pReader->SerializeFloat( s_TrailLen, traillen);
			obj->SetTrailLength( traillen);

			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Target_TrailLineColorA),s_LineColorA,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Target_TrailLineColorR),s_LineColorR,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Target_TrailLineColorG),s_LineColorG,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Target_TrailLineColorB),s_LineColorB,s_CurveKey);

			float alphaLife;
			pReader->SerializeFloat(s_AlphaLife,alphaLife);
			obj->SetAlphaLife(alphaLife);

			float amplitude;
			pReader->SerializeFloat(s_Amplitude,amplitude);
			obj->SetAmplitude(amplitude);

			float waveLength;
			pReader->SerializeFloat(s_WaveLength,waveLength);
			obj->SetWaveLength(waveLength);

			float amplitudeLife;
			pReader->SerializeFloat(s_AmplitudeLife,amplitudeLife);
			obj->SetAmplitudeLife(amplitudeLife);
		}
		//------------------------------------------------------------------------
		void Load_3(ParticleTrailTarget* obj, SerializeReader* pReader)
		{
			SizeT elementsCount;
			pReader->SerializeInt(s_ElementCount, elementsCount );
			obj->SetMaxElements( elementsCount);

			float traillen;
			pReader->SerializeFloat( s_TrailLen, traillen);
			obj->SetTrailLength( traillen);

			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Target_TrailLineColorA),s_LineColorA,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Target_TrailLineColorR),s_LineColorR,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Target_TrailLineColorG),s_LineColorG,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Target_TrailLineColorB),s_LineColorB,s_CurveKey);

			float alphaLife;
			pReader->SerializeFloat(s_AlphaLife,alphaLife);
			obj->SetAlphaLife(alphaLife);

			float amplitude;
			pReader->SerializeFloat(s_Amplitude,amplitude);
			obj->SetAmplitude(amplitude);

			float waveLength;
			pReader->SerializeFloat(s_WaveLength,waveLength);
			obj->SetWaveLength(waveLength);

			float amplitudeLife;
			pReader->SerializeFloat(s_AmplitudeLife,amplitudeLife);
			obj->SetAmplitudeLife(amplitudeLife);
		}
		//------------------------------------------------------------------------
		void Save( const ParticleTrailTarget* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeInt(s_ElementCount, int(obj->GetMaxElements()) );
			pWriter->SerializeFloat(s_TrailLen, obj->GetTrailLength());

			_serializeSaveMinMaxCurve(pWriter,*((ParticleTrailTarget* )obj)->getMinMaxCurve(Target_TrailLineColorA),s_LineColorA,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleTrailTarget* )obj)->getMinMaxCurve(Target_TrailLineColorR),s_LineColorR,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleTrailTarget* )obj)->getMinMaxCurve(Target_TrailLineColorG),s_LineColorG,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleTrailTarget* )obj)->getMinMaxCurve(Target_TrailLineColorB),s_LineColorB,s_CurveKey);

			pWriter->SerializeFloat(s_AlphaLife,obj->GetAlphaLife());
			pWriter->SerializeFloat(s_Amplitude,obj->GetAmplitude());
			pWriter->SerializeFloat(s_WaveLength,obj->GetWaveLength());
			pWriter->SerializeFloat(s_AmplitudeLife,obj->GetAmplitudeLife());
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ParticleTrailTarget::GetVersion() const
	{
		return 3;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleTrailTarget::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		ParticleTrailTargetSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleTrailTarget::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		ParticleTrailTargetSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ParticleTrailTarget::CopyFrom( const ParticleTargetPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<ParticleTrailTarget> source = target.downcast<ParticleTrailTarget>();
		SetMaxElements( source->GetMaxElements());
		SetTrailLength( source->GetTrailLength());
		SetAlphaLife(source->GetAlphaLife());
		_serializeCopyMinMaxCurve(source->mLineColorA,this->mLineColorA);
		_serializeCopyMinMaxCurve(source->mLineColorR,this->mLineColorR);
		_serializeCopyMinMaxCurve(source->mLineColorG,this->mLineColorG);
		_serializeCopyMinMaxCurve(source->mLineColorB,this->mLineColorB);
		SetAmplitude(source->GetAmplitude());
		SetWaveLength(source->GetWaveLength());
		SetAmplitudeLife(source->GetAmplitudeLife());
	}

}