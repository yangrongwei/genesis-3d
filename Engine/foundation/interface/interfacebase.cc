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

#include "stdneb.h"
#include "interface/interfacebase.h"
#include "interface/interfacehandlerbase.h"
#include "core/coreserver.h"

namespace Interface
{
__ImplementClass(Interface::InterfaceBase, 'INBS', Messaging::AsyncPort);

using namespace Core;

//------------------------------------------------------------------------------
/**
*/
InterfaceBase::InterfaceBase() :
    rootDirectory("home:")
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
InterfaceBase::~InterfaceBase()        
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
InterfaceBase::Open()
{
    n_assert(!this->IsOpen());
    
    // set core server attributes
    this->SetCompanyName(CoreServer::Instance()->GetCompanyName());
    this->SetAppName(CoreServer::Instance()->GetAppName());
    this->SetRootDirectory(CoreServer::Instance()->GetRootDirectory());

    Messaging::AsyncPort::Open();
}

//------------------------------------------------------------------------------
/**
*/
void
InterfaceBase::AttachHandler(const GPtr<Messaging::Handler>& handler)
{
    // set application attributes on handler
    const GPtr<InterfaceHandlerBase>& interfaceHandler = handler.downcast<InterfaceHandlerBase>();
    interfaceHandler->SetCompanyName(this->companyName);
    interfaceHandler->SetAppName(this->appName);

    // call parent class
    Messaging::AsyncPort::AttachHandler(handler);
}

} // namespace Interface