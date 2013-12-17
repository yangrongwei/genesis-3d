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

#android toolchain for andorid9
INCLUDE(CMAKEFORCECOMPILER)

SET( CMAKE_CROSSCOMPILING TRUE )
SET( CMAKE_SYSTEM_NAME Linux )
SET( CMAKE_SYSTEM_VERSION 1 )
SET( CMAKE_SYSTEM_PROCESSOR "armv7-a" )

#base path
SET( ANDROID_NDK_ROOT "${CMAKE_SOURCE_DIR}/extlibs/NDK/android-ndk-r8b-windows" )
SET( ANDROID_NDK_TOOLCHAIN_ROOT "${ANDROID_NDK_ROOT}/toolchains/arm-linux-androideabi-4.4.3/prebuilt/windows" )

#SET compiler
SET( CMAKE_C_COMPILER "${ANDROID_NDK_TOOLCHAIN_ROOT}/bin/arm-linux-androideabi-gcc.exe" )
SET( CMAKE_CXX_COMPILER "${ANDROID_NDK_TOOLCHAIN_ROOT}/bin/arm-linux-androideabi-g++.exe" )

CMAKE_FORCE_C_COMPILER( "${CMAKE_C_COMPILER}" GNU )
CMAKE_FORCE_CXX_COMPILER( "${CMAKE_CXX_COMPILER}" GNU )

SET( CMAKE_MAKE_PROGRAM "${ANDROID_NDK_ROOT}/prebuilt/windows/bin/make.exe" CACHE PATH "make")
SET( CMAKE_STRIP "${ANDROID_NDK_TOOLCHAIN_ROOT}/bin/arm-linux-androideabi-strip.exe" CACHE PATH "strip" )
SET( CMAKE_AR "${ANDROID_NDK_TOOLCHAIN_ROOT}/bin/arm-linux-androideabi-ar.exe" CACHE PATH "archive" )
SET( CMAKE_LINKER "${ANDROID_NDK_TOOLCHAIN_ROOT}/bin/arm-linux-androideabi-ld.exe" CACHE PATH "linker" ) 
SET( CMAKE_NM "${ANDROID_NDK_TOOLCHAIN_ROOT}/bin/arm-linux-androideabi-nm.exe" CACHE PATH "nm" ) 
SET( CMAKE_OBJCOPY "${ANDROID_NDK_TOOLCHAIN_ROOT}/bin/arm-linux-androideabi-objcopy.exe" CACHE PATH "objcopy" ) 
SET( CMAKE_OBJDUMP "${ANDROID_NDK_TOOLCHAIN_ROOT}/bin/arm-linux-androideabi-objdump.exe" CACHE PATH "objdump" ) 
SET( CMAKE_RANLIB "${ANDROID_NDK_TOOLCHAIN_ROOT}/bin/arm-linux-androideabi-ranlib.exe" CACHE PATH "ranlib" ) 

#cache flags
SET( CMAKE_SHARED_LINKER_FLAGS "" CACHE STRING "linker flags" FORCE )

SET( CMAKE_FIND_ROOT_PATH "${ANDROID_NDK_ROOT}/platforms/android-14/arch-arm" " ${ANDROID_NDK_TOOLCHAIN_ROOT}" )

INCLUDE_DIRECTORIES( ${ANDROID_NDK_ROOT}/platforms/android-14/arch-arm/usr/include )
LINK_DIRECTORIES( ${ANDROID_NDK_ROOT}/platforms/android-14/arch-arm/usr/lib )

SET( LIBS "${ANDROID_NDK_ROOT}/platforms/android-14/arch-arm/usr/lib" )

SET( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--fix-cortex-a8 -L${LIBS} --sysroot=${LIBS}/../.. " )


SET ( CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER )
SET ( CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY )
SET ( CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY )