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
#include "io/console.h"
#include "threading/thread.h"
#if __WIN32__
#include "io/win32/win32consolehandler.h"
#elif __XBOX360__
#include "io/xbox360/xbox360consolehandler.h"
#elif __WII__
#include "io/wii/wiiconsolehandler.h"
#elif __PS3__
#include "io/ps3/ps3consolehandler.h"
#elif __OSX__
#include "io/osx/osxconsolehandler.h"
#elif __ANDROID__
#include "io/android/androidconsolehandler.h"
#endif

namespace IO
{
__ImplementClass(IO::Console, 'CNSL', Core::RefCounted);
__ImplementImageSingleton(IO::Console);

using namespace Core;
using namespace Util;
using namespace Threading;

//------------------------------------------------------------------------------
/**
*/
Console::Console() :
    isOpen(false)
{
    __ConstructImageSingleton;
    this->creatorThreadId = Thread::GetMyThreadId();
}

//------------------------------------------------------------------------------
/**
*/
Console::~Console()
{
    this->critSect.Enter();
    if (this->IsOpen())
    {
        this->Close();
    }
    __DestructImageSingleton;
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Open()
{
    this->critSect.Enter();
    n_assert(!this->IsOpen());

    // create default console handlers
    #if __WIN32__
    GPtr<ConsoleHandler> consoleHandler = Win32::Win32ConsoleHandler::Create();
    #elif __XBOX360__
    GPtr<ConsoleHandler> consoleHandler = Xbox360::Xbox360ConsoleHandler::Create();
    #elif __WII__
    GPtr<ConsoleHandler> consoleHandler = Wii::WiiConsoleHandler::Create();
    #elif __PS3__
    GPtr<ConsoleHandler> consoleHandler = PS3::PS3ConsoleHandler::Create();
    #elif __OSX__
    GPtr<ConsoleHandler> consoleHandler = OSX::OSXConsoleHandler::Create();
	#elif __ANDROID__
	GPtr<ConsoleHandler> consoleHandler = Android::AndroidConsoleHandler::Create();
    #endif
    this->AttachHandler(consoleHandler);    

    this->isOpen = true;
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Close()
{
    this->critSect.Enter();
    n_assert(this->IsOpen());
    
    // cleanup console handlers
    while (this->consoleHandlers.Size() > 0)
    {
        this->RemoveHandler(this->consoleHandlers[0]);
    }
    this->isOpen = false;
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
    This method may only be called from the main thread!
*/
void
Console::Update()
{
    this->critSect.Enter();

    // make sure we're only called from the MainThread
    n_assert(Thread::GetMyThreadId() == this->creatorThreadId);
    IndexT i;
    for (i = 0; i < this->consoleHandlers.Size(); i++)
    {
        this->consoleHandlers[i]->Update();
    }
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
Console::AttachHandler(const GPtr<ConsoleHandler>& h)
{
    this->critSect.Enter();
    n_assert(h.isvalid());
    h->Open();
    // add new console handler before default handler, so that the custom
    // handler has a chance to inspect errors before the default handler
    // exits the process
    this->consoleHandlers.Insert(0, h);
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
Console::RemoveHandler(const GPtr<ConsoleHandler>& h)
{
    this->critSect.Enter();
    n_assert(h.isvalid());
    IndexT index = this->consoleHandlers.FindIndex(h);
    n_assert(InvalidIndex != index);
    this->consoleHandlers[index]->Close();
    this->consoleHandlers.EraseIndex(index);
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
bool
Console::HasInput() const
{
    this->critSect.Enter();
    bool retval = false;
    n_assert(this->IsOpen());
    IndexT i;
    for (i = 0; i < this->consoleHandlers.Size(); i++)
    {
        if (this->consoleHandlers[i]->HasInput())
        {
            retval = true;
            break;
        }
    }
    this->critSect.Leave();
    return retval;
}

//------------------------------------------------------------------------------
/**
*/
String
Console::GetInput() const
{
    this->critSect.Enter();
    String retval;
    n_assert(this->IsOpen());
    IndexT i;
    for (i = 0; i < this->consoleHandlers.Size(); i++)
    {
        if (this->consoleHandlers[i]->HasInput())
        {
            retval = this->consoleHandlers[i]->GetInput();
            break;
        }
    }
    this->critSect.Leave();
    return retval;
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Print(const char* fmt, ...)
{
    n_assert(this->IsOpen());
    va_list argList;
    va_start(argList, fmt);
    this->Print(fmt, argList);
    va_end(argList);
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Print(const char* fmt, va_list argList)
{
    this->critSect.Enter();
    n_assert(this->IsOpen());
    String str;
    str.FormatArgList(fmt, argList);
    IndexT i;
    for (i = 0; i < this->consoleHandlers.Size(); i++)
    {
        this->consoleHandlers[i]->Print(str);
    }
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Print(const String& str)
{
    this->critSect.Enter();
    n_assert(this->IsOpen());
    IndexT i;
    for (i = 0; i < this->consoleHandlers.Size(); i++)
    {
        this->consoleHandlers[i]->Print(str);
    }
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Error(const char* fmt, ...)
{
    n_assert(this->IsOpen());
    va_list argList;
    va_start(argList, fmt);
    this->Error(fmt, argList);
    va_end(argList);
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Error(const char* fmt, va_list argList)
{
    this->critSect.Enter();
    n_assert(this->IsOpen());
    String str;
    str.FormatArgList(fmt, argList);
    IndexT i;
    for (i = 0; i < this->consoleHandlers.Size(); i++)
    {
        this->consoleHandlers[i]->Error(str);
    }
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
Console::DebugOut(const char* fmt, ...)
{
    n_assert(this->IsOpen());
    va_list argList;
    va_start(argList, fmt);
    this->DebugOut(fmt, argList);
    va_end(argList);
}

//------------------------------------------------------------------------------
/**
*/
void
Console::DebugOut(const char* fmt, va_list argList)
{
    this->critSect.Enter();
    n_assert(this->IsOpen());
    String str;
    str.FormatArgList(fmt, argList);
    IndexT i;
    for (i = 0; i < this->consoleHandlers.Size(); i++)
    {
        this->consoleHandlers[i]->DebugOut(str);
    }
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Warning(const char* fmt, ...)
{
    n_assert(this->IsOpen());
    va_list argList;
    va_start(argList, fmt);
    this->Warning(fmt, argList);
    va_end(argList);
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Warning(const char* fmt, va_list argList)
{
    this->critSect.Enter();
    n_assert(this->IsOpen());
    String str;
    str.FormatArgList(fmt, argList);
    IndexT i;
    for (i = 0; i < this->consoleHandlers.Size(); i++)
    {
        this->consoleHandlers[i]->Warning(str);
    }
    this->critSect.Leave();
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Confirm(const char* fmt, ...)
{
    n_assert(this->IsOpen());
    va_list argList;
    va_start(argList, fmt);
    this->Confirm(fmt, argList);
    va_end(argList);
}

//------------------------------------------------------------------------------
/**
*/
void
Console::Confirm(const char* fmt, va_list argList)
{
    this->critSect.Enter();
    n_assert(this->IsOpen());
    String str;
    str.FormatArgList(fmt, argList);
    IndexT i;
    for (i = 0; i < this->consoleHandlers.Size(); i++)
    {
        this->consoleHandlers[i]->Confirm(str);
    }
    this->critSect.Leave();
}

}
