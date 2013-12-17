/****************************************************************************
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
#include "resource/resource_stdneb.h"
#include "resource/resourceinterface.h"
#include "resource/resource.h"
#include "io/iointerface.h"
#include "io/memorystream.h"
#include "messaging/blockinghandlerthread.h"

using namespace Messaging;
using namespace IO;

namespace Resources
{
	__ImplementClass(Resources::ResourceInterface, 'RRIF', Interface::InterfaceBase);

	__ImplementClass(Resources::ResourceHandler, 'RRHD', Interface::InterfaceHandlerBase);

	__ImplementClass(Resources::ResMsg, 'rrmg', Messaging::Message);
	__ImplementMsgId(ResMsg);
	__ImplementClass(Resources::ResLoadMsg, 'rrlm', Messaging::Message);
	__ImplementMsgId(ResLoadMsg);
	__ImplementClass(Resources::ResSaveMsg, 'rrsm', Messaging::Message);
	__ImplementMsgId(ResSaveMsg);

	ResourceInterface::ResourceInterface()
	{

	}
	//------------------------------------------------------------------------
	ResourceInterface::~ResourceInterface()
	{
		n_assert( !this->IsOpen() );
	}
	//------------------------------------------------------------------------
	void 
		ResourceInterface::Open()
	{
		// setup the message handler thread object
		GPtr<BlockingHandlerThread> handlerThread = BlockingHandlerThread::Create();
		handlerThread->SetName("ResourceInterface Thread");
		handlerThread->SetCoreId(System::Cpu::IoThreadCore);
#if __WII_
		handlerThread->SetPriority(Thread::NormalBoost);
#endif        
		handlerThread->AttachHandler(ResourceHandler::Create());
		this->SetHandlerThread(handlerThread.cast<Messaging::HandlerThreadBase>());

		Super::Open();
	}

	//------------------------------------------------------------------------
	ResourceHandler::ResourceHandler()
	{

	}
	//------------------------------------------------------------------------

	ResourceHandler::~ResourceHandler()
	{
		n_assert(!this->IsOpen());
	}
	//------------------------------------------------------------------------
	/// open the handler
	void 
		ResourceHandler::Open()
	{
		Super::Open();
		n_assert( IoInterface::Instance() );
	}
	//------------------------------------------------------------------------
	/// close the handler
	void 
		ResourceHandler::Close()
	{
		Super::Close();
	}
	//------------------------------------------------------------------------
	/// handle a message, return true if handled
	bool 
		ResourceHandler::HandleMessage(const GPtr<Messaging::Message>& msg)
	{
		n_assert(msg.isvalid());
		if (msg->CheckId(ResLoadMsg::Id))
		{
			this->OnLoad( msg.downcast<ResLoadMsg>() );
		}
		else if (msg->CheckId(ResSaveMsg::Id))
		{
			this->OnSave( msg.downcast<ResSaveMsg>() );
		}
		else
		{
			// unknown message
			return false;        
		}
		// fallthrough: message was handled
		return true;
	}
	//------------------------------------------------------------------------
	void 
		ResourceHandler::OnLoad( const GPtr<ResLoadMsg>& msg )
	{
		n_assert(msg.isvalid());

		if ( !msg->GetLoader() || !msg->GetResource() || !msg->GetStream() )
		{
			msg->SetHandled(true);
			msg->SetResult(false);
			return;
		}

		const GPtr<IO::Stream>& loadStream = msg->GetStream();
		loadStream->SetAccessMode( IO::Stream::ReadAccess );
		msg->GetLoader()->SetStream( loadStream );

		bool bLoadOK = false;
		if ( loadStream->Open() )
		{
			bLoadOK = msg->GetResource()->Load( msg->GetLoader() );
			loadStream->Close();
		}

		msg->SetHandled(true);
		msg->SetResult(bLoadOK);
	}
	//------------------------------------------------------------------------
	void 
		ResourceHandler::OnSave( const GPtr<ResSaveMsg>& msg )
	{
		n_assert(msg.isvalid());

		if ( !msg->GetSaver() || !msg->GetResource() || !msg->GetStream() )
		{
			msg->SetHandled(true);
			msg->SetResult(false);
			return;
		}

		const GPtr<IO::Stream>& saveStream = msg->GetStream();
		saveStream->SetAccessMode(IO::Stream::WriteAccess);
		msg->GetSaver()->SetStream( saveStream );
		bool bSaveOK = false;

		bSaveOK = msg->GetResource()->Save( msg->GetSaver() );	//	写出数据到pMemStream中

		msg->SetHandled(true);
		msg->SetResult(bSaveOK);
	}


}


