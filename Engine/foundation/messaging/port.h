#pragma once
/****************************************************************************
Copyright (c) 2006, Radon Labs GmbH
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

#include "core/refcounted.h"
#include "core/ptr.h"
#include "messaging/message.h"
#include "messaging/handler.h"

//------------------------------------------------------------------------------
namespace Messaging
{
class Port : public Core::RefCounted
{
    __DeclareClass(Port);
public:
    /// override to register accepted messages
    virtual void SetupAcceptedMessages();
    /// attach a message handler to the port
    void AttachHandler(const GPtr<Handler>& h);
    /// remove a message handler from the port
    void RemoveHandler(const GPtr<Handler>& h);
    /// remove all message handler from the port
    void RemoveAllHandlers();
    /// return number of handlers attached to the port
    SizeT GetNumHandlers() const;
    /// get a message handler by index
    const GPtr<Handler>& GetHandlerAtIndex(IndexT i) const;
    /// send a message to the port
    virtual void Send(const GPtr<Message>& msg);
	/// get the array of accepted messages (sorted)
    const Util::Array<const Id*>& GetAcceptedMessages() const;    
    /// return true if port accepts this msg
    bool AcceptsMessage(const Id& msgId) const;
    /// handle a single accepted message
    virtual void HandleMessage(const GPtr<Messaging::Message>& msg);

protected:
    /// register a single accepted message
    void RegisterMessage(const Id& msgId);

private:
    Util::Array<GPtr<Handler> > handlers;
    Util::Array<const Id*> acceptedMessageIds;
};

//------------------------------------------------------------------------------
/**
*/
inline
SizeT
Port::GetNumHandlers() const
{
    return this->handlers.Size();
}

//------------------------------------------------------------------------------
/**
*/
inline
void
Port::RegisterMessage(const Id& msgId)
{
    // ignore duplicate message ids (may happen when derived classes
    // process the same messages)
    if (InvalidIndex == this->acceptedMessageIds.BinarySearchIndex(&msgId))
    {
        this->acceptedMessageIds.InsertSorted(&msgId);
    }
}

//------------------------------------------------------------------------------
/**
*/
inline
const Util::Array<const Id*>&
Port::GetAcceptedMessages() const
{
    return this->acceptedMessageIds;
}

//------------------------------------------------------------------------------
/**
*/
inline
const GPtr<Handler>&
Port::GetHandlerAtIndex(IndexT i) const
{
    return this->handlers[i];
}

//------------------------------------------------------------------------------
/**
*/
inline
bool 
Port::AcceptsMessage(const Id& msgId) const
{
    return (InvalidIndex != this->acceptedMessageIds.FindIndex(&msgId));
}

} // namespace Messaging
//------------------------------------------------------------------------------
    