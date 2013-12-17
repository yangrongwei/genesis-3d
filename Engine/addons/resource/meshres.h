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
#ifndef __meshres_H__
#define __meshres_H__
#include "resource/resource.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "util/array.h"
#include "math/float2.h"
#include "math/float3.h"
#include "math/float4.h"
#include "math/color.h"
#include "math/bbox.h"

#include <deque>

namespace Resources
{

	struct SubMesh
	{
		SubMesh()
			: firstVertex(0) , numVertex(0), FirstIndex(0), numIndex(0)
		{
		}
		IndexT firstVertex;
		SizeT numVertex;
		IndexT FirstIndex;
		SizeT numIndex;
		Math::bbox box;
	};

	struct BoneInfo
	{
		BoneInfo()
		{
			boneIndex[0] = 0;   boneIndex[1] = 0; boneIndex[2] = 0; boneIndex[3] = 0;
			boneWeight[0] = 0.0; boneWeight[1] = 0.0; boneWeight[2] = 0.0; boneWeight[3] = 0.0;
		}
		ushort boneIndex[4];
		float boneWeight[4];
	};

	typedef Util::Array<Math::float2>  Vec2fArray;
	typedef Util::Array<Math::float3>  Vec3fArray;
	typedef Util::Array<Math::float4>  Vec4fArray;
	typedef Util::Array<ushort>        UShortArray;
	typedef Util::Array<uint>          UIntArray;
	typedef Util::Array<Math::Color32> ColorArray;
	typedef Util::Array<BoneInfo>      BoneInfoArray;
	typedef Util::Array<SubMesh>       SubMeshArray;
	typedef Util::Array< Util::Array<uchar> > AffectedBonesIndex;

	// 定义顶点组件。 顶点组件的元素数量或者和Positon的元素数量相等，或者为空
	class VertexIndex
	{
	public:
		enum code
		{
			egPosition = 0,	
			egColor,
			egTexCoord,
			egNormal,
			egTangent,
			egBiNormal,
			egBoneInfo,
		};
	};

	template<class _TContainer, int _TIndex>
	class VertexData: public _TContainer
	{
	public:
		enum 
		{
			_index = _TIndex,
		};
		typedef _TContainer Container;
		typedef typename Container::value_type Elem;
	};

	typedef VertexData<Vec3fArray,  VertexIndex::egPosition>    PositionData;
	typedef VertexData<ColorArray,  VertexIndex::egColor>       ColorData;
	typedef VertexData<Vec2fArray,  VertexIndex::egTexCoord>    TexCoordData;
	typedef VertexData<Vec3fArray,  VertexIndex::egNormal>      NormalData;
	typedef VertexData<Vec4fArray,  VertexIndex::egTangent>     TangentData;
	typedef VertexData<Vec4fArray,  VertexIndex::egBiNormal>    BiNormalData;
	typedef VertexData<BoneInfoArray,  VertexIndex::egBoneInfo> BoneInfoData;

	typedef UShortArray Index16Container;
	typedef UIntArray   Index32Container;

	//最大支持16个纹理坐标单元 [0,15]
	const SizeT MaxTexcoordUnitLimit = 15;

	class MeshRes: public Resource 
	{
		__DeclareSubClass(MeshRes,Resource);
		friend class MeshSpliter;
		friend class MeshReviseWorkspace;
	public:
		MeshRes();
		virtual ~MeshRes();

		/// 得到拓扑状态
		RenderBase::PrimitiveTopology::Code GetTopologyType() const;

		/// 设置拓扑状态
		void SetTopologyType( RenderBase::PrimitiveTopology::Code t );

		/// 得到包围盒大小
		const Math::bbox& GetBoundingBox() const;

		/// 设置包围盒大小
		void SetBoundingBox( const Math::bbox& b );

		/// slow。 需要在更新顶点信息后，手动调用。 includeSubMesh为true时，会重新计算当前的所有submesh的包围盒大小
		void RecalculateBounds( bool includeSubMesh = true );

		/// 重新计算index指向的submesh包围盒的大小。 slow。 需要在更新顶点信息或者submesh的索引数据后，手动调用
		void RecalculateSubMeshBounds( IndexT index );

