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
#include "appframework/scene.h"
#include "appframework/actormanager.h"
#include "graphicsystem/Material/GlobalShaderParam.h"
#include "Material/Material.h"
#include "physXfeature/physicsCore/PhysicsServer.h"
#include "graphicsystem/GraphicObjectManager.h"
#include "Material/MaterialManager.h"
#include "lightmap/lightmapSetting.h"

namespace App
{
	class SceneSerialization
	{
	public:
		SceneSerialization( const Scene* pScene )
			:mObject(pScene)
		{

		}
		inline void Load( Version ver, AppReader* pReader )
		{
			if ( 1 == ver )
			{
				Load_1(pReader);
				return;
			}
			if (2 == ver)
			{
				Load_2(pReader);
				return;
			}
			if (3 == ver)
			{
				Load_3(pReader);
				return;
			}
			if (4 == ver)
			{
				Load_4(pReader);
				return;
			}
			if (5 == ver)
			{
				Load_5(pReader);
				return;
			}
			if (6 == ver)
			{
				Load_6(pReader);
				return;
			}
			if (7 == ver)
			{
				Load_7(pReader);
				return;
			}
			if (8 == ver)
			{
				Load_8(pReader);
				return;
			}
			if (9 == ver)
			{
				Load_9(pReader);
				return;
			}
			else
			{
				n_error(" SceneSerialization::Load unknonw version " );
			}
		}

		void Load_1( AppReader* pReader );
		void Load_2( AppReader* pReader );
		void Load_3( AppReader* pReader );
		void Load_4( AppReader* pReader );
		void Load_5(AppReader* pSerialize);
		void Load_6(AppReader* pSerialize);
		void Load_7(AppReader* pSerialize);
		void Load_8(AppReader* pSerialize);
		void Load_9(AppReader* pSerialize);
		void Save( AppWriter* pWriter );
	protected:
		const Scene* mObject;


	};

	const char* s_SceneName = "SceneName";
	const char* s_ChildActorCount = "ChildActorCount";
	const char* s_GShaderVecFogColor = "eGShaderVecFogColor";
	const char* s_GShaderVecFogParam = "eGShaderVecFogParam";
	const char* s_GShaderVecAmbientColor = "eGShaderVecAmbientColor";
	const char* s_phyxLayerFilterIntArray = "phyxLayerFilterIntArray";
	const char* s_SoftShadowParam = "eGShaderVecShaowParam";
	const char* s_ShadowStrength = "eGShaderVecShadowStrength";
	const char* s_Gravity = "phyxGravity";
	const char* s_SkinWidth = "phyxSkinWidth";
	const char* s_BounceThreshold = "phyxBounceThreshold";
	const char* s_SleepVelocity = "phyxSleepVelocity";
	const char* s_SleepAngularVelocity = "phyxSleepAngularVelocity";
	const char* s_MaxAngularVelocity = "phyxMaxAngularVelocity";
	const char* s_DefaultMaterial = "phyxDefaultMaterial";
	//------------------------------------------------------------------------
	void SceneSerialization::Load_1(AppReader* pSerialize)
	{
		Scene* pScene = const_cast<Scene*>( mObject );

		//scene data
		{
			pSerialize->SerializeString( s_SceneName,   pScene->mName );
		}
	}

	//------------------------------------------------------------------------------
	void SceneSerialization::Load_2(AppReader* pSerialize)
	{
		Scene* pScene = const_cast<Scene*>( mObject );

		//scene data
		{
			pSerialize->SerializeString( s_SceneName,   pScene->mName );
		}

		// global shader param
		{
			Math::float4 fogColor;
			Math::float4 fogParam;
			pSerialize->SerializeFloat4(s_GShaderVecFogColor, fogColor);
			pSerialize->SerializeFloat4(s_GShaderVecFogParam, fogParam);
			Graphic::GlobalMaterialParam* globalMaterialParam = Graphic::Material::GetGlobalMaterialParams();
			if (globalMaterialParam)
			{
				globalMaterialParam->SetVectorParam(Graphic::eGShaderVecFogColor, fogColor);
				globalMaterialParam->SetVectorParam(Graphic::eGShaderVecFogParam, fogParam);
			}
			else
			{
				n_warning("WARNING! GlobalMaterialParam is null.");
			}
		}
	}

