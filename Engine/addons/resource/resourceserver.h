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
/** \file resourceserver.h
* \brief 

1、管理资源
2、管理资源的调度请求
1、资源只允许加载一次（UnLoaded状态时）。加载后的结果是成功(Loaded)或者失败(Failed)
2、资源要再次加载，需要先手动UnLoad。
3、资源加载的方式
同步：  在调用线程从存储设备获取内存流，将内存流解析为资源对象
异步：  Step1 调用线程通知IO线程，由IO线程异步从存储设备获取内存流
Step2 调用线程通知资源线程，由资源线程异步从内存流解析出临时资源对象
Step3 调用线程从临时资源对象将数据交换到真正的资源对象
4、资源存储方式。 通过线程，但是和调用线程同步
Step1  调用线程通知资源线程，等待资源线程从资源生成内存流
Step2  调用线程通知IO线程，等待IO线程将内存流写出到存储设备
*/
#ifndef __resourceserver_H__
#define __resourceserver_H__
#include "core/refcounted.h"
#include "resource/resource.h"
#include "core/singleton.h"
#include "util/delegate.h"
#include "util/queue.h"
#include "util/list.h"
#include "resource/resourceinterface.h"

#include "io/iointerfaceprotocol.h"
#include "timing/timer.h"

namespace Resources
{
	// 加载资源的回调参数
	struct LoadedArg
	{	
		LoadedArg(): processOK(false) { };
		bool processOK;	//	是否加载成功
		GPtr<Resource> res;	//	加载的资源
	};

	// 某种资源在读写时，使用的编解码器的注册器. 以在系统启动和结束时，完成编解码器的初始化和清理操作。
	class ResCodecReg: public Core::RefCounted
	{
		__DeclareClass(ResCodecReg);
	public:
		virtual void Open(void) {  }
		virtual void Close(void) {  }
	};


	class ResourceServer: public Core::RefCounted
	{
		__DeclareClass(ResourceServer);
		__DeclareImageSingleton(ResourceServer);
	public:
		ResourceServer();
		virtual ~ResourceServer();

		/**
		* Open  初始化ResourceServer
		* @return: void  
		* @see: 
		* @remark:  
		*/
		void Open(void);

		/**
		* IsOpen  是否已经初始化
		* @return: bool  
		* @see: 
		* @remark:  
		*/
		bool IsOpen(void) const;

		/**
		* Close  关闭接口，释放所有的资源
		* @return: void  
		* @see: 
		* @remark:  
		*/
		void Close(void);

		/**
		* RegisterResourceType  注册资源的读写器。需要在Open之前调用
		* @param: const Core::Rtti * resType	资源类型的Rtti信息
		* @param: const Util::FourCC & typeFilter  标示资源的filter，以支持从多种数据格式中读取资源，系统默认资源格式的filter是'CYWJ'
		* @param: const Core::Rtti * loaderType  资源类型和filter 对应的读取器
		* @param: const Core::Rtti * saverType  资源类型和filter  对应的写入器
		* @param: GPtr<ResCodecReg>& codecReg  Loader和Saver可能使用第三方的编解码器，这些编解码器可能需要初始化操作。在ResourceServer Open和Close时，将会调用对应操作
		* @return: void  
		* @see: 
		* @remark:  
		*/
		void RegisterResourceType( const Core::Rtti* resType,
			const Util::FourCC& typeFilter,
			const Core::Rtti* loaderType,
			const Core::Rtti* saverType,
			const GPtr<ResCodecReg>& codecReg = GPtr<ResCodecReg>() );

		/**
		* RegisterDefaultResouceTypes  注册系统中默认的资源类型、filter和读写器等。需要在Open之前调用
		* @return: void  
		* @see: 
		* @remark:  默认注册MeshRes、ImageRes、SkeletonRes、AnimationRes
		*/
		void RegisterDefaultResouceTypes();

		/**
		* CreateOrGetResource  创建一个资源或者得到一个已经存在的资源。
		* @param: const ResourceId & resID  资源ID
		* @param: const Core::Rtti * ResType   资源类型
		* @return: GPtr<Resource>  返回资源指针. 创建失败,返回空指针，
		* @see: 
		* @remark:  
		*/
		GPtr<Resource> CreateOrGetResource( const ResourceId& resID, const Core::Rtti* ResType );

		/**
		* HasResource  判断resID指向的资源是否存在
		* @param: const ResourceId & resID  
		* @return: bool  
		* @see: 
		* @remark:  
		*/
		bool HasResource(const ResourceId& resID);

		/**
		* GetResource  根据资源ID获取一个已经存在的资源
		* @param: const ResourceId & resID  
		* @return: GPtr<Resource>  资源不存在，返回空指针
		* @see: 
		* @remark:  
		*/
		GPtr<Resource> GetResource( const ResourceId& resID );

