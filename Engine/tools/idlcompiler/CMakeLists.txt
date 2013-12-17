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
# Build IdlcCompiler
##################################################################################

# folder
SET ( _HEADER_FILES 
	idlarg.h
	idlcodegenerator.h
	idlcommand.h
	idlcompiler.h
	idldependency.h
	idldocument.h
	idllibrary.h
	idlmessage.h
	idlprotocol.h
)

# folder
SET ( _SOURCE_FILES
	idlarg.cc
	idlc.cc
	idlcodegenerator.cc
	idlcommand.cc
	idlcompiler.cc
	idldependency.cc
	idldocument.cc
	idllibrary.cc
	idlmessage.cc
	idlprotocol.cc
	stdneb.cc
)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/extlibs	

	# should remove later
	${CMAKE_SOURCE_DIR}/
	${CMAKE_SOURCE_DIR}/tools	
)

ADD_EXECUTABLE( 
	IdlcCompiler
	#head
	${_HEADER_FILES}
	#source
	${_SOURCE_FILES}
)

#Organize projects into folders
SET_PROPERTY(TARGET IdlcCompiler PROPERTY FOLDER "0.CompilerTools")


TARGET_LINK_LIBRARIES(
	IdlcCompiler
#Project lib	
	TinyXML
	ZLib
#system lib
	wsock32.lib
	dbghelp.lib
	rpcrt4.lib
	wininet.lib
)

TARGET_LINK_LIBRARIES(
	IdlcCompiler
	debug 	${CMAKE_SOURCE_DIR}/../bin/lib/Foundation/Foundation_D.lib
)

TARGET_LINK_LIBRARIES(
	IdlcCompiler
	optimized ${CMAKE_SOURCE_DIR}/../bin/lib/Foundation/Foundation.lib
)

_MACRO_COPY_T0_BINARY_DIR_AFTER_BUILD( IdlcCompiler .exe )
