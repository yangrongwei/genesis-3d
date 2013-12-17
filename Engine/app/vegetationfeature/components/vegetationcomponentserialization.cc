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

#include "stdneb.h"
#include "vegetationfeature/components/vegetationrendercomponent.h"
#include "vegetation/VegetationObejct.h"
#include "serialization/serializeserver.h"

namespace App
{
	const char* s_vegeObjName = "VegeObjName";
	const char* s_vegeObjectCount = "VegeObjCount";
	const char* s_StringEmpty = " ";

	using namespace Vegetation;
	using namespace Graphic;

	class VegetationComponentSerialization
	{
	public:
		VegetationComponentSerialization()
		{

		}
		inline void Load( VegetationRenderComponent* obj, Version ver, AppReader* pReader)
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader);
				return;
			}
			n_error(" VegetationComponentSerialization::Load unknonw version " );
		}

		void Load_1( VegetationRenderComponent* obj, AppReader* pReader )
		{
			SizeT count;
			pReader->SerializeInt(s_vegeObjectCount,  count );
			for (IndexT objIdx = 0; objIdx < count; ++ objIdx)
			{
				GPtr<VegetationObject> vegeObj = pReader->SerializeObject<VegetationObject>();
				obj->AddVegetationObject(vegeObj);

				// save a .veg file
				GPtr<VegeInstanceMap>& pInstMap = vegeObj->CreateInstanceMap();

				Serialization::SerializationServer* pSerialzeMgr = Serialization::SerializationServer::Instance();
				if( pSerialzeMgr )
				{
					GPtr<Serialization::SerializeReader> pReader = pSerialzeMgr->OpenReadFile( vegeObj->GetInstanceFilePath() );
					if ( pReader )
					{
						pInstMap = pReader->SerializeObject<VegeInstanceMap>();
						pSerialzeMgr->CloseReadFile( pReader );
					}
				}
			}

		}

		void Save( const VegetationRenderComponent* obj , AppWriter* pWriter )
		{
			SizeT count = obj->GetCountOfObjectArray();

			pWriter->SerializeInt(s_vegeObjectCount, count );
			for ( IndexT index = 0; index < count; ++index )
			{
				GPtr<Vegetation::VegetationObject> tempObj = obj->GetVegetObject(index);
				pWriter->SerializeObject(tempObj);	

				// save a .veg file
				const GPtr<VegeInstanceMap>& pInstMap = tempObj->GetInstanceMap();

				Serialization::SerializationServer* pSerialzeMgr = Serialization::SerializationServer::Instance();
				if( pSerialzeMgr )
				{
					GPtr<Serialization::SerializeWriter> pWriter = pSerialzeMgr->OpenWriteFile( tempObj->GetInstanceFilePath() );
					if ( pWriter )
					{
						pWriter->SerializeObject( pInstMap );
						pSerialzeMgr->CloseWriteFile( pWriter );
					}
				}

			}
		}
	};

}

namespace App
{
	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version VegetationRenderComponent::GetVersion() const
	{
		return 1;	//	current version is 1
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void VegetationRenderComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		VegetationComponentSerialization Serialize;
		Serialize.Load( this, ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void VegetationRenderComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		VegetationComponentSerialization Serialize;
		Serialize.Save(this,  pWriter );
	}
	//------------------------------------------------------------------------
	void VegetationRenderComponent::CopyFrom( const GPtr<Component>& pComponent )
	{
		if( !pComponent.isvalid()  )
			return;
		if( !pComponent->GetRtti()->IsDerivedFrom( *(this->GetRtti()) ) )
			return;

		GPtr<VegetationRenderComponent> pSource = pComponent.downcast<VegetationRenderComponent>();
		//SetTemplateName( pSource->GetTemplateName(), pSource->GetParticleSystem()->GetName());
	}
}