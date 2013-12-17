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
    @file core/win32/win32singleton.h

    Provides helper macros to implement singleton objects:
    
	this mean one instance in one thread
	- __DeclareThreadSingleton             put this into class declaration.        old£º    __DeclareSingleton    
	- __ImplementThreadSingleton           put this into the implemention file.    old:     __ImplementSingleton
	- __ConstructThreadSingleton           put this into the constructor           old:     __ConstructSingleton    
	- __DestructThreadSingleton            put this into the destructor            old:     __DestructSingleton

	this mean one instance in one image 
	- __DeclareImageSingleton             put this into class declaration.         old:     __DeclareInterfaceSingleton    
	- __ImplementImageSingleton           put this into the implemention file.     old:     __ImplementInterfaceSingleton 
	- __ConstructImageInterfaceSingleton  put this into the constructor            old:     __ConstructInterfaceSingleton
	- __DestructImageInterfaceSingleton   put this into the destructor             old:     __DestructInterfaceSingleton

    Get a pointer to a singleton object using the static Instance() method:

    Core::Server* coreServer = Core::Server::Instance();
*/
#include "core/types.h"
#include "threading/ThreadRuntimeInfo.h"

//------------------------------------------------------------------------------
#if 0	//	old code

// ·ÏÆú´úÂë
//#define __DeclareThreadSingleton(type) \
//public: \
//    ThreadLocal static type * Singleton; \
//    static type * Instance() { n_assert(0 != Singleton); return Singleton; }; \
//    static bool HasInstance() { return 0 != Singleton; }; \
//private:
//
//#define __ImplementThreadSingleton(type) \
//	ThreadLocal type * type::Singleton = 0;
//
//#define __DestructThreadSingleton \
//	n_assert(Singleton); Singleton = 0;
//
//#define __ConstructThreadSingleton \
//	n_assert(0 == Singleton); Singleton = this;

#else	// new


#define __DeclareThreadSingleton(type) \
public: \
	static IndexT MyTlsID; \
	static type * Instance() {  Threading::ThreadRunTimeInfo* pInfo = Threading::ThreadRunTimeInfo::GetMyThreadRuntime(); n_assert(pInfo); char* pRef = pInfo->GetInstance(MyTlsID); return (type*)pRef; }; \
	static bool HasInstance() { Threading::ThreadRunTimeInfo* pInfo = Threading::ThreadRunTimeInfo::GetMyThreadRuntime(); if(pInfo) { return pInfo->HasInstance(MyTlsID); } else { return false; } }; \
private:

#define __ImplementThreadSingleton(type) \
	IndexT type::MyTlsID = Threading::ThreadRunTimeInfo::GetThreadInstanceID();\

#define __ConstructThreadSingleton \
	Threading::ThreadRunTimeInfo* pInfo = Threading::ThreadRunTimeInfo::GetMyThreadRuntime(); \
    n_assert(pInfo); \
    pInfo->SetInstance( MyTlsID , (char*)this );

#define __DestructThreadSingleton \
	Threading::ThreadRunTimeInfo* pInfo = Threading::ThreadRunTimeInfo::GetMyThreadRuntime(); \
	n_assert(pInfo); \
	pInfo->SetInstance( MyTlsID , NULL );

#endif





//------------------------------------------------------------------------
#define __DeclareImageSingleton(type) \
public: \
    static type * Singleton; \
    static type * Instance() { n_assert(0 != Singleton); return Singleton; }; \
    static bool HasInstance() { return 0 != Singleton; }; \
private:

#define __ImplementImageSingleton(type) \
    type * type::Singleton = 0;

#define __ConstructImageSingleton \
    n_assert(0 == Singleton); Singleton = this;

#define __DestructImageSingleton \
	n_assert(Singleton); Singleton = 0;
//------------------------------------------------------------------------------
