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
    @class core/types.h

    Basic type definitions for Nebula3.

*/

#if !SPU
#include "memory/memory.h"
#endif

// fixing Windows defines...
#ifdef DeleteFile
#undef DeleteFile
#endif
#ifdef CopyFile
#undef CopyFile
#endif
#ifdef GetObject
#undef GetObject
#endif

typedef unsigned long  ulong;
typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef unsigned char  ubyte;

typedef char int8;						// 8 bit signed
typedef unsigned char uint8;			// 8 bit unsigned
typedef unsigned char uchar;			// 8 bit unsigned
typedef short int16;					// 16 bit signed
typedef unsigned short uint16;			// 16 bit unsigned
typedef int int32;						// 32 bit signed
typedef unsigned int uint32;			// 32 bit unsigned
typedef long long int64;				// 64 bit signed
typedef unsigned long long uint64;		// 64 bit unsigned
typedef float float32;					// 32 bit floating value
typedef double float64;					// 64 bit floating value


typedef unsigned short char16_t;



typedef int IndexT;     // the index type
typedef int SizeT;      // the size type
typedef void* WindHandle;
static const int InvalidIndex = -1;

//主要用于枚举和int之间的转换。
template<typename Type>
class TypeConvert
{
public:
	static int Conver(Type value);

	static Type Conver(int value);
private:
	TypeConvert();
};
template<typename Type>
inline int TypeConvert<Type>::Conver(Type value)
{
	return int(value);
}
template<typename Type>
inline Type TypeConvert<Type>::Conver(int value)
{
	return Type(value);
}


#define N_ARGB(a,r,g,b) ((uint)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define N_RGBA(r,g,b,a) N_ARGB(a,r,g,b)
#define N_XRGB(r,g,b)   N_ARGB(0xff,r,g,b)
#define N_COLORVALUE(r,g,b,a) N_RGBA((uint)((r)*255.f),(uint)((g)*255.f),(uint)((b)*255.f),(uint)((a)*255.f))

// byte bit calc
#define BITS_TO_BYTES(x) (((x)+7)>>3)
#define BYTES_TO_BITS(x) ((x)<<3)

//比特位级的标志
#define BIT_FLAG_NONE  0
#define BIT_FLAG(num)  (1<<(num))
#define BIT_FLAG_ALL  ~0

#define BIT_FLAG_8BIT_MAX 0xff
#define BIT_FLAG_16BIT_MAX 0xffff
#define BIT_FLAG_32BIT_MAX 0xffffffff

template<typename T, typename T2>
inline bool BIT_FLAG_IS_OPEN(T x, T2 flag) 
{
	return ((T)flag) == (((T)x) & ((T)flag));
}

template<typename T, typename T2>
inline T BIT_FlAG_APPEND(T x, T2 flag)
{
	return (T)(((T)x) | (T)flag);
}
template<typename T, typename T2>
inline T BIT_FlAG_DELETE(T x, T2 flag)
{
	return (T)(((T)x) & (~((T)flag)));
}


#if (__PS3__ || __WII__ || __OSX__ || __ANDROID__)
inline ushort                _byteswap_ushort(ushort x)              { return ((x>>8) | (x<<8)); }
inline ulong                 _byteswap_ulong(ulong x)                { return ((x&0xff000000)>>24) | ((x&0x00ff0000)>>8) | ((x&0x00000ff00)<<8) | ((x&0x000000ff)<<24); }
inline unsigned long long    _byteswap_uint64(unsigned long long x)  { return ((((unsigned long long)_byteswap_ulong((ulong)(x & 0xffffffff))) << 32) | ((unsigned long long)_byteswap_ulong((ulong)(x >> 32)))); }
#endif

#if __WIN32__
#define n_stricmp stricmp
#define n_snprintf StringCchPrintf
#elif __XBOX360__
#define n_stricmp lstrcmpi
#define n_snprintf StringCchPrintf
#elif __WII__
#define n_stricmp stricmp
#define n_snprintf sprintf
#elif __PS3__
#define n_stricmp strcasecmp
#define n_snprintf sprintf
#elif __OSX__
#define n_stricmp strcasecmp
#define n_snprintf sprintf
#elif __ANDROID__
#define n_stricmp strcasecmp
#define n_snprintf sprintf
#else
#error "Unsupported platform!"
#endif

#define GET_FUNCTION_NAME() __FUNCTION__

#if __VC__
#define NEBULA3_ALIGN16 __declspec(align(16))
#elif __GNUC__
#define NEBULA3_ALIGN16 __attribute__((aligned(16)))
#else
#define NEBULA3_ALIGN16
#endif
//------------------------------------------------------------------------------
