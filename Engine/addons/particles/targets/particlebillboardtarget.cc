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
#include "particles/targets/particlebillboardtarget.h"
#include "particles/particlesystem.h"
#include "graphicsystem/GraphicSystem.h"
#include "particles/particlepool.h"

namespace Particles
{
	using namespace RenderBase;

	__ImplementClass(Particles::ParticleBillBoardTarget, CPFCC::TARGET_BILLBOARD, Particles::ParticleTarget );

	const SizeT VertexCountPerParticle = 4;
	const SizeT IndexCountPerParticle = 6;

	Math::scalar rotangle = 0.1f;

	ParticleBillBoardTarget::BillboardAlignWeight ParticleBillBoardTarget::alignType[ALIGNCOUNTS] ={
		1.0f,-1.0f, -1.0f,-1.0f, -1.0f,1.0f, 1.0f,1.0f,
		0.0f,-1.0f, -2.0f,-1.0f, -2.0f,1.0f, 0.0f,1.0f,
		2.0f,-1.0f, 0.0f,-1.0f,  0.0f,1.0f, 2.0f,1.0f,
		1.0f,0.0f, -1.0f,0.0f, -1.0f,2.0f, 1.0f,2.0f,
		1.0f,-2.0f, -1.0f,-2.0f, -1.0f,0.0f, 1.0f,0.0f,
	};

	ParticleBillBoardTarget::ParticleBillBoardTarget()
		: mBillBoardType(Billboard_Camera),
		mBillBoardAlignType(CENTERALIGN)
	{

	}
	//------------------------------------------------------------------------
	ParticleBillBoardTarget::~ParticleBillBoardTarget()
	{

	}
	//------------------------------------------------------------------------
	bool 
		ParticleBillBoardTarget::_preparePrimitiveGroup(SizeT& verticesSizeInByte, SizeT& indicesSizeInByte)
	{
		if ( !mNeedPrimitive )
			return false;

		SizeT Quota = ConstDefine::DEFAULT_TECHNIQUE_QUOTA;
		if ( mParentSystem )
		{
			Quota = mParentSystem->GetParticleQuota();
		}

		SizeT vertexCount = Quota * VertexCountPerParticle;	
		SizeT indexCount = Quota * IndexCountPerParticle;	

		CheckPrimitive(vertexCount, indexCount, verticesSizeInByte, indicesSizeInByte);
		return true;
	}
	//------------------------------------------------------------------------
	void 
		ParticleBillBoardTarget::_updateParticle_Common( Particle* particle, ParticleVertexData* particleVertex, ushort* indicies, IndexT particleIndex )
	{
		Math::Color32 tColor = particle->mColor;
		particleVertex[0].mColor = tColor.HexARGB();
		particleVertex[1].mColor = tColor.HexARGB();
		particleVertex[2].mColor = tColor.HexARGB();
		particleVertex[3].mColor = tColor.HexARGB();

		const UVRect* uvRect = getUVRect( particle->mTexCoordIndex );
		if ( uvRect )
		{
			particleVertex[0].mTexCoord.set(  uvRect->x,                 uvRect->y );
			particleVertex[1].mTexCoord.set(  uvRect->x,                 uvRect->y + uvRect->height );
			particleVertex[2].mTexCoord.set(  uvRect->x + uvRect->width, uvRect->y + uvRect->height );
			particleVertex[3].mTexCoord.set(  uvRect->x + uvRect->width, uvRect->y );
		}
		else
		{
			particleVertex[0].mTexCoord.set(  0.0, 0.0 );
			particleVertex[1].mTexCoord.set(  0.0, 1.0 );
			particleVertex[2].mTexCoord.set(  1.0, 1.0 );
			particleVertex[3].mTexCoord.set(  1.0, 0.0 );
		}

		IndexT beingVertex = particleIndex * VertexCountPerParticle;

		indicies[0] = beingVertex;
		indicies[1] = beingVertex + 1;
		indicies[2] = beingVertex + 2;
		indicies[3] = beingVertex + 2;
		indicies[4] = beingVertex + 3;
		indicies[5] = beingVertex ;
	}

