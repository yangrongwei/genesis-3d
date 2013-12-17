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
#include "appframework/feature.h"


namespace App
{
__ImplementClass(App::Feature, 'GAFE' , Core::RefCounted);

//------------------------------------------------------------------------------
/**
*/
Feature::Feature() : 
    mActive(false),
	mRenderDebug(false)
{
    // empty

}

//------------------------------------------------------------------------------
/**
*/
Feature::~Feature()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This method is called by Game::GameServer::ActivateComponents(). 
    Use this method for one-time initializations of the Feature.
*/
void
Feature::OnActivate()
{
	n_assert(!this->IsActive());
	this->mActive = true;
}

//------------------------------------------------------------------------------
/**
    This method is called by Game::GameServer::DeactivateComponents(). Use this 
    method to cleanup stuff which has been initialized in OnActivate().
*/
void
Feature::OnDeactivate()
{
    n_assert(this->IsActive());

    // remove all managers
    while (this->mManagers.Size() > 0)
    {
        this->mManagers[0]->OnDeactivate();
        this->mManagers.EraseIndex(0);
    }

    this->mActive = false;
}

//------------------------------------------------------------------------------
/**
    This method is called from within Game::GameServer::Load()
    on load of a savegame.
*/
void
Feature::OnLoad()
{
    // now call the OnLoad() method on all managers
    int managerIndex;
    int numManagers = this->mManagers.Size();
    for (managerIndex = 0; managerIndex < numManagers; ++managerIndex)
    {
        // invoke OnLoad() on manager
        this->mManagers[managerIndex]->OnLoad();
    }
}
//------------------------------------------------------------------------------
/**
    This method is called from within Game::GameServer::Save().
    It's called on save of a game.
*/
void
Feature::OnSave()
{
    int managerIndex;
    int numManagers = this->mManagers.Size();
    for (managerIndex = 0; managerIndex < numManagers; ++managerIndex)
    {
        this->mManagers[managerIndex]->OnSave();
    }  
}
//------------------------------------------------------------------------------
/**
    This method is called from within Game::GameServer::OnStart(). 
    Its called after all game features are activated and have initialized their subsystems.
    Use this
*/
void
Feature::OnStart()
{
    // call the OnStart method on all managers
	int managerIndex;
	int numManagers = this->mManagers.Size();
	for (managerIndex = 0; managerIndex < numManagers; ++managerIndex)
	{
		this->mManagers[managerIndex]->OnStart();
	}  
}
//------------------------------------------------------------------------------
/**
    This method is called from within Game::GameServer::Stop(). 
*/
void Feature::OnStop()
{
	int managerIndex;
	int numManagers = this->mManagers.Size();
	for (managerIndex = 0; managerIndex < numManagers; ++managerIndex)
	{
		this->mManagers[managerIndex]->OnStop();
	}  
}


//------------------------------------------------------------------------------
/**
    This method is called from Game::GameServer::OnBeginFrame() on all 
    game features attached to an GameServer in the order of attachment. Override this 
    method if your Feature has to do any work at the beginning of the frame.
*/
void
Feature::OnBeginFrame()
{
    // call OnBeginFrame() on managers
	int managerIndex;
	int numManagers = this->mManagers.Size();
	for (managerIndex = 0; managerIndex < numManagers; ++managerIndex)
	{
		this->mManagers[managerIndex]->OnBeginFrame();
	}  
}

//------------------------------------------------------------------------------
/**
    This method is called from Game::GameServer::OnMoveBefore() on all 
    game features attached to an GameServer in the order of attachment. Override this
    method if your Feature has any work to do before the physics subsystem
    is triggered.
*/
void
Feature::OnFrame()
{
    // call OnFrame() on managers   
	int managerIndex;
	int numManagers = this->mManagers.Size();
	for (managerIndex = 0; managerIndex < numManagers; ++managerIndex)
	{
		this->mManagers[managerIndex]->OnFrame();
	}  
}

//------------------------------------------------------------------------------
/**
    This method is called from Game::GameServer::OnRender() on all
    game features attached to an GameServer in the order of attachment. Override
    this method if your Feature has any work to do before rendering happens.
*/
void
Feature::OnEndFrame()
{
    // call OnEndFrame() on managers
	int managerIndex;
	int numManagers = this->mManagers.Size();
	for (managerIndex = 0; managerIndex < numManagers; ++managerIndex)
	{
		this->mManagers[managerIndex]->OnEndFrame();
	}  
}

//------------------------------------------------------------------------------
/**
    This method is called from Game::GameServer::OnRenderDebug() on all
    game features attached to an GameServer in the order of attachment. It's meant for debug
    issues. It will be called when debug mode is enabled.
*/
void
Feature::OnRenderDebug()
{
    // call OnEndFrame() on managers
	int managerIndex;
	int numManagers = this->mManagers.Size();
	for (managerIndex = 0; managerIndex < numManagers; ++managerIndex)
	{
		this->mManagers[managerIndex]->OnRenderDebug();
	}  
}
//------------------------------------------------------------------------------
/**
    Attach a manager object to the game world. The manager's OnActivate()
    method will be called once right away, and then its OnFrame() method
    once per frame.
*/
void
Feature::AttachManager(const GPtr<Manager>& manager)
{
    n_assert(manager);
    IndexT index = this->mManagers.FindIndex(manager);
    n_assert(InvalidIndex == index);

    manager->OnActivate();
    this->mManagers.Append(manager);

}

//------------------------------------------------------------------------------
/**
    Remove a manager object from the game world. The manager's OnDeactivate()
    method will be called.
*/
void
Feature::RemoveManager(const GPtr<Manager>& manager)
{
    n_assert(manager);
    IndexT index = this->mManagers.FindIndex(manager);
    if (InvalidIndex != index)
    {
        this->mManagers[index]->OnDeactivate();
        this->mManagers.EraseIndex(index);
    }
}
}; // namespace Game
