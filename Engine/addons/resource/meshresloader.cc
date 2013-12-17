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
#include "resource/meshresloader.h"
#include "resource/reslable.h"
#include "system/byteorder.h"

#include "resource/DataChunkPacket.h"
#include "resource/meshSpliter.h"


namespace Resources
{

	__ImplementClass(Resources::MeshResLoader,'MRLD',Resources::ResourceLoader);
	//------------------------------------------------------------------------
	MeshResLoader::MeshResLoader()
	{

	}
	//------------------------------------------------------------------------
	MeshResLoader::~MeshResLoader()
	{

	}
	//------------------------------------------------------------------------
	bool 
		MeshResLoader::LoadResource(Resource* res )
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

		GPtr<IO::BinaryReader> pReader = IO::BinaryReader::Create();
		n_assert(pReader.isvalid());

		pReader->SetStream( mStream );

#if __OSX__
		pReader->SetStreamByteOrder(System::ByteOrder::BigEndian);
#else
		// All files are little endian
		pReader->SetStreamByteOrder(System::ByteOrder::LittleEndian);
#endif
		if ( !pReader->Open() )
		{
			return false;
		}

		// mesh does not support stream, in order to reload correctly, unload existing data first.
		pMeshRes->UnLoadImpl();

		// load data
		if ( !LoadMesh(pReader, pMeshRes) )
		{
			pReader->Close();
			return false;
		}

		pReader->Close();

#if NEBULA3_BOUNDSCHECKS
		if ( !pMeshRes->Validate() )
		{
			n_warning( " MeshResLoader::LoadResource: %s is not valid \n", pMeshRes->GetResourceId().AsString().AsCharPtr() );
			return false;
		}
#endif

		MeshSpliter::Instance()->DoWork(pMeshRes);
		return true;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResLoader::LoadMesh(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh  )
	{
		int magicNum = pReader->ReadInt();
		if ( magicNum != ResLable::L_Mesh )
		{
			return false;
		}

		int version = pReader->ReadInt();
		if ( version == 1 )
		{
			return Load_1(pReader, pMesh);
		}
		else if(version == 2)
		{
			return Load_2(pReader, pMesh);
		}
		else if(version == 3)
		{
			return Load_3(pReader, pMesh);
		}
		else
		{
			// not support other version now
			return false;
		}

		return false;
	}

