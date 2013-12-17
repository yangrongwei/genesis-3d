#****************************************************************************
# Copyright (c) 2011-2013,WebJet Business Division,CYOU
#  
# http://www.genesis-3d.com.cn
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#****************************************************************************

##################################################################################
# Build app 
##################################################################################

#appframework folder
SET ( APPFRAMEWORK_HEADER_FILES 
	appframework/actor.h
	appframework/actormanager.h
	appframework/app_fwd_decl.h
	appframework/appconfig.h
	appframework/component.h
	appframework/feature.h
	appframework/feature_fwd_decl.h
	appframework/gameapplication.h
	appframework/gameserver.h
	appframework/manager.h
	appframework/serialization.h
	appframework/scene.h
	appframework/statehandler.h
	appframework/profiletool.h
)

#appframework folder
SET ( APPFRAMEWORK_SOURCE_FILES
	appframework/actor.cc
	appframework/actormanager.cc
	appframework/actormanagerserialization.cc
	appframework/actorserialization.cc
	appframework/appframeworkprotocol.cc
	appframework/component.cc
	appframework/component_force_compile.cc
	appframework/componentserialization.cc
	appframework/feature.cc
	appframework/gameapplication.cc
	appframework/gameserver.cc
	appframework/manager.cc
	appframework/serialization.cc
	appframework/scene.cc
	appframework/sceneserialization.cc
	appframework/statehandler.cc
	appframework/profiletool.cc
)

#apputil folder
SET ( APPUTIL_HEADER_FILES 
	apputil/intersectutil.h
	apputil/manuresutil.h
	apputil/mouserayutil.h
	apputil/shadowmaputil.h
)

#apputil folder
SET ( APPUTIL_SOURCE_FILES
	apputil/intersectutil.cc
	apputil/manuresutil.cc
	apputil/mouserayutil.cc
	apputil/shadowmaputil.cc
)

#lightmap folder
SET ( LIGHTMAP_HEADER_FILES 
	Lightmap/lightmapSetting.h
)

#lightmap folder
SET ( LIGHTMAP_SOURCE_FILES 
	Lightmap/lightmapSetting.cc
	Lightmap/lightMapSerialization.cc
)

#basegamefeature folder
SET ( BASEGAMEFEATURE_HEADER_FILES
	basegamefeature/managers/timesource.h
	basegamefeature/managers/timemanager.h
	basegamefeature/managers/sceneschedulemanager.h
	basegamefeature/managers/gameconfigmanger.h
	basegamefeature/basegamefeature.h
)

#basegamefeature folder
SET ( BASEGAMEFEATURE_SOURCE_FILES
	basegamefeature/managers/timesource.cc
	basegamefeature/managers/timemanager.cc
	basegamefeature/managers/sceneschedulemanager.cc
	basegamefeature/managers/gameconfigmanger.cc
	basegamefeature/basegamefeature.cc
)

#graphicfeature folder
SET ( GRAPHICFEATURE_HEADER_FILES 
	graphicfeature/components/apprenderable.h
	graphicfeature/components/skinnedrenderable.h

	graphicfeature/components/apprenderobject.h
	graphicfeature/components/meshrenderobject.h
	graphicfeature/components/skinnedrenderobject.h
	graphicfeature/components/screenmeshrenderobject.h
	graphicfeature/components/spriterenderobject.h

	graphicfeature/components/animationcomponent.h
	graphicfeature/components/cameracomponent.h
	graphicfeature/components/lightcomponent.h	
	graphicfeature/components/meshrendercomponent.h
	graphicfeature/components/spriterendercomponent.h
	graphicfeature/components/spritebaserendercomponent.h

	#graphicfeature/components/volumefogcomponent.h
	graphicfeature/components/mesh2drendercomponent.h
	graphicfeature/components/rendercomponent.h
	graphicfeature/components/skeletoncomponent.h
	#graphicfeature/components/volumefogrender.h
	graphicfeature/components/skinnedmeshrendercomponent.h
	graphicfeature/graphicsfeature.h
	graphicfeature/graphicsfeaturecomponents.h
	#graphicfeature/components/GoldenShineComponent.h
	graphicfeature/components/projectorcomponent.h
	graphicfeature/components/projectorrenderobject.h
	graphicfeature/components/simpleskycomponent.h
	graphicfeature/components/lightprobecomponent.h
	graphicfeature/components/locatercomponent.h
)

