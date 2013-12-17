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

#pragma once
#ifndef HTTP_HTTPMESSAGEHANDLER_H
#define HTTP_HTTPMESSAGEHANDLER_H
//------------------------------------------------------------------------------
/**
    @class Http::HttpMessageHandler
    
    Runs the HttpServer thread, and owns the central http server. Processes
    messages sent to the HttpInterface from other threads.

*/
#include "interface/interfacehandlerbase.h"
#include "messaging/message.h"
#include "io/console.h"
#include "http/httpserver.h"
#include "http/httpprotocol.h"

//------------------------------------------------------------------------------
namespace Http
{
class HttpMessageHandler : public Interface::InterfaceHandlerBase
{
    __DeclareClass(HttpMessageHandler);
public:
    /// constructor
    HttpMessageHandler();
    /// destructor
    virtual ~HttpMessageHandler();

    /// open the handler
    virtual void Open();
    /// close the handler
    virtual void Close();
    /// handle a message, return true if handled
    virtual bool HandleMessage(const GPtr<Messaging::Message>& msg);
    /// do per-frame work
    virtual void DoWork();

private:
    static const ushort DefaultTcpPort = 2100;

    /// handle AttachRequestHandler message
    void OnAttachRequestHandler(const GPtr<AttachRequestHandler>& msg);
    /// handle RemoveRequestHandler message
    void OnRemoveRequestHandler(const GPtr<RemoveRequestHandler>& msg);

    GPtr<HttpServer> httpServer;
};

} // namespace HttpMessageHandler
//------------------------------------------------------------------------------
#endif
