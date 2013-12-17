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
#ifndef __particletarget_H__
#define __particletarget_H__


#include "particles/particle_fwd_decl.h"
#include "rendersystem/base/PrimitiveGroup.h"
#include "foundation/util/scriptbind.h"
#include "particles/particle.h"

namespace Particles
{
	struct UVRect
	{
		UVRect() : x(0.0f), y(0.0f), width(0.0f), height(0.0f){
		}

		Math::scalar x; 
		Math::scalar y; 
		Math::scalar width;
		Math::scalar height; 
	};


	class ParticleTarget: public Core::RefCounted, Serialization::ISerialize
	{
		__DeclareClass( ParticleTarget )
			__ScriptBind

	public:
		//--------------------------------------------------------------------------------
		enum OrientType
		{
			OT_NONE = 0,
			OT_DIRECT = 1,

		};

		//------------------------------------------------------------------------
		class Beam_Camera_OP
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
				Math::float3 diffdir = derivedPos - lastDerivedPos;
				diffdir.normalise();

				Math::float3 rightVector =  eyedir.crossProduct( diffdir );
				rightVector.normalise();

				rightVector *= parentScale;

				Math::float3 right = rightVector * particle->mSize.x() * 0.5;

				particleVertex[0].mNormal = eyedir;

				particleVertex[1].mPosition = derivedPos - right;
				particleVertex[1].mNormal = eyedir;

