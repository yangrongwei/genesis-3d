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
#include "appframework/actormanager.h"
#include "serialization/serializeserver.h"
#include "app/basegamefeature/managers/timesource.h"
#include "app/basegamefeature/managers/sceneschedulemanager.h"
#include "addons/resource/resourcemanager.h"
#include "addons/serialization/xmserialize.h"
#include "addons/serialization/binaryserialize.h"
#include "io/memorystream.h"
#include "appframework/scene.h"
#include "app/graphicfeature/components/animationcomponent.h"
#include "graphicfeature/components/cameracomponent.h"

namespace App
{    
	__ImplementClass(App::ActorTemplateFile, 'GACM', App::Manager);
	__ImplementClass(App::ActorManager, 'GAMG', App::Manager);
	__ImplementThreadSingleton(App::ActorManager);
	
	const Util::StringAtom g_EmptyTemplateName("Empty");
	const int ActorManager::ActorDeadRefCount = 1;
	//------------------------------------------------------------------------
	ActorManager::ActorManager()
	{
		__ConstructThreadSingleton;
		mCurrentClearIterator = mAllCreatedActors.begin();
	}
	//------------------------------------------------------------------------
	ActorManager::~ActorManager()
	{
		n_assert( mActiveActors.Size() == 0 );
		n_assert( mTemplateActors.Size() == 0 );
		n_assert( mAllCreatedActors.size() == 0 );
		__DestructThreadSingleton;
	}
	//------------------------------------------------------------------------
	void ActorManager::OnActivate()
	{
		Super::OnActivate();
		n_assert( mActiveActors.Size() == 0 );
	}
	//------------------------------------------------------------------------
	Actor*
	ActorManager::GetActor(IndexT index) const
	{
		if ( index < 0 || index >= GetAllActorCount() )
		{
			return NULL;
		}

		ActorList_Const_Iterator itor = mAllCreatedActors.begin();
		Util::STL::advance(itor,index);
		return *itor;
	}
	//------------------------------------------------------------------------
	void ActorManager::OnDeactivate()
	{
		mTemplateActors.Clear();
		mActiveActors.Clear();

		//销毁所有剩余的Actor, 这些Actor的子actor都会在这里，所以只需全清掉即可，不用去关注它们的父子关系。
		if (!mAllCreatedActors.empty() )
		{
			ActorList_Iterator it = mAllCreatedActors.begin();
			ActorList_Iterator end = mAllCreatedActors.end();
			while(it != end)
			{
				(*it)->_Destory(true);
				(*it)->Release();
				++it;
			}
			
			mAllCreatedActors.clear();
		}
		Super::OnDeactivate();
	}
#define CLEAR_COUNT 100
	//------------------------------------------------------------------------
	//进一步优化，采用比较极端的方法，方法必须在mAllCreatedActors.erase其他地方不调用
	//这个函数造成mAllCreatedActors迭代器的失效
	void ActorManager::_GarbageOnFrame()
	{
#if NEBULA3_DEBUG && 0
		static int testFrame = 0;
		testFrame++;
		if ( testFrame % 10 == 0)
		{
			n_printf("Actor Count = %d \n", GetAllActorCount() );
		}

#endif
		for ( uint i = 0, des = CLEAR_COUNT;
			i < des; )
		{
			if ( mAllCreatedActors.end() == mCurrentClearIterator )
			{
				mCurrentClearIterator = mAllCreatedActors.begin();
				break;
			}
			if ( (*mCurrentClearIterator)->IsDestory() )
			{
				(*mCurrentClearIterator)->_Destory();
				(*mCurrentClearIterator)->Release();
				mCurrentClearIterator = mAllCreatedActors.erase(mCurrentClearIterator);
				des--;
			}
			else
			{
				mCurrentClearIterator++;
				i ++;
			}
		}
	}
	//------------------------------------------------------------------------
	void ActorManager::DeactiveActorDelayed( GPtr<Actor>& pActor, bool forceActiveControlofChild )
	{
		ActorInDustbin actor;

		actor.mForceActiveControlofChild = forceActiveControlofChild;
		actor.mpActor       = pActor;

		ActorDustbin::Iterator iter;
		for ( iter = mArrActorDustbin.Begin(); iter!=mArrActorDustbin.End(); iter++ )
		{		
			if ( (*iter).mpActor->GetFastId() == pActor->GetFastId() )
			{
				return;
			}
		}
		mArrActorDustbin.AddBack(actor);	
	}
	//------------------------------------------------------------------------
	void ActorManager::LoadTemplateFile(const Util::String& filePath)
	{
		if ( !Serialization::SerializationServer::HasInstance() )
		{
			return;
		}

		Serialization::SerializationServer* serialize = Serialization::SerializationServer::Instance();

		GPtr<Serialization::SerializeReader> pReader = serialize->OpenReadFile( filePath, Serialization::FT_DEFAULT );
		if ( pReader )
		{
			GPtr<ActorTemplateFile> tplFile = pReader->SerializeObject<ActorTemplateFile>();
			serialize->CloseReadFile(pReader);
		}

	}
	//--------------------------------------------------------------------------------
	GPtr<Actor> ActorManager::CreateActor()
	{
		GPtr<Actor> actor = Actor::Create();
		return actor;
	}
	//--------------------------------------------------------------------------------
	GPtr<Actor> ActorManager::CreatFromTemplateRes(Resources::ResourceId resID)
	{
		GPtr<Resources::TemplateResInfo> templateResInfo = Resources::ResourceManager::Instance()->CreateTemplateResInfo(resID);

		if (templateResInfo.isvalid())
		{
			const GPtr<Resources::TemplateRes>& res = templateResInfo->GetRes().downcast<Resources::TemplateRes>();			
			GPtr<Resources::TemplateResSaver> tplresSaver = Resources::TemplateResSaver::Create();
			if(tplresSaver->SaveResource(res))
			{			
				Serialization::SerializationServer* serialize = Serialization::SerializationServer::Instance();

				GPtr<Serialization::SerializeReader> pReader = serialize->OpenReadFile( tplresSaver->GetStream(), Serialization::FT_DEFAULT );
				if ( pReader )
				{
					GPtr<Actor> act = pReader->SerializeObject<Actor>();
					serialize->CloseReadFile(pReader);
					return act;
				}
			}
			
		}
		return NULL;
	}
	//------------------------------------------------------------------------
	void ActorManager::DeleteTemplateCache(Resources::ResourceId resID)
	{
		IndexT index = mTemplateActors.FindIndex( resID.AsString() );
		if ( InvalidIndex == index )
		{
			return;
		}
		mTemplateActors.EraseAtIndex(index);
	}
	//------------------------------------------------------------------------
	GPtr<Actor> ActorManager::CreateFromTemplate( const Util::String& actorTemplateName )
	{
		GPtr<Actor> pTemplate(NULL);

		IndexT index = mTemplateActors.FindIndex( actorTemplateName );
		if ( InvalidIndex == index )
		{
			Serialization::FileType eFileType;
			pTemplate = LoadSingleTemplate(actorTemplateName,eFileType);
		}
		else
		{
			pTemplate = mTemplateActors.ValueAtIndex( index ).m_ptr;
		}

		if ( !pTemplate.isvalid() )
		{
			return NULL;
		}

		GPtr<Actor> pActor = CreateActor();
		n_assert( pActor );

		pActor->CopyFrom( pTemplate, true);
		/*因为pTemplate一定是非激活状态，所以在复制完成之后要根据字典中保存的状态信息对pActor进行设置*/
		index = mTemplateActors.FindIndex( actorTemplateName );
		if (mTemplateActors.ValueAtIndex(index).activeFlag)
		{
			pActor->Active();
		}
		else
		{
			pActor->Deactive();
		}

		pActor->SetLinkTemplate( false );

		return pActor;
	}
	//------------------------------------------------------------------------
	bool ActorManager::CopyFromTemplate( const Util::String& actorTemplateName, GPtr<Actor>& pDestActor, bool includePrivateProperty )
	{
		if ( !pDestActor.isvalid() )
		{
			return false;
		}

		GPtr<Actor> pTemplate(NULL);

		IndexT index = mTemplateActors.FindIndex( actorTemplateName );
		if ( InvalidIndex == index )
		{
			Serialization::FileType iFileType;
			pTemplate = LoadSingleTemplate(actorTemplateName,iFileType);
		}
		else
		{
			pTemplate = mTemplateActors.ValueAtIndex( index ).m_ptr;
		}

		if ( !pTemplate.isvalid() )
		{
			return false;
		}

		pDestActor->CopyFrom( pTemplate, includePrivateProperty );
		/*因为pTemplate一定是非激活状态，所以在复制完成之后要根据字典中保存的状态信息对pActor进行设置*/
		index = mTemplateActors.FindIndex( actorTemplateName );
		if (mTemplateActors.ValueAtIndex(index).activeFlag)
		{
			pDestActor->Active();
		}
		else
		{
			pDestActor->Deactive();
		}

		pDestActor->SetLinkTemplate( false );
		return true;
	}
	//------------------------------------------------------------------------
	const Util::String g_SingleTemplateURI = "asset:";
	const Util::String g_SingleTemplateExt = ".template";
	bool ActorManager::SaveSingleTemplate( const Util::String& actorTemplateName, GPtr<Actor>& pSource, int iFileType, bool updateSource)
	{
		if ( iFileType<0 || 
			iFileType>=Serialization::FT_NUM )
		{
			return false;
		}
		//Util::String templateName = g_SingleTemplateURI + actorTemplateName.ExtractFileName();
		Util::String templateName = actorTemplateName;

		bool bHasInstance = Serialization::SerializationServer::HasInstance();
		if ( !pSource ||
			!bHasInstance )
		{
			return false;
		}

		GPtr<Actor> pTemplate = Actor::Create();
		pTemplate->CopyFrom(pSource, true);
		// template must deactive and link false
		RecursionUnLinkTemplate(pTemplate);	// 递归断开连接。避免嵌套
		pTemplate->SetTemplateName( templateName );
		if (updateSource)
		{
			//update the template name of pSource
			RecursionUnLinkTemplate( pSource );
			pSource->SetTemplateName( templateName );
		}

		Serialization::SerializationServer* serialize = Serialization::SerializationServer::Instance();
		
		Util::String filePath = actorTemplateName;

		Serialization::FileType eFileType = static_cast<Serialization::FileType>( iFileType );
		GPtr<Serialization::SerializeWriter> pWriter = serialize->OpenWriteFile( filePath, eFileType );
		if ( pWriter )
		{
			pWriter->SerializeObject( pTemplate );
			serialize->CloseWriteFile( pWriter );
		}
		else
		{
			pTemplate->Deactive(true);
			return false;
		}

		/*在将actor保存为模板时，即使ator之前并非由模板创建，在模板缓冲中也有可能存在同名的模板，
		所以序列化完成之后要更新模板缓冲*/
		IndexT index = mTemplateActors.FindIndex( templateName );
		TemplateInfo templateInfo(pTemplate, eFileType);
		/*使用pTemplate创建完templateInfo后，pTemplate的激活状态已经保存在templateInfo中，
		为了不让pTemplate渲染出来，应该将其变为非激活状态*/
		pTemplate->Deactive();
		if ( InvalidIndex != index )
		{
			mTemplateActors.ValueAtIndex( index ) = templateInfo;
		}
		else
		{
			mTemplateActors.Add(templateName, templateInfo);
		}

		return true;
	}
	//------------------------------------------------------------------------
	void ActorManager::UpdateTemplatedActors( GPtr<Actor>& pActor )
	{
		const GPtr<Actor> pRootActor(this->_GetMainSceneRootActor());
		const Util::String templateName = pActor->GetTemplateName().AsString();

		if ( "" == templateName)
		{
			return;
		}

		if ( pRootActor.isvalid() )
		{
			// 查找之前打开的文件的类型
			IndexT index = mTemplateActors.FindIndex( templateName );
			Serialization::FileType iFileType = Serialization::FT_XML;

			if ( InvalidIndex != index )
			{
				iFileType = mTemplateActors.ValueAtIndex( index ).iFileType;
			}
			else
			{
				LoadSingleTemplate( templateName ,iFileType);
			}

			SaveSingleTemplate(templateName, pActor, iFileType);
			GPtr<Actor> ptempActor = Actor::Create();
			ptempActor->CopyFrom(pActor,true);
			RecursionUpdateTemplate(ptempActor , pRootActor, templateName );
			ptempActor->Deactive();
		}
	}

