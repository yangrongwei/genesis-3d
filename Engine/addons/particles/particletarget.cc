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
#include "particles/particlesystem.h"
#include "particles/particletarget.h"
#include "particles/particle.h"
#include "graphicsystem/GraphicSystem.h"
#include "graphicsystem/base/GraphicBufferData.h"
namespace Particles
{
	using namespace RenderBase;


	void _initVertexBufferData(Graphic::VertexBufferData2& vbd2, SizeT needCount)
	{
		Util::Array<RenderBase::VertexComponent>& verDeclare = vbd2.GetVertexComponents();
		verDeclare.Append( VertexComponent(VertexComponent::Position,0, VertexComponent::Float3) );
		verDeclare.Append( VertexComponent(VertexComponent::Normal,0, VertexComponent::Float3) );

		verDeclare.Append( VertexComponent(VertexComponent::Color,0, VertexComponent::ColorBGRA) );

		verDeclare.Append( VertexComponent(VertexComponent::TexCoord, 0, VertexComponent::Float2) );

		vbd2.Setup(needCount, sizeof(ParticleVertexData), RenderBase::BufferData::Dynamic, RenderBase::PrimitiveTopology::TriangleList, false);
	}
	void _initVertexBufferData(Graphic::IndexBufferData2& ibd2, SizeT needCount)
	{
		ibd2.Setup(needCount, RenderBase::BufferData::Dynamic, RenderBase::IndexBufferData::Int16, false);
	}

	__ImplementClass( Particles::ParticleTarget, 'PPTG', Core::RefCounted)
		//------------------------------------------------------------------------
		ParticleTarget::ParticleTarget()
		: mParentSystem(NULL)
		, mName("Target")
		, mIsActive(false)
		, mTexRowSize(1)
		, mTexColumnSize(1)
		, mPrimDirty(false)
		, mOrientType(OT_NONE)
		, mStretchScale(1.0f)
		, mNeedPrimitive(false)
		, mCurrVertexCount(0)
		, mCurrIndexCount(0)
		, mActiveVertexCount(0)
		, mActiveIndexCount(0)
	{
		generateUVFrames();
	}
	//------------------------------------------------------------------------
	ParticleTarget::~ParticleTarget()
	{

	}
	//------------------------------------------------------------------------
	ParticleTarget::TargetType ParticleTarget::GetTargetType(void) const
	{
		return Unknown;
	}
	//------------------------------------------------------------------------
	void 
		ParticleTarget::_onActivate(void)
	{
		n_assert( !mIsActive );
		mIsActive = true;
		mPrimDirty = true;
	}
	//------------------------------------------------------------------------
	void 
		ParticleTarget::_onDeactivate(void)
	{
		n_assert( mIsActive );
		mIsActive = false;
		if (mPrimitiveHandle.IsValid())
		{
			Graphic::GraphicSystem::Instance()->RemovePrimitive(mPrimitiveHandle);
			mPrimitiveHandle = RenderBase::PrimitiveHandle();
			restActiveElemCount();
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleTarget::_updateTarget(ParticlePoolPtr& pool, Timing::Time frameTime)
	{
		n_error("ParticleTarget::_updateTarget Should impl in devired class ");
		// empty
	}
	//------------------------------------------------------------------------
	void
		ParticleTarget::CheckPrimitive(SizeT vertexCount, SizeT indexCount, SizeT& verticesSizeInByte, SizeT& indicesSizeInByte)
	{

		verticesSizeInByte = vertexCount * sizeof( ParticleVertexData );
		indicesSizeInByte = indexCount * sizeof(ushort);
		bool rebuild = false;

		if (mCurrVertexCount != vertexCount || mCurrIndexCount != indexCount)
		{
			mPrimDirty = true;
			rebuild = true;
		}
		if (rebuild)
		{
			Graphic::GraphicSystem::Instance()->RemovePrimitive(mPrimitiveHandle);

			Graphic::VertexBufferData2 vbd2;
			Graphic::IndexBufferData2 ibd2;
			_initVertexBufferData(vbd2, vertexCount);
			_initVertexBufferData(ibd2, indexCount);
			mCurrVertexCount = vertexCount;
			mCurrIndexCount = indexCount;
			mPrimitiveHandle = Graphic::GraphicSystem::Instance()->CreatePrimitiveHandle(&vbd2, &ibd2);
		}
	}
	//------------------------------------------------------------------------
	void 
		ParticleTarget::generateUVFrames(void)
	{
		n_assert( mTexRowSize >= 1 );
		n_assert( mTexColumnSize >= 1);

		SizeT numUVFrames = (mTexRowSize * mTexColumnSize);

		float animUScale = 1.0f / mTexRowSize;
		float animVScale = 1.0f / mTexColumnSize;

		if( numUVFrames == 1 )
		{
			mUVTexCoords.Clear();
		}
		else
		{
			if ( mUVTexCoords.Size() < numUVFrames )
			{
				mUVTexCoords.Reserve( numUVFrames - mUVTexCoords.Size() );
			}
			mUVTexCoords.Resize(numUVFrames, UVRect() );

			for( IndexT index=0;index < numUVFrames; ++index )
			{
				IndexT vIdx = index / mTexRowSize;
				IndexT uIdx = index - vIdx * mTexRowSize;	

				Math::scalar uOffset = (Math::scalar)uIdx * animUScale;
				Math::scalar vOffset = (Math::scalar)vIdx * animVScale;

				mUVTexCoords[index].x = uOffset;
				mUVTexCoords[index].y = vOffset;
				mUVTexCoords[index].width = animUScale;
				mUVTexCoords[index].height = animVScale;
			}
		}
	}
	//------------------------------------------------------------------------
	Math::bbox 
		ParticleTarget::computerBoundingBox( ParticleVertexData* particleVertex,  SizeT numVertex ) const
	{
		n_assert( particleVertex );
		Math::bbox bb;
		bb.begin_extend();
		for ( IndexT i = 0; i < numVertex; ++i)
		{	
			bb.extend( Math::point( particleVertex->mPosition.x(), 
				particleVertex->mPosition.y(),
				particleVertex->mPosition.z() ) );
			++particleVertex;
		}
		bb.end_extend();
		return bb;
	}
	//-----------------------------------------------------------------------------
	void ParticleTarget::_RotatorParticle(Particle* particle, ParticleVertexData* particleVertex)
	{
		Math::vector _axis(particleVertex->mNormal.x(),
			particleVertex->mNormal.y(),
			particleVertex->mNormal.z());
		Math::quaternion rq = Math::quaternion::rotationaxis( _axis , particle->mZRotation  );
		Math::matrix44 _mat = Math::matrix44::identity().rotationquaternion(rq);

		Math::float3 vPos = mParentSystem->IsMoveWorldCoord()?particle->mPosition :
			particle->mPosition.transformPoint(mParentSystem->GetWorldMatrix());

		SizeT n = 0;
		while (n<4)
		{
			Math::float3 tempos = particleVertex[n].mPosition - vPos;
			tempos = tempos.transformPoint(_mat);
			particleVertex[n].mPosition = tempos+vPos;
			n++;
		}		
	}
	void ParticleTarget::restActiveElemCount()
	{
		mPrimDirty = (mActiveIndexCount != 0);
		mActiveVertexCount = 0;
		mActiveIndexCount = 0;
		mCurrIndexCount = 0;
		mCurrVertexCount = 0;
	}
	//--------------------------------------------------------------------------------
	Math::MinMaxCurve*  ParticleTarget::getMinMaxCurve(ParticleCurveType pct)
	{
		return NULL;
	}
}