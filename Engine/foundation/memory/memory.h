/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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

#include "core/config.h"

#if (__WIN32__ || __XBOX360__)
#include "memory/win360/win360memory.h"
#elif __WII__
#include "memory/wii/wiimemory.h"
#elif __PS3__
#include "memory/ps3/ps3memory.h"
#elif __OSX__
#include "memory/osx/osxmemory.h"
#elif __ANDROID__
#include "memory/android/androidmemory.h"
#else
#error "UNKNOWN PLATFORM"
#endif


template<class T> inline void checked_ndelete(T* x)
{
	// intentionally complex - simplification causes regressions
	typedef char type_must_be_complete[ sizeof(T)? 1: -1 ];
	(void) sizeof(type_must_be_complete);
	n_delete(x);
}
namespace Memory
{

	//小单位的拷贝中，等号赋值比调用内存拷贝函数要快很多很多。
	//叫xmemcpy的一个工具就是这么干的，号称小于120字节以内的拷贝比gcc的内存拷贝快10倍。
	//不过貌似，等号赋值长度必须<=128字节，并且是机器字长的倍数

typedef size_t smallest;


__forceinline
void CopySmallOne(const smallest* from, smallest* to)
{
	to[0] = from[0];
}

__forceinline
	void CopySmallTwo(const smallest* from, smallest* to)
{
	to[0] = from[0];
	to[1] = from[1];
}

__forceinline
	void CopySmallThree(const smallest* from, smallest* to)
{
	to[0] = from[0];
	to[1] = from[1];
	to[2] = from[2];
}

__forceinline
	void CopySmallFour(const smallest* from, smallest* to)
{
	to[0] = from[0];
	to[1] = from[1];
	to[2] = from[2];
	to[3] = from[3];
}

__forceinline
	void CopySmallFive(const smallest* from, smallest* to)
{
	to[0] = from[0];
	to[1] = from[1];
	to[2] = from[2];
	to[3] = from[3];
	to[4] = from[4];
}

__forceinline
	void CopySmallSix(const smallest* from, smallest* to)
{
	to[0] = from[0];
	to[1] = from[1];
	to[2] = from[2];
	to[3] = from[3];
	to[4] = from[4];
	to[5] = from[5];
}
}