		/**
		* LoadResource  同步/异步 加载/重新加载资源数据  
		* @param: const GPtr<Resource> & res  要加载的资源指针
		* @param: bool bAsyn  是否开启异步加载
		* @param: const Util::FourCC & typeFilter  资源的filter，默认是'CYWJ'  
		* @param: const Core::Rtti * manuLoaderType  手动设置的资源读取器类型。
		1、为空时，使用typeFilter注册的。如果找不到，则加载资源失败，返回空指针; 
		2、不为空时，使用用户自定义的读取器 
		* @return: bool                              同步加载：bool 表示是否加载成功。
		异步加载：bool 表示成功加入到加载队列；false表示已经在加载队列中
		* @see: 
		* @remark:  资源只能加载一次,无论成功或者失败。需要多次加载，先卸载。然后再加载
		*/
		bool LoadResource( const GPtr<Resource>& res,
			bool bAsyn = true,
			const Util::FourCC& typeFilter = 'CYWJ',
			const Core::Rtti* manuLoaderType = NULL );

		/**
		* SaveResource  同步存储一个资源
		* @param: const GPtr<Resource> & res  要存储的资源指针
		* @param: const IO::URI & uri  资源的存储路径。为空时，使用res的ID标记的资源路径
		* @param: const Util::FourCC & typeFilter  存储的filter，默认是'CYWJ'		                                              
		* @param: const Core::Rtti * manuSaverType  手动设置的资源写入器类型
		1、为空时，使用typeFilter注册的。如果找不到，则存储失败  
		2、否则，使用用户传入的写入器
		* @return: bool  返回存储是否成功
		* @see: 
		* @remark:  
		*/
		bool SaveResource( const GPtr<Resource>& res,
			const IO::URI& uri = IO::URI(), 
			const Util::FourCC& typeFilter = 'CYWJ',
			const Core::Rtti* manuSaverType = NULL );
		/**
		* Flush  刷新资源数据。将线程加载的资源数据交换到主线程。该函数将会发出资源加载的回调通知
		* @param: void  
		* @return: void  
		* @see: 
		* @remark:  该函数应该每帧调用。
		*/
		void Flush(void);


		/**
		* UnLoadUnreferencedResources  
		* @param: void  
		* @return: void  
		* @see: 
		* @remark:  this method is not fast
		*/
		void UnLoadUnreferencedResources(void);

		/**
		* DicardUnreferencedResources  删除未使用的资源
		* @param: void  
		* @return: void  
		* @see: 
		* @remark:  this method is slow
		*/
		void DicardUnreferencedResources(void);

	protected:
		IO::URI _ConstructURI( const IO::URI& defaultUri, 
			const ResourceId& resID );

		const Core::Rtti* _ConstructLoaderOrSaverType( const Core::Rtti* defaultType, 
			const Core::Rtti* resType,
			const Util::FourCC& typeFilter,
			bool bloader );

		//	同步加载资源
		bool _SynLoad(const GPtr<Resource>& res, const ResourceId& uri, const GPtr<ResourceLoader>& resLoader);	

		//	异步加载资源
		bool _AsynPrepare(const GPtr<Resource>& res, const ResourceId& uri, const GPtr<ResourceLoader>& resLoader);	

		void _FlushReadList(const Timing::Timer& t ,Timing::Tick max_tick);
		void _FlushPrepareList(const Timing::Timer& t, Timing::Tick max_tick);

	protected:
		// 资源的读取器和写入器的注册 数据结构
		struct LoadSaveRegistry 
		{
			const Core::Rtti* Loader;
			const Core::Rtti* Saver;
			GPtr<ResCodecReg> codecReg;
		};
		typedef Util::Dictionary<Util::FourCC, LoadSaveRegistry> ResFilterRegistry;
		typedef Util::Dictionary<const Core::Rtti*, ResFilterRegistry> ResRegistry;
		typedef Util::Dictionary< ResourceId, GPtr<Resource> > ResMap;

		bool mIsOpen;
		ResRegistry mResReg;	//	注册的资源读写器
		ResMap mResources;	//	资源列表

		// 用于异步加载的数据结构和变量

		struct PrepareStub	//	IO调用申请的本地存根
		{
			GPtr<Resource> res;	//	加载的资源
			GPtr<ResourceLoader> loader;
			GPtr<IO::ReadStream> msg_stream;	//	和IO线程通信的消息
		};

		struct ReadStub		// 序列化调用申请的本地存根
		{
			GPtr<Resource> res;	//	加载的资源
			GPtr<ResMsg> msg_loader;	//	和序列化线程通信的消息
		};

		typedef Util::List<PrepareStub> PrepareStubbList;
		typedef Util::List<ReadStub>    ReadStubList;

		GPtr<ResourceInterface> mThreadInterface;//	序列化线程。从内存块中反序列化资源
		PrepareStubbList mAsynPrepareQueue;	//	记录正在IO线程中，从外部设备进行IO的资源
		ReadStubList mAsynReadQueue;	//	记录正在序列化线程中，进行反序列化的资源
	};
	//------------------------------------------------------------------------
	inline
		bool
		ResourceServer::IsOpen() const
	{
		return mIsOpen;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		ResourceServer::HasResource(const ResourceId& resID)
	{
		return mResources.FindIndex( resID ) != InvalidIndex;
	}
	//------------------------------------------------------------------------
	inline
		GPtr<Resource> 
		ResourceServer::GetResource( const ResourceId& resID )
	{
		IndexT findIndex = mResources.FindIndex( resID );
		if ( InvalidIndex != findIndex )
		{
			return mResources.ValueAtIndex(findIndex);
		}
		else
		{
			return GPtr<Resource>(0); 
		}
	}
}












#endif // __resourceserver_H__