	//------------------------------------------------------------------------
	bool MeshResLoader::Load_1( GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh )
	{
		do 
		{
			int type = pReader->ReadInt();
			if ( type == ResLable::L_End )
			{
				// End of file label read
				return true;
			}

			switch ( type )
			{
			case ResLable::L_Tolopogy:
				{
					if ( !ReadTopology(pReader, pMesh ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_Position:
				{
					if ( !ReadPosition(pReader, pMesh ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_Index:
				{
					if ( !ReadIndex(pReader, pMesh ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_Color:
				{
					if ( !ReadColor(pReader, pMesh ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_TexCoord:
				{
					if ( !ReadTexCoord(pReader, pMesh ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_Normal:
				{
					if ( !ReadNormal(pReader, pMesh ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_Tangent:
				{
					if ( !ReadTangent(pReader, pMesh ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_BiNormal:
				{
					if ( !ReadBiNormal(pReader, pMesh ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_BoneInfo:
				{
					if ( !ReadBoneInfo(pReader, pMesh ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_SubMesh:
				{
					if ( !ReadSubMesh(pReader, pMesh ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_AffectedBones:
				{
					if ( !ReadAffectedBones(pReader, pMesh) )
					{
						return false;
					}
				}
				break;
			default:
				return false;	// Unknown label read, file may corrupted.
			}

		} 
		while ( !pReader->Eof() );

		return true;
	}

	bool MeshResLoader::Load_2( GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh )
	{
		int type = pReader->ReadInt();
		if ( type == ResLable::L_End )
		{
			// End of file label read
			return true;
		}

		if ( type == ResLable::L_MeshID )
		{
			Util::String meshId = pReader->ReadString();
			pMesh->SetMeshID(meshId);
		}

		return Load_1(pReader, pMesh);
	}


	bool MeshResLoader::Load_3( GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh )
	{
		int type = pReader->ReadInt();
		if ( type == ResLable::L_End )
		{
			// End of file label read
			return true;
		}

		if ( type == ResLable::L_MeshID )
		{
			Util::String meshId = pReader->ReadString();
			pMesh->SetMeshID(meshId);
		}

		return Load_1(pReader, pMesh);
	}


	//------------------------------------------------------------------------
	bool 
		MeshResLoader::ReadTopology(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh )
	{
		int topologyType = pReader->ReadInt();
		pMesh->SetTopologyType( (RenderBase::PrimitiveTopology::Code)topologyType );

		float box[6];
		box[0] = pReader->ReadFloat();
		box[1] = pReader->ReadFloat();
		box[2] = pReader->ReadFloat();
		box[3] = pReader->ReadFloat();
		box[4] = pReader->ReadFloat();
		box[5] = pReader->ReadFloat();

		Math::bbox bb;
		bb.pmin.set( box[0],box[1],box[2] );
		bb.pmax.set( box[3],box[4],box[5] );

		pMesh->SetBoundingBox( bb );

		return true;
	}

	/// Fast write an array. ElemSize is byte size of element in the array you wish to write, it will check whether ElemSize equals T::value_type in case of mistake.
	template<int ElemSize, typename T>
	bool _FastReadArray(T& t,GPtr<IO::BinaryReader>& pReader)
	{
		n_static_assert( sizeof( typename T::value_type ) == ElemSize );

		int count = pReader->ReadInt();
		if ( count < 0 )
		{
			return false;
		}

		if( count == 0 )
		{
			t.Clear();
			return true;
		}

#if __WIN32__ || __ANDROID__ || __OSX__
		// need not swap. so can copy memory 

		t.Resize(count, typename T::value_type() );
		pReader->ReadRawData( &t[0], count*sizeof(typename T::value_type) );

		return true;
#else

		//#error		// don't kown if can directly copy now, should impl by Platform 

#endif

	}

	//------------------------------------------------------------------------
	bool 
		MeshResLoader::ReadPosition(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh)
	{
		int storage = pReader->ReadInt();
		if ( storage == ResLable::S_StdPosition )
		{
			return _FastReadArray<12>(pMesh->mPosition, pReader );
		}
		else if (storage == ResLable::S_PackedFloatFmt)
		{
			return ReadPackedFloat<PositionData, Math::float3>(pReader, pMesh->mPosition);
		}
		else
		{
			// unknown storage type 
			return false;
		}

		return false;
	}


	//------------------------------------------------------------------------
	bool 
		MeshResLoader::ReadIndex(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh)
	{
		int storage = pReader->ReadInt();

		if ( storage == ResLable::S_StdIndex16 )
		{
			return 	_FastReadArray<2>(pMesh->mIndex16, pReader );
		}
		else if ( storage == static_cast<int>(ResLable::S_StdIndex32) )
		{
			return 	_FastReadArray<4>(pMesh->mIndex32, pReader );
		}
		else if (storage == static_cast<int>(ResLable::S_PackedIntFmt) )
		{
			unsigned char indexByte = pReader->ReadUChar();
			if (indexByte == 2)
			{
				return ReadPackedInt<Index16Container, ushort, ushort>(pReader, pMesh->mIndex16);
			}
			else if (indexByte == 4)
			{
				return ReadPackedInt<Index32Container, uint, uint>(pReader, pMesh->mIndex32);
			}
		}
		else
		{
			// unknown storage type 
			return false;
		}

		return false;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResLoader::ReadColor(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh)
	{
		int storage = pReader->ReadInt();

		if ( storage == ResLable::S_StdColor )
		{
			return 	_FastReadArray<4>(pMesh->mColor, pReader );
		}
		else if (storage == static_cast<int>(ResLable::S_PackedIntFmt))
		{
			Util::Array<unsigned char> tmpArray;
			ReadPackedInt<Util::Array<unsigned char>, unsigned char, unsigned char>(pReader, tmpArray);

			if (tmpArray.Size() == 0)
			{
				return false;
			}

			pMesh->mColor.Resize(tmpArray.Size() / 4, Math::Color32());

			for (int i = 0; i < tmpArray.Size(); )
			{
				int j = i/4;
				pMesh->mColor[j].r = tmpArray[i++]; /* / 255.0f;*/
				pMesh->mColor[j].g = tmpArray[i++]; /* / 255.0f;*/
				pMesh->mColor[j].b = tmpArray[i++]; /* / 255.0f;*/
				pMesh->mColor[j].a = tmpArray[i++]; /* / 255.0f;*/
			}

			return true;
		}
		else
		{
			// unknown storage type 
			return false;
		}

		return false;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResLoader::ReadTexCoord(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh)
	{
		int storage = pReader->ReadInt();

		if ( storage == ResLable::S_StdTexCoord )
		{
			pMesh->mTexCoords.Append( TexCoordData() );
			return 	_FastReadArray<8>(pMesh->mTexCoords.Back(), pReader );
		}
		else if (storage == ResLable::S_PackedFloatFmt)
		{
			pMesh->mTexCoords.Append( TexCoordData() );
			return ReadPackedFloat<TexCoordData, Math::float2>(pReader, pMesh->mTexCoords.Back());
		}
		else
		{
			// unknown storage type 
			return false;
		}

		return false;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResLoader::ReadNormal(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh)
	{
		int storage = pReader->ReadInt();

		if ( storage == ResLable::S_StdNormal )
		{
			return 	_FastReadArray<12>(pMesh->mNormal, pReader );
		}
		else if (storage == ResLable::S_PackedFloatFmt)
		{
			return ReadPackedFloat<NormalData, Math::float3>(pReader, pMesh->mNormal);
		}
		else
		{
			// unknown storage type 
			return false;
		}

		return false;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResLoader::ReadTangent(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh)
	{
		int storage = pReader->ReadInt();

		if ( storage == ResLable::S_StdTangent )
		{
			return 	_FastReadArray<16>(pMesh->mTangent, pReader );
		}
		else if (storage == static_cast<int>(ResLable::S_PackedFloatFmt))
		{
			return ReadPackedFloat<TangentData, Math::float4>(pReader, pMesh->mTangent);
		}
		else
		{
			// unknown storage type 
			return false;
		}

		return false;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResLoader::ReadBiNormal(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh)
	{
		int storage = pReader->ReadInt();

		if ( storage == ResLable::S_StdBiNormal )
		{
			return 	_FastReadArray<16>(pMesh->mBiNormal, pReader );
		}
		else
		{
			// unknown storage type 
			return false;
		}

		return false;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResLoader::ReadBoneInfo(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh)
	{
		int storage = pReader->ReadInt();

		if ( storage == ResLable::S_StdBoneInfo )
		{
			return 	_FastReadArray<24>(pMesh->mBoneInfo, pReader );
		}
		else if (storage == ResLable::S_PackedFloatFmt || storage == ResLable::S_PackedIntFmt)
		{
			Util::Array<Math::float4> tmpFloatArray;
			if (!ReadPackedFloat<Util::Array<Math::float4>, Math::float4>(pReader, tmpFloatArray))
			{
				return false;
			}

			Util::Array<unsigned short> tmpIntArray;
			if(!ReadPackedInt<Util::Array<unsigned short>, unsigned short, unsigned short>(pReader, tmpIntArray) )
			{
				return false;
			}

			n_assert(tmpFloatArray.Size() * 4 == tmpIntArray.Size());

			pMesh->mBoneInfo.Resize(tmpFloatArray.Size(), Resources::BoneInfo());

			for (int i = 0; i < pMesh->mBoneInfo.Size(); ++i)
			{
				pMesh->mBoneInfo[i].boneWeight[0] = tmpFloatArray[i].x();
				pMesh->mBoneInfo[i].boneWeight[1] = tmpFloatArray[i].y();
				pMesh->mBoneInfo[i].boneWeight[2] = tmpFloatArray[i].z();
				pMesh->mBoneInfo[i].boneWeight[3] = tmpFloatArray[i].w();

				pMesh->mBoneInfo[i].boneIndex[0] = tmpIntArray[i*4];
				pMesh->mBoneInfo[i].boneIndex[1] = tmpIntArray[i*4+1];
				pMesh->mBoneInfo[i].boneIndex[2] = tmpIntArray[i*4+2];
				pMesh->mBoneInfo[i].boneIndex[3] = tmpIntArray[i*4+3];
			}

			return true;
		}
		else
		{
			// unknown storage type 
			return false;
		}

		return false;
	}
	//------------------------------------------------------------------------
	bool 
		MeshResLoader::ReadSubMesh(GPtr<IO::BinaryReader>& pReader, GPtr<MeshRes>& pMesh)
	{
		int storage = pReader->ReadInt();

		if ( storage == ResLable::S_StdSubMesh )
		{
			int Count = pReader->ReadInt();
			for ( int i = 0; i < Count; ++i )
			{
				pMesh->mSubMeshs.Append( SubMesh() );
				SubMesh& sMesh = pMesh->mSubMeshs.Back();
				sMesh.firstVertex = pReader->ReadInt();
				sMesh.numVertex = pReader->ReadInt();
				sMesh.FirstIndex = pReader->ReadInt();
				sMesh.numIndex = pReader->ReadInt();

				float box[6];
				box[0] = pReader->ReadFloat();
				box[1] = pReader->ReadFloat();
				box[2] = pReader->ReadFloat();
				box[3] = pReader->ReadFloat();
				box[4] = pReader->ReadFloat();
				box[5] = pReader->ReadFloat();

				sMesh.box.pmin.set( box[0],box[1],box[2] );
				sMesh.box.pmax.set( box[3],box[4],box[5] );
			}

			return true;
		}
		else
		{
			// unknown storage type 
			return false;
		}

		return false;
	}
	//------------------------------------------------------------------------
	bool
		MeshResLoader::ReadAffectedBones(GPtr<IO::BinaryReader> &pReader, GPtr<MeshRes> &pMesh)
	{
		int storage = pReader->ReadInt();

		if (storage == ResLable::S_StdAffectedBones)
		{
			int Count = pReader->ReadInt();

			Util::Array<uchar> bonesArray;
			for ( int i = 0; i < Count; ++i )
			{
				pMesh->mAffectedBonesIndex.Append(bonesArray);
				int nBonesAffected = static_cast<int>(pReader->ReadUChar());
				pMesh->mAffectedBonesIndex[i].Reserve(nBonesAffected);

				for (int iBone = 0; iBone<nBonesAffected; ++iBone)
				{
					uchar boneIndex = pReader->ReadUChar();
					pMesh->mAffectedBonesIndex[i].Append(boneIndex);
				}
			}

			return true;
		}
		else
		{
			return false;
		}

		return false;
	}






}