	//------------------------------------------------------------------------------
	void SceneSerialization::Load_3(AppReader* pSerialize)
	{
		Scene* pScene = const_cast<Scene*>( mObject );

		//scene data
		{
			pSerialize->SerializeString( s_SceneName,   pScene->mName );
		}
		// global shader param
		{
			Math::float4 fogColor;
			Math::float4 fogParam;
			Math::float4 ambientColor;
			pSerialize->SerializeFloat4(s_GShaderVecAmbientColor, ambientColor);
			pSerialize->SerializeFloat4(s_GShaderVecFogColor, fogColor);
			pSerialize->SerializeFloat4(s_GShaderVecFogParam, fogParam);
			Graphic::GlobalMaterialParam* globalMaterialParam = Graphic::Material::GetGlobalMaterialParams();
			if (globalMaterialParam)
			{
				globalMaterialParam->SetVectorParam(Graphic::eGShaderVecAmbientColor, ambientColor);
				globalMaterialParam->SetVectorParam(Graphic::eGShaderVecFogColor, fogColor);
				globalMaterialParam->SetVectorParam(Graphic::eGShaderVecFogParam, fogParam);
			}
			else
			{
				n_warning("WARNING! GlobalMaterialParam is null.");
			}
		}
	}

	//------------------------------------------------------------------------------
	void SceneSerialization::Load_4(AppReader* pSerialize)
	{
		Scene* pScene = const_cast<Scene*>( mObject );

		//scene data
		{
			pSerialize->SerializeString( s_SceneName,   pScene->mName );
		}

		// global shader param
		{
			pSerialize->SerializeFloat4(s_GShaderVecAmbientColor, pScene->mEnvironment.ambientColor);
			pSerialize->SerializeFloat4(s_GShaderVecFogColor, pScene->mEnvironment.fogColor);
			pSerialize->SerializeFloat4(s_GShaderVecFogParam, pScene->mEnvironment.fogParam);
			Graphic::GlobalMaterialParam* globalMaterialParam = Graphic::Material::GetGlobalMaterialParams();
			if (globalMaterialParam)
			{
				globalMaterialParam->SetVectorParam(Graphic::eGShaderVecAmbientColor, pScene->mEnvironment.ambientColor);
				globalMaterialParam->SetVectorParam(Graphic::eGShaderVecFogColor, pScene->mEnvironment.fogColor);
				globalMaterialParam->SetVectorParam(Graphic::eGShaderVecFogParam, pScene->mEnvironment.fogParam);
			}
			else
			{
				n_warning("WARNING! GlobalMaterialParam is null.");
			}
		}

		// phyx layer filter load
		{

			Util::Array<uint> layerIDArray;
			Util::String strName;
			for ( int i = 0; i < 32; i++ )
			{
				strName.Format("%s_%d",s_phyxLayerFilterIntArray,i);
				uint val(1);
				pSerialize->SerializeUInt(strName.Get(),val);
				layerIDArray.Append(val);
			}

			if ( layerIDArray.Size() != 32 )
			{
				n_assert(0);
			}
			else
			{
#if __WIN32__

				PhysicsServer::Instance()->SetAllCollisionMaskMatrix( layerIDArray );
#endif
			}
		}


	}

	//------------------------------------------------------------------------------
	void SceneSerialization::Load_5(AppReader* pSerialize)
	{
		Scene* pScene = const_cast<Scene*>( mObject );

		//scene data
		{
			pSerialize->SerializeString( s_SceneName,   pScene->mName );
		}

		// global shader param
		{

			pSerialize->SerializeFloat4(s_GShaderVecAmbientColor, pScene->mEnvironment.ambientColor);
			pSerialize->SerializeFloat4(s_GShaderVecFogColor, pScene->mEnvironment.fogColor);
			pSerialize->SerializeFloat4(s_GShaderVecFogParam, pScene->mEnvironment.fogParam);
			pSerialize->SerializeFloat4(s_SoftShadowParam, pScene->mEnvironment.softShadowParam);
			pSerialize->SerializeFloat4(s_ShadowStrength, pScene->mEnvironment.shadowStrength);
		}

		// phyx layer filter load
		{

			//Util::Array<uint> layerIDArray;
			Util::String strName;
			pScene->mEnvironment.layerIDArray.Clear();
			for ( int i = 0; i < 32; i++ )
			{
				strName.Format("%s_%d",s_phyxLayerFilterIntArray,i);
				uint val(1);
				pSerialize->SerializeUInt(strName.Get(),val);
				pScene->mEnvironment.layerIDArray.Append(val);
			}
		}


	}
	//------------------------------------------------------------------------
	void SceneSerialization::Load_6(AppReader* pSerialize)
	{
		Load_5(pSerialize);

		Scene* pScene = const_cast<Scene*>( mObject );
		//Math::float3 graivty;
		pSerialize->SerializeFloat3(s_Gravity, pScene->mEnvironment.graivty);


		//float skinWidth;
		pSerialize->SerializeFloat(s_SkinWidth, pScene->mEnvironment.skinWidth);


		//float bounce;
		pSerialize->SerializeFloat(s_BounceThreshold, pScene->mEnvironment.bounce);


		//float sleepVel;
		pSerialize->SerializeFloat(s_SleepVelocity, pScene->mEnvironment.sleepVel);


		//float sleepAngular;
		pSerialize->SerializeFloat(s_SleepAngularVelocity, pScene->mEnvironment.sleepAngular);


		//float maxAngular;
		pSerialize->SerializeFloat(s_MaxAngularVelocity, pScene->mEnvironment.maxAngular);

	}

