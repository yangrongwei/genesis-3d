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

#ifndef __INSTANCE_MAP_H__
#define __INSTANCE_MAP_H__
#include "vegetation/vegetation_fwd_decl.h"
//#include "vegetation/VegetationObejct.h"
#include "rendersystem/base/PrimitiveGroup.h"
#include "resource/meshres.h"
#include "foundation/math/float3.h"
#include "foundation/math/quaternion.h"

namespace Vegetation
{		
	using namespace Resources;
	using namespace RenderBase;
	class VegetationObject;

	//matrix3x3
	static const SizeT g_nNumBatchInstance = 50;
	static const SizeT g_VertexCount = 4;
	static const SizeT g_IndexCount = 6;

	/// base vertex data
	struct VEGE_VERTEX
	{
		Math::float3	pos;	// Position of the vertex
		Math::float3	normal;	// Normal at this vertex
		Math::Color32	color;	//Color r,g,b,a
		Math::float2	uv;		// Texture coordinates u,v
	};

	/// vertex data with index
	struct VEGE_VERTEX_INSTANCE
	{
		Math::float3	pos;	// Position of the vertex
		Math::float3	normal;	// Normal at this vertex
		Math::Color32	color;	//Color r,g,b,a
		Math::float2	uv;		// Texture coordinates u,v
		Math::float2	index;	//Index for Shader, and wave
	};

	/// instance data
	struct  INSTANCEDATA_POS
	{
#ifdef __GENESIS_EDITOR__
		static uint		Index;
		uint			id;
#endif		
		Math::float3	pos;	
		//Math::scalar	scale;	//x - width ,y - height
		Math::float3	scale;
		Math::float3	rotate;	
		Math::scalar	color;	//Color r,g,b,a
		Math::scalar	wave;	// a time (float) for wave
		INSTANCEDATA_POS()
		{
#ifdef __GENESIS_EDITOR__
			id		=	Index++;
#endif
			pos		=	Math::float3(0,0,0);
			scale	=	Math::float3(1,1,1);
			rotate	=	Math::float3(0,0,0);
			color	=	0.0f;//Math::Color32(255,255,255,255);
			wave	=	1.0f;
		}

		inline INSTANCEDATA_POS& operator = ( const INSTANCEDATA_POS& data )
		{
#ifdef __GENESIS_EDITOR__
			id		=	data.id;
#endif
			pos		=	data.pos;
			scale	=	data.scale;
			rotate	=	data.rotate;
			color	=	data.color;
			wave	=	data.wave;

			return *this;
		}
	};

	struct VEGE_VERTEX_BUFFER
	{
		union
		{
			VEGE_VERTEX* vege_vert;
			VEGE_VERTEX_INSTANCE* vege_vert_inst;
		};
	};

	typedef Util::Array<VEGE_VERTEX_BUFFER> InstanceVertArray;
	typedef Util::Array<INSTANCEDATA_POS> InstancePosArray;
	//typedef Util::Dictionary<Util::, >

	/*! \class InstanceMap InstanceMap.h
	*  \brief  This is a class.
	*
	* base class, be  used to organize data for shader Instance
	*/
	class VegeInstanceMap: public Core::RefCounted, Serialization::ISerialize
	{
		__DeclareClass( VegeInstanceMap )

	public:

		VegeInstanceMap();
		virtual ~VegeInstanceMap();

		/// 
		const static GPtr<VegeInstanceMap> NullVegeInstMap;

		virtual void Update();

		virtual void UpdateInstData();

		VegetationObject* GetParentVegeObject(void) const;
		void SetParentVegeObject( VegetationObject* obj);

		void Active();
		void DeActive(void);
		bool IsActive(void) const;

		bool IsDirty(void)const;
		void SetDirty(bool);

		virtual bool BuildPrimitive();

		virtual void BuildVertexComponents(const GPtr<Resources::MeshRes>& meshres);

		virtual bool CreateInstanceVBuffer( GPtr<RenderBase::PrimitiveGroup>& );

	protected:
		void _FillInstanceVBuffer( GPtr<VertexBuffer>& pVBO );

	public:


		/// 
		void SetParentMatrix( const Math::matrix44& m  );

		//void SetName( const Util::String& name);
		//const Util::String& GetName(void) const; 

		/// Is using HardWare Instance type
		bool IsHWInstancing(void) const;
		/// Set HWINstancing
		void SetHWInstacing(bool);

		/// Get instanceCount which in array
		const SizeT GetVertLimitCount( void ) const;

		/// get the total count
		const SizeT GetInstanceCount( void ) const;

		/// add a instance to instanceMap
		void AddInstance(const INSTANCEDATA_POS& inst);

		/// get the struct data of instance
		INSTANCEDATA_POS* GetInstance( IndexT index );
		const INSTANCEDATA_POS& GetInstance( IndexT index ) const;

		/// replace an instance
		void ReplaceInstance(const INSTANCEDATA_POS& inst, IndexT index);

		/// remove a single instance
		void RemoveInstance(IndexT index);

		/// Perform initialisation actions
		virtual void _onActivate(void);

		/// Reverse initialisation actions
		virtual void _onDeactivate(void);

