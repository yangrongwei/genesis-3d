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
#include "app/appframework/gameapplication.h"
#include "app/appframework/actor.h"

#include "app/appframework/actormanager.h"
#include "app/appframework/component.h"
#include "app/appframework/scene.h"
#include "app/basegamefeature/managers/gameconfigmanger.h"
#include "app/graphicfeature/components/cameracomponent.h"
#include "app/graphicfeature/components/lightcomponent.h"
#include "app/graphicfeature/components/meshrendercomponent.h"
#include "app/graphicfeature/components/skeletoncomponent.h"
#include "app/graphicfeature/components/animationcomponent.h"
#include "app/graphicfeature/components/skinnedmeshrendercomponent.h"
#include "app/graphicfeature/components/spriterendercomponent.h"
#include "app/scriptfeature/inc/script_component.h"
#include "app/scriptfeature/mono_script.h"
#include "app/scriptfeature/mono_script_manager.h"
#include "app/scriptfeature/script_general_manager.h"
#include "app/scriptfeature/inc/script_instance.h"
#include "app/graphicfeature/components/projectorcomponent.h"
#include "soundfeature/components/SoundSourceComponent.h"
#include "soundfeature/components/SoundListenerComponent.h"
#include "app/vegetationfeature/components/vegetationrendercomponent.h"
#include "app/terrainfeature/components/TerrainRenderComponent.h"
#include "app/graphicfeature/components/simpleskycomponent.h"

namespace App
{
	void GameApplication::_RegisterDynamicClass() const
	{
		Actor::RegisterWithFactory();
		ActorManager::RegisterWithFactory();
		Component::RegisterWithFactory();
		Scene::RegisterWithFactory();
		GameConfigManager::RegisterWithFactory();
		CameraComponent::RegisterWithFactory();
		LightComponent::RegisterWithFactory();
		MeshRenderComponent::RegisterWithFactory();
		SkeletonComponent::RegisterWithFactory();
		AnimationComponent::RegisterWithFactory();
		SkinnedMeshRenderComponent::RegisterWithFactory();
		//SkyComponent::RegisterWithFactory();
		SpriteRenderComponent::RegisterWithFactory();
#ifndef __SCRIPT_COMMIT__
		ScriptComponent::RegisterWithFactory();
		MonoScript::RegisterWithFactory();
		MonoScriptManager::RegisterWithFactory();
		ScriptGeneralManager::RegisterWithFactory();
		ScriptInstance::RegisterWithFactory();
#endif
		VegetationRenderComponent::RegisterWithFactory();
#ifndef __PROJECTOR_COMMIT__ 
		ProjectorRenderComponent::RegisterWithFactory();
#endif
#ifndef __SOUND_COMMIT__

        SoundSource::RegisterWithFactory();
        SoundListener::RegisterWithFactory();
#endif
		TerrainRenderComponent::RegisterWithFactory();
		SimpleSkyComponent::RegisterWithFactory();
	}
}


