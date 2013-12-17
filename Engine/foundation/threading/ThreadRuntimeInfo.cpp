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
#include "stdneb.h"
#include "threading/ThreadRuntimeInfo.h"

namespace Threading
{

// note 我们从10开始。因为静态变量初始化顺序的原因。一些单件在没有得到ThreadInstanceCounter计数的时候，就会直接初始化。
// 这些单件的ID使用特别的值。 包括：
//   LocalStringAtomTable 1
//

IndexT ThreadRunTimeInfo::ThreadInstanceCounter = 10;
IndexT ThreadRunTimeInfo::mTlsSlot = InvalidIndex;

ThreadRunTimeInfo::ThreadRunTimeInfo()
 : mThreadName(NULL)
{
	for ( IndexT index = 0; index < MaxThreadInstanceNum; ++index )
	{
		mInstanceArray[index] = 0;
	}
}
//------------------------------------------------------------------------
ThreadRunTimeInfo::~ThreadRunTimeInfo()
{
	mThreadName = NULL;
	for ( IndexT index = 0; index < MaxThreadInstanceNum; ++index )
	{
		mInstanceArray[index] = 0;
	}
}
//------------------------------------------------------------------------
void
ThreadRunTimeInfo::SetupMyThreadRunTime(const char* n)
{
#if __WIN32__ 
	if ( InvalidIndex == mTlsSlot )
	{
		mTlsSlot = ::TlsAlloc();
		if ( InvalidIndex == mTlsSlot )
		{
			Win32::SysFunc::Error(" can not init TLS Slot ");
		}
	}

	n_assert( TlsGetValue(mTlsSlot) == NULL );
	Threading::ThreadRunTimeInfo* pThreadRuntime = n_new( Threading::ThreadRunTimeInfo);
	n_assert( pThreadRuntime );
	pThreadRuntime->mThreadName = n;

	TlsSetValue(mTlsSlot, pThreadRuntime);

#elif __ANDROID__
	if ( InvalidIndex == mTlsSlot )
	{
		IndexT ret = pthread_key_create(&mTlsSlot, NULL);
		if (ret != 0)
		{
			n_error(" can not init TLS Slot ");
		}
	}

	n_assert( pthread_getspecific(mTlsSlot) == NULL );
	Threading::ThreadRunTimeInfo* pThreadRuntime = n_new( Threading::ThreadRunTimeInfo);
	n_assert( pThreadRuntime );
	pThreadRuntime->mThreadName = n;

	pthread_setspecific(mTlsSlot, pThreadRuntime);	
		 
#elif __OSX__	
    if ( InvalidIndex == mTlsSlot )
	{
        pthread_key_t keytmp;
		IndexT ret = pthread_key_create(&keytmp,NULL);
        mTlsSlot = keytmp;
		if (ret != 0)
		{
			n_error(" can not init TLS Slot ");
		}
	}
    
	n_assert( pthread_getspecific(mTlsSlot) == NULL );
	Threading::ThreadRunTimeInfo* pThreadRuntime = n_new( Threading::ThreadRunTimeInfo);
	n_assert( pThreadRuntime );
	pThreadRuntime->mThreadName = n;
    
	pthread_setspecific(mTlsSlot, pThreadRuntime);
#endif
}
//------------------------------------------------------------------------
void 
ThreadRunTimeInfo::DestoryThreadRunTime( bool isMainThread /*= false*/ )
{
#if __WIN32__ 
	Threading::ThreadRunTimeInfo* pInfo = (Threading::ThreadRunTimeInfo*)TlsGetValue(mTlsSlot);
	n_assert(pInfo);
	TlsSetValue(mTlsSlot, NULL);
	n_delete(pInfo);
	if ( isMainThread )
	{
		BOOL bOK = TlsFree( mTlsSlot );
		n_assert( bOK );
		mTlsSlot = InvalidIndex;
	}
#elif __ANDROID__
	Threading::ThreadRunTimeInfo* pInfo = (Threading::ThreadRunTimeInfo*)pthread_getspecific(mTlsSlot);
	n_assert(pInfo);
	pthread_setspecific(mTlsSlot, NULL);
	n_delete(pInfo);
	if ( isMainThread )
	{
		int ret = pthread_key_delete(mTlsSlot);
		n_assert( ret == 0 );
		mTlsSlot = InvalidIndex;
	}
#endif
}

//------------------------------------------------------------------------
Threading::ThreadRunTimeInfo*
ThreadRunTimeInfo::GetMyThreadRuntime(void)
{
#if __WIN32__ 
	return (Threading::ThreadRunTimeInfo*)TlsGetValue(mTlsSlot);

#elif __ANDROID__ || __OSX__
	return (Threading::ThreadRunTimeInfo*)pthread_getspecific(mTlsSlot);

#endif
}
//------------------------------------------------------------------------
IndexT ThreadRunTimeInfo::GetThreadInstanceID(void)
{
	return ThreadInstanceCounter++;

}

}
