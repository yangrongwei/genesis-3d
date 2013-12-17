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
#include "messaging/message.h"

//-----------------------------------------------------------------------------
namespace Messaging
{
class Handler : public Core::RefCounted
{
    __DeclareSubClass(Handler, Core::RefCounted);
public:
    /// constructor
    Handler();
    /// destructor
    virtual ~Handler();
    /// called once on startup 
    virtual void Open();
    /// called once before shutdown
    virtual void Close();
    /// return true if open
    bool IsOpen() const;
    /// handle a message, return true if handled
    virtual bool HandleMessage(const GPtr<Message>& msg);
    /// optional "per-frame" DoWork method for continuous handlers
    virtual void DoWork();
protected:
    bool isOpen;
};

//-----------------------------------------------------------------------------
/**
*/
inline bool
Handler::IsOpen() const
{
    return this->isOpen;
}

} // namespace Messaging
//-----------------------------------------------------------------------------
    
    