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
# Build Vegetation 
##################################################################################

# folder
SET ( _HEADER_FILES 
	vegetation_fwd_decl.h
	VegetationServer.h
	VegetationObejct.h
	VegetationRenderObject.h
	VegetationRenderable.cc
	InstanceMap.h
	GrassInstanceMap.h	
	MeshInstanceMap.h
	TreeInstanceMap.h
)

# folder
SET ( _SOURCE_FILES
	VegetationServer.cc	
	vegetationserverserialization.cc
	VegetationObject.cc
	VegetationObjectSerialization.cc
	VegetationRenderObject.cc
	VegetationRenderable.h
	InstanceMap.cc
	InstanceMapSerialization.cc
	GrassInstanceMap.cc
	GrassInstanceMapSerialization.cc	
	MeshInstanceMap.cc
	MeshInstanceMapSerialization.cc
	TreeInstanceMap.cc
	TreeInstanceMapSerialization.cc

)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/rendersystem
	${CMAKE_SOURCE_DIR}/extlibs	
	${CMAKE_SOURCE_DIR}/extlibs/boostWraper

	# should remove later
	${CMAKE_SOURCE_DIR}/graphicsystem
	${CMAKE_SOURCE_DIR}/addons/	
	${CMAKE_SOURCE_DIR}/
)

ADD_LIBRARY(
	Vegetation 
	STATIC 
	#header	
	${_HEADER_FILES}
	#source	
	${_SOURCE_FILES}

 )

#Organize projects into folders
SET_PROPERTY(TARGET Vegetation PROPERTY FOLDER "3.Addons")

#Compile properties
_MACRO_TREAT_WARRINGS_AS_ERRORS( Vegetation)
