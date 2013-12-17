#pragma once
/****************************************************************************
Copyright (c) 2009, Radon Labs GmbH
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

#include "threading/thread.h"
#include "threading/event.h"
#include "threading/criticalsection.h"
#include "messaging/handler.h"
#include "messaging/message.h"

//------------------------------------------------------------------------------
namespace Messaging
{
class HandlerThreadBase : public Threading::Thread
{
    __DeclareClass(HandlerThreadBase);
public:
    /// constructor
    HandlerThreadBase();
    
    /// attach a message handler
    void AttachHandler(const GPtr<Handler>& h);
    /// dynamically remove a message handler
    void RemoveHandler(const GPtr<Handler>& h);
    /// clear all attached message handlers
    void ClearHandlers();
    /// wait until handlers have been opened
    void WaitForHandlersOpened();

    /// add a message to be handled (override in subclass!)
    virtual void AddMessage(const GPtr<Message>& msg);
    /// cancel a pending message (override in subclass!)
    virtual void CancelMessage(const GPtr<Message>& msg);
    /// wait for message to be handled  (optionally override in subclass!)
    virtual void WaitForMessage(const GPtr<Message>& msg);

protected:
    /// open message handlers
    void ThreadOpenHandlers();
    /// close message handlers
    void ThreadCloseHandlers();
    /// open dynamically added handlers, and call DoWork() on all attached handlers
    void ThreadUpdateHandlers();
    /// update deferred messages, return true if at least one message has been handled
    bool ThreadUpdateDeferredMessages();
    /// clear leftover deferred messages
    void ThreadDiscardDeferredMessages();
    /// handle messages in array, return true if at least one message has been handled
    bool ThreadHandleMessages(const Util::Array<GPtr<Message> >& msgArray);
    /// handle a single message without deferred support, return if message has been handled
    bool ThreadHandleSingleMessage(const GPtr<Message>& msg);
    /// signal message handled event (only call if at least one message has been handled)
    void ThreadSignalMessageHandled();

    Threading::Event msgHandledEvent;
    Threading::Event handlersOpenedEvent;
    Threading::CriticalSection handlersCritSect;
    Util::Array<GPtr<Handler> > handlers;
    Util::Array<GPtr<Message> > deferredMessages;
};

} // namespace Messaging
//------------------------------------------------------------------------------
