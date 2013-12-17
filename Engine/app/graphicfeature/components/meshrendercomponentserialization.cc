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
#include "graphicfeature/components/meshrendercomponent.h"


namespace App
{
	class MeshRenderComponentSerialization
	{
	public:
		MeshRenderComponentSerialization( MeshRenderComponent* pComponent )
			:mObject(pComponent)
		{

		}
		inline void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
		{
			if ( 1 == ver )
			{
				Load_1(pReader);
				return;
			}
			if ( 2 == ver )
			{
				Load_2(pReader, args);
				return;
			}
			if ( 3 == ver )
			{
				Load_3(pReader, args);
				return;
			}
			if (4 == ver )
			{
				Load_4(pReader, args);
				return;
			}
			n_error(" MeshRenderComponentSerialization::Load unknonw version " );
		}

		void Load_1( AppReader* pReader );
		void Load_2( AppReader* pReader, const Serialization::SerializationArgs* args );
		void Load_3( AppReader* pReader, const Serialization::SerializationArgs* args );
		void Load_4( AppReader* pReader, const Serialization::SerializationArgs* args );
		void Save( AppWriter* pWriter );
	protected:
		MeshRenderComponent* mObject;

	};

	const char* s_MeshResID = "Mesh";
	const char* s_MeshLoadingPriority = "LoadingPriority";
	const Util::String s_MeshDummyID = "EmptyNull";
	const char* s_LMID = "LightmapID";
	const char* s_LMTexParam = "LightmapST";
	const char* s_LMScale = "LightmapScale";

	//------------------------------------------------------------------------
	void MeshRenderComponentSerialization::Load_1(AppReader* pSerialize)
	{
/*		
		// shader count
		SizeT count = 0;
		pSerialize->SerializeInt(s_ShaderCount, count);
		
		for ( IndexT iShader = 0; iShader < count; ++iShader )
		{
			Util::String ShaderID;
			pSerialize->SerializeString(s_ShaderID, ShaderID);
			n_assert( ShaderID.IsValid() );
			mObject->SetShaderID(iShader,ShaderID  );
			
			SizeT texCount = 0;
			pSerialize->SerializeInt(s_TextureCount, texCount );
			for ( IndexT iTex = 0; iTex < texCount; ++iTex )
			{
				Util::String paramName;
				Util::String texID;
				pSerialize->SerializeString(s_TextureParamName, paramName);
				pSerialize->SerializeString(s_TextureID, texID );
				n_assert(paramName.IsValid());
				n_assert(texID.IsValid());
				mObject->_AddTextureParam(iShader,paramName,texID);
			}
		}
*/
	}

	//------------------------------------------------------------------------
	void MeshRenderComponentSerialization::Load_2(AppReader* pSerialize, const Serialization::SerializationArgs* args)
	{
		const ComponentSerializationArgs* cargs = args->cast_fast<ComponentSerializationArgs>();

		Resources::Priority priority;
		pSerialize->SerializeInt(s_MeshLoadingPriority, priority);//此参数配置已废弃。
		
		priority = (Resources::ResourcePriority::Undefinition == cargs->getPriority()) ? Resources::ResourcePriority::MeshDefault : cargs->getPriority();
		Util::String meshName;
		pSerialize->SerializeString(s_MeshResID, meshName );
		if ( meshName != s_MeshDummyID )
		{
			mObject->SetMeshID( meshName, priority );
		}
	}
	//------------------------------------------------------------------------
	void MeshRenderComponentSerialization::Load_3(AppReader* pSerialize, const Serialization::SerializationArgs* args)
	{
		const ComponentSerializationArgs* cargs = args->cast_fast<ComponentSerializationArgs>();

		Resources::Priority priority;
		pSerialize->SerializeInt(s_MeshLoadingPriority, priority);//此参数配置已废弃。

		priority = (Resources::ResourcePriority::Undefinition == cargs->getPriority()) ? Resources::ResourcePriority::MeshDefault : cargs->getPriority();
		Util::String meshName;
		pSerialize->SerializeString(s_MeshResID, meshName );
		if ( meshName != s_MeshDummyID )
		{
			mObject->SetMeshID( meshName, priority );
		}

		unsigned int lmID = 0xFFFF;
		Math::float4 lmTexParam(1.0f,1.0f,0.0f,0.0f);

		pSerialize->SerializeUInt(s_LMID, lmID);
		mObject->SetLMIndex(lmID);
		
		pSerialize->SerializeFloat4(s_LMTexParam, lmTexParam);
		mObject->SetLMTexParam( lmTexParam );
	}
	//------------------------------------------------------------------------
	void MeshRenderComponentSerialization::Load_4(AppReader* pSerialize, const Serialization::SerializationArgs* args)
	{
		const ComponentSerializationArgs* cargs = args->cast_fast<ComponentSerializationArgs>();

		Resources::Priority priority;
		pSerialize->SerializeInt(s_MeshLoadingPriority, priority);//此参数配置已废弃。

		priority = (Resources::ResourcePriority::Undefinition == cargs->getPriority()) ? Resources::ResourcePriority::MeshDefault : cargs->getPriority();
		Util::String meshName;
		pSerialize->SerializeString(s_MeshResID, meshName );
		if ( meshName != s_MeshDummyID )
		{
			mObject->SetMeshID( meshName, priority );
		}

		unsigned int lmID = 0xFFFF;
		Math::float4 lmTexParam(1.0f,1.0f,0.0f,0.0f);

		pSerialize->SerializeUInt(s_LMID, lmID);
		mObject->SetLMIndex(lmID);

		pSerialize->SerializeFloat4(s_LMTexParam, lmTexParam);
		mObject->SetLMTexParam( lmTexParam );

		double lmScale = 1.0f;
		pSerialize->SerializeDouble( s_LMScale, lmScale );
		mObject->SetLMScale( lmScale );
	}
	//------------------------------------------------------------------------
	void MeshRenderComponentSerialization::Save(AppWriter* pSerialize)
	{
		if (mObject->GetMeshID().IsValid())
		{
			pSerialize->SerializeInt(s_MeshLoadingPriority, mObject->GetPriority());
			pSerialize->SerializeString(s_MeshResID, mObject->GetMeshID().AsString() );
		}
		else
		{
			// can not Serialize empty string
			pSerialize->SerializeInt(s_MeshLoadingPriority, 0);
			pSerialize->SerializeString(s_MeshResID, Util::String(s_MeshDummyID) );
		}

		unsigned int lmID = mObject->GetLMIndex();
		Math::float4 lmST = mObject->GetLMTexParam();
		double lmScale = mObject->GetLMScale();

		pSerialize->SerializeUInt(s_LMID, lmID);
		pSerialize->SerializeFloat4(s_LMTexParam, lmST);
		pSerialize->SerializeDouble(s_LMScale, lmScale);
	}

}

namespace App
{
	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version MeshRenderComponent::GetVersion() const
	{
		//return 2;	//	当前版本号是2
		//return 3;	//	当前版本号是3,增加lightmap信息的序列化
		return 4; //当前版本号是4
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void MeshRenderComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		MeshRenderComponentSerialization Serialize(this);
		Serialize.Load( ver, pReader, args );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void MeshRenderComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		MeshRenderComponentSerialization Serialize(const_cast<MeshRenderComponent*>(this));
		Serialize.Save( pWriter );
	}

}

