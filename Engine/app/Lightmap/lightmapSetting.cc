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
#include "lightmapSetting.h"
#include "rendersystem/base/RenderDeviceTypes.h"
#include "app/appframework/actormanager.h"
#include "app/graphicfeature/components/meshrendercomponent.h"
#include "app/terrainfeature/components/TerrainRenderComponent.h"

namespace App
{

	//------------------------------------------------------------------------
	LightmapSetting::LightmapSetting()
	{
	}

	//------------------------------------------------------------------------
	LightmapSetting::~LightmapSetting()
	{
		ClearLightmapInfos();
	}
	//------------------------------------------------------------------------
	RenderBase::TextureHandle LightmapSetting::GetLightmapTexHandle(int lightmapIndex)
	{
		Resources::ResourceId lightmapID = Resources::ResourceManager::DefaultTextureID;
		RenderBase::TextureHandle  lightmapHandle;

		IndexT indexOfName = indexToName.FindIndex( lightmapIndex );

		if ( indexOfName != InvalidIndex)
		{
			lightmapID = indexToName.ValueAtIndex( indexOfName );

			IndexT findtex = m_LightmapInfos.FindIndex( lightmapID );

			GPtr<Resources::TextureResInfo> texRI;

			if ( findtex != InvalidIndex )
			{
				texRI = m_LightmapInfos.ValueAtIndex(findtex);

				n_assert(texRI->GetResID() == lightmapID);
			}
			else
			{
				// it is Synchronization ,that is used by editor;
				texRI = Resources::ResourceManager::Instance()->CreateTextureInfo(lightmapID,0);
				m_LightmapInfos.Add(lightmapID,texRI);
			}
			// Do this use Default Resource.
			if ( !texRI->IsDefaultResUsed() )
			{
				lightmapHandle = texRI->GetHandle();
			}
		}
		
		return lightmapHandle;
	}

	void LightmapSetting::ClearLightmapInfos()
	{
		m_LightmapInfos.Clear();
		indexToName.Clear();
	}

#ifdef __GENESIS_EDITOR__
	void LightmapSetting::UpdateLightmaps()
	{
		LightMapInfos::Iterator itBegin = m_LightmapInfos.Begin();
		LightMapInfos::Iterator itEnd = m_LightmapInfos.End();

		for (; itBegin != itEnd; ++itBegin)
		{
			Resources::ResourceId resID = itBegin->Key();
			// reflush the lightmap texture
			Resources::ResourceManager::Instance()->UpdateTexResource( resID );
		}

		// refresh all components that used lightmap
		App::ActorManager* pActorMgr = App::ActorManager::Instance();
		Util::Array<GPtr<App::MeshRenderComponent>> pMeshRenderComponents;

		SizeT componentCounts = pActorMgr->GetAllActorComponents(pMeshRenderComponents);
		for ( IndexT i = 0; i < componentCounts; ++i )
		{
			GPtr<App::MeshRenderComponent>& pMeshRenderComponent = pMeshRenderComponents[i];

			if ( pMeshRenderComponent->IsUseLM() )
			{
				pMeshRenderComponent->SetLMDirty();
			}
		}

		Util::Array<GPtr<App::TerrainRenderComponent>> pTerrainRenderComponents;

		componentCounts = pActorMgr->GetAllActorComponents(pTerrainRenderComponents);
		for ( IndexT i = 0; i < componentCounts; ++i )
		{
			GPtr<App::TerrainRenderComponent>& pTerrainRenderComponent = pTerrainRenderComponents[i];

			if ( pTerrainRenderComponent->IsUseLM() )
			{
				pTerrainRenderComponent->SetLMDirty();
			}
		}
	}

	void LightmapSetting::UpdateSingleLightmap(Resources::ResourceId resID)
	{
		//index can be used when lightmap files is useless ,for recoveing when delete lightmap files;
		LightmapIndexToName::Iterator itBegin = indexToName.Begin();
		LightmapIndexToName::Iterator itEnd = indexToName.End();
		unsigned int lightmapIndex = 0xFFFF;

		for (; itBegin != itEnd; ++itBegin)
		{
			Resources::ResourceId currentResID = itBegin->Value();

			if (currentResID == resID)
			{
				lightmapIndex = itBegin->Key();
				break;
			}
		}

		if (0xFFFF == lightmapIndex)
		{
			// we dont use this resource
			return;
		}
		
		// refresh all meshRenderComponent that use this lightmap
		App::ActorManager* pActorMgr = App::ActorManager::Instance();
		Util::Array<GPtr<App::MeshRenderComponent>> pMeshRenderComponents;

		SizeT componentCounts = pActorMgr->GetAllActorComponents(pMeshRenderComponents);
		for ( IndexT i = 0; i < componentCounts; ++i )
		{
			GPtr<App::MeshRenderComponent>& pMeshRenderComponent = pMeshRenderComponents[i];
			bool bEnableLightmap = pMeshRenderComponent->IsUseLM();

			if ( pMeshRenderComponent->IsUseLM() )
			{
				unsigned int  currLightmapIndex = pMeshRenderComponent->GetLMIndex();

				if (currLightmapIndex == lightmapIndex)
				{
					pMeshRenderComponent->SetLMDirty();
				}
			}
		}

		// refresh all terrainRenderComponent that use this lightmap
		Util::Array<GPtr<App::TerrainRenderComponent>> pTerrainRenderComponents;

		componentCounts = pActorMgr->GetAllActorComponents(pTerrainRenderComponents);

		for ( IndexT i = 0; i < componentCounts; ++i )
		{
			GPtr<App::TerrainRenderComponent>& pTerrainRenderComponent = pTerrainRenderComponents[i];
			bool bEnableLightmap = pTerrainRenderComponent->IsUseLM();

			if ( pTerrainRenderComponent->IsUseLM() )
			{
				unsigned int  currLightmapIndex = pTerrainRenderComponent->GetLMIndex();

				if (currLightmapIndex == lightmapIndex)
				{
					pTerrainRenderComponent->SetLMDirty();
				}
			}
		}

	}
#endif
	void LightmapSetting::SetLightmap(int lightmapIndex,Util::String & lightmapName)
	{
		IndexT indexOfName = indexToName.FindIndex( lightmapIndex );

		if ( indexOfName != InvalidIndex)
		{
			LightmapIndexToName::key_value_pair_type & pair = indexToName.KeyValuePairAtIndex( indexOfName );
			pair.Value() = lightmapName;
		}
		else
		{
			indexToName.Add(lightmapIndex, lightmapName);
		}
	}

	void LightmapSetting::GetLightmap( int lightmapIndex, LightmapName &LightmapName ) const
	{
		IndexT indexOfName = indexToName.FindIndex( lightmapIndex );

		if ( indexOfName != InvalidIndex )
		{
			LightmapIndexToName::key_value_pair_type& pair = indexToName.KeyValuePairAtIndex( indexOfName );
			LightmapName = pair.Value();
		}
	}

}