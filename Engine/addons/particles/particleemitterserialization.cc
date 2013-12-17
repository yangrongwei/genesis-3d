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
#include "particles/particleemitter.h"
#include "particles/particlesystem.h"

namespace Particles
{
	using namespace Serialization;
	using namespace Util;
	using namespace Math;

	const char* s_EmitterName = "EmitterName";
	const char* s_EmitterEnable= "EmitterEnable";
	const char* s_EmitterDelayTime= "EmitterDelayTime"; 
	const char* s_EmitterRate= "EmitterRate";
	const char* s_EmitterMinRate= "EmitterMinRate";
	const char*	s_EmitterMaxRate= "EmitterMaxRate";
	const char* s_EmitterPosition= "EmitterPosition";

	const char* s_EmitterDirection= "EmitterDirection";
	const char* s_EmitterMinDirection= "EmitterMinDirection";
	const char* s_EmitterMaxDirection= "EmitterMaxDirection";
	const char* s_EmitterVelocity= "EmitterVelocity";
	const char* s_EmitterMinVelocity= "EmitterMinVelocity";
	const char* s_EmitterMaxVelocity= "EmitterMaxVelocity";
	const char* s_EmitterOrientation= "EmitterOrientation";
	const char* s_EmitterMinOrientation= "EmitterMinOrientation";
	const char* s_EmitterMaxOrientation= "EmitterMaxOrientation";
	const char* s_EmitterMass= "EmitterMass";
	const char* s_EmitterMinMass= "EmitterMinMass";
	const char* s_EmitterMaxMass= "EmitterMaxMass";
	const char* s_EmitterColor= "EmitterColor";
	const char* s_EmitterMinColor= "EmitterMinColor";
	const char* s_EmitterMaxColor= "EmitterMaxColor";
	const char* s_EmitterTexCoordIndex= "EmitterTexCoordIndex";
	const char* s_EmitterMinTexCoordIndex= "EmitterMinTexCoordIndex";
	const char*	s_EmitterMaxTexCoordIndex= "EmitterMaxTexCoordIndex";
	const char* s_EmitterLiveTime= "EmitterLiveTime";
	const char* s_EmitterMinLiveTime= "EmitterMinLiveTime";
	const char* s_EmitterMaxLiveTime= "EmitterMaxLiveTime";
	const char* s_EmitterSize= "EmitterSize";
	const char* s_EmitterMinSize= "EmitterMinSize";
	const char* s_EmitterMaxSize= "EmitterMaxSize";
	const char* s_EmitterRotationSpeed= "EmitterRotationSpeed";
	const char* s_EmitterMinRotationSpeed= "EmitterMinRotationSpeed";
	const char* s_EmitterMaxRotationSpeed= "EmitterMaxRotationSpeed";
	const char* s_EmitterInitRotation = "EmitterInitRotation";
	const char* s_EmitterMinInitRotation = "EmitterMinInitRotation";
	const char* s_EmitterMaxInitRotation = "EmitterMinInitRotation";

	const char* s_EmitterForceEmission= "EmitterForceEmission";
	const char* s_EmitterAutoDirection= "EmitterAutoDirection";
	const char* s_InterMission = "InterMission";
	const char* s_EmitterLoop = "EmitterLoop";
	const char* s_EmitterLifeTime = "EmitterLifeTime";

	const char* s_EmitAliveTime = "EmitAliveTime";
	const char* s_EmitFromType = "EmitFromType";
	const char* s_IsRandomDir = "IsRandomDir";

	const char* s_KeyFrameCount = "KeyFrameCount";
	const char* s_CurveKey = "CurveKey";
	const char* s_CurveValue = "CurveValue";

	const char* s_IsRandomRate = "IsRandomRate";
	const char* s_IsRandomVelocity = "IsRandomVelocity";
	const char* s_IsRandomColor = "IsRandomColor";
	const char* s_IsRandomLiveTime = "IsRandomLiveTime";
	const char* s_IsRandomSize = "IsRandomSize";
	const char* s_IsRandomRotationSpeed = "IsRandomRotationSpeed";
	const char* s_IsRandomInitRotation = "IsRandomInitRotation";

	const char* s_IsAxialVelocity = "IsAxialVelocity";
	const char* s_IsAxialSize = "IsAxialSize";

	const char* s_NormalSpeed0 = "NormalSpeed0";

