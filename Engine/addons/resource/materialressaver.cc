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
#include "graphicsystem/Material/materialinstance.h"
#include "resinfo.h"
#include "materialressaver.h"
#include "addons/serialization/serializeserver.h"


namespace Resources
{
	__ImplementClass(Resources::MaterialSaver,'MRSA',Resources::ResourceSaver);

	MaterialSaver::MaterialSaver()
	{

	}

	MaterialSaver::~MaterialSaver()
	{

	}

	bool MaterialSaver::SaveResource( Resource* res )
	{
		if ( !res )
			return false;

		if ( res->GetRtti() != &MaterialRes::RTTI )
		{
			return false;
		}

		GPtr<Resource> pRes = res;
		GPtr<MaterialRes> pDevRes = pRes.downcast<MaterialRes>();
		n_assert(pDevRes.isvalid());

		if ( !mStream.isvalid() )
		{
			return false;
		}

		// Only loaded resource can be saved
		if ( pDevRes->GetState() != Resource::Loaded )
		{
			return false;
		}

		n_assert(Serialization::SerializationServer::HasInstance());
		Serialization::SerializationServer* serialServer = Serialization::SerializationServer::Instance();

#ifdef __GENESIS_EDITOR__
		Serialization::FileType eFile = Serialization::FT_DEFAULT;
#else
		Serialization::FileType eFile = Serialization::FT_DEFAULT;
#endif
		GPtr<Serialization::SerializeWriter> pWriter = serialServer->OpenWriteFile(mStream,eFile);
		n_assert(pWriter.isvalid());

		//pWriter->SetStream( mStream );
		// save data
		bool bRet = SaveMaterialRes(pDevRes, pWriter);
		bRet &= serialServer->CloseWriteFile(pWriter);
		return bRet;
	}
	//------------------------------------------------------------------------
#define DEFINE_SERIAL_ITEM_NAME(name) static const char* s_##name = #name

	DEFINE_SERIAL_ITEM_NAME(ShaderID);
	DEFINE_SERIAL_ITEM_NAME(MaterialInstanceRef);

	DEFINE_SERIAL_ITEM_NAME(ShaderConstantParamMapCnt);
	DEFINE_SERIAL_ITEM_NAME(ShaderConstantParamKey);
	DEFINE_SERIAL_ITEM_NAME(ShaderConstantParamValue);

	DEFINE_SERIAL_ITEM_NAME(ShaderTexParamMapCnt);
	DEFINE_SERIAL_ITEM_NAME(ShaderTexParamKey);
	DEFINE_SERIAL_ITEM_NAME(ShaderTexParamValue);
	//------------------------------------------------------------------------
	bool MaterialSaver::SaveMaterialRes(GPtr<MaterialRes>& pRes,GPtr<Serialization::SerializeWriter>& pWriter)
	{
		//pWriter->BeginFileSerialize();
		//Util::FourCC fourcc("MINS");
		//pWriter->BeginSerializeObject(fourcc);
		pWriter->BeginSerializeObject(Graphic::MaterialInstance::RTTI.GetFourCC());
		pWriter->SerializeVersion(GetVersion());

		GPtr<Graphic::MaterialInstance> pIns = pRes->GetMaterialInstance();
		pWriter->SerializeString(s_ShaderID,pIns->GetShaderID().AsString());

		// shader const param
		IndexT cnt = pIns->GetConstantParamCount();
		pWriter->SerializeInt(s_ShaderConstantParamMapCnt,cnt);

		for (int index = 0; index < cnt; ++ index)
		{

			Util::String strKey		= pIns->GetConstantParamName(index).AsString();
			Util::String strValue	= pIns->GetConstantParamValue(index);

			pWriter->SerializeString(s_ShaderConstantParamKey,strKey);
			pWriter->SerializeString(s_ShaderConstantParamValue,strValue);
		}


		// texture param
		SizeT texParamCount = pIns->GetTextureParamCount();
		pWriter->SerializeInt(s_ShaderTexParamMapCnt, texParamCount );
		for( int index = 0; index < texParamCount; ++index)
		{

			Util::String strKey		= pIns->GetTextureParamName(index).AsString();
			const GPtr<Resources::TextureResInfo>& pTexRes = pIns->GetTextureResInfo(index);
			Util::String strValue	= pTexRes->GetResID().AsString();

			pWriter->SerializeString(s_ShaderTexParamKey,strKey);
			pWriter->SerializeString(s_ShaderTexParamValue,strValue);
		}

		pWriter->EndSerializeObject();
		//pWriter->EndFileSerialize();
		return true;
	}
	


}