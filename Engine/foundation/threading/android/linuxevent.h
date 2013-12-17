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
#ifndef __LINUXEVENT_H__
#define __LINUXEVENT_H__

#include "core/types.h"
#include <pthread.h>

typedef struct 
{
	pthread_mutex_t mtx;
	pthread_cond_t  cond;
	bool            manual_reset;
	bool            signaled;
}LinuxHandle, *HANDLE;

#define INFINITE      0xFFFFFFFF
#define WAIT_TIMEOUT  0x00000102L
#define WAIT_OBJECT_0 0
#define TRUE          true



extern HANDLE Linux_CreateEvent(void *pSec,bool bManualReset,bool bInitialState,char *pStr);

extern void Linux_CloseHandle(HANDLE handle);

extern void Linux_SetEvent(HANDLE handle);

extern void Linux_ResetEvent(HANDLE handle);

extern int Linux_WaitForSingleObject(HANDLE handle,unsigned int timeout);

class CLocker
{
public:
	explicit CLocker(pthread_mutex_t *lock = NULL):m_lock(lock)
	{
		pthread_mutex_lock(m_lock);
	}
	~CLocker()
	{
		pthread_mutex_unlock(m_lock);
	}
private:
	pthread_mutex_t *m_lock;
	CLocker();
	CLocker& operator=(const CLocker &rhs);
};

#endif