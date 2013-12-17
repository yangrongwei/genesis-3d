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
# Build Input 
##################################################################################

#base folder
SET ( BASE_HEADER_FILES 
	base/inputgamepadbase.h
	base/inputkeyboardbase.h
	base/inputmousebase.h
	base/inputserverbase.h
	base/inputtouchscreenbase.h
)

#base folder
SET ( BASE_SOURCE_FILES
	base/inputgamepadbase.cc
	base/inputkeyboardbase.cc
	base/inputmousebase.cc
	base/inputserverbase.cc
	base/inputtouchscreenbase.cc
)

#win32 folder
SET ( WIN32_HEADER_FILES 
	win32/win32inputhardwaresource.h
	win32/win32inputmouse.h
	win32/win32inputserver.h
	win32/win32inputwindowsource.h
	win32/win32inputwebwindowsource.h
	
)

#win32 folder
SET ( WIN32_SOURCE_FILES
	win32/win32inputhardwaresource.cc
	win32/win32inputmouse.cc
	win32/win32inputserver.cc
	win32/win32inputwindowsource.cc
	win32/win32inputwebwindowsource.cc

)

#android folder
SET ( ANDROID_HEADER_FILES 
	
	android/androidinputgamepad.h
	android/androidinputserver.h
	android/androidinputsource.h
	android/androidinputtouchscreen.h
	android/androidtouchevent.h
)

#android folder
SET ( ANDROID_SOURCE_FILES 
	
	android/androidinputgamepad.cc
	android/androidinputserver.cc
	android/androidinputsource.cc
	android/androidinputtouchscreen.cc
)

#xinput folder
SET ( XINPUT_HEADER_FILES 
	xinput/xinputgamepad.h
)

#xinput folder
SET ( XINPUT_SOURCE_FILES
	xinput/xinputgamepad.cc
)

# folder
SET ( _HEADER_FILES 
	input_fwd_decl.h
	input_stdneb.h
	inputchar.h
	inputevent.h
	inputgamepad.h
	inputhandler.h
	inputhardwaresource.h
	inputkey.h
	inputkeyboard.h
	inputmouse.h
	inputmousebutton.h
	inputpriority.h
	inputserver.h
	inputsource.h
	inputwindowsource.h
	inputtouchscreen.h
	inputeventtypes.h
	inputmobileconfig.h
	mobileinputevent.h
	mobiletouchevent.h
)

# folder
SET ( _SOURCE_FILES
	input_stdneb.cc
	inputgamepad.cc
	inputhandler.cc
	inputhardwaresource.cc
	inputkey.cc
	inputkeyboard.cc
	inputmouse.cc
	inputmousebutton.cc
	inputserver.cc
	inputsource.cc
	inputwindowsource.cc
	inputtouchscreen.cc
	inputeventtypes.cc
)

#<-------- Additional Include Directories ------------------>
INCLUDE_DIRECTORIES(
	#TODO:Make this clear and simple
	${CMAKE_SOURCE_DIR}/foundation
	${CMAKE_SOURCE_DIR}/rendersystem
	${CMAKE_SOURCE_DIR}/extlibs	
	${CMAKE_SOURCE_DIR}/extlibs/boostWraper

	# should remove later
	${CMAKE_SOURCE_DIR}/graphicsystem
	${CMAKE_SOURCE_DIR}/addons/
	${CMAKE_SOURCE_DIR}/
)

ADD_LIBRARY(
	Input 
	STATIC 
	#header
	${BASE_HEADER_FILES}
	${WIN32_HEADER_FILES}
	${XINPUT_HEADER_FILES}
	${ANDROID_HEADER_FILES}
	${_HEADER_FILES}
	#source
	${BASE_SOURCE_FILES}
	${WIN32_SOURCE_FILES}
	${XINPUT_SOURCE_FILES}
	${ANDROID_SOURCE_FILES}
	${_SOURCE_FILES}
 )
ADD_DEFINITIONS(
	-D_UNICODE
	-DUNICODE
)

 

#Organize projects into folders
SET_PROPERTY(TARGET Input PROPERTY FOLDER "3.Addons")

#Compile properties
_MACRO_TREAT_WARRINGS_AS_ERRORS( Input )

