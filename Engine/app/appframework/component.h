/****************************************************************************
Copyright (c) 2002, Radon Labs GmbH
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
#ifndef __component_H__
#define __component_H__

#include "app/appframework/app_fwd_decl.h"
#include "foundation/util/scriptbind.h"
#include "resource/resource.h"
#include "app/appframework/serialization.h"
#include "messaging/port.h"
#include "messaging/message.h"

//------------------------------------------------------------------------------
namespace App
{
class Actor;
class ComponentSerialization;

class Component : public Messaging::Port, App::ISerialization
{
    __DeclareClass(Component);
	// this macro shall not be appear in other child component!
	__ScriptBind
public:
	const static GPtr<Component> NullComplonent;
    
	/// callback types. will called for the active actor's status change
    enum CallbackType
    {
		BeginFrame = 0,             // please call Actor::OnBeginFrame()
        OnFrame,                    // please call Actor::OnFrame()
		EndFrame,					// please call Actor::OnEndFrame()
        MoveBefore,                 // please call Actor::OnMoveBefore()
        MoveAfter,                  // please call Actor::OnMoveAfter()
        RenderDebug,                // please call Actor::OnRenderDebug()
        NumCallbackTypes,           // KEEP AT END
    };

    /// constructor
    Component();
    /// destructor
    virtual ~Component();

	

	/// setup callbacks for this Component, call by Actor in OnActivate()
	virtual void SetupCallbacks(void);

	/// handle a single message
	virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

	virtual void SetupAllResource();
	virtual bool IsAllResourceLoaded();

	// Serialization. do not call load save directly
	// @ISerialization::GetVersion. when change storage, must add SerializeVersion count
	virtual Version GetVersion(void) const;

	// @ISerialization::Load 
	virtual void Load( Version ver, AppReader* pReader, const Serialization::SerializationArgs* args );

	// @ISerialization::Save
	virtual void Save( AppWriter* pWriter ) const;

	// copy from other component
	virtual void CopyFrom( const GPtr<Component>& pComponent );

	/// list all reference resource ids
	virtual void GetReferenceResourceId(Util::Array<Resources::ReferenceResource>& list) const;

	virtual void UpdateRenderLayer();

	/// get Actor this Component is attached to
	Actor* GetActor(void) const;

	/// return true if Actor pointer is valid
	bool HasActor(void) const;

	/// return Actor Transform
	const Math::matrix44& GetActorTransform(void) const;

	/// return true if Component is currently active
	bool IsActive(void) const;

	// send message to script
	template<typename T> 
	void SendMessageToScript(const Util::String& name,T& pair);

protected:
	/// called only from Actor::ActivateComponents()
	virtual void OnActivate(void);

	/// called only from Actor::DeactivateComponents()
	virtual void OnDeactivate(void);

	// called only form Actor::Destroy
	virtual void OnDestroy(void);

	virtual void OnRenderSceneChanged();

	virtual void OnActorParentChanged();

	/// called on begin of frame
	virtual void _OnBeginFrame();
	/// called before movement happens
	virtual void _OnMoveBefore();
	/// called after movement has happened
	virtual void _OnMoveAfter();
	/// called before rendering happens
	virtual void _OnFrame();
	/// called before rendering happens
	virtual void _OnEndFrame();
	/// called when game debug visualization is on
	virtual void _OnRenderDebug();

	/// Set actor, this is attached to, to `v'.
	virtual void _SetActor(Actor* v);

	/// Remove Actor.
	void _ClearActor(void);

	/// Setup all internal transform when BeginFrame
	virtual void _SetInternalTransform();

	void Component_force_compiler();

protected:

    Actor* mActor;
	bool mActive;
	

#if NEBULA3_DEBUG
	bool mDestoried;
#endif


	friend class Actor;
	friend class ComponentSerialization;
};
//------------------------------------------------------------------------------
/**
*/
inline 
bool
Component::IsActive() const
{
    return this->mActive;
}
//------------------------------------------------------------------------------
/**
*/
inline Actor*
Component::GetActor() const
{
    return this->mActor;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Component::HasActor() const
{
	return this->mActor != NULL;
}

}; // namespace Component

#endif // __component_H__





