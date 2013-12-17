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
# Build the whole Engine
##################################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
  
PROJECT ( GenesisEngine )

# debug
MESSAGE( STATUS "CMAKE_SOURECE_DIR:" ${CMAKE_SOURCE_DIR} )
MESSAGE( STATUS "PROJECT_SOURCE_DIR:" ${PROJECT_SOURCE_DIR} )
MESSAGE( STATUS "PROJECT_BIN_DIR:" ${PROJECT_BINARY_DIR} )

### binary dir should not be the same with the source dir
IF ( ${PROJECT_SOURCE_DIR} STREQUAL ${PROJECT_BINARY_DIR} )	
	MESSAGE( STATUS "Binary directory:" ${PROJECT_BINARY_DIR} )
	MESSAGE( STATUS "Source code directory:" ${PROJECT_SOURCE_DIR} )
	MESSAGE( FATAL_ERROR "Binary directory should not be the same with Source code directory!!!" )
ENDIF( )

# set moudule path
SET( CMAKE_MODULE_PATH   "${CMAKE_SOURCE_DIR}/CMake" )

#Options defult setting here
INCLUDE ( ${CMAKE_MODULE_PATH}/Options.cmake )

IF( WIN32 AND NOT ANDOIRD_BUILD )
	Set( WINDOWS_BUILD TRUE CACHE BOOL "" FORCE)
ENDIF ( WIN32 AND NOT ANDOIRD_BUILD ) 
#check if 
IF ( NOT ANDROID_BUILD AND
	NOT WINDOWS_BUILD AND
	NOT APPLE_BUILD )
	MESSAGE( FATAL_ERROR "Should choose a platform!" )	
ENDIF()



#Macros record here
INCLUDE ( ${CMAKE_MODULE_PATH}/Macros.cmake )

IF ( WINDOWS_BUILD )
	SET( MS_COMPILER TURE )

	INCLUDE ( ${CMAKE_MODULE_PATH}/WindowsBuildConfig.cmake )
ENDIF ( WINDOWS_BUILD )

IF ( ANDROID_BUILD )
	SET( GCC_COMPILER TURE )

	INCLUDE ( ${CMAKE_MODULE_PATH}/AndroidBuildConfig.cmake )
ENDIF( ANDROID_BUILD )

IF ( APPLE_BUILD )
	SET( MS_COMPILER TURE )

	INCLUDE ( ${CMAKE_MODULE_PATH}/AppleBuildConfig.cmake )
ENDIF ( APPLE_BUILD )

#add subdirectories
ADD_SUBDIRECTORY( extlibs )

ADD_SUBDIRECTORY( addons )

ADD_SUBDIRECTORY( app )

ADD_SUBDIRECTORY( foundation )

ADD_SUBDIRECTORY( graphicsystem )

ADD_SUBDIRECTORY( rendersystem )

ADD_SUBDIRECTORY( profilesystem )

ADD_SUBDIRECTORY( players )

ADD_SUBDIRECTORY( tools )

ADD_SUBDIRECTORY( packageTool )
