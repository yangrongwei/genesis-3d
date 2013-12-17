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
# Build Vorbisfile Container
##################################################################################

# folder
SET ( _HEADER_FILES
	backends.h
	bitrate.h
	codebook.h
	codec_internal.h
	envelope.h
	floor_all.h
	floor_books.h
	highlevel.h
	lookup.h
	lookup_data.h
	lpc.h
	lsp.h
	masking.h
	mdct.h
	misc.h
	os.h
	psy.h
	psych_11.h
	psych_16.h
	psych_44.h
	psych_8.h
	registry.h
	residue_16.h
	residue_44.h
	residue_44p51.h
	residue_44u.h
	residue_8.h
	res_books_51.h
	res_books_stereo.h
	res_books_uncoupled.h
	scales.h
	setup_11.h
	setup_16.h
	setup_22.h
	setup_32.h
	setup_44.h
	setup_44p51.h
	setup_44u.h
	setup_8.h
	setup_X.h
	smallft.h
	window.h
	codec.h
	vorbisenc.h
	vorbisfile.h
)

# folder
SET ( _SOURCE_FILES
	analysis.c
	barkmel.c
	bitrate.c
	block.c
	codebook.c
	envelope.c
	floor0.c
	floor1.c
	info.c
	lookup.c
	lpc.c
	lsp.c
	mapping0.c
	mdct.c
	psy.c
	registry.c
	res0.c
	sharedbook.c
	smallft.c
	synthesis.c
	vorbisenc.c
	vorbisfile.c
	window.c
)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple

)

ADD_LIBRARY(
	Vorbisfile 
	STATIC 
	#header
	${_HEADER_FILES}
	#source
	${_SOURCE_FILES}
 )

#SET ( CMAKE_C_FLAGS_DEBUG "/MTd")
#SET ( CMAKE_C_FLAGS_EDITOR_DEBUG "/MTd")
#SET ( CMAKE_C_FLAGS_EDITOR_RELEASE "/MT")
#SET ( CMAKE_C_FLAGS_RELEASE "/MT")

#SET ( CMAKE_C_FLAGS_PROFILE_DEBUG "/MTd")
#SET ( CMAKE_C_FLAGS_PROFILE_RELEASE "/MT")

#Organize projects into folders
SET_PROPERTY(TARGET Vorbisfile PROPERTY FOLDER "1.Libs")

# _MACRO_COPY_T0_BINARY_DIR_AFTER_BUILD( Vorbisfile.lib )