		//// 得到顶点数量。顶点的组件（位置、颜色、法线等）如果有效，则组件中元素的数量一定和顶点数量相同
		SizeT GetVertexCount(void) const;

		/**
		* GetMaxTexUnitIndex  得到当前有效的纹理坐标的最大单元索引
		* @param: void  
		* @return: IndexT  -1表示无有效单元
		* @see: 
		* @remark:  从0到最大有效单元号之间的其他纹理单元，不一定是有效的
		*/
		IndexT GetMaxTexUnitIndex(void) const;

		/**
		* GetVertexData  得到顶点组件的数据指针
		* @param: IndexT unit  对顶点组件有多个单元的情况（比如纹理坐标），返回指定单元的数据
		* @return: const typename T::Elem*  如果组件有效，返回顶点组件第一个元素的指针供直接修改，指针指向的数组大小等于顶点数量；否则，返回NULL
		* @see: 
		* @remark:  use like: const PositionData::Elem* elem = pMesh->GetVertexData<PositionData>();   // PositionData::Elem* is Math::float3* 

		*/
		template< typename T>
		const typename T::Elem* GetVertexData(IndexT unit = 0 ) const;

		/**
		* GetVertexData  得到顶点组件的数据
		* @param: IndexT unit  对顶点组件有多个单元的情况（比如纹理坐标），返回指定单元的数据
		* @return: typename T::Elem*  如果组件有效，返回顶点组件第一个元素的指针，指针指向的数组大小等于顶点数量；否则，返回NULL
		* @see: 
		* @remark: !!!!!!!!!!!!可以直接修改指针指向的数据，外部应该保证数据内容的有效性，比如索引指向的顶点不能越界!!!!!!!!!!!!!!!!!
		use like: PositionData::Elem* elem = pMesh->GetVertexData<PositionData>();   // PositionData::Elem* is Math::float3* 
		*/
		template< typename T>
		typename T::Elem* GetVertexData(IndexT unit = 0 );

		/** 
		* SetVertexData  设置顶点组件的数据
		* @param: const typename T::Elem * v 指向输入数组的地址。NULL代表删除该顶点组件  
		* @param: SizeT elemCount  输入数组的大小。0代表删除该组件
		* @param: IndexT unit  对顶点组件有多个单元的情况（比如纹理坐标），指定要修改的单元索引。需小于该组件的最大单元限制，否则设置失败
		* @return: bool  是否设置成功
		* @see: 
		* @remark:  当传入数组指针非空时，除position为，其他组件应保证输入数组的大小和当前的顶点数量相同，否则设置失败。
		当设置position时，会自动修改其他组件的数据大小。当Position的数量减小时，会使得索引和submesh全部失效。
		use like: pMesh->SetVertexData<PositionData>(PositionData::Elem* elem , count );   // PositionData::Elem* is Math::float3* 

		*/
		template< typename T>
		bool SetVertexData( const typename T::Elem* v ,SizeT elemCount, IndexT unit = 0 );

		/// 是否使用16位的索引。 当16位索引有效时，优先使用16位索引。无论32位索引是否有效
		bool IsUseIndex16(void) const;

		/// 得到顶点数量
		SizeT GetIndexCount(void) const;

		/// 得到顶点流。无效返回NULL
		const Index16Container::value_type* GetIndex16(void) const;
		const Index32Container::value_type* GetIndex32(void) const;

		/// 得到顶点流。无效返回NULL。!!!!!!!!!!!!可以直接修改指针指向的数据，外部应该保证数据内容的有效性，否则可能会Crash!!!!!!!!!!!!!!!!!
		Index16Container::value_type* GetIndex16(void);
		Index32Container::value_type* GetIndex32(void);

		/**
		* SetIndex16  设置16位索引
		* @param: const Index16Container::value_type * v   为NULL，代表删除16位索引
		* @param: SizeT elemCount  
		* @return: bool  
		* @see: 
		* @remark:  		           
		当设置索引时，索引数据应在顶点数量范围内，否则，设置失败。
		当更改索引的16位或者32位类型时，原有的索引将会被清除。所有的submesh将会失效
		当索引数据被更改时，所有的submesh将会失效
		*/
		bool SetIndex16(const Index16Container::value_type* v, SizeT elemCount);

