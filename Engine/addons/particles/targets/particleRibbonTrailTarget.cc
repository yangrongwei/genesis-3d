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
#include "particleRibbonTrailTarget.h"
#include "particles/particlesystem.h"
#include "particles/particletarget.h"
#include "graphicsystem/GraphicSystem.h"
#include "particles/particlepool.h"

namespace Particles
{
	using namespace RenderBase;

	__ImplementClass(Particles::RibbonTrailTarget, CPFCC::TARGET_RIBBONTRAIL, Particles::ParticleTarget );

	// Constants
	const SizeT DEFAULT_MAX_ELEMENTS = 10;
	const SizeT VertexCountPerParticle = 4;
	const SizeT IndexCountPerParticle = 6;
	const SizeT MAXPARTICLESANDELE = 10000;

	//------------------------------------------------------------------------
	RibbonTrailTarget::RibbonTrailTarget():ParticleTarget()
		, mMaxElements(DEFAULT_MAX_ELEMENTS)
		, mColorChange(Math::float4())
		, mUpdateInternal(0.01f)
		, mTimeSpace(0)
		, mTrailLength(10.0f)
		, mPerLength(1)
		, m_ColorGraded(true)
		, mCurQuato(ConstDefine::DEFAULT_TECHNIQUE_QUOTA)
	{		

	}
	//------------------------------------------------------------------------
	RibbonTrailTarget::~RibbonTrailTarget()
	{

	}
	//-------------------------------------------------------------------------
	ParticleTarget::TargetType RibbonTrailTarget::GetTargetType(void) const
	{
		return ParticleTarget::RibbonTrail;
	}
	//-------------------------------------------------------------------------
	bool RibbonTrailTarget::_preparePrimitiveGroup(SizeT& verticesSizeInByte, SizeT& indicesSizeInByte)
	{
		if ( !mNeedPrimitive )
			return false;

		mCurQuato = ConstDefine::DEFAULT_TECHNIQUE_QUOTA;
		if ( mParentSystem )
		{
			mCurQuato = mParentSystem->GetParticleQuota();
		}
		SizeT maxElements = (mMaxElements >= 2 ? mMaxElements: 2);

		if(mCurQuato * mMaxElements > MAXPARTICLESANDELE)
		{
			mCurQuato = MAXPARTICLESANDELE/mMaxElements;
		}
		SizeT vertexCount = mCurQuato * VertexCountPerParticle * maxElements;

		if ( vertexCount <= 0 )
		{
			return false;
		}
		SizeT indexCount = mCurQuato * IndexCountPerParticle * maxElements;	

		CheckPrimitive(vertexCount, indexCount, verticesSizeInByte, indicesSizeInByte);

		return true;
	}

	//------------------------------------------------------------------------
	void RibbonTrailTarget::_updateTarget(GPtr<ParticlePool>& pool, Timing::Time frameTime)
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
		RibbonTrailTarget::_updateParticle_Common( Particle* particle, IndexT t, ParticleVertexData* particleVertex, ushort* indicies, IndexT vertIndex, float v0, float v1)
	{
		{
			Math::Color32 tColor = particle->mColor;

			particleVertex[0].mColor = tColor.HexARGB();
			particleVertex[1].mColor = tColor.HexARGB();
			particleVertex[2].mColor = tColor.HexARGB();
			particleVertex[3].mColor = tColor.HexARGB();
		}
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
			particleVertex[0].mTexCoord.set(  0.0, v0 );
			particleVertex[1].mTexCoord.set(  0.0, v1 );
			particleVertex[2].mTexCoord.set(  1.0, v1 );
			particleVertex[3].mTexCoord.set(  1.0, v0 );
		}

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
		RibbonTrailTarget::_updateTarget_Trail( GPtr<ParticlePool>& pool, ParticleVertexData* particleVertex, ushort* indicies, const T&  op )
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
		IndexT parCount = 0;
		while ( particle )
		{
			parCount ++;
			if(parCount > mCurQuato)
				break;
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

			float toatalLength = 0;
			float lastVCoord = 0.0;

			for (SizeT t = 1; t < orbitSize; t++)
			{
				Math::float3 vPos = particle->mOrbitPositions[t];
				Math::float3 vLastPos = particle->mOrbitPositions[t-1];

				toatalLength += (vPos - vLastPos).length();
			}

			for (SizeT t = 1; t < orbitSize; t++)
			{
				Math::float3 vPos = particle->mOrbitPositions[t];
				Math::float3 vLastPos = particle->mOrbitPositions[t-1];
				if ( !mParentSystem->IsMoveWorldCoord())				
				{
					vPos =vPos.transformPoint(mParentSystem->GetWorldMatrix());
					vLastPos= vLastPos.transformPoint(mParentSystem->GetWorldMatrix());

				}

				op(particle, vPos, vLastPos,  t, particleVertex, indicies);

				float deltaV = (vPos - vLastPos).length() / toatalLength;
				float beginV = lastVCoord;
				float endV = beginV + deltaV;

				lastVCoord = endV;

				beginV = 1.0f - beginV;
				endV = 1.0f - endV;


				_updateParticle_Common(particle, t,  particleVertex, indicies, retNum, beginV , endV );

				particleVertex += VertexCountPerParticle;
				indicies += IndexCountPerParticle;

				++retNum;
			}
			particle = pool->GetNext();
		}
		return retNum;
	}

}