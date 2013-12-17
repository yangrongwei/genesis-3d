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
#include "particleTrailTarget.h"
#include "particles/particlesystem.h"
#include "particles/particletarget.h"
#include "graphicsystem/GraphicSystem.h"
#include "particles/particlepool.h"

namespace Particles
{
	using namespace RenderBase;

	__ImplementClass(Particles::ParticleTrailTarget, CPFCC::TARGET_TRAIL, Particles::ParticleTarget );

	const SizeT VertexCountPerParticle = 4;
	const SizeT DEFAULT_MAX_ELEMENTS = 10;
	const SizeT IndexCountPerParticle = 6;
	const SizeT IndexCountParticipate = 5;

	//------------------------------------------------------------------------
	ParticleTrailTarget::ParticleTrailTarget():ParticleTarget(),
		mMaxElements(DEFAULT_MAX_ELEMENTS),
		mTrailLength(10.0f),
		mAlphaLife(1.0f) ,
		mAmplitude(0.0f),
		mAmplitudeLife(1.0f),
		mWaveLength(20.0f)
	{
		
		mLineColorA.SetCurveState(Math::MinMaxCurve::Curve);
		mLineColorR.SetCurveState(Math::MinMaxCurve::Curve);
		mLineColorG.SetCurveState(Math::MinMaxCurve::Curve);
		mLineColorB.SetCurveState(Math::MinMaxCurve::Curve);
		Util::Array<Math::float2> _list;
		Util::Array<bool> _type;
		_list.Append(Math::float2(0,1));
		_type.Append(false);
		_type.Append(false);
		mLineColorA.SetCurveFromArray(_list,_type);
		_list.Clear();
		_list.Append(Math::float2(0,0.5));
		mLineColorB.SetCurveFromArray(_list,_type);
		mLineColorG.SetCurveFromArray(_list,_type);
		mLineColorR.SetCurveFromArray(_list,_type);
	}
	//------------------------------------------------------------------------
	ParticleTrailTarget::~ParticleTrailTarget()
	{

	}
	//-------------------------------------------------------------------------
	ParticleTarget::TargetType ParticleTrailTarget::GetTargetType(void) const
	{
		return ParticleTarget::Trail;
	}

	//-------------------------------------------------------------------------
	bool ParticleTrailTarget::_preparePrimitiveGroup(SizeT& verticesSizeInByte, SizeT& indicesSizeInByte)
	{
		if ( !mNeedPrimitive )
			return false;

		SizeT Quota = ConstDefine::DEFAULT_TECHNIQUE_QUOTA;
		if ( mParentSystem )
		{
			Quota = mParentSystem->GetParticleQuota();
		}

		SizeT maxElements = (mMaxElements >= 2 ? mMaxElements: 2);

		SizeT vertexCount = Quota * IndexCountParticipate * VertexCountPerParticle * maxElements;

		if ( vertexCount <= 0 )
		{
			return false;
		}
		SizeT indexCount = Quota * IndexCountParticipate * IndexCountPerParticle * maxElements;	

		CheckPrimitive(vertexCount, indexCount, verticesSizeInByte, indicesSizeInByte);

		return true;
	}
	//------------------------------------------------------------------------
	void ParticleTrailTarget::_updateTarget(GPtr<ParticlePool>& pool, Timing::Time frameTime)
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

		if ( !pool.isvalid() )
			return;

		n_assert(mPrimitiveHandle.IsValid());

		Graphic::DynamicBuffer dvb;
		Graphic::DynamicBuffer dib;
		dvb.SetSize(verticesSizeInByte);
		dib.SetSize(indicesSizeInByte);
		ParticleVertexData* particleVertex = dvb.GetBufferPtr<ParticleVertexData>();
		ushort* indicies = dib.GetBufferPtr<ushort>();
		n_assert( particleVertex && indicies );
		n_assert( particleVertex && indicies );

		SizeT numVert = 0;


		const Math::matrix44* camera = &(ConstDefine::MATRIX_IDENTITY);
		if ( mParentSystem && mParentSystem)
		{
			camera = &(mParentSystem->GetCameraMatrix());		
		}

