#---------------------------------------------------------------------------------
# Copyright (c) 2011,WebJet Enterprise Department.ChangYou
# All rights reserved.
# Date        Ver    Who          Comment
# 2013-8-2	  1.0    WangYanbin
#---------------------------------------------------------------------------------

##################################################################################
# Build OpenAL
##################################################################################

# folder
SET ( _HEADER_FILES
	al.h
	alAuxEffectSlot.h
	alBuffer.h
	alc.h
	alDatabuffer.h
	alEffect.h
	alError.h
	alext.h
	alFilter.h
	alListener.h
	alMain.h
	alSource.h
	alState.h
	alThunk.h
	alu.h
	bs2b.h
	config.h
	efx-creative.h
	efx.h
	xram.h
	efx-util.h
)

# folder
SET ( _SOURCE_FILES
	alAuxEffectSlot.c
	alBuffer.c
	ALc.c
	alcConfig.c
	alcEcho.c
	alcModulator.c
	alcReverb.c
	alcRing.c
	alcThread.c
	alDatabuffer.c
	alEffect.c
	alError.c
	alExtension.c
	alFilter.c
	alListener.c
	alSource.c
	alState.c
	alThunk.c
	ALu.c
	bs2b.c
	dsound.c
	mixer.c
	null.c
	panning.c
	wave.c
	winmm.c
)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple

)

ADD_LIBRARY(
	OpenAL 
	STATIC 
	#header
	${_HEADER_FILES}
	#source
	${_SOURCE_FILES}
 )

SET ( CMAKE_C_FLAGS_DEBUG "/MTd")
SET ( CMAKE_C_FLAGS_EDITOR_DEBUG "/MTd")
SET ( CMAKE_C_FLAGS_EDITOR_RELEASE "/MT")
SET ( CMAKE_C_FLAGS_RELEASE "/MT")

#Organize projects into folders
SET_PROPERTY(TARGET OpenAL PROPERTY FOLDER "1.Libs")

# _MACRO_COPY_T0_BINARY_DIR_AFTER_BUILD( OpenAL.lib )