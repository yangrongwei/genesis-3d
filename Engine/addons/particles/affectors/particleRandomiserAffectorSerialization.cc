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
#include "particles/affectors/particleRandomiserAffector.h"

namespace Particles
{
	using namespace Serialization;

	const static char* s_MaxDeviationX = "MaxDeviationX";
	const static char* s_MaxDeviationY = "MaxDeviationY";
	const static char* s_MaxDeviationZ = "MaxDeviationZ";
	const static char* s_TimeStep = "TimeStep";
	const static char* s_RandomDirection = "RandomDirection";

	class RandomiserAffectorSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( RandomiserAffector* obj,  SVersion ver, SerializeReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(RandomiserAffector* obj, SerializeReader* pReader)
		{
			Math::scalar mMaxDeviationX;
			pReader->SerializeFloat(s_MaxDeviationX, mMaxDeviationX);
			obj->SetMaxDeviationX(mMaxDeviationX);

			Math::scalar mMaxDeviationY;
			pReader->SerializeFloat(s_MaxDeviationY, mMaxDeviationY );
			obj->SetMaxDeviationY(mMaxDeviationY);

			Math::scalar mMaxDeviationZ;
			pReader->SerializeFloat(s_MaxDeviationZ, mMaxDeviationZ );
			obj->SetMaxDeviationZ(mMaxDeviationZ);

			Math::scalar mTimeStep;
			pReader->SerializeFloat(s_TimeStep, mTimeStep );
			obj->SetTimeStep(mTimeStep);

			bool mRandomDirection;
			pReader->SerializeBool(s_RandomDirection, mRandomDirection );
			obj->SetRandomDirection(mRandomDirection);
		}
		//------------------------------------------------------------------------
		void Save( const RandomiserAffector* obj, SerializeWriter* pWriter )
		{
			pWriter->SerializeFloat(s_MaxDeviationX, obj->GetMaxDeviationX());
			pWriter->SerializeFloat(s_MaxDeviationY, obj->GetMaxDeviationY() );
			pWriter->SerializeFloat(s_MaxDeviationZ, obj->GetMaxDeviationZ() );
			pWriter->SerializeFloat(s_TimeStep, obj->GetTimeStep() );
			pWriter->SerializeBool(s_RandomDirection, obj->IsRandomDirection() );
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion RandomiserAffector::GetVersion() const
	{
		return 1;	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void RandomiserAffector::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		RandomiserAffectorSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void RandomiserAffector::Save( SerializeWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		RandomiserAffectorSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void RandomiserAffector::CopyFrom( const ParticleAffectorPtr& target )
	{
		Super::CopyFrom( target );
		n_assert( target->GetRtti() == this->GetRtti() ); 
		GPtr<RandomiserAffector> source = target.downcast<RandomiserAffector>();

		SetMaxDeviationX( source->GetMaxDeviationX());
		SetMaxDeviationY( source->GetMaxDeviationY());
		SetMaxDeviationZ( source->GetMaxDeviationZ());
		SetRandomDirection( source->IsRandomDirection());
		SetTimeStep( source->GetTimeStep());
	}

}