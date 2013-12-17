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
#include "http/httpserverproxy.h"
#include "http/httpprotocol.h"
#include "http/httpinterface.h"

namespace Http
{
__ImplementClass(Http::HttpServerProxy, 'HTSP', Core::RefCounted);
__ImplementThreadSingleton(Http::HttpServerProxy);

//------------------------------------------------------------------------------
/**
*/
HttpServerProxy::HttpServerProxy() :
    isOpen(false)
{
    __ConstructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
*/
HttpServerProxy::~HttpServerProxy()
{
    n_assert(!this->isOpen);
    __DestructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void
HttpServerProxy::Open()
{
    n_assert(!this->isOpen);
    n_assert(this->requestHandlers.IsEmpty());
    this->isOpen = true;
}

//------------------------------------------------------------------------------
/**
*/
void
HttpServerProxy::Close()
{
    n_assert(this->isOpen);
    
    // cleanup request handlers
    while (this->requestHandlers.Size() > 0)
    {
        this->RemoveRequestHandler(this->requestHandlers.Back());
    }
    this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
*/
void
HttpServerProxy::AttachRequestHandler(const GPtr<HttpRequestHandler>& requestHandler)
{
    n_assert(this->isOpen);
    this->requestHandlers.Append(requestHandler);

    // register request handler with HttpServer thread 
    GPtr<Http::AttachRequestHandler> msg = Http::AttachRequestHandler::Create();
    msg->SetRequestHandler(requestHandler);
    HttpInterface::Instance()->Send(msg.cast<Messaging::Message>());
}

//------------------------------------------------------------------------------
/**
*/
void
HttpServerProxy::RemoveRequestHandler(const GPtr<HttpRequestHandler>& requestHandler)
{
    n_assert(this->isOpen);    
    IndexT index = this->requestHandlers.FindIndex(requestHandler);
    n_assert(InvalidIndex != index);
    
    // unregister request handler from HttpServer thread
    GPtr<Http::RemoveRequestHandler> msg = Http::RemoveRequestHandler::Create();
    msg->SetRequestHandler(requestHandler);
    HttpInterface::Instance()->Send(msg.cast<Messaging::Message>());

    // delete from local array
    this->requestHandlers.EraseIndex(index);
}

//------------------------------------------------------------------------------
/**
*/
void
HttpServerProxy::HandlePendingRequests()
{
    n_assert(this->isOpen);

    IndexT i;
    for (i = 0; i < this->requestHandlers.Size(); i++)
    {
        this->requestHandlers[i]->HandlePendingRequests();
    }
}

} // namespace Http

#endif