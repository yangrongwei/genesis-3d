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
#ifndef __particle_fwd_decl_H__
#define __particle_fwd_decl_H__
#include "core/ptr.h"
#include "core/singleton.h"
#include "timing/time.h"
#include "util/stringatom.h"
#include "math/float3.h"
#include "math/float2.h"
#include "math/quaternion.h"
#include "util/array.h"
#include "util/stl.h"
#include "math/color.h"
#include "util/randomnumbertable.h"
#include "serialization/serialize.h"
#include "util/algorithm.h"
#include "math/curve.h"
#include "math/MinMaxCurve.h"


namespace Particles
{
	/// the primitivegroup format
	struct ParticleVertexData {
		Math::float3 mPosition;
		Math::float3 mNormal;
		Math::Color32 mColor;
		Math::float2 mTexCoord;
	};

	enum	ColorContrlType{CCT_CONST, CCT_RND_CONST, CCT_GRADCURVE, CCT_RND_GRADCURVE};

	enum   SpaceCoordType{SCT_LOCAL, SCT_WORLD, SCT_CAMERA};

	enum	EmitFromType{EFT_SHELL,  EFT_BODY,EFT_POINT, EFT_CONEBODY};

	enum	MeshEmitType{ MMT_VERT = 0, MMT_EDGE, MMT_TRIANGLE};

	enum	ParticleCurveType{ Emitter_Rate = 0, Emitter_VelocityX, Emitter_VelocityY, Emitter_VelocityZ, Emitter_ColorR,Emitter_ColorG,Emitter_ColorB,Emitter_ColorA, Emitter_Livetime, Emitter_SizeX,Emitter_SizeY,Emitter_SizeZ, 
		Emitter_RotSpeed,Emitter_InitRot,
		Emitter_SphereRadius, Emitter_SphereHem, Emitter_SphereSlice,
		Emitter_BoxSizeX,Emitter_BoxSizeY,Emitter_BoxSizeZ,
		Emitter_ConeRadiusInner,Emitter_ConeRadiusOuter,Emitter_ConeAngle,Emitter_ConeHeight,
		Affector_LimitX, Affector_LimitY, Affector_LimitZ, Affector_LimitValue,
		Affector_ForceX,Affector_ForceY,Affector_ForceZ,
		Affector_RotationAngular,
		Affector_GravityX,Affector_GravityY,Affector_GravityZ,Affector_Gravity,
		Affector_VortexX,Affector_VortexY,Affector_VortexZ,Affector_Vortex,
		Affector_ScaleX,Affector_ScaleY,Affector_ScaleZ,
		Affector_ColorR,Affector_ColorG,Affector_ColorB,Affector_ColorA,
		Affetor_TexAnimation,
		Affector_MovementX,Affector_MovementY,Affector_MovementZ,Affector_MovementSpeed,

		Target_TrailLineColorA,Target_TrailLineColorR,Target_TrailLineColorG,Target_TrailLineColorB,
	};

	//typedef  Math::Math::MinMaxCurve Math::MinMaxCurve;

	struct  ConstDefine
	{
		static const Math::float3 FLOAT3_ZERO;
		static const Math::float3 FLOAT3_IDENTITY;
		static const Math::float3 FLOAT3_UNIT_X;
		static const Math::float3 FLOAT3_UNIT_Y;
		static const Math::float3 FLOAT3_UNIT_Z;

		static const Math::quaternion QUATERNION_ZERO;
		static const Math::quaternion QUATERNION_IDENTITY;

		static const SizeT DEFAULT_TECHNIQUE_QUOTA;
		static const SizeT MAX_TECHNIQUE_QUOTA;

		static const Math::float3 DEFAULT_EMITTER_DIRECTION;
		static const Math::scalar DEFAULT_EMITTER_MIN_DIRECTION;
		static const Math::scalar DEFAULT_EMITTER_MAX_DIRECTION;
		static const Math::float3 DEFAULT_EMITTER_VELOCITY;

		static const SizeT DEFAULT_MAX_EMITTER_RATE;
		static const SizeT DEFAULT_MIN_EMITTER_RATE;

