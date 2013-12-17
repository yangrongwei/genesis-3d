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
#Build Resource 
##################################################################################

# folder
SET ( _HEADER_FILES 
	animationres.h
	animationresloader.h
	animationressaver.h
	DDS_Header.h
	ETC_Header.h
	imageres.h
	imageresloader.h
	imageoperations.h
	meshres.h
	meshresloader.h
	meshressaver.h
	materialres.h
	materialresloader.h
	materialressaver.h
	physxmaterialres.h
	physxmaterialloader.h
	physxmaterialsaver.h
	PVRTC_Header.h
	reslable.h
	resourcebase.h
	resource.h
	resourcepriority.h
	resinfo.h
	resource_fwd_decl.h
	resource_stdneb.h
	resourceinterface.h
	resourceserver.h
	skeletonres.h
	skeletonresloader.h
	skeletonressaver.h

	spritepackageres.h
	spritepackageresloader.h
	spritepackageressaver.h

	resourcemanager.h
        rawres.h
	rawresloader.h
        rawressaver.h
	templateres.h
	templateresloader.h
	templateressaver.h
	audiores.h
	audioresloader.h
	audioressaver.h
	DXTextureDecompress.h
	DataChunkPacket.h
	meshSpliter.h
	FloatsCompression.h
	UnsignedIntPacking.h
	UnsignedIntUnpacking.h
)

# folder
SET ( _SOURCE_FILES
	animationres.cc
	animationresloader.cc
	animationressaver.cc
	imageres.cc
	imageresloader.cc
	imageoperations.cc
	meshres.cc
	meshresloader.cc
	meshressaver.cc
	materialres.cc
	materialresloader.cc
	materialressaver.cc
	physxmaterialres.cc
	physxmaterialloader.cc
	physxmaterialsaver.cc
	resource.cc
	resourcepriority.cc
	resinfo.cc
	resource_stdneb.cc
	resourceinterface.cc
	resourceserver.cc
	skeletonres.cc
	skeletonresloader.cc
	skeletonressaver.cc

	spritepackageres.cc
	spritepackageresloader.cc
	spritepackageressaver.cc

	resourcemanager.cc
        rawres.cc
	rawresloader.cc
        rawressaver.cc
	templateres.cc
	templateresloader.cc
	templateressaver.cc
	audiores.cc
	audioresloader.cc
	audioressaver.cc
	DXTextureDecompress.cc
	ETC_Header.cc
	meshSpliter.cc
	FloatsCompression.cc
	UnsignedIntPacking.cc
	UnsignedIntUnpacking.cc
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
	#${CMAKE_SOURCE_DIR}/addons/shardercompiler/
	#${CMAKE_SOURCE_DIR}/addons/shadercompiler/Compilers
	${CMAKE_SOURCE_DIR}/addons/shadercompiler/win
	${CMAKE_SOURCE_DIR}/addons
	${CMAKE_SOURCE_DIR}/
)

ADD_LIBRARY(
	Resource 
	STATIC 
	#header
	${_HEADER_FILES}	
	#SOURCE
	${_SOURCE_FILES}
 )

#Organize projects into folders
SET_PROPERTY(TARGET Resource PROPERTY FOLDER "3.Addons")

#Compile properties
_MACRO_TREAT_WARRINGS_AS_ERRORS( Resource )

 #_MACRO_COPY_T0_BINARY_DIR_AFTER_BUILD( Resource .lib )
