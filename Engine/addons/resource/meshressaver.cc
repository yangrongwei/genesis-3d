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
#include "resource/meshressaver.h"
#include "resource/reslable.h"
#include "system/byteorder.h"


namespace Resources
{

	__ImplementClass(Resources::MeshResSaver,'MRSV',Resources::ResourceSaver);
	//------------------------------------------------------------------------
	MeshResSaver::MeshResSaver()
	{

	}
	//------------------------------------------------------------------------
	MeshResSaver::~MeshResSaver()
	{

	}
	//------------------------------------------------------------------------
	bool 
		MeshResSaver::SaveResource(Resource* res )
	{
		if ( !res )
			return false;

		if ( res->GetRtti() != &MeshRes::RTTI )
		{
			return false;
		}

		GPtr<Resource> pRes = res;
		GPtr<MeshRes> pMeshRes = pRes.downcast<MeshRes>();
		n_assert(pMeshRes);

		if ( !mStream.isvalid() )
		{
			return false;
		}

		// Only LOADED resource can be saved
		if ( pMeshRes->GetState() != Resource::Loaded )
		{
			return false;
		}

		GPtr<IO::BinaryWriter> pWriter = IO::BinaryWriter::Create();
		n_assert(pWriter.isvalid());

		pWriter->SetStream( mStream );

		// All files are little endian
		pWriter->SetStreamByteOrder(System::ByteOrder::LittleEndian);

		if ( !pWriter->Open() )
		{
			return false;
		}

		// save data
		if ( !SaveMesh(pWriter, pMeshRes) )
		{
			pWriter->Close();
			return false;
		}

		pWriter->Close();
		return true;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResSaver::SaveMesh(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh  )
	{
		pWriter->WriteInt(ResLable::L_Mesh);

		// cur version is 1
		pWriter->WriteInt(1);

		if( !WriteTopology( pWriter, pMesh ) )
		{
			return false;
		}

		if ( !WritePosition(pWriter, pMesh ) )
		{
			return false;
		}

		if ( !WriteIndex(pWriter, pMesh ) )
		{
			return false;
		}

		if ( !WriteColor(pWriter, pMesh ) )
		{
			return false;
		}

		if ( !WriteTexCoord(pWriter, pMesh ) )
		{
			return false;
		}

		if ( !WriteNormal(pWriter, pMesh ) )
		{
			return false;
		}

		if ( !WriteTangent(pWriter, pMesh ) )
		{
			return false;
		}

		if ( !WriteBiNormal(pWriter, pMesh ) )
		{
			return false;
		}

		if ( !WriteBoneInfo(pWriter, pMesh ) )
		{
			return false;
		}

		if ( !WriteSubMesh(pWriter, pMesh ) )
		{
			return false;
		}


		pWriter->WriteInt( ResLable::L_End );

		return true;
	}

	//------------------------------------------------------------------------
	bool 
		MeshResSaver::WriteTopology(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh )
	{
		pWriter->WriteInt(ResLable::L_Tolopogy);

		pWriter->WriteInt( (int)pMesh->GetTopologyType() );

		const Math::bbox& box = pMesh->GetBoundingBox();

		pWriter->WriteFloat( box.pmin.x() );
		pWriter->WriteFloat( box.pmin.y() );
		pWriter->WriteFloat( box.pmin.z() );

		pWriter->WriteFloat( box.pmax.x() );
		pWriter->WriteFloat( box.pmax.y() );
		pWriter->WriteFloat( box.pmax.z() );

		return true;
	}

	/// Fast write an array. ElemSize is byte size of element in the array you wish to write, it will check whether ElemSize equals T::value_type in case of mistake.
	template<int ElemSize, typename T>
	bool _FastWriteArray(const T& t,GPtr<IO::BinaryWriter>& pWriter)
	{
		n_static_assert( sizeof( typename T::value_type ) == ElemSize );

		int count = t.Size();
		pWriter->WriteInt(count);

		if( count == 0 )
		{
			return true;
		}

#if __WIN32__ || __ANDROID__ || __OSX__
		// need not swap. so can copy memory 

		pWriter->WriteRawData( &t[0], count*sizeof(typename T::value_type) );

		return true;
#else

#error		// don't kown if can directly copy now, should impl by Platform 

#endif

	}

	//------------------------------------------------------------------------
	bool 
		MeshResSaver::WritePosition(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh)
	{
		if ( pMesh->mPosition.IsEmpty() )
		{
			return true;
		}

		// data segment label 
		pWriter->WriteInt(ResLable::L_Position);
		// storage type label
		pWriter->WriteInt(ResLable::S_StdPosition);
		return _FastWriteArray<12>(pMesh->mPosition, pWriter );
	}
	//------------------------------------------------------------------------
	bool 
		MeshResSaver::WriteIndex(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh)
	{
		if ( pMesh->mIndex16.IsEmpty() && pMesh->mIndex32.IsEmpty() )
		{
			return true;
		}

		// data segment label 
		pWriter->WriteInt(ResLable::L_Index);

		if ( !pMesh->mIndex16.IsEmpty() )
		{
			// storage type label
			pWriter->WriteInt(ResLable::S_StdIndex16);
			return _FastWriteArray<2>(pMesh->mIndex16, pWriter );
		}
		else if ( !pMesh->mIndex32.IsEmpty() )
		{
			// storage type label
			pWriter->WriteInt(ResLable::S_StdIndex32);
			return _FastWriteArray<4>(pMesh->mIndex32, pWriter );
		}

		return false;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResSaver::WriteColor(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh)
	{
		if ( pMesh->mColor.IsEmpty() )
		{
			return true;
		}

		// data segment label 
		pWriter->WriteInt(ResLable::L_Color);
		// storage type label
		pWriter->WriteInt(ResLable::S_StdColor);

		return _FastWriteArray<4>(pMesh->mColor, pWriter );
	}
	//------------------------------------------------------------------------
	bool 
		MeshResSaver::WriteTexCoord(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh)
	{

		if ( pMesh->mTexCoords.IsEmpty() )
		{
			return true;
		}

		bool bOK = true;

		for ( IndexT i = 0; i < pMesh->mTexCoords.Size(); ++i )
		{
			// data segment label 
			pWriter->WriteInt(ResLable::L_TexCoord);

			// storage type label
			pWriter->WriteInt(ResLable::S_StdTexCoord);

			bOK &= _FastWriteArray<8>(pMesh->mTexCoords[i], pWriter );
		}


		return bOK;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResSaver::WriteNormal(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh)
	{
		if ( pMesh->mNormal.IsEmpty() )
		{
			return true;
		}

		// data segment label 
		pWriter->WriteInt(ResLable::L_Normal);
		// storage type label
		pWriter->WriteInt(ResLable::S_StdNormal);

		return _FastWriteArray<12>(pMesh->mNormal, pWriter );

	}
	//------------------------------------------------------------------------
	bool 
		MeshResSaver::WriteTangent(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh)
	{
		if ( pMesh->mTangent.IsEmpty() )
		{
			return true;
		}

		// data segment label 
		pWriter->WriteInt(ResLable::L_Tangent);
		// storage type label
		pWriter->WriteInt(ResLable::S_StdTangent);

		return _FastWriteArray<16>(pMesh->mTangent, pWriter );

	}
	//------------------------------------------------------------------------
	bool 
		MeshResSaver::WriteBiNormal(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh)
	{
		if ( pMesh->mBiNormal.IsEmpty() )
		{
			return true;
		}

		// data segment label 
		pWriter->WriteInt(ResLable::L_BiNormal);
		// storage type label
		pWriter->WriteInt(ResLable::S_StdBiNormal);

		return _FastWriteArray<16>(pMesh->mBiNormal, pWriter );

	}
	//------------------------------------------------------------------------
	bool 
		MeshResSaver::WriteBoneInfo(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh)
	{
		if ( pMesh->mBoneInfo.IsEmpty() )
		{
			return true;
		}

		// data segment label 
		pWriter->WriteInt(ResLable::L_BoneInfo);
		// storage type label
		pWriter->WriteInt(ResLable::S_StdBoneInfo);

		return _FastWriteArray<24>(pMesh->mBoneInfo, pWriter );

	}
	//------------------------------------------------------------------------
	bool 
		MeshResSaver::WriteSubMesh(GPtr<IO::BinaryWriter>& pWriter, GPtr<MeshRes>& pMesh)
	{
		if ( pMesh->mSubMeshs.IsEmpty() )
		{
			return true;
		}
		// data segment label 
		pWriter->WriteInt(ResLable::L_SubMesh);
		// storage type label
		pWriter->WriteInt(ResLable::S_StdSubMesh);

		SizeT count = pMesh->mSubMeshs.Size();

		pWriter->WriteInt(count);

		for ( int i = 0; i < count; ++i )
		{
			SubMesh& sMesh = pMesh->mSubMeshs[i];

			pWriter->WriteInt(sMesh.firstVertex);
			pWriter->WriteInt(sMesh.numVertex);
			pWriter->WriteInt(sMesh.FirstIndex);
			pWriter->WriteInt(sMesh.numIndex);

			const Math::bbox& box = sMesh.box;

			pWriter->WriteFloat( box.pmin.x() );
			pWriter->WriteFloat( box.pmin.y() );
			pWriter->WriteFloat( box.pmin.z() );

			pWriter->WriteFloat( box.pmax.x() );
			pWriter->WriteFloat( box.pmax.y() );
			pWriter->WriteFloat( box.pmax.z() );
		}

		return true;
	}







}


