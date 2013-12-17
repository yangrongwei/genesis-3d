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
#ifndef __scene_H__
#define __scene_H__

#include "core/refcounted.h"
#include "core/ptr.h"
#include "math/float2.h"
#include "appframework/serialization.h"
#include "appframework/actor.h"


namespace Graphic
{
	class RenderScene;
}


namespace App
{
	class SceneSerialization;
	class Scene;
	class RootActor : public Actor
	{
		__DeclareSubClass(RootActor, Actor);
	public:
		RootActor();
		virtual ~RootActor();
		virtual Graphic::RenderScene* GetRenderScene() const;
		void SetScene(Scene* scene);

	private:
		Scene* mScene;
	};

	class Scene : public Core::RefCounted, public App::ISerialization
	{
		__DeclareClass(Scene);
		__ScriptBind
	public:
		typedef Graphic::RenderScene::Environment Environment;
		/// constructor
		Scene();
		/// destructor
		virtual ~Scene();

		//-------------------------------basic-----------------------------------------

		Graphic::RenderScene* GetRenderScene() const;

		Environment& GetEnvironment();

		const Environment& GetEnvironment() const;

		bool IsModified(void) const;

		/// must manual set
		void SetModified( bool bModified = true );

		//---------------------------attribute---------------------------------------------
		/**
		* GetName  
		* @param: void  
		* @return: const Util::String&  
		* @see: 
		* @remark: scene name like: 
		   "myscene.scene"                              will read from scene\myscene.scene(xml) or scene\myscene.scene(bxml) as application set xml read or bxml read or other file storage type
		   "myscene:myscene_1_2.scene"                  will read from scene\myscene\myscene_1_2.scene(xml|bxml)
		   "myscene:myscene_1_2:myscene_1_2_1_2.scene"  will read from scene\myscene\myscene_1_2\myscene_1_2.scene(xml|bxml)
		   the string will long, but i think just one or two layer need
		*/
		const Util::String& GetName(void) const;

		void SetName(const Util::String& name );

		// just for query. !!!!!!do not modify this actor. use like AddActor  
		const Actor* GetRoot(void) const;

		//
		const GPtr<Actor>& GetPtrRoot(void) const;

		//------------------------------actor------------------------------------------

		SizeT GetActorCount(void) const;

		/// 通过索引得到Actor。
		const GPtr<Actor>& GetActor(IndexT index) const;

		/// find actor by fast ID . if has actor. if not exist, return null
		const GPtr<Actor>& FindActor( Actor::FastId fastID ) const;

		const GPtr<Actor>& FindActorByTag(App::TagID id) const;

		void FindActorsByTag(const App::TagID tagID,Util::Array< GPtr<Actor> >& actors) const;

		const GPtr<Actor>& FindActor( const Util::Guid& guid ) const;

		const GPtr<Actor>& FindActor( const Util::String& name ) const;

		IndexT FindActorIndex( Actor::FastId fastID ) const;

		/// Add Actor in the scene. After add, the index of actor may be change
		void AddActor( GPtr<Actor>& pActor );

		/// Remove actor from scene. After remove, the index of actor may be change
		void RemoveActor( IndexT index);

		void RemoveActor( GPtr<Actor>& pActor );

		//-------------------------ISerialization-----------------------------------------------

		// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
		virtual Version GetVersion() const;

		// @ISerialization::Load 
		virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

		// @ISerialization::Save
		virtual void Save( AppWriter* pWriter ) const;

		// internal call.
		/// create when scene open . before load and othre operation
		void _Open( bool privateScene );

		// called after save and before close
		void _Close( void );


		//--------------------------------------------------------------------------------------

		void _ApplyEnvironment(bool apply = false);


		static void _Load(AppReader* pReader, GPtr<Scene>& scene, bool privateScene);

	protected:

		void _SerializeActorBegin();
		void _SerializeActorEnd();

		Util::String mName;

		bool mModified;

		GPtr<RootActor> mRoot;
		Graphic::RenderScene* mRenderScene;

		Graphic::RenderScene::Environment mEnvironment;

		friend class SceneSerialization;
		friend class ActorManager;
	};
	//------------------------------------------------------------------------
	inline bool 
	Scene::IsModified(void) const
	{
		return mModified;
	}
	//------------------------------------------------------------------------
	inline void 
	Scene::SetModified( bool bModified /*= true*/ )
	{
		mModified = bModified;
	}
	//------------------------------------------------------------------------
	inline
	const Util::String& 
	Scene::GetName(void) const
	{
		return mName;
	}
	//------------------------------------------------------------------------
	inline
	void 
	Scene::SetName(const Util::String& name )
	{
		mName = name;
	}
	//------------------------------------------------------------------------
	inline
	const Actor* 
	Scene::GetRoot(void) const
	{
		return mRoot.get_unsafe();
	}
	//------------------------------------------------------------------------
	inline
	const GPtr<Actor>& 
	Scene::GetPtrRoot(void) const
	{
		return mRoot.upcast<Actor>();
	}
	//------------------------------------------------------------------------
	inline
	const Scene::Environment&
	Scene::GetEnvironment() const
	{
		return mEnvironment;
	}

	//------------------------------------------------------------------------
	inline
	Scene::Environment&
	Scene::GetEnvironment()
	{
		return mEnvironment;
	}
}


#endif // __scene_H__

