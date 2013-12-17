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
#include "graphicfeature/components/rendercomponent.h"
#include "graphicfeature/components/simpleskycomponent.h"

namespace App
{
	class RenderComponentSerialization
	{
	public:
		RenderComponentSerialization( const RenderComponent* pComponent )
			:mObject(pComponent)
		{

		}
		inline void Load( Version ver, AppReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(pReader);
				return;
			}
			else if ( 2 == ver )
			{
				Load_2(pReader);
				return;
			}
			else if ( 3 == ver )
			{
				Load_3(pReader);
				return;
			}
			else if ( 4 == ver)
			{
				Load_4(pReader);
				return;
			}
			else if ( 5 == ver)
			{
				Load_5(pReader);
				return;
			}
			else if ( 6 == ver)
			{
				Load_6(pReader);
				return;
			}
			n_error(" MeshRenderComponentSerialization::Load unknonw version " );
		}

		void Load_1( AppReader* pReader );
		void Load_2( AppReader* pReader );
		void Load_3( AppReader* pReader );
		void Load_4( AppReader* pReader );
		void Load_5( AppReader* pReader );
		void Load_6( AppReader* pReader );
		void Save( AppWriter* pWriter );
		void Save_1( AppWriter* pWriter );
		void Save_2( AppWriter* pWriter );
	protected:
		const RenderComponent* mObject;

	};
	
	const char* s_ShaderCount = "ShaderCount";
	const char* s_ShaderID = "ShaderID";
	const char* s_TextureCount = "TextureCount";
	const char* s_TextureParamName = "TextureParam";
	const char* s_TextureID = "TextureID";
	const char* s_DummyID = "EmptyNull";
	const char* s_ConstantParamCount = "ConstantParamCount";
	const char* s_ConstantParamName = "ConstantParamName";
	const char* s_ConstantParamValue = "ConstantParamValue";

	const char* s_MaterialCount = "MaterialCount";
	const char* s_MaterialID = "MaterialID";

	const char* s_ReceiveShadow = "ReceiveShadow";
	const char* s_CastShadow = "CastShadow";
	//------------------------------------------------------------------------
	void RenderComponentSerialization::Load_1(AppReader* pSerialize)
	{
		RenderComponent* pRenderCom = const_cast<RenderComponent*>( mObject );
		
		// shader count
		SizeT count = 0;
		pSerialize->SerializeInt(s_ShaderCount, count);
		
		for ( IndexT iShader = 0; iShader < count; ++iShader )
		{
			Util::String ShaderID;
			pSerialize->SerializeString(s_ShaderID, ShaderID);
			n_assert( ShaderID.IsValid() );
			pRenderCom->SetMaterialByShaderID(iShader,ShaderID  );

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
				pRenderCom->_AddTextureParam(iShader,paramName,texID);
			}

			SizeT scCount = 0;
			pSerialize->SerializeInt(s_ConstantParamCount, scCount);
			for ( IndexT iSC = 0; iSC < scCount; ++iSC )
			{
				Util::String paramName;
				Util::String paramValue;
				pSerialize->SerializeString(s_ConstantParamName,paramName);
				pSerialize->SerializeString(s_ConstantParamValue,paramValue);
				n_assert(paramName.IsValid());
				n_assert(paramValue.IsValid());
				pRenderCom->_SetShaderConstantParam(iShader,paramName,paramValue);
			}
		}
	}
	//------------------------------------------------------------------------
	void RenderComponentSerialization::Load_2(AppReader* pSerialize)
	{
		RenderComponent* pRenderCom = const_cast<RenderComponent*>( mObject );

		// mat count
		SizeT count = 0;
		pSerialize->SerializeInt(s_MaterialCount, count);
		for ( IndexT iMat = 0; iMat < count; ++iMat )
		{
			Util::String matID;
			pSerialize->SerializeString(s_MaterialID, matID);
			n_assert( matID.IsValid() );
			pRenderCom->SetMaterialID(iMat,matID  );
            n_warning( "%s\n", matID.AsCharPtr() );
			// note: texParam and shaderConstParam be seted by materialIns Manager 


		}

	}
	//------------------------------------------------------------------------
	void RenderComponentSerialization::Load_3( AppReader* pReader )
	{
		Load_2(pReader);

		RenderComponent* pRenderCom = const_cast<RenderComponent*>( mObject );

		bool receiveShadow;
		pReader->SerializeBool(s_ReceiveShadow,receiveShadow);
		pRenderCom->SetReceiveShadow(receiveShadow);
	}
	//------------------------------------------------------------------------
	void RenderComponentSerialization::Load_4( AppReader* pReader )
	{
		Load_2(pReader);

		RenderComponent* pRenderCom = const_cast<RenderComponent*>( mObject );

		bool receiveShadow;
		pReader->SerializeBool(s_ReceiveShadow,receiveShadow);
		pRenderCom->SetReceiveShadow(receiveShadow);

		bool castShadow;
		pReader->SerializeBool(s_CastShadow,castShadow);
		pRenderCom->SetCastShadow(castShadow);
	}
	//------------------------------------------------------------------------
	void RenderComponentSerialization::Load_5( AppReader* pReader)
	{
		RenderComponent* pRenderCom = const_cast<RenderComponent*>( mObject );
		if ( !pRenderCom->IsA(SimpleSkyComponent::RTTI) )
		{// mat count
		   SizeT count = 0;
		   pReader->SerializeInt(s_MaterialCount, count);
		   for ( IndexT iMat = 0; iMat < count; ++iMat )
		   {
			   Util::String matID;
			   pReader->SerializeString(s_MaterialID, matID);
			   n_assert( matID.IsValid() );
			   pRenderCom->SetMaterialID(iMat,matID  );
			   n_warning( "%s\n", matID.AsCharPtr() );
		   }
		}

		bool receiveShadow;
		pReader->SerializeBool(s_ReceiveShadow,receiveShadow);
		pRenderCom->SetReceiveShadow(receiveShadow);

		bool castShadow;
		pReader->SerializeBool(s_CastShadow,castShadow);
		pRenderCom->SetCastShadow(castShadow);
	}
	//------------------------------------------------------------------------
	void RenderComponentSerialization::Load_6( AppReader* pReader)
	{
		Load_4( pReader );
	}
	//------------------------------------------------------------------------
	void RenderComponentSerialization::Save(AppWriter* pSerialize)
	{
		Save_2(pSerialize);
	}
	//------------------------------------------------------------------------
	void RenderComponentSerialization::Save_1(AppWriter* pSerialize)
	{
		RenderComponent* pRenderCom = const_cast<RenderComponent*>( mObject );

		// shader count
		SizeT count = pRenderCom->GetShaderCount();
		pSerialize->SerializeInt(s_ShaderCount , count );

		for ( IndexT iShader = 0; iShader < count; ++iShader )
		{
			// shader id
			const Resources::ResourceId& shaderID = pRenderCom->GetShaderID(iShader);
			n_assert( shaderID.IsValid() );
			pSerialize->SerializeString(s_ShaderID, shaderID.AsString());

			// texture param
			SizeT texParamCount = pRenderCom->GetTextureParamCount(iShader);
			pSerialize->SerializeInt(s_TextureCount, texParamCount );
			for ( IndexT iTex = 0; iTex < texParamCount; ++iTex )
			{
				const ShaderParamString& paramName =  pRenderCom->EnumTextureParam( iShader, iTex );
				n_assert( paramName.IsValid() );
				pSerialize->SerializeString( s_TextureParamName, paramName.AsString());

				const Resources::ResourceId& texID = pRenderCom->GetTexture(iShader,paramName);
				n_assert( texID.IsValid() );
				pSerialize->SerializeString( s_TextureID, texID.AsString());
			}

			// constant param
			SizeT scParamCount = pRenderCom->GetShaderConstantParamCount(iShader);
			pSerialize->SerializeInt(s_ConstantParamCount, scParamCount );
			for( IndexT iSC = 0; iSC < scParamCount; ++iSC )
			{
				const ShaderParamString& paramName = pRenderCom->EnumShaderConstantParam( iShader, iSC );
				n_assert( paramName.IsValid() );
				pSerialize->SerializeString( s_ConstantParamName, paramName.AsString());

				const Util::String& paramValue = pRenderCom->_GetShaderConstantParamValue(iShader,paramName);
				n_assert( paramValue.IsValid() );
				pSerialize->SerializeString( s_ConstantParamValue, paramValue );
			}
		}

	}
	//------------------------------------------------------------------------
	void RenderComponentSerialization::Save_2(AppWriter* pSerialize)
	{// 引入材质管理器后，只需存储一个matID，材质的存储由材质管理器做
		RenderComponent* pRenderCom = const_cast<RenderComponent*>( mObject );

		// mat count
		SizeT count = pRenderCom->GetMaterialCount();
		pSerialize->SerializeInt(s_MaterialCount , count );

		for ( IndexT iMat = 0; iMat < count; ++iMat )
		{
			// mat id
			const Resources::ResourceId& matID = pRenderCom->GetMaterialID(iMat);
			n_assert( matID.IsValid() );
			pSerialize->SerializeString(s_MaterialID, matID.AsString());
		}

		// receive shadow
		bool b = pRenderCom->GetReceiveShadow();
		pSerialize->SerializeBool(s_ReceiveShadow, b);
		bool castShadow = pRenderCom->GetCastShadow();
		pSerialize->SerializeBool(s_CastShadow, castShadow);
	}
}

namespace App
{
	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version RenderComponent::GetVersion() const
	{
		//return 1;	  //  当前版本号是1
		//return 2;   //  引入材质概念，存材质id
		//return 3;	  //  引入Receive Shadow
		//return 4;     //  引入Cast Shadow
		//return 5;      //天空盒不保存材质
		return 6;       //skybox 修改不合理代码
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void RenderComponent::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		pReader->SerializeSuper<Super>(this, args);
		RenderComponentSerialization Serialize(this);
		Serialize.Load( ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void RenderComponent::Save( AppWriter* pWriter ) const
	{
		pWriter->SerializeSuper<Super>(this);
		RenderComponentSerialization Serialize(this);
		Serialize.Save( pWriter );
	}

}

