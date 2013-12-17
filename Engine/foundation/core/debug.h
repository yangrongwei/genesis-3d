/****************************************************************************
Copyright (c) 2002, Radon Labs GmbH
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
    @file core/debug.h

    Nebula debug macros.
  
    n_assert()  - the vanilla assert() Macro
    n_verify()  - like assert() except that the statement in parens is simply evaluated, unchecked, if __NEBULA_NO_ASSERT is set
    n_assert2() - an assert() plus a message from the programmer
*/
#include "core/config.h"


#if __ANDROID__
#include <android/log.h>
#endif
#if __OSX__
#include <assert.h>
#endif


#if defined( DEBUG ) || defined( _DEBUG ) || defined( __WIN32__ )
#if __ANDROID__
#define n_printf(...) __android_log_print(ANDROID_LOG_VERBOSE, "ProjectName", __VA_ARGS__)
#define n_error(...)  __android_log_print(ANDROID_LOG_ERROR, "ProjectName", __VA_ARGS__)
#define n_dbgout(...) __android_log_print(ANDROID_LOG_DEBUG, "ProjectName", __VA_ARGS__)
#define n_warning(...)  __android_log_print(ANDROID_LOG_WARN, "ProjectName", __VA_ARGS__)
#define n_confirm(...)  __android_log_print(ANDROID_LOG_INFO, "ProjectName", __VA_ARGS__)
#else
void n_printf(const char *, ...) __attribute__((format(printf,1,2)));
void n_error(const char*, ...) __attribute__((format(printf,1,2)));
void n_dbgout(const char*, ...) __attribute__((format(printf,1,2)));
void n_warning(const char*, ...) __attribute__((format(printf,1,2)));
void n_confirm(const char*, ...) __attribute__((format(printf,1,2)));
#endif
#else

#define  n_printf(...) 
#define  n_error(...) 
#define  n_dbgout(...)
#define  n_warning(...) 
#define  n_confirm( ...)
#endif


typedef void (*__pCustomAssertCallback) (const char* exp_type, const char* msg, const char* file, int line);
void n_setCustomAssert(__pCustomAssertCallback callback);
void n_custom_assert(const char* exp, const char* file, int line);
void n_custom_assert2(const char* exp, const char* msg, const char* file, int line);


void n_sleep(double);
void n_barf(const char *, const char *, int);
void n_barf2(const char*, const char*, const char*, int);



// backward compatibility
#define n_message n_confirm

// Static compile-time assertion
namespace StaticAssert
{
	template< bool > struct FAILED;
	template<> struct FAILED< true > { };
}
// use template in compile check. so can use in Release mode
#define n_static_assert( exp ) (StaticAssert::FAILED< (exp) != 0 >())  




#if (__NEBULA_NO_ASSERT__ == 1)
#define n_assert(exp) if(!(exp)){}
#define n_verify(exp) (exp)
#define n_verify2(exp,imsg) (exp)
#define n_assert2(exp, msg) if(!(exp)){}
#if __WIN32__
#define n_dxtrace(hr, msg)
#endif
	//#define n_static_assert(exp)
#elif (__NEBULA_NO_ASSERT__ == 0)

#ifdef __OSX__
#define n_assert(exp) assert(exp);
#define n_assert2(exp, msg) assert(exp);
#else
#define n_assert(exp) { if (!(exp)) n_custom_assert(#exp,__FILE__,__LINE__); }
#define n_assert2(exp, msg) { if (!(exp)) n_custom_assert2(#exp,msg,__FILE__,__LINE__); }
#endif
	//#define n_static_assert(exp) { int _x[ 2*((exp) != 0)-1 ]; (void)(_x[0]=0);}	
#if __WIN32__
	// dx9 specific: check HRESULT and display DX9 specific message box
#define n_dxtrace(hr, msg) { if (FAILED(hr)) DXTrace(__FILE__,__LINE__,hr,msg,true); }
#endif
#endif

//------------------------------------------------------------------------------

