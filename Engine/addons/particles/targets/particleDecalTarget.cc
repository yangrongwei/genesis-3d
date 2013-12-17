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
#include "particleDecalTarget.h"
#include "particles/particlesystem.h"
#include "particles/particletarget.h"
#include "graphicsystem/GraphicSystem.h"
#include "particles/particlepool.h"

namespace Particles
{
	using namespace RenderBase;

	__ImplementClass(Particles::ParticleDecalTarget, CPFCC::TARGET_PARTICLEDECAL, Particles::ParticleTarget );

	const SizeT VertexCountPerParticle = 8;
	const SizeT IndexCountPerParticle = 36;

	//------------------------------------------------------------------------
	ParticleDecalTarget::ParticleDecalTarget():ParticleTarget()
	{		

	}
	//------------------------------------------------------------------------
	ParticleDecalTarget::~ParticleDecalTarget()
	{

	}
	//-------------------------------------------------------------------------
	ParticleTarget::TargetType ParticleDecalTarget::GetTargetType(void) const
	{
		return ParticleTarget::Decal;
	}
	//-------------------------------------------------------------------------
	bool ParticleDecalTarget::_preparePrimitiveGroup(SizeT& verticesSizeInByte, SizeT& indicesSizeInByte)
	{
		if ( !mNeedPrimitive )
			return false;

		SizeT Quota = ConstDefine::DEFAULT_TECHNIQUE_QUOTA;
		if ( mParentSystem )
		{
			Quota = mParentSystem->GetParticleQuota();
		}

		SizeT vertexCount = Quota * VertexCountPerParticle ;	
		SizeT indexCount = Quota * IndexCountPerParticle ;	

		CheckPrimitive(vertexCount, indexCount, verticesSizeInByte, indicesSizeInByte);

		return true;

	}

	Math::bbox ParticleDecalTarget::ComputerDecalBoundingBox( GPtr<ParticlePool>& pool ) const
	{
		Math::bbox bb;
		bb.begin_extend();

		Math::float4 outscale,outtranslate;
		Math::quaternion outquaternion;
		Math::matrix44  usedscaleMatrix = mParentSystem->GetWorldMatrix();

		usedscaleMatrix.decompose(outscale, outquaternion, outtranslate);
		Math::float3 scaleVector(outscale.x(), outscale.y(), outscale.z() );

		Particle* particle = pool->GetFirst();

		while ( particle )
		{

			Math::float3 vPos = particle->mPosition;
			Math::float3 size = particle->mSize;

			size *= scaleVector;
			size.x() = Math::n_abs(size.x());
			size.y() = Math::n_abs(size.y());
			size.y() = Math::n_abs(size.y());

			float maxSize = 1.415f * Math::n_max(size.x(),size.y());
			size.set(maxSize, maxSize, maxSize);
			if ( !mParentSystem->IsMoveWorldCoord())
			{
				vPos =vPos.transformPoint(mParentSystem->GetWorldMatrix());
			}
			Math::float3 min,max;

			min = vPos - size * 0.5f; 
			max = vPos + size * 0.5f;

			bb.extend( Math::point(min.x(),min.y(),min.z()));
			bb.extend( Math::point(max.x(),max.y(),max.z()));
			particle = pool->GetNext();
		}

		bb.end_extend();
		return bb;
	}

	//------------------------------------------------------------------------
	void ParticleDecalTarget::_updateTarget(GPtr<ParticlePool>& pool, Timing::Time frameTime)
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

		SizeT numVert = _updateTarget_Decal(pool,particleVertex, indicies);

