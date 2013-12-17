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
#ifndef __PARTICLE_DECAL_TARGET_H__
#define __PARTICLE_DECAL_TARGET_H__
#include "particles/particle_fwd_decl.h"
#include "particles/particletarget.h"
#include "particles/particle.h"

namespace Particles
{
	class ParticleDecalTarget: public ParticleTarget
	{
		__DeclareSubClass(ParticleDecalTarget, ParticleTarget );

		//----------------------------------------------------------------------
	public:

		class Decal_OP
		{
		public:
			void operator()( 	
				Particle* particle, 
				const Math::float3& derivedPos,
				const Math::float3& lastDerivedPos,
				IndexT index,
				ParticleVertexData* particleVertex, 
				ushort* indicies) const
			{

				Math::float3 eyedir = cameraPos - derivedPos;
				eyedir.normalise();
				Math::float3 diffdir = derivedPos - lastDerivedPos ;
				diffdir.normalise();

				Math::float3 rightVector = eyedir.crossProduct( diffdir );
				rightVector.normalise();

				Math::float3 right = rightVector * particle->mSize.x() * 0.5;

				particleVertex[0].mNormal = eyedir;

				particleVertex[1].mPosition = derivedPos  - right;
				particleVertex[1].mNormal = eyedir;

				particleVertex[2].mPosition = derivedPos  + right;
				particleVertex[2].mNormal = eyedir;


				particleVertex[3].mNormal = eyedir;

				if (index > 1)		
				{
					ParticleVertexData* lastVertexIndex = particleVertex-4; 
					particleVertex[0].mPosition = lastVertexIndex[1].mPosition;
					particleVertex[3].mPosition = lastVertexIndex[2].mPosition;
				}
				else
				{
					particleVertex[0].mPosition = lastDerivedPos  - right;
					particleVertex[3].mPosition = lastDerivedPos   + right;
				}

			}		
			Math::float3 cameraPos;
		};	

	public:
		ParticleDecalTarget();
		virtual ~ParticleDecalTarget();

		ParticleTarget::TargetType GetTargetType(void) const;


		void _updateParticle_Common( Particle* particle, ParticleVertexData* particleVertex, ushort* indicies , IndexT particleIndex);

		SizeT _updateTarget_Decal(GPtr<ParticlePool>& pool, ParticleVertexData* particleVertex, ushort* indicies);

		Math::bbox ComputerDecalBoundingBox( GPtr<ParticlePool>& pool ) const;

		void _updateTarget(GPtr<ParticlePool>& pool, Timing::Time frameTime);

		bool _preparePrimitiveGroup(SizeT& verticesSizeInByte, SizeT& indicesSizeInByte);

		Math::matrix44 GetDecalRotation();
	protected:



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
}

#endif // __PARTICLE_RIBBONTRAIL_TARGET_H__