#graphicfeature folder
SET ( GRAPHICFEATURE_SOURCE_FILES
	graphicfeature/components/apprenderable.cc
	graphicfeature/components/skinnedrenderable.cc

	graphicfeature/components/apprenderobject.cc
	graphicfeature/components/meshrenderobject.cc
	graphicfeature/components/skinnedrenderobject.cc
	graphicfeature/components/screenmeshrenderobject.cc
	graphicfeature/components/spriterenderobject.cc

	graphicfeature/components/animationcomponent.cc
	graphicfeature/components/animationcomponentserialization.cc
	graphicfeature/components/cameracomponent.cc
	graphicfeature/components/cameracomponentserialization.cc
	graphicfeature/components/lightcomponent.cc
	graphicfeature/components/lightcomponentserialization.cc
	graphicfeature/components/meshrendercomponent.cc
	graphicfeature/components/spriterendercomponent.cc
	graphicfeature/components/spriterendercomponentserialization.cc
	graphicfeature/components/spritebaserendercomponent.cc
	graphicfeature/components/spritebaserendercomponentserialization.cc

	graphicfeature/components/mesh2drendercomponent.cc
	graphicfeature/components/meshrendercomponentserialization.cc
	graphicfeature/components/rendercomponent.cc
	graphicfeature/components/rendercomponentserialization.cc
	graphicfeature/components/skeletoncomponent.cpp
	graphicfeature/components/skeletoncomponentserialization.cc
	graphicfeature/components/skinnedmeshrendercomponent.cc
	graphicfeature/components/skinnedmeshrendercomponentserialization.cc
	graphicfeature/graphicsfeature.cc
	graphicfeature/components/projectorcomponent.cc
	graphicfeature/components/projectorrenderobject.cc
	graphicfeature/components/projectorcomponentserialization.cc
	graphicfeature/components/simpleskycomponent.cc
	graphicfeature/components/simpleskycomponentserialization.cc
	graphicfeature/components/lightprobecomponent.cc
	graphicfeature/components/locatercomponentserialization.cc
	graphicfeature/components/locatercomponent.cc
)

#inputfeature folder
SET ( INPUTFEATURE_HEADER_FILES 
	inputfeature/inputfeature.h
)

#inputfeature folder
SET ( INPUTFEATURE_SOURCE_FILES
	inputfeature/inputfeature.cc
)

#ALSystemFeature folder
SET ( ALSystemFeature_HEADER_FILES 
	ALSystemFeature/ALSystemFeature.h
	ALSystemFeature/GameIap.h
)

SET ( ALSystemFeature_SOURCE_FILES
	ALSystemFeature/ALSystemFeature.cc
	ALSystemFeature/GameIap.cc
)

#paticle folder
SET ( PATICLE_HEADER_FILES 
	particlefeature/components/particlerenderable.h
	particlefeature/components/particlerenderobject.h
	particlefeature/components/particlerendercomponent.h
	particlefeature/particlefeatureprotocol.h
	particlefeature/particlefeature.h
)

#paticle folder
SET ( PATICLE_SOURCE_FILES
	particlefeature/components/particlerenderable.cc
	particlefeature/components/particlerenderobject.cc
	particlefeature/components/particlerendercomponentserialization.cc
	particlefeature/components/particlerendercomponent.cc
	particlefeature/particlefeatureprotocol.cc
	particlefeature/particlefeature.cc
)

#vegetation folder
SET ( VEGETATION_HEADER_FILES 
	vegetationfeature/vegetationfeature.h
	vegetationfeature/vegetationfeatureprotocol.h	
	vegetationfeature/components/vegetationrendercomponent.h
)

#vegetation folder
SET ( VEGETATION_SOURCE_FILES
	vegetationfeature/vegetationfeature.cc
	vegetationfeature/vegetationfeatureprotocol.cc	
	vegetationfeature/components/vegetationrendercomponent.cc
	vegetationfeature/components/vegetationcomponentserialization.cc
)

#scriptfeature folder
SET ( SCRIPTFEATURE_HEADER_FILES 
	scriptfeature/mono_script_manager.h
	scriptfeature/mono_script.h
	scriptfeature/mono_icall_registration.h
	scriptfeature/script_general_manager.h
	scriptfeature/script_message_regist.h
	scriptfeature/editable_field_value.h
	scriptfeature/script_root_instance.h
	scriptfeature/script_IAP_instance.h
	scriptfeature/script_render_buffer_filter.h
)


