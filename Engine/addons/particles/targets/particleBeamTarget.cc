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
#include "particleBeamTarget.h"
#include "particles/particlesystem.h"
#include "particles/particletarget.h"
#include "math/ray.h"
#include "graphicsystem/GraphicSystem.h"
#include "particles/particlepool.h"


namespace Particles
{
	using namespace RenderBase;

	__ImplementClass(Particles::ParticleBeamTarget, CPFCC::TARGET_BEAM, Particles::ParticleTarget );

	const SizeT DEFAULT_MAX_BEAM_ELEMENTS = 10;
	const Math::scalar DEFAULT_UPDATE_INTERVAL = 0.1f;
	const SizeT VertexCountPerParticle = 4;
	const SizeT IndexCountPerParticle = 6;
	const SizeT IndexCountParticipate = 5;

	//------------------------------------------------------------------------
	ParticleBeamTarget::ParticleBeamTarget():ParticleTarget(),
		mMaxElements(DEFAULT_MAX_BEAM_ELEMENTS),
		mUpdateInterval(DEFAULT_UPDATE_INTERVAL),
		mDestPos(Math::float3(0.0f,0.0f,0.0f)),
		mNoiseXMax(1.0f),
		mNoiseXMin(-1.0f),
		mNoiseYMax(1.0f),
		mNoiseYMin(-1.0f),
		mNoiseZMax(1.0f),
		mNoiseZMin(-1.0f),
		mTime(0)
	{		
	}

