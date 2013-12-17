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

#Organize projects into folders
SET_PROPERTY(TARGET OpenAL PROPERTY FOLDER "1.Libs")

# _MACRO_COPY_T0_BINARY_DIR_AFTER_BUILD( OpenAL.lib )