#scriptfeature folder
SET ( SCRIPTFEATURE_SOURCE_FILES
	scriptfeature/script_utility.cc
	scriptfeature/script_component.cc
	scriptfeature/mono_script_manager.cc
	scriptfeature/mono_script.cc
	scriptfeature/mono_icall_registration.cc
	scriptfeature/script_general_manager.cc
	scriptfeature/script_instance.cc
	scriptfeature/script_message.cc
	scriptfeature/script_message_regist.cc
	scriptfeature/script_feature.cc
	scriptfeature/editable_field_value.cc
	scriptfeature/script_root_instance.cc
	scriptfeature/script_IAP_instance.cc
	scriptfeature/script_render_buffer_filter.cc
)

#scriptfeature inc folder
SET ( SCRIPTFEATURE_INC_HEADER_FILES 
	scriptfeature/inc/script_utility.h
	scriptfeature/inc/script_instance.h
	scriptfeature/inc/script_fwd_decl.h
	scriptfeature/inc/script_message.h
	scriptfeature/inc/script_feature.h
	scriptfeature/inc/script_component.h
)

#terrain folder
SET ( TERRAIN_HEADER_FILES 
	terrainfeature/components/TerrainRenderComponent.h
	terrainfeature/components/TerrainRenderObject.h
	terrainfeature/components/TerrainNode.h
	terrainfeature/components/TerrainNodeTree.h
	terrainfeature/components/TerrainNodeTraverser.h
	terrainfeature/components/TerrainNodeFrameTraverser.h
)

#terrain folder
SET ( TERRAIN_SOURCE_FILES
	terrainfeature/components/TerrainRenderComponent.cc
	terrainfeature/components/TerrainRenderComponentSerialization.cc
	terrainfeature/components/TerrainRenderObject.cc
	terrainfeature/components/TerrainNode.cc
	terrainfeature/components/TerrainNode_Tear_Reqular.cc
	terrainfeature/components/TerrainNodeTree.cc
	terrainfeature/components/TerrainNodeTraverser.cc
	terrainfeature/components/TerrainNodeFrameTraverser.cc
)

#AnimationFeature
SET ( ANIMATIONFEATURE_HEADER_FILES 
	
	animationfeature/AnimationFeature.h
)

#AnimationFeature
SET ( ANIMATIONFEATURE_SOURCE_FILES
	animationfeature/AnimationFeature.cc
)


#physXfeature folder
SET ( PHYSX_HEADER_FILES
	physXfeature/physicsCore/PhysicsDynamic.h
	physXfeature/physicsCore/PhysicsStatic.h
	physXfeature/physicsCore/PhysicsRole.h
	physXfeature/physicsCore/PhysicsEntity.h
	physXfeature/physicsCore/PhysicsBoxShape.h
	physXfeature/physicsCore/PhysicsMaterial.h
	physXfeature/physicsCore/PhysicsPlaneShape.h
	physXfeature/physicsCore/PhysicsShape.h
	physXfeature/physicsCore/PhysicsSphereShape.h
	physXfeature/physicsCore/PhysicsTerrian.h
	physXfeature/physicsCore/PhysicsCapsuleShape.h
	physXfeature/physicsCore/PhysicsMeshShape.h
	physXfeature/physicsCore/PhysicsConvexShape.h
	physXfeature/physicsCore/PhysicsServer.h
	physXfeature/physicsCore/PhysicsUtil.h
	physXfeature/physicsCore/UserStream.h
	physXfeature/physicsCore/PhysicsDeclaration.h

	physXfeature/physicsCore/PhysicsDynamic.cc
	physXfeature/physicsCore/PhysicsStatic.cc
	physXfeature/physicsCore/PhysicsRole.cc
	physXfeature/physicsCore/PhysicsEntity.cc
	physXfeature/physicsCore/PhysicsBoxShape.cc
	physXfeature/physicsCore/PhysicsMaterial.cc
	physXfeature/physicsCore/PhysicsPlaneShape.cc
	physXfeature/physicsCore/PhysicsShape.cc
	physXfeature/physicsCore/PhysicsSphereShape.cc
	physXfeature/physicsCore/PhysicsTerrian.cc
	physXfeature/physicsCore/PhysicsCapsuleShape.cc
	physXfeature/physicsCore/PhysicsMeshShape.cc
	physXfeature/physicsCore/PhysicsConvexShape.cc
	physXfeature/physicsCore/PhysicsServer.cc
	physXfeature/physicsCore/UserStream.cc
)
#sprite bacth folder
SET ( SPRITEBACTH_FILES 
	spritebacth/sprite.h
	spritebacth/spritebacth.cc
	spritebacth/spritebacth.h
	spritebacth/spriterenderable.cc
	spritebacth/spriterenderable.h
	spritebacth/statictext.cc
	spritebacth/statictext.h
	spritebacth/drawunit.cc
	spritebacth/drawunit.h
	spritebacth/debugboard.h
	spritebacth/debugboard.cc
	spritebacth/DrawTextManager.h
	spritebacth/DrawTextManager.cc
)

