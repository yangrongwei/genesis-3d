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
#ifndef __ThreadRuntimeInfo_H__
#define __ThreadRuntimeInfo_H__

#include "core/refcounted.h"


namespace Threading
{
	// 允许每一个线程中包含的最大单件实例数量
	const SizeT MaxThreadInstanceNum = 256;

	class ThreadRunTimeInfo
	{
	public:
		ThreadRunTimeInfo(void);
		~ThreadRunTimeInfo(void);
		
		char* GetInstance( IndexT i );

		void SetInstance( IndexT i , char* pIns );

		bool HasInstance( IndexT i );

	public:
		// 当前线程中单件实例数组
		char* mInstanceArray[MaxThreadInstanceNum];
		// 线程名字
		const char* mThreadName;
	public:

		/// *******禁止外部调用*******     分配唯一的一个ID给线程独立的单件。
		static IndexT GetThreadInstanceID(void);

		/// 设置线程独立的运行时环境,每个线程只允许调用一次。主线程必须在工作线程和创建对象之前调用。工作线程必须在刚刚启动和创建对象之前调用。
		static void SetupMyThreadRunTime( const char* threadName );

		/// 必须在线程销毁时调用.主线程必须最后调用 
		static void DestoryThreadRunTime( bool isMainThread = false );

		/// 得到当前线程的运行时
		static Threading::ThreadRunTimeInfo* GetMyThreadRuntime( void );

	private:
		static IndexT ThreadInstanceCounter;
		static IndexT mTlsSlot;	//	利用Tls来存储线程运行时信息
	};

	//------------------------------------------------------------------------
	inline char* ThreadRunTimeInfo::GetInstance( IndexT i )
	{
		n_assert( i >=0 && i < MaxThreadInstanceNum );
		n_assert( mInstanceArray[i] );
		return mInstanceArray[i];
	}
	//------------------------------------------------------------------------
	inline void ThreadRunTimeInfo::SetInstance( IndexT i , char*  pIns )
	{
		n_assert( i >=0 && i < MaxThreadInstanceNum );
		mInstanceArray[i] = pIns;
	}
	//------------------------------------------------------------------------
	inline bool ThreadRunTimeInfo::HasInstance( IndexT i )
	{
		n_assert( i >=0 && i < MaxThreadInstanceNum );
		return mInstanceArray[i] != NULL;
	}

}







#endif // __ThreadRuntimeInfo_H__
