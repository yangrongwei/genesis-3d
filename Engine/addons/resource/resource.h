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
#ifndef __resource_H__
#define __resource_H__

#include "core/refcounted.h"
#include "util/stringatom.h"
#include "io/stream.h"
#include "core/weakptr.h"
#include "resource/resourcebase.h"
#include "resourcepriority.h"

namespace Resources
{
	typedef Util::StringAtom ResourceId; 


	struct ReferenceResource
	{
		Resources::ResourceId id;
		Resources::ResourceType type;
		inline ReferenceResource()
			:type(RR_Unknown)
		{

		}

		inline ReferenceResource(const Resources::ResourceId& id, Resources::ResourceType type)
		{
			this->id = id;
			this->type = type;
		}
	};

	class Resource;
	class ResourceNotifier;
	class ResourceServer;

	//-------------------------------资源读取器和写入器基类-----------------------------------------
	class ResourceLoaderSaver
	{
	public:
		void SetStream(const GPtr<IO::Stream>& pStream )
		{
			mStream = pStream;
		}
		const GPtr<IO::Stream>& GetStream(void) const
		{
			return mStream;
		}
	protected:
		ResourceLoaderSaver() { };
		GPtr<IO::Stream> mStream;	     //	要读取/写入的流
	};
	// 从Stream中读取序列化资源
	class ResourceLoader: public Core::RefCounted, public ResourceLoaderSaver
	{
		__DeclareClass(ResourceLoader);
	public:
		ResourceLoader(){ };
		virtual ~ResourceLoader(){ };
		virtual bool LoadResource(Resource* res ){ return false; };
	};
	// 将资源序列化到Stream中
	class ResourceSaver:  public Core::RefCounted, public ResourceLoaderSaver
	{
		__DeclareClass(ResourceSaver);
	public:
		ResourceSaver(){ };
		virtual ~ResourceSaver() { };
		virtual bool SaveResource( Resource* res ) { return false; };
	};

	//------------------------------资源基类------------------------------------------
	class Resource : public Core::RefCounted
	{
		__DeclareClass(Resource);
	public:
		enum State
		{
			UnLoaded,
			Loaded,
			Failed
		};

		/// constructor
		Resource();
		/// destructor
		virtual ~Resource();

		/**
		* GetState  得到资源的状态
		* @param: void  
		* @return: Resources::Resource::State  
		* @see: 
		* @remark:  
		*/
		State GetState(void) const;

		/**
		* SetManuLoad  设置是否是手动加载
		* @param: bool bManu  
		* @return: void  
		* @see: 
		* @remark:  手动加载的资源不会自动卸载。 必须手动调用Resource::Unload函数，并且，卸载之后，仍然必须手动加载
		*/
		void SetManuLoad(bool bManuLoad );

		/**
		* GetManuLoad  判断是否是手动加载
		* @param: void  
		* @return: bool  
		* @see: 
		* @remark:  
		*/
		bool IsManuLoad(void) const;

		/**
		* IsAsynProcessing  资源是否在异步处理中
		* @return: bool  
		* @see: 
		* @remark:  
		*/
		bool IsAsynProcessing() const;

		/**
		* SetResourceId  set the resource identifier
		* @param: const ResourceId & id  
		* @return: void  
		* @see: 
		* @remark:  !!!!!! nerver change resourceid after resource create!!!!!!!!!!
		*/
		void SetResourceId(const ResourceId& id);

		/**
		* GetResourceId  get the resource identifier
		* @return: const ResourceId&  
		* @see: 
		* @remark:  
		*/
		const ResourceId& GetResourceId() const;

		/**
		* AttachNotifier  增加一个状态变化的通知回调
		* @param: const WeakPtr<ResourceNotifier> & notifier  
		* @return: void  
		* @see: 
		* @remark:  ResourceNotifier的生命期由外部管理
		*/
		void AttachNotifier(const WeakPtr<ResourceNotifier>& notifier );

		/**
		* DeattachNotifier  删除一个状态变化的通知回调
		* @param: const WeakPtr<ResourceNotifier> & notifier  
		* @return: void  
		* @see: 
		* @remark:  ResourceNotifier的生命期由外部管理
		*/
		void DeattachNotifier(const WeakPtr<ResourceNotifier>& notifier);

		/**
		* Load  加载/重新加载一个资源。 数据从 ResourceLoader->Resource
		* @param: const GPtr<ResourceLoader> & loader  
		* @return: bool  加载/重新加载了全部或者部分数据（有数据变化），返回true。否则，返回false
		* @see: 
		* @remark:  当本次加载过程成功时，如果ResourceLoader::GetEndClipIndex是MaxResClipCount，则资源状态为Loaded；否则，资源为Unloaded/Falied/LoadedParty->LoadedParty
		当本次加载过程失败时，则变更为Failed。假设Loader加载失败会使已有的资源数据全部失效）
		*/
		virtual bool Load( const GPtr<ResourceLoader>& loader );