#ui system folder
SET ( GUIFEATURE_FILES
	guifeature/gui.h
	guifeature/guiserver.h
	guifeature/guiserver.cc
	guifeature/guiinputhandler.h
	guifeature/guiinputhandler.cc
	guifeature/win32guiinputhandler.h
	guifeature/win32guiinputhandler.cc
	guifeature/androidguiinputhandler.h
	guifeature/androidguiinputhandler.cc
	guifeature/guiroot.h
	guifeature/guiroot.cc
	guifeature/scriptgui.h
	guifeature/scriptgui.cc
	guifeature/guiutility.h
	guifeature/guiutility.cc
	guifeature/guievent.h
	guifeature/guievent.cc
	guifeature/FontFeature.h
	guifeature/FontFeature.cc
	
	
)
SET ( GUIBIND_FILES 
	guibind/scriptbind_gui.cc
	guibind/scriptbind_widget.cc
	guibind/scriptbind_textbox.cc
	guibind/scriptbind_window.cc
	guibind/scriptbind_tabitem.cc
	guibind/scriptbind_tabcontrol.cc
	guibind/scriptbind_scrollview.cc
	guibind/scriptbind_scrollbar.cc
	guibind/scriptbind_progressbar.cc
	guibind/scriptbind_popupmenu.cc
	guibind/scriptbind_multilistitem.cc
	guibind/scriptbind_multilistbox.cc
	guibind/scriptbind_menuitem.cc
	guibind/scriptbind_menucontrol.cc
	guibind/scriptbind_menubar.cc
	guibind/scriptbind_listbox.cc
	guibind/scriptbind_itembox.cc
	guibind/scriptbind_imagebox.cc
	guibind/scriptbind_editbox.cc
	guibind/scriptbind_ddcontainer.cc
	guibind/scriptbind_combobox.cc
	guibind/scriptbind_canvas.cc
	guibind/scriptbind_rendertarget.cc
	guibind/scriptbind_button.cc
	
)
#physXfeature folder
SET ( PHYSX_SOURCE_FILES
	physXfeature/PhysicsBodyComponent.h
	physXfeature/PhysicsFeature.h
	physXfeature/UserReport.h

	physXfeature/PhysicsBodyComponent.cc
	physXfeature/PhysicsBodyComponentSerialization.cc
	physXfeature/PhysicsFeature.cc
	physXfeature/UserReport.cc
)

#sound folder
SET ( SOUND_HEADER_FILES 
	soundfeature/SoundFeature.h
	soundfeature/SoundRes.h
	soundfeature/SoundTypes.h
	soundfeature/SoundSouceInfo.h
	soundfeature/components/SoundSourceComponent.h
	soundfeature/components/SoundListenerComponent.h
	soundfeature/components/SoundEchoFilterComponent.h
	soundfeature/components/SoundFilterComponent.h
	soundfeature/components/SoundLowPassFilterComponent.h
	soundfeature/components/SoundReverbFilterComponent.h
)

