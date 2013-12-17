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
#include "resource/rawressaver.h"
#include "resource/reslable.h"
#include "system/byteorder.h"


namespace Resources
{

	__ImplementClass(Resources::RawResSaver,'RRSV',Resources::ResourceSaver);
	//------------------------------------------------------------------------
	RawResSaver::RawResSaver()
	{

	}
	//------------------------------------------------------------------------
	RawResSaver::~RawResSaver()
	{

	}
	//------------------------------------------------------------------------
	bool 
		RawResSaver::SaveResource(Resource* res )
	{
		//if ( !res )
		//	return false;

		//if ( res->GetRtti() != &MeshRes::RTTI )
		//{
		//	return false;
		//}
		//
		//GPtr<Resource> pRes = res;
		//GPtr<MeshRes> pMeshRes = pRes.downcast<MeshRes>();
		//n_assert(pMeshRes);

		//if ( !mStream.isvalid() )
		//{
		//	return false;
		//}

		//// Only loaded res can be saved
		//if ( pMeshRes->GetState() != Resource::Loaded && pMeshRes->GetState() != Resource::LoadedPartly )
		//{
		//	return false;
		//}

		//GPtr<IO::BinaryWriter> pWriter = IO::BinaryWriter::Create();
		//n_assert(pWriter.isvalid());

		//pWriter->SetStream( mStream );

		////  every file should be LittleEndian
		//pWriter->SetStreamByteOrder(System::ByteOrder::LittleEndian);

		//if ( !pWriter->Open() )
		//{
		//	return false;
		//}

		//// save data
		//if ( !SaveMesh(pWriter, pMeshRes) )
		//{
		//	pWriter->Close();
		//	return false;
		//}

		//pWriter->Close();
		return true;
	}


}