	//------------------------------------------------------------------------
	ParticleBeamTarget::~ParticleBeamTarget()
	{

	}	
	//------------------------------------------------------------------------
	ParticleTarget::TargetType ParticleBeamTarget::GetTargetType(void) const
	{
		return ParticleTarget::Beam;
	}
	//-------------------------------------------------------------------------
	bool ParticleBeamTarget::_preparePrimitiveGroup(SizeT& verticesSizeInByte, SizeT& indicesSizeInByte)
	{
		if ( !mNeedPrimitive )
			return false;

		SizeT Quota = ConstDefine::DEFAULT_TECHNIQUE_QUOTA;
		if ( mParentSystem )
		{
			Quota = mParentSystem->GetParticleQuota();
		}

		SizeT vertexCount = Quota * VertexCountPerParticle * IndexCountPerParticle * mMaxElements;

		if ( vertexCount <= 0 )
		{
			return false;
		}
		SizeT indexCount = Quota * IndexCountPerParticle * IndexCountPerParticle * mMaxElements;	

		CheckPrimitive(vertexCount, indexCount, verticesSizeInByte, indicesSizeInByte);

		return true;

	}
	//------------------------------------------------------------------------
	void ParticleBeamTarget::_updateTarget(GPtr<ParticlePool>& pool, Timing::Time frameTime)
	{
		n_assert(pool.isvalid());
		if (pool->IsEmpty())
		{
			restActiveElemCount();
			return;
		}
		if (  (Math::scalar)(mParentSystem->GetEmitterTime() - mTime) >=  mUpdateInterval ||
			(Math::scalar)(mParentSystem->GetEmitterTime() - mTime) < 0)
		{
			mTime = mParentSystem->GetEmitterTime();
		}
		else
		{
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

		SizeT numVert = 0;


		const Math::matrix44* camera = &(ConstDefine::MATRIX_IDENTITY);
		if ( mParentSystem )
		{
			camera = &(mParentSystem->GetCameraMatrix());		
		}

		Beam_Camera_OP op;

		const Math::float4& cameraPos4 = camera->get_position();
		op.cameraPos.set(cameraPos4.x(), cameraPos4.y(), cameraPos4.z() );

		Math::float4 outscale,outtranslate;
		Math::quaternion outquaternion;
		Math::matrix44  usedscaleMatrix = mParentSystem->GetWorldMatrix();

		usedscaleMatrix.decompose(outscale, outquaternion, outtranslate);
		Math::float3 scaleVector(outscale.x(), outscale.y(), outscale.z() );
		op.parentScale = scaleVector;

		numVert = _updateTarget_Beam(pool,particleVertex, indicies, op);

		mActiveVertexCount = numVert * VertexCountPerParticle;
		mActiveIndexCount = numVert * IndexCountPerParticle;
		if ( mParentSystem )
		{
			if ( mParentSystem->IsUseExternBoundingBox() )
			{
			}
			else
			{
				Math::bbox bb = computerBoundingBox(particleVertex, numVert * VertexCountPerParticle );
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
		ParticleBeamTarget::_updateParticle_Common( Particle* particle, IndexT t, ParticleVertexData* particleVertex, ushort* indicies, IndexT vertIndex,float v0,float v1)
	{
		Math::Color32 tColor = particle->mColor;
		particleVertex[0].mColor = tColor.HexARGB();
		particleVertex[1].mColor = tColor.HexARGB();
		particleVertex[2].mColor = tColor.HexARGB();
		particleVertex[3].mColor = tColor.HexARGB();


		particleVertex[0].mTexCoord.set(  0.0, v0 );
		particleVertex[1].mTexCoord.set(  0.0, v1 );
		particleVertex[2].mTexCoord.set(  1.0, v1 );
		particleVertex[3].mTexCoord.set(  1.0, v0 );


		IndexT beingVertex = vertIndex * VertexCountPerParticle;

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
		ParticleBeamTarget::_updateTarget_Beam( GPtr<ParticlePool>& pool, ParticleVertexData* particleVertex, ushort* indicies, const T&  op )
	{

		n_assert( particleVertex && indicies);
		SizeT retNum = 0;
		Particle* particle = pool->GetFirst();


		Math::float4 SysPosition = mParentSystem->GetWorldMatrix().get_position();
		Math::float3 originPos = Math::float3(SysPosition.x(),SysPosition.y(),SysPosition.z());
		while ( particle )
		{
			particle->mPosition = originPos;
			Math::float3 diffdir = originPos -  mDestPos;
			diffdir = diffdir / (Math::scalar)mMaxElements;
			Math::float3 vLastPos = mDestPos;
			Math::float3 vPos;
			Math::float3 vTemp;
			Util::Array<Math::float3> tempPos;
			Math::scalar fStride = 1.0f /(Math::scalar)IndexCountParticipate;
			tempPos.Append(vLastPos);
			IndexT last = 0;
			IndexT lalast = -1;
			for (SizeT elemIt = 1; elemIt <= mMaxElements; elemIt++)
			{
				vTemp = vLastPos + diffdir;;
				vLastPos = vTemp;
				vTemp.x() += Math::n_rand(mNoiseXMin,mNoiseXMax);
				vTemp.y() += Math::n_rand(mNoiseYMin,mNoiseYMax);
				vTemp.z() += Math::n_rand(mNoiseZMin,mNoiseZMax);

				Math::float3 pT2; 
				Math::float3 pT1;

				pT2 = vTemp - tempPos[last];

				if(lalast < 0)
					pT1 = pT2;
				else
					pT1 = tempPos[last] - tempPos[lalast];

				for(int i=1;i<IndexCountParticipate;i++)
				{
					Math::float3 pOut;
					Math::float3::hermite(&pOut,&tempPos[last],&pT1,&vTemp,&pT2,i*fStride);
					tempPos.Append(pOut);
				}
				tempPos.Append(vTemp);
				lalast = last;
				last = tempPos.Size() - 1;
			}
			SizeT pointCount = tempPos.Size();
			Math::scalar totalLen = 0.0f;
			for(SizeT t=1;t<pointCount;t++)
			{
				totalLen += (tempPos[t] - tempPos[t-1]).length();
			}
			float beginV = 0;
			float endV;
			for(SizeT idx = 1;idx < pointCount;idx++)
			{
				Math::float3 vPos = tempPos[idx];
				Math::float3 vLastPos = tempPos[idx-1];

				op(particle, vPos, vLastPos, idx, particleVertex, indicies);
				endV = beginV + (vPos - vLastPos).length() / totalLen;
				_updateParticle_Common(particle, idx,  particleVertex, indicies, retNum,1.0f - beginV,1.0f - endV);

				beginV = endV;
				particleVertex += VertexCountPerParticle;
				indicies += IndexCountPerParticle;
				++retNum;
			}


			particle = pool->GetNext();
		}
		return retNum;
	}

}