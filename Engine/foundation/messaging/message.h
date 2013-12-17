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
#include "io/binaryreader.h"
#include "io/binarywriter.h"
#include "messaging/id.h"
#include "threading/interlocked.h"
#include "util/stringatom.h"

//------------------------------------------------------------------------------
/**
    Message Id macros.
*/
#define __DeclareMsgId \
public:\
    static Messaging::Id Id; \
    virtual const Messaging::Id& GetId() const;\
private:

#define __ImplementMsgId(type) \
    Messaging::Id type::Id; \
    const Messaging::Id& type::GetId() const { return type::Id; }

//------------------------------------------------------------------------------
namespace Messaging
{
class MessageReader;
class MessageWriter;
class Port;

class Message : public Core::RefCounted
{
    __DeclareClass(Message);
    __DeclareMsgId;
public:
    /// constructor
    Message();
    /// return true if message is of the given id
    bool CheckId(const Messaging::Id& id) const;
    /// encode message into a stream
    virtual void Encode(const GPtr<IO::BinaryWriter>& writer);
    /// decode message from a stream
    virtual void Decode(const GPtr<IO::BinaryReader>& reader);
    /// set the handled flag
    void SetHandled(bool b);
    /// return true if the message has been handled
    bool Handled() const;
    /// set deferred flag
    void SetDeferred(bool b);
    /// get deferred flag
    bool IsDeferred() const;
    /// set the deferred handled flag
    void SetDeferredHandled(bool b);
    /// get the deferred handled flag
    bool DeferredHandled() const;
protected:
    volatile int handled;
    bool deferred;
    bool deferredHandled;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
Message::CheckId(const Messaging::Id& id) const
{
    return (id == this->GetId());
}

//------------------------------------------------------------------------------
/**
*/
inline void
Message::SetHandled(bool b)
{
    Threading::Interlocked::Exchange(&this->handled, (int)b);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Message::Handled() const
{
    return 0 != this->handled;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Message::SetDeferred(bool b)
{
    this->deferred = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Message::IsDeferred() const
{
    return this->deferred;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Message::SetDeferredHandled(bool b)
{
    this->deferredHandled = b;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Message::DeferredHandled() const
{
    return this->deferredHandled;
}

} // namespace Messaging
//------------------------------------------------------------------------------
