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
#include "messaging/handler.h"

namespace Messaging
{
__ImplementClass(Messaging::Handler, 'MHDL', Core::RefCounted);

//------------------------------------------------------------------------------
/**
*/
Handler::Handler() :
    isOpen(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Handler::~Handler()
{
    n_assert(!this->IsOpen());
}

//------------------------------------------------------------------------------
/**
    Open the handler. This method is called once after the handler has been
    attached to a port and before the first call to HandleMessage().
*/
void
Handler::Open()
{
    n_assert(!this->IsOpen());
    this->isOpen = true;
}

//------------------------------------------------------------------------------
/**
    Close the handler. This method is called once before the handler
    is detached from the port.
*/
void
Handler::Close()
{
    n_assert(this->IsOpen());
    this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
    Derive this method in a subclass to handle specific messages. The method
    should return true only if a message has been handled.
*/
bool
Handler::HandleMessage(const GPtr<Message>& msg)
{
    n_assert(msg.isvalid());
    n_assert(this->isOpen);
    return false;
}

//------------------------------------------------------------------------------
/**
    This is an optional method for handlers which need to do continuous
    work (like a render thread message handler). This message will
    be called after messages have been handled.
*/
void
Handler::DoWork()
{
    // empty, override in subclass
    n_assert2(this->isOpen, this->GetRtti()->GetName().AsCharPtr());
}

} // namespace Messaging
