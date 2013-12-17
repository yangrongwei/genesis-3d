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

#if  (__WIN32__||__APPLE__)


#include "stdneb.h"
#include "http/httpinterface.h"
#include "http/httpmessagehandler.h"
#include "messaging/runthroughhandlerthread.h"
namespace Http
{
__ImplementClass(Http::HttpInterface, 'HTIF', Interface::InterfaceBase);
__ImplementImageSingleton(Http::HttpInterface);

using namespace Interface;
using namespace Messaging;

//------------------------------------------------------------------------------
/**
*/
HttpInterface::HttpInterface()
{
    __ConstructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
HttpInterface::~HttpInterface()
{
    __DestructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void
HttpInterface::Open()
{
    // setup runthrough handler thread
    GPtr<RunThroughHandlerThread> handlerThread = RunThroughHandlerThread::Create();
    handlerThread->SetName("HttpInterface Thread");
    handlerThread->SetCoreId(System::Cpu::MiscThreadCore);
#if __WII_
    handlerThread->SetPriority(Thread::NormalBoost);
#endif    
    handlerThread->AttachHandler(HttpMessageHandler::Create());
    this->SetHandlerThread(handlerThread.cast<HandlerThreadBase>());

    InterfaceBase::Open();
}

} // namespace Http

#endif