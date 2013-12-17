/****************************************************************************
Copyright (c) 2007,Radon Labs GmbH
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
#include "basegamefeature/basegamefeature.h"
#include "basegamefeature/managers/timesource.h"




namespace App
{
	__ImplementClass(App::BaseGameFeature, 'GAGF' , App::Feature);
    __ImplementThreadSingleton(App::BaseGameFeature);

//------------------------------------------------------------------------------
/**
*/
BaseGameFeature::BaseGameFeature()
{
    __ConstructThreadSingleton;

	mFeatureName = "BaseGame";
}

//------------------------------------------------------------------------------
/**
*/
BaseGameFeature::~BaseGameFeature()
{
    __DestructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void
BaseGameFeature::OnActivate()
{
	Feature::OnActivate();

	mResServer = Resources::ResourceServer::Create();
	mResServer->RegisterDefaultResouceTypes();
	mResServer->Open();
	mResManager = Resources::ResourceManager::Create();


	mSerializationServer = Serialization::SerializationServer::Create();
	mGameCfgMgr = GameConfigManager::Create();
	mSceneScheduleMgr = SceneScheduleManager::Create();
	mTimeMgr = TimeManager::Create();
	GPtr<GameTime> pGameTime = GameTime::Create();
	mActorMgr = ActorManager::Create();

	mSceneScheduleMgr->Open();

    this->AttachManager(this->mGameCfgMgr.upcast<App::Manager>());  
	this->AttachManager(this->mTimeMgr.upcast<App::Manager>() );
	mTimeMgr->AttachTimeSource( pGameTime.upcast<App::TimeSource>());
	this->AttachManager(mActorMgr.upcast<App::Manager>());
	this->AttachManager(this->mSceneScheduleMgr.upcast<App::Manager>());//在mActorMgr之后。以保证每帧的OnBeginFrame都在ActorManager之后触发
}

//------------------------------------------------------------------------------
/**
*/
void
BaseGameFeature::OnDeactivate()
{
    this->RemoveManager(this->mGameCfgMgr.upcast<App::Manager>());
    this->RemoveManager(this->mSceneScheduleMgr.upcast<App::Manager>());
	this->RemoveManager(this->mTimeMgr.upcast<App::Manager>());
	this->RemoveManager(this->mActorMgr.upcast<App::Manager>());

    this->mGameCfgMgr = NULL;  
    this->mSceneScheduleMgr = NULL;
	this->mTimeMgr = NULL;
	this->mActorMgr = NULL;

	mResServer->Close();
	mResManager->Close();	
	mResServer = NULL;
	mResManager = NULL;

	mSerializationServer = NULL;

    Feature::OnDeactivate();
}

//------------------------------------------------------------------------------
/**
*/
void
BaseGameFeature::OnRenderDebug()
{
    // render debug for all entities and its properties
    // this->entityManager->OnRenderDebug();
    Feature::OnRenderDebug();

    // print fps
 //   Timing::Time frameTime = SystemTimeSource::Instance()->GetFrameTime();        
	//Util::String txt;
	//txt.Format("FPS: %.0f \n", 1/frameTime);
	//_debug_text(txt, Math::float2(0.7f, 0.0f), Math::float4(1, 1, 1, 1));
}
//------------------------------------------------------------------------
/// called on begin of frame
void BaseGameFeature::OnBeginFrame()
{
	mResServer->Flush();
	mResManager->OnBeginFrame();
	Feature::OnBeginFrame();
}

//------------------------------------------------------------------------------
/**
*/
void
BaseGameFeature::OnEndFrame()
{
    Feature::OnEndFrame();
}

//------------------------------------------------------------------------------
/**
*/
void
BaseGameFeature::OnFrame()
{
    Feature::OnFrame();
}

//------------------------------------------------------------------------------
/**
*/
void 
BaseGameFeature::OnStop()
{
	mSceneScheduleMgr->Close();
	mActorMgr->ForceGC();
	Feature::OnStop();
}
//------------------------------------------------------------------------
void 
BaseGameFeature::LoadActorTemplate(const Util::String& templatePath)
{
	if ( templatePath.IsEmpty() )
	{
		return;
	}

	if ( mActorMgr.isvalid() )
	{
		mActorMgr->LoadTemplateFile(templatePath);
	}
}

} // namespace Game