#sound folder
SET ( SOUND_SOURCE_FILES
	soundfeature/SoundFeature.cc
	soundfeature/SoundRes.cc
	soundfeature/components/SoundSourceComponent.cc
	soundfeature/components/SoundListenerComponent.cc
 	soundfeature/components/SoundSourceComponentSerialization.cc
	soundfeature/components/SoundListenerComponentSerialization.cc
	soundfeature/components/SoundEchoFilterComponent.cc
	soundfeature/components/SoundEchoFilterComponentSerialization.cc
	soundfeature/components/SoundFilterComponent.cc
	soundfeature/components/SoundLowPassFilterComponent.cc
	soundfeature/components/SoundLowPassFilterComponentSerialization.cc
	soundfeature/components/SoundReverbFilterComponent.cc
	soundfeature/components/SoundReverbFilterComponentSerialization.cc
)

#scriptbind folder 
SET ( SCRIPTBIND_SOURCE_FILES
	scriptbind/scriptbind_actor.cc
	scriptbind/scriptbind_application.cc
	scriptbind/scriptbind_animation_component.cc
	scriptbind/scriptbind_scriptable_class.cc
	scriptbind/scriptbind_input.cc
	scriptbind/scriptbind_mesh_render_component.cc
	scriptbind/scriptbind_skeleton_component.cc	
	scriptbind/scriptbind_particle_render_component.cc
	scriptbind/scriptbind_particle_system.cc
	scriptbind/scriptbind_intersectWorld.cc
	scriptbind/scriptbind_actor_manager.cc
	scriptbind/scriptbind_render_component.cc
	scriptbind/scriptbind_camera.cc
	scriptbind/scriptbind_camera_component.cc
	scriptbind/scriptbind_light_component.cc
	scriptbind/scriptbind_util.cc
	scriptbind/scriptbind_script_component.cc
	scriptbind/scriptbind_debug.cc
	scriptbind/scriptbind_IO.cc
	scriptbind/scriptbind_XmlReader.cc
	scriptbind/scriptbind_xml_writer.cc
	scriptbind/scriptbind_component.cc
	scriptbind/scriptbind_soundsource_component.cc
	scriptbind/scriptbind_physicsbody_component.cc
	scriptbind/scriptbind_physicscapsuleshape.cc
	scriptbind/scriptbind_physicsmeshshape.cc
	scriptbind/scriptbind_physicsscene.cc
	scriptbind/scriptbind_physicsshape.cc 
	scriptbind/scriptbind_physicssphereshape.cc
    	scriptbind/scriptbind_physicsboxshape.cc
	scriptbind/scriptbind_graphic_system.cc
	scriptbind/scriptbind_render_to_texture.cc
	scriptbind/scriptbind_material.cc
	scriptbind/scriptbind_soundechofilter_component.cc
	scriptbind/scriptbind_soundlowpassfilter_component.cc
	scriptbind/scriptbind_soundreverbfilter_component.cc
	scriptbind/scriptbind_soundFilter_component.cc
	scriptbind/scriptbind_soundListener_component.cc
	scriptbind/scriptbind_scene.cc
	scriptbind/scriptbind_InAppPurchase.cc
	scriptbind/scriptbind_sprite_render_component.cc
	scriptbind/scriptbind_androidjni.cc
	scriptbind/scriptbind_androidjnihelper.cc
	scriptbind/scriptbind_projector_component.cc
)

#ResourceFeature folder
SET ( RESOURCEFEATURE_HEADER_FILES
	resourcefeature/ResourceFeature.h
)

#ResourceFeature folder
SET ( RESOURCEFEATURE_SOURCE_FILES
	resourcefeature/ResourceFeature.cc
)

# folder
SET ( _HEADER_FILES 
	stdneb.h
)

# folder
SET ( _SOURCE_FILES
	app_classregistry.cc
	stdneb.cc
)

#<--------nidl fils------------------>
SET ( _NIDL_FILES
	graphicfeature/graphicsfeatureprotocol.nidl
	appframework/appframeworkprotocol.nidl
	particlefeature/particlefeatureprotocol.nidl
)

#<--------generated fils------------------>
SET ( GENERATED_FILES
	appframework/appframeworkprotocol.h
	appframework/appframeworkprotocol.cc
	graphicfeature/graphicsfeatureprotocol.h
	graphicfeature/graphicsfeatureprotocol.cc 
)

#<-------- Source Group ------------------>
SOURCE_GROUP( 
	AppFramework 
	FILES 
	${APPFRAMEWORK_HEADER_FILES} 
	${APPFRAMEWORK_SOURCE_FILES} 
)

SOURCE_GROUP( 
	BaseGameFeature 
	FILES 
	${BASEGAMEFEATURE_HEADER_FILES}
	${BASEGAMEFEATURE_SOURCE_FILES}
)

