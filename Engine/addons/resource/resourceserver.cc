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
#include "resource/resource_stdneb.h"
#include "resource/resourceserver.h"

// 用于注册默认的读写器
#include "resource/imageresloader.h"
#include "resource/meshresloader.h"
#include "resource/meshressaver.h"
#include "resource/skeletonresloader.h"
#include "resource/skeletonressaver.h"
#include "resource/animationresloader.h"
#include "resource/animationressaver.h"
#include "resource/physxmaterialloader.h"
#include "resource/rawres.h"
#include "resource/rawresloader.h"
#include "resource/rawressaver.h"
#include "resource/templateres.h"
#include "resource/templateresloader.h"
#include "resource/templateressaver.h"
#include "resource/audiores.h"
#include "resource/audioresloader.h"
#include "resource/audioressaver.h"
#include "resource/physxmaterialres.h"
#include "resource/physxmaterialloader.h"
#include "resource/physxmaterialsaver.h"
#include "resource/materialres.h"
#include "resource/materialresloader.h"
#include "resource/materialressaver.h"
#include "resource/spritepackageres.h"
#include "resource/spritepackageresloader.h"
#include "resource/spritepackageressaver.h"

#include "timing/timer.h"

#include "foundation/io/ioserver.h"
#include "foundation/io/stream.h"

#include "io/iointerface.h"
#include "serialization/serializeserver.h"
#include "serialization/xmserialize.h"
#if __ANDROID__
#include "io/ioserver.h"
#include "io/memorystream.h"
#include "rendersystem/gles/OpenGLES.h"
#endif

namespace Resources{

