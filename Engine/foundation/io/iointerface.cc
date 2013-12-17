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
#include "stdneb.h"
#include "io/iointerface.h"
#include "io/iointerfacehandler.h"
//#include "messaging/blockinghandlerthread.h"
#include "messaging/asynhandlerthread.h"
namespace IO
{
__ImplementClass(IO::IoInterface, 'IIOF', Interface::InterfaceBase);
__ImplementImageSingleton(IO::IoInterface);

using namespace Messaging;
using namespace Interface;

//------------------------------------------------------------------------------
/**
*/
IoInterface::IoInterface()
{
    __ConstructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
IoInterface::~IoInterface()
{
    __DestructImageSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void
IoInterface::Open()
{
    // setup the message handler thread object
    //GPtr<BlockingHandlerThread> handlerThread = BlockingHandlerThread::Create();
	GPtr<AsynHandlerThread> handlerThread = AsynHandlerThread::Create();
    handlerThread->SetName("IoInterface Thread");
    handlerThread->SetCoreId(System::Cpu::IoThreadCore);
#if __WII_
    handlerThread->SetPriority(Thread::NormalBoost);
#endif        
    handlerThread->AttachHandler(IoInterfaceHandler::Create());
    this->SetHandlerThread(handlerThread.cast<HandlerThreadBase>());

    InterfaceBase::Open();
}

//------------------------------------------------------------------------------
/**
*/
bool 
IoInterface::IsAsynLoad( const URI& uri )
{
	Util::String pth = uri.AsString() ;

	return false ;
}

} // namespace IO
