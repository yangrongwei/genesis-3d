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
#include "particles/targets/particleBeamTarget.h"

namespace Particles
{
	using namespace Serialization;

	const char* s_MaxElements = "MaxElements";
	const char* s_UpdateInterval = "UpdateInterval";
	const char* s_NoiseXMin = "NorseXMin";
	const char* s_NoiseXMax = "NorseXMax";
	const char* s_NoiseYMin = "NorseYMin";
	const char* s_NoiseYMax = "NorseYMax";
	const char* s_NoiseZMin = "NorseZMin";
	const char* s_NoiseZMax = "NorseZMax";

	class BeamTargetSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ParticleBeamTarget* obj,  SVersion ver, SerializeReader* pReader)
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(ParticleBeamTarget* obj, SerializeReader* pReader)
		{
			SizeT elementsCount;
			pReader->SerializeInt(s_MaxElements, elementsCount );
			obj->SetMaxElements( elementsCount);

			Math::scalar updateInterval;
			pReader->SerializeFloat(s_UpdateInterval, updateInterval);
			obj->SetUpdateInterval(updateInterval);

			Math::scalar minValue;
			Math::scalar maxValue;
			pReader->SerializeFloat(s_NoiseXMin,minValue);
			obj->SetNoiseXMin(minValue);
			pReader->SerializeFloat(s_NoiseXMax,maxValue);
			obj->SetNoiseXMax(maxValue);

			pReader->SerializeFloat(s_NoiseYMin,minValue);
			obj->SetNoiseYMin(minValue);
			pReader->SerializeFloat(s_NoiseYMax,maxValue);
			obj->SetNoiseYMax(maxValue);

			pReader->SerializeFloat(s_NoiseZMin,minValue);
			obj->SetNoiseZMin(minValue);
			pReader->SerializeFloat(s_NoiseZMax,maxValue);
			obj->SetNoiseZMax(maxValue);
		}
		//------------------------------------------------------------------------
		void Save( const ParticleBeamTarget* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeInt(s_MaxElements, obj->GetMaxElements() );
			pWriter->SerializeFloat(s_UpdateInterval, obj->GetUpdateInterval() );

			pWriter->SerializeFloat(s_NoiseXMin,obj->GetNoiseXMin());
			pWriter->SerializeFloat(s_NoiseXMax,obj->GetNoiseXMax());
			pWriter->SerializeFloat(s_NoiseYMin,obj->GetNoiseYMin());
			pWriter->SerializeFloat(s_NoiseYMax,obj->GetNoiseYMax());
			pWriter->SerializeFloat(s_NoiseZMin,obj->GetNoiseZMin());
			pWriter->SerializeFloat(s_NoiseZMax,obj->GetNoiseZMax());
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ParticleBeamTarget::GetVersion() const
	{
		return 1;
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleBeamTarget::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		BeamTargetSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleBeamTarget::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		BeamTargetSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ParticleBeamTarget::CopyFrom( const ParticleTargetPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<ParticleBeamTarget> source = target.downcast<ParticleBeamTarget>();
		SetMaxElements(source->GetMaxElements());
		SetUpdateInterval(source->GetUpdateInterval());
		SetNoiseXMin(source->GetNoiseXMin());
		SetNoiseXMax(source->GetNoiseXMax());
		SetNoiseYMin(source->GetNoiseYMin());
		SetNoiseYMax(source->GetNoiseYMax());
		SetNoiseZMin(source->GetNoiseZMin());
		SetNoiseZMax(source->GetNoiseZMax());
	}

}