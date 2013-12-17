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
#include "resource/resource_stdneb.h"
#include "resource/meshres.h"


namespace Resources
{
	__ImplementClass(Resources::MeshRes, 'MSHR', Resources::Resource);
	GPtr<MeshRes> MeshRes::EmptyMeshRes;
	Util::Array<uchar> MeshRes::EmptyBonesIndex;
	//------------------------------------------------------------------------
	MeshRes::MeshRes()
		: mTopologyType(RenderBase::PrimitiveTopology::InvalidPrimitiveTopology)
	{

	}
	//------------------------------------------------------------------------
	MeshRes::~MeshRes()
	{

	}
	//------------------------------------------------------------------------
	template <typename T>
	const typename T::Elem* 
		_GetDataImpl(const T& t)
	{
		return t.IsEmpty() ? NULL : &(t[0]); 
	}
	//------------------------------------------------------------------------
	template <typename T>
	const typename T::value_type::Elem* 
		_GetDataImpl(const T& t, IndexT unit )
	{
		if ( unit >= 0 && unit < t.Size() )
		{
			return _GetDataImpl( t[unit] );
		}
		else
		{
			return NULL;
		}
	}
	//------------------------------------------------------------------------
	const void* 
		MeshRes::GetDataImpl( VertexIndex::code t, IndexT unit ) const
	{
		switch ( t )
		{
		case VertexIndex::egPosition:
			return _GetDataImpl(mPosition);
		case VertexIndex::egColor:
			return _GetDataImpl(mColor);
		case VertexIndex::egTexCoord:
			return _GetDataImpl(mTexCoords, unit);
		case  VertexIndex::egNormal:
			return _GetDataImpl(mNormal);
		case  VertexIndex::egTangent:
			return _GetDataImpl(mTangent);
		case  VertexIndex::egBiNormal:
			return _GetDataImpl(mBiNormal);
		case  VertexIndex::egBoneInfo:
			return _GetDataImpl(mBoneInfo);
		default: 
			return NULL;
		}
	}
	//------------------------------------------------------------------------
	template <typename T>
	bool _SetDataImpl(T& t, const void* _v, SizeT elemCount, SizeT vertexCount )
	{
		const typename T::Elem* v = (const typename T::Elem*)_v;
		if (elemCount <= 0 || !v)
		{
			t.Clear();
			return true;
		}

		if ( elemCount != vertexCount )
		{
			n_warning("Mesh data %d is out of bounds. The input array needs to be the same size as the position array.\n", T::_index);
			return false;
		}
		t.Assign(v, v+ elemCount );

		return true;
	}
	//------------------------------------------------------------------------
	template <typename T>
	bool _SetDataImpl(T& t, const void* _v, SizeT elemCount, SizeT vertexCount, IndexT unit , SizeT MaxUnitCount )
	{
		// Support up to 15 texture unit 
		if ( unit < 0 || unit > MaxUnitCount )
		{
			return false;
		}

		while( unit >= t.Size() )
		{
			t.Append( typename T::value_type() );
		}

		if ( _SetDataImpl( t[unit], _v, elemCount, vertexCount ) )
		{
			// when last unit is invalid, remove it
			while( t.Size() != 0 )
			{
				if ( t.Back().Size() == 0 )
				{
					t.EraseIndex( t.Size() - 1 );
				}
				else
				{
					break;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	//------------------------------------------------------------------------
	bool 
		MeshRes::SetDataImpl( VertexIndex::code t, const void* v, SizeT elemCount, IndexT unit )
	{
		SizeT vertexSize = GetVertexCount();
		switch ( t )
		{
		case VertexIndex::egColor:
			return _SetDataImpl(mColor, v, elemCount, vertexSize );
		case VertexIndex::egTexCoord:
			return _SetDataImpl(mTexCoords, v, elemCount, vertexSize, unit, MaxTexcoordUnitLimit );
		case  VertexIndex::egNormal:
			return _SetDataImpl(mNormal, v, elemCount, vertexSize );
		case  VertexIndex::egTangent:
			return _SetDataImpl(mTangent, v, elemCount, vertexSize );
		case  VertexIndex::egBiNormal:
			return _SetDataImpl(mBiNormal, v, elemCount, vertexSize );
		case  VertexIndex::egBoneInfo:
			return _SetDataImpl(mBoneInfo, v, elemCount, vertexSize );
		default: 
			return false;
		}
	}
	//------------------------------------------------------------------------
	template<typename T>
	void _ResizeData(T& t, SizeT elemCount, const typename T::value_type& v)
	{
		if ( !t.IsEmpty() )
		{
			t.Resize( elemCount, v );
		}
	}
	template<typename T>
	void _ResizeData(T& t, SizeT elemCount)
	{
		if ( !t.IsEmpty() )
		{
			t.Resize( elemCount, t.Back() );
		}
	}
	//------------------------------------------------------------------------
	template<>
	bool 
		MeshRes::SetVertexData<PositionData>( const PositionData::Elem* v ,SizeT elemCount, IndexT unit )
	{
		if ( elemCount != mPosition.Size() )
		{
			if ( elemCount < mPosition.Size() )
			{
				mIndex16.Clear();
				mIndex32.Clear();
				mSubMeshs.Clear();
			}
			else
			{
				_ResizeData(mIndex16, elemCount, 0 );
				_ResizeData(mIndex32, elemCount, 0 );
			}

			_ResizeData(mColor, elemCount, ColorData::Elem(0xFFFFFFFF) );
			for ( IndexT i = 0; i < mTexCoords.Size(); ++i )
			{
				_ResizeData(mTexCoords[i], elemCount, TexCoordData::Elem(0.0f,0.0f) );
			}
			_ResizeData(mNormal, elemCount);
			_ResizeData(mTangent, elemCount);
			_ResizeData(mBiNormal, elemCount);
			_ResizeData(mBoneInfo, elemCount);
		}

		mPosition.Assign( v, v+ elemCount );

		return true;
	}
	//------------------------------------------------------------------------
	template<typename T>
	bool ValidateIndex(const T* elem, SizeT count, SizeT MaxIndex )
	{
		if ( !elem || count <= 0 )
		{
			return true;
		}

		for ( IndexT index = 0; index < count; ++index )
		{
			if( elem[index] >= (T)MaxIndex )
			{
				return false;
			}
		}

		return true;
	}
	//------------------------------------------------------------------------
	bool 
		MeshRes::SetIndex16( const Index16Container::value_type* v, SizeT elemCount )
	{
		if ( v && elemCount > 0 )
		{
			if ( mPosition.Size() == 0 )
			{
				return false;
			}

			// set new index
			if ( !ValidateIndex( v, elemCount, mPosition.Size() ) )
			{
				return false;
			}

			mIndex16.Assign(v, v+ elemCount );

			mIndex32.Clear();
			mSubMeshs.Clear();
			return true;
		}
		else // clear index
		{
			if ( !mIndex16.IsEmpty() )
			{
				mIndex16.Clear();
				mSubMeshs.Clear();
			}
			return true;
		}
	}
	//------------------------------------------------------------------------
	bool 
		MeshRes::SetIndex32( const Index32Container::value_type* v, SizeT elemCount)
	{
		if ( v && elemCount > 0 )
		{
			if ( mPosition.Size() == 0 )
			{
				return false;
			}

			// set new index
			if ( !ValidateIndex( v, elemCount, mPosition.Size() ) )
			{
				return false;
			}
			mIndex32.Assign(v, v+ elemCount );

			mIndex16.Clear();
			mSubMeshs.Clear();
			return true;

		}
		else // clear index
		{
			if ( !mIndex32.IsEmpty() )
			{
				mIndex32.Clear();
				mSubMeshs.Clear();
			}
			return true;
		}
	}
	//------------------------------------------------------------------------
	bool 
		MeshRes::ValidateSubMesh(const SubMesh* submesh ) const
	{
		if ( !submesh )
		{
			return true;
		}

		if ( submesh->firstVertex < 0 || submesh->numVertex < 0 || submesh->FirstIndex < 0 || submesh->numIndex < 0 )
		{
			return false;
		}

		if ( (submesh->firstVertex + submesh->numVertex ) > mPosition.Size() ) 
		{
			return false;
		}

		if ( IsUseIndex16() )
		{
			if ( (submesh->FirstIndex + submesh->numIndex ) > mIndex16.Size() )
			{
				return false;
			}
		}
		else
		{
			if ( (submesh->FirstIndex + submesh->numIndex ) > mIndex32.Size() )
			{
				return false;
			}
		}

		return true;
	}
	//------------------------------------------------------------------------
	bool 
		MeshRes::SetSubMesh(const SubMesh* submesh, IndexT index)
	{
		if ( index < 0 )
		{
			return false;
		}

		if ( !submesh )
		{
			// delete
			if ( index < mSubMeshs.Size() )
			{
				mSubMeshs.EraseIndex( index );
			}
			return true;
		}
		else
		{
			if ( ValidateSubMesh(submesh) )
			{
				mSubMeshs.Fill(index, 1, *submesh );
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	//------------------------------------------------------------------------
	void 
		MeshRes::RecalculateBounds( bool includeSubMesh /*= true*/ )
	{
		mBox.begin_extend();
		//mBox.extend( Math::bbox() );
		for (IndexT i = 0; i < mPosition.Size();++i)
		{
			mBox.extend( Math::point(mPosition[i].x(), mPosition[i].y(), mPosition[i].z() ) );
		}
		mBox.end_extend();

		if ( includeSubMesh )
		{
			for ( IndexT i = 0; i < mSubMeshs.Size(); ++i)
			{
				RecalculateSubMeshBounds(i);
			}
		}
	}
	//------------------------------------------------------------------------
	void MeshRes::RecalculateSubMeshBounds( IndexT index )
	{
		if ( index >=0 && index < mSubMeshs.Size() )
		{
			SubMesh& sMesh = mSubMeshs[index];
			sMesh.box.begin_extend();
			if ( mPosition.Size() != 0 )
			{
				if ( IsUseIndex16() )
				{
					for (IndexT i = sMesh.FirstIndex;
						i < mIndex16.Size() && i < sMesh.numIndex;
						++i)
					{
						PositionData::Elem& elem = mPosition[ mIndex16[i] ];
						sMesh.box.extend( Math::point( elem.x(), elem.y(), elem.z() ) );
					}
				}
				else
				{
					for (IndexT i = sMesh.FirstIndex;
						i < mIndex32.Size() && i < sMesh.numIndex;
						++i)
					{
						PositionData::Elem& elem = mPosition[ mIndex32[i] ];
						sMesh.box.extend( Math::point( elem.x(), elem.y(), elem.z() ) );
					}
				}
			}
			sMesh.box.end_extend();
		}
	}
	bool 
		MeshRes::Validate(void) const
	{
		SizeT vertexCount = GetVertexCount();

		if ( !mColor.IsEmpty() )
		{
			if ( mColor.Size() != vertexCount )
			{
				return false; 
			}
		}

		for ( IndexT i = 0 ; i < mTexCoords.Size(); ++i )
		{
			const TexCoordData& texcoord = mTexCoords[i];

			if ( !texcoord.IsEmpty() )
			{
				if ( texcoord.Size() != vertexCount )
				{
					return false; 
				}
			}
		}

		if ( !mNormal.IsEmpty() )
		{
			if ( mNormal.Size() != vertexCount )
			{
				return false; 
			}
		}

		if ( !mTangent.IsEmpty() )
		{
			if ( mTangent.Size() != vertexCount )
			{
				return false; 
			}
		}

		if ( !mBiNormal.IsEmpty() )
		{
			if ( mBiNormal.Size() != vertexCount )
			{
				return false; 
			}
		}

		if ( !mBoneInfo.IsEmpty() )
		{
			if ( mBoneInfo.Size() != vertexCount )
			{
				return false; 
			}
		}

		// check index
		if ( !mIndex16.IsEmpty() && !mIndex32.IsEmpty() )
		{
			// 16bit or 32bit index only one type allowed 
			return false;
		}

		if ( mIndex16.Size() != 0 )
		{
			if( !ValidateIndex( &mIndex16[0], mIndex16.Size(), vertexCount ) )
			{
				return false;
			}
		}
		if ( mIndex32.Size() != 0 )
		{
			if( !ValidateIndex( &mIndex32[0], mIndex32.Size(),vertexCount ) )
			{
				return false;
			}
		}
		// check submesh
		for ( IndexT i = 0; i < mSubMeshs.Size(); ++i )
		{
			if( !ValidateSubMesh( &mSubMeshs[i] ) )
			{
				return false;
			}
		}

		return true;
	}
	//------------------------------------------------------------------------
	SizeT 
		MeshRes::CalculateRuntimeSize(void) const
	{
		SizeT size = 0;
		size += sizeof(mTopologyType);
		size += sizeof(mBox);

		size += sizeof(PositionData);
		size += sizeof(PositionData::Elem) * mPosition.Size();

		size += sizeof(ColorData);
		size += sizeof(ColorData::Elem) * mColor.Size();

		size += sizeof(mTexCoords);
		for( IndexT index = 0; index < mTexCoords.Size(); ++index )
		{
			size += sizeof(TexCoordData::Elem) * mTexCoords[index].Size();
		}

		size += sizeof(NormalData);
		size += sizeof(NormalData::Elem) * mNormal.Size();

		size += sizeof(TangentData);
		size += sizeof(TangentData::Elem) * mTangent.Size();

		size += sizeof(BiNormalData);
		size += sizeof(BiNormalData::Elem) * mBiNormal.Size();

		size += sizeof(BoneInfoData);
		size += sizeof(BoneInfoData::Elem) * mBoneInfo.Size();

		size += sizeof(Index16Container);
		size += sizeof(Index16Container::value_type) * mIndex16.Size();

		size += sizeof(Index32Container);
		size += sizeof(Index32Container::value_type) * mIndex32.Size();

		size += sizeof(SubMeshArray);
		size += sizeof(SubMeshArray::value_type) * mSubMeshs.Size();

		size += sizeof(AffectedBonesIndex);
		size += sizeof(AffectedBonesIndex::value_type) * mAffectedBonesIndex.Size();

		return size + Super::CalculateRuntimeSize();
	}
	//------------------------------------------------------------------------
	bool 
		MeshRes::SwapLoadImpl( const GPtr<Resource>& tempRes )
	{
		n_assert( tempRes.isvalid() );
		if ( tempRes->GetRtti() == this->GetRtti() )
		{
			GPtr<MeshRes> tempMesh = tempRes.downcast<MeshRes>();
			n_assert( tempMesh.isvalid() );

			mTopologyType = tempMesh->mTopologyType;
			mBox = tempMesh->mBox;
			meshId = tempMesh->meshId;
			mPosition.Swap( tempMesh->mPosition );
			mIndex16.Swap( tempMesh->mIndex16 );
			mIndex32.Swap( tempMesh->mIndex32 );
			mColor.Swap( tempMesh->mColor );

			mTexCoords.Clear();
			if ( tempMesh->mTexCoords.Size() != 0 )
			{
				mTexCoords.Fill(0, tempMesh->mTexCoords.Size(), TexCoordData() );
				for ( IndexT i = 0; i < mTexCoords.Size(); ++i )
				{
					mTexCoords[i].Swap( tempMesh->mTexCoords[i] );
				}
			}

			mNormal.Swap( tempMesh->mNormal );
			mTangent.Swap( tempMesh->mTangent );
			mBiNormal.Swap( tempMesh->mBiNormal );
			mBoneInfo.Swap( tempMesh->mBoneInfo );
			mSubMeshs.Swap( tempMesh->mSubMeshs );
			mAffectedBonesIndex.Swap( tempMesh->mAffectedBonesIndex );
			mSummeshUsedMaterial.Swap(tempMesh->mSummeshUsedMaterial);

			return true;
		}
		return false;
	}
	//------------------------------------------------------------------------
	void MeshRes::UnLoadImpl(void)
	{
		mPosition.Clear();
		mIndex16.Clear();
		mIndex32.Clear();
		mColor.Clear();
		mTexCoords.Clear();
		mNormal.Clear();
		mTangent.Clear();
		mBiNormal.Clear();
		mBoneInfo.Clear();
		mSubMeshs.Clear();
		mAffectedBonesIndex.Clear();
	}

}


