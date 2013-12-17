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
#include "resource/skeletonresloader.h"
#include "resource/reslable.h"
#include "system/byteorder.h"

namespace Resources
{
	__ImplementClass(Resources::SkeletonResLoader, 'SKRL', Resources::ResourceLoader );
	//------------------------------------------------------------------------
	SkeletonResLoader::SkeletonResLoader()
	{

	}
	//------------------------------------------------------------------------
	SkeletonResLoader::~SkeletonResLoader()
	{

	}
	//------------------------------------------------------------------------
	bool 
		SkeletonResLoader::LoadResource(Resource* res )
	{
		if ( !res )
			return false;

		if ( res->GetRtti() != &SkeletonRes::RTTI )
		{
			return false;
		}

		GPtr<Resource> pRes = res;
		GPtr<SkeletonRes> pSkelRes = pRes.downcast<SkeletonRes>();
		n_assert(pSkelRes.isvalid());

		if ( !mStream.isvalid() )
		{
			return false;
		}

		GPtr<IO::BinaryReader> pReader = IO::BinaryReader::Create();
		n_assert(pReader.isvalid());

		pReader->SetStream( mStream );

		//  所有文件都是小端的
#ifdef __OSX__
		pReader->SetStreamByteOrder(System::ByteOrder::BigEndian);
#else
		pReader->SetStreamByteOrder(System::ByteOrder::LittleEndian);
#endif

		if ( !pReader->Open() )
		{
			return false;
		}

		// skeleton不支持流式加载。为了能够正确的reload。首先卸载Mesh已经有的数据
		pSkelRes->UnLoadImpl();

		// load data
		if ( !LoadSkeleton(pReader, pSkelRes) )
		{
			pReader->Close();
			return false;
		}

		pReader->Close();

		return true;
	}
	//------------------------------------------------------------------------
	bool 
		SkeletonResLoader::LoadSkeleton(GPtr<IO::BinaryReader>& pReader, GPtr<SkeletonRes>& pSkelRes )
	{
		n_assert( pReader.isvalid() && pSkelRes.isvalid() );

		int magicNum = pReader->ReadInt();

		if ( magicNum != ResLable::L_Skeleton )
		{
			return false;
		}

		int version = pReader->ReadInt();
		if ( version == 1)
		{
			// 读取版本1
			return Load_1(pReader, pSkelRes);
		}
		else if(version == 2)
		{
			// 读取版本2
			return Load_2(pReader, pSkelRes);
		}
		else		
		{
			// not support other version now
			return false;
		}

		return false;
	}

	//------------------------------------------------------------------------
	bool SkeletonResLoader::Load_1( GPtr<IO::BinaryReader>& pReader, GPtr<SkeletonRes>& pSkelRes )
	{
		do 
		{
			int type = pReader->ReadInt();
			if ( type == ResLable::L_End )
			{
				// 读到文件结尾标志
				return true;
			}

			switch ( type )
			{
			case ResLable::L_Bone:	//	读取inverse binding matrix
				{
					if ( !ReadSkelBone(pReader, pSkelRes ) )
					{
						return false;
					}
				}
				break;
			case ResLable::L_BoneTree:
				{
					if (! ReadSkelTree(pReader, pSkelRes))
					{
						return false;
					}
				}
				break;
			default:
				return false;	//	不认识的标示符号。文件可能读错了。
			}

		} 
		while ( !pReader->Eof() );

		return true;
	}

	//------------------------------------------------------------------------
	bool SkeletonResLoader::Load_2( GPtr<IO::BinaryReader>& pReader, GPtr<SkeletonRes>& pSkelRes )
	{
		int type = pReader->ReadInt();
		if ( type == ResLable::L_End )
		{
			// 读到文件结尾标志
			return true;
		}

		if ( type == ResLable::L_SkelID )
		{
			Util::String skelId = pReader->ReadString();
			pSkelRes->SetSkelID(skelId);
		}

		return Load_1(pReader, pSkelRes);
	}

	//------------------------------------------------------------------------
	bool 
		SkeletonResLoader::ReadSkelBone(GPtr<IO::BinaryReader>& pReader, GPtr<SkeletonRes>& pSkelRes)
	{
		int storage = pReader->ReadInt();
		if ( storage == ResLable::S_StdBone )
		{
			ushort count = pReader->ReadUShort();

			pSkelRes->Reserve(count);
			for ( ushort index = 0; index < count; ++index )
			{
				SkelBone bone;
				bone.parentIndex = pReader->ReadUShort();
				bone.boneName = pReader->ReadString();
				bone.inverseBindingMatrix = pReader->ReadMatrix44();
				pSkelRes->AddSkelBone( bone );
			}
			if( pSkelRes->GetSkelBones().Size() == (SizeT)count ) 
			{
				pSkelRes->AddSkeletonPair();
				return true;
			}
			else
			{
				// add bone fail
				return false;
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
		SkeletonResLoader::ReadSkelTree(GPtr<IO::BinaryReader> &pReader, GPtr<SkeletonRes> &pSkelRes)
	{
		int storage = pReader->ReadInt();

		if ( storage == ResLable::S_StdBoneTree)
		{
			ushort count = pReader->ReadUShort();

			for (ushort index = 0; index<count; ++index)
			{
				GPtr<SkelTreeData> pData =SkelTreeData::Create();

				Util::String nodeName   = pReader->ReadString();
				Util::String parentName = pReader->ReadString();

				pData->name = nodeName;

				Math::vector pos   = pReader->ReadVector();
				Math::float4 trans = Math::float4(pos.x(), pos.y(), pos.z(), 1.0f);

				Math::vector scale  = pReader->ReadVector();
				Math::float4 scale4 = Math::float4(scale.x(), scale.y(), scale.z(), 0.0f);

				Math::float4 rot    = pReader->ReadFloat4();

				pData->pos   = trans;
				pData->scale = scale4;
				pData->rot   = rot;

				pSkelRes->AddSkelTreeData(pData, parentName);
			}

			if (pSkelRes->GetSkelTreeDataCount() == (SizeT) count)
			{
				return true;
			} 
			else
			{
				return false;
			}

		}	
		else
		{
			return false;
		}

		return false;
	}


}