		void _calcAxisVec(ushort, Math::vector& );



	public:	//	Serialization
		// @ISerialization::GetVersion. when change storage, must add SerializeSVersion count
		virtual Serialization::SVersion GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Serialization::SVersion ver, Serialization::SerializeReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( Serialization::SerializeWriter* pWriter ) const;

		// copy 
		virtual void CopyFrom( const GPtr<VegeInstanceMap>& instmap );



	protected:
		InstancePosArray mInstances;

		VegetationObject* mVegeObject;
		bool mIsActive;

		Util::Array<RenderBase::VertexComponent> m_vVerDeclare;
		SizeT	m_nVertCount;
		SizeT	m_nIndicesCount;
		SizeT	m_nInstUsingCount;
		SizeT	m_nVertLimitCount;
		SizeT	m_nVertexDataSize;
		bool	m_bHWInstancing;
		bool	m_bInstDirty;



	};
	//--------------------------------------------------------------------------------
	inline bool VegeInstanceMap::IsHWInstancing(void) const
	{
		return m_bHWInstancing;
	}
	//--------------------------------------------------------------------------------
	inline void VegeInstanceMap::SetHWInstacing(bool bUseHWInst)
	{
		m_bHWInstancing = bUseHWInst;
	}
	//-----------------------------------------------------------------------
	inline const SizeT VegeInstanceMap::GetVertLimitCount( void ) const
	{
		return m_nVertLimitCount;
	}
	//------------------------------------------------------------------------
	inline const SizeT VegeInstanceMap::GetInstanceCount( void ) const
	{
		return mInstances.Size();
	}

	//-------------------------------------------------------------------------
	inline INSTANCEDATA_POS* VegeInstanceMap::GetInstance( IndexT index )
	{
		return &mInstances[index];
	}
	//--------------------------------------------------------------------------------
	inline const INSTANCEDATA_POS& VegeInstanceMap::GetInstance( IndexT index ) const
	{
		return mInstances[index];
	}
	//------------------------------------------------------------------------

	inline void VegeInstanceMap::ReplaceInstance(const INSTANCEDATA_POS& inst, IndexT index)
	{
		mInstances[index] = inst;
	}
	//------------------------------------------------------------------------

	inline void VegeInstanceMap::RemoveInstance(IndexT index)
	{
		//BaseVegeInstance& tInst= mInstances[index];
		if (mInstances.Size() > index && index >= 0)
		{
			mInstances.EraseIndex(index);
			SetDirty(true);
		}
	}
	//------------------------------------------------------------------------
	inline bool VegeInstanceMap::IsActive(void) const
	{
		return mIsActive;
	}
	//--------------------------------------------------------------------------------
	inline bool VegeInstanceMap::IsDirty(void)const
	{
		return m_bInstDirty;
	}
	//--------------------------------------------------------------------------------
	inline void VegeInstanceMap::SetDirty(bool bdirty)
	{
		m_bInstDirty = bdirty;
	}
	//------------------------------------------------------------------------
	inline VegetationObject* VegeInstanceMap::GetParentVegeObject(void) const
	{
		return mVegeObject;
	}
	//------------------------------------------------------------------------
	inline void VegeInstanceMap::SetParentVegeObject( VegetationObject* obj)
	{
		mVegeObject = obj;

	}
	//------------------------------------------------------------------------
	template<typename T, SizeT elemSize >
	void StripeCopyValue( const T* from, uchar* to, SizeT toElemsSize,  SizeT toStripe,  SizeT numToCopy )
	{
		n_assert( from && to );
		n_assert( toStripe >= 0 && numToCopy > 0 );
		n_static_assert( elemSize == sizeof(T) );

		to += toStripe;

		for( IndexT i = 0; i < numToCopy; ++i )
		{
			Memory::Copy( from, to, elemSize );
			to += toElemsSize;
		}
	}
	//------------------------------------------------------------------------
	template<typename T, SizeT elemSize >
	void StripeCopy( const T* from, uchar* to, SizeT toElemsSize,  SizeT toStripe,  SizeT numToCopy )
	{
		n_assert( from && to );
		n_assert( toStripe >= 0 && numToCopy > 0 );
		n_static_assert( elemSize == sizeof(T) );

		to += toStripe;

		for( IndexT i = 0; i < numToCopy; ++i )
		{
			Memory::Copy( from, to, elemSize );
			++from;
			to += toElemsSize;
		}
	}
	//------------------------------------------------------------------------
	template<typename T , SizeT elemSize >
	void StripeSwapCopyColor( const T* from, uchar* to, SizeT toElemsSize,  SizeT toStripe,  SizeT numToCopy )
	{
		n_assert( from && to );
		n_assert( toStripe >= 0 && numToCopy > 0 );
		n_static_assert( elemSize == sizeof(T) );	// color is 4 byte

		to += toStripe;

		for( IndexT i = 0; i < numToCopy; ++i )
		{
			*((int*)to) = ((Math::Color32*)from)->HexARGB();

			++from;
			to += toElemsSize;
		}
	}

}
#endif // __INSTANCE_MAP_H__