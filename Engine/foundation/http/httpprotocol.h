#pragma once
//------------------------------------------------------------------------------
/**
    This file was generated with Nebula3's idlc compiler tool.
    DO NOT EDIT
*/
#include "messaging/message.h"
#include "http/httprequesthandler.h"

//------------------------------------------------------------------------------
namespace Http
{
//------------------------------------------------------------------------------
class AttachRequestHandler : public Messaging::Message
{
    __DeclareClass(AttachRequestHandler);
    __DeclareMsgId;
public:
    AttachRequestHandler() 
    { };
public:
    void SetRequestHandler(const GPtr<Http::HttpRequestHandler>& val)
    {
        n_assert(!this->handled);
        this->requesthandler = val;
    };
    const GPtr<Http::HttpRequestHandler>& GetRequestHandler() const
    {
        return this->requesthandler;
    };
private:
    GPtr<Http::HttpRequestHandler> requesthandler;
};
//------------------------------------------------------------------------------
class RemoveRequestHandler : public Messaging::Message
{
    __DeclareClass(RemoveRequestHandler);
    __DeclareMsgId;
public:
    RemoveRequestHandler() 
    { };
public:
    void SetRequestHandler(const GPtr<Http::HttpRequestHandler>& val)
    {
        n_assert(!this->handled);
        this->requesthandler = val;
    };
    const GPtr<Http::HttpRequestHandler>& GetRequestHandler() const
    {
        return this->requesthandler;
    };
private:
    GPtr<Http::HttpRequestHandler> requesthandler;
};
} // namespace Http
//------------------------------------------------------------------------------
