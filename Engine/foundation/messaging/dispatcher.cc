/****************************************************************************
Copyright (c) 2005, Radon Labs GmbH
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
#include "messaging/dispatcher.h"
#include "messaging/port.h"

namespace Messaging
{
__ImplementClass(Messaging::Dispatcher, 'MDIS', Messaging::Port);

//------------------------------------------------------------------------------
/**
*/
Dispatcher::Dispatcher() :
    idPorts(64, 64)
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Attach a new message port.

    @param  port    pointer to a message port object
*/
void
Dispatcher::AttachPort(const GPtr<Port>& port)
{
    n_assert(port);
    n_assert(!this->HasPort(port));

    // add to port array
    this->portArray.Append(port);

    // get the array of accepted messages from the port, and add each message
    // to our own accepted messages, and create a mapping of message ids to ports
    const Util::Array<const Id*>& idArray = port->GetAcceptedMessages();
    IndexT i;
    for (i = 0; i < idArray.Size(); i++)
    {
        const Id* msgIdPtr = idArray[i];
        this->RegisterMessage(*msgIdPtr);
        if (!this->idPortMap.Contains(msgIdPtr))
        {
            // need to add a new empty entry
            Util::Array<GPtr<Port> > emptyArray;
            this->idPorts.Append(emptyArray);
            this->idPortMap.Add(msgIdPtr, this->idPorts.Size() - 1);
        }
        this->idPorts[this->idPortMap[msgIdPtr]].Append(port);
    }
}

//------------------------------------------------------------------------------
/**
    Remove a message port object.

    @param  handler     pointer to message port object to be removed
*/
void
Dispatcher::RemovePort(const GPtr<Port>& port)
{
    n_assert(0 != port);
    n_assert(this->HasPort(port));

    // remove the port from the id/port map
    const Util::Array<const Id*>& idArray = port->GetAcceptedMessages();
    IndexT i;
    for (i = 0; i < idArray.Size(); i++)
    {
        const Id* msgIdPtr = idArray[i];
        if (this->idPortMap.Contains(msgIdPtr))
        {            
            Util::Array<GPtr<Port> >& ports = this->idPorts[this->idPortMap[msgIdPtr]];
            IndexT portIndex = ports.FindIndex(port);
            n_assert(InvalidIndex != portIndex);
            ports.EraseIndex(portIndex);
        }        
    }

    // NOTE: there's no way to remove the message from our accepted messages,
    // so that's not a bug!

    // finally remove the port from the ports array
    IndexT index = this->portArray.FindIndex(port);
    n_assert(InvalidIndex != index);
    this->portArray.EraseIndex(index);
}

//------------------------------------------------------------------------------
/**
    Return true if a port is already attached.
*/
bool
Dispatcher::HasPort(const GPtr<Port>& port) const
{
    n_assert(0 != port);
    return (InvalidIndex != this->portArray.FindIndex(port));
}

//------------------------------------------------------------------------------
/**
    Handle a message. The message will only be distributed to ports
    which accept the message.
*/
void
Dispatcher::HandleMessage(const GPtr<Message>& msg)
{
    const Id* msgIdPtr = &(msg->GetId());
    IndexT mapIndex = this->idPortMap.FindIndex(msgIdPtr);
    if (InvalidIndex != mapIndex)
    {
        const Util::Array<GPtr<Port> >& portArray = this->idPorts[this->idPortMap.ValueAtIndex(mapIndex)];
        IndexT portIndex;
        for (portIndex = 0; portIndex < portArray.Size(); portIndex++)
        {
            portArray[portIndex]->HandleMessage(msg);
        }
    }
}

} // namespace Messaging