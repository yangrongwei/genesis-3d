/****************************************************************************
Copyright (c) 2011-2013,WebJet Business Division,CYOU
 
http://www.genesis-3d.com.cn

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef RENDERDEVICECONFIG_H
#define RENDERDEVICECONFIG_H

#if __WIN32__
#	include <d3d9.h>
#	include <d3dx9.h>
////#include <dxerr9.h>
#	ifndef DXTRACE_ERR
#		define DXTRACE_ERR(x,y)
#	endif
#	ifndef DXGetErrorString9
#		define DXGetErrorString9(x) ""
#	endif // DXGetErrorString9
#	ifndef DXGetErrorDescription9
#		define DXGetErrorDescription9(x) ""
#	endif
#	define RENDERDEVICE_D3D9 1
#	define RENDERDEVICE_NULL 0
#	define RENDERDEVICE_OPENGLES 0
#elif __ANDROID__ || __OSX__
#	define RENDERDEVICE_OPENGLES 1
#	define RENDERDEVICE_NULL 0
#endif

#endif// RENDERDEVICECONFIG_H