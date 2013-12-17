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
#include "vegetation/VegetationObejct.h"

namespace Vegetation
{
	using namespace Serialization;

	const char* s_vegeInstanceFilePath = "InstanceFilePath";
	const char* s_vegeRenderType = "RenderType";
	const char* s_vegeRotation = "LocalRot";
	const char* s_vegeScale = "LocalScale";

	const char* s_vegeMeshID = "MeshID";
	const char* s_vegeMeshDummy = "EmptyNull";
	const char* s_vegeHWInstance = "HardWareInstance";

	const char* s_vegeShaderCount = "ShaderCount";
	const char* s_vegeShaderID = "ShaderID";
	const char* s_vegeTextureCount = "TextureCount";
	const char* s_vegeTextureParamName = "TextureParam";
	const char* s_vegeTextureID = "TextureID";
	const char* s_vegeDummyID = "EmptyNull";
	const char* s_vegeConstantParamCount = "ConstantParamCount";
	const char* s_vegeConstantParamName = "ConstantParamName";
	const char* s_vegeConstantParamValue = "ConstantParamValue";

	const char* s_MaterialCount = "MaterialCount";
	const char* s_MaterialID = "MaterialID";

	class VegetationObjectSerialization
	{
	public:
		//------------------------------------------------------------------------
		void Load( VegetationObject* obj,  SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
		{
			if ( 1 == ver )
			{
				Load_1(obj, pReader, args);
				return;
			}
			else if ( 2 == ver )
			{
				Load_2(obj, pReader, args);
				return;
			}
			else if ( 3 == ver )
			{
				Load_3(obj, pReader, args);
				return;
			}
			n_error(" %s Load unknown version.\n", obj->GetClassName().AsCharPtr() );
		}
		//------------------------------------------------------------------------
		void Load_1(VegetationObject* obj, SerializeReader* pReader, const Serialization::SerializationArgs* args)
		{

			Util::String filePath;
			pReader->SerializeString(s_vegeInstanceFilePath, filePath);
			obj->SetInstanceFilePath(filePath);

			int ntype ;
			pReader->SerializeInt(s_vegeRenderType, ntype);
			obj->SetRenderType( (RenderType)ntype );

			float angle = 0;
			pReader->SerializeFloat(s_vegeRotation, angle);
			float _y = angle * N_PI_DOUBLE / 360.0f;
			Math::quaternion quat = Math::quaternion::rotationyawpitchroll(_y,0,0);
			obj->SetRotation(quat);

			float s = 1;
			pReader->SerializeFloat(s_vegeScale, s);
			Math::vector scale(s, s, s);
			obj->SetScale(scale);

			//GPtr<VegetationBrush>& vegeBrush = pReader->SerializeObject<VegetationBrush>();
			//obj->SetBrush(vegeBrush);
			Util::String meshID;
			pReader->SerializeString(s_vegeMeshID, meshID);


			if ( meshID != s_vegeDummyID )
			{
				obj->SetMeshID(meshID);
			}

			int ncount ;
			pReader->SerializeInt(s_vegeShaderCount, ncount);

			for ( int i = 0; i< ncount; ++i )
			{
				Util::String shaderID;
				pReader->SerializeString( s_vegeShaderID, shaderID );
				obj->SetShaderID(i, shaderID );

				int ntextcount ;
				pReader->SerializeInt(s_vegeTextureCount, ntextcount);
				for ( IndexT iTex = 0 ;iTex < ntextcount; ++iTex )
				{
					Util::String texParam;
					pReader->SerializeString( s_vegeTextureParamName, texParam );

					Util::String textureID;
					pReader->SerializeString( s_vegeTextureID, textureID );

					obj->SetTexture(i, texParam, textureID );
				}
			}
		}

		void Load_2(VegetationObject* obj, SerializeReader* pReader, const Serialization::SerializationArgs* args)
		{

			Util::String filePath;
			pReader->SerializeString(s_vegeInstanceFilePath, filePath);
			obj->SetInstanceFilePath(filePath);

			int ntype ;
			pReader->SerializeInt(s_vegeRenderType, ntype);
			obj->SetRenderType( (RenderType)ntype );

			Math::float4 quat;
			pReader->SerializeFloat4(s_vegeRotation, quat);
			obj->SetRotation(Math::quaternion(quat));

			Math::float4 scale;
			pReader->SerializeFloat4(s_vegeScale, scale);
			obj->SetScale(scale);

			//GPtr<VegetationBrush>& vegeBrush = pReader->SerializeObject<VegetationBrush>();
			//obj->SetBrush(vegeBrush);
			Util::String meshID;
			pReader->SerializeString(s_vegeMeshID, meshID);


			if ( meshID != s_vegeDummyID )
			{
				obj->SetMeshID(meshID);
			}

			int ncount ;
			pReader->SerializeInt(s_vegeShaderCount, ncount);

			for ( int i = 0; i< ncount; ++i )
			{
				Util::String shaderID;
				pReader->SerializeString( s_vegeShaderID, shaderID );
				obj->SetShaderID(i, shaderID );

				int ntextcount ;
				pReader->SerializeInt(s_vegeTextureCount, ntextcount);
				for ( IndexT iTex = 0 ;iTex < ntextcount; ++iTex )
				{
					Util::String texParam;
					pReader->SerializeString( s_vegeTextureParamName, texParam );

					Util::String textureID;
					pReader->SerializeString( s_vegeTextureID, textureID );

					obj->SetTexture(i, texParam, textureID );
				}
			}


		}
		//------------------------------------------------------------------------
		void Load_3(VegetationObject* obj, SerializeReader* pReader, const Serialization::SerializationArgs* args)
		{

			Util::String filePath;
			pReader->SerializeString(s_vegeInstanceFilePath, filePath);
			obj->SetInstanceFilePath(filePath);

			int ntype ;
			pReader->SerializeInt(s_vegeRenderType, ntype);
			obj->SetRenderType( (RenderType)ntype );

			Math::float4 quat;
			pReader->SerializeFloat4(s_vegeRotation, quat);
			obj->SetRotation(Math::quaternion(quat));

			Math::float4 scale;
			pReader->SerializeFloat4(s_vegeScale, scale);
			obj->SetScale(scale);

			//GPtr<VegetationBrush>& vegeBrush = pReader->SerializeObject<VegetationBrush>();
			//obj->SetBrush(vegeBrush);
			Util::String meshID;
			pReader->SerializeString(s_vegeMeshID, meshID);


			if ( meshID != s_vegeDummyID )
			{
				obj->SetMeshID(meshID);
			}

			int ncount ;
			pReader->SerializeInt(s_MaterialCount, ncount);

			for ( int i = 0; i< ncount; ++i )
			{
				Util::String matID;
				pReader->SerializeString( s_MaterialID, matID );
				n_assert( matID.IsValid() );
				obj->SetMaterialID(i, matID );
			}


		}
		//------------------------------------------------------------------------
		void Save( const VegetationObject* obj, SerializeWriter* pWriter )
		{
			Save_2(obj, pWriter);
		}
		//------------------------------------------------------------------------
		void Save_1( const VegetationObject* obj, SerializeWriter* pWriter )
		{

			//there will  only be saved by sceneFile, instaneData through vegeserver
			/***/
			pWriter->SerializeString(s_vegeInstanceFilePath, obj->GetInstanceFilePath());
			pWriter->SerializeInt(s_vegeRenderType, (int)obj->GetRenderType());
			Math::quaternion qRot = obj->GetRotation();
			Math::float4 fRot = Math::float4(qRot.x(),qRot.y(),qRot.z(),qRot.w());
			pWriter->SerializeFloat4(s_vegeRotation, fRot);
			pWriter->SerializeFloat4(s_vegeScale, obj->GetScale());

			//const GPtr<VegetationBrush>& pVegeBrush = obj->GetBrush();
			//pWriter->SerializeObject(pVegeBrush);
			if ( obj->GetMeshID().IsValid() )
			{
				pWriter->SerializeString(s_vegeMeshID, obj->GetMeshID().AsString() );
			}
			else
			{
				// can not Serialize empty string
				pWriter->SerializeString(s_vegeMeshID, Util::String(s_vegeMeshDummy) );
			}	

			// shader count
			SizeT count = obj->GetShaderCount();
			pWriter->SerializeInt(s_vegeShaderCount , count );

			for ( IndexT iShader = 0; iShader < count; ++iShader )
			{
				// shader id

				const Resources::ResourceId& shaderID = obj->GetShaderID(iShader);
				n_assert( shaderID.IsValid() );
				pWriter->SerializeString(s_vegeShaderID, shaderID.AsString());

				const GPtr<Graphic::MaterialInstance>& curMat = obj->GetMaterial(iShader);
				// texture param
				SizeT texParamCount = curMat->GetTextureParamCount();
				pWriter->SerializeInt(s_vegeTextureCount, texParamCount );
				for ( IndexT iTex = 0; iTex < texParamCount; ++iTex )
				{
					const Vegetation::ShaderParamString& paramName =  obj->GetTextureName(iShader, iTex);

					n_assert( paramName.IsValid() );
					pWriter->SerializeString( s_vegeTextureParamName, paramName.AsString());

					const Resources::ResourceId& texID = obj->GetTexture(iShader,paramName);
					n_assert( texID.IsValid() );
					pWriter->SerializeString( s_vegeTextureID, texID.AsString());
				}
			}
		}
		//------------------------------------------------------------------------
		void Save_2( const VegetationObject* obj, SerializeWriter* pWriter )
		{

			//there will  only be saved by sceneFile, instaneData through vegeserver
			/***/
			pWriter->SerializeString(s_vegeInstanceFilePath, obj->GetInstanceFilePath());
			pWriter->SerializeInt(s_vegeRenderType, (int)obj->GetRenderType());
			Math::quaternion qRot = obj->GetRotation();
			Math::float4 fRot = Math::float4(qRot.x(),qRot.y(),qRot.z(),qRot.w());
			pWriter->SerializeFloat4(s_vegeRotation, fRot);
			pWriter->SerializeFloat4(s_vegeScale, obj->GetScale());

			if ( obj->GetMeshID().IsValid() )
			{
				pWriter->SerializeString(s_vegeMeshID, obj->GetMeshID().AsString() );
			}
			else
			{
				// can not Serialize empty string
				pWriter->SerializeString(s_vegeMeshID, Util::String(s_vegeMeshDummy) );
			}	

			// mat count
			SizeT count = obj->GetMaterialCount();
			pWriter->SerializeInt(s_MaterialCount , count );

			for ( IndexT iMat = 0; iMat < count; ++iMat )
			{
				// mat id
				const Resources::ResourceId& matID = obj->GetMaterialID(iMat);
				n_assert( matID.IsValid() );
				pWriter->SerializeString(s_MaterialID, matID.AsString());
			}
		}

	};

	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	SVersion VegetationObject::GetVersion() const
	{
		return 3; //current version is 3, change shader to material
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void VegetationObject::Load( SVersion ver, SerializeReader* pReader, const Serialization::SerializationArgs* args )
	{
		VegetationObjectSerialization Serialize;
		Serialize.Load( this, ver, pReader, args );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void VegetationObject::Save( SerializeWriter* pWriter ) const
	{
		VegetationObjectSerialization Serialize;
		Serialize.Save( this, pWriter );
	}
	//------------------------------------------------------------------------
	void VegetationObject::CopyFrom( const GPtr<VegetationObject>& obj )
	{
		if( !obj.isvalid()  )
			return;

		SetRenderType(obj->GetRenderType());
		SetInstanceFilePath(obj->GetInstanceFilePath());

		//const GPtr<VegetationBrush>& pVegeBrush = obj->GetBrush();	
		//if ( !this->mVegeBrush.isvalid())
		//{
		//	this->mVegeBrush = VegetationBrush::Create();
		//}
		//this->mVegeBrush->CopyFrom(pVegeBrush);

		// instance
		const GPtr<VegeInstanceMap>& pVegeInstMap = obj->GetInstanceMap();
		if ( this->mInstMap )
		{
		}
		CreateInstanceMap();
		this->mInstMap->CopyFrom(pVegeInstMap);
	}

}
