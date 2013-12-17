#pragma once
//------------------------------------------------------------------------------
/**
    This file was generated with Nebula3's idlc compiler tool.
    DO NOT EDIT
*/
#include "messaging/message.h"
#include "util/variant.h"
#include "appframework/component.h"

//------------------------------------------------------------------------------
namespace App
{
//------------------------------------------------------------------------------
class AttachComponentMsg : public Messaging::Message
{
    __DeclareClass(AttachComponentMsg);
    __DeclareMsgId;
public:
    AttachComponentMsg() 
    { };
public:
    void SetObject(const GPtr<App::Component>& val)
    {
        n_assert(!this->handled);
        this->object = val;
    };
    const GPtr<App::Component>& GetObject() const
    {
        return this->object;
    };
private:
    GPtr<App::Component> object;
};
//------------------------------------------------------------------------------
class DeAttachComponentMsg : public Messaging::Message
{
    __DeclareClass(DeAttachComponentMsg);
    __DeclareMsgId;
public:
    DeAttachComponentMsg() 
    { };
public:
    void SetObject(const GPtr<App::Component>& val)
    {
        n_assert(!this->handled);
        this->object = val;
    };
    const GPtr<App::Component>& GetObject() const
    {
        return this->object;
    };
private:
    GPtr<App::Component> object;
};
} // namespace App
//------------------------------------------------------------------------------
