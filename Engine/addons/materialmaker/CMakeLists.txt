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
# Build materialmaker
##################################################################################

#Parser folder
SET ( PARSER_HEADER_FILES
	parser/GenesisShaderParser.h 
	parser/GenesisShaderBison.h
)

#Parser folder
SET ( PARSER_SOURCE_FILES
	parser/GenesisShaderFlex.cpp
	parser/GenesisShaderFlex.lcc
	parser/GenesisShaderBison.cpp
	parser/GenesisShaderBison.ycc
	parser/GenesisShaderParser.cc
)

# folder
SET ( _HEADER_FILES 
	stdneb.h
	unistd.h
	GenesisMaterial.h
	GenesisMakeMaterial.h
	GenesisMakePass.h
	GenesisMakeGPUProgram.h
	GenesisMakeTechnique.h
)

# folder
SET ( _SOURCE_FILES
	stdneb.cc
	GenesisMaterial.cc
	GenesisMakeMaterial.cc
	GenesisMakePass.cc
	GenesisMakeGPUProgram.cc
	GenesisMakeTechnique.cc
)

#<-------- Source Group ------------------>
SOURCE_GROUP( 
	Parser
	FILES 
	${PARSER_HEADER_FILES}
	${PARSER_SOURCE_FILES}	
)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/rendersystem 
	${CMAKE_SOURCE_DIR}/extlibs/OpenGLES2.0/ARM/include
	${CMAKE_SOURCE_DIR}/extlibs
	${CMAKE_SOURCE_DIR}/extlibs/boostWraper

	# should remove later
	${CMAKE_SOURCE_DIR}/graphicsystem
	${CMAKE_SOURCE_DIR}/addons/materialmaker
	${CMAKE_SOURCE_DIR}/addons	
	${CMAKE_SOURCE_DIR}/
)

ADD_LIBRARY(
	MaterialMaker 
	STATIC 
	#header
	${PARSER_HEADER_FILES}
	${_HEADER_FILES}
	#SOURCE
	${PARSER_SOURCE_FILES}
	${_SOURCE_FILES}
)

#Organize projects into folders
SET_PROPERTY(TARGET MaterialMaker PROPERTY FOLDER "3.Addons")

#Compile properties
#_MACRO_WEBJET_PROJECT_COMPILE_PROPERTIES( MaterialMaker )

#_MACRO_COPY_T0_BINARY_DIR_AFTER_BUILD( MaterialMaker .lib )

TARGET_LINK_LIBRARIES( 
	MaterialMaker
#project lib
	ShaderCompiler 
)
