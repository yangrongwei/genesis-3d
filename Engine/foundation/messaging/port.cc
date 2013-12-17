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
#include "messaging/port.h"

namespace Messaging
{
__ImplementClass(Messaging::Port, 'PORT', Core::RefCounted);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
void
Port::SetupAcceptedMessages()
{
    // overwrite in subclass
}

//------------------------------------------------------------------------------
/**
    Attach a message handler to the port. 
*/
void
Port::AttachHandler(const GPtr<Handler>& h)
{
    n_assert(h.isvalid());
    n_assert(InvalidIndex == this->handlers.FindIndex(h));
    this->handlers.Append(h);
    h->Open();
}

//------------------------------------------------------------------------------
/**
    Remove a message handler from the port. 
*/
void
Port::RemoveHandler(const GPtr<Handler>& h)
{
    n_assert(h.isvalid());
    IndexT index = this->handlers.FindIndex(h);
    n_assert(InvalidIndex != index);
    h->Close();
    this->handlers.EraseIndex(index);
}

//------------------------------------------------------------------------------
/**
    Send a message to the port. This will immediately call the HandleMessage()
    method of all attached handlers. If the message has been handled by at least
    one of the handlers, the Handled() flag of the message will be set to true.
*/
void
Port::Send(const GPtr<Message>& msg)
{
    n_assert(msg.isvalid());
    Array<GPtr<Handler> >::Iterator iter;
    for (iter = this->handlers.Begin(); iter < this->handlers.End(); iter++)
    {
        if ((*iter)->HandleMessage(msg))
        {
            // message had been handled by this handler
            /// @todo should we stop here, once the message had been handled...?
            msg->SetHandled(true);
        }
    }
}
//------------------------------------------------------------------------------
/**
    Handle a specific message. Overwrite this method in a subclass.
    It is guaranteed that this method will only be called for messages
    which are accepted by AcceptMessage().
*/
void
Port::HandleMessage(const GPtr<Messaging::Message>& msg)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void 
Port::RemoveAllHandlers()
{
    IndexT i;
    for (i = 0; i < this->handlers.Size(); i++)
    {
        if (this->handlers[i]->IsOpen())
        {
            this->handlers[i]->Close();
        }
    }
    this->handlers.Clear();
}
} // namespace Messaging
