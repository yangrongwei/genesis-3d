#pragma once
/****************************************************************************
Copyright (c) 2007, Radon Labs GmbH
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

//------------------------------------------------------------------------------
/**
    @class Messaging::Dispatcher

    A message Dispatcher is a specialization of a message Port. A message
    Dispatcher distributes all messages it receives to the attached Ports
    which are interested in this message id.

    @verbatim
                                    +------+
                                +-->| Port |
                               /    +------+
                +------------+/     +------+
    --- Msg --->| Dispatcher |----->| Port |
                +------------+\     +------+
                               \    +------+
                                +-->| Port |
                                    +------+
    @endverbatim

    Dispatcher objects usually serve as front end message ports which hide
    a more complex message processing infrastructure underneath.

    (C) 2007 RadonLabs GmbH
*/
#include "core/ptr.h"
#include "messaging/port.h"

//------------------------------------------------------------------------------
namespace Messaging
{
class Dispatcher : public Port
{
	__DeclareClass(Dispatcher);
public:
    /// constructor
    Dispatcher();
    /// handle a single message (distribute to ports which accept the message)
    virtual void HandleMessage(const GPtr<Messaging::Message>& msg);
    /// attach a message port
    void AttachPort(const GPtr<Port>& port);
    /// remove a message port
    void RemovePort(const GPtr<Port>& port);
    /// return true if a port exists
    bool HasPort(const GPtr<Port>& port) const;

private:
    Util::Array<GPtr<Port> > portArray;
    Util::Array<Util::Array<GPtr<Port> > > idPorts;             // one entry per message, contains ports which accepts the message
    Util::Dictionary<const Id*,IndexT> idPortMap;    // maps message id's to indices in the msgIdPorts array
};

} // namespace Message
//------------------------------------------------------------------------------
