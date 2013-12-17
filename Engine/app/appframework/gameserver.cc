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
#include "appframework/actormanager.h"
#include "appframework/gameserver.h"
#include "core/factory.h"
#include "input/inputserver.h"
#include "input/inputkeyboard.h"
#include "input/inputgamepad.h"
#include "profilesystem/ProfileSystem.h"
#include "basegamefeature/managers/timesource.h"

//temp code
#ifdef __OSX__
#include "foundation/util/monoapi.h"
#include "actormanager.h"
#include "cameracomponent.h"
#include "osxinputsource.h"
#include "osxinputserver.h"
#include "inputtouchscreen.h"
#include "inputfeature.h"
#endif
//------------------------------------------------------------------------


namespace App
{


__ImplementClass(App::GameServer, 'GMSV', Core::RefCounted);
__ImplementThreadSingleton(App::GameServer);

//------------------------------------------------------------------------------
/**
*/
GameServer::GameServer() :
    mOpen(false),
    mStarted(false),
    mQuitRequested(false),
	mbScript(false),
	mbPhysics(false),
	mbAnimation(false),
	mbParticle(false),
	mbVegetaion(false),
	mbSound(false),
	mbNetwork(false),
	mbFont(false)
{
    __ConstructThreadSingleton;
    //_setup_timer(mGameServerOnFrame);
}

//------------------------------------------------------------------------------
/**
*/
GameServer::~GameServer()
{
    n_assert(!this->mOpen);
    //_discard_timer(mGameServerOnFrame);
    __DestructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
    Initialize the game server object. This will create and initialize all
    subsystems.
*/
bool
GameServer::Open()
{
    n_assert(!this->mOpen);
    n_assert(!this->mStarted);
    this->mOpen = true;
    return true;
}

//------------------------------------------------------------------------------
/**
    Close the game server object.
*/
void
GameServer::Close()
{
    n_assert(!this->mStarted);
    n_assert(this->mOpen);

    // remove all gameFeatures
 //   while (this->mGameFeatures.Size() > 0)
 //   {
 //       this->mGameFeatures[0]->OnDeactivate();
 //       this->mGameFeatures.EraseAtIndex(0);
 //   }
	GameFeatures::Iterator it = mGameFeatures.Begin();
	GameFeatures::Iterator end = mGameFeatures.End();
	while(it != end)
	{
		it->Value()->OnDeactivate();
		++it;
	}

#ifndef __SCRIPT_COMMIT__
	mGameFeatures["Script"]     = NULL;
#endif

#ifndef __PHYSX_COMMIT__
	mGameFeatures["Physics"]    = NULL;
#endif
	
	
	mGameFeatures["Animation"]  = NULL;

// #if __WIN32__
// 	mGameFeatures["Network"]    = NULL;
// #endif
    
	mGameFeatures["Particle"]   = NULL;

	//字体现在只在editor中使用，不是通用feature
	if (mGameFeatures.FindIndex("Font") != InvalidIndex)
	{
		mGameFeatures["Font"] = NULL;
	}

#ifndef __SOUND_COMMIT__
	mGameFeatures["Sound"]      = NULL;
#endif
	
	mGameFeatures["Vegetation"] = NULL;
	mGameFeatures["Input"]      = NULL;
	mGameFeatures["BaseGame"]   = NULL;
	mGameFeatures["Graphics"]   = NULL;

	mGameFeatures.Clear();

    this->mOpen = false;
}

//------------------------------------------------------------------------------
/**
*/
void
GameServer::AttachGameFeature(const GPtr<Feature>& feature)
{
    n_assert(0 != feature);
    //n_assert(InvalidIndex == this->mGameFeatures.FindIndex(feature));

	n_assert(false == this->mGameFeatures.Contains(feature->GetFeatureName()));

    feature->OnActivate();
    this->mGameFeatures.Add(feature->GetFeatureName(), feature);
}

//------------------------------------------------------------------------------
/**
*/
void
GameServer::RemoveGameFeature(const GPtr<Feature>& feature)
{
    n_assert(0 != feature);
    IndexT index = this->mGameFeatures.FindIndex(feature->GetFeatureName());
    n_assert(InvalidIndex != index);
    feature->OnDeactivate();
    this->mGameFeatures.EraseAtIndex(index);
}

//------------------------------------------------------------------------------
/**
    Start the game world, called after loading has completed.
*/
bool
GameServer::Start()
{
    n_assert(this->mOpen);
    n_assert(!this->mStarted);

    // call the OnStart method on all gameFeatures
    int i;
    int num = this->mGameFeatures.Size();
    for (i = 0; i < num; ++i)
    {
        this->mGameFeatures.ValueAtIndex(i)->OnStart();
    }
    
	if (mGameFeatures.FindIndex("Script") != InvalidIndex)
	{
		mbScript = true;
	}

	if (mGameFeatures.FindIndex("Physics") != InvalidIndex)
	{
		mbPhysics = true;
	}

	if (mGameFeatures.FindIndex("Animation") != InvalidIndex)
	{
		mbAnimation = true;
	}

// 	if (mGameFeatures.FindIndex("Network") != InvalidIndex)
// 	{
// 		mbNetwork = true;
// 	}

	if (mGameFeatures.FindIndex("Particle") != InvalidIndex)
	{
		mbParticle = true;
	}

	if (mGameFeatures.FindIndex("Sound") != InvalidIndex)
	{
		mbSound = true;
	}

	if (mGameFeatures.FindIndex("Vegetation") != InvalidIndex)
	{
		mbVegetaion = true;
	}
	if (mGameFeatures.FindIndex("Font") != InvalidIndex)
	{
		mbFont = true;
	}
    this->mStarted = true;
    return true;
}

//------------------------------------------------------------------------------
/**
*/
#ifdef __GENESIS_EDITOR__
bool 
GameServer::StartInEditor()
{
	n_assert(this->mOpen);
	n_assert(!this->mStarted);

	//mbScript    = true;
	mbScript    = false;//-edit by zhaoxiaohang 12.8.9

	IndexT index;
	index = mGameFeatures.FindIndex("Physics");
	if ( index != InvalidIndex)
	{
		mbPhysics = true;
	}
	index = mGameFeatures.FindIndex("Animation");
	if ( index != InvalidIndex)
	{
		mbAnimation = true;
		mGameFeatures.ValueAtIndex(index)->OnStart();
	}
	index = mGameFeatures.FindIndex("Particle");
	if ( index != InvalidIndex)
	{
		mbParticle = true;
		mGameFeatures.ValueAtIndex(index)->OnStart();
	}
	index = mGameFeatures.FindIndex("Sound");
	if ( index != InvalidIndex)
	{
		mbSound = true;
		mGameFeatures.ValueAtIndex(index)->OnStart();
	}
	index = mGameFeatures.FindIndex("Vegetation");
	if ( index != InvalidIndex)
	{
		mbVegetaion = true;
		mGameFeatures.ValueAtIndex(index)->OnStart();
	}
	index = mGameFeatures.FindIndex("Font");
	if ( index != InvalidIndex)
	{
		mbFont = true;
		mGameFeatures.ValueAtIndex(index)->OnStart();
	}
	this->mStarted = true;
	return true;
}

#endif
//------------------------------------------------------------------------------
/**
*/
bool
GameServer::HasStarted() const
{
    return this->mStarted;
}

//------------------------------------------------------------------------------
/**
    Stop the game world, called before the world(current level) is cleaned up.
*/
void
GameServer::Stop()
{
    n_assert(this->mOpen);
    n_assert(this->mStarted);

	int i;
	int num = this->mGameFeatures.Size();
	for (i = 0; i < num; ++i)
	{
		this->mGameFeatures.ValueAtIndex(i)->OnStop();
	}
    
    this->mStarted = false;
}


//------------------------------------------------------------------------------
/**
    Trigger the game server. If your application introduces new or different
    manager objects, you may also want to override the Game::GameServer::Trigger()
    method if those gameFeatures need per-frame callbacks.
*/

template<bool _graphic>
void
GameServer::onFrame()
{
    //_start_timer(mGameServerOnFrame);
	//OnBeginframe
	PROFILER_RESETICKSTATS();
	{
		mGameFeatures["Graphics"]->OnBeginFrame();

		mGameFeatures["Input"]->OnBeginFrame();

		mGameFeatures["BaseGame"]->OnBeginFrame();

		if (mbScript)
		{
			mGameFeatures["Script"]->OnBeginFrame();
		}
		
		if (mbPhysics)
		{
			mGameFeatures["Physics"]->OnBeginFrame();
		}
		if ( mbFont )
		{
			mGameFeatures["Font"]->OnBeginFrame();
		}
		
	}
   
	//OnFrame
	{
		if (mbAnimation)
		{
			mGameFeatures["Animation"]->OnFrame();
		}

		if (mbPhysics)
		{
			mGameFeatures["Physics"]->OnFrame();
		}

// 		if (mbNetwork)
// 		{
// 			mGameFeatures["Network"]->OnFrame();
// 		}	

		if (mbSound)
		{
			mGameFeatures["Sound"]->OnFrame();
		}
			
		if (mbParticle)
		{
			mGameFeatures["Particle"]->OnFrame();
		}
		
		if (mbVegetaion)
		{
			mGameFeatures["Vegetation"]->OnFrame();
		}

		mGameFeatures["BaseGame"]->OnFrame();

		if (mbScript)
		{
			mGameFeatures["Script"]->OnFrame();
		}
        
        
		if ( mbFont )
		{
			mGameFeatures["Font"]->OnFrame();
		}
		if(_graphic)
		{
			mGameFeatures["Graphics"]->OnFrame();
		}
	}

	//OnEndFrame
	{
		mGameFeatures["BaseGame"]->OnEndFrame();

		if (mbScript)
		{
			mGameFeatures["Script"]->OnEndFrame();
		}

		mGameFeatures["Graphics"]->OnEndFrame();

		mGameFeatures["Input"]->OnEndFrame();

		if ( mbFont )
		{ 
			mGameFeatures["Font"]->OnEndFrame();
		}

	}

#ifdef __OSX__
    ManuallyCollection( GameTime::Instance()->GetFrameTime() );
#endif
    

}
//------------------------------------------------------------------------------
/**    
*/
void
GameServer::OnFrame()
{
	onFrame<true>();
}
//------------------------------------------------------------------------------
/**    
*/
void
	GameServer::OnFrameWithoutGraphics()
{
	onFrame<false>();
}

//------------------------------------------------------------------------------
/**    
*/
void
GameServer::NotifyGameLoad()
{
    // call the OnLoad method on all gameFeatures
    int i;
    int num = this->mGameFeatures.Size();
    for (i = 0; i < num; ++i)
    {
        this->mGameFeatures.ValueAtIndex(i)->OnLoad();
    }
}
//------------------------------------------------------------------------------
/**    
*/
void
GameServer::NotifyGameSave()
{
    // call the OnLoad method on all gameFeatures
    int i;
    int num = this->mGameFeatures.Size();
    for (i = 0; i < num; ++i)
    {
        this->mGameFeatures.ValueAtIndex(i)->OnSave();
    }
}

//------------------------------------------------------------------------------
/**
*/
bool 
GameServer::IsFeatureAttached(const Util::String& stringName) const
{
    int i;
    int num = this->mGameFeatures.Size();
    for (i = 0; i < num; ++i)
    {
        if (this->mGameFeatures.ValueAtIndex(i)->GetRtti()->GetName() == stringName)
        {
            return true;
        }
    }
    return false;
}


void
GameServer::StopGameInEditor()
{
	n_assert(this->mOpen);
	//n_assert(this->mStarted);

	if (mGameFeatures.FindIndex("Script") != InvalidIndex)
	{
		mGameFeatures["Script"]->OnStop();
		mbScript = false;
	}

	if (mGameFeatures.FindIndex("Physics") != InvalidIndex)
	{
		mGameFeatures["Physics"]->OnStop();
		mbPhysics = false;
	}

	if (mGameFeatures.FindIndex("Animation") != InvalidIndex)
	{
		mGameFeatures["Animation"]->OnStop();
		mbAnimation = false;
	}

// 	if (mGameFeatures.FindIndex("Network") != InvalidIndex)
// 	{
// 		mGameFeatures["Network"]->OnStop();
// 		mbNetwork = false;
// 	}

	if (mGameFeatures.FindIndex("Particle") != InvalidIndex)
	{
		mGameFeatures["Particle"]->OnStop();
		mbParticle = false;
	}

	if (mGameFeatures.FindIndex("Sound") != InvalidIndex)
	{
		mGameFeatures["Sound"]->OnStop();
		mbSound = false;
	}

	if (mGameFeatures.FindIndex("Vegetation") != InvalidIndex)
	{
		mGameFeatures["Vegetation"]->OnStop();
		mbVegetaion = false;
	}


	this->mStarted = false;

}

} // namespace Game