		static const Math::scalar DEFAULT_MIN_TIME_LIVE;
		static const Math::scalar DEFAULT_MAX_TIME_LIVE;

		static const Math::scalar DEFAULT_MASS;
		static const Math::scalar DEFAULT_ROTATION_SPEED;
		static const Math::float3 DEFAULT_SIZE;

		static const Math::ColorF DEFAULT_MIN_COLOR;
		static const Math::ColorF DEFAULT_MAX_COLOR;

		static const IndexT DEFAULT_TEXCOORD_INDEX;

		static const Math::matrix44 MATRIX_IDENTITY;
		static const Math::float2 DEFAULT_ACCELERATION;

	};
	//const particle fourcc
	struct CPFCC
	{
		static const uint EMITTER_BOX = 'PABE';
		static const uint EMITTER_CIRCLE = 'PACE';
		static const uint EMITTER_POINT = 'PAPE';
		static const uint EMITTER_SPHERESURFACE = 'PASE';
		static const uint EMITTER_CONE = 'PACN';
		static const uint EMITTER_SYLINDER = 'PASD';
		static const uint EMITTER_MODEL = 'PAME';

		static const uint AFFECTOR_DEFAULT = 'PAAF';
		static const uint AFFECTOR_COLOR = 'PACA';
		static const uint AFFECTOR_FOLLOWER = 'PFAF';
		static const uint AFFECTOR_GRAVITY = 'PAGA';
		static const uint AFFECTOR_JET = 'PAJA';
		static const uint AFFECTOR_LINEARFORCE = 'PAFA';
		static const uint AFFECTOR_RANDOMISER = 'PARA';
		static const uint AFFECTOR_SCALE = 'PASA';
		static const uint AFFECTOR_TEXTUREANIMATOR = 'PATA';
		static const uint AFFECTOR_TEXTUREROTATOR = 'PATR';
		static const uint AFFECTOR_VORTEX = 'PAVA';
		static const uint AFFECTOR_LIMIT = 'PADP';
		static const uint AFFECTOR_MOVEMENT = 'PAMT';

		static const uint TARGET_BEAM = 'PABT';
		static const uint TARGET_BILLBOARD = 'PBBT';
		static const uint TARGET_ENTITY = 'PAET';
		static const uint TARGET_RIBBONTRAIL = 'PRTT';
		static const uint TARGET_PARTICLEDECAL = 'PRDC';
		static const uint TARGET_TRAIL = 'PATT';
		static const uint TARGET_RIBBON = 'PTRN';

	};

	struct Particle;
	class ParticleServer;
	class ParticleSystem;
	class ParticleEmitter;
	class ParticleAffector;
	class ParticleTarget;
	class ParticleJob;
	class ParticlePool;

	typedef GPtr<ParticlePool>		        ParticlePoolPtr;
	typedef GPtr<ParticleServer>			ParticleServerPtr;
	typedef GPtr<ParticleSystem>			ParticleSystemPtr;
	typedef GPtr<ParticleEmitter>			ParticleEmitterPtr;
	typedef GPtr<ParticleAffector>			ParticleAffectorPtr;
	typedef GPtr<ParticleTarget>			ParticleTargetPtr;
	typedef GPtr<ParticleJob>				ParticleJobPtr;
}

namespace Particles
{
	template<typename T>
	GPtr<T> Clone(const GPtr<T>& source)
	{
		n_assert( source.isvalid() );
		GPtr<Core::RefCounted> pObj = source->GetRtti()->Create();
		GPtr<T> dest = pObj.downcast<T>();
		n_assert( dest.isvalid() );
		dest->CopyFrom( source );
		return dest;
	}

	inline IndexT GenerateRandomSeed(void* p)
	{
		return ( (IndexT)p ) & 0xFFFF;
	}

