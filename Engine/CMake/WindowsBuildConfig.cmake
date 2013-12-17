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

#Options
# generate build type for Editor solution
SET( GENERATE_EDITOR_BUILD_TYPE OFF )

# let releae build typed generate debug information 
SET( RELEASE_BUILD_TYPE_GENERATE_DEBUG_INFORMATION ON )

#Setting build type, make Debug build in debug mode
SET_PROPERTY( GLOBAL PROPERTY DEBUG_CONFIGURATIONS "Debug;Profile_Debug" )
 
###SET the configuration types
IF ( CMAKE_CONFIGURATION_TYPES )

	SET( CMAKE_CONFIGURATION_TYPES Debug Release Profile_Debug Profile_Release)
	SET( CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
	"Reset the configurations to what we need"
	FORCE )

ENDIF( CMAKE_CONFIGURATION_TYPES )

########################## profile config ########################################

# profile debug

SET( CMAKE_CXX_FLAGS_PROFILE_DEBUG "/D__PROFILER__ /D_DEBUG /MTd /Zi /Ob0 /Od /RTC1" CACHE STRING
"Flags used by the C++ compiler during ProfileDebug builds."
FORCE )

SET( CMAKE_C_FLAGS_PROFILE_DEBUG "/D__PROFILER__ /D_DEBUG /MDd /Zi /Ob0 /Od /RTC1" CACHE STRING
"Flags used by the C compiler during ProfileDebug builds."
FORCE )

SET( CMAKE_EXE_LINKER_FLAGS_PROFILE_DEBUG
"/DEBUG /INCREMENTAL:YES" CACHE STRING
"Flags used for linking binaries during ProfileDebug builds."
FORCE )

SET( CMAKE_SHARED_LINKER_FLAGS_PROFILE_DEBUG
"/DEBUG /INCREMENTAL:YES" CACHE STRING
"Flags used by the shared libraries linker during ProfileDebug builds."
FORCE )

MARK_AS_ADVANCED(
CMAKE_CXX_FLAGS_PROFILE_DEBUG
CMAKE_C_FLAGS_PROFILE_DEBUG
CMAKE_EXE_LINKER_FLAGS_PROFILE_DEBUG
CMAKE_SHARED_LINKER_FLAGS_PROFILE_DEBUG  )

# profile release

SET( CMAKE_CXX_FLAGS_PROFILE_RELEASE "/D__PROFILER__ /MT /O2 /Ob2 /D NDEBUG" CACHE STRING
"Flags used by the C++ compiler during ProfileRelease builds."
FORCE )

SET( CMAKE_C_FLAGS_PROFILE_RELEASE "/D__PROFILER__ /MD /O2 /Ob2 /D NDEBUG" CACHE STRING
"Flags used by the C compiler during ProfileRelease builds."
FORCE )

SET( CMAKE_EXE_LINKER_FLAGS_PROFILE_RELEASE
"/INCREMENTAL:NO" CACHE STRING
"Flags used for linking binaries during ProfileRelease builds."
FORCE )

SET( CMAKE_SHARED_LINKER_FLAGS_PROFILE_RELEASE
"/INCREMENTAL:NO" CACHE STRING
"Flags used by the shared libraries linker during ProfileRelease builds."
FORCE )

MARK_AS_ADVANCED(
CMAKE_CXX_FLAGS_PROFILE_RELEASE
CMAKE_C_FLAGS_PROFILE_RELEASE
CMAKE_EXE_LINKER_FLAGS_PROFILE_RELEASE
CMAKE_SHARED_LINKER_FLAGS_PROFILE_RELEASE )

##################################################################################
###multi thread
FOREACH( flag_var
		CMAKE_CXX_FLAGS
		CMAKE_CXX_FLAGS_DEBUG
		CMAKE_CXX_FLAGS_RELEASE
		CMAKE_CXX_FLAGS_PROFILE_DEBUG
		CMAKE_CXX_FLAGS_PROFILE_RELEASE
)

IF( ${flag_var} MATCHES "/MD" )
	STRING( REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}" )
	#force update this on the CMAKE GUI
	SET(${flag_var} "${${flag_var}}" CACHE STRING
	"Reset the configurations to what we need"
	FORCE )

ENDIF( ${flag_var} MATCHES "/MD" )

IF( ${flag_var} MATCHES "/MDd" )
	STRING( REGEX REPLACE "/MDd" "/MTd" ${flag_var} "${${flag_var}}" )
	#force update this on the CMAKE GUI
	SET(${flag_var} "${${flag_var}}" CACHE STRING
	"Reset the configurations to what we need"
	FORCE )

ENDIF( ${flag_var} MATCHES "/MDd" )

ENDFOREACH( flag_var )

### let release build type generate debug information
IF ( ${RELEASE_BUILD_TYPE_GENERATE_DEBUG_INFORMATION} )
	FOREACH( flag_var
			CMAKE_CXX_FLAGS_RELEASE
			CMAKE_CXX_FLAGS_PROFILE_RELEASE
	)

	IF( NOT ${flag_var} MATCHES "/Zi" )
		
		SET( ${flag_var} "${${flag_var}} /Zi" CACHE STRING 
		"Let release build type generate debug info"
		FORCE )
		
	ENDIF( NOT ${flag_var} MATCHES "/Zi" )
	ENDFOREACH( flag_var )
ENDIF ( ${RELEASE_BUILD_TYPE_GENERATE_DEBUG_INFORMATION} )

#set directX path
SET(DIRECTX_INCLUDE_DIR     ${PROJECT_SOURCE_DIR}/extlibs/dxsdk/Include)
#set directX lib path
IF(CMAKE_CL_64)
	SET(DIRECTX_LIB_DIR ${PROJECT_SOURCE_DIR}/extlibs/dxsdk/Lib/x64)
ELSE(CMAKE_CL_64)
	SET(DIRECTX_LIB_DIR ${PROJECT_SOURCE_DIR}/extlibs/dxsdk/Lib/x86)
ENDIF(CMAKE_CL_64)

MESSAGE( STATUS "DIRECTX_INCLUDE_DIR:" ${DIRECTX_INCLUDE_DIR} )	
MESSAGE( STATUS "DIRECTX_LIB_DIRS:" ${DIRECTX_LIB_DIR} )

INCLUDE_DIRECTORIES( ${DIRECTX_INCLUDE_DIR} )
LINK_DIRECTORIES( ${DIRECTX_LIB_DIR} )

#Organize projects into folders
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

#Add definitions
ADD_DEFINITIONS(
	-D__WIN32__
	-DWIN32
	-DNT_PLUGIN )
		
### specify output directory
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../bin/win32/" )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../bin/win32/" )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../bin/win32/" )

