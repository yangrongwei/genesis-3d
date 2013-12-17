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
#ifndef __actormanager_H__
#define __actormanager_H__

#include "app/appframework/manager.h"
#include "app/appframework/serialization.h"
#include "addons/serialization/serializeserver.h"
#include "app/appframework/actor.h"
#include "core/singleton.h"

namespace App
{
	class Scene;
	/// this struct is used to bind a pointer of actor and a bool vaule together,for now it will only be used when removing actors
	struct ActorInDustbin
	{
		
	public:
		ActorInDustbin()
			: mForceActiveControlofChild(false)
		{
			
		}
		ActorInDustbin(const GPtr<Actor>& actor, bool  includeChild)
		{
			mpActor = actor;
			includeChild = mForceActiveControlofChild;
		}
		~ActorInDustbin(){}
	
		GPtr<Actor>		   mpActor;
		bool		   mForceActiveControlofChild;
	};

	class ActorTemplateFile: public Core::RefCounted, App::ISerialization
	{
		__DeclareClass(ActorTemplateFile)
	public:
		ActorTemplateFile(){ }

		virtual ~ActorTemplateFile(){ }

		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const ;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args ) ;

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const ;
	};


	class ActorManager: public App::Manager
	{
		__DeclareSubClass(ActorManager, App::Manager);
		__DeclareThreadSingleton(ActorManager);

	public:
		typedef Util::STL_list<Actor*>::type ActorList;
		typedef ActorList::iterator ActorList_Iterator;
		typedef ActorList::const_iterator ActorList_Const_Iterator;

	public:		
		ActorManager();

		virtual ~ActorManager();

		static const int ActorDeadRefCount;

		/// called when attached to game server
		virtual void OnActivate();

		/// called when removed from game server
		virtual void OnDeactivate();

		GPtr<Actor> CreateActor();

		// active the actor and it's component. add in active actor list in ActorManger
		// if includeChild is true, all child actor will be active too
		// after this call, the index of actor may be invalid when EnumActiveActor
		void ActiveActor( GPtr<Actor>& pActor, bool includeChild = false );

		// Deactive the actor and it's component. remove from active actor list in ActorManger
		// if includeChild is true, all child actor will be deactive
		// after this call, the index of actor may be invalid when EnumActiveActor

		void DeactiveActorDelayed( GPtr<Actor>& pActor, bool includeChild = false );

		void DeactiveActor( GPtr<Actor>& pActor, bool forceActiveControlofChild);// = false 

		//---------------------------actor template manage ---------------------------------------------
		/**
		* CreateFromTemplate  create actor from template. 
		* @param: const Util::StringAtom & actorTemplateName   template name which copy from
		* @return: GPtr<Actor>  If template not exist, Return null
		* @see: 
		* @remark:  The new actor will link to template. Should manu disconnect link if need 
                    The new actor is deactive
		*/
		GPtr<Actor> CreateFromTemplate( const Util::String& actorTemplateName );

		/// 
		GPtr<Actor> CreatFromTemplateRes(Resources::ResourceId resID);
		
		
		///clear the template cache for HotUpdating;
		void DeleteTemplateCache(Resources::ResourceId resID);

		/**
		* CopyFromTemplate  For a exist actor, Copy from template. 
		* @param: const Util::StringAtom & actorTemplateName  template name which copy from
		* @param: GPtr<Actor> & pDestActor    the actor which copy to
		* @param: bool includePrivateProperty  if true, the actor's private property( like transform, layerID,...)  will copy
		* @return: bool if copy sucess  
		* @see: 
		* @remark:  The actor's template name maybe be changed, And link to actor template. Should manu disconnect link if need
		            The actor will be deactive after copy
		*/
		bool CopyFromTemplate( const Util::String& actorTemplateName, GPtr<Actor>& pDestActor, bool includePrivateProperty );

		// 读取*.atp文件。
		void LoadTemplateFile(const Util::String& filePath);

		// 将某个Actor保存为模板，*.template. 
		bool SaveSingleTemplate( const Util::String& actorTemplateName, GPtr<Actor>& pSource, int iFileType ,bool updateSource = false );

		// 读取单个模板文件。 *.template
		GPtr<Actor> LoadSingleTemplate( const Util::String& actorTemplateName ,Serialization::FileType& fileType);


		// 递归Actor，断开Actor和Child Actor和模板的链接
		void RecursionUnLinkTemplate( const GPtr<Actor>& pActor);

		//更新templatedactors
		void UpdateTemplatedActors( GPtr<Actor>& pActor );
		//迭代更新templatedactors
		void RecursionUpdateTemplate(const GPtr<Actor>&  sourceActor,const GPtr<Actor>&  destActor, const Util::String& actorTemplateName);

		bool GetTemplateActiveFlag(const Util::String& actorTemplateName, bool& bActiveFlag);

		//---------------------------激活的 actor 的管理---------------------------------------------

		SizeT GetActiveActorCount() const;

		// Get Active Actor By Index
		Actor* GetActiveActor(IndexT index) const;

		// find active actor by fast ID
		Actor* FindActiveActor( App::Actor::FastId fastID ) const;

		// find active actor by GUID
		Actor* FindActiveActorByGUID(const Util::Guid& guid) const;

		// find active actor by Name
		Actor* FindActiveActorByName(const Util::String& name) const;

		// find actor index in active list
		IndexT FindActiveActorIndex(App::Actor::FastId fastID) const;

		// find actors by tag id
		void FindActiveActorsInGroup(const TagID tagID,Util::Array< GPtr<Actor> >& actors) const;
		// find actor by tag id
		Actor* FindActiveActorInGroup(const TagID tagID);

		SizeT GetAllActorCount() const;

		// find actor by GUID
		Actor* FindActorByGUID(const Util::Guid& gid) const;

		// Get Actor By Index
		Actor* GetActor(IndexT index) const;

#ifdef __GENESIS_EDITOR__	//editor use


		ActorList_Iterator GetAllActorBegin();

		ActorList_Const_Iterator GetAllActorBegin() const;

		ActorList_Iterator GetAllActorEnd();

		ActorList_Const_Iterator GetAllActorEnd() const;
		
			// Get All Actors by Type
		template<typename T>
		SizeT GetAllActorComponents(Util::Array<GPtr<T>> & components);

#endif // WJ_EDITOR


		void ForceGC();

		//------------------------------------------------------------------------
		/// called before frame by the game server
		virtual void OnBeginFrame();

		/// called per-frame by the game server
		virtual void OnFrame();

		/// called after frame by the game server
		virtual void OnEndFrame();

		//------------------------------------------------------------------------


		void SetModified(bool bModified);

		bool GetModified(void) const;

	protected:

		// 仅供Actor的构造函数调用，其他地方都不需调用
		void _AddAllCreatedManager(Actor* actor);

		// 为了使用场景树对场景进行遍历，加入了这个函数
		const GPtr<Actor>& _GetMainSceneRootActor();

		
		void _ActiveSingle( GPtr<Actor>& pActor );

		void _DeactiveSingle( GPtr<Actor>& pActor );

		void _DustbinOnFrame();

		/// 进行垃圾回收操作. 清楚掉Deactive并且引用计数为1的Actor
		void _GarbageOnFrame();

	protected:
		
		// 加入文件格式的信息，在更新到模板文件的时候会用到
		struct TemplateInfo
		{
			public:
				GPtr<Actor> m_ptr;
				Serialization::FileType iFileType;
				bool activeFlag;
			public:
				TemplateInfo(GPtr<Actor> pActor, Serialization::FileType fileType)
				{
					m_ptr = pActor;
					iFileType = fileType;
					activeFlag = pActor->GetActiveControl();
				}

				TemplateInfo( )
				{
					iFileType = Serialization::FT_XML;
				}
		};
		typedef Util::Dictionary< Actor::FastId, Actor*> ActiveActorContainer;//GPtr<Actor>
		typedef Util::Dictionary< Util::String, TemplateInfo > ActorTemplateContainer;
		typedef Util::List< ActorInDustbin > ActorDustbin;
		typedef Util::Array< GPtr<Actor> > ActorArray;

		ActorList_Iterator		mCurrentClearIterator;

		ActiveActorContainer mActiveActors;
		ActorList mAllCreatedActors;
		ActorTemplateContainer mTemplateActors;

		ActorDustbin  mArrActorDustbin; 

		bool mModified;

		friend class ActorManagerSerialization;
		friend class Actor;
	};
	//------------------------------------------------------------------------
	inline 
	void 
	ActorManager::SetModified(bool bModified)
	{
		mModified = bModified;
	}
	//------------------------------------------------------------------------
	inline 
	bool 
	ActorManager::GetModified(void) const
	{
		return mModified;
	}
	//------------------------------------------------------------------------
	inline
	SizeT 
	ActorManager::GetActiveActorCount() const
	{
		return mActiveActors.Size();
	}
	//------------------------------------------------------------------------
	inline
		SizeT 
		ActorManager::GetAllActorCount() const
	{
		return mAllCreatedActors.size();
	}
	//------------------------------------------------------------------------
	inline 
	Actor*
	ActorManager::GetActiveActor(IndexT index) const
	{
		if ( index < mActiveActors.Size() )
		{
			return mActiveActors.ValueAtIndex(index);
		}
		else
		{
			return NULL;
		}

	}

