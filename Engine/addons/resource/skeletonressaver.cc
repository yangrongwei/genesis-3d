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
#include "resource/skeletonressaver.h"
#include "resource/reslable.h"

namespace Resources
{
	__ImplementClass( Resources::SkeletonResSaver,'SKRS',Resources::ResourceSaver);
	//------------------------------------------------------------------------
	SkeletonResSaver::SkeletonResSaver()
	{

	}
	//------------------------------------------------------------------------
	SkeletonResSaver::~SkeletonResSaver()
	{

	}
	//------------------------------------------------------------------------
	bool SkeletonResSaver::SaveResource(Resource* res )
	{
		if ( !res )
			return false;

		if ( res->GetRtti() != &SkeletonRes::RTTI )
		{
			return false;
		}

		GPtr<Resource> pRes = res;
		GPtr<SkeletonRes> pSkelRes = pRes.downcast<SkeletonRes>();
		n_assert(pSkelRes);

		if ( !mStream.isvalid() )
		{
			return false;
		}

		// Only loaded res can be saved
		if ( pSkelRes->GetState() != Resource::Loaded  )
		{
			return false;
		}

		GPtr<IO::BinaryWriter> pWriter = IO::BinaryWriter::Create();
		n_assert(pWriter.isvalid());

		pWriter->SetStream( mStream );

		// Every file should be LittleEndian
		pWriter->SetStreamByteOrder(System::ByteOrder::LittleEndian);

		if ( !pWriter->Open() )
		{
			return false;
		}

		// save data
		if ( !SaveSkeleton(pWriter, pSkelRes) )
		{
			pWriter->Close();
			return false;
		}

		pWriter->Close();
		return true;
	}
	//------------------------------------------------------------------------
	bool 
		SkeletonResSaver::SaveSkeleton(GPtr<IO::BinaryWriter>& pWriter, GPtr<SkeletonRes>& pSkelRes)
	{
		pWriter->WriteInt(ResLable::L_Skeleton);

		// cur version is 1
		pWriter->WriteInt(1);

		if( !WriteSkelBone( pWriter, pSkelRes ) )
		{
			return false;
		}

		pWriter->WriteInt( ResLable::L_End );

		return true;
	}
	//------------------------------------------------------------------------
	bool 
		SkeletonResSaver::WriteSkelBone(GPtr<IO::BinaryWriter>& pWriter, GPtr<SkeletonRes>& pSkelRes)
	{
		n_assert( pWriter.isvalid() && pSkelRes.isvalid() );

		const SkelBoneContainer& container = pSkelRes->GetSkelBones();

		if ( container.IsEmpty() )
		{
			return true;
		}

		// Data mask
		pWriter->WriteInt(ResLable::L_Bone);

		//save type mask
		pWriter->WriteInt(ResLable::S_StdBone);

		SizeT size = container.Size();
		if ( size > MaxSkeletonBoneCount )
		{
			// the max bone count is 65535
			return false;
		}

		// note: ushort
		pWriter->WriteUShort( (ushort)size );

		for ( IndexT index = 0; index < size; ++index )
		{
			const SkelBone& bone = container[index];

#if NEBULA3_BOUNDSCHECKS
			if ( bone.boneName.IsValid() 
				&& ( (bone.parentIndex == MaxSkeletonBoneCount) || ( bone.parentIndex < size ) ) )
			{
				pWriter->WriteUShort( bone.parentIndex );
				pWriter->WriteString( bone.boneName.AsString() );
				pWriter->WriteMatrix44( bone.inverseBindingMatrix );
			}
			else
			{
				return false;
			}
#else
			pWriter->WriteUShort( bone.parentIndex );
			pWriter->WriteString( bone.boneName );
			pWriter->WriteMatrix44( bone.inverseBindingMatrix );
#endif
		}

		return true;
	}
}