	void SceneSerialization::Load_7(AppReader* pSerialize)
	{
		Load_5(pSerialize);

		Scene* pScene = const_cast<Scene*>( mObject );
		//Math::float3 graivty;
		pSerialize->SerializeFloat3(s_Gravity, pScene->mEnvironment.graivty);


		//float skinWidth;
		pSerialize->SerializeFloat(s_SkinWidth, pScene->mEnvironment.skinWidth);


		//float bounce;
		pSerialize->SerializeFloat(s_BounceThreshold, pScene->mEnvironment.bounce);


		//float sleepVel;
		pSerialize->SerializeFloat(s_SleepVelocity, pScene->mEnvironment.sleepVel);


		//float sleepAngular;
		pSerialize->SerializeFloat(s_SleepAngularVelocity, pScene->mEnvironment.sleepAngular);


		//float maxAngular;
		pSerialize->SerializeFloat(s_MaxAngularVelocity, pScene->mEnvironment.maxAngular);

		//Util::String defaultMat;
		pSerialize->SerializeString(s_DefaultMaterial, pScene->mEnvironment.defaultMat);

	}
	//------------------------------------------------------------------------
	void SceneSerialization::Load_8(AppReader* pSerialize)
	{
		Load_5(pSerialize);

		Scene* pScene = const_cast<Scene*>( mObject );
		//Math::float3 graivty;
		pSerialize->SerializeFloat3(s_Gravity, pScene->mEnvironment.graivty);


		//float skinWidth;
		pSerialize->SerializeFloat(s_SkinWidth, pScene->mEnvironment.skinWidth);


		//float bounce;
		pSerialize->SerializeFloat(s_BounceThreshold, pScene->mEnvironment.bounce);


		//float sleepVel;
		pSerialize->SerializeFloat(s_SleepVelocity, pScene->mEnvironment.sleepVel);


		//float sleepAngular;
		pSerialize->SerializeFloat(s_SleepAngularVelocity, pScene->mEnvironment.sleepAngular);


		//float maxAngular;
		pSerialize->SerializeFloat(s_MaxAngularVelocity, pScene->mEnvironment.maxAngular);

		//Util::String defaultMat;
		pSerialize->SerializeString(s_DefaultMaterial, pScene->mEnvironment.defaultMat);

		// load lightmapInfo add by zhangjitao
		GPtr<LightmapFile> tplFile = pSerialize->SerializeObject<LightmapFile>();
	}
	void SceneSerialization::Load_9(AppReader* pSerialize)
	{
		Load_5(pSerialize);

		Scene* pScene = const_cast<Scene*>( mObject );
		//Math::float3 graivty;
		pSerialize->SerializeFloat3(s_Gravity, pScene->mEnvironment.graivty);

		//float skinWidth;
		pSerialize->SerializeFloat(s_SkinWidth, pScene->mEnvironment.skinWidth);

		//float sleepVel;
		pSerialize->SerializeFloat(s_SleepVelocity, pScene->mEnvironment.sleepVel);

		//float maxAngular;
		pSerialize->SerializeFloat(s_MaxAngularVelocity, pScene->mEnvironment.maxAngular);

		//Util::String defaultMat;
		pSerialize->SerializeString(s_DefaultMaterial, pScene->mEnvironment.defaultMat);
		
		// load lightmapInfo add by zhangjitao
		GPtr<LightmapFile> tplFile = pSerialize->SerializeObject<LightmapFile>();
	}
	//------------------------------------------------------------------------
	void SceneSerialization::Save(AppWriter* pSerialize)
	{
		const Scene* pScene = mObject;

		//name
		{
			pSerialize->SerializeString( s_SceneName,   pScene->mName );
		}

		// environment shader param
		{
			const Scene::Environment& environment = pScene->GetEnvironment();
			pSerialize->SerializeFloat4(s_GShaderVecAmbientColor, environment.ambientColor);
			pSerialize->SerializeFloat4(s_GShaderVecFogColor, environment.fogColor);
			pSerialize->SerializeFloat4(s_GShaderVecFogParam, environment.fogParam);
			pSerialize->SerializeFloat4(s_SoftShadowParam, environment.softShadowParam);
			pSerialize->SerializeFloat4(s_ShadowStrength, environment.shadowStrength);
		}
#if __WIN32__
		// phyx layer filter
		{
			Util::Array<uint> layerIDArray = PhysicsServer::Instance()->GetAllCollisionMask();
			if ( layerIDArray.Size() != 32 )
			{
				n_assert(0);
			}
			else
			{
				Util::String strName;
				for ( int i = 0; i < 32; i++ )
				{
					strName.Format("%s_%d",s_phyxLayerFilterIntArray,i);
					uint val = layerIDArray[i];
					pSerialize->SerializeUInt(strName.Get(),val);

				}
			}

		}

		//全局物理参数
		{
			const Math::float3& gravity = PhysicsServer::Instance()->GetGravity();
			pSerialize->SerializeFloat3(s_Gravity, gravity);

			const float skinWidth = 0.025f;//PhysicsServer::Instance()->GetMinPenetrationForPenalty();
			pSerialize->SerializeFloat(s_SkinWidth, skinWidth);//这块下个序列化版本需要删掉

			const float sleepVel = PhysicsServer::Instance()->GetSleepThreshold();
			pSerialize->SerializeFloat(s_SleepVelocity, sleepVel);

			const float maxAngular = PhysicsServer::Instance()->GetMaxAngularVelocity();
			pSerialize->SerializeFloat(s_MaxAngularVelocity, maxAngular);

			const Util::String defaultMat = PhysicsServer::Instance()->GetDefaultMaterial();
			pSerialize->SerializeString(s_DefaultMaterial, defaultMat);
		}
#endif
		// lightmap serialzie add by zhangjitao
		GPtr<LightmapFile> pLightmapFile = LightmapFile::Create();
		pSerialize->SerializeObject( pLightmapFile );

		// child actor
		{
			SizeT count = pScene->GetActorCount();
			pSerialize->SerializeInt( s_ChildActorCount, count );
			for ( IndexT index = 0; index < count; ++index )
			{
				const GPtr<Actor>& pActor = pScene->GetActor(index);
				n_assert(pActor.isvalid());
				pSerialize->SerializeObject( pActor );
			}
		}

		//// 没找到合适的地方，先放这儿了
		GPtr<Graphic::MaterialInstanceManager>& manager = GraphicObjectManager::Instance()->GetMaterialInstanceManager();
		if ( manager )
		{
			manager->SaveMaterial();
		}


	}
}