	class ParticleEmitterSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( ParticleEmitter* obj,  SVersion ver, SerializeReader* pReader )
		{
			if(7 == ver)
			{
				Load_7(obj, pReader);
				return;
			}
			else if( 8 == ver)
			{
				Load_8(obj,pReader);
				return;
			}
			else if ( 9 == ver)
			{
				Load_9(obj,pReader);
				return;
			}
			else if( 10 == ver)
			{
				Load_10(obj,pReader);
				return;
			}
			else if( 11 == ver)
			{
				Load_11(obj,pReader);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//-------------------------------------------------------------------------------
		void Load_11(ParticleEmitter* obj, SerializeReader* pReader)
		{
			bool IsAxialVelocity;
			pReader->SerializeBool(s_IsAxialVelocity, IsAxialVelocity );
			obj->SetAxialVelocity( IsAxialVelocity );

			bool IsAxialSize;
			pReader->SerializeBool(s_IsAxialSize, IsAxialSize );
			obj->SetAxialSize( IsAxialSize );

			String name;
			pReader->SerializeString(s_EmitterName, name );
			obj->SetName( name );

			bool isEnable;
			pReader->SerializeBool(s_EmitterEnable, isEnable );
			obj->SetEnable( isEnable );
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_Rate),s_EmitterRate,s_CurveKey);


			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_VelocityX),s_EmitterVelocity,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_VelocityY),s_EmitterVelocity,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_VelocityZ),s_EmitterVelocity,s_CurveKey);


			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ColorR),s_EmitterColor,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ColorG),s_EmitterColor,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ColorB),s_EmitterColor,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ColorA),s_EmitterColor,s_CurveKey);



			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_Livetime),s_EmitterLiveTime,s_CurveKey);

			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_SizeX),s_EmitterSize,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_SizeY),s_EmitterSize,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_SizeZ),s_EmitterSize,s_CurveKey);

			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_RotSpeed),s_EmitterRotationSpeed,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_InitRot),s_EmitterInitRotation,s_CurveKey);


			int emitfromtype;
			pReader->SerializeInt(s_EmitFromType, emitfromtype );
			obj->SetParticleInitFromType((EmitFromType)emitfromtype);

			bool randomdir;
			pReader->SerializeBool(s_IsRandomDir, randomdir );
			obj->SetNormalDir(randomdir);

			float normalSpeed0;
			pReader->SerializeFloat(s_NormalSpeed0,normalSpeed0);
			obj->SetNormalSpeed(normalSpeed0);
		}
		//--------------------------------------------------------------------------------
		void Load_10(ParticleEmitter* obj, SerializeReader* pReader)
		{
			bool IsAxialVelocity;
			pReader->SerializeBool(s_IsAxialVelocity, IsAxialVelocity );
			obj->SetAxialVelocity( IsAxialVelocity );

			bool IsAxialSize;
			pReader->SerializeBool(s_IsAxialSize, IsAxialSize );
			obj->SetAxialSize( IsAxialSize );

			String name;
			pReader->SerializeString(s_EmitterName, name );
			obj->SetName( name );

			bool isEnable;
			pReader->SerializeBool(s_EmitterEnable, isEnable );
			obj->SetEnable( isEnable );

			Timing::Time delayTime;
			pReader->SerializeDouble(s_EmitterDelayTime, delayTime );
			obj->SetDelayTime( delayTime );

			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_Rate),s_EmitterRate,s_CurveKey);
			bool forceEmission;
			pReader->SerializeBool( s_EmitterForceEmission, forceEmission);
			bool autoDirection;
			pReader->SerializeBool( s_EmitterAutoDirection, autoDirection);

			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_VelocityX),s_EmitterVelocity,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_VelocityY),s_EmitterVelocity,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_VelocityZ),s_EmitterVelocity,s_CurveKey);


			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ColorR),s_EmitterColor,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ColorG),s_EmitterColor,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ColorB),s_EmitterColor,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_ColorA),s_EmitterColor,s_CurveKey);



			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_Livetime),s_EmitterLiveTime,s_CurveKey);

			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_SizeX),s_EmitterSize,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_SizeY),s_EmitterSize,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_SizeZ),s_EmitterSize,s_CurveKey);

			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_RotSpeed),s_EmitterRotationSpeed,s_CurveKey);
			_serializeLoadMinMaxCurve(pReader,*obj->getMinMaxCurve(Emitter_InitRot),s_EmitterInitRotation,s_CurveKey);

			bool mLoop;
			pReader->SerializeBool(s_EmitterLoop,mLoop);
			obj->SetLoop(mLoop);

			float mLife;
			pReader->SerializeFloat(s_EmitterLifeTime,mLife);
			obj->SetDuration(mLife);

			scalar emitAliveTime;
			pReader->SerializeFloat(s_EmitAliveTime, emitAliveTime );
			obj->SetDuration(emitAliveTime);

			int emitfromtype;
			pReader->SerializeInt(s_EmitFromType, emitfromtype );
			obj->SetParticleInitFromType((EmitFromType)emitfromtype);

			bool randomdir;
			pReader->SerializeBool(s_IsRandomDir, randomdir );
			obj->SetNormalDir(randomdir);

			float normalSpeed0;
			pReader->SerializeFloat(s_NormalSpeed0,normalSpeed0);
			obj->SetNormalSpeed(normalSpeed0);
		}
		//--------------------------------------------------------------------------------
		void Load_9(ParticleEmitter* obj, SerializeReader* pReader)
		{
			Load_8(obj, pReader);

			float normalSpeed0;
			pReader->SerializeFloat(s_NormalSpeed0,normalSpeed0);
			obj->SetNormalSpeed(normalSpeed0);
		}
		//--------------------------------------------------------------------------------
		void Load_8(ParticleEmitter* obj, SerializeReader* pReader)
		{
			bool IsAxialVelocity;
			pReader->SerializeBool(s_IsAxialVelocity, IsAxialVelocity );
			obj->SetAxialVelocity( IsAxialVelocity );

			bool IsAxialSize;
			pReader->SerializeBool(s_IsAxialSize, IsAxialSize );
			obj->SetAxialSize( IsAxialSize );

			String name;
			pReader->SerializeString(s_EmitterName, name );
			obj->SetName( name );

			bool isEnable;
			pReader->SerializeBool(s_EmitterEnable, isEnable );
			obj->SetEnable( isEnable );

			Timing::Time delayTime;
			pReader->SerializeDouble(s_EmitterDelayTime, delayTime );
			obj->SetDelayTime( delayTime );

			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_Rate),s_EmitterRate,s_CurveKey);
			bool forceEmission;
			pReader->SerializeBool( s_EmitterForceEmission, forceEmission);
			bool autoDirection;
			pReader->SerializeBool( s_EmitterAutoDirection, autoDirection);

			Math::float3 pos;
			pReader->SerializeFloat3(s_EmitterPosition, pos );

			Math::float3 dir;
			pReader->SerializeFloat3(s_EmitterDirection, dir );

			scalar minDir, maxDir;
			pReader->SerializeFloat(s_EmitterMinDirection, minDir );
			pReader->SerializeFloat(s_EmitterMaxDirection, maxDir );

			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_VelocityX),s_EmitterVelocity,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_VelocityY),s_EmitterVelocity,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_VelocityZ),s_EmitterVelocity,s_CurveKey);


			Math::quaternion minOrient, maxOrient;
			pReader->SerializeQuaternion( s_EmitterMinOrientation, minOrient );
			pReader->SerializeQuaternion( s_EmitterMaxOrientation, maxOrient );

			scalar minMass, maxMass;
			pReader->SerializeFloat(s_EmitterMinMass, minMass );
			pReader->SerializeFloat(s_EmitterMaxMass, maxMass );

			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_ColorR),s_EmitterColor,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_ColorG),s_EmitterColor,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_ColorB),s_EmitterColor,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_ColorA),s_EmitterColor,s_CurveKey);


			IndexT minTexIndex, maxTexIndex;
			pReader->SerializeInt(s_EmitterMinTexCoordIndex, minTexIndex );
			pReader->SerializeInt(s_EmitterMaxTexCoordIndex, maxTexIndex );

			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_Livetime),s_EmitterLiveTime,s_CurveKey);

			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_SizeX),s_EmitterSize,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_SizeY),s_EmitterSize,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_SizeZ),s_EmitterSize,s_CurveKey);

			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_RotSpeed),s_EmitterRotationSpeed,s_CurveKey);
			_serializeLoadMinMaxCurveOld(pReader,*obj->getMinMaxCurve(Emitter_InitRot),s_EmitterInitRotation,s_CurveKey);

			bool mLoop;
			pReader->SerializeBool(s_EmitterLoop,mLoop);
			obj->SetLoop(mLoop);

			float mLife;
			pReader->SerializeFloat(s_EmitterLifeTime,mLife);

			scalar emitAliveTime;
			pReader->SerializeFloat(s_EmitAliveTime, emitAliveTime );
			obj->SetDuration(emitAliveTime);

			int emitfromtype;
			pReader->SerializeInt(s_EmitFromType, emitfromtype );
			obj->SetParticleInitFromType((EmitFromType)emitfromtype);

			bool randomdir;
			pReader->SerializeBool(s_IsRandomDir, randomdir );
			obj->SetNormalDir(randomdir);
		}
		//--------------------------------------------------------------------------------
		void Load_7(ParticleEmitter* obj, SerializeReader* pReader)
		{
			bool IsAxialVelocity;
			pReader->SerializeBool(s_IsAxialVelocity, IsAxialVelocity );
			obj->SetAxialVelocity( IsAxialVelocity );

			bool IsAxialSize;
			pReader->SerializeBool(s_IsAxialSize, IsAxialSize );
			obj->SetAxialSize( IsAxialSize );

			String name;
			pReader->SerializeString(s_EmitterName, name );
			obj->SetName( name );

			bool isEnable;
			pReader->SerializeBool(s_EmitterEnable, isEnable );
			obj->SetEnable( isEnable );

			Timing::Time delayTime;
			pReader->SerializeDouble(s_EmitterDelayTime, delayTime );
			obj->SetDelayTime(delayTime );

			bool isRandom;
			pReader->SerializeBool(s_IsRandomRate, isRandom );
			if(isRandom)
			{
				obj->getMinMaxCurve(Emitter_Rate)->SetCurveState(Math::MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Emitter_Rate)->SetCurveState(Math::MinMaxCurve::Curve);
			}

			Util::Array<Math::float2> keyframelist1;
			Util::Array<Math::float2> keyframelist2;		
			MinMaxCurve* curve = obj->getMinMaxCurve(Emitter_Rate);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinRate, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxRate, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	


			bool forceEmission;
			pReader->SerializeBool( s_EmitterForceEmission, forceEmission);

			bool autoDirection;
			pReader->SerializeBool( s_EmitterAutoDirection, autoDirection);

			Math::float3 pos;
			pReader->SerializeFloat3(s_EmitterPosition, pos );

			Math::float3 dir;
			pReader->SerializeFloat3(s_EmitterDirection, dir );

			scalar minDir, maxDir;
			pReader->SerializeFloat(s_EmitterMinDirection, minDir );
			pReader->SerializeFloat(s_EmitterMaxDirection, maxDir );

			pReader->SerializeBool(s_IsRandomVelocity, isRandom );
			if(isRandom)
			{
				obj->getMinMaxCurve(Emitter_VelocityX)->SetCurveState(MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Emitter_VelocityY)->SetCurveState(MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Emitter_VelocityZ)->SetCurveState(MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Emitter_VelocityX)->SetCurveState(MinMaxCurve::Curve);
				obj->getMinMaxCurve(Emitter_VelocityY)->SetCurveState(MinMaxCurve::Curve);
				obj->getMinMaxCurve(Emitter_VelocityZ)->SetCurveState(MinMaxCurve::Curve);
			}

			curve = obj->getMinMaxCurve(Emitter_VelocityX);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinVelocity, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxVelocity, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			curve = obj->getMinMaxCurve(Emitter_VelocityY);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinVelocity, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxVelocity, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			curve = obj->getMinMaxCurve(Emitter_VelocityZ);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinVelocity, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxVelocity, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	


			Math::quaternion minOrient, maxOrient;
			pReader->SerializeQuaternion( s_EmitterMinOrientation, minOrient );
			pReader->SerializeQuaternion( s_EmitterMaxOrientation, maxOrient );

			scalar minMass, maxMass;
			pReader->SerializeFloat(s_EmitterMinMass, minMass );
			pReader->SerializeFloat(s_EmitterMaxMass, maxMass );

			pReader->SerializeBool(s_IsRandomColor, isRandom );
			if(isRandom)
			{
				obj->getMinMaxCurve(Emitter_ColorR)->SetCurveState(MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Emitter_ColorG)->SetCurveState(MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Emitter_ColorB)->SetCurveState(MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Emitter_ColorA)->SetCurveState(MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Emitter_ColorR)->SetCurveState(MinMaxCurve::Curve);
				obj->getMinMaxCurve(Emitter_ColorG)->SetCurveState(MinMaxCurve::Curve);
				obj->getMinMaxCurve(Emitter_ColorB)->SetCurveState(MinMaxCurve::Curve);
				obj->getMinMaxCurve(Emitter_ColorA)->SetCurveState(MinMaxCurve::Curve);
			}

			curve = obj->getMinMaxCurve(Emitter_ColorR);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinColor, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxColor, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);


			curve = obj->getMinMaxCurve(Emitter_ColorG);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinColor, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxColor, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	

			curve = obj->getMinMaxCurve(Emitter_ColorB);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinColor, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxColor, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);

			curve = obj->getMinMaxCurve(Emitter_ColorA);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinColor, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxColor, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	


			IndexT minTexIndex, maxTexIndex;
			pReader->SerializeInt(s_EmitterMinTexCoordIndex, minTexIndex );
			pReader->SerializeInt(s_EmitterMaxTexCoordIndex, maxTexIndex );

			pReader->SerializeBool(s_IsRandomLiveTime, isRandom );
			if(isRandom)
			{
				obj->getMinMaxCurve(Emitter_Livetime)->SetCurveState(MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Emitter_Livetime)->SetCurveState(MinMaxCurve::Curve);
			}

			curve = obj->getMinMaxCurve(Emitter_Livetime);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinLiveTime, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxLiveTime, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	

			pReader->SerializeBool(s_IsRandomSize, isRandom );
			if(isRandom)
			{
				obj->getMinMaxCurve(Emitter_SizeX)->SetCurveState(MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Emitter_SizeY)->SetCurveState(MinMaxCurve::TwoCurves);
				obj->getMinMaxCurve(Emitter_SizeZ)->SetCurveState(MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Emitter_SizeX)->SetCurveState(MinMaxCurve::Curve);
				obj->getMinMaxCurve(Emitter_SizeY)->SetCurveState(MinMaxCurve::Curve);
				obj->getMinMaxCurve(Emitter_SizeZ)->SetCurveState(MinMaxCurve::Curve);
			}


			curve = obj->getMinMaxCurve(Emitter_SizeX);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinSize, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxSize, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	

			curve = obj->getMinMaxCurve(Emitter_SizeY);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinSize, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxSize, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	

			curve = obj->getMinMaxCurve(Emitter_SizeZ);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinSize, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxSize, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	

			pReader->SerializeBool(s_IsRandomRotationSpeed, isRandom );

			curve = obj->getMinMaxCurve(Emitter_RotSpeed);
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinRotationSpeed, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxRotationSpeed, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	

			pReader->SerializeBool(s_IsRandomInitRotation, isRandom );
			if(isRandom)
			{
				obj->getMinMaxCurve(Emitter_InitRot)->SetCurveState(MinMaxCurve::TwoCurves);
			}
			else
			{
				obj->getMinMaxCurve(Emitter_InitRot)->SetCurveState(MinMaxCurve::Curve);
			}

			curve = obj->getMinMaxCurve( Emitter_InitRot );
			_serializeLoadCurveOld(pReader, keyframelist1, s_EmitterMinInitRotation, s_CurveKey);
			_serializeLoadCurveOld(pReader, keyframelist2, s_EmitterMaxInitRotation, s_CurveKey);
			_setCurveOld(keyframelist1,keyframelist2,curve);	
			//

			bool mLoop;
			pReader->SerializeBool(s_EmitterLoop,mLoop);
			obj->SetLoop(mLoop);

			float mLife;
			pReader->SerializeFloat(s_EmitterLifeTime,mLife);
			obj->SetDuration(mLife);

			scalar emitAliveTime;
			pReader->SerializeFloat(s_EmitAliveTime, emitAliveTime );
			obj->SetDuration(emitAliveTime);

			int emitfromtype;
			pReader->SerializeInt(s_EmitFromType, emitfromtype );
			obj->SetParticleInitFromType((EmitFromType)emitfromtype);

			bool randomdir;
			pReader->SerializeBool(s_IsRandomDir, randomdir );
			obj->SetNormalDir(randomdir);
		}
		//------------------------------------------------------------------------
		void Save( const ParticleEmitter* obj, SerializeWriter* pWriter )
		{			
			pWriter->SerializeBool(s_IsAxialVelocity,obj->IsAxialVelocity());
			pWriter->SerializeBool(s_IsAxialSize,obj->IsAxialSize());

			pWriter->SerializeString(s_EmitterName, obj->GetName() );
			pWriter->SerializeBool(s_EmitterEnable, obj->IsEnable() );

			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_Rate),s_EmitterRate,s_CurveKey);


			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_VelocityX),s_EmitterVelocity,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_VelocityY),s_EmitterVelocity,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_VelocityZ),s_EmitterVelocity,s_CurveKey);


			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_ColorR),s_EmitterColor,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_ColorG),s_EmitterColor,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_ColorB),s_EmitterColor,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_ColorA),s_EmitterColor,s_CurveKey);

			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_Livetime),s_EmitterLiveTime,s_CurveKey);

			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_SizeX),s_EmitterSize,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_SizeY),s_EmitterSize,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_SizeZ),s_EmitterSize,s_CurveKey);

			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_RotSpeed),s_EmitterRotationSpeed,s_CurveKey);
			_serializeSaveMinMaxCurve(pWriter,*((ParticleEmitter* )obj)->getMinMaxCurve(Emitter_InitRot),s_EmitterInitRotation,s_CurveKey);


			pWriter->SerializeInt(s_EmitFromType, (int)obj->GetParticleInitFromType());

			pWriter->SerializeBool(s_IsRandomDir, obj->IsNormalDir() );

			pWriter->SerializeFloat(s_NormalSpeed0, obj->GetNormalSpeed());
		}
	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion ParticleEmitter::GetVersion() const
	{
		return 11;	//	
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void ParticleEmitter::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		ParticleEmitterSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void ParticleEmitter::Save( SerializeWriter* pWriter ) const
	{
		ParticleEmitterSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void ParticleEmitter::CopyFrom( const ParticleEmitterPtr& obj )
	{
		SetName( obj->GetName() );
		SetEnable( obj->IsEnable() );
		SetDelayTime( obj->GetDelayTime() );

		_serializeCopyMinMaxCurve(obj->mMinMaxRate,this->mMinMaxRate);

		_serializeCopyMinMaxCurve(obj->mMinMaxVelocityX,this->mMinMaxVelocityX);
		_serializeCopyMinMaxCurve(obj->mMinMaxVelocityY,this->mMinMaxVelocityY);
		_serializeCopyMinMaxCurve(obj->mMinMaxVelocityZ,this->mMinMaxVelocityZ);

		_serializeCopyMinMaxCurve(obj->mMinMaxColorR,this->mMinMaxColorR);
		_serializeCopyMinMaxCurve(obj->mMinMaxColorG,this->mMinMaxColorG);
		_serializeCopyMinMaxCurve(obj->mMinMaxColorB,this->mMinMaxColorB);
		_serializeCopyMinMaxCurve(obj->mMinMaxColorA,this->mMinMaxColorA);


		_serializeCopyMinMaxCurve(obj->mMinMaxLiveTime,this->mMinMaxLiveTime);

		_serializeCopyMinMaxCurve(obj->mMinMaxSizeX,this->mMinMaxSizeX);
		_serializeCopyMinMaxCurve(obj->mMinMaxSizeY,this->mMinMaxSizeY);
		_serializeCopyMinMaxCurve(obj->mMinMaxSizeZ,this->mMinMaxSizeZ);

		_serializeCopyMinMaxCurve(obj->mMinMaxRotationSpeed,this->mMinMaxRotationSpeed);

		_serializeCopyMinMaxCurve(obj->mMinMaxInitRotaion,this->mMinMaxInitRotaion);
		SetDuration(obj->GetDuration());

		SetParticleInitFromType(obj->GetParticleInitFromType());

		SetNormalDir( obj->IsNormalDir());
		SetNormalSpeed(obj->GetNormalSpeed());
		//
		SetLoop(obj->GetLoop());

		_serializeCopyMinMaxCurve(obj->mMinMaxRate,this->mMinMaxRate);

		SetAxialVelocity(obj->IsAxialVelocity());
		SetAxialSize(obj->IsAxialSize());
	}
}