	// From Ogre: rotation of a vector by a quaternion
	inline Math::float3 operator* ( const Math::quaternion& q, const Math::float3& v )
	{
		// nVidia SDK implementation
		Math::float3 uv, uuv;
		Math::float3 qvec(q.x(), q.y(), q.z() );
		uv = qvec.crossProduct(v);
		uuv = qvec.crossProduct(uv);
		uv *= ( 2.0f * q.w() );
		uuv *= 2.0f;

		return v + uv + uuv;
	}

	// From Ogre
	inline Math::quaternion operator* (const Math::quaternion& lkQ, const Math::quaternion& rkQ)
	{
		// NOTE:  Multiplication is not generally commutative, so in most
		// cases p*q != q*p.

		return Math::quaternion
			(
			lkQ.w() * rkQ.w() - lkQ.x() * rkQ.x() - lkQ.y() * rkQ.y() - lkQ.z() * rkQ.z(),
			lkQ.w() * rkQ.x() + lkQ.x() * rkQ.w() + lkQ.y() * rkQ.z() - lkQ.z() * rkQ.y(),
			lkQ.w() * rkQ.y() + lkQ.y() * rkQ.w() + lkQ.z() * rkQ.x() - lkQ.x() * rkQ.z(),
			lkQ.w() * rkQ.z() + lkQ.z() * rkQ.w() + lkQ.x() * rkQ.y() - lkQ.y() * rkQ.x()
			);
	}
	// From Ogre: Generates a vector perpendicular to the vector
	inline Math::float3 Perpendicular(const Math::float3& f)
	{
		Math::float3 perp = f.crossProduct( ConstDefine::FLOAT3_UNIT_X );

		// Check length
		if( perp.lengthsq() < (N_TINY * N_TINY ) )
		{
			/* This vector is the Y axis multiplied by a scalar, so we have
			to use another axis.
			*/
			perp = f.crossProduct( ConstDefine::FLOAT3_UNIT_Y );
		}
		perp.normalise();

		return perp;
	}