		Trail_OP op;

		Math::float4 outscale,outtranslate;
		Math::quaternion outquaternion;
		Math::matrix44  usedscaleMatrix = mParentSystem->GetWorldMatrix();

		usedscaleMatrix.decompose(outscale, outquaternion, outtranslate);
		Math::float3 scaleVector(outscale.x(), outscale.y(), outscale.z() );
		op.parentScale = scaleVector;

		Math::float3 sysUp = Math::float3(0,1,0);
		op.sysytemUp = outquaternion * sysUp;

		numVert = _updateTarget_Trail(pool,particleVertex, indicies, op);


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
		ParticleTrailTarget::_updateParticle_Common( Particle* particle, IndexT t, ParticleVertexData* particleVertex, ushort* indicies, IndexT vertIndex, float v0, float v1)
	{
		Math::scalar persent = (particle->mTotalTimeToLive - particle->mTimeToLive)/particle->mTotalTimeToLive;
		Math::scalar alphaAdd = 1.0f;
		if(persent > mAlphaLife)
		{
			persent -= mAlphaLife;
			alphaAdd = persent/(1.0f - mAlphaLife);
			alphaAdd = Math::n_clamp(alphaAdd,0.0f,1.0f);
			alphaAdd = 1.0f - alphaAdd;
		}

		Math::Color32 color1;
		Math::Color32 color2;
		color1.a = Math::n_scalartoByte(alphaAdd * mLineColorA.Calculate(v0));
		color1.r = Math::n_scalartoByte(mLineColorR.Calculate(v0));
		color1.g = Math::n_scalartoByte(mLineColorG.Calculate(v0));
		color1.b = Math::n_scalartoByte(mLineColorB.Calculate(v0));

		color2.a = Math::n_scalartoByte(alphaAdd * mLineColorA.Calculate(v1));
		color2.r = Math::n_scalartoByte(mLineColorR.Calculate(v1));
		color2.g = Math::n_scalartoByte(mLineColorG.Calculate(v1));
		color2.b = Math::n_scalartoByte(mLineColorB.Calculate(v1));


		particleVertex[0].mColor = color1.HexARGB();
		particleVertex[1].mColor = color2.HexARGB();
		particleVertex[2].mColor = color2.HexARGB();
		particleVertex[3].mColor = color1.HexARGB();

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
		ParticleTrailTarget::_updateTarget_Trail( GPtr<ParticlePool>& pool, ParticleVertexData* particleVertex, ushort* indicies, const T&  op )
	{
		n_assert( particleVertex && indicies);
		SizeT retNum = 0;
		Particle* particle = pool->GetFirst();

		SizeT maxElements = mMaxElements;
		if (mMaxElements <= 2)
		{
			maxElements = 2;
		}

		float perLength = (Math::scalar)(mTrailLength * 1.0f/maxElements);
		if (perLength <= 0)
		{
			return retNum;
		}
		Math::float4 SysPosition = mParentSystem->GetWorldMatrix().get_position();
		while ( particle )
		{
			particle->mPosition = Math::float3(SysPosition.x(),SysPosition.y(),SysPosition.z());
			if ( particle->mOrbitPositions.Size() < 2  )
			{
				particle->mOrbitPositions.Append(particle->mPosition);
			}
			else
			{
				while (particle->mOrbitPositions.Size() > maxElements + 1)
				{
					particle->mOrbitPositions.EraseIndex(0);
				}

				bool done = false;

				Math::float3 headPos;
				Math::float3 headNextElementPos;
				Math::float3 newPos;
				Math::float3 diff;
				Math::scalar curLength;

				while (!done)
				{
					headPos = particle->mOrbitPositions[ particle->mOrbitPositions.Size()-1];
					headNextElementPos = particle->mOrbitPositions[ particle->mOrbitPositions.Size()-2];
					newPos = particle->mPosition;
					diff = newPos - headNextElementPos;
					curLength = diff.length();

					if (curLength >= perLength)
					{

						Math::float3 scaledDiff = diff * perLength / curLength;
						particle->mOrbitPositions.Back() = headPos = headNextElementPos + scaledDiff;

						if (particle->mOrbitPositions.Size() >= maxElements + 1)
						{

							particle->mOrbitPositions.EraseIndex(0);
						}
						particle->mOrbitPositions.Append(newPos);

						diff = newPos - headPos;

						if ( diff.length() <= perLength )
						{
							done = true;
						}
					}
					else
					{

						particle->mOrbitPositions.Back() = particle->mPosition;
						done = true;
					}


					if ( particle->mOrbitPositions.Size() >= maxElements + 1 )
					{
						Math::float3 tailElemPos = particle->mOrbitPositions[0];
						Math::float3 preTailElemPos = particle->mOrbitPositions[1];
						Math::float3 taildiff = tailElemPos - preTailElemPos;
						float taillen= taildiff.length();

						if (taillen > 1e-06)
						{
							float tailsize = perLength - diff.length();

							taildiff *= tailsize / taillen;
							particle->mOrbitPositions.Front() = preTailElemPos + taildiff;
						}
					}
				} 
			}

			SizeT orbitSize = particle->mOrbitPositions.Size();

			Math::scalar persent = (particle->mTotalTimeToLive - particle->mTimeToLive)/particle->mTotalTimeToLive;
			Math::scalar rateScale = 0.0f;
			if(persent > mAmplitudeLife)
			{
				persent -= mAmplitudeLife;
				rateScale = persent/(1.0f - mAmplitudeLife);
				rateScale = Math::n_clamp(rateScale,0.0f,1.0f);
			}
			rateScale *= mAmplitude;

			Util::Array<Math::float3> tempPos;
			Math::scalar fStride = 1.0f /(Math::scalar)IndexCountParticipate;

			for(SizeT t=0;t<orbitSize-1;t++)
			{
				tempPos.Append(particle->mOrbitPositions[t]);
				Math::float3 pT2; 
				Math::float3 pT1;
				pT1 = particle->mOrbitPositions[t+1] - particle->mOrbitPositions[t];
				
				if(t + 2 < orbitSize)
					pT2 = particle->mOrbitPositions[t+2] - particle->mOrbitPositions[t+1];
				else
					pT2 = pT1;
				for(int i=1;i<IndexCountParticipate;i++)
				{
					Math::float3 pOut;
					Math::float3::hermite(&pOut,&particle->mOrbitPositions[t],&pT1,&particle->mOrbitPositions[t+1],&pT2,i*fStride);
					tempPos.Append(pOut);
				}
				
			}
			tempPos.Append(particle->mOrbitPositions[orbitSize-1]);

			orbitSize = tempPos.Size();
			Math::scalar totalLen = 0.0f;
			for(SizeT t=1;t<orbitSize;t++)
			{
				totalLen += (tempPos[t] - tempPos[t-1]).length();
			}
			float beginV = 0;
			float endV;
			for (SizeT t = 1; t < orbitSize; t++)
			{
				Math::float3 vPos = tempPos[t];
				Math::float3 vLastPos = tempPos[t-1];

				op(particle, vPos, vLastPos,  t, particleVertex, rateScale,mWaveLength*IndexCountParticipate);
				endV = beginV + (vPos - vLastPos).length() / totalLen;
				_updateParticle_Common(particle, t,  particleVertex, indicies, retNum, 1.0f - beginV , 1.0f - endV );

				beginV = endV;
				particleVertex += VertexCountPerParticle;
				indicies += IndexCountPerParticle;

				++retNum;
			}
			particle = pool->GetNext();
		}
		return retNum;
	}
	Math::MinMaxCurve* ParticleTrailTarget::getMinMaxCurve(ParticleCurveType pct)
	{
		switch(pct)
		{
		case	Target_TrailLineColorA:
			return &mLineColorA;
		case	Target_TrailLineColorB:
			return &mLineColorB;
		case	Target_TrailLineColorG:
			return &mLineColorG;
		case	Target_TrailLineColorR:
			return &mLineColorR;

		default:
			return Super::getMinMaxCurve(pct);					
		}
	}
}