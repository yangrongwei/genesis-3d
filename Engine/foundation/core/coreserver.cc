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
#include "core/coreserver.h"

namespace Core
{
__ImplementClass(Core::CoreServer, 'CORS', Core::RefCounted);
__ImplementThreadSingleton(Core::CoreServer);

using namespace IO;

//------------------------------------------------------------------------------
/**
*/
CoreServer::CoreServer() :
    companyName("CYOU-INC.COM"),
    appName("Genesis Application"),
    rootDirectory("home:"),
    isOpen(false)
{
    __ConstructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
*/
CoreServer::~CoreServer()
{
    if (this->IsOpen())
    {
        this->Close();
    }
    __DestructThreadSingleton;
}

//------------------------------------------------------------------------------
/**
*/
void
CoreServer::Open()
{
    n_assert(!this->IsOpen());
    this->isOpen = true;

    // create console object
	if (Console::HasInstance())
	{
		this->con = Console::Instance();
		if (!this->con->IsOpen())
		{
			this->con->Open();
		}
	}
	else
	{
		this->con = Console::Create();
		this->con->Open();
	}
}

//------------------------------------------------------------------------------
/**
*/
void
CoreServer::Close()
{
    n_assert(this->IsOpen());

    // shutdown console
    this->con = 0;

    this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
*/
void 
CoreServer::Trigger()
{
    this->con->Update();
}
} // namespace Core
