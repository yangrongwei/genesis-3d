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
   
#include "messaging/message.h"
#include "messaging/handler.h"
#include "messaging/handlerthreadbase.h"

//------------------------------------------------------------------------------
namespace Messaging
{
class AsyncPort : public Core::RefCounted
{
    __DeclareClass(AsyncPort);
public:
    /// constructor
    AsyncPort();
    /// destructor
    virtual ~AsyncPort();
    
    /// set pointer to handler thread object (must be derived from HandlerThreadBase)
    void SetHandlerThread(const GPtr<HandlerThreadBase>& handlerThread);
    /// get pointer to handler thread object
    const GPtr<HandlerThreadBase>& GetHandlerThread() const;
        
    /// attach a handler to the port, may be called before or after Open()
    virtual void AttachHandler(const GPtr<Handler>& h);
    /// dynamically remove a handler from the port
    virtual void RemoveHandler(const GPtr<Handler>& h);

    /// open the async port
    virtual void Open();
    /// close the async port
    virtual void Close();
    /// return true if port is open
    bool IsOpen() const;

    /// send an asynchronous message to the port
    template<class MESSAGETYPE> void Send(const GPtr<MESSAGETYPE>& msg);
    /// send a message and wait for completion
    template<class MESSAGETYPE> void SendWait(const GPtr<MESSAGETYPE>& msg);
    /// wait for a message to be handled
    template<class MESSAGETYPE> void Wait(const GPtr<MESSAGETYPE>& msg);
    /// peek a message whether it has been handled
    template<class MESSAGETYPE> bool Peek(const GPtr<MESSAGETYPE>& msg);
    /// cancel a pending message
    template<class MESSAGETYPE> void Cancel(const GPtr<MESSAGETYPE>& msg);

private:
    /// send an asynchronous message to the port
    void SendInternal(const GPtr<Message>& msg);
    /// send a message and wait for completion
    void SendWaitInternal(const GPtr<Message>& msg);
    /// wait for a message to be handled
    void WaitInternal(const GPtr<Message>& msg);
    /// peek a message whether it has been handled
    bool PeekInternal(const GPtr<Message>& msg);
    /// cancel a pending message
    void CancelInternal(const GPtr<Message>& msg);

private:
    /// clear all attached message handlers
    void ClearHandlers();

    GPtr<HandlerThreadBase> thread;
    bool isOpen;
};

//------------------------------------------------------------------------------
/**
*/
inline void
AsyncPort::SetHandlerThread(const GPtr<HandlerThreadBase>& handlerThread)
{
    n_assert(!this->IsOpen());
    this->thread = handlerThread;
}

//------------------------------------------------------------------------------
/**
*/
inline const GPtr<HandlerThreadBase>&
AsyncPort::GetHandlerThread() const
{
    return this->thread;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
AsyncPort::IsOpen() const
{
    return this->isOpen;
}

//------------------------------------------------------------------------------
/**
*/
template<class MESSAGETYPE> inline void 
AsyncPort::Send(const GPtr<MESSAGETYPE>& msg)
{
    this->SendInternal((const GPtr<Messaging::Message>&)msg);
}

//------------------------------------------------------------------------------
/**
*/
template<class MESSAGETYPE> inline void 
AsyncPort::SendWait(const GPtr<MESSAGETYPE>& msg)
{
    this->SendWaitInternal((const GPtr<Messaging::Message>&)msg);
}

//------------------------------------------------------------------------------
/**
*/
template<class MESSAGETYPE> inline void 
AsyncPort::Wait(const GPtr<MESSAGETYPE>& msg)
{
    this->WaitInternal((const GPtr<Messaging::Message>&)msg);
}

//------------------------------------------------------------------------------
/**
*/
template<class MESSAGETYPE> inline bool 
AsyncPort::Peek(const GPtr<MESSAGETYPE>& msg)
{
    return this->PeekInternal((const GPtr<Messaging::Message>&)msg);
}

//------------------------------------------------------------------------------
/**
*/
template<class MESSAGETYPE> inline void 
AsyncPort::Cancel(const GPtr<MESSAGETYPE>& msg)
{
    this->CancelInternal((const GPtr<Messaging::Message>&)msg);
}

} // namespace Messaging
//------------------------------------------------------------------------------
