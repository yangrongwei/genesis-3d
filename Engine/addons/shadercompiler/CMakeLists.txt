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
# Build shardercompiler 
##################################################################################

#Compilers folder
SET ( COMPILERS_SOURCE_FILES 
	Compilers/CGTool.h
	Compilers/CGTool.cc
	Compilers/D3DCompiler.h
	Compilers/D3DCompiler.cc
	Compilers/MojoShaderTool.h
	Compilers/MojoShaderTool.cc
	Compilers/GLESCompiler.h
	Compilers/GLESCompiler.cc	
)

#Utility folder
SET ( UTILITY_HEADER_FILES 	
	Utility/ShaderCompilerUtil.h
	
)

#Utility folder
SET ( UTILITY_SOURCE_FILES	
	Utility/ShaderCompilerUtil.cc
	
)


#SurfaceCompiler folder
SET ( SHADERTEMPLATE_HEADER_FILES

	ShaderTemplate/ShaderJoint.h
)

#SurfaceCompiler folder
SET ( SHADERTEMPLATE_SOURCE_FILES

	ShaderTemplate/ShaderJoint.cc
)


# folder
SET ( _HEADER_FILES 
	ShaderCompiler.h
	ShaderFactory.h
	ShaderData.h
	ShaderElement.h
	ShaderAnalyzer.h
	ShaderCompilerSetting.h
)

# folder
SET ( _SOURCE_FILES
	ShaderCompiler.cc
	ShaderFactory.cc
	ShaderData.cc
	ShaderElement.cc
	ShaderAnalyzer.cc
	ShaderCompilerSetting.cc
	stdneb.cc
)

#<-------- Source Group ------------------>
SOURCE_GROUP( 
	Utility
	FILES 
	${UTILITY_HEADER_FILES}
	${UTILITY_SOURCE_FILES}
)

SOURCE_GROUP(
	ShaderTemplate
	FILES
	${SHADERTEMPLATE_HEADER_FILES}
	${SHADERTEMPLATE_SOURCE_FILES}
)

SOURCE_GROUP( 
	Compilers
	FILES 
	${COMPILERS_SOURCE_FILES}	
)



#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/rendersystem
	${CMAKE_SOURCE_DIR}/extlibs
	${CMAKE_SOURCE_DIR}/extlibs/boostWraper
	${CMAKE_SOURCE_DIR}/extlibs/ShaderUtil
	${CMAKE_SOURCE_DIR}/extlibs/ShaderUtil/Cg/
	${CMAKE_SOURCE_DIR}/extlibs/ShaderUtil/mojoshader
	${CMAKE_SOURCE_DIR}/extlibs/ShaderUtil/hlsl2glslfork
	${CMAKE_SOURCE_DIR}/extlibs/ShaderUtil/GlslOptimizer

	# should remove later
	${CMAKE_SOURCE_DIR}/graphicsystem
	${CMAKE_SOURCE_DIR}/addons/shadercompiler/
	${CMAKE_SOURCE_DIR}/addons/shadercompiler/Compilers
	${CMAKE_SOURCE_DIR}/addons
	${CMAKE_SOURCE_DIR}/
)

ADD_LIBRARY(
	ShaderCompiler 
	STATIC 
	#header
	${UTILITY_HEADER_FILES}
	${SHADERTEMPLATE_HEADER_FILES}

	${_HEADER_FILES}	
	#SOURCE
	${COMPILERS_SOURCE_FILES}
	${UTILITY_SOURCE_FILES}
	${SHADERTEMPLATE_SOURCE_FILES}
	${_SOURCE_FILES}
 )

#Organize projects into folders
SET_PROPERTY(TARGET ShaderCompiler PROPERTY FOLDER "3.Addons")

#Compile properties
_MACRO_TREAT_WARRINGS_AS_ERRORS( ShaderCompiler )


#_MACRO_COPY_T0_BINARY_DIR_AFTER_BUILD( ShaderCompiler.lib )
 
 TARGET_LINK_LIBRARIES(
	ShaderCompiler
	${CMAKE_SOURCE_DIR}/../bin/lib/CG/Win/cg.lib
)
