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
#include "app/application.h"
#include "core/sysfunc.h"
#include "foundation/threading/thread.h"

namespace App
{
__ImplementThreadSingleton(App::Application);

//------------------------------------------------------------------------------
/**
*/
Application::Application() :
    companyName("CYOU-INC.COM"),
    appName("Genesis Application"),
    appID("RLTITLEID"), 
    appVersion("1.00"),
    isOpen(false),
	isStart(false),
    returnCode(0)
{
    __ConstructThreadSingleton;
    Core::SysFunc::Setup();
}

//------------------------------------------------------------------------------
/**
*/
Application::~Application()
{
    n_assert(!this->isOpen);
}

//------------------------------------------------------------------------------
/**
*/
bool
Application::Open()
{
    n_assert(!this->isOpen);
    this->isOpen = true;
    return true;
}

//------------------------------------------------------------------------------
/**
*/
bool
Application::Start()
{
	n_assert(!this->isStart);
	this->isStart = true;
	return true;
}

//------------------------------------------------------------------------------
/**
*/
void
Application::Close()
{
    n_assert(this->isOpen);
    this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
*/
void
Application::Run()
{
    // empty, override in subclass
}

//------------------------------------------------------------------------------
/**
    This method must be called right before the main() function's end.
    It will properly cleanup the Nebula3 runtime, its static objects,
    private heaps and finally produce a refcount leak and mem leak report
    (debug builds only).
*/
void
Application::Exit()
{
    Core::SysFunc::Exit(this->returnCode);
}

void 
Application::ShutDown()
{
	Threading::Thread::DestoryThreadRunTime(true);
}

} // namespace App