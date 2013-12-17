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
#ifndef __resourceinterface_H__
#define __resourceinterface_H__

#include "messaging/handlerthreadbase.h"
#include "threading/safequeue.h"
#include "interface/interfacehandlerbase.h"
#include "interface/interfacebase.h"
#include "resource/resource.h"



namespace Resources
{
	//------------------------------消息类定义------------------------------------------
	class ResMsg: public Messaging::Message
	{
		__DeclareClass(ResMsg);
		__DeclareMsgId;
	public:
		ResMsg(): mResult(false)
		{  
		};
		void SetResult(bool bOK )
		{
			mResult = bOK;
		}
		bool GetResult(void) const
		{
			return mResult;
		}
		void SetResource(const GPtr<Resource>& res)
		{ 
			mRes = res; 
		};
		const GPtr<Resource>& GetResource(void) const 
		{ 
			return mRes; 
		};
		void SetSream(const GPtr<IO::Stream>& stream )	//	
		{
			mStream = stream;
		}
		const GPtr<IO::Stream>& GetStream(void) const
		{
			return mStream;
		}
	protected:
		bool mResult;	    //	消息处理之后，得到读取/写入 成功或者失败的结果
		GPtr<Resource> mRes;	//	读取/写入 的资源指针
		GPtr<IO::Stream> mStream;	//	内部创建，用于获取读/写的数据流
	};
	class ResLoadMsg: public ResMsg
	{
		__DeclareClass(ResLoadMsg);
		__DeclareMsgId;
	public:
		ResLoadMsg()
		{ };
		void SetLoader(const GPtr<ResourceLoader>& loader )
		{
			mLoader = loader;
		}
		const GPtr<ResourceLoader>& GetLoader(void) const
		{
			return mLoader;
		}
	protected:
		GPtr<ResourceLoader> mLoader;	//	Loader
	};
	class ResSaveMsg: public ResMsg
	{
		__DeclareClass(ResSaveMsg);
		__DeclareMsgId;
	public:
		ResSaveMsg()
		{ };
		void SetSaver(const GPtr<ResourceSaver>& saver )
		{
			mSaver = saver;
		}
		const GPtr<ResourceSaver>& GetSaver(void) const
		{
			return mSaver;
		}
	protected:
		GPtr<ResourceSaver> mSaver;	//	saver
	};
	//--------------------------------资源线程接口----------------------------------------
	class ResourceInterface: public Interface::InterfaceBase
	{
		__DeclareSubClass(ResourceInterface, Interface::InterfaceBase );
	public:
		ResourceInterface();
		virtual ~ResourceInterface();

		/**
		* Open  初始化ResrourceInterface
		* @return: void  
		* @see: 
		* @remark:  
		*/
		virtual void Open();
	};
	//------------------------------线程处理句柄------------------------------------------
	class ResourceHandler: public Interface::InterfaceHandlerBase
	{
		__DeclareSubClass(ResourceHandler, Interface::InterfaceHandlerBase);
	public:
		/// constructor
		ResourceHandler();
		/// destructor
		virtual ~ResourceHandler();

		/// open the handler
		virtual void Open();
		/// close the handler
		virtual void Close();
		/// handle a message, return true if handled
		virtual bool HandleMessage(const GPtr<Messaging::Message>& msg);

	protected:
		void OnLoad( const GPtr<ResLoadMsg>& msg );
		void OnSave( const GPtr<ResSaveMsg>& msg );
	};
}	//	namespace Resources





#endif // __resourceinterface_H__
