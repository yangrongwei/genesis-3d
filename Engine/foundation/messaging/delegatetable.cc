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

#include "stdneb.h"
#include "messaging/delegatetable.h"

#if !(__WII__ || __PS3__)
namespace Messaging
{
using namespace Util;

//------------------------------------------------------------------------------
/**
*/
void
DelegateTable::AddDelegate(const Id& msgId, const Delegate<const GPtr<Message>&>& del)
{
    IndexT index = this->idIndexMap.FindIndex(&msgId);
    if (InvalidIndex == index)
    {
        // this is the first delegate for this message id
        Array<Delegate<const GPtr<Message>& > > emptyArray;
        this->delegateArray.Append(emptyArray);
        index = this->delegateArray.Size() - 1;
        this->idIndexMap.Add(&msgId, index);
    }

    // add delegate to lookup table
    this->delegateArray[index].Append(del);
}

//------------------------------------------------------------------------------
/**
*/
bool
DelegateTable::Invoke(const GPtr<Message>& msg)
{
    // check if any delegates have been bound to the message
    IndexT index = this->idIndexMap.FindIndex(&msg->GetId());
    if (InvalidIndex != index)    
    {
        // call delegates for this message
        const Array<Delegate<const GPtr<Message>& > > delegates = this->delegateArray[index];
        IndexT delegateIndex;
        for (delegateIndex = 0; delegateIndex < delegates.Size(); delegateIndex++)
        {
            delegates[delegateIndex](msg);
        }
        return true;
    }
    else
    {
        // no delegates for this message
        return false;
    }
}

} // namespace Messaging
#endif