		/// see SetIndex16
		bool SetIndex32(const Index32Container::value_type* v, SizeT elemCount);

		/// 返回有效的submesh的数量
		SizeT GetSubMeshCount(void) const;

		//// 得到submesh
		const SubMesh* GetSubMesh(IndexT index ) const;

		/// 得到submesh，可用于修改。!!!!!!!!!!!!可以直接修改指针指向的数据，外部应该保证数据内容的有效性，否则可能会Crash!!!!!!!!!!!!!!!!!
		SubMesh* GetSubMesh(IndexT index);

		/// 得到每个submesh受到骨骼影响的索引集合
		const Util::Array<uchar>& GetAffectedBonesIndex(IndexT index) const;
		Util::Array<uchar>& GetAffectedBonesIndex(IndexT index);

		/**
		* SetSubMesh  设置submesh
		* @param: const SubMesh * submesh  为空时，删除对应索引的SubMesh
		* @param: IndexT index  当索引大于当前SubMesh的数量并且submesh的数据有效时，将会创建多份直到达到index指明的索引号
		* @return: bool 是否设置成功 
		* @see: 
		* @remark:  当submesh指向的数据和当前的顶点信息（数量，Index）不匹配时，设置失败
		不会自动计算SubMesh的包围盒，需要手动调用相关函数。
		当删除SubMesh时，会造成已有的索引失效。循环调用时注意!!!!!
		*/
		bool SetSubMesh(const SubMesh* submesh, IndexT index);

		void SetMeshID(const Util::String meshId);

		const Util::String GetMeshID();

		Util::Array<uint>& GetSubmeshUsedMaterial();

		/// 检查当前mesh中的数据是否有效。 slow
		bool Validate(void) const;

		// @Resource::CalculateRuntimeSize
		virtual SizeT CalculateRuntimeSize(void) const;

		static GPtr<MeshRes> EmptyMeshRes;
		static Util::Array<uchar> EmptyBonesIndex;
	protected:
		// @Resource::SwapLoadImpl
		virtual bool SwapLoadImpl( const GPtr<Resource>& tempRes);
		// @Resource::UnLoadImpl
		virtual void UnLoadImpl(void);

		const void* GetDataImpl( VertexIndex::code t, IndexT unit ) const;
		bool SetDataImpl( VertexIndex::code t, const void* v, SizeT elemCount, IndexT unit );

		bool ValidateSubMesh(const SubMesh* submesh ) const;
	protected:

		RenderBase::PrimitiveTopology::Code mTopologyType;
		Math::bbox mBox;

		Util::String meshId;

		PositionData mPosition;
		ColorData    mColor;
		Util::Array<TexCoordData> mTexCoords;
		NormalData    mNormal;
		TangentData   mTangent;
		BiNormalData  mBiNormal;
		BoneInfoData  mBoneInfo;

		Index16Container  mIndex16;
		Index32Container  mIndex32;

		SubMeshArray mSubMeshs;

		AffectedBonesIndex mAffectedBonesIndex;
		Util::Array<uint> mSummeshUsedMaterial;

