#---------------------------------------------------------------------------------
# Copyright (c) 2011,WebJet Enterprise Department.ChangYou
# All rights reserved.
# Date        Ver    Who          Comment
# 2011-11-10   1.0    SunHao 
# 2013-03-06   2.0    SunHao      Support Crocss Compile & Support Andorid  
#---------------------------------------------------------------------------------

##################################################################################
# Build ZLib 
##################################################################################

# folder
SET ( _HEADER_FILES 
	crc32.h
	crypt.h
	deflate.h
	inffast.h
	inffixed.h
	inflate.h
	inftrees.h
	ioapi.h
	ionebula3.h
	trees.h
	unzip.h
	zconf.h
	zconf.in.h
	zlib.h
	zutil.h
)

# folder
SET ( _SOURCE_FILES
	adler32.c
	compress.c
	crc32.c
	deflate.c
	gzio.c
	infback.c
	inffast.c
	inflate.c
	inftrees.c
	ionebula3.cc
	trees.c
	uncompr.c
	unzip.c
	zutil.c
)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple

	# should remove later
	${CMAKE_SOURCE_DIR}/extlibs	
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/foundation/math
)

ADD_LIBRARY(
	ZLib 
	STATIC 
	#header
	${_HEADER_FILES}
	#source
	${_SOURCE_FILES}
 )
 
 #Organize projects into folders
SET_PROPERTY(TARGET ZLib PROPERTY FOLDER "1.Libs")
