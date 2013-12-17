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

#include "stdneb.h"
#include "messaging/asyncport.h"

namespace Messaging
{
__ImplementClass(Messaging::AsyncPort, 'ASPT', Core::RefCounted);

using namespace Util;
using namespace Threading;

//------------------------------------------------------------------------------
/**
*/
AsyncPort::AsyncPort() :
    isOpen(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
AsyncPort::~AsyncPort()
{
    if (this->IsOpen())
    {
        this->Close();
    }
    this->thread = 0;
}

//------------------------------------------------------------------------------
/**
    Open the async port. The async port needs a valid name before it
    is opened. Messages can only be sent to an open port.
*/
void
AsyncPort::Open()
{
    n_assert(!this->IsOpen());
    n_assert(this->thread.isvalid());

    // start the handler thread, and wait until handlers are open
    this->thread->Start();
    this->thread->WaitForHandlersOpened();

    this->isOpen = true;
}

//------------------------------------------------------------------------------
/**
    Closes the async port.
*/
void
AsyncPort::Close()
{
    n_assert(this->IsOpen());
    this->thread->Stop();
    this->thread->ClearHandlers();
    this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
    Add a message handler, this can either be called before the handler
    thread is started, or any time afterwards.
*/
void
AsyncPort::AttachHandler(const GPtr<Handler>& h)
{
    this->thread->AttachHandler(h);
}

//------------------------------------------------------------------------------
/**
    Dynamically remove a message handler.
*/
void
AsyncPort::RemoveHandler(const GPtr<Handler>& h)
{
    this->thread->RemoveHandler(h);
}

//------------------------------------------------------------------------------
/**
    Handle an asynchronous message and return immediately. If the caller
    expects any results from the message he can poll with the AsyncPort::Peek()
    method, or he may wait for the message to be handled with the 
    AsyncPort::Wait() method.
*/
void
AsyncPort::SendInternal(const GPtr<Message>& msg)
{
    n_assert(msg.isvalid());
    n_assert(this->thread.isvalid());
    n_assert(!msg->Handled());
    this->thread->AddMessage(msg);
}

//------------------------------------------------------------------------------
/**
    Send an asynchronous message and wait until the message has been
    handled.
*/
void
AsyncPort::SendWaitInternal(const GPtr<Message>& msg)
{
    this->Send(msg);
    this->Wait(msg);
}

//------------------------------------------------------------------------------
/**
    This method peeks whether a message has already been handled. If the
    caller expects any return arguments from the message handling it 
    can use this message to check whether the results are ready using
    this non-blocking method. The caller can also wait for the results
    to become ready using the Wait() method.
*/
bool
AsyncPort::PeekInternal(const GPtr<Message>& msg)
{
    n_assert(msg.isvalid());
    return msg->Handled();
}

//------------------------------------------------------------------------------
/**
    This method will cancel a pending message.
*/
void
AsyncPort::CancelInternal(const GPtr<Message>& msg)
{
    n_assert(msg.isvalid());
    n_assert(this->thread.isvalid());
    this->thread->CancelMessage(msg);
}

//------------------------------------------------------------------------------
/**
    This method will wait until a message has been handled. If the caller
    expects any return arguments from the message handling it can use
    this method to wait for the results.
*/
void
AsyncPort::WaitInternal(const GPtr<Message>& msg)
{
    n_assert(msg.isvalid());
    n_assert(this->thread.isvalid());

    // only wait if the message hasn't been handled yet
    if (!msg->Handled())
    {
        this->thread->WaitForMessage(msg);
        n_assert(msg->Handled());
    }
}

} // namespace Messaging
