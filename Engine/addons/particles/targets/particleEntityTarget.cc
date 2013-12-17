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
#include "particleEntityTarget.h"
#include "particles/particlesystem.h"
#include "resource/resourceserver.h"
#include "Material/GlobalShaderParam.h"
#include "particles/particlepool.h"

namespace Particles
{
	using namespace RenderBase;
	using namespace Resources;
	using namespace Graphic;

	__ImplementClass(Particles::ParticleEntityTarget, CPFCC::TARGET_ENTITY, Particles::ParticleTarget );


	//------------------------------------------------------------------------
	ParticleEntityTarget::ParticleEntityTarget():ParticleTarget()
	{		
	}
	//------------------------------------------------------------------------
	ParticleEntityTarget::~ParticleEntityTarget()
	{

	}
	//------------------------------------------------------------------------
	ParticleTarget::TargetType ParticleEntityTarget::GetTargetType(void) const
	{
		return ParticleTarget::Mesh;
	}
	//------------------------------------------------------------------------
	void ParticleEntityTarget::_updateTarget(ParticlePoolPtr& pool, Timing::Time frameTime)
	{
		n_assert(pool.isvalid());
		if (pool->IsEmpty())
		{
			restActiveElemCount();
			mMats.Clear();
			mParticlesColor.Clear();
			return;
		}

		mMats.Clear();
		mParticlesColor.Clear();

		Particle* particle = pool->GetFirst();
		Math::scalar parsysTransp = (Math::scalar)(mParentSystem->GetTransparency())/255.0f;

		while ( particle )
		{	
			Math::float4 _scale(particle->mSize.x() ,
				particle->mSize.y() ,
				particle->mSize.z(),
				0);	
			Math::quaternion parentQuaternion = mParentSystem->GetDerivedRotation();
			Math::float3 _axis(0,0,1);
			_axis =  parentQuaternion * _axis;

			Math::quaternion _rq = Math::quaternion::rotationaxis( Math::float4(_axis.x(),_axis.y(),_axis.z(),1.0f) , particle->mZRotation  );
			Math::quaternion finalQ = Math::quaternion::multiply(_rq, particle->mOrientation ) ;

			Math::float3 vPos = particle->mPosition;
			if ( mParentSystem->IsMoveWorldCoord() )
			{
				vPos =vPos.transformPoint(Math::matrix44::inverse(mParentSystem->GetWorldMatrix()));
			}
			Math::float4 _pos(vPos.x(),vPos.y(),vPos.z(),0);

			Math::matrix44 _mat = Math::matrix44::transformation(_scale, finalQ, _pos);			

			_mat = Math::matrix44::multiply(mParentSystem->GetWorldMatrix(), _mat);
			mMats.Append(_mat);

			Math::float4 _color((Math::scalar)particle->mColor.r/255.0f, 
				(Math::scalar)particle->mColor.g/255.0f, 
				(Math::scalar)particle->mColor.b/255.0f,
				(Math::scalar)(particle->mColor.a * parsysTransp) /255.0f );
			mParticlesColor.Append(_color);

			particle = pool->GetNext();
		}
		Math::bbox bb;
		_calculateBBox(bb,GetMatrixList());
		const Math::matrix44& worldMat = mParentSystem->GetWorldMatrix();
		Math::matrix44 invMat = Math::matrix44::inverse(worldMat);
		bb.transform(invMat);
		mParentSystem->SetLocalBoundingBox( bb);
	}
	//------------------------------------------------------------------------
	void ParticleEntityTarget::_calculateBBox(Math::bbox& box,const Util::Array<Math::matrix44>& matlist) 
	{
		SizeT PosIndex = 0;
		box.begin_extend();
		while (PosIndex < matlist.Size())
		{
			Math::float4 curPos = matlist[PosIndex].get_position();
			box.extend(curPos);
			PosIndex++;
		}
		box.end_extend();
	}
}