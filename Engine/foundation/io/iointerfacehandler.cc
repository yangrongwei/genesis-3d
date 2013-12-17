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
#include "io/iointerfacehandler.h"
#include "io/filestream.h"
#include "io/ioserver.h"
#include "io/FileService/fileservicesystem.h"

namespace IO
{
__ImplementClass(IO::IoInterfaceHandler, 'IIOH', Interface::InterfaceHandlerBase);

using namespace Interface;
using namespace Messaging;

//------------------------------------------------------------------------------
/**    
*/
IoInterfaceHandler::IoInterfaceHandler()
{
}

//------------------------------------------------------------------------------
/**    
*/
IoInterfaceHandler::~IoInterfaceHandler()
{
    n_assert(!this->IsOpen());
}

//------------------------------------------------------------------------------
/**
    Opens the Interface message handler which does all the interesting stuff.
    This method already runs in the handler thread.
    The method initializes a minimal thread local Nebula3 runtime, just
    enough to handle the IO messages.
*/
void
IoInterfaceHandler::Open()
{
    InterfaceHandlerBase::Open();
    this->ioServer = IO::IoServer::Create();
    //#if __NEBULA3_HTTP_FILESYSTEM__
    //this->httpClientRegistry = Http::HttpClientRegistry::Create();
    //this->httpClientRegistry->Setup();
    //#endif
}

//------------------------------------------------------------------------------
/**
    Closes the Interface message handler. This will shut down the
    minimal Nebula3 runtime, the method runs in the handler thread and is
    called just before the thread shuts down.
*/
void
IoInterfaceHandler::Close()
{
    //#if __NEBULA3_HTTP_FILESYSTEM__
    //this->httpClientRegistry->Discard();
    //this->httpClientRegistry = 0;
    //#endif
    this->ioServer = 0;
    InterfaceHandlerBase::Close();
}

//------------------------------------------------------------------------------
/**
    Handles incoming messages. This method runs in the handler thread.
*/
bool
IoInterfaceHandler::HandleMessage(const GPtr<Message>& msg)
{

    n_assert(msg.isvalid());
	if (msg->CheckId(ReadStream::Id))
	{
		this->OnReadStream(msg.downcast<IO::ReadStream>());
	}
    else if (msg->CheckId(MountArchive::Id))
    {
        this->OnMountArchive(msg.downcast<IO::MountArchive>());
		msg->SetHandled(true);
    }
    else if (msg->CheckId(CreateDirectory::Id))
    {
        this->OnCreateDirectory(msg.downcast<IO::CreateDirectory>());
		msg->SetHandled(true);
    }
    else if (msg->CheckId(DeleteDirectory::Id))
    {
        this->OnDeleteDirectory(msg.downcast<IO::DeleteDirectory>());
		msg->SetHandled(true);
    }
    else if (msg->CheckId(DeleteFile::Id))
    {
        this->OnDeleteFile(msg.downcast<IO::DeleteFile>());
		msg->SetHandled(true);
    }
    else if (msg->CheckId(WriteStream::Id))
    {
        this->OnWriteStream(msg.downcast<IO::WriteStream>());
		msg->SetHandled(true);
    }
    else if (msg->CheckId(CopyFile::Id))
    {
        this->OnCopyFile(msg.downcast<IO::CopyFile>());
		msg->SetHandled(true);
    }
	else if (msg->CheckId(UseFileService::Id))
	{
		GPtr<UseFileService> msg_ufs = msg.downcast<UseFileService>();
		bool use = msg_ufs->GetUseFileService();
		if (use)
		{
			ioServer->SetupFileService(msg_ufs->GetFileServiceDir(), msg_ufs->GetCacheDir(), msg_ufs->GetServerAddress());
		}
		msg.downcast<UseFileService>()->SetResult(true);
		msg->SetHandled(true);
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
IoInterfaceHandler::DoWork()
{
	ioServer->DoWork();
	Super::DoWork();
}

//------------------------------------------------------------------------------
/**
*/
void
IoInterfaceHandler::OnMountArchive(const GPtr<IO::MountArchive>& msg)
{
    //n_printf("IOInterface: MountArchive %s\n", msg->GetURI().AsString().AsCharPtr());
    IO::IoServer::Instance()->MountArchive(URI(msg->GetFileName().Value()));
}

//------------------------------------------------------------------------------
/**
*/
void
IoInterfaceHandler::OnCreateDirectory(const GPtr<IO::CreateDirectory>& msg)
{
    //n_printf("IOInterface: CreateDirectory %s\n", msg->GetURI().AsString().AsCharPtr());
    msg->SetResult(IO::IoServer::Instance()->CreateDirectory(URI(msg->GetFileName().Value())));
}

//------------------------------------------------------------------------------
/**
*/
void
IoInterfaceHandler::OnDeleteDirectory(const GPtr<IO::DeleteDirectory>& msg)
{
    //n_printf("IOInterface: DeleteDirectory %s\n", msg->GetURI().AsString().AsCharPtr());
    msg->SetResult(IO::IoServer::Instance()->DeleteDirectory(URI(msg->GetFileName().Value())));
}

//------------------------------------------------------------------------------
/**
*/
void
IoInterfaceHandler::OnCopyFile(const GPtr<IO::CopyFile>& msg)
{
    //n_printf("IOInterface: CopyDirectory %s %s\n", msg->GetFromURI().AsString().AsCharPtr(), msg->GetToURI().AsString().AsCharPtr());
    msg->SetResult(IO::IoServer::Instance()->CopyFile(msg->GetFromURI(), msg->GetToURI()));
}

//------------------------------------------------------------------------------
/**
*/
void
IoInterfaceHandler::OnDeleteFile(const GPtr<IO::DeleteFile>& msg)
{
    //n_printf("IOInterface: DeleteFile %s\n", msg->GetURI().AsString().AsCharPtr());
    msg->SetResult(IO::IoServer::Instance()->DeleteFile(URI(msg->GetFileName().Value())));
}

//------------------------------------------------------------------------------
/**
*/
void
IoInterfaceHandler::OnWriteStream(const GPtr<IO::WriteStream>& msg)
{
    ioServer->_WriteStream(msg);
}

//------------------------------------------------------------------------------
/**
*/
void
IoInterfaceHandler::OnReadStream(const GPtr<IO::ReadStream>& msg)
{
    msg->SetResult(false);
	ioServer->_ReadStream(msg);
}

} // namespace IO