SOURCE_GROUP( 
	AppUtil
	FILES
	${APPUTIL_HEADER_FILES}	
	${APPUTIL_SOURCE_FILES}
)

SOURCE_GROUP( 
	Lightmap
	FILES
	${LIGHTMAP_HEADER_FILES}	
	${LIGHTMAP_SOURCE_FILES}
)

SOURCE_GROUP( 
	GraphicFeature
	FILES 
	${GRAPHICFEATURE_HEADER_FILES}
	${GRAPHICFEATURE_SOURCE_FILES}
)

SOURCE_GROUP( 
	InputFeature
	FILES 
	${INPUTFEATURE_HEADER_FILES}
	${INPUTFEATURE_SOURCE_FILES}
)

SOURCE_GROUP( 
	ALSystemFeature
	FILES 
	${ALSystemFeature_HEADER_FILES}
	${ALSystemFeature_SOURCE_FILES}
)

SOURCE_GROUP(
	PaticleFeature
	FILES
	${PATICLE_HEADER_FILES}
	${PATICLE_SOURCE_FILES}
)

SOURCE_GROUP( 
	ScriptFeatrue
	FILES 
	${SCRIPTFEATURE_SOURCE_FILES}
	${SCRIPTFEATURE_HEADER_FILES}
)

SOURCE_GROUP(
	ScriptFeatrue\\Inc
	FILES
	${SCRIPTFEATURE_INC_HEADER_FILES}
)

SOURCE_GROUP(
	VegetationFeature
	FILES
	${VEGETATION_HEADER_FILES}
	${VEGETATION_SOURCE_FILES}
)

SOURCE_GROUP(
	ScriptBind
	FILES
	${SCRIPTBIND_SOURCE_FILES}
)

SOURCE_GROUP(
	TerrainFeature
	FILES
	${TERRAIN_HEADER_FILES}
	${TERRAIN_SOURCE_FILES}
)

SOURCE_GROUP(
	PhysXFeature\\Core
	FILES
	${PHYSX_HEADER_FILES}
)

SOURCE_GROUP(
	PhysXFeature\\Components
	FILES	
	${PHYSX_SOURCE_FILES}
)

SOURCE_GROUP(
	SoundFeature
	FILES
	${SOUND_HEADER_FILES}
	${SOUND_SOURCE_FILES}
)

SOURCE_GROUP(
	"SpriteBacth"
	FILES
	${SPRITEBACTH_FILES}
)
SOURCE_GROUP(
	"GuiFeature"
	FILES
	${GUIFEATURE_FILES}
)
SOURCE_GROUP(
	"GuiBind"
	FILES
	${GUIBIND_FILES}
)
SOURCE_GROUP(
    AnimationFeature
    FILES
    ${ANIMATIONFEATURE_HEADER_FILES}
    ${ANIMATIONFEATURE_SOURCE_FILES}
)
SOURCE_GROUP(
    ResourceFeature
    FILES
    ${RESOURCEFEATURE_HEADER_FILES}
    ${RESOURCEFEATURE_SOURCE_FILES}
)


#<-------- Additional Include Directories ------------------>
IF ( ANDROID_BUILD )
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/rendersystem
	${CMAKE_SOURCE_DIR}/app
	
	${CMAKE_SOURCE_DIR}/addons	
	${CMAKE_SOURCE_DIR}/extlibs
	${CMAKE_SOURCE_DIR}/extlibs/boostWraper
	${CMAKE_SOURCE_DIR}/extlibs/freetype/include
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/cooking
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/foundation
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/common
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/characterkinematic
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/cloth
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/extensions
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/geometry
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/gpu
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/particles
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/physxprofilesdk
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/physxvisualdebuggersdk
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/pvd
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/pxtask
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/RepX
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/RepXUpgrader
	${CMAKE_SOURCE_DIR}/extlibs/physX3/linux/vehicle

	# should remove later
	${CMAKE_SOURCE_DIR}/graphicsystem
	${CMAKE_SOURCE_DIR}/
	${CMAKE_SOURCE_DIR}/addons/myguiplatforms/include
	${CMAKE_SOURCE_DIR}/addons/myguiengine/include
)
ENDIF( ANDROID_BUILD )

