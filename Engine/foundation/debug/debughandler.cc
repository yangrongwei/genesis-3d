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
#include "debug/debughandler.h"
#include "debug/debugpagehandler.h"
#include "timing/time.h"

namespace Debug
{
__ImplementClass(Debug::DebugHandler, 'DBGH', Interface::InterfaceHandlerBase);

using namespace Util;
using namespace Http;
using namespace Interface;

//------------------------------------------------------------------------------
/**
*/
DebugHandler::DebugHandler()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
DebugHandler::~DebugHandler()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This method runs in the Debug thread's context and sets up the required
    runtime.
*/
void
DebugHandler::Open()
{
    n_assert(!this->IsOpen());
    InterfaceHandlerBase::Open();

    // setup core runtime, debug server and a http server proxy
    this->debugServer = DebugServer::Create();
    this->debugServer->Open();

    this->httpServerProxy = HttpServerProxy::Create();
    this->httpServerProxy->Open();
    this->httpServerProxy->AttachRequestHandler(Debug::DebugPageHandler::Create());
}

//------------------------------------------------------------------------------
/**
*/
void
DebugHandler::Close()
{
    n_assert(this->IsOpen());

    this->httpServerProxy->Close();
    this->httpServerProxy = 0;

    this->debugServer->Close();
    this->debugServer = 0;

    InterfaceHandlerBase::Close();
}

//------------------------------------------------------------------------------
/**
    The per-frame method just checks periodically whether there are
    any pending HttpRequests to process...
*/
void
DebugHandler::DoWork()
{
    n_assert(this->IsOpen());
    this->httpServerProxy->HandlePendingRequests();
    Timing::Sleep(0.1);
}

} // namespace Debug
