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
#include "appframework/scene.h"
#include "appframework/actormanager.h"
#include "basegamefeature/managers/sceneschedulemanager.h"
#include "app/physXfeature/physicsCore/PhysicsServer.h"

namespace App
{

	__ImplementClass(App::RootActor, 'ROAC' , App::Actor);


	RootActor::RootActor()
		:mScene(NULL)
	{
		mName.Format("__scene_name_%d",(int)this);
		SetTagID(0xffffffff);
	}

	RootActor::~RootActor()
	{

	}

	void RootActor::SetScene(Scene* scene)
	{
		mScene = scene;
	}

	Graphic::RenderScene* RootActor::GetRenderScene() const
	{
		n_assert(mScene);
		return mScene->GetRenderScene();
	}

	__ImplementClass(App::Scene, 'SCEN' ,Core::RefCounted);

	//------------------------------------------------------------------------
	Scene::Scene()
		: mModified(false)
		, mName("NoName")
		, mRenderScene(NULL)
	{
	}
	//------------------------------------------------------------------------
	Scene::~Scene()
	{
		n_assert( !mRoot.isvalid() );
		if (mRenderScene)
		{
			mRenderScene->Destroy();
			n_delete(mRenderScene);
			mRenderScene = NULL;
		}
	}
	//------------------------------------------------------------------------ 
	Graphic::RenderScene*
	Scene::GetRenderScene() const
	{
		if (mRenderScene)
		{
			return mRenderScene;
		}
		else
		{
			return SceneScheduleManager::Instance()->_GetMainRenderScene();
		}
	}
	//------------------------------------------------------------------------ 
	void
	Scene::_ApplyEnvironment(bool apply /* = false */)
	{
		GetRenderScene()->SetEnvironment(&mEnvironment);
        
#ifndef __PHYSX_COMMIT__
		if(apply)
		{
			PhysicsServer::Instance()->SetGravity(mEnvironment.graivty);
			PhysicsServer::Instance()->SetSleepThreshold(mEnvironment.sleepVel);
			PhysicsServer::Instance()->SetMaxAngularVelocity(mEnvironment.maxAngular);
			PhysicsServer::Instance()->SetDefaultMaterial(mEnvironment.defaultMat);
			if(mEnvironment.layerIDArray.Size() == 32)
			{
				PhysicsServer::Instance()->SetAllCollisionMaskMatrix(mEnvironment.layerIDArray);
			}
		}
#endif
	}

	//------------------------------------------------------------------------
	SizeT 
	Scene::GetActorCount(void) const
	{
		n_assert( mRoot.isvalid() );
		return mRoot->GetChildCount();
	}
	//------------------------------------------------------------------------ 
	const GPtr<Actor>& 
	Scene::GetActor(IndexT index) const
	{
		n_assert( mRoot.isvalid() );
		return mRoot->GetChild( index );
	}
	//------------------------------------------------------------------------
	const GPtr<Actor>& 
	Scene::FindActor( Actor::FastId actorID ) const
	{
		n_assert( mRoot.isvalid() );
		return mRoot->FindChild(actorID);
	}
	//------------------------------------------------------------------------
	const GPtr<Actor>& Scene::FindActorByTag( App::TagID id ) const
	{
		n_assert( mRoot.isvalid() );
		return mRoot->FindChildByTag(id);
	}
	//------------------------------------------------------------------------
	void Scene::FindActorsByTag(const App::TagID tagID,Util::Array< GPtr<Actor> >& actors) const
	{
		n_assert( mRoot.isvalid());
		mRoot->FindChildrenByTag(tagID,actors);
		
	}
	//------------------------------------------------------------------------
	const GPtr<Actor>& 
		Scene::FindActor( const Util::Guid& guid ) const
	{
		n_assert( mRoot.isvalid() );
		return mRoot->FindChild(guid);
	}
	//------------------------------------------------------------------------
	const GPtr<Actor>& 
		Scene::FindActor( const Util::String& name ) const
	{
		n_assert( mRoot.isvalid() );
		return mRoot->FindChild(name);
	}
	//------------------------------------------------------------------------
	IndexT 
	Scene::FindActorIndex( Actor::FastId fastID ) const
	{
		n_assert( mRoot.isvalid() );
		return mRoot->FindChildIndex(fastID);
	}
	//------------------------------------------------------------------------
	void 
	Scene::AddActor( GPtr<Actor>& pActor )
	{
		//当导入角色动画等原本就有层级结构的Actor时，就不能把他们挂在最顶层的mRoot上
		if (pActor->GetParent())
		{
			return;
		}
		n_assert( mRoot.isvalid() );
		mRoot->AddChild( pActor );
	}
	//------------------------------------------------------------------------
	void 
	Scene::RemoveActor( IndexT index)
	{
		n_assert( mRoot.isvalid() );
		return mRoot->RemoveChild(index);
	}
	//------------------------------------------------------------------------
	void 
	Scene::RemoveActor( GPtr<Actor>& pActor )
	{
		n_assert( mRoot.isvalid() );
		return mRoot->RemoveChild( pActor );
	}
	//------------------------------------------------------------------------
	void
	Scene::_Open( bool privateScene )
	{
		n_assert( !mRoot.isvalid() );

		if (privateScene)
		{
			mRenderScene = n_new(Graphic::RenderScene);
			mRenderScene->Setup();
		}

		mRoot = RootActor::Create();
		mRoot->SetScene(this);
		mRoot->Active(false);
	}
	//------------------------------------------------------------------------
	// called before close
	void 
	Scene::_Close()
	{
		if ( mRoot.isvalid() )
		{
			//mRoot->Destory(true);
			GPtr<Actor> ac = mRoot.upcast<Actor>();
			ActorManager::Instance()->DeactiveActorDelayed(ac, true);
			mRoot = NULL;
		}
	}
}
