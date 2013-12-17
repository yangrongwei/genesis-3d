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
#include "appframework/component.h"
#include "appframework/actor.h"


namespace App
{
__ImplementClass(App::Component, 'GCOM' ,Messaging::Port);

const  GPtr<Component> Component::NullComplonent;
//------------------------------------------------------------------------------
/**
*/
Component::Component() : 
mActive(false)
#if NEBULA3_DEBUG
, mDestoried(false)
#endif
, mActor(NULL)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Component::~Component()
{
    n_assert(!this->mActor);
}

//------------------------------------------------------------------------------
/**
    Tells the Actor what per-frame callback methods should be called
    for this Component. and the Component is expected to call the 
    Actor::RegisterComponentCallback() once for every callback method
    (OnBeginFrame(), OnMoveBefore(), ...) that should be called per-frame.
*/
void
Component::SetupCallbacks()
{
    // empty, derive this method in a subclass
}

//------------------------------------------------------------------------------
/**
    This method is called by App::Actor::ActivateComponents(). 
    Use this method for one-time initializations of the Component.
*/
void
Component::OnActivate()
{
	n_assert(!this->IsActive() && mActor != NULL);
	this->mActive = true;
}

//------------------------------------------------------------------------------
/**
    This method is called by App::Actor::DeactivateComponents(). Use this 
    method to cleanup stuff which has been initialized in OnActivate().
*/
void
Component::OnDeactivate()
{
    n_assert(this->IsActive());
    this->mActive = false;
}
//------------------------------------------------------------------------
void 
Component::OnDestroy()
{
	n_assert( !this->IsActive() );
#if NEBULA3_DEBUG
	mDestoried = true;
#endif
}
//------------------------------------------------------------------------
void 
Component::OnRenderSceneChanged()
{
	///empty..
}
//------------------------------------------------------------------------
void 
Component::OnActorParentChanged()
{
	///empty..
}

//------------------------------------------------------------------------------
/**
*/
const Math::matrix44&
Component::GetActorTransform() const
{
	Actor* actor = GetActor();
	n_assert(actor);
	return actor->GetTransform();

}
//------------------------------------------------------------------------------
/**
    This method is called from App::Actor::OnBeginFrame() on all 
    Components attached to an Actor in the order of attachment. Override this 
    method if your Component has to do any work at the beginning of the frame.
	Note: you must call Super::OnBeginFrame in your Sub Component::OnBeginFrame!
*/
void
Component::_OnBeginFrame()
{
	_SetInternalTransform();
}

//------------------------------------------------------------------------------
/**
    This method is called from App::Actor::OnBeginFrame() on all 
    Components attached to an Actor in the order of attachment. Override this 
    method if your Component has to do any work at the beginning of the frame.
	Note: you must implement this function in your sub component class!
*/
void Component::_SetInternalTransform()
{
	// empty
}
//------------------------------------------------------------------------------
/**
    This method is called from App::Actor::OnMoveBefore() on all 
    Components attached to an Actor in the order of attachment. Override this
    method if your Component has any work to do before the physics subsystem
    is triggered.
*/
void
Component::_OnMoveBefore()
{
	//empty
}

//------------------------------------------------------------------------------
/**
    This method is called from App::Actor::OnMoveAfter() on all
    Components attached to an Actor in the order of attachment. Override this
    method if your Component has any work to do after the physics subsystem
    has been triggered.
*/
void
Component::_OnMoveAfter()
{
	//empty
}

//------------------------------------------------------------------------------
/**
    This method is called from App::Actor::OnFrame() on all
    Components attached to an Actor in the order of attachment. Override
    this method if your Component has any work to do before rendering happens.
*/
void
Component::_OnFrame()
{
	//empty
}
//------------------------------------------------------------------------
void 
Component::_OnEndFrame()
{
	// empty
}

//------------------------------------------------------------------------------
/**
    This method is called from App::Actor::OnRenderDebug() on all
    Components attached to an Actor in the order of attachment. It's meant for debug
    issues. It will be called when debug mode is enabled.
*/
void
Component::_OnRenderDebug()
{
	//empty
}

//------------------------------------------------------------------------------
/**
*/
void
Component::HandleMessage(const GPtr<Messaging::Message>& msg)
{
    // empty, override in subclass
}

//------------------------------------------------------------------------------
/**
*/
void
Component::_SetActor(Actor* e)
{
	n_assert(e != 0);
	n_assert(!this->HasActor());
	this->mActor = e;
}

//------------------------------------------------------------------------------
/**
*/
void
Component::_ClearActor()
{
	this->mActor = 0;
}

//------------------------------------------------------------------------
void Component::CopyFrom( const GPtr<Component>& pComponent )
{
	n_error("Component::CopyFrom not implement now ");
}

bool
Component::IsAllResourceLoaded()
{
	n_error("Component::IsAllResourceLoaded has not implemented now !");
	return true;
}

void
Component::SetupAllResource()
{
	//n_error("Component::IsAllResourceLoaded has not implemented now !");
	return;
}

//------------------------------------------------------------------------
void Component::GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const
{
	// empty.
}


void Component::UpdateRenderLayer()
{

}


}; // namespace Game
