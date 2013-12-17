/****************************************************************************
Copyright (c) 2003,Radon Labs GmbH
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
#include "appframework/statehandler.h"

namespace App
{
__ImplementClass(App::StateHandler, 'APST', Core::RefCounted);

//------------------------------------------------------------------------------
/**
*/
StateHandler::StateHandler()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
StateHandler::~StateHandler()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This method is called when the state handler is attached to the App object.
    One-time inits should be done here.
*/
void
StateHandler::OnAttachToApplication()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This method is called when the state handler is removed from
    the App object.
*/
void
StateHandler::OnRemoveFromApplication()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This method is called when the state associated with this state handler
    is entered. The parameter indicates the previously active state.

    @param  prevState   previous state
*/
void
StateHandler::OnStateEnter(const Util::String& prevState)
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This method is called when the state associated with this state handler
    is left. The parameter indicates the next active state.

    @param  nextState   next state
*/
void
StateHandler::OnStateLeave(const Util::String& nextState)
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This method is called on the current application state after the 
    database is opened and before entities are loaded. You can use this
    method to setup managers which depend on a valid database.
*/
void
StateHandler::OnLoadBefore()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This method is called on the current application state after entities 
    have been loaded. You can use this method to setup managers which depend 
    on loaded entities.
*/
void
StateHandler::OnLoadAfter()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This method is called once a frame while the state is active. The method
    must return a state identifier. If this is different from the current
    state, a state switch will occur after the method returns. This method
    MUST be overriden by subclasses.

    @return     a state identifier
*/
Util::String
StateHandler::OnFrame()
{
    return "";
}

} // namespace Application