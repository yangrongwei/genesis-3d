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
#include "io/consolehandler.h"

namespace IO
{
__ImplementClass(IO::ConsoleHandler, 'CONH', Core::RefCounted);

using namespace Util;

//------------------------------------------------------------------------------
/**
*/
ConsoleHandler::ConsoleHandler() :
    isOpen(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
ConsoleHandler::~ConsoleHandler()
{
    if (this->IsOpen())
    {
        this->Close();
    }
}

//------------------------------------------------------------------------------
/**
*/
void
ConsoleHandler::Open()
{
    n_assert(!this->IsOpen());
    this->isOpen = true;
}

//------------------------------------------------------------------------------
/**
*/
void
ConsoleHandler::Close()
{
    n_assert(this->IsOpen());
    this->isOpen = false;
}

//------------------------------------------------------------------------------
/**
*/
void
ConsoleHandler::Update()
{
    n_assert(this->IsOpen());
}

//------------------------------------------------------------------------------
/**
*/
void
ConsoleHandler::Print(const String& /*s*/)
{
    // empty, override in subclass as needed
}

//------------------------------------------------------------------------------
/**
*/
void
ConsoleHandler::Error(const String& /*s*/)
{
    // empty, override in subclass as needed
}

//------------------------------------------------------------------------------
/**
*/
void
ConsoleHandler::Warning(const String& s)
{
    // empty, override in subclass as needed
}

//------------------------------------------------------------------------------
/**
*/
void
ConsoleHandler::Confirm(const String& s)
{
    // empty, override in subclass as needed
}

//------------------------------------------------------------------------------
/**
*/
void
ConsoleHandler::DebugOut(const String& s)
{
    // empty, override in subclass as needed
}

//------------------------------------------------------------------------------
/**
*/
bool
ConsoleHandler::HasInput()
{
    return false;
}

//------------------------------------------------------------------------------
/**
*/
String
ConsoleHandler::GetInput()
{
    return "";
}

} // namespace IO