namespace App
{

	class SceneSerializationArgs : public Serialization::SerializationArgs
	{
	public:
		bool privateScene;
	};


	//------------------------------------------------------------------------
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	Version Scene::GetVersion() const
	{
		//return 3;	//	当前版本号是3
		//return 4;	//	增加物理碰撞过滤的序列化
		//return 5;	//	增加shader参数
		//return 6;   //  增加物理全局参数
		//return 7;	//增加全局物理DefaultMaterial
		//return 8; //增加lightmap信息
		return 9;//物理升级大改动
	}

	//------------------------------------------------------------------------
	// @ISerialization::Load 
	void Scene::Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args )
	{
		// before load, must Open First
		if (args)
		{
			bool pri = args->cast_fast<SceneSerializationArgs>()->privateScene;
			_Open(pri);
		}
		else
		{
			_Open(false);
		}

		SceneSerialization Serialize(this);
		Serialize.Load( ver, pReader );
	}

	//------------------------------------------------------------------------
	// @ISerialization::Save
	void Scene::Save( AppWriter* pWriter ) const
	{
		SceneSerialization Serialize(this);
		Serialize.Save( pWriter );
	}

	void Scene::_SerializeActorBegin()
	{
		n_assert(0 == mRoot->GetChildCount());
		mRoot->Deactive();
	}

	void Scene::_SerializeActorEnd()
	{
		mRoot->Active();
	}

	//------------------------------------------------------------------------
	void Scene::_Load(AppReader* pReader, GPtr<Scene>& scene, bool privateScene)
	{
		SceneSerializationArgs args;
		args.privateScene = privateScene;
		scene = pReader->SerializeObjectWidthOutEnd<Scene>(&args);
		if (!scene)
		{
			return;
		}
		scene->_SerializeActorBegin();
		// child actor
		{
			SizeT count;
			pReader->SerializeInt( s_ChildActorCount, count );

			if ( count != 0 )
			{
				ActorSerializationArgs args(scene->GetPtrRoot().get_unsafe());
				for ( IndexT index = 0; index < count; ++index)
				{
					GPtr<Actor> pActor = pReader->SerializeObject<Actor>(&args);
					//scene->AddActor( pActor );
				}
			}
		}
		scene->_SerializeActorEnd();
		pReader->EndSerializeObject();

	}

}


