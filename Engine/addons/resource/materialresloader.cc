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
#include "materialresloader.h"
#include "graphicsystem/Material/MaterialManager.h"
#include "graphicsystem/GraphicObjectManager.h"
#include "addons/serialization/serializeserver.h"

namespace Resources
{
	__ImplementClass(Resources::MaterialLoader,'MALD',Resources::ResourceLoader);

	MaterialLoader::MaterialLoader()
	{

	}

	MaterialLoader::~MaterialLoader()
	{

	}

	bool MaterialLoader::LoadResource( Resource* res )
	{
		if ( !res )
			return false;

		if ( res->GetRtti() != &MaterialRes::RTTI )
		{
			return false;
		}

		GPtr<Resource> pRes = res;
		GPtr<MaterialRes> pMaterialRes = pRes.downcast<MaterialRes>();
		n_assert(pMaterialRes);
		n_assert(Serialization::SerializationServer::HasInstance());
		Serialization::SerializationServer* serialServer = Serialization::SerializationServer::Instance();

		Serialization::FileType eFile = Serialization::FT_DEFAULT;

		GPtr<Serialization::SerializeReader> pReader =serialServer->OpenReadFile(mStream,eFile);

		//pReader->SetStream(mStream);

		n_assert(pReader.isvalid());

		bool bRet = LoadMaterialRes(pMaterialRes,pReader);
		serialServer->CloseReadFile(pReader);
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

	void MaterialLoader::_Load(Serialization::SVersion& ver,GPtr<MaterialRes>& pRes,GPtr<Serialization::SerializeReader>& pReader)
	{
		switch (ver)
		{
		case static_cast<uint>(-1):
		case 1:
			_Load_1(pRes,pReader);
			break;
		default:
			SYS_EXCEPT(Exceptions::SerializeException,"TerrainComponentSerialization::Load unknonw version!",pRes->GetResourceId().AsString() );
			break;
		}		
	}
	//------------------------------------------------------------------------
	void MaterialLoader::_Load_1(GPtr<MaterialRes>& pRes,GPtr<Serialization::SerializeReader>& pReader)
	{
		//shader id
		Util::String strShaderID;
		Resources::ResourceId shaderID;
		pReader->SerializeString(s_ShaderID,strShaderID);
		shaderID = strShaderID.Get();

		//Get default material according to shader id then set material id
		GPtr<Graphic::MaterialInstanceManager>& pManager = App::GraphicObjectManager::Instance()->GetMaterialInstanceManager();
		GPtr<Graphic::MaterialInstance> matInstance = pManager->LoadMaterialInstance(pRes->GetResourceId(),shaderID);

		// modify params
		if ( matInstance )
		{			
			// shader const param
			int idxRef;
			pReader->SerializeInt(s_ShaderConstantParamMapCnt,idxRef);
			for ( IndexT i = 0; i < idxRef; i++ )
			{
				Util::String ustrKey;
				Util::String ustrValue;
				pReader->SerializeString(s_ShaderConstantParamKey,ustrKey);
				pReader->SerializeString(s_ShaderConstantParamValue,ustrValue);
				matInstance->_SetConstantParam(ustrKey, ustrValue);
			}

			// tex param
			pReader->SerializeInt(s_ShaderTexParamMapCnt,idxRef);
			for ( IndexT i = 0; i < idxRef; i++ )
			{
				Util::String ustrKey;
				Util::String ustrValue;
				pReader->SerializeString(s_ShaderTexParamKey,ustrKey);
				pReader->SerializeString(s_ShaderTexParamValue,ustrValue);

				matInstance->SetTexture(ustrKey, ustrValue, 1);
			}
		}
		pRes->SetMaterialInstance(matInstance);
	}
	//------------------------------------------------------------------------
	bool MaterialLoader::LoadMaterialRes(GPtr<MaterialRes>& pRes,GPtr<Serialization::SerializeReader>& pReader)
	{
		
		
		//pReader->BeginFileSerialize();
		Util::FourCC fourcc("MINS");
		pReader->BeginSerializeObject(fourcc);

		Serialization::SVersion ver;
		pReader->SerializeVersion(ver);

		_Load(ver,pRes,pReader);

		pReader->EndSerializeObject();
		//pReader->EndFileSerialize();
		
		return true;
	}
}