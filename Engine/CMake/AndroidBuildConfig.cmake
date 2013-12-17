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

ADD_DEFINITIONS(
	-D__ANDROID__
	-DANDROID )

#temp definitions	
ADD_DEFINITIONS(
-D__APP_BUILD_COMMIT__
-D__PHYSX_COMMIT__
-D__PROFILER__)

IF ( ANDROID_OPTIMIZED )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fexceptions  -Wfatal-errors" )
	SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions -Wfatal-errors" )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3" )
	SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3" )
	MESSAGE( STATUS "ANDROID_OPTIMIZED Turn On!" )
ELSE ( ANDROID_OPTIMIZED )
	SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fexceptions  -Wfatal-errors -g" )
	SET( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fexceptions -Wfatal-errors -g" )
ENDIF ( ANDROID_OPTIMIZED )

IF ( ANDROID_NDEBUG )
	ADD_DEFINITIONS( -DNDEBUG )
	MESSAGE( STATUS "NDEBUG macro set!" )
ELSE( ANDROID_NDEBUG )
	ADD_DEFINITIONS( -D_DEBUG )
	MESSAGE( STATUS "_DEBUG macro set!" )
ENDIF ( ANDROID_NDEBUG )

IF ( ANDROID_PROFILE )
	ADD_DEFINITIONS( -DANDROID_PROFILE )
	MESSAGE( STATUS "ANDROID_PROFILE macro set!" )
ELSE( ANDROID_PROFILE )
	MESSAGE( STATUS "ANDROID_PROFILE macro not set!" )
ENDIF ( ANDROID_PROFILE )

SET( ANDROID_GUN_LIB_STD_INCLUDE_PATH "${ANDROID_NDK_ROOT}/sources/cxx-stl/gnu-libstdc++/4.4.3/include" )
SET( ANDROID_GUN_LIB_STD_LIB_PATH "${ANDROID_NDK_ROOT}/sources/cxx-stl/gnu-libstdc++/4.4.3/libs/armeabi" )
SET( ANDROID_GUN_LIB_STD_LIB_PATH_INCLUDE "${ANDROID_NDK_ROOT}/sources/cxx-stl/gnu-libstdc++/4.4.3/libs/armeabi/include" )
SET( ANDROID_PLATFORMS_ANDROID14_INCLUDE "${ANDROID_NDK_ROOT}/platforms/android-14/arch-arm/usr/include" )
SET( ANDROID_PLATFORMS_ANDROID14_LIB "${ANDROID_NDK_ROOT}/platforms/android-14/arch-arm/usr/lib" )
	
MESSAGE( STATUS "ANDROID_NDK_ROOT:" ${ANDROID_NDK_ROOT} )

INCLUDE_DIRECTORIES( ${ANDROID_GUN_LIB_STD_INCLUDE_PATH} )
INCLUDE_DIRECTORIES( ${ANDROID_GUN_LIB_STD_LIB_PATH_INCLUDE} )
INCLUDE_DIRECTORIES( ${ANDROID_PLATFORMS_ANDROID14_INCLUDE} )
LINK_DIRECTORIES( ${ANDROID_PLATFORMS_ANDROID14_LIB} )
LINK_DIRECTORIES( ${ANDROID_GUN_LIB_STD_LIB_PATH} )

### specify output directory
SET( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../bin/android/" )
SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../bin/android/" )
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../bin/android/" )