				particleVertex[2].mPosition = derivedPos + right;
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
					particleVertex[3].mPosition = lastDerivedPos  + right;
				}

			}		
			Math::float3 cameraPos;
			Math::float3  parentScale;
		};	
		//------------------------------------------------------------------------
		//------------------------------------------------------------------------
		class Trail_OP
		{
		public:
			void operator()( 	
				Particle* particle, 
				const Math::float3& derivedPos,
				const Math::float3& lastDerivedPos,
				IndexT index,
				ParticleVertexData* particleVertex, 
				float amplate,
				float waveLength) const
			{

				Math::float3 diffdir = derivedPos - lastDerivedPos ;
				diffdir.normalise();

				Math::float3 rightVector =  sysytemUp.crossProduct( diffdir );
				rightVector.normalise();

				rightVector *= parentScale;
				Math::float3 right = rightVector * particle->mSize.x() * 0.5;

				particleVertex[0].mNormal = sysytemUp;

				particleVertex[1].mPosition = derivedPos - right;
				particleVertex[1].mNormal = sysytemUp;

				particleVertex[2].mPosition = derivedPos  + right;
				particleVertex[2].mNormal = sysytemUp;


				particleVertex[3].mNormal = sysytemUp;

				Math::scalar x = 6.28f * index /  waveLength;
				Math::scalar upWave = amplate * x * Math::n_sin(x);
				particleVertex[1].mPosition += sysytemUp*upWave;
				particleVertex[2].mPosition += sysytemUp*upWave;

				if (index > 1)		
				{
					ParticleVertexData* lastVertexIndex = particleVertex-4; 
					particleVertex[0].mPosition = lastVertexIndex[1].mPosition;
					particleVertex[3].mPosition = lastVertexIndex[2].mPosition;
				}
				else
				{
					particleVertex[0].mPosition = lastDerivedPos - right;
					particleVertex[3].mPosition = lastDerivedPos + right;
				}

			}		
			Math::float3 sysytemUp;
			Math::float3  parentScale;
		};	
		//------------------------------------------------------------------------
		class Camera_OP
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

				particleVertex[0].mPosition = derivedPos + up - right;
				particleVertex[0].mNormal = dir;

				particleVertex[1].mPosition = derivedPos - up - right;
				particleVertex[1].mNormal = dir;

				particleVertex[2].mPosition = derivedPos - up + right;
				particleVertex[2].mNormal = dir;

				particleVertex[3].mPosition = derivedPos + up + right;
				particleVertex[3].mNormal = dir;
			}
			OrientType   ot;
			Math::scalar	upStretch;
			Math::float3 upVector;
			Math::float3 cameraPos;
			Math::float3 parentScale;
		};
		//--------------------------------------------------------------------------------
		class BillBoard_XZ_OP
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

				particleVertex[0].mPosition = derivedPos - xOff + zOff;
				particleVertex[0].mNormal.set(0.0, -1.0, 0.0);

				particleVertex[1].mPosition = derivedPos - xOff - zOff;
				particleVertex[1].mNormal.set(0.0, -1.0, 0.0);

				particleVertex[2].mPosition = derivedPos + xOff - zOff;
				particleVertex[2].mNormal.set(0.0, -1.0, 0.0);

				particleVertex[3].mPosition = derivedPos + xOff + zOff;
				particleVertex[3].mNormal.set(0.0, -1.0, 0.0);

			}

			OrientType   ot;
			Math::scalar	stretch;
			Math::quaternion  parentQuaternion;
		};
		//--------------------------------------------------------------------------------



	public:
		ParticleTarget();
		virtual ~ParticleTarget();

		ParticleSystem* GetParentSystem(void) const;
		void SetParentSystem( ParticleSystem* technique);

		void SetDirtyPrim(bool);
		bool IsDirtyPrim(void) const;

		bool IsActive(void) const;

		enum TargetType
		{
			Unknown,
			BillBoard,
			Beam,
			Box,
			Sphere,
			RibbonTrail,
			Decal,
			Trail,
			Mesh,
			HorizontalPlane,
		};
		virtual TargetType GetTargetType(void) const;

		void SetNeedPrimitive(bool need);

		bool GetNeedPrimitive() const;

		RenderBase::PrimitiveHandle GetPrimitiveHandle() const;

		void CheckPrimitive(SizeT vertexCount, SizeT indexCount, SizeT& verticesSizeInByte, SizeT& indicesSizeInByte);

		//---------------------Property---------------------------------------------------

		void SetName( const Util::String& name);
		const Util::String& GetName(void) const; 

		void SetTexCoordSize(SizeT row, SizeT column);
		void SetTexCoordRowSize(SizeT row);
		void SetTexcoordColumnSize(SizeT column);
		SizeT GetTexCoordRowSize(void) const;
		SizeT GetTexCoordColumnSize(void) const;

		///@
		void SetOrientType(OrientType t);
		OrientType GetOrientType(void) const;

		///
		void SetStretchScale(float _scale);
		float GetStretchScale(void) const;

		SizeT GetActiveVertexCount() const;
		SizeT GetActiveIndexCount() const;

		//-----------------------Internal Loop-------------------------------------------------

		virtual void _onActivate(void);

		virtual void _onDeactivate(void);

		virtual void _updateTarget( ParticlePoolPtr& pool, Timing::Time frameTime);

		/**
		*/
		virtual void _RotatorParticle(Particle* particle, ParticleVertexData* particleVertex);
		virtual Math::MinMaxCurve* getMinMaxCurve(ParticleCurveType pct);

	protected:
		void restActiveElemCount();
		void generateUVFrames(void);
		const UVRect* getUVRect(IndexT texCoordIndex) const ;

		Math::bbox computerBoundingBox( ParticleVertexData* particleVertex,  SizeT numVertex ) const;

	protected:
		ParticleSystem* mParentSystem;
		bool mIsActive;

		Util::String mName;
		SizeT mActiveVertexCount;
		SizeT mActiveIndexCount;
		SizeT mCurrVertexCount;
		SizeT mCurrIndexCount;
		SizeT mTexRowSize;
		SizeT mTexColumnSize;
		Util::Array<UVRect> mUVTexCoords;	
		OrientType		mOrientType;
		float					mStretchScale;

		RenderBase::PrimitiveHandle mPrimitiveHandle;
		bool	mPrimDirty;
		bool mNeedPrimitive;


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

	//--------------------------------------------------------------------------------
	inline void ParticleTarget::SetDirtyPrim(bool bset)
	{
		mPrimDirty = bset;
	}
	//--------------------------------------------------------------------------------
	inline bool ParticleTarget::IsDirtyPrim(void) const
	{
		return mPrimDirty; 
	}
	//------------------------------------------------------------------------
	inline
		ParticleSystem* 
		ParticleTarget::GetParentSystem(void) const
	{
		return mParentSystem;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleTarget::SetParentSystem( ParticleSystem* technique)
	{
		mParentSystem = technique;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		ParticleTarget::IsActive(void) const
	{
		return mIsActive;
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleTarget::SetTexCoordSize(SizeT row, SizeT column)
	{
		mTexRowSize = row;
		mTexColumnSize = column;
		if ( mTexRowSize < 1 )
		{
			mTexRowSize = 1;
		}
		if ( mTexColumnSize < 1 )
		{
			mTexColumnSize = 1;
		}
		generateUVFrames();
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleTarget::SetTexCoordRowSize(SizeT row)
	{
		mTexRowSize = row;
		if ( mTexRowSize < 1 )
		{
			mTexRowSize = 1;
		}
		generateUVFrames();
	}
	//------------------------------------------------------------------------
	inline
		void 
		ParticleTarget::SetTexcoordColumnSize(SizeT column)
	{
		mTexColumnSize = column;
		if ( mTexColumnSize < 1 )
		{
			mTexColumnSize = 1;
		}
		generateUVFrames();
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		ParticleTarget::GetTexCoordRowSize(void) const
	{
		return mTexRowSize;
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		ParticleTarget::GetTexCoordColumnSize(void) const
	{
		return mTexColumnSize;
	}	
	//------------------------------------------------------------------------
	inline
		void 
		ParticleTarget::SetName( const Util::String& name)
	{
		if ( name.IsEmpty() )
		{
			return;
		}
		mName = name;
	}
	//------------------------------------------------------------------------
	inline
		const Util::String& 
		ParticleTarget::GetName(void) const
	{
		return mName;
	}
	//------------------------------------------------------------------------
	inline
		const UVRect*
		ParticleTarget::getUVRect(IndexT texCoordIndex) const
	{
		n_assert( texCoordIndex >= 0 );
		if ( mUVTexCoords.IsEmpty() )
		{
			return NULL;
		}
		return &( mUVTexCoords[ texCoordIndex % mUVTexCoords.Size() ] );
	}
	//------------------------------------------------------------------------
	inline void ParticleTarget::SetOrientType(ParticleTarget::OrientType t)
	{
		mOrientType = t;
	}
	//-------------------------------------------------------------------------
	inline ParticleTarget::OrientType 
		ParticleTarget::GetOrientType(void) const
	{
		return mOrientType;
	}
	//--------------------------------------------------------------------------------
	inline void ParticleTarget::SetStretchScale(float _scale)
	{
		mStretchScale = _scale;
	}
	//--------------------------------------------------------------------------------
	inline float ParticleTarget::GetStretchScale(void) const
	{
		return mStretchScale;
	}

	inline void ParticleTarget::SetNeedPrimitive(bool need)
	{
		mNeedPrimitive = need;
	}

	inline bool ParticleTarget::GetNeedPrimitive() const
	{
		return mNeedPrimitive;
	}

	inline RenderBase::PrimitiveHandle ParticleTarget::GetPrimitiveHandle() const
	{
		return mPrimitiveHandle;
	}

	inline SizeT ParticleTarget::GetActiveVertexCount() const
	{
		return mActiveVertexCount;
	}

	inline SizeT ParticleTarget::GetActiveIndexCount() const
	{
		return mActiveIndexCount;
	}
}







#endif // __particletarget_H__
