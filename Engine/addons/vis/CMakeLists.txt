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
# Build vis 
##################################################################################

#jobs folder
SET ( JOBS_SOURCE_FILES
	jobs/viscelljob.cc
)

#vissystems
SET ( VISSYSTEMS_HEADER_FILES 
	vissystems/viscell.h
	vissystems/visquadtree.h
	vissystems/vissystembase.h
)

#xinput folder
SET ( VISSYSTEMS_SOURCE_FILES
	vissystems/viscell.cc
	vissystems/visquadtree.cc
	vissystems/vissystembase.cc
)

# folder
SET ( _HEADER_FILES 
	observercontext.h
	visentity.h
	visquery.h
	visserver.h
)

# folder
SET ( _SOURCE_FILES
	observercontext.cc
	visentity.cc
	visquery.cc
	visserver.cc
)

#<-------- Source Group ------------------>
SOURCE_GROUP( 
	VisSystem
	FILES 
	${VISSYSTEMS_HEADER_FILES}
	${VISSYSTEMS_SOURCE_FILES}
)

SOURCE_GROUP( 
	Jobs
	FILES 
	${JOBS_SOURCE_FILES}
)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/rendersystem
	${CMAKE_SOURCE_DIR}/extlibs	

	# should remove later
	#${CMAKE_SOURCE_DIR}/graphicsystem
	#${CMAKE_SOURCE_DIR}/vis	
	${CMAKE_SOURCE_DIR}/addons
	${CMAKE_SOURCE_DIR}/
)

ADD_LIBRARY(
	Vis 
	STATIC 
	#header
	${VISSYSTEMS_HEADER_FILES}
	${_HEADER_FILES}
	#source
	${JOBS_SOURCE_FILES}
	${VISSYSTEMS_SOURCE_FILES}
	${_SOURCE_FILES}
 )

#Organize projects into folders
SET_PROPERTY(TARGET Vis PROPERTY FOLDER "3.Addons")

#Compile properties
_MACRO_TREAT_WARRINGS_AS_ERRORS( Vis )

