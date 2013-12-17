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
#include "resource/reslable.h"
#include "system/byteorder.h"
#include "rawresloader.h"

namespace Resources
{

	__ImplementClass(Resources::RawResLoader,'RRLD',Resources::ResourceLoader);
	//------------------------------------------------------------------------
	RawResLoader::RawResLoader()
	{

	}
	//------------------------------------------------------------------------
	RawResLoader::~RawResLoader()
	{

	}
	//------------------------------------------------------------------------
	bool
		RawResLoader::LoadResource(Resource* res )
	{
		if ( !res )
			return false;

		if ( res->GetRtti() != &RawRes::RTTI )
		{
			return false;
		}

		GPtr<Resource> pRes = res;
		GPtr<RawRes> pRawRes = pRes.downcast<RawRes>();
		n_assert(pRawRes);

		if ( !mStream.isvalid() )
		{
			return false;
		}

		GPtr<IO::BinaryReader> pReader = IO::BinaryReader::Create();
		n_assert(pReader.isvalid());

		pReader->SetStream( mStream );

		//  every file should be LittleEndian
		pReader->SetStreamByteOrder(System::ByteOrder::LittleEndian);

		if ( !pReader->Open() )
		{
			return false;
		}

		// load data
		if ( !LoadRaw(pReader, pRawRes) )
		{
			pReader->Close();
			return false;
		}

		pReader->Close();

#if NEBULA3_BOUNDSCHECKS
		if ( !pRawRes.isvalid() )
		{
			n_warning( " RawResLoader::LoadResource: %s is not valid \n", pRawRes->GetResourceId().AsString().AsCharPtr() );
			return false;
		}
#endif

		return true;
	}

	//------------------------------------------------------------------------------
	bool RawResLoader::LoadRaw(GPtr<IO::BinaryReader>& pReader, GPtr<RawRes>& pRawRes)
	{
		const int rawSize = pReader->GetStream()->GetSize()/sizeof(uint16);
		pRawRes->Setup(rawSize);

		for (int i=0; i<rawSize; ++i)
		{
			*(pRawRes->Ptr()+i) = pReader->ReadUShort();
		}

		return true;
	}

}
