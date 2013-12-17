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

#if (__WIN32__ || __APPLE__)

#include "stdneb.h"
#include "http/httpmessagehandler.h"
#include "threading/thread.h"

namespace Http
{
__ImplementClass(Http::HttpMessageHandler, 'HTMH', Interface::InterfaceHandlerBase);

using namespace Interface;
using namespace Messaging;
using namespace Threading;

//------------------------------------------------------------------------------
/**
*/
HttpMessageHandler::HttpMessageHandler()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
HttpMessageHandler::~HttpMessageHandler()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
HttpMessageHandler::Open()
{   
    n_assert(!this->IsOpen());
    InterfaceHandlerBase::Open();

    // setup core runtime and central http server
    this->httpServer = HttpServer::Create();
    this->httpServer->SetPort(DefaultTcpPort);
    this->httpServer->Open();
}

//------------------------------------------------------------------------------
/**
*/
void
HttpMessageHandler::Close()
{
    n_assert(this->IsOpen());

    this->httpServer->Close();
    this->httpServer = 0;

    InterfaceHandlerBase::Close();
}

//------------------------------------------------------------------------------
/**
    Triggers the http server from time to time.
*/
void
HttpMessageHandler::DoWork()
{
    n_assert(this->IsOpen());

    // only process http requests once in a while
    this->httpServer->OnFrame();
    Core::SysFunc::Sleep(0.1f);   
}

//------------------------------------------------------------------------------
/**
*/
bool
HttpMessageHandler::HandleMessage(const GPtr<Message>& msg)
{
    n_assert(msg.isvalid());

    if (msg->CheckId(AttachRequestHandler::Id))
    {
        this->OnAttachRequestHandler(msg.cast<AttachRequestHandler>());
    }
    else if (msg->CheckId(RemoveRequestHandler::Id))
    {
        this->OnRemoveRequestHandler(msg.cast<RemoveRequestHandler>());
    }
    else
    {
        // unknown message
        return false;
    }
    // fallthrough: message was handled
    return true;
}

//------------------------------------------------------------------------------
/**
*/
void
HttpMessageHandler::OnAttachRequestHandler(const GPtr<AttachRequestHandler>& msg)
{
    this->httpServer->AttachRequestHandler(msg->GetRequestHandler());
}

//------------------------------------------------------------------------------
/**
*/
void
HttpMessageHandler::OnRemoveRequestHandler(const GPtr<RemoveRequestHandler>& msg)
{
    this->httpServer->RemoveRequestHandler(msg->GetRequestHandler());
}

} // namespace Http

#endif