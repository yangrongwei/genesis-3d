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
#ifndef __particlebillboardtarget_H__
#define __particlebillboardtarget_H__
#include "particles/particle_fwd_decl.h"
#include "particles/particletarget.h"


namespace Particles
{
	class ParticleBillBoardTarget: public ParticleTarget
	{
		__DeclareSubClass(ParticleBillBoardTarget, ParticleTarget );	


	public:
		ParticleBillBoardTarget();
		virtual ~ParticleBillBoardTarget();

		enum BillBoardType
		{
			Billboard_Camera	= 0,	
			Billboard_Camera_Y	= 1,	
			Billboard_XZ        = 2,			
			Billboard_ORIENTED_SELF	= 3,
			Billboard_ORIENTED_DIR		= 4,
			HorizontalPlane_XZ = 5,
			HorizontalPlane_YZ = 6,
			HorizontalPlane_XY = 7,
		};

		enum BillboardAlignType
		{
			CENTERALIGN = 0,
			TOPCENTERALIGN = 1,
			BOTTOMALIGN = 2,
			LEFTCENTERALIGN = 3,
			RIGHTCENTERALIGN = 4,
			ALIGNCOUNTS,
		};

		struct BillboardAlignWeight
		{
			float leftTopWeight_X,leftTopWeight_Y;
			float leftBottomWeight_X,leftBottomWeight_Y;
			float rightBottomWeight_X,rightBottomWeight_Y;
			float rightUpWeight_X,rightUpWeight_Y;
		};

		static BillboardAlignWeight alignType[ALIGNCOUNTS];

		class Camera_OP_PosAligned:public Camera_OP
		{
		public:
			void operator()( 	
				Particle* particle, 
				const Math::float3& derivedPos,
				const Math::float3& lastDerivedPos,
				ParticleVertexData* particleVertex, 
				ushort* indicies) const
			{

				Math::float3 dir = cameraPos - derivedPos ;
				dir.normalise();	

				Math::float3 upVec;				
				Math::scalar stretch;

				if ( ot == OT_DIRECT)
				{
					upVec = derivedPos-lastDerivedPos;
					upVec = upVec.transformVector(parentMatrix);
					stretch = upStretch;
				}
				else
				{
					upVec = upVector;
					stretch = 1.0f;
				}
	
				upVec.normalise();
				Math::float3 rightVector =upVec.crossProduct( dir );
				rightVector.normalise();

				upVec = upVec * parentScale;
				rightVector = rightVector * parentScale;

				Math::float3 up    =  upVec * particle->mSize.y() * 0.5 * stretch;
				Math::float3 right = rightVector * particle->mSize.x() * 0.5;

				particleVertex[0].mPosition = derivedPos + ParticleBillBoardTarget::alignType[bat].leftTopWeight_X * up + right * ParticleBillBoardTarget::alignType[bat].leftTopWeight_Y;
				particleVertex[0].mNormal = dir;

				particleVertex[1].mPosition = derivedPos + ParticleBillBoardTarget::alignType[bat].leftBottomWeight_X * up + right * ParticleBillBoardTarget::alignType[bat].leftBottomWeight_Y;
				particleVertex[1].mNormal = dir;

				particleVertex[2].mPosition = derivedPos + ParticleBillBoardTarget::alignType[bat].rightBottomWeight_X * up + right * ParticleBillBoardTarget::alignType[bat].rightBottomWeight_Y;
				particleVertex[2].mNormal = dir;

				particleVertex[3].mPosition = derivedPos + ParticleBillBoardTarget::alignType[bat].rightUpWeight_X*up + right * ParticleBillBoardTarget::alignType[bat].rightUpWeight_Y;
				particleVertex[3].mNormal = dir;
			}

			ParticleBillBoardTarget::BillboardAlignType bat;
			Math::matrix44  parentMatrix;
			Math::float3  parentScale;
		};