	//------------------------------------------------------------------------
	template<typename T>
	SizeT 
		ParticleBillBoardTarget::_updateTarget_BillBoard( GPtr<ParticlePool>& pool, ParticleVertexData* particleVertex, ushort* indicies, const T&  op, bool isRotated)
	{
		n_assert( particleVertex && indicies);
		SizeT numParticle = 0;
		Particle* particle = pool->GetFirst();
		while ( !pool->End() )
		{
			if (particle)
			{
				Math::float3 vPos = particle->mPosition;
				SizeT opCount = particle->mOrbitPositions.Size();
				Math::float3 vLastPos = particle->mPosition;
				if ( mOrientType == OT_DIRECT)
				{
					for(IndexT id = 0; id< opCount;id++)
					{
						vLastPos = particle->mOrbitPositions[id];
						Math::float3 upVec = vLastPos - particle->mPosition;
						if(upVec.lengthsq() > Math::float3::epsilon)
							break;
					}
				}
				if ( !mParentSystem->IsMoveWorldCoord() )
				{
					vPos =vPos.transformPoint(mParentSystem->GetWorldMatrix());
					vLastPos = vLastPos.transformPoint(mParentSystem->GetWorldMatrix());
				}

				op(particle, vPos, vLastPos,  particleVertex, indicies);
				{
					if  ( isRotated && (particle->mZRotation > (N_PI/180) || particle->mZRotation < (-N_PI/180)) )
						_RotatorParticle(particle, particleVertex);
				}

				_updateParticle_Common(particle, particleVertex, indicies, numParticle);
				particleVertex += VertexCountPerParticle;
				indicies += IndexCountPerParticle;
				++numParticle;

				if ( mOrientType == OT_DIRECT)
				{
					if(opCount == 0)
						particle->mOrbitPositions.Append(particle->mPosition);
					else
					{
						Math::float3 upVec = particle->mOrbitPositions[opCount-1] - particle->mPosition;
						if(upVec.lengthsq() > Math::float3::epsilon)
						{
							particle->mOrbitPositions.Append(particle->mPosition);
							if(particle->mOrbitPositions.Size() > 2)
								particle->mOrbitPositions.EraseIndex(0);
						}
					}
				}
			}
			particle = pool->GetNext();
		}
		return numParticle;
	}
	//------------------------------------------------------------------------
	void  
		ParticleBillBoardTarget::_updateTarget( GPtr<ParticlePool>& pool, Timing::Time frameTime)
	{
		n_assert(pool.isvalid());
		if (pool->IsEmpty())
		{
			restActiveElemCount();
			return;
		}
		SizeT verticesSizeInByte = 0;
		SizeT indicesSizeInByte = 0;	
		if( !_preparePrimitiveGroup(verticesSizeInByte, indicesSizeInByte) )
		{
			return;
		}
		n_assert(mPrimitiveHandle.IsValid());

		Graphic::DynamicBuffer dvb;
		Graphic::DynamicBuffer dib;

		dvb.SetSize(verticesSizeInByte);
		dib.SetSize(indicesSizeInByte);
		ParticleVertexData* particleVertex = dvb.GetBufferPtr<ParticleVertexData>();
		ushort* indicies = dib.GetBufferPtr<ushort>();
		n_assert( particleVertex && indicies );

		SizeT numParticle = 0;
		Math::float3 upVector;

		Math::float4 outscale,outtranslate;
		Math::quaternion outquaternion;
		Math::matrix44  usedscaleMatrix = mParentSystem->GetWorldMatrix();

		usedscaleMatrix.decompose(outscale, outquaternion, outtranslate);
		Math::float3 scaleVector(outscale.x(), outscale.y(), outscale.z() );
		switch ( mBillBoardType )
		{
		case Billboard_Camera:
			{
				const Math::matrix44* camera = &(ConstDefine::MATRIX_IDENTITY);
				if ( mParentSystem && mParentSystem )
				{
					camera = &(mParentSystem->GetCameraMatrix());		
				}

				Camera_OP_PosAligned op;
				bool bStretch = false;
				op.ot = mOrientType;
				op.bat = this->GetBillBoardAlignType();
				op.parentMatrix = ConstDefine::MATRIX_IDENTITY;
				op.parentScale = scaleVector;

				if ( mOrientType == OT_DIRECT)
				{
					op.upStretch = mStretchScale;
					bStretch = true;

					if ( !mParentSystem->IsMoveWorldCoord() )
					{
						op.parentMatrix = mParentSystem->GetWorldMatrix();
					}
				}
				else if (mOrientType == ParticleTarget::OT_NONE)
				{
					const Math::float4& upVector4 = camera->get_yaxis();
					op.upVector.set(upVector4.x(), upVector4.y(), upVector4.z() );
					op.upVector.normalise();
				}

				const Math::float4& cameraPos4 = camera->get_position(); 
				op.cameraPos.set(cameraPos4.x(), cameraPos4.y(), cameraPos4.z() );

				numParticle = _updateTarget_BillBoard(pool,particleVertex, indicies, op, !bStretch);
			}
			break;
		case Billboard_Camera_Y:
			{
				const Math::matrix44* camera = &(ConstDefine::MATRIX_IDENTITY);
				if ( mParentSystem && mParentSystem )
				{
					camera = &(mParentSystem->GetCameraMatrix());		
				}
				Camera_OP_PosAligned op;
				bool bStretch = false;
				op.ot = OT_NONE;
				op.bat = this->GetBillBoardAlignType();
				op.parentMatrix = ConstDefine::MATRIX_IDENTITY;
				op.parentScale = scaleVector;

				upVector = Math::float3(0.0, 1.0, 0.0 );
				upVector = outquaternion * upVector;
				op.upVector.set(upVector.x(), upVector.y(), upVector.z() );
				op.upVector.normalise();
				const Math::float4& cameraPos4 = camera->get_position(); 
				op.cameraPos.set(cameraPos4.x(), cameraPos4.y(), cameraPos4.z() );

				numParticle = _updateTarget_BillBoard(pool,particleVertex, indicies, op, !bStretch);
			}
			break;
		case Billboard_XZ:
			{
				BillBoard_XZ_PosAligned_OP op;
				bool bStretch = false;
				op.ot = OT_NONE;
				op.bat = this->GetBillBoardAlignType();
				op.parentScale = scaleVector;

				numParticle = _updateTarget_BillBoard(pool,particleVertex, indicies, op, !bStretch);
			}
			break;
		case HorizontalPlane_XZ:
			{
				HorizontalPlane_OP op;
				op.bt = HorizontalPlane_OP::ALIGN_XZ;
				op.bat = this->GetBillBoardAlignType();
				op.parentQuaternion = Math::quaternion::identity();
				op.parentScale = scaleVector;

				if (mParentSystem)
				{
					op.parentQuaternion = mParentSystem->GetDerivedRotation();
				}
				numParticle = _updateTarget_BillBoard(pool,particleVertex, indicies, op, false);
			}
			break;
		case HorizontalPlane_YZ:
			{
				HorizontalPlane_OP op;
				op.bt = HorizontalPlane_OP::ALIGN_YZ;
				op.bat = this->GetBillBoardAlignType();
				op.parentQuaternion = Math::quaternion::identity();
				op.parentScale = scaleVector;

				if (mParentSystem)
				{
					op.parentQuaternion = mParentSystem->GetDerivedRotation();
				}
				numParticle = _updateTarget_BillBoard(pool,particleVertex, indicies, op, false);
			}
			break;
		case HorizontalPlane_XY:
			{
				HorizontalPlane_OP op;
				op.bt = HorizontalPlane_OP::ALIGN_XY;
				op.bat = this->GetBillBoardAlignType();
				op.parentQuaternion = Math::quaternion::identity();
				op.parentScale = scaleVector;

				if (mParentSystem)
				{
					op.parentQuaternion = mParentSystem->GetDerivedRotation();
				}
				numParticle = _updateTarget_BillBoard(pool,particleVertex, indicies, op, false);
			}
			break;
		case Billboard_ORIENTED_SELF:
		case Billboard_ORIENTED_DIR:
			{
				const Math::matrix44* camera = &(ConstDefine::MATRIX_IDENTITY);
				if ( mParentSystem && mParentSystem )
				{
					camera = &(mParentSystem->GetCameraMatrix());		
				}

				Camera_OP op;				
				op.upVector.set(upVector.x(), upVector.y(), upVector.z() );
				op.upVector.normalise();
				const Math::float4& cameraPos4 = camera->get_position(); 
				op.cameraPos.set(cameraPos4.x(), cameraPos4.y(), cameraPos4.z() );

				numParticle = _updateTarget_BillBoard(pool,particleVertex, indicies, op);
			}
			break;
		}
		mActiveVertexCount = numParticle * VertexCountPerParticle;
		mActiveIndexCount = numParticle * IndexCountPerParticle;

		if ( mParentSystem )
		{
			if ( mParentSystem->IsUseExternBoundingBox() )
			{
			}
			else
			{
				Math::bbox bb = computerBoundingBox(particleVertex, numParticle * VertexCountPerParticle );
				const Math::matrix44& worldMat = mParentSystem->GetWorldMatrix();
				Math::matrix44 invMat = Math::matrix44::inverse(worldMat);
				bb.transform(invMat);
				mParentSystem->SetLocalBoundingBox( bb );
			}
		}
		Graphic::GraphicSystem::Instance()->UpdatePrimitiveHandle(mPrimitiveHandle, &dvb, &dib);
	}
}