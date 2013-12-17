#pragma once
#if !(__WII__ || __PS3__)   // fast delegates not supported on CodeWarrior...
/****************************************************************************
Copyright (c) 2008, Radon Labs GmbH
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

#include "util/delegate.h"
#include "messaging/id.h"
#include "messaging/message.h"

//------------------------------------------------------------------------------
namespace Messaging
{
class DelegateTable
{
public:
    /// bind a message id to a method call
    template<class CLASS, void (CLASS::*METHOD)(const GPtr<Message>&)> void Bind(const Id& msgId, CLASS* obj);
    /// invoke delegates bound to msg, returns false if no delegates bound to msg id
    bool Invoke(const GPtr<Message>& msg);
    
private:
    /// add a delegate
    void AddDelegate(const Id& msgId, const Util::Delegate<const GPtr<Message>&>& del);

    Util::Array<Util::Array<Util::Delegate<const GPtr<Message>& > > > delegateArray;
    Util::Dictionary<const Id*, IndexT> idIndexMap;
};

//------------------------------------------------------------------------------
/**
*/
template<class CLASS, void (CLASS::*METHOD)(const GPtr<Message>&)>
void
DelegateTable::Bind(const Id& msgId, CLASS* obj)
{
    // setup a new delegate
    Util::Delegate<const GPtr<Message>&> del = Util::Delegate<const GPtr<Message>&>::FromMethod<CLASS,METHOD>(obj);
    this->AddDelegate(msgId, del);
}

} // namespace Messaging
//------------------------------------------------------------------------------
#endif