		class BillBoard_XZ_PosAligned_OP:public BillBoard_XZ_OP
		{
		public:
			void operator()( 	
				Particle* particle, 
				const Math::float3& derivedPos,
				const Math::float3& lastDerivedPos,
				ParticleVertexData* particleVertex, 
				ushort* indicies) const
			{

				Math::float3 xOff(1.0, 0.0, 0.0);
				Math::float3 zOff(0.0, 0.0, 1.0);
				Math::float3 up,right;

				if ( ot == OT_DIRECT)
				{
					Math::float3 dir = derivedPos-lastDerivedPos;
					if (dir.length() > 0.00001F)
					{
						dir.y() = 0.0;
						dir.normalise();
						xOff = dir;
						zOff.x() = -xOff.z();
						zOff.z() = xOff.x();
					}
				}

				xOff *= ( particle->mSize.x() * 0.5f );
				zOff *= ( particle->mSize.y() * 0.5f );
				up = zOff * parentScale;
				right = xOff * parentScale;


				particleVertex[0].mPosition = derivedPos + ParticleBillBoardTarget::alignType[bat].leftTopWeight_X * up + right * ParticleBillBoardTarget::alignType[bat].leftTopWeight_Y;
				particleVertex[0].mNormal.set(0.0, -1.0, 0.0);

				particleVertex[1].mPosition = derivedPos + ParticleBillBoardTarget::alignType[bat].leftBottomWeight_X * up + right * ParticleBillBoardTarget::alignType[bat].leftBottomWeight_Y;
				particleVertex[1].mNormal.set(0.0, -1.0, 0.0);

				particleVertex[2].mPosition = derivedPos + ParticleBillBoardTarget::alignType[bat].rightBottomWeight_X * up + right * ParticleBillBoardTarget::alignType[bat].rightBottomWeight_Y;
				particleVertex[2].mNormal.set(0.0, -1.0, 0.0);

				particleVertex[3].mPosition = derivedPos + ParticleBillBoardTarget::alignType[bat].rightUpWeight_X*up + right * ParticleBillBoardTarget::alignType[bat].rightUpWeight_Y;
				particleVertex[3].mNormal.set(0.0, -1.0, 0.0);

			}

			ParticleBillBoardTarget::BillboardAlignType bat;
			Math::float3 parentScale;
		};

		class HorizontalPlane_OP
		{
		public:
			enum ALignType
			{
				ALIGN_XZ,
				ALIGN_YZ,
				ALIGN_XY,
			};

