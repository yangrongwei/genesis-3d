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
#pragma once
//------------------------------------------------------------------------------
/**
    @class IO::Console
    
    Nebula3's console, this is the central place for command-
    line-style communication with the user. By default, all output will
    just disappear unless console handlers are added. Console handlers
    are user-derivable objects which do something with the output and
    may provide text input.

*/
#include "core/types.h"
#include "util/string.h"
#include "util/array.h"
#include "core/refcounted.h"
#include "core/singleton.h"
#include "core/ptr.h"
#include "io/consolehandler.h"
#include "threading/threadid.h"
#include "threading/criticalsection.h"

//------------------------------------------------------------------------------
namespace IO
{
class Console : public Core::RefCounted
{
    __DeclareClass(Console);
    __DeclareImageSingleton(Console);
public:
    /// constructor
    Console();
    /// destructor
    virtual ~Console();
    /// open the console
    void Open();
    /// close the console
    void Close();
    /// return true if currently open
    bool IsOpen() const;
    /// called per-frame
    void Update();
    /// attach a console handler to the console
    void AttachHandler(const GPtr<ConsoleHandler>& handler);
    /// remove a console handler from the console
    void RemoveHandler(const GPtr<ConsoleHandler>& handler);
    /// get array of currently installed handlers
    Util::Array<GPtr<ConsoleHandler> > GetHandlers() const;
    /// return true if user input is available
    bool HasInput() const;
    /// get user input
    Util::String GetInput() const;
    /// print a formatted line (printf style)
    void __cdecl Print(const char* fmt, ...);
    /// print a formatted line (printf style)
    void __cdecl Print(const char* fmt, va_list argList);
    /// print a string object
    void Print(const Util::String& s);
    /// put an error message and cancel execution
    void __cdecl Error(const char* fmt, ...);
    /// put an error message and cancel execution
    void __cdecl Error(const char* fmt, va_list argList);
    /// put a warning message
    void __cdecl Warning(const char* fmt, ...);
    /// put a warning message
    void __cdecl Warning(const char* fmt, va_list argList);
    /// display a confirmation message box
    void __cdecl Confirm(const char* fmt, ...);
    /// display a confirmation message box
    void __cdecl Confirm(const char* fmt, va_list argList);
    /// print a debug-only message
    void __cdecl DebugOut(const char* fmt, ...);
    /// print a debug-only message
    void __cdecl DebugOut(const char* fmt, va_list argList);

protected:
    Threading::ThreadId creatorThreadId;
    Threading::CriticalSection critSect;
    Util::Array<GPtr<ConsoleHandler> > consoleHandlers;
    bool isOpen;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
Console::IsOpen() const
{
    return this->isOpen;
}

//------------------------------------------------------------------------------
/**
*/
inline Util::Array<GPtr<ConsoleHandler> >
Console::GetHandlers() const
{
    this->critSect.Enter();
    Util::Array<GPtr<ConsoleHandler> > handlers = this->consoleHandlers;
    this->critSect.Leave();
    return handlers;
}

} // namespace IO
//------------------------------------------------------------------------------
