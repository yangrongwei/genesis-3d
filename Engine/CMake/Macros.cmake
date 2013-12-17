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


# Get environment variable, define it as ENV_$var and make sure backslashes are converted to forward slashes
MACRO( _MACRO_GETENV_PATH VAR )
	SET( ENV_${VAR} $ENV{${VAR}} )

	# replace won't work IF var is blank
	IF ( ENV_${VAR} )
	 STRING( REGEX REPLACE "\\\\" "/" ENV_${VAR} ${ENV_${VAR}} )
	ENDIF ( ENV_${VAR} )	   
ENDMACRO(_MACRO_GETENV_PATH)

#treat warring as error
MACRO( _MACRO_TREAT_WARRINGS_AS_ERRORS arg_TargetName )
IF ( GCC_COMPILER )
	#SunHao TODO: too many warrings, so just comment it. Recovery it later. 2013.3.6
    #SET (WARRING_AS_ERROR_PARAM "-Werror" )
    SET (WARRING_AS_ERROR_PARAM " " ) #give a null value to make CMake.exe happy
ENDIF( GCC_COMPILER )
	
IF ( MS_COMPILER )
    SET (WARRING_AS_ERROR_PARAM "/WX" )
ENDIF( MS_COMPILER )

	SET_TARGET_PROPERTIES( 	${arg_TargetName}
							PROPERTIES
							COMPILE_FLAGS ${WARRING_AS_ERROR_PARAM} )
							
ENDMACRO( _MACRO_TREAT_WARRINGS_AS_ERRORS )