	__ImplementClass(Resources::ResourceServer,'RSSR', Core::RefCounted);
	__ImplementClass(Resources::ResCodecReg, 'RCRG', Core::RefCounted);
	__ImplementImageSingleton( ResourceServer );
	// 判断外部没有引用的资源，其引用计数是1 （ResourceServer::mResources ）
	const int UnRefResCounter = 1; 
	//------------------------------------------------------------------------
	ResourceServer::ResourceServer()
		:mIsOpen(false)
	{
		__ConstructImageSingleton;
	}
	//------------------------------------------------------------------------
	ResourceServer::~ResourceServer()
	{
		n_assert(!mIsOpen);

		__DestructImageSingleton;
	}
	//------------------------------------------------------------------------
	void 
		ResourceServer::Open()
	{
		n_assert(!mIsOpen);

		// may be need open resCodec in thread
		SizeT numReg = mResReg.Size();
		for ( IndexT indexReg = 0; indexReg < numReg; ++indexReg )
		{
			ResFilterRegistry& resFilterReg = mResReg.ValueAtIndex( indexReg );
			SizeT numFilter = resFilterReg.Size();
			for ( IndexT indexFilter = 0; indexFilter < numFilter; ++indexFilter )
			{
				LoadSaveRegistry& reg = resFilterReg.ValueAtIndex( indexFilter );
				if ( reg.codecReg.isvalid() )
				{
					reg.codecReg->Open();
				}
			}
		}


		mThreadInterface = ResourceInterface::Create();
		mThreadInterface->Open();

		mIsOpen = true;
	}
	//------------------------------------------------------------------------
	void 
		ResourceServer::Close()
	{
		n_assert(mIsOpen);

		mThreadInterface->Close();
		mThreadInterface = NULL;

		mAsynPrepareQueue.Clear();
		mAsynReadQueue.Clear();

		mResources.Clear();

		// may be need close resCodec in thread
		SizeT numReg = mResReg.Size();
		for ( IndexT indexReg = 0; indexReg < numReg; ++indexReg )
		{
			ResFilterRegistry& resFilterReg = mResReg.ValueAtIndex( indexReg );
			SizeT numFilter = resFilterReg.Size();
			for ( IndexT indexFilter = 0; indexFilter < numFilter; ++indexFilter )
			{
				LoadSaveRegistry& reg = resFilterReg.ValueAtIndex( indexFilter );
				if ( reg.codecReg.isvalid() )
				{
					reg.codecReg->Close();
				}
			}
		}

		mResReg.Clear();

		mIsOpen = false;
	}
	//------------------------------------------------------------------------
	void 
		ResourceServer::RegisterResourceType( const Core::Rtti* resType,
		const Util::FourCC& typeFilter,
		const Core::Rtti* loaderType,
		const Core::Rtti* saverType,
		const GPtr<ResCodecReg>& codecReg )
	{
		if( IsOpen() )
		{
			n_assert(false);
			return;
		}

		if ( resType == NULL )
		{
			return;
		}

		IndexT resIndex = mResReg.FindIndex( resType );
		if ( InvalidIndex == resIndex )
		{
			mResReg.Add( resType, ResFilterRegistry() );
			resIndex = mResReg.FindIndex(resType );
		}
		n_assert( InvalidIndex != resIndex );

		ResFilterRegistry& resFilterReg = mResReg.ValueAtIndex( resIndex );

		IndexT filterIndex = resFilterReg.FindIndex( typeFilter );
		if ( InvalidIndex == filterIndex )
		{
			resFilterReg.Add(typeFilter, LoadSaveRegistry() );
			filterIndex = resFilterReg.FindIndex( typeFilter );
		}
		n_assert( InvalidIndex != filterIndex  );

		LoadSaveRegistry& lsReg = resFilterReg.ValueAtIndex( filterIndex );
		lsReg.Loader = loaderType;
		lsReg.Saver = saverType;
		lsReg.codecReg = codecReg;

		if ( lsReg.Loader && !lsReg.Loader->IsDerivedFrom(ResourceLoader::RTTI ) )
		{
			n_warning("ResourceServer::RegisterResourceType: %s is not resource Loader\n", lsReg.Loader->GetName().AsCharPtr() );
			lsReg.Loader = NULL;
		}

		if ( lsReg.Saver && !lsReg.Saver->IsDerivedFrom(ResourceSaver::RTTI ) )
		{
			n_warning("ResourceServer::RegisterResourceType: %s is not resource Saver\n", lsReg.Saver->GetName().AsCharPtr() );
			lsReg.Saver = NULL;
		}

	}
	//------------------------------------------------------------------------
	void 
		ResourceServer::RegisterDefaultResouceTypes()
	{
		if ( IsOpen() )
		{
			n_assert(false);
			return;
		}

		RegisterResourceType( &MeshRes::RTTI, 'CYWJ', &MeshResLoader::RTTI, &MeshResSaver::RTTI ) ;
		RegisterResourceType( &SkeletonRes::RTTI, 'CYWJ', &SkeletonResLoader::RTTI, &SkeletonResSaver::RTTI );
		RegisterResourceType( &AnimationRes::RTTI, 'CYWJ', &AnimationResLoader::RTTI, &AnimationResSaver::RTTI );
		RegisterResourceType( &RawRes::RTTI, 'CYWJ', &RawResLoader::RTTI, &RawResSaver::RTTI );
		RegisterResourceType( &TemplateRes::RTTI, 'CYWJ', &TemplateResLoader::RTTI, &TemplateResSaver::RTTI );
		RegisterResourceType( &AudioRes::RTTI, 'CYWJ', &AudioResLoader::RTTI, &AudioResSaver::RTTI );
		RegisterResourceType( &PhysXMaterialRes::RTTI, 'CYWJ', &PhysXMaterialLoader::RTTI, &PhysXMaterialSaver::RTTI );
		RegisterResourceType( &MaterialRes::RTTI, 'CYWJ', &MaterialLoader::RTTI, &MaterialSaver::RTTI );
		RegisterResourceType( &SpritePackageRes::RTTI, 'CYWJ', &SpritePackageResLoader::RTTI, &SpritePackageResSaver::RTTI );

		if ( !ImageResCodecReg::HasInstance() )
		{
			ImageResCodecReg::Create();
		}
		GPtr<ImageResCodecReg> imageCode = ImageResCodecReg::Instance();
		RegisterResourceType( &ImageRes::RTTI, 'CYWJ', &ImageResLoader::RTTI, NULL, imageCode.upcast<ResCodecReg>() ) ;


		// RegisterResourceType( , , , );
	}
	//------------------------------------------------------------------------
	GPtr<Resource> 
		ResourceServer::CreateOrGetResource( const ResourceId& resID, const Core::Rtti* ResType )
	{
		n_assert(mIsOpen);

		IndexT resFind = mResources.FindIndex( resID );
		if ( InvalidIndex != resFind )
		{
			// exist
			return mResources.ValueAtIndex( resFind );
		}
		else
		{
			if ( ResType == NULL || !ResType->IsDerivedFrom( Resource::RTTI ) )
			{
				return GPtr<Resource>(0); 
			}
			else
			{
				GPtr<Core::RefCounted> pObject = ResType->Create();
				n_assert( pObject.isvalid() );
				GPtr<Resource> pRes = pObject.downcast<Resource>();
				n_assert( pRes.isvalid() );
				pRes->SetResourceId( resID ); 
				mResources.Add(resID, pRes );

				return pRes;
			}
		}
		return GPtr<Resource>(0); 
	}
	////------------------------------------------------------------------------
	bool
		ResourceServer::LoadResource( const GPtr<Resource>& res,
		bool bAsyn /*= true*/,
		const Util::FourCC& typeFilter /*= 'CYWJ'*/,
		const Core::Rtti* manuLoaderType /*= NULL*/ )
	{
		n_assert(mIsOpen);

		if( !res.isvalid() )
		{
			return false;
		}

		// 不支持重加载，需要先UnLoad
		if ( res->GetState() == Resource::Loaded )
		{
			return true;
		}
		if ( res->GetState() == Resource::Failed )
		{
			return false;
		}

		GPtr<ResourceLoader> resLoader;
		const Core::Rtti* loaderType = _ConstructLoaderOrSaverType(manuLoaderType, res->GetRtti(), typeFilter, true );
		if ( !loaderType  )
		{
			n_warning("ResourceServer::LoadResource %s: Can Not Get Loader\n", res->GetResourceId().AsString().AsCharPtr() );
			res->SetState(Resource::Failed);
			return false; 
		}
		else
		{
			GPtr<Core::RefCounted> pObject = loaderType->Create();
			n_assert( pObject.isvalid() );
			resLoader = pObject.downcast<ResourceLoader>();
		}
		n_assert( resLoader.isvalid() );

		// 异步加载，通过主线程进行
		if ( bAsyn )
		{
			return _AsynPrepare(res, res->GetResourceId(), resLoader);//resURI
		}
		else
		{
			return _SynLoad(res, res->GetResourceId(), resLoader);//resURI
		}
	}
	//------------------------------------------------------------------------
	bool 
		ResourceServer::_SynLoad(const GPtr<Resource>& res, const ResourceId& resURI, const GPtr<ResourceLoader>& resLoader)
	{
		bool bLoadOK = false;

		GPtr<IO::Stream> pStream = IO::IoServer::Instance()->ReadFileFromFileSystem(resURI);

		if ( pStream )
		{
			pStream->SetAccessMode(IO::Stream::ReadAccess);
			if ( pStream->Open() )
			{
				resLoader->SetStream(pStream);
				bLoadOK = res->Load( resLoader );
				if ( !bLoadOK )
				{
					res->SetState(Resource::Failed);
					n_warning("SynLoad Load Resource %s Failed. Not Read From Stream \n", resURI.AsString().AsCharPtr());
				}
				else
				{
					n_printf("SynLoad Load Resource %s OK \n", resURI.AsString().AsCharPtr());
				}

				pStream->Close();
			}
			else
			{
				res->SetState(Resource::Failed);
				n_warning("Syn Load Resource %s Failed. Not Open Stream \n", resURI.AsString().AsCharPtr());
			}
		}
		else
		{
			res->SetState(Resource::Failed);
			n_warning("Syn Load Resource %s Failed. Can Not Create Stream \n", resURI.AsString().AsCharPtr());
		}

		return bLoadOK;
	}
	//------------------------------------------------------------------------
	bool ResourceServer::_AsynPrepare(const GPtr<Resource>& res, const ResourceId& resURI, const GPtr<ResourceLoader>& resLoader)
	{
		// res 已经在异步加载中。 生成一个虚假的存根。避免多次加载
		if ( res->IsAsynProcessing() )
		{
			ReadStub read_stub;
			read_stub.res = res;
			mAsynReadQueue.AddBack(read_stub);	//	加入到ReadQueue中，等待资源被其他的Stub加载
			return true;
		}

		// 异步加载. 先进行外部设备的IO
		// 保存存根
		PrepareStub stub;
		stub.res = res;	// Real Res .  not Temp Res
		stub.msg_stream = IO::ReadStream::Create();
		stub.loader = resLoader;

		n_assert( stub.msg_stream.isvalid() );
		stub.msg_stream->SetFileName( resURI );
		stub.msg_stream->SetStream( IO::MemoryStream::Create() );
		IO::IoInterface::Instance()->Send( stub.msg_stream );

		// 增加资源的异步访问计数
		res->AddAsynProcessingIndex();

		mAsynPrepareQueue.AddBack(stub);

		return true;
	}
	//------------------------------------------------------------------------
	bool
		ResourceServer::SaveResource( const GPtr<Resource>& res,
		const IO::URI& uri /*= IO::URI()*/, 
		const Util::FourCC& typeFilter /*= 'CYWJ'*/,
		const Core::Rtti* manuSaverType /*= NULL*/ )
	{
		n_assert(mIsOpen);

		if( !res.isvalid() )
		{
			n_warning("ResourceServer::SaveResource: res = null\n");
			return false;
		}

		// get uri
		IO::URI resURI = _ConstructURI(uri, res->GetResourceId());
		if ( resURI.IsEmpty() )
		{
			n_warning("ResourceServer::SaveResource: Can Not Get URI\n");
			return false;
		}

		// Get Saver
		GPtr<ResourceSaver> resSaver;
		const Core::Rtti* saverType = _ConstructLoaderOrSaverType(manuSaverType, res->GetRtti(), typeFilter, false );
		if ( !saverType  )
		{
			n_warning("ResourceServer::SaveResource %s: Can Not Get Saver\n", res->GetResourceId().AsString().AsCharPtr() );
			return false; 
		}
		else
		{
			GPtr<Core::RefCounted> pObject = saverType->Create();
			n_assert( pObject.isvalid() );
			resSaver = pObject.downcast<ResourceSaver>();
		}
		n_assert( resSaver.isvalid() );

		// 安全的写入方法是在序列化线程序列化到内存，然后从IO线程写出到硬盘。 
		// 序列化到内存
		GPtr<ResSaveMsg> msg_save = ResSaveMsg::Create();
		msg_save->SetResource( res );
		msg_save->SetSaver( resSaver );
		msg_save->SetSream( IO::MemoryStream::Create() );
		msg_save->GetStream()->SetURI(uri);
		mThreadInterface->SendWait( msg_save );
		if ( !msg_save->GetResult() )
		{
			return false;
		}
		return true;

		//// 写出到硬盘
		//GPtr<IO::WriteStream> io_msg = IO::WriteStream::Create();
		//io_msg->SetStream( msg_save->GetStream() );
		//io_msg->SetURI(uri);
		//IO::IoInterface::Instance()->SendWait(io_msg);

		//return io_msg->GetResult();  
	}
	//------------------------------------------------------------------------
	const Timing::Tick Max_Tick_One_Frame = 5;	//	每帧允许的最大tick时间（毫秒）
	void 
		ResourceServer::Flush(void)
	{
		// 时间控制，避免flush的时间太长，影响效率
		Timing::Timer t;
		t.Start();

		// 优先进行反序列化的工作
		_FlushReadList(t, Max_Tick_One_Frame);

		t.Reset();
		_FlushPrepareList(t, Max_Tick_One_Frame);
	}
	//------------------------------------------------------------------------
	void 
		ResourceServer::_FlushReadList(const Timing::Timer& t, Timing::Tick max_tick)
	{
		ReadStubList::Iterator endItor = mAsynReadQueue.End(); 
		for ( ReadStubList::Iterator itor = mAsynReadQueue.Begin(); itor != endItor; )
		{
			/*Timing::Tick tick = t.GetTicks();
			if ( tick > Max_Tick_One_Frame)
			{
			return;
			}*/

			bool isRead = false;

			// 资源的状态不是Unload 或者虚假存根 , 说明在主线程加载过了。不进行重复加载
			if( itor->res->GetState() != Resource::UnLoaded )
			{
				isRead = true;
			}

			if ( itor->msg_loader && itor->msg_loader->Handled() )	
			{
				isRead = true;
				if ( itor->msg_loader->GetResult() )
				{
					if( itor->res->SwapLoad( itor->msg_loader->GetResource() ) )
					{
						n_printf("Asyn Load Resource %s OK \n", itor->res->GetResourceId().AsString().AsCharPtr() );
					}
					else
					{
						n_warning("Asyn Load Resource %s Failed. Swap Load Failed \n", itor->res->GetResourceId().AsString().AsCharPtr() );
						itor->res->SetState( Resource::Failed );
					}

				}
				else
				{
					n_warning("Asyn Load Resource %s Failed. Not Read From Stream \n", itor->res->GetResourceId().AsString().AsCharPtr() );
					itor->res->SetState( Resource::Failed );
				}
			}

			if ( isRead )
			{
				// 减少资源的异步访问计数
				itor->res->DecAsynProcessingIndex();

				// 移除存根
				ReadStubList::Iterator Removeitor = itor;
				++itor;
				mAsynReadQueue.Remove( Removeitor );
			}
			else
			{
				++itor;
			}
		}
	}
	void 
		ResourceServer::_FlushPrepareList(const Timing::Timer& t, Timing::Tick max_tick)
	{
		PrepareStubbList::Iterator endItor = mAsynPrepareQueue.End(); 
		for ( PrepareStubbList::Iterator itor = mAsynPrepareQueue.Begin(); itor != endItor; )
		{
			Timing::Tick tick = t.GetTicks();
			if ( tick > Max_Tick_One_Frame)
			{
				return;
			}

			if ( itor->msg_stream->Handled() )	
			{
				if ( itor->msg_stream->GetResult() )
				{
					// 构造一个存根，进行反序列化的操作
					GPtr<ResLoadMsg> msg = ResLoadMsg::Create();
					msg->SetLoader( itor->loader );
					msg->SetSream( itor->msg_stream->GetStream() );

					// 创建一个临时的资源
					GPtr<RefCounted> pTempResObject = itor->res->GetRtti()->Create();
					n_assert( pTempResObject.isvalid() );
					GPtr<Resource> pTempResData = pTempResObject.downcast<Resource>();
					pTempResData->InitLoadParam( itor->res );
					msg->SetResource( pTempResData );	// read to Temp Res

					//保存存根
					ReadStub stub;
					stub.res = itor->res;
					stub.msg_loader = msg;
					mAsynReadQueue.AddBack(stub);
					mThreadInterface->Send( msg );
				}
				else
				{
					n_warning("Asyn Load Resource %s Failed. Can Not Handle Stream!\n", itor->res->GetResourceId().AsString().AsCharPtr());

					itor->res->SetState( Resource::Failed );
				}


				// 移除存根
				PrepareStubbList::Iterator Removeitor = itor;
				++itor;
				mAsynPrepareQueue.Remove( Removeitor );
			}
			else
			{
				++itor;
			}
		}
	}
	//------------------------------------------------------------------------
	void 
		ResourceServer::UnLoadUnreferencedResources(void)
	{
		SizeT size = mResources.Size();
		for ( IndexT index = 0; index < size; ++index )
		{
			const GPtr<Resource> res = mResources.ValueAtIndex( index );
			if ( res->GetRefCount() <= UnRefResCounter && !res->IsManuLoad())
			{
				mResources.ValueAtIndex(index)->UnLoad();
			}
		}
	}
	//------------------------------------------------------------------------
	void 
		ResourceServer::DicardUnreferencedResources()
	{
		ResMap useRes;
		useRes.Reserve( mResources.Size() );

		useRes.BeginBulkAdd();
		SizeT size = mResources.Size();
		for ( IndexT index = 0; index < size; ++index )
		{
			if ( mResources.ValueAtIndex(index)->GetRefCount() > UnRefResCounter )
			{
				//还在使用的资源
				useRes.Add( mResources.KeyValuePairAtIndex(index) );
			}
		}
		useRes.EndBulkAdd();

		mResources.Swap(useRes);
	}
	//------------------------------------------------------------------------
	IO::URI
		ResourceServer::_ConstructURI( const IO::URI& defaultUri, 
		const ResourceId& resID )
	{
		IO::URI resURI = defaultUri;

		if ( defaultUri.IsEmpty() )
		{
			if ( resID.IsValid() )
			{
				resURI.Set( resID.AsString() );
			}
		}

		return resURI;
	}
	//------------------------------------------------------------------------
	const Core::Rtti* 
		ResourceServer::_ConstructLoaderOrSaverType( const Core::Rtti* defaultType, 
		const Core::Rtti* resType,
		const Util::FourCC& typeFilter,
		bool bloader )
	{
		const Core::Rtti* lsType = NULL;

		if ( !defaultType )
		{
			// from registry, loader must be null or valid loaderk
			IndexT resTypeFind = mResReg.FindIndex( resType );
			if ( resTypeFind != InvalidIndex )
			{
				ResFilterRegistry& resFilterReg = mResReg.ValueAtIndex(resTypeFind);
				IndexT resFilterFInd = resFilterReg.FindIndex( typeFilter );
				if ( resFilterFInd != InvalidIndex )
				{
					LoadSaveRegistry& lsReg = resFilterReg.ValueAtIndex( resFilterFInd );
					if ( bloader )
					{
						lsType = lsReg.Loader;
					}
					else
					{
						lsType = lsReg.Saver;
					}
				}
			}
		}
		else
		{
			if ( bloader )
			{
				if ( !defaultType->IsDerivedFrom( ResourceLoader::RTTI ) )
				{
					lsType = NULL;
				}
			}
			else
			{
				if ( !defaultType->IsDerivedFrom( ResourceSaver::RTTI ) )
				{
					lsType = NULL;
				}
			}
		}

		return lsType;
	}



}