	//------------------------------------------------------------------------
	void ActorManager::RecursionUpdateTemplate(const GPtr<Actor>&  sourceActor,const GPtr<Actor>&  destActor, 
		const Util::String& actorTemplateName)
	{
		if ( sourceActor.isvalid() && destActor.isvalid() && sourceActor.get() != destActor.get())
		{
			if ( destActor->GetTemplateName() == actorTemplateName)
			{
				//因为在actor的CopyFrom函数中会将actor自己Deactive掉，所以要将active状态保存，拷贝完成后恢复
				bool bIsActive = destActor->IsActive();
				destActor->CopyFrom( sourceActor, false);
				destActor->SetScale(sourceActor->GetScale());
				if (bIsActive)
				{
					destActor->Active(true);//因为子actor中没保存模板名，这里需要连同子actor一起激活
				} 
				else
				{
					destActor->Deactive(true);
				}
			}
			else
			{
				SizeT count = destActor->GetChildCount();
				for ( IndexT index = 0; index < count; ++index )
				{
					RecursionUpdateTemplate( sourceActor, destActor->GetChild(index), actorTemplateName);
				}
			}
		}
	}

	//------------------------------------------------------------------------
	GPtr<Actor> ActorManager::LoadSingleTemplate( const Util::String& actorTemplateName ,Serialization::FileType& file)
	{
		if ( !Serialization::SerializationServer::HasInstance() )
		{
			return NULL;
		}

		Serialization::SerializationServer* serialize = Serialization::SerializationServer::Instance();

		Util::String filePath = actorTemplateName;

		GPtr<Actor> pTemplate;

		GPtr<Serialization::SerializeReader> pReader = serialize->OpenReadFile( filePath, Serialization::FT_DEFAULT );
		if ( pReader )
		{
			pTemplate = pReader->SerializeObject<Actor>();
			if ( !pTemplate.isvalid())
			{
				serialize->CloseReadFile(pReader);
				return NULL;
			}
				//the name of pTemplate is the fileName
			pTemplate->SetTemplateName( actorTemplateName );
			serialize->CloseReadFile(pReader);
		}
		else
		{
			return NULL;
		}

		// 判断序列化文件的类型（二进制、xml类型）
		Serialization::FileType fileType;

		if ( pReader->GetRtti() == &Serialization::SerializeXmlReader::RTTI )
		{
			fileType = Serialization::FT_XML;
		}
		else if ( pReader->GetRtti() == &Serialization::SerializeBinaryReader::RTTI )
		{
			fileType = Serialization::FT_BINARY;
		}

		file = fileType;


		if ( pTemplate )
		{
			TemplateInfo templateInfo( pTemplate, fileType);
			/*使用pTemplate创建完templateInfo后，pTemplate的激活状态已经保存在templateInfo中，
			为了不让pTemplate渲染出来，应该将其变为非激活状态*/
			pTemplate->Deactive();
			// cache
			IndexT index = mTemplateActors.FindIndex( actorTemplateName );
			if ( index == InvalidIndex)
				mTemplateActors.Add(actorTemplateName, templateInfo);
			else
				mTemplateActors.ValueAtIndex( index ) = templateInfo;
			
			return pTemplate;
		}
		else
		{
			return NULL;
		}
	}
	//------------------------------------------------------------------------
	void ActorManager::RecursionUnLinkTemplate(const GPtr<Actor>& pActor)
	{
		if ( pActor )
		{
			SizeT count = pActor->GetChildCount();
			for ( IndexT index = 0; index < count; ++index )
			{
				RecursionUnLinkTemplate( pActor->GetChild(index) );
			}
			pActor->SetLinkTemplate(false);
			pActor->SetTemplateName("Empty");
		}
	}
	//------------------------------------------------------------------------------
	bool ActorManager::GetTemplateActiveFlag(const Util::String& actorTemplateName, bool& bActiveFlag)
	{
		IndexT index = mTemplateActors.FindIndex( actorTemplateName );
		if ( InvalidIndex == index)
		{
			return false;
		} 
		bActiveFlag = mTemplateActors.ValueAtIndex(index).activeFlag;
		return true;
	}
	//------------------------------------------------------------------------
	Actor* ActorManager::FindActiveActor( App::Actor::FastId fastID ) const
	{
		IndexT index = mActiveActors.FindIndex( fastID );
		if( index != InvalidIndex )
		{
			return mActiveActors.ValueAtIndex( index );
		}
		else
		{
			return NULL;
		}
	}
	//------------------------------------------------------------------------
	Actor* ActorManager::FindActiveActorByGUID(const Util::Guid& guid) const
	{
		for (SizeT i = 0; i < mActiveActors.Size(); ++i)
		{
			//if(mActiveActors[i]->GetGUID() == guid)
			if (mActiveActors.ValueAtIndex(i)->GetGUID() == guid)
			{
				return mActiveActors.ValueAtIndex(i);
			}
		}
		return NULL;
	}
	//------------------------------------------------------------------------
	Actor* ActorManager::FindActiveActorByName(const Util::String& name) const
	{
		for (SizeT i = mActiveActors.Size()-1; i >=0; --i)
		{
			if(mActiveActors.ValueAtIndex(i)->GetName() == name)
			{
				return mActiveActors.ValueAtIndex(i);
			}
		}
		return NULL;
	}