IF ( WINDOWS_BUILD )
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/rendersystem
	${CMAKE_SOURCE_DIR}/app
	
	${CMAKE_SOURCE_DIR}/addons	
	${CMAKE_SOURCE_DIR}/extlibs
	${CMAKE_SOURCE_DIR}/extlibs/boostWraper
	${CMAKE_SOURCE_DIR}/extlibs/freetype/include
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/cooking
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/foundation
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/common
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/characterkinematic
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/cloth
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/extensions
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/geometry
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/gpu
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/particles
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/physxprofilesdk
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/physxvisualdebuggersdk
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/pvd
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/pxtask
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/RepX
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/RepXUpgrader
	${CMAKE_SOURCE_DIR}/extlibs/physX3/windows/vehicle

	
	# should remove later
	${CMAKE_SOURCE_DIR}/graphicsystem
	${CMAKE_SOURCE_DIR}/
	${CMAKE_SOURCE_DIR}/addons/myguiplatforms/include
	${CMAKE_SOURCE_DIR}/addons/myguiengine/include
)
ENDIF ( WINDOWS_BUILD )

ADD_LIBRARY(
	App 
	STATIC 
	#header 
	${APPFRAMEWORK_HEADER_FILES}
	${APPUTIL_HEADER_FILES}
	${LIGHTMAP_HEADER_FILES}
	${BASEGAMEFEATURE_HEADER_FILES}
	${GRAPHICFEATURE_HEADER_FILES}
	${INPUTFEATURE_HEADER_FILES}
	${PATICLE_HEADER_FILES}
	${SCRIPTFEATURE_HEADER_FILES}
	${SCRIPTFEATURE_INC_HEADER_FILES}
	${VEGETATION_HEADER_FILES}
	${PHYSX_HEADER_FILES}
	${_HEADER_FILES}
	${TERRAIN_HEADER_FILES}
	${SOUND_HEADER_FILES}
	${ANIMATIONFEATURE_HEADER_FILES}
	 ${RESOURCEFEATURE_HEADER_FILES}
	${ALSystemFeature_HEADER_FILES}	
	 
	#source
	${APPFRAMEWORK_SOURCE_FILES}
	${APPUTIL_SOURCE_FILES}
	${LIGHTMAP_SOURCE_FILES}
	${BASEGAMEFEATURE_SOURCE_FILES}
	${GRAPHICFEATURE_SOURCE_FILES}
	${INPUTFEATURE_SOURCE_FILES}
	${PATICLE_SOURCE_FILES}
	${SCRIPTFEATURE_SOURCE_FILES}
	${VEGETATION_SOURCE_FILES}
	${SCRIPTBIND_SOURCE_FILES}
	${PHYSX_SOURCE_FILES}
	${_SOURCE_FILES}
	${TERRAIN_SOURCE_FILES}
	${SOUND_SOURCE_FILES}
	${ANIMATIONFEATURE_SOURCE_FILES}
	${RESOURCEFEATURE_SOURCE_FILES}
	${ALSystemFeature_SOURCE_FILES}
	
	#generate
	${GENERATED_FILES}

	${SPRITEBACTH_FILES}
	${GUIFEATURE_FILES}
	${GUIBIND_FILES}
 )

#Organize projects into folders
SET_PROPERTY(TARGET App PROPERTY FOLDER "4.App")
 
#Compile properties
_MACRO_TREAT_WARRINGS_AS_ERRORS( App )

 #<--------dependencies------------------>
 ADD_DEPENDENCIES(
	App
#dependencies
	App_nidls
 )
 
##################################################################################
# Build App_nidls 
##################################################################################
#add App_nidls projct
 ADD_CUSTOM_TARGET( 
	App_nidls 
	ALL 
	COMMAND ${CMAKE_SOURCE_DIR}/tools/idlcompiler/IdlcCompiler.exe ${CMAKE_SOURCE_DIR}/app/appframework/appframeworkprotocol.nidl ${CMAKE_SOURCE_DIR}/app/graphicfeature/graphicsfeatureprotocol.nidl
	SOURCES ${_NIDL_FILES}
)

#Organize projects into folders
SET_PROPERTY(TARGET App_nidls PROPERTY FOLDER "4.App")

#<--------dependencies------------------>
 ADD_DEPENDENCIES(
	App_nidls
#dependencies
	IdlcCompiler
)


