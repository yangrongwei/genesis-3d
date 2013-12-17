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
#include "appframework/manager.h"

namespace App
{
__ImplementClass(App::Manager, 'GAMA', Messaging::Port);

//------------------------------------------------------------------------------
/**
*/
Manager::Manager() :
    mIsActive(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Manager::~Manager()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This method is called when the manager is attached to the game server.
    The manager base class will register its message port with the
    message server.
*/
void
Manager::OnActivate()
{
    n_assert(!this->mIsActive);
    this->mIsActive = true;
}

//------------------------------------------------------------------------------
/**
    This method is called when the manager is removed from the game server.
    It will unregister its message port from the message server at this point.
*/
void
Manager::OnDeactivate()
{
    n_assert(this->mIsActive);
    this->mIsActive = false;
}

//------------------------------------------------------------------------------
/**
    Called before frame, override in subclasses
*/
void
Manager::OnBeginFrame()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
Manager::OnFrame()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Called after frame, override in subclasses
*/
void
Manager::OnEndFrame()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
Manager::OnLoad()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
Manager::OnRenderDebug()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
Manager::OnSave()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
Manager::OnStart()
{
    // empty
}
//------------------------------------------------------------------------
void Manager::OnStop()
{
	// empty
}

}; // namespace Game
