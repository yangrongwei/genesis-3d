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
# Build Rander System
##################################################################################

# base folder
SET ( BASE_HEADER_FILES 
	base/GPUProgram.h
	base/IndexBuffer.h
	base/PrimitiveGroup.h
	base/RenderCommandType.h
	base/PixelFormat.h
	base/PixelFormatDesc.h
	base/RenderDevice.h
	base/RenderDeviceTypes.h
	base/RenderDisplay.h
	base/RenderResource.h
	base/RenderStateDesc.h
	base/RenderTarget.h
	base/Texture.h
	base/VertexBuffer.h
	base/VertexComponent.h
	base/VertexLayout.h
	base/RenderWindow.h
	base/MultipleRenderTarget.h
	base/GraphicCardCapability.h
	base/BufferData.h
)

#base
SET ( BASE_SOURCE_FILES
	base/GPUProgram.cc
	base/IndexBuffer.cc
	base/PrimitiveGroup.cc
	base/RenderCommandType.cc
	base/PixelFormat.cc
	base/RenderDevice.cc
	base/RenderDeviceTypes.cc
	base/RenderDisplay.cc
	base/RenderResource.cc
	base/RenderStateDesc.cc
	base/RenderTarget.cc
	base/Texture.cc
	base/VertexBuffer.cc
	base/VertexComponent.cc
	base/VertexLayout.cc
	base/RenderWindow.cc
	base/MultipleRenderTarget.cc
	base/BufferData.cc
)

#config folder
SET ( CONFIG_HEADER_FILES
	config/RenderDeviceConfig.h 
)

#d3d9 folder
SET ( D3D9_HEADER_FILES 
	d3d9/D3D9Types.h
	d3d9/GPUProgramD3D9.h
	d3d9/IndexBufferD3D9.h
	d3d9/PrimitiveGroupD3D9.h
	d3d9/RenderDeviceD3D9.h
	d3d9/RenderTargetD3D9.h
	d3d9/TextureD3D9.h
	d3d9/VertexBufferD3D9.h
	d3d9/VertexLayoutD3D9.h
	d3d9/D3D9Window.h
	d3d9/MRTD3D9.h
)

#d3d9 folder
SET ( D3D9_SOURCE_FILES
	d3d9/D3D9Types.cc
	d3d9/GPUProgramD3D9.cc
	d3d9/IndexBufferD3D9.cc
	d3d9/PrimitiveGroupD3D9.cc
	d3d9/RenderDeviceD3D9.cc
	d3d9/RenderTargetD3D9.cc
	d3d9/TextureD3D9.cc
	d3d9/VertexBufferD3D9.cc
	d3d9/VertexLayoutD3D9.cc
	d3d9/GraphicCardCapabilityD3D9.cc
	d3d9/D3D9Window.cc
	d3d9/MRTD3D9.cc
)

#null folder
SET ( NULL_HEADER_FILES 
	null/RenderDeviceNull.h
)
#null folder
SET ( NULL_SOURCE_FILES
	null/RenderDeviceNull.cc
)

#gles folder
SET ( GLES_HEADER_FILES
	gles/EGLContext.h
	gles/GLESTypes.h
	gles/GPUProgramGLES.h
	gles/IndexBufferObjectGLES.h
	gles/MRTGLES.h
	gles/OpenGLES.h
	gles/PrimitiveGroupObjectGLES.h
	gles/RenderDeviceGLES.h
	gles/RenderTargetGLES.h
	gles/TextureGLES.h
	gles/VertexBufferObjectGLES.h
	gles/GlesWindow.h
)

SET ( GLES_SOURCE_FILES 
	gles/EGLContext.cc
	gles/GLESTypes.cc
	gles/GPUProgramGLES.cc
	gles/IndexBufferObjectGLES.cc
	gles/GraphicCardCapabilityGLES.cc
	gles/MRTGLES.cc
	gles/OpenGLES.cc
	gles/PrimitiveGroupObjectGLES.cc
	gles/RenderDeviceGLES.cc
	gles/RenderTargetGLES.cc
	gles/TextureGLES.cc
	gles/VertexBufferObjectGLES.cc
	gles/GlesWindow.cc
)

# folder
SET ( _HEADER_FILES 
	RenderSystem.h
	RenderSystemThreadHandler.h
	stdneb.h
)

# folder
SET ( _SOURCE_FILES
	RenderSystem.cc
	RenderSystemMessageHandler.cc
	RenderSystemThreadHandler.cc
	stdneb.cc
)

#<--------nidl fils------------------>
SET ( _NIDL_FILES
	RenderMessageProtocol.nidl
)

#<--------generated fils------------------>
SET ( GENERATED_FILES
	RenderMessageProtocol.h
	RenderMessageProtocol.cc
)

#<-------- Source Group ------------------>
SOURCE_GROUP( 
	base
	FILES 
	${BASE_HEADER_FILES}
	${BASE_SOURCE_FILES}
)

SOURCE_GROUP( 
	config
	FILES 
	${CONFIG_HEADER_FILES}
)

SOURCE_GROUP( 
	d3d9
	FILES 
	${D3D9_HEADER_FILES}
	${D3D9_SOURCE_FILES}	
)

SOURCE_GROUP( 
	null
	FILES 
	${NULL_HEADER_FILES}
	${NULL_SOURCE_FILES}	
)

SOURCE_GROUP(
 gles\\Header
 FILES
 ${GLES_HEADER_FILES}
 
)

SOURCE_GROUP(
 gles\\Source
 FILES
 ${GLES_SOURCE_FILES}	
)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/extlibs/OpenGLES2.0/ARM/include
	${CMAKE_SOURCE_DIR}/extlibs
	${CMAKE_SOURCE_DIR}/extlibs/boostWraper

	# should remove later
	${CMAKE_SOURCE_DIR}/rendersystem 

)

ADD_LIBRARY(
	RenderSystem 
	STATIC 
	#header
	${BASE_HEADER_FILES}
	${CONFIG_HEADER_FILES}
	${D3D9_HEADER_FILES}
	${NULL_HEADER_FILES}
	${_HEADER_FILES}
	${GLES_HEADER_FILES}
	${_HEADER_FILES}
	#source
	${BASE_SOURCE_FILES}
	${D3D9_SOURCE_FILES}
	${NULL_SOURCE_FILES}
	${_SOURCE_FILES}
	${GLES_SOURCE_FILES}
	${_SOURCE_FILES}
	#generate 
	${GENERATED_FILES}
 )

#Compile properties
_MACRO_TREAT_WARRINGS_AS_ERRORS( RenderSystem )

#Organize projects into folders
SET_PROPERTY(TARGET RenderSystem PROPERTY FOLDER "2.Foundation")

 #<--------dependencies------------------>
 ADD_DEPENDENCIES(
	RenderSystem
#dependencies
	RenderSystem_nidls
 )
  
##################################################################################
# build RenderSystem_nidls
##################################################################################

#add RenderSystem_nidls procject to 
ADD_CUSTOM_TARGET( 
	RenderSystem_nidls 
	ALL
	COMMAND ${CMAKE_SOURCE_DIR}/tools/idlcompiler/IdlcCompiler.exe ${CMAKE_SOURCE_DIR}/rendersystem/RenderMessageProtocol.nidl	
	SOURCES ${_NIDL_FILES}
)

#Organize projects into folders
SET_PROPERTY(TARGET RenderSystem_nidls PROPERTY FOLDER "2.Foundation")

 #<--------dependencies------------------>
 ADD_DEPENDENCIES(
	RenderSystem_nidls
#dependencies
	IdlcCompiler
 )
#####################################

