#---------------------------------------------------------------------------------
# Copyright (c) 2011,WebJet Enterprise Department.ChangYou
# All rights reserved.
# Date        Ver    Who          Comment
# 2013-8-4	  1.0    WangYanbin
#---------------------------------------------------------------------------------

##################################################################################
# Build Ogg Container
##################################################################################

# folder
SET ( _HEADER_FILES
	ogg.h
	os_types.h
)

# folder
SET ( _SOURCE_FILES
	bitwise.c
	framing.c
)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple

)

ADD_LIBRARY(
	Ogg 
	STATIC 
	#header
	${_HEADER_FILES}
	#source
	${_SOURCE_FILES}
 )

#Organize projects into folders
SET_PROPERTY(TARGET Ogg PROPERTY FOLDER "1.Libs")

SET ( CMAKE_C_FLAGS_DEBUG "/MTd")
SET ( CMAKE_C_FLAGS_EDITOR_DEBUG "/MTd")
SET ( CMAKE_C_FLAGS_EDITOR_RELEASE "/MT")
SET ( CMAKE_C_FLAGS_RELEASE "/MT")


# _MACRO_COPY_T0_BINARY_DIR_AFTER_BUILD( Ogg.lib )