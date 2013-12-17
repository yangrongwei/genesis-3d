/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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

#pragma once
//------------------------------------------------------------------------------
/**
    @file core/win32/precompiled.h
    
    Contains precompiled headers on the Win32 platform.
    
*/
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define _WIN32_WINNT 0x500

#define NOGDICAPMASKS
#define OEMRESOURCE
#define NOATOM
#define NOCTLMGR    
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSERVICE
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX


// Windows headers
#include <windows.h>
#include <winbase.h>
#include <process.h>
#include <tchar.h>
#include <strsafe.h>
#include <wininet.h>
#include <winsock2.h>
#include <rpc.h>
#include <dbghelp.h>
#include <intrin.h>
#include <OleAuto.h>
#include <WbemIdl.h>
// crt headers
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <algorithm>
#include <assert.h>
// DirectX headers
#if _DEBUG
#define D3D_DEBUG_INFO (1)
#endif
//#include <d3d9.h>
//#include <d3dx9.h>
////#include <dxerr9.h>

//#ifndef DXTRACE_ERR
//#define DXTRACE_ERR(x,y)
//#endif
//#ifndef DXGetErrorString9
//#define DXGetErrorString9(x) ""
//#endif // DXGetErrorString9
//#ifndef DXGetErrorDescription9
//#define DXGetErrorDescription9(x) ""
//#endif

#include <xinput.h>

//#include <xact3.h>
//#include <xact3d3.h>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

//------------------------------------------------------------------------------


