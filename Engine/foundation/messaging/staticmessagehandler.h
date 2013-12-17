#pragma once
/****************************************************************************
Copyright (c) 2010, Radon Labs GmbH
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

//------------------------------------------------------------------------------
namespace Messaging
{
class StaticMessageHandler
{
public:
    /// dispatch a message to handling method
    template<class OBJTYPE> static void Dispatch(const GPtr<OBJTYPE>& object, const GPtr<Message>& msg);
    /// a handler method with object association
    template<class OBJTYPE, class MSGTYPE> static void Handle(const GPtr<OBJTYPE>& object, const GPtr<MSGTYPE>& msg);
    /// a handler method without object association
    template<class MSGTYPE> static void Handle(const GPtr<MSGTYPE>& msg);
};

//------------------------------------------------------------------------------
/**
*/
#define __Dispatch(OBJCLASS,OBJ,MSG) Messaging::StaticMessageHandler::Dispatch<OBJCLASS>(OBJ, MSG)
#define __Dispatcher(OBJCLASS) template<> void Messaging::StaticMessageHandler::Dispatch(const GPtr<OBJCLASS>& obj, const GPtr<Messaging::Message>& msg)
#define __Handle(OBJCLASS,MSGCLASS) if (msg->CheckId(MSGCLASS::Id)) { Messaging::StaticMessageHandler::Handle<OBJCLASS,MSGCLASS>(obj, msg.downcast<MSGCLASS>()); return; }
#define __StaticHandle(MSGCLASS) if (msg->CheckId(MSGCLASS::Id)) { Messaging::StaticMessageHandler::Handle<MSGCLASS>(msg.downcast<MSGCLASS>()); return true; }
#define __HandleByRTTI(OBJCLASS,MSGCLASS) if (msg->IsA(MSGCLASS::RTTI)) { Messaging::StaticMessageHandler::Handle<OBJCLASS,MSGCLASS>(obj, msg.downcast<MSGCLASS>()); return; }
#define __HandleUnknown(SUPERCLASS) { Messaging::StaticMessageHandler::Dispatch<SUPERCLASS>(obj.upcast<SUPERCLASS>(), msg); }
#define __Handler(OBJCLASS,MSGCLASS) template<> void Messaging::StaticMessageHandler::Handle<OBJCLASS,MSGCLASS>(const GPtr<OBJCLASS>& obj, const GPtr<MSGCLASS>& msg)
#define __StaticHandler(MSGCLASS) template<> void Messaging::StaticMessageHandler::Handle<MSGCLASS>(const GPtr<MSGCLASS>& msg)

} // namespace Messaging  