		friend class MeshResLoader;
		friend class MeshResSaver;
	};
	//------------------------------------------------------------------------
	inline 
		RenderBase::PrimitiveTopology::Code 
		MeshRes::GetTopologyType() const
	{
		return mTopologyType;
	}
	//------------------------------------------------------------------------
	inline 
		void 
		MeshRes::SetTopologyType( RenderBase::PrimitiveTopology::Code t )
	{
		mTopologyType = t;
	}
	//------------------------------------------------------------------------
	inline 
		const Math::bbox& 
		MeshRes::GetBoundingBox() const
	{
		return mBox;
	}
	//------------------------------------------------------------------------
	inline 
		void 
		MeshRes::SetBoundingBox( const Math::bbox& b )
	{
		mBox = b;
	}
	//------------------------------------------------------------------------
	inline
		void 
		MeshRes::SetMeshID(const Util::String id)
	{
		meshId = id;
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		MeshRes::GetVertexCount(void) const
	{
		return mPosition.Size();
	}
	//------------------------------------------------------------------------
	inline
		IndexT 
		MeshRes::GetMaxTexUnitIndex(void) const
	{
		return mTexCoords.IsEmpty() ? InvalidIndex: ( mTexCoords.Size()-1 );

	}
	//------------------------------------------------------------------------
	template< typename T>
	inline
		const typename T::Elem* 
		MeshRes::GetVertexData(IndexT unit ) const
	{
		return (const typename T::Elem* )( GetDataImpl( (VertexIndex::code)(T::_index), unit ) );
	}
	//------------------------------------------------------------------------
	template< typename T>
	inline
		typename T::Elem* 
		MeshRes::GetVertexData(IndexT unit ) 
	{
		return (typename T::Elem* )( GetDataImpl( (VertexIndex::code)(T::_index), unit ) );
	}
	//------------------------------------------------------------------------
	template< typename T>
	inline
		bool 
		MeshRes::SetVertexData( const typename T::Elem* v ,SizeT elemCount, IndexT unit )
	{
		return SetDataImpl( (VertexIndex::code)(T::_index), v, elemCount, unit );
	}
	//------------------------------------------------------------------------
	/*  特化设置postion的实现
	*/
	template<>
	bool 
		MeshRes::SetVertexData<PositionData>( const PositionData::Elem* v ,SizeT elemCount, IndexT unit );
	//------------------------------------------------------------------------
	inline
		bool 
		MeshRes::IsUseIndex16(void) const
	{
		return ( !mIndex16.IsEmpty() ) ? true: ( mIndex32.IsEmpty() );
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		MeshRes::GetIndexCount(void) const
	{
		if ( !mIndex16.IsEmpty() )
		{
			return mIndex16.Size();
		}
		else
		{
			return mIndex32.Size();
		}
	}
	//------------------------------------------------------------------------
	inline 
		const Index16Container::value_type* 
		MeshRes::GetIndex16(void) const
	{
		return ( mIndex16.IsEmpty() ) ? NULL: ( &mIndex16[0] );
	}
	//------------------------------------------------------------------------
	inline
		const Index32Container::value_type* 
		MeshRes::GetIndex32(void) const
	{
		return ( mIndex32.IsEmpty() ) ? NULL: ( &mIndex32[0] );
	}
	//------------------------------------------------------------------------
	inline 
		Index16Container::value_type* 
		MeshRes::GetIndex16(void)
	{
		return ( mIndex16.IsEmpty() ) ? NULL: ( &mIndex16[0] );
	}
	//------------------------------------------------------------------------
	inline
		Index32Container::value_type* 
		MeshRes::GetIndex32(void)
	{
		return ( mIndex32.IsEmpty() ) ? NULL: ( &mIndex32[0] );
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		MeshRes::GetSubMeshCount(void) const
	{
		return mSubMeshs.Size();
	}
	//------------------------------------------------------------------------
	inline
		const SubMesh* 
		MeshRes::GetSubMesh(IndexT index ) const
	{
		if ( index >= 0 && index < mSubMeshs.Size() )
		{
			return &(mSubMeshs[index]);
		}
		else
		{
			return NULL;
		}
	}
	//------------------------------------------------------------------------
	inline
		SubMesh* 
		MeshRes::GetSubMesh(IndexT index)
	{
		if ( index >= 0 && index < mSubMeshs.Size() )
		{
			return &(mSubMeshs[index]);
		}
		else
		{
			return NULL;
		}
	}

	inline
		Util::Array<uchar>&
		MeshRes::GetAffectedBonesIndex(IndexT index) 
	{
		if (index >=0 && index < mAffectedBonesIndex.Size())
		{
			return mAffectedBonesIndex[index];
		}
		else
		{
			n_assert("AffectedBonesIndex: Out of bound");
			return EmptyBonesIndex;
		}

	}
	//------------------------------------------------------------------------
	inline
		const Util::Array<uchar>&
		MeshRes::GetAffectedBonesIndex(IndexT index) const
	{
		const Util::Array<uchar>& tmp = GetAffectedBonesIndex(index);
		return tmp;		
	}


	//--------------------------------------------------------------------------
	inline
		const Util::String 
		MeshRes::GetMeshID()
	{
		return meshId;
	}
	//-------------------------------------------------------------------------
	inline
		Util::Array<uint>& MeshRes::GetSubmeshUsedMaterial()
	{
		return mSummeshUsedMaterial;
	}

}






#endif // __meshres_H__