		/**
		* Save  存储资源。 数据从Resource->ResourceSaver
		* @param: const GPtr<ResourceSaver> & saver  
		* @return: bool  是否写入成功。
		* @see: 
		* @remark:  是写入到内存流或者文件流，取决于ResouceSaver
		*/
		virtual bool Save( const GPtr<ResourceSaver>& saver );

		/**
		* UnLoad  卸载所有加载的资源数据。资源状态变更为UnLoad
		* @return: void  
		* @see: 
		* @remark:  
		*/
		virtual void UnLoad(void);

		/**
		* SwapLoad  从一个临时资源中通过数据交换，快速的获取资源数据
		* @param: const GPtr<Resource> & tempResData   tempResData为空,UnLoaded或者Falied状态，或者要交换的两个资源的RTTI不相等，交换失败; 
		* @return: bool 是否交换成功  
		* @see: ResourceServer 使用该函数在当前资源和线程中加载的临时资源之间快速的交换数据。避免数据拷贝
		* @remark:  
		*/
		virtual bool SwapLoad(const GPtr<Resource>& tempResData );

		/**
		* CalculateRuntimeSize  计算资源运行时占用的内容大小. 子类应派生该函数，完成实际的计算过程
		* @param: void  
		* @return: SizeT  
		* @see: 
		* @remark:  this is not fast
		*/
		virtual SizeT CalculateRuntimeSize(void) const;

		/**
		* SetState  修改状态，并通知Notifier
		* @param: State newState  
		* @return: void  
		* @see: 
		* @remark:  !!!!!!!!!!应该通过Load,UnLoad,SwapLoad函数去修改。谨慎调用
		*/
		void SetState( State newState);

		static ResourceId EmptyResID;
	protected:

		// 设置异步处理资源的标志
		void AddAsynProcessingIndex(void);
		void DecAsynProcessingIndex(void);

		// 子类应派生该函数，完成真正的数据交换
		virtual bool SwapLoadImpl( const GPtr<Resource>& tempRes );

		// 子类派生，完成真正的数据卸载操作
		virtual void UnLoadImpl(void);

		// 从另一个resource得到一些加载需要的初始化的参数。resourceserver会用于给临时资源赋初始值
		virtual void InitLoadParam( const GPtr<Resource>& res );
	protected:
		State mState;
		ResourceId mResourceID;
		IndexT mAsynProcessingIndex;
		bool mManuLoad;
		Util::Array< WeakPtr<ResourceNotifier> > mNotifierList;

		friend class ResourceServer;
	};
	//------------------------------资源状态变化后的通知回调------------------------------------------
	class ResourceNotifier: public Core::RefCounted
	{
		__DeclareClass(ResourceNotifier);
	public:
		ResourceNotifier()
			:mAttachCount(0) {
		};

		virtual ~ResourceNotifier() { };
		// is notifier attach to a resource
		bool IsAttached(void) const{
			n_assert(mAttachCount >= 0 );
			return mAttachCount != 0;
		}

	protected:
		virtual void Notify(Resource* res, Resource::State preState) { };

		void Attach(Resource* res){
			++mAttachCount;
		}
		void Deattach(Resource* res){
			--mAttachCount;
		}
		IndexT mAttachCount;
		friend class Resource;
	};

	//------------------------------------------------------------------------
	inline
		Resource::State 
		Resource::GetState(void) const
	{
		return mState;
	}
	//------------------------------------------------------------------------
	inline 
		void
		Resource::SetResourceId(const ResourceId& id)
	{
		this->mResourceID = id;
	}
	//------------------------------------------------------------------------------
	inline 
		const ResourceId&
		Resource::GetResourceId() const
	{
		return this->mResourceID;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		Resource::IsAsynProcessing() const
	{
		return mAsynProcessingIndex > 0;
	}
	//------------------------------------------------------------------------
	inline
		void 
		Resource::AddAsynProcessingIndex(void)
	{
		++mAsynProcessingIndex;
	}
	//------------------------------------------------------------------------
	inline
		void 
		Resource::DecAsynProcessingIndex(void)
	{
		--mAsynProcessingIndex;
	}
	//------------------------------------------------------------------------
	inline
		void 
		Resource::SetManuLoad(bool bManuLoad )
	{
		mManuLoad = bManuLoad;
	}
	//------------------------------------------------------------------------
	inline
		bool 
		Resource::IsManuLoad(void) const
	{
		return mManuLoad;
	}

}	//	namespace Resources



#endif // __resource_H__