	IndexT ActorManager::FindActiveActorIndex(App::Actor::FastId fastID) const
	{
		return mActiveActors.FindIndex(fastID);
	}

	void ActorManager::FindActiveActorsInGroup( const TagID tagID,Util::Array< GPtr<Actor> >& actors ) const
	{
		for (SizeT i = mActiveActors.Size()-1; i >=0; --i)
		{
			if(mActiveActors.ValueAtIndex(i)->GetTagID() == tagID)
			{
				actors.Append(mActiveActors.ValueAtIndex(i));
			}
		}
	}

	Actor* ActorManager::FindActiveActorInGroup(const TagID tagID)
	{
		for(SizeT i = mActiveActors.Size()-1; i>=0; --i)
		{
			if(mActiveActors.ValueAtIndex(i)->GetTagID() == tagID)
			{
				return mActiveActors.ValueAtIndex(i);
			}
		}
		return NULL;
	}

	Actor* ActorManager::FindActorByGUID(const Util::Guid& gid) const
	{
		ActorList_Const_Iterator itor = mAllCreatedActors.begin();
		ActorList_Const_Iterator end = mAllCreatedActors.end();

		for (; itor != end; ++itor)
		{
			if( (*itor)->GetGUID() == gid )
			{
				return *itor;
			}
		}
		
		return NULL;
	}
	//------------------------------------------------------------------------
	void ActorManager::_ActiveSingle( GPtr<Actor>& pActor )
	{
		n_assert( !pActor->IsActive() );
		n_assert( mActiveActors.FindIndex( pActor->GetFastId() )  == InvalidIndex );
		mActiveActors.Add(pActor->GetFastId(), pActor.get_unsafe());
		pActor->OnActivate();

	}
	//------------------------------------------------------------------------
	void ActorManager::ActiveActor( GPtr<Actor>& pActor, bool includeChild )
	{
		if ( !pActor.isvalid() )
			return;
		
		if ( !pActor->IsActive() )
		{
			_ActiveSingle( pActor );
		}

		if ( includeChild )
		{
			SizeT count = pActor->GetChildCount();
			for ( IndexT i = 0; i < count; ++i)
			{
				GPtr<Actor> pChild = pActor->GetChild( i );
				n_assert( pChild );
				ActiveActor( pChild, includeChild );
			}
		}
	}
	//------------------------------------------------------------------------
	void ActorManager::_DeactiveSingle( GPtr<Actor>& pActor )
 	{
		n_assert( pActor->IsActive() );
		IndexT findIndex = mActiveActors.FindIndex( pActor->GetFastId() );
		n_assert( findIndex != InvalidIndex );
		if ( findIndex != InvalidIndex )
		{
			mActiveActors.EraseAtIndex( findIndex );
			pActor->OnDeactivate();
		}
		else
		{
			n_warning( "ActorManager::_DeactiveSingle: active actor not in active list\n");
		}
	}
	//------------------------------------------------------------------------
	void ActorManager::DeactiveActor( GPtr<Actor>& pActor, bool forceActiveControlofChild /* = false */ )
	{
		if ( !pActor.isvalid() )
			return;

		if ( pActor->IsActive() )
		{
			_DeactiveSingle( pActor );
		}

		if ( forceActiveControlofChild )
		{
			SizeT count = pActor->GetChildCount();
			for ( IndexT i = 0; i < count; ++i)
			{
				GPtr<Actor> pChild = pActor->GetChild( i );
				n_assert( pChild );
				DeactiveActor(pChild, forceActiveControlofChild );
			}
		}
	}

