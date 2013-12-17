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
#include "particleModelEmitter.h"
#include "particles/particlesystem.h"
#include "particles/particleemitter.h"
#include "particles/particle.h"
#include "resource/meshres.h"

namespace Particles
{
	using namespace Math;

	__ImplementClass(Particles::ModelEmitter, Particles::CPFCC::EMITTER_MODEL, Particles::ParticleEmitter);

	//-----------------------------------------------------------------------
	ModelEmitter::ModelEmitter():ParticleEmitter()
		, mMeshName(NULL)
		, mMeshRes(NULL)
		, mEmitType(MMT_VERT)
	{
		mName = "ModelEmitter";
		SetMeshName("sys:box.mesh");
	}
	//--------------------------------------------------------------------------------
	ModelEmitter:: ~ModelEmitter()
	{
		mMeshRes = NULL;
		mVertList.Clear();
	}

	//--------------------------------------------------------------------------------
	void ModelEmitter::SetMeshName(const Util::String& name)
	{
		if (mParentSystem)
		{
			mParentSystem->SetLoadEmitterMesh(false);
		}
		mMeshName = name;
		mMeshRes = NULL;
		mVertList.Clear();
	}
	//--------------------------------------------------------------------------------
	void ModelEmitter::SetMeshRes(void* resource)
	{
		if (mParentSystem)
		{
			mParentSystem->SetLoadEmitterMesh(true);
		}
		mMeshRes = resource;
	}	
	//-----------------------------------------------------------------------
	void ModelEmitter::_initParticlePosition(Particle* particle)
	{
		if (!mMeshRes)
			return;

		if (mVertList.IsEmpty())
		{
			Resources::MeshRes* meshres = (Resources::MeshRes*)mMeshRes;

			const Resources::NormalData::value_type* normals = meshres->GetVertexData<Resources::NormalData>();
			const Resources::PositionData::value_type* verteies = meshres->GetVertexData<Resources::PositionData>();


			SizeT vertexCount = meshres->GetVertexCount() - 1;
			while ( vertexCount >= 0 )
			{
				ParticleVertexData pVert;
				pVert.mPosition = verteies[vertexCount];
				pVert.mNormal = normals[vertexCount];
				mVertList.Append(pVert);

				vertexCount--;
			}

		}

		switch(mEmitType)
		{
		case MMT_VERT:
			{
				SizeT rndIdx  = (SizeT)Math::n_rand(0.0f, (float)mVertList.Size());
				rndIdx = Math::n_min(rndIdx,mVertList.Size()-1);
				particle->mPosition = mVertList[rndIdx].mPosition;
				particle->mDirection = mVertList[rndIdx].mNormal;
			}
			break;
		case  MMT_EDGE:
			{
				SizeT rndIdx  = (SizeT)Math::n_rand(0.0f, (float)mVertList.Size()-2);		
				rndIdx = Math::n_min(rndIdx,mVertList.Size()-3);
				GetRandomEdge(&mVertList[rndIdx],  particle->mPosition, particle->mDirection);
			}
			break;
		case MMT_TRIANGLE:
			{
				SizeT rndIdx  = (SizeT)Math::n_rand(0.0f, (float)mVertList.Size()-2);     
				rndIdx = Math::n_min(rndIdx,mVertList.Size()-3);
				GetRandomTriangle(&mVertList[rndIdx],  particle->mPosition, particle->mDirection);
			}
			break;
		default:
			break;
		}
		particle->mDirection *= mNormalSpeed;
		if(mParentSystem->IsMoveWorldCoord())
		{
			particle->mPosition += mParentSystem->GetDerivedPosition();
			particle->mDirection = particle->mDirection.transformVector(mParentSystem->GetWorldMatrix());
		}
		particle->mOrbitPositions.Clear();
	}
	//-----------------------------------------------------------------------
	void ModelEmitter::_initParticleVelocity(Particle* particle)
	{
		if(!IsNormalDir() || EFT_BODY == mInitFromType)
		{
			Super::_initParticleVelocity(particle);
		}
	}
}