#ifdef __GENESIS_EDITOR__	//editor use
	inline 
	ActorManager::ActorList_Iterator 
	ActorManager::GetAllActorBegin()
	{
		return mAllCreatedActors.begin();
	}
	//------------------------------------------------------------------------
	inline 
	ActorManager::ActorList_Const_Iterator 
	ActorManager::GetAllActorBegin() const
	{
		return mAllCreatedActors.begin();
	}
	//------------------------------------------------------------------------
	inline 
	ActorManager::ActorList_Iterator 
	ActorManager::GetAllActorEnd()
	{
		return mAllCreatedActors.end();
	}

	inline 
	ActorManager::ActorList_Const_Iterator 
	ActorManager::GetAllActorEnd() const
	{
		return mAllCreatedActors.end();
	}
	//------------------------------------------------------------------------
	template<typename T>
	SizeT ActorManager::GetAllActorComponents(Util::Array< GPtr<T> > & allComponents)
	{
		IndexT intersectCount = 0;
		SizeT actorSize = this->GetAllActorCount();

		for ( IndexT i = 0; i < actorSize; ++i )
		{
			GPtr<T> pCastedComponent;
			const GPtr<Actor>& pActor = this->GetActor(i);

			const Util::Array<GPtr<Component> > components = pActor->FindComponents(T::RTTI);
			SizeT componentSize = components.Size();

			for ( IndexT i = 0; i < componentSize; ++i)
			{
				if ( components[i].isvalid() )
				{
					pCastedComponent = components[i].downcast<T>();
					n_assert( pCastedComponent );

					allComponents.Append(pCastedComponent);
				}
			}
		}

		return allComponents.Size();
	}

#endif
}











#endif // __actormanager_H__
