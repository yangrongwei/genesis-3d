#---------------------------------------------------------------------------------
# Copyright (c) 2011,WebJet Enterprise Department.ChangYou
# All rights reserved.
# Date        Ver    Who          Comment
# 2013-6-8   1.0    zhangming   
#---------------------------------------------------------------------------------

##################################################################################
# Build libmpg123
##################################################################################


#header folder
SET ( _HEADER_FILES
		mpg123.h
		config.h
		mpg123.h.in
)

#Header Files/libmpg123 folder
SET ( __LIBMPG123_
		libmpg123/compat.h
		libmpg123/debug.h
		libmpg123/decode.h
		libmpg123/frame.h
		libmpg123/getbits.h
		libmpg123/getcpuflags.h
		libmpg123/huffman.h
		libmpg123/icy2utf8.h
		libmpg123/icy.h
		libmpg123/id3.h
		libmpg123/index.h
		libmpg123/l2tables.h
		libmpg123/mangle.h
		libmpg123/mpg123lib_intern.h
		libmpg123/optimize.h
		libmpg123/parse.h
		libmpg123/reader.h
		libmpg123/sample.h
		libmpg123/synth.h
		libmpg123/true.h
)

#Source folder
SET ( _SOURCE_FILES
		msvc.c
)

#Source Files/libmpg123 folder
SET ( __SOURCE_LIBMPG123_
		libmpg123/dct36_3dnow.S
		libmpg123/dct36_3dnowext.S
		libmpg123/dct64_3dnow.S
		libmpg123/dct64_3dnowext.S
		libmpg123/dct64_mmx.S
		libmpg123/dct64_sse.S
		libmpg123/dct64_sse_float.S
		libmpg123/dct64_x86_64.S
		libmpg123/dct64_x86_64_float.S
		libmpg123/equalizer_3dnow.S
		libmpg123/getcpuflags.S
		libmpg123/synth_3dnow.S
		libmpg123/synth_3dnowext.S
		libmpg123/synth_i586.S
		libmpg123/synth_i586_dither.S
		libmpg123/synth_mmx.S
		libmpg123/synth_sse.S
		libmpg123/synth_sse_accurate.S
		libmpg123/synth_sse_float.S
		libmpg123/synth_sse_s32.S
		libmpg123/synth_stereo_sse_accurate.S
		libmpg123/synth_stereo_sse_float.S
		libmpg123/synth_stereo_sse_s32.S
		libmpg123/synth_stereo_x86_64.S
		libmpg123/synth_stereo_x86_64_accurate.S
		libmpg123/synth_stereo_x86_64_float.S
		libmpg123/synth_stereo_x86_64_s32.S
		libmpg123/synth_x86_64.S
		libmpg123/synth_x86_64_accurate.S
		libmpg123/synth_x86_64_float.S
		libmpg123/synth_x86_64_s32.S
		libmpg123/tabinit_mmx.S
		libmpg123/compat.c
		libmpg123/dct64.c
		libmpg123/equalizer.c
		libmpg123/feature.c
		libmpg123/format.c
		libmpg123/frame.c
		libmpg123/icy2utf8.c
		libmpg123/icy.c
		libmpg123/id3.c
		libmpg123/index.c
		libmpg123/layer1.c
		libmpg123/layer2.c
		libmpg123/layer3.c
		libmpg123/libmpg123.c
		libmpg123/ntom.c
		libmpg123/optimize.c
		libmpg123/parse.c
		libmpg123/readers.c
		libmpg123/stringbuf.c
		libmpg123/synth.c
		libmpg123/synth_8bit.c
		libmpg123/synth_real.c
		libmpg123/synth_s32.c
		libmpg123/tabinit.c
)

#include folder
SOURCE_GROUP("Header Files" FILES
		${_HEADER_FILES}
)
SOURCE_GROUP("Header Files\\libmpg123" FILES
		${__LIBMPG123_}
)

#source folder
SOURCE_GROUP("Source Files" FILES
		${_SOURCE_FILES}
)
SOURCE_GROUP("Source Files\\libmpg123" FILES
		${__SOURCE_LIBMPG123_}
)


#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/extlibs/mpg123
	${CMAKE_SOURCE_DIR}/extlibs/mpg123/libmpg123
)

ADD_LIBRARY(
	libmpg123
	STATIC 
	#header
	${_HEADER_FILES}
	${__LIBMPG123_}
	#source
	${_SOURCE_FILES}	
	${__SOURCE_LIBMPG123_}
)

SET ( CMAKE_C_FLAGS_DEBUG "/MTd")
SET ( CMAKE_C_FLAGS_EDITOR_DEBUG "/MTd")
SET ( CMAKE_C_FLAGS_EDITOR_RELEASE "/MT")
SET ( CMAKE_C_FLAGS_RELEASE "/MT")

 #Organize projects into folders
SET_PROPERTY(TARGET libmpg123 PROPERTY FOLDER "1.Libs")

#Compile properties
#_MACRO_TREAT_WARRINGS_AS_ERRORS( libmpg123 )

ADD_DEFINITIONS(
	-D_CRT_SECURE_NO_WARNINGS
	-DOPT_GENERIC
)