	// From Ogre: Generates a new random vector which deviates from this vector by a given angle in a random direction
	// randomR in [0,1]
	inline Math::float3 RandomDeviant(
		const Math::float3& dir,
		Math::scalar radian,
		const Math::float3& up,
		Math::scalar randomR ) 
	{
		// Rotate up vector by random amount around this
		Math::float4 axisDir(dir.x(), dir.y(), dir.z(), 0.0f );
		Math::quaternion q = Math::quaternion::rotationaxis(axisDir,  randomR * N_PI_DOUBLE);

		Math::float3 newUp = q * up;

		// Finally rotate this by given angle around randomised up
		Math::float4 axisUp(newUp.x(), newUp.y(), newUp.z(), 0.0f );
		q = Math::quaternion::rotationaxis(axisUp,  radian);// FromAngleAxis( radian, newUp );

		return q * dir;
	}
	//--------------------------------------------------------------------------------
	inline bool GetRandomTriangle(const Particles::ParticleVertexData* _triangle,  Math::float3& _pos,  Math::float3& _normal) 
	{
		float a = Math::n_rand(0,1);
		float b = Math::n_rand(0,1);
		if (a + b > 1)
		{
			a = 1 - a;
			b = 1 - b;
		}
		float c = 1 - a - b;
		_pos = a * _triangle[0].mPosition + b *_triangle[1].mPosition + c * _triangle[2].mPosition;
		_normal = a * _triangle[0].mNormal + b *_triangle[1].mNormal + c * _triangle[2].mNormal;

		return true;
	}
	//--------------------------------------------------------------------------------
	inline bool GetRandomEdge(const Particles::ParticleVertexData* _triangle,  Math::float3& _pos,  Math::float3& _normal) 
	{
		float mult = Math::n_rand(0, 1);
		float randomVal = Math::n_rand(0, 3);
		_pos = ConstDefine::FLOAT3_ZERO;
		_normal =ConstDefine::FLOAT3_ZERO;
		Math::float3 v1 = _triangle[0].mPosition;
		Math::float3 v2 = _triangle[1].mPosition;
		Math::float3 v3 = _triangle[2].mPosition;

		Math::float3 vn1 = _triangle[0].mNormal;
		Math::float3 vn2 = _triangle[1].mNormal;
		Math::float3 vn3 = _triangle[2].mNormal;

		if (randomVal < 1)
		{
			_pos = Math::float3( v2.x() + mult*(v1.x() - v2.x()),
				v2.y() + mult*(v1.y() - v2.y()),
				v2.z() + mult*(v1.z() - v2.z()));
		}
		else
		{
			if (randomVal < 2)
			{
				_pos = Math::float3(	v3.x()+ mult*(v2.x() - v3.x()),
					v3.y() + mult*(v2.y() - v3.y()),
					v3.z() + mult*(v2.z() - v3.z()));
			}
			else
			{
				_pos = Math::float3(	v1.x() + mult*(v3.x() - v1.x()),
					v1.y() + mult*(v3.y() - v1.y()),
					v1.z() + mult*(v3.z() - v1.z()));

			}
		}
		float a = Math::n_rand(0,1);
		float b = Math::n_rand(0,1);
		if (a + b > 1)
		{
			a = 1 - a;
			b = 1 - b;
		}
		float c = 1 - a - b;
		_normal = a * _triangle[0].mNormal + b *_triangle[1].mNormal + c * _triangle[2].mNormal;
		return true;
	}
	//--------------------------------------------------------------------------------
	inline bool GetRandomVertex(const Particles::ParticleVertexData* _triangle,  Math::float3& _pos,  Math::float3& _normal) 
	{
		float randomVal = Math::n_rand(0, 3);
		_pos =  ConstDefine::FLOAT3_ZERO;
		_normal =  ConstDefine::FLOAT3_ZERO;

		if (randomVal < 1)
		{
			_pos = _triangle[0].mPosition;
			_normal=  _triangle[0].mNormal;
		}
		else
		{
			if (randomVal < 2)
			{
				_pos = _triangle[1].mPosition;
				_normal =  _triangle[1].mNormal;
			}
			else
			{
				_pos = _triangle[2].mPosition;
				_normal=  _triangle[2].mNormal;
			}
		}
		return true;
	}
	//--------------------------------------------------------------------------------
	inline  void _serializeSaveCurve( Serialization::SerializeWriter* pWriter, const Math::FloatPolyCurve& curve, const char* chrcnt, const char* chrtime )
	{
		SizeT count = curve.GetKeyFrameCount();
		SizeT leverCount = curve.GetFrameLeversCount();
		pWriter->SerializeInt(chrcnt, count + leverCount *2);
		for (IndexT nIdx = 0; nIdx < count; nIdx++)
		{

			Math::FloatKeyFrame fkf = curve.GetKeyFrame(nIdx);
			pWriter->SerializeFloat2( chrtime, Math::float2(fkf.GetTime(),  fkf.GetValue()));

			if (leverCount > nIdx)
			{
				Math::FloatKeyFrame fkfRight = curve.GetFrameLever(nIdx)._left;
				pWriter->SerializeFloat2( chrtime, Math::float2(fkfRight.GetTime(),  fkfRight.GetValue()));

				Math::FloatKeyFrame fkfLeft = curve.GetFrameLever(nIdx)._right;
				pWriter->SerializeFloat2( chrtime, Math::float2(fkfLeft.GetTime(),  fkfLeft.GetValue()));
			}
		}
		count = curve.GetCurveTypesCount();
		pWriter->SerializeInt(chrcnt,count);
		for (IndexT nIdx = 0; nIdx < count; nIdx++)
		{
			bool leftType = curve.GetLeftCurveType(nIdx);
			pWriter->SerializeBool(chrtime,leftType);

			bool rightType = curve.GetRightCurveType(nIdx);
			pWriter->SerializeBool(chrtime,rightType);
		}
	}
	//--------------------------------------------------------------------------------
	inline  void _serializeSaveMinMaxCurve( Serialization::SerializeWriter* pWriter, const Math::MinMaxCurve& curve, const char* chrcnt, const char* chrtime )
	{
		int ver = 0;		
		pWriter->SerializeInt("ver",ver);

		Math::MinMaxCurve::CurveState state = curve.GetCurveState();
		Math::float2 mScalar = curve.GetRandomScalar();
		pWriter->SerializeInt("MinMaxState",state);
		pWriter->SerializeFloat2("Scalar",mScalar);

		Math::FloatPolyCurve curve1;
		Math::FloatPolyCurve curve2;
		curve.GetTwoCurve(curve1,curve2);

		_serializeSaveCurve(pWriter,curve1,chrcnt,chrtime);
		_serializeSaveCurve(pWriter,curve2,chrcnt,chrtime);
	}
	//--------------------------------------------------------------------------------
	inline  void _serializeLoadCurveOld( Serialization::SerializeReader* pReader, Util::Array<Math::float2>& kfl, const char* chrcnt, const char* chrtime )
	{
		kfl.Clear();
		int count;
		pReader->SerializeInt(chrcnt,count);
		for (IndexT nIdx = 0; nIdx < count; nIdx++)
		{
			Math::float2 _framePair;
			pReader->SerializeFloat2(chrtime, _framePair);
			kfl.Append(_framePair);
		}
	}
	//--------------------------------------------------------------------------------
	inline void _setCurveOld(const Util::Array<Math::float2>& _list1, const Util::Array<Math::float2>& _list2,Math::MinMaxCurve* _curve)
	{
		Util::Array<bool> _curveType1;
		Util::Array<bool> _curveType2;
		_curve->SetCurveFromArray(_list1,_curveType1,_list2,_curveType2);
	}
	//--------------------------------------------------------------------------------
	inline  void _serializeLoadCurve( Serialization::SerializeReader* pReader, Util::Array<Math::float2>& kfl,Util::Array<bool>& _curveTypes, const char* chrcnt, const char* chrtime )
	{
		kfl.Clear();
		_curveTypes.Clear();
		int count;
		pReader->SerializeInt(chrcnt,count);
		for (IndexT nIdx = 0; nIdx < count; nIdx++)
		{
			Math::float2 _framePair;
			pReader->SerializeFloat2(chrtime, _framePair);
			kfl.Append(_framePair);
		}

		pReader->SerializeInt(chrcnt,count);
		bool leftType;
		bool rightType;
		for (IndexT nIdx = 0; nIdx < count; nIdx++)
		{
			pReader->SerializeBool(chrtime,leftType);
			_curveTypes.Append(leftType);

			pReader->SerializeBool(chrtime,rightType);
			_curveTypes.Append(rightType);
		}
	}
	//-------------------------------------------------------------------------------
	inline  void _serializeLoadMinMaxCurveOld( Serialization::SerializeReader* pReader, Math::MinMaxCurve& kfl, const char* chrcnt, const char* chrtime )
	{
		int state;
		Math::float2 mScalar;
		pReader->SerializeInt("MinMaxState",state);
		pReader->SerializeFloat2("Scalar",mScalar);
		kfl.SetCurveState((Math::MinMaxCurve::CurveState)state);
		kfl.SetRandomScalar(mScalar);
		Util::Array<Math::float2> curveArray1;
		Util::Array<Math::float2> curveArray2;
		_serializeLoadCurveOld(pReader,curveArray1,chrcnt,chrtime);
		_serializeLoadCurveOld(pReader,curveArray2,chrcnt,chrtime);

		Util::Array<bool> curveType1;
		Util::Array<bool> curveType2;
		curveType1.Clear();
		curveType2.Clear();
		SizeT count = curveArray1.Size();
		for(IndexT Idx=0;Idx < count; Idx++)
		{
			curveType1.Append(false);
		}
		count = curveArray2.Size();
		for(IndexT Idx=0;Idx < count; Idx++)
		{
			curveType2.Append(false);
		}
		kfl.SetCurveFromArray(curveArray1,curveType1,curveArray2,curveType2);
	}
	//-------------------------------------------------------------------------------
	inline  void _serializeLoadMinMaxCurve( Serialization::SerializeReader* pReader, Math::MinMaxCurve& kfl, const char* chrcnt, const char* chrtime )
	{
		int ver;
		pReader->SerializeInt("ver",ver);

		int state;
		Math::float2 mScalar;
		pReader->SerializeInt("MinMaxState",state);

		pReader->SerializeFloat2("Scalar",mScalar);
		kfl.SetCurveState((Math::MinMaxCurve::CurveState)state);
		kfl.SetRandomScalar(mScalar);
		Util::Array<Math::float2> curveArray1;
		Util::Array<bool>	curveTypes1;
		Util::Array<Math::float2> curveArray2;
		Util::Array<bool>	curveTypes2;
		_serializeLoadCurve(pReader,curveArray1,curveTypes1,chrcnt,chrtime);
		_serializeLoadCurve(pReader,curveArray2,curveTypes2,chrcnt,chrtime);

		kfl.SetCurveFromArray(curveArray1,curveTypes1,curveArray2,curveTypes2);

	}
	//--------------------------------------------------------------------------------
	inline  void _serializeCopyCurve(  const Math::FloatPolyCurve* sourceCurve,  Math::FloatPolyCurve& destCurve )
	{
		destCurve.ClearFrames();
		destCurve.ClearFrameLevers();
		SizeT keyCount = sourceCurve->GetKeyFrameCount();
		for (IndexT nIdx = 0; nIdx < keyCount; nIdx++)
		{
			const Math::FloatKeyFrame& key = sourceCurve->GetKeyFrame(nIdx);
			destCurve.AddPolyKeyFrame(key,sourceCurve->GetLeftCurveType(nIdx),sourceCurve->GetRightCurveType(nIdx));

			if ( sourceCurve->GetFrameLeversCount() > nIdx) 
			{
				const Math::FloatPolyCurve::FrameLever& fl =  sourceCurve->GetFrameLever(nIdx) ;
				destCurve.AddFrameLever(fl._left, fl._right);
			}
		}
	}
	//--------------------------------------------------------------------------------
	inline  void _serializeCopyMinMaxCurve(  const Math::MinMaxCurve& sourceCurve,  Math::MinMaxCurve& destCurve )
	{
		destCurve.CopyFrom(sourceCurve);
	}
	//--------------------------------------------------------------------------------
	inline int AdjustParamType(int nType)
	{
		if (nType > (int)Particles::Emitter_SizeX && nType <= (int)Particles::Emitter_SizeZ)
			nType = (int)Particles::Emitter_SizeX;
		if (nType > (int)Particles::Emitter_VelocityX && nType <= (int)Particles::Emitter_VelocityZ)
			nType = (int)Particles::Emitter_VelocityX;
		if (nType > (int)Particles::Emitter_BoxSizeX && nType <= (int)Particles::Emitter_BoxSizeZ)
			nType = (int)Particles::Emitter_BoxSizeX;
		if (nType > (int)Particles::Affector_ForceX && nType <= (int)Particles::Affector_ForceZ)
			nType = (int)Particles::Affector_ForceX;
		if (nType > (int)Particles::Affector_ScaleX && nType <= (int)Particles::Affector_ScaleZ)
			nType = (int)Particles::Affector_ScaleX;
		if (nType > (int)Particles::Affector_ColorR && nType <= (int)Particles::Affector_ColorA)
			nType = (int)Particles::Affector_ColorR;
		if (nType > (int)Particles::Emitter_ColorR && nType <= (int)Particles::Emitter_ColorA)
			nType = (int)Particles::Emitter_ColorR;
		if (nType > (int)Particles::Affector_LimitX && nType <= (int)Particles::Affector_LimitZ)
			nType = (int)Particles::Affector_LimitX;
		if (nType > (int)Particles::Affector_GravityX && nType <= (int)Particles::Affector_GravityZ)
			nType = (int)Particles::Affector_GravityX;
		if (nType > (int)Particles::Affector_MovementX && nType <= (int)Particles::Affector_MovementZ)
			nType = (int)Particles::Affector_MovementX;
		return nType;
	}
}

#endif // __particle_fwd_decl_H__
