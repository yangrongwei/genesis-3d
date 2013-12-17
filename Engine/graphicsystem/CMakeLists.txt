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
# Build Graphic System
##################################################################################

#base folder
SET ( BASE_HEADER_FILES
	base/GraphicObject.h
	base/RenderToTexture.h	
	base/ImageFilters.h
	base/MultipleRenderToTexture.h
	base/RenderBase.h
	base/DataCollection.h
	base/StreamBufferPool.h
	base/GraphicBufferData.h
	base/RenderQueue.h
)

#base folder
SET ( BASE_SOURCE_FILES
	base/GraphicObject.cc
	base/RenderToTexture.cc
	base/ImageFilters.cc
	base/MultipleRenderToTexture.cc
	base/StreamBufferPool.cc
	base/GraphicBufferData.cc
	base/RenderQueue.cc
)

#camera folder
SET ( CAMERA_HEADER_FILES
	Camera/RenderPipeline/ForwardShadingRenderPipeline.h
	Camera/RenderPipeline/DeferredLightingRenderPipeline.h
	Camera/RenderPipeline/DeferredLightingPass.h
	Camera/RenderPipeline/RenderPipelineManager.h
	Camera/RenderPipeline/RenderPipeline.h
	Camera/RenderPipeline/VisibleNode.h
	Camera/RenderPipeline/RenderData.h
	Camera/RenderPipeline/ActiveLight.h
	Camera/Camera.h
	Camera/CameraSetting.h
)

#camera folder
SET ( CAMERA_SOURCE_FILES
	Camera/RenderPipeline/ForwardShadingRenderPipeline.cc
	Camera/RenderPipeline/DeferredLightingRenderPipeline.cc
	Camera/RenderPipeline/DeferredLightingPass.cc
	Camera/RenderPipeline/RenderPipelineManager.cc
	Camera/RenderPipeline/RenderPipeline.cc
	Camera/RenderPipeline/VisibleNode.cc
	Camera/RenderPipeline/RenderData.cc
	Camera/RenderPipeline/ActiveLight.cc
	Camera/Camera.cc
	Camera/CameraSetting.cc
)

#Light folder
SET ( LIGHT_HEADER_FILES
	Light/Light.h
)

#Light folder
SET ( LIGHT_SOURCE_FILES
	Light/Light.cc
)

#Material folder
SET ( MATERIAL_HEADER_FILES 
	Material/GlobalShaderParam.h
	Material/Material.h
	Material/MaterialParam.h
	Material/MaterialPass.h
	Material/MaterialTech.h
	Material/ShaderParam.h
	Material/materialinstance.h
	Material/MaterialManager.h
)

#Material folder
SET ( MATERIAL_SOURCE_FILES
	Material/GlobalShaderParam.cc
	Material/Material.cc
	Material/MaterialParam.cc
	Material/MaterialPass.cc
	Material/MaterialTech.cc
	Material/ShaderParam.cc
	Material/materialinstance.cc
	Material/MaterialManager.cc
)

#Renderable folder
SET ( RENDERABLE_HEADER_FILES 
	Renderable/GraphicRenderer.h
	Renderable/Renderable.h
	Renderable/QuadRenderable.h
	Renderable/RenderObject.h
)

#Renderable folder
SET ( RENDERABLE_SOURCE_FILES
	Renderable/GraphicRenderer.cc
	Renderable/Renderable.cc
	Renderable/QuadRenderable.cc
	Renderable/RenderObject.cc
)


#Projector folder
SET ( PROJECTOR_HEADER_FILES 
	Projector/Projector.h
	Projector/CollisionModelServer.h
	Projector/CollisionModel.h
)

#Projector  folder
SET ( PROJECTOR_SOURCE_FILES
	Projector/Projector.cc
	Projector/CollisionModelServer.cc
	Projector/CollisionModel.cc
)

# folder
SET ( _HEADER_FILES 
	GraphicSystem.h
	GraphicObjectManager.h	
	stdneb.h
	ViewPortWindow.h
	RenderUnit.h
)

# folder
SET ( _SOURCE_FILES
	GraphicSystem.cc
	GraphicObjectManager.cc	
	stdneb.cc
	ViewPortWindow.cc
	RenderUnit.cc

)
# folder
SET ( _VISION_FILES
	Vision/RenderScene.h
	Vision/RenderScene.cc
)

#<-------- Source Group ------------------>
SOURCE_GROUP( 
	Base
	FILES 
	${BASE_HEADER_FILES}
	${BASE_SOURCE_FILES}
)

SOURCE_GROUP( 
	Camera
	FILES 
	${CAMERA_HEADER_FILES}
	${CAMERA_SOURCE_FILES}
)

SOURCE_GROUP( 
	Light
	FILES 
	${LIGHT_HEADER_FILES}
	${LIGHT_SOURCE_FILES}
)

SOURCE_GROUP( 
	Material
	FILES
	${MATERIAL_HEADER_FILES}
	${MATERIAL_SOURCE_FILES}
)

SOURCE_GROUP( 
	Renderable
	FILES 
	${RENDERABLE_HEADER_FILES}
	${RENDERABLE_SOURCE_FILES}	
)

SOURCE_GROUP( 
	Projector
	FILES 
	${PROJECTOR_HEADER_FILES}
	${PROJECTOR_SOURCE_FILES}
)
SOURCE_GROUP( 
	Vision
	FILES 
	${_VISION_FILES}
)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/rendersystem 
	${CMAKE_SOURCE_DIR}/extlibs/
	${CMAKE_SOURCE_DIR}/extlibs/boostWraper

	# should remove later
	${CMAKE_SOURCE_DIR}/graphicsystem
	${CMAKE_SOURCE_DIR}/addons	
	${CMAKE_SOURCE_DIR}/
)

ADD_LIBRARY(
	GraphicSystem 
	STATIC 
	#header
	${BASE_HEADER_FILES}
	${CAMERA_HEADER_FILES}
	${LIGHT_HEADER_FILES}
	${MATERIAL_HEADER_FILES}
	${RENDERABLE_HEADER_FILES}
	${PROJECTOR_HEADER_FILES}
	${_HEADER_FILES}
	#SOURCE
	${BASE_SOURCE_FILES}
	${CAMERA_SOURCE_FILES}
	${LIGHT_SOURCE_FILES}
	${MATERIAL_SOURCE_FILES}
	${RENDERABLE_SOURCE_FILES}
	${PROJECTOR_SOURCE_FILES}
	${_SOURCE_FILES}

	${_VISION_FILES}

 )

#Organize projects into folders
SET_PROPERTY(TARGET GraphicSystem PROPERTY FOLDER "3.Addons")

#Compile properties
_MACRO_TREAT_WARRINGS_AS_ERRORS( GraphicSystem )
