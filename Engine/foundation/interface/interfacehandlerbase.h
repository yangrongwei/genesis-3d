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

#pragma once
//------------------------------------------------------------------------------
/**
    @class Interface::InterfaceHandlerBase
    
    Base class for message handlers attached to Interface objects.
*/
#include "messaging/handler.h"
#include "util/stringatom.h"

//------------------------------------------------------------------------------
namespace Interface
{
class InterfaceHandlerBase : public Messaging::Handler
{
    __DeclareSubClass(InterfaceHandlerBase, Messaging::Handler);
public:
    /// constructor
    InterfaceHandlerBase();
    /// set the company name
    void SetCompanyName(const Util::StringAtom& companyName);
    /// get the company name
    const Util::StringAtom& GetCompanyName() const;
    /// set the application name
    void SetAppName(const Util::StringAtom& appName);
    /// get the application name
    const Util::StringAtom& GetAppName() const;
    /// optional "per-frame" DoWork method for continuous handlers
    virtual void DoWork();

protected:
    Util::StringAtom companyName;
    Util::StringAtom appName;
};

//------------------------------------------------------------------------------
/**
*/
inline void
InterfaceHandlerBase::SetCompanyName(const Util::StringAtom& n)
{
    this->companyName = n;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::StringAtom&
InterfaceHandlerBase::GetCompanyName() const
{
    return this->companyName;
}

//------------------------------------------------------------------------------
/**
*/
inline void
InterfaceHandlerBase::SetAppName(const Util::StringAtom& n)
{
    this->appName = n;
}

//------------------------------------------------------------------------------
/**
*/
inline const Util::StringAtom&
InterfaceHandlerBase::GetAppName() const
{
    return this->appName;
}

} // namespace Interface
//------------------------------------------------------------------------------