			void operator()( 	
				Particle* particle, 
				const Math::float3& derivedPos,
				const Math::float3& lastDerivedPos,
				ParticleVertexData* particleVertex, 
				ushort* indicies) const
			{
				const float offset[10] = 
				{
					0.0,0.0,
					-0.5f,0.0,
					0.5f,0.0,
					0.0,0.5f,
					0.0,-0.5f,
				};

				Math::float4 _scale(0.5f*particle->mSize.x()*parentScale.x(),
					0.5f*particle->mSize.y()*parentScale.y(),
					0.5f*particle->mSize.z()*parentScale.z(),
					0);	
				Math::float3 _axis(0,0,1);
				_axis =  parentQuaternion * _axis;
				Math::quaternion _rq = Math::quaternion::rotationaxis( Math::float4(_axis.x(),_axis.y(),_axis.z(),1.0f) , particle->mZRotation  );
				Math::quaternion finalQ = Math::quaternion::multiply(_rq, parentQuaternion ) ;
				Math::float4 _pos(derivedPos.x(),derivedPos.y(),derivedPos.z(),0);
				Math::matrix44 _mat = Math::matrix44::transformation(_scale, finalQ, _pos);

				Math::float3 vertex0,vertex1,vertex2,vertex3,normal0;
				Math::matrix44 offsetTransform;

				if (bt == ALIGN_XZ)
				{
					vertex0 = Math::float3(-0.5,0.0,0.5);
					vertex1 = Math::float3(-0.5,0.0,-0.5);
					vertex2 = Math::float3(0.5,0.0,-0.5);
					vertex3 = Math::float3(0.5,0.0,0.5);

					offsetTransform= Math::matrix44::translation(offset[bat*2],0.0,offset[bat*2+1]);
					normal0 = Math::float3(0.0,-1.0,0.0);
				}
				else if (bt == ALIGN_XY)
				{
					vertex0 = Math::float3(-0.5,0.5,0.0);
					vertex1 = Math::float3(-0.5,-0.5,0.0);
					vertex2 = Math::float3(0.5,-0.5,0.0);
					vertex3 = Math::float3(0.5,0.5,0.0);

					offsetTransform = Math::matrix44::translation(offset[bat*2],offset[bat*2+1],0.0);
					normal0 = Math::float3(0.0,0.0,-1.0);
				}
				else
				{
					vertex0 = Math::float3(0.0,-0.5,0.5);
					vertex1 = Math::float3(0.0,-0.5,-0.5);
					vertex2 = Math::float3(0.0,0.5,-0.5);
					vertex3 = Math::float3(0.0,0.5,0.5);

					offsetTransform = Math::matrix44::translation(0.0,offset[bat*2],offset[bat*2+1]);
					normal0 = Math::float3(-1.0,0.0,0.0);
				}

				_mat = Math::matrix44::multiply(_mat,offsetTransform);

				particleVertex[0].mPosition = vertex0.transformPoint(_mat);
				particleVertex[1].mPosition = vertex1.transformPoint(_mat);
				particleVertex[2].mPosition = vertex2.transformPoint(_mat);
				particleVertex[3].mPosition = vertex3.transformPoint(_mat);

				particleVertex[0].mNormal = normal0.transformVector(_mat);
				particleVertex[1].mNormal = particleVertex[0].mNormal;
				particleVertex[2].mNormal = particleVertex[0].mNormal;
				particleVertex[3].mNormal = particleVertex[0].mNormal;
			}

			ALignType   bt;
			BillboardAlignType bat;
			Math::quaternion  parentQuaternion;
			Math::float3      parentScale;
		};

		void SetBillBoardType( BillBoardType t);
		BillBoardType GetBillBoardType(void) const;

		void SetBillBoardAlignType( BillboardAlignType bat );
		BillboardAlignType GetBillBoardAlignType(void) const;

		virtual ParticleTarget::TargetType GetTargetType(void) const;

		virtual void _updateTarget(GPtr<ParticlePool>& pool, Timing::Time frameTime);

		bool _preparePrimitiveGroup(SizeT& verticesSizeInByte, SizeT& indicesSizeInByte);

		void _updateParticle_Common( Particle* particle, ParticleVertexData* particleVertex, ushort* indicies , IndexT particleIndex);

		template<typename T>
		SizeT _updateTarget_BillBoard(GPtr<ParticlePool>& pool, ParticleVertexData* particleVertex, ushort* indicies, const T&  op, bool isRotated = true);

	protected:
		BillBoardType mBillBoardType;
		BillboardAlignType mBillBoardAlignType;
	public:
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		// copy 
		virtual void CopyFrom( const ParticleTargetPtr& target );
	};

	//------------------------------------------------------------------------
	inline
		void 
		ParticleBillBoardTarget::SetBillBoardType( BillBoardType t)
	{
		mBillBoardType = t;
	}
	//------------------------------------------------------------------------
	inline
		ParticleBillBoardTarget::BillBoardType 
		ParticleBillBoardTarget::GetBillBoardType(void) const
	{
		return mBillBoardType;
	}
	//------------------------------------------------------------------------
	inline
		ParticleTarget::TargetType 
		ParticleBillBoardTarget::GetTargetType(void) const
	{
		return ParticleTarget::BillBoard;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleBillBoardTarget::SetBillBoardAlignType( BillboardAlignType bat )
	{
		mBillBoardAlignType = bat;
	}
	//------------------------------------------------------------------------
	inline
		ParticleBillBoardTarget::BillboardAlignType 
		ParticleBillBoardTarget::GetBillBoardAlignType(void) const
	{
		return mBillBoardAlignType;
	}

}









#endif // __particlebillboardtarget_H__
