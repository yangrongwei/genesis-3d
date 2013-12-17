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
#if (__ANDROID__ || __APPLE__)
#include "stdneb.h"
#include "linuxevent.h"
#ifdef __ANDROID__
#include <asm-generic/errno.h>
#endif
#if __APPLE__
#include <sys/time.h>
#include <sys/errno.h>
#endif
HANDLE Linux_CreateEvent(void *pSec,bool bManualReset,bool bInitialState,char *pStr)
{
	HANDLE handle = n_new(LinuxHandle);
	pthread_cond_init(&handle->cond, 0);
	pthread_mutex_init(&handle->mtx,NULL);
	handle->manual_reset = bManualReset;
	handle->signaled = bInitialState;
	return handle;
}

void Linux_CloseHandle(HANDLE handle)
{
	if(NULL == handle)
	{
		return;
	}

	pthread_mutex_destroy(&handle->mtx);
	pthread_cond_destroy(&handle->cond);
	n_delete(handle);
}

void Linux_SetEvent(HANDLE handle)
{
	if(NULL == handle)
	{	
		return;
	}

	CLocker lock(&handle->mtx);

	if(handle->manual_reset)
	{
		pthread_cond_broadcast(&handle->cond);
	}
	else
	{
		pthread_cond_signal(&handle->cond);
	}

	handle->signaled = true;
}

void Linux_ResetEvent(HANDLE handle)
{
	if(NULL == handle)
	{
		return;
	}

	CLocker lock(&handle->mtx);
	handle->signaled = false;
}

int Linux_WaitForSingleObject(HANDLE handle,unsigned int timeout)
{
	if(NULL == handle)
	{
		return 0;
	}

	CLocker lock(&handle->mtx);
	int ret = 0;
	if(!handle->signaled)
	{
		if(!timeout) ///no time for waiting
		{
			return WAIT_TIMEOUT;
		}
		else
		{
			timespec tm;
			if (INFINITE != timeout)
			{
				/// set timeout
				timeval now;
				gettimeofday(&now, 0);
				tm.tv_sec = now.tv_sec + timeout / 1000 + (((timeout % 1000) * 1000 + now.tv_usec) / 1000000);
				tm.tv_nsec = (((timeout % 1000) * 1000 + now.tv_usec) % 1000000) * 1000;
			}
			/// wait until condition thread returns control
			do
			{
				ret = (INFINITE == timeout ? pthread_cond_wait(&handle->cond,&handle->mtx) :
					pthread_cond_timedwait(&handle->cond, &handle->mtx, &tm));
			}
			while (!ret && !handle->signaled);
		}
	}
	/// adjust signaled member
	switch(ret)
	{
	case 0: // success
		if (!handle->manual_reset)
		{
			handle->signaled = false;
		}
		return WAIT_OBJECT_0;

	case ETIMEDOUT:

	default:
		return WAIT_TIMEOUT;
	}
}

#endif