	//------------------------------------------------------------------------
	void ActorManager::ForceGC()
	{
		_DustbinOnFrame();

		for ( ActorList::iterator it = mAllCreatedActors.begin();
			it != mAllCreatedActors.end(); )
		{
			if ( (*it)->IsDestory() )
			{
				(*it)->_Destory();
				(*it)->Release();
				it = mAllCreatedActors.erase(it);
			}
			else
			{
				++it;
			}
		}

		mCurrentClearIterator = mAllCreatedActors.begin();
	}
	//------------------------------------------------------------------------
	void ActorManager::OnBeginFrame()
	{
		_DustbinOnFrame();
		_GarbageOnFrame();

		//SizeT actorSize = mActiveActors.Size();
		//actor在更新中有可能把自己Deactive掉,
		//以至于mActiveActors的数目发生改变，所以最好实时得到mActiveActors的大小,
		//以防访问数组时越界。
		for ( IndexT index = 0; index < mActiveActors.Size(); ++index)
		{
			mActiveActors.ValueAtIndex(index)->OnBeginFrame();
		}
	}
	//------------------------------------------------------------------------
	void ActorManager::OnFrame()
	{
		//SizeT actorSize = mActiveActors.Size();
		//actor在更新中有可能把自己Deactive掉,
		//以至于mActiveActors的数目发生改变，所以最好实时得到mActiveActors的大小,
		//以防访问数组时越界。
		for ( IndexT index = 0; index < mActiveActors.Size(); ++index)
		{
			mActiveActors.ValueAtIndex(index)->OnFrame();
		}
	}
	//------------------------------------------------------------------------
	void ActorManager::OnEndFrame()
	{
		//SizeT actorSize = mActiveActors.Size();
		//actor在更新中有可能把自己Deactive掉,
		//以至于mActiveActors的数目发生改变，所以最好实时得到mActiveActors的大小,
		//以防访问数组时越界。
		for ( IndexT index = 0; index < mActiveActors.Size(); ++index)
		{
			mActiveActors.ValueAtIndex(index)->OnEndFrame();
		}
	}
	//------------------------------------------------------------------------
	void ActorManager::_DustbinOnFrame()
	{

		Util::List< ActorInDustbin >::Iterator iter;	
		for ( iter = mArrActorDustbin.Begin(); iter!=mArrActorDustbin.End(); iter++ )
		{		
			DeactiveActor(iter->mpActor,iter->mForceActiveControlofChild);
		}

		mArrActorDustbin.Clear();
	}

	void ActorManager::_AddAllCreatedManager(Actor* actor)
	{
		n_assert(actor);
		actor->AddRef();
		mAllCreatedActors.push_back(actor);
	}


	const GPtr<Actor>& ActorManager::_GetMainSceneRootActor()
	{
		return SceneScheduleManager::Instance()->GetMainScene()->GetPtrRoot();
	}
}
	