		mActiveVertexCount = numVert * VertexCountPerParticle;
		mActiveIndexCount = numVert * IndexCountPerParticle;
		if ( mParentSystem )
		{
			if ( mParentSystem->IsUseExternBoundingBox() )
			{
			}
			else
			{
				Math::bbox bb = ComputerDecalBoundingBox( pool );
				const Math::matrix44& worldMat = mParentSystem->GetWorldMatrix();
				Math::matrix44 invMat = Math::matrix44::inverse(worldMat);
				bb.transform(invMat);
				mParentSystem->SetLocalBoundingBox( bb );

			}
		}	
		Graphic::GraphicSystem::Instance()->UpdatePrimitiveHandle(mPrimitiveHandle, &dvb, &dib);
	}
	//------------------------------------------------------------------------
	void 
		ParticleDecalTarget::_updateParticle_Common( Particle* particle, ParticleVertexData* particleVertex, ushort* indicies, IndexT vertIndex)
	{

		Math::float3 vPos = particle->mPosition;
		Math::Color32 tColor = particle->mColor;
		Math::float3 scaledSize = particle->mSize;
		Math::scalar zRotate = particle->mZRotation;


		Math::float4 outscale,outtranslate;
		Math::quaternion outquaternion;
		Math::matrix44  usedscaleMatrix = mParentSystem->GetWorldMatrix();

		usedscaleMatrix.decompose(outscale, outquaternion, outtranslate);
		Math::float3 scaleVector(outscale.x(), outscale.y(), outscale.z() );
		scaledSize *= scaleVector;

		if ( !mParentSystem->IsMoveWorldCoord())
		{
			vPos =vPos.transformPoint(mParentSystem->GetWorldMatrix());
		}

		Math::float3 absScaledSize;

		absScaledSize = scaledSize;
		absScaledSize.x() = Math::n_abs( scaledSize.x() );
		absScaledSize.y() = Math::n_abs( scaledSize.y() );

		scaledSize.z() = Math::n_max(absScaledSize.x(),absScaledSize.y());

		for (int i=0; i<8; i++ )
		{
			Math::float3 vNDC = Math::float3((i==0 || i==1 || i==4 || i==5) ? -0.5f : 0.5f,
				(i==0 || i==3 || i==4 || i==7) ? -0.5f : 0.5f,
				(i==0 || i==1 || i==2 || i==3) ? -0.5f : 0.5f );

			particleVertex[i].mPosition =  vNDC * scaledSize;
			particleVertex[i].mNormal = vPos;
			particleVertex[i].mColor = tColor.HexARGB();
			particleVertex[i].mTexCoord.set( Math::n_sin(zRotate), Math::n_cos(zRotate) );
		}

		IndexT beingVertex = vertIndex * VertexCountPerParticle;

		static uint16 nFaces[6][4] = {{0,1,2,3},
		{4,7,6,5},
		{0,3,7,4},
		{1,5,6,2},
		{0,4,5,1},
		{3,2,6,7}
		};

		for(int i=0; i < 6; i++)
		{
			indicies[i * 6] = beingVertex + nFaces[i][0];
			indicies[i * 6 + 1] = beingVertex + nFaces[i][1];
			indicies[i * 6 + 2] = beingVertex + nFaces[i][2];

			indicies[i * 6 + 3] = beingVertex + nFaces[i][0];
			indicies[i * 6 + 4] = beingVertex + nFaces[i][2];
			indicies[i * 6 + 5] = beingVertex + nFaces[i][3];
		}

	}
	//------------------------------------------------------------------------
	SizeT 
		ParticleDecalTarget::_updateTarget_Decal( GPtr<ParticlePool>& pool, ParticleVertexData* particleVertex, ushort* indicies )
	{
		n_assert( particleVertex && indicies);
		SizeT retNum = 0;
		Particle* particle = pool->GetFirst();

		while ( particle )
		{

			Math::float3 vPos = particle->mPosition;

			_updateParticle_Common(particle,  particleVertex, indicies, retNum);

			particleVertex += VertexCountPerParticle;
			indicies += IndexCountPerParticle;

			++retNum;
			particle = pool->GetNext();
		}

		return retNum;
	}

	Math::matrix44 ParticleDecalTarget::GetDecalRotation()
	{
		Math::float4 outscale,outtranslate;
		Math::quaternion outquaternion;

		Math::matrix44  usedRotationMatrix = mParentSystem->GetWorldMatrix();

		usedRotationMatrix.decompose(outscale, outquaternion, outtranslate);
		Math::float4 oneScale = Math::float4(1.0f,1.0f,1.0f,1.0f);
		Math::float4 zeroPos = Math::float4(0.0f,0.0f,0.0f,0.0f);

		return Math::matrix44::transformation(oneScale, outquaternion, zeroPos);
	}

}